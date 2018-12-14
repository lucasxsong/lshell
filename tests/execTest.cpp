#include <gtest/gtest.h>
#include "Input.h"
#include <vector>

using namespace std;

TEST(ExecTest, echoTest) {
    Input i("echo hi hello");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("echo", b->returnType());
}

TEST(ExecTest, errorTest) {
    Input i("wrong input");
    i.parseInput();
    baseNode* b = i.returnHead();
    /*****
    //EXPECT_EQ("Rshell: wrong: command not found\n", b->returnCheck());
    //I think the top output is what should be output when "wrong input" is called.
    //error object cannot be created in baseExec class (need to figure out a work around so that we can properly call 
    //error::execute() instead of baseExec's returnCheck()).
    *****/
    //EXPECT_EQ("execvp() failed: No such file or directory\n", b->returnCheck());
    EXPECT_EQ("Rshell: wrong: command not found\n", b->returnCheck());

}

TEST(ExecTest, exitTest) {
    Input i("exit");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("working", b->returnCheck());
}

TEST(ExecTest, testTest) {
    Input i ("test doesnotexist");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("false", b->returnCheck());
}

TEST(ExecTest, bracketTest) {
    Input i("[ doesnotexist ]");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("false", b->returnCheck());
}

TEST(ExecTest, parTest) {
    Input i ("( test hi)");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("false", b->returnCheck());
}

// Added tests for Assignment #4
TEST(ExecTest, pipeTest) {
    Input i("~ hi");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("pipe", b->returnCheck());
}