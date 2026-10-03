#include "common.h"
#include "stage.h"
void func_800A4F90();
extern void (*D_800A6614[])(void);
void func_800A58AC();
void *func_800A4E60(s32 arg);
StageFloater *func_800A5854(s32 x, s32 y, s32 up);
extern StageFloaterSpot D_800A5F58[];
extern s16 D_800A609C[];
extern StageTileLoopFrame *D_800A6164[];
extern StageFloaterFrame D_800A6174[];
extern StageFloaterFrame D_800A61BC[];
extern StageFloaterFrame D_800A6204[];
extern StageFloaterFrame D_800A625C[];
StageFloater *func_800A5854(s32 x, s32 y, s32 up);
extern StageTileLoopFrame D_800A610C[];
extern StageTileLoopFrame D_800A60D4[];
extern StageTileLoopFrame D_800A6128[];
extern StageTileLoopFrame D_800A6144[];

/* Creates the 27 floaters; in TASK_DONE sets them moving one after the other */
void func_800A4CA8(StageFloaterChain *task, StageFloaters *children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        for (i = 0; i < 27; i++) {
            children->floaters[i] = func_800A5854(D_800A5F58[i].x, D_800A5F58[i].y, D_800A5F58[i].up);
        }
        break;
    case TASK_RUN:
        break;
    case TASK_DONE:
        if (task->timer >= D_800A609C[task->next] && task->timer < D_800A609C[task->next + 1]) {
            children->floaters[task->next]->setState(children->floaters[task->next], TASK_DONE);
            task->next++;
            if (D_800A609C[task->next] == 0x1000) {
                task->setState(task, TASK_RUN);
            }
        }
        task->timer += GFX_FUNCS.getFrameTime();
        break;
    case TASK_KILL:
        break;
    }
}

/* Starts the chain when the event of map object 0x335 happens */
void func_800A4E28(StageFloaterChain *task, s32 id) {
    if (task != NULL && id == 0x335) {
        task->next = 0;
        task->timer = 0;
        task->setState(task, TASK_DONE);
    }
}

/* Creates the chain of floaters */
void *func_800A4E60(s32 arg) {
    return createTaskWithId(func_800A4CA8, sizeof(StageFloaterChain), sizeof(StageFloaters), arg);
}

/* Advances a looping animation, returns its frame */
s32 func_800A4E90(StageTileAnim *obj, StageTileLoopFrame *frames, s32 depth) {
    StageTileLoopFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();
    s32 loop;

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            loop = frame->loop;
            frame = &frames[loop];
            obj->anim.index = loop;
            obj->anim.timer += frame->duration;
        }
        func_800A4E90(obj, frames, depth + 1);
    }
    return frame->frame;
}

