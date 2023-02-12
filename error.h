/**
 * @file error.h
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad b)
 * @date 2022-03-13
 * přeloženo pomoci gcc 9.4.0
 */

#include <stdarg.h>

//guard
#ifndef ERROR_H
#define ERROR_H

void warning_message(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif