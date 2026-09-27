/* libsnd.h declares data as unsigned char; the library took an int */
#define _SsSetNrpnVabAttr1 _SsSetNrpnVabAttr1_sdk
#include "psyq.h"
#undef _SsSetNrpnVabAttr1

void func_800345B8(void);

void _SsSetNrpnVabAttr1(short vabId, short prog, short vag, VagAtr vagatr, short fn, int data) {
    u_char mode;

    SsUtGetVagAtr(vabId, prog, vag, &vagatr);
    vagatr.mode = data;
    mode = data;
    SsUtSetVagAtr(vabId, prog, vag, &vagatr);
    if (mode == 0) {
        func_80034598();
    } else if (mode == 4) {
        func_800345B8();
    }
}

OBJECT_END();
