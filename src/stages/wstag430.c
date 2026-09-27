#include "common.h"
#include "stage.h"
extern u8 D_800A5940[];
extern u8 D_800A5730[];
extern u8 D_800A4EAC[];
extern u8 D_800A58F4[];
extern u8 D_800A57C0[];
extern void (*D_800A593C[])(void);
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
    D_800A593C[0]();
    return task;
}

void func_800A4D48(void) {
    D_800990B4.unk44 = 0xD4;
    D_800990B4.unk8 = 0x212;
    D_800990B4.unkC = 0x2130000;
    D_800990B4.unk10 = D_800A57C0;
    D_800990B4.unk14 = D_800A58F4;
    D_800990B4.unk1C = 0x316;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x18300;
    D_800990B4.unk30 = 0x1E600;
    D_800990B4.unk28 = D_800A4EAC;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A5730;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5940;
    D_8009A70C.unk40(0, 0x2130001);
    D_8009A70C.unk40(7, 0x2130002);
    D_8009A70C.unk50(0);
}
