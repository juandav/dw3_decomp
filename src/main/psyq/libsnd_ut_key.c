#include "psyq.h"

extern long D_80080D2C;
extern short D_80081E18;
void vmNoiseOff(u_char voice);
void _SsVmKeyOffNow(int mode);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ut_key", SsUtKeyOn);

short SsUtKeyOff(short voice, short vabId, short prog, short tone, short note) {
    if (D_80080D2C == 1) {
        return -1;
    }
    D_80080D2C = 1;
    if ((u_short)voice < 24) {
        if (D_800815D0[voice].vabId == vabId && D_800815D0[voice].prog == prog &&
            D_800815D0[voice].tone == tone && D_800815D0[voice].note == note &&
            D_800815D0[voice].unk0 == 0xFF) {
            vmNoiseOff(voice);
        } else {
            D_80081E18 = voice;
            _SsVmKeyOffNow(0);
        }
        D_800815D0[voice].unk2A = 0;
        D_800815D0[voice].unk1E = 0;
        D_80080D2C = 0;
        return 0;
    }
    D_80080D2C = 0;
    return -1;
}

OBJECT_END();
