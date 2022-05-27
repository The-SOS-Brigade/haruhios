#ifndef _ASM_X86_KBC_H
#define _ASM_X86_KBC_H

#include <haruhi/types.h>

#define KBC_DATA		0x60
#define KBC_STATUS		0x64
#define KBC_CMD			0x64

#define KBC_STATUS_OBSY		0b00000001
#define KBC_STATUS_IBSY		0b00000010
#define KBC_STATUS_SYS		0b00000100
#define KBC_STATUS_DATA		0b00001000
#define KBC_STATUS_TOERR	0b01000000
#define KBC_STATUS_PARERR	0b10000000

#define KBC_CMD_READ0		0x20
#define KBC_CMD_READ(x)		(KBC_CMD_READ0 | (x & 0x1F))
#define KBC_CMD_WRITE0		0x60
#define KBC_CMD_WRITE(x)	(KBC_CMD_WRITE0 | (x & 0x1F))
#define KBC_CMD_DISPORT2	0xA7
#define KBC_CMD_ENAPORT2	0xA8
#define KBC_CMD_TESTPORT2	0xA9
#define KBC_CMD_TESTKBC		0xAA
#define KBC_CMD_TESTPORT1	0xAB
#define KBC_CMD_MEMDUMP		0xAC
#define KBC_CMD_DISPORT1	0xAD
#define KBC_CMD_ENAPORT1	0xAE
#define KBC_CMD_RDIN		0xC0
#define KBC_CMD_LOWCP2STATUS	0xC1
#define KBC_CMD_HIGHCP2STATUS	0xC2
#define KBC_CMD_RDOUT		0xD0
#define KBC_CMD_WROUT		0xD1
#define KBC_CMD_WROUTPORT1	0xD2
#define KBC_CMD_WROUTPORT2	0xD3
#define KBC_CMD_WRINPORT2	0xD4
#define KBC_CMD_PULSE(l)	(0xF0 | (l & 0xF))

#define KBC_TEST_PASSED		0x55
#define KBC_TEST_FAILED		0xFC
#define KBC_PORTTEST_PASSED	0x00

unsigned char kbc_read_output(void);
void kbc_send_command8(u8 cmd);
void kbc_send_command16(u16 cmd);
int kbc_send_data_port1(u8 data);
int kbc_send_byte_port2(u8 data);
u8 kbc_read8(void);

#endif
