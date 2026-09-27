#ifndef FIELDSTG_H
#define FIELDSTG_H

/*
 * FIELDSTG.PRO: the field mode, where the player walks around the map.
 *
 * The stage overlays (AAA/PRO/WSTAG###.PRO, see stage.h) load on top of it
 * at 0x800A4CA4 and call into it.
 */

#include "game.h"

typedef struct Point {
    s32 x;
    s32 y;
} Point;

typedef struct Actor {
    TASK_HEADER(Actor);
    /* 0x050 */ s32 x;
    /* 0x054 */ s32 y;
    /* 0x058 */ Point tile;
    /* 0x060 */ s32 dir;
    /* 0x064 */ s32 unk64;
    /* 0x068 */ s32 unk68[3];
    /* 0x074 */ s32 unk74;
    /* 0x078 */ s32 unk78[4];
    /* 0x088 */ s32 unk88;
    /* 0x08C */ s32 unk8C;
    /* 0x090 */ s32 unk90;
    /* 0x094 */ s32 unk94;
    /* 0x098 */ s32 unk98[2];
    /* 0x0A0 */ s32 unkA0;
    /* 0x0A4 */ s32 unkA4[6];
    /* 0x0BC */ s32 unkBC;
    /* 0x0C0 */ s32 unkC0[3];
    /* 0x0CC */ s32 unkCC;
    /* 0x0D0 */ s32 unkD0;
    /* 0x0D4 */ s32 unkD4[5];
    /* 0x0E8 */ s32 unkE8;
    /* 0x0EC */ s32 unkEC;
    /* 0x0F0 */ s32 unkF0;
    /* 0x0F4 */ s32 unkF4;
    /* 0x0F8 */ s32 unkF8;
    /* 0x0FC */ s32 unkFC[3];
    /* 0x108 */ void (*unk108)(struct Actor *);
} Actor;

typedef struct StreamTask {
    TASK_HEADER(StreamTask);
    /* 0x050 */ s32 time;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 frame;
    /* 0x05C */ s32 sector;
    /* 0x060 */ s32 file;
    /* 0x064 */ s32 frameSectors;
    /* 0x068 */ s32 buffer;
    /* 0x06C */ s32 loaded;
    /* 0x070 */ s32 unk70;
} StreamTask;

typedef struct ChoiceTask {
    TASK_HEADER(ChoiceTask);
    /* 0x50 */ s32 type;
    /* 0x54 */ s32 selection;
    /* 0x58 */ s32 unk58[2];
    /* 0x60 */ s32 scale;
    /* 0x64 */ s32 unk64;
} ChoiceTask;

/*
 * The game flag functions: a table in the executable's .data right after
 * FLAGS_00 and PENDING_FLAG_10 (game3.c), with no symbol of its own yet.
 */
typedef struct FlagFuncs {
    /* 0x00 */ u8 flags[4]; /* FLAGS_00 */
    /* 0x04 */ s32 pendingFlag10; /* PENDING_FLAG_10 */
    /* 0x08 */ s32 (*checkConditions)(u16 *list);
    /* 0x0C */ void (*applyAction)(s32 code, s32 value);
    /* 0x10 */ s32 (*checkCondition)(u16 code, u16 value);
    /* 0x14 */ void (*applyActions)(u16 *list);
    /* 0x18 */ void (*updateModeFlags)(void);
} FlagFuncs;

#define FLAG_FUNCS (*(FlagFuncs *)FLAGS_00)

void func_80082F1C(Task *task);
void func_80083998();
void func_80086C4C();
void func_8008A154();
void func_8008AE18(s32, s32, s32, s32, s32, s32);
void func_800876E4();
void func_8008DB60(Actor *);
void func_8008E1A4(Actor *);
void func_800878A4(s32 arg0, s32 arg1, s32 arg2);
void func_80090154(void);

extern u8 D_80099758[];
extern s32 D_8009A70C[];
extern s32 D_80099134[];
extern u8 D_8009A424[];

#endif /* FIELDSTG_H */
