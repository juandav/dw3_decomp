#include "psyq.h"

/* CD-ROM DMA (channel 3) and interface registers */
extern volatile u_char *D_8005A660;
extern volatile u_char *D_8005A664;
extern volatile u_long *D_8005A668;
extern volatile u_long *D_8005A66C;
extern volatile u_long *D_8005A670;
extern volatile u_long *D_8005A674;
extern volatile u_long *D_8005A678;
extern volatile u_long *D_8005A67C;

int CD_getsector(void *madr, int size) {
    *D_8005A660 = 0;
    *D_8005A664 = 0x80;
    *D_8005A66C = 0x20943;
    *D_8005A668 = 0x1323;
    *D_8005A670 |= 0x8000;
    *D_8005A678 = (u_long)madr;
    *D_8005A67C = size | 0x10000;
    do {
    } while (!(*D_8005A660 & 0x40));
    *D_8005A674 = 0x11000000;
    while (*D_8005A674 & 0x1000000) {
    }
    *D_8005A668 = 0x1325;
    return 0;
}

void func_8002E388(void (*func)()) {
    DMACallback(3, func);
}

OBJECT_END();
