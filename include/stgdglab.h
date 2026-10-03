#ifndef STGDGLAB_H
#define STGDGLAB_H

/* STGDGLAB.PRO: the partners' digivolutions, it seems. Its main menu
   (STGDGLAB_createMenu) opens one of three screens (STGDGLAB_screens): the
   third checks the recipes of STGDGLAB_data (how many of a few ids are
   needed) against the entries a partner has (listPartnerEntries), and the
   second sets a partner's three slots (setPartnerSlots). On the way in it
   packs the party (STGDGLAB_packParty) so that the members come first. Its
   strings are in files 0x3A, 0x4F, 0x48, 0xA3 and 0x9C. */

#include "game.h"

/* The lab's sprite sheet; the next file is its texture archive */
#if VERSION_US
#define FILE_LAB_SPRITES 0x2B6
#elif VERSION_EU
#define FILE_LAB_SPRITES 0x2C5
#endif

/* The lab's main menu (STGDGLAB_createMenu) */
typedef struct LabMenu {
    TASK_HEADER(LabMenu);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 picked;
    /* 0x058 */ s32 layer;
    /* 0x05C */ s32 depth;
    /* 0x060 */ s32 choice; /* into STGDGLAB_screens */
    /* 0x064 */ PanelAnim panels[9];
    /* 0x0F4 */ s32 unkF4;
    /* 0x0F8 */ s32 unkF8;
    /* 0x0FC */ s32 unkFC[5];
    /* 0x110 */ s32 unk110;
    /* 0x114 */ void (*open)(struct LabMenu *menu);
    /* 0x118 */ void (*close)(struct LabMenu *menu);
} LabMenu;

typedef struct LabMenuWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *options[3]; /* the three screens */
    /* 0x10 */ TextWindow *label;
    /* 0x14 */ TextWindow *unk14[5];
    /* 0x28 */ TextWindow *unk28[5];
    /* 0x3C */ TextWindow *unk3C;
    /* 0x40 */ TextWindow *unk40;
    /* 0x44 */ Cursor *cursor;
    /* 0x48 */ struct LabPanel3 *panel;
} LabMenuWindows;

/* A recipe of STGDGLAB_data's tables: how many of the ids are needed, then up
   to five ids (0: none) */
typedef s16 LabRecipe[6];

/* A partner's animation: up to seven sprite ids, -1 ends it */
typedef struct LabAnim {
    s32 frames[7];
} LabAnim;

/* The main menu's first screen (func_8008BB30) */
typedef struct LabScreen1 {
    TASK_HEADER(LabScreen1);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ s32 unk60;
    /* 0x064 */ PanelAnim panels[5];
    /* 0x0B4 */ u8 unkB4[0xC4 - 0xB4];
    /* 0x0C4 */ s32 animTime;
    /* 0x0C8 */ s32 blinkTime;
    /* 0x0CC */ s32 frames[3]; /* the party's animation frames */
    /* 0x0D8 */ s32 frame; /* the picked partner's */
    /* 0x0DC */ s32 clut;
    /* 0x0E0 */ s32 clut2;
    /* 0x0E4 */ s32 partners[8]; /* the unlocked partners outside the party, -1 for none */
    /* 0x104 */ s32 count;
} LabScreen1;

typedef struct LabScreen1Windows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *labels[5];
    /* 0x18 */ TextWindow *values[5];
    /* 0x2C */ TextWindow *name;
    /* 0x30 */ TextWindow *unk30;
    /* 0x34 */ struct LabPanel3 *panel;
} LabScreen1Windows;

/* The main menu's second screen (func_80087FF0) */
typedef struct LabScreen2 {
    TASK_HEADER(LabScreen2);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ PanelAnim panels[6];
    /* 0x0B4 */ s32 layer;
    /* 0x0B8 */ s32 depth;
    /* 0x0BC */ s32 choice;
    /* 0x0C0 */ u8 unkC0[0xC8 - 0xC0];
    /* 0x0C8 */ s32 picked; /* the list's cursor when an entry was picked */
    /* 0x0CC */ s16 slots[3]; /* getPartnerSlots */
    /* 0x0D2 */ s16 entries[45]; /* listPartnerEntries */
    /* 0x12C */ s32 entryCount;
} LabScreen2;

