add_executable(stack_tests
        stack_tests.c
)

target_link_libraries(stack_tests common Unity)

add_test(stack_tests stack_tests)