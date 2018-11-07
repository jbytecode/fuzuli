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


void ArrayListAdd(ArrayList *arraylist, void *element){
  if(arraylist->currentSize == arraylist->maximumSize){
    arraylist->elements = realloc(arraylist->elements, arraylist->maximumSize * 2 * sizeof(void*));
    arraylist->maximumSize *= 2;
  }
  arraylist->elements[arraylist->currentSize] = element;
  arraylist->currentSize++;
}


void ArrayListPrepend(ArrayList *arraylist, void *element){
	if(arraylist->currentSize == arraylist->maximumSize){
		arraylist->elements = realloc(arraylist->elements, arraylist->maximumSize * 2 * sizeof(void*));
		arraylist->maximumSize *= 2;
	}
	unsigned int lastindex = arraylist->currentSize;
	for (unsigned int i = lastindex; i >= 1; i--){
		arraylist->elements[i] = arraylist->elements[i-1];
	}
	arraylist->elements[0] = element;
	arraylist->currentSize++;
}

void *ArrayListGet(ArrayList *arraylist, unsigned int index){
  return arraylist->elements[index];
}

unsigned int ArrayListSize(ArrayList *arrlist){
  return arrlist->currentSize;
}

