#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signalInterruptKeyHandler(int signum)
{
    printf("Interrupt Key accepted (Ctrl+C pressed)\n");
}

int main()
{
    if (signal(SIGINT, signalInterruptKeyHandler) == SIG_ERR)
    {
        printf("signal error\n");
        exit(-1);
    }
    char buf[512] = {0};
    while (fgets(buf, 512, stdin) != NULL)
    {
        fputs(buf, stdout);
    }
    return 0;
}