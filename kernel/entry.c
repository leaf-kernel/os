#include <stdbool.h>
#include <sys/boot.h>

static void hcf(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}

void _start(void) {
#ifdef LEAF_LIMINE
	if(LIMINE_BASE_REVISION_SUPPORTED == false) {
		hcf();
	}
#endif

	// Do nothing.
	hcf();
}