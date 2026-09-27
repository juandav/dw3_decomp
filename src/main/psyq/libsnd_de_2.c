/* libsnd.h declares data as unsigned char; the library took an int */
#define _SsSetNrpnVabAttr2 _SsSetNrpnVabAttr2_sdk
#include "psyq.h"
#undef _SsSetNrpnVabAttr2

void _SsSetNrpnVabAttr2(short vabId, short prog, short vag, VagAtr vagatr, short fn, int data) {
    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    vagatr.min = data;
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
}

OBJECT_END();
