/* Copyright (C) 2025 ITlopa */
#ifndef __PRINTREALISE__
#define __PRINTREALISE__ 1

// Only print :)

#include <linux/stdarg.h>
#include <linux/kernel.h>

int __VOSPRINT(int __ossoh, const char* __fmt, va_list __args);

int __OSPRINT(int __ossoh, const char* __fmt, ...);

#define vosprint(__ossoh, __fmt, __args) __VOSPRINT(__ossoh, __fmt, __args)

#define osprint(__ossoh, __fmt, ...) __OSPRINT(__ossoh, __fmt, ##__VA_ARGS__)

#define linux_print(__fmt, ...) osprint(KERN_SOH_ASCII, __fmt, ##__VA_ARGS__)

#endif