typedef struct LabScreen2Windows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *list[13]; /* two columns: 6, then 7 */
    /* 0x38 */ TextWindow *unk38[3];
    /* 0x44 */ TextWindow *options[2];
    /* 0x4C */ TextWindow *unk4C;
    /* 0x50 */ Cursor *cursor;
    /* 0x54 */ struct LabPanel3 *entryList;
    /* 0x58 */ struct LabPanel1 *entryPanel;
    /* 0x5C */ struct LabPanel2 *skillsPanel;
} LabScreen2Windows;

/* The main menu's third screen (func_80084CF4) */
typedef struct LabScreen3 {
    TASK_HEADER(LabScreen3);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ s16 owned[44];
    /* 0x0B8 */ s32 ownedCount;
    /* 0x0BC */ s32 table; /* into STGDGLAB_data.recipes */
    /* 0x0C0 */ s32 row;
    /* 0x0C4 */ s32 unkC4[2];
    /* 0x0CC */ s32 slots; /* how many of found[row] are in use */
    /* 0x0D0 */ s32 found[4][4][5]; /* the owned ids of each recipe */
    /* 0x210 */ s32 complete[4]; /* 0: a recipe of the row lacks ids */
    /* 0x220 */ s32 foundCount[4];
    /* 0x230 */ PanelAnim panels[5];
    /* 0x280 */ s32 arrowLeft;
    /* 0x284 */ s32 arrowRight;
    /* 0x288 */ s32 time;
    /* 0x28C */ s32 clutRow;
    /* 0x290 */ s32 col;
    /* 0x294 */ s32 slot;
    /* 0x298 */ s32 unk298;
} LabScreen3;

typedef struct LabScreen3Windows {
    /* 0x00 */ TextWindow *title; /* with the partner's name */
    /* 0x04 */ TextWindow *rowNumber;
    /* 0x08 */ TextWindow *rowLabel;
    /* 0x0C */ TextWindow *prev; /* by the arrows */
    /* 0x10 */ TextWindow *next;
    /* 0x14 */ TextWindow *name; /* the picked id's */
    /* 0x18 */ TextWindow *desc;
} LabScreen3Windows;

/* What getPartnerEntry gives */
typedef struct LabPartnerEntry {
    /* 0x00 */ s16 id;
    /* 0x02 */ s8 level;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s32 exp;
    /* 0x08 */ s16 skills[6]; /* the low 13 bits; 0x8000 and 0x4000 are flags */
} LabPartnerEntry;

/* A panel of the second screen (func_800869A4): a partner's entries and
   its three slots */
typedef struct LabPanel1 {
    TASK_HEADER(LabPanel1);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 unk58; /* the partner */
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 col;
    /* 0x64 */ s32 row;
    /* 0x68 */ s32 scroll;
    /* 0x6C */ s32 blinkTime;
    /* 0x70 */ s32 blink;
    /* 0x74 */ s16 slots[3]; /* getPartnerSlots */
    /* 0x7A */ s16 entries[47]; /* listPartnerEntries */
    /* 0xD8 */ s32 entryCount;
    /* 0xDC */ PanelAnim fades[2];
    /* 0xFC */ s32 unkFC;
} LabPanel1;

typedef struct LabPanel1Windows {
    /* 0x00 */ TextWindow *entries[10];
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *unk2C;
    /* 0x30 */ TextWindow *skills[6];
    /* 0x48 */ TextWindow *values[14]; /* the battle stats, the resistances, the level */
    /* 0x80 */ TextWindow *help;
    /* 0x84 */ TextWindow *options[4];
    /* 0x94 */ Cursor *optionCursor;
    /* 0x98 */ Cursor *cursor;
    /* 0x9C */ ScrollBar *scrollBar; /* USA only */
} LabPanel1Windows;

/* A panel of the second screen (func_8008D014) */
typedef struct LabPanel2 {
    TASK_HEADER(LabPanel2);
    /* 0x50 */ PanelAnim fade;
    /* 0x60 */ PanelAnim confirm;
    /* 0x70 */ s32 layer;
    /* 0x74 */ s32 depth;
    /* 0x78 */ s32 member;
    /* 0x7C */ s32 slot;
    /* 0x80 */ s16 slots[4];
    /* 0x88 */ LabPartnerEntry entry; /* skills: flags 0x2000, 0x4000 and 0x8000 */
    /* 0x9C */ s32 learned;
    /* 0xA0 */ s32 choice;
    /* 0xA4 */ s32 cursor;
    /* 0xA8 */ s32 skillCount;
} LabPanel2;

