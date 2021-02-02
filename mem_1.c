#include <stdio.h>
#include <stdlib.h>
#include "memlayout.h"

/**
 * In this example, we comparing the effect of malloc. The memory map will be different before and after
 * 1,000,000 int allocation and initialization.
 * @author: Danh Nguyen
 * @return
 */
int main() {
    /**
     * Allocation an memregion struct array on heap have been tested and needs to be
     * strictly less than 20!!!!
     *
     * For bigger array please use the other commented block to construct it on the heap
     */
    unsigned int array_size = 20;

    printf("Memory before massive malloc:\n");
    // struct memregion after[array_size];

    /**
     * Using this part for array_size >= 20;
     */
    struct memregion* after = (struct memregion*)malloc(array_size * sizeof(struct memregion));
    struct memregion* before = (struct memregion*)malloc(array_size * sizeof(struct memregion));


    int status = get_mem_layout(before, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(before[i]);
    }

    printf("\nMemory after massive malloc:\n");

    int* d = (int*)malloc(1000000*sizeof(int));
    for (unsigned long i = 0; i < 1000000; i++) {
        d[i] = 1;
    }


    get_mem_layout(after, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(after[i]);
    }

    memregion_compare(before, after, array_size);
}


