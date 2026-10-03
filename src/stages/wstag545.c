#include "common.h"
#include "stage.h"
extern s32 D_800A6230[];
extern s32 D_800A5EFC[];
extern s32 D_800A60AC[];
extern u8 D_800A5F18[];
extern u8 D_800A619C[];
extern u8 D_800A60C4[];
void func_800A5048();
extern void (*D_800A622C[])(void);
void func_800A5788();
void func_800A5900();
void func_800A4DE4();
void func_800A5350();
extern AnimFrame D_800A5BE0[];
extern AnimFrame D_800A5C18[];
extern AnimFrame *D_800A5CA4[3];
extern StageTileAtSpot D_800A5CB0[];

/* Steps an animation, holding its last frame, and returns the frame */
s32 func_800A4CDC(StageTileAnim *obj, AnimFrame *frames, s32 depth) {
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
        obj->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            obj->anim.index--;
            frame = &frames[obj->anim.index];
            obj->anim.timer += frame->duration;
        }
        func_800A4CDC(obj, frames, depth + 1);
    }
    return frame->frame;
}

/* Moves the record with the given animation to (x, y); hidden while running, shown and animated when done */
void func_800A4DE4(StageTileAt *task) {
    StageTile *rec;
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->obj.anim.index = 0;
        task->obj.anim.timer = D_800A5BE0[0].duration;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == task->anim) {
                task->obj.tile = rec;
                rec->unkA = task->x;
                rec->unkC = task->y;
            }
        }
        break;
    case TASK_RUN:
        task->obj.tile->visible = 0;
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->obj.anim.index = 0;
            task->obj.anim.timer = D_800A5BE0[0].duration;
            task->setSubstate(task, 1);
        }
        tile = task->obj.tile;
        tile->visible = 1;
        tile->frame = func_800A4CDC(&task->obj, D_800A5BE0, 0);
        break;
    case TASK_KILL:
        break;
    }
}

/* Creates a StageTileAt for the record with the given animation */
StageTileAt *func_800A4F18(s32 anim, s32 x, s32 y) {
    StageTileAt *task = createTask(func_800A4DE4, sizeof(StageTileAt), 0);

    task->anim = anim;
    task->x = x;
    task->y = y;
    return task;
}

s32 func_800A4F70(StageTileAnim *obj, AnimFrame *frames, s32 depth) {
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
        obj->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            return 0xFF;
        }
        func_800A4F70(obj, frames, depth + 1);
    }
    return frame->frame;
}

/* Shows the record with animation 1 (frame 0x18); when done, animates it once with a sound and goes back to TASK_RUN */
void func_800A5048(StageTileTask *task) {
    StageTile *rec;
    StageTile *shown;
    StageTile *tile;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->obj.anim.index = 0;
        task->obj.anim.timer = D_800A5C18[0].duration;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 1) {
                task->obj.tile = rec;
            }
        }
        break;
    case TASK_RUN:
        shown = task->obj.tile;
        shown->visible = 1;
        shown->frame = 0x18;
        shown->unk9 = 9;
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->obj.anim.index = 0;
            task->obj.anim.timer = D_800A5C18[0].duration;
            task->setSubstate(task, 1);
            SOUND.playSound(0x4C0002);
        }
        tile = task->obj.tile;
        frame = func_800A4F70(&task->obj, D_800A5C18, 0);
        if (frame == 0xFF) {
            task->setState(task, TASK_RUN);
            tile->unk9 = 9;
        } else {
            tile->unk9 = frame;
        }
        tile->visible = 1;
        tile->frame = 0x18;
        break;
    case TASK_KILL:
        break;
    }
}

void func_800A51C8(StageTask *task, s32 id) {
    if (task != NULL && id == 0x35A) {
        task->setState(task, TASK_DONE);
    }
}

void *func_800A5200(s32 arg) {
    return createTaskWithId(func_800A5048, 0x58, 0, arg);
}

