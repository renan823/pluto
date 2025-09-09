#ifndef LIST_H_
    #define LIST_H_

    #include <stdbool.h>

    typedef struct list List;

    typedef bool (Sorter)(void *a, void *b);
    typedef bool (Finder)(void *a);
    typedef void (Iterator)(void *a);

    List *NewList();
    void FreeList(List **list);

    void ListPushBack(List *list, void *item);
    void ListPushFront(List *list, void *item);

    void *ListPopBack(List *list);
    void *ListPopFront(List *list);

    void ListSort(List *list, Sorter *sorter);
    void *ListFind(List *list, Finder *finder);
    void ListForEach(List *list, Iterator *iterator);

    int ListSize(List *list);
#endif