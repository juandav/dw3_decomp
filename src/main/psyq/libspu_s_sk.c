#include "psyq.h"

extern long D_8005BA14;
extern u_short _spu_RQ[4];
extern volatile long D_8005B9E0;
extern volatile long D_8005B9DC;
extern long D_8005B9B4;

void SpuSetKey(long on_off, u_long voice_bit) {
    volatile u_short *q;
    u_long hi;

    voice_bit &= 0xFFFFFF;
    hi = voice_bit >> 16;
    switch (on_off) {
    case SPU_ON:
        if (D_8005BA14 & 1) {
            q = _spu_RQ;
            q[0] = voice_bit;
            q[1] = hi;
            D_8005B9E0 |= 1;
            D_8005B9DC |= voice_bit;
            if (q[2] & voice_bit) {
                q[2] &= ~voice_bit;
            }
            if (q[3] & hi) {
                q[3] &= ~hi;
            }
        } else {
            D_8005BA28[0xC4] = voice_bit;
            D_8005BA28[0xC5] = hi;
            D_8005B9B4 |= voice_bit;
        }
        break;
    case SPU_OFF:
        if (D_8005BA14 & 1) {
            q = _spu_RQ;
            q[2] = voice_bit;
            q[3] = hi;
            D_8005B9E0 |= 1;
            D_8005B9DC &= ~voice_bit;
            if (q[0] & voice_bit) {
                q[0] &= ~voice_bit;
            }
            if (q[1] & hi) {
                q[1] &= ~hi;
            }
        } else {
            D_8005BA28[0xC6] = voice_bit;
            D_8005BA28[0xC7] = hi;
            D_8005B9B4 &= ~voice_bit;
        }
        break;
    }
}

OBJECT_END();
