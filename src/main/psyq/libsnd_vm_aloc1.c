#include "psyq.h"

extern char D_80081DF4;
extern long D_8005B818;

u_char _SsVmAlloc(void) {
    u_char count;
    u_short age;
    u_short envx;
    u_char i;
    u_char channel;
    u_char best;
    u_short prior;

    channel = 99;
    envx = 0xFFFF;
    count = 0;
    age = 0;
    best = 99;
    prior = D_80081E00.priority;
    for (i = 0; i < D_80081DF4; i++) {
        if (!(D_8005B818 & (1 << i))) {
            if (D_800815D0[i].unk1D == 0 && D_800815D0[i].unk6 == 0) {
                channel = i;
                break;
            }
            if (D_800815D0[i].priority < prior) {
                prior = D_800815D0[i].priority;
                best = i;
                envx = D_800815D0[i].unk6;
                age = D_800815D0[i].unk2;
                count = 1;
            } else if (D_800815D0[i].priority == prior) {
                count++;
                if (D_800815D0[i].unk6 < envx) {
                    age = D_800815D0[i].unk2;
                    envx = D_800815D0[i].unk6;
                    best = i;
                } else if (D_800815D0[i].unk6 == envx) {
                    if (age < D_800815D0[i].unk2) {
                        age = D_800815D0[i].unk2;
                        best = i;
                    }
                }
            }
        }
    }
    if (channel == 99) {
        if (count == 0) {
            channel = D_80081DF4;
        } else {
            channel = best;
        }
    }
    if (channel < D_80081DF4) {
        for (i = 0; i < D_80081DF4; i++) {
            if (!(D_8005B818 & (1 << i))) {
                D_800815D0[i].unk2++;
            }
        }
        D_800815D0[channel].unk2 = 0;
        D_800815D0[channel].priority = D_80081E00.priority;
        D_800815D0[channel].unk2A = 0;
        D_800815D0[channel].unk1E = 0;
    }
    return channel;
}

OBJECT_END();
