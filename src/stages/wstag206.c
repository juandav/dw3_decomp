#include "common.h"
#include "stage.h"
extern void (*D_800A6108[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4CA8);

StageTask *func_800A4D84(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6108[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4DE0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4E0C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4E38);

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4E48);
