add_executable(word_frequency_tests word_frequency_tests.c)
target_link_libraries(word_frequency_tests common Unity)
set(N_TESTS 3)
target_compile_definitions(word_frequency_tests PRIVATE N_TESTS=${N_TESTS})
foreach (i RANGE 1 ${N_TESTS})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.ans.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()
add_test(word_frequency_tests word_frequency_tests)