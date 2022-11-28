#include <haruhi/int.h>
#include <asm/gate.h>
#include <asm/int.h>

#define CODE_SEG 0x8

static struct gate_struct idt_gates[IDT_GATES];
extern void int_default(void);

static void register_all_interrupts(void)
{
	size_t i;

	for (i = 0; i < INTEL_TRAPS; ++i)
		register_int(i, int_default, TRAP_GATE, DPL_KERN);

	for (; i < FREE_GATES; ++i)
		register_int(i, int_default, INT_GATE, DPL_KERN);
}

void prepare_gates(void)
{
	for (size_t i = 0; i < IDT_GATES; ++i) {
		idt_gates[i] = (struct gate_struct){
			.offset0 = 0,
			.segment = CODE_SEG,
			.type = TRAP_GATE,
			.dpl = DPL_KERN,
			.p = GATE_ABSENT,
			.offset1 = 0
		};
	}

	register_all_interrupts();

	struct idtr_desc idtr;
	idtr.limit = sizeof(idt_gates) - 1;
	idtr.base = (u32)idt_gates;
	load_idt(idtr);
}

void register_int(size_t entry, void *addr, u8 type, u8 dpl)
{
	idt_gates[entry].offset0 = (u32)addr & 0xFFFF;
	idt_gates[entry].offset1 = (u32)addr >> 16;
	idt_gates[entry].type = type;
	idt_gates[entry].p = GATE_PRESENT;
	idt_gates[entry].dpl = dpl;
}

