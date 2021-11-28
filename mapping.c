#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char *realStartAddr;
    char *startAddr;
    int startOffset;
    int size;
    int realSize;
    int fd;
} MemMap_t;

void *InitMemRegion(int physicalAddr, int size)
{
    MemMap_t *map = NULL;
    int realStartAddr = physicalAddr / sysconf(_SC_PAGE_SIZE) *
                        sysconf(_SC_PAGE_SIZE);
    map = (MemMap_t *)malloc(sizeof(MemMap_t));
    map->fd = open("/dev/mem", O_RDWR | O_SYNC);
    map->realSize = size + physicalAddr - realStartAddr;
    map->realStartAddr = (char *)mmap(
        NULL,
        map->realSize,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        map->fd,
        realStartAddr);
    map->startAddr = (char *)((int)map->realStartAddr+physicalAddr-realStartAddr);

    return (void *)map;
}
