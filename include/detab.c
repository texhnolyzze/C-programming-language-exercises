//
// Created by ikarimullin on 10.01.2024.
//

#include <stdio.h>
#include "detab.h"
#include "utils/single_positive_int_arg_parser.h"

static int tabSize;

int detab_init(int argc, const char **argv) {
    return parseSingleIntArg(argc, argv, &tabSize);
}

void detab(void) {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < tabSize; ++i) {
                putchar(' ');
            }
        } else {
            putchar(c);
        }
    }
}