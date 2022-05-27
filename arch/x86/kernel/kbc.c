#include <haruhi/console.h>
#include <haruhi/types.h>
#include <haruhi/kbc.h>
#include <asm/acpi.h>
#include <asm/kbc.h>
#include <asm/io.h>

#define KBC_POLL_TIMEOUT	100
#define KBC_MIN_ACPI_REVISION	2

static bool _port1_used = false;
static bool _port2_used = false;

static inline u8 kbc_read_status(void)
{
	return inb(KBC_STATUS);
}

static inline u8 kbc_read_confbyte(void)
{
	kbc_send_command8(KBC_CMD_READ0);
	return kbc_read8();
}

static inline void kbc_write_confbyte(u8 conf)
{
	kbc_send_command16(KBC_CMD_WRITE0 | (conf << 0x8));
}

static int kbc_wait4input(void)
{
	u8 timeout = KBC_POLL_TIMEOUT;

	do {
		if (kbc_read_status() & KBC_STATUS_OBSY)
			break;
		io_wait();
	} while (timeout--);

	if (!timeout)
		return -1;

	return 0;
}

static int kbc_wait4output(void)
{
	u8 timeout = KBC_POLL_TIMEOUT;

	do {
		if (kbc_read_status() & KBC_STATUS_IBSY)
			break;
		io_wait();
	} while (timeout--);

	if (!timeout)
		return -1;

	return 0;
}

void kbc_send_command8(u8 cmd)
{
	kbc_wait4output();
	outb(KBC_CMD, cmd);
}

void kbc_send_command16(u16 cmd)
{
	kbc_send_command8(cmd & 0xFF);
	kbc_wait4output();
	outb(KBC_DATA, cmd >> 0x10);
}

int kbc_send_byte_port1(u8 data)
{
	if (kbc_wait4output() != 0)
		return -1;

	outb(KBC_DATA, data);
	return 0;
}

int kbc_send_byte_port2(u8 data)
{
	kbc_send_command8(KBC_CMD_WRINPORT2);

	if (kbc_wait4output() != 0)
		return -1;

	outb(KBC_DATA, data);
	return 0;
}

u8 kbc_read8(void)
{
	kbc_wait4input();
	return inb(KBC_DATA);
}


/* init ACPI first */
void kbc_init(void)
{
	bool is_dual_channel = false;
	struct acpi_fadt_desc *fadt = get_fadt();

	if (fadt->hdr.revision < KBC_MIN_ACPI_REVISION) {
		printk("KBC: ACPI too old\n");
		return;
	}

	if (~((char *)fadt)[109] & 2) {
		printk("KBC: no controller found\n");
		return;
	}

	kbc_send_command8(KBC_CMD_DISPORT1);
	kbc_send_command8(KBC_CMD_DISPORT2);

	/* flush */
	inb(KBC_DATA);

	u8 config = kbc_read_confbyte();
	config &= 0b10111100;
	is_dual_channel = (config & 0b100000) ? true : false;


	/* kbc self test */
	kbc_send_command8(KBC_CMD_TESTKBC);
	if (kbc_read8() != KBC_TEST_PASSED) {
		printk("KBC: controller self test failed\n");
		return;
	}

	kbc_write_confbyte(config);

	/* test ports */
	kbc_send_command8(KBC_CMD_TESTPORT1);
	_port1_used |= (kbc_read8() == KBC_PORTTEST_PASSED)
			? true : false;

	if (is_dual_channel) {
		kbc_send_command8(KBC_CMD_ENAPORT2);

		if (kbc_read_status() & 0b100000) {
			is_dual_channel = false;
		} else {
			kbc_send_command8(KBC_CMD_DISPORT2);
			kbc_send_command8(KBC_CMD_TESTPORT2);
			_port2_used |= (kbc_read8() == KBC_PORTTEST_PASSED)
					? true : false;
		}
	}

	/* enable ports */
	if (_port1_used)
		kbc_send_command8(KBC_CMD_ENAPORT1);
	else
		kbc_send_byte_port1(0xFF);

	if (is_dual_channel) {
		if (_port2_used)
			kbc_send_command8(KBC_CMD_ENAPORT2);
		else
			kbc_send_byte_port2(0xFF);
	}

	printk("KBC: port1 %sabled\n", _port1_used ? "en" : "dis");
	printk("KBC: port2 %sabled\n", _port2_used ? "en" : "dis");
}

