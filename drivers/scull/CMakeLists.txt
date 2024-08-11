# CMakeLists.txt

# 指定所需的最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言
project(SCULLTest C)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 添加可执行文件
# 指定源文件 test_scull.c 并生成名为 test_scull 的可执行文件
add_executable(test_scull ../test_scull.c)
