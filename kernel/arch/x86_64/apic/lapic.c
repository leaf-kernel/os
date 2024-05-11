#include <arch/x86_64/acpi/hpet.h>
#include <arch/x86_64/apic/lapic.h>
#include <arch/x86_64/cpu/cpu.h>
#include <arch/x86_64/drivers/serial.h>
#include <sys/error.h>

uint32_t ticks = 0;

uint32_t rreg(uint16_t offset) {
	return *((uint32_t *)((uint64_t)madt_table->lapic_addr + offset));
}

void wreg(uint16_t offset, uint32_t val) {
	*((uint32_t *)((uint64_t)madt_table->lapic_addr + offset)) = val;
}

void lapic_timer_stop() {
	wreg(LAPIC_TMRINITCNT, 0);
	wreg(LAPIC_LVT_TMR, LVT_MASKED);
}

void lapic_timer_oneshot(uint64_t ms, uint8_t vec) {
	lapic_timer_stop();
	wreg(LAPIC_TMRDIV, 0);
	wreg(LAPIC_LVT_TMR, vec);
	wreg(LAPIC_TMRINITCNT, ms * ticks);
}

void init_lapic() {
	outb(0x21, 0xFF);
	iowait();
	outb(0xA1, 0xFF);
	iowait();

	wreg(LAPIC_SPURIOUS, 0x1FF);
	wreg(LAPIC_TASKPRIOR, 0);

	init_hpet();

	lapic_timer_stop();
	wreg(LAPIC_TMRDIV, 0);
	wreg(LAPIC_LVT_TMR, 0);
	wreg(LAPIC_TMRINITCNT, 0xFFFFFFFF);

	hpet_usleep(100);

	ticks = 0xFFFFFFFF - rreg(LAPIC_TMRCURRCNT);
	lapic_timer_stop();
}

void lapic_eoi() { wreg(LAPIC_EOI, 0); }