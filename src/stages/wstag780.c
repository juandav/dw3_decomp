#include "common.h"
#include "stage.h"
void func_800A5668();
extern void (*D_800A80B4[])(void);
void func_800A6390();

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A4D84);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A4F20);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A4FF4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A508C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5220);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5250);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5344);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A53F0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A553C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5574);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5668);

void *func_800A57D8(void) {
    return createTask(func_800A5668, 0x60, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5804);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A589C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A58C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5A10);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5C88);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5E04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5E50);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A5E80);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A6174);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A6314);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A6360);

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A6390);

StageTask *func_800A6474(void *owner) {
    StageTask *task = createTask(func_800A6390, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A80B4[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A64D0);

void func_800A64DC(void) {
    FLAGS_00.applyAction(0x4066, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag780", func_800A6508);
