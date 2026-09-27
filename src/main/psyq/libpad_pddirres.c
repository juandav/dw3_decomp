#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", _padInitDirPort);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800213F0);

void func_800214E4(PadPort *port) {
    u_char cmd = port->cmd;

    port->cmd = 0;
    port->prevCmd = cmd;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800214F4);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800215B0);

PadPort *func_8002182C(int port) {
    PadPort *p = D_8007E4D0;

    if (port & 0xF0) {
        p = &D_8007E4D0[1];
    }
    return p;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_8002184C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_8002195C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", _dirFailAuto);

int func_80021CA8(PadPort *p) {
    if (p->unkE6 == 0 || p->unk46 != 0xFF) {
        return 1;
    }
    return 0;
}

OBJECT_END();
