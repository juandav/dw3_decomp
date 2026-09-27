#include "psyq.h"

void SsInit(void) {
    ResetCallback();
    func_80037FD8();
    SpuClearReverbWorkArea(7);
    _SsInit();
}

OBJECT_END();
