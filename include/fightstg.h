#ifndef FIGHTSTG_H
#define FIGHTSTG_H

/* FIGHTSTG.PRO: the battle. It loads WFIGHTMN (file 0x1FA) for a normal
   battle, or WFIGHTTS (file 0x1FB) for the battle test, at STAGE_VRAM. */

#include "game.h"
#include <libgs.h>
#include "dw3/menus.h"
#include "dw3/files.h"

extern MATRIX D_8004D3C8; /* the identity, the root bone's parent */

/* The sub-overlays (func_800867F0) and their entry points */
#if VERSION_US
#define FILE_WFIGHTMN 0x1FA
#define FILE_WFIGHTTS 0x1FB
#elif VERSION_EU
#define FILE_WFIGHTMN 0x208
#define FILE_WFIGHTTS 0x209
#endif
Task *WFIGHTMN_start(void);
Task *WFIGHTTS_start(void);
struct BattleTask *func_800A9040(u8 actor, s32 id);

/* The images of a Digimon's change (func_80089458): entry 5 */
#if VERSION_EU
#define FILE_CHANGE 0x8A2
#elif VERSION_US
#define FILE_CHANGE 0x891
#endif

/* What fighter 0x1D2's entrance (func_80086180) loads */
#if VERSION_EU
#define FILE_ENTRANCE_1D2 0x6E2
#elif VERSION_US
#define FILE_ENTRANCE_1D2 0x6D3
#endif

/* Draws one bone of a Model (func_8008588C), from the parts of an archive */
typedef struct Mesh {
    TASK_HEADER(Mesh);
    /* 0x50 */ s32 unk50; /* drawn without the bounds check */
    /* 0x54 */ s32 colorMode; /* Model.setColor's */
    /* 0x58 */ CVECTOR color;
    /* 0x5C */ s32 archive;
    /* 0x60 */ u8 *unk60;
    /* 0x64 */ u8 *unk64;
    /* 0x68 */ u8 *unk68;
    /* 0x6C */ u8 *unk6C; /* 9 ShortVec3 points of its bounds (func_80084780) */
    /* 0x70 */ Vec2 texPos;
    /* 0x78 */ s32 *screen; /* where its vertices land on screen */
    /* 0x7C */ s32 *depth; /* and their depths in the ordering table */
    /* 0x80 */ CVECTOR *colors; /* its normals' colors under the lights */
    /* 0x84 */ MATRIX matrix;
    /* 0xA4 */ void (*draw)(struct Mesh *mesh, s32 layerId, MATRIX *matrix);
    /* 0xA8 */ void (*drawAlt)(struct Mesh *mesh, s32 layerId, MATRIX *matrix);
} Mesh;

/* A Mesh's drawing state while its drawer (func_80084890) walks its command
   bytes: a high nibble of 8 to 14 sets one of the flags, a low nibble of 1
   the texture page and CLUT, 2 to 5 one of the flat colors, and 0 starts a
   run of polygons, each a 0 byte then its vertices' indices, its normals'
   indices when lit and its UVs when textured. 0xFF ends the commands. */
typedef struct MeshDrawState {
    /* 0x00 */ s32 textured;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 quad;
    /* 0x10 */ s32 lit;
    /* 0x14 */ s32 gouraud;
    /* 0x18 */ s32 abr; /* the semi-transparency mode + 1, 0 for opaque */
    /* 0x1C */ u8 *cmd;
    /* 0x20 */ s32 *screen;
    /* 0x24 */ s32 *depth;
    /* 0x28 */ u_long *otBase;
    /* 0x2C */ CVECTOR *normalColors;
    /* 0x30 */ Vec2 texPos;
    /* 0x38 */ s32 u;
    /* 0x3C */ s32 v;
    /* 0x40 */ u16 tpage;
    /* 0x42 */ u16 clut;
    /* 0x44 */ CVECTOR color[4];
    /* 0x54 */ union {
        void *ptr;
        POLY_FT3 *ft3;
        POLY_FT4 *ft4;
        POLY_GT3 *gt3;
        POLY_GT4 *gt4;
        LINE_F2 *lineF2;
        LINE_F4 *lineF4;
    } prim;
    /* 0x58 */ s32 sxy[4]; /* the polygon's screen points */
    /* 0x68 */ u_long *ot;
    /* 0x6C */ u8 uv[4][2];
    /* 0x74 */ CVECTOR colors[4]; /* the polygon's vertex colors */
    /* 0x84 */ s32 unk84;
} MeshDrawState;

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

/* A motion in the motions' archive: its keyframes, step by step */
typedef struct MotionStep {
    /* 0x0 */ s16 index; /* 0x7FFF ends them */
    /* 0x2 */ s16 count; /* frames, 0 for the last one */
    /* 0x4 */ s16 frame;
    /* 0x6 */ s16 unk6; /* 0: blend to the next one */
} MotionStep;

/*
 * A 3D model (func_80083CE0), registered with id 0x11: a tree of bones,
 * each drawn by a Mesh child (children[i] for bone i, children[0] the
 * model's face, FIGHTSTG_createFace), and the motion it plays, from the
 * archive of motions in motionFile.
 */
typedef struct Model {
    TASK_HEADER(Model);
    /* 0x0050 */ s32 boneCount;
    /* 0x0054 */ ModelBone *bones;
    /* 0x0058 */ SVECTOR move; /* moves the root bone, along its rotation */
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
    /* 0x0D24 */ u16 unkD24[0x640];
    /* 0x19A4 */ u16 unk19A4[0x640];
    /* 0x2624 */ void (*setMotion)(struct Model *model, s32 motion, s32 restart);
    /* 0x2628 */ s32 (*isMotionDone)(struct Model *model);
    /* 0x262C */ void (*setColor)(); /* (model, mode, color): its meshes' */
    /* 0x2630 */ void (*unk2630)();
} Model;

/* A battle effect that is a model (func_80088FC4): D_800A12F0 lists them,
   ending with id 0 */
typedef struct EffectModelEntry {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 file; /* the model's file and index */
    /* 0x8 */ s32 motionFile;
} EffectModelEntry;

/* Shows an effect's model at a place until its motion ends
   (func_80088FC4) */
typedef struct EffectModel {
    TASK_HEADER(EffectModel);
    /* 0x50 */ s32 effect; /* 0 if it has no entry */
    /* 0x54 */ s32 file;
    /* 0x58 */ s32 motionFile;
    /* 0x5C */ SVECTOR pos;
    /* 0x64 */ SVECTOR rot;
    /* 0x6C */ Vec2 texPos;
    /* 0x74 */ ModelControl control;
} EffectModel;

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

