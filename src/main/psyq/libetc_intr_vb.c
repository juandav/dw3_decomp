#include "psyq.h"

void *startIntrVSync(void) {
    *D_8005B7C4 = 0x100;
    D_8005B7C0 = 0;
    func_8002EEA8(D_8005B7A0, 8);
    InterruptCallback(0, func_8002EE10);
    return func_8002EE7C;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr_vb", func_8002EE10);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr_vb", func_8002EE7C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr_vb", func_8002EEA8);

OBJECT_END();
