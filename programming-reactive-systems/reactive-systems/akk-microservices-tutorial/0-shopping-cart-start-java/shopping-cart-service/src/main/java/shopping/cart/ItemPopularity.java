package shopping.cart;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Version;

@Entity
@Table(name = "item_popularity")
public class ItemPopularity {
    @Id
    private final String itemId;

    @Version
    private final Long version;

    private final long count;

    public ItemPopularity() {
        this("", null, 0);
    }

    public ItemPopularity(String itemId, Long version, long count) {
        this.itemId = itemId;
        this.version = version;
        this.count = count;
    }

    public String getItemId() {
        return itemId;
    }

    public long getCount() {
        return count;
    }

    public long getVersion() {
        return version;
    }

    public ItemPopularity changeCount(long delta) {
        return new ItemPopularity(itemId, version, count + delta);
    }
}
