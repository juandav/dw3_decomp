#include "common.h"
#include "stage.h"
extern u8 D_800A6054[];
extern u8 D_800A50F4[];
extern u8 D_800A5D00[];
extern u8 D_800A5110[];
extern u8 D_800A5EB8[];
extern u8 D_800A5D50[];
extern void (*D_800A6050[])(void);
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
    D_800A6050[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x7C19, 1);
}

void func_800A4D74(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x61E;
    D_800990B4.unkC = 0x61F0000;
    D_800990B4.unk10 = D_800A5D50;
    D_800990B4.unk14 = D_800A5EB8;
    D_800990B4.unk1C = 0x61D;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1CB00;
    D_800990B4.unk30 = 0x21100;
    D_800990B4.unk28 = D_800A5110;
    D_800990B4.unk3C = 0x16;
    D_800990B4.unk40 = 0x60580000;
    D_800990B4.unk4C = D_800A5D00;
    D_800990B4.unk20 = D_800A50F4;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6054;
    D_8009A70C.unk40(0, 0x61F0001);
    D_8009A70C.unk40(7, 0x61F0002);
    D_8009A70C.unk50(0);
}
