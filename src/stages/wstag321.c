#include "common.h"
#include "stage.h"
extern u8 D_800A5080[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A51A4[];
extern u8 D_800A509C[];
extern u8 D_800A5900[];
extern u8 D_800A51B0[];
extern void (*D_800A59A8[])(void);
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
    D_800A59A8[0]();
    return task;
}

void func_800A4D4C(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x52F;
    D_800990B4.unkC = 0x5300000;
    D_800990B4.unk10 = D_800A51B0;
    D_800990B4.unk14 = D_800A5900;
    D_800990B4.unk1C = 0x52E;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x31100;
    D_800990B4.unk30 = 0x22700;
    D_800990B4.unk28 = D_800A509C;
    D_800990B4.unk3C = 6;
    D_800990B4.unk40 = 0x60180000;
    D_800990B4.unk4C = D_800A51A4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5080;
    D_8009A70C.unk40(0, 0x5300001);
    D_8009A70C.unk40(7, 0x5300002);
    D_8009A70C.unk40(4, 0x5300003);
    D_8009A70C.unk50(0);
}
