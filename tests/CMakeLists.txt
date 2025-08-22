# 测试配置
if(BUILD_TESTS)
    # 创建测试可执行文件
    add_executable(unit_tests test_main.cpp)

    # 链接Google Test
    target_link_libraries(unit_tests GTest::GTest GTest::Main)

    # 添加测试
    add_test(NAME UnitTests COMMAND unit_tests)
endif()
