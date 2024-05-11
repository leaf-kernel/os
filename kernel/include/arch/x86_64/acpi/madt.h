// Full credits to: https://github.com/asterd-og/ZanOS
#ifndef __MADT_H__
#define __MADT_H__

#include <libc/string.h>
#include <stdbool.h>
#include <stdint.h>

#include <arch/x86_64/acpi/rsdt.h>
#include <arch/x86_64/cpu/cpu.h>
#include <sys/boot.h>

typedef struct {
	char sign[4];
	uint32_t len;
	uint8_t revision;
	uint8_t checksum;
	char oem_id[6];
	char oem_table_id[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;

	/* MADT Specs */
	uint32_t lapic_address;
	uint32_t flags;

	char table[];
} acpi_madt;

typedef struct {
	uint8_t type;
	uint8_t len;
} madt_entry;

typedef struct {
	madt_entry un;
	uint8_t cpu_id;
	uint8_t apic_id;
	uint32_t flags;
} madt_cpu_lapic;

typedef struct {
	madt_entry un;
	uint8_t apic_id;
	uint8_t resv;
	uint32_t apic_addr;
	uint32_t gsi_base;
} madt_ioapic;

typedef struct {
	madt_entry un;
	uint8_t bus_src;
	uint8_t irq_src;
	uint32_t gsi;
	uint16_t flags;
} madt_iso;

typedef struct {
	madt_entry un;
	uint16_t resv;
	uint64_t phys_lapic;
} madt_lapic_addr;

extern madt_ioapic *madt_ioapic_list[128];
extern madt_iso *madt_iso_list[128];

extern uint32_t madt_ioapic_len;
extern uint32_t madt_iso_len;

extern uint64_t *lapic_addr;

void init_madt(acpi_madt *madt);
uint32_t madt_get_iso(uint32_t irq);

#endif	// __MADT_H__