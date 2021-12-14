#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("clock tik per second: %ld\n", sysconf(_SC_CLK_TCK));
    return 0;
}