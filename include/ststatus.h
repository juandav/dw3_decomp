#ifndef STSTATUS_H
#define STSTATUS_H

/* STSTATUS.PRO: the field menu's screens. createFieldMenu (in main) lists
   the options; picking one switches to this mode, which opens the screen of
   FIELD_MENU_CHOICE (STSTATUS_screens) and goes back to the field menu when
   it closes. Its strings are in files 0xB1, 0x6B, 0x64, 0x4F, 0x48, 0xA3 and
   0x9C. */

#include "game.h"

/* The menu's sprite sheet; the next file is its texture archive */
#if VERSION_US
#define FILE_STATUS_SPRITES 0x3F4
#define FILE_STATUS_BG 0x78A /* +2 in the second half of the game */
#elif VERSION_EU
#define FILE_STATUS_SPRITES 0x404
#define FILE_STATUS_BG 0x799
#endif

/* The mode's main task (func_80098DE4) */
typedef struct FieldMenuScreen {
    TASK_HEADER(FieldMenuScreen);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 blinkPos;
    /* 0x58 */ s32 blinkSkip;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 lateGame; /* STSTATUS_area.isLateGame() */
    /* 0x64 */ s32 bgFile;
    /* 0x68 */ s32 bgFile2;
    /* 0x6C */ s32 bgArchive;
    /* 0x70 */ s32 bgArchive1;
    /* 0x74 */ s32 bgArchive2;
} FieldMenuScreen;

typedef struct FieldMenuScreenChildren {
    /* 0x0 */ Task *fieldMenu;
    /* 0x4 */ Task *screen;
} FieldMenuScreenChildren;

/* A screen of the field menu (STSTATUS_screens) */
typedef struct StatusScreen {
    TASK_HEADER(StatusScreen);
    /* 0x50 */ FieldMenuScreen *menu;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
} StatusScreen;

/* The screens with the party's pages (func_800843B4, func_80085B90) */
typedef struct StatusScreen1 {
    TASK_HEADER(StatusScreen1);
    /* 0x50 */ FieldMenuScreen *menu;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 count; /* party members */
    /* 0x60 */ s32 frames[3]; /* of their portraits' animations */
    /* 0x6C */ s32 frameTime;
    /* 0x70 */ s32 choice; /* 0, 1: the options */
    /* 0x74 */ PanelAnim pageFades[3];
    /* 0xA4 */ PanelAnim fades[2];
    /* 0xC4 */ PanelAnim fade;
} StatusScreen1;

/* The field menu's first screen (func_80091318) */
typedef struct StatusScreen0 {
    TASK_HEADER(StatusScreen0);
    /* 0x050 */ FieldMenuScreen *menu;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 count; /* party members */
    /* 0x060 */ u8 unk60[0x70 - 0x60];
    /* 0x070 */ s32 option;
    /* 0x074 */ u8 unk74[4];
    /* 0x078 */ s32 item; /* the chosen one */
    /* 0x07C */ s32 unk7C;
    /* 0x080 */ s32 itemShown;
    /* 0x084 */ u8 unk84[0x3B0 - 0x84];
    /* 0x3B0 */ s32 member; /* the one an item is used on */
    /* 0x3B4 */ u8 unk3B4[0x3CC - 0x3B4];
    /* 0x3CC */ PanelAnim pageFades[3];
    /* 0x3FC */ PanelAnim fades[2];
    /* 0x41C */ PanelAnim fades2[2];
    /* 0x43C */ PanelAnim fade;
    /* 0x44C */ u8 unk44C[0x45C - 0x44C];
} StatusScreen0;

typedef struct StatusScreen0Windows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ PartnerPage pages[3];
    /* 0x88 */ TextWindow *help;
    /* 0x8C */ TextWindow *kind;
    /* 0x90 */ TextWindow *answers[2];
    /* 0x98 */ Cursor *answerCursor;
    /* 0x9C */ TextWindow *money;
    /* 0xA0 */ TextWindow *moneyLabel;
    /* 0xA4 */ TextWindow *options[5];
    /* 0xB8 */ Cursor *optionCursor;
    /* 0xBC */ TextWindow *itemName;
    /* 0xC0 */ TextWindow *equippedLabel;
    /* 0xC4 */ TextWindow *equipped; /* how many of the item are equipped */
    /* 0xC8 */ TextWindow *ownedLabel;
    /* 0xCC */ TextWindow *owned;
    /* 0xD0 */ u8 unkD0[0xD4 - 0xD0];
} StatusScreen0Windows;

