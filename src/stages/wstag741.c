#include "common.h"
#include "stage.h"
extern u8 D_800A6150[];
extern u8 D_800A5C18[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5E24[];
extern u8 D_800A5C34[];
extern u8 D_800A5F6C[];
extern u8 D_800A5E38[];
void func_800A4CA8();
extern void (*D_800A614C[])(void);
void func_800A4F5C();

INCLUDE_ASM("stages/nonmatchings/wstag741", func_800A4CA8);

void *func_800A4F30(void) {
    return createTask(func_800A4CA8, 0x54, 0xC);
}

void func_800A4F5C(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4084, 1) && FLAGS_00.checkCondition(0x4085, 0)) {
            children[1] = func_80084B80(0x510);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4FFC(void *owner) {
    StageTask *task = createTask(func_800A4F5C, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A614C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag741", func_800A5058);

INCLUDE_ASM("stages/nonmatchings/wstag741", func_800A5130);

INCLUDE_ASM("stages/nonmatchings/wstag741", func_800A51E8);

INCLUDE_ASM("stages/nonmatchings/wstag741", func_800A5380);

void func_800A53C8(void) {
    FLAGS_00.applyAction(0x4084, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5414(void) {
    FLAGS_00.applyAction(0x4085, 1);
    FLAGS_00.applyAction(0x8233, 1);
}

void func_800A5460(void) {
    FLAGS_00.applyAction(0x40BA, 1);
}

void func_800A548C(void) {
    FLAGS_00.applyAction(0x40BB, 1);
}

void func_800A54B8(void) {
    FLAGS_00.applyAction(0x40BC, 1);
}

void func_800A54E4(void) {
    FLAGS_00.applyAction(0x40BD, 1);
}

void func_800A5510(void) {
    FLAGS_00.applyAction(0x40BE, 1);
}

void func_800A553C(void) {
    FLAGS_00.applyAction(0x40BF, 1);
}

void func_800A5568(void) {
    FLAGS_00.applyAction(0x40C0, 1);
}

void func_800A5594(void) {
    FLAGS_00.applyAction(0x40C1, 1);
}

void func_800A55C0(void) {
    FLAGS_00.applyAction(0x40C2, 1);
}

void func_800A55EC(void) {
    FLAGS_00.applyAction(0x40C3, 1);
}

void func_800A5618(void) {
    FLAGS_00.applyAction(0x40C4, 1);
}

void func_800A5644(void) {
    FLAGS_00.applyAction(0x40C5, 1);
}

void func_800A5670(void) {
    FLAGS_00.applyAction(0x40C6, 1);
}

void func_800A569C(void) {
    FLAGS_00.applyAction(0x40C7, 1);
}

void func_800A56C8(void) {
    FLAGS_00.applyAction(0x40C8, 1);
}

void func_800A56F4(void) {
    FLAGS_00.applyAction(0x40C9, 1);
}

void func_800A5720(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x740;
    D_800990B4.unkC = 0x7410000;
    D_800990B4.unk10 = D_800A5E38;
    D_800990B4.unk14 = D_800A5F6C;
    D_800990B4.unk1C = 0x73F;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1CD00;
    D_800990B4.unk30 = 0x29A00;
    D_800990B4.unk28 = D_800A5C34;
    D_800990B4.unk3C = 0x19;
    D_800990B4.unk40 = 0x60640000;
    D_800990B4.unk4C = D_800A5E24;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5C18;
    D_800990B4.events = D_800A6150;
    D_8009A70C.unk40(0, 0x7410001);
    D_8009A70C.unk40(7, 0x7410002);
    D_8009A70C.unk40(4, 0x7410003);
    D_8009A70C.unk50(0);
}
