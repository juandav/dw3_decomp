/* libsnd.h declares data as unsigned char; the library took an int */
#define _SsSetNrpnVabAttr0 _SsSetNrpnVabAttr0_sdk
#include "psyq.h"
#undef _SsSetNrpnVabAttr0

void _SsSetNrpnVabAttr0(short vabId, short prog, short vag, VagAtr vagatr, short fn, int data) {
    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    vagatr.prior = data;
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
}

OBJECT_END();
