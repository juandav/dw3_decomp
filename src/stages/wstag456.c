#include "common.h"
#include "stage.h"
extern u8 D_800A507C[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5344[];
extern u8 D_800A5098[];
extern u8 D_800A550C[];
extern u8 D_800A536C[];
extern void (*D_800A5554[])(void);
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
    D_800A5554[0]();
    return task;
}

void func_800A4D4C(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x6D8;
    D_800990B4.unkC = 0x6D90000;
    D_800990B4.unk10 = D_800A536C;
    D_800990B4.unk14 = D_800A550C;
    D_800990B4.unk1C = 0x6D7;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x15E00;
    D_800990B4.unk30 = 0xD800;
    D_800990B4.unk28 = D_800A5098;
    D_800990B4.unk3C = 0x34;
    D_800990B4.unk40 = 0x60D00000;
    D_800990B4.unk4C = D_800A5344;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A507C;
    D_8009A70C.unk40(0, 0x6D90001);
    D_8009A70C.unk40(7, 0x6D90002);
    D_8009A70C.unk40(4, 0x6D90003);
    D_8009A70C.unk50(0);
}
