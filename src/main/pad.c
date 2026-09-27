#include "game.h"

void func_80017FAC(s32 multitap, s32 arg1) {
    s32 i;
    s32 j;
    s16 count;

    D_8004AD84.bzero(&D_8004AF78, 0x3E0);
    D_8004AD84.memset(D_8004AF78.act, 0xFF, sizeof(D_8004AF78.act));
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            func_8001855C((i * 16 + j) & 0xFF);
        }
    }
    if (multitap != 0) {
        PadInitMtap(D_8004AF78.buf[0], D_8004AF78.buf[1]);
        D_8004AF78.flags |= 0x80000000;
    } else {
        PadInitDirect(D_8004AF78.buf[0], D_8004AF78.buf[1]);
    }
    arg1 &= 0x7F;
    D_8004AF78.unk3D4 = (u8)arg1;
    count = (u8)arg1;
    D_8004AF78.flags |= 0x40000000;
    if (count == 0) {
        D_8004AF78.unk3D4 = 0x10;
    }
    func_800180FC();
}

void func_800180D8(void) {
    func_8001816C();
    D_8004AF78.flags = 0;
}

void func_800180FC(void) {
    if (!(D_8004AF78.flags & 0x40000000)) {
        func_80017FAC(0, 0x10);
    }
    if (!(D_8004AF78.flags & 0x20000000)) {
        PadStartCom();
        D_8004AF78.flags |= 0x20000000;
    }
}

void func_8001816C(void) {
    if (D_8004AF78.flags & 0x20000000) {
        PadStopCom();
    }
    D_8004AF78.flags &= ~0x20000000;
}

int PadChkVsync(void);
s32 func_80018BC0(u16 port, u8 *data);
void func_8001864C(void);
s32 func_80018654(s32 arg0);

void func_800181B8(void) {
    u8 *record = (u8 *)D_8004AF78.unk3D8 + D_8004AF78.unk3DC * 34;
    s32 ret;
    s32 i;
    s32 j;
    u16 port;

    ret = PadChkVsync();
    if (ret != 1) {
        return;
    }
    if (++D_8004AF78.unk3DC >= 0x707 && func_80018654(D_8004AF78.unk3D6) == ret) {
        func_8001864C();
        return;
    }
    for (i = 0; i < 2; i++) {
        port = i * 16;
        if (D_8004AF78.buf[i][1] == 0x80) {
            for (j = 0; j < 4; j++) {
                if (D_8004AF78.flags & 0x400000) {
                    func_80018868((u8)port, &D_8004AF78.buf[i][2 + j * 8], record + 2 + j * 8);
                } else {
                    func_80018BC0((u8)(port + j), &D_8004AF78.buf[i][2 + j * 8]);
                }
            }
        } else {
            if (D_8004AF78.flags & 0x400000) {
                func_80018868((u8)port, D_8004AF78.buf[i], record);
            } else {
                func_80018BC0((u8)port, D_8004AF78.buf[i]);
            }
        }
    }
}

s32 func_8001837C(u16 port, s32 motor, s16 time, u8 value) {
    u8 id = port;
    s32 mode;
    PadSlot *slot;
    s16 t;
    s32 pad;

    t = time;
    if (!(D_8004AF78.flags & 0x08000000)) {
        return 0;
    }
    if (func_80018774(id) == 0) {
        return 0;
    }
    mode = PadInfoMode(id, 2, 0);
    pad = id >> 4;
    slot = &D_8004AF78.slots[pad][port & 3];
    if (mode == 4 || mode == 7) {
        D_8004AF78.act[pad][motor & 1] = value;
    } else {
        D_8004AF78.act[pad][0] = 0x40;
        D_8004AF78.act[pad][1] = 1;
    }
    if (slot->actTimers[motor] <= 0) {
        slot->actTimers[motor] = t;
    } else if (t == 0) {
        slot->actTimers[motor] = 0;
    }
    PadSetAct(id, D_8004AF78.act[pad], 2);
    return 1;
}

u16 func_800184F0(s32 pad) {
    return D_8004AF78.slots[pad][0].unk0;
}

u16 func_80018514(s32 pad) {
    return D_8004AF78.slots[pad][0].unk6;
}

