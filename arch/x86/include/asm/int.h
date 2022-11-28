#ifndef _ASM_X86_INT_H
#define _ASM_X86_INT_H

#include <asm/gate.h>

static inline void load_idt(struct idtr_desc idtr)
{
	__asm__ __volatile__("lidtl %0" :: "m"(idtr));
}

static inline void enable_interrupts(void)
{
	__asm__ __volatile__("sti");
}

static inline void disable_interrupts(void)
{
	__asm__ __volatile__("cli");
}

void register_int(size_t entry, void *addr, u8 type, u8 dpl);

#endif

