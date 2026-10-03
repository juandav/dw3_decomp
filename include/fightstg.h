#ifndef FIGHTSTG_H
#define FIGHTSTG_H

/* FIGHTSTG.PRO: the battle. It loads WFIGHTMN (file 0x1FA) for a normal
   battle, or WFIGHTTS (file 0x1FB) for the battle test, at STAGE_VRAM. */

#include "game.h"
#include <libgs.h>

/* Draws one bone of a Model (func_8008588C), from the parts of an archive */
typedef struct Mesh {
    TASK_HEADER(Mesh);
    /* 0x50 */ u8 unk50[0xC];
    /* 0x5C */ s32 archive;
    /* 0x60 */ u8 *unk60;
    /* 0x64 */ u8 *unk64;
    /* 0x68 */ u8 *unk68;
    /* 0x6C */ u8 *unk6C;
    /* 0x70 */ Vec2 texPos;
    /* 0x78 */ void *unk78;
    /* 0x7C */ void *unk7C;
    /* 0x80 */ void *unk80;
    /* 0x84 */ MATRIX matrix;
    /* 0xA4 */ void (*draw)(struct Mesh *mesh, s32 layerId, MATRIX *matrix);
    /* 0xA8 */ void (*drawAlt)(struct Mesh *mesh, s32 layerId, MATRIX *matrix);
} Mesh;

/* One part of a Model: a mesh (Mesh) placed by a matrix relative to its
   parent's */
typedef struct ModelBone {
    /* 0x00 */ s32 parent;
    /* 0x04 */ s32 file; /* the mesh's file and index */
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 visible; /* 0 while its scale is tiny */
    /* 0x10 */ SVECTOR pos;
    /* 0x18 */ SVECTOR rot;
    /* 0x20 */ SVECTOR scale;
    /* 0x28 */ MATRIX local;
    /* 0x48 */ MATRIX *parentMatrix;
    /* 0x4C */ MATRIX world;
    /* 0x6C */ SVECTOR prevPos; /* the pose the motion blends from */
    /* 0x74 */ SVECTOR prevRot;
    /* 0x7C */ SVECTOR prevScale;
} ModelBone;

