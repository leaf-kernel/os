#ifndef __MADT_H__
#define __MADT_H__

#include <libc/string.h>
#include <stdbool.h>
#include <stdint.h>

#include <arch/x86_64/acpi/rsdt.h>
#include <arch/x86_64/cpu/cpu.h>
#include <sys/boot.h>

#define CONFIG_CPU_MAX 256

#define APIC_LAPIC 0
#define APIC_IOAPIC 1
#define APIC_ISO 2
#define APIC_IOAPIC_NMI 3
#define APIC_LAPIC_NMI 4
#define APIC_LAPIC_OVERRIDE 5
#define APIC_X2APIC 9

typedef struct {
	sdt_t header;
	uint32_t lapic_addr;
	uint32_t flags;
} __attribute__((packed)) madt_t;
typedef struct {
	uint8_t type;
	uint8_t length;
} __attribute__((packed)) apic_header_t;

typedef struct {
	apic_header_t header;
	uint8_t acpi_proc_id;
	uint8_t apic_id;
	uint32_t flags;
} __attribute__((packed)) apic_lapic_t;

typedef struct {
	apic_header_t header;
	uint8_t ioapic_id;
	uint8_t reserved;
	uint32_t ioapic_addr;
	uint32_t gsi_base;
} __attribute__((packed)) apic_ioapic_t;

typedef struct {
	apic_header_t header;
	uint8_t bus;
	uint8_t irq;
	uint32_t gsi;
	uint16_t flags;
} __attribute__((packed)) apic_iso_t;

extern madt_t *madt_table;
extern uint64_t g_ioapic_addr;
extern uint64_t g_lapic_addr;
extern uint32_t g_acpi_cpu_count;
extern uint64_t g_acpi_ioapic_count;
extern apic_lapic_t *g_acpi_lapic[CONFIG_CPU_MAX];
extern apic_ioapic_t *g_acpi_ioapic[CONFIG_CPU_MAX];
extern uint64_t g_acpi_iso_count;
extern apic_iso_t *g_apic_isos[16];

void init_madt(madt_t *madt_table);
uint32_t madt_get_iso(uint32_t irq);

#endif	// __MADT_H__