s32 func_800A5230(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        obj->anim.timer += frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5230(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Animates the record with animation 2 by substate and sets the child an event picked to TASK_DONE */
void func_800A5350(StageTileSwitch *task, StageTileAts *children) {
    StageTile *rec;
    StageTile *tile;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 2) {
                task->obj.anim.index = 0;
                task->obj.anim.timer = D_800A5CA4[0][0].duration;
                task->obj.tile = rec;
            }
        }
        for (i = 0; i < 5; i++) {
            children->tiles[i] = func_800A4F18(D_800A5CB0[i].anim, D_800A5CB0[i].x, D_800A5CB0[i].y);
        }
        task->silent = 0;
        task->spawn = 0;
        task->nextState(task);
        break;
    case TASK_RUN:
        tile = task->obj.tile;
        switch (task->substate) {
        case 0:
            tile->visible = 0;
            break;
        case 1:
            if (task->step == 0) {
                task->obj.anim.index = 0;
                task->obj.anim.timer = D_800A5CA4[0][0].duration;
                task->setStep(task, 1);
            }
            {
                s32 frame = func_800A5230(&task->obj, D_800A5CA4[0], 1, 0);

                tile->visible = 1;
                if (frame == 0xFF) {
                    tile->frame = 8;
                    task->setSubstate(task, 2);
                } else {
                    tile->frame = frame;
                }
            }
            break;
        case 3:
            if (task->step == 0) {
                task->obj.anim.index = 0;
                task->obj.anim.timer = D_800A5CA4[1][0].duration;
                task->setStep(task, 1);
            }
            {
                s32 frame = func_800A5230(&task->obj, D_800A5CA4[1], 1, 0);

                tile->visible = 1;
                if (frame == 0xFF) {
                    tile->frame = 9;
                    task->setSubstate(task, 4);
                } else {
                    tile->frame = frame;
                }
            }
            break;
        case 5:
            if (task->step == 0) {
                task->obj.anim.index = 0;
                task->obj.anim.timer = D_800A5CA4[2][0].duration;
                task->setStep(task, 1);
                SOUND.playSound(0x4C0001);
            }
            {
                s32 frame = func_800A5230(&task->obj, D_800A5CA4[2], 0, 0);

                tile->visible = 1;
                tile->frame = frame;
            }
            break;
        case 2:
        case 4:
            break;
        }
        if (task->spawn != 0) {
            children->tiles[task->spawn - 1]->setState(children->tiles[task->spawn - 1], TASK_DONE);
            task->spawn = 0;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Events 0x35D to 0x364: animate the record (substates 1, 3, 5) or pick a child to set to TASK_DONE */
void func_800A5644(void *arg, s32 id) {
    StageTileSwitch *task = arg;

    if (task != NULL) {
        if (task->silent == 0) {
            SOUND.playSound(0x8004474A);
        }
        switch (id) {
        case 0x35D:
            task->setSubstate(task, 1);
            break;
        case 0x35E:
            task->setSubstate(task, 3);
            break;
        case 0x35F:
            task->setSubstate(task, 5);
            break;
        case 0x360:
            task->spawn = 1;
            break;
        case 0x361:
            task->spawn = 2;
            break;
        case 0x362:
            task->spawn = 3;
            break;
        case 0x363:
            task->spawn = 4;
            break;
        case 0x364:
            task->spawn = 5;
            break;
        }
        task->setStep(task, 0);
    }
}

/* Creates the task of func_800A5350 with the given id */
void *func_800A5758(s32 id) {
    return createTaskWithId(func_800A5350, 0x60, 0x14, id);
}

/* Creates the stage object of flag 0x4051, and the event object of story progress 26 */
void func_800A5788(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4051, 0)) {
            children[0] = func_800A5200(0x34F);
        }
        if (GAME_PROGRESS == 0x1A && FLAGS_00.checkCondition(0x4051, 1)) {
            children[2] = func_80084B80(0x2C7);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5848(void *owner) {
    StageTask *task = createTask(func_800A5788, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A622C[0]();
    return task;
}

void func_800A58A4(void) {
    FLAGS_00.applyAction(0x4051, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A58F0(void) {
    GAME_PROGRESS = 27;
}

#if VERSION_US
void func_800A5900(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x266;
    D_800990B4.unkC = 0x2670000;
    D_800990B4.unk10 = D_800A60C4;
    D_800990B4.unk14 = D_800A619C;
    D_800990B4.unk1C = 0x3CF;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x18800;
    D_800990B4.unk30 = 0x24600;
    D_800990B4.unk28 = D_800A5F18;
    D_800990B4.unk3C = 0x13;
    D_800990B4.unk40 = 0x604C0000;
    D_800990B4.unk4C = D_800A60AC;
    D_800990B4.unk20 = D_800A5EFC;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6230;
    D_8009A70C.unk40(0, 0x2670001);
    D_8009A70C.unk40(7, 0x2670002);
    D_8009A70C.unk40(4, 0x2670003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag545", func_800A5900);
#endif

extern AnimFrame D_800A5C64[];
extern AnimFrame D_800A5C8C[];
extern AnimFrame D_800A5C98[];
extern s32 D_800A5CEC[];
extern s32 D_800A5CF8[];
extern s32 D_800A5D04[];
extern s32 D_800A5D10[];
extern s32 D_800A5D1C[];
extern s32 D_800A5D28[];
extern s32 D_800A5D34[];
extern s32 D_800A5D40[];
extern s32 D_800A5D70[];
extern s32 D_800A5D7C[];
extern s32 D_800A5D88[];
extern s32 D_800A5D94[];
extern s32 D_800A5DA0[];
extern s32 D_800A5DAC[];
extern s32 D_800A5DB8[];
extern s32 D_800A5DC4[];
extern s32 D_800A5DF4[];
extern s32 D_800A5E00[];
extern s32 D_800A5E0C[];
extern s32 D_800A5E18[];
extern s32 D_800A5E24[];
extern s32 D_800A5E30[];
extern s32 D_800A5E3C[];
extern s32 D_800A5E48[];
extern s32 D_800A5E78[];
extern s32 D_800A5E84[];
extern s32 D_800A5E90[];
extern s32 D_800A5E9C[];
extern s32 D_800A5EA8[];
extern s32 D_800A5EB4[];
extern s32 D_800A5EC0[];
extern s32 D_800A5ECC[];
extern s32 D_800A5D4C[];
extern s32 D_800A5DD0[];
extern s32 D_800A5E54[];
extern s32 D_800A5ED8[];
extern s32 D_800A5F98[];
extern s32 D_800A6020[];
extern s32 D_800A5FA8[];
extern s32 D_800A6028[];
extern s32 D_800A5FC0[];
extern s32 D_800A6030[];
extern s32 D_800A5FD8[];
extern s32 D_800A6038[];
extern s32 D_800A5FF0[];
extern s32 D_800A6040[];
extern s32 D_800A6008[];
extern s32 D_800A6048[];
extern s32 D_800A605C[];
extern s32 D_800A6070[];
extern s32 D_800A6084[];
extern s32 D_800A6098[];
extern s32 D_800A5A14[];
extern s32 D_800A5B64[];

s32 D_800A5A14[] = {
    0x20102, 0x1C40218, 0x1010005, 0x337032D,
    0x1010002, 0x35C0350, 0x3020002, 0x1010002,
    0x10002, 0x3000005, 0x102001E, 0x2680002,
    0x5019C, 0x20302, 1537, 0x1840296,
    0x32D0101, 0x20372, 0x1E0300, 0x3230101,
    0x20325, 0x32D0101, 0x20369, 0x3C0300,
    0x20101, 0x10001, 0x3230101, 0x20326,
    0x1E0300, 0x20101, 0x30001, 0x1E0300,
    0x20101, 0x70001, 0x1E0300, 512,
    0x20001, 0x1010000, 0x10002, 0x3010001,
    0x34F0101, 0x2035A, 0x1E0300, 0x5A0300,
    0x20101, 0x50001, 0x34F0101, 0x2035A,
    0x5A0300, 0x3500101, 0x20360, 0x480300,
    0x3500101, 0x20361, 0x240300, 0x3500101,
    0x20362, 0x180300, 0x3500101, 0x20363,
    0x300300, 0x3500101, 0x20364, 0x600300,
    0x3500101, 0x2035D, 0x960300, 0x3500101,
    0x2035E, 0x120300, 0x32D0101, 0x20373,
    0x2A0300, 512, 0x20002, 0x3010000,
    0x3500101, 0x2035F, 0x3C0300, 512,
    0x20003, 0x3010000, 0x1E0300, 0,
};
s32 D_800A5B64[] = {
    0x10601, 0x184029A, 0x20100, 0x19C0268,
    0x20101, 0x50001, 0x780300, 512,
    0x20001, 0x3010002, 0x1E0300, 0x3230101,
    0x20325, 0x3C0300, 0x3230101, 0x20326,
    0x1E0300, 512, 0x20002, 0x3010002,
    0x1E0300, 0x20102, 0x1680268, 0x3020005,
    0x1020002, 0x2A80002, 0x50148, 0x60300,
    0x2450304, 0x20C0708, 3,
};
AnimFrame D_800A5BE0[] = {
    { 11, 4 }, { 12, 4 }, { 13, 7 }, { 14, 9 },
    { 15, 10 }, { 16, 8 }, { 17, 4 }, { 18, 4 },
    { 19, 4 }, { 20, 4 }, { 21, 4 }, { 22, 4 },
    { 23, 100 }, { 255, 0 },
};
AnimFrame D_800A5C18[] = {
    { 9, 25 }, { 8, 4 }, { 7, 4 }, { 6, 4 },
    { 5, 4 }, { 4, 4 }, { 3, 6 }, { 2, 7 },
    { 1, 8 }, { 0, 8 }, { 1, 10 }, { 2, 10 },
    { 3, 10 }, { 4, 10 }, { 5, 10 }, { 6, 10 },
    { 7, 10 }, { 8, 10 }, { 255, 0x3E7 },
};
AnimFrame D_800A5C64[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 8, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A5C8C[] = {
    { 10, 4 }, { 9, 10 }, { 255, 0x3E7 },
};
AnimFrame D_800A5C98[] = {
    { 10, 4 }, { 9, 4 }, { 255, 0 },
};
AnimFrame *D_800A5CA4[3] = { D_800A5C64, D_800A5C8C, D_800A5C98 };
StageTileAtSpot D_800A5CB0[] = {
    { 0x288, 0x1D7, 3 },
    { 0x32F, 0x170, 4 },
    { 0x250, 0x11F, 5 },
    { 0x307, 0x1C9, 6 },
    { 0x234, 0x171, 7 },
};
s32 D_800A5CEC[] = {
    165, 10, 0x60080000,
};
s32 D_800A5CF8[] = {
    165, 10, 0x60080000,
};
s32 D_800A5D04[] = {
    173, 10, 0x60080000,
};
s32 D_800A5D10[] = {
    173, 10, 0x60080000,
};
s32 D_800A5D1C[] = {
    150, 10, 0x60080000,
};
s32 D_800A5D28[] = {
    150, 10, 0x60080000,
};
s32 D_800A5D34[] = {
    150, 10, 0x60080000,
};
s32 D_800A5D40[] = {
    92, 10, 0x60080000,
};
s32 D_800A5D4C[] = {
    4, (s32)D_800A5CEC, (s32)D_800A5CF8, (s32)D_800A5D04,
    (s32)D_800A5D10, (s32)D_800A5D1C, (s32)D_800A5D28, (s32)D_800A5D34,
    (s32)D_800A5D40,
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
    0, 0, 0x60040000,
};
s32 D_800A5DC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DD0[] = {
    0, (s32)D_800A5D70, (s32)D_800A5D7C, (s32)D_800A5D88,
    (s32)D_800A5D94, (s32)D_800A5DA0, (s32)D_800A5DAC, (s32)D_800A5DB8,
    (s32)D_800A5DC4,
};
s32 D_800A5DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E54[] = {
    0, (s32)D_800A5DF4, (s32)D_800A5E00, (s32)D_800A5E0C,
    (s32)D_800A5E18, (s32)D_800A5E24, (s32)D_800A5E30, (s32)D_800A5E3C,
    (s32)D_800A5E48,
};
s32 D_800A5E78[] = {
    12, 10, 0x60880000,
};
s32 D_800A5E84[] = {
    315, 10, 0x60880000,
};
s32 D_800A5E90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5ECC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5ED8[] = {
    0, (s32)D_800A5E78, (s32)D_800A5E84, (s32)D_800A5E90,
    (s32)D_800A5E9C, (s32)D_800A5EA8, (s32)D_800A5EB4, (s32)D_800A5EC0,
    (s32)D_800A5ECC,
};
s32 D_800A5EFC[] = {
    61, 0, 0, (s32)D_800A5D4C,
    (s32)D_800A5DD0, (s32)D_800A5E54, (s32)D_800A5ED8,
};
u8 D_800A5F18[] = {
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
    0x80, 0x01, 0x00, 0x01, 0xA8, 0x01, 0xC8, 0x01,
    0xA0, 0x01, 0xC8, 0x00, 0x50, 0x01, 0xFC, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA0, 0x01, 0xC8, 0x01,
    0x80, 0x01, 0xC8, 0x00, 0x60, 0x01, 0xFC, 0x01,
};
s32 D_800A5F98[] = {
    0x1021B, 0x18B09, 0x17013, 65535,
};
s32 D_800A5FA8[] = {
    0, (s32)D_800A5F98, 612, 0,
    0, 0,
};
s32 D_800A5FC0[] = {
    0, 0, 37, 0,
    0, 0,
};
s32 D_800A5FD8[] = {
    0, 0, 300, 0,
    0, 0,
};
s32 D_800A5FF0[] = {
    0, 0, 38, 0,
    0, 0,
};
s32 D_800A6008[] = {
    0, 0, 272, 0,
    0, 0,
};
s32 D_800A6020[] = {
    539, 65535,
};
s32 D_800A6028[] = {
    0x1601A, 65535,
};
s32 D_800A6030[] = {
    0x1701A, 65535,
};
s32 D_800A6038[] = {
    0x17019, 65535,
};
s32 D_800A6040[] = {
    0x16026, 65535,
};
s32 D_800A6048[] = {
    (s32)D_800A6020, (s32)D_800A5FA8, 0x40021, 0x2B90311,
    1,
};
s32 D_800A605C[] = {
    (s32)D_800A6028, (s32)D_800A5FC0, 0x50045, 0x479022F,
    1,
};
s32 D_800A6070[] = {
    (s32)D_800A6030, (s32)D_800A5FD8, 0x50045, 0x479022F,
    1,
};
s32 D_800A6084[] = {
    (s32)D_800A6038, (s32)D_800A5FF0, 0x50045, 0x479022F,
    1,
};
s32 D_800A6098[] = {
    (s32)D_800A6040, (s32)D_800A6008, 0x50045, 0x479022F,
    1,
};
s32 D_800A60AC[] = {
    (s32)D_800A6048, (s32)D_800A605C, (s32)D_800A6070, (s32)D_800A6084,
    (s32)D_800A6098, 0,
};
u8 D_800A60C4[] = {
    0x01, 0x00, 0x64, 0x02, 0x63, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x11, 0x02, 0xD1, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x64, 0x02, 0x61, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xAB, 0x01, 0x10, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x64, 0x02,
    0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x02,
    0x14, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x64, 0x02, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF6, 0x01, 0x1B, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xBD, 0x02, 0x73, 0x01, 0x73, 0x01,
    0x00, 0x00, 0x00, 0x07, 0xF0, 0x04, 0x0B, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x34, 0x02, 0x71, 0x01,
    0x71, 0x01, 0x00, 0x00, 0x00, 0x05, 0xF0, 0x04,
    0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x02,
    0x1F, 0x01, 0x1F, 0x01, 0x00, 0x00, 0x00, 0x03,
    0xF0, 0x04, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x88, 0x02, 0xD7, 0x01, 0xD7, 0x01, 0x00, 0x00,
    0x00, 0x06, 0xF0, 0x04, 0x0B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x03, 0xC9, 0x01, 0xC9, 0x01,
    0x00, 0x00, 0x00, 0x04, 0xF0, 0x04, 0x0B, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2F, 0x03, 0x70, 0x01,
    0x70, 0x01, 0x00, 0x00, 0x00, 0x01, 0x50, 0x04,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x02,
    0x54, 0x01, 0x72, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A619C[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x45, 0x02, 0x08, 0x07, 0x0C, 0x02,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x45, 0x02, 0x08, 0x07, 0xDC, 0x02,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x45, 0x02, 0x08, 0x07, 0xBC, 0x03,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x45, 0x02, 0x08, 0x07, 0x0E, 0x05,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x60, 0x01, 0x00, 0x51, 0x40, 0x00, 0x00,
    0x08, 0x00, 0xC6, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A622C[])(void) = {
    func_800A5900,
};
s32 D_800A6230[] = {
    710, (s32)D_800A5A14,
#if VERSION_US
    0x1350021,
#elif VERSION_EU
    0x13C0021,
#endif
    0, (s32)func_800A58A4, 711, (s32)D_800A5B64,
#if VERSION_US
    0x135001F,
#elif VERSION_EU
    0x13C001F,
#endif
    0, (s32)func_800A58F0, -1, 0,
    0, 0, 0,
};
