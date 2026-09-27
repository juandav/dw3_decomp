#include "common.h"
#include "stage.h"
extern void (*D_800A6594[])(void);
void func_800A5E70();

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4E54);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4E8C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4EBC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4FDC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A51D0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A51EC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A521C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5248);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5368);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5630);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A564C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A567C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A56A8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A57C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5804);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5974);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5AF0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5DCC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5DE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5E18);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5E70);

StageTask *func_800A5EE0(void *owner) {
    StageTask *task = func_800144DC(func_800A5E70, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6594[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5F3C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5F74);
