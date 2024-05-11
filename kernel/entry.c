static void hcf(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}

void _start(void) {
	// Do nothing.
	hcf();
}