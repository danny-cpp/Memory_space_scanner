#include <setjmp.h>
#include <signal.h>
#include "memlayout.h"
#include "stdio.h"

#define DEBUG 1


static const unsigned long mem_space = 0xffffffff;
static const unsigned long page_size = 0x4000;
static sigjmp_buf point;
static sigjmp_buf point2;

void NO_ACCESS_bypass(int signo, siginfo_t *info, void *context) {
    siglongjmp(point, 1);
    return;
}

int get_mem_layout(struct memregion *regions, unsigned int size) {

    unsigned long steps = mem_space/page_size;
    unsigned volatile char* tracer = 0x00; // 0x911c000
    struct sigaction act;


    act.sa_sigaction = NO_ACCESS_bypass;
    act.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &act, NULL);


    #if DEBUG
        steps = 1048576;
        printf("Pointer is currently at %p\n", tracer);
        // printf("Pointer content is %d\n", *tracer);
    #endif

    int previous_permission = MEM_NO;
    int current_permission = previous_permission;
    unsigned volatile char* mem_region_entry = tracer;
    for (unsigned long i = 0; i < steps; i++) {


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
            // printf("No accessible memregion\n");
            current_permission = MEM_NO;
            // break;
        }

        // This dictates a region ends
        if (current_permission != previous_permission) {
            // First we construct a mem_region object
            struct memregion tmp = {mem_region_entry, tracer - 1, previous_permission};
            printf("The memregion spans from %p to %p with permission %d\n", tmp.from,
                   tmp.to, tmp.mode);
            // break;

            previous_permission = current_permission;
            mem_region_entry = tracer;
        }

        tracer += page_size;
    }

    tracer -= 1;
    printf("Tracer is at %p\n", tracer);

}

