#ifndef __MM_H__
#define __MM_H__

#include <sys/boot.h>

#define VIRT_TO_PHYS(addr) ((uint64_t)(addr) - hhdm_request.response->offset)
#define PHYS_TO_VIRT(addr) ((uint64_t)(addr) + hhdm_request.response->offset)

#define ALIGN_ADDRESS_UP(ADDR, ALIGN)                                          \
	(void *)((((unsigned long)ADDR + (ALIGN - 1)) / ALIGN) * ALIGN)

#endif	// __MM_H__