<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [2. Unix标准与实现](#2-unix%E6%A0%87%E5%87%86%E4%B8%8E%E5%AE%9E%E7%8E%B0)
  - [2.0 各种组织](#20-%E5%90%84%E7%A7%8D%E7%BB%84%E7%BB%87)
  - [2.1 标准化](#21-%E6%A0%87%E5%87%86%E5%8C%96)
    - [2.1.1 ISO C](#211-iso-c)
    - [2.1.2 IEEE POSIX](#212-ieee-posix)
    - [2.1.3 Single UNIX Specification](#213-single-unix-specification)
  - [2.2 实现](#22-%E5%AE%9E%E7%8E%B0)
    - [2.2.1 UNIX系统演化史](#221-unix%E7%B3%BB%E7%BB%9F%E6%BC%94%E5%8C%96%E5%8F%B2)
    - [2.2.2 各种UNIX介绍](#222-%E5%90%84%E7%A7%8Dunix%E4%BB%8B%E7%BB%8D)
  - [2.3 限制](#23-%E9%99%90%E5%88%B6)
    - [2.3.1 ISO C限制](#231-iso-c%E9%99%90%E5%88%B6)
    - [2.3.2 POSIX限制](#232-posix%E9%99%90%E5%88%B6)
    - [2.3.3 XSI限制](#233-xsi%E9%99%90%E5%88%B6)
    - [2.3.4 函数获取限制](#234-%E5%87%BD%E6%95%B0%E8%8E%B7%E5%8F%96%E9%99%90%E5%88%B6)
    - [2.3.5 不确定的运行时限制](#235-%E4%B8%8D%E7%A1%AE%E5%AE%9A%E7%9A%84%E8%BF%90%E8%A1%8C%E6%97%B6%E9%99%90%E5%88%B6)
  - [2.4 选项](#24-%E9%80%89%E9%A1%B9)
  - [2.5 功能测试宏](#25-%E5%8A%9F%E8%83%BD%E6%B5%8B%E8%AF%95%E5%AE%8F)
  - [2.6 基本数据类型](#26-%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%B1%BB%E5%9E%8B)
  - [2.7 标准之间的冲突](#27-%E6%A0%87%E5%87%86%E4%B9%8B%E9%97%B4%E7%9A%84%E5%86%B2%E7%AA%81)
  - [2.8 总结](#28-%E6%80%BB%E7%BB%93)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 2. Unix标准与实现

## 2.0 各种组织

各种参与制定标准的国际协会与组织：
- ISO，国际标准化组织，International Organization for Standardization。
- IEC，国际电子技术委员会，International Electrotechnical Commission。
- ANSI，美国国家标准学会，American National Standards Institute。
- IEEE，电气与电子工程师学会，Institute of Electrical and Electronics Engineers。
- 许多国际标准是由是由多个组织协作推出并在不同的标准使用不同名称的同一标准，比如ANSI C，也称C89，1989年ANSI推动制定，而后1990年ISO基本在此基础上几乎未做任何改动推出了ISO C，标准号ISO/IEC 9899:1990。
- 使用一个能说明信息的标准号来区分，不用那么考究细节，知道谁推出的，谁在维护即可。
- 某些其他标准可能由其他的组织维护。

## 2.1 标准化

### 2.1.1 ISO C

C语言标准变迁：
- ANSI C/C89，ISO/IEC 9899:1990。
- C99，ISO/IEC 9899:1999。
- C11，ISO/IEC 9899:2011。
- C17，ISO/IEC 9899:2018，内容很少，和C11几乎相同，当前版本。
- C23，下一代C标准。

C语言标准化：
- 基调在C89或之前就已经确定了，在此之后，新增革命性内容并不多，语言特性就不多介绍了，比如C99新增了VLA这种。编译器中都可以指定具体版本。
- APUE第三版全书使用C99标准下的C语言。向后兼容一般做得都挺好，高版本一般来说都能跑。
- 标准的提出是为了提高程序在不同操作系统环境、不同编译器、不同字长和指令集的硬件下的可移植性。
- C语言标准包括语言特性和库，语言特性不必多说，简单介绍库和头文件，注意标准库也是库是建立在系统调用之上的。

ISO C标准库头文件：

|标准|头文件|说明|
|:-|:-|:-|
|C89/C99|`<assert.h>     `| 断言，`assert`宏
|C89/C99|`<complex.h>    `| 复数算术运算支持
|C89/C99|`<ctype.h>      `| 字符分类和映射
|C89/C99|`<errno.h>      `| 出错码`errno`
|C89/C99|`<fenv.h>       `| 浮点环境
|C89/C99|`<float.h>      `| 浮点常量和特性
|C89/C99|`<inttypes.h>   `| 整数格式变换
|C89/C99|`<iso646.h>     `| 逻辑运算符和位运算符宏定义
|C89/C99|`<limits.h>     `| 整数范围，实现相关常量
|C89/C99|`<locale.h>     `| 本地化
|C89/C99|`<math.h>       `| 数学函数、类型声明、常量
|C89/C99|`<setjmp.h>     `| 非局部`goto`，比如`setjmp` `longjmp`
|C89/C99|`<signal.h>     `| 信号处理
|C89/C99|`<stdarg.h>     `| 可变长度参数`va_list va_start va_arg va_end`
|C89/C99|`<stdbool.h>    `| 布尔类型和取值
|C89/C99|`<stddef.h>     `| 标准定义
|C89/C99|`<stdint.h>     `| 固定长度整型定义
|C89/C99|`<stdio.h>      `| 标准输入输出
|C89/C99|`<stdlib.h>     `| 实用函数，包括：整数浮点数与字符串互相转换、随机数、内存分配释放、终止退出程序、执行Shell程序、常用算法二分查找快排等、多字节字符集相关处理
|C89/C99|`<string.h>     `| 字符串与内存块相关操作
|C89/C99|`<tgmath.h>     `| 通用类型数学操作宏
|C89/C99|`<time.h>       `| 时间日期
|C89/C99|`<wchar.h>      `| 多字节和宽字符支持
|C89/C99|`<wctype.h>     `| 宽字符分类和映射
|C11    |`<stdalign.h>   `| 对齐，`alignas alignof`
|C11    |`<stdatomic.h>  `| 原子操作、内存屏障
|C11    |`<stdnoreturn.h>`| `noreturn`宏，不返回的函数
|C11    |`<threads.h>    `| 线程、锁
|C11    |`<uchar.h>      `| 16和32位宽度字符

注意：
- 最常用头文件：`<stdio.h> <stdlib.h> <string.h> <math.h>`。
- 原则上来说应当尽量使用标准头文件，像`<malloc.h>`这种实现头文件也包含`malloc`定义，但更好的用法是使用`<stdlib.h>`，`<memory.h>`也包含了`<string.h>`中的内存操作，但其实最好直接用`<string.h>`。

### 2.1.2 IEEE POSIX

标准化：
- [POSIX](https://en.wikipedia.org/wiki/POSIX)是由IEEE制定的标准族，是可移植操作系统接口（Portable Operating System Interface）的简称。
- 最初只是IEEE标准1003.1-1988（操作系统接口），后来扩充了其他标记为1003的标准和草案，如shell和使用程序（1003.2）。
- 总体来说标准号类似于：IEEE 1003.x-xxxx。APUE中仅关注操作系统接口，也就是1003.1-xxxx。
- 制定目的是为了提高应用程序在各种UNIX系统上环境之间的可移植性。
- IEEE 1003也称为POSIX.1标准，对应的ISO国际标准号是ISO/IEC 9945。说的都是一个东西，后续会更多使用POSIX.1来指代。
- 1003.1说明了一个接口，而不是实现，所以并不区分系统调用和库函数。后续统称为函数。

变迁与演进：
- 推出：IEEE 1003.1的1988版，即IEEE 1003.1-1988递交ISO之后，出版为了ISO/IEC 9945-1:1990。通常称之为POSIX.1，即是起源。
- 后续提出的若干新增标准的细节就不多说了，不需要那么挖掘历史，用POSIX.1 xxxx年版来说明标准的年份即可。

标准内容：
- ISO C的适用范围也更宽一些，而POSIX.1只适用于UNIX系统。
- APUE 第三版描述POSIX.1 2008年版。接口分为必需部分和可选部分。
- POSIX.1包含了ISO C标准库函数，是建立在标准C语言基础上的，这部分接口是必须实现的接口中的一部分就不赘述了。

除C标准库之外的POSIX标准的必须部分：

|头文件|说明|
|:-|:-|
|`<aio.h>        `|异步IO
|`<cpio.h>       `|`cpio`归档值，cpio就类似于tar
|`<dirent.h>     `|目录项，`opendir/closedir/readdir`等
|`<dlfcn.h>      `|动态链接，处理共享对象
|`<fcntl.h>      `|文件控制，`open/creat`等
|`<fnmatch.h>    `|文件名模式匹配，`fnmatch`
|`<glob.h>       `|路径名模式匹配与生成，`glob`
|`<grp.h>        `|组文件`/etc/group`操作
|`<iconv.h>      `|字符集变换
|`<langinfo.h>   `|语言信息常量，本地化相关
|`<monetary.h>   `|货币类型与函数
|`<netdb.h>      `|网络数据库操作
|`<nl_types.h>   `|消息类
|`<poll.h>       `|`poll`函数，IO复用
|`<pthread.h>    `|线程
|`<pwd.h>        `|口令文件
|`<regex.h>      `|正则表达式
|`<sched.h>      `|进程调度
|`<semaphore.h>  `|信号量
|`<strings.h>    `|字符串操作
|`<tar.h>        `|`tar`归档值
|`<termios.h>    `|终端I/O
|`<unistd.h>     `|符号常量，常用函数
|`<wordexp.h>    `|字扩充，`wordexp`
||
|`<arpa/inet.h>  `|因特网定义
|`<net/if.h>     `|套接字本地接口
|`<netinet/in.h> `|因特网地址族
|`<netinet/tcp.h>`|TCP协议
||
|`<sys/mman.h>   `|内存管理
|`<sys/select.h> `|`select`函数，IO复用
|`<sys/socket.h> `|套接字接口，`send/listen/recv`等
|`<sys/stat.h>   `|文件状态，`mkdir/chmod`等
|`<sys/statvfs.h>`|文件系统信息
|`<sys/times.h>  `|进程时间，`clock_t/times`
|`<sys/types.h>  `|基本系统数据类型
|`<sys/un.h>     `|UNIX域套接字定义
|`<sys/utsname.h>`|系统名，`uname`
|`<sys/wait.h>   `|进程控制，`wait/waitpid`

- 可以看到其中有很多很熟悉的东西。

XSI可选部分：

|头文件|说明|
|:-|:-|
|`<fmtmsg.h>      `|输出消息格式化，`fmtmsg`函数
|`<ftw.h>         `|文件树漫游
|`<libgen.h>      `|路径名管理，`dirname`
|`<ndbm.h>        `|数据库操作，Linux不提供
|`<search.h>      `|查找表
|`<syslog.h>      `|系统出错日志记录，`syslog`函数
|`<utmpx.h>       `|用户账户数据库
|`<sys/ipc.h>     `|IPC，进程间通信
|`<sys/msg.h>     `|XSI消息队列
|`<sys/resource.h>`|资源操作
|`<sys/sem.h>     `|XSI信号量
|`<sys/shm.h>     `|XSI共享存储
|`<sys/time.h>    `|时间类型
|`<sys/uio.h>     `|矢量I/O

标准定义的可选部分：

|头文件|说明|
|:-|:-|
|`<mqueue.h>`|消息队列
|`<spawn.h> `|实时spawn接口

说明：
- 可选部分接口按照功能进一步分为40个分区。每个部分用一个2~3个字母缩写组成的XSI选项码标识，其中的接口依赖于特定选项的支持。很多选项处理实时扩展。细节就不展开了。

### 2.1.3 Single UNIX Specification

SUS规范：
- 单一UNIX规范（SUS，Single UNIX Specification），是POSIX.1的一个超集，定义了一些附加接口扩展了POSIX.1规范提供的功能，POSIX.1相当于SUS中的基本规范部分。
- 文档可以在[OpenGroup的页面](https://publications.opengroup.org/standards/unix/single-unix-specification)上找到。
- POSIX.1中的X/Open系统接口（XSI，X/Open System Interface）选项描述了可选的接口，定义了遵循XSI的实现必须支持POSIX.1中的哪些可选部分。这些部分包括：文件同步、线程栈地址和长度属性、线程进程共享同步、`_XOPEN_UNIX`符号常量。
- 遵循了XSI选项的实现才能称为UNIX系统。
- [Open Group](https://www.opengroup.org/)拥有UNIX的商标，他们使用SUS定义了一系列接口。必须实现支持的接口，通过认证和测试之后才能得到UNIX商标的许可证。
- 我们称Mac OS X/Solaris为UNIX系统，而Linux是类UNIX系统（UNIX-Like），是因为Linux提供UNIX编程环境，但没有进行UNIX认证。

变迁和演进：
- SUSv1，1994年。
- SUSv2，1997年。
- SUSv3，2001年，2004年修正为SUSv3 2004年版。
- SUSv4，2010年，包括POSIX.1-2008和X/OPEN Curses规范。

## 2.2 实现

### 2.2.1 UNIX系统演化史


[UNIX](https://zh.wikipedia.org/wiki/UNIX)和类UNIX系统家族树：

[![UNIX和类UNIX系统家族树](https://upload.wikimedia.org/wikipedia/commons/7/77/Unix_history-simple.svg)](https://upload.wikimedia.org/wikipedia/commons/7/77/Unix_history-simple.svg)

简介：
- 起源于PDP-11系统上运行的UNIX分时系统第6版（1976）和第7版（1979）（V6和V7）。这两个是在贝尔实验室外得到广泛应用的版本。
- 在此基础上演化出3个分支：
    - AT&T，System III和System V（UNIX商用版）。
    - BSD（Berkeley Software Distribution）分支，直到4.xBSD实现。
    - AT&T贝尔实验室的计算科学研究中心后续开发的8、9版本，终止与1990年的第10版。

### 2.2.2 各种UNIX介绍

SVR4：
- 即是System V R4，整合了多个操作系统功能。
- 1990发布，并提供了SVID接口定义，类似于POSIX。

4.4BSD：
- BSD（Berkeley Software Distribution）是加州大学伯克利分校的计算系统研究组（CSRG）开发的。
- 经过了4.2，4.3，最终终止于4.4BSD-Lite。

FreeBSD：
- FreeBSD基于4.4BSD-Lite。
- 免费使用并开源。
- 还有多个基于BSD开发的项目，比如OpenBSD，NetBSD。

Linux：
- 这个比较熟悉，1991年Linus为了替代MINIX而开发。
- 类UNIX。

Mac OS X：
- 核心称为Darwin。基于Mach内核、FreeBSD操作系统以及具有面向对象框架的驱动和其他内核扩展的结合。

Solaris：
- Sun公司开发，基于SVR4，唯一商业成功的SVR4后裔。
- 大部分代码开源作为OpenSolaris的一部分，建立社区。

还有很多其他UNIX版本。

APUE关注：
- 重点关注POSIX.1。
- 也会关注UNIX必须，但POSIX.1可选的内容。

## 2.3 限制

限制：
- 前面说述的标准中定义了许多实现定义的魔法数字和常量，为了改善在UNIX下程序的可移植性，就需要使用可移植的方法获取具体实现定义的限制（也就是这些数）。
- 有两种限制：编译时、运行时。
- 为了解决这个问题，提供三种手段：
    - 定义在头文件中，编译时确定的限制。
    - 文件目录无关的运行时限制使用`sysconf`函数。
    - 文件目录有关的运行时限制使用`pathconf`和`fpathconf`函数。
- 如果一个限制在一个给定系统上不会改变，那么可以静态定义在头文件中，但如果没有定义在头文件中，就必须运行时使用其中一个函数获取。

### 2.3.1 ISO C限制

ISO C中的限制：
- 在头文件`<limits.h>`中定义了各种整型的边界或者位宽：如`CHAR_MIN INT_MAX ULLONG_MAX`等边界常量，或者`CHAR_BIT`是表字符位宽的常量。
- `<float.h>`中同样定义了浮点数的边界。
- POSIX.1对这些值都有一定要求，比如`CHAR_BIT`必须为8。
- `<stdio.h>`中`FOPEN_MAX`常量，表具体实现保证可同时打开的标准IO的最小个数，标准要求至少为8，本地64位Linux为16。
- `<stdio.h>`中常量`TMP_MAX`，表由函数`tmpnam`函数产生的唯一文件名的最大个数。
- `<stdio.h>`中`FILENAME_MAX`常量表编译器支持的最长合法文件名。在UNIX中应避免使用，POSIX.1提供了更好的替代`NAME_MAX PATH_MAX`。
- 不同UNIX系统中很多常量都不一样。

### 2.3.2 POSIX限制

POSIX.1限制：
- POSIX.1中定义了大量操作系统来实现的限制，这是POSIX.1中最令人迷惑的部分。
- 虽然定义了大量限制和常量，但我们仅关心和基本POSIX.1接口有关的部分。分为7类：
- (1) 数值限制：`LONG_BIT` `SSZIE_MAX` `WORD_BIT`。
- (2) 最小值：`<limits.h>`中的25个常量，命名都像是`_POSIX_XXXX_MAX`。
- (3) 最大值：`_POSIX_CLOCKRES_MIN`。
- (4) 运行时可增加的值：`CHARCLASS_NAME_MAX` `COLL_WEIGHTS_MAX` `LINE_MAX` `NGROUPS_MAX` `RE_DUP_MAX`。
- (5) 运行时不变值（可能不确定）：16个以`_MAX`结尾的值，他们的最小可接受值大多都对应于最小值中的对应值。另  外`PAGESIZE`是系统内存页大小，字节为单位，最小值为1。共17个都定义在`<limits.h>`。加上和线程相关的4个限制以及和异步IO相关的3个限制。
- (6) 其他不变值：`NL_ARGMAX` `NL_MSGMAX` `NL_SETMAX` `NL_TEXTMAX`。
- (7) 路径不可变值：`FILESIZEBITS` `LINK_MAX` `MAX_CANON` `MAX_INPUT` `NAME_MAX` `PATH_MAX` `PIPE_BUF` `SYSLINK_MAX`。

说明：
- 最小值是不变的。对于最小值，他们是用来指定一个特征最具有约束性的值，一个符合POSIX.1的实现至少应该提供这么大的值，但他们都是包含`MAX`这是因为他们的含义都是类似某一种资源可以有的最大值。
- 为了保证可移植性，一个严格符合POSIX标准的应用程序不应该要求更大的值。因为UNIX系统有可能只满足了最小值而导致提供不了。
- 25个不变最小值每一个都有一个相关实现值。都是将最小值的前缀`_POSIX_`删掉后得到，类似于`XXXX_MAX`。这25个值分别有1(`SSIZE_MAX`)、2、15、7个值属于第1、4、5、7类。
- 可变的值不能在头文件中定义，就需要调用函数获取。

### 2.3.3 XSI限制

一些常量：
- 最小值：`NL_LANGMAX` `NZERO` `_XOPEN_IOV_MAX` `_XOPEN_NAME_MAX` `_XOPEN_PATH_MAX`。
- 运行时不变值：`IOV_MAX PAGE_SIZE`。
- 注意`_XOPEN_NAME_MAX` `_XOPEN_PATH_MAX`，因为考虑到`NAME_MAX PATH_MAX`可能比较小，所以XSI增加了具有较大最小值的符号。

### 2.3.4 函数获取限制

```c
#include <unistd.h>
long sysconf(int name);
long pathconf(const char *path, int name);
long fpathconf(int fd, int name);
```

说明：
- 后两个函数，一个用路径做参数一个用文件描述符。
- 一个限制量的符号加上前缀`_SC_`作为`sysconf`第一个参数。
- 加上`_PC_`作为`pathconf fpathconf`的第二个参数。
- 返回值：
    - 如果`name`不是一个合适的常量，都返回-1，并设置`errno`为`EINVAL`。
    - 有些`name`会返回一个变量值（大于等于0的）或者提示该值不确定。不确定的值通过返回-1体现，不改变`errno`值。
- `_SC_CLK_TCK`作为名称传入`sysconf`没有对应的限制名，返回值是每秒的时钟滴答数，用于`times`函数返回值。
- `pathconf fpathconf`的路径和文件描述符对应不同限制名对应的`name`参数有诸多限制。使用时需要特别注意，细节查看APUE或者man手册。
- 并非所有平台都定义所有限制。

本地的各种限制的值：
```
_POSIX_ADVISORY_INFO is defined (val is 200809)
sysconf says _POSIX_ADVISORY_INFO = 200809

_POSIX_ASYNCHRONOUS_IO is defined (val is 200809)
sysconf says _POSIX_ASYNCHRONOUS_IO = 200809

_POSIX_BARRIERS is defined (val is 200809)
sysconf says _POSIX_BARRIERS = 200809

_POSIX_CLOCK_SELECTION is defined (val is 200809)
sysconf says _POSIX_CLOCK_SELECTION = 200809

_POSIX_CPUTIME is defined (val is 0)
sysconf says _POSIX_CPUTIME = 200809

_POSIX_FSYNC is defined (val is 200809)
sysconf says _POSIX_FSYNC = 200809

_POSIX_IPV6 is defined (val is 200809)
sysconf says _POSIX_IPV6 = 200809

_POSIX_JOB_CONTROL is defined (val is 1)
sysconf says _POSIX_JOB_CONTROL = 1

_POSIX_MAPPED_FILES is defined (val is 200809)
sysconf says _POSIX_MAPPED_FILES = 200809

_POSIX_MEMLOCK is defined (val is 200809)
sysconf says _POSIX_MEMLOCK = 200809

_POSIX_MEMLOCK_RANGE is defined (val is 200809)
sysconf says _POSIX_MEMLOCK_RANGE = 200809

_POSIX_MEMORY_PROTECTION is defined (val is 200809)
sysconf says _POSIX_MEMORY_PROTECTION = 200809

_POSIX_MESSAGE_PASSING is defined (val is 200809)
sysconf says _POSIX_MESSAGE_PASSING = 200809

_POSIX_MONOTONIC_CLOCK is defined (val is 0)
sysconf says _POSIX_MONOTONIC_CLOCK = 200809

_POSIX_PRIORITIZED_IO is defined (val is 200809)
sysconf says _POSIX_PRIORITIZED_IO = 200809

_POSIX_PRIORITY_SCHEDULING is defined (val is 200809)
sysconf says _POSIX_PRIORITY_SCHEDULING = 200809

_POSIX_RAW_SOCKETS is defined (val is 200809)
sysconf says _POSIX_RAW_SOCKETS = 200809

_POSIX_READER_WRITER_LOCKS is defined (val is 200809)
sysconf says _POSIX_READER_WRITER_LOCKS = 200809

_POSIX_REALTIME_SIGNALS is defined (val is 200809)
sysconf says _POSIX_REALTIME_SIGNALS = 200809

_POSIX_REGEXP is defined (val is 1)
sysconf says _POSIX_REGEXP = 1

_POSIX_SAVED_IDS is defined (val is 1)
sysconf says _POSIX_SAVED_IDS = 1

_POSIX_SEMAPHORES is defined (val is 200809)
sysconf says _POSIX_SEMAPHORES = 200809

_POSIX_SHARED_MEMORY_OBJECTS is defined (val is 200809)
sysconf says _POSIX_SHARED_MEMORY_OBJECTS = 200809

_POSIX_SHELL is defined (val is 1)
sysconf says _POSIX_SHELL = 1

_POSIX_SPAWN is defined (val is 200809)
sysconf says _POSIX_SPAWN = 200809

_POSIX_SPIN_LOCKS is defined (val is 200809)
sysconf says _POSIX_SPIN_LOCKS = 200809

_POSIX_SPORADIC_SERVER is defined (val is -1)
sysconf says _POSIX_SPORADIC_SERVER = (no limit)

_POSIX_SYNCHRONIZED_IO is defined (val is 200809)
sysconf says _POSIX_SYNCHRONIZED_IO = 200809

_POSIX_THREAD_ATTR_STACKADDR is defined (val is 200809)
sysconf says _POSIX_THREAD_ATTR_STACKADDR = 200809

_POSIX_THREAD_ATTR_STACKSIZE is defined (val is 200809)
sysconf says _POSIX_THREAD_ATTR_STACKSIZE = 200809

_POSIX_THREAD_ATTR_CPUTIME is undefined
sysconf says _POSIX_THREAD_ATTR_CPUTIME = 200809

_POSIX_THREAD_PRIO_INHERIT is defined (val is 200809)
sysconf says _POSIX_THREAD_PRIO_INHERIT = 200809

_POSIX_THREAD_PRIORITY_SCHEDULING is defined (val is 200809)
sysconf says _POSIX_THREAD_PRIORITY_SCHEDULING = 200809

_POSIX_THREAD_PROCESS_SHARED is defined (val is 200809)
sysconf says _POSIX_THREAD_PROCESS_SHARED = 200809

_POSIX_THREAD_ROBUST_PRIO_INHERIT is defined (val is 200809)
sysconf says _POSIX_THREAD_ROBUST_PRIO_INHERIT = (not supported)

_POSIX_THREAD_ROBUST_PRIO_PROTECT is defined (val is -1)
sysconf says _POSIX_THREAD_ROBUST_PRIO_PROTECT = (not supported)

_POSIX_THREAD_SAFE_FUNCTIONS is defined (val is 200809)
sysconf says _POSIX_THREAD_SAFE_FUNCTIONS = 200809

_POSIX_THREAD_SPORADIC_SERVER is defined (val is -1)
sysconf says _POSIX_THREAD_SPORADIC_SERVER = (no limit)

_POSIX_THREADS is defined (val is 200809)
sysconf says _POSIX_THREADS = 200809

_POSIX_TIMEOUTS is defined (val is 200809)
sysconf says _POSIX_TIMEOUTS = 200809

_POSIX_TIMERS is defined (val is 200809)
sysconf says _POSIX_TIMERS = 200809

_POSIX_TYPED_MEMORY_OBJECTS is defined (val is -1)
sysconf says _POSIX_TYPED_MEMORY_OBJECTS = (no limit)

_POSIX_VERSION is defined (val is 200809)
sysconf says _POSIX_VERSION = 200809

_XOPEN_CRYPT is undefined
sysconf says _XOPEN_CRYPT = (no limit)

_XOPEN_ENH_I18N is defined (val is 1)
sysconf says _XOPEN_ENH_I18N = 1

_XOPEN_REALTIME is defined (val is 1)
sysconf says _XOPEN_REALTIME = 1

_XOPEN_REALTIME_THREADS is defined (val is 1)
sysconf says _XOPEN_REALTIME_THREADS = 1

_XOPEN_SHM is defined (val is 1)
sysconf says _XOPEN_SHM = 1

_XOPEN_UNIX is defined (val is 1)
sysconf says _XOPEN_UNIX = 1

_XOPEN_UUCP is undefined
no symbol for _XOPEN_UUCP

_XOPEN_VERSION is defined (val is 700)
sysconf says _XOPEN_VERSION = 700

_POSIX_CHOWN_RESTRICTED is defined (val is 0)
pathconf says _POSIX_CHOWN_RESTRICTED = 1

_POSIX_NO_TRUNC is defined (val is 1)
pathconf says _POSIX_NO_TRUNC = 1

_POSIX_VDISABLE is defined (val is 0)
pathconf says _POSIX_VDISABLE = 0

_POSIX_ASYNC_IO is defined (val is 1)
pathconf says _POSIX_ASYNC_IO = (no limit)

_POSIX_PRIO_IO is undefined
pathconf says _POSIX_PRIO_IO = (no limit)

_POSIX_SYNC_IO is undefined
pathconf says _POSIX_SYNC_IO = (no limit)

_POSIX2_SYMLINKS is undefined
pathconf says _POSIX2_SYMLINKS = 1
```
以及：
```
no symbol for ARG_MAX
ARG_MAX = 2097152
no symbol for ATEXIT_MAX
ATEXIT_MAX = 2147483647
CHARCLASS_NAME_MAX defined to be 2048
CHARCLASS_NAME_MAX = 2048
no symbol for CHILD_MAX
CHILD_MAX = 37937
no symbol for CLOCKTICKSPERSECOND /*clock ticks/second*/
CLOCKTICKSPERSECOND /*clock ticks/second*/ = 100
COLL_WEIGHTS_MAX defined to be 255
COLL_WEIGHTS_MAX = 255
DELAYTIMER_MAX defined to be 2147483647
DELAYTIMER_MAX = 2147483647
HOST_NAME_MAX defined to be 64
HOST_NAME_MAX = 64
IOV_MAX defined to be 1024
IOV_MAX = 1024
LINE_MAX defined to be 2048
LINE_MAX = 2048
LOGIN_NAME_MAX defined to be 256
LOGIN_NAME_MAX = 256
NGROUPS_MAX defined to be 65536
NGROUPS_MAX = 65536
no symbol for OPEN_MAX
OPEN_MAX = 4096
no symbol for PAGESIZE
PAGESIZE = 4096
no symbol for PAGE_SIZE
PAGE_SIZE = 4096
RE_DUP_MAX defined to be 32767
RE_DUP_MAX = 32767
RTSIG_MAX defined to be 32
RTSIG_MAX = 32
no symbol for SEM_NSEMS_MAX
SEM_NSEMS_MAX = (no limit)
SEM_VALUE_MAX defined to be 2147483647
SEM_VALUE_MAX = 2147483647
no symbol for SIGQUEUE_MAX
SIGQUEUE_MAX = 37937
no symbol for STREAM_MAX
STREAM_MAX = 16
no symbol for SYMLOOP_MAX
SYMLOOP_MAX = (no limit)
no symbol for TIMER_MAX
TIMER_MAX = (no limit)
TTY_NAME_MAX defined to be 32
TTY_NAME_MAX = 32
no symbol for TZNAME_MAX
TZNAME_MAX = (no limit)
no symbol for FILESIZEBITS
FILESIZEBITS = 64
no symbol for LINK_MAX
LINK_MAX = 65000
MAX_CANON defined to be 255
MAX_CANON = 255
MAX_INPUT defined to be 255
MAX_INPUT = 255
NAME_MAX defined to be 255
NAME_MAX = 255
PATH_MAX defined to be 4096
PATH_MAX = 4096
PIPE_BUF defined to be 4096
PIPE_BUF = 4096
no symbol for SYMLINK_MAX
SYMLINK_MAX = (no limit)
no symbol for _POSIX_TIMESTAMP_RESOLUTION
no symbol for _PC_TIMESTAMP_RESOLUTION
```
- SourceCode分支`standards/`目录源码中实现了打印所有支持、不支持的限制的逻辑。上述结果是执行`./option .`和`./conf .`的结果，需要先`make`生成这两个C文件并编译。

### 2.3.5 不确定的运行时限制

路径名：
- 为路径名动态分配内存，应该取`PATH_MAX`变量值。
- 为了保证可移植性，在定义该常量和未定义该常量需要使用`sysconf`的系统上都能运行可以使用如下逻辑：
```c
#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif
```
- 然后在使用时判断`pathmax`是否为0，如果是再通过`pathconf("/", _PC_PATH_MAX)`获取一次，并且如果获取到的值是不确定的，那么就是用猜测的值。
- 以上逻辑实现在`lib/pathalloc.c`，可以作为参考。
- 如果不需要保证可移植性，那么不需要这么冗余的逻辑，可移植性某种程度上来说也是枷锁。

最大打开文件数：
- 限制：`POPEN_MAX`。
- 如果没有定义则使用`sysconf`。
- 对于某些守护进程需要关闭所有打开文件，可能就会获取到该值，做一个循环，对每一个文件描述符`close`。
- 但`sysconf`获取到的值可能是无限的，那么此时会将`LONG_MAX`作为`POPEN_MAX`报告，做循环效率会很差。
- 支持XSI扩展的系统上提供了`getrlimit(2)`函数获取限制，声明在`<sys/resource.h>`中。
- 可通过`ulimit`命令查看和设置某个限制，通过`ulimit --help`查看帮助，不在`man 1`中。

## 2.4 选项


关于一个UNIX系统是否支持一个可选功能：
- 可以通过选项获取这个信息，每个功能都对应一个符号常量。就是前面说的40个可选部分。
- 类似于对限制的处理：
- 编译时选项定义在`<unistd.h>`。
- 否则通过`sysconf pathconf fpathconf`传入选项的符号常量对应的`_SC _PC`前缀的名称来获取。
- 如果选项的符号常量是`_POSIX`前缀，那么将`_POSIX`替换为`_SC _PC`。如果是`_XOPEN`前缀，那么在前面添加`_SC _PC`。

关于选项的值：
- 如果符号常量没有定义，或者定义为-1，那么该平台编译时不支持该选项。
- 如果符号常量定义值大于0，那么平台支持该选项。
- 如果定义值为0，那么需要使用`sysconf pathconf fpathconf`获取。

Linux中支持：
- 几乎所有可选项都是支持的。
- 暂时不需要考虑到其他UNIX系统的可移植性。遇到再说，可能基本很长时间内都不会遇到。

## 2.5 功能测试宏

在源文件中定义宏以排除实现定义常量，而仅使用POSIX定义常量：
- `_POSIX_C_SOURCE _XOPEN_SOURCE`分别表示POSIX.1和XSI的版本，前者是四位十进制年和2位十进制月构成的6位十进制数，后者使用600(SUSv3)/700(SUSv4)这样的值。
- `_XOPEN_SOURCE`定义为700，除了表示XSI选项可用外，就POSIX.1功能而言，与将`_POSIX_C_SOURCE`定义为`200809L`作用相同。
- 细节请查看手册`feature_test_macros(7)`。

使用方法：
- 编译选项：`cc -D_POSIX_C_SOURCE=200809L file.c`。
- 源文件第一行：
```c
#define _POSIX_C_SOURCE 200809L
```

## 2.6 基本数据类型

`<sys/types.h>`中定义了实现相关的数据类型，称之为**基本系统数据类型**（primitive system data type）：
- 以后会常和这些类型打交道。都是用C的`typedef`定义，绝大多数以`_t`结尾。
- 常用的：

|类型|说明|
|:-|:-|
|`clock_t     `|时钟滴答计数器（clock tick），进程时间
|`comp_t      `|压缩的时钟滴答
|`dev_t       `|设备号（主和次）
|`fd_set      `|文件描述符集
|`fpos_t      `|文件位置
|`gid_t       `|数值用户组ID
|`ino_t       `|i节点编号
|`mode_t      `|文件类型，文件创建模式
|`nlink_t     `|目录项（文件、目录）连接计数
|`off_t       `|文件长度和偏移量（`lseek`），带符号
|`pid_t       `|进程ID和进程组ID
|`pthread_t   `|线程ID
|`ptrdiff_t   `|指针相减结果，带符号
|`rlim_t      `|资源限制
|`sig_atomic_t`|能原子性访问的数据
|`sigset_t    `|信号集
|`size_t      `|对象长度，无符号
|`ssize_t     `|字节计数的长度，带符号（`read write`）
|`time_t      `|日历时间的秒计数器
|`uid_t       `|数值用户ID
|`wchar_t     `|宽字符
- 使用这些类型以屏蔽因系统不同而变化的实现细节。

## 2.7 标准之间的冲突

不同的标准之间配合很好，SUS和POSIX.1基本是同一个东西。主要关注ISO C和POSIX.1存在的差别。
- 如果存在冲突，POSIX.1服从ISO C标准。
- ISO C定义了`clock`函数返回进程CPU时间，`clock_t`类型，但没有规定单位，除以`<time.h>`中定义的`CLOCKS_PER_SEC`以变换为秒为单位。
- POSIX.1定义了`times`函数调用者及其所有终止子进程的CPU时间以及时钟时间。都是`clock_t`类型，需要通过`sysconf`获取每秒滴答数用于表示函数返回值。
- 注意使用了同一类型，但不同单位，使用时需要注意，不要搞混了。

另外的冲突：
- ISO C标准没有POSIX.1那么严格，较少考虑宿主操作系统环境。
- 为了兼容性，都会实现ISO C，但某些功能可能也会在系统调用中提供类似函数。比如UNIX中信号处理更推荐使用POSIX.1的`sigaction`函数而非ISO C的`signal`(不同UNIX实现可能不同)。

## 2.8 总结

- UNIX环境存在标准，同时存在可选部分和可能随实现改变的参数。
- 区分ISO C和POSIX.1、SUS标准。
- 标准定义了各种限制和常量，但并不完美。