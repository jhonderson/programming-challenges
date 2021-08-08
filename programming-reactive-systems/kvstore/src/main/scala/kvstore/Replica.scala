package kvstore

import akka.actor.{ OneForOneStrategy, PoisonPill, Props, SupervisorStrategy, Terminated, ActorRef, Actor, actorRef2Scala }
import kvstore.Arbiter.*
import akka.pattern.{ ask, pipe }
import scala.concurrent.duration.*
import akka.util.Timeout
import akka.actor.ReceiveTimeout
import akka.actor.SupervisorStrategy.Restart
import java.util.stream.Collectors

object Replica:
  sealed trait Operation:
    def key: String
    def id: Long
  case class Insert(key: String, value: String, id: Long) extends Operation
  case class Remove(key: String, id: Long) extends Operation
  case class Get(key: String, id: Long) extends Operation

  sealed trait OperationReply
  case class OperationAck(id: Long) extends OperationReply
  case class OperationFailed(id: Long) extends OperationReply
  case class GetResult(key: String, valueOption: Option[String], id: Long) extends OperationReply

  case class OperationTimeout(id: Long)

  def props(arbiter: ActorRef, persistenceProps: Props): Props = Props(Replica(arbiter, persistenceProps))

class Replica(val arbiter: ActorRef, persistenceProps: Props) extends Actor:
  import Replica.*
  import Replicator.*
  import Persistence.*
  import context.dispatcher

  /*
   * The contents of this actor is just a suggestion, you can implement it in any way you like.
   */
  
  var kv = Map.empty[String, String]
  // a map from secondary replicas to replicators
  var secondaries = Map.empty[ActorRef, ActorRef]
  // the current set of replicators
  var replicators = Set.empty[ActorRef]

  var pendingPersistenceRequests = Map.empty[Long, (ActorRef, Persist)]
  var pendingReplicationRequests = Map.empty[Long, (ActorRef, Set[ActorRef])]

  arbiter ! Join

  override def supervisorStrategy = SupervisorStrategy.stoppingStrategy // On any failure issue an stop command

  val persistenceActor = context.actorOf(persistenceProps)

  context.setReceiveTimeout(100.milliseconds)

  def receive =
    case JoinedPrimary   => context.become(leader)
    case JoinedSecondary => context.become(replica(0))

  /* TODO Behavior for  the leader role. */
  val leader: Receive =
    case Insert(key, value, id) =>
      kv += (key -> value)
      persistChange(key, Some(value), id)
      context.system.scheduler.scheduleOnce(1.second, self, OperationTimeout(id))
    case Remove(key, id) =>
      kv -= key
      persistChange(key, None, id)
      context.system.scheduler.scheduleOnce(1.second, self, OperationTimeout(id))
    case Get(key, id) =>
      sender() ! GetResult(key, kv.get(key), id)
    case Persisted(key, id) =>
      onPersistedMessage(key, id, (sender, request) => {
        if (replicators.isEmpty) {
          sender ! OperationAck(id)
        } else {
          replicators.foreach(replicator => replicator ! Replicate(key, request.valueOption, id))
          pendingReplicationRequests += (id -> (sender, replicators))
        }
      })
    case ReceiveTimeout =>
      onReceiveTimeout()
    case Replicas(replicas) =>
      val secondaryReplicas = replicas.filter(_ != self)
      val removedReplicas = secondaries.keySet -- secondaryReplicas
      val newReplicas = secondaryReplicas -- secondaries.keySet
      newReplicas.foreach(newRep => {
        val replicator = context.actorOf(Replicator.props(newRep))
        secondaries += (newRep -> replicator)
        replicators += replicator
        kv.zipWithIndex.foreach((pair, index) => replicator ! Replicate(pair._1, Some(pair._2), pair._1.hashCode))
      })
      removedReplicas.foreach(removedRep => {
        val replicator = secondaries(removedRep)
        secondaries -= removedRep
        replicators -= replicator
        pendingReplicationRequests.foreach((id, tuple) => {
          var (requestSender, pendingReplicators) = tuple
          pendingReplicators -= replicator
          pendingReplicationRequests += (id, (requestSender, pendingReplicators))
        })
        context.stop(replicator)
      })
    case Replicated(key, id) =>
      if (pendingReplicationRequests.contains(id)) {
        var (requestSender, pendingReplicators) = pendingReplicationRequests(id)
        pendingReplicators -= sender()
        if (pendingReplicators.isEmpty) {
          pendingReplicationRequests -= id
          requestSender ! OperationAck(id)
        } else {
          pendingReplicationRequests += (id, (requestSender, pendingReplicators))
        }
      }
    case OperationTimeout(id) =>
      if (pendingPersistenceRequests.contains(id)) {
        val (requestSender, _) = pendingPersistenceRequests(id)
        pendingPersistenceRequests -= id
        requestSender ! OperationFailed(id)
      } else if (pendingReplicationRequests.contains(id)) {
        val (sender, pendingReplicators) = pendingReplicationRequests(id)
        pendingReplicationRequests -= id
        if (pendingReplicators.isEmpty) {
          sender ! OperationAck(id)
        } else {
          sender ! OperationFailed(id)
        }
      }

  /* TODO Behavior for the replica role. */
  def replica(currentSeq: Int): Receive =
    case Get(key, id) =>
      sender() ! GetResult(key, kv.get(key), id)
    case Snapshot(key, valueOption, seq) =>
      if (seq < currentSeq) {
        sender() ! SnapshotAck(key, seq)
      } else if (seq == currentSeq) {
        if (valueOption.isEmpty) {
          kv -= key
        } else {
          kv += (key -> valueOption.get)
        }
        persistChange(key, valueOption, seq)
        context.become(replica(currentSeq + 1))
      }
    case Persisted(key, seq) =>
      onPersistedMessage(key, seq, (sender, request) => sender ! SnapshotAck(key, seq))
    case ReceiveTimeout =>
      onReceiveTimeout()

  def persistChange(key: String, valueOption: Option[String], id: Long) =
    val persistRequest: Persist = Persist(key, valueOption, id)
    pendingPersistenceRequests += (id -> (sender(), persistRequest))
    persistenceActor ! persistRequest

  def onPersistedMessage(key: String, id: Long, acknFn: (ActorRef, Persist) => Unit) =
    if (pendingPersistenceRequests.contains(id)) {
      val (requestSender, persistentRequest) = pendingPersistenceRequests(id)
      pendingPersistenceRequests -= id
      acknFn(requestSender, persistentRequest)
    }

  def onReceiveTimeout() =
    pendingPersistenceRequests.foreach((id, tuple) => {
      val (_, persistenceRequest) = tuple
      persistenceActor ! persistenceRequest
    })
