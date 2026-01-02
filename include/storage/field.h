#ifndef FIELD_H_
#define FIELD_H_

#include <stdio.h>

typedef struct field Field;

Field *ReadField(FILE *file);

#endif