/* A position or rotation, without the SVECTOR pad */
typedef struct ShortVec3 {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ShortVec3;

/* What drives a Model, owned by whoever created it */
typedef struct ModelControl {
    /* 0x00 */ s32 active; /* in the Models task's list */
    /* 0x04 */ s32 id; /* the Models task's */
    /* 0x08 */ s32 motion; /* the motion to play */
    /* 0x0C */ s32 restart; /* play it again from the start */
    /* 0x10 */ s32 motionDone;
    /* 0x14 */ s32 fighter; /* the Models task's */
    /* 0x18 */ s32 idleMotion;
    /* 0x1C */ ShortVec3 pos;
    /* 0x22 */ ShortVec3 rot;
    /* 0x28 */ ShortVec3 homePos;
    /* 0x2E */ ShortVec3 homeRot;
    /* 0x34 */ struct {
        s32 enabled;
        s32 arg;
        s32 alt;
    } unk34[2];
} ModelControl;

/*
 * A 3D model (func_80083CE0), registered with id 0x11: a tree of bones,
 * each drawn by a Mesh child (children[i] for bone i, children[0] the
 * model's func_8008AC88 task), and the motion it plays, from the archive of
 * motions in motionFile.
 */
typedef struct Model {
    TASK_HEADER(Model);
    /* 0x0050 */ s32 boneCount;
    /* 0x0054 */ ModelBone *bones;
    /* 0x0058 */ u8 unk58[8];
    /* 0x0060 */ s32 unk60;
    /* 0x0064 */ ModelControl *control;
    /* 0x0068 */ Vec2 texPos; /* where its textures go in VRAM */
    /* 0x0070 */ s32 texFile;
    /* 0x0074 */ s32 motionFile;
    /* 0x0078 */ s32 motion;
    /* 0x007C */ s32 motionDone;
    /* 0x0080 */ s32 keyframe;
    /* 0x0084 */ s32 unk84;
    /* 0x0088 */ s32 unk88[2];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s32 unk98;
    /* 0x009C */ s32 unk9C;
    /* 0x00A0 */ s32 keyframeCount;
    /* 0x00A4 */ u16 keyframes[0x640];
    /* 0x0D24 */ s16 unkD24[0x640];
    /* 0x19A4 */ s16 unk19A4[0x640];
    /* 0x2624 */ void (*setMotion)(struct Model *model, s32 motion, s32 restart);
    /* 0x2628 */ s32 (*isMotionDone)(struct Model *model);
    /* 0x262C */ void (*unk262C)();
    /* 0x2630 */ void (*unk2630)();
} Model;

/* The fight stages, the battle's backgrounds: WFIGHTTS lists them as
   MFSTG001-027 */
#if VERSION_US
#define FILE_FIGHT_STAGES 0x1BD
#elif VERSION_EU
#define FILE_FIGHT_STAGES 0x1CB
#endif

/* A table of 0x46-byte entries that start with an s16 id, 0 after the
   last (FIGHTSTG_findBattleTableIndex) */
#if VERSION_US
#define FILE_BATTLE_TABLE 0xBE
#elif VERSION_EU
#define FILE_BATTLE_TABLE 0x1CF
#endif

typedef struct BattleTableEntry {
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 unk2[7];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14[0x32];
} BattleTableEntry;

/* The fighters' file, which D_800A32E0.funcs reads */
#if VERSION_US
#define FILE_FIGHTERS 0x1BE
#elif VERSION_EU
#define FILE_FIGHTERS 0x1CC
#endif

/* A fight stage's lights: three flat lights and the ambient colour */
typedef struct LightSet {
    /* 0x00 */ GsF_LIGHT lights[3];
    /* 0x30 */ s32 ambient[3];
} LightSet;

/* A fight stage, in FILE_FIGHT_STAGES */
typedef struct FightStageInfo {
    /* 0x00 */ s32 model; /* file << 16 | index */
    /* 0x04 */ s32 motions;
    /* 0x08 */ s32 music; /* an index in D_800A1238, or -1 */
    /* 0x0C */ u8 bgColor[3];
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10[8]; /* given to the model's unk2630, up to a 0 */
    /* 0x18 */ LightSet lights;
    /* 0x54 */ s32 unk54;
} FightStageInfo;

/* The fight stage (func_80086128), registered with id 0x15: its model,
   which fades in from black, and its music. setStage fades it out and
   the new one in. */
typedef struct FightStage {
    TASK_HEADER(FightStage);
    /* 0x50 */ s32 stage;
    /* 0x54 */ s32 prevStage;
    /* 0x58 */ ModelControl control;
    /* 0xA4 */ s32 fade; /* 0-0x1000 */
    /* 0xA8 */ s32 fadeStep;
    /* 0xAC */ s32 fadeInTime;
    /* 0xB0 */ s32 fadeOutTime;
    /* 0xB4 */ SVECTOR colorFrom; /* the model's */
    /* 0xBC */ SVECTOR colorTo;
    /* 0xC4 */ SVECTOR color;
    /* 0xCC */ SVECTOR bgFrom; /* layer 0x1000's background */
    /* 0xD4 */ SVECTOR bgTo;
    /* 0xDC */ SVECTOR bg;
    /* 0xE4 */ s16 voice; /* the music's */
    /* 0xE8 */ void (*setStage)(struct FightStage *task, s32 stage, s32 fadeOutTime, s32 fadeInTime);
} FightStage;

/* D_800A3420's functions */
typedef struct Methods800A3420 {
    /* 0x0 */ void (*unk0)();
    /* 0x4 */ void (*lerp)(SVECTOR *from, SVECTOR *to, s32 t, SVECTOR *out); /* t: 0-0x1000 */
} Methods800A3420;

/* The stage lights (func_8008A838), registered with id 0x13: set puts a
   light set, fade goes from one to another in time frames */
typedef struct Lights {
    TASK_HEADER(Lights);
    /* 0x050 */ s32 layerId;
    /* 0x054 */ LightSet current;
    /* 0x090 */ LightSet to;
    /* 0x0CC */ LightSet from;
    /* 0x108 */ s32 t; /* 0-0x1000 */
    /* 0x10C */ s32 tStep; /* per frame */
    /* 0x110 */ void (*set)(struct Lights *task, LightSet *set);
    /* 0x114 */ void (*fade)(struct Lights *task, LightSet *from, LightSet *to, s32 time); /* from: NULL for the current */
    /* 0x118 */ LightSet *(*getStageLights)(struct Lights *task, s32 stage);
} Lights;

/* func_8009A79C's task: moves a ModelControl to a position */
typedef struct MoveTask {
    TASK_HEADER(MoveTask);
    /* 0x50 */ ModelControl *control;
    /* 0x54 */ ShortVec3 from;
    /* 0x5A */ ShortVec3 to;
    /* 0x60 */ s32 t; /* 0-0x1000 */
    /* 0x64 */ s32 tStep;
} MoveTask;

/* An entry of the fighters' file's list */
typedef struct FighterEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ u8 index; /* in the partners' or the enemies' table */
    /* 0x3 */ u8 kind; /* 0x3A and up: an enemy */
} FighterEntry;

