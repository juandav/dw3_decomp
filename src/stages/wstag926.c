#include "common.h"
#include "stage.h"
extern void (*D_800A63F8[])(void);
void func_800A5F70();

void func_800A5DE0(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5E28(void *owner) {
    StageTask *task = createTask(func_800A5DE0, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A63F8[0]();
    return task;
}

extern s32 D_800A6218[];
extern s32 D_800A63C8[];
extern s32 D_800A60CC[];
extern s32 D_800A6208[];
extern s32 D_800A63FC[];
void func_800A5E84(void) {
    D_800990B4.unk44 = LANGUAGE + 0xFD;
    D_800990B4.unk8 = 0x1A0;
    D_800990B4.unkC = 0x8EB0000;
    D_800990B4.unk10 = D_800A6218;
    D_800990B4.unk14 = D_800A63C8;
    D_800990B4.unk1C = 0x8EA;
    D_800990B4.unk2C = (Vec2){0xDE00, 0xDE00};
    D_800990B4.unk28 = D_800A60CC;
    D_800990B4.unk3C = 5;
    D_800990B4.unk40 = 0x60140000;
    D_800990B4.unk4C = D_800A6208;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A63FC;
    D_8009A70C.setFile(0, 0x8EB0001);
    D_8009A70C.setFile(7, 0x8EB0002);
    D_8009A70C.unk50(0);
}

/* Shows the record with animation 1 and moves it and the player down a pixel a frame for 150 frames */
void func_800A5F70(StageTileTimer *task) {
    StageTile *rec;
    StageTile *tile;
    StageActor *player;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 1) {
                task->tile = rec;
                rec->unkC--;
                rec->visible = 1;
            }
        }
        task->timer = 0;
        break;
    case TASK_RUN:
        tile = task->tile;
        player = TASK_FUNCS.find(5, -1, 0);
        tile->unkC++;
        task->timer++;
        player->y += 0x100;
        if (task->timer >= 0x96) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A609C(s32 arg) {
    return createTaskWithId(func_800A5F70, 0x58, 0, arg);
}

void func_800A5E84();
extern s32 D_800A615C[];
extern s32 D_800A6164[];
extern s32 D_800A6170[];
extern s32 D_800A6178[];
extern s32 D_800A6184[];
extern s32 D_800A61B4[];
extern s32 D_800A61CC[];
extern s32 D_800A61E0[];
extern s32 D_800A61F4[];
extern s32 D_800A6424[];

s32 D_800A60CC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1480174, 0x4800D0, 0x1FF0170,
    0x1000140, 0x161015C, 0x610070, 0x1FE0160,
    0x1000140, 0x161016C, 0x6100B0, 0x1FE0170,
};
s32 D_800A615C[] = {
    28756, 65535,
};
s32 D_800A6164[] = {
    0x17054, 4108, 65535,
};
s32 D_800A6170[] = {
    0x1906F, 65535,
};
s32 D_800A6178[] = {
    0x17054, 0x1100C, 65535,
};
s32 D_800A6184[] = {
    (s32)D_800A615C, 0, 39, (s32)D_800A6164,
    (s32)D_800A6170, 40, (s32)D_800A6178, 0,
    41, 0, 0, 0,
};
s32 D_800A61B4[] = {
    0, 0, 42, 0,
    0, 0,
};
s32 D_800A61CC[] = {
    0, (s32)D_800A6184, 0x40020, 0x1580110,
    7,
};
s32 D_800A61E0[] = {
    0, 0, 0x50024, 0x14900F0,
    3,
};
s32 D_800A61F4[] = {
    0, (s32)D_800A61B4, 0x60175, 0xDA00CB,
    3,
};
s32 D_800A6208[] = {
    (s32)D_800A61CC, (s32)D_800A61E0, (s32)D_800A61F4, 0,
};
s32 D_800A6218[] = {
    0x2400001, 3, 0xC00000, 256,
    0x10000, 0x2320640, 0x40100, 0x680090,
    0, 0x6400001, 0x1000232, 0xA80004,
    92, 0x10000, 0x2320640, 0x40100,
    0x4000E0, 0, 0x6400001, 0xB000233,
    0x7F0008, 112, 0x10000, 0x2330640,
    0x80B00, 0x90007F, 0, 0x6400001,
    0xB000233, 0x9F0008, 96, 0x10000,
    0x2330640, 0x80B00, 0x80009F, 0,
    0x6400001, 0xB000233, 0xBF0008, 80,
    0x10000, 0x2330640, 0x80B00, 0x7000BF,
    0, 0x6400001, 0xB000233, 0xDF0008,
    64, 0x10000, 0x2330640, 0x80B00,
    0x6000DF, 0, 0x6400001, 0xB000234,
    0xC40008, 289, 0x10000, 0x2340640,
    0x80B00, 0x11200E2, 0, 0x6400001,
    0xB000235, 0xD40008, 266, 0x10000,
    0x2350640, 0x80B00, 0x11900D4, 0,
    0x6400001, 0xB000236, 0xC40008, 275,
    0x10000, 0x2360640, 0x80B00, 0x10400E2,
    0, 0x6400001, 0x39370137, 0xC8000A,
    290, 0x1010000, 0x20640, 0,
    0x1500100, 0, 0x4400001, 0x3C3A013A,
    0x100000A, 0x13B011E, 0x10000, 1088,
    0, 0x1380130, 329, 0x4400001,
    1, 0x1000000, 0x13B0118, 0,
    0, 0, 0, 0,
};
s32 D_800A63C8[] = {
    65535, 65535, 0x2730001, 0x11C0200,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A63F8[])(void) = {
    func_800A5E84,
};
s32 D_800A63FC[] = {
    1606, (s32)D_800A6424, 0x1580003, 0,
    0, -1, 0, 0,
    0, 0,
};
s32 D_800A6424[] = {
    0x20102, 0x168012F, 0x1010003, 0x10020,
    0x1010007, 0x337032D, 0x3020002, 0x1010002,
    0x10002, 0x3000003, 0x200001E, 0x10000,
    32, 0x3000301, 0x200001E, 0x20000,
    0x20002, 0x20101, 0x30007, 0x1010301,
    0x10002, 0x3000003, 0x200001E, 0x30000,
    32, 0x3000301, 0x101001E, 0x3250323,
    0x3000002, 0x101005A, 0x3260323, 0x3000002,
    0x200001E, 0x40000, 0x20002, 0x20101,
    0x30007, 0x1010301, 0x10002, 0x3000003,
    0x101001E, 0x10002, 0x3000000, 0x101003C,
    0x3490356, 0x3000002, 0x3040030, 0xC00278,
    0x50158,
};
