#include "common.h"
#include "stage.h"
extern void (*D_800A6108[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4CA8);

StageTask *func_800A4D84(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6108[0]();
    return task;
}

void func_800A4DE0(void) {
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4E0C(void) {
    FLAGS_00.applyAction(0x40CA, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4E38);

INCLUDE_ASM("asm/stages/nonmatchings/wstag206", func_800A4E48);
