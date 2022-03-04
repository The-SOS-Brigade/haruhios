#include <haruhi/memory/heap.h>

static size_t heap_get_blk_offset(struct heap_alloc_desc *heap, void *ptr)
{
	size_t offset = (ptr - heap->base) / heap->blk_size;

	if (offset >= heap->total_entries)
		return -1;

	return offset;
}

static void alloc_blocks(struct heap_alloc_desc *h, size_t offset, size_t n)
{
	u8 attr = HEAP_BLOCK_START | HEAP_BLOCK_USED;

	size_t i = offset;

	for (; i < n + offset; ++i) {
		h->blk[i] = attr;
		attr = HEAP_BLOCK_USED;
	}

	h->blk[i-1] |= HEAP_BLOCK_END;

}

void *malloc(struct heap_alloc_desc *heap, size_t size)
{
	size_t blocks;
	void *ptr = NULL;

	if (size % heap->blk_size)
		size += heap->blk_size - (size % heap->blk_size);

	blocks = size / heap->blk_size;

	if (!blocks || blocks >= heap->total_entries)
		return NULL;

	size_t i;

	for (i = 0; i < heap->total_entries - blocks; ++i) {
		size_t j;

		for (j = 0; j < blocks; ++j) {
			if (heap->blk[i+j] & HEAP_BLOCK_USED) {
				i += j;
				break;
			}
		}

		if (j == blocks) {
			alloc_blocks(heap, i, blocks);
			ptr = (void *)(heap->base + heap->blk_size * i);
			break;
		}
	}

	return ptr;
}

void free(struct heap_alloc_desc *heap, void *ptr)
{
	size_t blk_start;

	do {
		blk_start = heap_get_blk_offset(heap, ptr);
		ptr -= heap->blk_size;
	} while (~heap->blk[blk_start] & HEAP_BLOCK_START);

	size_t i = blk_start;
	u8 blk;

	do {
		blk = heap->blk[i];
		heap->blk[i++] = HEAP_BLOCK_FREE;
	} while (~blk & HEAP_BLOCK_END);
}

