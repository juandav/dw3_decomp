#include "common.h"
#include "stage.h"
void func_800A4CA4();
extern void (*D_800A5A08[])(void);
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

/* Ends the task when map object 0x35A is triggered */
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
        if (FLAGS_00.checkCondition(0x4008, 1) && FLAGS_00.checkCondition(0x4009, 0)) {
            children[1] = func_80084B80(0x178);
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
    D_800A5A08[0]();
    return task;
}

void func_800A4F88(void) {
    FLAGS_00.applyAction(0x4008, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4FD4(void) {
    FLAGS_00.applyAction(0x4009, 1);
    FLAGS_00.applyAction(0x8674, 1);
}

void func_800A5020(void) {
    GAME_PROGRESS = 22;
}

extern s32 D_800A584C[];
extern s32 D_800A59D8[];
extern s32 D_800A5528[];
extern s32 D_800A5820[];
extern s32 D_800A5A0C[];
extern s32 D_800A550C[];
#if VERSION_US
#define STAGE_TEXT 0xF0
#define STAGE_FILE 0x755
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE8)
#define STAGE_FILE 0x765
#endif
void func_800A5030(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A584C;
    D_800990B4.unk14 = D_800A59D8;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xF500, 0x17A00};
    D_800990B4.unk28 = D_800A5528;
    D_800990B4.unk3C = 0x2B;
    D_800990B4.unk40 = 0x60AC0000;
    D_800990B4.unk4C = D_800A5820;
    D_800990B4.events = D_800A5A0C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A550C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A5030();
extern s32 D_800A52FC[];
extern s32 D_800A5308[];
extern s32 D_800A5314[];
extern s32 D_800A5320[];
extern s32 D_800A532C[];
extern s32 D_800A5338[];
extern s32 D_800A5344[];
extern s32 D_800A5350[];
extern s32 D_800A5380[];
extern s32 D_800A538C[];
extern s32 D_800A5398[];
extern s32 D_800A53A4[];
extern s32 D_800A53B0[];
extern s32 D_800A53BC[];
extern s32 D_800A53C8[];
extern s32 D_800A53D4[];
extern s32 D_800A5404[];
extern s32 D_800A5410[];
extern s32 D_800A541C[];
extern s32 D_800A5428[];
extern s32 D_800A5434[];
extern s32 D_800A5440[];
extern s32 D_800A544C[];
extern s32 D_800A5458[];
extern s32 D_800A5488[];
extern s32 D_800A5494[];
extern s32 D_800A54A0[];
extern s32 D_800A54AC[];
extern s32 D_800A54B8[];
extern s32 D_800A54C4[];
extern s32 D_800A54D0[];
extern s32 D_800A54DC[];
extern s32 D_800A535C[];
extern s32 D_800A53E0[];
extern s32 D_800A5464[];
extern s32 D_800A54E8[];
extern s32 D_800A5598[];
extern s32 D_800A55A4[];
extern s32 D_800A55AC[];
extern s32 D_800A55B4[];
extern s32 D_800A55BC[];
extern s32 D_800A55C4[];
extern s32 D_800A55CC[];
extern s32 D_800A56E4[];
extern s32 D_800A55DC[];
extern s32 D_800A56F0[];
extern s32 D_800A55F4[];
extern s32 D_800A56F8[];
extern s32 D_800A560C[];
extern s32 D_800A5704[];
extern s32 D_800A5624[];
extern s32 D_800A5710[];
extern s32 D_800A5648[];
extern s32 D_800A571C[];
extern s32 D_800A566C[];
extern s32 D_800A5728[];
extern s32 D_800A5684[];
extern s32 D_800A5734[];
extern s32 D_800A569C[];
extern s32 D_800A5740[];
extern s32 D_800A56B4[];
extern s32 D_800A574C[];
extern s32 D_800A56CC[];
extern s32 D_800A5758[];
extern s32 D_800A576C[];
extern s32 D_800A5780[];
extern s32 D_800A5794[];
extern s32 D_800A57A8[];
extern s32 D_800A57BC[];
extern s32 D_800A57D0[];
extern s32 D_800A57E4[];
extern s32 D_800A57F8[];
extern s32 D_800A580C[];
extern s32 D_800A5128[];
extern s32 D_800A51D0[];
extern s32 D_800A5260[];

s32 D_800A5128[] = {
    0x20102, 0x1140191, 0x1000005, 0x1B100A5,
    0x1010104, 0x100A5, 0x1010001, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000005,
    0x200001E, 0x20000, 0x200A5, 0x3000301,
    0x200001E, 0x30000, 0x10002, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x1010005,
    0x3250323, 0x30000A5, 0x101003C, 0x3260323,
    0x3000002, 0x200001E, 0x40000, 0x200A5,
    0x3000301, 0x200001E, 0x50000, 0x10002,
    0x20101, 0x50007, 0x1010301, 0x10002,
    0x3000005, 30,
};
s32 D_800A51D0[] = {
    0x20100, 0x1140191, 0x20101, 0x50001,
    0xA50100, 0x10401B1, 0xA50101, 0x10001,
    0x780300, 512, 0xA50001, 0x3010002,
    0x32D0101, 0x2034A, 0x1E0300, 512,
    0x20002, 0x1010001, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0xA50003, 0x3010002, 0x1E0300, 512,
    0x20004, 0x1010001, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 0,
};
s32 D_800A5260[] = {
    0x20102, 0x1140191, 0x1000005, 0x1B100A5,
    0x1010104, 0x100A5, 0x1010001, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x1010005,
    0x3250323, 0x30000A5, 0x101003C, 0x3260323,
    0x30000A5, 0x200001E, 0x10000, 0x200A5,
    0x3000301, 0x200001E, 0x20000, 0x10002,
    0x20101, 0x50007, 0x1010301, 0x10002,
    0x3000005, 0x1010018, 0x10002, 0x3000001,
    0x1020018, 0x1540002, 0x10132, 0xC0300,
    0x21B0304, 0x2DC03F8, 1,
};
s32 D_800A52FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5308[] = {
    0, 0, 0x60040000,
};
s32 D_800A5314[] = {
    0, 0, 0x60040000,
};
s32 D_800A5320[] = {
    0, 0, 0x60040000,
};
s32 D_800A532C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5338[] = {
    0, 0, 0x60040000,
};
s32 D_800A5344[] = {
    0, 0, 0x60040000,
};
s32 D_800A5350[] = {
    0, 0, 0x60040000,
};
s32 D_800A535C[] = {
    0, (s32)D_800A52FC, (s32)D_800A5308, (s32)D_800A5314,
    (s32)D_800A5320, (s32)D_800A532C, (s32)D_800A5338, (s32)D_800A5344,
    (s32)D_800A5350,
};
s32 D_800A5380[] = {
    0, 0, 0x60040000,
};
s32 D_800A538C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5398[] = {
    0, 0, 0x60040000,
};
s32 D_800A53A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A53B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A53E0[] = {
    0, (s32)D_800A5380, (s32)D_800A538C, (s32)D_800A5398,
    (s32)D_800A53A4, (s32)D_800A53B0, (s32)D_800A53BC, (s32)D_800A53C8,
    (s32)D_800A53D4,
};
s32 D_800A5404[] = {
    0, 0, 0x60040000,
};
s32 D_800A5410[] = {
    0, 0, 0x60040000,
};
s32 D_800A541C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5428[] = {
    0, 0, 0x60040000,
};
s32 D_800A5434[] = {
    0, 0, 0x60040000,
};
s32 D_800A5440[] = {
    0, 0, 0x60040000,
};
s32 D_800A544C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5458[] = {
    0, 0, 0x60040000,
};
s32 D_800A5464[] = {
    0, (s32)D_800A5404, (s32)D_800A5410, (s32)D_800A541C,
    (s32)D_800A5428, (s32)D_800A5434, (s32)D_800A5440, (s32)D_800A544C,
    (s32)D_800A5458,
};
s32 D_800A5488[] = {
    9, 19, 0x60880000,
};
s32 D_800A5494[] = {
    313, 19, 0x60880000,
};
s32 D_800A54A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A54B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A54C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A54D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A54E8[] = {
    0, (s32)D_800A5488, (s32)D_800A5494, (s32)D_800A54A0,
    (s32)D_800A54AC, (s32)D_800A54B8, (s32)D_800A54C4, (s32)D_800A54D0,
    (s32)D_800A54DC,
};
s32 D_800A550C[] = {
    127, 0, 0, (s32)D_800A535C,
    (s32)D_800A53E0, (s32)D_800A5464, (s32)D_800A54E8,
};
s32 D_800A5528[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000168, 160, 0x1EE0140,
};
s32 D_800A5598[] = {
    0x19041, 0x10A03, 65535,
};
s32 D_800A55A4[] = {
    7195, 65535,
};
s32 D_800A55AC[] = {
    0x11C1B, 65535,
};
s32 D_800A55B4[] = {
    0x11C1B, 65535,
};
s32 D_800A55BC[] = {
    33169, 65535,
};
s32 D_800A55C4[] = {
    0x18191, 65535,
};
s32 D_800A55CC[] = {
    0x19024, 0x11C1D, 0x14005, 65535,
};
s32 D_800A55DC[] = {
    0, 0, 1175, 0,
    0, 0,
};
s32 D_800A55F4[] = {
    0, (s32)D_800A5598, 179, 0,
    0, 0,
};
s32 D_800A560C[] = {
    0, 0, 1046, 0,
    0, 0,
};
s32 D_800A5624[] = {
    (s32)D_800A55A4, (s32)D_800A55AC, 1176, (s32)D_800A55B4,
    0, 1177, 0, 0,
    0,
};
s32 D_800A5648[] = {
    (s32)D_800A55BC, 0, 1040, (s32)D_800A55C4,
    (s32)D_800A55CC, 180, 0, 0,
    0,
};
s32 D_800A566C[] = {
    0, 0, 1041, 0,
    0, 0,
};
s32 D_800A5684[] = {
    0, 0, 1042, 0,
    0, 0,
};
s32 D_800A569C[] = {
    0, 0, 1043, 0,
    0, 0,
};
s32 D_800A56B4[] = {
    0, 0, 1044, 0,
    0, 0,
};
s32 D_800A56CC[] = {
    0, 0, 1045, 0,
    0, 0,
};
s32 D_800A56E4[] = {
    0x17016, 0x10A03, 65535,
};
s32 D_800A56F0[] = {
    2563, 65535,
};
s32 D_800A56F8[] = {
    0x1602B, 0x10A03, 65535,
};
s32 D_800A5704[] = {
    0x10A03, 0x16014, 65535,
};
s32 D_800A5710[] = {
    0x16015, 0x10A03, 65535,
};
s32 D_800A571C[] = {
    0x10A03, 0x16016, 65535,
};
s32 D_800A5728[] = {
    0x17018, 0x10A03, 65535,
};
s32 D_800A5734[] = {
    0x10A03, 0x17019, 65535,
};
s32 D_800A5740[] = {
    0x16026, 0x10A03, 65535,
};
s32 D_800A574C[] = {
    0x10A03, 0x1701A, 65535,
};
s32 D_800A5758[] = {
    (s32)D_800A56E4, (s32)D_800A55DC, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A576C[] = {
    (s32)D_800A56F0, (s32)D_800A55F4, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A5780[] = {
    (s32)D_800A56F8, (s32)D_800A560C, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A5794[] = {
    (s32)D_800A5704, (s32)D_800A5624, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A57A8[] = {
    (s32)D_800A5710, (s32)D_800A5648, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A57BC[] = {
    (s32)D_800A571C, (s32)D_800A566C, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A57D0[] = {
    (s32)D_800A5728, (s32)D_800A5684, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A57E4[] = {
    (s32)D_800A5734, (s32)D_800A569C, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A57F8[] = {
    (s32)D_800A5740, (s32)D_800A56B4, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A580C[] = {
    (s32)D_800A574C, (s32)D_800A56CC, 0x400A5, 0x10401B1,
    5,
};
s32 D_800A5820[] = {
    (s32)D_800A5758, (s32)D_800A576C, (s32)D_800A5780, (s32)D_800A5794,
    (s32)D_800A57A8, (s32)D_800A57BC, (s32)D_800A57D0, (s32)D_800A57E4,
    (s32)D_800A57F8, (s32)D_800A580C, 0,
};
s32 D_800A584C[] = {
    0x2400001, 0x3000236, 0x1760004, 301,
    0x10000, 0x2360240, 0x40300, 0x1250186,
    0, 0x2400001, 0x3000236, 0x1960004,
    285, 0x10000, 0x2360240, 0x40300,
    0x11501A6, 0, 0x2400001, 0x3000236,
    0x1CA0004, 262, 0x10000, 0x1000649,
    0x40300, 0xC10054, 0, 0x65D0001,
    0x7040104, 0x440004, 252, 0x10000,
    0x105065D, 0x40805, 0xE30083, 0,
    0x65D0001, 0xE0B010B, 0xB60004, 153,
    0x10000, 0x1000649, 0x40300, 0xB200E3,
    0, 0x65D0001, 0xA070107, 0x1100004,
    108, 0x1010000, 0x2320640, 0x100200,
    0xDC01B6, 0, 0x6400301, 0x1000233,
    0x1B60010, 220, 0x2010000, 0x2340640,
    0x40300, 0xCA01BC, 0, 0x6400401,
    0x3000235, 0x1BC0004, 202, 0x10000,
    0x2360640, 0x40300, 0x1050126, 0,
    0x6400001, 0x3000236, 0x1360004, 253,
    0x10000, 0x2360640, 0x40300, 0xF50146,
    0, 0x6400001, 0x3000236, 0x1560004,
    237, 0x10000, 0x2360640, 0x40300,
    0xDC0176, 0, 0x6400001, 15,
    0x1C00000, 207, 0, 0,
    0, 0, 0,
};
s32 D_800A59D8[] = {
    65535, 65535, 0x21B0001, 0x2DC03F8,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5A08[])(void) = {
    func_800A5030,
};
s32 D_800A5A0C[] = {
    375, (s32)D_800A5128,
#if VERSION_US
    0x1200004,
#elif VERSION_EU
    0x1270004,
#endif
    0, (s32)func_800A4F88, 376, (s32)D_800A51D0,
#if VERSION_US
    0x1200005,
#elif VERSION_EU
    0x1270005,
#endif
    0, (s32)func_800A4FD4, 560, (s32)D_800A5260,
#if VERSION_US
    0x1200006,
#elif VERSION_EU
    0x1270006,
#endif
    0, (s32)func_800A5020, -1, 0,
    0, 0, 0,
};
