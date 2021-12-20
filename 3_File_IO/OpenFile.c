#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


// open openat (just like open but based on the path that input fd stand on)
// int open (const char *__path, int __oflag, ...)
// int openat (int __fd, const char *__path, int __oflag, ...)
int main()
{
    printf("OPEN_MAX = %ld\n", sysconf(_SC_OPEN_MAX));
    printf("NAME_MAX = %ld\n", pathconf(".", _PC_NAME_MAX));
    printf("PATH_MAX = %ld\n", pathconf("/", _PC_PATH_MAX));
    printf("_POSIX_NO_TRUNC = %d\n", _POSIX_NO_TRUNC);
    printf("/ path too long truncate(0) or error(1) : %ld\n", pathconf("/", _PC_NO_TRUNC));
    int fd = open("/", O_RDWR);
    printf("ESPIPE: %s\n", strerror(ESPIPE));
    printf("SEEK_SET = %d\n", SEEK_SET);
    printf("SEEK_CUR = %d\n", SEEK_CUR);
    printf("SEEK_END = %d\n", SEEK_END);
    close(fd);
    return 0;
}