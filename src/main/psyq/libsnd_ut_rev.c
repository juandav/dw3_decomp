#include "psyq.h"

extern SpuReverbAttr D_80081D00;

short SsUtSetReverbType(short reverbType) {
    int clear;
    short type;

    clear = 0;
    type = reverbType;

    if (type < 0) {
        clear = 1;
        type = -type;
    }
    if ((u_short)type < 10) {
        D_80081D00.mask = SPU_REV_MODE;
        if (clear) {
            D_80081D00.mode = type | SPU_REV_MODE_CLEAR_WA;
        } else {
            D_80081D00.mode = type;
        }
        if (type == 0) {
            SpuSetReverb(SPU_OFF);
        }
        SpuSetReverbModeParam(&D_80081D00);
        return type;
    }
    return -1;
}

OBJECT_END();
