#include "psyq.h"

extern int (*D_80055530)(PadPort *p);
extern int D_80055598;
extern int D_80055594;
extern int D_80055564;
int _padSioRW(PadPort *p, int data);
int _padChkRC2wait(void);
int _padSioRW2(PadPort *p, int arg);
extern long D_80055568;
extern long D_8005556C;
extern long D_80055550;
extern long D_8007F140[2];
extern int D_8007F13C;
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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_80023344);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padSioRW2);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padRecvAtLoadInfo);

int _padGetActSize(PadPort *p) {
    int a = ((p->unkE3 + 1) >> 1) * 4;
    int b = ((p->unkE9 * 5 + 3) & 0xFFC) + 4;

    return a + b + p->unkEC;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padLoadActInfo);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_80023E44);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_800243EC);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_80024570);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_8002468C);

OBJECT_END();
