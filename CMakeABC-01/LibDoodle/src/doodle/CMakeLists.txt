SET (SRC_LIST doodle.cpp)
# 添加静态库
ADD_LIBRARY(doodle STATIC ${SRC_LIST})

# 安装时把对应的文件，拷贝到对应的目录中
INSTALL(FILES doodle.h DESTINATION ${PROJECT_BINARY_DIR}/include/doodle)
 
# 二进制，静态库，动态库安装都是用 TARGETS
#  ARCHIVE特指静态库，LIBRATY特指动态库，RUNTIME特指可执行目标二进制
INSTALL(TARGETS doodle ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib/Win64)