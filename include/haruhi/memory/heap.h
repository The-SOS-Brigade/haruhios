#ifndef _HARUHI_MEMORY_HEAP_H
#define _HARUHI_MEMORY_HEAP_H

#include <haruhi/types.h>

#define HEAP_BLOCK_FREE		0b00000000
#define HEAP_BLOCK_USED		0b00000001
#define HEAP_BLOCK_START	0b00000010
#define HEAP_BLOCK_END		0b00000100
#define HEAP_BLOCK_RESERVED	0b00001000
#define HEAP_BLOCK_FLAGS	0b11110000

struct heap_alloc_desc {
	size_t blk_size;
	size_t total_entries;
	void *base;
	u8 *blk;
};

void *malloc(struct heap_alloc_desc *heap, size_t size);
void free(struct heap_alloc_desc *heap, void *ptr);

#endif

