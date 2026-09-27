#include "stdgname.h"

void func_80082724(Task *task, void **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x5000);
        GFX.funcs.setDisplayMode(320, 240, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 320;
        rect.h = 240;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        *children = func_80085B20();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_8008281C);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082848);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800828D0);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082A14);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082AC8);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082B10);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082BA4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082C10);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082E00);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80083104);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80083A30);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084640);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084744);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084750);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800847E4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800848E4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800848F0);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084998);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084B0C);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800850E0);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085354);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800856B4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800856F4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800858D8);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800859CC);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085ADC);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085B20);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085B60);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085C08);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085C78);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085D0C);
