#include <arch/x86_64/mm/heap.h>
#include <arch/x86_64/mm/pmm.h>
#include <libc/string.h>

void *malloc(size_t size) {
	char *PP = (char *)pmm_request_pages((size / 4096) + 1);
	*((size_t *)PP) = size;
	PP += sizeof(size_t);
	return (void *)PP;
}

void free(void *tofree) {
	char *PP = (char *)tofree;
	PP -= sizeof(size_t);
	size_t size = *((size_t *)PP);
	pmm_free_pages(PP, (size / 4096) + 1);
}

void *calloc(size_t count, size_t size) {
	void *malloced = malloc(count * size);
	memset(malloced, 0, count * size);
	return malloced;
}

void *realloc(void *old, size_t size) {
	size_t smallersize = size;
	if(old) {
		smallersize = *((size_t *)old - 1) < size ? *((size_t *)old - 1) : size;
		void *newmem = malloc(size);
		memcpy(newmem, old, smallersize);
		free(old);
		return newmem;
	}
	return malloc(size);
}