/* What an enemy does: its target (func_800888C8) when the condition holds */
typedef struct BattleTableAction {
    /* 0x0 */ u8 target;
    /* 0x1 */ u8 condition;
    /* 0x2 */ s16 conditionArg;
} BattleTableAction;

typedef struct BattleTableEntry {
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 item; /* what the enemy may leave */
    /* 0x04 */ s16 itemChance; /* in 1024ths, less one */
    /* 0x06 */ s16 nameId; /* string in file 0x4F */
    /* 0x08 */ s16 unk8[3];
    /* 0x0E */ s16 stats[5]; /* scaled by the enemy's unkA / 16 */
    /* 0x18 */ s16 resist[12];
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ BattleTableAction actions[3]; /* the first whose condition holds (func_800883AC) */
    /* 0x3E */ u8 unk3E[4];
    /* 0x42 */ BattleTableAction counter; /* its counterattack (func_8008E3C8) */
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
    /* 0x8 */ s32 (*ease)(s32 curve, s32 t, s32 value); /* value scaled by a curve of t */
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
    /* 0x0C */ s32 face; /* its FaceRects: an offset in the fighters' file */
    /* 0x10 */ s16 unk10; /* its distance from the middle, past 0x1400 */
    /* 0x12 */ u8 unk12[6];
    /* 0x18 */ s16 height;
    /* 0x1A */ ShortVec3 camPos[12]; /* the cameras that look at it; an enemy
                                        has 3 of each and then their count */
    /* 0x62 */ ShortVec3 camRef[12];
    /* 0xAA */ s16 camProj[12];
} FighterInfo;

/* An enemy's FighterInfo: it has 3 cameras where a partner has 12 */
typedef struct FighterInfoEnemy {
    /* 0x00 */ u8 unk0[0x1A];
    /* 0x1A */ ShortVec3 camPos[3];
    /* 0x2C */ ShortVec3 camRef[3];
    /* 0x3E */ s16 camProj[3];
    /* 0x44 */ s16 cameraCount;
} FighterInfoEnemy;

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
    /* 0x24 */ struct FaceRect *(*getFace)(s32 fighter); /* up to an x of 0xFF */
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

/* A part of a fighter's face (its eyes, then up to 14 more) and where its
   three frames are in its texture: copied into place by a DR_MOVE */
typedef struct FaceRect {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 w; /* 0: unused */
    /* 0x3 */ u8 h;
    /* 0x4 */ u8 frames[3][2];
} FaceRect;

typedef struct FacePart {
    /* 0x00 */ s32 used;
    /* 0x04 */ s32 frame; /* the one drawn */
    /* 0x08 */ FaceRect rect;
} FacePart;

/* A model's face (FIGHTSTG_createFace, the model's first child): the eyes
   blink (or close for some motions) and the other parts loop their frames */
typedef struct Face {
    TASK_HEADER(Face);
    /* 0x050 */ Model *model;
    /* 0x054 */ Vec2 texPos; /* the model's */
    /* 0x05C */ s32 partCount;
    /* 0x060 */ FacePart parts[16];
    /* 0x1A0 */ s32 blinkTimer;
    /* 0x1A4 */ s32 time;
} Face;

/* A fighter's camera (FIGHTSTG_createCamera) on layer 0x1009, from its
   FighterInfo; frames counts the frames it still has to be set */
typedef struct FighterCamera {
    TASK_HEADER(FighterCamera);
    /* 0x50 */ s32 fighter;
    /* 0x54 */ ModelControl *control;
    /* 0x58 */ GsRVIEW2 view;
    /* 0x78 */ s32 proj; /* the projection distance */
    /* 0x7C */ GsCOORDINATE2 coord; /* the view's */
    /* 0xCC */ SVECTOR rot;
    /* 0xD4 */ VECTOR trans;
    /* 0xE4 */ s32 frames;
} FighterCamera;

/* The jump heights and speeds (t per frame) of the Jump kinds 1-6 */
typedef struct JumpParams {
    /* 0x0 */ s32 height;
    /* 0x4 */ s32 speed;
} JumpParams;

/* A ModelControl's jump (FIGHTSTG_startJump): up and down from its y, or
   for kinds 4 and 5 also forwards from or back to its home */
typedef struct Jump {
    TASK_HEADER(Jump);
    /* 0x50 */ s32 kind;
    /* 0x54 */ s32 distance; /* kind 4: past 0x2800 */
    /* 0x58 */ s32 dist;
    /* 0x5C */ ModelControl *control;
    /* 0x60 */ s32 height;
    /* 0x64 */ s32 y;
    /* 0x68 */ s32 speed;
    /* 0x6C */ s32 t; /* 0-0x1000 */
} Jump;

/* A battle sound (FIGHTSTG_playBattleSound) that is keyed off after time */
typedef struct BattleSound {
    TASK_HEADER(BattleSound);
    /* 0x50 */ s32 sound;
    /* 0x54 */ s32 voice;
    /* 0x58 */ s32 time;
} BattleSound;

/* A sprite sheet for the battle's 2D effects: an archive of animations,
   the sheet and where its texture goes in VRAM */
typedef struct EffectSheet {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 sheet;
    /* 0x8 */ Vec2 texPos;
} EffectSheet;

/* A 2D effect: its sheet in D_800A1914 and its animations, an archive of
   SpriteAnim data; the list (D_800A1C44) ends with an id of -1 */
typedef struct SpriteEffectEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 sheet;
    /* 0x4 */ s32 file;
} SpriteEffectEntry;

/* A 2D effect (FIGHTSTG_startSpriteEffect): a SpriteAnim per animation, killed when
   they all are */
typedef struct SpriteEffect {
    TASK_HEADER(SpriteEffect);
    /* 0x50 */ s32 effect; /* -1: not found */
    /* 0x54 */ s32 sheet;
    /* 0x58 */ s32 file;
    /* 0x5C */ SVECTOR pos;
    /* 0x64 */ s32 count;
} SpriteEffect;

/* One animation of a 2D effect (FIGHTSTG_createSpriteAnim), drawn by a layer callback.
   Its data: flags, stride and duration, the 9 values of the first frame,
   then per frame the values whose bit is set in flags. */
