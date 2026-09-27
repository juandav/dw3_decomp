#include "psyq.h"

extern long D_80080C80;
void data_ready_callback(void);
void func_8002B7EC(void);

int CdRead2(long mode) {
    u_char param[4];

    param[0] = mode;
    CdControl(CdlSetmode, param, NULL);
    if (mode & 0x100) {
        if (mode & 0x20) {
            D_80080C80 = 0;
        } else {
            D_80080C80 = 1;
        }
        func_8002E388(data_ready_callback);
        func_8002DE88((long)func_8002B7EC);
    }
    return CdControl(CdlReadS, NULL, NULL);
}

void func_8002B7EC(void) {
    StCdInterrupt();
}

OBJECT_END();
