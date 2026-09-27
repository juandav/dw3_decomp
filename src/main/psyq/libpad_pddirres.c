#include "psyq.h"

extern u_char D_8007E6B0[2][0x23];
extern u_char D_8007E6F8[2][0x23];
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
extern volatile SioRegs *D_800554F0;

void func_800213F0();
void func_80021388(PadPort *p);
void func_800214E4(PadPort *port);
int func_800214F4(PadPort *p);
void func_800215B0();
PadPort *func_8002182C(int port);
int func_8002184C(PadPort *p);
void func_8002195C();
int func_80021CA8(PadPort *p);
void *bzero(u_char *p, int n);
void _padSendAtLoadInfo(PadPort *port);
void _padCmdParaMode(PadPort *port, u_char param);
void _dirFailAuto(PadPort *p, int status);
int _padInitSioMode(PadPort *p);

void _padInitDirPort(void) {
    bzero((u_char *)D_8007E4D0, sizeof(D_8007E4D0));
    D_8005554C = D_8007E4D0;
    D_8007E4D0[0].unk3C = D_8007E6B0[0];
    D_8007E4D0[0].unk40 = D_8007E6F8[0];
    D_8007E4D0[1].unk3C = D_8007E6B0[1];
    D_8007E4D0[1].unk40 = D_8007E6F8[1];
    D_80055518 = func_800213F0;
    D_8005551C = func_80021388;
    D_80055520 = func_800214F4;
    D_80055524 = func_800215B0;
    D_8005552C = func_8002182C;
    D_8005553C = func_800214E4;
    D_80055530 = func_8002184C;
    D_80055534 = func_80021CA8;
    D_80055538 = func_8002195C;
}

void func_80021388(PadPort *p) {
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
        d = p->unk5D;
        for (i = 0; i < 6; i++) {
            *d++ = 0xFF;
        }
    }
}

void func_800213F0(int status) {
    PadPort *p;
    int done;

    do {
        p = &D_8007E4D0[D_80055558];
        if (status != -9) {
            if (status == 0) {
                *(D_80055570 + D_80055558) = 0;
            } else {
                _dirFailAuto(p, status);
                func_800214E4(p);
            }
        }
        D_8005555C = 0;
        D_800554F0->ctrl = 0;
        D_80055558++;
        done = D_8005556C < D_80055558 ? 1 : _padInitSioMode(&D_8007E4D0[D_80055558]);
        status = 0xFFFF;
    } while (!done);
}

void func_800214E4(PadPort *port) {
    u_char cmd = port->cmd;

    port->cmd = 0;
    port->prevCmd = cmd;
}

int func_800214F4(PadPort *p) {
    int i = p->unk45 - 3;

    switch (p->cmd) {
    case 0:
        if (i < 6 && p->unk57[i] == 0) {
            return 0;
        }
        if (i < p->actLen) {
            return p->actTable[i];
        }
        return 0;
    case 0x4D:
        return i < p->len ? p->data[i] : 0xFF;
    }
    return i < p->len ? p->data[i] : 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800215B0);

PadPort *func_8002182C(int port) {
    PadPort *p = D_8007E4D0;

    if (port & 0xF0) {
        p = &D_8007E4D0[1];
    }
    return p;
}

int func_8002184C(PadPort *p) {
    if (*p->unk3C == 0xF3) {
        if (p->unkE8 == 0) {
            _padCmdParaMode(p, 0);
            return 0;
        }
        if (p->unk46 == 0xFF) {
            _padCmdParaMode(p, 0);
            return 0;
        }
        if (p->unk49 == 2) {
            D_8005551C(p);
        }
    }
    switch (p->unk46) {
    case 1:
        _padCmdParaMode(p, 1);
        break;
    case 0xFE:
        _padCmdParaMode(p, 0);
        break;
    default:
        if (p->unk14 != NULL) {
            p->unk14(p);
        } else {
            _padSendAtLoadInfo(p);
        }
        break;
    case 0:
    case 0xFF:
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_8002195C);

void _dirFailAuto(PadPort *p, int status) {
    p->unk4C++;
    if (p->unk46 != 0) {
        if (p->unk46 == 1) {
            if (p->unk4A < 11) {
                p->unk4A++;
                return;
            }
            p->unk49 = 2;
            p->unk46 = 0xFF;
            return;
        }
        if (p->unk4A < 11) {
            p->unk4A++;
            return;
        }
        if (p->unk49 != 0) {
            D_8005551C(p);
        }
    }
    if (*p->unk3C != 0xF3) {
        p->unk30[0] = 0xFF;
        p->unk30[1] = 0;
        p->unkE8 = 0;
        p->unk35 = 0;
    }
}

int func_80021CA8(PadPort *p) {
    if (p->unkE6 == 0 || p->unk46 != 0xFF) {
        return 1;
    }
    return 0;
}

OBJECT_END();
