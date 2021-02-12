#include "Logger.h"

#include <stdarg.h>
#include <stdio.h>

void logger::Clear() {
    FILE *f = fopen("log.txt", "w");
    fclose(f);
}

void logger::Logf(const char *output, ...) {
    FILE *f = fopen("log.txt", "a");

    va_list args;
    va_start(args, output);
    vfprintf(f, output, args);
    va_end(args);

    fclose(f);
}