/* The field menu's fifth screen (func_8008DEA4) */
typedef struct StatusScreen4 {
    TASK_HEADER(StatusScreen4);
    /* 0x050 */ FieldMenuScreen *menu;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 count; /* party members */
    /* 0x060 */ u8 unk60[0x70 - 0x60];
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 option; /* the options' cursor */
    /* 0x078 */ u8 unk78[0x7C - 0x78];
    /* 0x07C */ s32 member; /* in the party */
    /* 0x080 */ u8 unk80[0x88 - 0x80];
    /* 0x088 */ PanelAnim pageFades[3];
    /* 0x0B8 */ PanelAnim fades[2];
    /* 0x0D8 */ PanelAnim panelFades[6];
    /* 0x138 */ PanelAnim fade;
    /* 0x148 */ void (*func_8008BA38)(struct StatusScreen4 *screen, s32 slot, s32 item);
} StatusScreen4;

typedef struct StatusScreen4Windows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ PartnerPage pages[3];
    /* 0x88 */ TextWindow *help;
    /* 0x8C */ TextWindow *help2;
    /* 0x90 */ TextWindow *options[2];
    /* 0x98 */ Cursor *cursor;
    /* 0x9C */ TextWindow *unk9C;
    /* 0xA0 */ TextWindow *unkA0;
    /* 0xA4 */ TextWindow *slotTitle;
    /* 0xA8 */ TextWindow *slots[3]; /* the partner's getPartnerSlots entries */
    /* 0xB4 */ TextWindow *equipTitle;
    /* 0xB8 */ TextWindow *equip[6];
    /* 0xD0 */ TextWindow *values[13]; /* the stats of D_80099B58 */
    /* 0x104 */ TextWindow *unk104;
    /* 0x108 */ TextWindow *unk108;
    /* 0x10C */ TextWindow *unk10C;
} StatusScreen4Windows;

/* A panel of the fifth screen (func_8008AB04) */
typedef struct StatusPanel4A {
    TASK_HEADER(StatusPanel4A);
    /* 0x50 */ StatusScreen4 *screen;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 slot; /* the cursors' rows */
    /* 0x60 */ s32 option;
    /* 0x64 */ s32 tech; /* the list's row */
    /* 0x68 */ u8 unk68[4];
    /* 0x6C */ s32 fromEntry; /* the list shows the slot's techniques, not the partner's */
    /* 0x70 */ s32 member;
    /* 0x74 */ s16 slots[4]; /* getPartnerSlots */
    /* 0x7C */ s32 slotCount; /* the slots holding an entry (4 on) */
    /* 0x80 */ s32 listShown;
    /* 0x84 */ u8 unk84[0x8C - 0x84];
    /* 0x8C */ s32 scroll; /* added to the list's y */
    /* 0x90 */ u8 unk90[0xA0 - 0x90];
    /* 0xA0 */ s32 blink; /* the help arrow */
    /* 0xA4 */ s32 blinkFrame;
    /* 0xA8 */ s32 time;
    /* 0xAC */ PanelAnim fades[5];
} StatusPanel4A;

typedef struct StatusPanel4AWindows {
    /* 0x00 */ TextWindow *slots[3];
    /* 0x0C */ Cursor *slotCursor;
    /* 0x10 */ TextWindow *unk10;
    /* 0x14 */ TextWindow *unk14;
    /* 0x18 */ TextWindow *options[2];
    /* 0x20 */ Cursor *optionCursor;
    /* 0x24 */ Cursor *listCursor;
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *unk2C;
    /* 0x30 */ TextWindow *unk30;
    /* 0x34 */ TextWindow *list[13]; /* two columns: 6 and 7 */
    /* 0x68 */ TextWindow *values[6];
    /* 0x80 */ TextWindow *title;
    /* 0x84 */ TextWindow *help;
    /* 0x88 */ TextWindow *unk88;
    /* 0x8C */ TextWindow *unk8C;
} StatusPanel4AWindows;

