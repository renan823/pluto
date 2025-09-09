#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "errors.h"
#include "tests.h"

/*
Execute the given test with the given callback function.

This function emulates (very very simplified) the most common 
testing libraries, with colorful output.

Create a new test struct, with name and description. 
Create a new function that returns bool - your operation must be there. 
Create a test file on /test with a main functcion. Call ExcuteTest with
the previously created items.
Call "make test" to run all tests in /tests
*/
void ExecuteTest(Test *test, Tester *tester) {
    printf("\n----------------------------------------------------------------------\n\n");

    // Measure elapsed time
    clock_t start = clock();
    Error *error = tester();
    clock_t end = clock();

    if (error == NULL) {
        printf("\033[32m Name: %s\033[0m\n", test->name);
        printf("\033[32m Description: %s\033[0m\n", test->description);
        printf("\033[32m Error: --\033[0m\n");
        printf("\033[32m Duration: %.6f seconds\033[0m\n", ((double) (end - start)) / CLOCKS_PER_SEC);
        printf("\033[32m Status: PASSED\033[0m\n");
    } else {
        printf("\033[31m Name: %s\033[0m\n", test->name);
        printf("\033[31m Description: %s\033[0m\n", test->description);
        printf("\033[31m Error: %s\033[0m\n", GetErrorMessage(error));
        printf("\033[31m Duration: %.6f seconds\033[0m\n", ((double) (end - start)) / CLOCKS_PER_SEC);
        printf("\033[31m Status: FAILED\033[0m\n");
    }

    printf("\n----------------------------------------------------------------------\n");
}