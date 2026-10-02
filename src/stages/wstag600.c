#include "common.h"
#include "stage.h"
extern u8 D_800A5060[];
extern u8 D_800A5134[];
extern u8 D_800A507C[];
extern u8 D_800A5184[];
extern u8 D_800A513C[];
extern void (*D_800A51B4[])(void);
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
    D_800A51B4[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x4F0;
    D_800990B4.unkC = 0x4F10000;
    D_800990B4.unk10 = D_800A513C;
    D_800990B4.unk14 = D_800A5184;
    D_800990B4.unk1C = 0x4EF;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13400;
    D_800990B4.unk30 = 0x15F00;
    D_800990B4.unk28 = D_800A507C;
    D_800990B4.unk3C = 57;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A5134;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5060;
    D_8009A70C.unk40(0, 0x4F10001);
    D_8009A70C.unk40(7, 0x4F10002);
    D_8009A70C.unk40(4, 0x4F10003);
    D_8009A70C.unk50(0);
}
