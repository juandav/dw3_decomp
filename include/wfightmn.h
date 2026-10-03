#ifndef WFIGHTMN_H
#define WFIGHTMN_H

/* WFIGHTMN.PRO: the battle's sub-overlay. FIGHTSTG loads it (file 0x1FA)
   at STAGE_VRAM for a normal battle, and WFIGHTTS in its place for the
   battle test. */

#include "game.h"

/* The item a partner can equip that makes FIGHTSTG's func_8009B7A4 act on
   it at the start of the battle */
#define WFIGHTMN_ITEM 0x140

/* A fighter in the battle (Battle.units): partner HP and MP are copied back
   to the party when it ends */
typedef struct BattleUnit {
    /* 0x00 */ s16 id; /* the Digimon (DIGIMON_DATA) */
    /* 0x02 */ s16 prevId; /* its id before unk1A changed it */
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 maxHp;
    /* 0x08 */ s16 hp;
    /* 0x0A */ s16 maxMp;
    /* 0x0C */ s16 mp;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10[4];
    /* 0x18 */ s16 unk18; /* an enemy's item */
    /* 0x1A */ u8 unk1A; /* id is a temporary Digimon */
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 unk1D[3];
} BattleUnit;

/* FIGHTSTG's battle state (D_800A31E8); WFIGHTMN_start clears it from unk8 */
typedef struct Battle {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 current[2]; /* each side's fighter in units */
    /* 0x10 */ BattleUnit units[2][3]; /* the partners, then the enemies */
    /* 0xD0 */ s16 unkD0;
    /* 0xD2 */ s16 unkD2;
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ s16 unkD6;
    /* 0xD8 */ s16 unkD8;
    /* 0xDA */ s8 unkDA;
    /* 0xDB */ u8 unkDB;
} Battle;

/* An entry of FIGHTSTG's D_800A25F0 */
typedef struct BattleAction {
    /* 0x00 */ s16 kind; /* 0 for a free entry */
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 actor; /* side << 4 */
    /* 0x08 */ s32 unit;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10[0xC];
} BattleAction;

/* What D_800A25F0.add takes */
typedef struct BattleRequest {
    /* 0x00 */ s32 kind;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x10];
} BattleRequest;

/* FIGHTSTG's D_800A25F0 */
typedef struct BattleActions {
    /* 0x000 */ BattleAction entries[100];
    /* 0xAF0 */ u8 unkAF0;
    /* 0xAF1 */ s8 current; /* the entry being carried out */
    /* 0xAF2 */ u8 unkAF2[0xA];
    /* 0xAFC */ void (*add)(BattleRequest *request);
    /* 0xB00 */ s32 (*unkB00)();
    /* 0xB04 */ s32 (*findKind)(s32 kind);
    /* 0xB08 */ void (*unkB08)();
    /* 0xB0C */ s32 (*find)(s32 kind, s32 actor, s32 unit); /* -1 for none */
    /* 0xB10 */ void (*unkB10)();
    /* 0xB14 */ s32 (*unkB14)(s32 actor, s32 arg1);
} BattleActions;

/* What the battle menu's states start and wait for (BattleMenuChildren.task):
   FIGHTSTG's message window (func_80099400), effects and the like */
typedef struct BattleTask {
    TASK_HEADER(BattleTask);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
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
    /* 0x194 */ void (*face)(struct BattleModels *task, s32 id, s32 side);
    /* 0x198 */ void (*setIdleMotion)(struct BattleModels *task, s32 id, s32 motion);
} BattleModels;

/* The battle menu (WFIGHTMN_start), registered with id 0xC */
typedef struct BattleMenu {
    TASK_HEADER(BattleMenu);
    /* 0x50 */ s32 args[8]; /* the message's arguments */
    /* 0x70 */ s32 unk70;
} BattleMenu;

/* The battle menu's children */
typedef struct BattleMenuChildren {
    /* 0x00 */ Task *loader;
    /* 0x04 */ BattleCommands *commands;
    /* 0x08 */ void *unk8;
    /* 0x0C */ Task *lights;
    /* 0x10 */ Task *stage;
    /* 0x14 */ BattleModels *models;
    /* 0x18 */ Task *unk18;
    /* 0x1C */ BattleTask *task; /* what the state waits for, NULL when done */
} BattleMenuChildren;

/* Points to getDigimon, whatever its name says */
extern DigimonData *(*ON_PARTNER_ENTRY_ADDED)(s32 id);

/* FIGHTSTG's D_800A3308: its battle functions from 0x80, the ones WFIGHTMN
   calls */
typedef struct BattleFuncs {
    /* 0x00 */ u8 unk0[0x8C];
    /* 0x8C */ s32 (*getDamage)(s32 *actor); /* of the action actor is in */
    /* 0x90 */ s32 (*unk90[2])();
    /* 0x98 */ s32 (*getHeal)(u8 actor, s32 unit, s32 arg2);
    /* 0x9C */ s32 (*unk9C[13])();
#if VERSION_EU
    /* 0xD0 */ s32 (*unkEU)();
#endif
    /* the European version's offsets are 4 more from here */
    /* 0xD0 */ s32 (*unkD0[3])();
    /* 0xDC */ s32 (*unkDC)(s32 arg0);
    /* 0xE0 */ s32 (*unkE0)();
    /* 0xE4 */ s32 (*unkE4)(s32 damage);
    /* 0xE8 */ s32 (*unkE8)();
} BattleFuncs;

extern Battle D_800A31E8;
extern BattleFuncs D_800A3308;
extern BattleActions D_800A25F0;

#endif /* WFIGHTMN_H */
