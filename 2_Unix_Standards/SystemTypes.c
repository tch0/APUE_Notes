#include <stdio.h>
#include <sys/select.h>
#include <sys/acct.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <bits/types/sig_atomic_t.h>

int main()
{
    clock_t         t;      // clock-tik counter
    comp_t          comp;   // compressed tik-tok
    dev_t           d;      // device number ()
    fd_set          fs;     // file descriptor set
    fpos_t          fp;     // file position
    gid_t           g;      // group ID
    ino_t           i;      // i-node number
    mode_t          m;      // file type
    nlink_t         n;      // link count of directory items
    off_t           o;      // length and offset of file, lseek
    pid_t           p;      // process ID and process group ID, signed
    pthread_t       pt;     // thread ID
    ptrdiff_t       ptrd;   // result of subtraction of pointer
    rlim_t          rt;     // resouece limit
    sig_atomic_t    sa;     // atomic visiting data type
    sigset_t        st;     // signal set
    size_t          sz;     // size of obejct, unsigned
    ssize_t         ssz;    // count of byte, signed, read/write
    time_t          tt;     // second count of calendar time
    uid_t           ut;     // user ID
    wchar_t         wc;     // wide character

    return 0;
}