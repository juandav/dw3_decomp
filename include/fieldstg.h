#ifndef FIELDSTG_H
#define FIELDSTG_H

/*
 * FIELDSTG.PRO: the field mode, where the player walks around the map.
 *
 * The stage overlays (AAA/PRO/WSTAG###.PRO, see stage.h) load on top of it
 * at 0x800A4CA4 and call into it.
 */

#include "game.h"
#include "field_map.h"

typedef struct Point {
    s32 x;
    s32 y;
} Point;

/* A step of func_800896C0's spiral: one coordinate of a tile moves by dir
 * until it passes limit */
typedef struct TileMove {
    /* 0x0 */ s32 *value;
    /* 0x4 */ s32 dir; /* 1, -1, or 0 at the end */
    /* 0x8 */ s32 limit;
} TileMove;

/*
 * A character on the field (func_80090450): the player (kind 0) and the
 * other characters. Registered with id 5, key1 = character, key2 = kind.
 * x and y are in 1/256 tile units.
 */
typedef struct Actor {
    TASK_HEADER(Actor);
    /* 0x050 */ Vec2 pos;
    /* 0x058 */ Point tile;
    /* 0x060 */ s32 dir;
    /* 0x064 */ s32 unk64;
    /* 0x068 */ s32 unk68;
    /* 0x06C */ struct ActorImage *image;
    /* 0x070 */ struct FieldImage *unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ s32 unk78;
    /* 0x07C */ struct FieldActorEntry *entry; /* what created it, or NULL */
    /* 0x080 */ s32 unk80; /* width, in tiles */
    /* 0x084 */ s32 unk84;
    /* 0x088 */ struct Actor *unk88; /* the actor it talks to */
    /* 0x08C */ s32 unk8C;
    /* 0x090 */ s32 unk90;
    /* 0x094 */ s32 unk94;
    /* 0x098 */ s32 unk98;
    /* 0x09C */ s32 unk9C; /* a file and index, or 0 */
    /* 0x0A0 */ s32 unkA0;
    /* 0x0A4 */ s32 unkA4; /* the set unkA8 was loaded for */
    /* 0x0A8 */ s32 unkA8[5]; /* the set's animations, for the directions 0 to 4 */
    /* 0x0BC */ s32 unkBC;
    /* 0x0C0 */ s32 unkC0; /* set to reload the frame's image */
    /* 0x0C4 */ s32 unkC4;
    /* 0x0C8 */ s16 unkC8; /* a sound voice, or -1 */
    /* 0x0CA */ s16 unkCA;
    /* 0x0CC */ s32 unkCC;
    /* 0x0D0 */ s32 unkD0;
    /* 0x0D4 */ s32 unkD4[4]; /* the frame's image, the one loaded, and two values */
    /* 0x0E4 */ s16 unkE4; /* the loaded image's width in pixels */
    /* 0x0E6 */ s16 unkE6; /* and its height */
    /* 0x0E8 */ s32 unkE8; /* the animation ended */
    /* 0x0EC */ s32 unkEC;
    /* 0x0F0 */ s32 unkF0;
    /* 0x0F4 */ s32 unkF4;
    /* 0x0F8 */ s32 unkF8;
    /* 0x0FC */ s32 unkFC;
    /* 0x100 */ s32 unk100;
    /* 0x104 */ struct Trail *trail; /* a follower's: the leader's steps */
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

/* The last 64 steps of the actor that another one follows (Actor.trail) */
typedef struct TrailStep {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 dir;
} TrailStep;

typedef struct Trail {
    /* 0x000 */ Actor *leader;
    /* 0x004 */ s32 head;
    /* 0x008 */ s32 tail;
    /* 0x00C */ TrailStep steps[64];
} Trail;

/* A sprite of a StreamTask's frame */
typedef struct StreamSprite {
    /* 0x00 */ s32 visible;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 u;
    /* 0x10 */ s32 v;
    /* 0x14 */ s32 w;
    /* 0x18 */ s32 h;
} StreamSprite;

/* A task that reads the frames of a file from the disc (func_80086B54) */
typedef struct StreamTask {
    TASK_HEADER(StreamTask);
    /* 0x050 */ s32 time;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 frame;
    /* 0x05C */ s32 sector;
    /* 0x060 */ s32 file;
    /* 0x064 */ s32 frameSectors;
    /* 0x068 */ void *buffer;
    /* 0x06C */ s32 loaded;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 imageX;
    /* 0x078 */ s32 imageY;
    /* 0x07C */ s32 clutX;
    /* 0x080 */ s32 clutY;
    /* 0x084 */ StreamSprite sprites[3][5];
    /* 0x228 */ s32 slot;
    /* 0x22C */ Decompressor *source; /* what it reads its sprites from (func_80086858) */
    /* 0x230 */ s32 *unk230;
    /* 0x234 */ void (*seek)(struct StreamTask *task, s32 frame, s32 size);
    /* 0x238 */ s32 (*isLoaded)(struct StreamTask *task);
    /* 0x23C */ void (*draw)(struct StreamTask *task, Layer *layer, s32 x, s32 y);
    /* 0x240 */ void (*setSource)(struct StreamTask *task, s32 slot, Decompressor *source);
    /* 0x244 */ s32 (*getFrame)(struct StreamTask *task);
    /* 0x248 */ s32 (*unk248)(struct StreamTask *task);
    /* 0x24C */ void (*unk24C)(struct StreamTask *task);
    /* 0x250 */ void (*updateTime)(struct StreamTask *task);
} StreamTask;

/* The StreamTasks of a task's children (func_80085650) */
typedef struct StreamPool {
    /* 0x00 */ Decompressor *decompressor;
    /* 0x04 */ StreamTask *tasks[30];
} StreamPool;

/* Where an actor's frames go in VRAM: one of the records after the
   FieldImage (Actor.image) */
typedef struct ActorImage {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 w;
    /* 0x6 */ s16 h;
    /* 0x8 */ s16 u;
    /* 0xA */ s16 v;
    /* 0xC */ s16 clutX;
    /* 0xE */ s16 clutY;
} ActorImage;

/* The image of the field's effects (FieldState.unk28) */
typedef struct FieldImage {
    /* 0x00 */ ActorImage shadow; /* the actors' shadow (func_8008E7E0) */
    /* 0x10 */ s16 x; /* in VRAM */
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 w;
    /* 0x16 */ s16 h;
    /* 0x18 */ s16 u;
    /* 0x1A */ s16 v;
    /* 0x1C */ s16 clutX;
    /* 0x1E */ s16 clutY;
} FieldImage;

/* An entry of the table FieldState.unk24 (func_80084B80) */
typedef struct Unk80084B80Entry {
    /* 0x00 */ s32 id;
    /* 0x04 */ s16 *script; /* func_80084654's, or NULL */
    /* 0x08 */ s32 text; /* a file and index, the file counted from
                            TEXT_FILE(1); or 0 */
    /* 0x0C */ struct Task *(*start)(void); /* without a script */
    /* 0x10 */ void (*end)(void); /* or NULL */
} Unk80084B80Entry;

/* What a character says (func_8008F184): the first whose conditions hold,
   or the last, which has none */
typedef struct FieldTalk {
    /* 0x0 */ u16 *conditions; /* FLAGS_00.checkConditions's */
    /* 0x4 */ u16 *actions; /* FLAGS_00.applyActions's when it ends, or NULL */
    /* 0x8 */ s32 unk8; /* func_8008848C's */
} FieldTalk;

/* A character of the field (FieldState.unk4C), which func_8008A154 creates
   unless its conditions fail. Ids 1, 0x6A, 0x146 and 0x147 are the player's. */
typedef struct FieldActorEntry {
    /* 0x00 */ u16 *conditions; /* FLAGS_00.checkConditions's, or NULL */
    /* 0x04 */ struct FieldTalk *talks; /* up to the first without conditions */
    /* 0x08 */ s16 id;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 x; /* in pixels */
    /* 0x0E */ s16 y;
    /* 0x10 */ s16 dir;
} FieldActorEntry;

/* Where a warp leads (FieldTask.unk7C, func_8008B398) */
typedef struct FieldWarp {
    /* 0x0 */ s16 mode;
    /* 0x2 */ s16 x; /* in pixels */
    /* 0x4 */ s16 y;
    /* 0x6 */ s16 dir;
    /* 0x8 */ u8 unk8[2];
    /* 0xA */ u16 unkA; /* copied to GAME.unk44 and unk46 */
    /* 0xC */ u16 unkC;
} FieldWarp;

/*
 * The field's state (D_800990B4). The first 0x64 bytes are cleared by
 * func_800913CC, which also picks the stage overlay for the current mode.
 */
typedef struct FieldState {
    /* 0x00 */ s32 stageFile; /* the stage overlay's file */
    /* 0x04 */ struct Task *(*stageInit)(void *owner); /* starts the stage's task */
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ void *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ struct Unk800990D4 *unk20;
    /* 0x24 */ struct Unk80084B80Entry *unk24; /* up to the first id -1 */
    /* 0x28 */ FieldImage *unk28;
    /* 0x2C */ Vec2 unk2C; /* where the player starts */
    /* 0x34 */ s32 unk34; /* and its direction */
    /* 0x38 */ CVECTOR unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ void *unk4C; /* the characters (FieldActorEntry *), up to the first NULL */
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ Vec2 unk64; /* where the player starts without a mode argument */
    /* 0x6C */ s32 unk6C; /* and its direction */
    /* 0x70 */ void (*init)(void);
    /* 0x74 */ s32 (*unk74)(s32 index);
    /* 0x78 */ s32 (*unk78)(s32 index);
    /* 0x7C */ void *(*unk7C)(u8 *list, s32 id);
} FieldState;

/* The field's main task (func_8008A154, id 7); its children follow */
typedef struct FieldTask {
    TASK_HEADER(FieldTask);
    /* 0x50 */ s32 fade; /* func_80086460's level */
    /* 0x54 */ s32 width; /* of the clip rectangle */
    /* 0x58 */ s32 height;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ void *unk64; /* a buffer at the end of the heap */
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ Point unk74;
    /* 0x7C */ FieldWarp *unk7C;
} FieldTask;

/* An entry of the script command table D_8009A448 (ids from 0x320) */
typedef struct ScriptCommand {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 (*create)(s32 arg);
    /* 0x8 */ void (*handle)(s32 arg0, s32 arg1, s32 arg2);
} ScriptCommand;

/* The name of a mode's area (func_80086D20), up to the first mode 0: the
   strings of the two windows, from text files 0xAA and 0xB8 */
typedef struct AreaName {
    /* 0x0 */ u8 area;
    /* 0x1 */ u8 place;
    /* 0x2 */ s16 mode;
} AreaName;

/* The windows of func_80086D20 */
typedef struct AreaNameWindows {
    /* 0x0 */ TextWindow *area;
    /* 0x4 */ TextWindow *place;
} AreaNameWindows;

/* An entry of the stage tables (func_800913CC): the stage overlay of a mode,
   up to the first mode 0 */
typedef struct StageEntry {
    /* 0x0 */ s32 mode;
    /* 0x4 */ s32 file;
    /* 0x8 */ struct Task *(*init)(void *owner);
} StageEntry;

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

/* An encounter of D_800939E0, which func_8008AEDC starts: its enemies and
   the bytes it copies to D_80042728.unk3C on */
typedef struct Encounter {
    /* 0x00 */ BattleEnemy *enemies[3];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE[12];
    /* 0x1A */ u8 unk1A[2];
} Encounter;

typedef struct BattleList {
    /* 0x0 */ s32 count;
    /* 0x4 */ Battle *battles[1];
} BattleList;

typedef struct Unk800990D4 {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ BattleList *battles[4];
} Unk800990D4;

/*
 * An event (func_80084654, made by func_80084B80): it runs a script of
 * 16-bit words, each command a word of its kind << 8 | its variant followed
 * by its arguments, until a command waits; or, without a script, a task of
 * its own (start) until it ends.
 */
typedef struct Unk80084654 {
    TASK_HEADER(Unk80084654);
    /* 0x050 */ s32 event; /* its id */
    /* 0x054 */ s16 *pc;
    /* 0x058 */ struct Task *(*start)(void);
    /* 0x05C */ void (*end)(void);
    /* 0x060 */ s32 wait; /* frames left of a wait command */
    /* 0x064 */ struct {
        s32 id; /* 0 ends the list */
        struct Actor *actor;
    } entries[30]; /* the characters, held while the event runs */
} Unk80084654;

/* The children of an Unk80084654 */
typedef struct Unk80084654Children {
    /* 0x00 */ struct Task *task; /* start's */
    /* 0x04 */ struct Unk800882D8 *boxes[3]; /* the script's message boxes */
    /* 0x10 */ s32 scripts[10]; /* func_80091730's tasks */
} Unk80084654Children;

/* The children of the field's main task (FieldTask, func_8008A154) */
typedef struct FieldChildren {
    /* 0x00 */ struct Unk80085350 *unk0; /* func_80085588's */
    /* 0x04 */ ScreenFade *fade;
    /* 0x08 */ struct Unk80084D0C *unk8; /* func_80085240's */
    /* 0x0C */ Unk80084654 *unkC;
    /* 0x10 */ Task *unk10; /* the inn (createInn), or func_800892E8's */
    /* 0x14 */ Task *unk14; /* func_800874C8's */
    /* 0x18 */ struct Actor *actors[4]; /* the player and the partners */
    /* 0x28 */ struct Unk8008CC4C *unk28; /* func_8008CF0C's */
    /* 0x2C */ struct Actor *npcs[15]; /* FieldState.unk4C's other characters */
    /* 0x68 */ struct Unk80087FDC *unk68; /* func_800881A0's */
    /* 0x6C */ Task *stage; /* FieldState.stageInit's */
    /* 0x70 */ struct Unk80086144 *unk70; /* func_80086418's */
    /* 0x74 */ Task *menu; /* createFieldMenu's */
    /* 0x78 */ struct Unk8008878C *unk78; /* func_80088BE4's */
} FieldChildren;

/* The task of func_80086144 (id 4, see func_80086418) */
/* A tile of the map that Unk80086144 streams */
typedef struct MapTile {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} MapTile;

typedef struct Unk80086144 {
    TASK_HEADER(Unk80086144);
    /* 0x050 */ s32 unk50;
    /* 0x054 */ s32 *unk54;
    /* 0x058 */ Point scroll;
    /* 0x060 */ s32 unk60;
    /* 0x064 */ s32 unk64;
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ struct {
        s32 unk0;
        s32 unk4;
        s32 unk8;
    } unk74[12];
    /* 0x104 */ MapTile *unk104;
    /* 0x108 */ u8 unk108[30]; /* by the slots around the view, their tiles */
    /* 0x126 */ u8 unk126[2];
    /* 0x128 */ s32 unk128; /* the tile column of the slots' left edge */
    /* 0x12C */ s32 unk12C; /* their top row */
    /* 0x130 */ Point *(*unk130)(struct Unk80086144 *);
} Unk80086144;

/* The task of func_80084D0C (func_80085240) */
typedef struct Unk80084D0C {
    TASK_HEADER(Unk80084D0C);
    /* 0x50 */ s32 kind; /* 0: file 0x88C (0x87B in the USA), 1: file 0x88D (0x87C) */
    /* 0x54 */ s32 frame;
    /* 0x58 */ s32 index; /* into the animation */
    /* 0x5C */ s32 timer;
    /* 0x60 */ s32 frame2; /* kind 1's second animation */
    /* 0x64 */ s32 index2;
    /* 0x68 */ s32 timer2;
} Unk80084D0C;

/* An animation of an Unk80085350 (func_80085278) */
typedef struct Unk80085278 {
    /* 0x0 */ s32 active;
    /* 0x4 */ AnimState anim;
} Unk80085278;

/* The task of func_80085350 (func_80085588) */
typedef struct Unk80085350 {
    TASK_HEADER(Unk80085350);
    /* 0x50 */ s32 x;
    /* 0x54 */ s32 y;
    /* 0x58 */ s16 set; /* the row of D_800961E4 */
    /* 0x5A */ u8 unk5A[2];
    /* 0x5C */ Unk80085278 anims[4];
} Unk80085350;

/* The task of func_80087FDC (func_800881A0) */
/* The field's effect sprites (func_8008C2F4): the discs number their files
   differently */
#if VERSION_US
#define FIELD_SPRITES_FILE 0x152
#elif VERSION_EU
#define FIELD_SPRITES_FILE 0x160
#endif

/* The files of the exits' effects (func_80088D5C): the discs number their
   files differently */
#if VERSION_US
#define FIELD_EXIT_FILES 0x3B9
#elif VERSION_EU
#define FIELD_EXIT_FILES 0x3C9
#endif

/* The two animations of func_80084D0C, kind 0's file and kind 1's after it:
   the discs number their files differently */
#if VERSION_US
#define FIELD_ANIM_FILE 0x87B
#elif VERSION_EU
#define FIELD_ANIM_FILE 0x88C
#endif

typedef struct Unk80087FDCEntry {
    /* 0x00 */ u16 conditions[2][2]; /* code and value, or code 0xFFFF */
    /* 0x08 */ u16 type;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12; /* the id of the map objects to clear, or 0 */
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
} Unk80087FDCEntry;

typedef struct Unk80087FDC {
    TASK_HEADER(Unk80087FDC);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ Unk80087FDCEntry *entries;
    /* 0x58 */ Actor *actor;
    /* 0x5C */ s32 index;
    /* 0x60 */ s32 dir;
    /* 0x64 */ Unk80087FDCEntry *entry;
} Unk80087FDC;

/* The children of an Unk80087FDC */
typedef struct Unk80087FDCChildren {
    /* 0x0 */ struct Unk800876E4 *anim;
    /* 0x4 */ Unk80084654 *script;
} Unk80087FDCChildren;

/* A rectangle, edges included */
typedef struct Box {
    /* 0x0 */ s32 left;
    /* 0x4 */ s32 right;
    /* 0x8 */ s32 top;
    /* 0xC */ s32 bottom;
} Box;

/* An object of a map (FieldState.unk10, 0x12 bytes), up to unk2 0 */
typedef struct MapObject {
    /* 0x00 */ u8 unk0; /* drawn */
    /* 0x01 */ u8 id;
    /* 0x02 */ u8 unk2; /* how far off the view it is still drawn; 0 ends the list */
    /* 0x03 */ u8 depth;
    /* 0x04 */ u8 frame;
    /* 0x05 */ u8 anim; /* 1 cycles the frame, 2 the CLUT row, 3 the row back and forth */
    /* 0x06 */ u8 animFirst;
    /* 0x07 */ u8 animLast;
    /* 0x08 */ u8 animDelay;
    /* 0x09 */ u8 clutRow;
    /* 0x0A */ s16 x;
    /* 0x0C */ s16 y;
    /* 0x0E */ s16 unkE; /* drawn sorted at this depth, or 0 */
    /* 0x10 */ s16 animTime; /* in 1/256 frames; bit 15: going back */
} MapObject;

/* The task of func_8008878C (func_80088BE4) */
typedef struct Unk8008878C {
    TASK_HEADER(Unk8008878C);
    /* 0x50 */ s32 unk50; /* the sprite bank */
    /* 0x54 */ struct MapObject *unk54;
} Unk8008878C;

/* The task of func_80089320 (func_80089668) */
typedef struct Unk80089320 {
    TASK_HEADER(Unk80089320);
    /* 0x50 */ Actor *actor;
    /* 0x54 */ s32 frame;
    /* 0x58 */ s32 animStep;
    /* 0x5C */ s32 animTime;
    /* 0x60 */ u8 (*anim)[2]; /* (frame, time) pairs; 0xFF loops to a step */
} Unk80089320;

/* The task of func_800876E4 (func_800878A4) */
typedef struct Unk800876E4 {
    TASK_HEADER(Unk800876E4);
    /* 0x50 */ Actor *actor;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 frame; /* into its D_80096920 row */
    /* 0x68 */ s32 time;
} Unk800876E4;

/* The task of func_800882D8 (func_800883F4): a message or talk box */
typedef struct Unk800882D8 {
    TASK_HEADER(Unk800882D8);
    /* 0x50 */ Actor *actor;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C; /* nonzero: a message box */
    /* 0x60 */ s32 text; /* FILE_CACHE_GET_ENTRY */
} Unk800882D8;

/* The children of an actor (func_80090294) */
typedef struct ActorChildren {
    /* 0x0 */ Unk80089320 *anim; /* func_80089668's */
    /* 0x4 */ Unk800876E4 *unk4; /* func_800878A4's */
    /* 0x8 */ void *unk8;
    /* 0xC */ Unk800882D8 *unkC; /* func_8008848C's */
} ActorChildren;

/* The task of func_8008B450 (func_8008B930) */
typedef struct Unk8008B450 {
    TASK_HEADER(Unk8008B450);
    /* 0x50 */ Actor *actor;
    /* 0x54 */ s16 *dest; /* the tile it lands on, at [1] and [2] */
    /* 0x58 */ Task *from; /* the nearest task with id 0x17 */
    /* 0x5C */ Point start;
    /* 0x64 */ Point dist;
    /* 0x6C */ s32 negX;
    /* 0x70 */ s32 negY;
} Unk8008B450;

/* The task of func_8008B9D8 (func_8008BBD4) */
typedef struct Unk8008B9D8 {
    TASK_HEADER(Unk8008B9D8);
    /* 0x50 */ s32 time;
    /* 0x54 */ s32 speed; /* frames per palette step */
    /* 0x58 */ s32 frame;
    /* 0x5C */ Point from;
    /* 0x64 */ Point to;
} Unk8008B9D8;

/* An entry of an Unk8008BFE8's table */
typedef struct Unk8008BFE8Entry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ Point pos;
    /* 0x10 */ s32 unk10;
} Unk8008BFE8Entry;

