#include <stdio.h>
#include <stdlib.h>
#include "memlayout.h"

unsigned long long fibonacci(unsigned long long upto) {
    if (upto == 0)
        return 0;
    if (upto == 1)
        return 1;
    return (fibonacci(upto - 1) + fibonacci(upto - 2));
}

/**
 * In this example, we will consider the recursive call. The memory map will be different before and after
 * the Fibonacci call and after.
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
    // struct memregion results[array_size];

    /**
     * Using this part for array_size >= 20;
     */
    struct memregion* results = (struct memregion*)malloc(array_size * sizeof(struct memregion));

    unsigned long long upto = 5;
    unsigned long long result = fibonacci(upto);
    printf("Result of fibonacci %llu is %llu", upto, result);

    // int status = get_mem_layout(results, array_size);
    // for (unsigned int i = 0; i < array_size; i++) {
    //     print_memregion(results[i]);
    // }
    //
    // printf("\nMemory after massive malloc:\n");
    //
    // int* d = (int*)malloc(1000000*sizeof(int));
    // for (unsigned long i = 0; i < 1000000; i++) {
    //     d[i] = 1;
    // }
    //
    //
    // get_mem_layout(results, array_size);
    // for (unsigned int i = 0; i < array_size; i++) {
    //     print_memregion(results[i]);
    // }

}