/* The fighters' file: offsets from its start */
typedef struct FightersFile {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 entries; /* FighterEntry, up to an id 0 */
    /* 0x8 */ s32 partners; /* 0xC4 bytes each */
    /* 0xC */ s32 enemies; /* 0x48 bytes each */
} FightersFile;

/* A fighter's entry in its file, from D_800A32E0.funcs.getInfo */
typedef struct FighterInfo {
    /* 0x00 */ s32 model;
    /* 0x04 */ s32 motions;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC; /* an offset in the fighters' file */
    /* 0x10 */ s16 unk10; /* its distance from the middle, past 0x1400 */
    /* 0x12 */ u8 unk12[6];
    /* 0x18 */ s16 height;
} FighterInfo;

/* The fighters' file (D_800A32E0.funcs) */
typedef struct FighterInfoFuncs {
    /* 0x0 */ FighterInfo *(*getInfo)(s32 id);
    /* 0x4 */ void (*unk4)(s32 index);
    /* 0x8 */ void (*unk8)(u32 enemy, s32 *min, s32 *max); /* the indices of the partners or the enemies */
} FighterInfoFuncs;

/* D_800A32E0: the last fighter getInfo found, and the fighters' file's
   functions */
typedef struct FighterCache {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ FighterInfo *unk10;
    /* 0x14 */ FighterInfo *info;
    /* 0x18 */ FighterInfoFuncs funcs;
    /* 0x24 */ void (*unk24)();
} FighterCache;

/* The Models task's children: a removed model stays until it is gone */
typedef struct ModelsChildren {
    /* 0x00 */ Model *models[4];
    /* 0x10 */ Model *dying[4];
} ModelsChildren;

/* The fighters' models (func_800877D4), registered with id 0x14: up to four,
   each one with its ModelControl, found by an id */
typedef struct Models {
    TASK_HEADER(Models);
    /* 0x050 */ ModelControl controls[4];
    /* 0x180 */ void (*remove)(struct Models *task, s32 id);
    /* 0x184 */ void (*add)(struct Models *task, s32 id, s32 fighter, s32 arg3);
    /* 0x188 */ ModelControl *(*get)(struct Models *task, s32 id);
    /* 0x18C */ void (*setId)(struct Models *task, s32 id, s32 newId);
    /* 0x190 */ s32 (*getFighter)(struct Models *task, s32 id);
    /* 0x194 */ void (*face)(struct Models *task, s32 id); /* ids under 0x10 are one side */
    /* 0x198 */ void (*setIdleMotion)(struct Models *task, s32 id, s32 motion);
} Models;

/* Tasks whose update is still asm, named after it, with the fields their
   creators set */
