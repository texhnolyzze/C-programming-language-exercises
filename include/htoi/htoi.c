

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "htoi.h"
#include "utils/io/io.h"

static bool isHexDigit(int c);

static int toHexDigit(int c);

void htoi(void) {
    char line[DEFAULT_MAX_LINE];
    int len;
    while ((len = read_line(line, DEFAULT_MAX_LINE)) >= 0) {
        if (len == 0) {
            continue;
        }
        bool zeroXNotation = line[0] == '0' && len > 2 && tolower(line[1]) == 'x' && isHexDigit(line[2]);
        if (!(zeroXNotation || isHexDigit(line[0]))) {
            fprintf(stderr, "Invalid input, hex number required\n");
            continue;
        }
        int start = zeroXNotation ? 2 : 0;
        for (int i = start + 1; i < len; ++i) {
            if (!isHexDigit(line[i])) {
                fprintf(stderr, "Invalid input, hex number required\n");
                goto validationLoopExit;
            }
        }
        int n = 0;
        int c;
        for (int i = start; i < len; ++i) {
            c = line[i];
            n = 16 * n + toHexDigit(c);
        }
        printf("%d\n", n);
        validationLoopExit:
    }
}

bool isHexDigit(int c) {
    return c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F';
}

int toHexDigit(int c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    } else {
        return 10 + (c - 'a');
    }
}