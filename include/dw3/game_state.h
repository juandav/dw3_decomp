#ifndef DW3_GAME_STATE_H
#define DW3_GAME_STATE_H

/* The game state: modes, party, items, cards, flags (game3.c, game3_2.c, system.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

struct PartnerTotals;

/* The game state's methods (GAME.funcs, also GAME_FUNCS) */
typedef struct GameFuncs {
    /* 0x00 */ void (*newGame)();
    /* 0x04 */ void (*commitMode)();
    /* 0x08 */ s32 (*getMode)(void);
    /* 0x0C */ s32 (*getModeArg)();
    /* 0x10 */ void (*requestMode)(s32 mode, s32 arg);
    /* 0x14 */ s32 (*isModeChangePending)();
    /* 0x18 */ s32 (*getPrevMode)();
    /* 0x1C */ s32 (*getPartyMember)(s32 index);
    /* 0x20 */ void (*setParty)();
    /* 0x24 */ void (*addCards)(s32 card, s32 count);
    /* 0x28 */ void (*giveStarterDeck)(void);
    /* 0x2C */ s32 (*getPartyPartner)();
    /* 0x30 */ void (*setStat)();
    /* 0x34 */ void (*addStat)();
    /* 0x38 */ void (*computeStats)(s32 partner, struct PartnerTotals *out);
    /* 0x3C */ s32 (*getPartnerSlots)(); /* (partner, s16 *out): the count */
    /* 0x40 */ void (*setPartnerSlots)();
    /* 0x44 */ s32 (*listPartnerEntries)(); /* (partner, s16 *out): the count */
    /* 0x48 */ void (*addPartnerEntry)();
    /* 0x4C */ s32 (*getPartnerEntry)(); /* -1 if it hasn't the Digimon */
    /* 0x50 */ void (*setPartnerEntry)();
    /* 0x54 */ struct PartnerVitals *(*getPartnerStats)(s32 partner);
    /* 0x58 */ void (*resetPlayTime)();
    /* 0x5C */ void (*updatePlayTime)();
} GameFuncs;

/*
 * FLAGS_00, the first flag bitset, followed by the event functions: FIELDSTG
 * and the stages call them through here (+0xC applies an action, +0x10 checks
 * a condition).
 */
typedef struct GameFlags {
    /* 0x00 */ u8 bits[4];
    /* 0x04 */ s32 pendingFlag10; /* PENDING_FLAG_10 */
    /* 0x08 */ s32 (*checkConditions)(u16 *list);
    /* 0x0C */ void (*applyAction)(s32 code, s32 value);
    /* 0x10 */ s32 (*checkCondition)(u16 code, u16 value);
    /* 0x14 */ void (*applyActions)(u16 *list);
    /* 0x18 */ void (*updateModeFlags)(void);
} GameFlags;

/* Digimon definition (DIGIMON_DATA, 52 of them; the first 8 are the partners) */
typedef struct DigimonData {
    /* 0x00 */ u16 id;
    /* 0x02 */ u16 battleStats[6];
    /* 0x0E */ u16 resistances[7];
    /* 0x1C */ u16 skills[7]; /* [1]-[6] are learnt at skillLevels */
    /* 0x2A */ u8 unk2A[7];
    /* 0x31 */ u8 skillLevels[6];
    /* 0x37 */ u8 knownLevels[5]; /* the levels that mark an entry's skills[0]-[4] known */
    /* 0x3C */ u8 expLevel; /* the level after which its exp grows faster */
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 expRate; /* a partner's exp per level, in tenths */
    /* 0x3F */ u8 hp;
    /* 0x40 */ u8 mp;
    /* 0x41 */ u8 hpGrowth; /* what a partner's max HP grows by a level */
    /* 0x42 */ u8 mpGrowth;
    /* 0x43 */ u8 statGrowth[6]; /* columns of the growth tables */
    /* 0x49 */ u8 resistGrowth[7]; /* 1-5: how fast the gyms raise them */
    /* 0x50 */ u8 unk50[5];
    /* 0x55 */ u8 nameId; /* string in file 0x4F */
    /* 0x56 */ u8 unk56[2];
} DigimonData;