/* The task of func_8008BCAC (id 8/0xB, func_8008BFE8) */
typedef struct Unk8008BFE8 {
    TASK_HEADER(Unk8008BFE8);
    /* 0x50 */ s32 count;
    /* 0x54 */ Unk8008BFE8Entry *entries;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ Point pos;
} Unk8008BFE8;

/* The children of an Unk8008BFE8 */
typedef struct Unk8008BFE8Children {
    /* 0x0 */ struct Unk8008C388 *unk0;
    /* 0x4 */ struct Unk8008B9D8 *unk4;
} Unk8008BFE8Children;

/* The task of func_8008C388 (func_8008C564), drawn by func_8008C2F4 */
typedef struct Unk8008C388 {
    TASK_HEADER(Unk8008C388);
    /* 0x50 */ s32 x;
    /* 0x54 */ s32 y;
    /* 0x58 */ s32 dir;
    /* 0x5C */ s32 frame;
    /* 0x60 */ u8 *anim;
} Unk8008C388;

/* The task of func_8008C59C (func_8008C9F8) */
typedef struct Unk8008C59C {
    TASK_HEADER(Unk8008C59C);
    /* 0x50 */ Point pos;
    /* 0x58 */ s32 row; /* of FIELDSTG_gaugeRows */
    /* 0x5C */ s32 cursor; /* along the row, 0-0x3000 */
    /* 0x60 */ s32 speed;
    /* 0x64 */ s32 back; /* the cursor goes back */
} Unk8008C59C;

