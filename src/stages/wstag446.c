#include "common.h"
#include "stage.h"
extern u8 D_800A5080[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A54FC[];
extern u8 D_800A509C[];
extern u8 D_800A565C[];
extern u8 D_800A5528[];
extern void (*D_800A56A4[])(void);
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
    D_800A56A4[0]();
    return task;
}

void func_800A4D4C(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x595;
    D_800990B4.unkC = 0x5960000;
    D_800990B4.unk10 = D_800A5528;
    D_800990B4.unk14 = D_800A565C;
    D_800990B4.unk1C = 0x594;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x10300;
    D_800990B4.unk30 = 0x13800;
    D_800990B4.unk28 = D_800A509C;
    D_800990B4.unk3C = 0x34;
    D_800990B4.unk40 = 0x60D00000;
    D_800990B4.unk4C = D_800A54FC;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5080;
    D_8009A70C.unk40(0, 0x5960001);
    D_8009A70C.unk40(7, 0x5960002);
    D_8009A70C.unk40(4, 0x5960003);
    D_8009A70C.unk50(0);
}
