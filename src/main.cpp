#include <iostream>
#include <optional>
#include <vector>
#include "../include/example.hpp"
#include "spdlog/spdlog.h"

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

    // spdlog
    spdlog::set_level(spdlog::level::debug);  // Set *global* log level to debug
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug);  // Set *global* log level to debug
    spdlog::debug("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // Note that this does not change the current log level, it will only
    // remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");
    return 0;
}
