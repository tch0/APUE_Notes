<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [3. 文件I/O](#3-%E6%96%87%E4%BB%B6io)
  - [3.1 文件描述符](#31-%E6%96%87%E4%BB%B6%E6%8F%8F%E8%BF%B0%E7%AC%A6)
  - [3.2 open & openat & creat](#32-open--openat--creat)
  - [3.3 close](#33-close)
  - [3.4 lseek](#34-lseek)
  - [3.5 read](#35-read)
  - [3.6 write](#36-write)
  - [3.6 IO效率](#36-io%E6%95%88%E7%8E%87)
  - [3.7 文件共享](#37-%E6%96%87%E4%BB%B6%E5%85%B1%E4%BA%AB)
  - [3.8 原子操作](#38-%E5%8E%9F%E5%AD%90%E6%93%8D%E4%BD%9C)
  - [3.9 dup & dup2](#39-dup--dup2)
  - [3.10 sync fsync & fdatasync](#310-sync-fsync--fdatasync)
  - [3.11 fcntl](#311-fcntl)
  - [3.12 /dev/fd](#312-devfd)
  - [3.13 ioctl](#313-ioctl)
  - [3.14 总结](#314-%E6%80%BB%E7%BB%93)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 3. 文件I/O

总览：
- 函数： `open` `read` `write` `lseek` `close`
- 不带缓冲的I/O
- 原子操作，多个进程间共享文件，相关函数 `dup` `fcntl` `sync` `fsync` `ioctl`


## 3.1 文件描述符

文件描述符：
- 非负整数，操作系统通过文件描述符管理进程打开的文件，进程内所有打开文件都通过文件描述符引用。文件描述符值只在当前进程内有意义，进程内唯一无全局含义（比如0、1、2标准输入输出），每个进程都有自己的文件描述符表。
- `open creat`返回文件描述符，`read write lssek close`来使用。
- `<unistd.h>`中定义了三个标准化的文件描述符：
```c
/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```
- 文件描述符的变化范围是`0 ~ OPEN_MAX - 1`。对于现今的UNIX操作系统而言，文件描述符变化范围几乎是无限的。

## 3.2 open & openat & creat

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```
- 成功返回文件描述符，失败-1。
- C语言没有函数重载，真正的原型是最后一个是可变参数，在一个原型中定义的，不过`open`有限制仅接受2个或者3个参数，不接受更多。写作上面这样的形式仅为了说明。
- `openat`当传入相对路径时，则是相对于传入的描述符指定的路径，其余和`open`完全相同。因为一个进程中的多个线程共享进程的当前工作目录，所以此时不同线程中可能会需要使用到这一点。另外是为了避免TOCTTOU（time-of-check-to-time-of-use）错误。
- 无论打开还是创建，重点都在`flags`参数上。某些`flags`标记会需要使用额外的`mode`参数，主要就是创建。
- `flags`参数详解，更多查看`open(1)`：

|值|含义|
|:-|:-|
|`O_RDONLY   `|只读打开，值一般是0
|`O_WRONLY   `|只写打开，值一般是1
|`O_RDWR     `|读写打开，值一般是2
|`O_EXEC     `|只执行打开（Linux上没有）
|`O_SEARCH   `|只搜索打开目录（基本所有UNIX都没有实现）
|`O_APPEND   `|追加写
|`O_CLOSEXEC `|设置文件描述符标志为`FD_CLOEXEC`
|`O_CREAT    `|文件不存在则创建，需同时指定`mode`
|`O_DIRECTORY`|仅目录
|`O_EXCL     `|同时指定`O_CREAT`时打开已有文件或创建新文件
|`O_NOCTTY   `|引用终端设备相关
|`O_NOFOLLOW `|不允许符号链接
|`O_NONBLOCK `|非阻塞模式
|`O_SYNC     `|等待写完成再读（数据和属性）
|`O_TRUNC    `|写或读写打开时将长度截断为0
|`O_TTY_INIT `|打开终端设备则进行初始化
|`O_DSYNC    `|等待写完成再读（仅数据），实现可选
|`O_RSYNC    `|同步读和写（Linux不支持，等同于O_SYNC），实现可选

- 前5个选项互斥，后续的可选。并非所有选项Linux都有，看手册。
- `creat(path, mode)`等同于`open(path, O_RDWR | O_CREATE | O_TRUNC, mode)`。仅创建时会用到`mode`。

文件路径截断：
- `_POSIX_NO_TRUNC`常量决定要截断过长的文件和路径名还是返回一个错误（`errno`）。本地Linux为1，也就是返回错误。
- 路径长度和文件名长度使用`PATH_MAX NAME_MAX`。使用`pathconf`获取，本地64位Linux前者255，后者4096。一般都不会超。

## 3.3 close

```c
#include <unistd.h>
int close(int fd);
```
- 成功返回0，失败-1。
- 关闭文件。同时会释放所有加在改文件上的记录锁。
- 进程终止时，内核自动为其关闭它打开的所有文件。可以不显示关闭。


## 3.4 lseek

每个打开文件都有一个当前文件偏移量，`off_t`（本地实现是`long int`64位整数），通常是一个非负整数，从文件开始出计算的字节计数。如果打开时指定`O_APPEND`则在末尾，没有的话通常是0。
```c
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```
- 成功返回新的文件偏移量，失败-1。
- 显式为文件设置偏移量。
- `whence`可以设置为`SEEK_SET SEEK_CUR SEEK_END`（值通常是0、1、2），确定`offset`含义，绝对偏移量、相对当前位置偏移量、相对文件末尾偏移量。
- 得到当前偏移量：`curpos = lseek(fd, 0, SEEK_CUR)`。也可以用来确定当前涉及文件是否可以设置偏移量，比如管道、FIFO、网络套接字则返回-1，并设置`errno`为`ESPIPE`。
- 文件只支持非负偏移量，某些设备可能支持负偏移量。需要注意，判断是不要使用`<0`而是`==-1`。
- `lseek`仅修改内核中打开文件的偏移量，不做任何IO操作。该偏移量被用于下一个读或写操作。
- 偏移量可以大于文件长度，下一次写将加长文件，没有被写过的字节被设置为0。其中的空洞可能并不占用磁盘空间（中间内容也许并不占用磁盘块，`ls -s`），与文件系统实现有关。
- 读写文件`read write`同时会移动偏移量。

## 3.5 read

```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```
- 返回读取字节数，0表示文件尾，-1失败。
- 读取最多`count`字节，因为文件长度小于`count`、终端设备一次一行、网络的缓冲、读的过程中信号造成中断等原因都可能导致实际返回字节数小于`count`。
- 文件偏移量将实际增加读取成功的字节数。
- `ssize_t`是带符号整数（本地实现LP64的64位`long int`）。
- `size_t`是无符号整数。
- 历史上`buf`是`char *`。

## 3.6 write
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```
- 成功返回写入长度，错误-1。
- 返回写入长度，通常与`count`相同，否则表示出错。常见原因是磁盘写满、超过进程的文件长度限制。
- 普通文件在当前偏移量处开始写，`O_APPEND`打开的话则每次写之前将偏移量移到当前文件末尾。

## 3.6 IO效率

`read write`的缓冲区大小会影响IO的效率，1字节很明显太小了，也不宜过大，经过测试，到达一定程度之后，增大缓冲区对IO效率的影响很微小甚至有负影响。相对来说4096是个比较合适的值。

## 3.7 文件共享

有关的三个表：
- 文件描述符表：位于进程表中的进程表项中（概念上，实现中不一定）。每个进程一个，包含了进程的所有打开文件，文件描述符表项内容包括文件描述符标志和一个文件表指针。
- 文件表：全局的，内核为所有打开文件维护一张文件表，包括信息：文件状态标志（读写、追加、同步等）、打开文件偏移量、该文件v节点指针。
- v节点表：每个打开文件或设备会有一个v节点结构（v节点表项），包括文件类型和对此文件进行的各种操作函数的指针。对于大多数文件还包含一个i节点指针。i节点则保存了文件的更多信息：所有者、文件长度、指向磁盘数据块的指针等。

实现：
- 上述表具体实现可以不同，数组链表都行。重点在于理解相互关系，细节可能因实现而异。
- v节点是文件系统无关的，i节点是文件系统相关的。
- Linux未实现v节点，而是使用一个文件系统无关的i节点替代。其中保存的依然是一个文件系统相关的i节点。

文件共享：
- 两个独立进程各自打开同一个文件时：
- 各自进程的文件描述符表中都有一个文件描述符表项，每个进程用自己进程内的描述符引用该文件。
- 两个进程内该文件的文件描述符表项中文件表指针指向不同文件表项。
- 两个不同文件表项中的v节点指针指向同一个v节点。
- 共享的内容：v节点，包括v节点中的文件类型、文件操作，i节点中的文件所有者、文件长度、磁盘块指针等信息。
- 不共享的内容：不同进程内的文件描述符和文件描述符标志、文件表项中的文件状态（读写追加等）和偏移量。

说明：
- `write`后，文件表项中当前文件偏移量增加写入的字节数，如果超过了文件长度，那么将设置i节点文件长度为当前偏移量。
- `O_APPEND`打开文件，被设置到文件表项的文件状态标志中，每次`write`前，都会将文件表项中偏移设置为i节点表项中文件长度。
- `lseek`定位到尾端时（`SEEK_END`），文件表项中偏移量设置为i节点表项中文件长度。
- `lseek`仅修改文件表项中当前文件偏移量，不进行IO操作。

注意：
- 可能存在同一进程中多个文件描述符指向同一文件表项。（`dup`函数，以及`fork`产生的子进程(不懂就问，子进程算也算同一进程吗？)）
- 文件描述符表中的文件描述符标志（file descriptor flags）和文件表中的文件状态标志（file status flags）作用范围不同，前者作用于一个进程的一个描述符，后者作用于所有指向该文件表项的任何进程中的所有描述符。这两个标志的取值和含义后续介绍。
- 多个进程同时读取一个文件都能够工作，多个进程同时写一个文件则有可能出现预想不到的结果。为了避免这种情况，需要原子操作。

待了解的问题：
- 实现细节：相关结构、类型、函数。
- 文件描述符表项中文件描述符标志和文件表项中的文件状态标志异同细节。
- v节点和i节点中各种信息细节，不同文件系统，不同文件设备类型异同。

## 3.8 原子操作

`O_APPEND`原子性追加：
- 在有`O_APPEND`选项之前，追加内容到文件末尾可能需要这样：
```c
if (lseek(fd, 0, SEEK_END) < 0)
    exit(-1);
if (write(fd, buf, 100) != 100)
    exit(-1);
```
- 如果两个进程A和B写同一个日志文件，A执行`lseek`后，内核切到了进程B然后追加到了末尾。然后切回进程A，此时`write`就会覆盖进程A写下的内容。
- 定位到文件尾端和写操作是两个分开的函数调用。就会有这个问题，解决方法是将其作为一个原子操作。
- UNIX系统提供了原子操作，`O_APPEND`打开，则定位到文件尾和写会在同一个系统`write`中完成。不必每次都`lseek`。

`pread pwrite`：
- SUS规范的XSI扩展中允许原子性地定位并执行IO操作。函数是`pread pwrite`：
```c
#include <unistd.h>
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
```
- 返回值类似，成功返回读取/写入的字节数，读取时到达文件尾返回0，错误返回-1。
- 相当于调用`lseek`后调用`read/write`，原子执行，不会中断定位和读写操作。
- 不更新当前文件偏移量。
- 用于多线程或者多进程读写同一个文件场景。

创建文件：
- `open`函数中`O_CREAT O_EXCL`选项指定时，检查文件是否存在和创建文件是原子操作。
- 如果不是原子操作，那么可能需要调用`open`之后再调用`creat`。就可能判断了不存在，内核切换到其他进程创建了改文件，然后再回到该进程创建，这时另一个进程写入的信息会丢失。

在进行多线程程序的编写中，应该时刻注意系统调用的原子性，系统调用的设计上会考虑这些问题，使用时需要注意。手册中都会说明。

## 3.9 dup & dup2

```c
#include <unistd.h>
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```
- 复制一个文件描述符，成功返回新描述符，失败返回-1。
- `dup2`指定文件，如果`oldfd`和`newfd`相等，不做任何事情，不等且`newfd`已经打开，则相当于先`close(newfd)`再复制，原子操作。
- 新的和旧的文件文件描述符执行同一个文件表项，共享文件状态标志和偏移量。

## 3.10 sync fsync & fdatasync

UNIX系统内核中实现有缓冲区高速缓存（kernel buffer cache）或页高速缓存（page cache）用来缓存文件。通过`write`写文件时通常先写到页缓存，然后延迟写（delay write）回磁盘以提高性能（由周期性的系统守护进程完成）。

页缓存中被写入的页会标记为脏，回写进程会回写这些页，并清楚脏标记。细节尚不清楚。

提供了三个函数来显式将文件写回磁盘：
```c
#include <unistd.h>
void sync(void);
int fsync(int fd);
int fdatasync(int fd);
```
- `sync`写回所有文件，一般将修改过的块缓冲排入写队列，就返回，不等待磁盘I/O。同时有命令`sync(1)`。
- `fsync fdatasync`写回特定文件，等待磁盘I/O。
- `fdatasync`只影响数据部分，`fsync`还会更新文件属性。

## 3.11 fcntl

```c
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ... /* arg */ );
```
- 改变打开文件属性。
- 命令`cmd`取值：
    - 复制已有文件描述符，`F_DUPFD F_DUPFD_CLOEXEC`就像`dup`。
    - 获取和设置文件描述符标志：`F_GETFD F_SETFD`。
    - 获取和设置文件状态标志：`F_GETFL F_SETFL`。
    - 获取和设置异步IO所有权：`F_GETOWN F_SETOWN`。后续章节说明。
    - 获取和设置记录锁：`F_GETLK F_SETLK F_SETLKW`。后续章节说明。

文件描述符标志：
- 当前只有一个`FD_CLOEXEC`，表示在执行时（`exec`）关闭（`close`）。
- 保存在文件描述符表项中。
- 每个文件描述符一个。
- `dup2`会清除新描述符的`FD_CLOEXEC`标志，`F_DUPFD_CLOEXEC`也会。

文件状态标志：
- 保存在文件表项中，每个打开文件一个。
- 就是`open`的打开标志，可以通过`F_SETFL`设置。
- 前5个（Linux中只支持前3个），值为0到5（Linux中0、1、2）是连续的，而不是单独占用二进制位。需要用一个掩码（`O_ACCMODE`，linux中值为3）进行按位与后依次比较。其他的（`O_APPEND O_NONBLOCK O_SYNC ...`）可直接按位与获取。
- 修改标志一定要先获取再设置：添加`flag |= O_XXXX`，移除`flag &= ~O_XXXX`。
- 有`O_SYNC O_DSYNC`标记的话，`write`会进行磁盘I/O，功能类似于`fsync fdatasync`。通常来说这会导致`write`用时增加。

## 3.12 /dev/fd

这个目录中有0、1、2等一系列文件，可以使用`/dev/fd/0 /def/fd/1 /def/fd/2`作为路径打开，作为标准输入、输出、错误输出。
- 这样可以将标准IO和文件一样按照文件来处理。调用`open`打开得到描述符来工作。
- 主要用在shell程序的命令行中。
- 比如`cat -`中可以使用`-`来表示使用标准输入。就可以等价于`cat /dev/fd/0`。

## 3.13 ioctl

```c
#include <sys/ioctl.h>
int ioctl(int fd, unsigned long request, ...);
```
- 不能用其他函数调用的I/O操作，比如对特定设备比如磁带或者终端的操作。

## 3.14 总结

- 在这些函数的`man`手册中都能找到更详细的说明。比如标志含义、返回值、什么时候应该用系统调用提供的原子操作等。
- IO结构直观理解主要有三层：
    - 用户缓冲（user space）。
    - 内核缓冲区高速缓存（kernel buffer cache）或页高速缓存（page cache）。
    - 物理硬件，磁盘。
- 用户和内核间用系统调用`write read`实现，由CPU拷贝，内核缓存和硬件之间由DMA拷贝，用户层可使用`fsync O_SYNC`等手段一定程度控制。
- 务必理解文件描述符表项、文件表项、v节点i节点关系。
- 区分文件描述符标志（file descriptor flags，仅一个`FD_CLOEXEC`）和文件状态标志（file status flags，读写追加同步等）。