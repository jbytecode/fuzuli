#include <stdio.h>
#include "fmemory.h"

#ifndef memoryUsageStatsDef
#define memoryUsageStatsDef
static FuzuliMemoryUsage memoryUsageStats;
#endif


void* fmalloc (unsigned int size){
    memoryUsageStats.totalAllocated += 1;
    return malloc(size);
}

void ffree (void *pointer){
    if(pointer){
        memoryUsageStats.totalFreed += 1;
        free(pointer);
        pointer = NULL;
    }
}

unsigned int FuzuliMemoryGetAllocated(){
    return memoryUsageStats.totalAllocated;
}

unsigned int FuzuliMemoryGetFreed(){
    return memoryUsageStats.totalFreed;
}

