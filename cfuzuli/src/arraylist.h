#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "fmemory.h"

typedef struct ARRAYLIST {
  void **elements;
  unsigned int currentSize;
  unsigned int maximumSize;
} ArrayList;

ArrayList *ArrayListNew(unsigned int initialSize);
void ArrayListFree(ArrayList *arrlist);
void *ArrayListAdd(ArrayList *arraylist, void *element);
void *ArrayListGet(ArrayList *arraylist, unsigned int index);
unsigned int ArrayListSize(ArrayList *arrlist);

#endif