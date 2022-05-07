#include <haruhi/console.h>

__attribute__((noreturn)) void panic(const char *str) {
	printk("!kernel panic....... %s\n", str);
	for (;;);
}

