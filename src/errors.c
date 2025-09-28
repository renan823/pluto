#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

/*
 */
struct error {
    char *message;
    int code;
    bool fatal;
};

/*
Create the base error struct, allocating memory for it.
Used as base error generator.
*/
Error *NewError(const char *message, int code, bool fatal) {
    Error *error = (Error *)malloc(sizeof(Error));

    if (error != NULL) {
        error->fatal = fatal;
        error->code = code;

        error->message = (char *)malloc(strlen(message) + 1);
        if (error->message != NULL) {
            strcpy(error->message, message);
        }
    }

    return error;
}

/*
Deallocates an error.
*/
void FreeError(Error *error) {
    if (error == NULL) {
        return;
    }

    if (error->message != NULL) {
        free(error->message);
    }

    free(error);
}

/*
 */
char *GetErrorMessage(Error *error) {
    if (error == NULL) {
        return "";
    }

    return error->message == NULL ? "" : error->message;
}

/*
Show an error message and exit if fatal.
Free the previously allocated memory (if it's possible).
*/
void Raise(Error *error) {
    if (error == NULL) {
        fprintf(stderr, "Error: Something went wrong!\n");
        exit(1);
    }

    bool fatal = error->fatal;

    if (error->message != NULL) {
        fprintf(stderr, "[%d] Error: %s\n", error->code, error->message);
        free(error->message);
    }

    free(error);

    if (fatal) {
        exit(1);
    }
}
