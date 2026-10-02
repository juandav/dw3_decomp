#include "common.h"
#include "stage.h"
extern void (*D_800A5FC4[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag300", func_800A4CA4);

StageTask *func_800A4D9C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5FC4[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag300", func_800A4DF8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag300", func_800A4E58);

INCLUDE_ASM("asm/stages/nonmatchings/wstag300", func_800A4EA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag300", func_800A4ED0);
