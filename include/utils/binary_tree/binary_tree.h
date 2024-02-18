

#ifndef SANDBOXTEST_BINARY_TREE_H
#define SANDBOXTEST_BINARY_TREE_H

struct btree_node {
    void *key;
    void *value;
    struct btree_node *left;
    struct btree_node *right;
};

struct btree {
    size_t size;
    struct btree_node *root;

    const int (*cmp)(const void *, const void *);
};

struct btree *binary_tree_create(const int (*cmp)(const void *, const void *));

void binary_tree_free(struct btree *tree, bool free_key, bool free_value);

int binary_tree_put(struct btree *tree, void *key, void *value);

struct btree_node *binary_tree_search(struct btree *tree, void *key);

void binary_tree_traverse(struct btree *tree, void (*callback)(struct btree_node *));

#endif //SANDBOXTEST_BINARY_TREE_H
