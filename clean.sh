#!/bin/bash

# 清理构建文件脚本

echo "=== 清理构建文件 ==="

# 删除构建目录
if [ -d "build" ]; then
    echo "删除build目录..."
    rm -rf build
fi

# 删除CMake缓存文件
if [ -f "CMakeCache.txt" ]; then
    echo "删除CMakeCache.txt..."
    rm -f CMakeCache.txt
fi

# 删除CMake文件
find . -name "CMakeFiles" -type d -exec rm -rf {} + 2>/dev/null || true
find . -name "cmake_install.cmake" -type f -delete 2>/dev/null || true
find . -name "Makefile" -type f -delete 2>/dev/null || true

echo "清理完成！"
