#include <arch/x86_64/cpu/cpu.h>
#include <libc/stdio/printf.h>
#include <tools/logger.h>
#include <tools/panic.h>

void panic(const char *reason, int_frame_t *frame) {
	int cpuId = 0;
	if(frame != NULL) {
		fatal("panic(cpu %d @ 0x%016llx) type: %d (Name: %s) err: 0x%llx"
			  "0x%lx!",
			  cpuId, frame->rip, frame->vector, reason, frame->err);
		printf("Register Dump:\r\n");
		printf("  rax: 0x%.16llx, rbx: 0x%.16llx, rcx: 0x%.16llx, rdx: "
			   "0x%.16llx\r\n",
			   frame->rax, frame->rbx, frame->rcx, frame->rdx);
		printf("  rsp: 0x%.16llx, rbp: 0x%.16llx, rsi: 0x%.16llx, rdi: "
			   "0x%.16llx\r\n",
			   frame->rsp, frame->rbp, frame->rsi, frame->rdi);
		printf("  r8:  0x%.16llx, r9:  0x%.16llx, r10: 0x%.16llx, r11: "
			   "0x%.16llx\r\n",
			   frame->r8, frame->r9, frame->r10, frame->r11);
		printf("  r12: 0x%.16llx, r13: 0x%.16llx, r14: 0x%.16llx, r15: "
			   "0x%.16llx\r\n",
			   frame->r12, frame->r13, frame->r14, frame->r15);
		printf("  rfl: 0x%.16llx, rip: 0x%.16llx, cs:  0x%.16llx, ss:  "
			   "0x%.16llx\r\n",
			   frame->rflags, frame->rip, frame->cs, frame->ss);
		printf("  ds: 0x%.16llx,  cr2: 0x%.16llx, cr3: 0x%.16llx\r\n",
			   frame->ds, frame->cr2, frame->cr3);
	} else {

		fatal("panic(cpu %d) Name: %s!", cpuId, reason);
	}
	hcf();
}