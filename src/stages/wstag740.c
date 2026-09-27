#include "common.h"
#include "stage.h"
extern void (*D_800A60F0[])(void);
void func_800A4F5C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4F30);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4F5C);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A53C8);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5720);
