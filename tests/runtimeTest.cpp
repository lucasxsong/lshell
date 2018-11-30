#include <gtest/gtest.h>
#include "Input.h"
#include "BaseNode.h"
#include <vector>

using namespace std;

TEST(RuntimeTest, parTestA) {
    Input i("(echo A && echo B) || (echo C && echo D)");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("", b->returnCheck());
}