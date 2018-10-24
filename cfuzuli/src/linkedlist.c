#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "linkedlist.h"
#include "fuzulitypes.h"
#include "token.h"

LinkedList *LinkedListNew() {
    LinkedList *list = (LinkedList*) malloc(sizeof (LinkedList));
    list->first = NULL;
    return (list);
}

void LinkedListAdd(LinkedList *list, void *value) {
    LinkedListElement *parent, *child;
    LinkedListElement *element = list->first;
    if (element == NULL) {
        element = (LinkedListElement*) malloc(sizeof (LinkedListElement));
        element->value = value;
        element->next = NULL;
        list->first = element;
        return;
    }
    while (1) {
        parent = element;
        child = parent->next;
        if (child == NULL) {
            child = (LinkedListElement*) malloc(sizeof (LinkedListElement));
            child->value = value;
            child->next = NULL;
            parent->next = child;
            break;
        }
        element = child;
    }
    return;
}

unsigned int LinkedListLength(LinkedList *list) {
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

