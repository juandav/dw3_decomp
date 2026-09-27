#include "common.h"
#include "stage.h"
void func_800A4E48();
extern void (*D_800A70B4[])(void);
void func_800A5054();

INCLUDE_ASM("asm/stages/nonmatchings/wstag480", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag480", func_800A4CBC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag480", func_800A4E48);

void *func_800A5028(void) {
    return createTask(func_800A4E48, 0x78, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag480", func_800A5054);

StageTask *func_800A50F4(void *owner) {
    StageTask *task = createTask(func_800A5054, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A70B4[0]();
    return task;
}

void func_800A5150(void) {
    FLAGS_00.applyAction(0x4000, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag480", func_800A519C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag480", func_800A51AC);
