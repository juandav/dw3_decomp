#include "psyq.h"

short SsUtSetVagAtr(short vabId, short progNum, short toneNum, VagAtr *p) {
    short i;

    if (D_80081E20[vabId] == 1) {
        _SsVmVSetUp(vabId, progNum);
        i = D_80081E00.prog * 16 + toneNum;
        D_80081DF0[i].prior = p->prior;
        D_80081DF0[i].mode = p->mode;
        D_80081DF0[i].vol = p->vol;
        D_80081DF0[i].pan = p->pan;
        D_80081DF0[i].center = p->center;
        D_80081DF0[i].shift = p->shift;
        D_80081DF0[i].max = p->max;
        D_80081DF0[i].min = p->min;
        D_80081DF0[i].vibW = p->vibW;
        D_80081DF0[i].vibT = p->vibT;
        D_80081DF0[i].porW = p->porW;
        D_80081DF0[i].porT = p->porT;
        D_80081DF0[i].pbmin = p->pbmin;
        D_80081DF0[i].pbmax = p->pbmax;
        D_80081DF0[i].adsr1 = p->adsr1;
        D_80081DF0[i].adsr2 = p->adsr2;
        D_80081DF0[i].prog = p->prog;
        D_80081DF0[i].vag = p->vag;
        return 0;
    }
    return -1;
}

OBJECT_END();
