#ifndef STAGE_H
#define STAGE_H

/*
 * The stage overlays (AAA/PRO/WSTAG###.PRO), loaded at 0x800A4CA4 on top of
 * FIELDSTG. Each stage is its own small program; many share the same
 * functions, built from the same source.
 */

#include "game.h"

/* The task a stage starts (see its start function) */
typedef struct StageTask {
    TASK_HEADER(StageTask);
    /* 0x50 */ void *owner;
} StageTask;

/* An animation after one or two other words */
typedef struct Anim4 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ AnimState anim;
} Anim4;

typedef struct Anim8 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ AnimState anim;
} Anim8;

/* What a stage tells FIELDSTG about itself (filled by its setup function) */
typedef struct StageInfo {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8; /* a file id */
    /* 0x0C */ s32 unkC; /* the next file id << 16 */
    /* 0x10 */ void *unk10;
    /* 0x14 */ void *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C; /* a file id */
    /* 0x20 */ void *unk20;
    /* 0x24 */ void *events;
    /* 0x28 */ void *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ CVECTOR unk38; /* copied from the word at the start of the stage */
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
} StageInfo;

/*
 * Compiles to nothing, but its loop notes stop GCC 2.8's scheduler from moving
 * code across it. The setup functions have one after their first six fields:
 * probably a debug print, compiled out as do { } while (0) in the release.
 */
#define DEBUG_LOG() \
    do {            \
    } while (0)

/*
 * Carries the borrow down the digits of GAME.countdown, the timer of the
 * timed stages: a units digit that went below 0 (255) becomes 9 and takes one
 * from the digit above. The match depends on this statement macro's do-while.
 */
#define COUNTDOWN_BORROW(c)  \
    do {                     \
        if (c[2] >= 10) {    \
            c[2] = 9;        \
            c[1]--;          \
        }                    \
        if (c[1] >= 10) {    \
            c[1] = 9;        \
            c[0]--;          \
        }                    \
    } while (0)

/* FIELDSTG functions the stages call through a table */
typedef struct FieldFuncs {
    /* 0x00 */ void (*unk0[16])();
    /* 0x40 */ void (*unk40)(s32 arg0, s32 id);
    /* 0x44 */ void (*unk44[3])();
    /* 0x50 */ void (*unk50)(s32 arg0);
} FieldFuncs;

/* A point of a list (what its six halfwords are isn't known yet) */
typedef struct StagePoint {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ struct StagePoint *next;
} StagePoint;

/* The points of the place two ids name (GAME's halfwords at 0x44 and 0x46) */
typedef struct StagePoints {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ StagePoint *points;
} StagePoints;

/* A record of the table at StageInfo.unk14, which the points are copied to */
typedef struct StageSlot {
    /* 0x00 */ u8 unk0[0xA];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
} StageSlot;

/* A sprite of a StageEffect: its frame (0 for none) and palette row */
typedef struct StageSprite {
    /* 0x0 */ s16 frame;
    /* 0x2 */ s16 clutRow;
} StageSprite;

/*
 * A sprite at (x, y) from the stage's sheet (the file StageInfo.unkC names)
 * with an animated palette, and a second one above it that a one-shot
 * animation adds to frame (what it is in the game isn't known yet)
 */
typedef struct StageEffect {
    TASK_HEADER(StageEffect);
    /* 0x50 */ s32 frame;
    /* 0x54 */ s32 x;
    /* 0x58 */ s32 y;
    /* 0x5C */ AnimState anim; /* the one-shot animation */
    /* 0x60 */ AnimState clutAnim;
    /* 0x64 */ StageSprite sprites[2]; /* drawn at depth 6 and 4 */
} StageEffect;

/* A value that goes between 0 and 0x1000 (1.0) by a step each frame */
typedef struct StageTween {
    /* 0x0 */ s32 duration; /* in frames, going up */
    /* 0x4 */ s32 step;
    /* 0x8 */ s32 value;
    /* 0xC */ s32 active;
} StageTween;

/* The table of a stage's functions: its setup, then the menu stages' tween */
typedef struct StageFuncs {
    /* 0x0 */ void (*setup)(void); /* fills D_800990B4 */
    /* 0x4 */ void (*start)(StageTween *tween, s32 up);
    /* 0x8 */ s32 (*update)(StageTween *tween); /* whether it has ended */
} StageFuncs;

