#include "arch/x86_64/cpu/cpuid.h"
#include "sys/error.h"
#include <arch/x86_64/cpu/cpu.h>
#include <stdint.h>

void hlt() {
	for(;;)
		__asm__("hlt");
}
void hcf() {
	__asm__("cli");
	hlt();
}

// MSR
void read_msr(uint32_t msr, uint32_t *lo, uint32_t *hi) {
	if(!cpuid_check_feature(CPUID_FEAT_EDX_MSR)) {
		error("MSR is not supported", ERRNO_FEAT_INVALID, true);
		return;
	}
	asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}
void write_msr(uint32_t msr, uint32_t lo, uint32_t hi) {
	if(!cpuid_check_feature(CPUID_FEAT_EDX_MSR)) {
		error("MSR is not supported", ERRNO_FEAT_INVALID, true);
		return;
	}
	asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}
