#!/bin/bash

# LLVM工具链环境变量设置脚本

echo "=== 设置LLVM工具链环境变量 ==="

# 检测LLVM安装路径
LLVM_PATH=""
if [ -d "/opt/homebrew/opt/llvm" ]; then
    LLVM_PATH="/opt/homebrew/opt/llvm"
elif [ -d "/usr/local/opt/llvm" ]; then
    LLVM_PATH="/usr/local/opt/llvm"
else
    echo "错误: 未找到LLVM安装路径"
    echo "请先安装LLVM: brew install llvm"
    exit 1
fi

echo "找到LLVM路径: $LLVM_PATH"

# 设置环境变量
export PATH="$LLVM_PATH/bin:$PATH"
export CC="$LLVM_PATH/bin/clang"
export CXX="$LLVM_PATH/bin/clang++"
export LD="$LLVM_PATH/bin/ld64.lld"
export AR="$LLVM_PATH/bin/llvm-ar"
export NM="$LLVM_PATH/bin/llvm-nm"
export RANLIB="$LLVM_PATH/bin/llvm-ranlib"
export STRIP="$LLVM_PATH/bin/llvm-strip"
export OBJCOPY="$LLVM_PATH/bin/llvm-objcopy"
export OBJDUMP="$LLVM_PATH/bin/llvm-objdump"
export READELF="$LLVM_PATH/bin/llvm-readelf"
export SIZE="$LLVM_PATH/bin/llvm-size"

# 设置编译器标志
export CFLAGS="-I$LLVM_PATH/include"
export CXXFLAGS="-I$LLVM_PATH/include"
export LDFLAGS="-L$LLVM_PATH/lib"

echo "环境变量已设置:"
echo "PATH: $PATH"
echo "CC: $CC"
echo "CXX: $CXX"
echo "LD: $LD"

echo ""
echo "要永久设置，请将以下内容添加到 ~/.zshrc 或 ~/.bash_profile:"
echo ""
echo "# LLVM工具链环境变量"
echo "export PATH=\"$LLVM_PATH/bin:\$PATH\""
echo "export CC=\"$LLVM_PATH/bin/clang\""
echo "export CXX=\"$LLVM_PATH/bin/clang++\""
echo "export LD=\"$LLVM_PATH/bin/ld64.lld\""
echo "export AR=\"$LLVM_PATH/bin/llvm-ar\""
echo "export NM=\"$LLVM_PATH/bin/llvm-nm\""
echo "export RANLIB=\"$LLVM_PATH/bin/llvm-ranlib\""
echo "export STRIP=\"$LLVM_PATH/bin/llvm-strip\""
echo "export OBJCOPY=\"$LLVM_PATH/bin/llvm-objcopy\""
echo "export OBJDUMP=\"$LLVM_PATH/bin/llvm-objdump\""
echo "export READELF=\"$LLVM_PATH/bin/llvm-readelf\""
echo "export SIZE=\"$LLVM_PATH/bin/llvm-size\""
echo "export CFLAGS=\"-I$LLVM_PATH/include\""
echo "export CXXFLAGS=\"-I$LLVM_PATH/include\""
echo "export LDFLAGS=\"-L$LLVM_PATH/lib\""

echo ""
echo "设置完成！现在可以使用LLVM工具链了。"
