#ifndef FMEMORY_H
#define FMEMORY_H

#include <stdlib.h>


typedef struct FuzuliMemoryUsage {
    unsigned int totalAllocated;
    unsigned int totalFreed;
}FuzuliMemoryUsage;



void* fmalloc (unsigned int size);
void ffree (void *pointer);
unsigned int FuzuliMemoryGetAllocated();
unsigned int FuzuliMemoryGetFreed();

#endif
