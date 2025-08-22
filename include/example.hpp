#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>

namespace cpptest {

/**
 * @brief 现代C++17示例类
 *
 * 这个类展示了C++17的各种特性，包括：
 * - 结构化绑定
 * - constexpr if
 * - std::optional
 * - 折叠表达式
 */
class Example {
public:
    Example() = default;
    virtual ~Example() = default;

    // 禁用拷贝构造和赋值
    Example(const Example&) = delete;
    Example& operator=(const Example&) = delete;

    // 允许移动构造和赋值
    Example(Example&&) = default;
    Example& operator=(Example&&) = default;

    /**
     * @brief 获取数据对
     * @return 包含整数和字符串的pair
     */
    std::pair<int, std::string> getData() const;

    /**
     * @brief 处理不同类型的值
     * @tparam T 值类型
     * @param value 要处理的值
     * @return 处理后的结果
     */
    template<typename T>
    auto processValue(const T& value) const;

    /**
     * @brief 在向量中查找值
     * @param vec 要搜索的向量
     * @param target 目标值
     * @return 找到的值或std::nullopt
     */
    std::optional<int> findValue(const std::vector<int>& vec, int target) const;

    /**
     * @brief 计算向量的和
     * @param vec 输入向量
     * @return 所有元素的和
     */
    int sumVector(const std::vector<int>& vec) const;
};

} // namespace cpptest
