#include "common.h"

extern s32 initSound[];
extern s32 playSound[];
extern s32 soundKeyOn[];
extern s32 soundKeyOff[];
extern s32 loadSoundBank[];
extern s32 loadSoundBankInto[];
extern s32 updateSoundLoading[];
extern s32 isSoundLoading[];
extern s32 stopAllSounds[];
extern s32 stopSound[];
extern s32 fadeOutSound[];
extern s32 loadModeOverlay[];
extern s32 loadSubOverlay[];

u16 D_80055394[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
};
s32 SOUND[] = {
    0, 0, 0, 0,
    (s32)initSound, (s32)playSound, (s32)soundKeyOn,
};
s32 D_800553F8[] = {
    (s32)soundKeyOff, (s32)loadSoundBank, (s32)loadSoundBankInto,
};
s32 SOUND_CONTROL[] = {
    (s32)updateSoundLoading, (s32)isSoundLoading, (s32)stopAllSounds, (s32)stopSound,
    (s32)fadeOutSound,
};
s32 MODE_ENTRY_POINTS[] = {
    0, 0, 0x80086CF4, 0x80086CF4,
    0x80082A80, 0x800828B0, 0x800868E0, 0x80095020,
    0x80083BA8, 0x80082630, 0x80083258, 0x8008281C,
    0x80082560, 0x800827D8, 0x800827A0, 0x80082AB0,
    0x80082DEC, 0, 0x80083368, 0x8008739C,
    0x80082704, 0x80084564, 0x80082624,
};
s32 MODE_OVERLAY_FILES[] = {
    0, 0, 344, 344,
    444, 504, 345, 339,
    347, 346, 502, 340,
    483, 479, 449, 503,
    505, 0, 375, 448,
    450, 374, 343,
};
s32 OVERLAY_STATE[] = {
    0, 0,
};
s32 OVERLAY_FUNCS[] = {
    (s32)loadModeOverlay, (s32)loadSubOverlay,
};
