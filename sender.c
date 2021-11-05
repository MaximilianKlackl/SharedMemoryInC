#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "protocol.h"

int main() {

    int fd;
    void* addr;

    // create shared memory
    fd = shm_open(NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd == -1){
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // allocate size
    if (ftruncate(fd, SIZE) == -1){
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // map shared address space to process one
    addr = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    if(addr == MAP_FAILED){
        perror("mmap");
    }

    // copy to shared address space
    memcpy(addr, TEXT, SIZE);
    printf("Send data from process with pid: %d\n", getpid());

    // wait for someone to read
    sleep(2);

    // clear shared memory
    fd = munmap(addr, SIZE);

    if (fd == -1)
    {
        perror("munmap");
        return EXIT_FAILURE;
    }

    // unlink
    fd = shm_unlink(NAME);

    if (fd == -1)
    {
        perror("unlink");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
