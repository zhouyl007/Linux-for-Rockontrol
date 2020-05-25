# about linux dev

## 一、vscode 配置时遇到的问题及解决办法：

###  1、The authenticity of host xx(192.168.253.145) can't be established.

ssh对主机的public_key的检查等级是根据StrictHostKeyChecking变量来配置的。默认情况下,StrictHostKeyChecking=ask。

三种配置：

1.StrictHostKeyChecking=no最不安全的级别，内网**测试**时建议使用。如果连接**server**的key在本地不存在，那么就自动添加到文件中（默认是known_hosts），并且给出一个警告。

2.StrictHostKeyChecking=ask  默认的级别，就是授权问题提示。如果连接和key不匹配，给出提示，并拒绝登录。

3.StrictHostKeyChecking=yes  最安全的级别，如果连接与key不匹配，就拒绝连接，不会提示详细信息。  

在内网的进行的一些测试，为了方便，选择最低的安全级别，可在.ssh/config（或者/etc/ssh/ssh_config）中配置：

StrictHostKeyChecking no

UserKnownHostsFile /dev/null 

### 2、过程试图写入的管道不存在.

可能是因为win10内置的ssh的问题，由于装了Git，且自带ssh，因此可以在环境变量中将win10内置ssh的路径替换为git的

这是原本环境变量中路径，将其删除

%SYSTEMROOT%\System32\OpenSSH\

这是我电脑上git中ssh的路径，添加到环境变量（Path）中

C:\Program Files\Git\usr\bin

![](E:\files_for_learn\Linux-for-Rockontrol\linux-for-Rockontrol\pics\aHR0cHM6Ly9naXRlZS5jb20vdG1oaGhoL3BpdGN1cmVzL3Jhdy9tYXN0ZXIvaW1nLzIwMjAwMzI4MjEwMTQxLnBuZw.jpg)

### 3、permission denied.

ubuntu下，sudo vi /etc/ssh/sshd_config 找到PermitRootLogin，修改为yes 重启ssh服务。

### 4、getPlatformForHost was canceled.







### 5、Bad owner or permissions

目前实测有效的办法：

这个出错意味着：文件夹.ssh 的权限不仅仅是windows 当前用户拥有或者当前用户权限不足，故修改权限即可。

找到.ssh文件夹。它通常位于C:\Users，例如C:\Users\//.ssh。
右键单击.ssh文件夹，然后单击“属性”。
找到并点击“安全”标签。
然后单击“高级”。 单击“禁用继承”，单击“确定”。 将出现警告弹出窗口。单击“从此对象中删除所有继承的权限”。
你会注意到所有用户都将被删除。让我们添加所有者。在同一窗口中，单击“编辑”按钮。
接下来，单击“添加”以显示“选择用户或组”窗口。
单击“高级”，然后单击“立即查找”按钮。应显示用户结果列表。 选择您的用户帐户。
然后单击“确定”（大约三次）以关闭所有窗口。
完成所有操作后，再次关闭并打开VSCode 并尝试连接到远程SSH主机。

### 6、launch.json部分关键字不识别

与插件安装位置有关（远程、本地），该问题需要继续探索解决方法。

### 7、解决vscode打开页面覆盖问题

ctrl+shift+p -->输入settings进行搜索-->找到User Setting -->输入enablePreview(选项在Workbench工作台中)搜索 -->取消勾选enablePreview





## 二、cmake常用变量及定义

常用预定义变量：

变量名							含义

PROJECT_NAME  					project命令中写的项目名

CMAKE_VERSION					当前使用CMake的版本

CMAKE_SOURCE_DIR				工程顶层目录，即入口CMakeLists文件所在路径

PROJECT_SOURCE_DIR			同CMAKE_SOURCE_DIR

CMAKE_BINARY_DIR				工程编译发生的目录，即执行cmake命令进行项目配置的目录，一般为build

PROJECT_BINARY_DIR				同CMAKE_BINARY_DIR

CMAKE_CURRENT_SOURCE_DIR	当前处理的CMakeLists.txt所在的路径

CMAKE_CURRRENT_BINARY_DIR	当前处理的CMakeLists.txt中生成目标文件所在编译目录

CMAKE_CURRENT_LIST_FILE		输出调用这个变量的CMakeLists.txt文件的完整路径

CMAKE_CURRENT_LIST_DIR		当前处理的CMakeLists.txt文件所在目录的路径

CMAKE_INSTALL_PREFIX			指定make install命令执行时包安装路径

CMAKE_MODULE_PATH			find_package命令搜索包路径之一，默认为空

​							       SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)， 

EXECUTABLE_OUTPUT_PATH            重新定义目标二进制可执行文件的存放位置

LIBRARY_OUTPUT_PATH			重新定义目标链接库文件的存放位置 

编译配置相关变量：

变量名							含义

CMAKE_BUILD_TYPE				编译选项，Release或者Debug，如set(CMAKE_BUILD_TYPE "Release")

CMAKE_CXX_FLAGS				编译标志，设置C++11编译:

​								set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

CMAKE_CXX_STANDARD			也可以设置C++11编译，set(CMAKE_CXX_STANDARD 11)



编译选项说明：

-Wall：选项可以打印出编译时所有的错误或者警告信息。这个选项很容易被遗忘，编译的时候，没有错误或者警告提示，以为自己的程序很完美，其实，里面有可能隐藏着许多陷阱。变量没有初始化，类型不匹配，或者类型转换错误等警告提示需要重点注意，错误就隐藏在这些代码里面。没有使用的变量也需要注意，去掉无用的代码，让整个程序显得干净一点。下次写Makefile的时候，一定加-Wall编译选项。

-O0： 表示编译时没有优化。

-O1： 表示编译时使用默认优化。

-O2： 表示编译时使用二级优化。

-O3： 表示编译时使用最高级优化。

-Os：相当于-O2.5优化。



## 三、c oop思维

面向对象就是封装继承和多态。

封装：struct实现。

继承：指针实现，就是把父类包含在结构体中。

多态：可以用指针实现。虚表（Virtual Table）是这个类所有虚函数的函数指针的集合。虚指针（Virtual Pointer）是一个指向虚表的指针。这个虚指针必须存在于每个对象实例中，会被所有子类继承。一般实现多态，父结构体必须是子结构体的第一个元素，这样就可以通过强制转换子类和父类随意转换。

具体实例见工程oop/oop_2。