/* An item (ITEM_DATA, GET_ITEM) */
typedef struct ItemInfo {
    /* 0x0 */ u8 *data;
    /* 0x4 */ u16 price;
    /* 0x6 */ u16 sellPrice; /* 0: cannot be sold */
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 type; /* 2-14 weapons, 15-20 armour, 21-24 accessories */
    /* 0xA */ u8 unkA[2];
} ItemInfo;

typedef struct PartnerEntry {
    /* 0x00 */ s16 id; /* 0-2 unused */
    /* 0x02 */ u8 isNew;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s32 unk4[4];
} PartnerEntry;

/* A card deck */
typedef struct Deck {
    /* 0x00 */ char name[0x16];
    /* 0x16 */ s16 cards[40];
} Deck;

/*
 * One of the eight partner Digimon. Stats (computeStats and setStat order):
 * 0 level, 1 ?, 2 HP, 3 max HP, 4 MP, 5 max MP, 6-11 battle stats (6 is
 * raised by weapons, 7 by armour), 12-18 seven resistances; the totals add
 * 19-21, which are subtracted from 6, 7 and 10.
 */
typedef struct Partner {
    /* 0x000 */ u8 unk0[4];
    /* 0x004 */ s32 unlocked; /* partner id + 3, 0 while locked */
    /* 0x008 */ s32 unk8; /* an entry id, compared with the slots': the Digimon the battle starts it as, 0 for its own */
    /* 0x00C */ char name[0x1C];
    /* 0x028 */ s16 level;
    /* 0x02A */ s16 unk2A;
    /* 0x02C */ s16 hp;
    /* 0x02E */ s16 maxHp;
    /* 0x030 */ s16 mp;
    /* 0x032 */ s16 maxMp;
    /* 0x034 */ u16 battleStats[6];
    /* 0x040 */ u16 resistances[7];
    /* 0x04E */ u8 status[6];
    /* 0x054 */ s16 slots[4]; /* three entries picked from entries[] */
    /* 0x05C */ PartnerEntry entries[44];
    /* 0x3CC */ u8 unk3CC[0x10];
} Partner;

/* A Partner seen from its name (PARTNER_STATS = &GAME.partners[0].name) */
typedef struct PartnerStats {
    /* 0x000 */ char name[0x18];
    /* 0x018 */ s32 unk18; /* shown by the fifth status screen */
    /* 0x01C */ s16 stats[19];
    /* 0x042 */ u8 unk42[0xE];
    /* 0x050 */ PartnerEntry entries[44];
    /* 0x3C0 */ s16 equip[6];
    /* 0x3CC */ u8 unk3CC[0x10];
} PartnerStats;

/* An enemy of a battle (FIELDSTG's encounter table points to these) */
typedef struct BattleEnemy {
    /* 0x0 */ s32 fighter; /* 0 for none */
    /* 0x4 */ s16 level;
    /* 0x6 */ s16 hp;
    /* 0x8 */ s16 mp;
    /* 0xA */ s16 unkA;
} BattleEnemy;

typedef struct Unk80042728 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC; /* the battle's fight stage */
    /* 0x10 */ s32 unk10; /* the battle (BattleResult.battle) */
    /* 0x14 */ s32 unk14; /* the battle's music */
    /* 0x18 */ BattleEnemy enemies[3];
    /* 0x3C */ u8 unk3C; /* a chance that WFIGHTMN scales by level */
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 unk3E[12]; /* FIGHTSTG's func_800A0400 gives 0 for side 0 when [5] is set */
    /* 0x4C */ s32 unk4C; /* 1: the battle always gives unk50 */
    /* 0x50 */ s32 unk50;
    /* 0x54 */ void (*clearUnk58)(void);
    /* 0x58 */ s16 unk58[8];
} Unk80042728;

/* What the battle left for the report (D_80042790, cleared by WFIGHTMN) */
typedef struct BattleResult {
    /* 0x00 */ s16 battle; /* row of STFGTREP_rewards */
    /* 0x02 */ s16 item; /* the item won, 0 for none */
    /* 0x04 */ s16 member; /* the party member whose accessory adds money */
    /* 0x06 */ struct {
        u8 fought;
        u8 used[3]; /* the Digimon of each slot was used */
    } partners[3];
} BattleResult;

/* computeStats' result: the stats with the equipment added */
typedef struct PartnerTotals {
    /* 0x00 */ s16 stats[24];
} PartnerTotals;

