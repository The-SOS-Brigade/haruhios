#ifndef _HARUHI_MEMORY_KHEAP_H
#define _HARUHI_MEMORY_KHEAP_H

#include <haruhi/memory/heap.h>
#include <asm/memory.h>

#ifndef CONFIG_KHEAP_BLOCK_SIZE
# define CONFIG_KHEAP_BLOCK_SIZE 4096
#endif

extern struct heap_alloc_desc kheap;

void kheap_init(void);
void *kmalloc(size_t size);
void *kzalloc(size_t size);
void kfree(void *ptr);

#endif
