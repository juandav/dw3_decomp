#ifndef STAGE_H
#define STAGE_H

/*
 * The stage overlays (AAA/PRO/WSTAG###.PRO), loaded at 0x800A4CA4 on top of
 * FIELDSTG. Each stage is its own small program; many share the same
 * functions, built from the same source.
 */

#include "game.h"

/* The task a stage starts (see its start function) */
typedef struct StageTask {
    TASK_HEADER(StageTask);
    /* 0x50 */ void *owner;
} StageTask;

/* A frame of an animation script; a script ends with id 0xFF */
typedef struct AnimFrame {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 duration;
} AnimFrame;

/* Where an animation script is */
typedef struct Anim {
    /* 0x0 */ s16 index;
    /* 0x2 */ s16 timer;
} Anim;

/* An animation after one or two other words */
typedef struct Anim4 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Anim anim;
} Anim4;

typedef struct Anim8 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ Anim anim;
} Anim8;

/* What a stage tells FIELDSTG about itself (filled by its setup function) */
typedef struct StageInfo {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8; /* a file id */
    /* 0x0C */ s32 unkC; /* the next file id << 16 */
    /* 0x10 */ void *unk10;
    /* 0x14 */ void *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C; /* a file id */
    /* 0x20 */ void *unk20;
    /* 0x24 */ void *events;
    /* 0x28 */ void *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ void *unk4C;
} StageInfo;

/*
 * Compiles to nothing, but its loop notes stop GCC 2.8's scheduler from moving
 * code across it. The setup functions have one after their first six fields:
 * probably a debug print, compiled out as do { } while (0) in the release.
 */
#define DEBUG_LOG() \
    do {            \
    } while (0)

/* FIELDSTG functions the stages call through a table */
typedef struct FieldFuncs {
    /* 0x00 */ void (*unk0[16])();
    /* 0x40 */ void (*unk40)(s32 arg0, s32 id);
    /* 0x44 */ void (*unk44[3])();
    /* 0x50 */ void (*unk50)(s32 arg0);
} FieldFuncs;

extern StageInfo D_800990B4;
extern FieldFuncs D_8009A70C;

/* FIELDSTG functions the stages call */
void *func_80084B80(s32 id); /* creates the task of an event object */

#endif /* STAGE_H */
