#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

struct list *list_create() {
    struct list *res = malloc(sizeof(struct list));
    if (res == NULL) {
        fprintf(stderr, "list_create: insufficient memory\n");
        return NULL;
    }
    res->size = 0;
    res->tail = NULL;
    res->head = NULL;
    return res;
}

int list_add(struct list *l, void *elem) {
    if (l->head == NULL) {
        l->head = malloc(sizeof(struct list_node));
        if (l->head == NULL) {
            fprintf(stderr, "list_add: not enough memory\n");
            return -1;
        }
        l->tail = l->head;
        l->head->data = elem;
        l->head->next = NULL;
    } else {
        l->tail->next = malloc(sizeof(struct list_node));
        if (l->tail->next == NULL) {
            fprintf(stderr, "list_add: not enough memory\n");
            return -1;
        }
        l->tail = l->tail->next;
        l->tail->data = elem;
        l->tail->next = NULL;
    }
    l->size++;
    return 0;
}

void list_free(struct list *l, bool free_elems) {
    if (l == NULL) {
        return;
    }
    struct list_node *current = l->head;
    struct list_node *prev;
    while (current != NULL) {
        if (free_elems && current->data != NULL) {
            free(current->data);
        }
        prev = current;
        current = current->next;
        free(prev);
    }
    free(l);
}


