#include "game.h"

/* Opens the pads (PadInitMtap or PadInitDirect); repeatRate 0 means 16 */
void initPad(s32 multitap, s32 repeatRate) {
    s32 i;
    s32 j;
    s16 count;

    HEAP.zero(&PAD, 0x3E0);
    HEAP.fill(PAD.act, 0xFF, sizeof(PAD.act));
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            resetButtonMap((i * 16 + j) & 0xFF);
        }
    }
    if (multitap != 0) {
        PadInitMtap(PAD.buf[0], PAD.buf[1]);
        PAD.flags |= 0x80000000;
    } else {
        PadInitDirect(PAD.buf[0], PAD.buf[1]);
    }
    repeatRate &= 0x7F;
    PAD.repeatRate = (u8)repeatRate;
    count = (u8)repeatRate;
    PAD.flags |= 0x40000000;
    if (count == 0) {
        PAD.repeatRate = 0x10;
    }
    startPad();
}

void shutdownPad(void) {
    stopPad();
    PAD.flags = 0;
}

void startPad(void) {
    if (!(PAD.flags & 0x40000000)) {
        initPad(0, 0x10);
    }
    if (!(PAD.flags & 0x20000000)) {
        PadStartCom();
        PAD.flags |= 0x20000000;
    }
}

void stopPad(void) {
    if (PAD.flags & 0x20000000) {
        PadStopCom();
    }
    PAD.flags &= ~0x20000000;
}

int PadChkVsync(void);
s32 readPad(u16 port, u8 *data);
void stopDemoRecording(void);
s32 isDemoRecording(s32 pad);

/* Reads every pad, or the demo data while a demo plays */
void updatePad(void) {
    u8 *record = (u8 *)PAD.demoData + PAD.demoFrame * 34;
    s32 ret;
    s32 i;
    s32 j;
    u16 port;

    ret = PadChkVsync();
    if (ret != 1) {
        return;
    }
    if (++PAD.demoFrame >= 0x707 && isDemoRecording(PAD.demoPad) == ret) {
        stopDemoRecording();
        return;
    }
    for (i = 0; i < 2; i++) {
        port = i * 16;
        if (PAD.buf[i][1] == 0x80) {
            for (j = 0; j < 4; j++) {
                if (PAD.flags & 0x400000) {
                    readPadButtons((u8)port, &PAD.buf[i][2 + j * 8], record + 2 + j * 8);
                } else {
                    readPad((u8)(port + j), &PAD.buf[i][2 + j * 8]);
                }
            }
        } else {
            if (PAD.flags & 0x400000) {
                readPadButtons((u8)port, PAD.buf[i], record);
            } else {
                readPad((u8)port, PAD.buf[i]);
            }
        }
    }
}

/* Starts a motor for `time` vsyncs (0 stops it) */
s32 setVibration(u16 port, s32 motor, s16 time, u8 value) {
    u8 id = port;
    s32 mode;
    PadSlot *slot;
    s16 t;
    s32 pad;

    t = time;
    if (!(PAD.flags & 0x08000000)) {
        return 0;
    }
    if (pollPadState(id) == 0) {
        return 0;
    }
    mode = PadInfoMode(id, 2, 0);
    pad = id >> 4;
    slot = &PAD.slots[pad][port & 3];
    if (mode == 4 || mode == 7) {
        PAD.act[pad][motor & 1] = value;
    } else {
        PAD.act[pad][0] = 0x40;
        PAD.act[pad][1] = 1;
    }
    if (slot->vibrationTimers[motor] <= 0) {
        slot->vibrationTimers[motor] = t;
    } else if (t == 0) {
        slot->vibrationTimers[motor] = 0;
    }
    PadSetAct(id, PAD.act[pad], 2);
    return 1;
}

u16 getPadPressed(s32 pad) {
    return PAD.slots[pad][0].pressed;
}

u16 getPadHeld(s32 pad) {
    return PAD.slots[pad][0].held;
}

u16 getPadRepeated(s32 pad) {
    return PAD.slots[pad][0].repeated;
}

