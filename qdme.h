#ifndef _QDME_H
#define _QDME_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define MEM_PADD		12
#define RA				31
#define V0				2
#define V1				3
#define A0				4
#define A1				5
#define A2				6
#define A3				7
#define WORD_SIZE		4

extern uint8_t *memory;
extern size_t memsize;
extern uint32_t pc, hi, lo;
extern uint32_t regFile[32];
extern int exitStatus;
extern bool run;

#endif

