#ifndef __LEAF_H__
#define __LEAF_H__

typedef struct {
#ifdef LEAF_LIMINE
	struct limine_file *ramfs;
#else
	void *ramfs;
#endif
} LEAF_DATA;

#endif	// __LEAF_H__