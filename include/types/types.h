#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum types Types;
enum types { T_INT, T_DOUBLE, T_BOOL, T_TIMESTAMP, T_TEXT };

Types InferType(char *value);

int64_t ParseInt(char *value);
bool ParseBool(char *value);
double ParseDouble(char *value);

#endif