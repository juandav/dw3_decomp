#include "common.h"
#include "stage.h"
void func_800A4DC4();
extern void (*D_800A61E4[])(void);
void func_800A543C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A4DC4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A5044);

void *func_800A5094(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x68, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A50C4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A50F8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A5240);

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A5410);

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A543C);

StageTask *func_800A5518(void *owner) {
    StageTask *task = createTask(func_800A543C, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A61E4[0]();
    return task;
}

void func_800A5574(void) {
    FLAGS_00.applyAction(0x4043, 1);
}

void func_800A55A0(void) {
    FLAGS_00.applyAction(0x1C05, 1);
    FLAGS_00.applyAction(0x4063, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag795", func_800A55EC);
