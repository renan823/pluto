#ifndef FIELD_H_
    #define FIELD_H_

    #include <stdio.h>
    #include <stdbool.h>

    typedef enum {
        T_NULL,
        T_INT,
        T_FLOAT,
        T_TEXT,
        T_BLOB
    } FieldType;

    typedef struct field Field;

    void WriteField(Field **field, FILE *file);
    Field *ReadField(FILE *file);
    Field *NewField(FieldType type, void *value);
    bool CompareFieldValue(Field *field, void *value);
    void FreeField(Field **field);

#endif