package shopping.cart;

import akka.actor.typed.ActorSystem;
import akka.actor.typed.DispatcherSelector;
import akka.cluster.sharding.typed.javadsl.ClusterSharding;
import akka.cluster.sharding.typed.javadsl.EntityRef;
import akka.grpc.GrpcServiceException;
import io.grpc.Status;
import lombok.extern.slf4j.Slf4j;
import shopping.cart.proto.*;
import shopping.cart.repository.ItemPopularityRepository;

import java.time.Duration;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;
import java.util.concurrent.Executor;
import java.util.concurrent.TimeoutException;
import java.util.stream.Collectors;

@Slf4j
public class ShoppingCartServiceImpl implements ShoppingCartService {
    private final Duration timeout;
    private final ClusterSharding sharding;
    private final ItemPopularityRepository repository;
    private final Executor blockingJdbcExecutor;

    public ShoppingCartServiceImpl(final ActorSystem<?> system, ItemPopularityRepository repository) {
        DispatcherSelector dispatcherSelector =
                DispatcherSelector.fromConfig("akka.projection.jdbc.blocking-jdbc-dispatcher");
        this.blockingJdbcExecutor = system.dispatchers().lookup(dispatcherSelector);
        this.repository = repository;

        this.timeout = system.settings().config().getDuration("shopping-cart-service.ask-timeout");
        this.sharding = ClusterSharding.get(system);
    }

    @Override
    public CompletionStage<Cart> addItem(final AddItemRequest addItemRequest) {
        log.info("addItem {} to cart {}", addItemRequest.getItemId(), addItemRequest.getCartId());
        EntityRef<ShoppingCart.Command> commandEntityRef = sharding.entityRefFor(ShoppingCart.ENTITY_KEY,
                addItemRequest.getCartId());
        CompletionStage<ShoppingCart.Summary> reply = commandEntityRef.askWithStatus(
                replyTo -> new ShoppingCart.AddItem(addItemRequest.getItemId(), addItemRequest.getQuantity(), replyTo),
                timeout);
        CompletionStage<Cart> cart = reply.thenApply(ShoppingCartServiceImpl::toProtoCart);
        return convertError(cart);
    }

    @Override
    public CompletionStage<Cart> checkout(CheckoutRequest in) {
        log.info("checkout cart {}", in.getCartId());
        EntityRef<ShoppingCart.Command> commandEntityRef = sharding.entityRefFor(ShoppingCart.ENTITY_KEY,
                in.getCartId());
        CompletionStage<ShoppingCart.Summary> reply = commandEntityRef.askWithStatus(
                replyTo -> new ShoppingCart.Checkout(replyTo), timeout
        );
        CompletionStage<Cart> cart = reply.thenApply(ShoppingCartServiceImpl::toProtoCart);
        return convertError(cart);
    }

    @Override
    public CompletionStage<Cart> getCart(GetCartRequest in) {
        log.info("Getting cart {}", in.getCartId());
        EntityRef<ShoppingCart.Command> commandEntityRef = sharding.entityRefFor(ShoppingCart.ENTITY_KEY,
                in.getCartId());
        CompletionStage<ShoppingCart.Summary> reply = commandEntityRef.ask(
                ShoppingCart.Get::new, timeout
        );
        CompletionStage<Cart> protoCart =
                reply.thenApply(
                        cart -> {
                            if (cart.items.isEmpty())
                                throw new GrpcServiceException(
                                        Status.NOT_FOUND.withDescription("Cart " + in.getCartId() + " not found"));
                            else return toProtoCart(cart);
                        });
        return convertError(protoCart);
    }

    @Override
    public CompletionStage<GetItemPopularityResponse> getItemPopularity(GetItemPopularityRequest in) {
        CompletionStage<Optional<ItemPopularity>> itemPopularity =
                CompletableFuture.supplyAsync(
                        () -> repository.findById(in.getItemId()), blockingJdbcExecutor);

        return itemPopularity.thenApply(
                popularity -> {
                    long count = popularity.map(ItemPopularity::getCount).orElse(0L);
                    return GetItemPopularityResponse.newBuilder()
                            .setItemId(in.getItemId())
                            .setPopularityCount(count)
                            .build();
                });
    }

    private static Cart toProtoCart(ShoppingCart.Summary cart) {
        List<Item> protoItems =
                cart.items.entrySet().stream()
                        .map(
                                entry ->
                                        Item.newBuilder()
                                                .setItemId(entry.getKey())
                                                .setQuantity(entry.getValue())
                                                .build())
                        .collect(Collectors.toList());

        return Cart.newBuilder().setCheckedOut(cart.checkedOut).addAllItems(protoItems).build();
    }

    private static <T> CompletionStage<T> convertError(CompletionStage<T> response) {
        return response.exceptionally(
                ex -> {
                    if (ex instanceof TimeoutException) {
                        throw new GrpcServiceException(
                                Status.UNAVAILABLE.withDescription("Operation timed out"));
                    } else {
                        throw new GrpcServiceException(
                                Status.INVALID_ARGUMENT.withDescription(ex.getMessage()));
                    }
                });
    }
}
