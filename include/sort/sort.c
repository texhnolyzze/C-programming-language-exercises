#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "sort.h"
#include "utils/io/io.h"
#include "utils/strings/strings.h"

static bool numeric;
static bool sort_reverse;
static bool case_insensitive;

int numcmp(const char **s1, const char **s2);

int strcmp_wrapper(const char **s1, const char **s2);

int sort_init(int argc, const char **argv) {
    numeric = sort_reverse = case_insensitive = false;
    for (int i = 0; i < argc; ++i) {
        const char *arg = argv[i];
        if (strcmp(arg, "-n") == 0) {
            numeric = true;
        } else if (strcmp(arg, "-r") == 0) {
            sort_reverse = true;
        } else if (strcmp(arg, "-f") == 0) {
            case_insensitive = true;
        }
    }
    return 0;
}

void sort(void) {
    int read_lines_exit_code;
    size_t lines_read;
    char **lines = read_lines_dyn(SORT_MAXLINES, SORT_MAX_LINE_LEN, 16, &read_lines_exit_code, &lines_read);
    if (read_lines_exit_code == -2) {
        return;
    }
    qsort(lines, lines_read, sizeof(char *), (int (*)(const void *, const void *)) (numeric ? numcmp : strcmp_wrapper));
    for (int i = 0; i < lines_read; ++i) {
        char *line = lines[i];
        printf("%s\n", line);
        free(line);
    }
    free(lines);
}

int numcmp(const char **s1, const char **s2) {
    const double d1 = atof(*s1);
    const double d2 = atof(*s2);
    const int cmp = d1 < d2 ? -1 : (d1 > d2) ? 1 : 0;
    return sort_reverse ? -cmp : cmp;
}

int strcmp_wrapper(const char **s1, const char **s2) {
    return mystrcmp(*s1, *s2, sort_reverse, !case_insensitive);
}
