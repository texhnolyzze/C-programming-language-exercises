

#ifndef SANDBOXTEST_QUEUE_H
#define SANDBOXTEST_QUEUE_H

#include <corecrt.h>
#include <stdbool.h>

typedef struct queue {
    void **q;
    size_t start;
    size_t end;
    size_t capacity;
    size_t size;
} queue;

struct queue *create_queue(size_t capacity);

void queue_add(struct queue *q, void *elem);

void * queue_remove(struct queue *q);

size_t queue_size(struct queue *q);

void queue_free(struct queue *q, bool free_elems);

#endif //SANDBOXTEST_QUEUE_H
