#include "stdwtitl.h"

/* libpress's DecDCTvlcBuild, the object after DecDCTvlc2's (src/stdwtitl/
   libpress_vlc2.s), built like libpress.c. It unpacks the VLC table that
   DecDCTvlc2 decodes with. */

extern u8 D_800878F0[]; /* the packed table, in libpress.c's data */

void DecDCTvlcBuild(u_short *table) {
    s32 distance;
    u_char *src;
    u_char *dst;
    u_int c;
    s32 n;
    s32 i;

    distance = 0;
    src = D_800878F0;
    dst = (u_char *)table;
    do {
        c = *src++;
        n = c & 0xFF;
        if (n < 0xF0U) {
            if (distance != 0) {
                for (; n >= 0; n--) {
                    *dst = *(dst - distance);
                    dst++;
                }
            } else {
                for (; n >= 0; n--) {
                    *dst++ = *src++;
                }
            }
        } else {
            distance = 0;
            if (n != 0xF0) {
                distance = (n << 8 | *src++) - 0xF0FF;
            }
        }
    } while (distance != 0xF00);
    for (i = 4; i < 0x8800; i++) {
        table[i] ^= table[i - 4];
    }
}
