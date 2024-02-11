//
// Created by ikarimullin on 10.01.2024.
//

#include <stdio.h>
#include "fold.h"
#include "utils/single_positive_int_arg_parser.h"

static int size;

int fold_init(int argc, const char **argv) {
    return parseSingleIntArg(argc, argv, &size);
}

void fold(void) {
    int c;
    int len = 0;
    int spaces = 0;
    bool freezeSpaces = true;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!freezeSpaces) {
                spaces++;
            }
            len++;
        } else {
            freezeSpaces = false;
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
            freezeSpaces = true;
            len = 0;
        }
    }
}
