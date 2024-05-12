#ifndef __TAR_H__
#define __TAR_H__

#include <stdbool.h>
#include <stdint.h>

struct USTARHeader {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
};

struct USTARFile {
	char *path;
	char *name;
	char *content;
	int size;
	uint8_t type;
	bool directory;
};

struct USTAREntry {
	struct USTARFile *files;
	int fileCount;
};

#define TMAGIC "ustar"
#define TMAGLEN 6
#define TVERSION "00"
#define TVERSLEN 2

#define REGTYPE '0'	  /* regular file */
#define AREGTYPE '\0' /* regular file */
#define LNKTYPE '1'	  /* link */
#define SYMTYPE '2'	  /* reserved */
#define CHRTYPE '3'	  /* character special */
#define BLKTYPE '4'	  /* block special */
#define DIRTYPE '5'	  /* directory */
#define FIFOTYPE '6'  /* FIFO special */
#define CONTTYPE '7'  /* reserved */

void tar_extract(const char *raw, uint64_t size, struct USTAREntry *entry);

#endif	// __TAR_H__