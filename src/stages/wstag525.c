#include "common.h"
#include "stage.h"
extern u8 D_800A5CAC[];
extern u8 D_800A5528[];
extern u8 D_800A56C8[];
extern u8 D_800A5544[];
extern u8 D_800A5BB8[];
extern u8 D_800A56DC[];
extern void (*D_800A5CA8[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x402B, 1) && FLAGS_00.checkCondition(0x402C, 0)) {
            children[0] = func_80084B80(0x4FA);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4D44(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5CA8[0]();
    return task;
}

void func_800A4DA0(void) {
    FLAGS_00.applyAction(0x4003, 1);
}

void func_800A4DCC(void) {
    FLAGS_00.applyAction(0x402B, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4E18(void) {
    FLAGS_00.applyAction(0x402C, 1);
    FLAGS_00.applyAction(0x8013, 1);
}

void func_800A4E64(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x3B2;
    D_800990B4.unkC = 0x3B30000;
    D_800990B4.unk10 = D_800A56DC;
    D_800990B4.unk14 = D_800A5BB8;
    D_800990B4.unk1C = 0x3B1;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x18600;
    D_800990B4.unk30 = 0x18600;
    D_800990B4.unk28 = D_800A5544;
    D_800990B4.unk3C = 0x37;
    D_800990B4.unk40 = 0x60DC0000;
    D_800990B4.unk4C = D_800A56C8;
    D_800990B4.unk20 = D_800A5528;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5CAC;
    D_8009A70C.unk40(0, 0x3B30001);
    D_8009A70C.unk40(7, 0x3B30002);
    D_8009A70C.unk40(4, 0x3B30003);
    D_8009A70C.unk50(0);
}