/* The task of func_8008CC4C (id 0x10, func_8008CF0C) */
typedef struct Unk8008CC4C {
    TASK_HEADER(Unk8008CC4C);
    /* 0x50 */ Actor *unk50;
    /* 0x54 */ Point unk54;
    /* 0x5C */ s32 shaking;
    /* 0x60 */ s32 shake; /* the step of the shake, 0-3 */
    /* 0x64 */ s16 voice; /* of the shaking sound, or -1 */
    /* 0x66 */ u8 unk66[2];
    /* 0x68 */ Point unk68;
    /* 0x70 */ s32 hasBounds;
    /* 0x74 */ Point bounds; /* the map's size */
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
} Unk8008CC4C;

/* The task of func_800834A0 (func_80083930) */
typedef struct Unk800834A0 {
    TASK_HEADER(Unk800834A0);
    /* 0x50 */ struct MapObject *left; /* the map object 3 */
    /* 0x54 */ struct MapObject *right; /* the map object 2 */
    /* 0x58 */ s16 unk58; /* raised: the objects and the player are 0x7F lower */
    /* 0x5A */ s16 time;
    /* 0x5C */ s16 shake; /* the index into D_80095E84 */
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ s16 leftY; /* the positions when the move started */
    /* 0x62 */ s16 rightY;
    /* 0x64 */ s32 playerY;
    /* 0x68 */ s16 leftBaseY; /* the objects' positions on the map */
    /* 0x6A */ s16 rightBaseY;
} Unk800834A0;

