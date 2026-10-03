#ifndef WFIGHTTS_H
#define WFIGHTTS_H

/* WFIGHTTS.PRO: the battle test, a debug menu. FIGHTSTG loads it (file 0x1FB)
   in place of WFIGHTMN when the battle mode's argument is set. It picks
   the fighters, their motions (ウェイト, ダメージ, ガード...), the effects
   (ＭＥＦＴ00xx) and the fight stage (ＭＦＳＴＧ0xx) from lists. */

#include "fightstg.h"

/* The fighters' and the cameras' lists (func_800A6954, func_800A6ECC) */
typedef struct BattleTestList {
    TASK_HEADER(BattleTestList);
    /* 0x50 */ s32 *side; /* 0 the partner, 1 the enemy, -1 for none */
    /* 0x54 */ s32 *pick; /* set to 0 when it starts */
} BattleTestList;

/* WFIGHTTS_stageList's task */
typedef struct BattleTestStageList {
    TASK_HEADER(BattleTestStageList);
    /* 0x50 */ s32 *result; /* the stage picked, 1-55, or -1 */
} BattleTestStageList;

/* A fighter's motions, in func_800A764C's list */
typedef struct BattleTestMotionList {
    /* 0x00 */ s32 motions[0x3E]; /* the ones the fighter has */
    /* 0xF8 */ s32 count;
    /* 0xFC */ s32 shown; /* up to 14 */
} BattleTestMotionList;

/* A fighter's effects, in func_800A7BE8's list: each one plus 1, or just a
   0 for a fighter without any */
typedef struct BattleTestEffectList {
    /* 0x00 */ s32 effects[0x13];
    /* 0x4C */ s32 count;
    /* 0x50 */ s32 shown; /* up to 14 */
} BattleTestEffectList;

/* Where func_800A764C's and func_800A7BE8's lists are: the fighters they
   were made for, the list LEFT and RIGHT pick and the lists' cursors and
   scrolls */
typedef struct BattleTestCursors {
    /* 0x00 */ s32 fighter[2];
    /* 0x08 */ s32 side;
    /* 0x0C */ s32 cursor[2];
    /* 0x14 */ s32 scroll[2];
} BattleTestCursors;

/* func_800A764C's and func_800A7BE8's windows, by list */
typedef struct BattleTestWindows {
    /* 0x00 */ TextWindow *windows[2][14];
} BattleTestWindows;

/* func_800A764C's task */
typedef struct BattleTestMotions {
    TASK_HEADER(BattleTestMotions);
    /* 0x050 */ BattleTestMotionList lists[2]; /* the partner's, the enemy's */
    /* 0x250 */ s32 *side;
    /* 0x254 */ s32 *motion; /* the motion picked */
} BattleTestMotions;

/* func_800A7BE8's task */
typedef struct BattleTestEffects {
    TASK_HEADER(BattleTestEffects);
    /* 0x50 */ BattleTestEffectList lists[2]; /* the partner's, the enemy's */
    /* 0xF8 */ s32 *side;
    /* 0xFC */ s32 *effect; /* the effect picked */
} BattleTestEffects;

/* The battle test (func_800A5A54). Its pages (substate): 0 the battle,
   1 the fighters, 2 the camera, 3 the stage, 4 the motions, 5 the effects;
   L1 and R1 go from one list to the next */
typedef struct BattleTest {
    TASK_HEADER(BattleTest);
    /* 0x50 */ s32 page; /* the last list, which CROSS goes back to */
    /* 0x54 */ s32 side; /* 0 the partner, 1 the enemy, -1 for none */
    /* 0x58 */ s32 fighter;
    /* 0x5C */ s32 camera; /* by the fighter's motion */
    /* 0x60 */ s32 stage; /* 1-55, or -1 */
    /* 0x64 */ s32 motion;
    /* 0x68 */ s32 effect;
} BattleTest;

/* What FIGHTSTG's func_8008C090 makes play: WFIGHTMN's BattleTask */
typedef struct BattleTestMove {
    TASK_HEADER(BattleTestMove);
    /* 0x50 */ s32 actor;
    /* 0x54 */ s32 kind;
    /* 0x58 */ s32 hits[4]; /* 0 a hit, 3 a miss; [3] how it ended: 1 hit, 2 knocked out, 3 missed */
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
} BattleTestMove;

/* The battle test's children */
typedef struct BattleTestChildren {
    /* 0x00 */ BattleTestMove *task; /* what plays, NULL when done */
    /* 0x04 */ Task *commands;
    /* 0x08 */ Unk800911C8 *unk8; /* the camera */
    /* 0x0C */ Task *lights;
    /* 0x10 */ FightStage *stage;
    /* 0x14 */ BattleTestList *fighters;
    /* 0x18 */ BattleTestList *cameras;
    /* 0x1C */ BattleTestStageList *stages;
    /* 0x20 */ BattleTestMotions *motions;
    /* 0x24 */ BattleTestEffects *effects;
    /* 0x28 */ Models *models;
} BattleTestChildren;

/* An enemy's FighterInfo: its cameras are 3, where a partner has 12 */
typedef struct EnemyFighterInfo {
    /* 0x00 */ u8 unk0[0x1A];
    /* 0x1A */ ShortVec3 camPos[3];
    /* 0x2C */ ShortVec3 camRef[3];
    /* 0x3E */ s16 camProj[3];
} EnemyFighterInfo;

#endif /* WFIGHTTS_H */
