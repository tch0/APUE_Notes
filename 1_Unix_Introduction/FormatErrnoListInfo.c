#include <stdio.h>
#include <string.h>
#define BUF_SIZE 512

// format the output of errno -l command
// usage: errno -l | ./FormatErrnoListInfo

int printCharacters(char c, int num)
{
    int i = 0;
    for (i = 0; i < num; i ++)
    {
        putchar(c);
    }
}

// return count of spaces
int getAllSpaceIndexes(char* str, int* indexes)
{
    int i = 0;
    int len = strlen(str);
    int count = 0;
    for (i = 0; i < len; i ++)
    {
        if (str[i] == ' ')
        {
            count ++;
            *indexes++ = i;
        }
    }
    return count;
}

int main()
{
    char buf[BUF_SIZE] = {0};
    int maxMacroLen = 15;
    int maxValLen = 3;

    while (fgets(buf, BUF_SIZE, stdin) != NULL)
    {
        int i = 0;
        int macroLen = 0;
        int valueLen = 0;
        int bufLen = strlen(buf);
        if (buf[bufLen-1] == '\n')
        {
            buf[bufLen-1] = 0;
        }
        int spaceIndexes[64] = {0};
        if (getAllSpaceIndexes(buf, spaceIndexes) >= 2)
        {
            buf[spaceIndexes[0]] = buf[spaceIndexes[1]] = 0; // split
            macroLen = spaceIndexes[0];
            valueLen = spaceIndexes[1] - spaceIndexes[0] - 1;
            printf("%s ", buf);
            if (macroLen < maxMacroLen)
            {
                printCharacters(' ', maxMacroLen - macroLen);
            }
            printf("%s ", buf + macroLen + 1);
            if (valueLen < maxValLen)
            {
                printCharacters(' ', maxValLen - valueLen);
            }
            printf("%s\n", buf + spaceIndexes[1] + 1);
        }
    }
    return 0;
}