/* A record of the table at StageInfo.unk10, which ends with unk2 = 0 */
typedef struct StageTile {
    /* 0x00 */ u8 visible;
    /* 0x01 */ u8 anim; /* which animation sets frame (1-3) */
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 frame;
    /* 0x05 */ u8 unk5[4];
    /* 0x09 */ u8 unk9;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10[2];
} StageTile;

/* The task that animates the records of StageInfo.unk10's table */
typedef struct StageTileAnims {
    TASK_HEADER(StageTileAnims);
    /* 0x50 */ AnimState anims[4]; /* as many as the stage uses */
} StageTileAnims;

/* A record of StageInfo.unk10's table with the animation that sets its frame */
typedef struct StageTileAnim {
    /* 0x0 */ StageTile *tile;
    /* 0x4 */ AnimState anim;
} StageTileAnim;

/*
 * Three records of StageInfo.unk10's table (animations 1 to 3) moved to
 * (x, y) and animated once when the substate is set to 1
 */
typedef struct StageTileEffect {
    TASK_HEADER(StageTileEffect);
    /* 0x50 */ s32 x;
    /* 0x54 */ s32 y;
    /* 0x58 */ StageTileAnim anims[3];
} StageTileEffect;

/* A character on the field (FIELDSTG's Actor), as far as the stages use it */
typedef struct StageActor {
    TASK_HEADER(StageActor);
    /* 0x50 */ s32 x;
    /* 0x54 */ s32 y;
    /* 0x58 */ s32 tileX;
    /* 0x5C */ s32 tileY;
    /* 0x60 */ s32 dir;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68[3];
    /* 0x74 */ s32 unk74;
} StageActor;

/* The children of a task with one per party slot */
typedef struct StagePartyChildren {
    /* 0x0 */ void *party[3];
} StagePartyChildren;

/*
 * A record of StageInfo.unk10's table that wanders around where it starts,
 * animated, turning every period frames: towards home when it is more than
 * 30 away, else at random
 */
typedef struct StageWanderer {
    TASK_HEADER(StageWanderer);
    /* 0x50 */ s16 mode; /* 0: hidden, 1: wandering, 2: waiting, 3: slowing down */
    /* 0x52 */ u8 tileAnim; /* the record of StageInfo.unk10's table it moves */
    /* 0x53 */ u8 speedIndex;
    /* 0x54 */ s32 start; /* the first frame and timer */
    /* 0x58 */ s32 wait;
    /* 0x5C */ s32 homeX;
    /* 0x60 */ s32 homeY;
    /* 0x64 */ s32 x; /* 8.8 */
    /* 0x68 */ s32 y;
    /* 0x6C */ s16 posX; /* x and y >> 8 */
    /* 0x6E */ s16 posY;
    /* 0x70 */ s16 timer;
    /* 0x72 */ s16 period; /* frames between turns */
    /* 0x74 */ s16 speed;
    /* 0x76 */ s16 angle; /* 0x1000 a turn */
    /* 0x78 */ StageTileAnim tile;
} StageWanderer;

/* StageWanderer moving two records: tileAnim and tileAnim + 9 */
typedef struct StageWanderPair {
    TASK_HEADER(StageWanderPair);
    /* 0x50 */ s16 mode;
    /* 0x52 */ u8 tileAnim;
    /* 0x53 */ u8 speedIndex;
    /* 0x54 */ s32 start;
    /* 0x58 */ s32 wait;
    /* 0x5C */ s32 homeX;
    /* 0x60 */ s32 homeY;
    /* 0x64 */ s32 x;
    /* 0x68 */ s32 y;
    /* 0x6C */ s16 posX;
    /* 0x6E */ s16 posY;
    /* 0x70 */ s16 timer;
    /* 0x72 */ s16 period;
    /* 0x74 */ s16 speed;
    /* 0x76 */ s16 angle;
    /* 0x78 */ StageTileAnim tiles[2];
} StageWanderPair;

/*
 * Two records of StageInfo.unk10's table (animations 8 and 9) shown while
 * mode isn't 0, and hidden by a one-shot animation wait frames after mode 2
 */