/* A list of the fifth screen (func_800879C8) */
typedef struct StatusPanel4B {
    TASK_HEADER(StatusPanel4B);
    /* 0x050 */ StatusScreen4 *screen;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 partner;
    /* 0x060 */ s32 slot; /* the equipment slot being changed */
    /* 0x064 */ s32 cursor; /* the list's row */
    /* 0x068 */ s32 count; /* items */
    /* 0x06C */ s32 scroll; /* the first one shown */
    /* 0x070 */ u8 unk70[8];
    /* 0x078 */ s16 items[0x194]; /* those that fit the slot, -1: remove */
    /* 0x3A0 */ u8 unk3A0[0x6CC - 0x3A0];
    /* 0x6CC */ PanelAnim panels[4];
} StatusPanel4B;

typedef struct StatusPanel4BWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *slots[6]; /* the equipment */
    /* 0x1C */ Cursor *cursor;
    /* 0x20 */ TextWindow *listTitle;
    /* 0x24 */ Cursor *listCursor;
    /* 0x28 */ struct {
        TextWindow *name;
        TextWindow *times; /* the "x" before count */
        TextWindow *count; /* how many are owned */
    } rows[8];
    /* 0x88 */ TextWindow *help;
    /* 0x8C */ TextWindow *kind;
    /* 0x90 */ TextWindow *slotTitle;
    /* 0x94 */ TextWindow *slotItem;
    /* 0x98 */ u8 unk98[0xA4 - 0x98];
} StatusPanel4BWindows;

/* A list of the first screen (func_80092B0C) */
typedef struct StatusPanel0 {
    TASK_HEADER(StatusPanel0);
    /* 0x050 */ StatusScreen0 *screen;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 list; /* into D_80099BA4 */
    /* 0x060 */ s32 unk60; /* an item to put the cursor on */
    /* 0x064 */ s32 active; /* the player can move the cursor */
    /* 0x068 */ s32 count;
    /* 0x06C */ s16 items[0x194];
    /* 0x394 */ s16 bag[0x194];
    /* 0x6BC */ s32 cursor;
    /* 0x6C0 */ s32 arrowFrame; /* the page arrows' palette */
    /* 0x6C4 */ s32 time;
    /* 0x6C8 */ s32 page; /* of 16 items */
    /* 0x6CC */ s32 pageCount;
    /* 0x6D0 */ s32 hasPrev; /* pages before and after this one */
    /* 0x6D4 */ s32 hasNext;
    /* 0x6D8 */ u8 unk6D8[4];
    /* 0x6DC */ PanelAnim fades[3];
} StatusPanel0;

typedef struct StatusPanel0Windows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *items[8][2];
    /* 0x44 */ TextWindow *page;
    /* 0x48 */ TextWindow *unk48;
    /* 0x4C */ TextWindow *pageCount;
    /* 0x50 */ TextWindow *prev; /* arrows */
    /* 0x54 */ TextWindow *next;
    /* 0x58 */ Cursor *cursor;
    /* 0x5C */ u8 unk5C[0x6C - 0x5C];
} StatusPanel0Windows;

/* Moves a value towards a target in fixed point */
typedef struct StatusLerp {
    /* 0x00 */ s32 duration;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 fixed; /* value << 8 */
    /* 0x10 */ s32 target;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 active;
} StatusLerp;

/* The screens' helpers (STSTATUS_data.funcs) */
typedef struct StatusFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(StatusLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(StatusLerp *lerp);
    /* 0x18 */ s32 *(*getList)(s32 list, s32 index);
    /* 0x1C */ void (*listItems)(s32 list, u16 *out); /* 6, 7: special lists */
    /* 0x20 */ s32 (*canEquip)(s32 partner, s32 slot, s32 item);
    /* 0x24 */ void (*equip)(s32 partner, s32 slot, s32 item);
} StatusFuncs;

