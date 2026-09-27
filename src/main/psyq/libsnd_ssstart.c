#include "psyq.h"

extern long D_8005B85C;
extern void (*D_8005B850[2])(void);

/* the tick state D_8005B848..D_8005B85A as one object (D_8005B850 is func) */
typedef struct SndTick {
    long mode;
    long manual;
    void (*func[2])(void);
    char vsync;
    char half;
    char channel;
} SndTick;
extern SndTick D_8005B848;

void func_80032E08(void);
void func_80032E54(void);

void func_80032B98(int sw) {
    int i;
    u_long rcnt;
    u_short target;

    for (i = 0; i < 1000; i++) {
    }
    rcnt = RCntCNT2;
    target = 0x44E8;
    D_8005B848.vsync = 0;
    D_8005B848.half = 0;
    D_8005B848.channel = 6;
    D_8005B848.func[1] = NULL;
    switch (D_8005B848.mode) {
    case 0:
        D_8005B848.channel = 0x7F;
        return;
    case 5:
        D_8005B848.channel = 0;
        if (sw == 0) {
            D_8005B848.vsync = 1;
        } else {
            rcnt = RCntCNT3;
            target = 1;
        }
        break;
    case 3:
        target = 0x89D0;
        break;
    case 2:
        break;
    default:
        if (D_8005B848.manual != 0) {
            return;
        }
        if (D_8005B848.mode < 70) {
            target = 0x204CC0 / D_8005B848.mode;
            D_8005B848.half++;
        } else {
            target = 0x409980 / D_8005B848.mode;
        }
        break;
    }
    if (D_8005B848.vsync) {
        EnterCriticalSection();
        VSyncCallback(D_8005B848.func[0]);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcnt);
        SetRCnt(rcnt, target, RCntMdINTR);
        if (D_8005B848.channel == 0) {
            D_8005B848.func[1] = InterruptCallback(0, 0);
            InterruptCallback(D_8005B848.channel, func_80032E08);
        } else if (D_8005B848.half == 0) {
            InterruptCallback(D_8005B848.channel, D_8005B848.func[0]);
        } else {
            InterruptCallback(D_8005B848.channel, func_80032E54);
        }
    }
    ExitCriticalSection();
}

void SsStart(void) {
    func_80032B98(1);
}

void SsStart2(void) {
    func_80032B98(0);
}

void func_80032E08(void) {
    if (D_8005B850[1] != NULL) {
        D_8005B850[1]();
    }
    D_8005B850[0]();
}

void func_80032E54(void) {
    if (D_8005B85C == 0) {
        D_8005B85C = 1;
        return;
    }
    D_8005B85C = 0;
    D_8005B850[0]();
}

OBJECT_END();
