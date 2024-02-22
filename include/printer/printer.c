#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>
#include "printer.h"
#include "utils/io/io.h"

static size_t max_line = 150;
static size_t fold_at = 60;

static char temp_hex[16];

int printer_init(int argc, const char **argv) {
    if (argc % 2 != 0) {
        fprintf(stderr, "Options count must divide by 2");
        return -1;
    }
    if (argc > 4) {
        fprintf(stderr, "Too many options (%d), max is 4", argc);
        return -1;
    }
    for (int i = 0; i < argc; i += 2) {
        const char *arg = *argv++;
        if (strcmp("-ml", arg) == 0) {
            const char *arg_val = *argv++;
            if (sscanf(arg_val, "%zu", &max_line) != 1 || max_line == 0) {
                fprintf(stderr, "Illegal -ml option: %s", arg_val);
                return -1;
            }
        } else if (strcmp("-f", arg) == 0) {
            const char *arg_val = *argv++;
            if (sscanf(arg_val, "%zu", &fold_at) != 1 || fold_at == 0) {
                fprintf(stderr, "Illegal -f option: %s", arg_val);
                return -1;
            }
        } else {
            fprintf(stderr, "Unknown option: %s", arg);
            return -1;
        }
    }
    return 0;
}

static char prev_char = '\0';

static void put(char c) {
    if (prev_char != '\0') {
        if (c == '\n') {
            if (prev_char == ' ') {
                putchar('\n');
                prev_char = '\0';
            } else {
                putchar(prev_char);
                putchar('\n');
                prev_char = '\0';
            }
        } else {
            putchar(prev_char);
            prev_char = c;
        }
    } else {
        if (c == '\n') {
            putchar('\n');
        } else {
            prev_char = c;
        }
    }
}

void printer(void) {
    char *line = malloc((max_line + 1) * sizeof(char));
    size_t max_word = max_line * 6 * sizeof(char);
    char *word = malloc(max_word);
    if (line == NULL || word == NULL) {
        fprintf(stderr, "printer: insufficient memory\n");
        exit(1);
    }
    char *w = word;
    size_t printed_line_size = 0;
    size_t word_len;
    int line_size;
    char c;
    while ((line_size = read_line(line, max_line)) >= 0) {
        if (line_size == 0) {
            put('\n');
            printed_line_size = 0;
            continue;
        }
        for (int i = 0; i < line_size;) {
            c = line[i];
            if (c == ' ' || c == '\t') {
                if (printed_line_size == 0) {
                    i++;
                    continue;
                } else {
                    i++;
                    put(c);
                    printed_line_size += (c == ' ' ? 1 : 4);
                }
            } else {
                while (true) {
                    if (isprint(c)) {
                        *w++ = c;
                    } else {
                        int n = sprintf(temp_hex, "|0x%.2x|", c);
                        for (int j = 0; j < n; ++j) {
                            *w++ = temp_hex[j];
                        }
                    }
                    if (w - word > max_word) {
                        fprintf(stderr, "Line too big\n");
                        exit(1);
                    }
                    i++;
                    if (i >= line_size) {
                        break;
                    }
                    c = line[i];
                    if (c == ' ' || c == '\t') {
                        break;
                    }
                }
                word_len = w - word;
                if (printed_line_size + word_len > fold_at) {
                    put('\n');
                    while (word != w) {
                        put(*word++);
                    }
                    if (word_len >= fold_at) {
                        put('\n');
                        printed_line_size = 0;
                    } else {
                        printed_line_size = word_len;
                    }
                } else {
                    while (word != w) {
                        put(*word++);
                    }
                    printed_line_size += word_len;
                }
                word -= word_len;
                w = word;
            }
        }
        put('\n');
        printed_line_size = 0;
    }
    if (prev_char != '\0') {
        putchar(prev_char);
        prev_char = '\0';
    }
    free(line);
    free(word);
}