void resetButtonMap(u16 port) {
    s32 i;

    for (i = 0; i < 16; i++) {
        PAD.slots[(u8)port >> 4][port & 3].buttonMap[i] = DEFAULT_BUTTON_MAP[i];
    }
}

void swapButtons(u16 port, s32 a, s32 b) {
    u8 tmp = PAD.slots[(u8)port >> 4][port & 3].buttonMap[a];

    PAD.slots[(u8)port >> 4][port & 3].buttonMap[a] = PAD.slots[(u8)port >> 4][port & 3].buttonMap[b];
    PAD.slots[(u8)port >> 4][port & 3].buttonMap[b] = tmp;
}

u8 getButtonBit(s32 pad, s32 index) {
    return PAD.slots[pad][0].buttonMap[index];
}

/* Demo recording was left out of the release: these three are stubs */
s32 startDemoRecording(void) {
    return 0;
}

void stopDemoRecording(void) {
}

s32 isDemoRecording(s32 pad) {
    if (PAD.flags & 0x800000) {
        if (PAD.demoPad == pad) {
            return 1;
        }
        return -1;
    }
    return 0;
}

/* Replays `data` (34 bytes per frame) as the input of pad */
s32 startDemoPlayback(s16 pad, s32 data) {
    if (!(PAD.flags & 0xC00000)) {
        PAD.flags |= 0x400000;
        if (PAD.demoData == 0) {
            PAD.demoPad = pad;
            PAD.demoData = data;
            PAD.demoFrame = 0;
            setVibration((pad * 16) & 0xF0, 0, 0, 0);
            return 1;
        }
    }
    return 0;
}

void stopDemoPlayback(void) {
    if (PAD.flags & 0x400000) {
        PAD.flags &= ~0x400000;
        PAD.demoData = 0;
        PAD.demoPad = 0;
        PAD.demoFrame = 0;
    }
}

s32 isDemoPlaying(s32 pad) {
    if (PAD.flags & 0x400000) {
        if (PAD.demoPad == pad) {
            return 1;
        }
        return -1;
    }
    return 0;
}

s32 PadGetState(s32 port);
s32 alignActuators(u16 port);

