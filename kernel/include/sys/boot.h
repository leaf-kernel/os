#ifndef __BOOT_H__
#define __BOOT_H__

#ifdef LEAF_LIMINE
#include <limine/limine.h>

__attribute__((used,
			   section(".requests"))) static volatile LIMINE_BASE_REVISION(2);

__attribute__((used,
			   section(".requests_start_"
					   "marker"))) static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((
	used,
	section(
		".requests_end_marker"))) static volatile LIMINE_REQUESTS_END_MARKER;

#endif

#endif	// __BOOT_H__