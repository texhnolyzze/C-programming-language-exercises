add_executable(hash_table_tests
        hash_table_tests.c
)

target_link_libraries(hash_table_tests common Unity)

add_test(hash_table_tests hash_table_tests)