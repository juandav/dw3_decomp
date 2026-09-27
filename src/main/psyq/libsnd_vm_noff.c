#include "psyq.h"

void vmNoiseOff(u8 voice) {
    D_800815D0[voice].unk1D = 0;
    D_800815D0[voice].unk0 = 0;
    D_800815D0[voice].unk4 = 0;
}

OBJECT_END();
