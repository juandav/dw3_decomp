#include "psyq.h"

extern long D_80055568;
extern long D_8005556C;
extern long D_80055550;
extern long D_8007F140[2];
extern void (*D_80055518)(int status);
extern long D_80055560;
extern long D_8005555C;
extern long D_80055558;
extern PadPort *D_8005554C;
int _padInitSioMode(PadPort *p);
void func_80023344(PadPort *p);

int _padIsVsync(void) {
    if (!(D_8005558C[1] & 1)) {
        return 0;
    }
    if (!(D_8005558C[0] & 1)) {
        return 0;
    }
    if (D_80055540 != NULL) {
        D_80055540();
    }
    return 1;
}

int _padIntPad(void) {
    if (D_80055590->ctrl & 2) {
        D_80055590->ctrl = 0;
        return 0;
    }
    D_80055588 = 1;
    if (D_80055568 != 0 && D_8007F140[0] < 150) {
        D_8007F140[0]++;
    }
    if (D_8005556C == 0 && D_8007F140[1] < 150) {
        D_8007F140[1]++;
    }
    if (D_80055550 != 0 && D_80055568 <= D_8005556C) {
        D_8005555C = 0;
        D_80055558 = D_80055568;
        if (_padInitSioMode(&D_8005554C[D_80055568]) == 0) {
            D_80055518(0xFFFF);
        }
        D_80055560 = 0;
        while (D_80055558 <= D_8005556C) {
            func_80023344(&D_8005554C[D_80055558]);
        }
        D_80055590->baud = 0x88;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padInitSioMode);
