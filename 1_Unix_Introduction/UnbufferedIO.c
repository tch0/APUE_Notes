#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAXLINE 256

// unbuffered IO
// use file descriptor : 0 1 2 for stdin stdout stderr
// open read write lseek close

int main()
{
    int fd = open("IOTest.txt", O_RDWR); // read and write
    char buf[MAXLINE] = {};
    ssize_t num = 0;
    const char* info = "The contents of IOTest.txt:\n";
    write(STDOUT_FILENO, info, strlen(info) + 1);
    while ((num = read(fd, buf, MAXLINE)) > 0) // 0 EOF, -1 error
    {
        write(STDOUT_FILENO, buf, num);
    }

    info = "\n\nInput contents you want to write to IOTest.txt:\n";
    write(STDOUT_FILENO, info, strlen(info) + 1);
    lseek(fd, 0, SEEK_SET);
    while ((num = read(STDIN_FILENO, buf, MAXLINE)) > 0)
    {
        write(fd, buf, num);
    }
    close(fd);
    return 0;
}