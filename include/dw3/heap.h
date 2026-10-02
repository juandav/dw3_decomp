#ifndef DW3_HEAP_H
#define DW3_HEAP_H

/* The heap (game3_2.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/*
 * The heap: a doubly linked list of blocks from HEAP_START to 0x801FF000.
 * Every block has a tag: 0 free, 1 the end marker, 2 the current mode's
 * allocations (freed by main whenever the mode task ends), 3 the file cache,
 * 4 a locked block (lockMem).
 */
typedef struct Heap {
    /* 0x00 */ s32 size;
    /* 0x04 */ struct MemBlock *first;
    /* 0x08 */ struct MemBlock *end;
    /* 0x0C */ void (*init)();
    /* 0x10 */ void (*free)(void *ptr);
    /* 0x14 */ void (*freeByTag)();
    /* 0x18 */ void *(*alloc)(s32 size, s32 tag);
    /* 0x1C */ void *(*allocHigh)(s32 size, s32 tag); /* from the end of the heap */
    /* 0x20 */ void *(*allocZeroed)(s32 size, s32 tag);
    /* 0x24 */ void (*zero)(void *ptr, s32 size);
    /* 0x28 */ void (*fill)(void *ptr, s32 value, s32 size);
    /* 0x2C */ void (*lock)();
    /* 0x30 */ void (*unk30)();
} Heap;

/* Header of a heap block; the data follows it */
typedef struct MemBlock {
    /* 0x0 */ struct MemBlock *prev;
    /* 0x4 */ struct MemBlock *next;
    /* 0x8 */ s32 tag;
} MemBlock;

void zeroMem(void *dst, s32 size);
void *allocMem();
void *tryAllocMem(u32 size, s32 tag);
void *tryAllocMemHigh(u32 size, s32 tag);

extern Heap HEAP;
extern MemBlock *HEAP_START;

#endif /* DW3_HEAP_H */