typedef struct SpriteAnim {
    TASK_HEADER(SpriteAnim);
    /* 0x50 */ s16 *data;
    /* 0x54 */ SVECTOR pos; /* vz 0x7FFF: on screen in front, -1: on screen */
    /* 0x5C */ s32 sheet;
    /* 0x60 */ Vec2 texPos;
    /* 0x68 */ s32 layerId;
    /* 0x6C */ s32 time;
    /* 0x70 */ s32 flags;
    /* 0x74 */ s32 stride; /* of a frame's values */
    /* 0x78 */ s32 duration;
    /* 0x7C */ s16 frame;
    /* 0x7E */ s16 clutRow;
    /* 0x80 */ s16 x;
    /* 0x82 */ s16 y;
    /* 0x84 */ union {
        s16 v[2]; /* x, y; 0x1000 = 1.0 */
        s32 both; /* to test the two at once */
    } scale;
    /* 0x88 */ union {
        s16 v[2]; /* x, y */
        s32 both;
    } rot;
    /* 0x8C */ s16 rotZ;
} SpriteAnim;

/* Tasks whose update is still asm, named after it, with the fields their
   creators set */
typedef struct Unk80087870 {
    TASK_HEADER(Unk80087870);
    /* 0x50 */ struct Models *models;
    /* 0x54 */ struct BattleCamera *camera;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 sheet; /* its file in the high half */
    /* 0x68 */ Vec2 texPos;
} Unk80087870;

/* func_8008C0BC's task (func_8008C8B8): a side's first technique */
typedef struct Unk8008C0BC {
    TASK_HEADER(Unk8008C0BC);
    /* 0x50 */ u8 unk50; /* the side that uses it, 0 or 0x10 */
    /* 0x54 */ s32 tech;
    /* 0x58 */ s32 damage;
    /* 0x5C */ s32 unk5C; /* whether the other side's fighter had flag 8 */
    /* 0x60 */ s32 lines[8]; /* func_80097F8C's */
} Unk8008C0BC;

/* func_8008CFFC's task: an item used in battle, func_8008C8F0 its script */
typedef struct Unk8008CFFC {
    TASK_HEADER(Unk8008CFFC);
    /* 0x50 */ s32 lines[8]; /* func_80097F8C's, 0 ends them */
    /* 0x70 */ s32 unk70; /* the item */
    /* 0x74 */ s32 unk74; /* item 0x54's element, 2-8 */
    /* 0x78 */ s32 unk78; /* the damage */
    /* 0x7C */ s32 unk7C; /* item 0x58's: 1 it lowered the enemy's first stat, 2 its second */
} Unk8008CFFC;

/* An item's script settings (D_800A210C, ended by -1) */
typedef struct ItemScript {
    /* 0x0 */ s16 item;
    /* 0x2 */ s16 unk6C; /* BattleScript's */
    /* 0x4 */ s16 sound;
} ItemScript;

typedef struct Unk8008EAF8 {
    TASK_HEADER(Unk8008EAF8);
    /* 0x50 */ u8 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 unk58[0x2C];
} Unk8008EAF8;

/* func_80090290's task (func_800908C0): an attack on the player's active
   fighter, as state unk74 + 1 */
typedef struct Unk80090290 {
    TASK_HEADER(Unk80090290);
    /* 0x50 */ s32 lines[4]; /* func_80097F8C's */
    /* 0x60 */ s32 unk60; /* call func_800A9840 once the motion starts */
    /* 0x64 */ u8 unk64[0xC];
    /* 0x70 */ s32 unk70; /* the technique */
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78; /* don't knock the fighter out at 0 HP */
    /* 0x7C */ s32 unk7C; /* the fighter had flag 8 */
} Unk80090290;

typedef struct Unk80090908 {
    TASK_HEADER(Unk80090908);
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51[0x23];
} Unk80090908;


typedef struct Unk80092350 {
    TASK_HEADER(Unk80092350);
    /* 0x50 */ s32 unk50; /* 0xFF / the frames */
    /* 0x54 */ s32 level; /* added to the screen (white), 0-0xFF */
} Unk80092350;

/* A number that eases from one value to another (func_80092660) */
typedef struct HpTween {
    /* 0x00 */ s32 from;
    /* 0x04 */ s32 to;
    /* 0x08 */ s32 value; /* the one shown */
    /* 0x0C */ s16 active;
    /* 0x0E */ s16 fighter; /* whose hp it is */
    /* 0x10 */ s16 time;
    /* 0x12 */ s16 duration;
} HpTween;

/* func_80093058's task: the names and the hp of the fighters out */
typedef struct HpDisplay {
    TASK_HEADER(HpDisplay);
    /* 0x50 */ s32 shown[2]; /* the fighters the names are of */
    /* 0x58 */ HpTween hp[2]; /* each side's */
    /* 0x80 */ s32 timer;
    /* 0x84 */ s32 interval; /* how often the hp is checked */
} HpDisplay;

/* The player's turn (func_80091A58, id 0xE): the battle menu, then the
   menus of its commands */
typedef struct Unk80091A58 {
    TASK_HEADER(Unk80091A58);
    /* 0x50 */ s32 command; /* the battle menu's choice */
    /* 0x54 */ s32 unk54; /* func_80096C8C's */
    /* 0x58 */ s32 result; /* the open menu's, -1 until it is done and -2 to go back */
    /* 0x5C */ s32 action; /* what the turn does */
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68; /* func_80097BEC's */
} Unk80091A58;

typedef struct Unk800937FC {
    TASK_HEADER(Unk800937FC);
    /* 0x50 */ s32 *unk50;
    /* 0x54 */ s32 unk54; /* *unk50, which becomes -1: a partner */
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s16 ids[4]; /* the partner, then its slots of 3 or more */
    /* 0x68 */ s32 count;
    /* 0x6C */ s16 slots[4]; /* GAME.funcs.getPartnerSlots's */
} Unk800937FC;

/* A partner's entry in its slot, as GAME.funcs.getPartnerEntry gives it */
typedef struct BattlePartnerEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ s16 unk4[2];
    /* 0x8 */ s16 techs[6]; /* the low 13 bits, 0x4000 for one it can pass on */
} BattlePartnerEntry;

