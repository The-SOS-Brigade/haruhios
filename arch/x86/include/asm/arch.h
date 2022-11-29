#ifndef _ASM_X86_ARCH_H
#define _ASM_X86_ARCH_H

#include <haruhi/console.h>
#include <haruhi/types.h>

static inline __attribute__((always_inline)) void printregs(void)
{
	u32 eax, ebx, ecx, edx;
	u32 esi, edi, ebp, esp;
	u32 cr0, cr2, cr3, cr4;
	asm volatile("" : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx));
	printk("EAX: 0x%x EBX: 0x%x ECX: 0x%x EDX: 0x%x\n", eax, ebx, ecx, edx);
	asm volatile("movl %%ebp, %2\n\t"
		     "movl %%esp, %3"
		     : "=S" (esi), "=D" (edi), "=r" (ebp), "=r" (esp) :: "ebp");
	printk("ESI: 0x%x EDI: 0x%x EBP: 0x%x ESP: 0x%x\n", esi, edi, ebp, esp);
	asm volatile("movl %%cr0, %0\n\t"
		     "movl %%cr2, %1\n\t"
		     "movl %%cr3, %2\n\t"
		     "movl %%cr4, %3\n\t"
		     : "=r" (cr0), "=r" (cr2), "=r" (cr3), "=r" (cr4));
	printk("CR0: 0x%x CR2: 0x%x CR3: 0x%x CR4: 0x%x\n", cr0, cr2, cr3, cr4);
}

#endif

