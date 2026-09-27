#include "common.h"
#include "stage.h"
void func_800A4CA8();
extern void (*D_800A614C[])(void);
void func_800A4F5C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A4CA8);

void *func_800A4F30(void) {
    return createTask(func_800A4CA8, 0x54, 0xC);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A4F5C);

StageTask *func_800A4FFC(void *owner) {
    StageTask *task = createTask(func_800A4F5C, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A614C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A5058);

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A5130);

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A51E8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A5380);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag741", func_800A5720);
