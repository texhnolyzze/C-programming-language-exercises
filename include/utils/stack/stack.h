

#ifndef SANDBOX_DOUBLE_STACK_H
#define SANDBOX_DOUBLE_STACK_H

#include <stdbool.h>

#define MAX_DOUBLE_STACK_DEPTH 100

typedef struct stack {
    void **s;
    size_t capacity;
    size_t top;
} stack;

struct stack *stack_create(size_t capacity);

void stack_push(struct stack *s, void *elem);

void *stack_pop(struct stack *s);

size_t stack_size(struct stack *s);

void *stack_peek(struct stack *s);

void stack_clear(struct stack *s, bool free_elems);

void stack_free(struct stack *s, bool free_elems);

#endif //SANDBOX_DOUBLE_STACK_H
