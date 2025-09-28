#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

/*
Defines the List Node struct.
*/
typedef struct node Node;
struct node {
    void *value;
    Node *prev;
    Node *next;
};

/*
Defines the List struct.
*/
struct list {
    Node *head;
    Node *tail;
    int size;
};

/*
Swap two pointers.
*/
void Swap(void *pa, void *pb) {
    void *aux = pa;

    pa = pb;
    pb = aux;
}

/*
Allocates a new node with the given value.
*/
Node *NewNode(void *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->value = value;

    return node;
}

/*
Allocates a new empty list.
*/
List *NewList() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/*
Deallocates the given list.
Also deallocates each value.
*/
void FreeList(List **list) {
    if ((*list) == NULL) {
        return;
    }

    // Deallocate nodes

    // Dealocate the list
    free(*list);
    *list = NULL;
}

/*
Appends a new the element to the end of the list.
*/
void ListPushBack(List *list, void *item) {
    if (list == NULL) {
        return;
    }

    // Create node
    Node *node = NewNode(item);
    if (node == NULL) {
        return;
    }

    // Case 1: empty list
    if (list->size == 0) {
        list->head = node;
        list->tail = node;

        list->size += 1;
        return;
    }

    // Case 2: default
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->size += 1;
}

/*
Appends a new element to the beginning of the list.
*/
void ListPushFront(List *list, void *item) {
    if (list == NULL) {
        return;
    }

    // Create node
    Node *node = NewNode(item);
    if (node == NULL) {
        return;
    }

    // Case 1: empty list
    if (list->size == 0) {
        list->head = node;
        list->tail = node;

        list->size += 1;
        return;
    }

    // Case 2: default
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    list->size += 1;
}

/*
Removes the last element in the list.
*/
void *ListPopBack(List *list) {
    if (list == NULL || list->size == 0) {
        return NULL;
    }

    void *item = NULL;

    // Case 1: unique item
    if (list->size == 1) {
        item = list->head->value;

        free(list->head);

        list->head = NULL;
        list->tail = NULL;
        list->size = 0;

        return item;
    }

    item = list->tail->value;

    free(list->tail);

    list->tail->prev->next = NULL;

    return NULL;
}

/*
Removes the first element int the list.
*/
void *ListPopFront(List *list) {
    if (list == NULL || list->size == 0) {
        return NULL;
    }
    
    // Not implemented

    return NULL;
}

/*
Uses bubble sort and the given sort condition
to sort the list.
*/
void ListSort(List *list, Sorter *sorter) {
    if (list == NULL) {
        return;
    }
    
    // Not implemented
}

/*
Runs over the entire list and try to find
the element that satisfies the given contidion.
If no element matches, NULL is returned.
*/
void *ListFind(List *list, Finder *finder) {
    if (list == NULL) {
        return NULL;
    }

    Node *curr = list->head;

    while (curr != NULL) {
        if (finder(curr->value)) {
            return curr->value;
        }

        curr = curr->next;
    }

    return NULL;
}

/*
Runs over the entire list applying the given
Iterator function.
*/
void ListForEach(List *list, Iterator *iterator) {
    if (list == NULL) {
        return;
    }

    Node *curr = list->head;

    while (curr != NULL) {
        iterator(curr->value);

        curr = curr->next;
    }
}

/*
Returns the current list size.
Returns 0 if the list is NULL.
*/
int ListSize(List *list) { return list == NULL ? 0 : list->size; }
