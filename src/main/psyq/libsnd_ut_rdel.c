#include "psyq.h"

extern SpuReverbAttr D_80081D00;

void SsUtSetReverbDelay(short delay) {
    D_80081D00.mask = SPU_REV_DELAYTIME;
    D_80081D00.delay = delay;
    SpuSetReverbModeParam(&D_80081D00);
}

OBJECT_END();
