#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_cdread2", CdRead2);

void func_8002B7EC(void) {
    StCdInterrupt();
}

OBJECT_END();
