#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdbool.h>
#include <stdint.h>

#define ERRNO_NULL_VALUE 0x10
#define ERRNO_FEAT_INVALID 0x32
#define ERRNO_KINIT_FAIL 0x69
#define ERRNO_UNKNOWN 0xFF

void error(char *error, uint8_t errno, bool f);

#endif	// __ERROR_H__