#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "cross_referencer.h"
#include "utils/word_tokenizer/word_tokenizer.h"
#include "utils/single_positive_int_arg_parser/single_positive_int_arg_parser.h"
#include "utils/strings/strings.h"
#include "utils/binary_tree/binary_tree.h"
#include "utils/list/list.h"

static size_t max_word_len = 1000;

void print_cross_reference(struct btree_node *node);

void free_indices(struct btree_node *node);

void cross_reference(void) {
    struct word_tokenizer *tokenizer = word_tokenizer_create(max_word_len);
    if (tokenizer == NULL) {
        exit(1);
    }
    struct btree_node *btree_root = binary_tree_create();
    if (btree_root == NULL) {
        exit(1);
    }
    while (true) {
        word_tokenizer_next_word(tokenizer);
        if (tokenizer->state < 0) {
            fprintf(stderr, "Can't read next word from stdin. Tokenizer state: %d\n", tokenizer->state);
            exit(1);
        }
        if (tokenizer->state == 1) {
            break;
        }
        char *word = tokenizer->word;
        char *word_dup = strdup_len_known(word, tokenizer->word_len);
        if (word_dup == NULL) {
            fprintf(stderr, "Can't duplicate word %s (not enough memory)\n", word);
            exit(1);
        }
        struct btree_node *node = binary_tree_search(btree_root, word_dup, (int (*)(const void *, const void *)) strcmp);
        struct list *indices;
        if (node == NULL) {
            indices = list_create();
            if (indices == NULL) {
                exit(1);
            }
            if (binary_tree_put(btree_root, word_dup, indices, (int (*)(const void *, const void *)) strcmp) != 0) {
                exit(1);
            }
        } else {
            indices = (struct list *) node->value;
        }
        if (list_add(indices, (void *) tokenizer->word_line_number) != 0) {
            exit(1);
        }
    }
    binary_tree_traverse(btree_root, print_cross_reference);
    word_tokenizer_free(tokenizer);
    binary_tree_traverse(btree_root, free_indices);
    binary_tree_free(btree_root, true, false);
}

int cross_reference_init(int argc, const char **argv) {
    if (argc != 0) {
        return parse_single_int_arg(argc, argv, &max_word_len);
    }
    return 0;
}

void print_cross_reference(struct btree_node *node) {
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

void free_indices(struct btree_node *node) {
    struct list *list = (struct list *) node->value;
    list_free(list, false);
}
