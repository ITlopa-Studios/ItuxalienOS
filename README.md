# Ituxalien Operating System
## Documentation
Example:
```c
#include <linux/module.h>
#include <ituxalien/kernel.h>
// #include <ituxalien/unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("Simple module for Ituxalien.");
MODULE_VERSION("0.1");

static int __init hello_init(void) {
    printitux(_ITUX_INF "Hello, World!\n"); // Or write(STDOUT_FILENO, "Hello, World!\n", itux_lofstring("Hello, World!\n"))
    return 0; // 0 is success
}

static void __exit hello_exit(void) {
    printitux(_ITUX_INF "Goodbye, World!\n"); // Or write(STDOUT_FILENO, "Goodbye, World!\n", itux_lofstring("Goodbye, World!\n"))
}

module_init(hello_init);
module_exit(hello_exit);
```
