/**
 * @file error.c
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad b)
 * @date 2022-03-13
 * přeloženo pomoci gcc 9.4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void warning_message(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Chyba: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Chyba: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}
