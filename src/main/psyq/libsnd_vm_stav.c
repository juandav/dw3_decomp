#include "psyq.h"

u_char _SsVmSelectToneAndVag(u_char *tones, u_char *vags) {
    char i;
    u_char n = 0;

    for (i = 0; i < D_80081E00.tones; i++) {
        if (D_80081DF0[i + D_80081E00.prog * 16].min <= D_80081E00.note &&
            D_80081DF0[i + D_80081E00.prog * 16].max >= D_80081E00.note) {
            vags[n] = *(u_char *)&D_80081DF0[i + D_80081E00.prog * 16].vag;
            tones[n++] = i;
        }
    }
    return n;
}

OBJECT_END();
