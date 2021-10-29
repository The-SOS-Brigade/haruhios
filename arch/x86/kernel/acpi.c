#include <haruhi/console.h>
#include <haruhi/types.h>
#include <haruhi/string.h>
#include <asm/acpi.h>

static int rsdp_is_valid(struct acpi_rsdp_desc *rsdp)
{
	u32 checksum = 0;
	char *addr = (char *)rsdp;

	for (size_t i = 0; i < sizeof(struct acpi_rsdp_desc); ++i) {
		checksum += addr[i];
	}

	return (checksum & 0xFF) == 0;
}

static int table_is_valid(struct acpi_table_header *table)
{
	u32 checksum = 0;
	const char *addr = (const char *)table;
	while ((u32)addr < table->length) {
		checksum += *addr++;
	}

	return checksum == 0;
}

static void *locate_rsdp(void)
{
	char *signature		= ACPI_RSDP_SIGNATURE;
	short *ebda_seg_ptr	= (short *)0x40E;
	char *start_addr	= (char *)(*ebda_seg_ptr << 1);
	char *end_addr		= (char *)(start_addr + 0x400);
	void *rsdp 		= NULL;

	/* Search in EBDA region */
	for (char *addr = start_addr; addr < end_addr; ++addr) {
		if(strcmp(signature, addr) == 0) {
			rsdp = (void *)addr;
			goto out;
		}
	}

	start_addr	= (char *)0xF0000;
	end_addr	= (char *)0xFFFFF;

	/* Search in main BIOS region */
	for (char *addr = start_addr; addr < end_addr; ++addr) {
		if(strcmp(signature, addr) == 0) {
			rsdp = (void *)addr;
			goto out;
		}
	}

out:
	return rsdp;
}

int acpi_init(void)
{
	int res = 0;
	struct acpi_rsdp_desc *rsdp;
	struct acpi_table_header *rsdt;

	rsdp = (struct acpi_rsdp_desc *)locate_rsdp();

	if (rsdp == NULL) {
		res = -1;
		goto out;
	}

	if(!rsdp_is_valid(rsdp)) {
		res = -1;
		goto out;
	}

	rsdt = (struct acpi_table_header *)rsdp->rsdt_addr;
	char *signature = ACPI_RSDT_SIGNATURE;

	if(strcmp(signature, rsdt->signature) != 0
				|| !table_is_valid(rsdt)) {
		res = -1;
		goto out;
	}

out:
	return res;
}

