#include "psyq.h"

extern SpuReverbAttr D_80081D00;

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    D_80081D00.mask = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
    D_80081D00.depth.left = ldepth * 0x7FFF / 127;
    D_80081D00.depth.right = rdepth * 0x7FFF / 127;
    SpuSetReverbModeParam(&D_80081D00);
}

OBJECT_END();
