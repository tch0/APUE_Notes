#include <stdio.h>
#include <unistd.h>

// try different user
// sudo ./UserIdGroupId will get uid and gid of root
int main()
{
    printf("uid: %d, gid: %d\n", getuid(), getgid());
    return 0;
}