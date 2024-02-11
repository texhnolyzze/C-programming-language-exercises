//
// Created by ikarimullin on 10.01.2024.
//

#include <stdio.h>
#include <string.h>
#include "fold.h"
#include "entab.h"
#include "detab.h"
#include "c_comment_remover.h"
#include "print_ranges.h"
#include "htoi.h"
#include "squeeze.h"
#include "anychar.h"
#include "expr/expr.h"
#include "tail.h"
#include "sort.h"

#define INIT(x) { \
    int err = x; \
    if (err != 0) { \
        return err;            \
    }\
}

int main(int argc, const char **argv) {
    if (argc < 2) {
        fprintf(stderr, "You must set at least one program argument, which specifies subroutine you want to run");
        return -1;
    }
    void (*function_ptr)(void);
    const char *subroutine_name = argv[1];
    const int subroutine_argc = argc - 2;
    const char **const subroutine_argv = argv + 2;
    if (strcmp(subroutine_name, "fold") == 0) {
        INIT(fold_init(subroutine_argc, subroutine_argv))
        function_ptr = &fold;
    } else if (strcmp(subroutine_name, "entab") == 0) {
        INIT(entab_init(subroutine_argc, subroutine_argv))
        function_ptr = &entab;
    } else if (strcmp(subroutine_name, "detab") == 0) {
        INIT(detab_init(subroutine_argc, subroutine_argv))
        function_ptr = &detab;
    } else if (strcmp(subroutine_name, "remove_comments") == 0) {
        function_ptr = &remove_comments;
    } else if (strcmp(subroutine_name, "print_ranges") == 0) {
        function_ptr = &print_ranges;
    } else if (strcmp(subroutine_name, "htoi") == 0) {
        function_ptr = &htoi;
    } else if (strcmp(subroutine_name, "squeeze") == 0) {
        INIT(squeeze_init(subroutine_argc, subroutine_argv))
        function_ptr = &squeeze;
    } else if (strcmp(subroutine_name, "anychar") == 0) {
        INIT(anychar_init(subroutine_argc, subroutine_argv))
        function_ptr = &anychar;
    } else if (strcmp(subroutine_name, "expr") == 0) {
        function_ptr = &expr;
    } else if (strcmp(subroutine_name, "tail") == 0) {
        INIT(tail_init(subroutine_argc, subroutine_argv))
        function_ptr = &tail;
    } else if (strcmp(subroutine_name, "sort") == 0) {
        INIT(sort_init(subroutine_argc, subroutine_argv))
        function_ptr = &sort;
    } else {
        fprintf(stderr, "Unknown subroutine %s", subroutine_name);
        return -1;
    }
    function_ptr();
    fflush(stdout);
    return 0;
}