#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_s_ini", _SpuInit);

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
