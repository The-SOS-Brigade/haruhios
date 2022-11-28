#include <haruhi/memory/kheap.h>
#include <haruhi/string.h>
#include <haruhi/panic.h>

struct heap_alloc_desc kheap;

void kheap_init(void)
{
	kheap.blk_size = CONFIG_KHEAP_BLOCK_SIZE;
	kheap.total_entries = CONFIG_KHEAP_ENTRIES;
	kheap.base = (void *)CONFIG_KHEAP_BASE;
	kheap.blk = (u8 *)0x1401000;

	for (size_t i = 0; i < kheap.total_entries; ++i)
		kheap.blk[i] = HEAP_BLOCK_FREE;
}

void *kmalloc(size_t size)
{
	return malloc(&kheap, size);
}

void *kzalloc(size_t size)
{
	void *ptr;
	ptr = malloc(&kheap, size);

	if (!ptr)
		return NULL;

	memset(ptr, 0, size);
	return ptr;
}

void kfree(void *ptr)
{
	if (free(&kheap, ptr) < 0)
		panic("kfree");
}

