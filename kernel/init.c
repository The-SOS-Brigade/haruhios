#include <haruhi/console.h>
#include <haruhi/acpi.h>
#include <haruhi/string.h>

void kernel_entry(void)
{
	console_init();
	if(acpi_init())
		printk("ACPI: initialization failed\n");
	printk("haruhios\n");
	return;
}

