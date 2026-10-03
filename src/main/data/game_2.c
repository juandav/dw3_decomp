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

#if VERSION_US
u16 D_80055394[] = {
#elif VERSION_EU
u16 D_80055BEC[] = {
#endif
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
#if VERSION_US
s32 D_800553F8[] = {
#elif VERSION_EU
s32 D_80055C50[] = {
#endif
    (s32)soundKeyOff, (s32)loadSoundBank, (s32)loadSoundBankInto,
};
s32 SOUND_CONTROL[] = {
    (s32)updateSoundLoading, (s32)isSoundLoading, (s32)stopAllSounds, (s32)stopSound,
    (s32)fadeOutSound,
};
#if VERSION_US
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
#elif VERSION_EU
s32 MODE_ENTRY_POINTS[] = {
    0, 0, 0x80087580, 0x80087580,
    0x800832E8, 0x80083118, 0x80087160, 0x80095E2C,
    0x80084410, 0x80082E98, 0x80083AC0, 0x80083084,
    0x80082DC8, 0x80083040, 0x80083028, 0x80083318,
    0x80083654, 0, 0x80083BD0, 0x80087CD4,
    0x80082F6C, 0x80084A30, 0x80082E8C,
};
s32 MODE_OVERLAY_FILES[] = {
    0, 0, 358, 358,
    458, 518, 359, 353,
    361, 360, 498, 354,
    494, 492, 464, 517,
    519, 0, 389, 462,
    465, 388, 357,
};
#endif
s32 OVERLAY_STATE[] = {
    0, 0,
};
s32 OVERLAY_FUNCS[] = {
    (s32)loadModeOverlay, (s32)loadSubOverlay,
};