/* Where the game is (D_8009AA00) */
typedef struct StatusAreaFuncs {
    /* 0x0 */ s32 (*isLateGame)(void); /* -1 outside of the field */
    /* 0x4 */ s32 (*getArea)(void);
    /* 0x8 */ void (*func_800999CC)(s32 *out);
} StatusAreaFuncs;

/* The windows of a screen with the party's pages after a window */
typedef struct StatusPagesB {
    /* 0x00 */ TextWindow *unk0;
    /* 0x04 */ PartnerPage pages[3];
} StatusPagesB;

/* The windows of the screens func_80084204 and func_800859E0 */
typedef struct StatusWindows1 {
    /* 0x00 */ PartnerPage pages[3];
    /* 0x84 */ TextWindow *help; /* two lines */
    /* 0x88 */ TextWindow *unk88;
    /* 0x8C */ TextWindow *unk8C;
    /* 0x90 */ TextWindow *options[2];
    /* 0x98 */ Cursor *cursor;
    /* 0x9C */ ScreenFade *fader;
} StatusWindows1;

/* The map screen (func_8009868C); the offsets are the European version's,
   the USA version's are 4 more from 0x64 to 0x188 */
typedef struct StatusMapScreen {
    TASK_HEADER(StatusMapScreen);
    /* 0x050 */ FieldMenuScreen *menu;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 height;
    /* 0x060 */ s32 top; /* where the map starts */
#if VERSION_US
    /* 0x064 */ s32 hoverY;
#endif
    /* 0x064 */ u8 unk64[4];
    /* 0x068 */ s32 file; /* FILE_STATUS_BG or the next one but one */
    /* 0x06C */ u8 unk6C[0x78 - 0x6C];
    /* 0x078 */ s32 lateGame;
    /* 0x07C */ s32 progress; /* which towns are drawn */
    /* 0x080 */ s32 archive; /* entries of file: the map */
    /* 0x084 */ s32 archive1; /* the towns */
    /* 0x088 */ s32 archive2; /* the marks */
    /* 0x08C */ s32 textFile;
    /* 0x090 */ s32 scrollX;
    /* 0x094 */ s32 scrollY;
    /* 0x098 */ s32 homeX; /* the current area's mark */
    /* 0x09C */ s32 homeY;
    /* 0x0A0 */ s32 homeFrame;
    /* 0x0A4 */ u8 unkA4[4];
    /* 0x0A8 */ s32 visited[47]; /* the areas, spot i at i - 1 */
    /* 0x164 */ s32 cursorX;
    /* 0x168 */ s32 cursorY;
    /* 0x16C */ s32 ready;
    /* 0x170 */ s32 cursorFrame;
    /* 0x174 */ s32 time;
    /* 0x178 */ s32 speedX;
    /* 0x17C */ s32 speedY;
    /* 0x180 */ s32 hovering;
    /* 0x184 */ s32 spot; /* the area under the cursor */
#if VERSION_EU
    /* 0x188 */ s32 hoverX; /* where the cursor was when it got there */
    /* 0x18C */ s32 hoverY;
#endif
    /* 0x190 */ PanelAnim fade;
} StatusMapScreen;

/* The screen of func_800975FC */
typedef struct StatusScreen9 {
    TASK_HEADER(StatusScreen9);
    /* 0x50 */ FieldMenuScreen *menu;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 count; /* party members */
    /* 0x60 */ u8 unk60[0x94 - 0x60];
    /* 0x94 */ PanelAnim pageFades[3];
    /* 0xC4 */ PanelAnim fades[2];
    /* 0xE4 */ PanelAnim fade;
} StatusScreen9;

typedef struct StatusWindows9 {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ PartnerPage pages[3];
    /* 0x88 */ TextWindow *help;
} StatusWindows9;

/* The executable's table of techniques (0x12 bytes each), from 1 */
typedef struct StatusTech {
    /* 0x00 */ u16 mp; /* its cost */
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ u8 icon;
    /* 0x05 */ u8 kind; /* 3: heals the target */
    /* 0x06 */ u8 unk6[6];
    /* 0x0C */ u8 power;
    /* 0x0D */ u8 unkD[5];
} StatusTech;
extern StatusTech D_800427E8[];

