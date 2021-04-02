## Start dependencies

1. Start dependencies:

```bash
docker-compose up -d
```

2. Create tables:
```bash
docker exec -i shopping-cart-service_postgres-db_1 psql -U shopping-cart -t < ddl-scripts/create_tables.sql
docker exec -i shopping-cart-service_postgres-db_1 psql -U shopping-cart -t < ddl-scripts/create_user_tables.sql
```

## Running the sample code

1. Compile:

    ```
    mvn compile
    ```

2. Start a first node:

    ```
    mvn compile exec:exec -DAPP_CONFIG=local1.conf
    ```

3. (Optional) Start another node with different ports:

    ```
    mvn compile exec:exec -DAPP_CONFIG=local2.conf
    ```

4. Check for service readiness

    ```
    curl http://localhost:9101/ready
    ```
