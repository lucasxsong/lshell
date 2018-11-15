#include <gtest/gtest.h>
#include "input.h"

using namespace std;

TEST(InputTest, ParseInputTest) {
    vector<string> test;
    test.push_back("argument1 ");
    test.push_back(" argument2 ");
    test.push_back(" argument3 ");
    test.push_back(" argument4");
    Input i("argument1 && argument2 ; argument3 || argument4");
    vector<string> toTest = i.returnStrings();
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}

TEST(InputTest, ParseSpacesTest) {
    vector<string> test1;
    vector<string> test2;
    vector<string> test3;
    vector<string> test4;
    vector< vector <string> > test;
    test1.push_back("argument1");
    test2.push_back("argument2");
    test3.push_back("argument3");
    test4.push_back("argument4");
    test.push_back(test1);
    test.push_back(test2);
    test.push_back(test3);
    test.push_back(test4);
    Input i("argument1 && argument2 ; argument3 || argument4");
    i.parseConnectors();
    vector<string> toTestSpaces = i.returnStrings();
    i.parseSpaces();
    vector< vector <string> > toTest = toTestSpaces.returnParsedNoSpace();
    for (int i = 0; i < toTest.size(); ++i) {
        for (int j = 0; j < toTest.at(i).size(); ++j) {
                EXPECT_EQ(test.at(i).at(j), toTest.at(i).at(j);
        } 
    }
}

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

TEST(InputTest, ConnectorsTest) {
    vector<string> test;
    test.push_back("&&");
    test.push_back(";");
    test.push_back("||");
    Input i("argument1 && argument2 ; argument3 || argument4");
    i.parseConnectors();
    vector<string> toTest = Input.returnConnectors();
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}



int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
