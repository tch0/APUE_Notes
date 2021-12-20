#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    {
        // ./SeekFile // stdin
        // cat ./SeekFile.c | ./SeekFile // PIPE
        printf("can not seek: %s\n", strerror(errno));
    }
    else 
    {
        // ./SeekFile < ./SeekFile.c
        printf("can seek\n");
    }
    return 0;
}