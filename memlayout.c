#include <setjmp.h>
#include <signal.h>
#include "memlayout.h"
#include "stdio.h"

#define DEBUG 1


static const unsigned long mem_space = 0xffffffff;
static const unsigned long page_size = 0x4000;
static sigjmp_buf point;

void SIGSEGV_bypass(int signo, siginfo_t *info, void *context) {
    siglongjmp(point, 1);
    return;
}

int get_mem_layout(struct memregion *regions, unsigned int size) {

    int steps = (int) (mem_space/page_size);
    unsigned volatile char* tracer = 0x00;
    struct sigaction act;

    act.sa_sigaction = SIGSEGV_bypass;
    act.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &act, NULL);

    #if DEBUG
        steps = 100000;
        printf("Pointer is currently at %p\n", tracer);
        // printf("Pointer content is %d\n", *tracer);
    #endif

    int previous_permission = MEM_NO;
    int current_permission = MEM_NO;
    unsigned volatile char* mem_region_entry = tracer;
    for (int i = 0; i < steps; i++) {


        // Attempting to access the data. If no permission -> seg fault.
        if (sigsetjmp(point, 0) == 0) {
            char content = *tracer;

            // Once the reading is successful, we know the page is readable
            current_permission = MEM_RO;
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
            break;
        }

        tracer += page_size;
    }

    printf("Tracer is at %p\n", tracer);

}

