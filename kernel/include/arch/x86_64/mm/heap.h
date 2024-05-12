#ifndef __HEAP_H__
#define __HEAP_H__

#include <libc/string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void *malloc(size_t size);
void *calloc(size_t size);
void *realloc(void *old, size_t size);
void free(void *tofree);

#endif	// __HEAP_H__