#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../src/arraylist.h"

#include "testconstants.h"

void arraylist_add(){
	ArrayList *arrlist = ArrayListNew(3);
  ArrayListAdd(arrlist, (void*) 3);
  ArrayListAdd(arrlist, (void*) 4);
  ArrayListAdd(arrlist, (void*) 5);
  ArrayListAdd(arrlist, (void*) 6);
  ArrayListAdd(arrlist, (void*) 7);
  assert (ArrayListSize(arrlist) == 5);
	printf("%s\n",passed);
}


void arraylist_size(){
	ArrayList *arrlist = ArrayListNew(3);
  ArrayListAdd(arrlist, (void*) 3);
  ArrayListAdd(arrlist, (void*) 4);
  
  assert(ArrayListSize(arrlist) == 2);

  ArrayListAdd(arrlist, (void*) 5);
  ArrayListAdd(arrlist, (void*) 6);
  ArrayListAdd(arrlist, (void*) 7);
  ArrayListAdd(arrlist, (void*) 8);
  ArrayListAdd(arrlist, (void*) 9);
  ArrayListAdd(arrlist, (void*) 10);

  assert(ArrayListSize(arrlist) == 8);

	printf("%s\n",passed);
}


void arraylist_get(){
	ArrayList *arrlist = ArrayListNew(3);
  ArrayListAdd(arrlist, (void*) 3);
  ArrayListAdd(arrlist, (void*) 4);
  ArrayListAdd(arrlist, (void*) 5);
  ArrayListAdd(arrlist, (void*) 6);
  ArrayListAdd(arrlist, (void*) 7);
  ArrayListAdd(arrlist, (void*) 8);
  ArrayListAdd(arrlist, (void*) 9);
  ArrayListAdd(arrlist, (void*) 10);
  

  assert (ArrayListGet(arrlist, 0) == (void*)3);
  assert (ArrayListGet(arrlist, 1) == (void*)4);
  assert (ArrayListGet(arrlist, 2) == (void*)5);
  assert (ArrayListGet(arrlist, 3) == (void*)6);
  assert (ArrayListGet(arrlist, 4) == (void*)7);
  assert (ArrayListGet(arrlist, 5) == (void*)8);
  assert (ArrayListGet(arrlist, 6) == (void*)9);
  assert (ArrayListGet(arrlist, 7) == (void*)10);
  

	printf("%s\n",passed);
}


int main(int argc, char **argv){
	puts("ArrayList test: ");
	arraylist_add();
  arraylist_size();
	arraylist_get();
	return 0;
}