typedef struct Unk80087870 {
    TASK_HEADER(Unk80087870);
    /* 0x50 */ u8 unk50[8];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60[0x10];
} Unk80087870;

typedef struct Unk80089FBC {
    TASK_HEADER(Unk80089FBC);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 unk58[0xC];
    /* 0x64 */ void (*unk64)();
} Unk80089FBC;

typedef struct Unk8008C0BC {
    TASK_HEADER(Unk8008C0BC);
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51[0x2F];
} Unk8008C0BC;

typedef struct Unk8008CFFC {
    TASK_HEADER(Unk8008CFFC);
    /* 0x50 */ u8 unk50[0x20];
    /* 0x70 */ s32 unk70;
    /* 0x74 */ u8 unk74[0xC];
} Unk8008CFFC;

typedef struct Unk8008EAF8 {
    TASK_HEADER(Unk8008EAF8);
    /* 0x50 */ u8 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 unk58[0x2C];
} Unk8008EAF8;

typedef struct Unk80090290 {
    TASK_HEADER(Unk80090290);
    /* 0x50 */ u8 unk50[0x24];
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ u8 unk7C[4];
} Unk80090290;

typedef struct Unk80090908 {
    TASK_HEADER(Unk80090908);
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51[0x23];
} Unk80090908;

typedef struct Unk800910C8 {
    TASK_HEADER(Unk800910C8);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 unk58[0x90];
} Unk800910C8;

typedef struct Unk80092350 {
    TASK_HEADER(Unk80092350);
    /* 0x50 */ s32 unk50; /* 0xFF / the frames */
    /* 0x54 */ u8 unk54[4];
} Unk80092350;

typedef struct Unk800937FC {
    TASK_HEADER(Unk800937FC);
    /* 0x50 */ s32 *unk50;
    /* 0x54 */ s32 unk54; /* *unk50, which becomes -1 */
    /* 0x58 */ u8 unk58[0x1C];
} Unk800937FC;

typedef struct Unk800973D4 {
    TASK_HEADER(Unk800973D4);
    /* 0x50 */ s32 *unk50;
    /* 0x54 */ u8 unk54[8];
    /* 0x5C */ s32 unk5C; /* *unk50, which becomes -1 */
    /* 0x60 */ s32 unk60; /* that party member */
    /* 0x64 */ u8 unk64[0x1C];
    /* 0x80 */ s32 unk80;
} Unk800973D4;

/* func_80093324's task */
typedef struct Unk800931CC {
    TASK_HEADER(Unk800931CC);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 *unk54; /* -1 until it is done */
} Unk800931CC;

/* func_8008EAA0's task */
typedef struct Unk8008E3C8 {
    TASK_HEADER(Unk8008E3C8);
    /* 0x50 */ u8 unk50[0x20];
    /* 0x70 */ s8 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ u8 unk78[0xC];
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
} Unk8008E3C8;

/* func_80099400's task */
typedef struct Unk80097F8C {
    TASK_HEADER(Unk80097F8C);
    /* 0x50 */ u8 unk50[0x48];
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 found[3]; /* the fighters FIGHTSTG_findFighters found */
    /* 0xA8 */ s32 foundCount;
    /* 0xAC */ void (*unkAC)();
    /* 0xB0 */ void (*unkB0)(struct Unk80097F8C *task);
} Unk80097F8C;

typedef struct Unk80086180 {
    TASK_HEADER(Unk80086180);
    /* 0x50 */ u8 unk50[0x14];
    /* 0x64 */ s32 unk64;
} Unk80086180;

typedef struct Unk80094278 {
    TASK_HEADER(Unk80094278);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60[0x8C];
} Unk80094278;

typedef struct Unk800967A4 {
    TASK_HEADER(Unk800967A4);
    /* 0x50 */ s32 *unk50; /* -1 until it is done */
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 unk5C[0x2C];
} Unk800967A4;

typedef struct Unk800999E4 {
    TASK_HEADER(Unk800999E4);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 *unk58; /* -1 until it is done */
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 unk64[0x60];
} Unk800999E4;

