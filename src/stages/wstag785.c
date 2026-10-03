#include "common.h"
#include "stage.h"
void func_800A5178();
void func_800A4DC8();
extern void (*D_800A6494[])(void);
void func_800A54D0();
StageTileSet *func_800A5068(void);
extern AnimFrame D_800A5FD4[];
extern AnimFrame D_800A6010[];
extern AnimFrame D_800A6044[];
extern AnimFrame D_800A6060[];

/* The file of the marks, which the versions number differently */
#if VERSION_US
#define MARKS 0x1B9
#elif VERSION_EU
#define MARKS 0x1C7
#endif

s32 func_800A4CA8(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4CA8(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Plays the animations of records 4/3 then 2 (with 1 looping); starts at 2 when done is set */
void func_800A4DC8(StageTileSet *task) {
    StageTile *rec;
    StageTile *tile;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 1:
                task->tiles[3] = rec;
                break;
            case 2:
                task->tiles[2] = rec;
                break;
            case 3:
                task->tiles[1] = rec;
                break;
            case 4:
                task->tiles[0] = rec;
                break;
            }
        }
        task->anim2.index = 0;
        task->anim2.timer = D_800A6060[0].duration;
        if (task->done == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A5FD4[0].duration;
            task->nextState(task);
        } else {
            task->setState(task, TASK_DONE);
        }
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            tile = task->tiles[0];
            frame = func_800A4CA8(&task->anim, D_800A5FD4, 1, 0);
            if (frame == 0xFF) {
                task->setSubstate(task, 1);
                tile->visible = 0;
                task->anim.index = 0;
                task->anim.timer = D_800A6010[0].duration;
            } else {
                tile->unk9 = frame;
                tile->visible = 1;
            }
            break;
        case 1:
            tile = task->tiles[1];
            tile->unk9 = func_800A4CA8(&task->anim, D_800A6010, 0, 0);
            tile->visible = 1;
            break;
        case 2:
            break;
        }
        tile = task->tiles[3];
        tile->unk9 = func_800A4CA8(&task->anim2, D_800A6060, 0, 0);
        tile->visible = 1;
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A6044[0].duration;
            task->anim2.index = 0;
            task->anim2.timer = D_800A6060[0].duration;
            task->nextSubstate(task);
        }
        tile = task->tiles[2];
        tile->unk9 = func_800A4CA8(&task->anim, D_800A6044, 0, 0);
        tile->visible = 1;
        tile = task->tiles[3];
        tile->unk9 = func_800A4CA8(&task->anim2, D_800A6060, 0, 0);
        tile->visible = 1;
        break;
    case TASK_KILL:
        break;
    }
}

/* Creates the task of func_800A4DC8 already done */
StageTileSet *func_800A5068(void) {
    StageTileSet *task = createTask(func_800A4DC8, sizeof(StageTileSet), 0);

    task->done = 1;
    return task;
}

void *func_800A509C(s32 arg) {
    return createTaskWithId(func_800A4DC8, 0x6C, 0, arg);
}

/* Draws frame FRAME of file MARKS over the character */
void func_800A50CC(StageActorMark *task, s32 frame) {
    SpriteDrawer drawer;
    s32 pos[2];

    pos[0] = task->actor->x >> 8;
    pos[1] = (task->actor->y >> 8) - 0x18;
    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1002, 2);
    drawer.setTexture(0x140, 0x100);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](MARKS << 16 | 1), frame, pos[0], pos[1]);
}

