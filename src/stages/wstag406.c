#include "common.h"
#include "stage.h"
extern s32 D_800A595C[];
extern s32 D_800A5530[];
extern s32 D_800A5788[];
extern u8 D_800A554C[];
extern u8 D_800A5820[];
extern u8 D_800A57A0[];
void func_800A4D98();
extern void (*D_800A5958[])(void);
void func_800A4E98();
void func_800A503C();
extern AnimFrame D_800A5294[];

s32 func_800A4CA4(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A4CA4(anim, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A4D98(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A5294[0].duration;
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = func_800A4CA4(&task->anims[0], D_800A5294, 0);
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A4E6C(void) {
    return createTask(func_800A4D98, 0x54, 0);
}

/* Creates the stage helper task, and the event object when flag 0x407A is set and 0x407B is not */
void func_800A4E98(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4E6C();
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x407A, 1) && FLAGS_00.checkCondition(0x407B, 0)) {
            children[1] = func_80084B80(0x506);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4F48(void *owner) {
    StageTask *task = createTask(func_800A4E98, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5958[0]();
    return task;
}

void func_800A4FA4(void) {
    FLAGS_00.applyAction(0x407A, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4FF0(void) {
    FLAGS_00.applyAction(0x407B, 1);
    FLAGS_00.applyAction(0x8AF5, 1);
}

#if VERSION_US
void func_800A503C(void) {
    D_800990B4.unk44 = 0xE9;
    D_800990B4.unk8 = 0x733;
    D_800990B4.unkC = 0x7340000;
    D_800990B4.unk10 = D_800A57A0;
    D_800990B4.unk14 = D_800A5820;
    D_800990B4.unk1C = 0x732;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x17A00;
    D_800990B4.unk30 = 0x44500;
    D_800990B4.unk28 = D_800A554C;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A5788;
    D_800990B4.unk20 = D_800A5530;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A595C;
    D_8009A70C.setFile(0, 0x7340001);
    D_8009A70C.setFile(7, 0x7340002);
    D_8009A70C.setFile(4, 0x7340003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag406", func_800A503C);
#endif

extern s32 D_800A5320[];
extern s32 D_800A532C[];
extern s32 D_800A5338[];
extern s32 D_800A5344[];
extern s32 D_800A5350[];
extern s32 D_800A535C[];
extern s32 D_800A5368[];
extern s32 D_800A5374[];
extern s32 D_800A53A4[];
extern s32 D_800A53B0[];
extern s32 D_800A53BC[];
extern s32 D_800A53C8[];
extern s32 D_800A53D4[];
extern s32 D_800A53E0[];
extern s32 D_800A53EC[];
extern s32 D_800A53F8[];
extern s32 D_800A5428[];
extern s32 D_800A5434[];
extern s32 D_800A5440[];
extern s32 D_800A544C[];
extern s32 D_800A5458[];
extern s32 D_800A5464[];
extern s32 D_800A5470[];
extern s32 D_800A547C[];
extern s32 D_800A54AC[];
extern s32 D_800A54B8[];
extern s32 D_800A54C4[];
extern s32 D_800A54D0[];
extern s32 D_800A54DC[];
extern s32 D_800A54E8[];
extern s32 D_800A54F4[];
extern s32 D_800A5500[];
extern s32 D_800A5380[];
extern s32 D_800A5404[];
extern s32 D_800A5488[];
extern s32 D_800A550C[];
extern s32 D_800A55BC[];
extern s32 D_800A55C4[];
extern s32 D_800A55D0[];
extern s32 D_800A55D8[];
extern s32 D_800A55E0[];
extern s32 D_800A55EC[];
extern s32 D_800A55F4[];
extern s32 D_800A55FC[];
extern s32 D_800A5608[];
extern s32 D_800A5610[];
extern s32 D_800A5618[];
extern s32 D_800A5624[];
extern s32 D_800A562C[];
extern s32 D_800A5634[];
extern s32 D_800A5640[];
extern s32 D_800A56FC[];
extern s32 D_800A5648[];
extern s32 D_800A5704[];
extern s32 D_800A566C[];
extern s32 D_800A570C[];
extern s32 D_800A5690[];
extern s32 D_800A5714[];
extern s32 D_800A56B4[];
extern s32 D_800A571C[];
extern s32 D_800A56D8[];
extern s32 D_800A5724[];
extern s32 D_800A5738[];
extern s32 D_800A574C[];
extern s32 D_800A5760[];
extern s32 D_800A5774[];
extern s32 D_800A5150[];
extern s32 D_800A51F0[];

s32 D_800A5150[] = {
    0x10600, 0x1020002, 0x37B0002, 0x50153,
    0x1080100, 0x13D039B, 0x1080101, 0x10001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x50001, 0x60300, 0x1E0300, 512,
    0x20001, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0x1080002, 0x3010000, 0x1E0300, 512,
    0x20003, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0x1080004, 0x3010000, 0x1E0300,
#if VERSION_US
    0x800A0000,
#elif VERSION_EU
    0x20000,
#endif
};
s32 D_800A51F0[] = {
    0x10600, 0x1000002, 0x37B0002, 0x1010153,
    0x10002, 0x1000005, 0x39B0108, 0x101013D,
    0x10108, 0x3000001, 0x2000078, 0x10000,
    264, 0x3000301, 0x200001E, 0x20000,
    0x30002, 0x20101, 0x50007, 0x1010301,
    0x10002, 0x3000005, 0x200001E, 0x30000,
    264, 0x1010301, 0x34A032D, 0x3000002,
    0x200001E, 0x40000, 0x30002, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x200001E, 0x50000, 264, 0x3000301,
    60,
};
AnimFrame D_800A5294[] = {
    { 50, 8 }, { 51, 4 }, { 52, 8 }, { 53, 4 },
    { 54, 8 }, { 55, 4 }, { 56, 8 }, { 57, 16 },
    { 58, 4 }, { 59, 8 }, { 60, 4 }, { 61, 8 },
    { 62, 8 }, { 63, 12 }, { 64, 20 }, { 65, 4 },
    { 66, 8 }, { 67, 4 }, { 68, 8 }, { 69, 8 },
    { 70, 8 }, { 71, 8 }, { 72, 8 }, { 73, 4 },
    { 74, 8 }, { 75, 4 }, { 76, 8 }, { 77, 8 },
    { 78, 8 }, { 79, 8 }, { 80, 8 }, { 81, 12 },
    { 82, 8 }, { 83, 30 }, { 255, 0 },
};
s32 D_800A5320[] = {
    100, 4, 0x60080000,
};
s32 D_800A532C[] = {
    100, 4, 0x60080000,
};
s32 D_800A5338[] = {
    100, 4, 0x60080000,
};
s32 D_800A5344[] = {
    100, 4, 0x60080000,
};
s32 D_800A5350[] = {
    101, 4, 0x60080000,
};
s32 D_800A535C[] = {
    101, 4, 0x60080000,
};
s32 D_800A5368[] = {
    101, 4, 0x60080000,
};
s32 D_800A5374[] = {
    101, 4, 0x60080000,
};
s32 D_800A5380[] = {
    3, (s32)D_800A5320, (s32)D_800A532C, (s32)D_800A5338,
    (s32)D_800A5344, (s32)D_800A5350, (s32)D_800A535C, (s32)D_800A5368,
    (s32)D_800A5374,
};
s32 D_800A53A4[] = {
    101, 4, 0x60080000,
};
s32 D_800A53B0[] = {
    101, 4, 0x60080000,
};
s32 D_800A53BC[] = {
    101, 4, 0x60080000,
};
s32 D_800A53C8[] = {
    101, 4, 0x60080000,
};
s32 D_800A53D4[] = {
    101, 4, 0x60080000,
};
s32 D_800A53E0[] = {
    101, 4, 0x60080000,
};
s32 D_800A53EC[] = {
    101, 4, 0x60080000,
};
s32 D_800A53F8[] = {
    101, 4, 0x60080000,
};
s32 D_800A5404[] = {
    5, (s32)D_800A53A4, (s32)D_800A53B0, (s32)D_800A53BC,
    (s32)D_800A53C8, (s32)D_800A53D4, (s32)D_800A53E0, (s32)D_800A53EC,
    (s32)D_800A53F8,
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
    0, 0, 0x60040000,
};
s32 D_800A5470[] = {
    0, 0, 0x60040000,
};
s32 D_800A547C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5488[] = {
    0, (s32)D_800A5428, (s32)D_800A5434, (s32)D_800A5440,
    (s32)D_800A544C, (s32)D_800A5458, (s32)D_800A5464, (s32)D_800A5470,
    (s32)D_800A547C,
};
s32 D_800A54AC[] = {
    15, 19, 0x60880000,
};
s32 D_800A54B8[] = {
    317, 19, 0x60880000,
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
    0, 0, 0x60040000,
};
s32 D_800A54F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5500[] = {
    0, 0, 0x60040000,
};
s32 D_800A550C[] = {
    0, (s32)D_800A54AC, (s32)D_800A54B8, (s32)D_800A54C4,
    (s32)D_800A54D0, (s32)D_800A54DC, (s32)D_800A54E8, (s32)D_800A54F4,
    (s32)D_800A5500,
};
s32 D_800A5530[] = {
    69, 0, 0, (s32)D_800A5380,
    (s32)D_800A5404, (s32)D_800A5488, (s32)D_800A550C,
};
u8 D_800A554C[] = {
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
    0x40, 0x01, 0x00, 0x01, 0x6A, 0x01, 0x00, 0x01,
    0xA8, 0x00, 0x00, 0x00, 0x70, 0x01, 0xFF, 0x01,
};
s32 D_800A55BC[] = {
    2569, 65535,
};
s32 D_800A55C4[] = {
    0x10A09, 0x1903A, 65535,
};
s32 D_800A55D0[] = {
    0x10A09, 65535,
};
s32 D_800A55D8[] = {
    2569, 65535,
};
s32 D_800A55E0[] = {
    0x10A09, 0x1903A, 65535,
};
s32 D_800A55EC[] = {
    0x10A09, 65535,
};
s32 D_800A55F4[] = {
    2569, 65535,
};
s32 D_800A55FC[] = {
    0x10A09, 0x1903A, 65535,
};
s32 D_800A5608[] = {
    0x10A09, 65535,
};
s32 D_800A5610[] = {
    2569, 65535,
};
s32 D_800A5618[] = {
    0x10A09, 0x1903A, 65535,
};
s32 D_800A5624[] = {
    0x10A09, 65535,
};
s32 D_800A562C[] = {
    2569, 65535,
};
s32 D_800A5634[] = {
    0x10A09, 0x1903A, 65535,
};
s32 D_800A5640[] = {
    0x10A09, 65535,
};
s32 D_800A5648[] = {
    (s32)D_800A55BC, (s32)D_800A55C4, 723, (s32)D_800A55D0,
    0, 153, 0, 0,
    0,
};
s32 D_800A566C[] = {
    (s32)D_800A55D8, (s32)D_800A55E0, 723, (s32)D_800A55EC,
    0, 154, 0, 0,
    0,
};
s32 D_800A5690[] = {
    (s32)D_800A55F4, (s32)D_800A55FC, 723, (s32)D_800A5608,
    0, 155, 0, 0,
    0,
};
s32 D_800A56B4[] = {
    (s32)D_800A5610, (s32)D_800A5618, 723, (s32)D_800A5624,
    0, 156, 0, 0,
    0,
};
s32 D_800A56D8[] = {
    (s32)D_800A562C, (s32)D_800A5634, 723, (s32)D_800A5640,
    0, 157, 0, 0,
    0,
};
s32 D_800A56FC[] = {
    0x1701D, 65535,
};
s32 D_800A5704[] = {
    0x16025, 65535,
};
s32 D_800A570C[] = {
    0x16026, 65535,
};
s32 D_800A5714[] = {
    0x1701A, 65535,
};
s32 D_800A571C[] = {
    0x1602B, 65535,
};
s32 D_800A5724[] = {
    (s32)D_800A56FC, (s32)D_800A5648, 0x40108, 0x13D039B,
    1,
};
s32 D_800A5738[] = {
    (s32)D_800A5704, (s32)D_800A566C, 0x40108, 0x13D039B,
    1,
};
s32 D_800A574C[] = {
    (s32)D_800A570C, (s32)D_800A5690, 0x40108, 0x13D039B,
    1,
};
s32 D_800A5760[] = {
    (s32)D_800A5714, (s32)D_800A56B4, 0x40108, 0x13D039B,
    1,
};
s32 D_800A5774[] = {
    (s32)D_800A571C, (s32)D_800A56D8, 0x40108, 0x13D039B,
    1,
};
s32 D_800A5788[] = {
    (s32)D_800A5724, (s32)D_800A5738, (s32)D_800A574C, (s32)D_800A5760,
    (s32)D_800A5774, 0,
};
u8 D_800A57A0[] = {
    0x01, 0x01, 0xE6, 0x02, 0x32, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0x03, 0x6C, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x54, 0x02,
    0x00, 0x02, 0x06, 0x00, 0xA3, 0x03, 0x25, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00,
    0x93, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x58, 0x02, 0x31, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x78, 0x06, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE9, 0x02, 0x56, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2A, 0x01, 0xBA, 0x01,
    0xF9, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5820[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x99, 0x02, 0x48, 0x06, 0xD0, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x08, 0x00, 0xF0, 0x00, 0xD8, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x08, 0x00, 0x00, 0x01, 0x50, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x09, 0x00, 0x02, 0x01, 0x20, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x09, 0x00, 0xF2, 0x00, 0x88, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x06, 0x00, 0xD2, 0x01, 0xC8, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x06, 0x00, 0xC2, 0x01, 0x60, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x0F, 0x00, 0xAF, 0x01, 0x28, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x0F, 0x00, 0xBF, 0x01, 0x30, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x04, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x09, 0x00, 0x30, 0x03, 0x08, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x09, 0x00, 0x40, 0x03, 0x70, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A5958[])(void) = {
    func_800A503C,
};
s32 D_800A595C[] = {
    1285, (s32)D_800A5150,
#if VERSION_US
    0x12E001B,
#elif VERSION_EU
    0x135001B,
#endif
    0, (s32)func_800A4FA4, 1286, (s32)D_800A51F0,
#if VERSION_US
    0x12E001C,
#elif VERSION_EU
    0x135001C,
#endif
    0, (s32)func_800A4FF0, -1, 0,
    0, 0, 0,
};
