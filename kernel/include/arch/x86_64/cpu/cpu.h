#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

void hlt();
void hcf();

// MSR
void read_msr(uint32_t msr, uint32_t *lo, uint32_t *hi);
void write_msr(uint32_t msr, uint32_t lo, uint32_t hi);

#endif	// __CPU_H__
