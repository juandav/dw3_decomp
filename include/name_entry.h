#ifndef NAME_ENTRY_H
#define NAME_ENTRY_H

/*
 * The on-screen keyboard that the overlays use to type a name (STCRDDEK's
 * deck names, for example). The name is kept as maxLength full-width
 * Shift-JIS characters, padded with spaces.
 */

#include "game.h"

#define SJIS_SPACE 0x4081 /* full-width space, 0x81 0x40 */

typedef struct NameEntry {
    TASK_HEADER(NameEntry);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 imageX; /* where the keyboard's images go in VRAM */
    /* 0x60 */ s32 imageY;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ u8 unk68[0x10];
    /* 0x78 */ u16 text[14];
    /* 0x94 */ s32 maxLength;
    /* 0x98 */ u8 unk98[0x54];
    /* 0xEC */ void (*getText)(struct NameEntry *entry, char *dst);
    /* 0xF0 */ void (*close)(struct NameEntry *entry);
} NameEntry;

#endif /* NAME_ENTRY_H */
