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

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8002019C);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020218);

short func_80020534(s32 index, short prog, short note) {
    return SsUtKeyOn(D_80051194.sounds[index].vabId, prog, 0, note, 0, 0x7F, 0x7F);
}

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020594);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020638);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020764);

void func_80020844(void) {
    func_800144DC(func_80020764, 0x50, 4);
}

INCLUDE_ASM("asm/main/nonmatchings/sound", func_80020870);

INCLUDE_ASM("asm/main/nonmatchings/sound", func_8002091C);

INCLUDE_RODATA("asm/main/nonmatchings/sound", jtbl_800102EC);
