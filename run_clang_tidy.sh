#!/bin/bash

# clang-tidy运行脚本

echo "=== 运行clang-tidy静态分析 ==="

# 检查clang-tidy是否安装
CLANG_TIDY_PATH=""
if command -v /opt/homebrew/opt/llvm/bin/clang-tidy &> /dev/null; then
    CLANG_TIDY_PATH="/opt/homebrew/opt/llvm/bin/clang-tidy"
elif command -v clang-tidy &> /dev/null; then
    CLANG_TIDY_PATH="clang-tidy"
else
    echo "错误: clang-tidy未安装"
    echo "在macOS上安装: brew install llvm"
    echo "在Ubuntu上安装: sudo apt-get install clang-tidy"
    exit 1
fi

# 显示clang-tidy版本
echo "clang-tidy版本:"
clang-tidy --version

# 设置参数
CONFIG_FILE=".clang-tidy"
HEADER_FILTER="(src/.*|include/.*|tests/.*)"
SOURCE_FILES="src/*.cpp"
HEADER_FILES="include/*.hpp"

# 检查配置文件是否存在
if [ ! -f "$CONFIG_FILE" ]; then
    echo "错误: 配置文件 $CONFIG_FILE 不存在"
    exit 1
fi

echo ""
echo "=== 分析源文件 ==="

# 分析源文件
if ls src/*.cpp 1> /dev/null 2>&1; then
    echo "分析 src/*.cpp..."
    $CLANG_TIDY_PATH \
        --config-file="$CONFIG_FILE" \
        --header-filter="$HEADER_FILTER" \
        src/*.cpp \
        -- \
        -std=c++17 \
        -Iinclude \
        -Isrc
else
    echo "未找到源文件"
fi

echo ""
echo "=== 分析头文件 ==="

# 分析头文件
if ls include/*.hpp 1> /dev/null 2>&1; then
    echo "分析 include/*.hpp..."
    $CLANG_TIDY_PATH \
        --config-file="$CONFIG_FILE" \
        --header-filter="$HEADER_FILTER" \
        include/*.hpp \
        -- \
        -std=c++17 \
        -Iinclude \
        -Isrc
else
    echo "未找到头文件"
fi

echo ""
echo "=== clang-tidy分析完成 ==="
echo ""
echo "提示:"
echo "- 要自动修复问题，运行: ./run_clang_tidy.sh --fix"
echo "- 要查看特定检查，运行: clang-tidy --list-checks"
echo "- 要禁用特定检查，编辑 .clang-tidy 文件"

# 如果传入--fix参数，则运行修复
if [ "$1" = "--fix" ]; then
    echo ""
    echo "=== 自动修复问题 ==="

    if ls src/*.cpp 1> /dev/null 2>&1; then
        echo "修复 src/*.cpp..."
        $CLANG_TIDY_PATH \
            --config-file="$CONFIG_FILE" \
            --header-filter="$HEADER_FILTER" \
            --fix \
            src/*.cpp \
            -- \
            -std=c++17 \
            -Iinclude \
            -Isrc
    fi

    if ls include/*.hpp 1> /dev/null 2>&1; then
        echo "修复 include/*.hpp..."
        $CLANG_TIDY_PATH \
            --config-file="$CONFIG_FILE" \
            --header-filter="$HEADER_FILTER" \
            --fix \
            include/*.hpp \
            -- \
            -std=c++17 \
            -Iinclude \
            -Isrc
    fi

    echo "自动修复完成！"
fi
