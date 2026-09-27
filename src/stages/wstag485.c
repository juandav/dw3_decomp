#include "common.h"
#include "stage.h"
extern u8 D_800A63FC[];
extern u8 D_800A5170[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5478[];
extern u8 D_800A518C[];
extern u8 D_800A62A8[];
extern u8 D_800A54A8[];
extern void (*D_800A63F8[])(void);
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
    D_800A63F8[0]();
    return task;
}

void func_800A4D4C(void) {
    FLAGS_00.applyAction(0x1C51, 1);
}

void func_800A4D78(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x3A5;
    D_800990B4.unkC = 0x3A60000;
    D_800990B4.unk10 = D_800A54A8;
    D_800990B4.unk14 = D_800A62A8;
    D_800990B4.unk1C = 0x3A4;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x59100;
    D_800990B4.unk30 = 0x2E900;
    D_800990B4.unk28 = D_800A518C;
    D_800990B4.unk3C = 0x36;
    D_800990B4.unk40 = 0x60D80000;
    D_800990B4.unk4C = D_800A5478;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5170;
    D_800990B4.events = D_800A63FC;
    D_8009A70C.unk40(0, 0x3A60001);
    D_8009A70C.unk40(7, 0x3A60002);
    D_8009A70C.unk40(4, 0x3A60003);
    D_8009A70C.unk50(0);
}
