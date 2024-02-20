#include <stdlib.h>
#include "unity.h"
#include "utils/hash_table/hash_table.h"
#include "utils/test_utils/test_utils.h"

void setUp() {
    setup_random();
}

void tearDown() {

}

size_t hash(int key) {
    return key;
}

bool equals(int k1, int k2) {
    return k1 == k2;
}

void run_test(size_t n, const struct random_test_key_value *data, struct hash_table *table) {
    for (size_t i = 0; i < n; ++i) {
        TEST_ASSERT_NULL(hash_table_get(table, (void *) data[i].key));
        TEST_ASSERT_EQUAL_INT(0, hash_table_put(table, (void *) data[i].key, (void *) data[i].value));
        struct ht_node *node = hash_table_get(table, (void *) data[i].key);
        TEST_ASSERT_NOT_NULL(node);
        TEST_ASSERT_EQUAL_INT(data[i].key, node->key);
        TEST_ASSERT_EQUAL_INT(data[i].value, node->value);
    }
    for (size_t i = 0; i < n; ++i) {
        struct ht_node *node = hash_table_get(table, (void *) data[i].key);
        TEST_ASSERT_NOT_NULL(node);
        TEST_ASSERT_EQUAL_INT(data[i].key, node->key);
        TEST_ASSERT_EQUAL_INT(data[i].value, node->value);
    }
    size_t num_removed = 0;
    for (size_t i = 0; i < n; ++i) {
        if (rand() < RAND_MAX / 2) {
            struct ht_node *node = hash_table_get(table, (const void *) data[i].key);
            TEST_ASSERT_NOT_NULL(node);
            TEST_ASSERT_EQUAL_INT(data[i].key, node->key);
            TEST_ASSERT_EQUAL_INT(data[i].value, node->value);
        } else {
            void *value = hash_table_remove(table, (const void *) data[i].key, false);
            TEST_ASSERT_EQUAL_INT(data[i].value, value);
            num_removed++;
        }
    }
    size_t num_found = 0;
    for (size_t i = 0; i < n; ++i) {
        struct ht_node *node = hash_table_get(table, (const void *) data[i].key);
        if (node != NULL) {
            TEST_ASSERT_EQUAL_INT(data[i].key, node->key);
            TEST_ASSERT_EQUAL_INT(data[i].value, node->value);
            num_found++;
            hash_table_remove(table, (const void *) data[i].key, false);
        }
    }
    TEST_ASSERT_EQUAL_INT(n, num_found + num_removed);
}

void random_test(void) {
    size_t n = 10000;
    struct random_test_key_value *data = create_random_test_key_values(n);
    struct hash_table *table = hash_table_create(
            10,
            0.75F,
            (const size_t (*)(const void *)) hash,
            (const bool (*)(const void *, const void *)) equals
    );
    run_test(n, data, table);
    run_test(n, data, table);
    hash_table_free(table, false, false);
    free(data);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(random_test);
    return UNITY_END();
}