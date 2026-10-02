#ifndef DW3_MEMCARD_H
#define DW3_MEMCARD_H

/* Memory card saves (memcard.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/* Memory card save header (first 0x80 bytes of a save) */
typedef struct CardClut {
    /* 0x00 */ u8 data[0x20];
} CardClut;

typedef struct CardHeader {
    /* 0x00 */ char magic[2];
    /* 0x02 */ u8 type;
    /* 0x03 */ u8 blocks;
    /* 0x04 */ char title[64];
    /* 0x44 */ u8 reserved[28];
    /* 0x60 */ CardClut clut;
} CardHeader;

/* Same layout as the kernel's struct DIRENTRY */
typedef struct CardDirEntry {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 attr;
    /* 0x18 */ s32 size;
    /* 0x1C */ struct CardDirEntry *next;
    /* 0x20 */ s32 head;
    /* 0x24 */ char system[4];
} CardDirEntry;

/*
 * Memory card access (MEMCARD), one step per call: every operation returns
 * 0 while it runs, 1 when it succeeds and result + 1 when it fails.
 * The save file (4 blocks) holds the header and 1-3 icon frames (128 bytes
 * each), an info section (infoSize) and data sections (dataSize each).
 */
typedef struct MemCard {
    /* 0x00 */ s32 state;
    /* 0x04 */ u8 unk4[8];
    /* 0x0C */ char *fileName;
    /* 0x10 */ CardHeader header;
    /* 0x90 */ s32 cmd;
    /* 0x94 */ u32 result;
    /* 0x98 */ s32 retries;
    /* 0x9C */ s32 maxRetries;
    /* 0xA0 */ s32 restart; /* the command failed and must be reissued */
    /* 0xA4 */ s32 fileCount;
    /* 0xA8 */ CardDirEntry files[15];
    /* 0x300 */ s32 progress;
    /* 0x304 */ s32 offset;
    /* 0x308 */ s32 unk308;
    /* 0x30C */ s32 dataSize;
    /* 0x310 */ s32 infoSize;
    /* 0x314 */ s32 iconCount;
    /* 0x318 */ s32 icons[3];
    /* 0x324 */ s32 unk324;
} MemCard;

s32 memCardCommand(s32 port, s32 op);
s32 checkMemCard(s32 port);
s32 acceptMemCard(s32 port);
s32 syncMemCard(void);

extern MemCard MEMCARD;

#endif /* DW3_MEMCARD_H */