typedef struct StageTileDuo {
    TASK_HEADER(StageTileDuo);
    /* 0x50 */ s16 mode;
    /* 0x52 */ s16 wait;
    /* 0x54 */ StageTileAnim tiles[2];
} StageTileDuo;

/*
 * Animates the records of StageInfo.unk10's table with animations 1 and 2:
 * the first alone while running, both when done
 */
typedef struct StageTilePair {
    TASK_HEADER(StageTilePair);
    /* 0x50 */ s32 playing; /* the second animation of the first record */
    /* 0x54 */ s32 done; /* start in TASK_DONE */
    /* 0x58 */ StageTileAnim anims[2];
} StageTilePair;

/* StageTilePair with halfword flags */
typedef struct StageTilePair16 {
    TASK_HEADER(StageTilePair16);
    /* 0x50 */ s16 playing;
    /* 0x52 */ s16 done;
    /* 0x54 */ StageTileAnim anims[2];
} StageTilePair16;

/* StageTilePair with byte flags, for the records of two given animations */
typedef struct StageTilePairN {
    TASK_HEADER(StageTilePairN);
    /* 0x50 */ u8 playing;
    /* 0x51 */ u8 done; /* 1: start in TASK_DONE */
    /* 0x52 */ s16 anim; /* the records' animations: anim and anim + 1 */
    /* 0x54 */ StageTileAnim anims[2];
} StageTilePairN;

/*
 * Two sprites from the stage's sheet at (x, y), each animated once, drawn
 * 0xF0 above and 0x14 below (what they are in the game isn't known yet)
 */
typedef struct StageSpritePair {
    TASK_HEADER(StageSpritePair);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 x;
    /* 0x58 */ s32 y;
    /* 0x5C */ AnimState anims[2];
    /* 0x64 */ StageSprite sprites[2];
} StageSpritePair;

/* A record of StageInfo.unk10's table played through a sequence of animations */
typedef struct StageTileSeq {
    /* 0x0 */ s16 seq; /* the step playing, 0 when finished */
    /* 0x2 */ s16 setFrame; /* 0: the animation sets unk9, else frame */
    /* 0x4 */ StageTile *tile;
    /* 0x8 */ AnimState anim;
} StageTileSeq;

/* The records of StageInfo.unk10's table with animations 1 to 4, sequenced */
typedef struct StageTileSeqs {
    TASK_HEADER(StageTileSeqs);
    /* 0x50 */ StageTileSeq entries[4];
} StageTileSeqs;

/* StageTileSeq with a byte setFrame and a sound to play at frame 0x34 */
typedef struct StageTileSeq8 {
    /* 0x0 */ s16 seq;
    /* 0x2 */ u8 sound; /* 1: play it, once */
    /* 0x3 */ u8 setFrame;
    /* 0x4 */ StageTile *tile;
    /* 0x8 */ AnimState anim;
} StageTileSeq8;

typedef struct StageTileSeqs8 {
    TASK_HEADER(StageTileSeqs8);
    /* 0x50 */ StageTileSeq8 entries[4];
} StageTileSeqs8;

/* A step of a StageTileSeq: its animation, and the step after it ends */
typedef struct StageSeqStep {
    /* 0x0 */ AnimFrame *frames;
    /* 0x4 */ s16 once; /* play once, then go to next */
    /* 0x6 */ s16 next; /* 0: hide the record */
} StageSeqStep;

/* A frame of a StageTileFrame animation, which sets two frames of a record */
typedef struct StageTileFrame {
    /* 0x0 */ u8 frame;
    /* 0x1 */ u8 duration;
    /* 0x2 */ u8 unk9; /* for StageTile.unk9 */
    /* 0x3 */ u8 last; /* go to the next animation of the sequence after it */
} StageTileFrame;

/* Where a sequence of StageTileFrame animations (NULL-terminated) is at */
typedef struct StageTileCursor {
    /* 0x0 */ s16 seq;
    /* 0x2 */ s16 index;
    /* 0x4 */ s32 timer;
} StageTileCursor;

/*
 * The record of StageInfo.unk10's table with animation 1, played once with a
 * sound when the substate is set to 1 (frame 5 before, 10 after)
 */
typedef struct StageSoundTile {
    TASK_HEADER(StageSoundTile);
    /* 0x50 */ s16 voice; /* what SOUND.playSound returned */
    /* 0x54 */ StageTileAnim obj;
} StageSoundTile;

