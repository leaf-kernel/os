#include <arch/x86_64/cpu/cpuid.h>

int cpuid_string(int code, uint32_t where[4]) {
	asm volatile("cpuid"
				 : "=a"(*where), "=b"(*(where + 1)), "=c"(*(where + 2)),
				   "=d"(*(where + 3))
				 : "a"(code));
	return (int)where[0];
}

bool cpuid_check_feature(uint32_t feat) {
	unsigned int eax, unused, edx;
	__get_cpuid(1, &eax, &unused, &unused, &edx);
	return edx & feat;
}