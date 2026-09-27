#include "common.h"
#include "stage.h"
extern u8 D_800A5060[];
extern u8 D_800A567C[];
extern u8 D_800A507C[];
extern u8 D_800A58C8[];
extern u8 D_800A56BC[];
extern void (*D_800A5988[])(void);
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
    D_800A5988[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x693;
    D_800990B4.unkC = 0x6940000;
    D_800990B4.unk10 = D_800A56BC;
    D_800990B4.unk14 = D_800A58C8;
    D_800990B4.unk1C = 0x692;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x37900;
    D_800990B4.unk30 = 0x10500;
    D_800990B4.unk28 = D_800A507C;
    D_800990B4.unk3C = 63;
    D_800990B4.unk40 = 0x60FC0000;
    D_800990B4.unk4C = D_800A567C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5060;
    D_8009A70C.unk40(0, 0x6940001);
    D_8009A70C.unk40(7, 0x6940002);
    D_8009A70C.unk40(4, 0x6940003);
    D_8009A70C.unk50(0);
}
