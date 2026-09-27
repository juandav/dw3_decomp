#include "common.h"
#include "stage.h"
extern void (*D_800A5AFC[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag685", func_800A4CA4);

StageTask *func_800A4D1C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5AFC[0]();
    return task;
}

void func_800A4D78(void) {
    GAME_PROGRESS = 16;
}

void func_800A4D88(void) {
    FLAGS_00.applyAction(0x4020, 1);
}

void func_800A4DB4(void) {
    GAME_PROGRESS = 25;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag685", func_800A4DC4);
