#include "foo.h"
#include <stdarg.h>

trace(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    //printf("ghjg %d\n", 1);
    va_end(argptr);
    //printf("%s", format);
    //printf(format, ...);
}
