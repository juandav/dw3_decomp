#include "psyq.h"

extern PadPort D_8007E740[2];
extern long D_80055564;
extern PadPort D_8007E920[8];
extern u_char D_8007F0A0[2][0x23];
extern u_char D_8007F0E8[2][0x23];
extern void (*D_80055518)();
extern int (*D_80055520)(PadPort *p);
extern void (*D_80055524)();
extern int (*D_80055530)(PadPort *p);
extern int (*D_80055534)(PadPort *p);
extern void (*D_80055538)();
extern void (*D_8005553C)(PadPort *p);
extern PadPort *D_8005554C;
extern long D_80055558;
extern long D_8005555C;
extern long D_8005556C;
extern long D_80055570[];
extern long D_80055500[];
extern volatile SioRegs *D_80055508;

void func_80021DF0(PadPort *p);
void func_80021E64();
int func_80021FC0(); /* (PadPort *p, int mode) */
void func_800220D0();
PadPort *func_8002234C(int port);
void func_80021F7C(PadPort *p);
int func_800223BC(PadPort *p);
int func_80022D60(PadPort *p);
void func_8002262C();
void *bzero(u_char *p, int n);
void _mtapFailAuto();
int _padInitSioMode(PadPort *p);
int _padRecvAtLoadInfo(PadPort *p);
void _padCmdParaMode(PadPort *port, u_char param);
void _padSendAtLoadInfo(PadPort *port);

void _padInitMtapPort(void) {
    bzero((u_char *)D_8007E740, sizeof(D_8007E740));
    bzero((u_char *)D_8007E920, sizeof(D_8007E920));
    D_8005554C = D_8007E740;
    D_8007E740[0].unk3C = D_8007F0A0[0];
    D_8007E740[0].unk40 = D_8007F0E8[0];
    D_8007E740[0].unkC = &D_8007E920[0];
    D_8007E740[1].unk3C = D_8007F0A0[1];
    D_8007E740[1].unk40 = D_8007F0E8[1];
    D_8007E740[1].unkC = &D_8007E920[4];
    D_80055518 = func_80021E64;
    D_8005551C = func_80021DF0;
    D_80055520 = func_80021FC0;
    D_80055524 = func_800220D0;
    D_8005552C = func_8002234C;
    D_8005553C = func_80021F7C;
    D_80055530 = func_800223BC;
    D_80055534 = func_80022D60;
    D_80055538 = func_8002262C;
}

void func_80021DF0(PadPort *p) {
    int i;
    u_char *d;

    if (p->unk49 != 0) {
        p->unk49 = 0;
        p->unk46 = 0;
        p->unkE6 = 0;
        p->unk14 = NULL;
        p->unk18 = NULL;
        p->unkE3 = 0;
        p->unkE4 = 0;
        p->unkE6 = 0;
        p->unkE9 = 0;
        p->unkEA = 0;
        p->unk0 = 0;
        p->unk4 = 0;
        p->unk8 = 0;
        p->cmd = 0;
        p->prevCmd = 0;
        p->unk39 = 0;
        d = p->unk5D;
        for (i = 0; i < 6; i++) {
            *d++ = 0xFF;
        }
    }
}

void func_80021E64(int status) {
    PadPort *p;
    int done;

    do {
        p = &D_8007E740[D_80055558];
        D_80055508->ctrl = 0;
        *(D_80055500 + D_80055558) = status;
        if (status != -9) {
            if (status == 0) {
                *(D_80055570 + D_80055558) = ((*p->unk3C >> 4) == 8) * 4;
            } else {
                _mtapFailAuto(p);
            }
        }
        D_8005555C = 0;
        D_80055558++;
        done = D_8005556C < D_80055558 ? 1 : _padInitSioMode(&D_8007E740[D_80055558]);
        status = 0xFFFF;
    } while (!done);
}

