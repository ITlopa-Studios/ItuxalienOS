/*
Copyright (C) 2025 ITlopa
*/
#ifndef _ITUX_TYPES_
#define _ITUX_TYPES_ 1

#include <linux/types.h>

#define _ITUX_RETURN 0

#define _ITUXSOH "\t"

#define _ITUXSOH_ASCII '\t'

#define _ITUXSOH_INT 9

#define _ITUXINF _ITUXSOH "1"

#define _ITUXERR _ITUXSOH "2"

#define _ITUXALR _ITUXSOH "3"

#define _ITUXWARN _ITUXSOH "4"

#define _ITUXFATAL _ITUXSOH "5"

#define _ITUXCRITICAL _ITUXSOH "6"

#define _ITUXCONTSTR _ITUXSOH "a"

#define _ITUXSUCCES _ITUX_RETURN + 0
#define _ITUXFAIL _ITUX_RETURN - 1

#ifndef __ituxalien__
#define __ituxalien__ 1
#endif

typedef char* itux_string;



#endif