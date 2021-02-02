#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "memlayout.h"

static void *handle;
struct memregion* after;
int array_size;

void dynamicLoadingExample();

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
    struct memregion* before = (struct memregion*)malloc(array_size * sizeof(struct memregion));
    after = (struct memregion*)malloc(array_size * sizeof(struct memregion));

    printf("========================\n");
    printf("Memory before dynamic load is:\n");

    get_mem_layout(before, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(before[i]);
    }

    dynamicLoadingExample();



    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(after[i]);
    }

    memregion_compare(after, before, array_size);
}

void dynamicLoadingExample() {
    double (*cosine)(double);
    handle = dlopen("/usr/lib32/libm.so", RTLD_LAZY);
    *(void **)(&cosine) = dlsym(handle, "cos");
    printf("%f\n", (*cosine)(0.0));
    get_mem_layout(after, array_size);
    dlclose(handle);
}
