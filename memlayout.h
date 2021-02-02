#pragma once
#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2

#ifndef USER_PAGE_SIZE
#define USER_PAGE_SIZE 4096
#endif

struct memregion {
	void *from;
	void *to;
	unsigned char mode; /* MEM_RW, or MEM_RO, or MEM_NO */
};

/**
 * Scanning the process space of a 32-bit process (spanning from 0x0 to 0xffffffff). The result is of contiguous
 * access permission regions will be marked (from address -> to address). Results will be stored in @param regions
 * array, which has its size predetermined as input @param size.
 * @param regions A pointer that will be used to store memregions
 * @param size array size
 * @return: 0 for a full array,
 *          -1 for not-full array,
 *          -2 for size 0 array.
 */
int get_mem_layout (struct memregion *regions, unsigned int size);

void print_memregion(struct memregion region);

void memregion_compare(struct memregion *region1, struct memregion *region2, int len);