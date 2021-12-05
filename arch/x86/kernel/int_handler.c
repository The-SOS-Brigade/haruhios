#include <asm/pic.h>
#include <asm/io.h>

void timer_irq_handler(void)
{
	pic_eoi(IRQ_TASK_TIMER);
}

void keyboard_irq_handler(void)
{
	inb(0x60);
	pic_eoi(IRQ_TASK_KBD);
}

void comm2_irq_handler(void)
{
	pic_eoi(IRQ_TASK_COMM2);
}

void comm1_irq_handler(void)
{
	pic_eoi(IRQ_TASK_COMM1);
}

void floppy_irq_handler(void)
{
	pic_eoi(IRQ_TASK_FLOPPY);
}

void lpt1_irq_handler(void)
{
	pic_eoi(IRQ_TASK_LPT1);
}

void clock_irq_handler(void)
{
	pic_eoi(IRQ_TASK_RTC);
}

void cga_irq_handler(void)
{
	pic_eoi(IRQ_TASK_CGA);
}

void ps2_irq_handler(void)
{
	pic_eoi(IRQ_TASK_PS2);
}

void fpu_irq_handler(void)
{
	pic_eoi(IRQ_TASK_FPU);
}

