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
    baseNode* b = i.returnHead();
    /*****
    //EXPECT_EQ("Rshell: wrong: command not found\n", b->returnCheck());
    //Originally output^ but after changes made to makeExec() now output is
    //as shown V.
    //I think the top output is what should be output when "wrong input"
    //is called. Issue may lie in else condition: change baseExec to error
    //object
    *****/
   EXPECT_EQ("execvp() failed: No such file or directory\n", b->returnCheck());
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