#include "common.h"
#include "stage.h"
void func_800A5DE0();
extern void (*D_800A65B8[])(void);
extern AnimFrame *D_800A67B4[];
void func_800A6110();
extern s8 D_800A67C0[];
extern s8 D_800A67C4[];

/* Creates the event object of flag 0x40CD while it is clear */
void func_800A5DE0(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (FLAGS_00.checkCondition(0x40CD, 0)) {
            children[0] = func_80084B80(0x640);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5E64(void *owner) {
    StageTask *task = createTask(func_800A5DE0, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A65B8[0]();
    return task;
}

/* Applies flag actions 0x40CD and 0x7053 */
void func_800A5EC0(void) {
    FLAGS_00.applyAction(0x40CD, 1);
    FLAGS_00.applyAction(0x7053, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag925", func_800A5F0C);

s32 func_800A6000(Anim4 *obj, AnimFrame *frames, s32 depth) {
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
        func_800A6000(obj, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A60D8(StageTileEffect *task) {
    s32 i;

    for (i = 0; i < 3; i++) {
        task->anims[i].anim.index = 0;
        task->anims[i].anim.timer = D_800A67B4[i][0].duration;
    }
}

/* Moves the records with animations 1 to 3 to (x, y) and plays their animations once with a sound, then hides them and kills itself */
void func_800A6110(StageTileEffect *task) {
    StageTile *rec;
    StageTile *tile;
    s32 i;
    s32 j;
    s32 k;
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A60D8(task);
        task->nextState(task);
        task->setSubstate(task, 1);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            switch (task->step) {
            case 0:
                i = 0;
                for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
                    if (rec->anim >= 1 && rec->anim <= 3) {
                        task->anims[i].tile = rec;
                        rec->unkA = task->x;
                        rec->unkC = task->y + D_800A67C4[i];
                        rec->unkE = task->y + D_800A67C0[i];
                        i++;
                    }
                }
                SOUND.playSound(0xCC0001);
                task->nextStep(task);
            case 1:
                done = 0;
                for (j = 0; j < 3; j++) {
                    tile = task->anims[j].tile;
                    frame = func_800A6000(&task->anims[j], D_800A67B4[j], 0);
                    switch (frame) {
                    case 0xFF:
                        done++;
                    case 0x12C:
                        tile->visible = 0;
                        tile->frame = 0;
                        break;
                    default:
                        tile->visible = 1;
                        tile->frame = frame;
                        break;
                    }
                }
                if (done < 3) {
                    break;
                }
                task->nextStep(task);
            case 2:
                for (k = 0; k < 3; k++) {
                    task->anims[k].tile->visible = 0;
                }
                func_800A60D8(task);
                task->setState(task, TASK_KILL);
                break;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the StageTileEffect of func_800A6110 at (0x150, 0x112) with the given id */
void *func_800A639C(s32 id) {
    StageTileEffect *task = createTaskWithId(func_800A6110, sizeof(StageTileEffect), 0, id);

    task->x = 0x150;
    task->y = 0x112;
    return task;
}

void func_800A5F0C();
void func_800A5EC0();
extern s32 D_800A6474[];
extern s32 D_800A645C[];
extern s32 D_800A647C[];
extern s32 D_800A6490[];
extern s32 D_800A65E4[];
extern AnimFrame D_800A6710[];
extern AnimFrame D_800A6774[];
extern AnimFrame D_800A6724[];

s32 D_800A63DC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1B8014A, 0xB80028, 0x1FE0170,
    0x1000140, 0x1B00170, 0xB000C0, 0x1FD0160,
};
s32 D_800A645C[] = {
    0, 0, 38, 0,
    0, 0,
};
s32 D_800A6474[] = {
    16589, 65535,
};
s32 D_800A647C[] = {
    (s32)D_800A6474, 0, 0x40001, 0,
    1,
};
s32 D_800A6490[] = {
    0, (s32)D_800A645C, 0x5000D, 0x18D0109,
    3,
};
s32 D_800A64A4[] = {
    (s32)D_800A647C, (s32)D_800A6490, 0,
};
s32 D_800A64B0[] = {
    0x6500100, 70, 0x700000, 274,
    0x10000, 0x13F0640, 0x6423F, 0x1020074,
    0, 0x6400001, 0x423F013F, 0xE40006,
    282, 0x10000, 0x13F0640, 0x6423F,
    0x1020154, 0, 0x6400001, 0x423F013F,
    0x1630006, 346, 0x2000000, 0x480450,
    0, 0xE30070, 301, 0x4500300,
    85, 0x700000, 0x12600E3, 0x10000,
    0x13B0440, 0x63E3B, 0x1120074, 300,
    0x4400001, 0x3E3B013B, 0xE40006, 0x144012A,
    0x10000, 0x13B0440, 0x63E3B, 0x1120154,
    300, 0x4400001, 0x3E3B013B, 0x1630006,
    0x184016A, 0, 0, 0,
    0, 0,
};
s32 D_800A6588[] = {
    65535, 65535, 0x2730001, 0x17E02DA,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A65B8[])(void) = {
    func_800A5F0C,
};
s32 D_800A65BC[] = {
    1600, (s32)D_800A65E4, 0x1580000, 0,
    (s32)func_800A5EC0, -1, 0, 0,
    0, 0,
};
s32 D_800A65E4[] = {
    0x10601, 0x127011E, 0x10100, 0,
    0x10101, 1, 0xD0100, 0x191010F,
    0xD0101, 0x30001, 0x780300, 0x1E0300,
    0x3570101, 0x10335, 0x5A0300, 0x5A0300,
    0x10100, 0x11F0170, 0x10101, 0x10001,
    0xB40300, 0x1E0300, 0x10102, 0x1300150,
    0x3020001, 0x1010001, 0x3A0001, 0x3000001,
    0x20000B4, 0x10000, 1, 0x10101,
    0x10001, 0x3000301, 0x102001E, 0x1300001,
    0x10160, 0x10302, 1536, 0x1020001,
    0xF00001, 0x10180, 0x10302, 0x10101,
    0x70001, 0x1E0300, 512, 0xD0002,
    0x1010002, 0x7000D, 0x3010003, 0xD0101,
    0x30001, 0x1E0300, 512, 0x10003,
    0x1010001, 0x70001, 0x3010007, 0x10101,
    0x10001, 0x1E0300, 512, 0x10004,
    0x3010001, 0x1E0300, 0x10102, 0x1D00050,
    0x1010001, 0x1000D, 0x3000001, 0x304005A,
    0x2DA0273, 0x1017E, 0,
};
AnimFrame D_800A6710[] = {
    { 70, 4 }, { 71, 4 }, { 70, 4 }, { 71, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A6724[] = {
    { 0x12C, 56 }, { 85, 6 }, { 86, 6 }, { 87, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 88, 4 },
    { 89, 4 }, { 90, 4 }, { 88, 4 }, { 89, 4 },
    { 90, 4 }, { 88, 4 }, { 89, 4 }, { 90, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A6774[] = {
    { 0x12C, 16 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 73, 4 }, { 75, 6 }, { 76, 6 }, { 77, 14 },
    { 78, 114 }, { 79, 6 }, { 80, 6 }, { 81, 6 },
    { 82, 6 }, { 83, 6 }, { 84, 8 }, { 255, 0x3E7 },
};
AnimFrame *D_800A67B4[] = {
    D_800A6710, D_800A6774, D_800A6724,
};
s8 D_800A67C0[] = {
    30, 30, 30, 0,
};
