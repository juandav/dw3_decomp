#ifndef SHOCKTST_H
#define SHOCKTST_H

/* SHOCKTST.PRO: the debug vibration test. It loads the vibration patterns
   from the PC (DLSKDATA.TXT), writes them back as DLSKDATA.BIN, and lets the
   patterns be edited and played on the controller's two motors. */

#include "game.h"

/* DLSKDATA.BIN: a header, then the offsets are from its start */
typedef struct ShockFile {
    /* 0x0 */ s32 count;       /* number of patterns */
    /* 0x4 */ s32 typesOffset; /* s32 per pattern */
    /* 0x8 */ s32 timesOffset; /* u8 per motor and pattern */
    /* 0xC */ s32 powersOffset; /* u8 per motor and pattern */
} ShockFile;

/* The patterns loader: the scene's first task */
typedef struct ShockLoader {
    TASK_HEADER(ShockLoader);
    /* 0x50 */ ShockFile *file; /* DLSKDATA.BIN being built */
    /* 0x54 */ u8 *text;        /* DLSKDATA.TXT */
    /* 0x58 */ s32 unk58;
} ShockLoader;

typedef struct ShockLoaderWindows {
    /* 0x0 */ TextWindow *title;
    /* 0x4 */ TextWindow *help[2];
    /* 0xC */ struct ShockTest *test;
} ShockLoaderWindows;

/* One step of a motor's pattern */
typedef struct ShockStep {
    /* 0x0 */ u8 time;  /* frames */
    /* 0x1 */ u8 power; /* the small motor is only on (1) or off (0) */
} ShockStep;

/* The pattern editor */
typedef struct ShockTest {
    TASK_HEADER(ShockTest);
    /* 0x50 */ u8 *unk50;
    /* 0x54 */ s32 windowId;
    /* 0x58 */ s32 column; /* the motor */
    /* 0x5C */ s32 row;    /* pattern, time, power, play */
    /* 0x60 */ s32 playing; /* the pattern being played by "play all" */
    /* 0x64 */ s32 timers[2];
    /* 0x6C */ s32 motors[2]; /* 0: start, 1: vibrating, -1: done */
    /* 0x74 */ s32 pattern;
    /* 0x78 */ s32 count;
    /* 0x7C */ ShockStep *steps[2];
    /* 0x84 */ s32 unk84;
} ShockTest;

/* The editor's text windows */
typedef struct ShockTestWindows {
    /* 0x00 */ TextWindow *pattern;
    /* 0x04 */ TextWindow *unk4;
    /* 0x08 */ TextWindow *motors[2];
    /* 0x10 */ TextWindow *times[2];
    /* 0x18 */ TextWindow *powers[2];
    /* 0x20 */ TextWindow *play;
} ShockTestWindows;

/* One row of the editor's menu */
typedef struct ShockTestRow {
    /* 0x0 */ s32 enabled[2]; /* per column */
    /* 0x8 */ s32 highlight[4]; /* per column: selected, then being edited */
} ShockTestRow;

#endif /* SHOCKTST_H */