/* The task of func_800842C8 (func_800844B8) */
typedef struct Unk800842C8 {
    TASK_HEADER(Unk800842C8);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 script; /* the script to run next, or 0 */
} Unk800842C8;

typedef struct Unk800842C8Children {
    /* 0x0 */ Unk800834A0 *unk0;
    /* 0x4 */ Unk80084654 *script;
} Unk800842C8Children;

/* A story event (D_80095F18): at a progress, while a flag is clear and a
   condition holds, a script runs, and then another one */
typedef struct ProgressEvent {
    /* 0x0 */ s32 progress; /* -1 ends the list */
    /* 0x4 */ s32 flag;
    /* 0x8 */ s32 condition;
    /* 0xC */ s16 script;
    /* 0xE */ s16 nextScript;
} ProgressEvent;

/* The task of func_800870D4 (id 9, func_800874C8) */
/* A rectangle of an Unk800870D4, which can stretch to a new range */
typedef struct Unk800870D4Box {
    /* 0x00 */ s32 visible;
    /* 0x04 */ DVECTOR pos;
    /* 0x08 */ DVECTOR size;
    /* 0x0C */ s32 color;
    /* 0x10 */ s32 stretch; /* 1: horizontally, 2: vertically */
    /* 0x14 */ s32 from;
    /* 0x18 */ s32 to;
    /* 0x1C */ s32 speed;
    /* 0x20 */ s32 unk20;
} Unk800870D4Box;

