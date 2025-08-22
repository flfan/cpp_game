#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <string>
#include <vector>
#include "../include/example.hpp"

int main() {
    std::cout << "=== 现代C++17项目示例 ===" << '\n';

    cpptest::Example example;

    // 结构化绑定示例
    auto [number, message] = example.getData();
    std::cout << "结构化绑定: " << number << ", " << message << '\n';

    // constexpr if示例
    std::cout << "整数处理: " << example.processValue(10) << '\n';
    std::cout << "浮点数处理: " << example.processValue(3.14) << '\n';
    std::cout << "字符串处理: " << example.processValue("test") << '\n';

    // std::optional示例
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    auto result = example.findValue(numbers, 3);
    if (result.has_value()) {
        std::cout << "找到值: " << result.value() << '\n';
    } else {
        std::cout << "未找到值" << '\n';
    }

    // 折叠表达式 (C++17)
    auto sum = example.sumVector(numbers);
    std::cout << "向量求和: " << sum << '\n';

    std::cout << "项目构建成功！" << '\n';
    return 0;
}
