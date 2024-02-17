#include <stdio.h>
#include "entab.h"
#include "utils/single_positive_int_arg_parser/single_positive_int_arg_parser.h"

static size_t tabSize;

int entab_init(int argc, const char **argv) {
    return parse_single_int_arg(argc, argv, &tabSize);
}

void entab(void) {
    int c;
    size_t spaces = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            spaces++;
        } else {
            while (spaces != 0) {
                if (spaces >= tabSize) {
                    putchar('\t');
                    spaces -= tabSize;
                } else {
                    putchar(' ');
                    spaces -= 1;
                }
            }
            putchar(c);
        }
    }
}
