#ifndef SANDBOXTEST_CROSS_REFERENCER_H
#define SANDBOXTEST_CROSS_REFERENCER_H

struct btree *build_cross_reference(size_t max_word_len);

void free_cross_reference(struct btree *tree);

#endif //SANDBOXTEST_CROSS_REFERENCER_H
