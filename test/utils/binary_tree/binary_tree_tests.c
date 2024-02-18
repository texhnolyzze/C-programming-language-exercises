#include <stdlib.h>
#include <time.h>
#include "unity.h"
#include "utils/binary_tree/binary_tree.h"

void setUp() {
    time_t rawtime;
    time(&rawtime);
    srand(rawtime);
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

struct random_test_data {
    int key;
    int value;
};

int random_unseen_key(struct random_test_data *data, int idx);

void random_test() {
    struct random_test_data data[10000];
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i].key = random_unseen_key(data, i);
        data[i].value = rand();
    }
    struct btree *tree = binary_tree_create((const int (*)(const void *, const void *)) cmp);
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        TEST_ASSERT_EQUAL(NULL, binary_tree_search(tree, (void *) data[i].key));
        binary_tree_put(tree, (void *) data[i].key, (void *) data[i].value);
    }
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        struct btree_node *node = binary_tree_search(tree, (void *) data[i].key);
        TEST_ASSERT_EQUAL_INT(data[i].value, node->value);
    }
    binary_tree_traverse(tree, increment_value);
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        struct btree_node *node = binary_tree_search(tree, (void *) data[i].key);
        TEST_ASSERT_EQUAL_INT(data[i].value + 1, node->value);
    }
    binary_tree_free(tree, false, false);
}

int random_unseen_key(struct random_test_data *data, int idx) {
    for (;;) {
        int key = rand();
        if (key == 0) {
            continue;
        }
        bool unseen = true;
        for (int i = 0; i < idx; i++) {
            if (data[i].key == key) {
                unseen = false;
                break;
            }
        }
        if (unseen) {
            return key;
        }
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    RUN_TEST(random_test);
    return UNITY_END();
}