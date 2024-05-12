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
extern volatile struct limine_smp_request smp_request;
extern volatile struct limine_kernel_address_request kernel_addr_request;

#endif

extern uint8_t __kernel_start;
extern uint8_t __text_start;
extern uint8_t __text_end;
extern uint8_t __rodata_start;
extern uint8_t __rodata_end;
extern uint8_t __data_start;
extern uint8_t __data_end;
extern uint8_t __bss_start;
extern uint8_t __bss_end;
extern uint8_t __kernel_end;

extern uint64_t kernel_stack[8192];

#endif	// __BOOT_H__