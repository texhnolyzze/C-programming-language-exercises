cmake_minimum_required(VERSION 3.27)

add_library(Unity STATIC Unity-2.5.2/src/unity.c)

target_include_directories(Unity PUBLIC Unity-2.5.2/src)