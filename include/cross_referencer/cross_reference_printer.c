#include <stdlib.h>
#include <stdio.h>
#include "cross_reference_printer.h"
#include "utils/single_positive_int_arg_parser/single_positive_int_arg_parser.h"
#include "cross_referencer.h"
#include "utils/binary_tree/binary_tree.h"
#include "utils/list/list.h"

static size_t max_word_len = 1000;

int cross_reference_printer_init(int argc, const char **argv) {
    if (argc > 0) {
        return parse_single_int_arg(argc, argv, &max_word_len);
    }
    return 0;
}

static void print(struct btree_node *node) {
    printf("%s: [", (char *) node->key);
    struct list *list = (struct list *) node->value;
    struct list_node *current = list->head;
    while (current != NULL) {
        printf("%zu", (size_t) current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void cross_reference_print(void) {
    struct btree *tree = build_cross_reference(max_word_len);
    if (tree == NULL) {
        exit(1);
    }
    binary_tree_traverse(tree, print);
    free_cross_reference(tree);
}
