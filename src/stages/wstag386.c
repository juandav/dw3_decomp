#include "common.h"
#include "stage.h"
extern u8 D_800A6558[];
extern u8 D_800A5E64[];
extern u8 D_800A51B4[];
extern u8 D_800A641C[];
extern u8 D_800A5EC4[];
extern void (*D_800A6554[])(void);
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
    D_800A6554[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xE9;
    D_800990B4.unk8 = 0x57C;
    D_800990B4.unkC = 0x57D0000;
    D_800990B4.unk10 = D_800A5EC4;
    D_800990B4.unk14 = D_800A641C;
    D_800990B4.unk1C = 0x57B;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x32500;
    D_800990B4.unk30 = 0x36900;
    D_800990B4.unk28 = D_800A51B4;
    D_800990B4.unk3C = 0xA;
    D_800990B4.unk40 = 0x60280000;
    D_800990B4.unk4C = D_800A5E64;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6558;
    D_8009A70C.unk40(0, 0x57D0001);
    D_8009A70C.unk40(7, 0x57D0002);
    D_8009A70C.unk50(0);
}
