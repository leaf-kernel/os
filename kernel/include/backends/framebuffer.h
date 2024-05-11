#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <stdint.h>
#include <sys/boot.h>

struct leaf_framebuffer {
	void *address;
	uint64_t width;
	uint64_t height;
	uint64_t pitch;
	uint16_t bpp;
	uint8_t memory_model;
	uint8_t red_mask_size;
	uint8_t red_mask_shift;
	uint8_t green_mask_size;
	uint8_t green_mask_shift;
	uint8_t blue_mask_size;
	uint8_t blue_mask_shift;
	uint8_t unused[7];
	uint64_t edid_size;
	void *edid;
	uint64_t mode_count;
#ifdef LEAF_LIMINE
	LIMINE_PTR(struct limine_video_mode **) modes;
#else
	void *modes;
#endif
};

#endif	// __FRAMEBUFFER_H__
