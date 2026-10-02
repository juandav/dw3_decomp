#include "common.h"
#include "stage.h"
extern u8 D_800A5B74[];
extern u8 D_800A51A4[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5608[];
extern u8 D_800A51C0[];
extern u8 D_800A5A38[];
extern u8 D_800A5648[];
extern void (*D_800A5B70[])(void);
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
    D_800A5B70[0]();
    return task;
}

void func_800A4D4C(void) {
    FLAGS_00.applyAction(0x40A8, 1);
}

void func_800A4D78(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x5AD;
    D_800990B4.unkC = 0x5AE0000;
    D_800990B4.unk10 = D_800A5648;
    D_800990B4.unk14 = D_800A5A38;
    D_800990B4.unk1C = 0x5AC;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x19500;
    D_800990B4.unk30 = 0xD000;
    D_800990B4.unk28 = D_800A51C0;
    D_800990B4.unk3C = 0x36;
    D_800990B4.unk40 = 0x60D80000;
    D_800990B4.unk4C = D_800A5608;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A51A4;
    D_800990B4.events = D_800A5B74;
    D_8009A70C.unk40(0, 0x5AE0001);
    D_8009A70C.unk40(7, 0x5AE0002);
    D_8009A70C.unk40(4, 0x5AE0003);
    D_8009A70C.unk50(0);
}
