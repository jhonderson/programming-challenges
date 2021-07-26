/**
 * Copyright (C) 2009-2013 Typesafe Inc. <http://www.typesafe.com>
 */
package actorbintree

import akka.actor.*
import scala.collection.immutable.Queue

object BinaryTreeSet:

  trait Operation:
    def requester: ActorRef
    def id: Int
    def elem: Int

  trait OperationReply:
    def id: Int

  /** Request with identifier `id` to insert an element `elem` into the tree.
    * The actor at reference `requester` should be notified when this operation
    * is completed.
    */
  case class Insert(requester: ActorRef, id: Int, elem: Int) extends Operation

  /** Request with identifier `id` to check whether an element `elem` is present
    * in the tree. The actor at reference `requester` should be notified when
    * this operation is completed.
    */
  case class Contains(requester: ActorRef, id: Int, elem: Int) extends Operation

  /** Request with identifier `id` to remove the element `elem` from the tree.
    * The actor at reference `requester` should be notified when this operation
    * is completed.
    */
  case class Remove(requester: ActorRef, id: Int, elem: Int) extends Operation

  /** Request to perform garbage collection */
  case object GC

  /** Holds the answer to the Contains request with identifier `id`.
    * `result` is true if and only if the element is present in the tree.
    */
  case class ContainsResult(id: Int, result: Boolean) extends OperationReply

  /** Message to signal successful completion of an insert or remove operation. */
  case class OperationFinished(id: Int) extends OperationReply


class BinaryTreeSet extends Actor with akka.actor.ActorLogging:
  import BinaryTreeSet.*
  import BinaryTreeNode.*

  def createRoot: ActorRef = context.actorOf(BinaryTreeNode.props(0, initiallyRemoved = true))

  var root = createRoot

  // optional (used to stash incoming operations during garbage collection)
  var pendingQueue = Queue.empty[Operation]

  // optional
  def receive = normal

  // optional
  /** Accepts `Operation` and `GC` messages. */
  val normal: Receive =
    case operation: Operation =>
      root ! operation
    case GC =>
      val newRoot = createRoot
      root ! CopyTo(newRoot)
      context.become(garbageCollecting(newRoot))

  // optional
  /** Handles messages while garbage collection is performed.
    * `newRoot` is the root of the new binary tree where we want to copy
    * all non-removed elements into.
    */
  def garbageCollecting(newRoot: ActorRef): Receive =
    case operation: Operation =>
      pendingQueue = pendingQueue.enqueue(operation)
    case CopyFinished =>
      root ! PoisonPill
      root = newRoot
      pendingQueue.foreach(operation => root ! operation)
      pendingQueue = Queue.empty[Operation]
      context.become(normal)
    case GC =>
      // Ignoring GC messages while garbage collecting

object BinaryTreeNode:
  trait Position

  case object Left extends Position
  case object Right extends Position

  case class CopyTo(treeNode: ActorRef)
  /**
   * Acknowledges that a copy has been completed. This message should be sent
   * from a node to its parent, when this node and all its children nodes have
   * finished being copied.
   */
  case object CopyFinished

  def props(elem: Int, initiallyRemoved: Boolean) = Props(classOf[BinaryTreeNode],  elem, initiallyRemoved)

class BinaryTreeNode(val elem: Int, initiallyRemoved: Boolean) extends Actor with akka.actor.ActorLogging:
  import BinaryTreeNode.*
  import BinaryTreeSet.*

  var subtrees = Map[Position, ActorRef]()
  var removed = initiallyRemoved

  // optional
  def receive = normal

  // optional
  /** Handles `Operation` messages and `CopyTo` requests. */
  val normal: Receive =
    case Insert(requester, id, newElement) =>
      if (elem == newElement) {
        removed = false
        requester ! OperationFinished(id)
      } else if (newElement < elem) {
        insertInNode(Left, requester, id, newElement)
      } else {
        insertInNode(Right, requester, id, newElement)
      }
    case Contains(requester, id, lookupElem) =>
      if (elem == lookupElem) {
        requester ! ContainsResult(id, !removed)
      } else if (lookupElem < elem) {
        searchInNode(Left, requester, id, lookupElem)
      } else {
        searchInNode(Right, requester, id, lookupElem)
      }
    case Remove(requester, id, elemToRemove) =>
      if (elem == elemToRemove) {
        removed = true
        requester ! OperationFinished(id)
      } else if (elemToRemove < elem) {
        removeInNode(Left, requester, id, elemToRemove)
      } else {
        removeInNode(Right, requester, id, elemToRemove)
      }
    case CopyTo(treeNode) =>
      var insertConfirmed = true
      if (!removed) {
        treeNode ! Insert(self, elem, elem)
        insertConfirmed = false
      }
      var expected: Set[ActorRef] = Set()
      subtrees.get(Left).foreach(subtree =>
        subtree ! CopyTo(treeNode)
        expected = expected + subtree
      )
      subtrees.get(Right).foreach(subtree =>
        subtree ! CopyTo(treeNode)
        expected = expected + subtree
      )
      context.become(copying(expected, insertConfirmed))

  // optional
  /** `expected` is the set of ActorRefs whose replies we are waiting for,
    * `insertConfirmed` tracks whether the copy of this node to the new tree has been confirmed.
    */
  def copying(expected: Set[ActorRef], insertConfirmed: Boolean): Receive =
    if (expected.isEmpty && insertConfirmed)
      context.parent ! CopyFinished
      normal
    else
      case OperationFinished(id) =>
        context.become(copying(expected, true))
      case CopyFinished =>
        sender ! PoisonPill
        context.become(copying(expected - sender, insertConfirmed))

  def insertInNode(position: Position, requester: ActorRef, id: Int, newElement: Int) =
    subtrees.get(position) match
      case None =>
        subtrees += (position -> context.actorOf(BinaryTreeNode.props(newElement, false)))
        requester ! OperationFinished(id)
      case Some(childNode) =>
        childNode ! Insert(requester, id, newElement)

  def searchInNode(position: Position, requester: ActorRef, id: Int, lookupElem: Int) =
    subtrees.get(position) match
      case None =>
        requester ! ContainsResult(id, false)
      case Some(childNode) =>
        childNode ! Contains(requester, id, lookupElem)

  def removeInNode(position: Position, requester: ActorRef, id: Int, elemToRemove: Int) =
    subtrees.get(position) match
      case None =>
        requester ! OperationFinished(id)
      case Some(childNode) =>
        childNode ! Remove(requester, id, elemToRemove)
