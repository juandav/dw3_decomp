#include "common.h"
#include "stage.h"
extern s32 D_800A5544[];
extern s32 D_800A5CF8[];
extern s32 D_800A5AF8[];
extern u8 D_800A5560[];
extern u8 D_800A5BBC[];
extern u8 D_800A5B3C[];
void func_800A4D98();
extern void (*D_800A5CF4[])(void);
void func_800A4E98();
void func_800A5050();
extern AnimFrame D_800A52A8[];

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

/* Sets the frame of the records of StageInfo.unk10 with animation 1 */
void func_800A4D98(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A52A8[0].duration;
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = func_800A4CA4(&task->anims[0], D_800A52A8, 0);
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

/* Creates the event object of progress 4 when flag 0x400F is set and 0x4010 is not, and the stage helper task */
void func_800A4E98(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (GAME_PROGRESS == 4 && FLAGS_00.checkCondition(0x400F, 1) && FLAGS_00.checkCondition(0x4010, 0)) {
            children[0] = func_80084B80(0x3D);
        }
        children[1] = func_800A4E6C();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4F5C(void *owner) {
    StageTask *task = createTask(func_800A4E98, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5CF4[0]();
    return task;
}

void func_800A4FB8(void) {
    FLAGS_00.applyAction(0x400F, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5004(void) {
    FLAGS_00.applyAction(0x4010, 1);
    FLAGS_00.applyAction(0x8699, 1);
}

#if VERSION_US
void func_800A5050(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x247;
    D_800990B4.unkC = 0x2480000;
    D_800990B4.unk10 = D_800A5B3C;
    D_800990B4.unk14 = D_800A5BBC;
    D_800990B4.unk1C = 0x3C9;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x16B00;
    D_800990B4.unk30 = 0x44400;
    D_800990B4.unk28 = D_800A5560;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A5AF8;
    D_800990B4.events = D_800A5CF8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5544;
    D_8009A70C.setFile(0, 0x2480001);
    D_8009A70C.setFile(7, 0x2480002);
    D_8009A70C.setFile(4, 0x2480003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag405", func_800A5050);
#endif

extern s32 D_800A5334[];
extern s32 D_800A5340[];
extern s32 D_800A534C[];
extern s32 D_800A5358[];
extern s32 D_800A5364[];
extern s32 D_800A5370[];
extern s32 D_800A537C[];
extern s32 D_800A5388[];
extern s32 D_800A53B8[];
extern s32 D_800A53C4[];
extern s32 D_800A53D0[];
extern s32 D_800A53DC[];
extern s32 D_800A53E8[];
extern s32 D_800A53F4[];
extern s32 D_800A5400[];
extern s32 D_800A540C[];
extern s32 D_800A543C[];
extern s32 D_800A5448[];
extern s32 D_800A5454[];
extern s32 D_800A5460[];
extern s32 D_800A546C[];
extern s32 D_800A5478[];
extern s32 D_800A5484[];
extern s32 D_800A5490[];
extern s32 D_800A54C0[];
extern s32 D_800A54CC[];
extern s32 D_800A54D8[];
extern s32 D_800A54E4[];
extern s32 D_800A54F0[];
extern s32 D_800A54FC[];
extern s32 D_800A5508[];
extern s32 D_800A5514[];
extern s32 D_800A5394[];
extern s32 D_800A5418[];
extern s32 D_800A549C[];
extern s32 D_800A5520[];
extern s32 D_800A55F0[];
extern s32 D_800A55F8[];
extern s32 D_800A5600[];
extern s32 D_800A560C[];
extern s32 D_800A561C[];
extern s32 D_800A5630[];
extern s32 D_800A5638[];
extern s32 D_800A564C[];
extern s32 D_800A5654[];
extern s32 D_800A5660[];
extern s32 D_800A5668[];
extern s32 D_800A5670[];
extern s32 D_800A5678[];
extern s32 D_800A5684[];
extern s32 D_800A5694[];
extern s32 D_800A56A8[];
extern s32 D_800A56B0[];
extern s32 D_800A56C4[];
extern s32 D_800A56CC[];
extern s32 D_800A56D8[];
extern s32 D_800A56E0[];
extern s32 D_800A56E8[];
extern s32 D_800A56F4[];
extern s32 D_800A5704[];
extern s32 D_800A5920[];
extern s32 D_800A5710[];
extern s32 D_800A5930[];
extern s32 D_800A5758[];
extern s32 D_800A5940[];
extern s32 D_800A577C[];
extern s32 D_800A594C[];
extern s32 D_800A57C4[];
extern s32 D_800A5958[];
extern s32 D_800A57E8[];
extern s32 D_800A5960[];
extern s32 D_800A5818[];
extern s32 D_800A5968[];
extern s32 D_800A5830[];
extern s32 D_800A5970[];
extern s32 D_800A5848[];
extern s32 D_800A5978[];
extern s32 D_800A5860[];
extern s32 D_800A5980[];
extern s32 D_800A5878[];
extern s32 D_800A5988[];
extern s32 D_800A5890[];
extern s32 D_800A5990[];
extern s32 D_800A58A8[];
extern s32 D_800A5998[];
extern s32 D_800A58C0[];
extern s32 D_800A59A0[];
extern s32 D_800A58D8[];
extern s32 D_800A59A8[];
extern s32 D_800A58F0[];
extern s32 D_800A59B0[];
extern s32 D_800A5908[];
extern s32 D_800A59B8[];
extern s32 D_800A59CC[];
extern s32 D_800A59E0[];
extern s32 D_800A59F4[];
extern s32 D_800A5A08[];
extern s32 D_800A5A1C[];
extern s32 D_800A5A30[];
extern s32 D_800A5A44[];
extern s32 D_800A5A58[];
extern s32 D_800A5A6C[];
extern s32 D_800A5A80[];
extern s32 D_800A5A94[];
extern s32 D_800A5AA8[];
extern s32 D_800A5ABC[];
extern s32 D_800A5AD0[];
extern s32 D_800A5AE4[];
extern s32 D_800A5164[];
extern s32 D_800A5204[];

s32 D_800A5164[] = {
    0x10600, 0x1020002, 0x37C0002, 0x50153,
    0x5A0100, 0x143039C, 0x5A0101, 0x10001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x50001, 0x60300, 0x1E0300, 512,
    0x20001, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0x5A0002, 0x3010000, 0x1E0300, 512,
    0x20003, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x1E0300, 512,
    0x5A0004, 0x3010000, 0x1E0300,
#if VERSION_US
    0x1B60000,
#elif VERSION_EU
    0,
#endif
};
s32 D_800A5204[] = {
    0x10600, 0x1000002, 0x37C0002, 0x1010153,
    0x10002, 0x1000005, 0x39C005A, 0x1010143,
    0x1005A, 0x3000001, 0x2000078, 0x10000,
    90, 0x1010301, 0x34A032D, 0x3000002,
    0x200001E, 0x20000, 0x30002, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x200001E, 0x30000, 90, 0x3000301,
    0x200001E, 0x40000, 0x30002, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x200001E, 0x50000, 90, 0x3000301,
    60,
};
AnimFrame D_800A52A8[] = {
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
s32 D_800A5334[] = {
    50, 4, 0x60080000,
};
s32 D_800A5340[] = {
    50, 4, 0x60080000,
};
s32 D_800A534C[] = {
    50, 4, 0x60080000,
};
s32 D_800A5358[] = {
    51, 4, 0x60080000,
};
s32 D_800A5364[] = {
    51, 4, 0x60080000,
};
s32 D_800A5370[] = {
    51, 4, 0x60080000,
};
s32 D_800A537C[] = {
    52, 4, 0x60080000,
};
s32 D_800A5388[] = {
    52, 4, 0x60080000,
};
s32 D_800A5394[] = {
    3, (s32)D_800A5334, (s32)D_800A5340, (s32)D_800A534C,
    (s32)D_800A5358, (s32)D_800A5364, (s32)D_800A5370, (s32)D_800A537C,
    (s32)D_800A5388,
};
s32 D_800A53B8[] = {
    51, 4, 0x60080000,
};
s32 D_800A53C4[] = {
    51, 4, 0x60080000,
};
s32 D_800A53D0[] = {
    51, 4, 0x60080000,
};
s32 D_800A53DC[] = {
    51, 4, 0x60080000,
};
s32 D_800A53E8[] = {
    51, 4, 0x60080000,
};
s32 D_800A53F4[] = {
    51, 4, 0x60080000,
};
s32 D_800A5400[] = {
    51, 4, 0x60080000,
};
s32 D_800A540C[] = {
    51, 4, 0x60080000,
};
s32 D_800A5418[] = {
    5, (s32)D_800A53B8, (s32)D_800A53C4, (s32)D_800A53D0,
    (s32)D_800A53DC, (s32)D_800A53E8, (s32)D_800A53F4, (s32)D_800A5400,
    (s32)D_800A540C,
};
s32 D_800A543C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5448[] = {
    0, 0, 0x60040000,
};
s32 D_800A5454[] = {
    0, 0, 0x60040000,
};
s32 D_800A5460[] = {
    0, 0, 0x60040000,
};
s32 D_800A546C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5478[] = {
    0, 0, 0x60040000,
};
s32 D_800A5484[] = {
    0, 0, 0x60040000,
};
s32 D_800A5490[] = {
    0, 0, 0x60040000,
};
s32 D_800A549C[] = {
    0, (s32)D_800A543C, (s32)D_800A5448, (s32)D_800A5454,
    (s32)D_800A5460, (s32)D_800A546C, (s32)D_800A5478, (s32)D_800A5484,
    (s32)D_800A5490,
};
s32 D_800A54C0[] = {
    2, 19, 0x60880000,
};
s32 D_800A54CC[] = {
    310, 19, 0x60880000,
};
s32 D_800A54D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A54E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A54F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5508[] = {
    0, 0, 0x60040000,
};
s32 D_800A5514[] = {
    0, 0, 0x60040000,
};
s32 D_800A5520[] = {
    0, (s32)D_800A54C0, (s32)D_800A54CC, (s32)D_800A54D8,
    (s32)D_800A54E4, (s32)D_800A54F0, (s32)D_800A54FC, (s32)D_800A5508,
    (s32)D_800A5514,
};
s32 D_800A5544[] = {
    12, 0, 0, (s32)D_800A5394,
    (s32)D_800A5418, (s32)D_800A549C, (s32)D_800A5520,
};
u8 D_800A5560[] = {
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
    0x80, 0x01, 0x00, 0x01, 0xB4, 0x01, 0x20, 0x01,
    0xD0, 0x01, 0x20, 0x00, 0x70, 0x01, 0xFF, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA0, 0x01, 0x20, 0x01,
    0x80, 0x01, 0x20, 0x00, 0x50, 0x01, 0xFE, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xAA, 0x01, 0x48, 0x01,
    0xA8, 0x01, 0x48, 0x00, 0x60, 0x01, 0xFE, 0x01,
};
s32 D_800A55F0[] = {
    6701, 65535,
};
s32 D_800A55F8[] = {
    0x11A2D, 65535,
};
s32 D_800A5600[] = {
    0x11A2D, 28714, 65535,
};
s32 D_800A560C[] = {
    28709, 0x11A2D, 0x1702A, 65535,
};
s32 D_800A561C[] = {
    0x17025, 28711, 0x11A2D, 0x1702A,
    65535,
};
s32 D_800A5630[] = {
    0x10600, 65535,
};
s32 D_800A5638[] = {
    0x17025, 0x17027, 0x11A2D, 0x1702A,
    65535,
};
s32 D_800A564C[] = {
    28683, 65535,
};
s32 D_800A5654[] = {
    0x17031, 0x17013, 65535,
};
s32 D_800A5660[] = {
    0x1700B, 65535,
};
s32 D_800A5668[] = {
    6701, 65535,
};
s32 D_800A5670[] = {
    0x11A2D, 65535,
};
s32 D_800A5678[] = {
    0x11A2D, 28714, 65535,
};
s32 D_800A5684[] = {
    0x11A2D, 0x1702A, 28709, 65535,
};
s32 D_800A5694[] = {
    0x11A2D, 0x1702A, 0x17025, 28711,
    65535,
};
s32 D_800A56A8[] = {
    0x10600, 65535,
};
s32 D_800A56B0[] = {
    0x11A2D, 0x1702A, 0x17025, 0x17027,
    65535,
};
s32 D_800A56C4[] = {
    28683, 65535,
};
s32 D_800A56CC[] = {
    0x17031, 0x17013, 65535,
};
s32 D_800A56D8[] = {
    0x1700B, 65535,
};
s32 D_800A56E0[] = {
    7184, 65535,
};
s32 D_800A56E8[] = {
    0x11C10, 7185, 65535,
};
s32 D_800A56F4[] = {
    0x1902F, 0x11C11, 0x10A01, 65535,
};
s32 D_800A5704[] = {
    0x11C10, 0x11C11, 65535,
};
s32 D_800A5710[] = {
    (s32)D_800A55F0, (s32)D_800A55F8, 690, (s32)D_800A5600,
    0, 695, (s32)D_800A560C, 0,
    696, (s32)D_800A561C, (s32)D_800A5630, 691,
    (s32)D_800A5638, 0, 700, 0,
    0, 0,
};
s32 D_800A5758[] = {
    (s32)D_800A564C, (s32)D_800A5654, 692, (s32)D_800A5660,
    0, 694, 0, 0,
    0,
};
s32 D_800A577C[] = {
    (s32)D_800A5668, (s32)D_800A5670, 690, (s32)D_800A5678,
    0, 695, (s32)D_800A5684, 0,
    696, (s32)D_800A5694, (s32)D_800A56A8, 691,
    (s32)D_800A56B0, 0, 700, 0,
    0, 0,
};
s32 D_800A57C4[] = {
    (s32)D_800A56C4, (s32)D_800A56CC, 692, (s32)D_800A56D8,
    0, 694, 0, 0,
    0,
};
s32 D_800A57E8[] = {
    (s32)D_800A56E0, 0, 241, (s32)D_800A56E8,
    (s32)D_800A56F4, 733, (s32)D_800A5704, 0,
    734, 0, 0, 0,
};
s32 D_800A5818[] = {
    0, 0, 745, 0,
    0, 0,
};
s32 D_800A5830[] = {
    0, 0, 758, 0,
    0, 0,
};
s32 D_800A5848[] = {
    0, 0, 756, 0,
    0, 0,
};
s32 D_800A5860[] = {
    0, 0, 751, 0,
    0, 0,
};
s32 D_800A5878[] = {
    0, 0, 753, 0,
    0, 0,
};
s32 D_800A5890[] = {
    0, 0, 754, 0,
    0, 0,
};
s32 D_800A58A8[] = {
    0, 0, 759, 0,
    0, 0,
};
s32 D_800A58C0[] = {
    0, 0, 757, 0,
    0, 0,
};
s32 D_800A58D8[] = {
    0, 0, 755, 0,
    0, 0,
};
s32 D_800A58F0[] = {
    0, 0, 752, 0,
    0, 0,
};
s32 D_800A5908[] = {
    0, 0, 693, 0,
    0, 0,
};
s32 D_800A5920[] = {
    24580, 32774, 0x17022, 65535,
};
s32 D_800A5930[] = {
    0x17022, 24580, 0x18006, 65535,
};
s32 D_800A5940[] = {
    0x1602B, 32774, 65535,
};
s32 D_800A594C[] = {
    0x1602B, 0x18006, 65535,
};
s32 D_800A5958[] = {
    0x16004, 65535,
};
s32 D_800A5960[] = {
    0x17015, 65535,
};
s32 D_800A5968[] = {
    0x1701A, 65535,
};
s32 D_800A5970[] = {
    0x17019, 65535,
};
s32 D_800A5978[] = {
    0x1600C, 65535,
};
s32 D_800A5980[] = {
    0x17016, 65535,
};
s32 D_800A5988[] = {
    0x17017, 65535,
};
s32 D_800A5990[] = {
    0x1602B, 65535,
};
s32 D_800A5998[] = {
    0x16026, 65535,
};
s32 D_800A59A0[] = {
    0x17018, 65535,
};
s32 D_800A59A8[] = {
    0x1600E, 65535,
};
s32 D_800A59B0[] = {
    0x1701A, 65535,
};
s32 D_800A59B8[] = {
    (s32)D_800A5920, (s32)D_800A5710, 0x4002B, 0x47202FC,
    1,
};
s32 D_800A59CC[] = {
    (s32)D_800A5930, (s32)D_800A5758, 0x4002B, 0x47202FC,
    1,
};
s32 D_800A59E0[] = {
    (s32)D_800A5940, (s32)D_800A577C, 0x4002B, 0x47202FC,
    1,
};
s32 D_800A59F4[] = {
    (s32)D_800A594C, (s32)D_800A57C4, 0x4002B, 0x47202FC,
    1,
};
s32 D_800A5A08[] = {
    (s32)D_800A5958, (s32)D_800A57E8, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A1C[] = {
    (s32)D_800A5960, (s32)D_800A5818, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A30[] = {
    (s32)D_800A5968, (s32)D_800A5830, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A44[] = {
    (s32)D_800A5970, (s32)D_800A5848, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A58[] = {
    (s32)D_800A5978, (s32)D_800A5860, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A6C[] = {
    (s32)D_800A5980, (s32)D_800A5878, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A80[] = {
    (s32)D_800A5988, (s32)D_800A5890, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5A94[] = {
    (s32)D_800A5990, (s32)D_800A58A8, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5AA8[] = {
    (s32)D_800A5998, (s32)D_800A58C0, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5ABC[] = {
    (s32)D_800A59A0, (s32)D_800A58D8, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5AD0[] = {
    (s32)D_800A59A8, (s32)D_800A58F0, 0x5005A, 0x143039C,
    1,
};
s32 D_800A5AE4[] = {
    (s32)D_800A59B0, (s32)D_800A5908, 0x6009D, 0x47202FC,
    1,
};
s32 D_800A5AF8[] = {
    (s32)D_800A59B8, (s32)D_800A59CC, (s32)D_800A59E0, (s32)D_800A59F4,
    (s32)D_800A5A08, (s32)D_800A5A1C, (s32)D_800A5A30, (s32)D_800A5A44,
    (s32)D_800A5A58, (s32)D_800A5A6C, (s32)D_800A5A80, (s32)D_800A5A94,
    (s32)D_800A5AA8, (s32)D_800A5ABC, (s32)D_800A5AD0, (s32)D_800A5AE4,
    0,
};
u8 D_800A5B3C[] = {
    0x01, 0x01, 0xE6, 0x02, 0x32, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0x03, 0x6C, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x54, 0x02,
    0x00, 0x02, 0x06, 0x00, 0xA3, 0x03, 0x25, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x01, 0x01, 0x01, 0x06, 0x08, 0x00, 0xB3, 0x00,
    0x90, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x01, 0x01, 0x01, 0x06, 0x08, 0x00,
    0x5A, 0x02, 0x2F, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0xC8, 0x06, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE9, 0x02, 0x56, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2A, 0x01, 0xBA, 0x01,
    0xF9, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5BBC[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x2A, 0x02, 0x48, 0x06, 0xD0, 0x00,
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
void (*D_800A5CF4[])(void) = {
    func_800A5050,
};
s32 D_800A5CF8[] = {
    60, (s32)D_800A5164,
#if VERSION_US
    0x12E0000,
#elif VERSION_EU
    0x1350000,
#endif
    0, (s32)func_800A4FB8, 61, (s32)D_800A5204,
#if VERSION_US
    0x12E0001,
#elif VERSION_EU
    0x1350001,
#endif
    0, (s32)func_800A5004, -1, 0,
    0, 0, 0,
};
