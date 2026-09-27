/* CD status byte, read as a u_char in this object */
#define D_8005A2D4 D_8005A2D4_long
#include "psyq.h"
#undef D_8005A2D4

extern u_char D_8005A2D4;
extern long D_8005A5E0[];
int CD_cw(u_char com, u_char *param, u_char *result, int async);
int CD_sync(int mode, u_char *result);

static inline int cd_control(u_char com, u_char *param, u_char *result, int async) {
    long old = D_8005A2C8;
    int cnt = 4;

    while (cnt--) {
        D_8005A2C8 = 0;
        if (com != CdlNop && (D_8005A2D4 & CdlStatShellOpen)) {
            CD_cw(CdlNop, 0, 0, 0);
        }
        if (param == 0 || D_8005A5E0[com] == 0 || CD_cw(CdlSetloc, param, result, 0) == 0) {
            D_8005A2C8 = old;
            if (CD_cw(com, param, result, async) == 0) {
                return 0;
            }
        }
    }
    D_8005A2C8 = old;
    return -1;
}

int CdControl(u_char com, u_char *param, u_char *result) {
    return cd_control(com, param, result, 0) == 0;
}

int CdControlF(u_char com, u_char *param) {
    return cd_control(com, param, 0, 1) == 0;
}

int CdControlB(u_char com, u_char *param, u_char *result) {
    if (cd_control(com, param, result, 0) != 0) {
        return 0;
    }
    return CD_sync(0, result) == CdlComplete;
}

OBJECT_END();
