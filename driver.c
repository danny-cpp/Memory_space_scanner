#include <stdio.h>
#include <stdlib.h>
#include "memlayout.h"


int main() {
    /**
     * Allocation an memregion struct array on heap have been tested and needs to be
     * strictly less than 20!!!!
     *
     * For bigger array please use the other commented block to construct it on the heap
     */
    unsigned int array_size = 17;

    printf("Memory before massive malloc:\n");
    // struct memregion results[array_size];

    /**
     * Uncomment this part for array_size >= 20;
     */
    struct memregion* results = (struct memregion*)malloc(array_size * sizeof(struct memregion));

    int status = get_mem_layout(results, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(results[i]);
    }

    printf("\nMemory after massive malloc:\n");

    int* d = (int*)malloc(1000000*sizeof(int));
    for (unsigned long i = 0; i < 1000000; i++) {
        d[i] = 1;
    }


    get_mem_layout(results, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(results[i]);
    }

}


