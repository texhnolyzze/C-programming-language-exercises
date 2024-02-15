#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "binary_tree.h"

struct btree_node *binary_tree_create() {
    struct btree_node *result = malloc(sizeof(struct btree_node));
    if (result == NULL) {
        fprintf(stderr, "binary_tree_create: not enough memory\n");
        return NULL;
    }
    result->key = NULL;
    result->value = NULL;
    result->left = NULL;
    result->right = NULL;
    return result;
}

void binary_tree_free(struct btree_node *root, bool free_key, bool free_value) {
    if (root == NULL) {
        return;
    }
    if (free_key) {
        free(root->key);
    }
    if (free_value && root->value != NULL) {
        free(root->value);
    }
    binary_tree_free(root->left, free_key, free_value);
    binary_tree_free(root->right, free_key, free_value);
    free(root);
}

void *binary_tree_put(struct btree_node *root, void *key, void *value, int (*cmp)(const void *, const void *)) {
    if (root->key == NULL) {
        root->key = key;
        root->value = value;
        return NULL;
    }
    int c = cmp(key, root->key);
    if (c < 0) {
        if (root->left == NULL) {
            root->left = binary_tree_create();
            root->left->key = key;
            root->left->value = value;
            return NULL;
        } else {
            return binary_tree_put(root->left, key, value, cmp);
        }
    } else if (c > 0) {
        if (root->right == NULL) {
            root->right = binary_tree_create();
            root->right->key = key;
            root->right->value = value;
            return NULL;
        } else {
            return binary_tree_put(root->right, key, value, cmp);
        }
    } else {
        void *prev_value = root->value;
        root->value = value;
        return prev_value;
    }
}

struct btree_node *binary_tree_search(struct btree_node *root, void *key, int (*cmp)(const void *, const void *)) {
    if (root == NULL) {
        return NULL;
    }
    int c = cmp(key, root->key);
    if (c < 0) {
        return binary_tree_search(root->left, key, cmp);
    } else if (c > 0) {
        return binary_tree_search(root->right, key, cmp);
    } else {
        return root;
    }
}

void binary_tree_traverse(struct btree_node *root, void (*callback)(struct btree_node *)) {
    if (root == NULL) {
        return;
    }
    binary_tree_traverse(root->left, callback);
    callback(root);
    binary_tree_traverse(root->right, callback);
}
