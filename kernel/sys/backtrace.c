#include <libc/stdio/printf.h>
#include <sys/backtrace.h>

void backtrace(void *rbp, uint64_t caller) {
	dprintf("[%.16lx]\r\n", caller);
	printf("[%.16lx]\r\n", caller);
	struct stackframe *frame = (struct stackframe *)rbp;
	while(frame) {
		if(frame->rip == 0)
			break;

		dprintf("[%.16lx]\r\n", frame->rip);
		printf("[%.16lx]\r\n", frame->rip);

		frame = frame->rbp;
	}
}