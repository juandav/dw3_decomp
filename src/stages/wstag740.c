#include "common.h"
#include "stage.h"
extern u8 D_800A60F4[];
extern u8 D_800A5C04[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5DAC[];
extern u8 D_800A5C20[];
extern u8 D_800A5EF8[];
extern u8 D_800A5DC4[];
void func_800A4CA8();
extern void (*D_800A60F0[])(void);
void func_800A4F5C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4CA8);

void *func_800A4F30(void) {
    return createTask(func_800A4CA8, 0x54, 0xC);
}

void func_800A4F5C(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x403F, 1) && FLAGS_00.checkCondition(0x4040, 0)) {
            children[0] = func_80084B80(0x321);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4FFC(void *owner) {
    StageTask *task = createTask(func_800A4F5C, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A60F0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5058);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5130);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A51E8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5380);

void func_800A53C8(void) {
    FLAGS_00.applyAction(0x403F, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5414);

void func_800A5460(void) {
    FLAGS_00.applyAction(0x40AA, 1);
}

void func_800A548C(void) {
    FLAGS_00.applyAction(0x40AB, 1);
}

void func_800A54B8(void) {
    FLAGS_00.applyAction(0x40AC, 1);
}

void func_800A54E4(void) {
    FLAGS_00.applyAction(0x40AD, 1);
}

void func_800A5510(void) {
    FLAGS_00.applyAction(0x40AE, 1);
}

void func_800A553C(void) {
    FLAGS_00.applyAction(0x40AF, 1);
}

void func_800A5568(void) {
    FLAGS_00.applyAction(0x40B0, 1);
}

void func_800A5594(void) {
    FLAGS_00.applyAction(0x40B1, 1);
}

void func_800A55C0(void) {
    FLAGS_00.applyAction(0x40B2, 1);
}

void func_800A55EC(void) {
    FLAGS_00.applyAction(0x40B3, 1);
}

void func_800A5618(void) {
    FLAGS_00.applyAction(0x40B4, 1);
}

void func_800A5644(void) {
    FLAGS_00.applyAction(0x40B5, 1);
}

void func_800A5670(void) {
    FLAGS_00.applyAction(0x40B6, 1);
}

void func_800A569C(void) {
    FLAGS_00.applyAction(0x40B7, 1);
}

void func_800A56C8(void) {
    FLAGS_00.applyAction(0x40B8, 1);
}

void func_800A56F4(void) {
    FLAGS_00.applyAction(0x40B9, 1);
}

void func_800A5720(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x6CD;
    D_800990B4.unkC = 0x6CE0000;
    D_800990B4.unk10 = D_800A5DC4;
    D_800990B4.unk14 = D_800A5EF8;
    D_800990B4.unk1C = 0x6CC;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x12200;
    D_800990B4.unk30 = 0x2F400;
    D_800990B4.unk28 = D_800A5C20;
    D_800990B4.unk3C = 0x19;
    D_800990B4.unk40 = 0x60640000;
    D_800990B4.unk4C = D_800A5DAC;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5C04;
    D_800990B4.events = D_800A60F4;
    D_8009A70C.unk40(0, 0x6CE0001);
    D_8009A70C.unk40(7, 0x6CE0002);
    D_8009A70C.unk40(4, 0x6CE0003);
    D_8009A70C.unk50(0);
}
