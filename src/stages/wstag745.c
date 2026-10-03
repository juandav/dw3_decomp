#include "common.h"
#include "stage.h"
extern void (*D_800A6388[])(void);
void func_800A5070();
extern AnimFrame D_800A5BA0[];
extern AnimFrame D_800A5B88[];
extern StageEffectSpot D_800A5AA4[];
void *func_800A4EB8(void);
StageEffect *func_800A5734(s32 x, s32 y, s32 frame);

/* The flash: a white screen drawn while in TASK_DONE (GAME.unk26E8 is set then) */
void func_800A4CA4(StageTask *task) {
    Layer *layer;
    u_long *ot;
    POLY_F4 *poly;
    DR_TPAGE *mode;

    if (task->state == TASK_INIT) {
        if (GAME.unk26E8 != 0) {
            task->setState(task, TASK_DONE);
        } else {
            task->setState(task, TASK_RUN);
        }
    }
    switch (task->state) {
    case TASK_RUN:
        if (task->key1 != 0) {
            if (task->substate != 5) {
                task->nextSubstate(task);
            } else {
                task->key1 = 0;
                task->setState(task, TASK_DONE);
                SOUND.playSound(0x800410BD);
            }
        }
        GAME.unk26E8 = 0;
        break;
    case TASK_DONE:
        layer = GFX.funcs.getLayer(0x1002);
        ot = (u_long *)layer->getOtEntry(layer, 6);
        poly = GFX.funcs.getPrim();
        setlen(poly, 5);
        poly->code = 0x2A;
        poly->r0 = poly->g0 = poly->b0 = 0xFF;
        poly->x1 = poly->x3 = 320;
        poly->x0 = poly->x2 = 0;
        poly->y0 = poly->y1 = 0;
        poly->y2 = poly->y3 = 256;
        addPrim(ot, poly);
        mode = (DR_TPAGE *)(poly + 1);
        setlen(mode, 1);
        mode->code[0] = 0xE1000245;
        addPrim(ot, mode);
        GFX.funcs.setPrim(mode + 1);
        GAME.unk26E8 = 1;
        break;
    case TASK_INIT:
    case TASK_KILL:
        break;
    }
}

/* Creates the flash task (id 0x18) */
void *func_800A4EB8(void) {
    return createTaskWithId(func_800A4CA4, sizeof(StageTask), 0, 0x18);
}

/* Turns the flash off (TASK_RUN) */
s32 func_800A4EE8(void) {
    StageTask *task = TASK_FUNCS.find(0x18, -1, -1);

    if (task != NULL) {
        if (task->state != TASK_RUN) {
            SOUND.playSound(0x800410BD);
        }
        task->setState(task, TASK_RUN);
        task->key1 = 0;
    }
    return 0;
}

/* Turns the flash on (TASK_DONE) */
s32 func_800A4F68(void) {
    StageTask *task = TASK_FUNCS.find(0x18, -1, -1);

    if (task != NULL) {
        if (task->state != TASK_DONE) {
            SOUND.playSound(0x800410BD);
        }
        task->setState(task, TASK_DONE);
        task->key1 = 0;
    }
    return 0;
}

/* Turns the flash off and starts its countdown (TASK_RUN, key1 = 1) */
s32 func_800A4FE8(void) {
    StageTask *task = TASK_FUNCS.find(0x18, -1, -1);

    if (task != NULL) {
        if (task->state != TASK_RUN) {
            SOUND.playSound(0x800410BD);
        }
        task->setState(task, TASK_RUN);
        task->key1 = 1;
    }
    return 0;
}