/* PartnerStats as the inn and the menus declare it (HP and MP unsigned) */
typedef struct PartnerVitals {
    /* 0x00 */ char name[0x1C];
    /* 0x1C */ s16 level;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ u16 hp;
    /* 0x22 */ u16 maxHp;
    /* 0x24 */ u16 mp;
    /* 0x26 */ u16 maxMp;
    /* 0x28 */ u8 unk28[0xA];
    /* 0x32 */ s16 unk32;
    /* 0x34 */ u8 unk34[0xE];
    /* 0x42 */ s16 status[3];
} PartnerVitals;

/*
 * The game state (GAME): the first 0x26BC bytes are what newGame clears (the
 * save data), then the current game mode and the methods.
 * Game modes: mode >> 8 selects the overlay (MODE_OVERLAY_FILES); a mode
 * change is requested with requestMode and applied by commitMode when main
 * recreates the mode task.
 */
typedef struct GameState {
    /* 0x0000 */ u8 unk0[4];
    /* 0x0004 */ s8 unk4;
    /* 0x0005 */ u8 unk5[7];
    /* 0x000C */ s32 unkC;
    /* 0x0010 */ u8 unk10[0x18];
    /* 0x0028 */ s32 stageSelectTop; /* the debug stage select's first line */
    /* 0x002C */ s32 stageSelectCursor;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 fieldMode; /* where the menu returns to */
    /* 0x0038 */ Vec2 fieldPos; /* the player's, there */
    /* 0x0040 */ s32 fieldDir;
    /* 0x0044 */ u16 unk44;
    /* 0x0046 */ u16 unk46;
    /* 0x0048 */ s32 playFrames; /* 8.8, counted by the vsync callback */
    /* 0x004C */ s16 playHours;
    /* 0x004E */ s16 playMinutes;
    /* 0x0050 */ s16 playSeconds;
    /* 0x0052 */ s16 playTimeMaxed;
    /* 0x0054 */ char name[0x18]; /* PLAYER_NAME */
    /* 0x006C */ s32 money;
    /* 0x0070 */ s32 party[3]; /* partner indices */
    /* 0x007C */ s8 items[0x193]; /* counts, up to 99 */
    /* 0x020F */ s8 equippedItems[0x193];
    /* 0x03A2 */ s8 cards[0x13D]; /* counts, up to 9 */
    /* 0x04DF */ u8 cardsSeen[0x149];
    /* 0x0628 */ Deck decks[3];
    /* 0x075A */ u8 unk75A[2];
    /* 0x075C */ Partner partners[8];
    /* 0x263C */ s32 progress; /* GAME_PROGRESS */
    /* 0x2640 */ s32 partySet; /* PARTY_SET */
#if VERSION_US
    /* 0x2644 */ u8 flags[0x78]; /* FLAGS_02... */
    /* 0x26BC */ s32 mode;
    /* 0x26C0 */ s32 nextMode;
    /* 0x26C4 */ s32 prevMode;
    /* 0x26C8 */ s32 modeArg;
    /* 0x26CC */ u8 countdown[4]; /* three digits of seconds, then frames */
    /* 0x26D0 */ s32 clearTempFlags;
    /* 0x26D4 */ s32 unk26D4;
    /* 0x26D8 */ s32 unk26D8;
    /* 0x26DC */ s32 unk26DC;
    /* 0x26E0 */ s32 unk26E0;
    /* 0x26E4 */ s32 unk26E4;
    /* 0x26E8 */ s32 unk26E8;
    /* 0x26EC */ s32 unk26EC;
    /* 0x26F0 */ GameFuncs funcs; /* GAME_FUNCS */
#elif VERSION_EU
    /* 0x2644 */ u8 flags[0x80]; /* FLAGS_02... */
    /* 0x26C4 */ s32 mode;
    /* 0x26C8 */ s32 nextMode;
    /* 0x26CC */ s32 prevMode;
    /* 0x26D0 */ s32 modeArg;
    /* 0x26D4 */ u8 countdown[4];
    /* 0x26D8 */ s32 clearTempFlags;
    /* 0x26DC */ s32 unk26D4;
    /* 0x26E0 */ s32 unk26D8;
    /* 0x26E4 */ s32 unk26DC;
    /* 0x26E8 */ s32 unk26E0;
    /* 0x26EC */ s32 unk26E4;
    /* 0x26F0 */ s32 unk26E8;
    /* 0x26F4 */ s32 unk26EC;
    /* 0x26F8 */ s32 unk26F8;
    /* 0x26FC */ GameFuncs funcs; /* GAME_FUNCS */
#endif
} GameState;

