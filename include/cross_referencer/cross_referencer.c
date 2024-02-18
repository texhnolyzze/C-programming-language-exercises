#include <stdio.h>
#include <string.h>
#include "cross_referencer.h"
#include "utils/word_tokenizer/word_tokenizer.h"
#include "utils/strings/strings.h"
#include "utils/binary_tree/binary_tree.h"
#include "utils/list/list.h"

void free_indices(struct btree_node *node) {
    struct list *list = (struct list *) node->value;
    list_free(list, false);
}

struct btree *build_cross_reference(const size_t max_word_len) {
    struct word_tokenizer *tokenizer = word_tokenizer_create(max_word_len);
    if (tokenizer == NULL) {
        return NULL;
    }
    struct btree *tree = binary_tree_create((const int (*)(const void *, const void *)) strcmp);
    if (tree == NULL) {
        word_tokenizer_free(tokenizer);
        return NULL;
    }
    while (true) {
        word_tokenizer_next_word(tokenizer);
        if (tokenizer->state < 0) {
            fprintf(stderr, "Can't read next word from stdin. Tokenizer state: %d\n", tokenizer->state);
            word_tokenizer_free(tokenizer);
            free_cross_reference(tree);
            return NULL;
        }
        if (tokenizer->state == 1) {
            break;
        }
        char *word = tokenizer->word;
        char *word_dup = strdup_len_known(word, tokenizer->word_len);
        if (word_dup == NULL) {
            fprintf(stderr, "Can't duplicate word %s (not enough memory)\n", word);
            word_tokenizer_free(tokenizer);
            free_cross_reference(tree);
            return NULL;
        }
        struct btree_node *node = binary_tree_search(tree, word_dup);
        struct list *indices;
        if (node == NULL) {
            indices = list_create();
            if (indices == NULL) {
                word_tokenizer_free(tokenizer);
                free_cross_reference(tree);
                return NULL;
            }
            if (binary_tree_put(tree, word_dup, indices) != 0) {
                word_tokenizer_free(tokenizer);
                free_cross_reference(tree);
                list_free(indices, false);
                return NULL;
            }
        } else {
            indices = (struct list *) node->value;
        }
        if (list_add(indices, (void *) tokenizer->word_line_number) != 0) {
            word_tokenizer_free(tokenizer);
            free_cross_reference(tree);
            return NULL;
        }
    }
    word_tokenizer_free(tokenizer);
    return tree;
}

void free_cross_reference(struct btree *tree) {
    binary_tree_traverse(tree, free_indices);
    binary_tree_free(tree, true, false);
}