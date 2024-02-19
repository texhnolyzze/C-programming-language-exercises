#include <stdlib.h>
#include <time.h>
#include "unity.h"
#include "utils/binary_tree/binary_tree.h"
#include "utils/test_utils/test_utils.h"

void setUp() {
    setup_random();
}

void tearDown() {

}

void increment_value(struct btree_node *node) {
    int value = (int) node->value;
    node->value = (void *) (value + 1);
}

int cmp(int l, int r) {
    if (l < r) {
        return -1;
    } else if (l > r) {
        return +1;
    } else {
        return 0;
    }
}

void assert_value(struct btree *tree, int key, int expected) {
    struct btree_node *node = binary_tree_search(tree, (void *) key);
    if (expected == 0) {
        TEST_ASSERT_NULL(node);
    } else {
        TEST_ASSERT_NOT_NULL(node);
        TEST_ASSERT_EQUAL_INT(expected, node->value);
    }
}

void test() {
    struct btree *tree = binary_tree_create((const int (*)(const void *, const void *)) cmp);
    binary_tree_put(tree, (void *) 1, (void *) 2);
    assert_value(tree, 1, 2);
    binary_tree_put(tree, (void *) 1, (void *) 3);
    assert_value(tree, 1, 3);
    binary_tree_put(tree, (void *) -1, (void *) 4);
    assert_value(tree, -1, 4);
    assert_value(tree, 5, 0);
    binary_tree_put(tree, (void *) 5, (void *) 7);
    assert_value(tree, 5, 7);
    binary_tree_free(tree, false, false);
}

void random_test() {
    size_t n = 10000;
    struct random_test_key_value *data = create_random_test_key_values(n);
    struct btree *tree = binary_tree_create((const int (*)(const void *, const void *)) cmp);
    for (int i = 0; i < n; ++i) {
        TEST_ASSERT_EQUAL(NULL, binary_tree_search(tree, (void *) data[i].key));
        binary_tree_put(tree, (void *) data[i].key, (void *) data[i].value);
    }
    for (int i = 0; i < n; ++i) {
        struct btree_node *node = binary_tree_search(tree, (void *) data[i].key);
        TEST_ASSERT_EQUAL_INT(data[i].value, node->value);
    }
    binary_tree_traverse(tree, increment_value);
    for (int i = 0; i < n; ++i) {
        struct btree_node *node = binary_tree_search(tree, (void *) data[i].key);
        TEST_ASSERT_EQUAL_INT(data[i].value + 1, node->value);
    }
    binary_tree_free(tree, false, false);
    free(data);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    RUN_TEST(random_test);
    return UNITY_END();
}