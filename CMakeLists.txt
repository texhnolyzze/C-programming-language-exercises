cmake_minimum_required(VERSION 3.27)
project(sandbox C)

set(CMAKE_C_STANDARD 23)

add_subdirectory(include)
add_subdirectory(src)
include(CTest)

if (BUILD_TESTING)
    add_subdirectory(external)
    add_subdirectory(test)
endif ()
