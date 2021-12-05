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

#define _TASK(n) (INTEL_TRAPS + n), irq_task##n, INT_GATE

void interrupt_init(void)
{
	prepare_gates();
	pic_remap(INTEL_TRAPS, INTEL_TRAPS+8);
	register_int(_TASK(0));
	register_int(_TASK(1));
	register_int(_TASK(3));
	register_int(_TASK(4));
	register_int(_TASK(6));
	register_int(_TASK(7));
	register_int(_TASK(8));
	register_int(_TASK(9));
	register_int(_TASK(12));
	register_int(_TASK(13));
	enable_interrupts();
}

