#ifndef __BOOT_H__
#define __BOOT_H__

#ifdef LEAF_LIMINE
#include <limine/limine.h>

static volatile LIMINE_BASE_REVISION(2);

extern volatile struct limine_framebuffer_request framebuffer_request;

#endif

#endif	// __BOOT_H__