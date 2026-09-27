#include "psyq.h"

extern _SsFCALL D_80080C98;
extern long D_80080D30;
void func_80031E58();
void func_80031EB8();
void func_80031EE8();
void func_80031F18();
long _SsInitSoundSep(short sep, short seq, short vab, u_long *addr);

short SsSepOpen(u_long *addr, short vab_id, short seq_num) {
    int i;
    short sep = 0;
    short seq;
    long size;

    if (D_80080D30 == -1) {
        printf("Can't Open Sequence data any more\n\n");
        return -1;
    }
    D_80080C98.noteon = (void (*)())_SsNoteOn;
    D_80080C98.programchange = (void (*)())_SsSetProgramChange;
    D_80080C98.metaevent = (void (*)())_SsGetMetaEvent;
    D_80080C98.pitchbend = (void (*)())_SsSetPitchBend;
    D_80080C98.control[CC_NUMBER] = (void (*)())_SsSetControlChange;
    D_80080C98.control[CC_BANKCHANGE] = (void (*)())_SsContBankChange;
    D_80080C98.control[CC_MAINVOL] = (void (*)())_SsContMainVol;
    D_80080C98.control[CC_PANPOT] = (void (*)())_SsContPanpot;
    D_80080C98.control[CC_EXPRESSION] = (void (*)())_SsContExpression;
    D_80080C98.control[CC_DAMPER] = (void (*)())_SsContDamper;
    D_80080C98.control[CC_NRPN1] = (void (*)())_SsContNrpn1;
    D_80080C98.control[CC_NRPN2] = (void (*)())_SsContNrpn2;
    D_80080C98.control[CC_RPN1] = (void (*)())_SsContRpn1;
    D_80080C98.control[CC_RPN2] = (void (*)())_SsContRpn2;
    D_80080C98.control[CC_EXTERNAL] = (void (*)())_SsContExternal;
    D_80080C98.control[CC_RESETALL] = (void (*)())_SsContResetAll;
    D_80080C98.control[CC_DATAENTRY] = (void (*)())_SsContDataEntry;
    D_80080C98.ccentry[DE_PRIORITY] = (void (*)())_SsSetNrpnVabAttr0;
    D_80080C98.ccentry[DE_MODE] = (void (*)())_SsSetNrpnVabAttr1;
    D_80080C98.ccentry[DE_LIMITL] = (void (*)())_SsSetNrpnVabAttr2;
    D_80080C98.ccentry[DE_LIMITH] = (void (*)())_SsSetNrpnVabAttr3;
    D_80080C98.ccentry[DE_ADSR_AR_L] = (void (*)())_SsSetNrpnVabAttr4;
    D_80080C98.ccentry[DE_ADSR_AR_E] = (void (*)())_SsSetNrpnVabAttr5;
    D_80080C98.ccentry[DE_ADSR_DR] = (void (*)())_SsSetNrpnVabAttr6;
    D_80080C98.ccentry[DE_ADSR_SL] = (void (*)())_SsSetNrpnVabAttr7;
    D_80080C98.ccentry[DE_ADSR_SR_L] = (void (*)())_SsSetNrpnVabAttr8;
    D_80080C98.ccentry[DE_ADSR_SR_E] = (void (*)())_SsSetNrpnVabAttr9;
    D_80080C98.ccentry[DE_ADSR_RR_L] = (void (*)())_SsSetNrpnVabAttr10;
    D_80080C98.ccentry[DE_ADSR_RR_E] = (void (*)())_SsSetNrpnVabAttr11;
    D_80080C98.ccentry[DE_ADSR_SR] = (void (*)())_SsSetNrpnVabAttr12;
    D_80080C98.ccentry[DE_VIB_TIME] = (void (*)())_SsSetNrpnVabAttr13;
    D_80080C98.ccentry[DE_PORTA_DEPTH] = (void (*)())_SsSetNrpnVabAttr14;
    D_80080C98.ccentry[DE_REV_TYPE] = (void (*)())func_80031E58;
    D_80080C98.ccentry[DE_REV_DEPTH] = (void (*)())_SsSetNrpnVabAttr16;
    D_80080C98.ccentry[DE_ECHO_FB] = (void (*)())func_80031EB8;
    D_80080C98.ccentry[DE_ECHO_DELAY] = (void (*)())func_80031EE8;
    D_80080C98.ccentry[DE_DELAY] = (void (*)())func_80031F18;
    for (i = 0; i < 32; i++) {
        if (!(D_80080D30 & (1 << i))) {
            sep = i;
            break;
        }
    }
    D_80080D30 |= 1 << sep;
    for (seq = 0; seq < seq_num; seq++) {
        size = _SsInitSoundSep(sep, seq, vab_id, addr);
        if (size == -1) {
            return -1;
        }
        addr = (u_long *)((u_char *)addr + size);
    }
    return sep;
}

__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
