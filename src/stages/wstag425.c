#include "common.h"
#include "stage.h"
extern u8 D_800A5448[];
extern u8 D_800A4E2C[];
extern u8 D_800A5620[];
extern u8 D_800A5494[];
extern void (*D_800A56B0[])(void);
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
    D_800A56B0[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xD4;
    D_800990B4.unk8 = 0x23D;
    D_800990B4.unkC = 0x2450000;
    D_800990B4.unk10 = D_800A5494;
    D_800990B4.unk14 = D_800A5620;
    D_800990B4.unk1C = 0x321;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1A200;
    D_800990B4.unk30 = 0x17A00;
    D_800990B4.unk28 = D_800A4E2C;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A5448;
    D_8009A70C.unk40(0, 0x2450001);
    D_8009A70C.unk40(7, 0x2450002);
    D_8009A70C.unk50(0);
}
