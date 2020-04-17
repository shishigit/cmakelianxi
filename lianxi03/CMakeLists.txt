#################################################################
## 相比 lianxi01，这里添加了动态编译选项 USE_MYMATH
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
