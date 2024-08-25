#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

typedef struct {
	unsigned int op: 6;
	unsigned int rs: 5;
	unsigned int rt: 5;
	unsigned int rd: 5;
	unsigned int shamt: 5;
	unsigned int func: 6;
} rtype_t;

typedef struct {
	unsigned int op: 6;
	unsigned int rs: 5;
	unsigned int rt: 5;
	unsigned int imm: 16;
} itype_t;

typedef struct {
	unsigned int op: 6;
	unsigned int addr: 26;
} jtype_t;

typedef enum { NOP, RTYPE, ITYPE, JTYPE } type_t;

typedef struct {
	type_t type;
	union {
		rtype_t r;
		jtype_t j;
		itype_t i;
		uint32_t value;
	};
} inst_t;

void InstFetch(inst_t *inst);
void InstExec(const inst_t inst);

#endif
