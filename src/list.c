#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

/*
*/
typedef struct node Node;
struct node {
    void *value;
    Node *prev;
    Node *next;
};

/*
*/
struct list {
    Node *head;
    Node *tail;
    int size;
};

/*
*/
void Swap(void *pa, void *pb) {
    void *aux = pa;

    pa = pb;
    pb = aux;
}

/*
*/
Node *NewNode(void *value) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->value = value;

    return node;
}

/*
*/
List *NewList() {
    List *list = (List*) malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/*
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
*/
void *ListPopFront(List *list) {
    if (list == NULL || list->size == 0) {
        return NULL;
    }

    return NULL;
}

/*
*/
void ListSort(List *list, Sorter *sorter) {
    if (list == NULL) {
        return;
    }

    Node *curr = list->head;

    while (curr->next != NULL) {
        if (sorter(curr->value, curr->next->value)) {
            Swap(curr->value, curr->next->value);
        }

        curr = curr->next;
    }
}

/**/
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
*/
int ListSize(List *list) {
    return list == NULL ? 0 : list->size;
}