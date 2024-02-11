//
// Created by ikarimullin on 10.01.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "single_positive_int_arg_parser.h"

int parseSingleIntArg(int argc, const char **argv, int *result) {
    if (argc != 1) {
        fprintf(stderr, "You must specify exactly one program argument, which is positive integer, e.g. 10");
        return -1;
    }
    const char *str = argv[0];
    int sz = atoi(str);
    if (sz == 0) {
        fprintf(stderr, "You must specify positive integer as second program argument. Actual: %s", str);
        return -1;
    }
    *result = sz;
    return 0;
}
