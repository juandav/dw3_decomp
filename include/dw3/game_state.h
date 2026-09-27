#ifndef DW3_GAME_STATE_H
#define DW3_GAME_STATE_H

/* The game state: modes, party, items, cards, flags (game3.c, game3_2.c, system.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

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
    /* 0x3C */ void (*getPartnerSlots)();
    /* 0x40 */ void (*setPartnerSlots)();
    /* 0x44 */ void (*listPartnerEntries)();
    /* 0x48 */ void (*addPartnerEntry)();
    /* 0x4C */ void (*getPartnerEntry)();
    /* 0x50 */ void (*setPartnerEntry)();
    /* 0x54 */ struct PartnerVitals *(*getPartnerStats)(s32 partner);
    /* 0x58 */ void (*resetPlayTime)();
    /* 0x5C */ void (*updatePlayTime)();
} GameFuncs;

/* Digimon definition (DIGIMON_DATA, 52 of them; the first 8 are the partners) */
typedef struct DigimonData {
    /* 0x00 */ u16 id;
    /* 0x02 */ u16 battleStats[6];
    /* 0x0E */ u16 resistances[7];
    /* 0x1C */ u8 unk1C[0x23];
    /* 0x3F */ u8 hp;
    /* 0x40 */ u8 mp;
    /* 0x41 */ u8 unk41[0x14];
    /* 0x55 */ u8 nameId; /* string in file 0x4F */
    /* 0x56 */ u8 unk56[2];
} DigimonData;

/* An item (ITEM_DATA, GET_ITEM) */
typedef struct ItemInfo {
    /* 0x0 */ u8 *data;
    /* 0x4 */ u8 unk4[4];
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
    /* 0x16 */ u16 cards[40];
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
    /* 0x008 */ u8 unk8[4];
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
    /* 0x000 */ char name[0x1C];
    /* 0x01C */ s16 stats[19];
    /* 0x042 */ u8 unk42[0xE];
    /* 0x050 */ PartnerEntry entries[44];
    /* 0x3C0 */ s16 equip[6];
    /* 0x3CC */ u8 unk3CC[0x10];
} PartnerStats;

typedef struct Unk80042728 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x4C];
    /* 0x58 */ s16 unk58[8];
} Unk80042728;

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
    /* 0x0038 */ u8 unk38[0xC];
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
    /* 0x2644 */ u8 flags[0x78]; /* FLAGS_02... */
    /* 0x26BC */ s32 mode;
    /* 0x26C0 */ s32 nextMode;
    /* 0x26C4 */ s32 prevMode;
    /* 0x26C8 */ s32 modeArg;
    /* 0x26CC */ s8 unk26CC;
    /* 0x26CD */ s8 unk26CD;
    /* 0x26CE */ s8 unk26CE;
    /* 0x26CF */ s8 unk26CF;
    /* 0x26D0 */ s32 clearTempFlags;
    /* 0x26D4 */ s32 unk26D4;
    /* 0x26D8 */ s32 unk26D8;
    /* 0x26DC */ u8 unk26DC[0x14];
    /* 0x26F0 */ GameFuncs funcs; /* GAME_FUNCS */
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
extern ItemInfo ITEM_DATA[];
extern struct ItemInfo *(*GET_ITEM)(s32 item);
extern u8 ITEM_TYPE_CATEGORIES[];
extern s32 MONEY_REQUIRED[];
extern u8 SPECIAL_CONDITIONS[];
extern u8 FLAGS_40[];
/* The event flag groups in GAME.flags: bitsets packed one after the other, so
   most start at an odd byte; they are offsets into FLAGS_02 */
extern u8 FLAGS_02[];
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
extern s32 MONEY_GAINS[];
extern s32 MONEY_LOSSES[];
extern u8 FLAGS_00[];
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
