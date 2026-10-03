#include "common.h"
#include "stage.h"
void func_800A4CA4();
extern void (*D_800A57B0[])(void);
void func_800A4E8C();

void func_800A4CA4(StageTask *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            switch (tile->anim) {
            case 1:
                tile->visible = 1;
                break;
            case 2:
                tile->visible = 1;
                break;
            case 3:
                tile->visible = 0;
                break;
            case 4:
                tile->visible = 0;
                break;
            }
        }
        break;
    case TASK_DONE:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            switch (tile->anim) {
            case 1:
                tile->visible = 0;
                break;
            case 2:
                tile->visible = 0;
                break;
            case 3:
                tile->visible = 1;
                break;
            case 4:
                tile->visible = 1;
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

void *func_800A4E24(s32 arg) {
    return createTaskWithId(func_800A4CA4, 0x50, 0, arg);
}

void func_800A4E54(StageTask *task, s32 id) {
    if (task != NULL && id == 0x35A) {
        task->setState(task, TASK_DONE);
    }
}

void func_800A4E8C(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4076, 1) && FLAGS_00.checkCondition(0x4077, 0)) {
            children[1] = func_80084B80(0x502);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4F2C(void *owner) {
    StageTask *task = createTask(func_800A4E8C, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A57B0[0]();
    return task;
}

void func_800A4F88(void) {
    FLAGS_00.applyAction(0x4076, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4FD4(void) {
    FLAGS_00.applyAction(0x4077, 1);
    FLAGS_00.applyAction(0x802A, 1);
}

extern s32 D_800A5660[];
extern s32 D_800A5780[];
extern s32 D_800A5488[];
extern s32 D_800A5650[];
extern s32 D_800A57B4[];
extern s32 D_800A546C[];
#if VERSION_US
#define STAGE_TEXT 0xE2
#define STAGE_FILE 0x52A
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xDA)
#define STAGE_FILE 0x53A
#endif
void func_800A5020(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5660;
    D_800990B4.unk14 = D_800A5780;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xF300, 0x17A00};
    D_800990B4.unk28 = D_800A5488;
    D_800990B4.unk3C = 0x2B;
    D_800990B4.unk40 = 0x60AC0000;
    D_800990B4.unk4C = D_800A5650;
    D_800990B4.events = D_800A57B4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A546C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A5020();
extern s32 D_800A525C[];
extern s32 D_800A5268[];
extern s32 D_800A5274[];
extern s32 D_800A5280[];
extern s32 D_800A528C[];
extern s32 D_800A5298[];
extern s32 D_800A52A4[];
extern s32 D_800A52B0[];
extern s32 D_800A52E0[];
extern s32 D_800A52EC[];
extern s32 D_800A52F8[];
extern s32 D_800A5304[];
extern s32 D_800A5310[];
extern s32 D_800A531C[];
extern s32 D_800A5328[];
extern s32 D_800A5334[];
extern s32 D_800A5364[];
extern s32 D_800A5370[];
extern s32 D_800A537C[];
extern s32 D_800A5388[];
extern s32 D_800A5394[];
extern s32 D_800A53A0[];
extern s32 D_800A53AC[];
extern s32 D_800A53B8[];
extern s32 D_800A53E8[];
extern s32 D_800A53F4[];
extern s32 D_800A5400[];
extern s32 D_800A540C[];
extern s32 D_800A5418[];
extern s32 D_800A5424[];
extern s32 D_800A5430[];
extern s32 D_800A543C[];
extern s32 D_800A52BC[];
extern s32 D_800A5340[];
extern s32 D_800A53C4[];
extern s32 D_800A5448[];
extern s32 D_800A54F8[];
extern s32 D_800A5504[];
extern s32 D_800A5510[];
extern s32 D_800A551C[];
extern s32 D_800A5528[];
extern s32 D_800A5534[];
extern s32 D_800A5540[];
extern s32 D_800A5548[];
extern s32 D_800A5554[];
extern s32 D_800A555C[];
extern s32 D_800A5564[];
extern s32 D_800A5570[];
extern s32 D_800A55FC[];
extern s32 D_800A5578[];
extern s32 D_800A5604[];
extern s32 D_800A55B4[];
extern s32 D_800A560C[];
extern s32 D_800A55D8[];
extern s32 D_800A5614[];
extern s32 D_800A5628[];
extern s32 D_800A563C[];
extern s32 D_800A5118[];
extern s32 D_800A51B8[];

s32 D_800A5118[] = {
    0x10600, 0x1020002, 0x18D0002, 0x5010E,
    0x1050100, 0x10001A9, 0x1050101, 0x10001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x50001, 0x60300, 0x1E0300, 512,
    0x20001, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0x1050002, 0x3010000, 0x1E0300, 512,
    0x20003, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0x1050004, 0x3010000, 0x1E0300,
#if VERSION_US
    0,
#elif VERSION_EU
    0x60040000,
#endif
};
s32 D_800A51B8[] = {
    0x10600, 0x1000002, 0x18D0002, 0x101010E,
    0x10002, 0x1000005, 0x1A90105, 0x1010100,
    0x10105, 0x3000001, 0x2000078, 0x10000,
    261, 0x3000301, 0x200001E, 0x20000,
    0x30002, 0x20101, 0x50007, 0x1010301,
    0x10002, 0x3000005, 0x200001E, 0x30000,
    261, 0x1010301, 0x34A032D, 0x3000002,
    0x200001E, 0x40000, 0x30002, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x200001E, 0x50000, 261, 0x3000301,
    60,
};
s32 D_800A525C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5268[] = {
    0, 0, 0x60040000,
};
s32 D_800A5274[] = {
    0, 0, 0x60040000,
};
s32 D_800A5280[] = {
    0, 0, 0x60040000,
};
s32 D_800A528C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5298[] = {
    0, 0, 0x60040000,
};
s32 D_800A52A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52BC[] = {
    0, (s32)D_800A525C, (s32)D_800A5268, (s32)D_800A5274,
    (s32)D_800A5280, (s32)D_800A528C, (s32)D_800A5298, (s32)D_800A52A4,
    (s32)D_800A52B0,
};
s32 D_800A52E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5304[] = {
    0, 0, 0x60040000,
};
s32 D_800A5310[] = {
    0, 0, 0x60040000,
};
s32 D_800A531C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5328[] = {
    0, 0, 0x60040000,
};
s32 D_800A5334[] = {
    0, 0, 0x60040000,
};
s32 D_800A5340[] = {
    0, (s32)D_800A52E0, (s32)D_800A52EC, (s32)D_800A52F8,
    (s32)D_800A5304, (s32)D_800A5310, (s32)D_800A531C, (s32)D_800A5328,
    (s32)D_800A5334,
};
s32 D_800A5364[] = {
    0, 0, 0x60040000,
};
s32 D_800A5370[] = {
    0, 0, 0x60040000,
};
s32 D_800A537C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5388[] = {
    0, 0, 0x60040000,
};
s32 D_800A5394[] = {
    0, 0, 0x60040000,
};
s32 D_800A53A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53C4[] = {
    0, (s32)D_800A5364, (s32)D_800A5370, (s32)D_800A537C,
    (s32)D_800A5388, (s32)D_800A5394, (s32)D_800A53A0, (s32)D_800A53AC,
    (s32)D_800A53B8,
};
s32 D_800A53E8[] = {
    31, 19, 0x60880000,
};
s32 D_800A53F4[] = {
    321, 19, 0x60880000,
};
s32 D_800A5400[] = {
    0, 0, 0x60040000,
};
s32 D_800A540C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5418[] = {
    0, 0, 0x60040000,
};
s32 D_800A5424[] = {
    0, 0, 0x60040000,
};
s32 D_800A5430[] = {
    0, 0, 0x60040000,
};
s32 D_800A543C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5448[] = {
    0, (s32)D_800A53E8, (s32)D_800A53F4, (s32)D_800A5400,
    (s32)D_800A540C, (s32)D_800A5418, (s32)D_800A5424, (s32)D_800A5430,
    (s32)D_800A543C,
};
s32 D_800A546C[] = {
    129, 0, 0, (s32)D_800A52BC,
    (s32)D_800A5340, (s32)D_800A53C4, (s32)D_800A5448,
};
s32 D_800A5488[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000140, 0, 0x1FB0140,
};
s32 D_800A54F8[] = {
    0x16025, 2573, 65535,
};
s32 D_800A5504[] = {
    0x10A0D, 0x19038, 65535,
};
s32 D_800A5510[] = {
    0x10A0D, 0x16025, 65535,
};
s32 D_800A551C[] = {
    0x16026, 2573, 65535,
};
s32 D_800A5528[] = {
    0x10A0D, 0x19038, 65535,
};
s32 D_800A5534[] = {
    0x10A0D, 0x16026, 65535,
};
s32 D_800A5540[] = {
    2573, 65535,
};
s32 D_800A5548[] = {
    0x10A0D, 0x19038, 65535,
};
s32 D_800A5554[] = {
    0x10A0D, 65535,
};
s32 D_800A555C[] = {
    2573, 65535,
};
s32 D_800A5564[] = {
    0x10A0D, 0x19038, 65535,
};
s32 D_800A5570[] = {
    0x10A0D, 65535,
};
s32 D_800A5578[] = {
    (s32)D_800A54F8, (s32)D_800A5504, 427, (s32)D_800A5510,
    0, 177, (s32)D_800A551C, (s32)D_800A5528,
    427, (s32)D_800A5534, 0, 178,
    0, 0, 0,
};
s32 D_800A55B4[] = {
    (s32)D_800A5540, (s32)D_800A5548, 427, (s32)D_800A5554,
    0, 179, 0, 0,
    0,
};
s32 D_800A55D8[] = {
    (s32)D_800A555C, (s32)D_800A5564, 427, (s32)D_800A5570,
    0, 180, 0, 0,
    0,
};
s32 D_800A55FC[] = {
    0x1701C, 65535,
};
s32 D_800A5604[] = {
    0x1701A, 65535,
};
s32 D_800A560C[] = {
    0x1602B, 65535,
};
s32 D_800A5614[] = {
    (s32)D_800A55FC, (s32)D_800A5578, 0x40105, 0x10001A9,
    1,
};
s32 D_800A5628[] = {
    (s32)D_800A5604, (s32)D_800A55B4, 0x40105, 0x10001A9,
    1,
};
s32 D_800A563C[] = {
    (s32)D_800A560C, (s32)D_800A55D8, 0x40105, 0x10001A9,
    1,
};
s32 D_800A5650[] = {
    (s32)D_800A5614, (s32)D_800A5628, (s32)D_800A563C, 0,
};
s32 D_800A5660[] = {
    0x2400001, 0x3000236, 0x1760004, 301,
    0x10000, 0x2360240, 0x40300, 0x1250186,
    0, 0x2400001, 0x3000236, 0x1960004,
    285, 0x10000, 0x2360240, 0x40300,
    0x11501A6, 0, 0x2400001, 0x3000236,
    0x1CA0004, 262, 0x1010000, 0x2320640,
    0x100200, 0xDC01B6, 0, 0x6400301,
    0x1000233, 0x1B60010, 220, 0x4010000,
    0x2350640, 0x40300, 0xCA01BC, 0,
    0x6400201, 0x3000234, 0x1BC0004, 202,
    0x10000, 0x2360640, 0x40300, 0x1050126,
    0, 0x6400001, 0x3000236, 0x1360004,
    253, 0x10000, 0x2360640, 0x40300,
    0xF50146, 0, 0x6400001, 0x3000236,
    0x1560004, 237, 0x10000, 0x2360640,
    0x40300, 0xDC0176, 0, 0x6400001,
    12, 0x1C00000, 207, 0,
    0, 0, 0, 0,
};
s32 D_800A5780[] = {
    65535, 65535, 0x28A0001, 0x2DC03F8,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A57B0[])(void) = {
    func_800A5020,
};
s32 D_800A57B4[] = {
    1281, (s32)D_800A5118,
#if VERSION_US
    0x1200020,
#elif VERSION_EU
    0x1270020,
#endif
    0, (s32)func_800A4F88, 1282, (s32)D_800A51B8,
#if VERSION_US
    0x1200021,
#elif VERSION_EU
    0x1270021,
#endif
    0, (s32)func_800A4FD4, -1, 0,
    0, 0, 0,
};
