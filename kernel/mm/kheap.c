#include <haruhi/memory/kheap.h>

struct heap_alloc_desc kheap;

void kheap_init(void)
{
	kheap.blk_size = CONFIG_KHEAP_BLOCK_SIZE;
	kheap.total_entries = CONFIG_KHEAP_ENTRIES;
	kheap.base = (void *)CONFIG_KHEAP_BASE;

	for (size_t i = 0; i < kheap.total_entries; ++i)
		kheap.blk[i] = HEAP_BLOCK_FREE;
}

void *kmalloc(size_t size)
{
	return malloc(&kheap, size);
}

void kfree(void *ptr)
{
	return free(&kheap, ptr);
}

