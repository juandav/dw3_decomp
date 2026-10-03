#include "common.h"
#include "stage.h"
void func_800A4E48();
extern void (*D_800A5E6C[])(void);
void func_800A5054();
extern StageTileFrame **D_800A5420[];

/* Plays a sequence of StageTileFrame animations on tile */
void func_800A4CBC(StageTile *tile, StageTileFrame **seqs, StageTileCursor *cur, s32 depth) {
    s32 dt;

    if (depth == 0) {
        dt = GFX_FUNCS.getFrameTime();
        if (dt > 4) {
            dt = 4;
        }
        cur->timer -= dt;
    }
    if (cur->timer <= 0) {
        if (seqs[cur->seq][cur->index].last) {
            cur->seq++;
            cur->index = 0;
            if (seqs[cur->seq] == NULL) {
                cur->seq = 0;
            }
        } else {
            cur->index++;
        }
        cur->timer += seqs[cur->seq][cur->index].duration;
        func_800A4CBC(tile, seqs, cur, depth + 1);
    }
    if (depth == 0) {
        tile->frame = seqs[cur->seq][cur->index].frame;
        tile->unk9 = seqs[cur->seq][cur->index].unk9;
    }
}

/* Plays the sequences of the records with animations 1 to 5 */
void func_800A4E48(StageTileCursors *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->cursors[0].seq = 0;
        task->cursors[0].index = 0;
        task->cursors[0].timer = D_800A5420[0][0][0].duration;
        task->cursors[1].seq = 0;
        task->cursors[1].index = 0;
        task->cursors[1].timer = D_800A5420[1][0][0].duration;
        task->cursors[2].seq = 0;
        task->cursors[2].index = 0;
        task->cursors[2].timer = D_800A5420[2][0][0].duration;
        task->cursors[3].seq = 0;
        task->cursors[3].index = 0;
        task->cursors[3].timer = D_800A5420[3][0][0].duration;
        task->cursors[4].seq = 0;
        task->cursors[4].index = 0;
        task->cursors[4].timer = D_800A5420[3][0][0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            switch (tile->anim) {
            case 1:
                func_800A4CBC(tile, D_800A5420[0], &task->cursors[0], 0);
                break;
            case 2:
                func_800A4CBC(tile, D_800A5420[1], &task->cursors[1], 0);
                break;
            case 3:
                func_800A4CBC(tile, D_800A5420[2], &task->cursors[2], 0);
                break;
            case 4:
                func_800A4CBC(tile, D_800A5420[3], &task->cursors[3], 0);
                break;
            case 5:
                func_800A4CBC(tile, D_800A5420[4], &task->cursors[4], 0);
                break;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5028(void) {
    return createTask(func_800A4E48, 0x78, 0);
}

void func_800A5054(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A5028();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A50B8(void *owner) {
    StageTask *task = createTask(func_800A5054, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5E6C[0]();
    return task;
}

/* the color the setup copies to D_800990B4.unk38 */
const CVECTOR D_800A4CB8 = { 0x80, 0x80, 0x80, 0 };

INCLUDE_ASM("stages/nonmatchings/wstag481", func_800A5114);

void func_800A5114();
extern StageTileFrame D_800A5240[];
extern StageTileFrame D_800A5250[];
extern StageTileFrame D_800A5268[];
extern StageTileFrame D_800A5278[];
extern StageTileFrame D_800A5290[];
extern StageTileFrame D_800A52A0[];
extern StageTileFrame D_800A52B8[];
extern StageTileFrame D_800A52C8[];
extern StageTileFrame D_800A52E0[];
extern StageTileFrame D_800A52F0[];
extern StageTileFrame *D_800A5308[];
extern StageTileFrame *D_800A5340[];
extern StageTileFrame *D_800A5378[];
extern StageTileFrame *D_800A53B0[];
extern StageTileFrame *D_800A53E8[];
extern s32 D_800A5434[];
extern s32 D_800A5440[];
extern s32 D_800A544C[];
extern s32 D_800A5458[];
extern s32 D_800A5464[];
extern s32 D_800A5470[];
extern s32 D_800A547C[];
extern s32 D_800A5488[];
extern s32 D_800A54B8[];
extern s32 D_800A54C4[];
extern s32 D_800A54D0[];
extern s32 D_800A54DC[];
extern s32 D_800A54E8[];
extern s32 D_800A54F4[];
extern s32 D_800A5500[];
extern s32 D_800A550C[];
extern s32 D_800A553C[];
extern s32 D_800A5548[];
extern s32 D_800A5554[];
extern s32 D_800A5560[];
extern s32 D_800A556C[];
extern s32 D_800A5578[];
extern s32 D_800A5584[];
extern s32 D_800A5590[];
extern s32 D_800A55C0[];
extern s32 D_800A55CC[];
extern s32 D_800A55D8[];
extern s32 D_800A55E4[];
extern s32 D_800A55F0[];
extern s32 D_800A55FC[];
extern s32 D_800A5608[];
extern s32 D_800A5614[];
extern s32 D_800A5494[];
extern s32 D_800A5518[];
extern s32 D_800A559C[];
extern s32 D_800A5620[];

StageTileFrame D_800A5240[] = {
    { 64, 10, 0, 0 }, { 64, 10, 1, 0 }, { 64, 10, 2, 0 }, { 64, 10, 1, 1 },
};
StageTileFrame D_800A5250[] = {
    { 65, 4, 2, 0 }, { 65, 4, 4, 0 }, { 65, 4, 6, 0 }, { 65, 4, 4, 0 },
    { 65, 4, 2, 0 }, { 65, 4, 0, 1 },
};
StageTileFrame D_800A5268[] = {
    { 66, 10, 0, 0 }, { 66, 10, 1, 0 }, { 66, 10, 2, 0 }, { 66, 10, 1, 1 },
};
StageTileFrame D_800A5278[] = {
    { 67, 4, 2, 0 }, { 67, 4, 4, 0 }, { 67, 4, 6, 0 }, { 67, 4, 4, 0 },
    { 67, 4, 2, 0 }, { 67, 4, 0, 1 },
};
StageTileFrame D_800A5290[] = {
    { 68, 10, 0, 0 }, { 68, 10, 1, 0 }, { 68, 10, 2, 0 }, { 68, 10, 1, 1 },
};
StageTileFrame D_800A52A0[] = {
    { 69, 4, 2, 0 }, { 69, 4, 4, 0 }, { 69, 4, 6, 0 }, { 69, 4, 4, 0 },
    { 69, 4, 2, 0 }, { 69, 4, 0, 1 },
};
StageTileFrame D_800A52B8[] = {
    { 70, 10, 0, 0 }, { 70, 10, 1, 0 }, { 70, 10, 2, 0 }, { 70, 10, 1, 1 },
};
StageTileFrame D_800A52C8[] = {
    { 71, 4, 2, 0 }, { 71, 4, 4, 0 }, { 71, 4, 6, 0 }, { 71, 4, 4, 0 },
    { 71, 4, 2, 0 }, { 71, 4, 0, 1 },
};
StageTileFrame D_800A52E0[] = {
    { 72, 10, 0, 0 }, { 72, 10, 1, 0 }, { 72, 10, 2, 0 }, { 72, 10, 1, 1 },
};
StageTileFrame D_800A52F0[] = {
    { 73, 4, 2, 0 }, { 73, 4, 4, 0 }, { 73, 4, 6, 0 }, { 73, 4, 4, 0 },
    { 73, 4, 2, 0 }, { 73, 4, 0, 1 },
};
StageTileFrame *D_800A5308[] = {
    D_800A5240, D_800A5240, D_800A5240, D_800A5240,
    D_800A5240, D_800A5240, D_800A5240, D_800A5240,
    D_800A5240, D_800A5240, D_800A5240, D_800A5240,
    D_800A5250, NULL,
};
StageTileFrame *D_800A5340[] = {
    D_800A5268, D_800A5268, D_800A5268, D_800A5268,
    D_800A5268, D_800A5268, D_800A5268, D_800A5268,
    D_800A5268, D_800A5268, D_800A5268, D_800A5268,
    D_800A5278, NULL,
};
StageTileFrame *D_800A5378[] = {
    D_800A5290, D_800A5290, D_800A5290, D_800A5290,
    D_800A5290, D_800A5290, D_800A5290, D_800A5290,
    D_800A5290, D_800A5290, D_800A5290, D_800A5290,
    D_800A52A0, NULL,
};
StageTileFrame *D_800A53B0[] = {
    D_800A52B8, D_800A52B8, D_800A52B8, D_800A52B8,
    D_800A52B8, D_800A52B8, D_800A52B8, D_800A52B8,
    D_800A52B8, D_800A52B8, D_800A52B8, D_800A52B8,
    D_800A52C8, NULL,
};
StageTileFrame *D_800A53E8[] = {
    D_800A52E0, D_800A52E0, D_800A52E0, D_800A52E0,
    D_800A52E0, D_800A52E0, D_800A52E0, D_800A52E0,
    D_800A52E0, D_800A52E0, D_800A52E0, D_800A52E0,
    D_800A52F0, NULL,
};
StageTileFrame **D_800A5420[] = {
    D_800A5308, D_800A5340, D_800A5378, D_800A53B0,
    D_800A53E8,
};
s32 D_800A5434[] = {
    107, 9, 0x60080000,
};
s32 D_800A5440[] = {
    107, 9, 0x60080000,
};
s32 D_800A544C[] = {
    107, 9, 0x60080000,
};
s32 D_800A5458[] = {
    107, 9, 0x60080000,
};
s32 D_800A5464[] = {
    155, 9, 0x60080000,
};
s32 D_800A5470[] = {
    155, 9, 0x60080000,
};
s32 D_800A547C[] = {
    155, 9, 0x60080000,
};
s32 D_800A5488[] = {
    155, 9, 0x60080000,
};
s32 D_800A5494[] = {
    4, (s32)D_800A5434, (s32)D_800A5440, (s32)D_800A544C,
    (s32)D_800A5458, (s32)D_800A5464, (s32)D_800A5470, (s32)D_800A547C,
    (s32)D_800A5488,
};
s32 D_800A54B8[] = {
    105, 8, 0x60080000,
};
s32 D_800A54C4[] = {
    105, 8, 0x60080000,
};
s32 D_800A54D0[] = {
    105, 8, 0x60080000,
};
s32 D_800A54DC[] = {
    105, 8, 0x60080000,
};
s32 D_800A54E8[] = {
    159, 8, 0x60080000,
};
s32 D_800A54F4[] = {
    159, 8, 0x60080000,
};
s32 D_800A5500[] = {
    159, 8, 0x60080000,
};
s32 D_800A550C[] = {
    159, 8, 0x60080000,
};
s32 D_800A5518[] = {
    2, (s32)D_800A54B8, (s32)D_800A54C4, (s32)D_800A54D0,
    (s32)D_800A54DC, (s32)D_800A54E8, (s32)D_800A54F4, (s32)D_800A5500,
    (s32)D_800A550C,
};
s32 D_800A553C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5548[] = {
    0, 0, 0x60040000,
};
s32 D_800A5554[] = {
    0, 0, 0x60040000,
};
s32 D_800A5560[] = {
    0, 0, 0x60040000,
};
s32 D_800A556C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5578[] = {
    0, 0, 0x60040000,
};
s32 D_800A5584[] = {
    0, 0, 0x60040000,
};
s32 D_800A5590[] = {
    0, 0, 0x60040000,
};
s32 D_800A559C[] = {
    0, (s32)D_800A553C, (s32)D_800A5548, (s32)D_800A5554,
    (s32)D_800A5560, (s32)D_800A556C, (s32)D_800A5578, (s32)D_800A5584,
    (s32)D_800A5590,
};
s32 D_800A55C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A55CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A55D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A55E4[] = {
    331, 9, 0x60080000,
};
s32 D_800A55F0[] = {
    332, 8, 0x60080000,
};
s32 D_800A55FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5608[] = {
    177, 9, 0x60080000,
};
s32 D_800A5614[] = {
    106, 8, 0x60080000,
};
s32 D_800A5620[] = {
    0, (s32)D_800A55C0, (s32)D_800A55CC, (s32)D_800A55D8,
    (s32)D_800A55E4, (s32)D_800A55F0, (s32)D_800A55FC, (s32)D_800A5608,
    (s32)D_800A5614,
};
s32 D_800A5644[] = {
    74, 0, 0, (s32)D_800A5494,
    (s32)D_800A5518, (s32)D_800A559C, (s32)D_800A5620,
};
s32 D_800A5660[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A56C0[] = {
    0x2400101, 64, 0x1360000, 197,
    0x2010000, 0x420240, 0, 0xD0017D,
    0, 0x2400301, 68, 0x1A00000,
    204, 0x5010000, 0x480240, 0,
    0x10201D0, 0, 0x2400401, 70,
    0x1D40000, 206, 0x10000, 0x1320240,
    0x83732, 0x19800BF, 0, 0x2400001,
    0x37320132, 0x2340008, 488, 0x10000,
    0x1320240, 0x83732, 0x1F20252, 0,
    0x2400001, 0x37320132, 0x2D40008, 120,
    0x10000, 0x1320240, 0x83732, 0x1A30304,
    0, 0x2400001, 0x37320132, 0x3240008,
    410, 0x10000, 0x1320240, 0x83732,
    0x21D0385, 0, 0x2400001, 0x3D380138,
    0x3D10008, 774, 0x10000, 0x1380240,
    0x83D38, 0x30403DA, 0, 0x2400001,
    0x3D380138, 0x3E30008, 783, 0x10000,
    0x1380240, 0x83D38, 0x30303F2, 0,
    0x2400001, 0x3D380138, 0x3F90008, 771,
    0x10000, 0x1380240, 0x83D38, 0x3100400,
    0, 0x2400001, 0x3D380138, 0x4170008,
    799, 0x10000, 0x1380240, 0x83D38,
    0x3170421, 0, 0x2400001, 0x3D380138,
    0x42A0008, 796, 0x10000, 0x1380240,
    0x83D38, 0x31B0439, 0, 0x2400001,
    0x3D380138, 0x4400008, 789, 0x10000,
    0x1380240, 0x83D38, 0x31C0448, 0,
    0x2400001, 0xF00023E, 0x4F0006, 617,
    0x10000, 0x23E0240, 0x60F00, 0x3720106,
    0, 0x2400001, 0xF00023E, 0x1AF0006,
    638, 0x10000, 0x23E0240, 0x60F00,
    0x29802BE, 0, 0x2400001, 0xF00023E,
    0x3A30006, 679, 0x10000, 0x23E0240,
    0x60F00, 0x282047F, 0, 0x2400001,
    0xF00023E, 0x50D0006, 701, 0x10000,
    0x23F0240, 0x60F00, 0x44F02C3, 0,
    0x2400001, 0xF00023F, 0x2DC0006, 964,
    0x10000, 0x23F0240, 0x60F00, 0x3BC041B,
    0, 0x2400001, 0xF00023F, 0x4340006,
    1132, 0x10000, 0x23F0240, 0x60F00,
    0x3A1050A, 0, 0x2400001, 0x564B014B,
    0x3670010, 187, 0x10000, 0x1570240,
    0x106257, 0x1CE0100, 0, 0x2FF0001,
    26, 0x5000000, 250, 0x10000,
    0x1B0280, 0, 0x2800280, 0,
    0x2800001, 28, 0x4800000, 640,
    0x10000, 0x1D0280, 0, 0x2800500,
    0, 0x2400001, 0, 0x4650000,
    1033, 0x10000, 0x1220640, 0xA3122,
    0x10F00C8, 0, 0x6400001, 0x31220122,
    0x12B000A, 546, 0x10000, 0x1220640,
    0xA3122, 0x529017B, 0, 0x6400001,
    0x31220122, 0x184000A, 925, 0x10000,
    0x1220640, 0xA3122, 0x2F701B4, 0,
    0x6400001, 0x31220122, 0x235000A, 1172,
    0x10000, 0x1220640, 0xA3122, 0x3CE028D,
    0, 0x6400001, 0x31220122, 0x367000A,
    170, 0x10000, 0x1220640, 0xA3122,
    0x4F30373, 0, 0x6400001, 0x31220122,
    0x375000A, 889, 0x10000, 0x1220640,
    0xA3122, 0x2F80384, 0, 0x6400001,
    0x31220122, 0x437000A, 128, 0x10000,
    0x1220640, 0xA3122, 0x222052A, 0,
    0x6400001, 0x31220122, 0x53D000A, 990,
    0x10000, 0x6306FF, 0, 0x1180118,
    0, 0x4400001, 10, 0x4110000,
    0x25B0236, 0x10000, 0xB0440, 0,
    0x249046D, 596, 0x4400001, 12,
    0x35E0000, 0x29A0293, 0x10000, 0xD0480,
    0, 0x13903FE, 367, 0x4400001,
    14, 0x2B50000, 0x1DF01DB, 0x10000,
    0xF0440, 0, 0x2470295, 589,
    0x4400001, 16, 0x4050000, 0x383037B,
    0x10000, 0x110440, 0, 0x3A803F3,
    945, 0x4400001, 18, 0x1410000,
    0x4070401, 0x10000, 0x130440, 0,
    0x4170335, 1057, 0x4400001, 20,
    0x1050000, 0x424041F, 0x10000, 0x150440,
    0, 0x4400264, 1097, 0x4400001,
    22, 0x3E10000, 0x4670462, 0x10000,
    0x170440, 0, 0x4800324, 1160,
    0x4400001, 24, 0x1910000, 0x4CF04C9,
    0x10000, 0x190440, 0, 0x4E10260,
    1255, 0x464FF01, 56, 0x1F00000,
    0x3270327, 0xFF010000, 0x380464, 0,
    0x3B70210, 951, 0x464FF01, 56,
    0x2300000, 0x2E702E7, 0xFF010000, 0x380464,
    0, 0x1670241, 359, 0x464FF01,
    56, 0x25F0000, 0x3000300, 0xFF010000,
    0x380464, 0, 0x34F02C0, 847,
    0x464FF01, 56, 0x3200000, 0x34F034F,
    0xFF010000, 0x380464, 0, 0x1D70430,
    471, 0x464FF01, 56, 0x4600000,
    0x1BF01BF, 0xFF010000, 0x380464, 0,
    0x1E70470, 487, 0x464FF01, 56,
    0x4800000, 0x20F020F, 0xFF010000, 0x380464,
    0, 0x1B90497, 441, 0x464FF01,
    56, 0x4A00000, 0x22F022F, 0xFF010000,
    0x380464, 0, 0x1D704B0, 471,
    0x464FF01, 56, 0x4E00000, 0x1EF01EF,
    0xFF010000, 0x380464, 0, 0x25D0517,
    605, 0x464FF01, 56, 0x5200000,
    0x1AF01AF, 0xFF010000, 0x380464, 0,
    0x26F0540, 623, 0, 0,
    0, 0, 0,
};
s32 D_800A5D4C[] = {
    65535, 65535, 0x2A80001, 0x1D406C8,
    3, 0, 65535, 65535,
    0x2A20001, 0x3500140, 5, 0,
    0x17094, 65535, 0x2E80009, 0xD00240,
    1, 0x20003, 0x17094, 65535,
    0x2E80009, 0xD00240, 1, 0x1001A,
    0x18005, 65535, 0xFFD00007, 65512,
    0, 0, 0x18005, 65535,
    0x300007, 65512, 0, 0,
    0x18005, 65535, 7, 65496,
    0, 0, 0x18005, 65535,
    0xFFD00007, 40, 0, 0,
    0x18005, 65535, 0x300007, 40,
    0, 0, 65535, 65535,
    6, 0, 0, 0,
    65535, 65535, 0x10006, 0,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5E6C[])(void) = {
    func_800A5114,
};
