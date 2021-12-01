#include <asm/gate.h>
#include <asm/int.h>

#define INTEL_TRAPS 0x20
#define FREE_GATES (IDT_GATES - INTEL_TRAPS)

#define CODE_SEG 0x8

static struct gate_struct idt_gates[IDT_GATES];
extern void int_default(void);

static void register_all_interrupts(void)
{
	size_t i;

	for (i = 0; i < INTEL_TRAPS; ++i)
		register_int(i, int_default, TRAP_GATE);

	for (; i < FREE_GATES; ++i)
		register_int(i, int_default, INT_GATE);
}

void interrupt_init(void)
{
	for (size_t i = 0; i < IDT_GATES; ++i) {
		idt_gates[i] = (struct gate_struct){
			.offset0 = 0,
			.segment = CODE_SEG,
			.type = TRAP_GATE,
			.dpl = 3,
			.p = GATE_ABSENT,
			.offset1 = 0
		};
	}

	register_all_interrupts();

	struct idtr_desc idtr;
	idtr.limit = sizeof(idt_gates) - 1;
	idtr.base = (u32)idt_gates;

	load_idt(idtr);
	enable_interrupts();
}

void register_int(size_t entry, void *addr, u8 type)
{
	idt_gates[entry].offset0 = (u32)addr & 0xFFFF;
	idt_gates[entry].offset1 = (u32)addr >> 16;
	idt_gates[entry].type = type;
	idt_gates[entry].p = GATE_PRESENT;
}

