#include <arch/x86_64/acpi/madt.h>
#include <tools/logger.h>

madt_t *madt_table;
uint32_t g_acpi_cpu_count;
apic_lapic_t *g_acpi_lapic[CONFIG_CPU_MAX];
apic_ioapic_t *g_acpi_ioapic[CONFIG_CPU_MAX];
uint8_t g_acpi_cpu_ids[CONFIG_CPU_MAX];

uint64_t g_ioapic_addr;
uint64_t g_lapic_addr;

uint64_t g_acpi_ioapic_count;
uint64_t g_acpi_iso_count;

// 16 IRQs
apic_iso_t *g_apic_isos[16];

void init_madt(madt_t *madt) {
	madt_table = madt;
	g_acpi_cpu_count = 0;
	g_acpi_ioapic_count = 0;
	g_lapic_addr = PHYS_TO_VIRT(madt->lapic_addr);

	for(size_t i = 0; i < 16; i++) {
		g_apic_isos[i] = NULL;
	}

	uint8_t *ptr = (uint8_t *)(madt + 1);
	uint8_t *end = (uint8_t *)madt + madt->header.length;

	while(ptr < end) {
		apic_header_t *header = (apic_header_t *)ptr;

		switch(header->type) {
		case APIC_LAPIC: {
			apic_lapic_t *lapic = (apic_lapic_t *)ptr;
			if(g_acpi_cpu_count < CONFIG_CPU_MAX) {
				g_acpi_lapic[g_acpi_cpu_count] = lapic;
				g_acpi_cpu_ids[g_acpi_cpu_count] = lapic->apic_id;
				++g_acpi_cpu_count;
			}
			break;
		}
		case APIC_IOAPIC: {
			apic_ioapic_t *ioapic = (apic_ioapic_t *)ptr;
			g_ioapic_addr = PHYS_TO_VIRT(ioapic->ioapic_addr);
			g_acpi_ioapic[g_acpi_ioapic_count++] = ioapic;
			g_acpi_ioapic_count++;
			break;
		}
		case APIC_ISO: {
			apic_iso_t *iso = (apic_iso_t *)ptr;
			g_apic_isos[iso->irq] = iso;
			g_acpi_iso_count++;
			break;
		}
		case APIC_IOAPIC_NMI: {
			break;
		}
		case APIC_LAPIC_NMI: {
			break;
		}
		case APIC_LAPIC_OVERRIDE: {
			break;
		}
		case APIC_X2APIC: {
			break;
		}
		default: {
			fail("found invalid madt entry %i", header->type);
			break;
		}
		}

		ptr += header->length;
	}
}

uint32_t madt_get_iso(uint32_t irq) {
	if(g_apic_isos[irq] != NULL) {
		return g_apic_isos[irq]->gsi;
	}
	return irq;
}