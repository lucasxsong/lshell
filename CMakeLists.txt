CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

project(rshell)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")


ADD_EXECUTABLE(rshell 
    ${SOURCES}
)

ADD_EXECUTABLE(test
	src/main.cpp
	tests/inputTest.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS (test PRIVATE gtest_disable_pthreads=ON)
