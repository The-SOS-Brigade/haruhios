#include <haruhi/canary.h>
#include <haruhi/types.h>
#include <haruhi/panic.h>

#ifndef _STACK_CANARY
# define _STACK_CANARY 0x422A4221
#endif

uintptr_t __stack_chk_guard = _STACK_CANARY;

__attribute__((noreturn)) void __stack_chk_fail(void)
{
	panic("stack canary overwritten");
}

