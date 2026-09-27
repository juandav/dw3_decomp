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
void _mtapFailAuto(PadPort *p);
int _padInitSioMode(PadPort *p);

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
        D_80055500[D_80055558] = status;
        if (status != -9) {
            if (status == 0) {
                D_80055570[D_80055558] = ((*p->unk3C >> 4) == 8) * 4;
            } else {
                _mtapFailAuto(p);
            }
        }
        D_8005555C = 0;
        D_80055558++;
        if (D_80055558 <= D_8005556C) {
            done = _padInitSioMode(&D_8007E740[D_80055558]);
            status = 0xFFFF;
        } else {
            done = 1;
            status = 0xFFFF;
        }
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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_800220D0);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_800223BC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_8002262C);

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
