cmake_minimum_required(VERSION 3.16)
project(cppTest VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++20标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
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

# 查找spdlog
add_subdirectory(third_party/spdlog)

#nlohmann_json
add_subdirectory(third_party/nlohmann_json)

#glm
add_subdirectory(third_party/glm)


#SDL3
add_subdirectory(third_party/SDL EXCLUDE_FROM_ALL)

#SDL_image
# set(SDLIMAGE_VENDORED ON)
add_subdirectory(third_party/SDL_image EXCLUDE_FROM_ALL)

#SDL_ttf
set(SDLTTF_VENDORED ON)
add_subdirectory(third_party/SDL_ttf EXCLUDE_FROM_ALL)

#SDL_mixer
set(SDLMIXER_VENDORED ON)
add_subdirectory(third_party/SDL_mixer EXCLUDE_FROM_ALL)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 添加spdlog
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

# 添加nlohmann_json
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

# 添加glm
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

# 添加SDL3
target_link_libraries(${PROJECT_NAME} PUBLIC 
                        SDL3_image::SDL3_image
                        SDL3_mixer::SDL3_mixer
                        SDL3_ttf::SDL3_ttf
                        SDL3::SDL3)

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 设置资源目录
# 复制assets文件夹到构建目录
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# 如果有测试，可以添加测试支持
# option(BUILD_TESTS "Build tests" OFF)
# if(BUILD_TESTS)
#     message(STATUS "Building tests")
#     enable_testing()
#     # 添加Google Test作为子目录
#     add_subdirectory(third_party/googletest)
#     add_subdirectory(tests)
# endif()