/* A sprite effect a stage creates at (x, y) with the given frame, by kind */
typedef struct StageEffectSpot {
    /* 0x0 */ s16 frame;
    /* 0x2 */ s16 kind;
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
} StageEffectSpot;

/* The body of a StageFaller: falls at (x, y) in 8.8, bouncing once */
typedef struct StageFallBody {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 vx;
    /* 0x0C */ s32 vy;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 bounced;
    /* 0x14 */ AnimState anim;
} StageFallBody;

/* A sprite of WSTAG415 that falls from a point of a table, bounces once and dies at the bottom */
typedef struct StageFaller {
    TASK_HEADER(StageFaller);
    /* 0x50 */ s32 frame;
    /* 0x54 */ s32 x;
    /* 0x58 */ s32 y;
    /* 0x5C */ StageFallBody body;
} StageFaller;

/* Where a StageFaller starts and how it falls */
typedef struct StageFallParams {
    /* 0x0 */ AnimFrame *frames;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
    /* 0x8 */ s16 floorY;
    /* 0xA */ s16 vx;
    /* 0xC */ s16 gravity;
    /* 0xE */ s16 bounce; /* divides vy when bouncing, 0 for no bounce */
} StageFallParams;

/* What moves a StageMover at (x, y) in 8.8, and its animation */
typedef struct StageMoverBody {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 vx;
    /* 0x0C */ s32 vy;
    /* 0x10 */ s16 timer;
    /* 0x12 */ s16 mode;
    /* 0x14 */ AnimState anim;
} StageMoverBody;

/* The object of WSTAG415 that events 0x331 to 0x334 drive */
typedef struct StageMover {
    TASK_HEADER(StageMover);
    /* 0x50 */ s32 frame;
    /* 0x54 */ s32 x;
    /* 0x58 */ s32 y;
    /* 0x5C */ StageTile *tile; /* the record of StageInfo.unk10's table with animation 1 */
    /* 0x60 */ StageMoverBody body;
} StageMover;

/* A scrolling background of two images of an archive, moving by (vx, -vy) */
typedef struct StageScroller {
    TASK_HEADER(StageScroller);
    /* 0x50 */ s32 x; /* 8.8 */
    /* 0x54 */ s32 y;
    /* 0x58 */ s32 vx;
    /* 0x5C */ s32 vy;
} StageScroller;

/* A record of StageInfo.unk10's table, animated */
typedef struct StageTileTask {
    TASK_HEADER(StageTileTask);
    /* 0x50 */ StageTileAnim obj;
} StageTileTask;

/* StageTileDuo with one record */
typedef struct StageTileSolo {
    TASK_HEADER(StageTileSolo);
    /* 0x50 */ s16 mode;
    /* 0x52 */ s16 wait;
    /* 0x54 */ StageTileAnim tile;
} StageTileSolo;

/* The record of StageInfo.unk10's table with the given animation, moved to (x, y) */
typedef struct StageTileAt {
    TASK_HEADER(StageTileAt);
    /* 0x50 */ s32 x;
    /* 0x54 */ s32 y;
    /* 0x58 */ s32 anim;
    /* 0x5C */ StageTileAnim obj;
} StageTileAt;

/* The record of StageInfo.unk10's table with animation 1 and a frame counter */
typedef struct StageTileTimer {
    TASK_HEADER(StageTileTimer);
    /* 0x50 */ StageTile *tile;
    /* 0x54 */ s32 timer;
} StageTileTimer;

/* The records of StageInfo.unk10's table with animations 2 to 9 */
typedef struct StageTileGroup {
    TASK_HEADER(StageTileGroup);
    /* 0x50 */ StageTile *tiles[8];
} StageTileGroup;

/* A frame of a StageRiser's animation; the last (frame 0xFF) sets move */
typedef struct StageRiserFrame {
    /* 0x0 */ s16 frame;
    /* 0x2 */ u8 duration;
    /* 0x3 */ u8 move;
} StageRiserFrame;

