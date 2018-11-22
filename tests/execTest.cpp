#include <gtest/gtest.h>
#include "Input.h"
#include <vector>

using namespace std;

TEST(ExecTest, echoTest) {
    Input i("echo hi");
    i.parseInput();
    baseExec* b = i.returnHead();
    EXPECT_EQ("hi ", b->returnArgs());
}