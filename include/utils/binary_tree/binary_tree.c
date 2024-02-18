#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "binary_tree.h"

struct btree *binary_tree_create(const int (*cmp)(const void *, const void *)) {
    struct btree *result = malloc(sizeof(struct btree));
    if (result == NULL) {
        fprintf(stderr, "binary_tree_create: not enough memory\n");
        return NULL;
    }
    result->size = 0;
    result->root = NULL;
    result->cmp = cmp;
    return result;
}

static void free_node(struct btree_node *node, bool free_key, bool free_value) {
    if (node == NULL) {
        return;
    }
    if (free_key && node->key != NULL) {
        free(node->key);
    }
    if (free_value && node->value != NULL) {
        free(node->value);
    }
    free_node(node->left, free_key, free_value);
    free_node(node->right, free_key, free_value);
    free(node);
}

void binary_tree_free(struct btree *tree, bool free_key, bool free_value) {
    if (tree == NULL) {
        return;
    }
    if (tree->size != 0) {
        free_node(tree->root, free_key, free_value);
    }
    free(tree);
}

static struct btree_node *put(
        struct btree_node *root,
        void *key,
        void *value,
        const int (*cmp)(const void *, const void *),
        int *err_code
) {
    if (root == NULL) {
        struct btree_node *node = malloc(sizeof(struct btree_node));
        if (node == NULL) {
            fprintf(stderr, "binary_tree.put: not enough memory\n");
            *err_code = -1;
            return NULL;
        }
        node->left = NULL;
        node->right = NULL;
        node->key = key;
        node->value = value;
        return node;
    } else {
        int c = cmp(key, root->key);
        if (c < 0) {
            root->left = put(root->left, key, value, cmp, err_code);
        } else if (c > 0) {
            root->right = put(root->right, key, value, cmp, err_code);
        } else {
            root->value = value;
        }
        return root;
    }
}

int binary_tree_put(struct btree *tree, void *key, void *value) {
    if (tree == NULL) {
        return -2;
    }
    int err_code = 0;
    tree->root = put(tree->root, key, value, tree->cmp, &err_code);
    if (err_code == 0) {
        tree->size++;
    }
    return err_code;
}

static struct btree_node *search(struct btree_node *root, void *key, const int (*cmp)(const void *, const void *)) {
    if (root == NULL) {
        return NULL;
    }
    int c = cmp(key, root->key);
    if (c < 0) {
        return search(root->left, key, cmp);
    } else if (c > 0) {
        return search(root->right, key, cmp);
    } else {
        return root;
    }
}

struct btree_node *binary_tree_search(struct btree *tree, void *key) {
    if (tree == NULL || tree->size == 0) {
        return NULL;
    }
    return search(tree->root, key, tree->cmp);
}

static void traverse(struct btree_node *node, void (*callback)(struct btree_node *)) {
    if (node == NULL) {
        return;
    }
    traverse(node->left, callback);
    callback(node);
    traverse(node->right, callback);
}

void binary_tree_traverse(struct btree *tree, void (*callback)(struct btree_node *)) {
    if (tree == NULL || tree->size == 0) {
        return;
    }
    traverse(tree->root, callback);
}
