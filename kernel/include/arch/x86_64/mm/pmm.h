#ifndef __X64_PMM_H__
#define __X64_PMM_H__

#include <stddef.h>

#define PAGE_SIZE 4096
void init_pmm();
void update_memory();
void *pmm_request_page();
void *pmm_request_pages(size_t numPages);
void pmm_free(void *ptr);
void pmm_free_pages(void *ptr, size_t numPages);

#endif	// __X64_PMM_H__