#include "common.h"
#include "stage.h"
extern u8 D_800A579C[];
extern u8 D_800A51DC[];
extern u8 D_800A5654[];
extern u8 D_800A51F8[];
extern u8 D_800A5738[];
extern u8 D_800A5670[];
extern void (*D_800A5798[])(void);
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
    D_800A5798[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x4049, 1);
}

void func_800A4D74(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x61A;
    D_800990B4.unkC = 0x61B0000;
    D_800990B4.unk10 = D_800A5670;
    D_800990B4.unk14 = D_800A5738;
    D_800990B4.unk1C = 0x619;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x2C900;
    D_800990B4.unk30 = 0x23B00;
    D_800990B4.unk28 = D_800A51F8;
    D_800990B4.unk3C = 0x38;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A5654;
    D_800990B4.unk20 = D_800A51DC;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A579C;
    D_8009A70C.unk40(0, 0x61B0001);
    D_8009A70C.unk40(7, 0x61B0002);
    D_8009A70C.unk40(4, 0x61B0003);
    D_8009A70C.unk50(0);
}
