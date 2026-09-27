#include "psyq.h"

void _SsUtResolveADSR(u_short adsr1, u_short adsr2, SsADSR *adsr);
void _SsUtBuildADSR(SsADSR *adsr, u_short *adsr1, u_short *adsr2);

void _SsSetNrpnVabAttr11(short vabId, short prog, short vag, VagAtr vagatr, short fn, u_char data) {
    SsADSR adsr;

    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    /* adsr is not filled from vagatr first (the library's own bug) */
    adsr.rrMode = 1;
    adsr.rr = data;
    _SsUtBuildADSR(&adsr, &vagatr.adsr1, &vagatr.adsr2);
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
}

OBJECT_END();
