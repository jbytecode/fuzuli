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
void LinkedListAdd(LinkedList *list, void *value);

#endif
