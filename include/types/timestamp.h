#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <stdint.h>

typedef int64_t Timestamp;

Timestamp CurrentTimestamp(void);
Timestamp ParseTimestamp(char *timestamp);

#endif
