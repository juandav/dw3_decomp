#include "psyq.h"

extern PadPort D_8007E740[2];
extern long D_80055564;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", _padInitMtapPort);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_80021DF0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_80021E64);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdtapres", func_80021F7C);

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
