#include <gtest/gtest.h>
#include "Input.h"
#include "BaseNode.h"
#include <vector>

using namespace std;

//will be changed
TEST(RuntimeTest, parTestA) {
    Input i("(echo A && echo B) || (echo C && echo D)");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("or", b->returnCheck());
}

//will be changed
TEST(RuntimeTest, parTestB) {
    Input i("echo A && (echo B && echo C) || echo D");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("and", b->returnCheck());
}

TEST(RuntimeTest, parTestC) {
    Input i("()");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("working", b->returnCheck());
}