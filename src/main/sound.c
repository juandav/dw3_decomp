#include "game.h"
#include "libsnd.h"

/* The sound buffers are read through fixed addresses (0x800100C4/0x800100C8 in
 * game.c's rodata); a symbol reference would be compiled differently. */
#define FIXED_PTR(addr) (*(void **)(addr))

extern s32 D_80055474[];

s32 func_8001FC68(s32 id) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_80051194.sounds[i].unk0 == id) {
            return i;
        }
    }
    return -1;
}

s32 func_8001FCA4(s32 packed) {
    s32 id = (packed >> 18) & 0x7F;
    u32 keyOn = (u32)packed >> 31;
    s32 exclusive = (packed >> 30) & 1;
    s32 prog = (packed >> 11) & 0x7F;
    s32 tone = (packed >> 7) & 0xF;
    s32 note = packed & 0x7F;
    s32 seq = (packed >> 8) & 0xFF;
    s32 sep = packed & 0xFF;
    s32 index = func_8001FC68(id);
    s32 voice = -1;

    if (index != -1) {
        if (index != 0) {
            D_800553DC.unk4 = index;
        }
        if (exclusive) {
            if (D_80051194.unk4248 == packed) {
                return 0;
            }
            if (D_80051194.unk4248 != 0) {
                D_80051194.unk427C(D_80051194.unk4248);
            }
            D_80051194.unk4248 = packed;
        }
        if (keyOn) {
            voice = SsUtKeyOn(D_80051194.sounds[index].vabId, prog, tone, note, 0, 0x7F, 0x7F);
        } else {
            id = sep;
            SsSepStop(D_80051194.sounds[index].seqs[seq], id);
            SsSepSetVol(D_80051194.sounds[index].seqs[seq], id, 0x7F, 0x7F);
            SsSepPlay(D_80051194.sounds[index].seqs[seq], id, 1, 1);
        }
        return voice;
    }
    return 0;
}

void func_8001FE3C(void) {
    s32 i;
    s32 j;
    s32 k;
    SoundEntry *e;

    for (i = 0; i < 3; i++) {
        e = &D_80051194.sounds[i];
        if (e->vabId != -1) {
            for (j = 0; j < e->numSeqs; j++) {
                for (k = 0; k < 16; k++) {
                    SsSepStop(e->seqs[j], k);
                }
            }
        }
    }
    SsUtAllKeyOff(0);
    D_800553DC.unk0 = 0;
}

void func_8001FF0C(s32 packed) {
    s32 id = (packed >> 18) & 0x7F;
    u32 stopped = (u32)packed >> 31;
    s32 seq = (packed >> 8) & 0xFF;
    s32 sep = packed & 0xFF;
    s32 index = func_8001FC68(id);

    if (index != -1 && !stopped) {
        SsSepStop(D_80051194.sounds[index].seqs[seq], sep);
        if (D_80051194.unk4248 == packed) {
            D_80051194.unk4248 = 0;
        }
    }
}

void func_8001FFB4(s32 packed) {
    s32 id = (packed >> 18) & 0x7F;
    u32 stopped = (u32)packed >> 31;
    s32 seq = (packed >> 8) & 0xFF;
    s32 sep = packed & 0xFF;
    s32 index = func_8001FC68(id);

    if (index != -1 && !stopped) {
        SsSepSetDecrescendo(D_80051194.sounds[index].seqs[seq], sep, 0x80, 0x3C);
        if (D_80051194.unk4248 == packed) {
            D_80051194.unk4248 = 0;
        }
    }
}

s32 func_80020064(void) {
    return D_800553DC.unkC != 0;
}

void func_80020074(s32 index, s32 id) {
    SoundEntry *e = &D_80051194.sounds[index];
    SoundBank *bank = &D_80051194.bank;
    s32 i;
    s32 j;

    e->unk0 = id;
    if (e->vabId != -1) {
        for (i = 0; i < e->numSeqs; i++) {
            for (j = 0; j < 16; j++) {
                SsSepStop(e->seqs[i], j);
            }
            func_80030198(e->seqs[i]);
        }
        SsVabClose(e->vabId);
        e->vabId = -1;
    }
    bank->loading = 1;
    bank->data = D_8005105C[id];
    bank->index = index;
    D_80044B50(bank->data[1]);
}

void func_8002019C(s32 id) {
    if (D_80051194.sounds[1].unk0 != id && D_80051194.sounds[2].unk0 != id) {
        if (D_80051194.unk424C == 1) {
            func_80020074(2, id);
            D_80051194.unk424C = 2;
        } else {
            func_80020074(1, id);
            D_80051194.unk424C = 1;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020218);

short func_80020534(s32 index, short prog, short note) {
    return SsUtKeyOn(D_80051194.sounds[index].vabId, prog, 0, note, 0, 0x7F, 0x7F);
}

void func_80020594(s32 packed, s16 voice) {
    s32 id = (packed >> 18) & 0x7F;
    s32 prog = (packed >> 11) & 0x7F;
    s32 tone = (packed >> 7) & 0xF;
    s32 note = packed & 0x7F;
    s32 index = func_8001FC68(id);

    if (voice != -1 && index != -1) {
        SsUtKeyOff(voice, D_80051194.sounds[index].vabId, prog, tone, note);
    }
}

void func_80020638(void) {
    s32 i;

    SsSetTableSize(D_80051194.unk0, 6, 16);
    SsSetTickMode(0x1000);
    SsStart2();
    SsSetMVol(0x7F, 0x7F);
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7F, 0x7F);
    SsUtSetReverbType(3);
    SsUtSetReverbDepth(0, 0);
    func_800345B8();
    for (i = 0; i < 3; i++) {
        D_80051194.sounds[i].vabId = -1;
        D_80051194.sounds[i].numSeqs = 0;
        D_80051194.sounds[i].unk10 = D_8005117C[i];
        D_80051194.sounds[i].unk14 = D_80051188[i];
    }
    D_80051194.bank.index = 0;
    D_80051194.bank.loading = 0;
    D_80051194.bank.data = NULL;
    func_80020074(0, 1);
    while (func_80020064() != 0) {
        D_80044744.unk410();
        func_80020218();
    }
}

void func_80020764(Task80011FBC *task, s32 *out) {
    switch (task->state) {
    case 0:
    default:
        D_800554D8.unk0();
        *out = D_80055418[D_8004ABD8.unk8() >> 8]();
        task->unk38(task);
        break;
    case 1:
        if (D_8004ABD8.unk14() != 0) {
            task->unk28(task, 3);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void func_80020844(void) {
    func_800144DC(func_80020764, 0x50, 4);
}

void func_80020870(void) {
    s32 id = D_8004ABD8.unk8() >> 8;
    u8 *src;
    void *dst;

    if (D_800554D0.unk0 != id) {
        D_800554D0.unk0 = id;
        D_800554D0.current = -1;
        src = D_80044B58(D_80055474[id]);
        dst = FIXED_PTR(0x800100C4);
        memcpy(dst, src, D_80047F04.getFileSectors(D_80055474[id]) << 11);
    }
}

void func_8002091C(s32 id) {
    u8 *src;
    void *dst;

    if (D_800554D0.current != id) {
        D_800554D0.current = id;
        src = D_80044B58(id);
        dst = FIXED_PTR(0x800100C8);
        memcpy(dst, src, D_80047F04.getFileSectors(id) << 11);
    }
}

INCLUDE_RODATA("asm/main/nonmatchings/sound", jtbl_800102EC);
