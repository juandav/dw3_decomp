#ifndef STFGTREP_H
#define STFGTREP_H

/* STFGTREP.PRO: mode 0x1400, the report after a battle. WFIGHTMN requests
   it when a battle ends; it goes through the party (getPartyMember) and
   shows the partners that went up a level, with their name and new level,
   from text file 0x56. */

#include "game.h"

/* The sprite archive the overlay loads */
#if VERSION_US
#define FILE_FGTREP_SPRITES 0x791
#elif VERSION_EU
#define FILE_FGTREP_SPRITES 0x7A0
#endif

/* What a battle gives (STFGTREP_rewards) */
typedef struct BattleReward {
    /* 0x0 */ s32 digimonExp; /* shared by the Digimon used */
    /* 0x4 */ s32 exp; /* shared by the partners who fought */
    /* 0x8 */ s32 money;
} BattleReward;

/* A Digimon a partner can learn, once the conditions are met */
typedef struct Evolution {
    /* 0x0 */ s32 digimon; /* DIGIMON_DATA index + 1 */
    /* 0x4 */ struct {
        s16 digimon; /* 0 for none */
        s16 level;
    } needs[2];
    /* 0xC */ s16 stat; /* 1-6 battle stats, 7 level, 8-14 resistances */
    /* 0xE */ s16 value; /* the least the stat must be */
} Evolution;

/* A Digimon entry of a partner as the report reads it (PartnerEntry) */
typedef struct ReportEntry {
    /* 0x00 */ s16 id;
    /* 0x02 */ s8 level;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s32 exp;
    /* 0x08 */ s16 skills[6]; /* 0x2000: known, 0x8000: the last one */
} ReportEntry;

/* A partner as the report raises it (getPartnerStats) */
typedef struct ReportPartnerStats {
    /* 0x000 */ char name[0x18];
    /* 0x018 */ s32 exp;
    /* 0x01C */ s16 stats[19]; /* PartnerStats' order: 0 level, 3 max HP... */
    /* 0x042 */ u8 unk42[0xE];
    /* 0x050 */ ReportEntry entries[44];
    /* 0x3C0 */ s16 equip[6]; /* [4] and [5] are the accessories */
} ReportPartnerStats;

struct FightReport;

/* A blinking image of a partner's panel */
typedef struct ReportBlink {
    /* 0x0 */ s32 on;
    /* 0x4 */ s32 frame;
    /* 0x8 */ s32 time;
} ReportBlink;

/* The panel of a partner of the party (STFGTREP_createPartner) */
typedef struct ReportPartner {
    TASK_HEADER(ReportPartner);
    /* 0x050 */ struct FightReport *report;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 index; /* in the party */
    /* 0x060 */ s32 exp; /* what the partner gets */
    /* 0x064 */ s32 boosted; /* the exp accessory was applied */
    /* 0x068 */ s32 selected;
    /* 0x06C */ s32 frame; /* of the partner's animation */
    /* 0x070 */ s32 frameTime;
    /* 0x074 */ s16 slots[3];
    /* 0x07A */ s16 entries[44]; /* listPartnerEntries */
    /* 0x0D2 */ s16 unkD2;
    /* 0x0D4 */ ReportEntry entry;
    /* 0x0E8 */ s32 slot; /* whose Digimon gets its exp, -1 for none */
    /* 0x0EC */ s32 unkEC;
    /* 0x0F0 */ ReportBlink levelBlink;
    /* 0x0FC */ struct {
        s32 unk0;
        ReportBlink blink;
    } slotBlinks[3];
    /* 0x12C */ s32 learned;
    /* 0x130 */ s32 sound;
    /* 0x134 */ s16 voice; /* -1 for none */
    /* 0x138 */ s32 shownExp;
    /* 0x13C */ s32 targetExp;
    /* 0x140 */ s32 rollTime;
    /* 0x144 */ s32 unk144;
    /* 0x148 */ PanelAnim fade;
    /* 0x158 */ s32 cursorFrame;
    /* 0x15C */ s32 cursorTime;
    /* 0x160 */ void (*show)(struct ReportPartner *partner);
    /* 0x164 */ void (*hide)(struct ReportPartner *partner);
    /* 0x168 */ void (*raise)(struct ReportPartner *partner);
    /* 0x16C */ s32 (*boostExp)(struct ReportPartner *partner);
    /* 0x170 */ void (*select)(struct ReportPartner *partner);
} ReportPartner;

/* The children of a partner's panel */
typedef struct ReportPartnerWindows {
    /* 0x00 */ TextWindow *name;
    /* 0x04 */ TextWindow *level;
    /* 0x08 */ TextWindow *levelLabel;
    /* 0x0C */ TextWindow *exp;
    /* 0x10 */ TextWindow *expLabel;
    /* 0x14 */ struct {
        TextWindow *name;
        TextWindow *level;
    } slots[3];
    /* 0x2C */ TextWindow *message;
} ReportPartnerWindows;

/* The main task of the screen (STFGTREP_createScreen) */
typedef struct FightReport {
    TASK_HEADER(FightReport);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 bgScroll;
    /* 0x5C */ s32 bgSkip; /* the background moves every other frame */
    /* 0x60 */ s32 count; /* partners in the party */
    /* 0x64 */ s32 exp[3]; /* what each one gets */
    /* 0x70 */ s32 used; /* Digimon used in the battle */
    /* 0x74 */ s32 arrowOn; /* the message waits for a button */
    /* 0x78 */ s32 arrowTime;
    /* 0x7C */ s32 arrowFrame;
    /* 0x80 */ PanelAnim header;
    /* 0x90 */ PanelAnim footer;
} FightReport;

/* The children of the main task */
typedef struct FightReportChildren {
    /* 0x00 */ TextWindow *exp;
    /* 0x04 */ TextWindow *expLabel;
    /* 0x08 */ TextWindow *message;
    /* 0x0C */ ReportPartner *partners[3];
    /* 0x18 */ ScreenFade *fade;
} FightReportChildren;

/* The overlay's helpers (STFGTREP_funcs) */
typedef struct FightReportFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(MenuLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(MenuLerp *lerp);
    /* 0x18 */ s32 (*addExp)(s32 partner, s32 exp);
    /* 0x1C */ s32 (*learnDigimon)(s32 partner);
    /* 0x20 */ s32 (*addDigimonExp)(s32 partner, s32 id, s32 exp);
    /* 0x24 */ s32 (*addSkill)(s32 partner, s32 id);
    /* 0x28 */ s32 (*learnSkill)(s32 partner, s32 id);
    /* 0x2C */ s32 (*getDigimonExp)(s32 partner, s32 id, s32 exp, s32 used);
} FightReportFuncs;

/* Points to getDigimon, whatever its name says */
extern DigimonData *(*ON_PARTNER_ENTRY_ADDED)(s32 id);

/* What a level adds to the exp the next one needs, by tier */
extern s32 STFGTREP_levelExp[4];
/* What is taken from the HP and MP growth, by tier, and added at random */
extern s32 STFGTREP_vitalCuts[4];
extern s32 STFGTREP_vitalRandom[9];
/* A battle stat's gain by tier, from its growth plus 0-4 at random */
extern s32 STFGTREP_statGains[6][9];
/* A resistance's gain, from its growth plus 0-3 at random */
extern s32 STFGTREP_resistGains[8];

extern BattleReward STFGTREP_rewards[];
extern FightReportFuncs STFGTREP_funcs;

#endif /* STFGTREP_H */
