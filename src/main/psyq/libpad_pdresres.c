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
extern long D_80055570[];
extern void (*D_80055538)(PadPort *p);
extern void (*D_8005553C)(PadPort *p);
int _padChkRC2wait(void);
void _padSetRC2wait(int wait);
int _padClrIntSio0(void);
void _padWaitRXready(void);
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

int _padInitSioMode(PadPort *p) {
    D_80055590->ctrl = 0x40;
    D_80055590->ctrl = 0;
    D_80055590->mode = 0xD;
    D_80055590->baud = 0x88;
    _padSetRC2wait(p->unkE8 == 8 ? 0x50 : 0x91);
    D_80055590->ctrl = D_80055558 ? 0x3003 : 0x1003;
    if (D_80055570[D_80055558] >= 0) {
        while (D_80055570[D_80055558] > 0) {
            D_80055570[D_80055558]--;
            D_80055538(&p->unkC[D_80055570[D_80055558]]);
        }
        if (D_80055570[D_80055558] == 0) {
            D_80055570[D_80055558] = -1;
            D_80055538(p);
            D_8005553C(p);
        }
    }
    if (D_80055590->stat & 0x200) {
        D_80055590->ctrl |= 0x10;
        if (D_80055590->stat & 0x200) {
            while (_padChkRC2wait() == 0) {
            }
            D_80055590->data = 1;
            _padSetRC2wait(2000);
            if (_padClrIntSio0() == 0) {
                return 0;
            }
            _padWaitRXready();
            D_80055590->data;
            _padSetRC2wait(0x1AE);
            while (!(*D_8005558C & 0x80)) {
                if (_padChkRC2wait() != 0) {
                    return 0;
                }
            }
            D_80055590->data = 0x42;
            _padSetRC2wait(0x3C);
            if (_padClrIntSio0() == 0) {
                return 0;
            }
            _padWaitRXready();
            D_80055590->data;
            _padSetRC2wait(0x1AE);
            while (!(*D_8005558C & 0x80)) {
                if (_padChkRC2wait() != 0) {
                    return 0;
                }
            }
            D_80055590->data = 1;
            _padSetRC2wait(0x3C);
            if (_padClrIntSio0() == 0) {
                return 0;
            }
            _padWaitRXready();
            D_80055590->data;
            return 0;
        }
        *D_8005558C = ~0x80;
    }
    if (p->unk50 != 0 && p->cmd != 0) {
        return 0;
    }
    return 1;
}
