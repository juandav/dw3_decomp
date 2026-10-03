#ifndef NAME_ENTRY_H
#define NAME_ENTRY_H

/*
 * The on-screen keyboard that the overlays use to type a name (STCRDDEK's
 * deck names, for example). The name is kept as maxLength full-width
 * Shift-JIS characters, padded with spaces.
 */

#include "game.h"

#define SJIS_SPACE 0x4081 /* full-width space, 0x81 0x40 */

/* A linear tween of a scale, 0 to 0x1000 */
typedef struct NameTween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s32 step;
    /* 0x8 */ s32 value;
    /* 0xC */ s32 active;
} NameTween;

/*
 * The Japanese keyboard (three pages) is for language 0 of the European
 * version; the USA version only has the one page.
 */
#if VERSION_US
#define NAME_ENTRY_JAPANESE 0
#elif VERSION_EU
#define NAME_ENTRY_JAPANESE (LANGUAGE == 0)
#endif

/* A sprite of the keyboard drawn per language, one after the other (USA: the first) */
#if VERSION_US
#define NAME_ENTRY_TEXT_SPRITE(sprite) ((sprite) + 1)
#elif VERSION_EU
#define NAME_ENTRY_TEXT_SPRITE(sprite) (LANGUAGE + (sprite))
#endif

/* A key of the keyboard bigger than one cell: its sprite and where it goes */
typedef struct BigKey {
    /* 0x0 */ s32 sprite;
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
} BigKey;

/* A keyboard cell: 1 starts a key, 0 is empty and negative cells belong to a wide key */
typedef struct NameKey {
    /* 0x0 */ s8 kind;
    /* 0x1 */ u8 code;
} NameKey;

/* A page of the keyboard: 7 rows of 15 cells */
typedef struct KeyPage {
    /* 0x0 */ NameKey cells[7][15];
} KeyPage;

/* The texts of a keyboard page's three tabs */
typedef struct KeyTabs {
    /* 0x0 */ s32 texts[3];
} KeyTabs;

/* The character pages of the keyboard (as STDGNAME's and STPLNMET's) */
typedef struct NameKeyboard {
    /* 0x0 */ s32 pageCount;
    /* 0x4 */ KeyTabs *tabTexts; /* one per page */
    /* 0x8 */ KeyPage *pages;
} NameKeyboard;

typedef struct NameEntryWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *name;
    /* 0x08 */ TextWindow *tabs[3];
    /* 0x14 */ TextWindow *unk14[3];
    /* 0x20 */ TextWindow *unk20;
    /* 0x24 */ TextWindow *unk24;
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *unk2C;
    /* 0x30 */ TextWindow *unk30;
} NameEntryWindows;

/* STDGNAME's NameTask without its unused 0x98 */
typedef struct NameEntry {
    TASK_HEADER(NameEntry);
    /* 0x50 */ s32 mode;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 imageX; /* where the keyboard's images go in VRAM */
    /* 0x60 */ s32 imageY;
    /* 0x64 */ s32 partner; /* -1: none */
    /* 0x68 */ s32 partnerFrame;
    /* 0x6C */ s32 partnerTime;
    /* 0x70 */ s32 clutRow;
    /* 0x74 */ s32 clutTime;
    /* 0x78 */ u16 text[12];
    /* 0x90 */ s32 cursor;
    /* 0x94 */ s32 maxLength;
    /* 0x98 */ s32 column;
    /* 0x9C */ s32 row;
    /* 0xA0 */ s32 keyFrame;
    /* 0xA4 */ s32 keyTime;
    /* 0xA8 */ s32 active;
    /* 0xAC */ s32 page;
    /* 0xB0 */ s32 arrowFrame;
    /* 0xB4 */ s32 arrowTime;
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ NameTween unkBC;
    /* 0xCC */ NameTween unkCC;
    /* 0xDC */ NameTween unkDC;
    /* 0xEC */ void (*getText)(struct NameEntry *entry, char *dst);
    /* 0xF0 */ void (*close)(struct NameEntry *entry);
} NameEntry;

#endif /* NAME_ENTRY_H */
