#ifndef SOUNDTST_H
#define SOUNDTST_H

/* SOUNDTST.PRO: the debug sound test */

#include "game.h"

/* One line of a list: its name and what it plays (a sound bank for the
   bank list, a packed sound id for a bank's sound list); id 0 ends a list. */
typedef struct SoundTestEntry {
    /* 0x0 */ char *name;
    /* 0x4 */ s32 id;
} SoundTestEntry;

/* The text windows the sound test owns (its task items) */
typedef struct SoundTestWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *header;
    /* 0x08 */ TextWindow *cursor;
    /* 0x0C */ TextWindow *lines[8];
} SoundTestWindows;

typedef struct SoundTest {
    TASK_HEADER(SoundTest);
    /* 0x50 */ s32 bankCursor;
    /* 0x54 */ s32 bankTop;
    /* 0x58 */ s32 bankCount;
    /* 0x5C */ s32 bank;
    /* 0x60 */ s32 soundCursor;
    /* 0x64 */ s32 soundTop;
    /* 0x68 */ s32 soundCount;
    /* 0x6C */ s32 playing;
    /* 0x70 */ s32 voice;
} SoundTest;

#endif /* SOUNDTST_H */
