#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "qdme.h"

uint8_t memory[MEM_SIZE] = {0};
uint32_t pc = 0, hi = 0, lo = 0;
uint32_t regFile[32] = {0};

/* InstFetch: Fetch the next instruction from memory into the given
 * instruction */
void InstFetch(inst_t *inst) {
	uint32_t value = 0;
	memcpy(&value, memory + pc, WORD_SIZE);
	value = ntohl(value);
	switch ((value & 0xFC000000) >> 24) {
		case 0:
			inst->type = RTYPE;
			inst->r.op = (value & 0xFC000000) >> 26;
			inst->r.rs = (value & 0x03E00000) >> 21;
			inst->r.rt = (value & 0x001F0000) >> 16;
			inst->r.rd = (value & 0x0000F800) >> 11;
			inst->r.shamt = (value & 0x000007C0) >> 6;
			inst->r.func = value & 0x0000002F;
			break;
		case 2:
		case 3:
			inst->type = JTYPE;
			inst->j.op = (value & 0xFC000000) >> 26;
			inst->j.addr = value & 0X03FFFFFF;
			break;
		default:
			inst->type = ITYPE;
			inst->i.op = (value & 0xFC000000) >> 26;
			inst->i.rs = (value & 0x03E00000) >> 21;
			inst->i.rt = (value & 0x001F0000) >> 16;
			inst->i.imm = value & 0x0000FFFF;
			break;
	}
	if (inst->value == 0) {
		inst->type = NOP;
	}
	pc += WORD_SIZE;
}

void Syscall(void) {
	char c, *s;
	switch (regFile[V0]) {
		case 1:	// print integer
			printf("%d", regFile[A0]);
			break;
		case 2:	// print float
			break;
		case 3:	// print double
			break;
		case 4:	// print string
			printf("%s", memory + regFile[A0]);
			break;
		case 5:	// read integer
			scanf("%d", (int *)regFile + V0);
			break;
		case 6:	// read float
			break;
		case 7:	// read double
			break;
		case 8:	// read string
			s = (char *)calloc(regFile[A0], sizeof(char));
			fgets(s, regFile[A0], stdin);
			memcpy(memory + regFile[A1], s, regFile[A0]);
			free(s);
			break;
		case 9:	// sbrk
			break;
		case 10:	//exit
			exit(0);
		case 11:	// print char
			printf("%c", regFile[A0]);
			break;
		case 12:	// read char
			c = 0;
			scanf("%c", &c);
			regFile[V0] = c;
			break;
		case 13:	// open file
			break;
		case 14:	// read from file
			break;
		case 15:	// write to file
			break;
		case 16:	// close file
			break;
		case 17:	// exit2
			exit(regFile[A0]);
	}
}

/* ExecRtype: Execute a given R-Type instruction */
void ExecRtype(const inst_t inst) {
	rtype_t r = inst.r;
	uint32_t a = regFile[r.rs], b = regFile[r.rt];
	uint64_t mult = 0;
	switch (r.func) {
		case 32: // add
			regFile[r.rd] = (signed)a + (signed)b;
			break;
		case 33: // addu
			regFile[r.rd] = a + b;
			break;
		case 36: // and
			regFile[r.rd] = a & b;
			break;
		case 37: // or
			regFile[r.rd] = a | b;
			break;
		case 42: // slt
			regFile[r.rd] = (signed)a < (signed)b;
			break;
		case 43: // sltu
			regFile[r.rd] = a < b;
			break;
		case 34: // sub
			regFile[r.rd] = (signed)a - (signed)b;
			break;
		case 35: // subu
			regFile[r.rd] = a - b;
			break;
		case 38: // xor
			regFile[r.rd] = a ^ b;
			break;
		case 0: // sll
			regFile[r.rd] = b << r.shamt;
			break;
		case 3: // sra
			regFile[r.rd] = (signed)b >> r.shamt;
			break;
		case 2: // srl
			regFile[r.rd] = b >> r.shamt;
			break;
		case 26: // div
			hi = (signed)a % (signed)b;
			lo = (signed)a / (signed)b;
			break;
		case 27: // divu
			hi = a % b;
			lo = a / b;
			break;
		case 24: // mult
			mult = (signed)a * (signed)b;
			hi = (0xFFFFFFFF00000000 & mult) >> 32;
			lo = 0x00000000FFFFFFFF & mult;
			break;
		case 25: // multu
			mult = a * b;
			hi = (0xFFFFFFFF00000000 & mult) >> 32;
			lo = 0x00000000FFFFFFFF & mult;
			break;
		case 16: // MFHI
			regFile[r.rd] = hi;
			break;
		case 18: // MFLO
			regFile[r.rd] = lo;
			break;
		case 17: // MTHI
			hi = regFile[r.rs];
			break;
		case 19: // MTLO
			lo = regFile[r.rs];
			break;
		case 8: // jr
			pc = a;
			break;
		case 9: // jalr
			regFile[r.rd] = pc + 4;
			pc = a;
			break;
		case 12: // syscall
			Syscall();
			break;
	}
}

