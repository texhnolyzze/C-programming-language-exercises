add_executable(io_tests
        io_tests.c)

target_link_libraries(io_tests common Unity)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/EOF.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1-line.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1-line-with-line-break.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/line-limit-exceeded.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/2-lines-with-line-break.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/line-break.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(io_tests io_tests)