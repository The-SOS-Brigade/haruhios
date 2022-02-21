#include <haruhi/types.h>
#include <haruhi/console.h>
#include <asm/acpi.h>
#include <asm/io.h>

#define KBC_DATA	0x60
#define KBC_STATUS	0x64
#define KBC_CMD		0x64

#define _STR_OUT_STATUS		0b00000001
#define _STR_IN_STATUS		0b00000010
#define _STR_SYSTEM_FLAG	0b00000100
#define _STR_DATA_TARGET	0b00001000
#define _STR_SPECIFIC		0b00110000
#define _STR_TIMEOUT		0b01000000
#define _STR_PARITY_ERROR	0b10000000

#define KBC_READ_BYTE0 0x20
#define KBC_READ_BYTE(n) ((n | PS_READ_BYTE) & 0x1F)
#define KBC_WRITE_BYTE0 0x60
#define KBC_WRITE_BYTE(n) ((n | PS2_WRITE_BYTE) & 0x1F)
#define KBC_DISABLE_SECOND 0xA7
#define KBC_ENABLE_SECOND 0xA8
#define KBC_TEST 0xAA
# define KBC_TEST_PASSED 0x55
# define KBC_TEST_FAILED 0xFC
#define KBC_DISABLE_FIRST 0xAD
#define KBC_ENABLE_FIRST 0xAE
#define KBC_READ_IPORT 0xC0
#define KBC_READ_OPORT 0xD0

static inline void kbc_wait(void)
{
	while (~inb(KBC_STATUS) & 1)
		io_wait();
}

static u8 kbc_read_output(void)
{
	outb(KBC_CMD, KBC_READ_OPORT);
	kbc_wait();
	return inb(KBC_DATA);
}

static u8 read_config_byte(void)
{
	outb(KBC_CMD, KBC_READ_BYTE0);
	kbc_wait();
	return inb(KBC_DATA);
}

/* init ACPI first */
void kbc_init(void)
{
	struct acpi_fadt_desc *fadt = get_fadt();

	if (fadt->hdr.revision < 2) {
		printk("i8042: ACPI too old\n");
		return;
	}

	if (~((char *)fadt)[109] & 2) {
		printk("i8042: not found\n");
		return;
	}

	outb(KBC_CMD, KBC_DISABLE_FIRST);
	kbc_wait();
	outb(KBC_CMD, KBC_DISABLE_SECOND);
	kbc_wait();

	/* flush */
	inb(KBC_DATA);

	u8 config = read_config_byte();
	config &= 0b01000011;
}

