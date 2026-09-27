#include "psyq.h"

extern int (*D_80055530)(PadPort *p);
extern int D_80055598;
extern int D_80055594;
extern int D_80055564;
int _padSioRW(PadPort *p, int data);
int _padChkRC2wait(void);
int _padSioRW2(PadPort *p, int data);
void _padSetRC2wait(int wait);
int _padClrIntSio0(void);
extern int D_8007F13C;
extern void (*D_80055518)(int status);
extern long D_8005555C;
extern int (*D_800555A0[])(PadPort *p);

void func_80023344(PadPort *p) {
    int ret;

    ret = D_800555A0[D_8005555C++](p);
    if (ret >= 0) {
        if (D_8005555C != 0) {
            if (D_8005555C != 3 || p->unk3C[0] != 0x80) {
                _padSetRC2wait(0x3C);
                if (_padClrIntSio0() == 0) {
                    D_80055518(-3);
                }
            }
        }
        if (D_8005555C > 4) {
            D_8005555C--;
        }
    } else {
        D_80055518(ret);
    }
}

int _padSioRW(PadPort *p, int data) {
    volatile SioRegs *sio;
    int rx;
    int baud;
    int id;

    if (data < 0) {
        rx = D_80055590->data;
        p->unk44 = 0xFF;
        p->unk45 = 1;
        *p->unk40 = ~data;
        sio = D_80055590;
        while (!(sio->stat & 1)) {
        }
        while (_padChkRC2wait() == 0) {
        }
        D_80055590->data = ~data;
    } else {
        baud = 0x88;
        id = *p->unk3C;
        if ((id >> 4) == 8 && p->unk44 >= 9) {
            baud = 0x22;
        }
        D_8007F138 = 0x1AE;
        D_8007F134 = *(volatile u_short *)0x1F801120;
        D_8007F13C = *(volatile u_short *)0x1F801124;
        if (!(D_80055590->stat & 2)) {
            volatile SioRegs *rxsio = D_80055590;

            while (!(rxsio->stat & 2)) {
            }
        }
        rx = D_80055590->data;
        D_80055590->baud = baud;
        while (!(*D_8005558C & 0x80)) {
            if (_padChkRC2wait() != 0) {
                return -20;
            }
        }
        D_80055590->data = data;
        if (baud == 0x22) {
            volatile u_long *irq = D_8005558C;
            volatile SioRegs *ctl = D_80055590;

            *irq = ~0x80;
            ctl->ctrl |= 0x10;
        }
        p->unk45++;
        p->unk3C[p->unk44] = rx;
        p->unk44++;
    }
    return rx;
}

int _padSioRW2(PadPort *p, int data) {
    volatile SioRegs *sio;
    int baud;
    int id;
    int rx;
    int now;
    int pos;

    baud = 0x88;
    id = *p->unk3C;
    if ((id >> 4) == 8 && p->unk44 >= 9) {
        baud = 0x22;
    }
    sio = D_80055590;
    do {
    } while (!(sio->stat & 2));
    _padSetRC2wait(400);
    rx = D_80055590->data;
    if (p->unk44 != 0 || (rx >> 4) != 8) {
        D_80055590->baud = baud;
    } else {
        D_80055590->baud = 0x22;
    }
    while (!(*D_8005558C & 0x80)) {
        *(volatile u_short *)0x1F801124;
        now = *(volatile u_short *)0x1F801120;
        if (now < D_8007F134) {
            if (*(volatile u_short *)0x1F801128 != 0) {
                now += *(volatile u_short *)0x1F801128;
            } else {
                now += 0x10000;
            }
        }
        if (*(volatile u_short *)0x1F801124 & 0x200) {
            if ((now - D_8007F134) >= D_8007F138) {
                return -2;
            }
        } else if (((now - D_8007F134) >> 3) >= D_8007F138) {
            return -2;
        }
    }
    if (p->unkE8 != 8 && D_8005555C == 2) {
        _padSetRC2wait(60);
        while (_padChkRC2wait() == 0) {
        }
    }
    D_80055590->data = data;
    if (D_8005555C == 3 && rx == 0x80) {
        volatile u_long *irq = D_8005558C;
        volatile SioRegs *ctl = D_80055590;

        *irq = ~0x80;
        ctl->ctrl |= 0x10;
    }
    pos = p->unk44;
    p->unk45++;
    if (pos != 0xFF) {
        p->unk3C[p->unk44] = rx;
    }
    p->unk44++;
    return rx;
}

int _padClrIntSio0(void) {
    volatile u_long *irq = D_8005558C;
    volatile SioRegs *sio = D_80055590;

    *irq = ~0x80;
    if (sio->stat & 0x80) {
        do {
            if (_padChkRC2wait() != 0) {
                return 0;
            }
        } while (D_80055590->stat & 0x80);
    }
    D_80055590->ctrl |= 0x10;
    return 1;
}

void _padWaitRXready(void) {
    do {
    } while (!(D_80055590->stat & 2));
}

void _padSetCmd(PadPort *port, u_char cmd, u_char *data, u_char len) {
    port->cmd = cmd;
    port->data = data;
    port->len = len;
}