/* A record of StageInfo.unk10's table animated and moved by its animation */
typedef struct StageRiser {
    /* 0x00 */ s32 y; /* 8.8 */
    /* 0x04 */ s32 move; /* added to the record's unkC */
    /* 0x08 */ s16 active;
    /* 0x0A */ s16 tileAnim;
    /* 0x0C */ AnimState anim;
    /* 0x10 */ StageTile *tile;
} StageRiser;

/* A record of StageInfo.unk10's table that moves by a speed in 8.8 */
typedef struct StageLift {
    /* 0x0 */ s16 active;
    /* 0x2 */ s16 speed;
    /* 0x4 */ StageTile *tile;
} StageLift;

/* Records of StageInfo.unk10's table that events start moving */
typedef struct StageRisers {
    TASK_HEADER(StageRisers);
    /* 0x050 */ StageRiser risers[11];
    /* 0x12C */ StageLift lifts[3];
    /* 0x144 */ s32 timer;
    /* 0x148 */ s16 pushing; /* moves the player */
    /* 0x14A */ s16 push;
} StageRisers;

/* A record of StageInfo.unk10's table animated while playing is set */
typedef struct StageTileAnimFlag {
    /* 0x0 */ StageTile *tile;
    /* 0x4 */ s32 playing;
    /* 0x8 */ AnimState anim;
} StageTileAnimFlag;

/* Six records of StageInfo.unk10's table, animated by mode */
typedef struct StageTileSix {
    TASK_HEADER(StageTileSix);
    /* 0x50 */ s32 mode;
    /* 0x54 */ StageTileAnim tiles[6];
} StageTileSix;

/* StageTileSix with flagged records */
typedef struct StageTileSixW {
    TASK_HEADER(StageTileSixW);
    /* 0x50 */ s32 mode;
    /* 0x54 */ StageTileAnimFlag tiles[6];
} StageTileSixW;

/* A sprite that flies off diagonally, animated */
typedef struct StageFlyer {
    TASK_HEADER(StageFlyer);
    /* 0x50 */ s32 up; /* else down */
    /* 0x54 */ s32 right; /* else left; also flips the sprite */
    /* 0x58 */ s32 still; /* doesn't move or animate */
    /* 0x5C */ s32 anim;
    /* 0x60 */ s32 frame;
    /* 0x64 */ s32 timer;
    /* 0x68 */ s32 x; /* 8.8 */
    /* 0x6C */ s32 y;
} StageFlyer;

/* A brightness that rises from 12 to 28, holds, then falls back */
typedef struct StageGlow {
    TASK_HEADER(StageGlow);
    /* 0x50 */ s32 level;
} StageGlow;

/* An animation played at (x, y) */
typedef struct StageAnimSpot {
    /* 0x0 */ AnimFrame *frames;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
} StageAnimSpot;

/* Two records of StageInfo.unk10's table, animated */
typedef struct StageTileLoop2 {
    TASK_HEADER(StageTileLoop2);
    /* 0x50 */ StageTileAnim tiles[2];
} StageTileLoop2;

/* Two pictures that change by turns, and the flyers they let out */
typedef struct StageFlyerGate {
    TASK_HEADER(StageFlyerGate);
    /* 0x50 */ s32 left; /* the picture of the first two (0-2) */
    /* 0x54 */ s32 right; /* the picture of the third (0-2) */
    /* 0x58 */ s32 spawnA; /* let out the first set of flyers */
    /* 0x5C */ s32 spawnB; /* let out the second set */
} StageFlyerGate;

/* An animation of a table of byte pairs (frame, duration; duration 0 loops to frame) */
typedef struct StageByteAnim {
    /* 0x00 */ s32 anim; /* the animation wanted */
    /* 0x04 */ s32 cur; /* the animation playing */
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 frame;
    /* 0x10 */ s32 timer;
} StageByteAnim;

/* Two StageByteAnim animations */
typedef struct StageByteAnims {
    TASK_HEADER(StageByteAnims);
    /* 0x50 */ StageByteAnim anims[2];
} StageByteAnims;

/* A quad of the screen: its corners and what it shows */
typedef struct StageQuad {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 y0;
    /* 0x04 */ s16 x1;
    /* 0x06 */ s16 y1;
    /* 0x08 */ s16 x2;
    /* 0x0A */ s16 y2;
    /* 0x0C */ s16 x3;
    /* 0x0E */ s16 y3;
    /* 0x10 */ s16 kind; /* 0-1: the frame of that animation, else the texture */
} StageQuad;

