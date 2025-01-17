/*
Copyright (C) 2025 ITlopa
*/
#ifndef _ITUX_KERNEL_
#define _ITUX_KERNEL_ 1

#include <ituxalien/types.h>
#include <ituxalien/kernel/printitux.h>

#ifndef CONFIG_PRINTK
#define CONFIG_PRINTK 1
#endif

#ifndef __linux__
#define __linux__ 1
#endif



#ifndef __ituxalien__
#define __ituxalien__ 1
#endif

#ifndef printitux
#define printitux(__fmt, ...) WRAPE_PRINTFUNC(_printitux, __fmt, ##__VA_ARGS__)
#endif

#ifndef printic
#define printic(__ty, __ch) NWRAPE_PRINTCHFUNC(_printic, __ty, __ch)
#endif

size_t itux_lofstring(const itux_string __str);

#include <ituxalien/kernel/readitux.h>

#ifndef readitux
#define readitux(__fmt, ...) WRAPE_READFUNC(_readitux, __fmt, ##__VA_ARGS__)
#endif

#ifndef readic
#define readic(__ch) WRAPE_READFUNC(_readic, __ch)
#endif

#define STDIN_FILE "/dev/stdin"

#define STDOUT_FILE "/dev/stdout"

#define STDERR_FILE "/dev/stderr"

itux_string itux_dupstring(itux_string __str);

void* itux_malloc(size_t __size);

void itux_free(const void*);

void* itux_realloc(const void *, size_t);

void itux_efp(long __code);

#endif