#include <gtest/gtest.h>
#include "main.cpp"

TEST(InputTest, ParseInputTest) {
    vector<string> test;
    test.push_back("argument1");
    test.push_back(" argument2 ");
    test.push_back(" argument 3 ");
    test.push_back(" argument 4");
    vector<string> toTest = parseInput("argument1 && argument2 ; argument3 || argument4");
    for (int i = 0; i < toTest.size(); ++i) {
        EXPECT_EQ(test.at(i), toTest.at(i));
    }
}



int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
