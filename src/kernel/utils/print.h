#ifndef __PRINT_H
#define __PRINT_H

#include "varargs.h"

int vsprintf(char *buf, const char *fmt, va_list args);
void printk(const char *fmt, ...);

#endif
