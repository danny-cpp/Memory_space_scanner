#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ftw.h>
#include <unistd.h>
#include <sys/mman.h>
#include "memlayout.h"

void mem_loading(const char* path);

/**
 * In this example, mmap() a large data file and observe the memory changing. Project includes a
 * 300KB json data file as an example. If no argument is provided, the file is default to Tags.json
 * @return
 */
int main(int argc, char *argv[]) {
    const char* path;

    if (argc > 2) {
        printf("Too many arguments!\n");
        exit(-1);
    }
    if (argc == 2)
        path = argv[1];
    else
        path = "Tags.json\0";

    unsigned int array_size = 20;
    struct memregion* before = (struct memregion*)malloc(array_size * sizeof(struct memregion));
    struct memregion* after = (struct memregion*)malloc(array_size * sizeof(struct memregion));


    printf("\nMemory before mmap():\n");
    int status = get_mem_layout(before, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(before[i]);
    }

    printf("\nLoading file \"%s\" to memory\n", path);
    mem_loading(path);

    get_mem_layout(after, array_size);
    for (unsigned int i = 0; i < array_size; i++) {
        print_memregion(after[i]);
    }

    memregion_compare(before, after, array_size);

    // mem_loading();
}

void mem_loading(const char* path) {
    struct stat buffer;

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("Can't open\n");
        exit(1);
    }

    int error = fstat(fd, &buffer);
    if (error < 0) {
        printf("error");
        exit(2);
    }

    char *ptr = mmap(NULL,buffer.st_size,
                     PROT_READ,
                     MAP_SHARED,
                     fd,0);
    if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        return;
    }
    close(fd);

    printf("Successfully mapped!\n");
    printf("====================\n");
}


