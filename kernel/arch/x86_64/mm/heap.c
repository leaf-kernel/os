#include <arch/x86_64/mm/heap.h>
#include <arch/x86_64/mm/pmm.h>
#include <tools/logger.h>

void *malloc(size_t size) {
	char *PP = (char *)pmm_request_pages((size / PAGE_SIZE) + 1);
	if(PP == NULL) {
		return NULL;
	}
	*((size_t *)PP) = size;
	PP += sizeof(size_t);
	return (void *)PP;
}

void free(void *tofree) {
	if(tofree == NULL) {
		return;
	}
	char *PP = (char *)tofree;
	PP -= sizeof(size_t);
	size_t size = *((size_t *)PP);
	pmm_free_pages(PP, (size / PAGE_SIZE) + 1);
}

void *calloc(size_t size) {
	void *mallocVal = malloc(size);
	if(mallocVal == NULL) {
		return NULL;
	}
	memset(mallocVal, 0, size);
	return mallocVal;
}

void *realloc(void *old, size_t size) {
	if(old == NULL) {
		return malloc(size);
	}

	size_t old_size = *((size_t *)old - 1);

	size_t new_num_pages = (size / PAGE_SIZE) + 1;
	size_t old_num_pages = (old_size / PAGE_SIZE) + 1;

	if(new_num_pages > old_num_pages) {
		void *new_mem = pmm_request_pages(new_num_pages - old_num_pages);
		if(new_mem == NULL) {
			return NULL;
		}

		memcpy(new_mem, old, old_size);
		free(old);

		return new_mem;
	} else {
		return old;
	}
}