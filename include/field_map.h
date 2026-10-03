#ifndef FIELD_MAP_H
#define FIELD_MAP_H

/*
 * FIELDSTG's map and the functions that read it, which the stages call too.
 * The map is a tree of cells: a grid of 128-pixel cells, then levels of 64,
 * 32, 16 and 8 pixels, each cell four of the next level's, then a byte for
 * each pixel of the 8x8 blocks.
 */

#include "common.h"

struct Point; /* fieldstg.h */

typedef struct FieldMap {
    /* 0x00 */ s32 files[8]; /* the file entry of each map, set by setFile */
    /* 0x20 */ s32 width; /* of the grid, in cells */
    /* 0x24 */ s32 height;
    /* 0x28 */ u8 *grid;
    /* 0x2C */ u8 *cells64;
    /* 0x30 */ s16 *cells32;
    /* 0x34 */ s16 *cells16;
    /* 0x38 */ s16 *cells8;
    /* 0x3C */ u8 *pixels;
    /* 0x40 */ void (*setFile)(s32 index, s32 file); /* func_80091B78 */
    /* 0x44 */ s32 (*getCell)(s32 index, struct Point *pos); /* func_80091BC0 */
    /* 0x48 */ void (*unk48)(struct Point *pos, s32 scale, s32 index, struct Point *out);
    /* 0x4C */ void (*unk4C)(s32 arg0, s32 scale, s32 index, struct Point *out);
    /* 0x50 */ void (*unk50)(s32 arg0); /* func_80091B90: sets GAME.unk26D8 if GAME.clearTempFlags */
    /* 0x54 */ void (*unk54)(s32 arg0); /* func_80091BB4: sets GAME.unk26D8 */
    /* 0x58 */ s32 (*unk58)(struct Point *pos); /* func_80091D3C: 0 where a character or an object stands */
} FieldMap;

extern FieldMap D_8009A70C;

#endif
