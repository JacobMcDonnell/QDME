#ifndef _QDME_H
#define _QDME_H

#include <stdint.h>

#define MEM_PADD		12
#define RA				31
#define V0				2
#define V1				3
#define A0				4
#define A1				5
#define A2				6
#define A3				7
#define WORD_SIZE		4

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

#endif

