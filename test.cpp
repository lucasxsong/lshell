#include <gtest/gtest.h>
#include "input.h"

TEST(InputTest, ParseInputTest) {
    vector<string> test;
    test.push_back("argument1 ");
    test.push_back(" argument2 ");
    test.push_back(" argument3 ");
    test.push_back(" argument4");
    Input i("argument1 && argument2 ; argument3 || argument4");
    vector<string> toTest = Input.returnStrings();
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}

TEST(InputTest, ConnectorsTest) {
    vector<string> test;
    test.push_back("&&");
    test.push_back(";");
    test.push_back("||");
    Input i("argument1 && argument2 ; argument3 || argument4");
    vector<string> toTest = Input.returnConnectors();
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}



int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
