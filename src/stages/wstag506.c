#include "common.h"
#include "stage.h"
extern u8 D_800A523C[];
extern u8 D_800A511C[];
extern u8 D_800A4EAC[];
extern u8 D_800A5208[];
extern u8 D_800A5140[];
extern void (*D_800A5238[])(void);
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
    D_800A5238[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x5B1;
    D_800990B4.unkC = 0x5B20000;
    D_800990B4.unk10 = D_800A5140;
    D_800990B4.unk14 = D_800A5208;
    D_800990B4.unk1C = 0x5B0;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x27400;
    D_800990B4.unk30 = 0x1A400;
    D_800990B4.unk28 = D_800A4EAC;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A511C;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A523C;
    D_8009A70C.unk40(0, 0x5B20001);
    D_8009A70C.unk40(7, 0x5B20002);
    D_8009A70C.unk50(0);
}
