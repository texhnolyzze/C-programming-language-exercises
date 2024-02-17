#include <stdio.h>
#include "detab.h"
#include "utils/single_positive_int_arg_parser/single_positive_int_arg_parser.h"

static size_t tab_size;

int detab_init(int argc, const char **argv) {
    return parse_single_int_arg(argc, argv, &tab_size);
}

void detab(void) {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < tab_size; ++i) {
                putchar(' ');
            }
        } else {
            putchar(c);
        }
    }
}