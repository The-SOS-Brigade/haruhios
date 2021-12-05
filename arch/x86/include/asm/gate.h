#ifndef _ASM_X86_GATE_H
#define _ASM_X86_GATE_H

#include <haruhi/types.h>

#define TASK_GATE	0b0101
#define INT_GATE	0b1110
#define TRAP_GATE	0b1111

#define GATE_ABSENT	0b0
#define GATE_PRESENT	0b1

#define IDT_GATES	0x100

#define INTEL_TRAPS 0x20
#define FREE_GATES (IDT_GATES - INTEL_TRAPS)

struct gate_struct {
	u16 offset0;
	u16 segment;
	u8 reserved;
	u8 type	: 5;
	u8 dpl	: 2;
	u8 p	: 1;
	u16 offset1;
} __attribute__((packed));

struct idtr_desc {
	u16 limit;
	u32 base;
} __attribute__((packed));

void prepare_gates(void);

#endif

