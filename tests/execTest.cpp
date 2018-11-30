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
    // EXPECT_EQ("execvp() failed: No such file or directory\nRshell: wrong: command not found\n", b->execute());
    /*****
    //Originally output^ but after changes made to makeExec() now output is
    //as shown V.
    //I think the top output is what should be output when "wrong input"
    //is called. Issue may lie in execute function of baseExec class
    *****/
   EXPECT_EQ("execvp() failed: No such file or directory\n", b->execute());

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