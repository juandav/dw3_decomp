#include "psyq.h"

extern u_long D_80081E38[];
extern u_long D_80081E80[];
u_long func_8003A3E8(u_char *addr, u_long size);
void _spu_setInTransfer(int mode);

short SsVabTransBody(u_char *addr, short vabId) {
    u_long start;

    if (vabId >= 0 && vabId <= 16 && D_80081E20[vabId] == 2) {
        start = D_80081E80[vabId];
        SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
        if (SpuSetTransferStartAddr(start) != 0) {
            func_8003A3E8(addr, D_80081E38[vabId]);
            D_80081E20[vabId] = 1;
            return vabId;
        }
    }
    _spu_setInTransfer(0);
    return -1;
}

OBJECT_END();
