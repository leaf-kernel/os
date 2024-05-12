#include <sys/boot.h>
#include <sys/error.h>

#include "main.h"

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
#include <arch/x86_64/gdt/gdt.h>
#include <arch/x86_64/idt/idt.h>
#include <arch/x86_64/mm/heap.h>
#include <arch/x86_64/mm/mm.h>
#include <arch/x86_64/mm/pmm.h>
#include <arch/x86_64/mm/vmm.h>

// Etc includes
#include <sched/scheduler.h>

// Tools includes
#include <tools/logger.h>
#include <tools/panic.h>

// Libc includes
#include <libc/stdio/printf.h>
#include <libc/string.h>

// Freestanding header includes
#include <stdbool.h>
#include <stddef.h>

uint64_t kernel_stack[8192];

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

volatile struct limine_kernel_address_request kernel_addr_request = {
	.id = LIMINE_KERNEL_ADDRESS_REQUEST, .revision = 0};
#endif

struct flanterm_context *ft_ctx;

void map_kernel();
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
	ok("Initialized Serial");
	init_gdt((uint64_t *)kernel_stack);
	ok("Initialized GDT");
	init_idt();
	ok("Initialized IDT");
	init_pmm();
	ok("Initialized PMM");
	init_vmm();
	ok("Initialized VMM");
	map_kernel();
	ok("Mapped Kernel");
	init_acpi();
	ok("Initialized ACPI");
	init_apic();
	ok("Initialized APIC");
	__asm__ volatile("sti");
	init_sched();

	int cores = smp_request.response->cpu_count;
	if(cores <= 1)
		printf("\x1b[1;32mLeaf\x1b[0m booted successfully with %d "
			   "core!\n",
			   cores);
	else
		printf("\x1b[1;32mLeaf\x1b[0m booted successfully with %d "
			   "cores!\n",
			   cores);

	sched_spawn_process("kmain", main);
	__asm__("int $32");

	hlt();
}

void map_kernel() {
	volatile struct limine_memmap_response *memmap = memmap_request.response;
	uint64_t hhdm_offset = hhdm_request.response->offset;

	vmm_map_range(
		&__kernel_start,
		(void *)((uint64_t)&__kernel_start -
				 (uint64_t)kernel_addr_request.response->virtual_base +
				 (uint64_t)kernel_addr_request.response->physical_base),
		&__kernel_end, _VMM_PRESENT | _VMM_EXECUTE_DISABLE);

	vmm_map_range(
		&__text_start,
		(void *)((uint64_t)&__text_start -
				 (uint64_t)kernel_addr_request.response->virtual_base +
				 (uint64_t)kernel_addr_request.response->physical_base),
		&__text_end, _VMM_PRESENT);

	ALIGN_ADDRESS_UP(&__text_end, 4096);
	vmm_map_range(
		&__rodata_start,
		(void *)((uint64_t)&__rodata_start -
				 (uint64_t)kernel_addr_request.response->virtual_base +
				 (uint64_t)kernel_addr_request.response->physical_base),
		&__rodata_end, _VMM_PRESENT | _VMM_EXECUTE_DISABLE);

	ALIGN_ADDRESS_UP(&__rodata_end, 4096);
	vmm_map_range(
		&__data_start,
		(void *)((uint64_t)&__data_start -
				 (uint64_t)kernel_addr_request.response->virtual_base +
				 (uint64_t)kernel_addr_request.response->physical_base),
		&__data_end, _VMM_PRESENT | _VMM_WRITE | _VMM_EXECUTE_DISABLE);

	ALIGN_ADDRESS_UP(&__data_end, 4096);
	vmm_map_range(
		&__bss_start,
		(void *)((uint64_t)&__bss_start -
				 (uint64_t)kernel_addr_request.response->virtual_base +
				 (uint64_t)kernel_addr_request.response->physical_base),
		&__bss_end, _VMM_PRESENT | _VMM_WRITE | _VMM_EXECUTE_DISABLE);

	ALIGN_ADDRESS_UP(&__bss_end, 4096);
	for(uint64_t entryCount = 0; entryCount < memmap->entry_count;
		entryCount++) {
		struct limine_memmap_entry *entry = memmap->entries[entryCount];

		if(entry == NULL) {
			error("Failed to get memmap entry!", ERRNO_NULL_VALUE, true);
		}

		if((entry->base + entry->length) < 0x100000000)
			continue;
		uint64_t addr = entry->base & ~0xfff;
		uint64_t length = entry->length + 0xfff;
		length &= ~0xfff;

		for(uint64_t j = 0; j < length; j += 0x1000) {
			vmm_map_range((void *)(uint64_t)entry->base + (uint64_t)hhdm_offset,
						  &entry->base,
						  (void *)(uint64_t)entry->base +
							  (uint64_t)entry->length,
						  _VMM_PRESENT | _VMM_WRITE | _VMM_EXECUTE_DISABLE);
		}
	}
}