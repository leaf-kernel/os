#include <arch/x86_64/cpu/cpu.h>

void hlt() {
	for(;;)
		__asm__("hlt");
}
void hcf() {
	__asm__("cli");
	hlt();
}