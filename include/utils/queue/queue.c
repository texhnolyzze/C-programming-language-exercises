

#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

struct queue *create_queue(size_t capacity) {
    struct queue *q = malloc(sizeof(queue));
    if (q == NULL) {
        return NULL;
    }
    q->capacity = capacity;
    q->start = 0;
    q->end = 0;
    q->q = malloc(capacity * sizeof(void *));
    if (q->q == NULL) {
        free(q);
        return NULL;
    }
    q->size = 0;
    return q;
}

void queue_add(struct queue *q, void *elem) {
    size_t size = queue_size(q);
    if (size == q->capacity) {
        fprintf(stderr, "add: queue full\n");
        return;
    }
    q->q[q->end] = elem;
    if (q->end == q->capacity - 1) {
        q->end = 0;
    } else {
        q->end++;
    }
    q->size++;
}

void * queue_remove(struct queue *q) {
    size_t size = queue_size(q);
    if (size == 0) {
        fprintf(stderr, "remove: queue empty\n");
        return NULL;
    }
    char *res = q->q[q->start];
    if (q->start == q->capacity - 1) {
        q->start = 0;
    } else {
        q->start++;
    }
    q->size--;
    return res;
}

size_t queue_size(const struct queue *q) {
    return q->size;
}

void queue_free(struct queue *q, bool free_elems) {
    if (free_elems) {
        for (size_t i = 0; i < q->size; ++i) {
            free(*(q->q + i));
        }
    }
    free(q->q);
    free(q);
}
