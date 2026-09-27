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

/* FIELDSTG functions the stages call */
void *func_80084B80(s32 id); /* creates the task of an event object */

#endif /* STAGE_H */
