#ifndef TYPES_H_
#define TYPES_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum types Types;
enum types { T_INT, T_DOUBLE, T_BOOL, T_TIMESTAMP, T_TEXT };

Types InferType(char *value);

int8_t ParseInt(char *value);
bool ParseBool(char *value);
double ParseDouble(char *value);

#endif