void _padSendAtLoadInfo(PadPort *port) {
    switch (port->unk46) {
    case 2:
        func_8002425C(port);
        return;
    case 3:
        func_80024270(port, port->unkE4);
        return;
    case 4:
        func_800242B0(port, port->unk47[0]);
        return;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres_2", _padRecvAtLoadInfo);

int _padGetActSize(PadPort *p) {
    int a = ((p->unkE3 + 1) >> 1) * 4;
    int b = ((p->unkE9 * 5 + 3) & 0xFFC) + 4;

    return a + b + p->unkEC;
}

extern int (*D_80055534)(PadPort *p);
void func_80023D9C(PadPort *p);
int func_80023E44(PadPort *p);

int _padLoadActInfo(PadPort *p, int n) {
    int size;
    int len;

    if (n == 0 || p->unk4 != 0 || D_80055534(p) != 0) {
        return 0;
    }
    len = ((n + 3) >> 2) << 2;
    p->unk49 = 4;
    p->unk0 = len;
    p->unk46 = 1;
    p->unk14 = func_80023D9C;
    p->unk18 = func_80023E44;
    p->unk47[0] = 0;
    size = len + ((p->unkE3 + 1) >> 1) * 4;
    p->unk4 = size;
    p->unk8 = size + ((p->unkE9 * 5 + 3) & 0xFFC);
    return 1;
}

void func_80023D9C(PadPort *port) {
    switch (port->unk46) {
    case 2:
        func_80024270(port, port->unk47[0]);
        return;
    case 3:
        func_80024290(port, port->unk47[0]);
        return;
    case 4:
        if (port->unk47[1] == 0) {
            func_800242B0(port, port->unk47[0]);
            return;
        }
        func_800242D0(port);
        return;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres_2", func_80023E44);

void _padCmdParaMode(PadPort *port, u_char param) {
    port->cmd = 0x43;
    port->data = &port->param;
    port->param = param;
    port->len = 1;
}

void func_8002425C(PadPort *port) {
    port->cmd = 0x45;
    port->data = NULL;
    port->len = 0;
}

void func_80024270(PadPort *port, u_char param) {
    port->cmd = 0x4C;
    port->data = &port->param;
    port->param = param;
    port->len = 1;
}

void func_80024290(PadPort *port, u_char param) {
    port->cmd = 0x46;
    port->data = &port->param;
    port->param = param;
    port->len = 1;
}

void func_800242B0(PadPort *port, u_char param) {
    port->cmd = 0x47;
    port->data = &port->param;
    port->param = param;
    port->len = 1;
}

void func_800242D0(PadPort *port) {
    port->cmd = 0x4B;
    port->data = NULL;
    port->len = 0;
}

void _padSetRC2wait(int wait) {
    D_8007F138 = wait;
    D_8007F134 = *(volatile u_short *)0x1F801120;
}

int _padChkRC2wait(void) {
    int now = *(volatile u_short *)0x1F801120;

    if (now < D_8007F134) {
        if (*(volatile u_short *)0x1F801128 != 0) {
            now += *(volatile u_short *)0x1F801128;
        } else {
            now += 0x10000;
        }
    }
    if (*(volatile u_short *)0x1F801124 & 0x200) {
        return (now - D_8007F134) >= D_8007F138;
    }
    return ((now - D_8007F134) >> 3) >= D_8007F138;
}

void func_800243A4(PadPort *p) {
    D_80055598 = D_80055530(p);
    *p->unk3C = 0;
    _padSioRW(p, -2);
}

extern long D_80055558;
extern long D_80055568;
extern long D_80055554;
extern void (*D_80055548)(void);
extern void (*D_80055544)(void);

int func_800243EC(PadPort *p) {
    if (D_80055558 == D_80055568 && D_80055554 != 0) {
        D_80055548();
        D_80055544();
    }
    if (D_80055598 != 0) {
        D_80055530(p->unkC);
        D_80055530(p->unkC + 1);
    }
    if (p->cmd != 0) {
        return _padSioRW2(p, p->cmd);
    }
    return _padSioRW2(p, 0x42);
}

int func_800244C4(PadPort *p) {
    int ret;

    if (D_80055598 != 0) {
        D_80055530(&p->unkC[2]);
        D_80055530(&p->unkC[3]);
    }
    ret = _padSioRW2(p, p->cmd == 0 ? D_80055564 : 0);
    if (ret >= 0) {
        D_80055594 = (ret & 0xF) * 2;
        if (D_80055594 == 0) {
            D_80055594 = 0x20;
        }
        ret = 0;
    }
    return ret;
}

extern long D_8005559C;
extern void (*D_80055524)(PadPort *p);
extern u_char (*D_80055520)(PadPort *p, long flag);

int func_80024570(PadPort *p) {
    int ret;
    int type;
    long flag;

    flag = 0;
    if (D_80055564 != 0) {
        type = *p->unk3C;
        if ((type >> 4) == 8) {
            flag = p->cmd == 0;
        }
    }
    D_8005559C = flag;
    if (D_8005559C == 0 && p->cmd == 0 && p->prevCmd == 0 && (p == p->unk10 || p->unk39 == 0) &&
        *p->unk30 == 0) {
        D_80055524(p);
    }
    ret = _padSioRW2(p, D_80055520(p, D_8005559C));
    if (ret == 0x5A || ret == 0 || ret < 0) {
        return ret;
    }
    return -4;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres_2", func_8002468C);
