#include <arch/x86_64/acpi/fadt.h>
#include <libc/string.h>
#include <tools/logger.h>
fadt_t *fadt_table;

void init_fadt(fadt_t *fadt) {
	if(strncmp(fadt->h.signature, "FACP", 4) == 0) {
		fadt_table = fadt;
	} else {
		fail("Failed to init FADT");
		hcf();
	}
}