/* func_8009619C's task: a menu of techniques, six a page */
typedef struct Unk80095AC0 {
    TASK_HEADER(Unk80095AC0);
    /* 0x50 */ s32 *unk50; /* -1 until it is done */
    /* 0x54 */ s32 sel; /* the cursor's line last frame */
    /* 0x58 */ s16 slots[4]; /* GAME.funcs.getPartnerSlots's */
    /* 0x60 */ BattlePartnerEntry entries[3];
    /* 0x9C */ s32 techs[12]; /* ids in the low 13 bits, from 1 */
    /* 0xCC */ s32 count;
    /* 0xD0 */ s32 page;
    /* 0xD4 */ s32 pageCount;
} Unk80095AC0;

/* The battle's item menu (func_80094D04): the usable items, seven a page */
typedef struct ItemMenu {
    TASK_HEADER(ItemMenu);
    /* 0x050 */ s32 *unk50; /* -1 until it is done, then the item or -2 */
    /* 0x054 */ s32 sel; /* the cursor's line last frame */
    /* 0x058 */ s16 items[0x194]; /* ITEM_FUNCS->list's */
    /* 0x380 */ s16 *usable; /* the items with flag 2 */
    /* 0x384 */ s32 count;
    /* 0x388 */ s32 page;
    /* 0x38C */ s32 pageCount;
} ItemMenu;

/* func_80094D04's children */
typedef struct ItemMenuWindows {
    /* 0x00 */ struct Unk8009A098 *cursor;
    /* 0x04 */ TextWindow *unk4;
    /* 0x08 */ TextWindow *unk8;
    /* 0x0C */ TextWindow *unkC;
    /* 0x10 */ TextWindow *count; /* how many of the item */
    /* 0x14 */ TextWindow *message; /* its description */
    /* 0x18 */ TextWindow *names[7];
} ItemMenuWindows;

typedef struct Unk800973D4 {
    TASK_HEADER(Unk800973D4);
    /* 0x50 */ s32 *unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C; /* *unk50, which becomes -1 */
    /* 0x60 */ s32 unk60; /* that party member */
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s16 ids[4]; /* the partner, then its slots of 3 or more */
    /* 0x70 */ s32 count;
    /* 0x74 */ s16 slots[4]; /* GAME.funcs.getPartnerSlots's */
    /* 0x7C */ s32 tech; /* from 1, 0 for none */
    /* 0x80 */ s32 *unk80; /* gets the technique picked */
} Unk800973D4;

/* func_800973D4's children */
typedef struct Unk800973D4Windows {
    /* 0x00 */ struct Unk8009A098 *cursor;
    /* 0x04 */ struct Unk8009A098 *techCursor;
    /* 0x08 */ struct Unk80094278 *unk8; /* the two take turns */
    /* 0x0C */ struct Unk80094278 *unkC;
    /* 0x10 */ TextWindow *names[4];
    /* 0x20 */ TextWindow *unk20[5];
    /* 0x34 */ TextWindow *mp[4]; /* "MP", the active fighter's, "/", its max */
} Unk800973D4Windows;

/* An entry of the executable's technique table (D_800427E8, from 1) */
typedef struct BattleTech {
    /* 0x00 */ u16 mp; /* its cost */
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ u8 icon; /* a frame of the menu sprites, from 0x37 */
    /* 0x05 */ u8 unk5[0xD];
} BattleTech;
extern BattleTech D_800427E8[];

/* func_80093324's task */
typedef struct Unk800931CC {
    TASK_HEADER(Unk800931CC);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 *unk54; /* -1 until it is done */
} Unk800931CC;

/* func_800931CC's children: a cursor over six lines */
typedef struct Unk800931CCWindows {
    /* 0x00 */ struct Unk8009A098 *cursor;
    /* 0x04 */ TextWindow *lines[6];
} Unk800931CCWindows;

/* Shows the partner's model on layer 0x1009 (func_800935F4), through
   the two FighterCamera children, a new one each time it is set up */
typedef struct Unk800933EC {
    TASK_HEADER(Unk800933EC);
    /* 0x50 */ Layer *layer;
    /* 0x54 */ s32 unk54;
} Unk800933EC;

/* func_8008EAA0's task */
typedef struct Unk8008E3C8 {
    TASK_HEADER(Unk8008E3C8);
    /* 0x50 */ s32 lines[8]; /* func_80097F8C's */
    /* 0x70 */ u8 unk70; /* the side that counters, 0 or 0x10 */
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 tech;
    /* 0x7C */ s32 hit; /* whether the technique hits (D_800A3308.unk9C) */
    /* 0x80 */ s32 damage;
    /* 0x84 */ s32 unk84; /* when set, a knockout doesn't call func_8009C054 */
    /* 0x88 */ s32 unk88;
} Unk8008E3C8;

/* func_80088380's task */
typedef struct Unk80087CE4 {
    TASK_HEADER(Unk80087CE4);
    /* 0x50 */ s32 lines[10]; /* func_80097F8C's, 0 ends them */
    /* 0x78 */ s32 target; /* -2 to -4 for an enemy, else any but the active one */
    /* 0x7C */ s32 unk7C;
} Unk80087CE4;

/* func_80099400's task */
typedef struct Unk80097F8C {
    TASK_HEADER(Unk80097F8C);
    /* 0x50 */ s32 unk50[9]; /* what unkAC goes through, 0 ends them */
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78; /* the window being shown */
    /* 0x7C */ s32 unk7C; /* how many */
    /* 0x80 */ s32 unk80; /* the time between them */
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90; /* the arrow's palette, 0-4 */
    /* 0x94 */ s32 unk94; /* when it last changed */
    /* 0x98 */ s32 unk98; /* show the arrow */
    /* 0x9C */ s32 found[3]; /* the fighters FIGHTSTG_findFighters found */
    /* 0xA8 */ s32 foundCount;
    /* 0xAC */ void (*unkAC)();
    /* 0xB0 */ void (*unkB0)(struct Unk80097F8C *task);
} Unk80097F8C;

/* func_80090264's task: two func_80099400 messages around WFIGHTMN's
   func_800A9040, then the battle goes on (func_8009B5F8) */
typedef struct Unk80090098 {
    TASK_HEADER(Unk80090098);
    /* 0x50 */ s32 lines[8]; /* func_80097F8C's, 0 ends them */
} Unk80090098;

/* func_80097F8C's children: the lines it shows one by one */
typedef struct Unk80097F8CWindows {
    /* 0x0 */ TextWindow *lines[2];
} Unk80097F8CWindows;

/* What func_80097F8C's messages say, for some of their types */
typedef struct BattleMessage {
    /* 0x0 */ u8 side;
    /* 0x4 */ s32 kind;
    /* 0x8 */ s32 value;
} BattleMessage;