/* 0x34 bytes that func_80091618 copies */
typedef struct Unk80091618 {
    /* 0x00 */ s32 unk0[13];
} Unk80091618;

/* func_800919EC's task, registered with id 0x12 */
typedef struct Unk800911C8 {
    TASK_HEADER(Unk800911C8);
    /* 0x050 */ s32 unk50;
    /* 0x054 */ Unk80091618 unk54;
    /* 0x088 */ u8 unk88[0x68];
    /* 0x0F0 */ s32 unkF0;
    /* 0x0F4 */ s32 unkF4;
    /* 0x0F8 */ void (*unkF8)(struct Unk800911C8 *task, Unk80091618 *arg1);
    /* 0x0FC */ void (*unkFC)();
    /* 0x100 */ void (*unk100)();
    /* 0x104 */ void (*unk104)();
} Unk800911C8;

/* 32 bytes that func_8009A214 copies into func_8009A098's task */
typedef struct Unk8009A214 {
    /* 0x00 */ s32 unk0[8];
} Unk8009A214;

typedef struct Unk8009A098 {
    TASK_HEADER(Unk8009A098);
    /* 0x50 */ s32 unk50[2];
    /* 0x58 */ Unk8009A214 unk58;
    /* 0x78 */ u8 unk78[0x30];
} Unk8009A098;

/* Which fighters FIGHTSTG_findFighters looks for */
typedef struct FighterFilter {
    /* 0x0 */ s32 side;
    /* 0x4 */ s32 type;
} FighterFilter;

/* The battle script's task (func_8008BD10) */
typedef struct BattleScript {
    TASK_HEADER(BattleScript);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54[0x38];
    /* 0x8C */ s16 *pc;
    /* 0x90 */ u8 unk90[0x24];
} BattleScript;

/* The two text windows of func_80099894's task (its children) */
typedef struct Unk80099894 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ struct TextWindow *unk4;
    /* 0x8 */ struct TextWindow *unk8;
} Unk80099894;

/* An event of the battle, as it is queued (FIGHTSTG_pushEvent) */
typedef struct BattleEvent {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 delay;
    /* 0x08 */ s32 args[6];
} BattleEvent;

/* A queued event: its time counts down to when it runs */
typedef struct QueuedEvent {
    /* 0x00 */ s16 type; /* 0 for a free entry */
    /* 0x02 */ s16 time;
    /* 0x04 */ s32 args[6];
} QueuedEvent;

/* What FIGHTSTG_removeEvents removes the events of */
typedef struct EventKey {
    /* 0x0 */ u8 unk0;
    /* 0x4 */ s32 unk4;
} EventKey;

/* The event queue's functions (D_800A25F0.funcs) */
typedef struct EventQueueFuncs {
    /* 0x00 */ s8 unk0;
    /* 0x04 */ void (*push)(BattleEvent *event);
    /* 0x08 */ void (*pushFirst)(BattleEvent *event); /* before all the others */
    /* 0x0C */ s16 (*unkC)(void);
    /* 0x10 */ s32 (*first)(s32 type);
    /* 0x14 */ s32 (*next)(void);
    /* 0x18 */ s32 (*find)(s32 type, u8 side, s32 fighter);
    /* 0x1C */ void (*remove)(EventKey *key); /* the events whose first two args are its */
} EventQueueFuncs;

/* The battle's events (D_800A25F0) */
typedef struct EventQueue {
    /* 0x000 */ QueuedEvent events[99];
    /* 0xAD4 */ u8 unkAD4[0x1E];
    /* 0xAF2 */ s8 findType; /* what first and next look for, 1-24 */
    /* 0xAF3 */ s8 found; /* the event they found, or -1 */
    /* 0xAF4 */ EventQueueFuncs funcs;
} EventQueue;

/* One of the battle's fighters, three on each side */
typedef struct BattleFighter {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
} BattleFighter;

/* How the battle's frames go by (func_8009D648 sets it) */
typedef struct BattleSpeed {
    /* 0x0 */ s32 mode; /* 1: stopped, 2: slowed (a frame per 4 of time), 3: double */
    /* 0x4 */ s32 rest; /* the time mode 2 hasn't counted yet */
} BattleSpeed;

