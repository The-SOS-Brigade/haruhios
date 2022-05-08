#include <haruhi/memory/kheap.h>
#include <haruhi/memory/paging.h>
#include <haruhi/console.h>
#include <haruhi/canary.h>
#include <haruhi/acpi.h>
#include <haruhi/string.h>
#include <haruhi/int.h>
#include <haruhi/kbc.h>

void __attribute__((section(".text.entry"))) kernel_entry(void)
{
	load_canary();

	console_init();
	kheap_init();
	interrupt_init();

	if(acpi_init())
		printk("ACPI: initialization failed\n");

	kbc_init();
	printk("haruhios\n");
	asm volatile("1: jmp 1b");
}

