#include "common.h"
#include "stage.h"
extern void (*D_800A63BC[])(void);
void func_800A5070();
extern AnimFrame D_800A5B74[];
extern AnimFrame D_800A5B5C[];
extern StageEffectSpot D_800A5A6C[];
void *func_800A4EB8(void);
StageEffect *func_800A5734(s32 x, s32 y, s32 frame);

INCLUDE_ASM("stages/nonmatchings/wstag746", func_800A4CA4);

void func_800A4CA4();

/* Creates the flash task (id 0x19) */
void *func_800A4EB8(void) {
    return createTaskWithId(func_800A4CA4, sizeof(StageTask), 0, 0x19);
}

/* Turns the flash off (TASK_RUN) */
s32 func_800A4EE8(void) {
    StageTask *task = TASK_FUNCS.find(0x19, -1, -1);

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
    StageTask *task = TASK_FUNCS.find(0x19, -1, -1);

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
    StageTask *task = TASK_FUNCS.find(0x19, -1, -1);

    if (task != NULL) {
        if (task->state != TASK_RUN) {
            SOUND.playSound(0x800410BD);
        }
        task->setState(task, TASK_RUN);
        task->key1 = 1;
    }
    return 0;
}

/* Creates the stage's twenty effects, another object and the event object of flags 0x4086/0x4087 */
void func_800A5070(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        children[20] = func_800A4EB8();
        for (i = 0; i < 20; i++) {
            if (D_800A5A6C[i].kind == 0) {
                children[i] = func_800A5734(D_800A5A6C[i].x, D_800A5A6C[i].y, D_800A5A6C[i].frame);
            }
        }
        if (FLAGS_00.checkCondition(0x4086, 1) && FLAGS_00.checkCondition(0x4087, 0)) {
            children[21] = func_80084B80(0x512);
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
    D_800A63BC[0]();
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
        task->anim.timer = D_800A5B74[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A5B5C[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A51D8(&task->clutAnim, D_800A5B5C, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A53E0(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A52F8, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A5B74[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A5B5C[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A51D8(&task->clutAnim, D_800A5B5C, 0, 0);
        done = 0;
        frame = func_800A51D8(&task->anim, D_800A5B74, 1, 0);
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
    FLAGS_00.applyAction(0x4086, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A57DC(void) {
    FLAGS_00.applyAction(0x4087, 1);
    FLAGS_00.applyAction(0x8F41, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag746", func_800A5828);

void func_800A5828();
extern s32 D_800A5BCC[];
extern s32 D_800A5BD8[];
extern s32 D_800A5BE4[];
extern s32 D_800A5BF0[];
extern s32 D_800A5BFC[];
extern s32 D_800A5C08[];
extern s32 D_800A5C14[];
extern s32 D_800A5C20[];
extern s32 D_800A5C50[];
extern s32 D_800A5C5C[];
extern s32 D_800A5C68[];
extern s32 D_800A5C74[];
extern s32 D_800A5C80[];
extern s32 D_800A5C8C[];
extern s32 D_800A5C98[];
extern s32 D_800A5CA4[];
extern s32 D_800A5CD4[];
extern s32 D_800A5CE0[];
extern s32 D_800A5CEC[];
extern s32 D_800A5CF8[];
extern s32 D_800A5D04[];
extern s32 D_800A5D10[];
extern s32 D_800A5D1C[];
extern s32 D_800A5D28[];
extern s32 D_800A5D58[];
extern s32 D_800A5D64[];
extern s32 D_800A5D70[];
extern s32 D_800A5D7C[];
extern s32 D_800A5D88[];
extern s32 D_800A5D94[];
extern s32 D_800A5DA0[];
extern s32 D_800A5DAC[];
extern s32 D_800A5C2C[];
extern s32 D_800A5CB0[];
extern s32 D_800A5D34[];
extern s32 D_800A5DB8[];
extern s32 D_800A5E88[];
extern s32 D_800A5E98[];
extern s32 D_800A5EA0[];
extern s32 D_800A5EA8[];
extern s32 D_800A5EB0[];
extern s32 D_800A5EB8[];
extern s32 D_800A5EC0[];
extern s32 D_800A5EC8[];
extern s32 D_800A5ED0[];
extern s32 D_800A5F98[];
extern s32 D_800A5ED8[];
extern s32 D_800A5FA0[];
extern s32 D_800A5EF0[];
extern s32 D_800A5FAC[];
extern s32 D_800A5F08[];
extern s32 D_800A5FB8[];
extern s32 D_800A5F20[];
extern s32 D_800A5FC8[];
extern s32 D_800A5F5C[];
extern s32 D_800A5FD8[];
extern s32 D_800A5FEC[];
extern s32 D_800A6000[];
extern s32 D_800A6014[];
extern s32 D_800A6028[];
extern s32 D_800A5954[];
extern s32 D_800A59EC[];

s32 D_800A5954[] = {
    0x10600, 0x1020002, 0x1030002, 0x300DA,
    0xCD0100, 0xD100F0, 0xCD0101, 0x70001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x30001, 0x1E0300, 512, 0xCD0001,
    0x3010002, 0x1E0300, 512, 0x20002,
    0x1010001, 0x70002, 0x3010003, 0x20101,
    0x30001, 0x1E0300, 512, 0xCD0003,
    0x3010002, 512, 0x20004, 0x1010001,
    0x70002, 0x3010003, 0x20101, 0x30001,
    0x1E0300, 0,
};
s32 D_800A59EC[] = {
    0x10600, 0x10000CD, 0x1030002, 0x10100DA,
    0x10002, 0x1000003, 0xF000CD, 0x10100D1,
    0x100CD, 0x3000007, 0x2000078, 0x10000,
    0x200CD, 0x1010301, 0x34A032D, 0x3000002,
    0x200003C, 0x20000, 2, 0x20101,
    0x30007, 0x1010301, 0x10002, 0x3000003,
    0x200001E, 0x30000, 205, 0x3000301,
    0x600001E, 0x20001, 0x1E0300,
#if VERSION_US
    0,
#elif VERSION_EU
    0x20000,
#endif
};
StageEffectSpot D_800A5A6C[] = {
    { 68, 0, 0x11B, 0x154 },
    { 68, 0, 0x13C, 0x1C4 },
    { 68, 0, 0x15C, 0x1F4 },
    { 68, 0, 0x15C, 0x234 },
    { 68, 0, 0x1BC, 0x104 },
    { 68, 0, 0x1BC, 0x184 },
    { 68, 0, 0x1DC, 0x1B4 },
    { 68, 0, 0x1DC, 0x2B4 },
    { 68, 0, 0x1FC, 0x224 },
    { 68, 0, 0x1FC, 0x264 },
    { 68, 0, 0x23C, 0x144 },
    { 68, 0, 0x25C, 0x1B4 },
    { 68, 0, 0x27C, 0x224 },
    { 68, 0, 0x29C, 0x294 },
    { 68, 0, 0x2BC, 0x2C4 },
    { 68, 0, 0x2DC, 0x234 },
    { 68, 0, 0x2FC, 0x1A4 },
    { 68, 0, 0x31C, 0x1D4 },
    { 68, 0, 0x31C, 0x214 },
    { 20, 0, 0x3AC, 0x2A4 },
};
AnimFrame D_800A5B5C[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A5B74[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A5BCC[] = {
    181, 26, 0x60080000,
};
s32 D_800A5BD8[] = {
    181, 26, 0x60080000,
};
s32 D_800A5BE4[] = {
    181, 26, 0x60080000,
};
s32 D_800A5BF0[] = {
    181, 26, 0x60080000,
};
s32 D_800A5BFC[] = {
    142, 26, 0x60080000,
};
s32 D_800A5C08[] = {
    142, 26, 0x60080000,
};
s32 D_800A5C14[] = {
    142, 26, 0x60080000,
};
s32 D_800A5C20[] = {
    142, 26, 0x60080000,
};
s32 D_800A5C2C[] = {
    2, (s32)D_800A5BCC, (s32)D_800A5BD8, (s32)D_800A5BE4,
    (s32)D_800A5BF0, (s32)D_800A5BFC, (s32)D_800A5C08, (s32)D_800A5C14,
    (s32)D_800A5C20,
};
s32 D_800A5C50[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C74[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C80[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C98[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CB0[] = {
    0, (s32)D_800A5C50, (s32)D_800A5C5C, (s32)D_800A5C68,
    (s32)D_800A5C74, (s32)D_800A5C80, (s32)D_800A5C8C, (s32)D_800A5C98,
    (s32)D_800A5CA4,
};
s32 D_800A5CD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D28[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D34[] = {
    0, (s32)D_800A5CD4, (s32)D_800A5CE0, (s32)D_800A5CEC,
    (s32)D_800A5CF8, (s32)D_800A5D04, (s32)D_800A5D10, (s32)D_800A5D1C,
    (s32)D_800A5D28,
};
s32 D_800A5D58[] = {
    29, 26, 0x608C0000,
};
s32 D_800A5D64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DB8[] = {
    0, (s32)D_800A5D58, (s32)D_800A5D64, (s32)D_800A5D70,
    (s32)D_800A5D7C, (s32)D_800A5D88, (s32)D_800A5D94, (s32)D_800A5DA0,
    (s32)D_800A5DAC,
};
s32 D_800A5DDC[] = {
    122, 0, 0, (s32)D_800A5C2C,
    (s32)D_800A5CB0, (s32)D_800A5D34, (s32)D_800A5DB8,
};
s32 D_800A5DF8[] = {
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
s32 D_800A5E88[] = {
    0x1025D, 0x18B0E, 0x17013, 65535,
};
s32 D_800A5E98[] = {
    0x1701D, 65535,
};
s32 D_800A5EA0[] = {
    0x16025, 65535,
};
s32 D_800A5EA8[] = {
    0x16026, 65535,
};
s32 D_800A5EB0[] = {
    0x1602B, 65535,
};
s32 D_800A5EB8[] = {
    0x1701D, 65535,
};
s32 D_800A5EC0[] = {
    0x16025, 65535,
};
s32 D_800A5EC8[] = {
    0x16026, 65535,
};
s32 D_800A5ED0[] = {
    0x1602B, 65535,
};
s32 D_800A5ED8[] = {
    0, (s32)D_800A5E88, 397, 0,
    0, 0,
};
s32 D_800A5EF0[] = {
    0, 0, 537, 0,
    0, 0,
};
s32 D_800A5F08[] = {
    0, 0, 537, 0,
    0, 0,
};
s32 D_800A5F20[] = {
    (s32)D_800A5E98, 0, 534, (s32)D_800A5EA0,
    0, 535, (s32)D_800A5EA8, 0,
    536, (s32)D_800A5EB0, 0, 538,
    0, 0, 0,
};
s32 D_800A5F5C[] = {
    (s32)D_800A5EB8, 0, 534, (s32)D_800A5EC0,
    0, 535, (s32)D_800A5EC8, 0,
    536, (s32)D_800A5ED0, 0, 538,
    0, 0, 0,
};
s32 D_800A5F98[] = {
    605, 65535,
};
s32 D_800A5FA0[] = {
    16519, 0x1701A, 65535,
};
s32 D_800A5FAC[] = {
    0x1701A, 0x14087, 65535,
};
s32 D_800A5FB8[] = {
    28698, 16519, 0x17008, 65535,
};
s32 D_800A5FC8[] = {
    28698, 0x14087, 0x17008, 65535,
};
s32 D_800A5FD8[] = {
    (s32)D_800A5F98, (s32)D_800A5ED8, 0x40021, 0xE90311,
    1,
};
s32 D_800A5FEC[] = {
    (s32)D_800A5FA0, (s32)D_800A5EF0, 0x5009D, 0xD100F0,
    7,
};
s32 D_800A6000[] = {
    (s32)D_800A5FAC, (s32)D_800A5F08, 0x5009D, 0xD100F0,
    7,
};
s32 D_800A6014[] = {
    (s32)D_800A5FB8, (s32)D_800A5F20, 0x600CD, 0xD100F0,
    7,
};
s32 D_800A6028[] = {
    (s32)D_800A5FC8, (s32)D_800A5F5C, 0x600CD, 0xD100F0,
    7,
};
s32 D_800A603C[] = {
    (s32)D_800A5FD8, (s32)D_800A5FEC, (s32)D_800A6000, (s32)D_800A6014,
    (s32)D_800A6028, 0,
};
s32 D_800A6054[] = {
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
s32 D_800A6164[] = {
    65535, 65535, 0x2D30001, 0x33C00D0,
    5, 0, 16518, 28698,
    0x5110008, 0, 0, 0,
    65535, 65535, 0x1F400008, 0,
    0, 0, 65535, 65535,
    0x1F410008, 0, 0, 0,
    65535, 65535, 0x1F420008, 0,
    0, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0x2D4000D, 0x2B003C0,
    7, 0, 65535, 65535,
    0x2D4000D, 0x2B003C0, 7, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A63BC[])(void) = {
    func_800A5828,
};
s32 D_800A63C0[] = {
    1297, (s32)D_800A5954,
#if VERSION_US
    0x1430017,
#elif VERSION_EU
    0x14A0017,
#endif
    0, (s32)func_800A5790, 1298, (s32)D_800A59EC,
#if VERSION_US
    0x1430018,
#elif VERSION_EU
    0x14A0018,
#endif
    0, (s32)func_800A57DC, 8000, 0,
    0, (s32)func_800A4EE8, 0, 8001,
    0, 0, (s32)func_800A4F68, 0,
    8002, 0, 0, (s32)func_800A4FE8,
    0, -1, 0, 0,
    0, 0,
};
