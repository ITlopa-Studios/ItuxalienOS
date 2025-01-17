/*
Copyright (C) 2025 ITlopa
The POSIX <unistd.h> file. Works in Ituxalien
*/
#ifndef _ITUX_UNISTD_
#define _ITUX_UNISTD_ 1

#include <linux/types.h>

#include <asm/unistd.h>

#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/namei.h>
#include <linux/file.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/mm.h>

int open(const char __user *__path, int __flags, umode_t __mode);

#define UNIX_CALLFUNC(__func) ({ \
    int ret = (__func); \
    if (ret < 0) { \
        printk(KERN_ERR "Error in %s: %d\n", #__func, ret); \
        return ret; \
    } \
})

#define UNUSED_CALLFUNC(__func, ...) UNIX_CALLFUNC(__func)(__VA_ARGS__)

#define GEN_FILENO(__fd) __fd

#define STDIN_FILENO (GEN_FILENO(0))
#define STDOUT_FILENO (GEN_FILENO(1))
#define STDERR_FILENO (GEN_FILENO(2))

int close(int __fd);

ssize_t write(int __fd, const void *__str, size_t __bytes);

ssize_t read(int __fd, void *__buf, size_t __count);

int execlp(const char *__file, const char *__arg, ..., NULL);

#endif