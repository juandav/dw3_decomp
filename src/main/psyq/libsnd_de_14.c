/* libsnd.h declares data as unsigned char; the library took an int */
#define _SsSetNrpnVabAttr14 _SsSetNrpnVabAttr14_sdk
#include "psyq.h"
#undef _SsSetNrpnVabAttr14

void _SsUtResolveADSR(u_short adsr1, u_short adsr2, SsADSR *adsr);
void _SsUtBuildADSR(SsADSR *adsr, u_short *adsr1, u_short *adsr2);

void _SsSetNrpnVabAttr14(short vabId, short prog, short vag, VagAtr vagatr, short fn, int data) {
    SsADSR adsr;

    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    /* adsr is not filled from vagatr first (the library's own bug) */
    vagatr.porW = data;
    _SsUtBuildADSR(&adsr, &vagatr.adsr1, &vagatr.adsr2);
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
}

OBJECT_END();
