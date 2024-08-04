# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(SCULLTest C)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR)/bin)

# 添加可执行文件
add_executable(scull_test scull_test.c)
