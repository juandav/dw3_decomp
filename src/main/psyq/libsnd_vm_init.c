#include "psyq.h"

typedef struct SsRevAttr {
    long unk0;
    long unk4;
    short unk8;
    short unkA;
} SsRevAttr;

extern char D_80081EC8[];
extern u_short D_80081B30[192];
extern u_char D_80081B10[24];
extern short D_80081E78;
extern char D_80081DF4;
extern SsRevAttr D_80081D00;
extern short D_800815C0;
extern short D_800815C2;
extern short D_80081CF8;
extern short D_800815C4;
extern short D_800815C6;
extern short D_800815C8;
extern short D_800815CA;
extern char D_80081E30;
extern short D_80081DE0;
extern long D_80081DF8;
extern short D_80081DE2;
void _spu_setInTransfer(int mode);
void _SsVmKeyOffNow(int mode);
void _SsVmFlush(void);

void _SsVmInit(char voice_num) {
    u_short i;
    SpuVoiceAttr attr;
    int n;

    _spu_setInTransfer(0);
    D_80081D98 = 0;
    SpuInitMalloc(32, D_80081EC8);
    for (i = 0; i < 192; i++) {
        D_80081B30[i] = 0;
    }
    for (i = 0; i < 24; i++) {
        D_80081B10[i] = 0;
    }
    D_80081E78 = 0;
    for (i = 0; i < 16; i++) {
        D_80081E20[i] = 0;
    }
    n = voice_num;
    if (n >= 24U) {
        D_80081DF4 = 24;
    } else {
        D_80081DF4 = n;
    }
    attr.mask = 0x60093;
    attr.pitch = 0x1000;
    attr.addr = 0x1000;
    attr.adsr1 = 0x80FF;
    attr.volume.left = 0;
    attr.volume.right = 0;
    attr.adsr2 = 0x4000;
    for (i = 0; i < D_80081DF4; i++) {
        D_800815D0[i].unk2 = 24;
        D_800815D0[i].unk0 = 0xFF;
        D_800815D0[i].unk1D = 0;
        D_800815D0[i].unk4 = 0;
        D_800815D0[i].unk6 = 0;
        D_800815D0[i].unk10 = -1;
        D_800815D0[i].unk12 = 0;
        D_800815D0[i].prog = 0;
        D_800815D0[i].tone = 0xFF;
        D_800815D0[i].unk8 = 0;
        D_800815D0[i].unkC = 0;
        D_800815D0[i].unkA = 0x40;
        D_800815D0[i].unk36 = 0;
        D_800815D0[i].unk1E = 0;
        D_800815D0[i].unk20 = 0;
        D_800815D0[i].unk22 = 0;
        D_800815D0[i].unk24 = 0;
        D_800815D0[i].unk2A = 0;
        D_800815D0[i].unk2C = 0;
        D_800815D0[i].unk2E = 0;
        D_800815D0[i].unk30 = 0;
        D_800815D0[i].unk32 = 0;
        D_800815D0[i].unk26 = 0;
        attr.voice = 1 << i;
        SpuSetVoiceAttr(&attr);
        D_80081E00.voice = i;
        _SsVmKeyOffNow(1);
    }
    D_80081D00.unk0 = 0;
    D_80081D00.unk8 = 0x3FFF;
    D_80081D00.unkA = 0x3FFF;
    D_80081D00.unk4 = 0;
    D_800815C0 = 0;
    D_800815C2 = 0;
    D_80081CF8 = 0;
    D_800815C4 = 0;
    D_800815C6 = 0;
    D_800815C8 = 0;
    D_800815CA = 0;
    D_80081E30 = 0;
    D_80081DE0 = 0;
    D_80081DF8 = 0;
    D_80081DE2 = 0x80;
    _SsVmFlush();
}

OBJECT_END();
