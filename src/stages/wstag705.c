#include "common.h"
#include "stage.h"
extern u8 D_800A505C[];
extern u8 D_800A55E0[];
extern u8 D_800A5078[];
extern u8 D_800A565C[];
extern u8 D_800A5600[];
extern void (*D_800A586C[])(void);
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
    D_800A586C[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x638;
    D_800990B4.unkC = 0x6390000;
    D_800990B4.unk10 = D_800A5600;
    D_800990B4.unk14 = D_800A565C;
    D_800990B4.unk1C = 0x637;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x4E400;
    D_800990B4.unk30 = 0x7B00;
    D_800990B4.unk28 = D_800A5078;
    D_800990B4.unk3C = 0x3E;
    D_800990B4.unk40 = 0x60F80000;
    D_800990B4.unk4C = D_800A55E0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A505C;
    D_8009A70C.unk40(0, 0x6390001);
    D_8009A70C.unk40(7, 0x6390002);
    D_8009A70C.unk40(4, 0x6390003);
    D_8009A70C.unk50(0);
}
