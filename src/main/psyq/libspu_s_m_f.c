#include "psyq.h"

typedef struct SpuMallocBlock {
    u_long addr;
    u_long size;
} SpuMallocBlock;
extern SpuMallocBlock *D_8005BA90;
extern long D_8005BA88;
void _spu_gcSPU(void);

void SpuFree(u_long addr) {
    int i;

    for (i = 0; i < D_8005BA88; i++) {
        if (D_8005BA90[i].addr & 0x40000000) {
            break;
        }
        if (D_8005BA90[i].addr == addr) {
            D_8005BA90[i].addr = addr | 0x80000000;
            break;
        }
    }
    _spu_gcSPU();
}

OBJECT_END();
