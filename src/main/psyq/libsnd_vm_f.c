#include "psyq.h"

extern long D_80081CB4;
extern long D_80081CB8[];
extern char D_80081DF4;
extern char D_80081E30;
extern u_short D_80081CF8;
extern u_short D_80081CFA;
extern u_short D_800815C0;
extern u_short D_800815C2;
extern u_short D_800815C4;
extern u_short D_800815C6;
extern u_short D_800815C8;
extern u_short D_800815CA;
extern void (*D_80081CB0)(int voice);
extern void (*D_80081B28)(int voice);
extern u_char D_80081B10[24];
extern u_short D_80081B30[];

void _SsVmFlush(void) {
    int voice;
    long mask;
    u_char hi;
    short lo;
    SpuVoiceAttr attr;
    u_long vmask;
    u_long bits;

    D_80081CB4 = (D_80081CB4 + 1) & 0xF;
    D_80081CB8[D_80081CB4] = 0;
    for (voice = 0; voice < D_80081DF4; voice++) {
        SpuGetVoiceEnvelope(voice, (short *)&D_800815D0[voice].unk6);
        if (D_800815D0[voice].unk6 == 0) {
            D_80081CB8[D_80081CB4] |= 1 << voice;
        }
    }
    if (D_80081E30 == 0) {
        mask = -1;
        for (voice = 0; voice < 15; voice++) {
            mask &= D_80081CB8[voice];
        }
        for (voice = 0; voice < D_80081DF4; voice++) {
            if (mask & (1 << voice)) {
                if (D_800815D0[voice].unk1D == 2) {
                    if (voice < 16) {
                        lo = 1 << voice;
                        hi = 0;
                    } else {
                        lo = 0;
                        hi = 1 << (voice - 16);
                    }
                    SpuSetNoiseVoice(0, (hi << 16) | lo);
                }
                D_800815D0[voice].unk1D = 0;
            }
        }
    }
    D_800815C0 &= ~D_80081CF8;
    D_800815C2 &= ~D_80081CFA;
    for (voice = 0; voice < 24; voice++) {
        if (D_800815D0[voice].unk1E != 0) {
            D_80081CB0(voice);
        }
        if (D_800815D0[voice].unk2A != 0) {
            D_80081B28(voice);
        }
    }
    for (voice = 0; voice < 24; voice++) {
        attr.mask = 0;
        attr.voice = 1 << voice;
        if (D_80081B10[voice] & 1) {
            attr.mask = 3;
            attr.volume.left = D_80081B30[voice * 8 + 0];
            attr.volume.right = D_80081B30[voice * 8 + 1];
        }
        if (D_80081B10[voice] & 4) {
            attr.mask |= 0x10;
            attr.pitch = D_80081B30[voice * 8 + 2];
        }
        if (D_80081B10[voice] & 8) {
            attr.mask |= 0x80;
            attr.addr = D_80081B30[voice * 8 + 3] << 3;
        }
        if (D_80081B10[voice] & 0x10) {
            attr.mask |= 0x60000;
            attr.adsr1 = D_80081B30[voice * 8 + 4];
            attr.adsr2 = D_80081B30[voice * 8 + 5];
        }
        if (attr.mask != 0) {
            SpuSetVoiceAttr(&attr);
        }
        D_80081B10[voice] = 0;
    }
    SpuSetKey(0, ((u_char)D_80081CFA << 16) | D_80081CF8);
    SpuSetKey(1, ((u_char)D_800815C2 << 16) | D_800815C0);
    vmask = 0xFFFFFF >> (24 - D_80081DF4);
    bits = ((D_800815C6 << 16) | D_800815C4) & vmask;
    SpuSetReverbVoice(8, bits | (SpuGetReverbVoice() & ~vmask));
    bits = ((D_800815CA << 16) | D_800815C8) & vmask;
    SpuSetNoiseVoice(8, bits | (SpuGetNoiseVoice() & ~vmask));
    D_80081CF8 = 0;
    D_80081CFA = 0;
    D_800815C0 = 0;
    D_800815C2 = 0;
    D_800815C8 = 0;
    D_800815CA = 0;
}

OBJECT_END();
