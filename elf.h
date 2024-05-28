#ifndef ELF_H
#define ELF_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define EI_NIDENT		16
#define MIPS			0x08
#define PF_READ			4
#define PF_WRITE		2
#define PF_EXEC			1
#define _LITTLE_ENDIAN_	0x01
#define _BIG_ENDIAN_	0x02
#define ELF_VERSION		0x01
#define BIT_WIDTH		0x01	// 32-bit Format


enum {ET_NONE, ET_REL, ET_EXEC, ET_DYN, ET_CORE};
enum {PT_NULL, PT_LOAD, PT_DYNAMIC, PT_INTERP, PT_NOTE, PT_SHLIB, PT_TLS};

typedef struct {
	uint8_t e_ident[EI_NIDENT];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint32_t e_entry;
	uint32_t e_phoff;
	uint32_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} ElfHeader_t;

typedef struct {
	uint32_t ptype;
	uint32_t offset;
	uint32_t vaddr;
	uint32_t paddr;
	uint32_t filesz;
	uint32_t memsz;
	uint32_t flags;
	uint32_t align;
} ProgramHeader_t;

ElfHeader_t ReadElf(FILE *fp);
bool ValidateElf(ElfHeader_t e);
void ReadProgramHeader(size_t n, ProgramHeader_t p[n], FILE *fp);

#endif
