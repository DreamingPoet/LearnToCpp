# 设置变量
set(SRC_LIST HelloWorld.cpp)

# 添加可执行文件，引用 变量 SRC_LIST
add_executable(HelloWorld ${SRC_LIST})
# 打印消息
message(STATUS "SRC_LIST = ${SRC_LIST}")
