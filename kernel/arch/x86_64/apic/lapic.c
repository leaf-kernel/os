// Full credits to: https://github.com/asterd-og/ZanOS
#include <arch/x86_64/acpi/hpet.h>
#include <arch/x86_64/apic/lapic.h>
#include <arch/x86_64/cpu/cpu.h>
#include <arch/x86_64/drivers/serial.h>
#include <sys/boot.h>

uint64_t apic_ticks = 0;

uint64_t rdmsr(uint32_t msr) {
	uint32_t low;
	uint32_t high;
	__asm__ volatile("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
	return ((uint64_t)high << 32) | low;
}

void wrmsr(uint32_t msr, uint64_t val) {
	__asm__ volatile("wrmsr"
					 :
					 : "a"((uint32_t)val), "d"((uint32_t)(val >> 32)),
					   "c"(msr));
}

void init_lapic() {
	lapic_write(0xf0, lapic_read(0xf0) | 0x100);
	init_hpet();
	lapic_calibrate_timer();
}

void lapic_stop_timer() {
	lapic_write(LAPIC_TIMER_INITCNT, 0);
	lapic_write(LAPIC_TIMER_LVT, LAPIC_TIMER_DISABLE);
}

void lapic_oneshot(uint8_t vec, uint64_t ms) {
	lapic_stop_timer();
	lapic_write(LAPIC_TIMER_DIV, 0);
	lapic_write(LAPIC_TIMER_LVT, vec);
	lapic_write(LAPIC_TIMER_INITCNT, apic_ticks * ms);
}

void lapic_calibrate_timer() {
	lapic_stop_timer();
	lapic_write(LAPIC_TIMER_DIV, 0);
	lapic_write(LAPIC_TIMER_LVT, 0);
	lapic_write(LAPIC_TIMER_INITCNT, 0xFFFFFFFF);
	hpet_usleep(1000);
	lapic_write(LAPIC_TIMER_LVT, LAPIC_TIMER_DISABLE);
	uint32_t ticks = 0xFFFFFFFF - lapic_read(LAPIC_TIMER_CURCNT);
	apic_ticks = ticks;
	lapic_stop_timer();
}

void lapic_write(uint32_t reg, uint32_t val) {
	*((volatile uint32_t *)(PHYS_TO_VIRT(0xfee00000) + reg)) = val;
}

uint32_t lapic_read(uint32_t reg) {
	return *((volatile uint32_t *)(PHYS_TO_VIRT(0xfee00000) + reg));
}

void lapic_eoi() { lapic_write((uint8_t)0xb0, 0x0); }

void lapic_ipi(uint32_t id, uint32_t dat) {
	lapic_write(LAPIC_ICRHI, id << LAPIC_ICDESTSHIFT);
	lapic_write(LAPIC_ICRLO, dat);

	while((lapic_read(LAPIC_ICRLO) & LAPIC_ICPEND) != 0)
		;
}

void lapic_send_all_int(uint32_t id, uint32_t vec) {
	lapic_ipi(id, vec | LAPIC_ICRAIS);
}

void lapic_send_others_int(uint32_t id, uint32_t vec) {
	lapic_ipi(id, vec | LAPIC_ICRAES);
}

void lapic_init_cpu(uint32_t id) {
	lapic_ipi(id, (uint32_t)(LAPIC_ICINI | LAPIC_ICPHYS | LAPIC_ICASSR |
							 LAPIC_ICEDGE | LAPIC_ICSHRTHND));
}

void lapic_start_cpu(uint32_t id, uint32_t vec) {
	lapic_ipi(id, vec | LAPIC_ICSTR | LAPIC_ICPHYS | LAPIC_ICASSR |
					  LAPIC_ICEDGE | LAPIC_ICSHRTHND);
}

uint32_t lapic_get_id() { return lapic_read(0x0020) >> LAPIC_ICDESTSHIFT; }

void lapic_set_base(uint64_t lapic) {
	wrmsr(0x800, (lapic & 0xfffff000ULL) | 0x800);
}

uint64_t lapic_get_base() { return rdmsr(0x1bU) & 0xfffff000ULL; }