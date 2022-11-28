#include <asm/syscall.h>
#include <asm/gate.h>
#include <asm/pic.h>
#include <asm/int.h>

extern void irq_task0(void);
extern void irq_task1(void);
extern void irq_task3(void);
extern void irq_task4(void);
extern void irq_task6(void);
extern void irq_task7(void);
extern void irq_task8(void);
extern void irq_task9(void);
extern void irq_task12(void);
extern void irq_task13(void);
extern void int_syscall(void);

#define _IRQ(n) (INTEL_TRAPS + n), irq_task##n, INT_GATE, 0

void interrupt_init(void)
{
	prepare_gates();
	pic_remap(INTEL_TRAPS, INTEL_TRAPS+8);
	pic_clear_all_masks();
	register_int(_IRQ(0));
	register_int(_IRQ(1));
	register_int(_IRQ(3));
	register_int(_IRQ(4));
	register_int(_IRQ(6));
	register_int(_IRQ(7));
	register_int(_IRQ(8));
	register_int(_IRQ(9));
	register_int(_IRQ(12));
	register_int(_IRQ(13));
	register_int(INT_SYSCALL, int_syscall, TRAP_GATE, DPL_USER);
	enable_interrupts();
}

