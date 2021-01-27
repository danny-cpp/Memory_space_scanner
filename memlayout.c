#include "memlayout.h"
#include "stdio.h"

static const unsigned long mem_space = 0xffffffff;
static const unsigned long page_size = 0x4000;

int get_mem_layout(struct memregion *regions, unsigned int size) {

    const int steps = (int) (mem_space/page_size);
    unsigned volatile char* tracer = (unsigned char*) 0x00;

    for (int i = 0; i < steps; i++) {
        tracer += page_size;
    }

    printf("Tracer is at %p\n", tracer);
}
