#ifndef SANDBOXTEST_LIST_H
#define SANDBOXTEST_LIST_H

#include <corecrt.h>

struct list {
    size_t size;
    struct list_node *head;
    struct list_node *tail;
};

struct list_node {
    void *data;
    struct list_node *next;
};

struct list *list_create();

void list_free(struct list *l, bool free_elems);

int list_add(struct list *l, void *elem);

#endif //SANDBOXTEST_LIST_H
