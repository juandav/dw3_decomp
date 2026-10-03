#ifndef STGMCARD_H
#define STGMCARD_H

/* STGMCARD.PRO: mode 0xC00, the memory card screen. */

#include "game.h"

/* The root task of the overlay (STGMCARD_start) */
typedef struct MemCardScene {
    TASK_HEADER(MemCardScene);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
} MemCardScene;

#endif /* STGMCARD_H */
