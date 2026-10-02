#include "common.h"
#include "stage.h"
extern u8 D_800A55DC[];
extern u8 D_800A703C[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A62A8[];
extern u8 D_800A55F8[];
extern u8 D_800A6F00[];
extern u8 D_800A630C[];
extern void (*D_800A7038[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x402D, 1) && FLAGS_00.checkCondition(0x402E, 0)) {
            children[0] = func_80084B80(0x4FC);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4D48(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A7038[0]();
    return task;
}

void func_800A4DA4(void) {
    FLAGS_00.applyAction(0x402D, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4DF0(void) {
    FLAGS_00.applyAction(0x402E, 1);
    FLAGS_00.applyAction(0x8168, 1);
}

void func_800A4E3C(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x503;
    D_800990B4.unkC = 0x4E80000;
    D_800990B4.unk10 = D_800A630C;
    D_800990B4.unk14 = D_800A6F00;
    D_800990B4.unk1C = 0x4E7;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x3C500;
    D_800990B4.unk30 = 0x3D200;
    D_800990B4.unk28 = D_800A55F8;
    D_800990B4.unk3C = 0xA;
    D_800990B4.unk40 = 0x60280000;
    D_800990B4.unk4C = D_800A62A8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.events = D_800A703C;
    D_800990B4.unk20 = D_800A55DC;
    D_8009A70C.unk40(0, 0x4E80001);
    D_8009A70C.unk40(7, 0x4E80002);
    D_8009A70C.unk50(0);
}
