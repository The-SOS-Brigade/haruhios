#include <haruhi/memory/heap.h>

static size_t heap_get_blk_offset(struct heap_alloc_desc *heap, void *ptr)
{
	size_t offset = (ptr - heap->base) / heap->blk_size;

	if (offset > heap->total_entries)
		return -1;

	return offset;
}

void *malloc(struct heap_alloc_desc *heap, size_t size)
{
	size_t blocks;
	void *ptr = NULL;

	size += heap->blk_size - (size % heap->blk_size);
	blocks = size / heap->blk_size;

	if (!blocks)
		return NULL;

	size_t i;

	for (i = 0; i < heap->total_entries; ++i) {
		size_t j;

		for (j = 0; j < blocks; ++j) {
			if (heap->blk[i+j] & HEAP_BLOCK_USED) {
				i += j;
				break;
			}
		}

		if (j == blocks) {
			ptr = (void *)(heap->base + heap->blk_size * i);
			break;
		}
	}

	size_t blk_offset = i;
	u8 attr = HEAP_BLOCK_START | HEAP_BLOCK_USED;

	for (; i < blk_offset + blocks; ++i) {
		heap->blk[i] = attr;
		attr = HEAP_BLOCK_USED;
	}

	heap->blk[i-1] |= HEAP_BLOCK_END;

	return ptr;
}

void free(struct heap_alloc_desc *heap, void *ptr)
{
	const size_t blk_start = heap_get_blk_offset(heap, ptr);
	size_t i = blk_start;
	u8 blk;

	do {
		blk = heap->blk[i];
		heap->blk[i] = HEAP_BLOCK_FREE;
	} while (~blk & HEAP_BLOCK_END);
}

