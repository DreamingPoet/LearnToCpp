# cmake 最低版本要求
cmake_minimum_required(VERSION 3.15.0)
# 项目名称
project(LibDoodle)
# src 指定 CMakeLists.txt 和代码文件所在的目录
# bin 指定 输出文件的目录, 如果不指定则默认在src目录下
add_subdirectory(LibDoodle/src/doodle bin)