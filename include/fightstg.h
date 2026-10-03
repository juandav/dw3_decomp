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

/* A fighter's entry in its file, from D_800A32F8.getInfo */
typedef struct FighterInfo {
    /* 0x00 */ s32 model;
    /* 0x04 */ s32 motions;
    /* 0x08 */ u8 unk8[8];
    /* 0x10 */ s16 unk10; /* its distance from the middle, past 0x1400 */
    /* 0x12 */ u8 unk12[6];
    /* 0x18 */ s16 height;
} FighterInfo;

/* The fighters' file (D_800A32F8) */
typedef struct FighterInfoFuncs {
    /* 0x0 */ FighterInfo *(*getInfo)(s32 id);
    /* 0x4 */ void (*unk4)(s32 index);
    /* 0x8 */ void (*unk8)(s32 kind, s32 *min, s32 *max);
} FighterInfoFuncs;

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

/* An event of the battle, as it is queued (func_8009AA7C) */
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

/* The battle's events (D_800A25F0) */
typedef struct EventQueue {
    /* 0x000 */ QueuedEvent events[99];
    /* 0xAD4 */ u8 unkAD4[0x1E];
    /* 0xAF2 */ s8 findType; /* what first and next look for, 1-24 */
    /* 0xAF3 */ s8 found; /* the event they found, or -1 */
} EventQueue;

/* What func_8009AE44 removes the events of */
typedef struct EventKey {
    /* 0x0 */ u8 unk0;
    /* 0x4 */ s32 unk4;
} EventKey;

/* The event queue's functions (D_800A30E4) */
typedef struct EventQueueFuncs {
    /* 0x00 */ s8 unk0;
    /* 0x04 */ void (*push)(BattleEvent *event);
    /* 0x08 */ void (*pushFirst)(BattleEvent *event); /* before all the others */
    /* 0x0C */ s16 (*unkC)(void);
    /* 0x10 */ s8 (*first)(s32 type);
    /* 0x14 */ s8 (*next)(void);
    /* 0x18 */ s8 (*find)(s32 type, s32 arg0, s32 arg1);
    /* 0x1C */ void (*remove)(EventKey *key); /* the events whose first two args are its */
} EventQueueFuncs;

/* Shared between the overlay's objects */
extern s32 D_800A1238[];
extern s32 D_800A31EC;
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
FighterInfo *func_8009DACC(s32 id);
void func_8009DC14(s32 index);
void func_8009DD18(s32 kind, s32 *min, s32 *max);
extern FighterInfoFuncs D_800A32F8;
extern Vec2 D_800A12D0[];
extern EventQueue D_800A25F0;
extern EventQueueFuncs D_800A30E4;
extern BattleEvent D_800A34E0;
void func_8009AA7C(BattleEvent *event);
void func_8009AB1C(BattleEvent *event);
s16 func_8009AB90(void);
s32 func_8009ACA8(s32 start);
s8 func_8009AD14(s32 type);
s8 func_8009AD54(void);
s8 func_8009AD94(s32 type, s32 arg0, s32 arg1);
void func_8009AE44(EventKey *key);

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
#endif /* FIGHTSTG_H */
