#include "psyq.h"

extern _SsFCALL D_80080C98;

void _SsSetControlChange(short sep, short seq, u_char control) {
    SeqStruct *score = &D_80080D38[sep][seq];
    u_char *p = score->readPos;
    u_char data = *p++;

    score->readPos = p;

    switch (control) {
    case 0:
        score->vabId = data;
        score->delta = _SsReadDeltaValue(sep, seq);
        break;
    case 6:
        D_80080C98.control[CC_DATAENTRY](sep, seq, data);
        break;
    case 7:
        D_80080C98.control[CC_MAINVOL](sep, seq, data);
        break;
    case 10:
        D_80080C98.control[CC_PANPOT](sep, seq, data);
        break;
    case 11:
        D_80080C98.control[CC_EXPRESSION](sep, seq, data);
        break;
    case 64:
        D_80080C98.control[CC_DAMPER](sep, seq, data);
        break;
    case 91:
        D_80080C98.control[CC_EXTERNAL](sep, seq, data);
        break;
    case 98:
        D_80080C98.control[CC_NRPN1](sep, seq, data);
        break;
    case 99:
        D_80080C98.control[CC_NRPN2](sep, seq, data);
        break;
    case 100:
        D_80080C98.control[CC_RPN1](sep, seq, data);
        break;
    case 101:
        D_80080C98.control[CC_RPN2](sep, seq, data);
        break;
    case 121:
        D_80080C98.control[CC_RESETALL](sep, seq);
        break;
    default:
        score->delta = _SsReadDeltaValue(sep, seq);
        break;
    }
}

OBJECT_END();
