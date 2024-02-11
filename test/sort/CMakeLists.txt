add_executable(sort_tests sort_tests.c)

target_link_libraries(sort_tests common Unity)

foreach (i RANGE 1 4)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sort_test_${i}.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sort_test_${i}_ans.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()

add_test(sort_tests sort_tests)