/* A partner Digimon's change (func_80089F74): key1 the new Digimon, key2 the
   side. The stage and two clipped layers wipe the scene away and back. */
typedef struct Unk80089458 {
    TASK_HEADER(Unk80089458);
    /* 0x50 */ struct Models *models;
    /* 0x54 */ struct BattleCamera *camera;
    /* 0x58 */ struct FightStage *stage;
    /* 0x5C */ s32 idleMotion; /* the old Digimon's */
    /* 0x60 */ RECT clip0; /* layer 0x1004's */
    /* 0x68 */ RECT clip1; /* layer 0x1003's */
    /* 0x70 */ s32 file; /* the new Digimon's model's */
} Unk80089458;

typedef struct Unk80089458Children {
    /* 0x00 */ struct Unk80092350 *fade;
    /* 0x04 */ Task *unk4;
    /* 0x08 */ struct SpriteEffect *effects[4];
} Unk80089458Children;

/* A shot of func_8008690C's camera */
typedef struct CameraShot {
    /* 0x0 */ s16 time; /* -1 ends the list */
    /* 0x2 */ s16 substate;
} CameraShot;

/* A camera (func_80087304) that goes through lists of shots (D_800A1258), the
   next list picked at random (D_800A12B8) */
typedef struct Unk8008690C {
    TASK_HEADER(Unk8008690C);
    /* 0x50 */ struct BattleCamera *camera;
    /* 0x54 */ struct CameraView *view;
    /* 0x58 */ struct Models *models;
    /* 0x5C */ s16 list;
    /* 0x5E */ s16 shot;
    /* 0x60 */ s16 ry; /* where the turn of substate 1 is */
    /* 0x62 */ s16 turned;
    /* 0x64 */ s32 time;
    /* 0x68 */ s32 speed;
} Unk8008690C;

/* A fighter's entrance (func_80086780): key1 its Digimon, key2 its side */
typedef struct Unk80086180 {
    TASK_HEADER(Unk80086180);
    /* 0x50 */ s32 done;
    /* 0x54 */ struct Models *models;
    /* 0x58 */ struct BattleCamera *camera;
    /* 0x5C */ struct FightStage *stage;
    /* 0x60 */ s32 file; /* its model's */
    /* 0x64 */ s32 unk64;
} Unk80086180;

typedef struct Unk80094278 {
    TASK_HEADER(Unk80094278);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54; /* the partner */
    /* 0x58 */ s32 unk58; /* what it shows: 0 the stats, 1 and 2 techniques */
    /* 0x5C */ s32 unk5C; /* the slot, from 1, or 0 for the partner itself */
    /* 0x60 */ s32 unk60; /* shown as a number, or text 0x1A when negative */
    /* 0x64 */ s16 stats[0x16]; /* shown up to 999 */
    /* 0x90 */ s16 slots[4]; /* GAME.funcs.getPartnerSlots's */
    /* 0x98 */ BattlePartnerEntry entries[3];
    /* 0xD4 */ s32 techs[6]; /* a technique in the low 13 bits */
} Unk80094278;

/* A line of func_80093E4C's stat list (D_800A2294): where its number goes and
   the stat it shows */
typedef struct StatLine {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 stat; /* of Unk80094278.stats */
} StatLine;

typedef struct Unk800967A4 {
    TASK_HEADER(Unk800967A4);
    /* 0x50 */ s32 *unk50; /* -1 until it is done */
    /* 0x54 */ s32 *unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C[2]; /* the other fighters of the player's side */
    /* 0x64 */ s32 count;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74[2];
    /* 0x7C */ s16 slots[6]; /* GAME.funcs.getPartnerSlots's */
} Unk800967A4;

/* func_800967A4's children: two of each window, one per fighter */
typedef struct Unk800967A4Windows {
    /* 0x00 */ struct Unk8009A098 *cursor;
    /* 0x04 */ TextWindow *unk4[2];
    /* 0x0C */ TextWindow *unkC[2];
    /* 0x14 */ TextWindow *unk14[2];
    /* 0x1C */ TextWindow *unk1C[2];
    /* 0x24 */ TextWindow *unk24[2];
    /* 0x2C */ TextWindow *unk2C[2];
    /* 0x34 */ TextWindow *unk34[2];
    /* 0x3C */ TextWindow *unk3C[2];
    /* 0x44 */ TextWindow *unk44[2];
    /* 0x4C */ TextWindow *message;
} Unk800967A4Windows;

/* A roulette of six (func_80099CC0): a cursor over the shuffled lines, then
   the message of the one picked, shown like func_80097F8C's */
typedef struct Unk800999E4 {
    TASK_HEADER(Unk800999E4);
    /* 0x50 */ s32 unk50; /* the cursor's first line */
    /* 0x54 */ s32 picked;
    /* 0x58 */ s32 *unk58; /* -1 until it is done */
    /* 0x5C */ Task *unk5C; /* both stopped on a pick */
    /* 0x60 */ Task *unk60;
    /* 0x64 */ s32 unk64[9]; /* like func_80097F8C's unk50 */
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 line; /* the window being shown */
    /* 0x90 */ s32 lineCount;
    /* 0x94 */ s32 delay; /* the time between them */
    /* 0x98 */ s32 time;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 arrowPalette; /* 0-4 */
    /* 0xA8 */ s32 arrowTime; /* when it last changed */
    /* 0xAC */ s32 showArrow;
    /* 0xB0 */ s32 unkB0[4];
    /* 0xC0 */ void (*unkC0)();
} Unk800999E4;

/* Its children: the cursor, then its six lines; the first two are the
   message's after a pick */
typedef struct Unk800999E4Windows {
    /* 0x00 */ struct Unk8009A098 *cursor;
    /* 0x04 */ TextWindow *lines[6];
} Unk800999E4Windows;

/* Where the battle camera looks from and to, as a GsRVIEW2 with the
   transform of its coordinate system */
typedef struct CameraView {
    /* 0x00 */ s32 vpx;
    /* 0x04 */ s32 vpy;
    /* 0x08 */ s32 vpz;
    /* 0x0C */ s32 vrx;
    /* 0x10 */ s32 vry;
    /* 0x14 */ s32 vrz;
    /* 0x18 */ s32 tx;
    /* 0x1C */ s32 ty;
    /* 0x20 */ s32 tz;
    /* 0x24 */ SVECTOR rot;
    /* 0x2C */ s32 rz; /* the roll, in degrees */
    /* 0x30 */ s32 proj; /* the projection distance */
} CameraView;

