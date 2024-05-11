#include <sys/boot.h>

static void hcf(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}
void _start(void) {
	// just hang
	hcf();
}