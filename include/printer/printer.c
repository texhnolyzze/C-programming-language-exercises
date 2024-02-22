#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>
#include "printer.h"
#include "utils/io/io.h"

static size_t max_word = 150;
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
        if (strcmp("-mw", arg) == 0) {
            const char *arg_val = *argv++;
            if (sscanf(arg_val, "%zu", &max_word) != 1 || max_word == 0) {
                fprintf(stderr, "Illegal -mw option: %s", arg_val);
                return -1;
            }
            max_word *= 6; // to account for non-printable characters, which we print as '|0xXX|', where X is any hex digit
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
    char *word = malloc(max_word);
    if (word == NULL) {
        fprintf(stderr, "printer: insufficient memory\n");
        exit(1);
    }
    char *w = word;
    size_t word_len;
    size_t line_size = 0;
    size_t space_size;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            put('\n');
            line_size = 0;
        } else if (c == ' ' || c == '\t') {
            if (line_size == 0) {
                continue;
            }
            space_size = c == ' ' ? 1 : 4;
            if (line_size + space_size < fold_at) {
                put(c);
                line_size += space_size;
            } else {
                put('\n');
                line_size = 0;
            }
        } else {
            while (true) {
                if (w - word > max_word) {
                    *w = '\0';
                    fprintf(stderr, "Word too big: %s\n", word);
                    exit(1);
                }
                if (isprint(c)) {
                    *w++ = c;
                } else {
                    int n = sprintf(temp_hex, "|0x%.2x|", c);
                    for (int j = 0; j < n; ++j) {
                        *w++ = temp_hex[j];
                    }
                }
                c = getchar();
                if (isspace(c) || c == EOF) {
                    ungetc(c, stdin);
                    break;
                }
            }
            word_len = w - word;
            if (line_size + word_len > fold_at) {
                if (line_size != 0) {
                    put('\n');
                }
                while (word != w) {
                    put(*word++);
                }
                if (word_len >= fold_at && c != '\n') {
                    put('\n');
                    line_size = 0;
                } else {
                    line_size = word_len;
                }
            } else {
                while (word != w) {
                    put(*word++);
                }
                line_size += word_len;
            }
            word -= word_len;
            w = word;
        }
    }
    if (prev_char != '\0') {
        putchar(prev_char);
    }
    prev_char = '\0';
    free(word);
}