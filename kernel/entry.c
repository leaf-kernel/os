#include <backends/framebuffer.h>
#include <sys/boot.h>

#include <stdbool.h>
#include <stddef.h>

#ifdef LEAF_LIMINE
volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};
#endif

static void hcf(void) {
	__asm__("cli");
	for(;;) {
		__asm__("hlt");
	}
}

void _start(void) {
	struct leaf_framebuffer *framebuffer;

#ifdef LEAF_LIMINE
	if(LIMINE_BASE_REVISION_SUPPORTED == false) {
		hcf();
	}

	if(framebuffer_request.response == NULL ||
	   framebuffer_request.response->framebuffer_count < 1) {
		hcf();
	}

	struct limine_framebuffer *limine_framebuffer =
		framebuffer_request.response->framebuffers[0];
	framebuffer = (struct leaf_framebuffer *)limine_framebuffer;
#endif

	if(framebuffer == NULL) {
		hcf();
	}

	for(size_t i = 0; i < 100; i++) {
		volatile uint32_t *fb_ptr = framebuffer->address;
		fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
	}

	// Do nothing.
	hcf();
}