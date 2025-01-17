/*
Copyright (C) 2025 ITlopa
*/
#include <ituxalien/kernel.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <ituxalien/unistd.h>
#include <ituxalien/encode.h>

#include <linkedio/print.h>



// For print

int __VOSPRINT(int __ossoh, const char* __fmt, va_list __args) {
    if (__ossoh == _ITUXSOH_ASCII) {
        #ifdef __ituxalien__
        int result = -1;

        if (strlen(__fmt) > 2 && __fmt[0] == '\t') {
            if (__fmt[1] == '1') {
                result = vprintk(KERN_INFO __fmt + 3, __args);
            } else if (__fmt[1] == '2') {
                result = vprintk(KERN_ERR __fmt + 3, __args);
            } else if (__fmt[1] == '3') {
                result = vprintk(KERN_ALERT __fmt + 3, __args);
            } else if (__fmt[1] == '4') {
                result = vprintk(KERN_WARNING __fmt + 3, __args);
            } else if (__fmt[1] == '5') {
                result = vprintk(KERN_CRIT __fmt + 3, __args);
            } else if (__fmt[1] == '6') {
                result = vprintk(KERN_EMERG __fmt + 3, __args);
            } else if (__fmt[1] == 'a') {
                result = vprintk(KERN_CONT __fmt + 3, __args);
            }
        }
        return result;
        #else
        return -1;
        #endif
    }
    else if (__ossoh == KERN_SOH_ASCII) {
        #ifdef __linux__
        return vprintk(__fmt, __args);
        #else
        return -1;
        #endif
    }
}

int __OSPRINT(int __ossoh, const char* __fmt, ...)
{
    int result;
    va_list args;
    va_start(args, __fmt);
    result = __VOSPRINT(__ossoh, __fmt, args);
    va_end(args);
    return result;
}

// Realisation of _printitux
#ifdef _PRINTITUX_

int vprintitux(const char* __fmt, va_list __args)
{
    return vosprint(_ITUXSOH_ASCII, __fmt, __args);
}

int _printitux(const char* __fmt, ...)
{
    int result;
    va_list arg;
    va_start(arg);
    result = vprintitux(__fmt, arg);
    va_end(arg);
    return result;
}

#endif


// Realisation of _printic

#ifdef _PRINTITUX_
int _printic(const char* __ty, int __ch)
{
    int result = printitux(__ty "%d", __ch);
    return result;
}
#endif




int open(const char __user *__path, int __flags, umode_t __mode) {
    #ifdef __ituxalien__
    struct file *file;
    int fd;

    if (!__path) {
        return -EINVAL;
    }

    file = filp_open(__path, __flags, __mode);
    if (IS_ERR(file)) {
        return PTR_ERR(file);
    }

    fd = get_unused_fd_flags(__flags);
    if (fd < 0) {
        filp_close(file, NULL);
        return fd;
    }

    fget(fd);
    current->files->fd_array[fd] = file;

    return fd;
    #else
    return -1;
    #endif
}

int close(int __fd)
{
    #ifdef __ituxalien__
    int result = -1;
    if (__fd == STDIN_FILENO || __fd == STDOUT_FILENO || __fd == STDERR_FILENO) {
        return result;
    }
    struct file *fl;
    fl = fget(__fd);
    fput(fl);
    result = 0;
    return result;
    #else
    return -1;
    #endif
}

ssize_t write(int __fd, const void *__str, size_t __bytes) {
    ssize_t result = 0;

    if (__fd == STDIN_FILENO) {
        return -EINVAL;
    }

    if (__fd == STDOUT_FILENO) {
        for (size_t i = 0; i < __bytes; i++) {
            printic(_ITUXINF, __str[i]);
            result++;
        }
        return result;
    }

    if (__fd == STDERR_FILENO) {
        for (size_t i = 0; i < __bytes; i++) {
            printic(_ITUXERR, __str[i]);
            result++;
        }
        return result;
    }

    #ifdef __ituxalien__
    struct file *file;

    file = fget(__fd);
    if (!file) {
        return -EBADF;
    }

    result = kernel_write(file, __str, __bytes, &file->f_pos);

    return result;
    #else
    return -1;
    #endif
}

