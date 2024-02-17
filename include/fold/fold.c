

#include <stdio.h>
#include "fold.h"
#include "utils/single_positive_int_arg_parser/single_positive_int_arg_parser.h"

static size_t size;

int fold_init(int argc, const char **argv) {
    return parse_single_int_arg(argc, argv, &size);
}

void fold(void) {
    int c;
    size_t len = 0;
    size_t spaces = 0;
    bool freeze_spaces = true;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!freeze_spaces) {
                spaces++;
            }
            len++;
        } else {
            freeze_spaces = false;
            while (spaces != 0) {
                putchar(' ');
                spaces--;
            }
            putchar(c);
            len++;
        }
        if (len == size) {
            putchar('\n');
            spaces = 0;
            freeze_spaces = true;
            len = 0;
        }
    }
}