/* A texture of a StageQuad: its page, square at (u, v), and palette */
typedef struct StageQuadTexture {
    /* 0x00 */ s16 tpageX;
    /* 0x02 */ s16 tpageY;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 u;
    /* 0x0A */ s16 v;
    /* 0x0C */ u16 clutX;
    /* 0x0E */ u16 clutY;
} StageQuadTexture;

/* The records with animations 3 and 4, each animated once */
typedef struct StageTileOnce {
    TASK_HEADER(StageTileOnce);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ StageTileAnimFlag tiles[2];
} StageTileOnce;

/* A frame of a looping animation: after the last (frame 0xFF) it goes back to loop */
typedef struct StageTileLoopFrame {
    /* 0x0 */ s16 frame;
    /* 0x2 */ u8 duration;
    /* 0x3 */ u8 loop;
} StageTileLoopFrame;

/* A frame of a StageFloaterPart's animation, with what it adds to value */
typedef struct StageFloaterFrame {
    /* 0x0 */ s16 frame;
    /* 0x2 */ s16 duration;
    /* 0x4 */ s32 delta;
} StageFloaterFrame;

/* A sprite of a StageFloater, its animation and what the animation adds up */
typedef struct StageFloaterPart {
    /* 0x0 */ s32 value;
    /* 0x4 */ StageSprite sprite;
    /* 0x8 */ AnimState anim;
} StageFloaterPart;

/* A sprite from the stage's sheet at (x, y) that moves up or down in TASK_DONE */
typedef struct StageFloater {
    TASK_HEADER(StageFloater);
    /* 0x50 */ s32 x;
    /* 0x54 */ s32 y;
    /* 0x58 */ s32 y8; /* y << 8 while moving */
    /* 0x5C */ s32 up;
    /* 0x60 */ StageFloaterPart parts[3];
} StageFloater;

/* Where a StageFloater is created */
typedef struct StageFloaterSpot {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 up;
} StageFloaterSpot;

/* Sets its children to TASK_DONE one after the other, at the times of a table */
typedef struct StageFloaterChain {
    TASK_HEADER(StageFloaterChain);
    /* 0x50 */ s16 next;
    /* 0x52 */ s16 timer;
} StageFloaterChain;

/* The children of a StageFloaterChain */
typedef struct StageFloaters {
    /* 0x00 */ StageFloater *floaters[27];
} StageFloaters;

/* The records of StageInfo.unk10's table with animations 1 to 4 */
typedef struct StageTileQuad {
    TASK_HEADER(StageTileQuad);
    /* 0x50 */ StageTileAnim anims[4];
} StageTileQuad;

/*
 * Two records of StageInfo.unk10's table (animations 3 and 2) that move 0x7F
 * up or down with the player, shaking before and after
 */
typedef struct StageTileLift {
    TASK_HEADER(StageTileLift);
    /* 0x50 */ StageTile *tiles[2]; /* animations 3 and 2 */
    /* 0x58 */ s16 down; /* the records are 0x7F up, and move down */
    /* 0x5A */ s16 timer;
    /* 0x5C */ s16 shake; /* the step of the stage's shake table, then a frame count */
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ s16 y[2]; /* the records' unkC when the move starts */
    /* 0x64 */ s32 playerY;
    /* 0x68 */ s16 homeY[2]; /* the records' unkC at the start */
} StageTileLift;

/* The records of StageInfo.unk10's table with animations 4 to 1, animated */
typedef struct StageTileSet {
    TASK_HEADER(StageTileSet);
    /* 0x50 */ s32 done; /* start in TASK_DONE */
    /* 0x54 */ StageTile *tiles[4]; /* animations 4, 3, 2 and 1 */
    /* 0x64 */ AnimState anim;
    /* 0x68 */ AnimState anim2; /* animation 1's, looping */
} StageTileSet;

/* A sprite drawn over a character (FIELDSTG's actor found by its key) */
typedef struct StageActorMark {
    TASK_HEADER(StageActorMark);
    /* 0x50 */ s32 kind;
    /* 0x54 */ StageActor *actor;
} StageActorMark;