s32 unequipItem(s32 slot, s32 item);
s32 checkPartner(u32 op, s32 arg);
s32 findDigimon(s32 id);
ItemInfo *getItem(s32 id);
void initNewGameData(void);
void addCards(s32 item, s32 count);
s32 findPartnerEntry(s32 slot, s32 id);
void applyAction(s32 code, s32 value);
s32 checkCondition(u16, u16);
s32 testBit(u8 *bits, s32 index, s32 set);

extern DigimonData DIGIMON_DATA[];
extern GameFuncs GAME_FUNCS;
extern Unk80042728 D_80042728;
extern BattleResult D_80042790;
extern ItemInfo ITEM_DATA[];
extern struct ItemInfo *(*GET_ITEM[])(s32 item);
/* GET_ITEM's entries, each with its own type */
typedef struct ItemFuncs {
    /* 0x0 */ struct ItemInfo *(*get)(s32 item); /* getItem */
    /* 0x4 */ s32 (*getCategory)(s32 item); /* getItemCategory (u8, but the menus read an int) */
    /* 0x8 */ s32 (*isKind)(s32 item, s32 kind); /* ItemInfo.unk8 == kind */
    /* 0xC */ s32 (*list)(s32 type, u16 *out); /* listItems */
} ItemFuncs;
#define ITEM_FUNCS ((ItemFuncs *)GET_ITEM)
extern u8 ITEM_TYPE_CATEGORIES[];
extern s32 MONEY_REQUIRED[];
extern u8 SPECIAL_CONDITIONS[];
/* The event flag groups in GAME.flags: bitsets packed one after the other, so
   most start at an odd byte; they are offsets into FLAGS_02 */
extern u8 FLAGS_02[];
#if VERSION_US
#define FLAGS_04 (FLAGS_02 + 0xD)
#define FLAGS_06 (FLAGS_02 + 0xF)
#define FLAGS_08 (FLAGS_02 + 0x10)
#define FLAGS_0A (FLAGS_02 + 0x11)
#define FLAGS_0C (FLAGS_02 + 0x13)
#define FLAGS_0E (FLAGS_02 + 0x1B)
#define FLAGS_10 (FLAGS_02 + 0x27)
#define FLAGS_18 (FLAGS_02 + 0x29)
#define FLAGS_1A (FLAGS_02 + 0x2A)
#define FLAGS_1C (FLAGS_02 + 0x33)
#define FLAGS_20 (FLAGS_02 + 0x3E)
extern u8 FLAGS_40[]; /* right after FLAGS_02's 0x5C bytes */
#elif VERSION_EU
#define FLAGS_04 (FLAGS_02 + 0x12)
#define FLAGS_06 (FLAGS_02 + 0x14)
#define FLAGS_08 (FLAGS_02 + 0x15)
#define FLAGS_0A (FLAGS_02 + 0x16)
#define FLAGS_0C (FLAGS_02 + 0x1A)
#define FLAGS_0E (FLAGS_02 + 0x22)
#define FLAGS_10 (FLAGS_02 + 0x2E)
#define FLAGS_18 (FLAGS_02 + 0x32)
#define FLAGS_1A (FLAGS_02 + 0x34)
#define FLAGS_1C (FLAGS_02 + 0x3D)
#define FLAGS_20 (FLAGS_02 + 0x48)
#define FLAGS_40 (FLAGS_02 + 0x66)
#endif
extern s32 MONEY_GAINS[];
extern s32 MONEY_LOSSES[];
extern GameFlags FLAGS_00;
extern s32 PENDING_FLAG_10;
extern s32 GAME_CLEAR_TEMP_FLAGS;
extern s32 STARTER_DECK[40];
extern u8 STARTER_PARTIES[][3];
extern s32 PARTY_SET;
extern u8 PROGRESS_RANGES[][2];
extern s32 GAME_PROGRESS;
extern PartnerStats PARTNER_STATS[];
extern GameState GAME;
extern u8 PLAYER_NAME[];
extern s32 GAME_MODE;
extern s32 GAME_NEXT_MODE;
extern s32 GAME_PREV_MODE;
extern s32 GAME_MODE_ARG;

#endif /* DW3_GAME_STATE_H */
