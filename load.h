#ifndef LOAD_H
#define LOAD_H

#include "elf.h"
#include <stdio.h>

int LoadBinary(const char * const path);
int LoadProgramHeader(ProgramHeader_t p, FILE *fp);

#endif