/* Shows the mark over the character: opens (0x32-0x34), stays by kind, closes (0x36-0x37) */
void func_800A5178(StageActorMark *task) {
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            frame = 0x32;
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step < 4) {
                break;
            }
            task->nextSubstate(task);
        case 1:
            frame = 0x33;
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step < 4) {
                break;
            }
            task->nextSubstate(task);
        case 2:
            frame = 0x34;
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step < 4) {
                break;
            }
            task->nextSubstate(task);
        case 3:
            switch (task->kind) {
            case 0:
            default:
                frame = 0x35;
                break;
            case 1:
                frame = ((task->step >> 3) & 1) + 0x38;
                task->step += GFX_FUNCS.getFrameTime();
                break;
            case 2:
                frame = 0x3C;
                break;
            case 3:
                frame = 0x3D;
                break;
            }
            break;
        }
        func_800A50CC(task, frame);
        break;
    case TASK_DONE:
        switch (task->substate) {
        case 0:
        default:
            frame = 0x36;
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step < 4) {
                break;
            }
            task->nextSubstate(task);
        case 1:
            frame = 0x37;
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step < 4) {
                break;
            }
            task->nextState(task);
            break;
        }
        func_800A50CC(task, frame);
        break;
    case TASK_KILL:
        break;
    }
}

void *func_800A53D4(s32 arg) {
    return createTaskWithId(func_800A5178, 0x58, 0, arg);
}

/* Map objects 0x328/0x329 set the kind and the character (actor of key KEY), 0x32A ends it */
void func_800A5404(void *arg, s32 id, s32 key) {
    StageActorMark *task = arg;

    switch (id) {
    case 0x328:
        task->kind = 2;
        break;
    case 0x329:
        task->kind = 3;
        break;
    case 0x32A:
        task->setState(task, TASK_DONE);
        break;
    }
    switch (id) {
    case 0x328:
    case 0x329:
        task->actor = TASK_FUNCS.find(5, key, -1);
        break;
    }
}

