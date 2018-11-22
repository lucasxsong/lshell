#include <gtest/gtest.h>
#include "Input.h"
#include <vector>

using namespace std;

TEST(ExecTest, echoTest) {
    Input i("echo hi hello");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("hi hello ", b->returnCheck());
}

TEST(ExecTest, errorTest) {
    Input i("wrong input");
    i.parseInput();
    baseNode* b = i.returnHead(); //seg fault
    EXPECT_EQ("", b->returnCheck());
}

// TEST(ExecTest, exitTest) {

// }