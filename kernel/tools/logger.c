#include <libc/stdio/printf.h>
#include <tools/logger.h>
void ok(const char *fmt, ...) {
	va_list args1;
	va_start(args1, fmt);
	printf("[  \033[32mOK\033[0m  ] ");
	vprintf(fmt, args1);
	printf("\r\n");
	va_end(args1);
}

void fail(const char *fmt, ...) {
	va_list args1;
	va_start(args1, fmt);
	printf("[  \033[31mERROR\033[0m  ] ");
	vprintf(fmt, args1);
	printf("\r\n");
	va_end(args1);
}

void warn(const char *fmt, ...) {
	va_list args1;
	va_start(args1, fmt);
	printf("[  \033[33mWARNING\033[0m  ] ");
	vprintf(fmt, args1);
	printf("\r\n");
	va_end(args1);
}

void fatal(const char *fmt, ...) {
	va_list args1;
	va_start(args1, fmt);
	printf("[  \033[91mFATAL\033[0m  ] ");
	vprintf(fmt, args1);
	printf("\r\n");
	va_end(args1);
}