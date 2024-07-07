#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qdme.h"
#include "load.h"
#include "instruction.h"

uint8_t *memory = NULL;
size_t memsize = MEM_PADD;
uint32_t pc = 0, hi = 0, lo = 0;
uint32_t regFile[32] = {0};
int exitStatus = 0;
bool run = true;

void CycleCpu(void) {
	inst_t instFetch, instExec;
	memset(&instFetch, 0, sizeof(inst_t));
	memset(&instExec, 0, sizeof(inst_t));
	while (pc < memsize && run) {
		InstFetch(&instFetch);
		InstExec(instExec);
		instExec = instFetch;
	}
}

int main(int argc, char *argv[]) {
	if (LoadBinary(*++argv) == -1) {
		return -1;
	}
	CycleCpu();
	free((void *)memory);
	return exitStatus;
}

