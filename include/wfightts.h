#ifndef WFIGHTTS_H
#define WFIGHTTS_H

/* WFIGHTTS.PRO: the battle test, a debug menu. FIGHTSTG loads it (file 0x1FB)
   in place of WFIGHTMN when the battle mode's argument is set. It picks
   the fighters, their motions (ウェイト, ダメージ, ガード...), the effects
   (ＭＥＦＴ00xx) and the fight stage (ＭＦＳＴＧ0xx) from lists. */

#include "game.h"

/* A list to pick from (func_800A6954, func_800A6ECC) */
typedef struct BattleTestList {
    TASK_HEADER(BattleTestList);
    /* 0x50 */ s32 *unk50;
    /* 0x54 */ s32 *done; /* set to 0 when it starts */
} BattleTestList;

/* WFIGHTTS_stageList's task */
typedef struct BattleTestStageList {
    TASK_HEADER(BattleTestStageList);
    /* 0x50 */ s32 *result; /* the stage picked, 1-55, or -1 */
} BattleTestStageList;

/* func_800A764C's task */
typedef struct BattleTestMotions {
    TASK_HEADER(BattleTestMotions);
    /* 0x050 */ u8 unk50[0x200];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ s32 unk254;
} BattleTestMotions;

/* func_800A7BE8's task */
typedef struct BattleTestEffects {
    TASK_HEADER(BattleTestEffects);
    /* 0x50 */ u8 unk50[0xA8];
    /* 0xF8 */ s32 unkF8;
    /* 0xFC */ s32 unkFC;
} BattleTestEffects;

#endif /* WFIGHTTS_H */
