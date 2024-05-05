#include <stdio.h>
#include <stdint.h>

int main(void) {
	uint32_t insts[] = {
		0x2008000a,			// addi $t0, $zero, 10
		0x2009000b,			// addi $t1, $zero, 11
		0x01285020,			// add  $t2, $t1, $t0
		0x20020001,			// addi $v0, $zero, 1
		0x000a2020,			// add $a0, $zero, $t2
		0x0000000C,			// syscall
		0x2002000a,			// addi $v0, $zero, 10
		0x0000000C,			// syscall
	};
	FILE *fp = fopen("test.bin", "w");
	for (size_t i = 0; i < sizeof(insts) / sizeof(insts[0]); i++) {
		fwrite(insts + i, 1, 4, fp);
	}
	fclose(fp);
	return 0;
}
