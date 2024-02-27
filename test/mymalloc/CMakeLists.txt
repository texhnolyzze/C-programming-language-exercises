add_executable(mymalloc_tests mymalloc_tests.c
        mymalloc_tests.c
        mymalloc_tests.c)
target_link_libraries(mymalloc_tests common Unity)
add_test(mymalloc_tests mymalloc_tests)