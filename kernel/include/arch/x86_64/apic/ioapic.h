// Full credits to: https://github.com/asterd-og/ZanOS
#ifndef __IOAPIC_H__
#define __IOAPIC_H__

#include <stdint.h>

#include <arch/x86_64/acpi/acpi.h>
#include <arch/x86_64/acpi/madt.h>

#define IOAPIC_REGSEL 0x0
#define IOAPIC_IOWIN 0x10

#define IOAPIC_ID 0x0
#define IOAPIC_VER 0x01
#define IOAPIC_ARB 0x02
#define IOAPIC_REDTBL 0x10

void init_ioapic();

void ioapic_write(apic_ioapic_t *ioapic, uint8_t reg, uint32_t val);
uint32_t ioapic_read(apic_ioapic_t *ioapic, uint8_t reg);

void ioapic_redirect_irq(uint32_t lapic_id, uint8_t vec, uint8_t irq,
						 bool mask);
uint32_t ioapic_get_redirect_irq(uint8_t irq);

#endif	// __IOAPIC_H__