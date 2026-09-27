#include "psyq.h"

extern u_long D_80081E80[];
extern u_short D_80081E78;
void _spu_setInTransfer(int mode);
int _spu_getInTransfer(void);

void SsVabClose(short vabId) {
    int flag;

    if (vabId >= 0 && vabId < 16) {
        flag = D_80081E20[vabId];
        if (flag < 3 && flag != 0) {
            SpuFree(D_80081E80[vabId]);
            D_80081E20[vabId] = 0;
            D_80081E78--;
            if (_spu_getInTransfer() == 1) {
                _spu_setInTransfer(0);
            }
        }
    }
}

OBJECT_END();
