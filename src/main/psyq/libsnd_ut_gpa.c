#include "psyq.h"

/* which VABs are open */
extern u_char D_80081E20[];

short SsUtGetProgAtr(short vabId, short progNum, ProgAtr *p) {
    if (D_80081E20[vabId] == 1) {
        _SsVmVSetUp(vabId, progNum);
        p->tones = D_80081DE4[progNum].tones;
        p->mvol = D_80081DE4[progNum].mvol;
        p->prior = D_80081DE4[progNum].prior;
        p->mode = D_80081DE4[progNum].mode;
        p->mpan = D_80081DE4[progNum].mpan;
        p->attr = D_80081DE4[progNum].attr;
        return 0;
    }
    return -1;
}

OBJECT_END();
