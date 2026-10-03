#include "common.h"
#include "stage.h"
extern s16 D_800A5938[];
#if VERSION_US
#define TIMER_SHEET 0x6E6
#elif VERSION_EU
#define TIMER_SHEET 0x6F6
#endif
extern s32 D_800A61E8[];
extern s32 D_800A5B50[];
extern s32 D_800A5F7C[];
extern u8 D_800A5B6C[];
extern u8 D_800A613C[];
extern u8 D_800A5FB0[];
void func_800A5240();
extern AnimFrame D_800A58D8[];
extern AnimFrame D_800A58E4[];
extern AnimFrame D_800A5910[];
extern AnimFrame *D_800A592C[];
void func_800A4DC4();
extern void (*D_800A61E4[])(void);
void func_800A543C();
void func_800A55EC();
void *func_800A50C4(void);

/* func_800A4F74 of WSTAG310 with durations read as bytes */
s32 func_800A4CA4(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
    AnimFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += (u8)frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += (u8)frame->duration;
        }
        func_800A4CA4(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Shows the first record animated while running; when done, both */
void func_800A4DC4(StageTilePair *task) {
    StageTile *tile;
    StageTile *rec;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 1:
                task->anims[0].anim.index = 0;
                task->anims[0].anim.timer = (u8)D_800A592C[0]->duration;
                task->anims[0].tile = rec;
                break;
            case 2:
                task->anims[1].anim.index = 0;
                task->anims[1].anim.timer = (u8)D_800A592C[2]->duration;
                task->anims[1].tile = rec;
                break;
            }
        }
        task->playing = 0;
        if (task->done == 0) {
            task->nextState(task);
        } else {
            task->anims[0].anim.index = 0;
            task->anims[0].anim.timer = (u8)D_800A58E4[0].duration;
            task->setState(task, TASK_DONE);
        }
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                tile->frame = 0x46;
                tile->unk9 = func_800A4CA4(&task->anims[0], D_800A58D8, 0, 0);
                break;
            case 1:
                tile->visible = 0;
                break;
            }
        }
        break;
    case TASK_DONE:
        for (i = 0; i < 2; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                if (task->playing) {
                    frame = func_800A4CA4(&task->anims[0], D_800A58E4, 1, 0);
                    if (frame == 0xFF) {
                        tile->frame = 0x50;
                        task->playing = 0;
                    } else {
                        tile->frame = frame;
                    }
                } else {
                    tile->frame = 0x50;
                }
                tile->unk9 = 0;
                break;
            case 1:
                tile->visible = 1;
                tile->frame = 0x51;
                tile->unk9 = func_800A4CA4(&task->anims[1], D_800A5910, 0, 0);
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Plays the first record's one-shot animation when the event of map object 0x35B happens */
void func_800A5044(StageTilePair *task, s32 id) {
    if (task != NULL && id == 0x35B) {
        task->playing = 1;
        task->anims[0].anim.index = 0;
        task->anims[0].anim.timer = (u8)D_800A58E4[0].duration;
        task->setState(task, TASK_DONE);
    }
}

void *func_800A5094(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x68, 0, arg);
}

/* Creates the tile pair object, started in TASK_DONE */
void *func_800A50C4(void) {
    StageTilePair *task = createTask(func_800A4DC4, sizeof(StageTilePair), 0);

    task->done = 1;
    return task;
}

/* Draws the timer: its frame and the three digits of GAME.countdown */
void func_800A50F8(StageTask *task) {
    SpriteDrawer drawer;
    Vec2 scroll;
    s32 i;
    Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getScroll(layer, &scroll);
    initSpriteDrawer(&drawer);
    drawer.setLayer(layer, 0);
    drawer.setTexture(0x140, 0x100);
    drawer.setAltClut(0, 0x1F0);
    drawer.draw(FILE_CACHE.getEntry(TIMER_SHEET << 16), 1, scroll.x + 0xE0, scroll.y + 0x16);
    scroll.y += 0x19;
    for (i = 0; i < 3; i++) {
        drawer.draw(FILE_CACHE.getEntry(TIMER_SHEET << 16), GAME.countdown[i] + 2, scroll.x + D_800A5938[i], scroll.y);
    }
}

