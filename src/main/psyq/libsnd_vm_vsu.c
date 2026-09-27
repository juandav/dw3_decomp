#include "psyq.h"

extern short D_80081DE2;
extern ProgAtr *D_80081D18[];
extern VagAtr *D_80081D58[];
extern VagAtr *D_80081DA0[];
extern VagAtr *D_80081DEC;

long _SsVmVSetUp(short vabId, short prog) {
    if ((u_short)vabId >= 16 || D_80081E20[vabId] != 1 || prog >= D_80081DE2) {
        return -1;
    }
    D_80081DEC = D_80081D58[vabId];
    D_80081DE4 = D_80081D18[vabId];
    D_80081DF0 = D_80081DA0[vabId];
    D_80081E00.vabId = vabId;
    D_80081E00.progNum = prog;
    D_80081E00.prog = *(u_char *)&D_80081DE4[prog].reserved1;
    return 0;
}

OBJECT_END();
