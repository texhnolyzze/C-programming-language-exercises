#include <unity.h>
#include <stdarg.h>
#include "cross_referencer/cross_referencer.h"
#include "utils/test_utils/test_utils.h"
#include "utils/binary_tree/binary_tree.h"
#include "utils/list/list.h"

void setUp(void) {}

void tearDown(void) {}

void test1(void) {
    stdin_from_file("test-1.txt");
    struct btree *tree = build_cross_reference(100);
    TEST_ASSERT_EQUAL_INT(0, tree->size);
    free_cross_reference(tree);
}

void assert_lines(struct btree *tree, const char *word, ...) {
    struct btree_node *node = binary_tree_search(tree, word);
    TEST_ASSERT_NOT_NULL(node);
    struct list *list = (struct list *) node->value;
    struct list_node *current = list->head;
    va_list args;
    va_start(args, word);
    for (;;) {
        int i = va_arg(args, int);
        if (i == -1) {
            TEST_ASSERT_NULL(current);
            break;
        }
        TEST_ASSERT_NOT_NULL(current);
        TEST_ASSERT_EQUAL_INT(i, current->data);
        current = current->next;
    }
    va_end(args);
}

void test2(void) {
    stdin_from_file("test-2.txt");
    struct btree *tree = build_cross_reference(100);
    TEST_ASSERT_EQUAL_INT(19, tree->size);
    assert_lines(tree, "In", 1, -1);
    assert_lines(tree, "all", 1, -1);
    assert_lines(tree, "and", 4, -1);
    assert_lines(tree, "application", 2, -1);
    assert_lines(tree, "been", 3, -1);
    assert_lines(tree, "cases", 1, -1);
    assert_lines(tree, "data", 3, -1);
    assert_lines(tree, "disk", 4, -1);
    assert_lines(tree, "has", 3, 5, -1);
    assert_lines(tree, "holding", 3, -1);
    assert_lines(tree, "if", 2, -1);
    assert_lines(tree, "is", 3, -1);
    assert_lines(tree, "not", 3, -1);
    assert_lines(tree, "potential", 5, -1);
    assert_lines(tree, "some", 5, -1);
    assert_lines(tree, "synchronized", 4, -1);
    assert_lines(tree, "to", 4, -1);
    assert_lines(tree, "which", 3, 5, -1);
    assert_lines(tree, "your", 2, -1);
    free_cross_reference(tree);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test2);
    return UNITY_END();
}