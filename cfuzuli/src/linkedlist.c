#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "linkedlist.h"
#include "fuzulitypes.h"
#include "token.h"
#include "fmemory.h"

LinkedList *LinkedListNew() {
    LinkedList *list = (LinkedList*) fmalloc(sizeof (LinkedList));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return (list);
}

void LinkedListAdd(LinkedList *list, void *value) {
    LinkedListElement *parent, *child;
    LinkedListElement *element = list->first;
    if (element == NULL) {
        element = (LinkedListElement*) fmalloc(sizeof (LinkedListElement));
        element->value = value;
        element->next = NULL;
        list->first = element;
        list->last = element;
        list->length++;
        return;
    }
    /*
    while (1) {
        parent = element;
        child = parent->next;
        if (child == NULL) {
            child = (LinkedListElement*) fmalloc(sizeof (LinkedListElement));
            child->value = value;
            child->next = NULL;
            parent->next = child;
            break;
        }
        element = child;
    }
    */
    child = (LinkedListElement*) fmalloc(sizeof (LinkedListElement));
    child->value = value;
    child->next = NULL;
    list->length++;
    list->last->next = child;
    list->last = child;        
    return;
}

void LinkedListPrepend(LinkedList *list, void *value){
    LinkedListElement *newhead = (LinkedListElement*)fmalloc(sizeof(LinkedListElement));
    newhead->value = value;
    newhead->next = list->first;
    list->first = newhead;
    list->length++;
}

unsigned int LinkedListLength(LinkedList *list) {
    return list->length;
    /*
    unsigned int size = 0;
    LinkedListElement *element = list->first;
    if (element == NULL) {
        return (size);
    }
    size = 1;
    while (1) {
        element = element->next;
        if (element == NULL) {
            break;
        }
        size++;
    }
    return (size);
    */
}

void* LinkedListGet(LinkedList *list, unsigned int index) {
    unsigned int i = 0;
    LinkedListElement *element = list->first;
    while (i != index) {
        element = element->next;
        i++;
    }
    return (element->value);
}

LinkedListElement* LinkedListGetCore(LinkedList *list, unsigned int index) {
    unsigned int i = 0;
    LinkedListElement *element = list->first;
    while (i != index) {
        element = element->next;
        i++;
    }
    return (element);
}


void LinkedListRemove(LinkedList *list, unsigned int index){
    unsigned int len = LinkedListLength(list);
    LinkedListElement *previousElement;
    LinkedListElement *nextElement;
    LinkedListElement *element;
    if(index >= len){
        return;
    }
    if(len == 1){
        list->first = NULL;
        list->length--;
    }
    if(index == 0){
        nextElement = LinkedListGetCore(list, index + 1);
        list->first = nextElement;
        list->length--;
    }
    if(index == (len - 1)){
        previousElement = LinkedListGetCore(list, index - 1);
        previousElement->next = NULL;
        list->length--;
    }
    if(index > 0 && index < (len - 1)){
        previousElement = LinkedListGetCore(list, index - 1);
        nextElement = LinkedListGetCore(list, index + 1);
        element = LinkedListGetCore(list, index);
        
        previousElement->next = nextElement;
        
        previousElement = LinkedListGetCore(list, index - 1);
        nextElement = LinkedListGetCore(list, index + 1);
        element = LinkedListGetCore(list, index);
        list->length--;
    }
}


void LinkedListFreeWithFuzuliValueType(LinkedList *list){
    unsigned int len = LinkedListLength(list);
    LinkedListElement *element = LinkedListGetCore(list, 0);
    for (unsigned int i = 0; i < len; i++){
        FuzuliValue *val = (FuzuliValue*)element->value;
        if(val != NULL){
            val->links = 0;
            FuzuliValueFree(val);
        }
        LinkedListElement *oldelelement = element;
        element = element->next;
        ffree(oldelelement);
    }    
    ffree(list);
}