/* What getPartnerEntry gives */
typedef struct StatusPartnerEntry {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ s16 techs[6]; /* the low 13 bits */
} StatusPartnerEntry;

/* A party member's techniques on the tech screen */
typedef struct StatusTechRow {
    /* 0x00 */ s16 slots[4]; /* getPartnerSlots */
    /* 0x08 */ StatusPartnerEntry entries[3];
    /* 0x44 */ s16 techs[5]; /* the ones it can use here */
    /* 0x4E */ u8 unk4E[2];
    /* 0x50 */ s32 techCount;
} StatusTechRow;

/* The tech screen's windows */
typedef struct StatusTechWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ PartnerPage pages[3];
    /* 0x88 */ TextWindow *help;
    /* 0x8C */ TextWindow *help2;
    /* 0x90 */ TextWindow *mpLabel;
    /* 0x94 */ TextWindow *mp; /* the technique's cost */
    /* 0x98 */ TextWindow *listTitle;
    /* 0x9C */ TextWindow *techs[5];
    /* 0xB0 */ Cursor *cursor;
} StatusTechWindows;

/* The tech screen (func_80095934) */
typedef struct StatusScreen8 {
    TASK_HEADER(StatusScreen8);
    /* 0x050 */ FieldMenuScreen *menu;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 count; /* party members */
    /* 0x060 */ u8 unk60[0x7C - 0x60];
    /* 0x07C */ s32 member; /* who uses the technique */
    /* 0x080 */ s32 unk80;
    /* 0x084 */ s32 target;
    /* 0x088 */ s32 cursor;
    /* 0x08C */ StatusTechRow rows[3];
    /* 0x188 */ u8 unk188[0x194 - 0x188];
    /* 0x194 */ PanelAnim pageFades[3];
    /* 0x1C4 */ PanelAnim fades[2];
    /* 0x1E4 */ PanelAnim fade;
} StatusScreen8;

/* A partner's portrait animation: sprites, -1 ends it */
typedef struct StatusAnim {
    s32 frames[7];
} StatusAnim;

/* An area on the map screen */
typedef struct StatusMapSpot {
    /* 0x0 */ s32 sprite;
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
} StatusMapSpot;

typedef struct StatusMapPoint {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} StatusMapPoint;

/* The screens' tables, item lists and helpers, in one object: the functions
   that use two of them keep its address in a register */
typedef struct StatusData {
    /* 0x000 */ StatusAnim *partnerAnims; /* the partners' portraits */
    /* 0x004 */ WindowPos *layout; /* where the windows go, and their strings */
    /* 0x008 */ StatusMapSpot *spots; /* the map's areas, from 1 */
    /* 0x00C */ StatusMapPoint *towns; /* from 1 */
    /* 0x010 */ s16 items[404]; /* ITEM_FUNCS->list(2) */
    /* 0x338 */ s32 itemCount;
    /* 0x33C */ s16 items2[404]; /* ITEM_FUNCS->list(3) */
    /* 0x664 */ s32 item2Count;
    /* 0x668 */ StatusFuncs funcs;
} StatusData;

extern StatusData STSTATUS_data;
extern s32 D_80099B58[]; /* the stats screen 4 shows */
extern s32 D_80099C8C[]; /* the map cursor's frames */

