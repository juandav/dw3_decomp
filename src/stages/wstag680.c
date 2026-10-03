#include "common.h"
#include "stage.h"
void func_800A4E9C();
extern void (*D_800A5854[])(void);
void func_800A52A0();
extern StageRiserFrame *D_800A564C[];

/* Steps a mover's looping animation, its last frame setting how far it moves */
s32 func_800A4DA0(StageRiser *obj, StageRiserFrame *frames, s32 depth) {
    StageRiserFrame *frame = &frames[obj->anim.index];
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
            obj->move = frame->move;
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A4DA0(obj, frames, depth + 1);
    }
    return frame->frame;
}

/* Animates and moves the records of the stage's table (lifts for animations 8-10) and pushes the player */
void func_800A4E9C(StageRisers *task) {
    StageTile *rec;
    StageTile *tile;
    StageActor *actor;
    s32 i;
    s32 j;

    switch (task->state) {
    case TASK_INIT:
    default:
        i = 0;
        j = 0;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 0:
                break;
            case 8:
            case 9:
            case 10:
                task->lifts[j].active = 0;
                task->lifts[j].speed = 0;
                task->lifts[j].tile = rec;
                j++;
                break;
            default:
                task->risers[i].tileAnim = rec->anim;
                task->risers[i].y = rec->unkC << 8;
                task->risers[i].active = 0;
                task->risers[i].anim.index = 0;
                task->risers[i].anim.timer = D_800A564C[i]->duration;
                task->risers[i].tile = rec;
                i++;
                break;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        for (i = 0; i < 11; i++) {
            if (task->risers[i].active) {
                tile = task->risers[i].tile;
                tile->frame = func_800A4DA0(&task->risers[i], D_800A564C[i], 0);
                tile->unkC += task->risers[i].move;
                task->risers[i].move = 0;
                if (tile->unkC > 0x190) {
                    task->risers[i].active = 0;
                }
            }
        }
        for (i = 0; i < 3; i++) {
            if (task->lifts[i].active) {
                tile = task->lifts[i].tile;
                task->lifts[i].speed += GFX.funcs.getFrameTime() << 7;
                tile->unkC += task->lifts[i].speed >> 8;
                if (tile->unkC > 0x190) {
                    task->lifts[i].active = 0;
                }
            }
        }
        if (task->pushing) {
            actor = TASK_FUNCS.find(5, -1, 0);
            task->push += 0x40;
            actor->y += task->push;
            if (task->timer++ > 0x78) {
                task->pushing = 0;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Starts the records an event moves (the handler of the events the task gets) */
void func_800A5140(void *arg, s32 event) {
    StageRisers *task = arg;
    StageActor *player;
    s32 anim;
    s32 i;

    if (task != NULL) {
        player = TASK_FUNCS.find(5, -1, 0);
        anim = 0;
        switch (event) {
        case 0x344:
            anim = 0;
            break;
        case 0x33D:
            anim = 1;
            break;
        case 0x33E:
            anim = 2;
            break;
        case 0x33F:
            task->lifts[0].active = 1;
            anim = 3;
            break;
        case 0x340:
            anim = 4;
            break;
        case 0x341:
            task->lifts[2].active = 1;
            anim = 5;
            break;
        case 0x342:
            anim = 6;
            break;
        case 0x343:
            anim = 7;
            task->lifts[1].active = 1;
            player->unk74 = 0;
            break;
        case 0x37B:
            task->pushing = 1;
            return;
        }
        if (anim != 0) {
            for (i = 0; i < 11; i++) {
                if (anim == task->risers[i].tileAnim) {
                    task->risers[i].active = 1;
                }
            }
            SOUND.playSound(0xEC0001);
        }
    }
}

void *func_800A5270(s32 arg) {
    return createTaskWithId(func_800A4E9C, 0x14C, 0, arg);
}

/* Creates the event object of story progress 15 */
void func_800A52A0(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (GAME_PROGRESS == 0xF) {
            children[0] = func_80084B80(0x19C);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5318(void *owner) {
    StageTask *task = createTask(func_800A52A0, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5854[0]();
    return task;
}

extern s32 D_800A5710[];
extern s32 D_800A5678[];
extern s32 D_800A5708[];
extern s32 D_800A5858[];
#if VERSION_US
#define STAGE_TEXT 0xD4
#define STAGE_FILE 0x62D
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xCC)
#define STAGE_FILE 0x63D
#endif
void func_800A5374(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5710;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x9F00, 0x8500};
    D_800990B4.unk28 = D_800A5678;
    D_800990B4.unk3C = 0x3B;
    D_800990B4.unk40 = 0x60EC0000;
    D_800990B4.unk4C = D_800A5708;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5858;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.unk50(0);
}

void func_800A5374();
extern StageRiserFrame D_800A5618[];
extern StageRiserFrame D_800A5628[];
extern StageRiserFrame D_800A5638[];
extern s32 D_800A56E8[];
extern s32 D_800A56F4[];
extern s32 D_800A5438[];

s32 D_800A5438[] = {
    0x10601, 0x7A00A2, 0x10100, 0xBA0104,
    0x10101, 0x30001, 0x32E0101, 0x10344,
    0x1E0300, 0x10102, 0x800090, 0x3020001,
    0x1010001, 0x10001, 0x3000001, 0x101001E,
    0x3A0001, 0x3000001, 0x101003C, 0x10001,
    0x3000001, 0x200001E, 0x10000, 1,
    0x3000301, 0x101001E, 0x33D032E, 0x303032E,
    0x300032E, 0x101001E, 0x3250323, 0x1010001,
    0x369032D, 0x3000001, 0x101003C, 0x3260323,
    0x3000001, 0x101001E, 0x10001, 0x3000007,
    0x101003C, 0x33E032E, 0x303032E, 0x300032E,
    0x200001E, 0x20000, 1, 0x3000301,
    0x101001E, 0x33F032E, 0x303032E, 0x300032E,
    0x101003C, 0x10001, 0x3000001, 0x101001E,
    0x3250323, 0x3000001, 0x101003C, 0x3260323,
    0x3000001, 0x102001E, 0xB00001, 0x10070,
    0x10302, 0x32E0101, 0x32E0340, 0x32E0303,
    0x10101, 0x10001, 0x3C0300, 0x32E0101,
    0x32E0341, 0x32E0303, 0x10101, 0x70033,
    0x1E0300, 512, 0x10003, 0x1010000,
    0x10001, 0x3010007, 0x1E0300, 0x10101,
    0x70001, 0x3230101, 0x10325, 0x3C0300,
    0x3230101, 0x10326, 0x1E0300, 0x10102,
    0x600090, 0x3020007, 0x1010001, 0x342032E,
    0x303032E, 0x300032E, 0x101005A, 0x343032E,
    0x303032E, 0x101032E, 0x3250323, 0x3000001,
    0x101003C, 0x3260323, 0x3000001, 0x101001E,
    0x250001, 0x3000007, 0x200001E, 0x40000,
    0x30001, 0x1010301, 0x37B032E, 0x3000001,
    0x304005A, 0x3300260, 264, 0,
};
StageRiserFrame D_800A5618[] = {
    { 14, 6, 0 },
    { 15, 6, 0 },
    { 16, 6, 0 },
    { 255, 0, 72 },
};
StageRiserFrame D_800A5628[] = {
    { 10, 6, 0 },
    { 11, 6, 0 },
    { 12, 6, 0 },
    { 255, 0, 80 },
};
StageRiserFrame D_800A5638[] = {
    { 5, 6, 0 },
    { 6, 6, 0 },
    { 7, 6, 0 },
    { 8, 6, 0 },
    { 255, 0, 80 },
};
StageRiserFrame *D_800A564C[] = {
    D_800A5618,
    D_800A5628,
    D_800A5618,
    D_800A5628,
    D_800A5628,
    D_800A5618,
    D_800A5638,
    D_800A5618,
    D_800A5628,
    D_800A5638,
    D_800A5638,
};
s32 D_800A5678[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1640176, 0x6400D8, 0x1FF0150,
};
s32 D_800A56E8[] = {
    0x1600F, 16412, 65535,
};
s32 D_800A56F4[] = {
    (s32)D_800A56E8, 0, 0x40001, 0,
    0,
};
s32 D_800A5708[] = {
    (s32)D_800A56F4, 0,
};
s32 D_800A5710[] = {
    0x2400001, 0x1000232, 0x380006, 56,
    0x10000, 0x2320240, 0x60100, 0x16007C,
    0, 0x6400001, 3, 0xF00000,
    176, 0x1010000, 0xD0640, 0,
    0xA000D0, 0, 0x6400201, 9,
    0xB00000, 144, 0x3010000, 0xD0640,
    0, 0x900070, 0, 0x6400301,
    9, 0x500000, 128, 0x4010000,
    0x90640, 0, 0x800090, 0,
    0x6400301, 13, 0x300000, 112,
    0x4010000, 0x40640, 0, 0x700070,
    0, 0x6400501, 13, 0xB00000,
    112, 0x4010000, 0x90640, 0,
    0x600050, 0, 0x6400601, 4,
    0x900000, 96, 0x7010000, 0x40640,
    0, 0x500070, 0, 0x6400801,
    0, 0x370000, 119, 0xA010000,
    0x10640, 0, 0x55007A, 0,
    0x6400901, 2, 0xD80000, 127,
    0, 0, 0, 0,
    0,
};
void (*D_800A5854[])(void) = {
    func_800A5374,
};
s32 D_800A5858[] = {
    412, (s32)D_800A5438,
#if VERSION_US
    0x13C0002,
#elif VERSION_EU
    0x1430002,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
