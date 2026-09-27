#include "psyq.h"

typedef struct SpuMallocBlock {
    u_long addr;
    u_long size;
} SpuMallocBlock;
extern long D_8005BA8C;
extern SpuMallocBlock *D_8005BA90;

void _spu_gcSPU(void) {
    long i;
    long j;
    u_long addr;
    u_long size;

    for (i = 0; i <= D_8005BA8C;) {
        if (D_8005BA90[i].addr & 0x80000000) {
            j = i + 1;
            while (1) {
                if (D_8005BA90[j].addr != 0x2FFFFFFF) {
                    break;
                }
                j++;
            }
            if ((D_8005BA90[j].addr & 0x80000000) &&
                (D_8005BA90[j].addr & 0x0FFFFFFF) ==
                    (D_8005BA90[i].addr & 0x0FFFFFFF) + D_8005BA90[i].size) {
                D_8005BA90[j].addr = 0x2FFFFFFF;
                D_8005BA90[i].size += D_8005BA90[j].size;
                continue;
            }
        }
        i++;
    }
    for (i = 0; i <= D_8005BA8C; i++) {
        if (D_8005BA90[i].size == 0) {
            D_8005BA90[i].addr = 0x2FFFFFFF;
        }
    }
    for (i = 0; i <= D_8005BA8C; i++) {
        if (D_8005BA90[i].addr & 0x40000000) {
            break;
        }
        for (j = i + 1; j <= D_8005BA8C; j++) {
            if (D_8005BA90[j].addr & 0x40000000) {
                break;
            }
            if ((D_8005BA90[j].addr & 0x0FFFFFFF) < (D_8005BA90[i].addr & 0x0FFFFFFF)) {
                addr = D_8005BA90[i].addr;
                size = D_8005BA90[i].size;
                D_8005BA90[i].addr = D_8005BA90[j].addr;
                D_8005BA90[i].size = D_8005BA90[j].size;
                D_8005BA90[j].addr = addr;
                D_8005BA90[j].size = size;
            }
        }
    }
    for (i = 0; i <= D_8005BA8C; i++) {
        if (D_8005BA90[i].addr & 0x40000000) {
            break;
        }
        if (D_8005BA90[i].addr == 0x2FFFFFFF) {
            D_8005BA90[i].addr = D_8005BA90[D_8005BA8C].addr;
            D_8005BA90[i].size = D_8005BA90[D_8005BA8C].size;
            D_8005BA8C = i;
            break;
        }
    }
    for (i = D_8005BA8C - 1; i >= 0; i--) {
        if (!(D_8005BA90[i].addr & 0x80000000)) {
            break;
        }
        D_8005BA90[i].addr = (D_8005BA90[i].addr & 0x0FFFFFFF) | 0x40000000;
        D_8005BA90[i].size += D_8005BA90[D_8005BA8C].size;
        D_8005BA8C = i;
    }
}

OBJECT_END();