/* The timer: counts GAME.countdown down while nothing stops it, then starts event 0x5E1 */
void func_800A5240(StageTask *task, void **children) {
    u8 *countdown;

    switch (task->state) {
    case TASK_RUN:
        if (FLAGS_00.checkCondition(0x4043, 0) || D_800990B4.unk58 != 0 || D_800990B4.unk5C != 0 ||
            D_800990B4.unk54 != 0 || D_800990B4.unk50 != 0 || D_800990B4.unk60 != 0) {
            break;
        }
        func_800A50F8(task);
        countdown = GAME.countdown;
        if (countdown[0] != 0 || countdown[1] != 0 || countdown[2] != 0) {
            countdown[3] -= GFX_FUNCS.getFrameTime();
            if (countdown[3] > 60) {
                countdown[2]--;
                countdown[3] += 60;
                SOUND.playSound(0x800452C6);
            }
            COUNTDOWN_BORROW(countdown);
            break;
        }
        children[0] = func_80084B80(0x5E1);
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5410(void) {
    return createTask(func_800A5240, 0x54, 0x4);
}

/* Creates the timer, one of two objects by flag 0x4063, and the event object of story progress 0x20 */
void func_800A543C(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A5410();
        if (FLAGS_00.checkCondition(0x4063, 0)) {
            children[1] = func_800A5094(0x344);
        } else {
            children[1] = func_800A50C4();
        }
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4043, 0) && GAME_PROGRESS == 0x20) {
            children[2] = func_80084B80(0x33E);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

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

#if VERSION_US
void func_800A55EC(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x711;
    D_800990B4.unkC = 0x6E60000;
    D_800990B4.unk10 = D_800A5FB0;
    D_800990B4.unk14 = D_800A613C;
    D_800990B4.unk1C = 0x6E2;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x4B200;
    D_800990B4.unk30 = 0x3AA00;
    D_800990B4.unk28 = D_800A5B6C;
    D_800990B4.unk3C = 0xD;
    D_800990B4.unk40 = 0x60340000;
    D_800990B4.unk4C = D_800A5F7C;
    D_800990B4.unk20 = D_800A5B50;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A61E8;
    D_8009A70C.setFile(0, 0x6E60001);
    D_8009A70C.setFile(7, 0x6E60002);
    D_8009A70C.setFile(4, 0x6E60003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A55EC);
#endif

extern s32 D_800A5940[];
extern s32 D_800A594C[];
extern s32 D_800A5958[];
extern s32 D_800A5964[];
extern s32 D_800A5970[];
extern s32 D_800A597C[];
extern s32 D_800A5988[];
extern s32 D_800A5994[];
extern s32 D_800A59C4[];
extern s32 D_800A59D0[];
extern s32 D_800A59DC[];
extern s32 D_800A59E8[];
extern s32 D_800A59F4[];
extern s32 D_800A5A00[];
extern s32 D_800A5A0C[];
extern s32 D_800A5A18[];
extern s32 D_800A5A48[];
extern s32 D_800A5A54[];
extern s32 D_800A5A60[];
extern s32 D_800A5A6C[];
extern s32 D_800A5A78[];
extern s32 D_800A5A84[];
extern s32 D_800A5A90[];
extern s32 D_800A5A9C[];
extern s32 D_800A5ACC[];
extern s32 D_800A5AD8[];
extern s32 D_800A5AE4[];
extern s32 D_800A5AF0[];
extern s32 D_800A5AFC[];
extern s32 D_800A5B08[];
extern s32 D_800A5B14[];
extern s32 D_800A5B20[];
extern s32 D_800A59A0[];
extern s32 D_800A5A24[];
extern s32 D_800A5AA8[];
extern s32 D_800A5B2C[];
extern s32 D_800A5C8C[];
extern s32 D_800A5C98[];
extern s32 D_800A5CA0[];
extern s32 D_800A5CAC[];
extern s32 D_800A5CB4[];
extern s32 D_800A5CBC[];
extern s32 D_800A5CC8[];
extern s32 D_800A5CD4[];
extern s32 D_800A5CDC[];
extern s32 D_800A5CE8[];
extern s32 D_800A5CF4[];
extern s32 D_800A5D00[];
extern s32 D_800A5E2C[];
extern s32 D_800A5D0C[];
extern s32 D_800A5E34[];
extern s32 D_800A5D24[];
extern s32 D_800A5E3C[];
extern s32 D_800A5D3C[];
extern s32 D_800A5E44[];
extern s32 D_800A5D54[];
extern s32 D_800A5E4C[];
extern s32 D_800A5D6C[];
extern s32 D_800A5E54[];
extern s32 D_800A5D84[];
extern s32 D_800A5E5C[];
extern s32 D_800A5D9C[];
extern s32 D_800A5E64[];
extern s32 D_800A5DB4[];
extern s32 D_800A5E6C[];
extern s32 D_800A5DCC[];
extern s32 D_800A5E74[];
extern s32 D_800A5DE4[];
extern s32 D_800A5E7C[];
extern s32 D_800A5DFC[];
extern s32 D_800A5E84[];
extern s32 D_800A5E14[];
extern s32 D_800A5E8C[];
extern s32 D_800A5EA0[];
extern s32 D_800A5EB4[];
extern s32 D_800A5EC8[];
extern s32 D_800A5EDC[];
extern s32 D_800A5EF0[];
extern s32 D_800A5F04[];
extern s32 D_800A5F18[];
extern s32 D_800A5F2C[];
extern s32 D_800A5F40[];
extern s32 D_800A5F54[];
extern s32 D_800A5F68[];
extern s32 D_800A5700[];
extern s32 D_800A5780[];
extern s32 D_800A5884[];

s32 D_800A5700[] = {
    0x20100, 0x37D045F, 0x20101, 0x10001,
    0x780300, 0x3230101, 0x20325, 0x5A0300,
    0x3230101, 0x20326, 0x1E0300, 0x20101,
    0x70001, 0x1E0300, 0x20101, 0x10001,
    0x1E0300, 0x20101, 0x70001, 0x1E0300,
    0x20101, 0x10001, 0x1E0300, 512,
    0x20001, 0x1010002, 0x70002, 0x3010001,
    0x20101, 0x10001, 0x1E0300,
#if VERSION_US
    0x31A80000,
#elif VERSION_EU
    0,
#endif
};
s32 D_800A5780[] = {
    0x20102, 0x38701C1, 0x1010005, 0x337032D,
    0x3020002, 0x3000002, 0x101001E, 0x3250323,
    0x3000002, 0x101005A, 0x3260323, 0x3000002,
    0x200001E, 0x10000, 2, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x101001E, 0x377032D, 0x3000002, 0x101001E,
    0x35B0344, 0x3000002, 0x1010078, 0x10002,
    0x3000005, 0x101003C, 0x10002, 0x1010001,
    0x37F032D, 0x3000002, 0x101001E, 0x10002,
    0x3000007, 0x101001E, 0x10002, 0x3000001,
    0x101001E, 0x10002, 0x3000007, 0x101001E,
    0x10002, 0x3000001, 0x200001E, 0x20000,
    2, 0x20101, 0x10007, 0x1010301,
    0x10002, 0x3000001, 0x102001E, 0x1A00002,
    0x30379, 0x20302, 0x20101, 0x30001,
    0x1E0300, 0x20101, 0x10001, 0x1E0300,
#if VERSION_US
    0x31A80000,
#elif VERSION_EU
    0,
#endif
};
s32 D_800A5884[] = {
    0x1E0300, 0x3230101, 0x20325, 0x5A0300,
    0x3230101, 0x20326, 0x1E0300, 0x20101,
    1, 0x1E0300, 512, 0x20001,
    0x1010002, 0x70002, 0x3010000, 0x20101,
    1, 0x1E0300, 0x26D0304, 0x10001,
    1,
};
AnimFrame D_800A58D8[] = {
    { 0, 8 }, { 1, 8 }, { 255, 0 },
};
AnimFrame D_800A58E4[] = {
    { 71, 4 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 75, 4 }, { 76, 4 }, { 77, 4 }, { 78, 4 },
    { 79, 4 }, { 80, 4 }, { 255, 0 },
};
AnimFrame D_800A5910[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 255, 0 },
};
AnimFrame *D_800A592C[] = {
    D_800A58D8, D_800A58E4, D_800A5910,
};
s16 D_800A5938[] = {
    226, 253, 0x118, 0,
};
s32 D_800A5940[] = {
    124, 16, 0x60080000,
};
s32 D_800A594C[] = {
    124, 16, 0x60080000,
};
s32 D_800A5958[] = {
    124, 16, 0x60080000,
};
s32 D_800A5964[] = {
    125, 16, 0x60080000,
};
s32 D_800A5970[] = {
    125, 16, 0x60080000,
};
s32 D_800A597C[] = {
    125, 16, 0x60080000,
};
s32 D_800A5988[] = {
    123, 16, 0x60080000,
};
s32 D_800A5994[] = {
    123, 16, 0x60080000,
};
s32 D_800A59A0[] = {
    3, (s32)D_800A5940, (s32)D_800A594C, (s32)D_800A5958,
    (s32)D_800A5964, (s32)D_800A5970, (s32)D_800A597C, (s32)D_800A5988,
    (s32)D_800A5994,
};
s32 D_800A59C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A59D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A59DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A59E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A24[] = {
    0, (s32)D_800A59C4, (s32)D_800A59D0, (s32)D_800A59DC,
    (s32)D_800A59E8, (s32)D_800A59F4, (s32)D_800A5A00, (s32)D_800A5A0C,
    (s32)D_800A5A18,
};
s32 D_800A5A48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A60[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AA8[] = {
    0, (s32)D_800A5A48, (s32)D_800A5A54, (s32)D_800A5A60,
    (s32)D_800A5A6C, (s32)D_800A5A78, (s32)D_800A5A84, (s32)D_800A5A90,
    (s32)D_800A5A9C,
};
s32 D_800A5ACC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B2C[] = {
    0, (s32)D_800A5ACC, (s32)D_800A5AD8, (s32)D_800A5AE4,
    (s32)D_800A5AF0, (s32)D_800A5AFC, (s32)D_800A5B08, (s32)D_800A5B14,
    (s32)D_800A5B20,
};
s32 D_800A5B50[] = {
    90, 0, 0, (s32)D_800A59A0,
    (s32)D_800A5A24, (s32)D_800A5AA8, (s32)D_800A5B2C,
};
u8 D_800A5B6C[] = {
    0x00, 0x02, 0x00, 0x01, 0x1C, 0x02, 0xA6, 0x01,
    0x70, 0x00, 0xA6, 0x00, 0x30, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x16, 0x02, 0x38, 0x01,
    0x58, 0x00, 0x38, 0x00, 0x00, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x08, 0x02, 0xBC, 0x01,
    0x20, 0x00, 0xBC, 0x00, 0x10, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x10, 0x02, 0xBC, 0x01,
    0x40, 0x00, 0xBC, 0x00, 0x20, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0xBC, 0x01,
    0x00, 0x00, 0xBC, 0x00, 0x30, 0x02, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x4C, 0x01, 0x9A, 0x01,
    0x30, 0x00, 0x9A, 0x00, 0x40, 0x01, 0xF9, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x40, 0x01, 0xA2, 0x01,
    0x00, 0x00, 0xA2, 0x00, 0x50, 0x01, 0xF9, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x52, 0x01, 0xB9, 0x01,
    0x48, 0x00, 0xB9, 0x00, 0x60, 0x01, 0xF9, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x58, 0x01, 0xB9, 0x01,
    0x60, 0x00, 0xB9, 0x00, 0x70, 0x01, 0xF9, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x5E, 0x01, 0xB9, 0x01,
    0x78, 0x00, 0xB9, 0x00, 0x40, 0x01, 0xF8, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x64, 0x01, 0xB9, 0x01,
    0x90, 0x00, 0xB9, 0x00, 0x50, 0x01, 0xF8, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x46, 0x01, 0xBA, 0x01,
    0x18, 0x00, 0xBA, 0x00, 0x60, 0x01, 0xF8, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x4C, 0x01, 0xBA, 0x01,
    0x30, 0x00, 0xBA, 0x00, 0x70, 0x01, 0xF8, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x6A, 0x01, 0xC0, 0x01,
    0xA8, 0x00, 0xC0, 0x00, 0x40, 0x01, 0xF7, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x70, 0x01, 0xC0, 0x01,
    0xC0, 0x00, 0xC0, 0x00, 0x50, 0x01, 0xF7, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0xC0, 0x01,
    0xD8, 0x00, 0xC0, 0x00, 0x60, 0x01, 0xF7, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x40, 0x01, 0xC2, 0x01,
    0x00, 0x00, 0xC2, 0x00, 0x70, 0x01, 0xF7, 0x01,
};
s32 D_800A5C8C[] = {
    0x10239, 0x184D5, 65535,
};
s32 D_800A5C98[] = {
    0x1023A, 65535,
};
s32 D_800A5CA0[] = {
    0x1023B, 0x1822B, 65535,
};
s32 D_800A5CAC[] = {
    0x1023C, 65535,
};
s32 D_800A5CB4[] = {
    0x1023D, 65535,
};
s32 D_800A5CBC[] = {
    0x1023E, 0x188A5, 65535,
};
s32 D_800A5CC8[] = {
    0x1023F, 0x184AE, 65535,
};
s32 D_800A5CD4[] = {
    0x10240, 65535,
};
s32 D_800A5CDC[] = {
    0x10241, 0x1822C, 65535,
};
s32 D_800A5CE8[] = {
    0x10242, 0x18464, 65535,
};
s32 D_800A5CF4[] = {
    0x10243, 0x18497, 65535,
};
s32 D_800A5D00[] = {
    0x10244, 0x18B22, 65535,
};
s32 D_800A5D0C[] = {
    0, (s32)D_800A5C8C, 513, 0,
    0, 0,
};
s32 D_800A5D24[] = {
    0, (s32)D_800A5C98, 401, 0,
    0, 0,
};
s32 D_800A5D3C[] = {
    0, (s32)D_800A5CA0, 382, 0,
    0, 0,
};
s32 D_800A5D54[] = {
    0, (s32)D_800A5CAC, 401, 0,
    0, 0,
};
s32 D_800A5D6C[] = {
    0, (s32)D_800A5CB4, 401, 0,
    0, 0,
};
s32 D_800A5D84[] = {
    0, (s32)D_800A5CBC, 498, 0,
    0, 0,
};
s32 D_800A5D9C[] = {
    0, (s32)D_800A5CC8, 511, 0,
    0, 0,
};
s32 D_800A5DB4[] = {
    0, (s32)D_800A5CD4, 401, 0,
    0, 0,
};
s32 D_800A5DCC[] = {
    0, (s32)D_800A5CDC, 381, 0,
    0, 0,
};
s32 D_800A5DE4[] = {
    0, (s32)D_800A5CE8, 489, 0,
    0, 0,
};
s32 D_800A5DFC[] = {
    0, (s32)D_800A5CF4, 497, 0,
    0, 0,
};
s32 D_800A5E14[] = {
    0, (s32)D_800A5D00, 399, 0,
    0, 0,
};
s32 D_800A5E2C[] = {
    569, 65535,
};
s32 D_800A5E34[] = {
    570, 65535,
};
s32 D_800A5E3C[] = {
    571, 65535,
};
s32 D_800A5E44[] = {
    572, 65535,
};
s32 D_800A5E4C[] = {
    573, 65535,
};
s32 D_800A5E54[] = {
    574, 65535,
};
s32 D_800A5E5C[] = {
    575, 65535,
};
s32 D_800A5E64[] = {
    576, 65535,
};
s32 D_800A5E6C[] = {
    577, 65535,
};
s32 D_800A5E74[] = {
    578, 65535,
};
s32 D_800A5E7C[] = {
    579, 65535,
};
s32 D_800A5E84[] = {
    580, 65535,
};
s32 D_800A5E8C[] = {
    (s32)D_800A5E2C, (s32)D_800A5D0C, 0x40021, 0x2A603C1,
    1,
};
s32 D_800A5EA0[] = {
    (s32)D_800A5E34, (s32)D_800A5D24, 0x5004D, 0x35702E1,
    1,
};
s32 D_800A5EB4[] = {
    (s32)D_800A5E3C, (s32)D_800A5D3C, 0x6004E, 0x3870280,
    1,
};
s32 D_800A5EC8[] = {
    (s32)D_800A5E44, (s32)D_800A5D54, 0x7004F, 0x3B60221,
    1,
};
s32 D_800A5EDC[] = {
    (s32)D_800A5E4C, (s32)D_800A5D6C, 0x80050, 0x3E60300,
    1,
};
s32 D_800A5EF0[] = {
    (s32)D_800A5E54, (s32)D_800A5D84, 0x90051, 0x22E0190,
    1,
};
s32 D_800A5F04[] = {
    (s32)D_800A5E5C, (s32)D_800A5D9C, 0xA0052, 0x16E0310,
    1,
};
s32 D_800A5F18[] = {
    (s32)D_800A5E64, (s32)D_800A5DB4, 0xB0053, 0x1DE01B0,
    1,
};
s32 D_800A5F2C[] = {
    (s32)D_800A5E6C, (s32)D_800A5DCC, 0xC0054, 0x41702A0,
    1,
};
s32 D_800A5F40[] = {
    (s32)D_800A5E74, (s32)D_800A5DE4, 0xD0055, 0x20F014F,
    1,
};
s32 D_800A5F54[] = {
    (s32)D_800A5E7C, (s32)D_800A5DFC, 0xE0056, 0x33700A0,
    1,
};
s32 D_800A5F68[] = {
    (s32)D_800A5E84, (s32)D_800A5E14, 0xF0057, 0x20E00CD,
    1,
};
s32 D_800A5F7C[] = {
    (s32)D_800A5E8C, (s32)D_800A5EA0, (s32)D_800A5EB4, (s32)D_800A5EC8,
    (s32)D_800A5EDC, (s32)D_800A5EF0, (s32)D_800A5F04, (s32)D_800A5F18,
    (s32)D_800A5F2C, (s32)D_800A5F40, (s32)D_800A5F54, (s32)D_800A5F68,
    0,
};
u8 D_800A5FB0[] = {
    0x01, 0x00, 0x40, 0x02, 0x38, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x99, 0x00, 0x97, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x38, 0x02,
    0x00, 0x05, 0x04, 0x00, 0xA6, 0x00, 0x9E, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x38, 0x02, 0x00, 0x05, 0x04, 0x00, 0xB9, 0x00,
    0xA7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x38, 0x02, 0x00, 0x05, 0x04, 0x00,
    0xC6, 0x00, 0xAE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x38, 0x02, 0x00, 0x05,
    0x04, 0x00, 0xD9, 0x00, 0xB7, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x38, 0x02,
    0x00, 0x05, 0x04, 0x00, 0xE6, 0x00, 0xBE, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x38, 0x02, 0x00, 0x05, 0x04, 0x00, 0xF9, 0x00,
    0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x38, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x06, 0x01, 0xCE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x02, 0x64, 0x06, 0x51, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x9E, 0x01, 0x42, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x64, 0x06, 0x46, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9E, 0x01, 0x42, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x37, 0x02, 0x00, 0x05, 0x06, 0x00, 0x5D, 0x04,
    0x4D, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x01, 0x32, 0x36, 0x06, 0x00,
    0x61, 0x04, 0x51, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x38, 0x02, 0x00, 0x05,
    0x04, 0x00, 0xE2, 0x00, 0x73, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x38, 0x02,
    0x00, 0x05, 0x04, 0x00, 0xEF, 0x00, 0x7A, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x38, 0x02, 0x00, 0x05, 0x04, 0x00, 0x02, 0x01,
    0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x38, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x0F, 0x01, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x38, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x21, 0x01, 0x93, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x38, 0x02,
    0x00, 0x05, 0x04, 0x00, 0x2F, 0x01, 0x9A, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x38, 0x02, 0x00, 0x05, 0x04, 0x00, 0x42, 0x01,
    0xA3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x38, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x4F, 0x01, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x64, 0x7A, 0x06, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x8E, 0x00, 0x43, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A613C[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDB, 0x02, 0x08, 0x02, 0xCC, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDB, 0x02, 0x68, 0x01, 0x1C, 0x01,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDB, 0x02, 0x28, 0x01, 0x9C, 0x01,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDB, 0x02, 0x28, 0x01, 0x5C, 0x03,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x1C, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDC, 0x02, 0xB4, 0x02, 0x98, 0x01,
    0x03, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x60, 0x01, 0x00, 0x63, 0x40, 0x00, 0x00,
    0x08, 0x00, 0x48, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A61E4[])(void) = {
    func_800A55EC,
};
s32 D_800A61E8[] = {
    830, (s32)D_800A5700,
#if VERSION_US
    0x143001A,
#elif VERSION_EU
    0x14A001A,
#endif
    0, (s32)func_800A5574, 840, (s32)D_800A5780,
#if VERSION_US
    0x143001B,
#elif VERSION_EU
    0x14A001B,
#endif
    0, (s32)func_800A55A0, 1505, (s32)D_800A5884,
#if VERSION_US
    0x1430025,
#elif VERSION_EU
    0x14A0025,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
