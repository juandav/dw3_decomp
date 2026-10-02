#include "common.h"
#include "stage.h"
extern u8 D_800A5054[];
extern u8 D_800A5070[];
extern u8 D_800A548C[];
extern u8 D_800A50D0[];
extern void (*D_800A56E4[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task) {
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

StageTask *func_800A4CEC(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A56E4[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x76A;
    D_800990B4.unkC = 0x76B0000;
    D_800990B4.unk10 = D_800A50D0;
    D_800990B4.unk14 = D_800A548C;
    D_800990B4.unk1C = 0x769;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x10400;
    D_800990B4.unk30 = 0x3AD00;
    D_800990B4.unk28 = D_800A5070;
    D_800990B4.unk3C = 0x39;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5054;
    D_8009A70C.unk40(0, 0x76B0001);
    D_8009A70C.unk40(7, 0x76B0002);
    D_8009A70C.unk40(4, 0x76B0003);
    D_8009A70C.unk50(0);
}
