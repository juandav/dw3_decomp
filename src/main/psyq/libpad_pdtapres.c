#include "psyq.h"

extern PadPort D_8007E740[2];
extern long D_80055564;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", _padInitMtapPort);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_80021E64);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_80022D60);

OBJECT_END();
