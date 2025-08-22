# 测试配置
if(BUILD_TESTS)
    # 创建测试可执行文件
    add_executable(unit_tests test_main.cpp ${CMAKE_SOURCE_DIR}/src/example.cpp)

    # 链接Google Test（使用源码编译的库）
    target_link_libraries(unit_tests gtest gtest_main)

    # 设置包含目录
    target_include_directories(unit_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
    )

    # 添加测试
    add_test(NAME UnitTests COMMAND unit_tests)
endif()
