#include <setjmp.h>
#include <signal.h>
#include "memlayout.h"
#include "stdio.h"

#define DEBUG 0


static const unsigned long long mem_space = 1ULL<<32;
static const unsigned long long page_size = 4096;
static sigjmp_buf point;

void NO_ACCESS_bypass(int signo, siginfo_t *info, void *context);

int get_mem_layout(struct memregion *regions, unsigned int size) {

    if (size == 0)
        return -2;

    unsigned int counter = 0;

    unsigned long steps = mem_space/page_size;
    // printf("Steps are %d\n", steps);
    unsigned volatile char* tracer = 0x00; // 0x911c000
    struct sigaction act;

    act.sa_sigaction = NO_ACCESS_bypass;
    act.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGBUS, &act, NULL);

    #if DEBUG
        steps = 1048576;
        printf("Pointer is currently at %p\n", tracer);
        // printf("Pointer content is %d\n", *tracer);
    #endif

    int previous_permission = MEM_NO;
    int current_permission = previous_permission;
    unsigned volatile char* mem_region_entry = tracer;
    for (unsigned long i = 0; i <= steps; i++) {


        // Attempting to access the data. If no permission -> seg fault.
        if (sigsetjmp(point, 0) == 0) {
            char content = *tracer;

            // Once the reading is successful, we know the page is readable (write is still unknown)
            current_permission = MEM_RO;

            // Attempting to write to the data. If no permission -> seg fault
            if (sigsetjmp(point, 0) == 0) {
                tracer[0] = content;

                // If the upper successfully wrote back the data, this block is RW
                current_permission = MEM_RW;
            }
            else {
                // If not, it is read-only, but we already set that above
            }
        }
        else {
            current_permission = MEM_NO;
        }

        // This dictates a region ends
        if (current_permission != previous_permission) {
            // First we construct a mem_region object
            struct memregion tmp = {mem_region_entry, tracer - 1, previous_permission};

            #if DEBUG
                printf("The memregion spans from %p to %p with permission %d\n", tmp.from,
                        tmp.to, tmp.mode);
            #endif

            // Store it to the array
            regions[counter] = tmp;
            counter++;
            if (counter == size) {
                return 0;
            }

            previous_permission = current_permission;
            mem_region_entry = tracer;
        }

        tracer += page_size;

    }

    // To test the last region (from ??? -> 0xffffffff) we have to check explicitly, since
    // the loop causes out of bound memory (2^32 instead 2^32 -1)
    // Attempting to access the data. If no permission -> seg fault.
    tracer = 0xffffffff;


    struct memregion tmp = {mem_region_entry, tracer, previous_permission};
    regions[counter] = tmp;
    counter++;


    #if DEBUG
        printf("The memregion spans from %p to %p with permission %d\n", tmp.from,
               tmp.to, tmp.mode);
        printf("Tracer is at %p\n", tracer);
        printf("Last mem entry was %p\n", mem_region_entry);
    #endif

    if (counter == size)
        return 0;
    else
        return -1;
}

void NO_ACCESS_bypass(int signo, siginfo_t *info, void *context) {
    siglongjmp(point, 1);
}

void print_memregion(struct memregion region) {
    printf("%p-%p ", region.from, region.to);
    if (region.mode == 0) {
        printf(" RW\n");
    }
    else if (region.mode == 1) {
        printf(" RO\n");
    }
    else {
        printf(" NO\n");
    }
}