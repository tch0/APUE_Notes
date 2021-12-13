// ISO C99 Standard Libraries
#include <assert.h>     // assert macro
#include <complex.h>    // Complex arithmetic operations 
#include <ctype.h>      // character classification and mapping
#include <errno.h>      // errno lvalue
#include <fenv.h>       // float environment
#include <float.h>      // float constants and features
#include <inttypes.h>   // int types transfromation
#include <iso646.h>     // macros for operators: logical and bit-wise
#include <limits.h>     // limits of integers
#include <locale.h>     // localization
#include <math.h>       // math functions, types, constants
#include <setjmp.h>     // non-local goto
#include <signal.h>     // signal handling
#include <stdarg.h>     // variable arguments
#include <stdbool.h>    // bool true false
#include <stddef.h>     // standard definition
#include <stdint.h>     // fixed length integer types
#include <stdio.h>      // standard Input/Output
#include <stdlib.h>     // general utilities
#include <string.h>     // string operations
#include <tgmath.h>     // general math macros (for float and complex)
#include <time.h>       // date and time
#include <wchar.h>      // wide characters and string operations
#include <wctype.h>     // wide character calssification and mapping
// ISO C11 added Standard Libraries
#include <stdalign.h>   // alignas alignof
#include <stdatomic.h>  // atomic operation & memory fence
#include <stdnoreturn.h>// noreturn macro, specify a function will not return to it's caller(example: return through longjmp)
#include <threads.h>    // thread functions, lock
#include <uchar.h>      // 16 and 32 bits characters

int main()
{
    // in <string.h>, just a test
    printf("%ld\n", strcspn("hellowrold", "osdfs")); // return count until get char in reject strings
    printf("%ld\n", strspn("helloworld", "helasdf")); // return count of chars in accept strings
    return 0;
}