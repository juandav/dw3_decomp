#include "psyq.h"


extern long D_8005B9B4;
extern long D_8005B9BC;
extern long D_8005B9C0;
extern long D_8005B9C4;
extern SpuRevAttrInternal D_8005B9CC;
extern long D_8005B9DC;
extern long D_8005B9E0;
extern u_short D_8005B9E4[24];
extern long D_8005BA14;
extern long D_8005BA88;
extern long D_8005BA8C;
extern long D_8005BA90;
extern long D_8005BFB8[];

void _spu_init(int mode);
long _spu_FsetRXX(long reg, u_long addr, long flag);
int ResetCallback(void);
void SpuStart(void);

void _SpuInit(int mode) {
    int i;

    ResetCallback();
    _spu_init(mode);
    if (mode == 0) {
        for (i = 0; i < 24; i++) {
            D_8005B9E4[i] = 0xC000;
        }
    }
    SpuStart();
    D_8005B9BC = 0;
    D_8005B9C0 = 0;
    D_8005B9CC.mode = 0;
    D_8005B9CC.depthLeft = 0;
    D_8005B9CC.depthRight = 0;
    D_8005B9CC.delay = 0;
    D_8005B9CC.feedback = 0;
    D_8005B9C4 = D_8005BFB8[0];
    _spu_FsetRXX(0xD1, D_8005B9C4, 0);
    D_8005BA88 = 0;
    D_8005BA8C = 0;
    D_8005BA90 = 0;
    D_8005B9B8 = 0;
    D_8005BA44 = 0;
    D_8005B9B4 = 0;
    D_8005B9E0 = 0;
    D_8005B9DC = 0;
    D_8005BA14 = 0;
}

void SpuStart(void) {
    long event;

    if (D_8005BA18 == 0) {
        D_8005BA18 = 1;
        EnterCriticalSection();
        _SpuDataCallback(_spu_FiDMA);
        event = OpenEvent(0xF0000009, 0x20, 0x2000, NULL);
        D_8005B9B0 = event;
        EnableEvent(event);
        ExitCriticalSection();
    }
}

OBJECT_END();
