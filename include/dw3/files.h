#ifndef DW3_FILES_H
#define DW3_FILES_H

/* The disc file table, the CD reader and the file cache (system.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/* The disc's file table (FILE_TABLE): files are numbered, not named */
typedef struct FileTableFuncs {
    /* 0x0 */ void (*exists)();
    /* 0x4 */ s32 (*getSectorCount)(s32 file);
    /* 0x8 */ s32 (*getSector)(s32 file);
    /* 0xC */ void (*getPos)(s32 file, s32 offset, u8 *loc);
} FileTableFuncs;

/* A file in the cache */
typedef struct FileSlot {
    /* 0x0 */ s16 state; /* 0 free, 1 queued, 2 being read, 3 loaded */
    /* 0x2 */ s16 marked;
    /* 0x4 */ s32 file;
    /* 0x8 */ s32 lastUsed; /* GFX time */
    /* 0xC */ void *data;
} FileSlot;

/* Reads whole sectors of a file with CdlReadN, from callbacks */
typedef struct CdReader {
    /* 0x00 */ s32 state; /* 0 idle, 1 seek, 2 set mode, 3 read, 4 done */
    /* 0x04 */ s32 file;
    /* 0x08 */ s32 offset; /* in sectors */
    /* 0x0C */ s32 sectorCount;
    /* 0x10 */ s32 buffer;
    /* 0x14 */ s32 *done; /* set to 1 when the read is complete */
    /* 0x18 */ u8 loc[4];
    /* 0x1C */ s32 sector;
    /* 0x20 */ s32 sectorsLeft;
    /* 0x24 */ s32 dst;
    /* 0x28 */ s32 nextSector;
    /* 0x2C */ s32 (*isBusy)(void);
    /* 0x30 */ void (*read)(s32 file, s32 offset, s32 size, void *buf, s32 *done);
} CdReader;

/*
 * The file cache (FILE_CACHE): up to 64 files loaded in the heap (tag 3),
 * read in the background one at a time and evicted least recently used
 * first when the heap is full. The methods after the slots are also
 * reachable as FILE_CACHE_REQUEST, FILE_CACHE_UPDATE, FILE_CACHE_LOAD[] and
 * FILE_CACHE_GET_ENTRY[].
 */
typedef struct FileCache {
    /* 0x000 */ s32 pending;
    /* 0x004 */ FileSlot slots[64];
    /* 0x404 */ s32 (*isLoading)(s32 file);
    /* 0x408 */ void (*evictOldest)(void);
    /* 0x40C */ void (*request)(s32 file);
    /* 0x410 */ void (*update)(void);
    /* 0x414 */ char *(*load)(s32 file);
    /* 0x418 */ void (*free)(s32 file);
    /* 0x41C */ void (*freeAll)(void);
    /* 0x420 */ void (*freeFrom)(u32 addr);
    /* 0x424 */ s32 (*getEntry)(s32 fileAndIndex);
    /* 0x428 */ u8 *(*getArchiveEntry)(s32 index, s32 archive);
    /* 0x42C */ void (*markCached)(void);
    /* 0x430 */ void (*touchMarked)(void);
} FileCache;

s32 isFileLoading(s32);
FileSlot *findFileSlot(s32 file);
FileSlot *findFreeFileSlot(void);
FileSlot *findOldestFile(void);
void requestFile(s32);
void updateFileCache(void);
s32 *loadFile(u32 id);
void cdSyncCallback();
s32 cdCheckSector(void);
s32 isCdReading(void);
void startCdRead(void);

extern FileTableFuncs FILE_TABLE;
extern void (*FILE_CACHE_REQUEST)(s32 file);
extern CdReader CD_READER;
extern u8 *(*FILE_CACHE_LOAD[])(s32 file);
extern u8 CD_SECTOR_HEADER[];
extern FileSlot FILE_CACHE_SLOTS[64];
extern FileCache FILE_CACHE;
extern s32 FILE_SECTORS[];
extern u16 FILE_SECTOR_COUNTS[];
extern s32 (*FILE_CACHE_GET_ENTRY[])(s32 id);

/*
 * Files the engine loads by number. The European disc numbers its files
 * differently, and has each text file once per language, in a row:
 * TEXT_FILE() gives the copy of the language the player picked (LANGUAGE,
 * set by CNTY_SEL), copy 1 being at the USA version's number.
 */
#if VERSION_US
#define FILE_MENU_SPRITES 0x277 /* the menu graphics, a sprite sheet */
#define FILE_FONT 0x278
#define TEXT_FILE(file) (file)
#elif VERSION_EU
#define FILE_MENU_SPRITES 0x286
#define FILE_FONT 0x287
#define TEXT_FILE(file) (LANGUAGE + (file) - 1)
extern s32 LANGUAGE; /* 2-5 */
#endif

/* The battle menu's files (WFIGHTMN, WFIGHTTS): FILE_BATTLE_IMAGES is an
   archive whose entries go through FILE_CACHE.getEntry, the four after it
   are archives of images for VRAM */
#if VERSION_US
#define FILE_BATTLE_MENU 0x445
#define FILE_BATTLE_IMAGES 0x446
#define FILE_BATTLE_IMAGES_1 0x78F
#define FILE_BATTLE_IMAGES_2 0x79F
#define FILE_BATTLE_IMAGES_3 0x7D2
#define FILE_BATTLE_IMAGES_4 0x7D4
#elif VERSION_EU
#define FILE_BATTLE_MENU 0x455
#define FILE_BATTLE_IMAGES 0x456
#define FILE_BATTLE_IMAGES_1 0x79E
#define FILE_BATTLE_IMAGES_2 0x7AE
#define FILE_BATTLE_IMAGES_3 0x7E1
#define FILE_BATTLE_IMAGES_4 0x7E3
#endif

#endif /* DW3_FILES_H */
