//
// Created by ikarimullin on 01.02.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "tail.h"
#include "utils/io.h"
#include "utils/queue.h"

#define MAXLINE 10000

static int n = 10;

void tail(void) {
    struct queue *q = create_queue(n);
    if (q == NULL) {
        fprintf(stderr, "tail: not enough memory\n");
        return;
    }
    int exit_code;
    size_t chars_read;
    for (;;) {
        char *line = read_line_dyn(MAXLINE, 128, &exit_code, &chars_read);
        if (exit_code == -2) {
            fprintf(stderr, "tail: read_line_dyn exit_code code == -2 (not enough memory)\n");
            queue_free(q);
            return;
        }
        if (chars_read == 0 && exit_code == -1) {
            break;
        }
        if (queue_size(q) == n) {
            char *temp = queue_remove(q);
            free(temp);
        }
        queue_add(q, line);
    }
    while (queue_size(q) != 0) {
        char *string = queue_remove(q);
        printf("%s\n", string);
        free(string);
    }
    queue_free(q);
}

int tail_init(int argc, const char **argv) {
    if (argc == 0) {
        return 0;
    }
    if (argc > 1) {
        fprintf(stderr, "usage: tail -n");
        return -1;
    }
    const char *arg = *argv;
    int i = atoi(arg);
    if (i >= 0) {
        fprintf(stderr, "usage: tail -n");
        return -1;
    }
    n = -i;
    return 0;
}
