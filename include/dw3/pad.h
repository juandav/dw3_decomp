#ifndef DW3_PAD_H
#define DW3_PAD_H

/* Controllers and random numbers (pad.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/* Random numbers from a table of 4096 (RANDOM_TABLE) */
typedef struct Random {
    /* 0x0 */ s32 index; /* the entry returned last */
    /* 0x4 */ void (*seed)(s32 seed);
    /* 0x8 */ s32 (*next)(void); /* 0-0xFFFF */
} Random;

/*
 * Logical buttons: bits of PadSlot.held/pressed/repeated, which readPadButtons
 * builds from the raw pad data (circle, cross and triangle are rotated, and
 * the left analog stick also sets the d-pad bits). A button map
 * (getButtonBit) translates them again; by default it is the identity.
 * The menus confirm with PAD_CROSS and cancel with PAD_TRIANGLE.
 */
#define PAD_SELECT 0
#define PAD_L3 1
#define PAD_R3 2
#define PAD_START 3
#define PAD_UP 4
#define PAD_RIGHT 5
#define PAD_DOWN 6
#define PAD_LEFT 7
#define PAD_L2 8
#define PAD_R2 9
#define PAD_L1 10
#define PAD_R1 11
#define PAD_CIRCLE 12
#define PAD_CROSS 13
#define PAD_TRIANGLE 14
#define PAD_SQUARE 15

/* One controller: a port, or one of the four multitap slots behind it */
typedef struct PadSlot {
    /* 0x00 */ u16 pressed; /* this frame */
    /* 0x02 */ u16 repeated; /* pressed, or held long enough to repeat */
    /* 0x04 */ u16 prevHeld;
    /* 0x06 */ u16 held;
    /* 0x08 */ u8 analog[4];
    /* 0x0C */ s32 repeatTime[16];
    /* 0x4C */ u8 repeatCount[16];
    /* 0x5C */ u8 buttonMap[16];
    /* 0x6C */ s16 vibrationTimers[2];
} PadSlot;

/*
 * Controller input (PAD). flags: bits 0-7 analog mode of each port/slot,
 * 0x400000 demo playback, 0x800000 demo recording, 0x04000000 actuators
 * being aligned, 0x08000000 vibration ready, 0x20000000 PadStartCom done,
 * 0x40000000 initialised, 0x80000000 multitap.
 * A demo replays recorded pad data (34 bytes a frame, up to 0x707 frames)
 * instead of the pad, except for Start.
 */
typedef struct PadState {
    /* 0x000 */ s32 flags;
    /* 0x004 */ u8 buf[2][0x22];
    /* 0x048 */ PadSlot slots[2][4];
    /* 0x3C8 */ u8 act[2][6];
    /* 0x3D4 */ s16 repeatRate; /* vsyncs */
    /* 0x3D6 */ s16 demoPad;
    /* 0x3D8 */ s32 demoData;
    /* 0x3DC */ s16 demoFrame;
    /* 0x3DE */ u8 unk3DE[2];
    /* 0x3E0 */ void (*init)(); /* PAD_INIT */
    /* 0x3E4 */ void (*shutdown)();
    /* 0x3E8 */ void (*update)(); /* PAD_UPDATE */
    /* 0x3EC */ s32 (*setVibration)(u16 port, s32 motor, s16 time, u8 value);
    /* 0x3F0 */ s32 (*setAnalogMode)();
    /* 0x3F4 */ s32 (*getPressed)(s32 pad);
    /* 0x3F8 */ s32 (*getHeld)(s32 pad);
    /* 0x3FC */ s32 (*getRepeated)(s32 pad);
    /* 0x400 */ void (*resetButtonMap)();
    /* 0x404 */ void (*swapButtons)();
    /* 0x408 */ s32 (*getButtonBit)(s32 pad, s32 button);
    /* 0x40C */ s32 (*startDemoRecording)();
    /* 0x410 */ void (*stopDemoRecording)();
    /* 0x414 */ s32 (*isDemoRecording)();
    /* 0x418 */ s32 (*startDemoPlayback)();
    /* 0x41C */ void (*stopDemoPlayback)();
    /* 0x420 */ s32 (*isDemoPlaying)();
} PadState;

/* One button of pad 1: newly pressed, or auto-repeated while held */
#define PAD_PRESSED(button) ((PAD.getPressed(0) >> PAD.getButtonBit(0, button)) & 1)
#define PAD_REPEATED(button) ((PAD.getRepeated(0) >> PAD.getButtonBit(0, button)) & 1)

void readPadButtons(s32 port, u8 *data, u8 *record);
void updateVibration(u16 port);
void resetButtonMap(u16 port);
void swapButtons(u16 port, s32 a, s32 b);
void startPad(void);
s32 pollPadState(u32 port);
void stopPad(void);
void initPad(s32, s32);
s32 setVibration(u16 port, s32 motor, s16 time, u8 value);

extern Random RANDOM;
extern u8 DEFAULT_BUTTON_MAP[16];
extern PadState PAD;
extern u16 RANDOM_TABLE[0x1000];

#endif /* DW3_PAD_H */
