cmake_minimum_required(VERSION 3.27)

add_executable(dcl_tokenizer_tests dcl_tokenizer_tests.c)

foreach (i RANGE 1 9)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()

target_link_libraries(dcl_tokenizer_tests common Unity)

add_test(dcl_tokenizer_tests dcl_tokenizer_tests)