void func_80021F7C(PadPort *p) {
    int i;
    PadPort *s;
    u_char cmd = p->cmd;

    p->cmd = 0;
    p->prevCmd = cmd;
    s = p->unkC;
    for (i = 0; i < 4; i++) {
        s->unk39 = s->prevCmd;
        s->prevCmd = s->cmd;
        s->cmd = 0;
        s++;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_80021FC0);

extern long D_80055560;

void func_800220D0(PadPort *p) {
    int i;
    int j;
    int n;
    int found;
    int power;
    u_char mask;
    u_char *align;
    u_char *act;

    bzero(p->unk57, 6);
    if (p->unkE6 != 0 && p->actTable != NULL) {
        n = p->actLen < 7 ? p->actLen : 6;
        for (i = 0; i < p->unkE9; i++) {
            found = 0;
            mask = ((PadActInfo *)p->unk4)[i].unk2 ? 0xFF : 1;
            align = p->unk5D;
            act = p->actTable;
            for (j = 0; j < n; align++, j++, act++) {
                if (*align == i && (*act & mask)) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                power = D_80055560 + ((PadActInfo *)p->unk4)[i].power;
                if (power < 0x3D) {
                    D_80055560 = power;
                } else {
                    found = 0;
                }
            }
            if (found) {
                align = p->unk5D;
                act = p->unk57;
                for (j = 0; j < n; j++, act++) {
                    if (*align++ == i) {
                        *act = 1;
                    }
                }
            }
        }
    } else if ((p->unkE8 == 4 || p->unkE8 == 5 || p->unkE8 == 7) && p->unkE6 == 0 && p->actLen >= 2) {
        if ((p->actTable[0] & 0xC0) == 0x40 && (p->actTable[1] & 1) && D_80055560 + 10 < 0x3D) {
            p->unk57[1] = 1;
            p->unk57[0] = 1;
            D_80055560 += 10;
        }
    } else if (p->unkE8 == 3) {
        p->unk57[0] = 1;
    } else if (p->unkE6 == 0) {
        for (j = 0; j < 6; j++) {
            p->unk57[j] = 1;
        }
    }
}

PadPort *func_8002234C(int port) {
    PadPort *p = &D_8007E740[0];

    if (port & 0xF0) {
        p = &D_8007E740[1];
    }
    if (D_80055564 != 0) {
        if ((p->unkE8 == 8 && !(port & 0xF)) || (port & 3)) {
            p = &p->unkC[port & 3];
        }
    }
    return p;
}

int func_800223BC(PadPort *p) {
    int i;
    PadPort *s;
    u_char cmd;

    if (p->unkC == NULL) {
        cmd = p->prevCmd;
        if (cmd != 0) {
            if (D_80055500[D_80055558] != 0 && cmd != 0x43) {
                p->cmd = cmd;
                p->prevCmd = 0;
            }
            return 0;
        }
        s = p->unk10->unkC;
        for (i = 0; i < 4; i++, s++) {
            if ((s->cmd == 0x43 || s->prevCmd == 0x43) && *s->data == 1) {
                return 0;
            }
        }
    }
    if (*p->unk3C == 0xF3) {
        if (p->unkE8 == 0 || (p->unk46 == 0xFF && p->unk49 != 2)) {
            _padCmdParaMode(p, 0);
            return 0;
        }
        if (*p->unk3C == 0xF3 && p->unk49 == 2 && p->unkE8 != 8) {
            D_8005551C(p);
            return 0;
        }
    }
    switch (p->unk46) {
    case 0:
        break;
    case 1:
        _padCmdParaMode(p, 1);
        break;
    case 0xFF:
        if (p->unkE8 == 8 && (s = p->unkC) != NULL) {
            for (i = 0; i < 4; i++, s++) {
                if (s->unk46 == 1) {
                    func_800223BC(s);
                    return 0;
                }
            }
            return 1;
        }
        break;
    case 0xFE:
        if (p->unk49 != 2) {
            _padCmdParaMode(p, 0);
            break;
        }
        p->cmd = 0;
        break;
    default:
        if (p->unk14 != NULL) {
            p->unk14(p);
        } else {
            _padSendAtLoadInfo(p);
        }
        break;
    }
    return 0;
}

void func_8002262C(PadPort *p) {
    u_char *rx;
    u_char *dst;
    int id;
    int old;
    int i;
    int cmd;

    if ((*p->unk3C & 0xF0) == 0) {
        p->unk30[0] = 0xFF;
        p->unk30[1] = 0;
        p->unkE8 = 0;
        p->unk35 = 0;
        D_8005551C(p);
        return;
    }
    if (p != p->unk10 && ((p->unk3C[1] != 0 && p->unk3C[1] != 0x5A) || (*(volatile u_char *)p->unk3C >> 4) == 8)) {
        _mtapFailAuto(p, 0xFF);
        return;
    }
    id = *p->unk3C >> 4;
    dst = p->unk30;
    old = p->unkE8;
    if (p->unk3C[1] == 0x5A) {
        if (old == 8) {
            *dst = 0;
        } else if (id != 0xF) {
            p->unkE8 = id;
            rx = p->unk3C;
            *dst++ = 0;
            *dst++ = *rx++;
            if (p != p->unk10) {
                p->unk35 = 8;
                rx++;
                for (i = 2; i < 8; i++) {
                    *dst++ = *rx++;
                }
            } else if (id == 8) {
                p->unk35 = 2;
            } else {
                p->unk35 = p->unk44;
                rx++;
                for (i = 2; i < p->unk35; i++) {
                    *dst++ = *rx++;
                }
            }
        }
    }
    if ((p->unk3C[1] == 0 && (p->unk46 != 1 || p->unk14 != NULL) && p->unk50 == 0) || p->unkE8 != old) {
        D_8005551C(p);
    }
    if (p->unkC != NULL || p->cmd == 0) {
        p->unk4A = 0;
    }
    if (p->unk46 == 0xFF) {
        return;
    }
    if ((u_char)(p->unk46 - 2) < 0xFC && *p->unk3C != 0xF3) {
        D_8005551C(p);
        return;
    }
    if (p->unkE8 == 8) {
        if (p->unk46 != 0) {
            p->unk46++;
            return;
        }
    } else if (p->unk46 != 0) {
        cmd = p == p->unk10 ? p->cmd : p->prevCmd;
        if (cmd == 0) {
            return;
        }
    }
    switch (p->unk46) {
    case 0:
        if (p->unkC == NULL && p->cmd != 0) {
            return;
        }
        if (p->unkE8 == 8 && p->unkC != NULL && *p->unkC->unk3C == 0xFF) {
            p->unk49 = 2;
            p->unk46 = 0xFF;
        } else {
            p->unk49 = 1;
            p->unk46++;
        }
        break;
    case 1:
        p->unk47[0] = 0;
        p->unk46++;
        break;
    case 0xFE:
        p->unk46++;
        break;
    case 0xFF:
        break;
    default:
        if (p->unk18 != NULL) {
            p->unk46 += p->unk18(p);
        } else {
            p->unk46 += _padRecvAtLoadInfo(p);
        }
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", _mtapFailAuto);

int func_80022D60(PadPort *p) {
    int i;
    PadPort *q;

    if (p->unkE6 == 0) {
        return 1;
    }
    if (p->unkC != NULL) {
        if (p->unk46 != 0xFF) {
            return 1;
        }
        q = p->unk10->unkC;
        for (i = 0; i < 4; i++, q++) {
            if (q->unk46 != 0xFF && q->unk46 != 0) {
                return 1;
            }
        }
        return 0;
    }
    return p->unk10->unk46 != 0xFF || p->unk46 != 0xFF;
}

OBJECT_END();
