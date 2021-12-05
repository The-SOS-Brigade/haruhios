#include <haruhi/types.h>
#include <asm/pic.h>
#include <asm/gate.h>
#include <asm/io.h>

#define PIC_EOI OCW2_EOI
#define PIC_IRR (OCW3_RR | OCW3_REQ)
#define PIC_ISR (OCW3_RR | OCW3_RIS | OCW3_REQ)

void pic_remap(u8 offset0, u8 offset1)
{
	u8 imr0 = inb(PIC0_DATA);
	u8 imr1 = inb(PIC1_DATA);

	/* ICW1 */
	outb(PIC0_CMD, ICW1_INIT | ICW1_ICW4);
	outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();

	/* ICW2 */
	outb(PIC0_DATA, offset0);
	outb(PIC1_DATA, offset1);
	io_wait();

	/* ICW3 */
	outb(PIC0_DATA, 0b00000100);
	outb(PIC1_DATA, 0b010);
	io_wait();

	/* ICW4 */
	outb(PIC0_DATA, ICW4_808X);
	outb(PIC1_DATA, ICW4_808X);
	io_wait();

	outb(PIC0_DATA, imr0);
	outb(PIC1_DATA, imr1);
	io_wait();
}

u16 pic_irr(void)
{
	outb(PIC0_CMD, PIC_IRR);
	outb(PIC1_CMD, PIC_IRR);
	return inb(PIC0_CMD) | (inb(PIC1_CMD) << 8);
}

u16 pic_isr(void)
{
	outb(PIC0_CMD, PIC_ISR);
	outb(PIC1_CMD, PIC_ISR);
	return inb(PIC0_CMD) | (inb(PIC1_CMD) << 8);
}

void pic_eoi(u8 irq)
{
	if (irq >= 8)
		outb(PIC1_CMD, PIC_EOI);

	outb(PIC0_CMD, PIC_EOI);
}

