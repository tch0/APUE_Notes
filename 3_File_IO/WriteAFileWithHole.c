#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

char buf1[] = "abcdefg";
char buf2[] = "ABCDEFG";
int main()
{
    int fd;
    if ((fd = creat("file.hole", (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))) == -1)
    {
        printf("create file error: %s\n", strerror(errno));
        exit(-1);
    }
    if (write(fd, buf1, strlen(buf1)) != strlen(buf1))
    {
        printf("buf1 write error %s\n", strerror(errno));
        exit(-1);
    }
    if (lseek(fd, 32768, SEEK_SET) == -1)
    {
        printf("lseek error %s\n", strerror(errno));
        exit(-1);
    }
    if (write(fd, buf2, strlen(buf2)) != strlen(buf2))
    {
        printf("buf2 write error %s\n", strerror(errno));
        exit(-1);
    }
    close(fd);
    return 0;
}
