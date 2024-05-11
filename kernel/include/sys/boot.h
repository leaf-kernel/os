#ifndef __BOOT_H__
#define __BOOT_H__

#include <backends/flanterm/flanterm.h>

extern struct flanterm_context *ft_ctx;

#ifdef LEAF_LIMINE
#include <limine/limine.h>

extern volatile struct limine_framebuffer_request framebuffer_request;

#endif

#endif	// __BOOT_H__