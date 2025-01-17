/*
Copyright (C) 2025 ITlopa
*/
#ifndef _ITUX_KERNEL_PI_
#define _ITUX_KERNEL_PI_ 1

#include <linux/stdarg.h>

#define _PRINTITUX_ 1

#ifdef _PRINTITUX_

int vprintitux(const char* __fmt, va_list __args);


int _printitux(const char* __fmt, ...);

#else

inline int _printitux(const char* __fmt, ...)
{
    return 0;
}


inline int vprintitux(const char* __fmt, va_list __args)
{
    return 0;
}

#endif

#define _WRAPE_PRINTFUNC(__func, __fmt, ...) ({ do {} while (0); __func(__fmt, ##__VA_ARGS__); })

#define WRAPE_PRINTFUNC(__func, __fmt, ...) _WRAPE_PRINTFUNC(__func, __fmt, ##__VA_ARGS__)

#define _CREATE_PRINTFUNC(__func) int __func(const char* __fmt, ...) {va_list args; va_start(args, __fmt); int result = vprintitux(_ITUXINF __fmt, args); va_end(args); return result;}

#define CREATE_PRINTFUNC(__func) _CREATE_PRINTFUNC(__func)

#define _DEFINE_PRINTFUNC(__func) int __func(const char* __fmt, ...)

#define DEFINE_PRINTFUNC(__func) _DEFINE_PRINTFUNC(__func)



#ifndef printitux
#define printitux(__fmt, ...) WRAPE_PRINTFUNC(_printitux, __fmt, ##__VA_ARGS__)
#endif

#ifdef _PRINTITUX_
int _printic(const char* __ty, int __ch);
#else
inline int _printic(const char* __ty, int __ch)
{
    return 0;
}
#endif

#define _WRAPE_PRINTCHFUNC(__func, __ch) ({ do {} while (0); __func(__ch); })

#define WRAPE_PRINTCHFUNC(__func, __ch) _WRAPE_PRINTCHFUNC(__func, __ch)

#define _DEFINE_PRINTCHFUNC(__func) int __func(int __ch)

#define DEFINE_PRINTCHFUNC(__func) _DEFINE_PRINTCHFUNC(__func)

#define NWRAPE_PRINTCHFUNC(__func, __ty, __ch) ({ do {} while (0); __func(__ty, __ch); })

#ifndef printic
#define printic(__ty, __ch) NWRAPE_PRINTCHFUNC(_printic, __ty, __ch)
#endif

#define CREATE_PRINTCHFUNC(__func) int __func(int __ch) {return printic(_ITUXINF, __ch);}

#endif
