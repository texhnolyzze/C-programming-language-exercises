#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "word_frequency.h"
#include "utils/single_positive_int_arg_parser/single_positive_int_arg_parser.h"
#include "cross_referencer/cross_referencer.h"
#include "utils/binary_tree/binary_tree.h"
#include "utils/list/list.h"

static size_t max_word_len = 1000;

int init_word_frequency(int argc, const char **argv) {
    if (argc > 0) {
        return parse_single_int_arg(argc, argv, &max_word_len);
    }
    return 0;
}

static int cmp(size_t s1, size_t s2) {
    if (s1 < s2) {
        return 1;
    } else if (s1 > s2) {
        return -1;
    } else {
        return 0;
    }
}

static struct btree *index;

static void index_by_word_frequency(struct btree_node *cross_ref_node) {
    struct list *indices = (struct list *) cross_ref_node->value;
    struct btree_node *index_node = binary_tree_search(index, (void *) indices->size);
    struct list *words;
    if (index_node == NULL) {
        words = list_create();
        if (words == NULL) {
            exit(1);
        }
        if (binary_tree_put(index, (void *) indices->size, words) != 0) {
            exit(1);
        }
    } else {
        words = index_node->value;
    }
    char *word = (char *) cross_ref_node->key;
    if (list_add(words, word) != 0) {
        exit(1);
    }
}

static void print_word_frequency(struct btree_node *node) {
    size_t freq = (size_t) node->key;
    printf("%zu: [", freq);
    struct list *words = node->value;
    struct list_node *current = words->head;
    while (current != NULL) {
        printf("%s", (char *) current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

static void free_words(struct btree_node *node) {
    struct list *words = node->value;
    list_free(words, false);
}

void word_frequency(void) {
    struct btree *cross_ref = build_cross_reference(max_word_len);
    if (cross_ref == NULL) {
        fprintf(stderr, "Can't build cross reference\n");
        exit(1);
    }
    index = binary_tree_create((const int (*)(const void *, const void *)) cmp);
    if (index == NULL) {
        fprintf(stderr, "Can't create btree index\n");
        exit(1);
    }
    binary_tree_traverse(cross_ref, index_by_word_frequency);
    binary_tree_traverse(index, print_word_frequency);
    free_cross_reference(cross_ref);
    binary_tree_traverse(index, free_words);
    binary_tree_free(index, false, false);
}