s32 pollPadState(u32 port) {
    u32 p = port;
    u32 mask;
    s32 state = PadGetState(p & 0xFF);

    switch (state) {
    case 0:
    case 1:
        mask = ~(((p >> 2) & 0x3C) | (p & 3)); PAD.flags = PAD.flags & mask & ~0xC000000;
        return 0;
    case 6:
        if (!(PAD.flags & 0x8000000)) {
            if (PAD.flags & 0x4000000) {
                PAD.flags |= 0x8000000;
            } else if (alignActuators(p & 0xFF)) {
                PAD.flags |= 0x4000000;
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

/* Builds held/pressed/repeated from the raw data (the demo record replaces all but Start) */
void readPadButtons(s32 port, u8 *data, u8 *record) {
    u32 id = port & 0xFF;
    s32 mode = PadInfoMode(id, 2, 0);
    u32 pad = (id >> 4) & 1;
    PadSlot *slot = &PAD.slots[(u8)pad][port & 3];
    s16 buttons;
    s16 i;
    u16 b;
    s16 circle, cross, triangle;

    if ((PAD.flags & 0x400000) && PAD.demoPad == ((port & 3) | pad)) {
        buttons = (~*(u16 *)(data + 2) & 8) | (~*(u16 *)(record + 2) & ~8);
        if (mode == 7) {
            for (i = 0; i < 4; i++) {
                slot->analog[i] = record[4 + i];
            }
        }
    } else {
#if VERSION_US
        b = ~*(u16 *)(data + 2);
        circle = (b >> 13) & 1;
        cross = (b >> 14) & 1;
        triangle = (b >> 12) & 1;
        buttons = ~*(u16 *)(data + 2) & ~0x7000;
        if (cross) {
            buttons |= 0x2000;
        }
        if (triangle) {
            buttons |= 0x4000;
        }
        if (circle) {
            buttons |= 0x1000;
        }
#elif VERSION_EU
        /* the Japanese language keeps the buttons as they are */
        buttons = ~*(u16 *)(data + 2);
        if (LANGUAGE != 0) {
            b = buttons;
            circle = (b >> 13) & 1;
            cross = (b >> 14) & 1;
            triangle = (b >> 12) & 1;
            buttons &= ~0x7000;
            if (cross) {
                buttons |= 0x2000;
            }
            if (triangle) {
                buttons |= 0x4000;
            }
            if (circle) {
                buttons |= 0x1000;
            }
        }
#endif
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
    slot->repeated = 0;
    for (; i < 16; i++) {
        u8 bit = slot->buttonMap[i];
        s32 *time = &slot->repeatTime[bit];
        u8 *count = &slot->repeatCount[bit];

        if ((buttons >> bit) & 1) {
            if (PAD.repeatRate > 0) {
                if ((GFX.funcs.getTime() - *time + *count) / PAD.repeatRate != 0) {
                    *count += 10;
                    if (*count >= 12) {
                        *count = 12;
                    }
                    *time = GFX.funcs.getTime();
                    slot->repeated |= 1 << slot->buttonMap[i];
                }
            }
        } else {
            *time = GFX.funcs.getTime();
            *count = 0;
        }
    }
    b = slot->held;
    slot->held = buttons;
    slot->prevHeld = b;
    slot->pressed = buttons & (b ^ buttons);
}

s32 readPad(u16 port, u8 *data) {
    u8 id = port;
    s32 mode;

    if (*data != 0 || pollPadState(id & 0xFF) == 0) {
        PAD.slots[(id >> 4) & 1][port & 3].pressed = 0;
        PAD.slots[(id >> 4) & 1][port & 3].repeated = 0;
        PAD.slots[(id >> 4) & 1][port & 3].held = 0;
        return 0;
    }
    mode = PadInfoMode(id & 0xFF, 2, 0);
    if (mode == 4 || mode == 7) {
        updateVibration(id & 0xFF);
    }
    readPadButtons(id & 0xFF, data, 0);
    return 1;
}

s32 setAnalogMode(s32 port, s32 on) {
    u32 id = port & 0xFF;
    s32 mode;
    s32 bit;

    if (pollPadState(id) != 0) {
        mode = PadInfoMode(id, 2, 0);
        if (mode == 4 || mode == 7) {
            bit = ((id >> 4) << 2) | (port & 3);
            if (on != 0) {
                PAD.flags |= 1 << bit;
                PadSetMainMode(id, PadInfoMode(id, 3, 0), 3);
            } else {
                PAD.flags &= ~(1 << bit);
                PadSetMainMode(id, PadInfoMode(id, 3, 0), 2);
            }
            PAD.flags &= 0xF3FFFFFF;
            return 1;
        }
    }
    return 0;
}

s32 alignActuators(u16 port) {
    u32 id = (u8)port;
    s32 count = PadInfoAct(id, -1, 0);
    s32 i;
    s32 act;

    for (i = 0; i < count; i++) {
        act = PadInfoAct(id, i, 2);
        if (act != 0) {
            PAD.act[id >> 4][i] = act & 1;
        }
    }
    return PadSetActAlign(port & 0xFF, PAD.act[(port & 0xFF) >> 4]);
}

void updateVibration(u16 port) {
    u8 id = port;
    s32 i;
    PadSlot *slot = &PAD.slots[id >> 4][port & 3];

    for (i = 0; i < 2; i++) {
        if (slot->vibrationTimers[i] != 0) {
            if ((slot->vibrationTimers[i] -= GFX.funcs.getFrameTime()) <= 0) {
                slot->vibrationTimers[i] = 0;
                PAD.act[id >> 4][i] = 0;
            }
            PadSetAct(port & 0xFF, PAD.act[id >> 4], 2);
        }
    }
}

void seedRandom(s32 arg0) {
    RANDOM.index = arg0 & 0xFFF;
}

u16 random(void) {
    s32 index = (RANDOM.index + 1) & 0xFFF;

    RANDOM.index = index;
    return RANDOM_TABLE[index];
}
