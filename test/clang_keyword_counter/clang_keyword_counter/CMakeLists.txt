cmake_minimum_required(VERSION 3.27)

add_executable(clang_keyword_counter_tests clang_keyword_counter_tests.c)

foreach (i RANGE 1 1)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()

target_link_libraries(clang_keyword_counter_tests common Unity)

add_test(clang_keyword_counter_tests clang_keyword_counter_tests)