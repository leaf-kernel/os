#include <sys/boot.h>
#include <sys/error.h>

// Wrapper includes
#include <backends/framebuffer.h>

// Flanterm includes
#include <backends/flanterm/backends/fb.h>
#include <backends/flanterm/flanterm.h>

// Arch specific includes
#include <arch/x86_64/acpi/acpi.h>
#include <arch/x86_64/acpi/hpet.h>
#include <arch/x86_64/acpi/madt.h>
#include <arch/x86_64/apic/apic.h>
#include <arch/x86_64/cpu/cpu.h>
#include <arch/x86_64/drivers/serial.h>
#include <arch/x86_64/idt/idt.h>
#include <arch/x86_64/mm/heap.h>
#include <arch/x86_64/mm/pmm.h>

// Tools includes
#include <tools/logger.h>
#include <tools/panic.h>

// Libc includes
#include <libc/stdio/printf.h>
#include <libc/string.h>

// Freestanding header includes
#include <stdbool.h>
#include <stddef.h>

#ifdef LEAF_LIMINE
static volatile LIMINE_BASE_REVISION(2);

volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

volatile struct limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST, .revision = 0};

volatile struct limine_hhdm_request hhdm_request = {.id = LIMINE_HHDM_REQUEST,
													.revision = 0};

volatile struct limine_rsdp_request rsdp_request = {.id = LIMINE_RSDP_REQUEST,
													.revision = 0};

volatile struct limine_smp_request smp_request = {.id = LIMINE_SMP_REQUEST,
												  .revision = 0};
#endif

struct flanterm_context *ft_ctx;

void test(void) { printf("Hello, world!\n"); }

// Kernel entry point.
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

	if(memmap_request.response == NULL) {
		hcf();
	}

	if(hhdm_request.response == NULL) {
		hcf();
	}

	if(rsdp_request.response == NULL) {
		hcf();
	}

	if(smp_request.response == NULL) {
		hcf();
	}
#endif

	if(framebuffer == NULL) {
		hcf();
	}

	ft_ctx = flanterm_fb_init(
		NULL, NULL, framebuffer->address, framebuffer->width,
		framebuffer->height, framebuffer->pitch, framebuffer->red_mask_size,
		framebuffer->red_mask_shift, framebuffer->green_mask_size,
		framebuffer->green_mask_shift, framebuffer->blue_mask_size,
		framebuffer->blue_mask_shift, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, 0, 0, 1, 0, 0, 0);

	ft_ctx->cursor_enabled = false;
	ft_ctx->full_refresh(ft_ctx);

	init_serial();
	init_idt();
	init_pmm();
	init_acpi();
	init_apic();

	printf("we up\n");

	hlt();
}