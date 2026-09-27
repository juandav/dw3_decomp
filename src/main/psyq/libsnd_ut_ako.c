#include "psyq.h"

extern long D_8005B818;
extern char D_80081DF4;
extern short D_80081E18;
void _SsVmKeyOffNow(int mode);

void SsUtAllKeyOff(short mode) {
    SpuVoiceAttr attr;
    short i;

    attr.mask = 0x60093;
    attr.pitch = 0x1000;
    attr.addr = 0x1000;
    attr.adsr1 = 0x80FF;
    attr.volume.left = 0;
    attr.volume.right = 0;
    attr.adsr2 = 0x4000;
    for (i = 0; i < D_80081DF4; i++) {
        if (!(D_8005B818 & (1 << i))) {
            D_800815D0[i].unk2 = 0x18;
            D_800815D0[i].unk6 = 0;
            D_800815D0[i].unk10 = 0xFF;
            D_800815D0[i].unk12 = 0;
            D_800815D0[i].prog = 0;
            D_800815D0[i].tone = 0xFF;
            D_800815D0[i].unk36 = 0;
            attr.voice = 1 << i;
            SpuSetVoiceAttr(&attr);
            D_80081E18 = i;
            _SsVmKeyOffNow(1);
        }
    }
}

OBJECT_END();
