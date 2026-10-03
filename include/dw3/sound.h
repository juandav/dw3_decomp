#ifndef DW3_SOUND_H
#define DW3_SOUND_H

/* Sound banks and the mode overlays (sound.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/*
 * Sound ids pack everything needed to play them:
 *   bit 31     a key-on of one VAB tone (sound effect), else a SEP sequence
 *   bit 30     exclusive (music): stops the previous exclusive sound
 *   bits 18-24 the sound bank id (see findSoundBank)
 *   key-on:    program bits 11-17, tone bits 7-10, note bits 0-6
 *   sequence:  SEQ bits 8-15, track (SEP) bits 0-7
 */
/* The sound interface (SOUND = SOUND_STATE + 0x4248) */
typedef struct SoundFuncs {
    /* 0x00 */ s32 music; /* the exclusive sound playing */
    /* 0x04 */ s32 lastSlot;
    /* 0x08 */ s32 loaderFiles;
    /* 0x0C */ s16 loaderState;
    /* 0x0E */ s16 loaderSlot;
    /* 0x10 */ void (*init)();
    /* 0x14 */ short (*playSound)(s32 id); /* SOUND_STATE.playSound */
    /* 0x18 */ short (*keyOn)(s32 slot, short prog, short note);
    /* 0x1C */ void (*keyOff)();
    /* 0x20 */ void (*loadBank)();
    /* 0x24 */ void (*loadBankInto)();
} SoundFuncs;

/* Loads the overlay of the current mode (OVERLAY_FUNCS) */
typedef struct OverlayFuncs {
    /* 0x0 */ void (*loadModeOverlay)();
    /* 0x4 */ void (*loadSubOverlay)();
} OverlayFuncs;

/* One of the three loaded sound banks: a VAB and its SEP sequences */
typedef struct SoundBank {
    /* 0x00 */ s32 id;
    /* 0x04 */ s16 vabId;
    /* 0x06 */ s16 numSeqs;
    /* 0x08 */ s16 seqs[4];
    /* 0x10 */ s32 headBuffer; /* VAB header and SEPs are copied here */
    /* 0x14 */ s32 spuAddr;
} SoundBank;

/* Loads a bank in the background (updateSoundLoading) */
typedef struct SoundLoader {
    /* 0x0 */ s32 *files; /* SoundFiles */
    /* 0x4 */ s16 state; /* 0 idle, 1 header, 2 body, 3 transfer */
    /* 0x6 */ s16 slot;
} SoundLoader;

typedef struct SoundState {
    /* 0x0000 */ u8 seqTable[0x4200]; /* SsSetTableSize(6 SEQs, 16 SEPs) */
    /* 0x4200 */ SoundBank banks[3];
    /* 0x4248 */ s32 music; /* SOUND starts here */
    /* 0x424C */ s32 lastSlot;
    /* 0x4250 */ SoundLoader loader;
    /* 0x4258 */ void (*init)(void);
    /* 0x425C */ short (*playSound)(s32 id); /* returns the voice of a key-on */
    /* 0x4260 */ short (*keyOn)(s32 slot, short prog, short note);
    /* 0x4264 */ void (*keyOff)(s32 id, s16 voice);
    /* 0x4268 */ void (*loadBank)(s32 id);
    /* 0x426C */ void (*loadBankInto)(s32 slot, s32 id);
    /* 0x4270 */ void (*updateLoading)(void);
    /* 0x4274 */ s32 (*isLoading)(void);
    /* 0x4278 */ void (*stopAll)(void);
    /* 0x427C */ void (*stopSound)(s32 id);
} SoundState;

typedef struct OverlayState {
    /* 0x0 */ s32 mode; /* whose overlay is loaded */
    /* 0x4 */ s32 subOverlay;
} OverlayState;

void updateSoundLoading(void);
s32 isSoundLoading(void);
s32 findSoundBank(s32 id);
void loadSoundBankInto(s32 index, s32 id);

extern SoundFuncs SOUND;
extern OverlayFuncs OVERLAY_FUNCS[];
extern s32 *SOUND_BANK_FILES[];
extern s32 SOUND_SPU_ADDRS[];
extern s32 SOUND_HEAD_BUFFERS[];
extern s32 (*MODE_ENTRY_POINTS[])(void);
extern void *SUB_OVERLAY_ADDRESS;
extern OverlayState OVERLAY_STATE[];
extern SoundState SOUND_STATE;

#endif /* DW3_SOUND_H */
