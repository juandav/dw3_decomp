#include "psyq.h"

int PadInfoMode(int port, int term, int offs) {
    PadPort *p = D_8005552C(port);

    switch (term) {
    case 1:
        return p->unkE8;
    case 2:
        return p->unkE6;
    case 3:
        return p->unkE4;
    case 4:
        if (offs < 0) {
            return p->unkE3;
        }
        if (offs < p->unkE3) {
            return ((u_short *)p->unk0)[offs];
        }
        return 0;
    case 100:
        return p->unk4C;
    }
    return 0;
}

OBJECT_END();
