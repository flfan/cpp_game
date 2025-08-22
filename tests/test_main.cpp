#include <gtest/gtest.h>
#include "../include/example.hpp"

// 测试示例类
TEST(ExampleTest, GetDataTest) {
    cpptest::Example example;
    auto [number, message] = example.getData();

    EXPECT_EQ(number, 42);
    EXPECT_EQ(message, "Hello C++17!");
}

TEST(ExampleTest, ProcessValueTest) {
    cpptest::Example example;

    // 测试整数处理
    EXPECT_EQ(example.processValue(10), 20);

    // 测试浮点数处理
    EXPECT_DOUBLE_EQ(example.processValue(3.14), 3.64);

    // 测试字符串处理
    EXPECT_EQ(example.processValue("test"), "Unknown type");
}

TEST(ExampleTest, FindValueTest) {
    cpptest::Example example;
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 测试找到值
    auto result = example.findValue(numbers, 3);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 3);

    // 测试未找到值
    auto notFound = example.findValue(numbers, 10);
    EXPECT_FALSE(notFound.has_value());
}

TEST(ExampleTest, SumVectorTest) {
    cpptest::Example example;
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    EXPECT_EQ(example.sumVector(numbers), 15);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
