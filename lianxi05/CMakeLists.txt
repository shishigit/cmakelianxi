#################################################################
## 相比 lianxi04，这里多了系统检查
#################################################################

# 指定 cmake 的最低版本
cmake_minimum_required(VERSION 3.10)

# 设定项目名称和版本号
project(Tutorial VERSION 1.0)

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 配置编译选项， 此选项需要在 TutorialConfig.h.in 中的配置的配合
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# 系统函数检测
include(CheckSymbolExists)
set(CMAKE_REQUIRED_LIBRARIES "m")
check_symbol_exists(log "math.h" DINGJI_HAVE_LOG)
check_symbol_exists(expx "math.h" DINGJI_HAVE_EXPX)

# cmake 处理的配置文件,详情对比两个文件
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 动态添加链接选项
if (USE_MYMATH)
    # 添加一个动态链接库，这个需要和子级配合
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
endif ()

# 添加一个执行程序
add_executable(${PROJECT_NAME} tutorial.cxx)

# 添加链接目录
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

# 包含 cmake 处理后的文件夹，使得找到处理后的配置
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        "${PROJECT_BINARY_DIR}"
)

# 添加安装规则
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
        DESTINATION include
        )

# 启用测试
enable_testing()

# 添加一个测试
add_test(NAME Runs COMMAND Tutorial 25)

# 添加一个测试
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
        PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
        )

# 定义个 cmake 函数，简化代码
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
            PROPERTIES PASS_REGULAR_EXPRESSION ${result}
            )
endfunction(do_test)

# 使用函数添加一些测试
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is [-nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 is 0.01")