/* The area name banner (func_800870D4) */
typedef struct Unk800870D4 {
    TASK_HEADER(Unk800870D4);
    /* 0x050 */ Unk800870D4Box boxes[10];
    /* 0x1B8 */ RECT clip; /* the layer's, closing on state 2 */
} Unk800870D4;

/* A yes/no question of the story (func_80083998) */
typedef struct ChoiceTask {
    TASK_HEADER(ChoiceTask);
    /* 0x50 */ s32 type; /* D_80095E98's */
    /* 0x54 */ s32 selection;
    /* 0x58 */ Tween tween; /* the panel's width */
} ChoiceTask;

typedef struct ChoiceChildren {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *options[2];
    /* 0x0C */ Cursor *cursor;
    /* 0x10 */ Unk80084654 *event;
} ChoiceChildren;

/* A question of a ChoiceTask */
typedef struct ChoiceText {
    /* 0x0 */ s32 text; /* the file counted from TEXT_FILE(1) << 16 | its
                           entry: the question, then the answers */
    /* 0x4 */ s16 events[2]; /* func_80084B80's, for each answer */
} ChoiceText;

void func_80082F1C(Task *task);
void func_80083998();
void func_80086C4C(Task *task, Task **children);
Task *func_8008ADE8(void);
void func_8008A154();
void func_8008AE18(s32, s32, s32, s32, s32, s32);
void func_800876E4(Unk800876E4 *task);
void func_8008DB60(Actor *);
void func_8008E1A4(Actor *);
Unk800876E4 *func_800878A4(s32 arg0, s32 arg1, s32 arg2);
void func_80090154(void);
void func_800901D4(void);
Actor *func_800914F0(s32 id);
void func_8008E768(Actor *actor, s32 arg1);
void func_8008DD9C(Actor *);
void *func_80088C2C(void);
void func_8008AEDC(s32);
void func_80084654(Unk80084654 *task, Unk80084654Children *children);
Unk80084654 *func_80084B80(s32 id);
void func_8008DFE0(Actor *);
s32 func_80088E4C(Task *);
Unk8008B450 *func_8008B930(Actor *actor, s32 arg1);
void func_8008B398(s32 arg0, Point *pos, FieldWarp *arg2);
ScriptCommand *func_800916E8(s32 id);
Task *createInn(s32);
Task *func_800892E8(s32 arg0);
Task *func_800874C8(s32 arg0);
Task *createFieldMenu(s32 layerId, s32 cursor);
ScreenFade *createScreenFade(s32 layerId);
struct Actor *func_80090450(s32 id, s32 arg1, s32 arg2, FieldActorEntry *entry);
void func_800896C0(FieldTask *task, FieldChildren *children);
Unk8008878C *func_80088BE4(s32 arg0, MapObject *arg1);
Unk80087FDC *func_800881A0(s32 arg0, void *entries);
Unk80086144 *func_80086418(s32 arg0);
Unk80085350 *func_80085588(s32 arg0, s32 arg1, s32 arg2);
Unk80084D0C *func_80085240(s32 arg0);
Unk8008CC4C *func_8008CF0C(void);
Point *func_800863F4(Unk80086144 *);
void func_800868AC(StreamTask *task);
/* text_window.c's, which leaves the task it creates in $v0 */
Decompressor *createDecompressor(void);
StreamTask *func_80086B54(s32 size, s32 file);
void func_80085EEC(Unk80086144 *task);
void func_80085A78(Unk80086144 *task, StreamPool *pool);
void func_80085650(Unk80086144 *task, StreamPool *pool);
void func_80086D20(Task *task, AreaNameWindows *windows);
Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
struct Unk800882D8 *func_800883F4(Actor *actor, s32 arg1, s32 arg2, s32 arg3);
void func_8008AEB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8008CF44(s32 arg0, s32 arg1);
void func_8008C23C(void);
void func_8008D07C(s32 arg0);
void func_8008CFF4(s32 arg0, s32 arg1, s32 arg2);
StreamTask *func_800855E0(StreamPool *pool);
void func_800857DC(Layer *layer, s32 x, s32 y, s32 level);
void func_80086460(s32 id, s32 level);
void func_800882D8(Unk800882D8 *task, void **box);
void func_8008B450(Unk8008B450 *task);
void func_8008D3F0(Actor *actor, s32 pad);
Actor *func_8008D4C4(Point *pos);
void func_8008BCAC(Unk8008BFE8 *task, Unk8008BFE8Children *children);
void func_8008E7E0(void *arg, void *arg2);
void func_8008EC74(Actor *actor);
void func_8008D710(Actor *actor);
struct Unk8008BFE8 *func_8008BFE8(s32 count);
void func_8008F184(Actor *actor, struct ActorChildren *children);
void func_8008BC30(Unk8008BFE8 *task);
s32 func_8008D0C0(Actor *actor, s32 x, s32 y, Point offset);
s32 func_80091730(s32 id);
void func_80091774(s32 arg0, s32 id, s32 arg2, s32 arg3);
Unk8008C59C *func_8008C9F8(Point pos);
s32 func_80085278(Unk80085278 *anim, AnimFrame *frames, s32 depth);
/* A stage overlay function, at a fixed address (wstag730/731) */
#if VERSION_US
void func_800A4EE8();
#elif VERSION_EU
void func_800A6024();
#endif
void func_800865AC(StreamTask *task, Layer *layer, s32 x, s32 y);
void func_80084D0C();
void func_80087FDC(Unk80087FDC *task, Unk80087FDCChildren *children);
s32 func_80087ACC(Unk80087FDC *task, Unk80087FDCChildren *children);
void func_80087D28(Unk80087FDC *task);
void func_8008926C();
void func_8008C388();
void func_8008CC4C(Unk8008CC4C *task);
void func_8008C59C(Unk8008C59C *task);
void func_80086144();
void func_800870D4();
void func_8008878C();
void func_80085350();
void func_80089320(Unk80089320 *task);
void func_800842C8(Unk800842C8 *task, Unk800842C8Children *children);
void func_8008B9D8(Unk8008B9D8 *task);
void func_8008CA3C(Unk8008CC4C *task);
void func_800834A0();

