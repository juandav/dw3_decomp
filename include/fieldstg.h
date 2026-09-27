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

/*
 * A character on the field (func_80090450): the player (kind 0) and the
 * other characters. Registered with id 5, key1 = character, key2 = kind.
 * x and y are in 1/256 tile units.
 */
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
    /* 0x10C */ s32 unk10C;
    /* 0x110 */ void (*unk110)(struct Actor *, s32 dir);
    /* 0x114 */ void (*unk114)();
    /* 0x118 */ void (*unk118)();
    /* 0x11C */ void (*unk11C)();
    /* 0x120 */ void (*unk120)();
    /* 0x124 */ void (*unk124)();
    /* 0x128 */ void (*unk128)();
    /* 0x12C */ void (*unk12C)(struct Actor *);
    /* 0x130 */ void (*unk130)(struct Actor *);
    /* 0x134 */ void (*setDir)(struct Actor *, s32 dir);
    /* 0x138 */ s32 (*unk138)(struct Actor *);
    /* 0x13C */ void (*unk13C)(struct Actor *, s32, s32, s32);
    /* 0x140 */ s32 (*unk140)(struct Actor *);
    /* 0x144 */ void (*unk144)(struct Actor *, s32);
    /* 0x148 */ void (*unk148)(struct Actor *, s32, s32 dir);
    /* 0x14C */ void (*getFacingTile)(struct Actor *, Point *out);
    /* 0x150 */ void (*unk150)(struct Actor *, s32 dir);
    /* 0x154 */ void (*unk154)(struct Actor *);
    /* 0x158 */ void (*unk158)();
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

/* The task of func_80086144 (id 4, see func_80086418) */
typedef struct Unk80086144 {
    TASK_HEADER(Unk80086144);
    /* 0x050 */ u8 unk50[0x14];
    /* 0x064 */ s32 unk64;
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ u8 unk70[0xC0];
    /* 0x130 */ Point *(*unk130)(struct Unk80086144 *);
} Unk80086144;

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
Actor *func_800914F0(s32 id);
void func_8008E768(Actor *actor, s32 arg1);
void func_8008DD9C(Actor *);
void *func_80088C2C(void);
void func_8008AEDC(s32);

extern Point D_8009A938;
extern s32 D_800990C4;
extern u8 *D_8009A940;
extern s32 D_8009A944;
extern Point D_80097000[]; /* tile offset of each direction */
extern Point D_8009A76C[];

extern u8 D_80099758[];
extern s32 D_8009A70C[];
extern s32 D_80099134[];
extern u8 D_8009A424[];

#endif /* FIELDSTG_H */
