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
    cout << "part a" << endl;
    Input i("wrong input");
    cout << "part b" << endl;
    baseNode* b = i.returnHead();
    cout << "part c" << endl;
    EXPECT_EQ("Rshell: wrong: command not found\n", b->returnCheck());
}

// TEST(ExecTest, exitTest) {

// }