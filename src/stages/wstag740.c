#include "common.h"
#include "stage.h"
extern void (*D_800A60F0[])(void);
void func_800A4F5C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4F30);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A4F5C);

StageTask *func_800A4FFC(void *owner) {
    StageTask *task = func_800144DC(func_800A4F5C, sizeof(StageTask), 4);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5460);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A548C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A54B8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A54E4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5510);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A553C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5568);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5594);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A55C0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A55EC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5618);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5644);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5670);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A569C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A56C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A56F4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag740", func_800A5720);
