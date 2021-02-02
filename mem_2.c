#include <stdio.h>
#include <stdlib.h>
#include "memlayout.h"


static struct memregion* result_array;
static unsigned int array_size;
static struct memregion* recursion_array;

int recursionExample(int upto) {
    if (upto == 0) {
        printf("\nRecursive call reached base case!!\n");
        printf("Current memory map is:\n");
        // get_mem_layout(recursion_array, array_size);
        //
        // for (unsigned int i = 0; i < array_size; i++) {
        //     print_memregion(recursion_array[i]);
        // }

        return -1;
    }
    int a[10000];


    // printf("Current upto is %d\n", upto);
    return recursionExample(upto - 1);
}

/**
 * In this example, we will consider the recursive call. The memory map before will be
 * different from after the recursion call
 * @return
 */
int main() {

    array_size = 20;
    result_array = (struct memregion*)malloc(array_size * sizeof(struct memregion));
    recursion_array = (struct memregion*)malloc(array_size * sizeof(struct memregion));

    printf("\nMalloc Successfully\n");
    printf("========================\n");
    printf("Memory before recursion is:\n");
    get_mem_layout(result_array, array_size);

    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(result_array[i]);
    }

    int upto = 10;
    // int result = recursionExample(upto);

    {
        int a[10000];
        for (int i = 0; i < 10000; ++i) {
            a[i] = 10;
        }
        printf("\nRescan attempt\n");
        get_mem_layout(recursion_array, array_size);
    }

    memregion_compare( recursion_array, result_array, array_size);

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
