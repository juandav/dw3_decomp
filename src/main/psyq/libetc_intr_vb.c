#include "psyq.h"

void *startIntrVSync(void) {
    *D_8005B7C4 = 0x100;
    D_8005B7C0 = 0;
    func_8002EEA8((long *)D_8005B7A0, 8);
    InterruptCallback(0, func_8002EE10);
    return func_8002EE7C;
}

void func_8002EE10(void) {
    int i;

    D_8005B7C0++;
    for (i = 0; i < 8; i++) {
        if (D_8005B7A0[i] != NULL) {
            D_8005B7A0[i]();
        }
    }
}

void *func_8002EE7C(int index, void (*func)()) {
    void (*old)() = D_8005B7A0[index];

    if (func != old) {
        D_8005B7A0[index] = func;
    }
    return old;
}

void func_8002EEA8(long *p, int n) {
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = 0;
        } while (i-- != 0);
    }
}

OBJECT_END();
