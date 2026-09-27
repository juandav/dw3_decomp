#include "common.h"
#include "stage.h"
extern u8 D_800A505C[];
extern u8 D_800A55E0[];
extern u8 D_800A5078[];
extern u8 D_800A5744[];
extern u8 D_800A5600[];
extern void (*D_800A5894[])(void);
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
    D_800A5894[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x75E;
    D_800990B4.unkC = 0x75F0000;
    D_800990B4.unk10 = D_800A5600;
    D_800990B4.unk14 = D_800A5744;
    D_800990B4.unk1C = 0x75D;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x33200;
    D_800990B4.unk30 = 0xD500;
    D_800990B4.unk28 = D_800A5078;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A55E0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A505C;
    D_8009A70C.unk40(0, 0x75F0001);
    D_8009A70C.unk40(7, 0x75F0002);
    D_8009A70C.unk40(4, 0x75F0003);
    D_8009A70C.unk50(0);
}
