# 指定 cmake 的最低版本
cmake_minimum_required(VERSION 3.10)

# 设定项目名称和版本号
project(Tutorial VERSION 1.0)

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 配置编译选项
option(USE_MYMATH "Use tutorial provided math implementation" off)


# cmake 处理的配置文件,详情对比两个文件
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 动态添加链接选项
if (USE_MYMATH)
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif ()

# 添加一个执行程序
add_executable(Tutorial tutorial.cxx)

# 添加链接目录
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

# 包含 cmake 处理后的文件夹，使得找到处理后的配置
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        "${PROJECT_BINARY_DIR}"
        ${EXTRA_INCLUDES}
)
