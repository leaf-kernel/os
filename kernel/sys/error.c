#include <sys/error.h>

#include <arch/x86_64/cpu/cpu.h>
#include <tools/logger.h>

#include <libc/string.h>

void error(char *error, uint8_t errno, bool f) {
	char errno_str[64];
	switch(errno) {
	case ERRNO_NULL_VALUE:
		strncpy(errno_str, "ERRNO_NULL_VALUE", sizeof(errno_str));
		break;
	case ERRNO_FEAT_INVALID:
		strncpy(errno_str, "ERRNO_FEAT_INVALID", 64);
		break;
	case ERRNO_KINIT_FAIL:
		strncpy(errno_str, "ERRNO_KINIT_FAIL", 64);
		break;
	default:
		strncpy(errno_str, "ERRNO_UNKOWN", 64);
		break;
	}

	if(f) {
		fatal("ERROR: \"%s\" ERRNO: 0x%02X (%s)", error, errno, errno_str);
		hcf();
	} else {
		fail("ERROR: \"%s\" ERRNO: 0x%02X (%s)", error, errno, errno_str);
	}
}