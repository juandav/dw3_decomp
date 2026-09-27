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

Task *func_8008281C(void) {
    return createTask(func_80082724, sizeof(Task), sizeof(void *));
}

void func_80082848(FadeTask *task, s32 fadeIn, s32 duration) {
    task->setState(task, TASK_RUN);
    task->substate = 1;
    task->fadeIn = fadeIn;
    if (fadeIn == 0) {
        task->level = 0;
        task->delta = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->delta = -(0xFF00 / duration);
    }
}

void func_800828D0(FadeTask *task) {
    Layer *layer = GFX.funcs.getLayer(task->layer);
    u_long *ot = (u_long *)layer->getOtEntry(layer, task->depth);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->code = 0x2A;
    poly->r0 = poly->g0 = poly->b0 = task->level >> 8;
    poly->x0 = poly->x2 = 0;
    poly->x1 = poly->x3 = 320;
    poly->y0 = poly->y1 = 0;
    poly->y2 = poly->y3 = 256;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = 0xE1000245;
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void func_80082A14(FadeTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->substate != 0) {
            task->level += task->delta;
            if (task->fadeIn == 0) {
                if (task->level > 0xFF00) {
                    task->level = 0xFF00;
                    task->state = TASK_DONE;
                }
            } else if (task->level < 0) {
                task->level = 0;
                task->state = TASK_DONE;
            }
            func_800828D0(task);
        }
        break;
    case TASK_DONE:
        func_800828D0(task);
        break;
    case TASK_KILL:
        break;
    }
}

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
