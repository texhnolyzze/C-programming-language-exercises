add_executable(printer_tests printer_tests.c
        printer_tests.c)
target_link_libraries(printer_tests common Unity)
set(N_TESTS 4)
target_compile_definitions(printer_tests PRIVATE N_TESTS=${N_TESTS})
foreach (i RANGE 1 ${N_TESTS})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-${i}.ans.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()
add_test(printer_tests printer_tests)