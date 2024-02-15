cmake_minimum_required(VERSION 3.27)

add_library(common STATIC
        utils/strings.h
        utils/io.c
        utils/io.h
        utils/strings.c
        detab.c
        detab.h
        entab.c
        entab.h
        utils/single_positive_int_arg_parser.c
        utils/single_positive_int_arg_parser.h
        fold.c
        fold.h
        c_comment_remover.c
        c_comment_remover.h
        print_ranges.c
        print_ranges.h
        htoi.c
        htoi.h
        squeeze.c
        squeeze.h
        anychar.c
        anychar.h
        expr/expr.c
        expr/expr.h
        utils/stack.c
        utils/stack.h
        expr/op_parser.c
        expr/op_parser.h
        tail.c
        tail.h
        utils/queue.c
        utils/queue.h
        sort.c
        sort.h
        dcl/dcl.c
        dcl/dcl.h
        dcl/dcl_tokenizer.c
        dcl/dcl_tokenizer.h
        clang_keyword_counter/clang_keyword_tokenizer.c
        clang_keyword_counter/clang_keyword_tokenizer.h
        clang_keyword_counter/clang_keyword_counter.c
        clang_keyword_counter/clang_keyword_counter.h
        utils/binary_tree.c
        utils/binary_tree.h
)

target_include_directories(common PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)