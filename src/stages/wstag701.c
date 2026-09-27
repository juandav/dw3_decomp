#include "common.h"
#include "stage.h"
extern u8 D_800A51F4[];
extern u8 D_800A5140[];
extern u8 D_800A4ED0[];
extern u8 D_800A51C0[];
extern u8 D_800A5164[];
extern void (*D_800A51F0[])(void);
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
    D_800A51F0[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x7C1B, 1);
}

void func_800A4D74(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x659;
    D_800990B4.unkC = 0x65A0000;
    D_800990B4.unk10 = D_800A5164;
    D_800990B4.unk14 = D_800A51C0;
    D_800990B4.unk1C = 0x658;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x14400;
    D_800990B4.unk30 = 0xF700;
    D_800990B4.unk28 = D_800A4ED0;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A5140;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A51F4;
    D_8009A70C.unk40(0, 0x65A0001);
    D_8009A70C.unk40(7, 0x65A0002);
    D_8009A70C.unk50(0);
}
