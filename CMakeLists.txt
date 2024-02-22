cmake_minimum_required(VERSION 3.10)

project(IncompLibProj)

add_subdirectory(src)

add_subdirectory(docs)

option(TESTS "Build Tests" ON)

if (TESTS)
    enable_testing()
    add_subdirectory(test)
endif()