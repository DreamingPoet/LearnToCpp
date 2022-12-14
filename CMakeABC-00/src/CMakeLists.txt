# 设置变量
# ${PROJECT_SOURCE_DIR} 是 CMake 内置变量，项目根目录
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)
# 打印消息
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

# 添加 include 目录
include_directories(${THIRD_PARTY_DIR}/doodle/include)

# 添加 链接静态库 目录
link_directories(${THIRD_PARTY_DIR}/doodle/lib/Win64)

# 设置变量
set(SRC_LIST HelloWorld.cpp)

# 添加可执行文件，引用 变量 SRC_LIST
add_executable(HelloWorld ${SRC_LIST})
# 打印消息
message(STATUS "SRC_LIST = ${SRC_LIST}")
# 添加目标连接库文件
target_link_libraries(HelloWorld doodle.lib)