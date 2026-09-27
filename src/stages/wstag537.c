#include "common.h"
#include "stage.h"
extern void (*D_800A60AC[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag537", func_800A4CA4);

StageTask *func_800A4D4C(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A60AC[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag537", func_800A4DA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag537", func_800A4DD4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag537", func_800A4E20);

INCLUDE_ASM("asm/stages/nonmatchings/wstag537", func_800A4E6C);
