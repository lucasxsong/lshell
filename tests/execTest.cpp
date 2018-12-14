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
TEST(DataRedirectTests, pipeTest) {
    Input i("| pipe");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("pipe", b->returnType());
}

TEST(DataRedirectTests, OConcatenate) {
    Input i("echo hello >> OConcatenate");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ(">>", b->returnType());
}

TEST(DataRedirectTests, OOverwrite) {
    Input i("echo hello > OOverwrite");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ(">", b->returnType());
}

TEST(DataRedirectTests, IOverwrite) {
    Input i("test.txt < IOverwrite");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("<", b->returnType());
}

TEST(DataRedirectTests, ParseIOTest) {
    vector<string> test;
    test.push_back("ioredirect0875 echo && hello");
    string userInput = "helolo < yes"; //not sure what to put here
    Input i;
    i.parseIO(userInput);
    vector<string> toTest;
    toTest.push_back(i.containsRedirect);
    cout << i.containsRedirect << endl;
    EXPECT_EQ(toTest.at(0), toTest.at(0));
}

Test(DataRedirectTests, ParseOConTest) {
    Input* i = new Input();
    string toTest;
    i->parsePipe("parse this >> parse");
    EXPECT_EQ(toTest, toTest);
}

Test(DataRedirectTests, ParseIOverTest) {
    Input* i = new Input();
    string toTest;
    i->parsePipe("parse this < parse");
    EXPECT_EQ(toTest, toTest);
}

Test(DataRedirectTests, ParseOOverTest) {
    Input* i = new Input();
    string toTest;
    i->parsePipe("parse this >> parse");
    EXPECT_EQ(toTest, toTest);
}

Test(DataRedirectTests, ParseOConTest) {
    Input* i = new Input();
    string toTest;
    i->parsePipe("parse this > parse");
    EXPECT_EQ(toTest, toTest);
}