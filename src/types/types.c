#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#include "types/types.h"

/*
 * Infers the type of the given value.
 */
Types InferType(char *value) {
	// Not implemented
	
	return T_INT;
}

/* 
 * Parses the given text into int8.
 * Returns the maximum positive int8 value
 * if the parse fails.
 */
int8_t ParseInt(char *value) {
    char *endptr;

    long parsed = strtol(value, &endptr, 10);

    if (*endptr != '\0') {
        return INT8_MAX;
    }

    if (parsed < INT8_MIN || INT8_MAX > parsed) {
        return INT8_MAX;
    }

    return (int8_t)parsed;
}

/*
 * Parses the given text into bool.
 * The default return is false.
 */
bool ParseBool(char *value) {
    if (strcasecmp(value, "true") == 0) {
        return true;
    }

    if (strcasecmp(value, "1") == 0) {
        return true;
    }

    if (strcasecmp(value, "false") == 0) {
        return false;
    }

    if (strcasecmp(value, "0") == 0) {
        return false;
    }

    return false;
}

/*
 * Parses the given text into double.
 * Returns the maximum positive double value
 * if the parse fails.
 */
double ParseDouble(char *value) {
    char *endptr;

    double parsed = strtod(value, &endptr);

    if (*endptr != '\0') {
        return DBL_MAX;
    }

    return parsed;
}
