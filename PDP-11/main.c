#include "foo.h"
#include <stdarg.h>

int main(int argc, char* argv[]){
    test_mem();
    load_file(argv[1]);
    test_load();
    trace("ghjg %d\n", 1);
    return 0;
}

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