/* The functions and data the overlay's objects share */
Task *createFieldMenu(s32 layerId, s32 cursor);
Task *func_80091318(FieldMenuScreen *menu, s32 extra);
FieldMenuScreen *func_80098DE4(void);
void func_80098BF8(FieldMenuScreen *menu, FieldMenuScreenChildren *children);
void STSTATUS_loadFiles(void);
s32 STSTATUS_filesLoading(void);
void STSTATUS_startFade(PanelAnim *fade, s32 fadeIn);
s32 STSTATUS_updateFade(PanelAnim *fade);
void STSTATUS_startLerp(StatusLerp *lerp, s32 from, s32 to, s32 frames);
s32 STSTATUS_updateLerp(StatusLerp *lerp);
s32 *func_80099270(s32 list, s32 index);
void STSTATUS_listItems(s32 list, u16 *out);
s32 STSTATUS_canEquip(s32 partner, s32 slot, s32 item);
void STSTATUS_equip(s32 partner, s32 slot, s32 item);
s32 STSTATUS_isLateGame(void);
s32 STSTATUS_getArea(void);
void func_800999CC(s32 *out);

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
void func_80084204(StatusScreen1 *screen, StatusWindows1 *windows);
void func_800859E0(StatusScreen1 *screen, StatusWindows1 *windows);
void func_800911E4(StatusScreen0 *screen, StatusScreen0Windows *windows);
void func_8009576C(StatusScreen8 *screen, StatusTechWindows *windows);
void func_80097460(StatusScreen9 *screen, StatusWindows9 *windows);
void func_8008DCF0(StatusScreen4 *screen, StatusScreen4Windows *windows);
void func_8008AA00(StatusPanel4A *panel, StatusPanel4AWindows *windows);
void func_80087914(StatusPanel4B *panel, void *children);
void func_80092974(StatusPanel0 *panel, StatusPanel0Windows *windows);
void STSTATUS_startFader(ScreenFade *task, s32 fadeIn, s32 duration);
void STSTATUS_updateFader(ScreenFade *task);
void func_8008BA38(StatusScreen4 *screen, s32 slot, s32 item);
void func_8008E668(StatusScreen0 *screen, s32 arg);
void func_8008E828(StatusScreen0 *screen, s32 mode);
void func_8008EA38(StatusScreen0 *screen, s32 show);
s32 func_8008EAAC(StatusScreen0 *screen);
ScreenFade *STSTATUS_createFader(void);
StatusPanel4B *func_800879C8(StatusScreen4 *screen);
StatusPanel4A *func_8008AB04(StatusScreen4 *screen);
StatusPanel0 *func_80092B0C(StatusScreen0 *screen, s32 list, s32 arg2);
void STSTATUS_drawFader(ScreenFade *task);
void func_80085BD8(StatusPanel4B *panel, StatusPanel4BWindows *windows);
void func_80086B28(StatusPanel4B *panel, void *children);
void func_800864B0(StatusPanel4B *panel);
s32 func_8009930C(u16 *out);
void func_8008340C(StatusScreen1 *screen);
void func_80084D14(StatusScreen1 *screen);
s32 func_800994D0(s32 list, u16 *out);
extern s32 FIELD_MENU_CHOICE[2];
extern s32 D_80099BA4[];
extern Task *(*STSTATUS_screens[2][7])(FieldMenuScreen *menu, s32 extra);
extern s32 *D_8009A254[][5];
extern u8 D_8009A90C[];
extern u8 D_8009A910[];
extern StatusAreaFuncs D_8009AA00;
extern s32 D_80099A98[];
extern s32 D_80099C78[];
extern s32 D_80099C50[];
extern s32 D_80099BB8[];

/* A partner's equipment, copied as a whole */
typedef struct StatusEquip {
    s16 items[6];
} StatusEquip;

/* What an item does (its ItemInfo.data) */
typedef struct StatusItemEffect {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 kind; /* 1: heals, 17: raises stats[1], others: D_80099BF0 */
    /* 0x2 */ u16 amount;
} StatusItemEffect;

/* What the items that raise a stat raise (D_80099BF0), up to a kind of -1 */
typedef struct StatusStatItem {
    /* 0x0 */ s16 kind; /* the item's second byte */
    /* 0x2 */ s16 stat; /* in PartnerStats.stats */
    /* 0x4 */ s16 max;
} StatusStatItem;
extern StatusStatItem D_80099BF0[];
extern s32 D_80099B44[];
extern s32 D_80099AAC[];
extern s32 D_80099AC0[];
extern s32 D_80099AD8[];
extern s32 D_80099B8C[];
extern s32 D_80099BCC[];
extern DigimonData *(*ON_PARTNER_ENTRY_ADDED)(s32 id);

#endif /* STSTATUS_H */