/* The battle camera (FIGHTSTG_createBattleCamera), registered with id 0x12 on a layer:
   set puts a view, fade goes from one to another in time frames */
typedef struct BattleCamera {
    TASK_HEADER(BattleCamera);
    /* 0x050 */ s32 layerId;
    /* 0x054 */ CameraView current;
    /* 0x088 */ CameraView to;
    /* 0x0BC */ CameraView from;
    /* 0x0F0 */ s32 t; /* 0-0x1000 */
    /* 0x0F4 */ s32 tStep; /* per frame, << 8 */
    /* 0x0F8 */ void (*set)(struct BattleCamera *task, CameraView *view);
    /* 0x0FC */ void (*fade)(struct BattleCamera *task, CameraView *from, CameraView *to, s32 time); /* from: NULL for the current */
    /* 0x100 */ CameraView *(*getEnemyView)(struct BattleCamera *task);
    /* 0x104 */ CameraView *(*getFighterView)(struct BattleCamera *task, s32 id, s32 camera);
} BattleCamera;

/* The European version's camera (func_800A246C): one of three lists of shots
   (D_800A46A8) picked at random, then back to the enemy's view */
typedef struct Unk800A1FE0 {
    TASK_HEADER(Unk800A1FE0);
    /* 0x50 */ struct BattleCamera *camera;
    /* 0x54 */ struct CameraView *view;
    /* 0x58 */ struct Models *models;
    /* 0x5C */ s16 list;
    /* 0x5E */ s16 shot;
    /* 0x60 */ s16 ry; /* where the turn of substate 6 starts */
    /* 0x62 */ s16 rx;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 time;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ struct CameraView to; /* where substates 4 and 5 fade to */
} Unk800A1FE0;

/* The camera's turn around the fighters (func_800A1048) */
typedef struct Unk800A1048 {
    TASK_HEADER(Unk800A1048);
    /* 0x50 */ BattleCamera *camera;
} Unk800A1048;

/* CameraView and BattleCamera by the names WFIGHTTS still uses, until it
   moves to them: unkF8, unkFC and unk100 are set, fade and getEnemyView */
typedef struct Unk80091618 {
    /* 0x00 */ s32 unk0[13];
} Unk80091618;

typedef struct Unk800911C8 {
    TASK_HEADER(Unk800911C8);
    /* 0x050 */ s32 unk50;
    /* 0x054 */ Unk80091618 unk54;
    /* 0x088 */ u8 unk88[0x68];
    /* 0x0F0 */ s32 unkF0;
    /* 0x0F4 */ s32 unkF4;
    /* 0x0F8 */ void (*unkF8)(struct Unk800911C8 *task, Unk80091618 *arg1);
    /* 0x0FC */ void (*unkFC)();
    /* 0x100 */ Unk80091618 *(*unk100)(struct Unk800911C8 *task);
    /* 0x104 */ void (*unk104)();
} Unk800911C8;

/* A menu cursor's layout, which func_8009A214 copies into its task: a
   highlight bar over count lines, and a sprite per line (sprite -1: none) */
typedef struct Unk8009A214 {
    /* 0x00 */ s32 count;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 step;
    /* 0x10 */ s32 sprite;
    /* 0x14 */ s32 spriteX;
    /* 0x18 */ s32 spriteY;
    /* 0x1C */ s32 spriteStep;
} Unk8009A214;

/* A menu cursor (func_8009A214): up and down move it, its bar is drawn by
   func_80099D24 at vsync and each line's sprite blinks while it is picked */
typedef struct Unk8009A098 {
    TASK_HEADER(Unk8009A098);
    /* 0x50 */ s32 sel;
    /* 0x54 */ s32 locked;
    /* 0x58 */ Unk8009A214 params;
    /* 0x78 */ s32 prevSel; /* where the bar was drawn last */
    /* 0x7C */ s32 frame; /* of the bar, 0-11 */
    /* 0x80 */ s32 blink[6]; /* the time of each line's sprite */
    /* 0x98 */ u8 unk98[0x10];
} Unk8009A098;

/* Which fighters FIGHTSTG_findFighters looks for */
typedef struct FighterFilter {
    /* 0x0 */ s32 side;
    /* 0x4 */ s32 type;
} FighterFilter;

/* The battle script's task (func_8008BD10) */
/* A fighter's battle script (func_8008BD10, WFIGHTMN's BattleTask): a list
   of s16 commands in an archive entry of the fighter's file, which play its
   motions, effects, sounds and camera moves */
typedef struct BattleScript {
    TASK_HEADER(BattleScript);
    /* 0x50 */ s32 unk50; /* the enemy's */
    /* 0x54 */ s32 index; /* the script, in the fighter's archive */
    /* 0x58 */ s32 hits[4]; /* 0 a hit, 3 a miss; [3] how it ended */
    /* 0x68 */ s32 stage; /* what the stage command's 0x38 stands for */
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 sound; /* what the sound commands' 0x62 and 0x63 stand for on a hit */
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 fighter;
    /* 0x7C */ s32 model; /* the Models task's id */
    /* 0x80 */ s32 archive;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ Models *models;
    /* 0x8C */ s16 *pc;
    /* 0x90 */ s32 scripts; /* how many hits command 5 has played */
    /* 0x94 */ s32 sounds; /* and the sound commands */
    /* 0x98 */ s32 waiting;
    /* 0x9C */ s32 wait; /* the time left */
    /* 0xA0 */ s32 loadStep; /* func_8008B400's, loading a 2D effect */
    /* 0xA4 */ s32 effectImages; /* FIGHTSTG_findEffectSheet's */
    /* 0xA8 */ s32 effectSheet;
    /* 0xAC */ Vec2 effectTexPos;
} BattleScript;

/* The battle script's children */
typedef struct BattleScriptChildren {
    /* 0x00 */ Unk80092350 *fade;
    /* 0x04 */ Task *unk4;
    /* 0x08 */ Task *unk8;
    /* 0x0C */ BattleSound *sound;
    /* 0x10 */ Task *unk10[8];
    /* 0x30 */ EffectModel *effects[3];
    /* 0x3C */ BattleScript *script; /* one it plays */
} BattleScriptChildren;


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
    /* 0x01 */ u8 unk1;
    /* 0x04 */ void (*push)(BattleEvent *event);
    /* 0x08 */ void (*pushFirst)(BattleEvent *event); /* before all the others */
    /* 0x0C */ s32 (*pop)(void); /* the next event due */
    /* 0x10 */ s32 (*first)(s32 type);
    /* 0x14 */ s32 (*next)(void);
    /* 0x18 */ s32 (*find)(s32 type, u8 side, s32 fighter);
    /* 0x1C */ void (*remove)(EventKey *key); /* the events whose first two args are its */
    /* 0x20 */ s32 (*getDelay)(s32 side, s32 kind); /* func_8009AEA4: when an event of side's runs */
} EventQueueFuncs;

