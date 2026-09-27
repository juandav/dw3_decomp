#include "common.h"
#include "stage.h"
extern CVECTOR D_800A4CA4;
extern u8 D_800A4F70[];
extern u8 D_800A4E4C[];
extern u8 D_800A50D8[];
extern u8 D_800A4F80[];
extern void (*D_800A5120[])(void);
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
    D_800A5120[0]();
    return task;
}

void func_800A4D4C(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x51E;
    D_800990B4.unkC = 0x51F0000;
    D_800990B4.unk10 = D_800A4F80;
    D_800990B4.unk14 = D_800A50D8;
    D_800990B4.unk1C = 0x51D;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x10100;
    D_800990B4.unk30 = 0x1C800;
    D_800990B4.unk28 = D_800A4E4C;
    D_800990B4.unk3C = 0x2C;
    D_800990B4.unk40 = 0x60B00000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A4F70;
    D_800990B4.unk38 = D_800A4CA4;
    D_8009A70C.unk40(0, 0x51F0001);
    D_8009A70C.unk40(7, 0x51F0002);
    D_8009A70C.unk50(0);
}
