#include <stdio.h>
#include <stdbool.h>

#include "field.h"
#include "tests.h"
#include "error.h"

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

Error *test(void) {
    char *name = "John Doe";
    int age = 10;
    double money = 20.50;

    if (!write(age, money, name)) {
        return NewError("Failed to write field!", -1, false);
    } 

    if (!read(age, money, name)) {
       return NewError("Invalid values on compare!", -1, false);
    } 

    return NULL;
}

int main(void) {
    Test t = {"Test field structures", "Tests the Field struct, with read and write."};
    ExecuteTest(&t, &test);

    return 0;
}