#include <stdio.h>
#include <stdbool.h>

#include "field.h"
#include "list.h"

bool write(int age, double money, char *name) {
    FILE *file = fopen("test.dat", "wb");
    if (file == NULL) {
        return false;
    }

    Field *f1 = NewField(T_INT, &age);
    Field *f2 = NewField(T_FLOAT, &money);
    Field *f3 = NewField(T_TEXT, name);

    WriteField(&f1, file);
    WriteField(&f2, file);
    WriteField(&f3, file);

    fclose(file);
    return true;
}

bool read(int age, double money, char *name) {
    FILE *file = fopen("test.dat", "rb");
    if (file == NULL) {
        return false;
    }

    Field *f1 = ReadField(file);
    Field *f2 = ReadField(file);
    Field *f3 = ReadField(file);

    bool result = CompareFieldValue(f1, &age) && CompareFieldValue(f2, &money) && CompareFieldValue(f3, name);

    FreeField(&f1);
    FreeField(&f2);
    FreeField(&f3);

    fclose(file);
    return result;
}

bool sort(void *a, void *b) {
    int *aa = a;
    int *bb = b;

    return (*aa) > (*bb);
}

void print(void *a) {
    int *aa = a;

    printf("%d\n", *aa);
}

int main(void) {
    char *name = "Joãozinho da silva junior";
    int age = 10;
    double money = 20.50;

    if (write(age, money, name)) {
        printf("Escreveu!\n");
    } else {
        printf("Não escreveu!\n");
        return 1;
    }

    if (read(age, money, name)) {
       printf("Dados corretos!\n");
    } else {
        printf("Dados errados!\n");
        return 1;
    } 

    List *list = NewList();

    int a = 1;
    int b = 2;
    int c = 9;
    int d = 354;

    ListPushBack(list, &d);
    ListPushBack(list, &b);
    ListPushBack(list, &a);
    ListPushBack(list, &c);

    ListSort(list, &sort);

    ListForEach(list, &print);

    FreeList(&list);

    return 0;
}