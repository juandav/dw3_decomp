#include "psyq.h"

extern void (*D_8005A1E0)();
extern long D_8005A1E4;

int func_8002B618(void);
void func_8002B654(void);
void func_8002B67C(void);
void func_8002B6A4(void);

int CdInit(void) {
    int i;

    i = 4;
    while (func_8002B618() != 1) {
        if (--i == -1) {
            printf("CdInit: Init failed\n");
            return 0;
        }
    }
    D_8005A2C8 = (long)func_8002B654;
    D_8005A2CC = (long)func_8002B67C;
    D_8005A1E0 = func_8002B6A4;
    D_8005A1E4 = 0;
    return 1;
}

int func_8002B618(void) {
    if (CD_init() != 0) {
        return 0;
    }
    return CD_initvol() == 0;
}

void func_8002B654(void) {
    func_8002B6D8(0xF0000003, 0x20);
}

void func_8002B67C(void) {
    func_8002B6D8(0xF0000003, 0x40);
}

void func_8002B6A4(void) {
    func_8002B6D8(0xF0000003, 0x40);
}

/* ASPSX padded the string table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