/* An event kind's delay range (D_800A310C, by kind): func_8009AEA4 adds a
   random part below div, and clamps to min and max where they are not 0 */
typedef struct EventDelay {
    /* 0x0 */ s16 div;
    /* 0x2 */ s16 min;
    /* 0x4 */ s16 max;
} EventDelay;

/* The battle's events (D_800A25F0) */
typedef struct EventQueue {
    /* 0x000 */ QueuedEvent events[99];
    /* 0xAD4 */ u8 unkAD4[0x1C];
    /* 0xAF0 */ s8 curType; /* the type of the event popped last */
    /* 0xAF1 */ s8 curIndex; /* and where it is */
    /* 0xAF2 */ s8 findType; /* what first and next look for, 1-24 */
    /* 0xAF3 */ s8 found; /* the event they found, or -1 */
    /* 0xAF4 */ EventQueueFuncs funcs;
} EventQueue;

/* One of the battle's fighters, three on each side (WFIGHTMN's BattleUnit):
   a partner's HP and MP go back to the party when the battle ends */
typedef struct BattleFighter {
    /* 0x00 */ s16 id; /* the Digimon (DIGIMON_DATA) */
    /* 0x02 */ s16 prevId; /* its id before unk1A changed it */
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 maxHp;
    /* 0x08 */ s16 hp;
    /* 0x0A */ s16 maxMp;
    /* 0x0C */ s16 mp;
    /* 0x0E */ s16 unkE; /* FIGHTSTG_computeStats reads its low byte */
    /* 0x10 */ s16 boosts[4]; /* added to the stats that D_800A3418 picks */
    /* 0x18 */ s16 item; /* an enemy's */
    /* 0x1A */ u8 unk1A; /* id is a temporary Digimon */
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 flags; /* 2, 4 and 8 have the counters after */
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
    /* 0xD0 */ s16 unkD0; /* an element func_8009E74C boosts, under 2 for none */
    /* 0xD2 */ s16 unkD2; /* and how much, in 128ths */
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ s16 unkD6; /* the kind of battle */
    /* 0xD8 */ s16 unkD8; /* a technique id, set by WFIGHTMN */
    /* 0xDA */ s8 unkDA;
    /* 0xDB */ u8 unkDB;
    /* 0xDC */ BattleSpeed speed;
    /* 0xE4 */ s32 (*unkE4)();
    /* 0xE8 */ s32 (*unkE8)();
    /* 0xEC */ void (*project)(Layer *layer, SVECTOR *pos, ShortVec3 *out); /* FIGHTSTG_projectPoint */
    /* 0xF0 */ s32 (*unkF0)();
    /* 0xF4 */ s32 (*unkF4)();
} Battle;

/* The technique table (BattleTech) seen from D_800427D6, an entry before
   D_800427E8, so that the technique id indexes it */
typedef struct Unk800427D6 {
    /* 0x00 */ u16 mp; /* as BattleTech */
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
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
    /* 0x28 */ s32 damage; /* per hit */
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 hits[4]; /* whether each hit lands */
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x28]; /* by D_800427D6's unkA */
    /* 0x60 */ s32 unk60[2];
    /* 0x68 */ void (*unk68)();
} BattleAction;

/* A side's stats as FIGHTSTG_computeStats works them out */
typedef struct BattleStats {
    /* 0x00 */ s16 level;
    /* 0x02 */ s16 stats[5]; /* with the fighter's boosts */
    /* 0x0C */ s16 resist[12];
    /* 0x24 */ u8 flags; /* the fighter's */
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26; /* the fighter's unkE */
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 unk28[3]; /* from the equipment, as are the ones after */
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30[0x10];
} BattleStats;

/* D_800A3308 */
typedef struct Battle800A3308 {
    /* 0x00 */ BattleStats stats[2]; /* the player's, then the enemy's */
    /* 0x80 */ BattleStats *(*computeStats)(u8 side, s32 which, s32 index); /* FIGHTSTG_computeStats */
    /* 0x84 */ s32 (*unk84)();
    /* 0x88 */ s32 (*unk88)();
    /* 0x8C */ s32 (*getDamage)(s32 *args); /* of the event whose args these are */
    /* 0x90 */ s32 (*unk90)();
    /* 0x94 */ s32 (*unk94)();
    /* 0x98 */ s32 (*getHeal)(u8 side, s32 index, s32 big); /* a part of its max HP */
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
    /* 0xDC */ s32 (*unkDC)(u8 side); /* whether status 2 holds the other side */
    /* 0xE0 */ void (*unkE0)(); /* func_800A0B10: changes a fighter's stat boost */
    /* 0xE4 */ s32 (*unkE4)(s32 damage); /* from the partner's damage, up to 1000 */
    /* 0xE8 */ s32 (*unkE8)();
} Battle800A3308;

