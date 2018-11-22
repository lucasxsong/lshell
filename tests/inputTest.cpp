#include <gtest/gtest.h>
#include "Input.h"
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
    test.push_back(e);
    vector<string> preExec;
    preExec.push_back("echo");
    preExec.push_back("hello");
    baseExec* b = makeExec(preExec);
    EXPECT_EQ("echo", e->returnType());
}
/*
// Checks to make sure that the argument list passed on with the executable is properly constructed
TEST(InputTest, ParseArgTest) {
    vector<string> preExec;
    preExec.push_back("echo");
    preExec.push_back("hello");
    baseExec* b = makeExec(preExec);
    EXPECT_EQ("hello", preExec.at(1));
}

// Checks to make sure that clear input is properly flushing memory
TEST(InputTest, ClearInputTest) {
    Input i("echo hi && ls -a || echo foo ; git status");
    i.parseInput();
    i.clearInput();
    EXPECT_EQ("", i.returnStrings());
}

// Checks to make sure that the connectors are properly pushed back to the connector vector
TEST(InputTest, ParseConnectorsTest) {
    vector<string> test;
    test.push_back("&&");
    test.push_back("||";
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

TEST(InputTest, ExecutableTreeTest) {
    Input i("echo hi && ls -a || echo foo ; git status");
    i.parseInput();
    baseNode* b = i.returnHead();
    EXPECT_EQ("echo", b.returnType());
}
*/