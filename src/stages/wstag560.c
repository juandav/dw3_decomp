#include "common.h"
#include "stage.h"
extern u8 D_800A5598[];
extern u8 D_800A5128[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A52C8[];
extern u8 D_800A5144[];
extern u8 D_800A54D4[];
extern u8 D_800A52DC[];
extern void (*D_800A5594[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task) {
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

StageTask *func_800A4CF0(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5594[0]();
    return task;
}

void func_800A4D4C(void) {
    FLAGS_00.applyAction(0x7C16, 1);
}

void func_800A4D78(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x2A0;
    D_800990B4.unkC = 0x2A10000;
    D_800990B4.unk10 = D_800A52DC;
    D_800990B4.unk14 = D_800A54D4;
    D_800990B4.unk1C = 0x315;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x25900;
    D_800990B4.unk30 = 0x1AB00;
    D_800990B4.unk28 = D_800A5144;
    D_800990B4.unk3C = 0x41;
    D_800990B4.unk40 = 0x61040000;
    D_800990B4.unk4C = D_800A52C8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5128;
    D_800990B4.events = D_800A5598;
    D_8009A70C.unk40(0, 0x2A10001);
    D_8009A70C.unk40(7, 0x2A10002);
    D_8009A70C.unk40(4, 0x2A10003);
    D_8009A70C.unk50(0);
}
