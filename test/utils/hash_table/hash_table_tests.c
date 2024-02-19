#include <stdlib.h>
#include <time.h>
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

size_t equals(int k1, int k2) {
    return k1 == k2;
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
    for (size_t i = 0; i < n; ++i) {
        TEST_ASSERT_NULL(hash_table_get(table, (void *) data[i].key));
        hash_table_put(table, (void *) data[i].key, (void *) data[i].value);
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
    hash_table_free(table, false, false);
    free(data);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(random_test);
    return UNITY_END();
}