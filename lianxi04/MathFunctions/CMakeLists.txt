# 添加一个动态链接库，这个需要和父级配合
add_library(MathFunctions mysqrt.cxx)

# 使得任何使用该库的代码，自动包含该库的头文件
target_include_directories(MathFunctions
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

# 安装规则
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
