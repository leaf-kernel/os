#include <arch/x86_64/apic/lapic.h>
#include <arch/x86_64/mm/heap.h>
#include <arch/x86_64/mm/pmm.h>
#include <libc/string.h>
#include <sched/scheduler.h>
#include <tools/logger.h>

process_t processes[MAX_PROCESSES];
uint32_t sched_num_procs = 0;
uint32_t sched_current_pid = 0;
bool sched_running = false;

void sched_main(int_frame_t *regs) {
	if(!sched_running) {
		sched_running = true;
	} else {
		memcpy(&processes[sched_current_pid].regs, regs, sizeof(int_frame_t));
	}
	sched_current_pid++;
	if(sched_current_pid > sched_num_procs)
		sched_current_pid = 0;
	while(!(processes[sched_current_pid].state == SCHED_STATE_READY)) {
		if(processes[sched_current_pid].state == SCHED_STATE_DEAD) {
			memset(&processes[sched_current_pid], 0,
				   sizeof(processes[sched_current_pid]));
		}
		sched_current_pid++;
		if(sched_current_pid > sched_num_procs)
			sched_current_pid = 0;
	}

	memcpy(regs, &processes[sched_current_pid].regs, sizeof(int_frame_t));

	lapic_oneshot(1, 32);
	lapic_eoi();
}

void init_sched() {
	memset(processes, 0, sizeof(processes));
	irq_register(32, sched_main);
}

uint32_t sched_spawn_process(char *name, void (*entry)(void)) {
	if(sched_num_procs < MAX_PROCESSES) {
		processes[sched_num_procs].name = name;
		processes[sched_num_procs].regs.rip = (uint64_t)entry;
		processes[sched_num_procs].regs.rsp = (uint64_t)pmm_request_page();
		processes[sched_num_procs].regs.cs = 0x8;
		processes[sched_num_procs].regs.ss = 0x10;
		processes[sched_num_procs].regs.rflags = 0x202;
		processes[sched_num_procs].state = SCHED_STATE_READY;
		sched_num_procs++;
		return sched_num_procs - 1;
	}
	return -1;
}

void sched_kill_process(uint32_t pid) {
	if(pid < MAX_PROCESSES) {
		processes[pid].state = SCHED_STATE_DEAD;
	}
}

process_t *sched_get_curr_process() { return &processes[sched_current_pid]; }

void sched_block(uint32_t pid) { processes[pid].state = SCHED_STATE_BLOCKED; }

void sched_unblock(uint32_t pid) { processes[pid].state = SCHED_STATE_READY; }