#include "common.h"
#include "stage.h"
extern void (*D_800A7010[])(void);
void func_800A5E90();

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A52D4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A5300);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A589C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A58C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A5E64);

void func_800A5E90(StageTask *task) {
    switch (task->header.state) {
    case 0:
    default:
        task->header.nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

StageTask *func_800A5ED8(void *owner) {
    StageTask *task = func_800144DC(func_800A5E90, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7010[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A5F34);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A608C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A6120);