/* Animates the records with animations 1 to 4: 2 and 3 hidden while running */
void func_800A4F90(StageTileQuad *task) {
    StageTile *rec;
    StageTile *tile;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 1:
                task->anims[0].anim.index = 0;
                task->anims[0].anim.timer = D_800A6164[0]->duration;
                task->anims[0].tile = rec;
                break;
            case 2:
                task->anims[1].anim.index = 0;
                task->anims[1].anim.timer = D_800A6164[1]->duration;
                task->anims[1].tile = rec;
                break;
            case 3:
                task->anims[2].anim.index = 0;
                task->anims[2].anim.timer = D_800A6164[2]->duration;
                task->anims[2].tile = rec;
                break;
            case 4:
                task->anims[3].anim.index = 0;
                task->anims[3].anim.timer = D_800A6164[3]->duration;
                task->anims[3].tile = rec;
                break;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        for (i = 0; i < 4; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                tile->frame = 0x24;
                tile->unk9 = 0;
                break;
            case 1:
                tile->visible = 0;
                break;
            case 2:
                tile->visible = 0;
                break;
            case 3:
                tile->visible = 1;
                tile->frame = 0x13;
                tile->unk9 = func_800A4E90(&task->anims[3], D_800A610C, 0);
                break;
            }
        }
        break;
    case TASK_DONE:
        for (i = 0; i < 4; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                tile->frame = func_800A4E90(&task->anims[0], D_800A60D4, 0);
                tile->unk9 = 0;
                break;
            case 1:
                tile->visible = 1;
                tile->frame = 0x15;
                tile->unk9 = func_800A4E90(&task->anims[1], D_800A6128, 0);
                break;
            case 2:
                tile->visible = 1;
                tile->frame = 0x16;
                frame = func_800A4E90(&task->anims[2], D_800A6144, 0);
                if (frame == 0x12C) {
                    tile->unk9 = 0;
                } else {
                    tile->unk9 = frame;
                }
                break;
            case 3:
                tile->visible = 0;
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Plays a sound and starts the records' TASK_DONE animations when the event of map object 0x35B happens */
void func_800A5288(StageTileQuad *task, s32 id) {
    if (task != NULL && id == 0x35B) {
        SOUND.playSound(0x340004);
        task->setState(task, TASK_DONE);
    }
}

void *func_800A52E0(s32 arg) {
    return createTaskWithId(func_800A4F90, 0x70, 0, arg);
}

/* Advances a part's animation (adding up its deltas when once), returns its frame */
s32 func_800A5310(StageFloaterPart *obj, StageFloaterFrame *frames, s32 once, s32 depth) {
    StageFloaterFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (once) {
        obj->value += frame->delta;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                obj->anim.index--;
                frame--;
                obj->anim.timer += frame->duration;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5310(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

s32 func_800A5464(s32 x, s32 y, s32 w, s32 h) {
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

/* Draws a part of a floater */
void func_800A5528(StageFloater *task, Layer *layer, s32 idx) {
    SpriteDrawer drawer;
    StageFloaterPart *part = &task->parts[idx];

    initSpriteDrawer(&drawer);
    drawer.setTexture(0x140, 0x100);
    drawer.setLayer(layer, 10);
    drawer.setClutRow(part->sprite.clutRow);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), part->sprite.frame, task->x, task->y);
}

/* A floater: animated in place while running, moving up or down with a sound in TASK_DONE */
void func_800A55E8(StageFloater *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 y8;
    s32 value;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->substate == 0) {
            task->parts[0].anim.index = 0;
            task->parts[0].anim.timer = D_800A6174[0].duration;
            task->parts[1].anim.index = 0;
            task->parts[1].anim.timer = D_800A625C[0].duration;
            task->parts[2].anim.index = 0;
            task->parts[2].anim.timer = D_800A61BC[0].duration;
            task->setSubstate(task, 1);
        }
        task->parts[0].sprite.frame = func_800A5310(&task->parts[0], D_800A6174, 0, 0);
        task->parts[0].sprite.clutRow = func_800A5310(&task->parts[2], D_800A61BC, 0, 0);
        task->parts[1].sprite.frame = 0x28;
        task->parts[1].sprite.clutRow = func_800A5310(&task->parts[1], D_800A625C, 0, 0);
        if (task->parts[0].sprite.frame != 0 && func_800A5464(task->x, task->y, 0x20, 0x64)) {
            func_800A5528(task, layer, 0);
        }
        if (task->parts[1].sprite.frame != 0 && func_800A5464(task->x, task->y, 0x20, 0x64)) {
            func_800A5528(task, layer, 1);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->parts[0].anim.index = 0;
            task->parts[0].anim.timer = D_800A6204[0].duration;
            task->y8 = task->y << 8;
            task->setSubstate(task, 1);
            SOUND.playSound(0x800421BF);
        }
        task->parts[0].sprite.frame = func_800A5310(&task->parts[0], D_800A6204, 1, 0);
        task->parts[0].sprite.clutRow = 0;
        if (task->y >= -100 && task->y <= 1000) {
            value = task->parts[0].value;
            y8 = task->y8;
            task->y8 = task->up ? y8 - value : y8 + value;
            task->y = task->y8 >> 8;
        }
        if (task->parts[0].sprite.frame != 0 && func_800A5464(task->x, task->y, 0x20, 0x64)) {
            func_800A5528(task, layer, 0);
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Creates a floater at (x, y) */
StageFloater *func_800A5854(s32 x, s32 y, s32 up) {
    StageFloater *task = createTask(func_800A55E8, sizeof(StageFloater), 0);

    task->x = x;
    task->y = y;
    task->up = up;
    return task;
}

/* Creates two objects and the event object of flags 0x4046/0x4048 that applies */
void func_800A58AC(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        children[0] = func_800A4E60(0x349);
        children[1] = func_800A52E0(0x348);
        do {
            if (FLAGS_00.checkCondition(0x4048, 0) && FLAGS_00.checkCondition(0x4046, 0)) {
                children[2] = func_80084B80(0x370);
                break;
            }
            if (FLAGS_00.checkCondition(0x4048, 0) && FLAGS_00.checkCondition(0x4046, 1) &&
                FLAGS_00.checkCondition(0x4064, 0)) {
                children[2] = func_80084B80(0x371);
                break;
            }
            if (FLAGS_00.checkCondition(0x4048, 1) && FLAGS_00.checkCondition(0x4046, 0) &&
                FLAGS_00.checkCondition(0x4065, 0)) {
                children[2] = func_80084B80(0x372);
                break;
            }
        } while (0);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5A08(void *owner) {
    StageTask *task = createTask(func_800A58AC, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A6614[0]();
    return task;
}

void func_800A5A64(void) {
    FLAGS_00.applyAction(0x4046, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

/* Sets flag 0x8AF0 */
void func_800A5AB0(void) {
    FLAGS_00.applyAction(0x8AF0, 1);
}

void func_800A5ADC(void) {
    FLAGS_00.applyAction(0x4065, 1);
}

extern s32 D_800A65B8[];
extern s32 D_800A64C0[];
extern s32 D_800A65A8[];
extern CVECTOR D_800A4CA4;
extern s32 D_800A64A4[];
extern s32 D_800A6618[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x662
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x672
#endif
void func_800A5B08(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A65B8;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x2A000, 0x18C00};
    D_800990B4.unk28 = D_800A64C0;
    D_800990B4.unk3C = 0xD;
    D_800990B4.unk40 = 0x60340000;
    D_800990B4.unk4C = D_800A65A8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A64A4;
    D_800990B4.events = D_800A6618;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.unk50(0);
}

void func_800A5B08();
void func_800A5AB0();
extern s32 D_800A6294[];
extern s32 D_800A62A0[];
extern s32 D_800A62AC[];
extern s32 D_800A62B8[];
extern s32 D_800A62C4[];
extern s32 D_800A62D0[];
extern s32 D_800A62DC[];
extern s32 D_800A62E8[];
extern s32 D_800A6318[];
extern s32 D_800A6324[];
extern s32 D_800A6330[];
extern s32 D_800A633C[];
extern s32 D_800A6348[];
extern s32 D_800A6354[];
extern s32 D_800A6360[];
extern s32 D_800A636C[];
extern s32 D_800A639C[];
extern s32 D_800A63A8[];
extern s32 D_800A63B4[];
extern s32 D_800A63C0[];
extern s32 D_800A63CC[];
extern s32 D_800A63D8[];
extern s32 D_800A63E4[];
extern s32 D_800A63F0[];
extern s32 D_800A6420[];
extern s32 D_800A642C[];
extern s32 D_800A6438[];
extern s32 D_800A6444[];
extern s32 D_800A6450[];
extern s32 D_800A645C[];
extern s32 D_800A6468[];
extern s32 D_800A6474[];
extern s32 D_800A62F4[];
extern s32 D_800A6378[];
extern s32 D_800A63FC[];
extern s32 D_800A6480[];
extern s32 D_800A6550[];
extern s32 D_800A6558[];
extern s32 D_800A6564[];
extern s32 D_800A656C[];
extern s32 D_800A6580[];
extern s32 D_800A6594[];
extern s32 D_800A5BFC[];
extern s32 D_800A5D10[];
extern s32 D_800A5E9C[];

s32 D_800A5BFC[] = {
    0x10100, 0x19802B4, 0x10101, 0x30001,
    0xD20100, 0xC50168, 0xD20101, 0x30001,
    0x1E0300, 0x10102, 0x1820288, 0x3020003,
    0x1020001, 0x2480001, 0x30136, 0x10302,
    0x10102, 0xFE01D8, 0x3020003, 0x2000001,
    0x50000, 0x300D2, 0x10101, 0x30001,
    0x1010301, 0xC0001, 0x1010003, 0x3250323,
    0x3000001, 0x101003C, 0x10001, 0x1010003,
    0x3260323, 0x3000001, 0x102001E, 0x1880001,
    0x300D6, 0x10302, 0x10101, 0x30001,
    0x1E0300, 512, 0x10001, 0x1010003,
    0xC0001, 0x3010003, 0x3230101, 0xD20325,
    0x3C0300, 0x10101, 0x30001, 0xD20101,
    0x70001, 0x3230101, 0xD20326, 0x1E0300,
    512, 0xD20002, 0x3010002, 0x1E0300,
    512, 0x10003, 0x3010003, 0x1E0300,
    512, 0xD20004, 0x3010002, 0x1E0300,
    0,
};
s32 D_800A5D10[] = {
    0x10100, 0xD60188, 0x10101, 0x30001,
    0x13C0100, 0xCA0173, 0x13C0101, 0x10001,
    0x780300, 512, 0x10001, 0x1010002,
    0x70001, 0x3010003, 0x10101, 0x30001,
    0x1E0300, 0x10102, 0xCF017A, 0x3020003,
    0x3000001, 0x100001E, 316, 0x1010000,
    0x1013C, 0x3000001, 0x200001E, 0x70000,
    0x20001, 0x10101, 0x30007, 0x1010301,
    0x10001, 0x3000003, 0x101003C, 0x35B0348,
    0x3000001, 0x200003C, 0x30000, 0x40001,
    0x1010301, 0x3250323, 0x1010001, 0x369032D,
    0x3000001, 0x101003C, 0x3260323, 0x3000001,
    0x200001E, 0x40000, 0x20001, 0x1020301,
    0x1600001, 0x300C2, 0x10302, 0x10101,
    0x30001, 0x1E0300, 0x10101, 0x30001,
    0x3230101, 0x10327, 0x3C0300, 0x3230101,
    0x10326, 0x1E0300, 512, 0x10006,
    0x3010003, 0x780300, 0x3230101, 0x10325,
    0x3C0300, 0x3230101, 0x10326, 0x1E0300,
    512, 0x10002, 0x3010003, 0x1E0300,
    1537, 0xB200E0, 0x3490101, 0x10335,
    0x12C0300, 1536, 0x3000001, 0x200001E,
    0x50000, 0x30001, 0x1010301, 0x372032D,
    0x3000001, 0x1010096, 0x373032D, 0x3040001,
#if VERSION_US
    0x10E03,
#elif VERSION_EU
    0x10E04,
#endif
    0x10001, 0,
};
s32 D_800A5E9C[] = {
    0x10600, 0x10000D2, 2, 0x1010000,
    0x10002, 0x1000000, 0x16800D2, 0x10100C5,
    0x100D2, 0x3000003, 0x300001E, 0x20000B4,
    0x40000, 0x300D2, 0x3000301, 0x101001E,
    0x35B0348, 0x3000002, 0x200003C, 0x10000,
    0x400D2, 0x1010301, 0x369032D, 0x3000002,
    0x6010096, 0xE00000, 0x10100B2, 0x3350349,
    0x3000002, 0x600012C, 0xD20000, 0x1E0300,
    512, 0xD20002, 0x3010003, 0x5A0300,
    512, 0xD20003, 0x3010003, 0x32D0101,
    0x20372, 0x960300, 0x32D0101, 0x20373,
#if VERSION_US
    0xE030304,
#elif VERSION_EU
    0xE040304,
#endif
    0xCA015E, 1,
};
StageFloaterSpot D_800A5F58[] = {
    { 8, 140, 0 },
    { 28, 0x12C, 1 },
    { 48, 120, 0 },
    { 68, 0x118, 1 },
    { 88, 100, 0 },
    { 108, 0x104, 1 },
    { 128, 80, 0 },
    { 148, 240, 1 },
    { 168, 60, 0 },
    { 188, 220, 1 },
    { 208, 40, 1 },
    { 228, 200, 0 },
    { 248, 20, 1 },
    { 0x120, 0, 1 },
    { 0x148, -0x14, 1 },
    { 0x15C, 140, 1 },
    { 0x170, -0x28, 0 },
    { 0x184, 120, 1 },
    { 0x198, -0x3C, 0 },
    { 0x1AC, 100, 1 },
    { 0x1C0, -0x50, 0 },
    { 0x1D4, 80, 1 },
    { 0x1FC, 60, 1 },
    { 0x224, 40, 1 },
    { 0x24C, 20, 1 },
    { 0x274, 0, 1 },
    { 0x29C, -0x14, 1 },
};
s16 D_800A609C[] = {
    0, 4, 12, 16, 24, 28, 36, 40,
    48, 52, 60, 64, 72, 84, 96, 100,
    108, 112, 120, 124, 132, 136, 148, 160,
    172, 184, 196, 0x1000,
};
StageTileLoopFrame D_800A60D4[] = {
    { 23, 4, 0 },
    { 24, 4, 0 },
    { 25, 4, 0 },
    { 26, 4, 0 },
    { 27, 4, 0 },
    { 28, 4, 0 },
    { 29, 4, 0 },
    { 30, 4, 0 },
    { 31, 4, 0 },
    { 32, 4, 0 },
    { 33, 4, 0 },
    { 34, 8, 0 },
    { 35, 8, 0 },
    { 255, 0, 11 },
};
StageTileLoopFrame D_800A610C[] = {
    { 0, 8, 0 },
    { 1, 8, 0 },
    { 2, 8, 0 },
    { 3, 8, 0 },
    { 4, 8, 0 },
    { 5, 8, 0 },
    { 255, 0, 0 },
};
StageTileLoopFrame D_800A6128[] = {
    { 0, 8, 0 },
    { 1, 8, 0 },
    { 2, 8, 0 },
    { 3, 6, 0 },
    { 4, 6, 0 },
    { 5, 6, 0 },
    { 255, 0, 0 },
};
StageTileLoopFrame D_800A6144[] = {
    { 0x12C, 4, 0 },
    { 0, 8, 0 },
    { 1, 8, 0 },
    { 2, 8, 0 },
    { 3, 6, 0 },
    { 4, 6, 0 },
    { 5, 6, 0 },
    { 255, 0, 1 },
};
StageTileLoopFrame *D_800A6164[] = {
    D_800A60D4,
    D_800A6128,
    D_800A6144,
    D_800A610C,
};
StageFloaterFrame D_800A6174[] = {
    { 42, 4, 0 },
    { 42, 4, 0 },
    { 43, 4, 0 },
    { 43, 4, 0 },
    { 44, 4, 0 },
    { 44, 4, 0 },
    { 45, 4, 0 },
    { 45, 4, 0 },
    { 255, 0, 0 },
};
StageFloaterFrame D_800A61BC[] = {
    { 0, 4, 0 },
    { 1, 4, 0 },
    { 0, 4, 0 },
    { 1, 4, 0 },
    { 0, 4, 0 },
    { 1, 4, 0 },
    { 0, 4, 0 },
    { 1, 4, 0 },
    { 255, 0, 0 },
};
StageFloaterFrame D_800A6204[] = {
    { 11, 4, 0 },
    { 12, 4, 0 },
    { 13, 4, 0 },
    { 14, 4, 0 },
    { 15, 4, 0 },
    { 16, 4, 0 },
    { 17, 4, 0 },
    { 17, 4, 0 },
    { 18, 30, 64 },
    { 18, 30, 0 },
    { 255, 0x3E7, 0 },
};
StageFloaterFrame D_800A625C[] = {
    { 0, 8, 0 },
    { 1, 8, 0 },
    { 2, 8, 0 },
    { 3, 8, 0 },
    { 4, 8, 0 },
    { 5, 8, 0 },
    { 255, 0, 0 },
};
s32 D_800A6294[] = {
    0, 0, 0x60040000,
};
s32 D_800A62A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A62B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A62D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A62E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62F4[] = {
    0, (s32)D_800A6294, (s32)D_800A62A0, (s32)D_800A62AC,
    (s32)D_800A62B8, (s32)D_800A62C4, (s32)D_800A62D0, (s32)D_800A62DC,
    (s32)D_800A62E8,
};
s32 D_800A6318[] = {
    0, 0, 0x60040000,
};
s32 D_800A6324[] = {
    0, 0, 0x60040000,
};
s32 D_800A6330[] = {
    0, 0, 0x60040000,
};
s32 D_800A633C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6348[] = {
    0, 0, 0x60040000,
};
s32 D_800A6354[] = {
    0, 0, 0x60040000,
};
s32 D_800A6360[] = {
    0, 0, 0x60040000,
};
s32 D_800A636C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6378[] = {
    0, (s32)D_800A6318, (s32)D_800A6324, (s32)D_800A6330,
    (s32)D_800A633C, (s32)D_800A6348, (s32)D_800A6354, (s32)D_800A6360,
    (s32)D_800A636C,
};
s32 D_800A639C[] = {
    0, 0, 0x60040000,
};
s32 D_800A63A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63FC[] = {
    0, (s32)D_800A639C, (s32)D_800A63A8, (s32)D_800A63B4,
    (s32)D_800A63C0, (s32)D_800A63CC, (s32)D_800A63D8, (s32)D_800A63E4,
    (s32)D_800A63F0,
};
s32 D_800A6420[] = {
    22, 18, 0x608C0000,
};
s32 D_800A642C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6438[] = {
    0, 0, 0x60040000,
};
s32 D_800A6444[] = {
    0, 0, 0x60040000,
};
s32 D_800A6450[] = {
    0, 0, 0x60040000,
};
s32 D_800A645C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6468[] = {
    0, 0, 0x60040000,
};
s32 D_800A6474[] = {
    0, 0, 0x60040000,
};
s32 D_800A6480[] = {
    0, (s32)D_800A6420, (s32)D_800A642C, (s32)D_800A6438,
    (s32)D_800A6444, (s32)D_800A6450, (s32)D_800A645C, (s32)D_800A6468,
    (s32)D_800A6474,
};
s32 D_800A64A4[] = {
    140, 0, 0, (s32)D_800A62F4,
    (s32)D_800A6378, (s32)D_800A63FC, (s32)D_800A6480,
};
s32 D_800A64C0[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1200159, 0x200064, 0x1F50140,
    0x1000140, 0x1000147, 28, 0x1F50150,
    0x1000140, 0x1D80144, 0xD80010, 0x1F50160,
};
s32 D_800A6550[] = {
    0x16020, 65535,
};
s32 D_800A6558[] = {
    0x16020, 16454, 65535,
};
s32 D_800A6564[] = {
    0x16020, 65535,
};
s32 D_800A656C[] = {
    (s32)D_800A6550, 0, 0x40001, 0,
    0,
};
s32 D_800A6580[] = {
    (s32)D_800A6558, 0, 0x500D2, 0xC50168,
    3,
};
s32 D_800A6594[] = {
    (s32)D_800A6564, 0, 0x6013C, 0,
    1,
};
s32 D_800A65A8[] = {
    (s32)D_800A656C, (s32)D_800A6580, (s32)D_800A6594, 0,
};
s32 D_800A65B8[] = {
    0x6FF0101, 19, 0xEB0000, 78,
    0x2010000, 0x1506FF, 0, 0x4E00EB,
    0, 0x6FF0301, 22, 0xEB0000,
    78, 0x4010000, 0x1706FF, 0,
    0x4E00EB, 0, 0, 0,
    0, 0, 0,
};
void (*D_800A6614[])(void) = {
    func_800A5B08,
};
s32 D_800A6618[] = {
    880, (s32)D_800A5BFC,
#if VERSION_US
    0x14A0003,
#elif VERSION_EU
    0x1510003,
#endif
    0, (s32)func_800A5A64, 881, (s32)D_800A5D10,
#if VERSION_US
    0x14A0004,
#elif VERSION_EU
    0x1510004,
#endif
    0, (s32)func_800A5AB0, 882, (s32)D_800A5E9C,
#if VERSION_US
    0x14A0005,
#elif VERSION_EU
    0x1510005,
#endif
    0, (s32)func_800A5ADC, -1, 0,
    0, 0, 0,
};
