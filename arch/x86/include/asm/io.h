#ifndef _ASM_X86_IO_H
#define _ASM_X86_IO_H

#include <haruhi/types.h>

static inline u8 inb(u16 port)
{
	u8 data;
	__asm__ __volatile__("inb %w1, %b0" : "=a" (data) : "dN" (port));
	return data;
}

static inline void outb(u16 port, u8 data)
{
	__asm__ __volatile__("outb %b0, %w1" :: "a" (data), "dN" (port));
}

static inline u16 inw(u16 port)
{
	u16 data;
	__asm__ __volatile__("inw %w1, %w0" : "=a" (data) : "dN" (port));
	return data;
}

static inline void outw(u16 port, u16 data)
{
	__asm__ __volatile__("outw %w0, %w1" :: "a" (data), "dN" (port));
}

static inline void io_wait(void)
{
	__asm__ __volatile__("outb %b0, %1" :: "a"(0), "dN"(0x80));
}

#endif