/* Creates the stage's twenty effects, another object and the event object of flags 0x4041/0x4042 */
void func_800A5070(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        children[20] = func_800A4EB8();
        for (i = 0; i < 20; i++) {
            if (D_800A5AA4[i].kind == 0) {
                children[i] = func_800A5734(D_800A5AA4[i].x, D_800A5AA4[i].y, D_800A5AA4[i].frame);
            }
        }
        if (FLAGS_00.checkCondition(0x4041, 1) && FLAGS_00.checkCondition(0x4042, 0)) {
            children[21] = func_80084B80(0x32B);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A517C(void *owner) {
    StageTask *task = createTask(func_800A5070, sizeof(StageTask), 0x58);

    task->owner = owner;
    D_800A6388[0]();
    return task;
}

s32 func_800A51D8(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        anim->timer -= dt;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A51D8(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A52F8(StageEffect *task, void *arg, s32 idx) {
    SpriteDrawer drawer;
    Layer *layer = arg;
    StageSprite *sprite = &task->sprites[idx];
    s32 y = task->y;
    s32 x = task->x;
    s32 depth;

    if (idx == 1) {
        y -= 0x20;
        depth = 4;
    } else {
        depth = 6;
    }
    initSpriteDrawer(&drawer);
    drawer.setTexture(0x140, 0x100);
    drawer.setLayer(layer, depth);
    drawer.setClutRow(sprite->clutRow);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), sprite->frame, x, y);
}

s32 func_800A53E0(s32 x, s32 y, s32 w, s32 h) {
    RECT rect;
    struct Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getViewRect(layer, &rect);
    if (x + w < rect.x) {
        return 0;
    }
    if (rect.x + rect.w < x) {
        return 0;
    }
    if (y + h < rect.y) {
        return 0;
    }
    return rect.y + rect.h >= y;
}

void func_800A54A4(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A5BA0[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A5B88[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A51D8(&task->clutAnim, D_800A5B88, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A53E0(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A52F8, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A5BA0[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A5B88[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A51D8(&task->clutAnim, D_800A5B88, 0, 0);
        done = 0;
        frame = func_800A51D8(&task->anim, D_800A5BA0, 1, 0);
        switch (frame) {
        case 0xFF:
            task->sprites[1].frame = 0;
            done = 1;
            break;
        case 0x12C:
            task->sprites[1].frame = 0;
            break;
        default:
            task->sprites[1].frame = task->frame + frame;
            break;
        }
        if (done) {
            task->setState(task, TASK_RUN);
        }
        if (task->sprites[0].frame != 0 && func_800A53E0(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A52F8, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A53E0(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A52F8, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A5734(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A54A4, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

void func_800A5790(void) {
    FLAGS_00.applyAction(0x4041, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

/* Sets flags 0x88A3 and 0x4042 */
void func_800A57DC(void) {
    FLAGS_00.applyAction(0x88A3, 1);
    FLAGS_00.applyAction(0x4042, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag745", func_800A5828);

void func_800A5828();
void func_800A57DC();
extern s32 D_800A5BF8[];
extern s32 D_800A5C04[];
extern s32 D_800A5C10[];
extern s32 D_800A5C1C[];
extern s32 D_800A5C28[];
extern s32 D_800A5C34[];
extern s32 D_800A5C40[];
extern s32 D_800A5C4C[];
extern s32 D_800A5C7C[];
extern s32 D_800A5C88[];
extern s32 D_800A5C94[];
extern s32 D_800A5CA0[];
extern s32 D_800A5CAC[];
extern s32 D_800A5CB8[];
extern s32 D_800A5CC4[];
extern s32 D_800A5CD0[];
extern s32 D_800A5D00[];
extern s32 D_800A5D0C[];
extern s32 D_800A5D18[];
extern s32 D_800A5D24[];
extern s32 D_800A5D30[];
extern s32 D_800A5D3C[];
extern s32 D_800A5D48[];
extern s32 D_800A5D54[];
extern s32 D_800A5D84[];
extern s32 D_800A5D90[];
extern s32 D_800A5D9C[];
extern s32 D_800A5DA8[];
extern s32 D_800A5DB4[];
extern s32 D_800A5DC0[];
extern s32 D_800A5DCC[];
extern s32 D_800A5DD8[];
extern s32 D_800A5C58[];
extern s32 D_800A5CDC[];
extern s32 D_800A5D60[];
extern s32 D_800A5DE4[];
extern s32 D_800A5EB4[];
extern s32 D_800A5F54[];
extern s32 D_800A5EC4[];
extern s32 D_800A5F5C[];
extern s32 D_800A5EDC[];
extern s32 D_800A5F64[];
extern s32 D_800A5EF4[];
extern s32 D_800A5F6C[];
extern s32 D_800A5F0C[];
extern s32 D_800A5F74[];
extern s32 D_800A5F24[];
extern s32 D_800A5F80[];
extern s32 D_800A5F3C[];
extern s32 D_800A5F8C[];
extern s32 D_800A5FA0[];
extern s32 D_800A5FB4[];
extern s32 D_800A5FC8[];
extern s32 D_800A5FDC[];
extern s32 D_800A5FF0[];
extern s32 D_800A5954[];
extern s32 D_800A59EC[];

s32 D_800A5954[] = {
    0x10600, 0x1020002, 0x1030002, 0x300DA,
    0xCA0100, 0xD100F0, 0xCA0101, 0x70001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x30001, 0x1E0300, 512, 0xCA0001,
    0x3010002, 0x1E0300, 512, 0x20002,
    0x1010001, 0x70002, 0x3010003, 0x20101,
    0x30001, 0x1E0300, 512, 0xCA0003,
    0x3010002, 512, 0x20004, 0x1010001,
    0x70002, 0x3010003, 0x20101, 0x30001,
    0x1E0300,
#if VERSION_US
    0,
#elif VERSION_EU
    0x40000,
#endif
};
s32 D_800A59EC[] = {
    0x10600, 0x10000CA, 0x1030002, 0x10100DA,
    0x10002, 0x1000003, 0xF000CA, 0x10100D1,
    0x100CA, 0x3000007, 0x2000078, 0x10000,
    0x200CA, 0x3000301, 0x101001E, 0x100CA,
    0x3000005, 0x102001E, 0x10F00CA, 0x500C1,
    0xCA0302, 0xCA0101, 0x10001, 0x1E0300,
    0x20102, 0xD100F0, 0x3020003, 0x1010002,
    0x10002, 0x3000005, 0x200001E, 0x20000,
    0x200CA, 0x3000301, 0x200001E, 0x30000,
    2, 0x20101, 0x50007, 0x1010301,
    0x10002, 0x3000005, 0x600001E, 0x20001,
    0x1E0300, 0,
};
StageEffectSpot D_800A5AA4[] = {
    { 68, 0, 188, 0x1C4 },
    { 68, 0, 0x11C, 0x154 },
    { 68, 0, 0x11C, 0x254 },
    { 68, 0, 0x15C, 0x1F4 },
    { 68, 0, 0x1BC, 0x184 },
    { 68, 0, 0x1BC, 0x244 },
    { 68, 0, 0x1DC, 0x1B4 },
    { 68, 0, 0x1DC, 0x2B4 },
    { 68, 0, 0x1FC, 0x124 },
    { 68, 0, 0x1FC, 0x224 },
    { 68, 0, 0x25C, 0x174 },
    { 68, 0, 0x27C, 0x1E4 },
    { 68, 0, 0x27C, 0x224 },
    { 68, 0, 0x27C, 0x2E4 },
    { 68, 0, 0x29C, 0x254 },
    { 68, 0, 0x2DC, 0x174 },
    { 68, 0, 0x2FC, 0x2A4 },
    { 68, 0, 0x31C, 0x214 },
    { 20, 0, 0x3AC, 0x2A4 },
};
AnimFrame D_800A5B88[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A5BA0[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A5BF8[] = {
    120, 26, 0x60080000,
};
s32 D_800A5C04[] = {
    120, 26, 0x60080000,
};
s32 D_800A5C10[] = {
    121, 26, 0x60080000,
};
s32 D_800A5C1C[] = {
    121, 26, 0x60080000,
};
s32 D_800A5C28[] = {
    171, 26, 0x60080000,
};
s32 D_800A5C34[] = {
    171, 26, 0x60080000,
};
s32 D_800A5C40[] = {
    171, 26, 0x60080000,
};
s32 D_800A5C4C[] = {
    171, 26, 0x60080000,
};
s32 D_800A5C58[] = {
    2, (s32)D_800A5BF8, (s32)D_800A5C04, (s32)D_800A5C10,
    (s32)D_800A5C1C, (s32)D_800A5C28, (s32)D_800A5C34, (s32)D_800A5C40,
    (s32)D_800A5C4C,
};
s32 D_800A5C7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CDC[] = {
    0, (s32)D_800A5C7C, (s32)D_800A5C88, (s32)D_800A5C94,
    (s32)D_800A5CA0, (s32)D_800A5CAC, (s32)D_800A5CB8, (s32)D_800A5CC4,
    (s32)D_800A5CD0,
};
s32 D_800A5D00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D60[] = {
    0, (s32)D_800A5D00, (s32)D_800A5D0C, (s32)D_800A5D18,
    (s32)D_800A5D24, (s32)D_800A5D30, (s32)D_800A5D3C, (s32)D_800A5D48,
    (s32)D_800A5D54,
};
s32 D_800A5D84[] = {
    21, 26, 0x608C0000,
};
s32 D_800A5D90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DE4[] = {
    0, (s32)D_800A5D84, (s32)D_800A5D90, (s32)D_800A5D9C,
    (s32)D_800A5DA8, (s32)D_800A5DB4, (s32)D_800A5DC0, (s32)D_800A5DCC,
    (s32)D_800A5DD8,
};
s32 D_800A5E08[] = {
    89, 0, 0, (s32)D_800A5C58,
    (s32)D_800A5CDC, (s32)D_800A5D60, (s32)D_800A5DE4,
};
s32 D_800A5E24[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000178, 224, 0x1FB0170,
    0x1000140, 0x1800170, 0x8000C0, 0x1FA0150,
    0x1000140, 0x1600140, 0x600000, 0x1FA0160,
};
s32 D_800A5EB4[] = {
    0x17091, 0x10238, 0x17013, 65535,
};
s32 D_800A5EC4[] = {
    0, (s32)D_800A5EB4, 623, 0,
    0, 0,
};
s32 D_800A5EDC[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A5EF4[] = {
    0, 0, 525, 0,
    0, 0,
};
s32 D_800A5F0C[] = {
    0, 0, 523, 0,
    0, 0,
};
s32 D_800A5F24[] = {
    0, 0, 522, 0,
    0, 0,
};
s32 D_800A5F3C[] = {
    0, 0, 522, 0,
    0, 0,
};
s32 D_800A5F54[] = {
    568, 65535,
};
s32 D_800A5F5C[] = {
    0x1701A, 65535,
};
s32 D_800A5F64[] = {
    0x1602B, 65535,
};
s32 D_800A5F6C[] = {
    0x16026, 65535,
};
s32 D_800A5F74[] = {
    16450, 0x17019, 65535,
};
s32 D_800A5F80[] = {
    0x14042, 0x17019, 65535,
};
s32 D_800A5F8C[] = {
    (s32)D_800A5F54, (s32)D_800A5EC4, 0x40021, 0xE90311,
    1,
};
s32 D_800A5FA0[] = {
    (s32)D_800A5F5C, (s32)D_800A5EDC, 0x5009D, 0xC1010F,
    1,
};
s32 D_800A5FB4[] = {
    (s32)D_800A5F64, (s32)D_800A5EF4, 0x600CA, 0xC1010F,
    1,
};
s32 D_800A5FC8[] = {
    (s32)D_800A5F6C, (s32)D_800A5F0C, 0x600CA, 0xC1010F,
    1,
};
s32 D_800A5FDC[] = {
    (s32)D_800A5F74, (s32)D_800A5F24, 0x600CA, 0xD100F0,
    7,
};
s32 D_800A5FF0[] = {
    (s32)D_800A5F80, (s32)D_800A5F3C, 0x600CA, 0xC1010F,
    1,
};
s32 D_800A6004[] = {
    (s32)D_800A5F8C, (s32)D_800A5FA0, (s32)D_800A5FB4, (s32)D_800A5FC8,
    (s32)D_800A5FDC, (s32)D_800A5FF0, 0,
};
s32 D_800A6020[] = {
    0x6400001, 0xF000232, 0xD00004, 361,
    0x10000, 0x2320640, 0x40F00, 0x1D900F0,
    0, 0x6400001, 0xF000232, 0x1700004,
    409, 0x10000, 0x2320640, 0x40F00,
    0x2090190, 0, 0x6400001, 0xF000232,
    0x1B00004, 633, 0x10000, 0x2320640,
    0x40F00, 0x15901F0, 0, 0x6400001,
    0xF000232, 0x2100004, 457, 0x10000,
    0x2320640, 0x40F00, 0x2390230, 0,
    0x6400001, 0xF000232, 0x2500004, 681,
    0x10000, 0x2320640, 0x40F00, 0x1890290,
    0, 0x6400001, 0xF000232, 0x2B00004,
    505, 0x10000, 0x2320640, 0x40F00,
    0x26902D0, 0, 0x6400001, 0xF000232,
    0x2F00004, 729, 0x10000, 0x2320640,
    0x40F00, 0x2290350, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A6130[] = {
    65535, 65535, 0x26B0001, 0x33C00D0,
    5, 0, 65535, 65535,
    0x26D0001, 0x25401E8, 3, 0,
    0x18011, 16449, 0x32A0008, 0,
    0, 0, 65535, 65535,
    0x1F400008, 0, 0, 0,
    65535, 65535, 0x1F410008, 0,
    0, 0, 65535, 65535,
    0x1F420008, 0, 0, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x26C000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x26C000D, 0x2B003C0, 7, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6388[])(void) = {
    func_800A5828,
};
s32 D_800A638C[] = {
    810, (s32)D_800A5954,
#if VERSION_US
    0x143000E,
#elif VERSION_EU
    0x14A000E,
#endif
    0, (s32)func_800A5790, 811, (s32)D_800A59EC,
#if VERSION_US
    0x143000F,
#elif VERSION_EU
    0x14A000F,
#endif
    0, (s32)func_800A57DC, 8000, 0,
    0, (s32)func_800A4EE8, 0, 8001,
    0, 0, (s32)func_800A4F68, 0,
    8002, 0, 0, (s32)func_800A4FE8,
    0, -1, 0, 0,
    0, 0,
};
