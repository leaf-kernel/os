// Full credits to: https://github.com/asterd-og/ZanOS
#include <arch/x86_64/apic/ioapic.h>
#include <arch/x86_64/drivers/serial.h>
#include <arch/x86_64/mm/pmm.h>
#include <sys/boot.h>
#include <sys/error.h>

void init_ioapic() {
	apic_ioapic_t *ioapic = g_acpi_ioapic[0];

	uint32_t val = ioapic_read(ioapic, IOAPIC_VER);
	uint32_t count = ((val >> 16) & 0xFF);

	if((ioapic_read(ioapic, 0) >> 24) != ioapic->ioapic_id) {
		error("Failed to initialize IOAPIC", ERRNO_UNKNOWN, true);
	}

	for(uint32_t i = 0; i <= count; ++i) {
		ioapic_write(ioapic, IOAPIC_REDTBL + 2 * i, 0x00010000 | (32 + i));
		ioapic_write(ioapic, IOAPIC_REDTBL + 2 * i + 1, 0);
	}
}

void ioapic_write(apic_ioapic_t *ioapic, uint8_t reg, uint32_t val) {
	*((volatile uint32_t *)(PHYS_TO_VIRT(ioapic->ioapic_addr) +
							IOAPIC_REGSEL)) = reg;
	*((volatile uint32_t *)(PHYS_TO_VIRT(ioapic->ioapic_addr) + IOAPIC_IOWIN)) =
		val;
}

uint32_t ioapic_read(apic_ioapic_t *ioapic, uint8_t reg) {
	*((volatile uint32_t *)(PHYS_TO_VIRT(ioapic->ioapic_addr) +
							IOAPIC_REGSEL)) = reg;
	return *((volatile uint32_t *)(PHYS_TO_VIRT(ioapic->ioapic_addr) +
								   IOAPIC_IOWIN));
}

void ioapic_set_entry(apic_ioapic_t *ioapic, uint8_t idx, uint64_t data) {
	ioapic_write(ioapic, (uint8_t)(IOAPIC_REDTBL + idx * 2), (uint32_t)data);
	ioapic_write(ioapic, (uint8_t)(IOAPIC_REDTBL + idx * 2 + 1),
				 (uint32_t)(data >> 32));
}

uint64_t ioapic_gsi_count(apic_ioapic_t *ioapic) {
	return (ioapic_read(ioapic, 1) & 0xff0000) >> 16;
}

apic_ioapic_t *ioapic_get_gsi(uint32_t gsi) {
	for(uint64_t i = 0; i < g_acpi_ioapic_count; i++) {
		apic_ioapic_t *ioapic = g_acpi_ioapic[i];
		if(ioapic->gsi_base <= gsi &&
		   ioapic->gsi_base + ioapic_gsi_count(ioapic) > gsi)
			return ioapic;
	}
	return NULL;
}

void ioapic_redirect_gsi(uint32_t lapic_id, uint8_t vec, uint32_t gsi,
						 uint16_t flags, bool mask) {
	apic_ioapic_t *ioapic = ioapic_get_gsi(gsi);

	uint64_t redirect = vec;

	if((flags & (1 << 1)) != 0) {
		redirect |= (1 << 13);
	}

	if((flags & (1 << 3)) != 0) {
		redirect |= (1 << 15);
	}

	if(mask)
		redirect |= (1 << 16);
	else
		redirect &= ~(1 << 16);

	redirect |= (uint64_t)lapic_id << 56;

	uint32_t redir_table = (gsi - ioapic->gsi_base) * 2 + 16;
	ioapic_write(ioapic, redir_table, (uint32_t)redirect);
	ioapic_write(ioapic, redir_table + 1, (uint32_t)(redirect >> 32));
}

void ioapic_redirect_irq(uint32_t lapic_id, uint8_t vec, uint8_t irq,
						 bool mask) {
	uint8_t idx = 0;
	apic_iso_t *iso;

	while(idx < g_acpi_iso_count) {
		iso = g_apic_isos[idx];
		if(iso->irq == irq) {
			ioapic_redirect_gsi(lapic_id, vec, iso->gsi, iso->flags, mask);
			return;
		}
		idx++;
	}

	ioapic_redirect_gsi(lapic_id, vec, irq, 0, mask);
}

uint32_t ioapic_get_redirect_irq(uint8_t irq) {
	uint8_t idx = 0;
	apic_iso_t *iso;

	while(idx < g_acpi_iso_count) {
		iso = g_apic_isos[idx];
		if(iso->irq == irq) {
			return iso->gsi;
		}
		idx++;
	}

	return irq;
}