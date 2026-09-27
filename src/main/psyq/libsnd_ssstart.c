#include "psyq.h"

extern long D_8005B85C;
extern void (*D_8005B850[2])(void);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssstart", func_80032B98);

void SsStart(void) {
    func_80032B98(1);
}

void SsStart2(void) {
    func_80032B98(0);
}

void func_80032E08(void) {
    if (D_8005B850[1] != NULL) {
        D_8005B850[1]();
    }
    D_8005B850[0]();
}

void func_80032E54(void) {
    if (D_8005B85C == 0) {
        D_8005B85C = 1;
        return;
    }
    D_8005B85C = 0;
    D_8005B850[0]();
}

OBJECT_END();
