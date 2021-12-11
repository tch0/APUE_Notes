#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXLINE 256

// chdir function: change the current working directory(cwd) of current program
// getcwd function: get current working directory

// input "showcwd": print current dir
// input "ls": show all file in current dir
// input a directory: change to this dir
int main()
{
    char buf[MAXLINE] = {};
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) // EOF(Ctrl+D) will return NULL
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0;
        }
        if (strcmp(buf, "showcwd") == 0)
        {
            if (getcwd(buf, MAXLINE) != NULL)
            {
                printf("cwd: %s\n", buf);
            }
            else
            {
                printf("getcwd() returns NULL\n");
            }
        }
        else if (strcmp(buf, "ls") == 0)
        {
            pid_t pid;
            if ((pid = fork()) < 0) {
                printf("fork failed\n");
                return -1;
            }
            else if (pid == 0) // child process
            {
                execlp("ls", "", NULL);
                exit(0);
            }
            // parent process
            int status = 0;
            if (waitpid(pid, &status, 0) < 0)
            {
                printf("waitpid error\n");
                return -1;
            }
        }
        else {
            if (chdir(buf) == 0)
            {
                printf("change dir success\n");
            }
            else
            {
                printf("change dir failed\n");
            }
        }
        printf("%% ");
    }
    return 0;
}