#include "common.h"
#include "stage.h"
extern u8 D_800A56DC[];
extern u8 D_800A52A0[];
extern u8 D_800A54F8[];
extern u8 D_800A52BC[];
extern u8 D_800A5678[];
extern u8 D_800A5510[];
extern void (*D_800A56D8[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x407E, 1) && FLAGS_00.checkCondition(0x407F, 0)) {
            children[0] = func_80084B80(0x50A);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4D44(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A56D8[0]();
    return task;
}

void func_800A4DA0(void) {
    FLAGS_00.applyAction(0x407E, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4DEC(void) {
    FLAGS_00.applyAction(0x407F, 1);
    FLAGS_00.applyAction(0x8B0E, 1);
}

void func_800A4E38(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x602;
    D_800990B4.unkC = 0x6030000;
    D_800990B4.unk10 = D_800A5510;
    D_800990B4.unk14 = D_800A5678;
    D_800990B4.unk1C = 0x601;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x2C000;
    D_800990B4.unk30 = 0x25C00;
    D_800990B4.unk28 = D_800A52BC;
    D_800990B4.unk3C = 0x39;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A54F8;
    D_800990B4.unk20 = D_800A52A0;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A56DC;
    D_8009A70C.unk40(0, 0x6030001);
    D_8009A70C.unk40(7, 0x6030002);
    D_8009A70C.unk40(4, 0x6030003);
    D_8009A70C.unk50(0);
}