extern Point D_8009A938;
extern u8 *D_8009A940;
extern s32 D_8009A944;
extern Point D_80097000[]; /* tile offset of each direction */
extern Point D_80096398[]; /* VRAM position of each StreamTask slot's image */
extern s32 D_8009638C[]; /* depth of each layer of a StreamTask's sprites */
extern Point D_8009A76C[][8]; /* a direction's vector, scaled by 4096 */
extern u8 D_8009A92C[];
extern Point FIELDSTG_tiles[5][6]; /* func_800896C0's 64x40 tiles of the screen */
extern TileMove FIELDSTG_tileMoves[];
extern s32 D_8009AA38; /* func_800896C0's file requests, 0 to 2 */
extern RECT D_8009AA40;
s32 func_80091AA8(s32 index);
s32 func_80091BC0(s32, Point *);
extern FieldState D_800990B4;
extern ScriptCommand D_8009A448[];
extern StageEntry D_800998E4[];
extern u8 (*D_80096A7C[])[2]; /* func_80089320's animation of each substate */
extern s16 D_80096A8C[][2]; /* offsets, up to (0, 0) */
extern s32 D_80096ACC; /* the step in D_80096A8C */
extern u8 D_80096D14[][2]; /* animation of func_8008BCAC: (frame, time) pairs up to 0xFF */
extern void (*D_8009A6EC[])();
Unk8008B9D8 *func_8008BBD4(Point from, Point to);
Unk8008C388 *func_8008C564(s32 arg0);
extern AreaName D_800963F8[];
#if VERSION_EU
extern StageEntry D_8009A884[];
#endif
extern s16 D_80096C38[];
extern s32 D_80096FDC[];
extern u8 D_80096984[][8];
extern void (*D_8009A6E8)();
extern void (*D_8009A434[])(); /* the script helpers (func_80091648...) */
extern s16 D_800969C4[]; /* the modes that load the field file 0x5D (func_80088CD0) */
extern s32 D_80096FE8[];
extern s32 D_80096FF4[];
extern void (*FIELDSTG_initFuncs[])(void);

