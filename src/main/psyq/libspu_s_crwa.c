#include "psyq.h"

extern long D_8005BFB8[];
extern u_char D_8005BA98[];
void func_8003A218(long event);
long _SpuIsInAllocateArea_(u_long addr);

long SpuClearReverbWorkArea(long rev_mode) {
    volatile long callback = 0;
    long restore = 0;
    u_long size;
    u_long addr;
    long mode;
    long more;
    u_long chunk;

    if ((u_long)rev_mode >= 10 || _SpuIsInAllocateArea_(D_8005BFB8[rev_mode])) {
        return -1;
    }
    if (rev_mode == 0) {
        size = 0x10 << D_8005BA50;
        addr = 0xFFF0 << D_8005BA50;
    } else {
        size = (0x10000 - D_8005BFB8[rev_mode]) << D_8005BA50;
        addr = D_8005BFB8[rev_mode] << D_8005BA50;
    }
    mode = D_8005BA44;
    if (mode == 1) {
        D_8005BA44 = 0;
        restore = 1;
    }
    more = 1;
    if (D_8005BA60 != 0) {
        callback = D_8005BA60;
        D_8005BA60 = 0;
    }
    do {
        chunk = 0x400;
        if (size <= 0x400) {
            chunk = size;
            more = 0;
        }
        _spu_t(2, addr);
        _spu_t(1);
        _spu_t(3, D_8005BA98, chunk);
        func_8003A218(D_8005B9B0);
        size -= 0x400;
        addr += 0x400;
    } while (more);
    if (restore) {
        D_8005BA44 = mode;
    }
    if (callback) {
        D_8005BA60 = callback;
    }
    return 0;
}

OBJECT_END();
