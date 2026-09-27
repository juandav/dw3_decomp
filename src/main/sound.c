#include "game.h"

s32 func_8001FC68(s32 id) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_80051194.sounds[i].unk0 == id) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8001FCA4);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8001FE3C);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8001FF0C);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8001FFB4);

s32 func_80020064(void) {
    return D_800553DC.unkC != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020074);

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

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020638);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020764);

void func_80020844(void) {
    func_800144DC(func_80020764, 0x50, 4);
}

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020870);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8002091C);

INCLUDE_RODATA("asm/main/nonmatchings/sound", jtbl_800102EC);
