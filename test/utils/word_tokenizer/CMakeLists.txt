add_executable(word_tokenizer_tests
        word_tokenizer_tests.c
)

foreach (i RANGE 1 3)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()

target_link_libraries(word_tokenizer_tests common Unity)

add_test(word_tokenizer_tests word_tokenizer_tests)