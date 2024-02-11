add_executable(tail_tests tail_tests.c)
target_link_libraries(tail_tests common Unity)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/big.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(tail_tests tail_tests)