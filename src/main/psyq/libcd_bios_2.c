#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_2", CD_getsector);

void func_8002E388(void (*func)()) {
    DMACallback(3, func);
}

OBJECT_END();
