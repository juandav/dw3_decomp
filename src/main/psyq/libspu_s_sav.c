#include "psyq.h"

extern long D_8005BA14;
extern volatile u_short D_80081E48[];
extern volatile long D_8005B9E0;

u_long _SpuSetAnyVoice(long on_off, u_long voice_bit, int lo, int hi) {
    u_long ret;

    if (!(D_8005BA14 & 1)) {
        ret = ((D_8005BA28[hi] & 0xFF) << 16) | D_8005BA28[lo];
    } else {
        ret = ((D_80081E48[hi] & 0xFF) << 16) | D_80081E48[lo];
    }
    switch (on_off) {
    case SPU_ON:
        if (D_8005BA14 & 1) {
            D_80081E48[lo] |= voice_bit;
            D_80081E48[hi] |= (voice_bit >> 16) & 0xFF;
            D_8005B9E0 |= 1 << ((lo - 0xC6) >> 1);
        } else {
            D_8005BA28[lo] |= voice_bit;
            D_8005BA28[hi] |= (voice_bit >> 16) & 0xFF;
        }
        ret |= voice_bit & 0xFFFFFF;
        break;
    case SPU_OFF:
        if (D_8005BA14 & 1) {
            D_80081E48[lo] &= ~voice_bit;
            D_80081E48[hi] &= ~((voice_bit >> 16) & 0xFF);
            D_8005B9E0 |= 1 << ((lo - 0xC6) >> 1);
        } else {
            D_8005BA28[lo] &= ~voice_bit;
            D_8005BA28[hi] &= ~((voice_bit >> 16) & 0xFF);
        }
        ret &= ~(voice_bit & 0xFFFFFF);
        break;
    case SPU_BIT:
        if (D_8005BA14 & 1) {
            D_80081E48[lo] = voice_bit;
            D_80081E48[hi] = (voice_bit >> 16) & 0xFF;
            D_8005B9E0 |= 1 << ((lo - 0xC6) >> 1);
        } else {
            D_8005BA28[lo] = voice_bit;
            D_8005BA28[hi] = (voice_bit >> 16) & 0xFF;
        }
        ret = voice_bit & 0xFFFFFF;
        break;
    }
    return ret & 0xFFFFFF;
}

OBJECT_END();
