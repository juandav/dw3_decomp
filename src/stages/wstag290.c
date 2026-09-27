#include "common.h"
#include "stage.h"
extern u8 D_800A5048[];
extern u8 D_800A51C0[];
extern u8 D_800A5064[];
extern u8 D_800A5448[];
extern u8 D_800A51D0[];
extern void (*D_800A54A8[])(void);
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
    D_800A54A8[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xF0;
    D_800990B4.unk8 = 0x29C;
    D_800990B4.unkC = 0x29D0000;
    D_800990B4.unk10 = D_800A51D0;
    D_800990B4.unk14 = D_800A5448;
    D_800990B4.unk1C = 0x31F;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1E000;
    D_800990B4.unk30 = 0x1D400;
    D_800990B4.unk28 = D_800A5064;
    D_800990B4.unk3C = 6;
    D_800990B4.unk40 = 0x60180000;
    D_800990B4.unk4C = D_800A51C0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5048;
    D_8009A70C.unk40(0, 0x29D0001);
    D_8009A70C.unk40(7, 0x29D0002);
    D_8009A70C.unk50(0);
}
