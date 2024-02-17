add_executable(cross_referencer_tests cross_referencer_tests.c)

target_link_libraries(cross_referencer_tests common Unity)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-1.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-2.ans.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(cross_referencer_tests cross_referencer_tests)