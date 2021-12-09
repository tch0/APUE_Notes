## 0. 准备

UNIX发行版：
- FreeBSD
- Linux (Unix-like)
- Apple Mac OS X (Darwin)
- Solaris

选择环境：
- WSL2 Ubuntu 20.04 LTS，配合VSCode。
- 实体机或虚拟机亦可，其他发行版亦可。

源码：
- 访问[http://www.apuebook.com/code3e.html](http://www.apuebook.com/code3e.html)下载第三版APUE的源码。
- 所有代码都是ANSI C标准编写，可以运行于所有Unix系统上，一般来说最常见的还是Linux和MacOS。
- 代码结构是一章一个目录，基本上每个例子一个小文件，会共用一个公共的头文件`apue.h`。
- 编译过程中会遇到错误，使用`-i`选项忽略错误继续编译：
```bash
make -i
```
- 本地编译过程中会遇到两个文件编译错误：`./filedir/devrdev.c`和`./stdio/buf.c`，无伤大雅，都是单独的例子，不影响其他代码，等用到了再解决就行。
- 然后需要运行书中给了源码的例子时直接去对应目录下找到程序运行或者找到源码调试就行啦。
- 为了方便，代码上传到了[SourceCode分支](https://github.com/tch0/APUE_Notes/tree/SourceCode)，版权归原作者所有，未做任何修改。

Unix程序员手册:
- UNIX Programmer's Manual
- 操作系统内置，使用`man`命令查看，划分为了多个部分：
```
       man  is  the system's manual pager.  Each page argument given to man is normally the name of a program, utility or function.  The manual page associated with each of these arguments is then found and displayed.  A section, if provided, will direct man to look only in that section
       of the manual.  The default action is to search in all of the available sections following a pre-defined order (see DEFAULTS), and to show only the first page found, even if page exists in several sections.

       The table below shows the section numbers of the manual followed by the types of pages they contain.

       1   Executable programs or shell commands
       2   System calls (functions provided by the kernel)
       3   Library calls (functions within program libraries)
       4   Special files (usually found in /dev)
       5   File formats and conventions, e.g. /etc/passwd
       6   Games
       7   Miscellaneous (including macro packages and conventions), e.g. man(7), groff(7)
       8   System administration commands (usually only for root)
       9   Kernel routines [Non standard]
```
- 可以查看命令、系统调用、库函数等。例子`man ls`，`man 2 open`。