u16 func_80018538(s32 pad) {
    return D_8004AF78.slots[pad][0].unk2;
}

void func_8001855C(u16 port) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[i] = D_8004B39C[i];
    }
}

void func_800185C4(u16 port, s32 a, s32 b) {
    u8 tmp = D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[a];

    D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[a] = D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[b];
    D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[b] = tmp;
}

u8 func_8001861C(s32 pad, s32 index) {
    return D_8004AF78.slots[pad][0].unk5C[index];
}

s32 func_80018644(void) {
    return 0;
}

void func_8001864C(void) {
}

s32 func_80018654(s32 arg0) {
    if (D_8004AF78.flags & 0x800000) {
        if (D_8004AF78.unk3D6 == arg0) {
            return 1;
        }
        return -1;
    }
    return 0;
}

s32 func_8001868C(s16 arg0, s32 arg1) {
    if (!(D_8004AF78.flags & 0xC00000)) {
        D_8004AF78.flags |= 0x400000;
        if (D_8004AF78.unk3D8 == 0) {
            D_8004AF78.unk3D6 = arg0;
            D_8004AF78.unk3D8 = arg1;
            D_8004AF78.unk3DC = 0;
            func_8001837C((arg0 * 16) & 0xF0, 0, 0, 0);
            return 1;
        }
    }
    return 0;
}

void func_80018700(void) {
    if (D_8004AF78.flags & 0x400000) {
        D_8004AF78.flags &= ~0x400000;
        D_8004AF78.unk3D8 = 0;
        D_8004AF78.unk3D6 = 0;
        D_8004AF78.unk3DC = 0;
    }
}

s32 func_8001873C(s32 arg0) {
    if (D_8004AF78.flags & 0x400000) {
        if (D_8004AF78.unk3D6 == arg0) {
            return 1;
        }
        return -1;
    }
    return 0;
}

s32 PadGetState(s32 port);
s32 func_80018DC4(u16 port);

s32 func_80018774(u32 port) {
    u32 p = port;
    u32 mask;
    s32 state = PadGetState(p & 0xFF);

    switch (state) {
    case 0:
    case 1:
        mask = ~(((p >> 2) & 0x3C) | (p & 3)); D_8004AF78.flags = D_8004AF78.flags & mask & ~0xC000000;
        return 0;
    case 6:
        if (!(D_8004AF78.flags & 0x8000000)) {
            if (D_8004AF78.flags & 0x4000000) {
                D_8004AF78.flags |= 0x8000000;
            } else if (func_80018DC4(p & 0xFF)) {
                D_8004AF78.flags |= 0x4000000;
            }
        }
        return state;
    case 2:
        return state;
    case 3:
    case 4:
    case 5:
    default:
        return 0;
    }
}

void func_80018868(s32 port, u8 *data, u8 *record) {
    u32 id = port & 0xFF;
    s32 mode = PadInfoMode(id, 2, 0);
    u32 pad = (id >> 4) & 1;
    PadSlot *slot = &D_8004AF78.slots[(u8)pad][port & 3];
    s16 buttons;
    s16 i;
    u16 b;
    s16 x, y, z;

    if ((D_8004AF78.flags & 0x400000) && D_8004AF78.unk3D6 == ((port & 3) | pad)) {
        buttons = (~*(u16 *)(data + 2) & 8) | (~*(u16 *)(record + 2) & ~8);
        if (mode == 7) {
            for (i = 0; i < 4; i++) {
                slot->analog[i] = record[4 + i];
            }
        }
    } else {
        b = ~*(u16 *)(data + 2);
        x = (b >> 13) & 1;
        y = (b >> 14) & 1;
        z = (b >> 12) & 1;
        buttons = ~*(u16 *)(data + 2) & ~0x7000;
        if (y) {
            buttons |= 0x2000;
        }
        if (z) {
            buttons |= 0x4000;
        }
        if (x) {
            buttons |= 0x1000;
        }
        if (mode == 7) {
            for (i = 0; i < 4; i++) {
                slot->analog[i] = data[4 + i];
            }
        }
    }
    if (mode == 7) {
        if (slot->analog[2] < 0x41) {
            buttons |= 0x80;
        } else if (slot->analog[2] >= 0xC0) {
            buttons |= 0x20;
        }
        if (slot->analog[3] < 0x41) {
            buttons |= 0x10;
        } else if (slot->analog[3] >= 0xC0) {
            buttons |= 0x40;
        }
    }
    i = 0;
    slot->unk2 = 0;
    for (; i < 16; i++) {
        u8 bit = slot->unk5C[i];
        s32 *time = &slot->repeatTime[bit];
        u8 *count = &slot->repeatCount[bit];

        if ((buttons >> bit) & 1) {
            if (D_8004AF78.unk3D4 > 0) {
                if ((D_8004D5B8.funcs.unk38() - *time + *count) / D_8004AF78.unk3D4 != 0) {
                    *count += 10;
                    if (*count >= 12) {
                        *count = 12;
                    }
                    *time = D_8004D5B8.funcs.unk38();
                    slot->unk2 |= 1 << slot->unk5C[i];
                }
            }
        } else {
            *time = D_8004D5B8.funcs.unk38();
            *count = 0;
        }
    }
    b = slot->unk6;
    slot->unk6 = buttons;
    slot->unk4 = b;
    slot->unk0 = buttons & (b ^ buttons);
}

