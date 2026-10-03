#include "common.h"

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A4D90);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A529C);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A52C8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A5538);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A56D4);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A57A8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A5840);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A5878);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A59A0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A5ACC);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A61C8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A62B8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A6654);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A6778);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A69D0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A6AC8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A6E6C);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A6FA0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A70E8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A72E0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7358);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A75F8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7754);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7878);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7950);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7A7C);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7CB8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A7DB0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A83D8);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8494);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8610);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A86E0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8A64);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8B08);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8E40);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8EBC);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A8F60);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A9040);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A9840);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A9960);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A99F0);

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn", func_800A9A40);

void func_800A62B8();
void func_800A6654();
void func_800A6778();
void func_800A69D0();
void func_800A6AC8();
void func_800A6E6C();
void func_800A6FA0();
void func_800A70E8();
void func_800A72E0();
void func_800A7358();
void func_800A75F8();
void func_800A7754();
void func_800A7878();
void func_800A7950();
void func_800A7A7C();
void func_800A7CB8();
void func_800A7DB0();
void func_800A83D8();
void func_800A8494();
void func_800A8610();
void func_800A86E0();
void func_800A8A64();

u16 D_800A9B58[] = {
    0x0000, 0x0000, 0x0140, 0x00F0,
};
#if VERSION_US
s32 D_800A9B60[] = {
    2, 19, 26, 3,
    20, 26, 4, 21,
    27, 5, 22, 50,
    6, 26, 50, 8,
    28, 39, -1, 37,
    49, 27, 39, 49,
    28, 41, 49, -1,
    0, 0,
};
#elif VERSION_EU
s32 D_800A9B60[] = {
    2, 19, 26, 3,
    20, 26, 4, 21,
    27, 5, 22, 50,
    6, 26, 50, 8,
    28, 39, -1, 37,
    49,
};
#endif
s32 D_800A9BD8[] = {
    2, 5, 64, 34,
    3, 9, 45, 37,
    4, 11, 44, 40,
    5, 14, 29, 43,
    6, 16, 44, 46,
    7, 65, 64, 49,
    8, 7, 64, 52,
    -1, 0, 0, 0,
};
s32 D_800A9C58[] = {
    0, 0, 0, (s32)func_800A62B8,
    (s32)func_800A6654, (s32)func_800A6778, (s32)func_800A69D0, (s32)func_800A6AC8,
    (s32)func_800A6E6C, (s32)func_800A6FA0, (s32)func_800A70E8, (s32)func_800A72E0,
    (s32)func_800A7358, (s32)func_800A75F8, (s32)func_800A75F8, (s32)func_800A75F8,
    (s32)func_800A7754, (s32)func_800A7878, (s32)func_800A7950, (s32)func_800A7A7C,
    (s32)func_800A7CB8, (s32)func_800A7DB0, (s32)func_800A83D8, (s32)func_800A8494,
    (s32)func_800A8610, (s32)func_800A86E0, (s32)func_800A8A64,
};
s32 D_800A9CC4[] = {
    19, 26, 20, 26,
    21, 27, 22, 50,
    26, 50, 0, 0,
    28, 39, 0, 0,
    46, 30, 0, 59,
    31, 58,
};
