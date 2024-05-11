// Full credits to: https://github.com/asterd-og/ZanOS
#include <arch/x86_64/acpi/madt.h>
#include <tools/logger.h>
madt_ioapic *madt_ioapic_list[128] = {0};
madt_iso *madt_iso_list[128] = {0};

uint32_t madt_ioapic_len = 0;
uint32_t madt_iso_len = 0;

uint64_t *lapic_addr = NULL;

void init_madt(acpi_madt *madt) {

	uint64_t off = 0;
	int current_idx = 0;
	madt_ioapic_len = 0;
	madt_iso_len = 0;

	while(true) {
		if(off > madt->len - sizeof(madt))
			break;

		madt_entry *entry = (madt_entry *)(madt->table + off);

		switch(entry->type) {
		case 0:
			current_idx++;
			break;
		case 1:
			madt_ioapic_list[madt_ioapic_len++] = (madt_ioapic *)entry;
			break;
		case 2:
			madt_iso_list[madt_iso_len++] = (madt_iso *)entry;
			break;
		case 5:
			lapic_addr = (uint64_t *)((madt_lapic_addr *)entry)->phys_lapic;
			break;
		}

		off += entry->len;
	}
}