extern u8 D_80099758[];
extern u8 D_80096E94[][5]; /* the probes of each direction (func_8008D2A0) */
extern Point D_80096EBC[]; /* a probe's position */
extern u8 D_80096F3C[][2]; /* a probe's offset: bit 0 set, bit 7 negative */
extern u8 *D_80096DAC[]; /* func_8008C388's animation for each direction */
extern s32 D_80096DCC[]; /* and its depth offset */
extern ProgressEvent D_80095F18[];
extern u8 *FIELDSTG_gaugeRows[];
extern AnimFrame D_80096028[]; /* func_80084D0C's animations */
extern AnimFrame D_80096074[];
extern AnimFrame D_800960A0[];
extern AnimFrame *D_800961E4[][4]; /* func_80085350's animations */
extern s32 D_8009A6F4[]; /* how much each area lowers GAME.unk30, the steps to the next battle */
extern s32 D_8009A768; /* the frame D_8009AA4C was filled in */
extern Box D_8009AA4C[20]; /* the characters' boxes (func_80091D3C) */
extern s32 D_8009AB8C; /* and their number */
extern Point D_80096E6C[]; /* the camera's shake offsets */
extern s32 D_80096F5C[]; /* the direction of each combination of the pad directions */
extern s16 D_80096F9C[][2]; /* the actors that stand for other actors: {key, key of the actor that answers} */
extern u8 D_80096920[][9]; /* animations: (frame, time) pairs up to 0xFF */
extern s32 FIELDSTG_fileEntries[];
extern ScriptTimer D_8009A424;
extern s16 D_80095E84[]; /* func_800834A0's shakes, up to 1000 */
extern s16 D_8009A934; /* the voice of func_80082F84's held sound */
extern ChoiceText D_80095E98[16];
extern void (*D_80098B70)(Tween *tween, s32 in); /* func_80091298 */
extern s32 (*D_80098B74)(Tween *tween); /* func_8009132C */
extern Unk800870D4Box D_800967B8[10]; /* func_800870D4's boxes */
extern u8 D_80096204[]; /* func_80085EEC's slot layouts: [layout][quadrant][row][column] */
extern u8 D_8009636C[][2]; /* the layout and its flips for each direction */
extern u8 D_8009637C[][4]; /* the slots' offset in tiles, by quadrant: x, flipped x, y, flipped y */

#endif /* FIELDSTG_H */
