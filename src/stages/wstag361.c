#include "common.h"
#include "stage.h"
extern u8 D_800A5288[];
extern u8 D_800A4FDC[];
extern u8 D_800A4EAC[];
extern u8 D_800A520C[];
extern u8 D_800A4FF0[];
extern void (*D_800A5284[])(void);
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
    D_800A5284[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xE9;
    D_800990B4.unk8 = 0x584;
    D_800990B4.unkC = 0x5850000;
    D_800990B4.unk10 = D_800A4FF0;
    D_800990B4.unk14 = D_800A520C;
    D_800990B4.unk1C = 0x583;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x17C00;
    D_800990B4.unk30 = 0x14F00;
    D_800990B4.unk28 = D_800A4EAC;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A4FDC;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5288;
    D_8009A70C.unk40(0, 0x5850001);
    D_8009A70C.unk40(7, 0x5850002);
    D_8009A70C.unk50(0);
}
