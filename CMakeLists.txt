CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

project(rshell)

include_directories(include)

set(COMMON_SOURCES src/Input.cpp src/BaseNode.h)
set(TARGET_SOURCES src/Shell.cpp)
set(TEST_SOURCES tests/*.cpp)


ADD_EXECUTABLE(rshell 
    ${COMMON_SOURCES}
    ${TARGET_SOURCES}
)

ADD_EXECUTABLE(tests
    ${COMMON_SOURCES}
    ${TEST_SOURCES}
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS (test PRIVATE gtest_disable_pthreads=ON)
