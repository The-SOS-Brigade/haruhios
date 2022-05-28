#include <haruhi/console.h>
#include <haruhi/types.h>
#include <haruhi/string.h>
#include <asm/acpi.h>
#include <asm/io.h>

struct acpi_rsdp_desc *_rsdp;
struct acpi_fadt_desc *_fadt;
struct acpi_rsdt_desc *_rsdt;

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
	char *start_addr	= (char *)(*ebda_seg_ptr << 4);
	char *end_addr		= (char *)(start_addr + 0x400);
	void *rsdp 		= NULL;

	/* Search in EBDA region */
	for (char *addr = start_addr; addr < end_addr; ++addr) {
		if(!strncmp(signature, addr, 8)
		   && rsdp_is_valid((struct acpi_rsdp_desc *)addr)) {
			rsdp = (void *)addr;
			goto out;
		}
	}

	start_addr	= (char *)0xE0000;
	end_addr	= (char *)0xFFFFF;

	/* Search in main BIOS region */
	for (char *addr = start_addr; addr < end_addr; ++addr) {
		if (!strncmp(signature, addr, 8)
		    && rsdp_is_valid((struct acpi_rsdp_desc *)addr)) {
			rsdp = (void *)addr;
			goto out;
		}
	}

out:
	return rsdp;
}

static struct acpi_fadt_desc *locate_fadt(struct acpi_rsdt_desc *rsdt)
{
	struct acpi_table_header *rsdt_hdr = &rsdt->hdr;
	size_t entries = (rsdt_hdr->length - sizeof(rsdt_hdr)) / 4;

	struct acpi_table_header *header = NULL;

	for (size_t i = 0; i < entries; ++i) {
		header = (struct acpi_table_header *)((u32 *)&rsdt->table_ptr)[i];
		if (!strncmp(ACPI_FADT_SIGNATURE, header->signature, 4)
		    && table_is_valid(header))
			return (struct acpi_fadt_desc *)header;
	}
	return NULL;
}

int acpi_init(void)
{
	int res = 0;

	_rsdp = (struct acpi_rsdp_desc *)locate_rsdp();

	if (_rsdp == NULL) {
		printk("ACPI: RSDP not found\n");
		res = -1;
		goto out;
	}

	printk("ACPI: RSDP revision %d\n", _rsdp->revision);

	_rsdt = (struct acpi_rsdt_desc *)_rsdp->rsdt_addr;
	char *signature = ACPI_RSDT_SIGNATURE;

	if (strncmp(signature, _rsdt->hdr.signature, 4) != 0
				|| !table_is_valid(&_rsdt->hdr)) {
		res = -1;
		goto out;
	}

	printk("ACPI: RSDT revision %d\n", _rsdt->hdr.revision);

	_fadt = locate_fadt(_rsdt);

	if (_fadt == NULL) {
		printk("ACPI: FADT not found\n");
		res = -1;
		goto out;
	}

	printk("ACPI: FADT revision %d\n", _fadt->hdr.revision);

out:
	return res;
}
