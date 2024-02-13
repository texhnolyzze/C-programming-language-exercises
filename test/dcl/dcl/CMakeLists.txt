cmake_minimum_required(VERSION 3.27)

add_executable(dcl_tests dcl_tests.c)

foreach (i RANGE 1 10)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()

target_link_libraries(dcl_tests common Unity)

add_test(dcl_tests dcl_tests)