

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "expr.h"
#include "utils/stack/stack.h"
#include "op_parser.h"
#include "utils/io/io.h"

#define PUSH_STR(stck, str) \
    double *x = malloc(sizeof(double)); \
    *x = atof(str);                       \
    stack_push(stck, x);

#define PUSH_DBL(stck, dbl) \
    double *x = malloc(sizeof(double)); \
    *x = dbl;               \
    stack_push(stck, x);

#define POP(stck, ptr, target) \
    ptr = stack_pop(stck); \
    target = *ptr;       \
    free(ptr);

const char POSSIBLE_OPERATIONS[8][4] = {
        "+", "-", "/", "*", "%", "sin", "exp", "pow"
};

#define MAX_EXPRESSION_SIZE 1000
#define MAX_EXPRESSION_CHARS 10000

void expr(void) {
    struct stack *s = stack_create(MAX_EXPRESSION_SIZE);
    if (s == NULL) {
        fprintf(stderr, "expr: can't allocate stack\n");
        return;
    }
    char *line;
    int read_line_exit_code;
    size_t chars_read;
    while (true) {
        line = read_line_dyn(MAX_EXPRESSION_CHARS, 64, &read_line_exit_code, &chars_read);
        if (read_line_exit_code == -2) {
            fprintf(stderr, "expr: read_line not enough memory\n");
            stack_free(s, true);
            break;
        } else if (read_line_exit_code == -1 && chars_read == 0) {
            free(line);
            stack_free(s, true);
            break;
        }
        evaluate_expr(line, s);
        free(line);
    }
}

void evaluate_expr(const char *line, struct stack *s) {
    double temp1;
    double temp2;
    double *d_ptr;
    size_t start_offset;
    size_t total_offset;
    while (*line) {
        int cls = getop(line, &start_offset, &total_offset);
        line += start_offset;
        if (cls == NUMBER) {
            PUSH_STR(s, line)
        } else if (cls == END_OF_EXPR) {
            break;
        } else if (cls == UNKNOWN_EXPR) {
            fprintf(stderr, "Unknown expression starting at %s\n", line);
            break;
        } else if (cls == OPERATION) {
            if (strncmp(line, "+", 1) == 0) {
                POP(s, d_ptr, temp1)
                POP(s, d_ptr, temp2)
                PUSH_DBL(s, temp1 + temp2)
            } else if (strncmp(line, "-", 1) == 0) {
                POP(s, d_ptr, temp1)
                POP(s, d_ptr, temp2)
                PUSH_DBL(s, temp2 - temp1)
            } else if (strncmp(line, "*", 1) == 0) {
                POP(s, d_ptr, temp1)
                POP(s, d_ptr, temp2)
                PUSH_DBL(s, temp2 * temp1)
            } else if (strncmp(line, "/", 1) == 0) {
                POP(s, d_ptr, temp1)
                POP(s, d_ptr, temp2)
                PUSH_DBL(s, temp2 / temp1)
            } else if (strncmp(line, "%", 1) == 0) {
                POP(s, d_ptr, temp1)
                POP(s, d_ptr, temp2)
                PUSH_DBL(s, fmod(temp2, temp1))
            } else if (strncmp(line, "sin", 3) == 0) {
                POP(s, d_ptr, temp1)
                PUSH_DBL(s, sin(temp1))
            } else if (strncmp(line, "exp", 3) == 0) {
                POP(s, d_ptr, temp1)
                PUSH_DBL(s, exp(temp1))
            } else if (strncmp(line, "pow", 3) == 0) {
                POP(s, d_ptr, temp1)
                POP(s, d_ptr, temp2)
                PUSH_DBL(s, pow(temp2, temp1))
            } else {
                fprintf(stderr, "Unknown op starting at %s\n", line);
                break;
            }
        }
        line += (total_offset - start_offset);
    }
    if (stack_size(s) != 1) {
        fprintf(stderr, "Stack size != 1 at the end of expression eval\n");
        stack_clear(s, true);
    } else {
        POP(s, d_ptr, temp1)
        printf("%f\n", temp1);
    }
}
