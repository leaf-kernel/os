#include <arch/x86_64/mm/heap.h>
#include <data/tar.h>
#include <libc/string.h>
#include <sys/error.h>

char *_remove_prefix(const char *str, const char *prefix) {
	size_t prefix_len = strlen(prefix);
	if(strncmp(str, prefix, prefix_len) == 0) {
		return strdup(str + prefix_len);
	}
	return strdup(str);
}

void tar_extract(const char *raw, uint64_t size, struct USTAREntry *entry) {
	if(entry == NULL) {
		error("A NULL TAR entry was passed to tar_extract()!", ERRNO_NULL_VALUE,
			  false);
		return;
	}

	entry->files = NULL;
	entry->fileCount = 0;

	for(uint64_t offset = 0; offset < size;) {
		struct USTARHeader *header = (struct USTARHeader *)(raw + offset);

		if(header->name[0] == '\0') {
			break;
		}

		struct USTARFile file;

		unsigned int size = 0;
		unsigned int count = 1;

		for(int j = 11; j > 0; j--, count *= 8)
			size += ((header->size[j - 1] - '0') * count);

		file.size = size;

		// TODO: Split the path and extract the name.
		file.path = _remove_prefix(header->name, "ramfs/");
		file.name = file.path;

		file.type = header->typeflag;
		file.directory = file.type == DIRTYPE;

		if(!file.directory) {
			file.content = (char *)malloc(file.size + 1);
			memcpy(file.content, raw + offset, file.size);
			file.content[file.size] = '\0';
		} else {
			file.content = "";
		}

		struct USTARFile *files = realloc(
			entry->files, (entry->fileCount + 1) * sizeof(struct USTARFile));

		if(files == NULL) {
			error("Failed to allocate memory for TAR entry files!",
				  ERRNO_NULL_VALUE, false);
			return;
		}

		entry->files = files;
		entry->files[entry->fileCount] = file;
		entry->fileCount++;
		offset += ((file.size + 511) / 512 + 1) * 512;
	}
}