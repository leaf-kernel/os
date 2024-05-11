#ifndef __PANIC_H__
#define __PANIC_H__

#include <arch/x86_64/idt/idt.h>

void panic(const char *reason, int_frame_t *frame);

#endif	// __PANIC_H__