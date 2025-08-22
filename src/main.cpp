#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

// 使用C++17特性
class ModernCppExample {
public:
  // 结构化绑定 (C++17)
  std::pair<int, std::string> getData() const { return {42, "Hello C++17!"}; }

  // constexpr if (C++17)
  template <typename T> auto processValue(const T &value) const {
    if constexpr (std::is_integral<T>::value) {
      return value * 2;
    } else if constexpr (std::is_floating_point<T>::value) {
      return value + 0.5;
    } else {
      return std::string("Unknown type");
    }
  }

  // std::optional (C++17)
  std::optional<int> findValue(const std::vector<int> &vec, int target) const {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
      return *it;
    }
    return std::nullopt;
  }
};

int main() {
  std::cout << "=== 现代C++17项目示例 ===" << std::endl;

  ModernCppExample example;

  // 结构化绑定示例
  auto [number, message] = example.getData();
  std::cout << "结构化绑定: " << number << ", " << message << std::endl;

  // constexpr if示例
  std::cout << "整数处理: " << example.processValue(10) << std::endl;
  std::cout << "浮点数处理: " << example.processValue(3.14) << std::endl;
  std::cout << "字符串处理: " << example.processValue("test") << std::endl;

  // std::optional示例
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  auto result = example.findValue(numbers, 3);
  if (result.has_value()) {
    std::cout << "找到值: " << result.value() << std::endl;
  } else {
    std::cout << "未找到值" << std::endl;
  }

  // 折叠表达式 (C++17)
  auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  std::cout << "向量求和: " << sum << std::endl;

  std::cout << "项目构建成功！" << std::endl;
  return 0;
}
