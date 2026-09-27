/* libsnd.h declares data as unsigned char; the library took an int */
#define _SsSetNrpnVabAttr12 _SsSetNrpnVabAttr12_sdk
#include "psyq.h"
#undef _SsSetNrpnVabAttr12

void _SsUtResolveADSR(u_short adsr1, u_short adsr2, SsADSR *adsr);
void _SsUtBuildADSR(SsADSR *adsr, u_short *adsr1, u_short *adsr2);

void _SsSetNrpnVabAttr12(short vabId, short prog, short vag, VagAtr vagatr, short fn, int data) {
    SsADSR adsr;

    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    /* adsr is not filled from vagatr first (the library's own bug) */
    if ((u_char)(data - 1) < 0x3F) {
        adsr.srDir = 0;
    } else if ((u_char)(data - 0x40) < 0x40) {
        adsr.srDir = 1;
    }
    _SsUtBuildADSR(&adsr, &vagatr.adsr1, &vagatr.adsr2);
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
}

OBJECT_END();
