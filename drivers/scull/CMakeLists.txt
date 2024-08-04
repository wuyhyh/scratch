# CMakeLists.txt

# 指定所需的最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言
project(SCULLTest C)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 添加可执行文件
# 指定源文件 scull_test.c 并生成名为 scull_test 的可执行文件
add_executable(scull_test ../scull_test.c)
