#include "psyq.h"

extern SpuReverbAttr D_80081D00;

void SsUtSetReverbFeedback(short feedback) {
    D_80081D00.mask = SPU_REV_FEEDBACK;
    D_80081D00.feedback = feedback;
    SpuSetReverbModeParam(&D_80081D00);
}

OBJECT_END();
