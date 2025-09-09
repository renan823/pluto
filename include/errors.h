#ifndef ERRORS_H_
    #define ERRORS_H_

    #include <stdbool.h>

    typedef struct error Error;

    Error *NewError(const char *message, int code, bool fatal);
    void FreeError(Error *error);

    char *GetErrorMessage(Error *error);

    void Raise(Error *error);
#endif