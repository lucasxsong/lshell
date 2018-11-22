#include <gtest/gtest.h>
#include "Input.h"
#include <vector>

using namespace std;

TEST(ExecTest, echoTest) {
    Input i("echo hi hello");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("hi hello ", b->returnArgs());
}