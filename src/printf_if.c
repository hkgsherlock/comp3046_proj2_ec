#include "printf_if.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

// http://stackoverflow.com/questions/21540778/pass-varargs-to-printf

void printf_if(bool how, const char* format, ...) {
    if (how) {
        va_list argptr;
        va_start(argptr, format);
        vfprintf(stdout, format, argptr);
        va_end(argptr);
    }
}