s32 func_80018BC0(u16 port, u8 *data) {
    u8 id = port;
    s32 mode;

    if (*data != 0 || func_80018774(id & 0xFF) == 0) {
        D_8004AF78.slots[(id >> 4) & 1][port & 3].unk0 = 0;
        D_8004AF78.slots[(id >> 4) & 1][port & 3].unk2 = 0;
        D_8004AF78.slots[(id >> 4) & 1][port & 3].unk6 = 0;
        return 0;
    }
    mode = PadInfoMode(id & 0xFF, 2, 0);
    if (mode == 4 || mode == 7) {
        func_80018EA0(id & 0xFF);
    }
    func_80018868(id & 0xFF, data, 0);
    return 1;
}

s32 func_80018CA8(s32 port, s32 on) {
    u32 id = port & 0xFF;
    s32 mode;
    s32 bit;

    if (func_80018774(id) != 0) {
        mode = PadInfoMode(id, 2, 0);
        if (mode == 4 || mode == 7) {
            bit = ((id >> 4) << 2) | (port & 3);
            if (on != 0) {
                D_8004AF78.flags |= 1 << bit;
                PadSetMainMode(id, PadInfoMode(id, 3, 0), 3);
            } else {
                D_8004AF78.flags &= ~(1 << bit);
                PadSetMainMode(id, PadInfoMode(id, 3, 0), 2);
            }
            D_8004AF78.flags &= 0xF3FFFFFF;
            return 1;
        }
    }
    return 0;
}

s32 func_80018DC4(u16 port) {
    u32 id = (u8)port;
    s32 count = PadInfoAct(id, -1, 0);
    s32 i;
    s32 act;

    for (i = 0; i < count; i++) {
        act = PadInfoAct(id, i, 2);
        if (act != 0) {
            D_8004AF78.act[id >> 4][i] = act & 1;
        }
    }
    return PadSetActAlign(port & 0xFF, D_8004AF78.act[(port & 0xFF) >> 4]);
}

void func_80018EA0(u16 port) {
    u8 id = port;
    s32 i;
    PadSlot *slot = &D_8004AF78.slots[id >> 4][port & 3];

    for (i = 0; i < 2; i++) {
        if (slot->actTimers[i] != 0) {
            if ((slot->actTimers[i] -= D_8004D5B8.funcs.unk3C()) <= 0) {
                slot->actTimers[i] = 0;
                D_8004AF78.act[id >> 4][i] = 0;
            }
            PadSetAct(port & 0xFF, D_8004AF78.act[id >> 4], 2);
        }
    }
}

void func_80018FA8(s32 arg0) {
    D_8004D3AC = arg0 & 0xFFF;
}

u16 func_80018FB8(void) {
    s32 index = (D_8004D3AC + 1) & 0xFFF;

    D_8004D3AC = index;
    return D_8004B3AC[index];
}
