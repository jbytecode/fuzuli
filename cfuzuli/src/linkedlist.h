#ifndef LINKED_LIST_H
#define LINKED_LIST_H


struct _LinkedListElement;
struct _LinkedList;

typedef struct _LinkedListElement{
    void *value;
    struct _LinkedListElement *next;
} LinkedListElement;


typedef struct _LinkedList {
    struct _LinkedListElement *first;
} LinkedList;



LinkedList *LinkedListNew();
unsigned int LinkedListLength(LinkedList *list);
void* LinkedListGet(LinkedList *list, unsigned int index);
LinkedListElement* LinkedListGetCore(LinkedList *list, unsigned int index);
void LinkedListAdd(LinkedList *list, void *value);
void LinkedListPrepend(LinkedList *list, void *value);
void LinkedListRemove(LinkedList *list, unsigned int index);

#endif
