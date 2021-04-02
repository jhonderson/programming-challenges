package shopping.order;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;

import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import shopping.order.proto.Item;
import shopping.order.proto.OrderRequest;
import shopping.order.proto.OrderResponse;
import shopping.order.proto.ShoppingOrderService;

@Slf4j
public class ShoppingOrderServiceImpl implements ShoppingOrderService {
    @Override
    public CompletionStage<OrderResponse> order(OrderRequest in) {
        int total = 0;
        for (Item item : in.getItemsList()) {
            total += item.getQuantity();
        }
        log.info("Order {} items from cart {}.", total, in.getCartId());
        OrderResponse response = OrderResponse.newBuilder().setOk(true).build();
        return CompletableFuture.completedFuture(response);
    }
}
