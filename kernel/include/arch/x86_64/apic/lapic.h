// Full credits to: https://github.com/asterd-og/ZanOS
#ifndef __LAPIC_H__
#define __LAPIC_H__

#include <arch/x86_64/acpi/acpi.h>
#include <arch/x86_64/acpi/madt.h>

#include <stdint.h>

#define LAPIC_PPR 0x00a0

#define LAPIC_ICRLO 0x0300
#define LAPIC_ICRHI 0x0310

#define LAPIC_ICINI 0x0500
#define LAPIC_ICSTR 0x0600

#define LAPIC_ICEDGE 0x0000

#define LAPIC_ICPEND 0x00001000
#define LAPIC_ICPHYS 0x00000000
#define LAPIC_ICASSR 0x00004000
#define LAPIC_ICSHRTHND 0x00000000
#define LAPIC_ICDESTSHIFT 24

#define LAPIC_ICRAIS 0x00080000
#define LAPIC_ICRAES 0x000c0000

// Timer

#define LAPIC_TIMER_DIV 0x3E0
#define LAPIC_TIMER_INITCNT 0x380
#define LAPIC_TIMER_LVT 0x320
#define LAPIC_TIMER_DISABLE 0x10000
#define LAPIC_TIMER_CURCNT 0x390
#define LAPIC_TIMER_PERIODIC 0x20000

void init_lapic();

void lapic_stop_timer();
void lapic_oneshot(uint8_t vec, uint64_t ms);
void lapic_calibrate_timer();

void lapic_write(uint32_t reg, uint32_t val);
uint32_t lapic_read(uint32_t reg);

void lapic_eoi();

void lapic_ipi(uint32_t id, uint32_t dat);

void lapic_send_all_int(uint32_t id, uint32_t vec);
void lapic_send_others_int(uint32_t id, uint32_t vec);

void lapic_init_cpu(uint32_t id);
void lapic_start_cpu(uint32_t id, uint32_t vec);
uint32_t lapic_get_id();

#endif	// __LAPIC_H__