#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#include "types/timestamp.h"

/*
 * Returns the current time in milliseconds.
 */
Timestamp CurrentTimestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/*
 * Parses the given string date into a valid timestamp.
 */
Timestamp ParseTimestamp(char *timestamp) {
	// Not implemented
	
	return -1;
}
