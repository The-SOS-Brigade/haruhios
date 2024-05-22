#ifndef _ASM_X86_MEMORY_H
#define _ASM_X86_MEMORY_H

#include <haruhi/types.h>

extern u32 __kheap_start;

#define CONFIG_KHEAP_BASE &__kheap_start
//__kheap_start
#define CONFIG_KHEAP_ENTRIES 25600
#define CONFIG_KHEAP_BLOCK_SIZE 4096

#endif
