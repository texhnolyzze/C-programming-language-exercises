add_executable(strings_tests
        strings_tests.c)

target_link_libraries(strings_tests common Unity)

add_test(strings_tests strings_tests)