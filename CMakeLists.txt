cmake_minimum_required(VERSION 3.16)
project(cppTest VERSION 1.0.0 LANGUAGES CXX)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)
endif()

# 查找clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy" PATHS "/opt/homebrew/opt/llvm/bin" NO_DEFAULT_PATH)
if(NOT CLANG_TIDY_EXE)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
endif()
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
else()
    message(STATUS "clang-tidy not found")
endif()

# 选项：启用/禁用clang-tidy
option(ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
if(ENABLE_CLANG_TIDY AND CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
    message(STATUS "clang-tidy enabled")
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 如果有测试，可以添加测试支持
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    # 添加Google Test作为子目录
    add_subdirectory(third_party/googletest)
    add_subdirectory(tests)
endif()
