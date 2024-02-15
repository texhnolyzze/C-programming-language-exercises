add_executable(binary_tree_tests
        binary_tree_tests.c
)

target_link_libraries(binary_tree_tests common Unity)

add_test(binary_tree_tests binary_tree_tests)