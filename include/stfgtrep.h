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

/* The main task of the screen (STFGTREP_createScreen) */
typedef struct FightReport {
    TASK_HEADER(FightReport);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ u8 unk58[0x48];
} FightReport;

#endif /* STFGTREP_H */
