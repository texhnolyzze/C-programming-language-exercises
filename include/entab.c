//
// Created by ikarimullin on 10.01.2024.
//

#include <stdio.h>
#include "entab.h"
#include "utils/single_positive_int_arg_parser.h"

static int tabSize;

int entab_init(int argc, const char **argv) {
    return parseSingleIntArg(argc, argv, &tabSize);
}

void entab(void) {
    int c;
    int spaces = 0;
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
