#include "psyq.h"

void *startIntrDMA(void) {
    func_8002F150((long *)D_8005B7D4, 8);
    *D_8005B7D0 = 0;
    InterruptCallback(3, func_8002EF24);
    return func_8002F0A4;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr_dma", func_8002EF24);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr_dma", func_8002F0A4);

void func_8002F150(long *p, int n) {
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = 0;
        } while (i-- != 0);
    }
}

OBJECT_END();