/* InstExec: Execute a given instruction */
void InstExec(const inst_t inst) {
	if (inst.type == NOP) {
		return;
	}
	switch (inst.j.op) {
		case 0: // R-type instruction
			ExecRtype(inst);
			break;
		case 3: // jal
			regFile[RA] = pc + 4;
			/* intentional fall through */
		case 2: // j
			pc = (0xF0000000 & pc ) | inst.j.addr;
			break;
		case 4: // beq
			pc = (regFile[inst.i.rs] == regFile[inst.i.rt]) ? pc + 4 +
				inst.i.imm : pc;
			break;
		case 5: // bne
			pc = (regFile[inst.i.rs] != regFile[inst.i.rt]) ? pc + 4 +
				inst.i.imm : pc;
			break;
		case 8: // addi
			regFile[inst.i.rt] = (signed)inst.i.rs + (signed)inst.i.imm;
			break;
		case 9: // addiu
			regFile[inst.i.rt] = inst.i.rs + inst.i.imm;
			break;
		case 12: // andi
			regFile[inst.i.rt] = inst.i.rs & inst.i.imm;
			break;
		case 13: // ori
			regFile[inst.i.rt] = inst.i.rs | inst.i.imm;
			break;
		case 14: // xori
			regFile[inst.i.rt] = inst.i.rs ^ inst.i.imm;
			break;
		case 10: // slti
			regFile[inst.i.rt] = (signed)inst.i.rs < (signed)inst.i.imm;
			break;
		case 11: // sltiu
			regFile[inst.i.rt] = inst.i.rs < inst.i.imm;
			break;
		case 15: // lui
			regFile[inst.i.rt] = inst.i.imm << 16;
			break;
		case 35: // lw
			memcpy(regFile + inst.i.rs, memory + inst.i.rt + inst.i.imm,
					WORD_SIZE);
			break;
		case 43: // sw
			memcpy(memory + inst.i.rt + inst.i.imm, regFile + inst.i.rs,
					WORD_SIZE);
			break;
	}
}

void CycleCpu(void) {
	inst_t instFetch, instExec;
	memset(&instFetch, 0, sizeof(inst_t));
	memset(&instExec, 0, sizeof(inst_t));
	while (pc < MEM_SIZE) {
		InstFetch(&instFetch);
		InstExec(instExec);
		instExec = instFetch;
	}
}

int LoadBinary(const char * const path) {
	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		perror("LoadBinary");
		return -1;
	}
	int8_t byte = 0;
	size_t i = 0;
	while ((byte = fgetc(fp)) != EOF && i < MEM_SIZE) {
		memory[i++] = byte;
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[]) {
	if (LoadBinary(*++argv) == -1) {
		return -1;
	}
	CycleCpu();
}

