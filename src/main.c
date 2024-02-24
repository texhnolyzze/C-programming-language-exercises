#include <stdio.h>
#include <string.h>
#include "fold/fold.h"
#include "entab/entab.h"
#include "detab/detab.h"
#include "clang_comment_remover/clang_comment_remover.h"
#include "print_ranges/print_ranges.h"
#include "htoi/htoi.h"
#include "squeeze/squeeze.h"
#include "anychar/anychar.h"
#include "expr/expr.h"
#include "tail/tail.h"
#include "sort/sort.h"
#include "dcl/dcl.h"
#include "clang_keyword_counter/clang_keyword_counter.h"
#include "cross_referencer/cross_reference_printer.h"
#include "word_frequency/word_frequency.h"
#include "printer/printer.h"
#include "fcmp/fcmp.h"

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
    } else if (strcmp(subroutine_name, "dcl") == 0) {
        function_ptr = &dcl_main;
    } else if (strcmp(subroutine_name, "clang_keyword_counter") == 0) {
        function_ptr = &count_keywords;
    } else if (strcmp(subroutine_name, "cross_reference") == 0) {
        INIT(cross_reference_printer_init(subroutine_argc, subroutine_argv))
        function_ptr = &cross_reference_print;
    } else if (strcmp(subroutine_name, "word_frequency") == 0) {
        INIT(init_word_frequency(subroutine_argc, subroutine_argv))
        function_ptr = &word_frequency;
    } else if (strcmp(subroutine_name, "printer") == 0) {
        INIT(printer_init(subroutine_argc, subroutine_argv))
        function_ptr = &printer;
    } else if (strcmp(subroutine_name, "fcmp") == 0) {
        INIT(fcmp_init(subroutine_argc, subroutine_argv))
        function_ptr = &fcmp;
    } else {
        fprintf(stderr, "Unknown subroutine %s", subroutine_name);
        return -1;
    }
    function_ptr();
    fflush(stdout);
    return 0;
}