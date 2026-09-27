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
    /* 0x00 */ TaskHeader header;
    /* 0x50 */ void *owner;
} StageTask;

#endif /* STAGE_H */
