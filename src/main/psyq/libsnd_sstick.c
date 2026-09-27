#include "psyq.h"

typedef struct SndTick {
    long mode;
    long manual;
} SndTick;
extern SndTick D_8005B848;
extern long D_80080D34;

void SsSetTickMode(long tick_mode) {
    long video = GetVideoMode();

    if (tick_mode & SS_NOTICK) {
        D_8005B848.manual = 1;
        D_8005B848.mode = tick_mode & 0xFFF;
    } else {
        D_8005B848.manual = 0;
        D_8005B848.mode = tick_mode;
    }
    if (D_8005B848.mode < SS_TICKMODE_MAX) {
        switch (D_8005B848.mode) {
        case SS_TICK50:
            D_80080D34 = 50;
            if (video == MODE_PAL) {
                D_8005B848.mode = SS_TICKVSYNC;
            } else {
                D_8005B848.mode = 50;
            }
            break;
        case SS_TICK60:
            D_80080D34 = 60;
            if (video == MODE_NTSC) {
                D_8005B848.mode = SS_TICKVSYNC;
            } else {
                D_8005B848.mode = 60;
            }
            break;
        case SS_TICK120:
            D_80080D34 = 120;
            break;
        case SS_TICK240:
            D_80080D34 = 240;
            break;
        case SS_TICKVSYNC:
            if (video == MODE_NTSC) {
                D_80080D34 = 60;
            } else if (video == MODE_PAL) {
                D_80080D34 = 50;
            } else {
                D_80080D34 = 60;
            }
            break;
        case SS_NOTICK0:
            if (video == MODE_NTSC) {
                D_80080D34 = 60;
            } else if (video == MODE_PAL) {
                D_80080D34 = 50;
            } else {
                D_80080D34 = 60;
            }
            break;
        default:
            D_80080D34 = 60;
            break;
        }
    } else {
        D_80080D34 = D_8005B848.mode;
    }
}

__asm__(".section .rodata\n\t.align 4\n");
OBJECT_END();