typedef struct LabPanel2Windows {
    /* 0x00 */ TextWindow *unk0;
    /* 0x04 */ TextWindow *unk4;
    /* 0x08 */ TextWindow *unk8;
    /* 0x0C */ TextWindow *left[6];
    /* 0x24 */ TextWindow *right[6];
    /* 0x3C */ TextWindow *unk3C;
    /* 0x40 */ TextWindow *unk40;
    /* 0x44 */ TextWindow *unk44;
    /* 0x48 */ TextWindow *help;
    /* 0x4C */ TextWindow *unk4C;
    /* 0x50 */ TextWindow *unk50;
    /* 0x54 */ Cursor *optionCursor;
    /* 0x58 */ Cursor *cursor;
} LabPanel2Windows;

/* A panel of the main menu (func_8008E320) */
typedef struct LabPanel3 {
    TASK_HEADER(LabPanel3);
    /* 0x050 */ s32 unk50;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 layer;
    /* 0x05C */ s32 depth;
    /* 0x060 */ PanelAnim unk60;
    /* 0x070 */ PanelAnim unk70;
    /* 0x080 */ PanelAnim fade;
    /* 0x090 */ s32 ids[50]; /* the partner's slots, then (unk50) its other entries */
    /* 0x158 */ s32 scroll;
    /* 0x15C */ s32 count;
    /* 0x160 */ s32 cursor;
    /* 0x164 */ s32 blinkTime;
    /* 0x168 */ s32 blink; /* the scroll arrows */
    /* 0x16C */ s32 unk16C;
    /* 0x170 */ void (*close)(struct LabPanel3 *panel);
} LabPanel3;

typedef struct LabPanel3Windows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *options[3];
    /* 0x10 */ TextWindow *unk10;
    /* 0x14 */ TextWindow *unk14;
    /* 0x18 */ TextWindow *skills[6];
    /* 0x30 */ TextWindow *values[14]; /* the battle stats, the resistances, the level */
    /* 0x68 */ Cursor *cursor;
    /* 0x6C */ ScrollBar *scrollBar;
} LabPanel3Windows;

/* The mode's main task (STGDGLAB_createLab) */
typedef struct Lab {
    TASK_HEADER(Lab);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 blinkPos;
    /* 0x58 */ s32 blinkSkip;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 partyCount;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 (*openMenu)(struct Lab *lab);
    /* 0x6C */ s32 (*closeMenu)(struct Lab *lab);
    /* 0x70 */ s32 (*menuOpen)(struct Lab *lab);
    /* 0x74 */ void (*packParty)(struct Lab *lab);
    /* 0x78 */ void (*fadeOut)(struct Lab *lab);
} Lab;

typedef struct LabChildren {
    /* 0x0 */ LabMenu *menu;
    /* 0x4 */ Task *screen;
    /* 0x8 */ ScreenFade *fade;
} LabChildren;

/* Moves a value towards a target in fixed point */
typedef struct LabLerp {
    /* 0x00 */ s32 duration;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 fixed; /* value << 8 */
    /* 0x10 */ s32 target;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 active;
} LabLerp;

/* An entry of D_8008EE4C */
typedef struct LabEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 a;
    /* 0x4 */ s16 b;
} LabEntry;

/* The lab's helpers (STGDGLAB_data.funcs) */
typedef struct LabFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(LabLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(LabLerp *lerp);
    /* 0x18 */ s32 (*getA)(s32 id);
    /* 0x1C */ s32 (*getB)(s32 id);
} LabFuncs;

/* The overlay's tables and helpers */
typedef struct LabData {
    /* 0x00 */ LabAnim *anim; /* D_8008ECE8, by partner */
    /* 0x04 */ s32 *pos; /* D_8008EDC8 */
    /* 0x08 */ LabRecipe *recipes[8]; /* [row * 4 + col] */
    /* 0x28 */ LabFuncs funcs;
} LabData;

