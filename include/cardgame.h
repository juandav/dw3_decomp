#ifndef CARDGAME_H
#define CARDGAME_H

/* CARDGAME.PRO: the card battle (mode 0x700) */

#include "game.h"

/* Fades the screen to a colour: a POLY_F4 over it, blended (blend is the
   semi-transparency rate) */
typedef struct CardFader {
    TASK_HEADER(CardFader);
    /* 0x50 */ s32 mode; /* 0 idle, 1 fading, 2 done: the task ends */
    /* 0x54 */ s32 time; /* left */
    /* 0x58 */ s32 duration;
    /* 0x5C */ u8 blend;
    /* 0x5D */ u8 killWhenDone;
    /* 0x5E */ u8 target[3];
    /* 0x61 */ u8 from[3];
    /* 0x64 */ u8 color[3];
    /* 0x68 */ void (*setColor)(struct CardFader *fader, u8 r, u8 g, u8 b);
    /* 0x6C */ void (*start)(struct CardFader *fader, u8 r, u8 g, u8 b, s32 frames, s32 killWhenDone);
    /* 0x70 */ s32 (*isDone)(struct CardFader *fader);
    /* 0x74 */ void (*kill)(struct CardFader *fader);
} CardFader;

#endif /* CARDGAME_H */
