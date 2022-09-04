#ifndef _ASM_X86_PIC_H
#define _ASM_X86_PIC_H

#include <haruhi/types.h>

#define PIC0_CMD 0x20
#define PIC0_DATA (PIC0_CMD + 1)
#define PIC1_CMD 0xA0
#define PIC1_DATA (PIC1_CMD + 1)

#define ICW1_ICW4	0b00000001
#define ICW1_SNGL	0b00000010
#define ICW1_LTIM	0b00001000
#define ICW1_INIT	0b00010000 /* always required */

#define ICW2_OFF	0b11111000

#define ICW3_MASTER	0b11111111
#define ICW3_SLAVE	0b00000111

#define ICW4_808X	0b00000001
#define ICW4_AEOI	0b00000010
#define ICW4_MASTER	0b00000100
#define ICW4_BUF	0b00001000
#define ICW4_SFNM	0b00010000

#define OCW1_MASK	0b11111111

#define OCW2_L		0b00000111
#define OCW2_EOI	0b00100000
#define OCW2_SL		0b01000000
#define OCW2_R		0b10000000

#define OCW3_RIS	0b00000001
#define OCW3_RR		0b00000010
#define OCW3_P		0b00000100
#define OCW3_REQ	0b00001000 /* always required */
#define OCW3_SMM	0b00100000
#define OCW3_ESMM	0b01000000

enum {
	IRQ_TASK_TIMER	= 0,
	IRQ_TASK_KBD	= 1,
	IRQ_TASK_CAS	= 2,
	IRQ_TASK_COMM2	= 3,
	IRQ_TASK_COMM1	= 4,
	IRQ_TASK_FLOPPY	= 6,
	IRQ_TASK_LPT1	= 7,
	IRQ_TASK_RTC	= 8,
	IRQ_TASK_CGA	= 9,
	IRQ_TASK_PS2	= 12,
	IRQ_TASK_FPU	= 13,
	IRQ_TASK_HDC	= 14
};

void pic_remap(u8 offset0, u8 offset1);
u16 pic_irr(void);
u16 pic_isr(void);
void pic_eoi(u8 irq);
void pic_set_mask(u8 line);
void pic_clear_mask(u8 line);
void pic_set_all_masks(void);
void pic_clear_all_masks(void);

#endif

