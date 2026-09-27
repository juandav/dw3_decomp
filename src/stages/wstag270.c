#include "common.h"
#include "stage.h"
extern u8 D_800A762C[];
extern u8 D_800A7404[];
extern u8 D_800A5FE4[];
extern u8 D_800A75F0[];
extern u8 D_800A7498[];
void func_800A52CC();
extern void (*D_800A7620[])(void);
void func_800A5894();

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A52A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A52CC);

void *func_800A5868(void) {
    return createTask(func_800A52CC, 0x64, 0x14);
}

void func_800A5894(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A58DC(void *owner) {
    StageTask *task = createTask(func_800A5894, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7620[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5938);

void func_800A5998(void) {
    D_800990B4.unk44 = 0xCD;
    D_800990B4.unk8 = 0x1A0;
    D_800990B4.unkC = 0x1A10000;
    D_800990B4.unk10 = D_800A7498;
    D_800990B4.unk14 = D_800A75F0;
    D_800990B4.unk1C = 0x3C2;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1A400;
    D_800990B4.unk30 = 0xC800;
    D_800990B4.unk28 = D_800A5FE4;
    D_800990B4.unk3C = 8;
    D_800990B4.unk40 = 0x60200000;
    D_800990B4.unk4C = D_800A7404;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A762C;
    D_8009A70C.unk40(0, 0x1A10001);
    D_8009A70C.unk40(7, 0x1A10002);
    D_8009A70C.unk50(0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5A84);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5B18);
