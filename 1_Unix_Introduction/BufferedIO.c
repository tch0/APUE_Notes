#include <stdio.h>
#define MAXLINE 256

// buffered IO : standard IO
// input : fgetc fgets getc getchar ungetc
// output: fputc fputs putc putchar puts
// printf family: printf, fprintf, sprintf ...
// scanf family: scanf, ...

int main()
{
    int n = 0;
    char buf[MAXLINE] = {};
    while (n = fgets(buf, MAXLINE, stdin) != NULL) {
        fputs(buf, stdout);
    }
    return 0;
}