/* Creates the event object of story progress 0 or 1 (with an object for 1) */
void func_800A54D0(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        switch (GAME_PROGRESS) {
        case 0:
            children[0] = func_80084B80(1);
            break;
        case 1:
            children[1] = func_800A5068();
            children[0] = func_80084B80(3);
            break;
        }
        task->nextState(task);
        children[1] = NULL;
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5574(void *owner) {
    StageTask *task = createTask(func_800A54D0, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A6494[0]();
    return task;
}

void func_800A55D0(void) {
    GAME_PROGRESS = 1;
}

extern s32 D_800A62C0[];
extern s32 D_800A607C[];
extern s32 D_800A628C[];
const CVECTOR D_800A4CA4 = { 0x80, 0x80, 0x80, 0x00 };
extern s32 D_800A6498[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x1B9
#define STAGE_ARCHIVE 0x3D2
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x1C7
#define STAGE_ARCHIVE 0x3E2
#endif
void func_800A55E0(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16 | 1;
    D_800990B4.unk10 = D_800A62C0;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0x15000, 0x18300};
    D_800990B4.unk28 = D_800A607C;
    D_800990B4.unk3C = 0x1B;
    D_800990B4.unk40 = 0x606C0000;
    D_800990B4.unk4C = D_800A628C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.events = D_800A6498;
    D_8009A70C.setFile(0, STAGE_FILE << 16);
    D_8009A70C.unk50(0);
}

void func_800A55E0();
extern s32 D_800A613C[];
extern s32 D_800A6144[];
extern s32 D_800A614C[];
extern s32 D_800A6154[];
extern s32 D_800A615C[];
extern s32 D_800A6164[];
extern s32 D_800A616C[];
extern s32 D_800A6174[];
extern s32 D_800A617C[];
extern s32 D_800A6184[];
extern s32 D_800A618C[];
extern s32 D_800A6194[];
extern s32 D_800A619C[];
extern s32 D_800A61B0[];
extern s32 D_800A61C4[];
extern s32 D_800A61D8[];
extern s32 D_800A61EC[];
extern s32 D_800A6200[];
extern s32 D_800A6214[];
extern s32 D_800A6228[];
extern s32 D_800A623C[];
extern s32 D_800A6250[];
extern s32 D_800A6264[];
extern s32 D_800A6278[];
extern s32 D_800A56CC[];
extern s32 D_800A5EBC[];

s32 D_800A56CC[] = {
    0x10601, 0x15001E0, 0x10100, 0x1000280,
    0x10101, 0x10001, 0xB0100, 0xF002A0,
    0xB0101, 0x10001, 0xC0100, 0xE002C0,
    0xC0101, 0x10001, 0xD0100, 0x121014A,
    0xD0101, 0x10001, 0xE0100, 0x1260185,
    0xE0101, 0x70003, 0xF0100, 0xFC0136,
    0xF0101, 0x20003, 0x1E0300, 0x10102,
    0x15001E0, 0x1020001, 0x200000B, 0x10140,
    0xC0102, 0x1300220, 0x3020001, 0x6000001,
    0x10001, 0x10102, 0x15801D0, 0x1020001,
    0x1E0000B, 0x10140, 0xC0102, 0x1380210,
    0x3020001, 0x1010001, 0x3A0001, 0x1010001,
    0x3A000B, 0x1010003, 0x3A000C, 0x3000005,
    0x200003C, 0x10000, 1, 0x10101,
    0x10001, 0x1010301, 0x3A0001, 0x1010001,
    0x1000C, 0x3000003, 0x101001E, 0x3250323,
    0x300000C, 0x101003C, 0x3260323, 0x3000001,
    0x102001E, 0x200000C, 0x30130, 0xC0302,
    1536, 0x200000C, 0x20000, 12,
    0xB0101, 0x3003A, 0xC0101, 0x20007,
    0x1010301, 0x3B000B, 0x1010003, 0x3B000C,
    0x3000003, 0x101003C, 0x10001, 0x3000005,
    0x6000078, 0x10000, 0x10101, 0x5002A,
    0x780300, 0x10101, 0x50001, 0x1E0300,
    1536, 0x2000001, 0x30000, 1,
    0x10101, 0x50007, 0x1010301, 0x2A0001,
    0x1010005, 0x1000B, 0x1010001, 0x1000C,
    0x1010001, 0x3250323, 0x101000C, 0x3250324,
    0x300000B, 0x101005A, 0x10001, 0x1010005,
    0x3260323, 0x1010001, 0x3260324, 0x3000001,
    0x101001E, 0x10001, 0x1010005, 0x1000B,
    0x1010001, 0x1000C, 0x3000001, 0x101001E,
    0x9000B, 0x1010001, 0x9000C, 0x3030001,
    0x101000C, 0x1000B, 0x1010001, 0x1000C,
    0x3000001, 0x102001E, 0x1700001, 0x30158,
    0xB0102, 0x1580170, 0x1020003, 0x170000C,
    0x30158, 0x10302, 0x10102, 0x12E0124,
    0x3020005, 0x102000B, 0x144000B, 0x5013E,
    0xC0302, 0xC0102, 0x14E0164, 0x3020005,
    0x101000B, 0x10001, 0x1010005, 0x1000B,
    0x1010005, 0x1000C, 0x1010005, 0x1000D,
    0x3000001, 0x101001E, 0x9000D, 0x3030001,
    0x101000D, 0x1000D, 0x3000001, 0x600001E,
    0xD0000, 512, 0xD0004, 0x1010000,
    0x7000D, 0x3010001, 0xD0101, 0x10001,
    0x1E0300, 0x10101, 0x50009, 0xB0101,
    0x50009, 0xC0101, 0x50009, 0x10303,
    0x10101, 0x50001, 0xB0101, 0x50001,
    0xC0101, 0x50001, 0x1E0300, 1536,
    0x200000D, 0x50000, 13, 0xD0101,
    0x10007, 0x1010301, 0x1000D, 0x3000001,
    0x600001E, 0xB0000, 0x3230101, 0x10325,
    0x3240101, 0xB0325, 0x3250101, 0xC0325,
    0x5A0300, 0x3230101, 0x10326, 0x3240101,
    0x10326, 0x3250101, 0x10326, 0x1E0300,
    1536, 0x200000D, 0x60000, 13,
    0xD0101, 0x10007, 0x1010301, 0x1000D,
    0x3000001, 0x101001E, 0x90001, 0x1010005,
    0x9000B, 0x1010005, 0x9000C, 0x3030005,
    0x2000001, 0x70000, 13, 0x10101,
    0x50001, 0xB0101, 0x50001, 0xC0101,
    0x50001, 0xD0101, 0x10007, 0x1010301,
    0x1000D, 0x3000001, 0x600001E, 0x10000,
    0x10101, 0x50029, 0xB0101, 0x50009,
    0xC0101, 0x50009, 0x3230101, 0x10327,
    0xB0303, 0x10101, 0x10029, 0xB0101,
    0x50001, 0xC0101, 0x50001, 0x780300,
    0xB0101, 0x30001, 0xC0101, 0x30001,
    0x1E0300, 1536, 0x101000B, 0x39000B,
    0x3030003, 0x101000B, 0x1000B, 0x3000003,
    0x101001E, 0x290001, 0x1020001, 0xF4000B,
    0x50166, 0xB0302, 0x10101, 0x10001,
    0xB0101, 0x50001, 0xC0101, 0x10001,
    0x3230101, 0x10326, 0x1E0300, 0x10102,
    0x13E0104, 0x1020001, 0x144000C, 0x1015E,
    0x10302, 0x1E0300, 512, 0xB0008,
    0x1010001, 0x7000B, 0x3010005, 0xB0101,
    0x50001, 0x1E0300, 1536, 0x2000001,
    0x90000, 1, 0x10101, 0x10007,
    0xB0101, 0x50001, 0xC0101, 0x1003B,
    0x3270101, 0xC0328, 0x1010301, 0x10001,
    0x1010001, 0x39000B, 0x1010005, 0x1000C,
    0x1010001, 0x32A0327, 0x3030001, 0x101000B,
    0x1000B, 0x3000005, 0x600001E, 0xB0000,
    512, 0xB000A, 0x1010001, 0x7000B,
    0x3010005, 0xB0101, 0x50001, 0x1E0300,
    1536, 0x2000001, 0xB0000, 1,
    0x10101, 0x10007, 0x3270101, 0xC0329,
    0x1010301, 0x10001, 0x1010001, 0x32A0327,
    0x3000001, 0x600001E, 0xB0000, 0xB0101,
    0x10001, 0x1E0300, 0xB0101, 0x10039,
    0xB0303, 0xB0101, 0x10001, 0x1E0300,
    0xB0101, 0x50001, 0x1E0300, 512,
    0xB000C, 0x1010001, 0x7000B, 0x3010005,
    0xB0101, 0x50001, 0x1E0300, 0x10101,
    0x10029, 0xB0102, 0x13E0144, 0x1020005,
    0x164000C, 0x5014E, 0x3230101, 0x10327,
    0xB0302, 0xB0101, 0x50001, 0xC0101,
    0x50001, 0x1E0300, 0xB0101, 0x10001,
    0xC0101, 0x10001, 0x1E0300, 512,
    0xB000D, 0x1010000, 0x7000B, 0x3010001,
    0x10101, 0x10001, 0xB0101, 0x10001,
    0x3230101, 0x10326, 0x1E0300, 0x3230101,
    0x10325, 0x3C0300, 0x10102, 0x12E0124,
    0x1010005, 0x1000B, 0x1010005, 0x1000C,
    0x1010005, 0x3260323, 0x3020001, 0x1010001,
    0x10001, 0x3000005, 0x200001E, 0xE0000,
    13, 0xD0101, 0x10007, 0x1010301,
    0x1000D, 0x3000001, 0x101001E, 0x290001,
    0x1010005, 0x9000B, 0x1010005, 0x9000C,
    0x1010005, 0x3270323, 0x3030001, 0x101000B,
    0x1000B, 0x1010005, 0x1000C, 0x3000005,
    0x101003C, 0x1000B, 0x3000003, 0x200001E,
    0xF0000, 11, 0xB0101, 0x30007,
    0x1010301, 0x10001, 0x1010005, 0x1000B,
    0x1010003, 0x3260323, 0x3000001, 0x101001E,
    0x2E0001, 0x3030005, 0x1010001, 0x10001,
    0x3000005, 0x101001E, 0x90001, 0x3030005,
    0x1010001, 0x10001, 0x1010005, 0x1000B,
    0x1010005, 0x1000C, 0x3000005, 0x200001E,
    0x100000, 13, 0xD0101, 0x10007,
    0x1010301, 0x90001, 0x1010005, 0x9000B,
    0x1010005, 0x9000C, 0x1010005, 0x1000D,
    0x3030001, 0x1010001, 0x10001, 0x1010005,
    0x1000B, 0x1010005, 0x1000C, 0x1010005,
    0x2000D, 0x1010001, 0x3350343, 0x3000001,
    0x3040096, 0x640500, 100, 0,
};
s32 D_800A5EBC[] = {
    0x10600, 0x100000B, 0x1240001, 0x101012E,
    0x10001, 0x1010005, 0x10002, 0x1000001,
    0x144000B, 0x101013E, 0x1000B, 0x1000005,
    0x164000C, 0x101014E, 0x1000C, 0x1000005,
    0x14A000D, 0x1010121, 0x1000D, 0x1000001,
    0x185000E, 0x1010126, 0x1000E, 0x1000007,
    0x136000F, 0x10100FC, 0x1000F, 0x3000002,
    0x2000078, 0x10000, 13, 0x1010301,
    0x10001, 0x1010007, 0x1000B, 0x1010003,
    0x1000C, 0x3000003, 0x200001E, 0x20000,
    1, 0x10101, 0x70007, 0x3000301,
    0x102001E, 0xB30001, 0x100F5, 0x10302,
    0x10101, 0x10001, 0xB0101, 0x30001,
    0xC0101, 0x30001, 0x1E0300, 0x10200,
    0xC0004, 0x2000001, 0x30000, 0x2000B,
    0x10102, 0x12F003D, 0x1010001, 0x7000B,
    0x1010002, 0x7000C, 0x3010002, 0x2D90304,
    0x640064, 0,
};
AnimFrame D_800A5FD4[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 8, 4 }, { 9, 4 }, { 10, 4 }, { 11, 4 },
    { 12, 4 }, { 13, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A6010[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 8, 4 }, { 9, 4 }, { 10, 4 }, { 11, 4 },
    { 255, 0 },
};
AnimFrame D_800A6044[] = {
    { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 },
    { 4, 8 }, { 5, 8 }, { 255, 0 },
};
AnimFrame D_800A6060[] = {
    { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 },
    { 4, 8 }, { 5, 8 }, { 255, 0 },
};
s32 D_800A607C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x11F019C, 0x1F0170, 0x1F10140,
    0x1000180, 0x12901A4, 0x290190, 0x1F10160,
    0x1000180, 0x12901AC, 0x2901B0, 0x1F10170,
    0x1000140, 0x1380176, 0x3800D8, 0x1F00140,
    0x1000180, 0x11001B6, 0x1001D8, 0x1F00160,
    0x1000180, 0x11F0194, 0x1F0150, 0x1F00170,
};
s32 D_800A613C[] = {
    0x16000, 65535,
};
s32 D_800A6144[] = {
    0x16001, 65535,
};
s32 D_800A614C[] = {
    0x16000, 65535,
};
s32 D_800A6154[] = {
    0x16001, 65535,
};
s32 D_800A615C[] = {
    0x16000, 65535,
};
s32 D_800A6164[] = {
    0x16001, 65535,
};
s32 D_800A616C[] = {
    0x16001, 65535,
};
s32 D_800A6174[] = {
    0x16000, 65535,
};
s32 D_800A617C[] = {
    0x16000, 65535,
};
s32 D_800A6184[] = {
    0x16001, 65535,
};
s32 D_800A618C[] = {
    0x16000, 65535,
};
s32 D_800A6194[] = {
    0x16001, 65535,
};
s32 D_800A619C[] = {
    (s32)D_800A613C, 0, 0x40001, 0,
    1,
};
s32 D_800A61B0[] = {
    (s32)D_800A6144, 0, 0x40001, 0,
    1,
};
s32 D_800A61C4[] = {
    (s32)D_800A614C, 0, 0x5000B, 0,
    1,
};
s32 D_800A61D8[] = {
    (s32)D_800A6154, 0, 0x5000B, 0,
    1,
};
s32 D_800A61EC[] = {
    (s32)D_800A615C, 0, 0x6000C, 0,
    1,
};
s32 D_800A6200[] = {
    (s32)D_800A6164, 0, 0x6000C, 0,
    1,
};
s32 D_800A6214[] = {
    (s32)D_800A616C, 0, 0x7000D, 0,
    1,
};
s32 D_800A6228[] = {
    (s32)D_800A6174, 0, 0x7000D, 0,
    1,
};
s32 D_800A623C[] = {
    (s32)D_800A617C, 0, 0x8000E, 0,
    1,
};
s32 D_800A6250[] = {
    (s32)D_800A6184, 0, 0x8000E, 0,
    1,
};
s32 D_800A6264[] = {
    (s32)D_800A618C, 0, 0x9000F, 0,
    1,
};
s32 D_800A6278[] = {
    (s32)D_800A6194, 0, 0x9000F, 0,
    1,
};
s32 D_800A628C[] = {
    (s32)D_800A619C, (s32)D_800A61B0, (s32)D_800A61C4, (s32)D_800A61D8,
    (s32)D_800A61EC, (s32)D_800A6200, (s32)D_800A6214, (s32)D_800A6228,
    (s32)D_800A623C, (s32)D_800A6250, (s32)D_800A6264, (s32)D_800A6278,
    0,
};
s32 D_800A62C0[] = {
    0x2640100, 0x500024A, 0x12B0008, 232,
    0x10000, 0x2510240, 0xA0B00, 0xFE009C,
    0, 0x2400001, 0xB000251, 0xEC000A,
    358, 0x10000, 0x2510240, 0xA0B00,
    0x166018E, 0, 0x2640001, 0x500024B,
    0x1710008, 246, 0x4000000, 0x2460264,
    0x40D00, 0xE8012B, 0, 0x2640300,
    0xB000247, 0x12B0008, 232, 0x2000000,
    0x2480264, 0x80500, 0xE8012B, 0,
    0x2640001, 0x5000249, 0x1710008, 246,
    0x10000, 0x500240, 0, 0xFE009C,
    0, 0x2400001, 80, 0xEC0000,
    358, 0x10000, 0x500240, 0,
    0x166018E, 0, 0x2640001, 0x3000252,
    0x1940008, 239, 0x10000, 1088,
    0, 0x1900192, 408, 0x4400001,
    12, 0xF10000, 0x1970190, 0x10000,
    0xD0440, 0, 0x12700A0, 303,
    0x4400001, 14, 0x1210000, 0x10900F4,
    0x10000, 0xF0440, 0, 0x1060121,
    292, 0x4400001, 16, 0x1310000,
    0x12C0110, 0x10000, 0x110440, 0,
    0x1170141, 308, 0x4400001, 18,
    0x1510000, 0x13C011E, 0x10000, 0x130440,
    0, 0x12A0161, 324, 0x4400001,
    20, 0x1710000, 0x13C0121, 0x10000,
    0x150440, 0, 0x1190181, 308,
    0x4400001, 22, 0x18F0000, 0x12C0111,
    0, 0, 0, 0,
    0,
};
void (*D_800A6494[])(void) = {
    func_800A55E0,
};
s32 D_800A6498[] = {
    1, (s32)D_800A56CC,
#if VERSION_US
    0x1430001,
#elif VERSION_EU
    0x14A0001,
#endif
    0, (s32)func_800A55D0, 3, (s32)D_800A5EBC,
#if VERSION_US
    0x1430002,
#elif VERSION_EU
    0x14A0002,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
