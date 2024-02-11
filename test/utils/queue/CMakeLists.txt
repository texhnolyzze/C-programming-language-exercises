add_executable(queue_tests
        queue_tests.c
)

target_link_libraries(queue_tests common Unity)

add_test(queue_tests queue_tests)