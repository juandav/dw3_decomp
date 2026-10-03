#ifndef WFIGHTMN_H
#define WFIGHTMN_H

/* WFIGHTMN.PRO: the battle's sub-overlay. FIGHTSTG loads it (file 0x1FA)
   at STAGE_VRAM for a normal battle, and WFIGHTTS in its place for the
   battle test. */

#include "fightstg.h"

/* The item a partner can equip that makes FIGHTSTG's func_8009B7A4 act on
   it at the start of the battle */
#define WFIGHTMN_ITEM 0x140






/* What the battle menu's states start and wait for (BattleMenuChildren.task):
   FIGHTSTG's message window (func_80099400), effects and the like */
typedef struct BattleTask {
    TASK_HEADER(BattleTask);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 hits[4]; /* 0 a hit, 3 a miss; [3] how it ended: 1 hit, 2 knocked out, 3 missed */
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ u8 unk74[0x38];
    /* 0xAC */ void (*show)(struct BattleTask *task, s32 kind, s32 *args); /* the message window's */
    /* 0xB0 */ void (*close)(struct BattleTask *task);
} BattleTask;

/* The battle menu's commands (FIGHTSTG's func_80092124) */
typedef struct BattleCommands {
    TASK_HEADER(BattleCommands);
    /* 0x50 */ u8 unk50[0xC];
    /* 0x5C */ s32 choice;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
} BattleCommands;

/* What drives one of FIGHTSTG's fighter models */
typedef struct BattleModel {
    /* 0x00 */ s32 active;
    /* 0x04 */ s32 id;
    /* 0x08 */ s32 motion; /* the motion it plays */
} BattleModel;

/* FIGHTSTG's fighter models (func_800877D4), by id: 0 the partner, 0x10
   the enemy */
typedef struct BattleModels {
    TASK_HEADER(BattleModels);
    /* 0x050 */ u8 unk50[0x134];
    /* 0x184 */ void (*add)(struct BattleModels *task, s32 id, s32 fighter, s32 arg3);
    /* 0x188 */ BattleModel *(*get)(struct BattleModels *task, s32 id);
    /* 0x18C */ void (*setId)(struct BattleModels *task, s32 id, s32 newId);
    /* 0x190 */ s32 (*getFighter)(struct BattleModels *task, s32 id);
    /* 0x194 */ void (*face)(struct BattleModels *task, s32 id); /* ids under 0x10 are one side */
    /* 0x198 */ void (*setIdleMotion)(struct BattleModels *task, s32 id, s32 motion);
} BattleModels;

/* The battle menu (WFIGHTMN_start), registered with id 0xC */
typedef struct BattleMenu {
    TASK_HEADER(BattleMenu);
    /* 0x50 */ s32 args[8]; /* the message's arguments */
    /* 0x70 */ s32 unk70;
} BattleMenu;

/* FIGHTSTG's func_800919EC's task (its Unk800911C8), registered with id
   0x12 */
typedef struct Unk800919EC {
    TASK_HEADER(Unk800919EC);
    /* 0x050 */ u8 unk50[0xA8];
    /* 0x0F8 */ void (*unkF8)(struct Unk800919EC *task, void *arg1); /* copies 0x34 bytes from arg1 */
    /* 0x0FC */ void (*unkFC)();
    /* 0x100 */ void *(*unk100)(struct Unk800919EC *task);
} Unk800919EC;

/* The battle menu's children */
typedef struct BattleMenuChildren {
    /* 0x00 */ Task *loader;
    /* 0x04 */ BattleCommands *commands;
    /* 0x08 */ Unk800919EC *unk8;
    /* 0x0C */ Task *lights;
    /* 0x10 */ Task *stage;
    /* 0x14 */ BattleModels *models;
    /* 0x18 */ Task *unk18;
    /* 0x1C */ BattleTask *task; /* what the state waits for, NULL when done */
} BattleMenuChildren;

/* Points to getDigimon, whatever its name says */
extern DigimonData *(*ON_PARTNER_ENTRY_ADDED)(s32 id);





/* FIGHTSTG's func_8008A22C: the fade at the end of a battle */
typedef struct BattleEnd {
    TASK_HEADER(BattleEnd);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 unk58[0xC];
    /* 0x64 */ void (*start)(struct BattleEnd *task, s32 arg1, s32 duration);
} BattleEnd;

BattleEnd *func_8008A22C(void);
void func_8009C0B0(void);

/* How the battle ended: 1 won (mode 0x1400 follows, for the report), 2 requests
   mode 0xE00 and anything else goes back to the field */
extern u8 D_800A30E4;

#endif /* WFIGHTMN_H */
