#ifndef __SHCEDULER_H__
#define __SHCEDULER_H__

#include <arch/x86_64/idt/idt.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_PROCESSES 256

enum process_state {
	SCHED_STATE_NONEXISTENT = 0,
	SCHED_STATE_READY = 1,
	SCHED_STATE_BLOCKED = 2,
	SCHED_STATE_DEAD = 3
};

typedef struct {
	uint8_t state;
	char *name;
	int_frame_t regs;
} process_t;

void init_sched();

uint32_t sched_spawn_process(char *name, void (*entry)(void));
void sched_kill_process(uint32_t pid);
process_t *sched_get_curr_process();

void sched_block(uint32_t pid);
void sched_unblock(uint32_t pid);

extern bool sched_running;
extern uint32_t sched_current_pid;

#endif	// __SHCEDULER_H__