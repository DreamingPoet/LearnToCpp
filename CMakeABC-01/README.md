# CMake 详细入门练习

## 一. make 基本介绍

make 是用来构建和管理工程的工具。  
Makefile 描述了整个工程的编译、连接等规则：  
 * 需要编译哪些源文件以及如何编译
 * 需要创建哪些库文件以及如何创建
 * 如何产生可执行文件

Makefile就像一个Shell脚本一样，也可以执行操作系统的命令，也就可以进行更复杂的功能操作，比如下载依赖，解压，新建文件或目录，文件拷贝删除，等等。

make是一个命令工具，它解释并处理 Makefile 中的指令，大多数的IDE都有这个命令，比如：Delphi的make，Visual C++的nmake，Linux下GNU的make。  
一旦Makefile文件编写好，执行一条make命令即可自动编译整个工程。

make工作时的执行步骤入下：  
1. 读入所有的Makefile。
2. 读入被include的其它Makefile。
3. 初始化文件中的变量。
4. 推导隐晦规则，并分析所有规则。
5. 为所有的目标文件创建依赖关系链。
6. 根据依赖关系，决定哪些目标要重新生成。
7. 执行生成命令。

makefile 学习文档：  
https://www.gnu.org/software/make/manual/html_node/index.html  
https://makefiletutorial.com/  
https://seisman.github.io/how-to-write-makefile/index.html  


## 二. cmake 基本介绍

CMake 可以生成一个本地构建环境或本地IDE工程(比如 Unix 会生成Makefile文件，Windows下会生成一个VS工程)，使用该环境或者工程就可以编译生成目标文件。

你或许听过好几种 Make 工具，例如 GNU Make ，QT 的 qmake ，微软的 MS nmake，BSD Make（pmake），Makepp，等等。   
这些 Make 工具遵循着不同的规范和标准，所执行的 Makefile 格式也千差万别。   
这样就带来了一个严峻的问题：如果软件想跨平台，必须要保证能够在不同平台编译。   
而如果使用上面的 Make 工具，就得为每一种标准写一次 Makefile ，这将是一件让人抓狂的工作。   

为了解决上述问题：  
它首先允许开发者编写一种平台无关的 CMakeList.txt 文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化 Makefile 或者 工程文件，如 Unix 的 Makefile 或 Windows 的 Visual Studio 工程,从而做到“Write once, run everywhere”。
显然，CMake 是一个比上述几种 make 更上层的编译/构建工具。


学习文档：  
https://cmake.org/cmake/help/latest/index.html  
https://cmake.org/cmake/help/latest/guide/tutorial/index.html  
https://cloud.tencent.com/developer/article/1561162  
https://blog.csdn.net/qwq1503/article/details/85866602  
https://www.cnblogs.com/yymn/p/7780816.html  
https://blog.csdn.net/afei__/article/details/81201039 

<!-- Android NDK 从入门到精通（汇总篇）  
https://blog.csdn.net/afei__/article/details/81290711   -->


## 三. 练习
### 3.1 练习目标
    1、用 CMake 管理一个可执行文件 `HelloWorld`，在 Windows 平台完成构建  
    2、用 CMake 管理一个库 `doodle`，在 Windows 平台完成构建  
    3、`HelloWorld` 引入库 `doodle`，在 Windows 平台完成构建  
    4、在 Linux 平台完成以上步骤  
    5、在 Windows 和 Linux 上完成交叉编译出 Android 库文件  

### 3.2 准备工作  
 * 安装 cmake，略  
 * 安装 visual studio，略  
 * cmake --version 查看版本  
 * cmake --help 查看各种命令的说明  
 * cmake --help 中能看到 Generators 相关的内容  
 * 列出了当前平台可用的 Generators，我显示：  
 \* Visual Studio 16 2019  
 * 带 \* 表示默认生成器，也可以用 -G 参数指定

扩展阅读：  
cmake中有个概念叫做 [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators)  

它允许cmake支持不同的底层，比如Makefile系列、Ninja系列等。例如要产生Ninja，加上 -G Ninja 即可：cmake -G Ninja如果没有 cmake --build . 这条命令，就需要调用底层命令，比如make或者ninja。  
但现在cmake提供了一个统一的命令接口，不管底层是啥，直接--build即可。  
另外，建议学习[modern cmake](https://cliutils.gitlab.io/modern-cmake/)：


### 3.3 Windows 构建 HelloWorld 项目
项目目录：
``` bash
.
│  CMakeLists.txt
└─src
        CMakeLists.txt
        HelloWorld.cpp
```

./CMakeLists.txt

``` bash
# cmake 最低版本要求
cmake_minimum_required(VERSION 3.15.0)
# 项目名称
project(HelloWorld)
# src 指定 CMakeLists.txt 和代码文件所在的目录
# bin 指定 输出文件的目录, 如果不指定则默认在src目录下
add_subdirectory(src bin)
```
./src/CMakeLists.txt
``` bash
# 设置变量
set(SRC_LIST HelloWorld.cpp)

# 添加可执行文件，引用 变量 SRC_LIST
add_executable(HelloWorld ${SRC_LIST})
# 打印消息
message(STATUS "SRC_LIST = ${SRC_LIST}")
```
./src/HelloWorld.cpp
``` c++
#include<iostream>
int main(int argc, char *argv[]){
   std::cout << "Hello World!" << std::endl;
   return 0;
}
```

关于源内构建和源外构建：
源内构建会在项目目录中生成一堆中间文件，污染源文件，这里直接使用源外构建。

```bash
mkdir build
cd build
cmake ..
```
清除CMake缓存，就直接删除 build 文件夹即可。

此时项目目录（其他文件忽略）：
```bash
.
│  CMakeLists.txt
├─build
│  │  HelloWorld.sln
│  │  ...
│  ├─bin
│  └─CMakeFiles
└─src
        CMakeLists.txt
        HelloWorld.cpp
```

多出了 bin 文件夹和 sln 文件。

* 以上是 cmake 的第一个阶段，配置阶段 Configure 和 Generate，也就是配置和生成对应平台的工程文件
* 接下来是第二个阶段，构建阶段 build，也就是完成工程的编译和构建

可以，双击打开 HelloWorld.sln 即可启动 VS，
在解决方案目录中选择 HelloWorld 作为默认启动项，点击运行，输出 HelloWorld，并且在 build/bin/Debug 目录下生成了 HelloWorld.exe 可执行文件。  
也可以，不启动 VS, 直接使用cmake 的 --build 命令, 在build目录下执行：

```bash
# 简单版，默认生成Debug
cmake --build .

# 完整版
# --build . 指定当前目录为构建目录
# --target 默认All，构建所有目标
# --config Release 指定编译Release版本
# install 执行安装
cmake --build . --target --config Release install
```
build/bin/Debug 和 build/bin/Release 目录下生成了 HelloWorld.exe 可执行文件。
```bash
# 运行
./bin/Release/HelloWorld.exe
# 输出
Hello World!
```
### 3.4 Windows 构建 doodle 库项目

项目目录：
``` bash
.
│  CMakeLists.txt
└─src
        CMakeLists.txt
        HelloWorld.cpp
```








Makefile

CC代表" C编译器"(在GCC的缩写中，也被视为"编译器集合")。
LD是链接器(来自"链接编辑器"或"加载程序")。
这些在makefile中也很常用(请参见GNU Make手册的"隐式变量"一章)：
CPP代表" C预处理程序"
CXX是C ++编译器
AS是汇编语言编译器
AR是一个存档维护程序