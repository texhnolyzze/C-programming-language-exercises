#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

struct hash_table *hash_table_create(
        size_t init_capacity,
        float load_factor,
        const size_t (*hash)(const void *),
        const bool (*equals)(const void *, const void *)
) {
    struct hash_table *table = malloc(sizeof(struct hash_table));
    if (table == NULL) {
        fprintf(stderr, "hash_table_create: not enough memory\n");
        return NULL;
    }
    table->size = 0;
    table->load_factor = load_factor <= 0 || load_factor > 1 ? 0.75F : load_factor;
    table->capacity = init_capacity <= 0 ? 10 : init_capacity;
    table->threshold = (float) table->capacity * (table->load_factor + 1.0F);
    table->hash = hash;
    table->equals = equals;
    table->nodes = malloc(table->capacity * sizeof(struct ht_node *));
    if (table->nodes == NULL) {
        free(table);
        fprintf(stderr, "hash_table_create: not enough memory\n");
        return NULL;
    }
    memset(table->nodes, 0, table->capacity * sizeof(struct ht_node *));
    return table;
}

static int put_internal(struct hash_table *table, void *key, void *value) {
    size_t bucket = table->hash(key) % table->capacity;
    struct ht_node *head = table->nodes[bucket];
    if (head == NULL) {
        head = malloc(sizeof(struct ht_node));
        if (head == NULL) {
            fprintf(stderr, "hash_table_put: not enough memory\n");
            return -1;
        }
        head->key = key;
        head->value = value;
        head->next = NULL;
        table->nodes[bucket] = head;
        table->size++;
        return 0;
    }
    struct ht_node *tail;
    struct ht_node *current = head;
    while (current != NULL) {
        tail = current;
        if (table->equals(key, current->key)) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    current = malloc(sizeof(struct ht_node));
    if (current == NULL) {
        fprintf(stderr, "hash_table_put: not enough memory\n");
        return -1;
    }
    tail->next = current;
    current->key = key;
    current->value = value;
    current->next = NULL;
    table->size++;
    return 0;
}

static void free_nodes(const size_t capacity, struct ht_node **nodes, bool free_keys, bool free_values) {
    struct ht_node *current;
    struct ht_node *next;
    for (size_t i = 0; i < capacity; ++i) {
        current = *nodes++;
        while (current != NULL) {
            next = current->next;
            if (free_keys) {
                free(current->key);
            }
            if (free_values && current->value != NULL) {
                free(current->value);
            }
            free(current);
            current = next;
        }
    }
    free(nodes - capacity);
}

static int resize(struct hash_table *table, const size_t new_capacity, const size_t new_threshold) {
    struct ht_node **new_nodes = malloc(new_capacity * (sizeof(struct ht_node *)));
    if (new_nodes == NULL) {
        fprintf(stderr, "hash_table.resize: not enough memory\n");
        return -1;
    }
    memset(new_nodes, 0, new_capacity * sizeof(struct ht_node *));
    size_t old_capacity = table->capacity;
    size_t old_threshold = table->threshold;
    size_t old_size = table->size;
    struct ht_node **old_nodes = table->nodes;
    table->capacity = new_capacity;
    table->threshold = new_threshold;
    table->nodes = new_nodes;
    table->size = 0;
    struct ht_node *current;
    int err = 0;
    for (size_t i = 0; i < old_capacity; ++i) {
        current = *old_nodes++;
        while (current != NULL) {
            err = put_internal(table, current->key, current->value);
            if (err != 0) {
                break;
            }
            current = current->next;
        }
    }
    if (err != 0) {
        table->capacity = old_capacity;
        table->threshold = old_threshold;
        table->nodes = old_nodes;
        table->size = old_size;
        free_nodes(new_capacity, new_nodes, false, false);
        return err;
    }
    free_nodes(old_capacity, old_nodes - old_capacity, false, false);
    return 0;
}

int hash_table_put(struct hash_table *table, void *key, void *value) {
    if (table->size == table->threshold) {
        float new_capacity = table->capacity * (table->load_factor + 1.0F);
        float new_threshold = new_capacity * (table->load_factor + 1.0F);
        int err = resize(table, new_capacity, new_threshold);
        if (err != 0) {
            return err;
        }
    }
    return put_internal(table, key, value);
}

struct ht_node *hash_table_get(const struct hash_table *table, const void *key) {
    size_t bucket = table->hash(key) % table->capacity;
    struct ht_node *node = table->nodes[bucket];
    while (node != NULL) {
        if (table->equals(key, node->key)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void hash_table_free(struct hash_table *table, bool free_keys, bool free_values) {
    free_nodes(table->capacity, table->nodes, free_keys, free_values);
    free(table);
}

void *hash_table_remove(struct hash_table *table, const void *key, bool free_node_key) {
    size_t bucket = table->hash(key) % table->capacity;
    struct ht_node *prev = NULL;
    struct ht_node *node = table->nodes[bucket];
    bool found = false;
    while (node != NULL) {
        if (table->equals(key, node->key)) {
            found = true;
            break;
        }
        prev = node;
        node = node->next;
    }
    if (!found) {
        return NULL;
    }
    if (prev == NULL) {
        table->nodes[bucket] = node->next;
    } else {
        prev->next = node->next;
    }
    if (free_node_key) {
        free(node->key);
    }
    void *value = node->value;
    free(node);
    table->size--;
    return value;
}

