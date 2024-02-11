//
// Created by ikarimullin on 24.01.2024.
//

#include <stdio.h>
#include <malloc.h>
#include "stack.h"

struct stack *stack_create(size_t capacity) {
    stack *result = malloc(sizeof(stack));
    if (result == NULL) {
        fprintf(stderr, "stack_create: not enough memory\n");
        return NULL;
    }
    result->capacity = capacity;
    result->top = 0;
    result->s = malloc(capacity * sizeof(void *));
    if (result->s == NULL) {
        fprintf(stderr, "stack_create: not enough memory\n");
        free(result);
        return NULL;
    }
    return result;
}

void stack_push(struct stack *s, void *elem) {
    if (s->top < s->capacity) {
        s->s[s->top++] = elem;
    } else {
        fprintf(stderr, "Error: stack full\n");
    }
}

void *stack_pop(struct stack *s) {
    if (s->top > 0) {
        return s->s[--s->top];
    } else {
        fprintf(stderr, "Error: stack empty\n");
        return NULL;
    }
}

size_t stack_size(struct stack *s) {
    return s->top;
}

void *stack_peek(struct stack *s) {
    if (s->top > 0) {
        return s->s[s->top - 1];
    } else {
        fprintf(stderr, "Error: stack empty\n");
        return NULL;
    }
}

void stack_clear(struct stack *s) {
    for (int i = 0; i < s->top; ++i) {
        free(s->s[i]);
    }
    s->top = 0;
}

void stack_free(struct stack *s) {
    for (int i = 0; i < s->top; ++i) {
        free(s->s[i]);
    }
    free(s->s);
    free(s);
}
