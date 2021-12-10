#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> // strerror
#include <stdio.h> // perror

// lvalue errno in <errno.h>

int main()
{
    // open a non-existing file
    int ret = open("non-existing.whatever", O_RDWR);
    if (ret == -1)
    {
        printf("errno vlaue : %d\n", errno);
        perror("error");
        printf("error: %s\n", strerror(errno));
    }

    // print all possile errno info
    int errnoVal = 0;
    for (errnoVal = 0; errnoVal <= 140; errnoVal++)
    {
        printf("errno: %d, string: %s\n", errnoVal, strerror(errnoVal));
    }
    // try errno -l command
    return 0;
}