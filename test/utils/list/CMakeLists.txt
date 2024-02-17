add_executable(list_tests
        list_tests.c
)

target_link_libraries(list_tests common Unity)

add_test(list_tests list_tests)