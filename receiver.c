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
    char data[SIZE];

    // open shared memory
    fd = shm_open(NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd == -1){
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // get address of shared memory
    addr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0);

    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return EXIT_FAILURE;
    }

    // copy from shared memory
    memcpy(data, addr, SIZE);

    printf("Received data from process with pid: %d\n%s", getpid(),data);

    return EXIT_SUCCESS;
}
