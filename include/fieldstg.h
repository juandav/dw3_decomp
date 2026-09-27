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

/*
 * The field's state (D_800990B4). The first 0x64 bytes are cleared by
 * func_800913CC, which also picks the stage overlay for the current mode.
 */
typedef struct FieldState {
    /* 0x00 */ s32 stageFile; /* the stage overlay's file */
    /* 0x04 */ void (*stageInit)(void);
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ void *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ struct Unk800990D4 *unk20;
    /* 0x24 */ s32 *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ char unk38[4];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ void (*init)(void);
    /* 0x74 */ s32 (*unk74)(s32 index);
    /* 0x78 */ u8 (*unk78)(s32 index);
    /* 0x7C */ void *(*unk7C)(u8 *list, s32 id);
} FieldState;

/* The field's main task (func_8008A154, id 7); its children follow */
typedef struct FieldTask {
    TASK_HEADER(FieldTask);
    /* 0x50 */ u8 unk50[0x20];
    /* 0x70 */ s32 unk70;
    /* 0x74 */ Point unk74;
    /* 0x7C */ s32 unk7C;
} FieldTask;

/* An entry of the script command table D_8009A448 (ids from 0x320) */
typedef struct ScriptCommand {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 (*create)(s32 arg);
    /* 0x8 */ void (*handle)(s32 arg0, s32 arg1, s32 arg2);
} ScriptCommand;

/* A linear 0-0x1000 tween (func_80091298, func_8009132C) */
typedef struct Tween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s32 step;
    /* 0x8 */ s32 value;
    /* 0xC */ s32 active;
} Tween;

/* A wait timer for the scripts (func_80091520) */
typedef struct ScriptTimer {
    /* 0x0 */ s32 time;
    /* 0x4 */ s32 active;
    /* 0x8 */ void (*reset)(void);
    /* 0xC */ Actor *(*findActor)(s32 id);
} ScriptTimer;

/* A battle that can start on the field (see func_8008AEDC) */
typedef struct Battle {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Battle;

typedef struct BattleList {
    /* 0x0 */ s32 count;
    /* 0x4 */ Battle *battles[1];
} BattleList;

typedef struct Unk800990D4 {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ BattleList *battles[4];
} Unk800990D4;

/* The task of func_80084654 (func_80084B80) */
typedef struct Unk80084654 {
    TASK_HEADER(Unk80084654);
    /* 0x050 */ s32 unk50;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 unk58;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ u8 unk60[4];
    /* 0x064 */ struct {
        s32 id;
        s32 value;
    } entries[30];
} Unk80084654;

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

/* The task of func_80084D0C (func_80085240) */
typedef struct Unk80084D0C {
    TASK_HEADER(Unk80084D0C);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54[0x18];
} Unk80084D0C;

/* The task of func_80085350 (func_80085588) */
typedef struct Unk80085350 {
    TASK_HEADER(Unk80085350);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u8 unk5A[0x22];
} Unk80085350;

/* The task of func_80087FDC (func_800881A0) */
typedef struct Unk80087FDC {
    TASK_HEADER(Unk80087FDC);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54[0x14];
} Unk80087FDC;

/* The task of func_8008878C (func_80088BE4) */
typedef struct Unk8008878C {
    TASK_HEADER(Unk8008878C);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
} Unk8008878C;

/* The task of func_80089320 (func_80089668) */
typedef struct Unk80089320 {
    TASK_HEADER(Unk80089320);
    /* 0x50 */ Actor *actor;
    /* 0x54 */ u8 unk54[0x10];
} Unk80089320;

/* The task of func_8008B9D8 (func_8008BBD4) */
typedef struct Unk8008B9D8 {
    TASK_HEADER(Unk8008B9D8);
    /* 0x50 */ u8 unk50[0xC];
    /* 0x5C */ Point from;
    /* 0x64 */ Point to;
} Unk8008B9D8;

/* The task of func_8008C59C (func_8008C9F8) */
typedef struct Unk8008C59C {
    TASK_HEADER(Unk8008C59C);
    /* 0x50 */ Point pos;
    /* 0x58 */ u8 unk58[0x10];
} Unk8008C59C;

/* The task of func_8008CC4C (id 0x10, func_8008CF0C) */
typedef struct Unk8008CC4C {
    TASK_HEADER(Unk8008CC4C);
    /* 0x50 */ u8 unk50[0xC];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60[4];
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 unk66[0x2A];
} Unk8008CC4C;

/* The task of func_800834A0 (func_80083930) */
typedef struct Unk800834A0 {
    TASK_HEADER(Unk800834A0);
    /* 0x50 */ u8 unk50[8];
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u8 unk5A[0x12];
} Unk800834A0;

/* The task of func_800842C8 (func_800844B8) */
typedef struct Unk800842C8 {
    TASK_HEADER(Unk800842C8);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
} Unk800842C8;

/* The task of func_800870D4 (id 9, func_800874C8) */
typedef struct Unk800870D4 {
    TASK_HEADER(Unk800870D4);
    /* 0x050 */ u8 unk50[0x170];
} Unk800870D4;

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
Unk80084654 *func_80084B80(s16);
void func_8008DFE0(Actor *);
s32 func_80088E4C(Task *);
s32 func_8008B930(Actor *, s32);
void func_8008B398(s32 arg0, Point *pos, s32 arg2);
ScriptCommand *func_800916E8(s32 id);
Task *createInn(s32);
Point *func_800863F4(Unk80086144 *);
void func_80084D0C();
void func_80087FDC();
void func_8008926C();
void func_8008C388();
void func_8008CC4C();
void func_8008C59C();
void func_80086144();
void func_800870D4();
void func_8008878C();
void func_80085350();
void func_80089320();
void func_800842C8();
void func_8008B9D8();
void func_800834A0();

extern Point D_8009A938;
extern u8 *D_8009A940;
extern s32 D_8009A944;
extern Point D_80097000[]; /* tile offset of each direction */
extern Point D_8009A76C[];
extern FieldState D_800990B4;
extern ScriptCommand D_8009A448[];
extern s16 D_80096C38[];
extern s32 D_80096FE8[];
extern s32 D_80096FF4[];
extern s32 (*D_8009A750)(s32, Point *);
extern void (*D_80098B6C[])(void);

extern u8 D_80099758[];
extern s32 D_8009A70C[];
extern s32 D_80099134[];
extern ScriptTimer D_8009A424;

#endif /* FIELDSTG_H */
