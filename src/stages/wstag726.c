#include "common.h"
#include "stage.h"
extern u8 D_800A5060[];
extern u8 D_800A5468[];
extern u8 D_800A507C[];
extern u8 D_800A56AC[];
extern u8 D_800A54A0[];
extern void (*D_800A576C[])(void);
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
    D_800A576C[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x677;
    D_800990B4.unkC = 0x6780000;
    D_800990B4.unk10 = D_800A54A0;
    D_800990B4.unk14 = D_800A56AC;
    D_800990B4.unk1C = 0x676;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x37700;
    D_800990B4.unk30 = 0x10700;
    D_800990B4.unk28 = D_800A507C;
    D_800990B4.unk3C = 63;
    D_800990B4.unk40 = 0x60FC0000;
    D_800990B4.unk4C = D_800A5468;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5060;
    D_8009A70C.unk40(0, 0x6780001);
    D_8009A70C.unk40(7, 0x6780002);
    D_8009A70C.unk40(4, 0x6780003);
    D_8009A70C.unk50(0);
}
