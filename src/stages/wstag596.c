#include "common.h"
#include "stage.h"
extern u8 D_800A5060[];
extern u8 D_800A5130[];
extern u8 D_800A507C[];
extern u8 D_800A5170[];
extern u8 D_800A5138[];
extern void (*D_800A51A0[])(void);
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
    D_800A51A0[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x5E2;
    D_800990B4.unkC = 0x5E30000;
    D_800990B4.unk10 = D_800A5138;
    D_800990B4.unk14 = D_800A5170;
    D_800990B4.unk1C = 0x5E1;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x12C00;
    D_800990B4.unk30 = 0x15400;
    D_800990B4.unk28 = D_800A507C;
    D_800990B4.unk3C = 57;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A5130;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5060;
    D_8009A70C.unk40(0, 0x5E30001);
    D_8009A70C.unk40(7, 0x5E30002);
    D_8009A70C.unk40(4, 0x5E30003);
    D_8009A70C.unk50(0);
}
