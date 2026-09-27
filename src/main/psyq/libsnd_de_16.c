#include "psyq.h"

void _SsSetNrpnVabAttr16(short vabId, short prog, short tone, VagAtr vag, short fn, unsigned char data) {
    SsUtSetReverbDepth(data, data);
}

OBJECT_END();
