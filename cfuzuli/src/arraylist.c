#include "arraylist.h"

ArrayList *ArrayListNew(unsigned int initialSize){
  ArrayList *arrlist = (ArrayList*) fmalloc(sizeof(ArrayList));
  arrlist->elements = (void**) fmalloc(sizeof(void*) * initialSize);
  arrlist->currentSize = 0;
  arrlist->maximumSize = initialSize;
  return arrlist;
}

void ArrayListFree(ArrayList *arrlist){
  ffree(arrlist->elements);
  ffree(arrlist);
}


void *ArrayListAdd(ArrayList *arraylist, void *element){
  if(arraylist->currentSize == arraylist->maximumSize){
    arraylist->elements = realloc(arraylist->elements, arraylist->maximumSize * 2 * sizeof(void*));
    arraylist->maximumSize *= 2;
  }
  arraylist->elements[arraylist->currentSize] = element;
  arraylist->currentSize++;
}


void *ArrayListGet(ArrayList *arraylist, unsigned int index){
  return arraylist->elements[index];
}

unsigned int ArrayListSize(ArrayList *arrlist){
  return arrlist->currentSize;
}

