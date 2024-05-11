#include <arch/x86_64/apic/apic.h>
#include <arch/x86_64/cpu/cpuid.h>
#include <sys/error.h>
#include <tools/logger.h>
#include <tools/panic.h>

#include <stdbool.h>

void init_apic() {
	if(!cpuid_check_feature(CPUID_FEAT_EDX_APIC)) {
		error("APIC not supported", ERRNO_FEAT_INVALID, true);
	}

	init_lapic();
	init_ioapic();
}