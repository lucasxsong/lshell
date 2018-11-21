CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

project(rshell)

#include_directories(include)

ADD_EXECUTABLE(test
    src/test.cpp
    tests/inputTest.cpp
    src/Input.cpp
    src/Input.h
    src/BaseNode.h
)

ADD_EXECUTABLE(rshell 
    src/Shell.cpp
    src/Input.h
    src/Input.cpp
    src/BaseNode.h
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS (test PRIVATE gtest_disable_pthreads=ON)
