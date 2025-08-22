# 现代C++17项目

这是一个使用C++17标准和CMake构建工具的现代C++项目模板。

## 特性

- 🚀 使用C++17标准
- 🏗️ CMake构建系统
- 📁 清晰的项目结构
- 🧪 支持测试框架
- 🔧 完整的开发工具配置
- 📚 详细的文档和注释

## 项目结构

```
cppTest/
├── src/                    # 源文件目录
│   └── main.cpp           # 主程序
├── include/                # 头文件目录
│   └── example.hpp        # 示例头文件
├── tests/                  # 测试文件目录
├── build/                  # 构建输出目录
├── docs/                   # 文档目录
├── .vscode/               # VSCode配置
├── CMakeLists.txt         # CMake配置
├── build.sh               # 构建脚本
├── clean.sh               # 清理脚本
├── .cursor/               # Cursor规则
└── README.md              # 项目说明
```

## 系统要求

- CMake 3.16+
- 支持C++17的编译器 (GCC 7+, Clang 5+, MSVC 2017+)
- 在macOS上推荐使用Xcode Command Line Tools

## 快速开始

### 1. 克隆项目

```bash
git clone <your-repo-url>
cd cppTest
```

### 2. 构建项目

```bash
# 使用构建脚本
chmod +x build.sh
./build.sh

# 或者手动构建
mkdir build
cd build
cmake ..
make
```

### 3. 运行程序

```bash
./build/bin/cppTest
```

### 4. 清理构建文件

```bash
chmod +x clean.sh
./clean.sh
```

## C++17特性示例

项目展示了以下C++17特性：

- **结构化绑定** - 简化pair和tuple的使用
- **constexpr if** - 编译时条件分支
- **std::optional** - 安全的可选值表示
- **折叠表达式** - 简化可变参数模板

## 开发工具配置

### VSCode/Cursor

项目包含完整的VSCode配置：

- C++ IntelliSense配置
- CMake集成
- 调试配置
- 任务配置
- clang-tidy静态分析集成

### 代码质量工具

- **clang-tidy** - 静态代码分析
- **clang-format** - 代码格式化
- **CMake集成** - 构建时分析

### 快捷键

- `Ctrl+Shift+P` → "Tasks: Run Task" → 选择构建任务
- `F5` - 启动调试
- `Ctrl+Shift+P` → "CMake: Configure"
- `Ctrl+Shift+P` → "CMake: Build"
- `Ctrl+Shift+P` → "Tasks: Run Task" → "clang-tidy Check" - 代码分析
- `Ctrl+Shift+P` → "Tasks: Run Task" → "clang-tidy Fix" - 自动修复

## 构建配置

### Debug构建

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Release构建

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### 启用测试

```bash
cmake -B build -S . -DBUILD_TESTS=ON
cmake --build build
```

### 代码质量检查

```bash
# 运行clang-tidy分析
./run_clang_tidy.sh

# 自动修复问题
./run_clang_tidy.sh --fix

# 启用clang-tidy构建
cmake -B build -DENABLE_CLANG_TIDY=ON
cmake --build build
```

## 代码规范

- 使用4空格缩进
- 遵循现代C++最佳实践
- 使用RAII和智能指针
- 优先使用constexpr和const
- 使用namespace组织代码

## 贡献指南

1. Fork项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开Pull Request

## 许可证

本项目采用MIT许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 联系方式

如有问题或建议，请通过以下方式联系：

- 创建Issue
- 发送Pull Request
- 联系项目维护者
