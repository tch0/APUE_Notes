#include <stdio.h>
#include <limits.h>

#define PRINT_LIMIT(macro, descriptor) printf(#macro" is : "descriptor"\n", macro);

// x64 linux
int main()
{
    PRINT_LIMIT(CHAR_BIT, "%d"); // 8
    PRINT_LIMIT(CHAR_MAX, "%d"); // 127, char is signed char
    PRINT_LIMIT(CHAR_MIN, "%d");
    PRINT_LIMIT(SCHAR_MAX, "%d");
    PRINT_LIMIT(SCHAR_MIN, "%d");
    PRINT_LIMIT(UCHAR_MAX, "%d");
    PRINT_LIMIT(INT_MAX, "%d"); // int is 32 bit
    PRINT_LIMIT(USHRT_MAX, "%d"); // short is 16 bit
    PRINT_LIMIT(ULONG_MAX, "%lu"); // long is 64 bit
    PRINT_LIMIT(ULLONG_MAX, "%llu"); // long long is 64 bit
    PRINT_LIMIT(MB_LEN_MAX, "%d"); // 16
    PRINT_LIMIT(FOPEN_MAX, "%d"); // 16
    PRINT_LIMIT(TMP_MAX, "%d"); // 238328
    PRINT_LIMIT(FILENAME_MAX, "%d"); // 4096
    return 0;
}