/* D_800A31E8: the battle */
typedef struct Battle {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 frames; /* since the last update */
    /* 0x08 */ s32 active[2]; /* each side's fighter */
    /* 0x10 */ BattleFighter fighters[2][3];
    /* 0xD0 */ s16 unkD0[4];
    /* 0xD8 */ u8 unkD8[4];
    /* 0xDC */ BattleSpeed speed;
    /* 0xE4 */ s32 (*unkE4)();
    /* 0xE8 */ s32 (*unkE8)();
    /* 0xEC */ s32 (*unkEC)();
    /* 0xF0 */ s32 (*unkF0)();
    /* 0xF4 */ s32 (*unkF4)();
} Battle;

/* An entry of the executable's table at D_800427D6 (0x12 bytes) */
typedef struct Unk800427D6 {
    /* 0x00 */ u8 unk0[2];
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5[5];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD[3];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
} Unk800427D6;

extern Unk800427D6 D_800427D6[];

/* D_800A317C: the command being carried out (?) */
typedef struct BattleAction {
    /* 0x00 */ s16 unk0[0xE];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D[3];
    /* 0x20 */ u8 unk20;
    /* 0x24 */ s32 unk24; /* an entry of D_800427D6 */
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 unk30[4];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x28]; /* by D_800427D6's unkA */
    /* 0x60 */ s32 unk60[2];
    /* 0x68 */ void (*unk68)();
} BattleAction;

/* A side's stats as FIGHTSTG_computeStats works them out */
typedef struct BattleStats {
    /* 0x00 */ s32 unk0[2];
    /* 0x08 */ s16 unk8[0x14];
    /* 0x30 */ u8 unk30[0x10];
} BattleStats;

/* D_800A3308 */
typedef struct Battle800A3308 {
    /* 0x00 */ BattleStats stats[2]; /* the player's, then the enemy's */
    /* 0x80 */ BattleStats *(*unk80)();
    /* 0x84 */ s32 (*unk84)();
    /* 0x88 */ s32 (*unk88)();
    /* 0x8C */ s32 (*unk8C)();
    /* 0x90 */ s32 (*unk90)();
    /* 0x94 */ s32 (*unk94)();
    /* 0x98 */ s32 (*unk98)();
    /* 0x9C */ s32 (*unk9C)();
    /* 0xA0 */ s32 (*unkA0)();
    /* 0xA4 */ s32 (*unkA4)();
    /* 0xA8 */ s32 (*unkA8)();
    /* 0xAC */ s32 (*unkAC)();
    /* 0xB0 */ s32 (*unkB0)();
    /* 0xB4 */ s32 (*unkB4)();
    /* 0xB8 */ s32 (*unkB8)();
    /* 0xBC */ s32 (*unkBC)();
    /* 0xC0 */ s32 (*unkC0)();
    /* 0xC4 */ s32 (*unkC4)();
    /* 0xC8 */ s32 (*unkC8)();
    /* 0xCC */ s32 (*unkCC)();
#if VERSION_EU
    /* 0xD0 */ s32 (*unkEU)(); /* func_800A15A8 */
#endif
    /* the European version's offsets are 4 more from here */
    /* 0xD0 */ s32 (*unkD0)();
    /* 0xD4 */ s32 (*unkD4)();
    /* 0xD8 */ s32 (*unkD8)();
    /* 0xDC */ s32 (*unkDC)();
    /* 0xE0 */ s32 (*unkE0)();
    /* 0xE4 */ s32 (*unkE4)();
    /* 0xE8 */ s32 (*unkE8)();
} Battle800A3308;

