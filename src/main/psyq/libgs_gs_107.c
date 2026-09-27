#include "psyq.h"

extern MATRIX D_80080AB0;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_107", GsSetFlatLight);

void func_80029A70(MATRIX *m) {
    D_80080AB0 = *m;
    SetColorMatrix(m);
}

void func_80029AD4(MATRIX *m) {
    *m = D_80080AB0;
}

OBJECT_END();