/* Shared between the overlay's objects */
extern Battle D_800A31E8;
extern BattleAction D_800A317C;
extern FighterCache D_800A32E0;
extern Battle800A3308 D_800A3308;
extern s16 D_800A3418[];
extern s32 D_800A1238[];
extern Methods800A3420 D_800A3420;
void func_800831D4(Model *model, s32 motion, s32 restart);
void func_8008358C(Model *model, Mesh **children);
Mesh *func_8008588C(s32 archive, Vec2 texPos);
void FIGHTSTG_setModelColor(Model *model, s32 mode, CVECTOR *color);
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
extern void (*D_800A3108)();
extern u8 D_800A315C[]; /* func_8009B430's event types */
extern u8 D_800A3164[]; /* and the status flags they clear */
extern RECT D_800A3470; /* func_800933EC's layer */
extern BattleEvent D_800A34E0;
extern BattleTableEntry *(*D_800A2584)(s32 id);
void FIGHTSTG_pushEvent(BattleEvent *event);
void FIGHTSTG_pushEventFirst(BattleEvent *event);
s32 FIGHTSTG_popEvent(void);
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
s32 func_80086084(void);
void func_8008690C();
void func_80087CE4(Unk80087CE4 *task, Unk80097F8C **children);
void func_8008BD10();
void func_80090098(Unk80090098 *task, Unk80097F8C **children);
void func_8009B5F8(s32 arg0);
void func_8009C18C(void);
void func_800924DC(HpDisplay *task, TextWindow **windows);
void func_800928BC(HpDisplay *task, TextWindow **windows);
void func_80092E0C(HpDisplay *task, TextWindow **windows);
void func_800933EC(Unk800933EC *task, FighterCamera **cameras);
void func_800A1048();
void func_800A1FE0();
void func_80091A58(Unk80091A58 *task, Task **children);
void func_8009D8B4(s32 layerId, s32 depth, DVECTOR *xy, CVECTOR *colors, s32 semi);
void func_800973D4();
void func_80087870();
void FIGHTSTG_updateScreenFade(ScreenFade *task);
void FIGHTSTG_startScreenFade(ScreenFade *task, s32 fadeIn, s32 duration);
void func_80089458();
void func_8008EAF8();
void func_80090290();
void FIGHTSTG_updateCamera(FighterCamera *task);
void func_800921EC(Unk80092350 *task);
void func_80092350(Unk80092350 *task);
void func_800937FC();
void func_8008C0BC();
void func_8008CFFC();
s32 func_8008C8F0(Unk8008CFFC *task, BattleScript **children);
void func_80090908();
Unk800973D4 *func_80097B74(s32 *arg0);
void func_80094D04();
void func_80095AC0(Unk80095AC0 *task, TextWindow **windows);
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
void func_8009BD20(u8 side, s32 fighter, s32 kind, s32 arg3);
void func_80097C14();
void func_80097D74();
void func_80098808();
void func_800931CC();
void func_8008E3C8();
s32 FIGHTSTG_findBattleTableIndex(s32 id);
BattleTableEntry *FIGHTSTG_getBattleTableEntry(s32 id);
void func_80094278();
void func_800967A4();
void func_800999E4();
void FIGHTSTG_updateBattleCamera(BattleCamera *task);
void FIGHTSTG_fadeBattleCamera(BattleCamera *task, CameraView *from, CameraView *to, s32 time);
CameraView *func_80091788(BattleCamera *task, s32 id, s32 camera);
CameraView *func_80091950(BattleCamera *task);
void func_80086180();
void func_8009245C(Unk80092350 *task, s32 frames);
Unk80092350 *func_80092494(s32 frames);
void func_8009A098();
BattleStats *FIGHTSTG_computeStats(u8 side, s32 which, s32 index);
extern s32 D_800A33F4[];
void func_800833B0(Model *model);
extern EffectModelEntry D_800A12F0[];
Face *FIGHTSTG_createFace(Model *model, s32 fighter);
void FIGHTSTG_projectPoint(Layer *layer, SVECTOR *pos, ShortVec3 *out);
void func_80029DB8(GsRVIEW2 *view); /* GsSetRefView2 */
extern JumpParams D_800A23E4[];
extern s32 D_800A2414[]; /* sound ids */
extern EffectSheet D_800A1914[];
extern SpriteEffectEntry D_800A1C44[];
void func_8008899C(void *arg, Layer *layer);
extern CameraView D_800A3438;
extern s32 D_800A2588[]; /* per event type, FIGHTSTG_popEvent takes (1), peeks at (-1) or skips (0) it */
extern DigimonData *(*ON_PARTNER_ENTRY_ADDED)(s32 id);
struct Unk8009A098 *func_8009A214(Unk8009A214 *arg0);
extern Unk8009A214 D_800A2254; /* func_800931CC's cursor */
extern Unk8009A214 D_800A22BC; /* func_80094D04's cursor */
extern Unk8009A214 D_800A22DC; /* func_80095AC0's cursor */
extern Unk8009A214 D_800A22FC; /* func_800967A4's cursor */
extern Unk8009A214 D_800A231C[2]; /* func_800973D4's cursors */
extern Unk8009A214 D_800A23BC; /* func_800999E4's */
extern StatLine D_800A2294[13];
extern s16 D_800A236C[][2]; /* func_800999E4's results: the message, its line */
extern s16 D_800A23AC[]; /* func_800999E4's lines, shuffled */
extern RECT D_800A23DC; /* where func_80099D24's bar is in VRAM */
extern DR_MOVE D_800A3478[4];
extern u_long D_800A34D8[2]; /* their OT */
struct Unk80094278 *func_80094754(s32 arg0, s32 arg1, s32 arg2);
s32 func_800961DC(Unk800967A4 *task, s32 index, s32 member);
extern u16 D_800A235C[];
extern CameraShot D_800A1258[4][6];
extern u8 D_800A12B8[8][3];
#if VERSION_EU
extern CameraShot D_800A46A8[3][3];
#endif
void func_80098004(Unk80097F8C *task, Unk80097F8CWindows *w, s32 side, s32 index);
void func_80098428(Unk80097F8C *task, Unk80097F8CWindows *w, BattleMessage *msg);
void func_80099444(Unk800999E4 *task);
void func_80099514(Unk800999E4 *task);
void func_80099674(Unk800999E4 *task, Unk800999E4Windows *w);
void func_8009981C(Unk800999E4 *task, Unk800999E4Windows *windows, s32 arg2);
void func_80099894(Unk800999E4 *task, s32 index, s32 arg2);
void func_80099F20(Unk8009A098 *task);
void func_80099D24(Unk8009A098 *task);
s32 func_8009E74C(s32 value, s32 arg1);
s32 func_8009E7E4(u8 side, s32 id, s32 value);
s32 func_8009F36C(u8 side, s32 id);
s32 func_8009F5D4(u8 side, s32 id);
s32 func_800860DC(s32 id);
extern s32 D_800A3430;
s32 FIGHTSTG_getEffectModelFile(s32 id);
EffectModel *func_80088FC4(s32 id, SVECTOR *pos, SVECTOR *rot);
BattleSound *FIGHTSTG_playBattleSound(s32 index, s32 time);
s32 FIGHTSTG_findEffectSheet(s32 effect, s32 *images, s32 *sheet, Vec2 *texPos);
SpriteEffect *FIGHTSTG_startSpriteEffect(s32 effect, SVECTOR *pos);
extern s32 D_800A3168[]; /* the event types of func_8009BD20, by kind */
extern s32 D_800A3174[]; /* and of func_8009BE1C */
#endif /* FIGHTSTG_H */
