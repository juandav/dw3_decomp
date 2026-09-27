#include "psyq.h"

short SsUtGetVagAtr(short vabId, short progNum, short toneNum, VagAtr *p) {
    short i;

    if (D_80081E20[vabId] == 1) {
        _SsVmVSetUp(vabId, progNum);
        i = D_80081E00.prog * 16 + toneNum;
        p->prior = D_80081DF0[i].prior;
        p->mode = D_80081DF0[i].mode;
        p->vol = D_80081DF0[i].vol;
        p->pan = D_80081DF0[i].pan;
        p->center = D_80081DF0[i].center;
        p->shift = D_80081DF0[i].shift;
        p->max = D_80081DF0[i].max;
        p->min = D_80081DF0[i].min;
        p->vibW = D_80081DF0[i].vibW;
        p->vibT = D_80081DF0[i].vibT;
        p->porW = D_80081DF0[i].porW;
        p->porT = D_80081DF0[i].porT;
        p->pbmin = D_80081DF0[i].pbmin;
        p->pbmax = D_80081DF0[i].pbmax;
        p->adsr1 = D_80081DF0[i].adsr1;
        p->adsr2 = D_80081DF0[i].adsr2;
        p->prog = D_80081DF0[i].prog;
        p->vag = D_80081DF0[i].vag;
        return 0;
    }
    return -1;
}

OBJECT_END();
