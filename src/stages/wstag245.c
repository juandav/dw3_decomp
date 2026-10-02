#include "common.h"
#include "stage.h"
extern u8 D_800A7068[];
extern u8 D_800A6D54[];
extern u8 D_800A4F50[];
extern u8 D_800A6FBC[];
extern u8 D_800A6ED0[];
extern void (*D_800A7064[])(void);
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
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A7064[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xF0;
    D_800990B4.unk8 = 0x198;
    D_800990B4.unkC = 0x1990000;
    D_800990B4.unk10 = D_800A6ED0;
    D_800990B4.unk14 = D_800A6FBC;
    D_800990B4.unk1C = 0x314;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x15A00;
    D_800990B4.unk30 = 0x18E00;
    D_800990B4.unk28 = D_800A4F50;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A6D54;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A7068;
    D_8009A70C.unk40(0, 0x1990002);
    D_8009A70C.unk40(7, 0x1990001);
    D_8009A70C.unk50(0);
}
