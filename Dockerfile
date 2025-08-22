# 现代C++17项目Docker配置
FROM ubuntu:22.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive
ENV CMAKE_VERSION=3.25.1

# 安装系统依赖
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# 安装最新版本的CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
    && chmod +x cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
    && ./cmake-${CMAKE_VERSION}-Linux-x86_64.sh --skip-license --prefix=/usr/local \
    && rm cmake-${CMAKE_VERSION}-Linux-x86_64.sh

# 设置工作目录
WORKDIR /workspace

# 复制项目文件
COPY . .

# 创建构建目录
RUN mkdir -p build

# 构建项目
RUN cd build && \
    cmake .. && \
    make -j$(nproc)

# 设置默认命令
CMD ["./build/bin/cppTest"]
