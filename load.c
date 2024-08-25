#include "load.h"
#include "qdme.h"
#include "elf.h"
#include <stdlib.h>

int LoadBinary(const char * const path) {
	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		perror("LoadBinary");
		return -1;
	}

	ElfHeader_t e = ReadElf(fp);
	if (!ValidateElf(e)) {
		return -1;
	}

	pc = e.e_entry;

	const size_t n = e.e_phnum;
	ProgramHeader_t *p = (ProgramHeader_t *)calloc(n, e.e_phentsize);
	if (p == NULL) {
		perror("calloc");
		return -1;
	}
	ReadProgramHeader(n, p, fp);

	for (size_t i = 0; i < n; i++) {
		memsize += p[i].memsz;
	}

	if ((memory = (uint8_t *)calloc(memsize, sizeof(uint8_t))) == NULL) {
		perror("calloc");
		free((void *)p);
		fclose(fp);
		return -1;
	}

	for (size_t i = 0; i < n; i++) {
		if (LoadProgramHeader(p[i], fp) == -1) {
			free((void *)p);
			fclose(fp);
			return -1;
		}
	}

	free((void *)p);
	fclose(fp);
	return 0;
}

/* LoadProgramHeader: Load the program segment described by the given program
 * header from file fp. Returns 0 on success and -1 on failure. */
int LoadProgramHeader(ProgramHeader_t p, FILE *fp) {
	uint8_t *memloc = memory + p.vaddr;
	size_t s = p.filesz;
	if (fseek(fp, p.offset, SEEK_SET) != 0) {
		perror("fseek");
		return -1;
	}
	fread(memloc, sizeof(uint8_t), s, fp);
	if (ferror(fp)) {
		return -1;
	}
	return 0;
}

