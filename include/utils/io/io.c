

#include <stdio.h>
#include <malloc.h>
#include "io.h"

size_t min(size_t a, size_t b);

int read_line(char line[], const size_t limit) {
    if (limit == 0) {
        return -1;
    }
    int i = 0;
    int c;
    for (; i < limit; ++i) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        line[i] = c;
    }
    if (i != 0) {
        return i;
    }
    return c == '\n' ? 0 : -1;
}

char *read_line_dyn(size_t limit, size_t initial_size, int *exit_code, size_t *chars_read) {
    size_t curr_size = initial_size + 1;
    size_t new_size;
    char *line = malloc(curr_size * sizeof(char));
    char *temp;
    if (line == NULL) {
        fprintf(stderr, "read_line_dyn: not enough memory\n");
        *exit_code = -2;
        *chars_read = 0;
        return NULL;
    }
    size_t i = 0;
    int c = 0;
    while (i < limit) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        if (i == curr_size - 1) {
            if (curr_size == limit + 1) {
                break;
            }
            new_size = min(limit + 1, (curr_size << 1) + 1) * sizeof(char);
            temp = realloc(line, new_size);
            if (temp == NULL) {
                fprintf(stderr, "read_line_dyn: not enough memory\n");
                free(line);
                *exit_code = -2;
                *chars_read = 0;
                return NULL;
            }
            line = temp;
            curr_size = new_size;
        }
        *(line + i++) = c;
    }
    *(line + i) = '\0';
    *chars_read = i;
    *exit_code = c == EOF ? -1 : 0;
    return line;
}

inline size_t min(const size_t a, size_t b) {
    return a < b ? a : b;
}

int read_lines(char **lines, const size_t max_lines, const size_t max_chars_per_line) {
    int n = 0;
    char *line;
    int i;
    while (n < max_lines) {
        line = *lines++;
        i = read_line(line, max_chars_per_line);
        if (i == -1) {
            break;
        }
        line[i] = '\0';
        n++;
    }
    return n;
}

char **read_lines_dyn(
        const size_t max_lines,
        const size_t max_chars_per_line,
        size_t initial_line_size,
        int *exit_code,
        size_t *lines_read
) {
    *lines_read = 0;
    char **lines = malloc(max_lines * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "read_lines_dyn: insufficient memory\n");
        *exit_code = -2;
        return NULL;
    }
    char *line;
    size_t chars_read;
    while (*lines_read < max_lines) {
        chars_read = 0;
        line = read_line_dyn(max_chars_per_line, initial_line_size, exit_code, &chars_read);
        if (*exit_code == -2) {
            for (size_t i = 0; i < *lines_read; ++i) {
                free(lines[i]);
            }
            free(lines);
            *lines_read = 0;
            return NULL;
        } else if (*exit_code == -1 && chars_read == 0) {
            free(line);
            break;
        } else {
            *(lines + *lines_read) = line;
            *lines_read = *lines_read + 1;
        }
    }
    return lines;
}
