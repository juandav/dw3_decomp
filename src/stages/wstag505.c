#include "common.h"
#include "stage.h"
extern u8 D_800A535C[];
extern u8 D_800A5224[];
extern u8 D_800A4EAC[];
extern u8 D_800A5328[];
extern u8 D_800A5260[];
extern void (*D_800A5358[])(void);
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
    D_800A5358[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xD4;
    D_800990B4.unk8 = 0x22C;
    D_800990B4.unkC = 0x22D0000;
    D_800990B4.unk10 = D_800A5260;
    D_800990B4.unk14 = D_800A5328;
    D_800990B4.unk1C = 0x3CB;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x28500;
    D_800990B4.unk30 = 0x1A200;
    D_800990B4.unk28 = D_800A4EAC;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A5224;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A535C;
    D_8009A70C.unk40(0, 0x22D0002);
    D_8009A70C.unk40(7, 0x22D0001);
    D_8009A70C.unk50(0);
}