/* A frame the task sets on a record of StageInfo.unk10's table */
typedef struct StageFrameTask {
    TASK_HEADER(StageFrameTask);
    /* 0x50 */ s32 frame;
    /* 0x54 */ u8 unk54[8];
} StageFrameTask;

/* The records of StageInfo.unk10's table with animations 1 to 5, each playing a sequence */
typedef struct StageTileCursors {
    TASK_HEADER(StageTileCursors);
    /* 0x50 */ StageTileCursor cursors[5];
} StageTileCursors;

/*
 * The record of StageInfo.unk10's table with animation 2, animated by
 * substate, and the StageTileAt children that events set to TASK_DONE
 */
typedef struct StageTileSwitch {
    TASK_HEADER(StageTileSwitch);
    /* 0x50 */ s32 spawn; /* the child to set to TASK_DONE, + 1 */
    /* 0x54 */ s32 silent; /* no sound when an event comes */
    /* 0x58 */ StageTileAnim obj;
} StageTileSwitch;

/* Where a StageTileAt is created */
typedef struct StageTileAtSpot {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 anim;
} StageTileAtSpot;

/* The children of a StageTileSwitch */
typedef struct StageTileAts {
    /* 0x00 */ StageTileAt *tiles[5];
} StageTileAts;

/* A looping animation of a table of byte pairs (frame, duration; frame 0 loops) */
typedef struct StageBytePlay {
    /* 0x0 */ s32 frame;
    /* 0x4 */ s32 index;
    /* 0x8 */ s32 timer; /* counts up */
} StageBytePlay;

/* The animations of sprites drawn all over the stage */
typedef struct StageSpriteField {
    TASK_HEADER(StageSpriteField);
    /* 0x50 */ StageBytePlay anims[10]; /* nine used */
} StageSpriteField;

/* A sprite of the stage: where, which animation, and flipped */
typedef struct StageSpriteSpot {
    /* 0x0 */ s16 x; /* 0 ends the table */
    /* 0x2 */ s16 y;
    /* 0x4 */ u8 anim;
    /* 0x5 */ u8 flip;
} StageSpriteSpot;

/* A yes/no menu at the bottom of the screen */
typedef struct StageMenu {
    TASK_HEADER(StageMenu);
    /* 0x50 */ s32 cursor;
    /* 0x54 */ StageTween tween;
} StageMenu; /* 0x64 */

typedef struct StageMenuChildren {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *options[2];
    /* 0x0C */ Cursor *cursor;
    /* 0x10 */ void *event;
} StageMenuChildren; /* 0x14 */

/* A list menu whose entries show a message */
typedef struct StageListMenu {
    TASK_HEADER(StageListMenu);
    /* 0x50 */ s32 count;
    /* 0x54 */ s32 cursor;
    /* 0x58 */ s32 showArrow;
    /* 0x5C */ s32 arrowFrame;
    /* 0x60 */ s32 arrowTime;
    /* 0x64 */ StageTween tweens[2]; /* list, message box */
} StageListMenu; /* 0x84 */

typedef struct StageListMenuChildren {
    /* 0x00 */ TextWindow *options[8];
    /* 0x20 */ Cursor *cursor;
    /* 0x24 */ TextWindow *message;
} StageListMenuChildren; /* 0x28 */

/*
 * The menu sprite sheet, and an entry of a text file: the European version
 * numbers the disc's files differently, and has a copy of each text file per
 * language, one after the other, so it adds the language (LANGUAGE, which
 * CNTY_SEL sets) to the file.
 */
#if VERSION_US
#define MENU_SPRITES 0x2770000
#define TEXT_ENTRY(file, n) ((file) << 16 | (n))
#elif VERSION_EU
extern s32 LANGUAGE; /* 2-5 */
#define MENU_SPRITES 0x2860000
#define TEXT_ENTRY(file, n) ((LANGUAGE << 16) + ((file) << 16 | (n)))
#endif

extern StageInfo D_800990B4;
extern FieldFuncs D_8009A70C;

/* FIELDSTG functions the stages call */
void *func_80084B80(s32 id); /* creates the task of an event object */
StageTile *func_80088C9C(s32 anim); /* the record of StageInfo.unk10's table with that animation */
s32 func_8008B258(void); /* starts a battle: the handler of the stages' events 9000 */

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);

#endif /* STAGE_H */
