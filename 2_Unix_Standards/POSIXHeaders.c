// 1.ISO C standard headers ...
// 2.mandatory part
#include <aio.h>        // asynchronous IO functions
#include <cpio.h>       // cpio archive (cpio is like tar) values
#include <dirent.h>     // directory operations, opendir/closedir/readdir etc
#include <dlfcn.h>      // dynaimc linking functions, processing shared objects
#include <fcntl.h>      // file contorl operations, open/creat etc
#include <fnmatch.h>    // file name matching functions, just a fnmatch function
#include <glob.h>       // pattern matching and generating of path names, glob function
#include <grp.h>        // user group functions
#include <iconv.h>      // codeset transfromations (charset), iconv/iconv_open/iconv_close
#include <langinfo.h>   // language info constants
#include <monetary.h>   // monetary types and functions
#include <netdb.h>      // network data base operations
#include <nl_types.h>   // message catalogs
#include <poll.h>       // poll function
#include <pthread.h>    // threads
#include <pwd.h>        // passwd file
#include <regex.h>      // regex
#include <sched.h>      // process scheduling 
#include <semaphore.h>  // semaphore
#include <strings.h>    // string operations
#include <tar.h>        // tar archive values
#include <termios.h>    // IO in terminal
#include <unistd.h>     // Symbolic Constants
#include <wordexp.h>    // wordexp function

#include <arpa/inet.h>  // internet definitions
#include <net/if.h>     // socket local interface
#include <netinet/in.h> // internet IP family
#include <netinet/tcp.h>// TCP protocal

#include <sys/mman.h>   // memory management functions
#include <sys/select.h> // select functions
#include <sys/socket.h> // socket functions, send/listen/recv etc.
#include <sys/stat.h>   // file status, mkdir/chmod etc.
#include <sys/statvfs.h>// file system infomations
#include <sys/times.h>  // times function, type clock_t, process time
#include <sys/types.h>  // basic system types
#include <sys/un.h>     // UNIX domain sockets definition
#include <sys/utsname.h>// system name
#include <sys/wait.h>   // process control, wait/waitpid

// 3.XSI(X/Open System Interface) optional part
#include <fmtmsg.h>     // format output message, fmtmsg function
#include <ftw.h>        // file tree wandering, ftw function
#include <libgen.h>     // path name management, dirname functions
// #include <ndbm.h>       // database operations, Linux do not support
#include <search.h>     // search table
#include <syslog.h>     // logging of system error, openlog/closelog/syslog function
#include <utmpx.h>      // user account database
#include <sys/ipc.h>    // inter-process communication
#include <sys/msg.h>    // XSI message queen
#include <sys/resource.h>// resource operations
#include <sys/sem.h>    // XSI semaphore
#include <sys/shm.h>    // shared memory
#include <sys/time.h>   // time
#include <sys/uio.h>    // vector I/O

// 4.Standard optional part
#include <mqueue.h>     // message queen
#include <spawn.h>      // real-time spawn interface

int main()
{
    return 0;
}