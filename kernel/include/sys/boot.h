#ifndef __BOOT_H__
#define __BOOT_H__

#include <backends/flanterm/flanterm.h>

extern struct flanterm_context *ft_ctx;

#ifdef LEAF_LIMINE
#include <limine/limine.h>

extern volatile struct limine_framebuffer_request framebuffer_request;
extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_hhdm_request hhdm_request;
extern volatile struct limine_rsdp_request rsdp_request;

#define VIRT_TO_PHYS(addr) ((uint64_t)(addr) - hhdm_request.response->offset)
#define PHYS_TO_VIRT(addr) ((uint64_t)(addr) + hhdm_request.response->offset)

#endif

#endif	// __BOOT_H__