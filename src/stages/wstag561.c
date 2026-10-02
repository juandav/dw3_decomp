#include "common.h"
#include "stage.h"
extern u8 D_800A5444[];
extern u8 D_800A5108[];
extern u8 D_800A5260[];
extern u8 D_800A5124[];
extern u8 D_800A5380[];
extern u8 D_800A5270[];
extern void (*D_800A5440[])(void);
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
    D_800A5440[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x7C1A, 1);
}

void func_800A4D74(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x5C5;
    D_800990B4.unkC = 0x5C60000;
    D_800990B4.unk10 = D_800A5270;
    D_800990B4.unk14 = D_800A5380;
    D_800990B4.unk1C = 0x5C4;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x26F00;
    D_800990B4.unk30 = 0x1DF00;
    D_800990B4.unk28 = D_800A5124;
    D_800990B4.unk3C = 0x41;
    D_800990B4.unk40 = 0x61040000;
    D_800990B4.unk4C = D_800A5260;
    D_800990B4.unk20 = D_800A5108;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5444;
    D_8009A70C.unk40(0, 0x5C60001);
    D_8009A70C.unk40(7, 0x5C60002);
    D_8009A70C.unk40(4, 0x5C60003);
    D_8009A70C.unk50(0);
}
