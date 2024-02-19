#ifndef SANDBOX_HASH_TABLE_H
#define SANDBOX_HASH_TABLE_H

#include <corecrt.h>
#include <stdbool.h>

struct ht_node {
    void *key;
    void *value;
    struct ht_node *next;
};

struct hash_table {
    size_t size;
    size_t capacity;
    size_t threshold;
    float load_factor;
    struct ht_node **nodes;

    const size_t (*hash)(const void *);
    const bool (*equals)(const void *, const void *);
};

struct hash_table *hash_table_create(
        size_t init_capacity,
        float load_factor,
        const size_t (*hash)(const void *),
        const bool (*equals)(const void *, const void *)
);

void hash_table_free(struct hash_table *table, bool free_keys, bool free_values);

int hash_table_put(struct hash_table *table, void *key, void *value);

struct ht_node *hash_table_get(const struct hash_table *table, const void *key);

#endif //SANDBOX_HASH_TABLE_H