/* Shared between the overlay's objects */
extern Battle D_800A31E8;
extern BattleAction D_800A317C;
extern FighterCache D_800A32E0;
extern Battle800A3308 D_800A3308;
extern s32 D_800A1238[];
extern Methods800A3420 D_800A3420;
void func_800831D4(Model *model, s32 motion, s32 restart);
void func_8008358C(Model *model, Task **children);
void func_80083BE4();
void func_80083C78();
s32 func_80083CD4(Model *model);
Model *func_80083F44(s32 file, s32 motionFile, Vec2 texPos, ModelControl *control);
void func_80084890();
void func_800850D8();
void func_80085A84(FightStage *task, Model **children);
void func_8008A270(Lights *task);
void func_8008A61C(Lights *task, LightSet *set);
void func_8008A690(Lights *task, LightSet *from, LightSet *to, s32 time);
LightSet *func_8008A7EC(Lights *task, s32 stage);
void func_8009A638(MoveTask *task);
FighterInfo *FIGHTSTG_getFighterInfo(s32 id);
void FIGHTSTG_cacheFighter(s32 index);
void FIGHTSTG_getFighterRange(u32 enemy, s32 *min, s32 *max);
extern Vec2 D_800A12D0[];
extern EventQueue D_800A25F0;
extern BattleEvent D_800A34E0;
extern BattleTableEntry *(*D_800A2584)(s32 id);
void FIGHTSTG_pushEvent(BattleEvent *event);
void FIGHTSTG_pushEventFirst(BattleEvent *event);
s16 func_8009AB90(void);
s32 FIGHTSTG_findEventFrom(s32 start);
s32 FIGHTSTG_findFirstEvent(s32 type);
s32 FIGHTSTG_findNextEvent(void);
s32 FIGHTSTG_findEvent(s32 type, u8 side, s32 fighter);
void FIGHTSTG_removeEvents(EventKey *key);

void func_80087330(Models *task);
s32 func_80087378(Models *task, s32 id);
s32 func_800873BC(Models *task);
void func_800873F0(Models *task, s32 id);
void func_80087480(Models *task, s32 id, s32 fighter, s32 arg3);
ModelControl *func_800875A8(Models *task, s32 id);
void func_800875FC(Models *task, s32 id, s32 newId);
s32 func_80087664(Models *task, s32 id);
void func_800876B8(Models *task, s32 id);
void func_800877A4(Models *task, s32 id, s32 motion);
Model *func_80083F10(s32 file, s32 motionFile, Vec2 texPos, ModelControl *control);
void func_800867F0();
void func_8008690C();
void func_80087CE4();
void func_8008BD10();
void func_80090098();
void func_80092E0C();
void func_800933EC();
void func_800A1048();
void func_800A1FE0();
void func_80091A58();
void func_8009D8B4();
void func_800973D4();
void func_80087870();
void func_8008A188();
void func_80089FBC();
void func_80089458();
void func_8008EAF8();
void func_80090290();
void func_800910C8();
void func_80092350();
void func_800937FC();
void func_8008C0BC();
void func_8008CFFC();
void func_80090908();
Unk800973D4 *func_80097B74(s32 *arg0);
void func_80094D04();
void func_80095AC0();
void func_8009C294();
void func_8009C330();
void func_8009C418();
void func_8009C500();
void func_8009C764();
void func_8009C998();
void func_8009CA84();
void func_8009CB4C();
void func_8009CBEC();
void func_8009CCD4();
void func_8009CDCC();
void func_8009C8EC();
extern u8 D_8004276E;
void func_8009BD20();
void func_80097C14();
void func_80097D74();
void func_80098808();
void func_800931CC();
void func_8008E3C8();
s32 func_8009AEA4();
s32 FIGHTSTG_findBattleTableIndex(s32 id);
BattleTableEntry *FIGHTSTG_getBattleTableEntry(s32 id);
void func_80094278();
void func_800967A4();
void func_800999E4();
void func_800911C8();
void func_80091688();
void func_80091788();
void func_80091950();
void func_80086180();
void func_8009245C(Unk80092350 *task, s32 frames);
Unk80092350 *func_80092494(s32 frames);
void func_8009A098();
BattleStats *FIGHTSTG_computeStats();
extern s32 D_800A33F4[];
#endif /* FIGHTSTG_H */
