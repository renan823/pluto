#ifndef TESTS_H_
    #define TESTS_H_

    #include <stdbool.h>

    #include "errors.h"

    typedef struct test Test;
    struct test {
        char name[50];
        char description[255];
    };

    typedef Error *(Tester)(void);

    void ExecuteTest(Test* test, Tester *tester);
#endif