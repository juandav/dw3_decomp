#include "common.h"
#include "stage.h"
extern void (*D_800A5DD8[])(void);
void func_800A4CA8();

INCLUDE_ASM("stages/nonmatchings/wstag335", func_800A4CA8);

StageTask *func_800A4D00(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 0x38);

    task->owner = owner;
    D_800A5DD8[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag335", func_800A4D5C);
