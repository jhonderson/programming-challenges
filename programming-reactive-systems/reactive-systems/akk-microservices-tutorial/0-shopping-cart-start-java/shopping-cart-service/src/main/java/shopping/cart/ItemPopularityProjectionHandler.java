package shopping.cart;

import akka.projection.eventsourced.EventEnvelope;
import akka.projection.jdbc.javadsl.JdbcHandler;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import shopping.cart.repository.HibernateJdbcSession;
import shopping.cart.repository.ItemPopularityRepository;

@Slf4j
public class ItemPopularityProjectionHandler extends JdbcHandler<EventEnvelope<ShoppingCart.Event>, HibernateJdbcSession> {

    private final String tag;
    private final ItemPopularityRepository repository;

    public ItemPopularityProjectionHandler(String tag, ItemPopularityRepository repository) {
        this.tag = tag;
        this.repository = repository;
    }

    private ItemPopularity findOrNew(final String itemId) {
        return repository.findById(itemId).orElseGet(() -> new ItemPopularity(itemId, 0L, 0L));
    }

    @Override
    public void process(final HibernateJdbcSession session, final EventEnvelope<ShoppingCart.Event> eventEventEnvelope)
            throws Exception {
        ShoppingCart.Event event = eventEventEnvelope.event();
        if (event instanceof ShoppingCart.ItemAdded) {
            ShoppingCart.ItemAdded added = (ShoppingCart.ItemAdded) event;
            String itemId = added.itemId;

            final ItemPopularity existentItemPopularity = findOrNew(itemId);
            final ItemPopularity updatedItemPopularity = existentItemPopularity.changeCount(added.quantity);
            repository.save(updatedItemPopularity);

            log.info(
                    "ItemPopularityProjectionHandler({}) item popularity for '{}': [{}]",
                    this.tag,
                    itemId,
                    updatedItemPopularity.getCount());
        } else {
            // skip all other events, such as `CheckedOut`
        }
    }
}
