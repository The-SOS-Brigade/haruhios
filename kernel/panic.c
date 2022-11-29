#include <haruhi/console.h>
#include <asm/arch.h>

__attribute__((noreturn)) void panic(const char *str) {
	printk("!kernel panic....... %s\n", str);
	printregs();
	for (;;);
}

