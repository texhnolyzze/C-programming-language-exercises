add_executable(expr_tests expr_tests.c
        ../dcl/dcl_tokenizer/dcl_tokenizer_tests.c)

target_link_libraries(expr_tests common Unity)
add_test(expr_tests expr_tests)