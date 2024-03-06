add_executable(qsort_tests
        qsort_tests.c
)

target_link_libraries(qsort_tests common Unity)

add_test(qsort_tests qsort_tests)