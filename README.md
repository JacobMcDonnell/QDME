# QDME - Quick and Dirty MIPS Emulator

## Intro

QDME is a simple MIPS emulator written in C. Currently the binary file must be
manually created, eventually this will change. QDME will use the native byte
order of the machine. [QDMA](https://github.com/JacobMcDonnell/QDMA), the
assembler written for this emulator, also assembles based on the host byte
order.

## Instructions
|Instruction|Type|Action|
|-----------|----|------|
|add        |R   |rd = rs + rt|
|addu       |R   |rd = rs + rt|
|and        |R   |rd = rs & rt|
|or         |R   |rd = rs \| rt|
|slt        |R   |rd = rs < rt|
|sltu       |R   |rd = rs < rt|
|sub        |R   |rd = rs - rt|
|subu       |R   |rd = rs - rt|
|xor        |R   |rd = rs ^ rt|
|sll        |R   |rd = rt << shamt|
|sra        |R   |rd = rt >> shamt|
|srl        |R   |rd = rt >> shamt|
|div        |R   |hi = rs % rt lo = rs / rt|
|divu       |R   |hi = rs % rt lo = rs / rt|
|mult       |R   |hi, lo = rs * rt|
|multu      |R   |hi, lo = rs * rt|
|MFHI       |R   |rd = hi|
|MFLO       |R   |rd = lo|
|MTHI       |R   |rs = hi|
|MTLO       |R   |rs = lo|
|jr         |R   |pc = addr, pc = $ra|
|jalr       |R   |rd = pc, pc = addr|
|syscall    |R   |System Call|
|jal        |J   |$ra = pc, pc = addr|
|j          |J   |pc = addr|
|beq        |I   | pc = (rs == rt) ? imm + pc + 4 : pc|
|bne        |I   | pc = (rs != rt) ? imm + pc + 4 : pc|
|addi       |I   |rt = rs + imm|
|addiu      |I   |rt = rs + imm|
|andi       |I   |rt = rs & imm|
|ori        |I   |rt = rs \| imm|
|xori       |I   |rt = rs ^ imm|
|slti       |R   |rt = rs < imm|
|sltiu      |R   |rt = rs < imm|
|lui        |I   |rt = rs << 16|
|lw         |I   |rs = imm(rt)|
|sw         |I   |imm(rt) = rs|

## Syscalls

|Syscall|Action|
|-------|------|
|1      |Print integer in $a0|
|2      |Not Implemented Yet|
|3      |Not Implemented Yet|
|4      |Print Null Terminated String, address in $a0|
|5      |Read integer into $v0|
|6      |Not Implemented Yet|
|7      |Not Implemented Yet|
|8      |Read string of length $a0 into memory at $a1|
|9      |Not Implemented Yet|
|10     |Exit with Status code 0|
|11     |Print Character in $a0|
|12     |Read Character into $v0|
|13     |Not Implemented Yet|
|14     |Not Implemented Yet|
|15     |Not Implemented Yet|
|16     |Not Implemented Yet|
|17     |Exit with Status Code in $a0|

