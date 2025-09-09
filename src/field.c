#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "field.h"

/**/
typedef union field_data FIELD_DATA;
union field_data {
    double d;
    int64_t i;
    void *z;
};

/**/
struct field {
    size_t size;
    FieldType type;
    FIELD_DATA data;
};

/**/
void FreeField(Field **field) {
    if (*field == NULL) {
        return;
    }

    if ((*field)->type == T_TEXT || (*field)->type == T_BLOB) {
        free((*field)->data.z);
    }

    free(*field);
    *field = NULL;
}

/**/
void WriteField(Field **field, FILE *file) {
    if (*field == NULL) {
        return;
    }

    // Writes field size
    fwrite(&(*field)->size, sizeof(size_t), 1, file);

    // Writes file type
    fwrite(&(*field)->type, sizeof(FieldType), 1, file);

    // Writes file data
    switch ((*field)->type) {
        case T_INT:
            fwrite(&(*field)->data.i, sizeof(int64_t), 1, file);
            break;

        case T_FLOAT:
            fwrite(&(*field)->data.d, sizeof(double), 1, file);
            break;

        case T_TEXT:
            fwrite((*field)->data.z, (*field)->size, 1, file);
            break;

        default:
            return;
    }

    FreeField(field);
}

/**/
Field *ReadField(FILE *file) {
    Field *field = (Field*) malloc(sizeof(Field));
    if (field == NULL) {
        return NULL;
    }

    // Reads field size
    fread(&field->size, sizeof(size_t), 1, file);

    // Reads field type
    fread(&field->type, sizeof(FieldType), 1, file);

    // Reads field data
    switch (field->type) {
        case T_INT:
            fread(&field->data.i, field->size, 1, file);
            break;

        case T_FLOAT:
            fread(&field->data.d, field->size, 1, file);
            break;

        case T_TEXT:
            field->data.z = (char*) malloc(field->size + 1);

            if (field->data.z == NULL) {
                FreeField(&field);
                return NULL;
            }

            if (fread(field->data.z, field->size, 1, file) != 1) {
                FreeField(&field);
                return NULL;
            }

            ((char*)field->data.z)[field->size] = '\0';
            break;

        default:
            return NULL;
    }

    return field;
}

/**/
Field *NewField(FieldType type, void *value) {
    Field *field = (Field*) malloc(sizeof(Field));
    if (field == NULL) {
        return NULL;
    }

    field->type = type;

    switch (field->type) {
        case T_INT:
            field->size = sizeof(int64_t);
            field->data.i = *(int64_t*) value;
            break;

        case T_FLOAT:
            field->size = sizeof(double);
            field->data.d = *(double*) value;
            break;

        case T_TEXT: {
            char *str = (char*) value;

            field->size = strlen(str);
            field->data.z = (char*) malloc(field->size + 1);

            if (field->data.z == NULL) {
                FreeField(&field);
                return NULL;
            }

            strcpy(field->data.z, str);
            break;
        }
          
        default:
            return NULL;
    }

    return field;
}

/**/
bool CompareFieldValue(Field *field, void *value) {
    if (field == NULL || value == NULL) {
        return false;
    }

    switch (field->type) {
        case T_INT:
            return field->data.i == *(int64_t*) value;

        case T_FLOAT:
            return field->data.d == *(double*) value;

        case T_TEXT:
            return strcmp(field->data.z, (char*) value) == 0;

        default:
            return false;
    }
}