/* An entry of the executable's technique table (the one STSTATUS reads) */
typedef struct LabTech {
    /* 0x00 */ u16 mp;
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ u8 icon;
    /* 0x05 */ u8 unk5[0xD];
} LabTech;

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);

extern LabTech D_800427E8[];

extern LabData STGDGLAB_data;

/* The overlay's functions and data, which its five objects share */
Task *func_80084CF4(Lab *lab);
Task *func_80087FF0(Lab *lab);
LabMenu *STGDGLAB_createMenu(Lab *lab);
Task *func_8008BB30(Lab *lab);
ScreenFade *STGDGLAB_createFader(void);
void STGDGLAB_drawFader(ScreenFade *task);
void func_800869FC(LabScreen2 *screen, LabScreen2Windows *windows);
void func_80086F6C(LabScreen2 *screen, LabScreen2Windows *windows);
LabPanel2 *func_8008D014(s32 arg0, s32 arg1);
void func_80087B68(LabScreen2 *screen, void *children);
void func_80088164(LabMenu *menu, LabMenuWindows *windows);
void func_800884A0(LabMenu *menu, LabMenuWindows *windows);
void func_800893FC(LabMenu *menu, void *children);
void func_8008397C(LabScreen3 *screen, LabScreen3Windows *win);
void func_8008568C(LabPanel1 *panel, LabPanel1Windows *windows);
void func_8008B960(LabScreen1 *screen, void *children);
void func_8008A6A4(LabScreen1 *screen, void *children);
void func_8008B0A4(LabScreen1 *screen, LabScreen1Windows *windows);
LabPanel3 *func_8008E320(s32 arg0, s32 arg1, s32 arg2);
void func_8008C234(LabPanel2 *panel, LabPanel2Windows *windows);
void func_8008E134(LabPanel3 *panel, LabPanel3Windows *windows);
void func_8008D06C(LabPanel3 *panel, LabPanel3Windows *windows);
void func_8008D884(LabPanel3 *panel, LabPanel3Windows *windows);
void func_8008DD30(LabPanel3 *panel, LabPanel3Windows *windows);
void func_8008D25C(LabPanel3 *panel, LabPanel3Windows *windows, s32 arg);
void STGDGLAB_openMenu(LabMenu *menu);
void STGDGLAB_closeMenu(LabMenu *menu);
void STGDGLAB_updateMenu(LabMenu *menu, void *children);
void func_8008D80C(LabPanel3 *panel);
void func_80087F48(LabScreen2 *screen, void *children);
s32 func_80082C1C(LabScreen3 *screen, s32 row, u32 col);
ScrollBar *STGDGLAB_createScrollBar(void);
void STGDGLAB_setScrollBarX(ScrollBar *bar, s32 x, s32 width);
void STGDGLAB_setScrollBarRange(ScrollBar *bar, s32 top, s32 bottom);
void STGDGLAB_setScrollBarCount(ScrollBar *bar, s32 pageSize, s32 count);
void STGDGLAB_setScrollBarPos(ScrollBar *bar, s32 pos);
void func_8008E394(Lab *lab, LabChildren *children);
void STGDGLAB_packParty(Lab *lab);
s32 func_8008E704(Lab *lab);
s32 func_8008E760(Lab *lab);
s32 func_8008E7BC(Lab *lab);
void func_8008E7F0(Lab *lab);
Lab *STGDGLAB_createLab(void);
void STGDGLAB_loadFiles(void);
s32 STGDGLAB_filesLoading(void);
void STGDGLAB_startFade(PanelAnim *fade, s32 fadeIn);
s32 STGDGLAB_updateFade(PanelAnim *fade);
void STGDGLAB_startLerp(LabLerp *lerp, s32 from, s32 to, s32 frames);
s32 STGDGLAB_updateLerp(LabLerp *lerp);
s32 func_8008EBFC(s32 id);
s32 func_8008EC48(s32 id);

extern Task *(*STGDGLAB_screens[])(Lab *lab);
extern s32 D_8008EC94[];
extern s32 D_8008ECB4[];
extern s32 D_8008ECC8[];
extern LabEntry D_8008EE4C[];
extern DigimonData *(*ON_PARTNER_ENTRY_ADDED)(s32 id);

#endif /* STGDGLAB_H */
