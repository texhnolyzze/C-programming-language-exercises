

#ifndef SANDBOX_IO_H
#define SANDBOX_IO_H

#define DEFAULT_MAX_LINE 1000

int read_line(char line[], size_t limit);

char *read_line_dyn(size_t limit, size_t initial_size, int *exit_code, size_t *chars_read);

int read_lines(char **lines, size_t max_lines, size_t max_chars_per_line);

char **read_lines_dyn(
        size_t max_lines,
        size_t max_chars_per_line,
        size_t initial_line_size,
        int *exit_code,
        size_t *lines_read
);

#endif //SANDBOX_IO_H
