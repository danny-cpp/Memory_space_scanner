#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "memlayout.h"

static void *handle;
struct memregion* after;
int array_size;

/**
 * Dynamically loaded library. This causes memory layout to be altered at run time
 */
void dynamicLoadingExample();

/**
 * In this example, we will consider dynamic load. The memory map before will be
 * different from after the dynamic loading
 * @author: Danh Nguyen
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

/**
 * Code snippet in courtesy of Lab3 - Memory Mapped Files, CMPUT 379, University of Alberta,
 * Winter 2021.
 * @authors: Matt Gallivan and Yan Wang
 */
void dynamicLoadingExample() {
    double (*cosine)(double);
    handle = dlopen("/usr/lib32/libm.so", RTLD_LAZY);
    *(void **)(&cosine) = dlsym(handle, "cos");
    printf("%f\n", (*cosine)(0.0));
    get_mem_layout(after, array_size);
    dlclose(handle);
}
