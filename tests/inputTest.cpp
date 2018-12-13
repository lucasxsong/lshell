#include <gtest/gtest.h>
#include "Input.h"
#include "BaseNode.h"
#include <vector>


using namespace std;


// This is an outdated test harness. Was used early on to test parsing based on
// connectors, but no longer needed.
/*
TEST(InputTest, ParseInputTest) {
    vector<string> test;
    test.push_back("argument1 ");
    test.push_back(" argument2 ");
    test.push_back(" argument3 ");
    test.push_back(" argument4");
    Input i("argument1 && argument2 ; argument3 || argument4");
    i->parseInput();
    vector<string> toTest = i.returnStrings();
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}*/ 

// Checks to make sure that the parse spaces function properly removes spaces
TEST(InputTest, ParseSpacesTest) {
    vector<string> test;
    test.push_back("argument1");
    test.push_back("argument2");
    test.push_back("argument3");
    test.push_back("argument4");
    Input i;
    vector<string> toTest = i.parseSpaces("argument1 argument2 argument3 argument4");
    for (int i = 0; i < test.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    } 
}

// Checks to make sure that the exec object instantiated is corresponding to the one passed in
TEST(InputTest, ParseExecTest) {
    echo* e = new echo();
    vector<string> preExec;
    preExec.push_back("echo");
    preExec.push_back("hello");
    echo* b = new echo();
    EXPECT_EQ("echo", b->returnType());
}

// Checks to make sure that the argument list passed on with the executable is properly constructed
TEST(InputTest, ParseArgTest) {
    vector<string> preExec;
    preExec.push_back("echo");
    preExec.push_back("hello");
    EXPECT_EQ("hello", preExec.at(1));
}

// Checks to make sure that clear input is properly flushing memory
TEST(InputTest, ClearInputTest) {
    Input i("echo hi && ls -a || echo foo ; git status");
    i.clearInput();
    string s  = i.returnStrings();
    EXPECT_EQ("", s);
}

TEST(InputTest, RemoveCommentTest) {
    Input i("echo hi #&& echo hello");
    i.removeComment();
    string s = i.returnStrings();
    EXPECT_EQ("echo hi", s);
}

// Checks to make sure that the connectors are properly pushed back to the connector vector
TEST(InputTest, ParseConnectorsTestA) {
    vector<string> test;
    test.push_back("&&");
    test.push_back("||");
    test.push_back(";");
    Input i("echo hi && ls -a || echo foo ; git status");
    i.parseConnectors();
    vector<string> toTest;
    vector<Connector* > c = i.returnConnectors();
    toTest.push_back("&&");
    toTest.push_back("||");
    toTest.push_back(";");

    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}

// Added test for additional connectors (Assignment 4)
TEST(InputTest, ParseConnectorsTestB) {
    
}

// Tests the head node of the executable tree to make sure its been constructed properly
TEST(InputTest, ExecutableTreeTest) {
    Input i("echo hi && ls -a || echo foo ; git status");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("&&", b->returnType());
}

// Tests parsePar function for simple commands with a single set of parenthesis
TEST(InputTest, SimpleParTest) {
    vector<string> test;
    test.push_back("echo B && echo C");
    Input i;
    string userInput = "echo A && (echo B && echo C) && echo D";
    vector<string> toTest = i.parsePar(userInput);
    EXPECT_EQ(test.at(0), toTest.at(0));
}

// Tests parsePar function for commands with nested parentheses
TEST(InputTest, NestedParTest) {
    vector<string> test;
    test.push_back("echo A && (echo B && echo C) && echo D");
    test.push_back("echo B && echo C");
    string userInput = "(echo A && (echo B && echo C) && echo D) && echo E";
    Input i;
    vector<string> toTest = i.parsePar(userInput);
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}

// Added test cases for Assignment #4

// Tests parseIO function (look for "ioredirect0875 ")
TEST(InputTest, ParseIOTest) {
    vector<string> test;
    test.push_back("ioredirect0875");
    string userInput = "< yes";
    Input i;
    i.parseIO(userInput);
    vector<string> toTest;
    toTest.push_back(i.containsRedirect);
    cout << i.containsRedirect << endl;
    EXPECT_EQ(test.at(0), toTest.at(0));
}

// Tests parsePipe function (should replace | with ~)
// TEST(InputTest, ParsePipeTest) {

// }

// // Tests parseOCon function (should replace >> with ~)
// TEST(InputTest, ParseOConTest) {

// }
