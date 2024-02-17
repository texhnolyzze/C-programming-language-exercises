

#include <stdio.h>
#include <ctype.h>
#include "op_parser.h"
#include "expr.h"

int classify(const char *src, size_t *total_offset);

bool is_number(const char *src, size_t *total_offset);

int getop(const char *src, size_t *start_offset, size_t *total_offset) {
    *start_offset = 0;
    *total_offset = 0;
    while (isspace(*src)) {
        src++;
        *start_offset = *start_offset + 1;
        *total_offset = *total_offset + 1;
    }
    if (*src == '\0') {
        return END_OF_EXPR;
    }
    return classify(src, total_offset);
}

int classify(const char *src, size_t *total_offset) {
    const char *temp;
    for (size_t i = 0; i < sizeof(POSSIBLE_OPERATIONS) / sizeof(POSSIBLE_OPERATIONS[0]); ++i) {
        const char *op = POSSIBLE_OPERATIONS[i];
        bool match = true;
        temp = src;
        while (true) {
            char c = *op;
            if (c == '\0') {
                break;
            } else if (c != *temp) {
                match = false;
                break;
            }
            op++;
            temp++;
        }
        if (match && !isspace(*temp) && *temp != '\0') {
            match = false;
        }
        if (match) {
            *total_offset += op - POSSIBLE_OPERATIONS[i];
            return OPERATION;
        }
    }
    if (is_number(src, total_offset)) {
        return NUMBER;
    }
    return UNKNOWN_EXPR;
}

bool is_number(const char *src, size_t *total_offset) {
    const char *temp = src;
    if (*src == '-' || *src == '+') {
        src++;
    }
    bool has_digits = false;
    while (true) {
        if (isdigit(*src)) {
            has_digits = true;
            src++;
        } else if (*src == '.') {
            src++;
            break;
        } else if (*src == '\0' || isspace(*src)) {
            break;
        } else {
            return false;
        }
    }
    while (true) {
        if (isdigit(*src)) {
            has_digits = true;
            src++;
        } else if (*src == '\0' || isspace(*src)) {
            break;
        } else {
            return false;
        }
    }
    if (has_digits) {
        *total_offset += src - temp;
    }
    return has_digits;
}
