add_executable(fcmp_tests fcmp_tests.c
        fcmp_tests.c)
target_link_libraries(fcmp_tests common Unity)
set(N_TESTS 2)
target_compile_definitions(fcmp_tests PRIVATE N_TESTS=${N_TESTS})
foreach (i RANGE 1 ${N_TESTS})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.a.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.b.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.ans.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()
add_test(fcmp_tests fcmp_tests)