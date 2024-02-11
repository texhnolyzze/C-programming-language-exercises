//
// Created by ikarimullin on 01.02.2024.
//

#ifndef SANDBOXTEST_QUEUE_H
#define SANDBOXTEST_QUEUE_H

#include <corecrt.h>

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

void queue_free(struct queue *q);

#endif //SANDBOXTEST_QUEUE_H
