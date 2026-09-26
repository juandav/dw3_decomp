#include "common.h"

typedef struct Fade {
    s32 duration;
    s32 step;
    s32 level;
    s32 active;
} Fade;

extern void (*D_800553F0)(s32);

void func_80010F80(Fade *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn) {
        D_800553F0(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        D_800553F0(0x4001A);
        fade->level = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011014);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011080);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011114);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800119AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011DB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011DF0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011E78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011FBC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80012070);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800120B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001214C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800121B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800123E4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80012698);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800126FC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013434);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013484);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800134C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001350C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001355C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013590);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800135C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001366C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800136CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013758);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013880);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013890);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800138EC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800139D4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013A0C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013A44);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013AB4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013BBC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013C08);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013CB4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013DF8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013E34);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013ED4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013F38);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013FCC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800140B0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800140E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014100);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014148);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800141BC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800141D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800141F4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014210);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001424C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014260);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014270);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001427C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014284);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800142A0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800142B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800142CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800142E0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800143B4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800144DC);

INCLUDE_ASM("asm/main/nonmatchings/game", main);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C4);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014884);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014898);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014A10);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014AAC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014B8C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014C6C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014F2C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800151F0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800153E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015420);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015458);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015490);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015498);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800154CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800154F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001553C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015584);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800155F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015814);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015904);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015940);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015A34);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015A78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015BB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015BEC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015C58);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015CA4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015D90);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015DD8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015E8C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015FC8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001602C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016064);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016260);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800165D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001663C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016694);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016748);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800167DC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001680C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001681C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001682C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001683C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016850);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016860);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016A30);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016A5C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016AC8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016B08);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016BA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016BC8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016C74);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016CC4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016D64);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016E10);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017214);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800172E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017348);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001746C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800175C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800176B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017750);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800177E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001780C);

void func_80017878(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017880);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800178F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001794C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800179A4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800179C8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017A78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017B20);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017B88);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017BF0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017C30);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017C50);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017C78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017CB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017CE8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DDC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017ECC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017F38);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017F64);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017FAC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800180D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800180FC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001816C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800181B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001837C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800184F0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018514);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018538);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001855C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800185C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001861C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018644);

void func_8001864C(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018654);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001868C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018700);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001873C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018774);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018868);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018BC0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018CA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018DC4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018EA0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018FA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018FB8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018FEC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019140);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019164);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019184);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001922C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019308);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019360);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800101D8);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800101FC);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_80010230);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_80010268);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019420);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019C2C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019DFC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019E34);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019E64);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019E70);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019E78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019E80);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019EB8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019ED8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019F28);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A094);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A09C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0D4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0DC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A0F4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A108);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A364);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A3B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A4A8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A530);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A684);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A68C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A7AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A820);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A890);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AAB4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001ACC8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001ACE4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001ACF8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AD08);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AD10);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AD18);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AD20);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AFE0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B0C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B108);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B148);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B1D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B2B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B314);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B368);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B3A0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B434);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B490);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B5AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B6A8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B804);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B864);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BA7C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BB68);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BCCC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C0C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C130);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C168);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C454);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C4D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C5C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C72C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CAC0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CE60);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CEE0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D070);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D114);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D138);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D2EC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D2FC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D30C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D31C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D3CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D44C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D45C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D468);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D4D4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D5E4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D668);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D6B4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D718);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D768);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D7C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D860);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D8E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D984);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D9C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DA4C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DB8C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DBB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DBE0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC00);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC0C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC3C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC48);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC6C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DC94);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DCA0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DCAC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DCFC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DD80);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DDCC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DE24);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DF08);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DF70);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DFE8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E054);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E0D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E140);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E1A0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E3C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E3D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E474);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E51C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E570);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E584);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E598);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E5AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E5B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E5C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E7B0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E7DC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E894);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8A0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8BC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8DC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E918);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E950);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F1B4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F1D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F1EC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F200);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F20C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F22C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F31C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F328);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800102BC);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800102CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F354);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F658);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F8F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F954);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F960);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F974);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F988);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FA70);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FBD4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FBE0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FC68);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FCA4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FE3C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FF0C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FFB4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020064);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020074);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8002019C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020218);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020594);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020638);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020764);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020844);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020870);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8002091C);

INCLUDE_RODATA("asm/main/nonmatchings/game", jtbl_800102EC);
