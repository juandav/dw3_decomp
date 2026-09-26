#include "psyq.h"

int ResetCallback(void) {
    return D_8005B780->resetCallback();
}

void *InterruptCallback(int irq, void (*func)()) {
    return D_8005B780->interruptCallback(irq, func);
}

void *DMACallback(int dma, void (*func)()) {
    return D_8005B780->dmaCallback(dma, func);
}

int VSyncCallback(void (*func)()) {
    return (int)D_8005B780->vsyncCallbacks(4, func);
}

void *VSyncCallbacks(int ch, void (*func)()) {
    return D_8005B780->vsyncCallbacks(ch, func);
}

int StopCallback(void) {
    return D_8005B780->stopCallback();
}

int RestartCallback(void) {
    return D_8005B780->restartCallback();
}

int CheckCallback(void) {
    return D_8005A6FA;
}

u_short GetIntrMask(void) {
    return *D_8005B788;
}

u_short SetIntrMask(u_short mask) {
    u_short old = *D_8005B788;

    *D_8005B788 = mask;
    return old;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002E7BC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002E894);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002EA64);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002EBAC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002EC4C);

void func_8002ECC4(long *p, int n) {
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = 0;
        } while (i-- != 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002ECE8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", _96_remove);

OBJECT_END();
