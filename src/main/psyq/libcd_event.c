#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_event", CdInit);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_event", func_8002B618);

void func_8002B654(void) {
    func_8002B6D8(0xF0000003, 0x20);
}

void func_8002B67C(void) {
    func_8002B6D8(0xF0000003, 0x40);
}

void func_8002B6A4(void) {
    func_8002B6D8(0xF0000003, 0x40);
}

OBJECT_END();
