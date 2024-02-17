

#ifndef SANDBOXTEST_BINARY_TREE_H
#define SANDBOXTEST_BINARY_TREE_H

struct btree_node {
    void *key;
    void *value;
    struct btree_node *left;
    struct btree_node *right;
};

struct btree_node *binary_tree_create();

void binary_tree_free(struct btree_node *root, bool free_key, bool free_value);

int binary_tree_put(struct btree_node *root, void *key, void *value, int (*cmp)(const void *, const void *));

struct btree_node *binary_tree_search(struct btree_node *root, void *key, int (*cmp)(const void *, const void *));

void binary_tree_traverse(struct btree_node *root, void (*callback)(struct btree_node *));

#endif //SANDBOXTEST_BINARY_TREE_H
