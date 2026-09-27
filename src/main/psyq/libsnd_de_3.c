/* libsnd.h declares data as unsigned char; the library took an int */
#define _SsSetNrpnVabAttr3 _SsSetNrpnVabAttr3_sdk
#include "psyq.h"
#undef _SsSetNrpnVabAttr3

void _SsSetNrpnVabAttr3(short vabId, short prog, short vag, VagAtr vagatr, short fn, int data) {
    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    vagatr.max = data;
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
}

OBJECT_END();
