#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padIsVsync);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padIntPad);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padInitSioMode);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_80023344);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padSioRW);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padSioRW2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padClrIntSio0);

void _padWaitRXready(void) {
    while (!(D_80055590->stat & 2)) {
    }
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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padGetActSize);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padSetRC2wait);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", _padChkRC2wait);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_800243A4);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_800243EC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_800244C4);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_80024570);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdresres", func_8002468C);

OBJECT_END();