ssize_t read(int __fd, void *__buf, size_t __count) {
    #ifdef __ituxalien__
    struct file *file;
    ssize_t result;

    if (__fd < 0 || !__buf || __count == 0) {
        return -EINVAL;
    }

    if (__fd == STDIN_FILENO) {
        file = filp_open(STDIN_FILE, O_RDONLY, 0);
        if (IS_ERR(file)) {
            return PTR_ERR(file);
        }
    }
    if (__fd == STDOUT_FILENO || __fd == STDERR_FILENO) {
        return -EINVAL; // Check the stdout, stderr stream
    } else {
        file = fget(__fd);
        if (!file) {
            return -EBADF;
        }
    }

    result = kernel_read(file, __buf, __count, &file->f_pos);
    
    if (__fd == STDIN_FILENO) {
        fput(file);
    }

    if (result < 0) {
        return result;
    }

    return result;
    #else
    return -1;
    #endif
}

int execlp(const char *__file, const char *__arg, ..., NULL) {
    #ifdef __ituxalien__
    struct path path;
    struct file *file_ptr;
    char *exec_path;
    char *argv[64];
    int i = 0;
    va_list args;

    if (kern_path(__file, LOOKUP_FOLLOW, &path)) {
        return -ENOENT;
    }

    file_ptr = filp_open(__file, O_RDONLY, 0);
    if (IS_ERR(file_ptr)) {
        return PTR_ERR(file_ptr);
    }

    va_start(args, __arg);
    argv[i++] = (char *)__arg;
    while (__arg != NULL && i < 64) {
        __arg = va_arg(args, char *);
        argv[i++] = __arg;
    }
    argv[i] = NULL;

    if (do_execve(file_ptr->f_path.dentry->d_name.name, argv, NULL) < 0) {
        filp_close(file_ptr, NULL);
        return -1;
    }

    filp_close(file_ptr, NULL);
    return 0;
    #else
    return -1;
    #endif
}

size_t itux_lofstring(const itux_string __str)
{
    size_t i = 0; // Init the counter
    while (__str[i] != '\0') {
        i++;
    }
    return i;
}

int vreaditux(const char* __fmt, va_list __arg)
{
    #ifdef __ituxalien__
    static char buf[1024];
    vsnprintf(buf, sizeof(buf), __fmt, __arg);
    read(STDIN_FILENO, buf, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    __fmt = buf;
    return (int)itux_lofstring(buf);
    #else
    return -1;
    #endif
}

int _readitux(const char* __fmt, ...)
{
    int result;
    va_list args;
    va_start(args, __fmt);
    result = vreaditux(__fmt, args);
    va_end(args);
    return result;
}

int _readic(int __ch)
{
    return readitux("%d", __ch);
}

typedef struct {
    const itux_string st;
    const itux_string origin;
} ItuxBinTable;

ItuxBinTable Binary_Table[] = {
    {"1", "full"},
    {"0", "not"},
    {"a", "cont"},
    {"c", "inue"}
};

itux_string itux_dupstring(itux_string __str)
{
    return kstrdup(__str, GFP_KERNEL);
}

void* itux_malloc(size_t __size)
{
    return kmalloc(__size, GFP_KERNEL);
}

void itux_free(const void* __block)
{
    return kfree(__block);
}

void* itux_realloc(const void *__last, size_t __new)
{
    return krealloc(__last, __new, GFP_KERNEL);
}

const itux_string encode_ituxbin(const itux_string __input) {
    size_t table_size = sizeof(Binary_Table) / sizeof(Binary_Table[0]);
    
    size_t buffer_size = itux_lofstring(__input) * 5;
    itux_string result = itux_malloc(buffer_size);
    if (!result) {
        return NULL;
    }
    
    result[0] = '\0';
    itux_string temp = itux_dupstring(__input);

    for (size_t i = 0; i < table_size; i++) {
        char *pos;
        while ((pos = strstr(temp, Binary_Table[i].st)) != NULL) {
            size_t new_length = itux_lofstring(result) + (pos - temp) + itux_lofstring(Binary_Table[i].origin);
            char *new_result = itux_realloc(result, new_length + 1);
            if (!new_result) {
                itux_free(result);
                itux_free(temp);
                return NULL;
            }
            result = new_result;

            strncat(result, temp, pos - temp);
            strcat(result, Binary_Table[i].origin);
            temp = pos + itux_lofstring(Binary_Table[i].st);
        }
    }

    strcat(result, temp);
    itux_free(temp);
    return result;
}

void encode_ituxbin_end(const itux_string __nt)
{
    itux_free(__nt);
}

void itux_efp(long __code)
{
    do_exit(__code);
}
