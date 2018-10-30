#include <stdio.h>
#include <assert.h>
#include "../src/linkedlist.h"
#include "../src/constants.h"
#include "../src/fuzulitypes.h"
#include "testconstants.h"

void linkedlist_new_test1(){
	LinkedList *list = LinkedListNew();
	assert(list != NULL);
	printf("%s\n",passed);
}

void linkedlist_add_double_test1(){
	LinkedList *list = LinkedListNew();
	LinkedListAdd(list, FuzuliValueCreateDouble(1.0));
	assert(LinkedListLength(list) == 1);
	printf("%s\n",passed);
}

void linkedlist_add_doubles_test1(){
	LinkedList *list = LinkedListNew();
	LinkedListAdd(list, FuzuliValueCreateDouble(1.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(2.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(3.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(4.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(5.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(6.0));
	assert(LinkedListLength(list) == 6);
	printf("%s\n",passed);
}

void linkedlist_get_double_test1(){
	LinkedList *list = LinkedListNew();
	LinkedListAdd(list, FuzuliValueCreateDouble(10.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(20.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(30.0));
	FuzuliValue *val = (FuzuliValue*)LinkedListGet(list, 2);
	FuzuliValue *val2 = (FuzuliValue*)LinkedListGet(list, 1);
	assert( val->dvalue == 30.0 && val2->dvalue == 20.0);
	printf("%s\n",passed);
}

void linkedlist_prepend_double_test1(){
	LinkedList *list = LinkedListNew();
	LinkedListAdd(list, FuzuliValueCreateDouble(10.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(20.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(30.0));
	
	LinkedListPrepend(list, FuzuliValueCreateDouble(40.0));
	FuzuliValue *val = LinkedListGet(list, 0);
	assert(val->dvalue == 40);

	LinkedListPrepend(list, FuzuliValueCreateDouble(50.0));
	FuzuliValue *val2 = LinkedListGet(list, 0);
	assert(val2->dvalue == 50);

	assert(LinkedListLength(list) == 5);

	printf("%s\n",passed);
}

void linkedlist_remove_double_test1(){
	LinkedList *list = LinkedListNew();
	LinkedListAdd(list, FuzuliValueCreateDouble(10.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(20.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(30.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(40.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(50.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(60.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(70.0));
	
	LinkedListRemove(list, 2);
	assert(LinkedListLength(list) == 6);

	FuzuliValue *val1 = LinkedListGet(list, 2);
	assert(val1->dvalue == 40.0);
	printf("%s\n",passed);
}

void linkedlist_remove_add_again1(){
	LinkedList *list = LinkedListNew();
	LinkedListAdd(list, FuzuliValueCreateDouble(10.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(20.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(30.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(40.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(50.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(60.0));
	LinkedListAdd(list, FuzuliValueCreateDouble(70.0));	
	
	LinkedListRemove(list, 6);
	
	LinkedListAdd(list, FuzuliValueCreateDouble(100.0));
	FuzuliValue *val = LinkedListGet(list, 6);
	assert (val->dvalue == 100.0);

	printf("%s\n",passed);
}


int main(int argc, char **argv){
	puts("LinkedList test: ");
	linkedlist_new_test1();
	linkedlist_add_double_test1();	
	linkedlist_add_doubles_test1();	
	linkedlist_get_double_test1();	
	linkedlist_prepend_double_test1();
	linkedlist_remove_double_test1();
	linkedlist_remove_add_again1();
	return 0;
}

