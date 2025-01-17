/*
Copyright (C) 2025 ITlopa
*/
#ifndef _ITUX_KERNEL_RI_
#define _ITUX_KERNEL_RI_ 1

#include <linux/stdarg.h>

#define _READITUX_ 1

#ifdef _READITUX_
int vreaditux(const char* __fmt, va_list __arg);
int _readitux(const char* __fmt, ...);
int _readic(int __ch);
#endif

#ifndef _READITUX_
inline int vreaditux(const char* __fmt, va_list __arg)
{
    return 0;
}
inline int _readitux(const char* __fmt, ...)
{
    return 0;
}
inline int _readic(int __ch)
{
    return 0;
}
#endif

#define _DEFINE_READFUNC(__name) int __name(const char *__fmt, ...)

#define DEFINE_READFUNC(__name) _DEFINE_READFUNC(__name)

#define _CREATE_READFUNC(__name) DEFINE_READFUNC(__name) {int result; va_list args; va_start(args, __fmt); result = vreaditux(__fmt, args) va_end(args); return result;}

#define CREATE_READFUNC(__name) _CREATE_READFUNC(__name)

#define _WRAPE_READFUNC(__name, __fmt, ...) ({ do {} while (0); __name(__fmt, ##__VA_ARGS__); })

#define WRAPE_READFUNC(__name, __fmt, ...) _WRAPE_READFUNC(__name, __fmt, ##__VA_ARGS__)

#ifndef readitux
#define readitux(__fmt, ...) WRAPE_READFUNC(_readitux, __fmt, ##__VA_ARGS__)
#endif

#ifndef readic
#define readic(__ch) WRAPE_READFUNC(_readic, __ch)
#endif

#endif
