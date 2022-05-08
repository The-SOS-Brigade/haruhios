#ifndef _HARUHI_CANARY_H
#define _HARUHI_CANARY_H

#include <haruhi/types.h>

extern uintptr_t __stack_chk_guard;

__attribute__((always_inline)) void inline load_canary(void)
{
	__stack_chk_guard = *(u32 *)0x500;
}

#endif

