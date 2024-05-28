#include "elf.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <arpa/inet.h>

static inline bool IsBigEndian(void);

/* Elf Header for Little Endian Machines */
const uint8_t e_ident_le[EI_NIDENT] = {
	0x7f, 0x45, 0x4c, 0x46,	// ELF Magic Number
	BIT_WIDTH,				// 32-bit format
	_LITTLE_ENDIAN_,		// Little Endian
	ELF_VERSION,			// ELF Version
	0x00,					// Target OS
	0x00,					// Target ABI
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Padding
};

/* Elf Header for Big Endian Machines */
const uint8_t e_ident_be[EI_NIDENT] = {
	0x7f, 0x45, 0x4c, 0x46,	// ELF Magic Number
	BIT_WIDTH,				// 32-bit format
	_BIG_ENDIAN_,			// Big Endian
	ELF_VERSION,			// ELF Version
	0x00,					// Target OS
	0x00,					// Target ABI
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Padding
};

/* ReadElf: Read the elf header into e from file fp */
ElfHeader_t ReadElf(FILE *fp) {
	ElfHeader_t e;
	fread(&e, sizeof(e), 1, fp);
	if (ferror(fp)) {
		perror("ReadElf");
	}
	return e;
}

/* ValidateElf: Validate the elf header for the given system */
bool ValidateElf(ElfHeader_t e) {
	const uint8_t * const e_ident = IsBigEndian() ? e_ident_be : e_ident_le;
	for (size_t i = 0; i < EI_NIDENT; i++) {
		if (e.e_ident[i] != e_ident[i]) {
			return false;
		}
	}
	if (e.e_machine != MIPS || e.e_version != ELF_VERSION ||
			e.e_type != ET_EXEC || e.e_phentsize != sizeof(ProgramHeader_t)) {
		return false;
	}
	return true;
}

/* ReadProgramHeader: Read n program headers into array p of size n from file
 * fp */
void ReadProgramHeader(size_t n, ProgramHeader_t p[n], FILE *fp) {
	fread(p, sizeof(ProgramHeader_t), n, fp);
	if (ferror(fp)) {
		perror("ReadElf");
	}
}

static inline bool IsBigEndian(void) {
	int32_t x = 10;
	return x == htonl(x);
}
