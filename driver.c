#include <stdio.h>
#include "memlayout.h"

int main() {
    printf("Hi\n");
    struct memregion results[20];
    int status = get_mem_layout(results, 20);

    for (unsigned int i = 0; i < 20; i++) {
        print_memregion(results[i]);
    }
}


