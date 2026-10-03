#include "common.h"
#include "stage.h"
void func_800A4DB4();
extern void (*D_800A5C44[])(void);
void func_800A50EC();
extern AnimFrame *D_800A577C[];
extern s8 D_800A5788[];
extern s8 D_800A578C[];
extern s16 D_800A5790[][2];

s32 func_800A4CA4(Anim4 *obj, AnimFrame *frames, s32 depth) {
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
        func_800A4CA4(obj, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A4D7C(StageTileEffect *task) {
    s32 i;

    for (i = 0; i < 3; i++) {
        task->anims[i].anim.index = 0;
        task->anims[i].anim.timer = D_800A577C[i][0].duration;
    }
}

/* Moves its records to (x, y) and animates them when the substate is set to 1 */
void func_800A4DB4(StageTileEffect *task) {
    StageTile *tile;
    StageTile *t;
    s32 i;
    s32 n;
    s32 j;
    s32 frame;
    s32 done;

    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A4D7C(task);
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            switch (task->step) {
            case 0:
                n = 0;
                for (t = D_800990B4.unk10; t->unk2 != 0; t++) {
                    if (t->anim >= 1 && t->anim <= 3) {
                        task->anims[n].tile = t;
                        t->unkA = task->x;
                        t->unkC = task->y + D_800A578C[n];
                        t->unkE = task->y + D_800A5788[n];
                        n++;
                    }
                }
                func_800A4D7C(task);
                task->nextStep(task);
            case 1:
                done = 0;
                for (i = 0; i < 3; i++) {
                    tile = task->anims[i].tile;
                    frame = func_800A4CA4((Anim4 *)&task->anims[i], D_800A577C[i], 0);
                    switch (frame) {
                    case 0xFF:
                        done++;
                        tile->visible = 0;
                        tile->frame = 0;
                        break;
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
                for (j = 0; j < 3; j++) {
                    task->anims[j].tile->visible = 0;
                }
                func_800A4D7C(task);
                task->setSubstate(task, 0);
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

/* Starts the effect at the place of map 0 or 1 */
void func_800A5028(StageTileEffect *task, s32 id) {
    s32 i;

    if (task != NULL) {
        i = 0;
        switch (id) {
        case 1:
            i = 1;
        case 0:
            task->x = D_800A5790[i][0];
            task->y = D_800A5790[i][1];
            task->setSubstate(task, 1);
            break;
        }
    }
}

void *func_800A5090(s32 arg) {
    return createTaskWithId(func_800A4DB4, 0x70, 0, arg);
}

void *func_800A50C0(void) {
    return createTask(func_800A4DB4, 0x70, 0);
}

/* Creates the stage helper task and the event object of progress 0x25 when flag 0x4060 is set */
void func_800A50EC(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[1] = func_800A50C0();
        do {
            if (GAME_PROGRESS == 0x25 && FLAGS_00.checkCondition(0x4060, 1)) {
                children[0] = func_80084B80(0x3A7);
                break;
            }
        } while (0);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A518C(void *owner) {
    StageTask *task = createTask(func_800A50EC, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5C44[0]();
    return task;
}

void func_800A51E8(void) {
    GAME_PROGRESS = 38;
}

INCLUDE_ASM("stages/nonmatchings/wstag226", func_800A51F8);

void func_800A51F8();
extern AnimFrame D_800A56D8[];
extern AnimFrame D_800A573C[];
extern AnimFrame D_800A56EC[];
extern s32 D_800A5878[];
extern s32 D_800A5880[];
extern s32 D_800A5888[];
extern s32 D_800A5890[];
extern s32 D_800A5898[];
extern s32 D_800A58A0[];
extern s32 D_800A58A8[];
extern s32 D_800A5994[];
extern s32 D_800A59A0[];
extern s32 D_800A59AC[];
extern s32 D_800A59B8[];
extern s32 D_800A58B0[];
extern s32 D_800A59C0[];
extern s32 D_800A58D4[];
extern s32 D_800A59CC[];
extern s32 D_800A58EC[];
extern s32 D_800A59D8[];
extern s32 D_800A5904[];
extern s32 D_800A59E4[];
extern s32 D_800A5928[];
extern s32 D_800A59F0[];
extern s32 D_800A5940[];
extern s32 D_800A59F8[];
extern s32 D_800A5958[];
extern s32 D_800A5A00[];
extern s32 D_800A597C[];
extern s32 D_800A5A0C[];
extern s32 D_800A5A18[];
extern s32 D_800A5A2C[];
extern s32 D_800A5A40[];
extern s32 D_800A5A54[];
extern s32 D_800A5A68[];
extern s32 D_800A5A7C[];
extern s32 D_800A5A90[];
extern s32 D_800A5AA4[];
extern s32 D_800A5AB8[];
extern s32 D_800A5ACC[];
extern s32 D_800A5AE0[];
extern s32 D_800A5AF4[];
extern s32 D_800A5330[];

s32 D_800A5330[] = {
    0x10100, 0x1CC0058, 0x10101, 0x50001,
    0x9D0100, 0x18D0109, 0x9D0101, 0x30001,
    0x1E0300, 0x10102, 0x1BC0078, 0x1000005,
    0x58000C, 0x10101CC, 0x1000C, 0x3020005,
    0x1020001, 0xA00001, 0x501A8, 0xC0102,
    0x1B80080, 0x3020005, 0x1010001, 0x10001,
    0x1010005, 0x1000C, 0x1010005, 0x3250323,
    0x1010001, 0x3250324, 0x300000C, 0x101003C,
    0x3260323, 0x1010001, 0x3260324, 0x300000C,
    0x102001E, 0xF00001, 0x50180, 0xC0102,
    0x19000D0, 0x3020005, 0x101000C, 0x3A0001,
    0x1020007, 0xD0000C, 0x40178, 0xC0302,
    0x10101, 0x7002F, 0xC0102, 0x16100FE,
    0x1010005, 0x3270323, 0x3000001, 0x101005A,
    0x3A000C, 0x1010003, 0x3260323, 0x3000001,
    0x200003C, 0x10000, 0x30001, 0xC0101,
    0x5003A, 0x3000301, 0x600001E, 0xC0000,
    512, 0xC0002, 0x1010000, 0x10001,
    0x1010004, 0x7000C, 0x1010000, 0x1009D,
    0x3010004, 0xB0100, 0x1CC0058, 0xB0101,
    0x50001, 0xC0101, 1, 0x1E0300,
    0xB0102, 0x1BC0078, 0x1000005, 0x58013D,
    0x10101CC, 0x1013D, 0x3020005, 0x102000B,
    0xD0000B, 0x50190, 0x9D0101, 0x20001,
    0x13D0102, 0x1A000B0, 0x3020005, 0x101000B,
    0x1000B, 0x1010005, 0x1013D, 0x3000005,
    0x600001E, 0xB0000, 512, 0xB000B,
    0x1010001, 0x7000B, 0x3010005, 0xC0101,
    0x50001, 0x3230101, 0x10325, 0x3240101,
    0xC0325, 0x3C0300, 0x10101, 0x10001,
    0xC0101, 0x10001, 0x9D0101, 0x10001,
    0x3230101, 0x10326, 0x3240101, 0xC0326,
    0x1E0300, 1537, 0x17500EA, 0x10200,
    0x10003, 0x2000003, 0x40000, 0x2000C,
    0x3000301, 0x101001E, 0x10001, 0x1020003,
    0xD0000B, 0x40162, 0x9D0101, 0x30001,
    0x13D0102, 0x19000D0, 0x3020005, 0x101013D,
    0x1000B, 0x1020007, 0xD0013D, 0x60180,
    0x13D0302, 512, 0xB0005, 0x1010000,
    0x7000B, 0x3010007, 0xB0101, 0x70001,
    0x1E0300, 512, 0xB000C, 0x1010000,
    0x7000B, 0x1010006, 0x1009D, 0x3010005,
    0xB0101, 0x60001, 0x1E0300, 512,
    0xB0007, 0x1010000, 0x10001, 0x1010002,
    0x1000B, 0x3010000, 0x1E0300, 512,
    0x13D0006, 0x1010003, 0x1013D, 0x3010004,
    0x1E0300, 512, 0xC0008, 0x1010002,
    0x10001, 0x1010004, 0x7000C, 0x1010001,
    0x1009D, 0x3010004, 0xC0101, 0x10001,
    0x1E0300, 512, 0xC0009, 0x1010002,
    0x7000C, 0x3010000, 0xC0101, 1,
    0x1E0300, 512, 0x1000A, 0x1010003,
    0x70001, 0x1010003, 0x1000B, 0x1010007,
    0x1009D, 0x1010003, 0x1013D, 0x3010006,
    0x10101, 0x30001, 0x1E0300, 0x10102,
    0x1CC0058, 0x1010001, 0x1000B, 0x1010001,
    0x1000C, 0x1010001, 0x1009D, 0x1010001,
    0x1013D, 0x3000001, 0x3040078, 0x3E80270,
    0x100EC, 0,
};
AnimFrame D_800A56D8[] = {
    { 70, 4 }, { 71, 4 }, { 70, 4 }, { 71, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A56EC[] = {
    { 0x12C, 56 }, { 85, 6 }, { 86, 6 }, { 87, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 88, 4 },
    { 89, 4 }, { 90, 4 }, { 88, 4 }, { 89, 4 },
    { 90, 4 }, { 88, 4 }, { 89, 4 }, { 90, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A573C[] = {
    { 0x12C, 16 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 73, 4 }, { 75, 6 }, { 76, 6 }, { 77, 14 },
    { 78, 114 }, { 79, 6 }, { 80, 6 }, { 81, 6 },
    { 82, 6 }, { 83, 6 }, { 84, 8 }, { 255, 0x3E7 },
};
AnimFrame *D_800A577C[] = {
    D_800A56D8, D_800A573C, D_800A56EC,
};
s8 D_800A5788[] = {
    30, 30, 30, 0,
};
s8 D_800A578C[] = {
    0, -0x2F, -0x2F, 0,
};
s16 D_800A5790[][2] = {
    { 0x150, 0x112 }, { 112, 0x112 },
};
s32 D_800A5798[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1800160, 0x800080, 0x1FE0170,
    0x1000140, 0x1800168, 0x8000A0, 0x1FD0160,
    0x1000140, 0x1600160, 0x600080, 0x1FD0170,
    0x1000140, 0x1980152, 0x980048, 0x1FC0150,
    0x1000140, 0x198015A, 0x980068, 0x1FC0160,
    0x1000140, 0x1600168, 0x6000A0, 0x1FC0170,
    0x1000140, 0x190014A, 0x900028, 0x1FB0160,
    0x1000140, 0x170014A, 0x700028, 0x1FB0170,
};
s32 D_800A5878[] = {
    6666, 65535,
};
s32 D_800A5880[] = {
    0x11A0A, 65535,
};
s32 D_800A5888[] = {
    0, 65535,
};
s32 D_800A5890[] = {
    0x10000, 65535,
};
s32 D_800A5898[] = {
    0x10000, 65535,
};
s32 D_800A58A0[] = {
    6666, 65535,
};
s32 D_800A58A8[] = {
    0x11A0A, 65535,
};
s32 D_800A58B0[] = {
    (s32)D_800A5878, 0, 436, (s32)D_800A5880,
    0, 521, 0, 0,
    0,
};
s32 D_800A58D4[] = {
    0, 0, 91, 0,
    0, 0,
};
s32 D_800A58EC[] = {
    0, 0, 93, 0,
    0, 0,
};
s32 D_800A5904[] = {
    (s32)D_800A5888, (s32)D_800A5890, 513, (s32)D_800A5898,
    0, 514, 0, 0,
    0,
};
s32 D_800A5928[] = {
    0, 0, 90, 0,
    0, 0,
};
s32 D_800A5940[] = {
    0, 0, 92, 0,
    0, 0,
};
s32 D_800A5958[] = {
    (s32)D_800A58A0, 0, 506, (s32)D_800A58A8,
    0, 520, 0, 0,
    0,
};
s32 D_800A597C[] = {
    0, 0, 507, 0,
    0, 0,
};
s32 D_800A5994[] = {
    0x16025, 0x14060, 65535,
};
s32 D_800A59A0[] = {
    0x16025, 0x14060, 65535,
};
s32 D_800A59AC[] = {
    0x16025, 0x14060, 65535,
};
s32 D_800A59B8[] = {
    0x16026, 65535,
};
s32 D_800A59C0[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A59CC[] = {
    0x1882B, 0x1602B, 65535,
};
s32 D_800A59D8[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A59E4[] = {
    6666, 0x1701C, 65535,
};
s32 D_800A59F0[] = {
    0x1701A, 65535,
};
s32 D_800A59F8[] = {
    0x16026, 65535,
};
s32 D_800A5A00[] = {
    0x16026, 6666, 65535,
};
s32 D_800A5A0C[] = {
    0x16025, 0x14060, 65535,
};
s32 D_800A5A18[] = {
    (s32)D_800A5994, 0, 0x40001, 0,
    1,
};
s32 D_800A5A2C[] = {
    (s32)D_800A59A0, 0, 0x5000B, 0,
    1,
};
s32 D_800A5A40[] = {
    (s32)D_800A59AC, 0, 0x6000C, 0,
    1,
};
s32 D_800A5A54[] = {
    (s32)D_800A59B8, (s32)D_800A58B0, 0x6000C, 0x17800D0,
    7,
};
s32 D_800A5A68[] = {
    (s32)D_800A59C0, (s32)D_800A58D4, 0x70020, 0x18D0109,
    3,
};
s32 D_800A5A7C[] = {
    (s32)D_800A59CC, (s32)D_800A58EC, 0x70020, 0x18D0109,
    3,
};
s32 D_800A5A90[] = {
    (s32)D_800A59D8, (s32)D_800A5904, 0x80068, 0x16000FF,
    7,
};
s32 D_800A5AA4[] = {
    (s32)D_800A59E4, (s32)D_800A5928, 0x9009D, 0x18D0109,
    3,
};
s32 D_800A5AB8[] = {
    (s32)D_800A59F0, (s32)D_800A5940, 0x9009D, 0x18D0109,
    3,
};
s32 D_800A5ACC[] = {
    (s32)D_800A59F8, (s32)D_800A5958, 0xA00B2, 0x16B0115,
    3,
};
s32 D_800A5AE0[] = {
    (s32)D_800A5A00, (s32)D_800A597C, 0xB013D, 0x16000FF,
    7,
};
s32 D_800A5AF4[] = {
    (s32)D_800A5A0C, 0, 0xB013D, 0,
    1,
};
s32 D_800A5B08[] = {
    (s32)D_800A5A18, (s32)D_800A5A2C, (s32)D_800A5A40, (s32)D_800A5A54,
    (s32)D_800A5A68, (s32)D_800A5A7C, (s32)D_800A5A90, (s32)D_800A5AA4,
    (s32)D_800A5AB8, (s32)D_800A5ACC, (s32)D_800A5AE0, (s32)D_800A5AF4,
    0,
};
s32 D_800A5B3C[] = {
    0x6500100, 70, 0x1500000, 274,
    0x10000, 0x13F0640, 0x6423F, 0x1020074,
    0, 0x6400001, 0x423F013F, 0xE40006,
    282, 0x10000, 0x13F0640, 0x6423F,
    0x1020154, 0, 0x6400001, 0x423F013F,
    0x1630006, 346, 0x2000000, 0x480450,
    2, 0xE30150, 301, 0x4500300,
    85, 0x1500000, 0x12600E3, 0x10000,
    0x13B0440, 0x63E3B, 0x1120074, 300,
    0x4400001, 0x3E3B013B, 0xE40006, 0x144012A,
    0x10000, 0x13B0440, 0x63E3B, 0x1120154,
    300, 0x4400001, 0x3E3B013B, 0x1630006,
    0x184016A, 0, 0, 0,
    0, 0,
};
s32 D_800A5C14[] = {
    65535, 65535, 0x2730001, 0x17E02DA,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5C44[])(void) = {
    func_800A51F8,
};
s32 D_800A5C48[] = {
    935, (s32)D_800A5330,
#if VERSION_US
    0x10B0029,
#elif VERSION_EU
    0x1120029,
#endif
    0, (s32)func_800A51E8, -1, 0,
    0, 0, 0,
};
