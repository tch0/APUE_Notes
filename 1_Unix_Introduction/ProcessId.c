#include <stdio.h>
#include <unistd.h>

// getpid 
// fork exec waitpid

int main()
{
    printf("pid of current process: %ld\n", (long)getpid());
    return 0;
}