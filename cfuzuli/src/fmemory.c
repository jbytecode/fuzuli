#include <stdio.h>
#include "fmemory.h"

#ifndef memoryUsageStatsDef
#define memoryUsageStatsDef
static FuzuliMemoryUsage memoryUsageStats;
#endif


void* fmalloc (unsigned int size){
    memoryUsageStats.totalAllocated += size;
    return malloc(size);
}

void ffree (void *pointer){
    memoryUsageStats.totalFreed += sizeof(pointer);
    free(pointer);
    pointer = NULL;
}

unsigned int FuzuliMemoryGetAllocated(){
    return memoryUsageStats.totalAllocated;
}

unsigned int FuzuliMemoryGetFreed(){
    return memoryUsageStats.totalFreed;
}

