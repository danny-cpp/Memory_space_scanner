#include <stdio.h>
#include <stdlib.h>
#include "memlayout.h"

int main() {
    unsigned int array_size = 10;

    printf("Memory before massive malloc:\n");
    struct memregion results[array_size];

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


