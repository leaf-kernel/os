#include "main.h"
#include <arch/x86_64/cpu/cpu.h>
#include <tools/logger.h>

void main(void) {
	ok("Reached main!");
	hlt();
}