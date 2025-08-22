#!/bin/bash

# 现代C++17项目构建脚本

echo "=== 开始构建现代C++17项目 ==="

# 创建构建目录
mkdir -p build
cd build

# 配置项目
echo "配置CMake项目..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译项目
echo "编译项目..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 检查编译结果
if [ $? -eq 0 ]; then
    echo "=== 构建成功！ ==="
    echo "可执行文件位置: build/bin/cppTest"
    echo ""
    echo "运行程序:"
    ./bin/cppTest
else
    echo "=== 构建失败！ ==="
    exit 1
fi
