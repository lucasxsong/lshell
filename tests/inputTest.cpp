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

TEST(InputTest, ParseConnectors) {
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

TEST(InputTest, clearInput) {
    Input i("echo hi && ls -a || echo foo ; git status");
    i.parseInput();
    i.clearInput();
    EXPECT_EQ("", i.returnStrings());
}




/*
TEST(InputTest, ExecTest) {
    test1 = new echo();
    test2 = new ls();
    test3 = new cd();
    vector<vector <baseExec*> test;
    test.push_back(test1);
    test.push_back(test2);
    test.push_back(test3);
    Input i("echo hi && ls file ; cd file");
    i.parseConnectors();
    vector<string> toTestSpaces = i.returnStrings();
    i.parseSpaces();
    vector<vector <string> > toTest = toTestSpaces.returnParsedNoSpace();
    i.makeExec();
    vector<baseExec* > testExec = toTest.returnParsedExec();
    for (int i = 0; i < toTest.size(); ++i) {
        for (int j = 0; j < toTest.at(i).size(); ++j) {
                EXPECT_EQ(test.at(i).at(j), toTest.at(i).at(j);
        } 
    }
}

*/
