#include "psyq.h"

long _SsVmSetProgVol(short vab, short prog, u_char vol) {
    if (_SsVmVSetUp(vab, prog) != 0) {
        return -1;
    }
    D_80081DE4[prog].mvol = vol;
    return D_80081DE4[prog].mvol;
}

OBJECT_END();
