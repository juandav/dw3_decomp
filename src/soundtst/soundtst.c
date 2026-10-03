#include "soundtst.h"

extern char SOUNDTST_STR_SELECT_VAB[]; /* "－てんそうするＶＡＢをせんたくしてください－" */
extern char SOUNDTST_STR_SOUND_TEST[]; /* "サウンドテスト" */
extern char SOUNDTST_STR_CURSOR[]; /* "＞" */
extern char SOUNDTST_entryNames[]; /* the lists' texts */

/* A text in SOUNDTST_entryNames */
#define NAME(offset) (SOUNDTST_entryNames + (offset))

/* Each bank's sound list, then the bank list */
SoundTestEntry D_8008450C[] = {
    {NAME(0x8C4), 0xA004E03C}, /* "ＢＴ＿ＬＯＯＰ０" */
    {NAME(0x8B0), 0xA004E0BD}, /* "ＢＴ＿ＬＯＯＰ１" */
    {NAME(0x89C), 0xA004E13E}, /* "ＢＴ＿ＬＯＯＰ２" */
    {NAME(0x888), 0xA004E1BF}, /* "ＢＴ＿ＬＯＯＰ３" */
    {NAME(0x874), 0xA004E240}, /* "ＢＴ＿ＬＯＯＰ４" */
    {NAME(0x860), 0xA004E2C1}, /* "ＢＴ＿ＬＯＯＰ５" */
    {NAME(0x84C), 0xA004E342}, /* "ＢＴ＿ＬＯＯＰ６" */
    {NAME(0x838), 0xA004E3C3}, /* "ＢＴ＿ＬＯＯＰ７" */
    {NAME(0x824), 0x8004603C}, /* "ＣＡＲＤ＿０００" */
    {NAME(0x810), 0x800460BD}, /* "ＣＡＲＤ＿００１" */
    {NAME(0x7FC), 0x8004613E}, /* "ＣＡＲＤ＿００２" */
    {NAME(0x7E8), 0x60040000}, /* "ＣＯＭ＿ＣＮＦＳ" */
    {NAME(0x7D4), 0x8004213E}, /* "ＣＯＭＡＴ１０２" */
    {NAME(0x7C0), 0x800421BF}, /* "ＣＯＭＡＴ１０３" */
    {NAME(0x7AC), 0xA0042240}, /* "ＣＯＭＡＴ１０４" */
    {NAME(0x798), 0x80042342}, /* "ＣＯＭＡＴ１０６" */
    {NAME(0x784), 0x80042444}, /* "ＣＯＭＡＴ１０８" */
    {NAME(0x770), 0x8004293E}, /* "ＣＯＭＣＤ１０２" */
    {NAME(0x75C), 0x800429BF}, /* "ＣＯＭＣＤ１０３" */
    {NAME(0x748), 0x80042A40}, /* "ＣＯＭＣＤ１０４" */
    {NAME(0x734), 0x40001}, /* "ＣＯＭＣＤ１０５" */
    {NAME(0x720), 0x80042B42}, /* "ＣＯＭＣＤ１０６" */
    {NAME(0x70C), 0x80042C44}, /* "ＣＯＭＣＤ１０８" */
    {NAME(0x6F8), 0x80042CC5}, /* "ＣＯＭＣＤ１０９" */
    {NAME(0x6E4), 0x80042D46}, /* "ＣＯＭＣＤ１１０" */
    {NAME(0x6D0), 0x80042DC7}, /* "ＣＯＭＣＤ１１１" */
    {NAME(0x6BC), 0x80042E48}, /* "ＣＯＭＣＤ１１２" */
    {NAME(0x6A8), 0xA0042F4A}, /* "ＣＯＭＣＤ１１４" */
    {NAME(0x694), 0xA0042FCB}, /* "ＣＯＭＣＤ１１５" */
    {NAME(0x680), 0xA004303C}, /* "ＣＯＭＣＤ２００" */
    {NAME(0x66C), 0x800430BD}, /* "ＣＯＭＣＤ２０１" */
    {NAME(0x658), 0x8004313E}, /* "ＣＯＭＣＤ２０２" */
    {NAME(0x644), 0xA00431BF}, /* "ＣＯＭＣＤ２０３" */
    {NAME(0x630), 0xA0043240}, /* "ＣＯＭＣＤ２０４" */
    {NAME(0x61C), 0x800432C1}, /* "ＣＯＭＣＤ２０５" */
    {NAME(0x608), 0x80043342}, /* "ＣＯＭＣＤ２０６" */
    {NAME(0x5F4), 0x800433C3}, /* "ＣＯＭＣＤ２０７" */
    {NAME(0x5E0), 0x800434C5}, /* "ＣＯＭＣＤ２０９" */
    {NAME(0x5CC), 0x80043546}, /* "ＣＯＭＣＤ２１０" */
    {NAME(0x5B8), 0xA00435C7}, /* "ＣＯＭＣＤ２１１" */
    {NAME(0x5A4), 0x80043648}, /* "ＣＯＭＣＤ２１２" */
    {NAME(0x590), 0x8004374A}, /* "ＣＯＭＣＤ２１４" */
    {NAME(0x57C), 0x800437CB}, /* "ＣＯＭＣＤ２１５" */
    {NAME(0x568), 0x8004383C}, /* "ＣＯＭＣＤ３００" */
    {NAME(0x554), 0x80043A40}, /* "ＣＯＭＣＤ３０４" */
    {NAME(0x540), 0xA0043BC3}, /* "ＣＯＭＣＤ３０７" */
    {NAME(0x52C), 0xA0043C44}, /* "ＣＯＭＣＤ３０８" */
    {NAME(0x518), 0x800440BD}, /* "ＣＯＭＥＸ１０１" */
    {NAME(0x504), 0x8004413E}, /* "ＣＯＭＥＸ１０２" */
    {NAME(0x4F0), 0x800441BF}, /* "ＣＯＭＥＸ１０３" */
    {NAME(0x4DC), 0x80044240}, /* "ＣＯＭＥＸ１０４" */
    {NAME(0x4C8), 0x800442C1}, /* "ＣＯＭＥＸ１０５" */
    {NAME(0x4B4), 0x80044444}, /* "ＣＯＭＥＸ１０８" */
    {NAME(0x4A0), 0x800445C7}, /* "ＣＯＭＥＸ１１１" */
    {NAME(0x48C), 0x80044648}, /* "ＣＯＭＥＸ１１２" */
    {NAME(0x478), 0x800446C9}, /* "ＣＯＭＥＸ１１３" */
    {NAME(0x464), 0x8004474A}, /* "ＣＯＭＥＸ１１４" */
    {NAME(0x450), 0x8004483C}, /* "ＣＯＭＥＸ２００" */
    {NAME(0x43C), 0x60040002}, /* "ＤＥＭＯ＿ＢＧＭ" */
    {NAME(0x428), 0x40003}, /* "ＤＩＧ＿ＤＥＭＯ" */
    {NAME(0x414), 0x80045FCB}, /* "ＤＩＧ＿ＭＯＶＥ" */
    {NAME(0x400), 0x40004}, /* "ＤＩＧＩＭＥＮＴ" */
    {NAME(0x3EC), 0x80045E48}, /* "ＤＩＧＭ＿ＤＩＧ" */
    {NAME(0x3D8), 0x40005}, /* "ＥＮＣＯＵＮＴＳ" */
    {NAME(0x3C4), 0x20040006}, /* "ＥＸ＿ＡＴ＿ＬＰ" */
    {NAME(0x3B0), 0x40007}, /* "ＦＵＫＩＤＡＳＨ" */
    {NAME(0x39C), 0x60040008}, /* "ＧＡＭＥＯＶＥＲ" */
    {NAME(0x388), 0x40009}, /* "ＩＴＥＭ＿ＧＥＴ" */
    {NAME(0x374), 0x4000A}, /* "ＪＩＮＧＬＥ０１" */
    {NAME(0x360), 0x4000B}, /* "ＪＩＮＧＬＥ０２" */
    {NAME(0x34C), 0x4000C}, /* "ＪＩＮＧＬＥ０３" */
    {NAME(0x338), 0x4004000D}, /* "ＪＩＮＧＬＥ０４" */
    {NAME(0x324), 0x4000E}, /* "ＬＲＧ＿ＤＯＷＮ" */
    {NAME(0x310), 0x4000F}, /* "ＬＲＧ＿ＳＴＥＰ" */
    {NAME(0x2FC), 0x40010}, /* "ＭＩＤ＿ＤＯＷＮ" */
    {NAME(0x2E8), 0x40011}, /* "ＭＩＤ＿ＳＴＥＰ" */
    {NAME(0x2D4), 0x40012}, /* "ＭＴＬ＿ＤＯＷＮ" */
    {NAME(0x2C0), 0x40013}, /* "ＰＩＹＯＰＩＹＯ" */
    {NAME(0x2AC), 0x8004583C}, /* "ＰＬＡＹＥＲ００" */
    {NAME(0x298), 0x800458BD}, /* "ＰＬＡＹＥＲ０１" */
    {NAME(0x284), 0x8004593E}, /* "ＰＬＡＹＥＲ０２" */
    {NAME(0x270), 0x800459BF}, /* "ＰＬＡＹＥＲ０３" */
    {NAME(0x25C), 0x80045A40}, /* "ＰＬＡＹＥＲ０４" */
    {NAME(0x248), 0x80045AC1}, /* "ＰＬＡＹＥＲ０５" */
    {NAME(0x234), 0x80045B42}, /* "ＰＬＡＹＥＲ０６" */
    {NAME(0x220), 0x80045BC3}, /* "ＰＬＡＹＥＲ０７" */
    {NAME(0x20C), 0x80045C44}, /* "ＰＬＡＹＥＲ０８" */
    {NAME(0x1F8), 0x80045CC5}, /* "ＰＬＡＹＥＲ０９" */
    {NAME(0x1E4), 0x80045D46}, /* "ＰＬＡＹＥＲ１０" */
    {NAME(0x1D0), 0xA0045EC9}, /* "ＰＬＡＹＥＲ１１" */
    {NAME(0x1BC), 0x40014}, /* "ＲＥＣＯＶＥＲＹ" */
    {NAME(0x1A8), 0x40015}, /* "ＳＡＶＥＤＥＭＯ" */
    {NAME(0x194), 0x40016}, /* "ＳＨＴ＿ＤＯＷＮ" */
    {NAME(0x180), 0x40017}, /* "ＳＨＴ＿ＳＴＥＰ" */
    {NAME(0x16C), 0x40018}, /* "ＳＵＢ＿ＤＥＭＯ" */
    {NAME(0x158), 0xA0045F4A}, /* "ＳＵＢ＿ＭＯＶＥ" */
    {NAME(0x144), 0x8004103C}, /* "ＳＷＩＴＣＨ０１" */
    {NAME(0x130), 0x800410BD}, /* "ＳＷＩＴＣＨ０２" */
    {NAME(0x11C), 0x8004113E}, /* "ＳＷＩＴＣＨ０３" */
    {NAME(0x108), 0x8004503C}, /* "ＳＹＳＴＥＭ００" */
    {NAME(0xF4), 0x800450BD}, /* "ＳＹＳＴＥＭ０１" */
    {NAME(0xE0), 0x8004513E}, /* "ＳＹＳＴＥＭ０２" */
    {NAME(0xCC), 0x40019}, /* "ＳＹＳＴＥＭ０３" */
    {NAME(0xB8), 0x4001A}, /* "ＳＹＳＴＥＭ０４" */
    {NAME(0xA4), 0x80045341}, /* "ＳＹＳＴＥＭ０５" */
    {NAME(0x90), 0x4001B}, /* "ＳＹＳＴＥＭ０６" */
    {NAME(0x7C), 0x4001C}, /* "ＳＹＳＴＥＭ０７" */
    {NAME(0x68), 0x800454C4}, /* "ＳＹＳＴＥＭ０８" */
    {NAME(0x54), 0x800452C6}, /* "ＳＹＳＴＥＭ１０" */
    {NAME(0x40), 0x4001D}, /* "ＴＥＬＥＰＯＲＴ" */
    {NAME(0x2C), 0x80045DC7}, /* "ＴＲＥＳＵＲＥＢ" */
    {NAME(0x18), 0x6004001E}, /* "Ｗ＿ＪＩＮＧＬＥ" */
    {NAME(0x4), 0x4001F}, /* "ＷＮＧ＿ＳＴＥＰ" */
    {NAME(0), 0},
};

SoundTestEntry D_8008489C[] = {
    {NAME(0x8D8), 0x60080000}, /* "ＢＡＴＬ００００" */
    {NAME(0), 0},
};

SoundTestEntry D_800848AC[] = {
    {NAME(0x8EC), 0x600C0000}, /* "ＢＡＴＬ１０００" */
    {NAME(0), 0},
};

SoundTestEntry D_800848BC[] = {
    {NAME(0x900), 0x60100000}, /* "ＡＳＫＡ＿ＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_800848CC[] = {
    {NAME(0x914), 0x60140000}, /* "ＫＡＮＲＩＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_800848DC[] = {
    {NAME(0x928), 0x60180000}, /* "ＢＧＭ＿０００３" */
    {NAME(0), 0},
};

SoundTestEntry D_800848EC[] = {
    {NAME(0x93C), 0x601C0000}, /* "ＳＨＯＰ１ＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_800848FC[] = {
    {NAME(0x950), 0x60200000}, /* "ＳＨＯＰ２ＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_8008490C[] = {
    {NAME(0x964), 0x60240000}, /* "ＦＩＥＬＤＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_8008491C[] = {
    {NAME(0x978), 0x60280000}, /* "ＢＧＭ＿０００８" */
    {NAME(0), 0},
};

SoundTestEntry D_8008492C[] = {
    {NAME(0x98C), 0x602C0000}, /* "ＰＹＲＡ＿ＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_8008493C[] = {
    {NAME(0x9A0), 0x60300000}, /* "ＳＥＩＲ＿ＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_8008494C[] = {
    {NAME(0xA04), 0x60340000}, /* "ＢＧＭ＿００１１" */
    {NAME(0x9F0), 0x340001}, /* "ＢＵＬＢ＿０００" */
    {NAME(0x9DC), 0x340002}, /* "ＢＵＬＢ＿００１" */
    {NAME(0x9C8), 0x340003}, /* "ＧＯＮＤＲＡ＿Ｂ" */
    {NAME(0x9B4), 0x340004}, /* "ＧＯＮＤＲＡ＿Ｓ" */
    {NAME(0), 0},
};

SoundTestEntry D_8008497C[] = {
    {NAME(0xA18), 0x60380000}, /* "ＢＧＭ＿００１２" */
    {NAME(0), 0},
};

SoundTestEntry D_8008498C[] = {
    {NAME(0xA40), 0x603C0000}, /* "ＢＧＭ＿００１３" */
    {NAME(0xA2C), 0x803C503C}, /* "ＭＡＳＫ＿ＳＥＴ" */
    {NAME(0), 0},
};

SoundTestEntry D_800849A4[] = {
    {NAME(0xA54), 0x60400000}, /* "ＢＧＭ＿００１４" */
    {NAME(0), 0},
};

SoundTestEntry D_800849B4[] = {
    {NAME(0xA90), 0x60440000}, /* "ＢＧＭ＿００１５" */
    {NAME(0xA7C), 0x440001}, /* "ＢＵＬＢ＿００３" */
    {NAME(0xA68), 0x440002}, /* "ＢＵＬＢ＿００４" */
    {NAME(0), 0},
};

SoundTestEntry D_800849D4[] = {
    {NAME(0xAA4), 0x60480000}, /* "ＢＧＭ＿００１６" */
    {NAME(0), 0},
};

SoundTestEntry D_800849E4[] = {
    {NAME(0xAE0), 0x604C0000}, /* "ＢＧＭ＿００１７" */
    {NAME(0xACC), 0x4C0001}, /* "ＢＵＬＢ＿００２" */
    {NAME(0xAB8), 0x4C0002}, /* "ＦＬＯＯＲ＿ＬＴ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A04[] = {
    {NAME(0xAF4), 0x60500000}, /* "ＢＧＭ＿００１８" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A14[] = {
    {NAME(0xB44), 0xA054583C}, /* "ＢＥＡＭ＿ＨＩＴ" */
    {NAME(0xB30), 0x805458BD}, /* "ＢＥＡＭ＿ＳＨＴ" */
    {NAME(0xB1C), 0x60540000}, /* "ＢＧＭ＿００１９" */
    {NAME(0xB08), 0x540001}, /* "ＤＩＧＩＴＡＭＡ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A3C[] = {
    {NAME(0xB58), 0x60580000}, /* "ＢＧＭ＿００２０" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A4C[] = {
    {NAME(0xB6C), 0x605C0000}, /* "ＢＧＭ＿００２１" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A5C[] = {
    {NAME(0xB80), 0x60600000}, /* "ＢＧＭ＿００２２" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A6C[] = {
    {NAME(0xBBC), 0x60640000}, /* "ＢＧＭ＿００２３" */
    {NAME(0xBA8), 0xA064683C}, /* "ＴＲＡＰ＿ＩＣＥ" */
    {NAME(0xB94), 0x8064703C}, /* "ＴＲＡＰ＿ＬＧＴ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A8C[] = {
    {NAME(0xBD0), 0x60680000}, /* "ＢＧＭ＿００２４" */
    {NAME(0), 0},
};

SoundTestEntry D_80084A9C[] = {
    {NAME(0xBE4), 0x606C0000}, /* "ＯＮ＿ＣＮＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084AAC[] = {
    {NAME(0xC0C), 0x60700000}, /* "ＢＧＭ＿００２６" */
    {NAME(0xBF8), 0x700001}, /* "ＴＲＡＰ＿ＯＦＦ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084AC4[] = {
    {NAME(0xC20), 0x60740000}, /* "ＢＧＭ＿００２７" */
    {NAME(0), 0},
};

SoundTestEntry D_80084AD4[] = {
    {NAME(0xC34), 0x60780000}, /* "ＢＧＭ＿００２８" */
    {NAME(0), 0},
};

SoundTestEntry D_80084AE4[] = {
    {NAME(0xC48), 0x607C0000}, /* "ＢＧＭ＿００２９" */
    {NAME(0), 0},
};

SoundTestEntry D_80084AF4[] = {
    {NAME(0xC5C), 0x60800000}, /* "ＢＧＭ＿００３０" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B04[] = {
    {NAME(0xCAC), 0xA084603C}, /* "ＴＲＡＩＮ＿ＣＨ" */
    {NAME(0xC98), 0x840000}, /* "ＴＲＡＩＮ＿ＮＧ" */
    {NAME(0xC84), 0x840001}, /* "ＴＲＡＩＮ＿ＯＫ" */
    {NAME(0xC70), 0x60840002}, /* "ＴＲＡＩＮＩＮＧ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B2C[] = {
    {NAME(0xCC0), 0x60880000}, /* "ＢＯＳＳ＿０００" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B3C[] = {
    {NAME(0xCD4), 0x608C0000}, /* "ＢＯＳＳ＿００１" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B4C[] = {
    {NAME(0xCE8), 0x60900000}, /* "ＬＡＳＴＢＯＳＳ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B5C[] = {
    {NAME(0xCFC), 0x60940000}, /* "ＬＡＳＴＢ＿０１" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B6C[] = {
    {NAME(0xD10), 0x60980000}, /* "ＬＡＳＴＢ＿０２" */
    {NAME(0), 0},
};

SoundTestEntry D_80084B7C[] = {
    {NAME(0xD74), 0x9C0000}, /* "ＣＡＲＤＤＭＧＥ" */
    {NAME(0xD60), 0x9C0001}, /* "ＣＡＲＤＦＩＲＥ" */
    {NAME(0xD4C), 0x9C0002}, /* "ＣＡＲＤＳＧＮＬ" */
    {NAME(0xD38), 0x9C0003}, /* "ＣＡＲＤＴＨＮＤ" */
    {NAME(0xD24), 0x609C0004}, /* "ＣＢＴＬＭＡＩＮ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084BAC[] = {
    {NAME(0xD88), 0x60A00000}, /* "ＣＯＮＦＵＳＩＯ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084BBC[] = {
    {NAME(0xE28), 0x60A40000}, /* "ＢＧＭ０００００" */
    {NAME(0xE14), 0x60A40001}, /* "ＢＧＭ００００１" */
    {NAME(0xE00), 0x60A40002}, /* "ＢＧＭ００００２" */
    {NAME(0xDEC), 0x60A40003}, /* "ＢＧＭ００００３" */
    {NAME(0xDD8), 0x80A4203C}, /* "ＤＯＯＲＯＰＥＮ" */
    {NAME(0xDC4), 0xA40004}, /* "ＳＥ００００００" */
    {NAME(0xDB0), 0xA40005}, /* "ＳＥ０００００１" */
    {NAME(0xD9C), 0xA40006}, /* "ＳＥ０００００２" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C04[] = {
    {NAME(0xE3C), 0x60A80000}, /* "ＥＮＶ＿０００２" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C14[] = {
    {NAME(0xE50), 0x60AC0000}, /* "ＥＮＶ＿０００３" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C24[] = {
    {NAME(0xE64), 0x60B00000}, /* "ＥＮＶ＿０００４" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C34[] = {
    {NAME(0xE78), 0x60B40000}, /* "ＥＮＶ０５＿００" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C44[] = {
    {NAME(0xEA0), 0x60B80000}, /* "ＥＮＶ＿０００６" */
    {NAME(0xE8C), 0xB80001}, /* "ＩＮＦＯ＿ＳＩＧ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C5C[] = {
    {NAME(0xEB4), 0x60BC0000}, /* "ＥＮＶ＿０００７" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C6C[] = {
    {NAME(0xEC8), 0x60C00000}, /* "ＥＮＶ＿０００８" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C7C[] = {
    {NAME(0xEDC), 0x60C40000}, /* "ＥＮＶ＿０００９" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C8C[] = {
    {NAME(0xEF0), 0x60C80000}, /* "ＥＮＶ１０＿００" */
    {NAME(0), 0},
};

SoundTestEntry D_80084C9C[] = {
    {NAME(0xF14), 0x60CC0000}, /* "ＥＮＶ＿００１１" */
    {NAME(0xF04), 0xCC0001}, /* "ＬＯＧＩＮＥＦ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084CB4[] = {
    {NAME(0xF28), 0x60D00000}, /* "ＥＮＶ＿００１２" */
    {NAME(0), 0},
};

SoundTestEntry D_80084CC4[] = {
    {NAME(0xF3C), 0x60D40000}, /* "ＥＮＶ＿００１３" */
    {NAME(0), 0},
};

SoundTestEntry D_80084CD4[] = {
    {NAME(0xF50), 0x60D80000}, /* "ＥＮＶ＿００１４" */
    {NAME(0), 0},
};

SoundTestEntry D_80084CE4[] = {
    {NAME(0xF64), 0x60DC0000}, /* "ＥＮＶ＿００１５" */
    {NAME(0), 0},
};

SoundTestEntry D_80084CF4[] = {
    {NAME(0xF78), 0x60E00000}, /* "ＥＮＶ＿００１６" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D04[] = {
    {NAME(0xF8C), 0x60E40000}, /* "ＥＮＶ＿００１７" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D14[] = {
    {NAME(0xFB4), 0x60E80000}, /* "ＥＮＶ＿００１８" */
    {NAME(0xFA0), 0x80E8383C}, /* "ＷＥＡＲ＿ＯＦＦ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D2C[] = {
    {NAME(0xFDC), 0x60EC0000}, /* "ＥＮＶ＿００１９" */
    {NAME(0xFC8), 0xEC0001}, /* "ＦＬＯＯＲ＿ＤＮ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D44[] = {
    {NAME(0xFF0), 0x60F00000}, /* "ＥＮＶ＿００２０" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D54[] = {
    {NAME(0x1004), 0x60F40000}, /* "ＥＮＶ＿００２１" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D64[] = {
    {NAME(0x1018), 0x60F80000}, /* "ＥＮＶ＿００２２" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D74[] = {
    {NAME(0x102C), 0x60FC0000}, /* "ＥＮＶ＿００２３" */
    {NAME(0), 0},
};

SoundTestEntry D_80084D84[] = {
    {NAME(0x1090), 0x8100383C}, /* "ＣＣＯＭＢＩＮＥ" */
    {NAME(0x107C), 0x8100303C}, /* "ＤＯＯＲＣＬＳＥ" */
    {NAME(0x1068), 0x1000000}, /* "ＥＮＴＲＹ＿０２" */
    {NAME(0x1054), 0x61000001}, /* "ＥＮＶ＿００２４" */
    {NAME(0x1040), 0x1000002}, /* "ＳＩＧＮＡＬＯＮ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084DB4[] = {
    {NAME(0x10A4), 0x61040000}, /* "ＥＮＶ＿００２５" */
    {NAME(0), 0},
};

SoundTestEntry D_80084DC4[] = {
    {NAME(0x10E0), 0x61080000}, /* "ＥＡＵＣＴＩＯＮ" */
    {NAME(0x10CC), 0x1080001}, /* "ＥＬＥＶＡＴＥＲ" */
    {NAME(0x10B8), 0x61080002}, /* "ＥＮＶ＿０２０４" */
    {NAME(0), 0},
};

SoundTestEntry D_80084DE4[] = {
    {NAME(0x1144), 0x10C0000}, /* "ＤＩＧＩ＿ＥＮ０" */
    {NAME(0x1130), 0x10C0001}, /* "ＤＩＧＩ＿ＥＮ１" */
    {NAME(0x111C), 0x10C0002}, /* "ＤＩＧＩ＿ＥＮ２" */
    {NAME(0x1108), 0x610C0003}, /* "ＥＮＶ＿０２０５" */
    {NAME(0x10F4), 0xA10C703C}, /* "ＧＡＹＡＬＯＯＰ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084E14[] = {
    {NAME(0x11BC), 0x1100000}, /* "ＢＭ＿ＥＲＡＳＥ" */
    {NAME(0x11A8), 0x61100001}, /* "ＥＮＶ＿０２０６" */
    {NAME(0x1194), 0x1100002}, /* "ＬＤ＿ＥＲＡＳＥ" */
    {NAME(0x1180), 0x811031BF}, /* "ＬＤ＿ＶＡＣＵＭ" */
    {NAME(0x116C), 0x8110303C}, /* "ＳＮ＿ＥＮＴＲＹ" */
    {NAME(0x1158), 0x81103240}, /* "ＳＮ＿ＥＲＡＳＥ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084E4C[] = {
    {NAME(0x11D0), 0x41140000}, /* "ＥＶＯＬＵＴＩＯ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084E5C[] = {
    {NAME(0x11E4), 0x41180000}, /* "ＪＯＧＲＥＳＳＥ" */
    {NAME(0), 0},
};

SoundTestEntry D_80084E6C[] = {
    {NAME(0x11F8), 0x611C0000}, /* "ＴＩＴＬＥＢＧＭ" */
    {NAME(0), 0},
};

SoundTestEntry *SOUNDTST_soundLists[] = {
    D_8008450C, D_8008489C, D_800848AC, D_800848BC, D_800848CC, D_800848DC,
    D_800848EC, D_800848FC, D_8008490C, D_8008491C, D_8008492C, D_8008493C,
    D_8008494C, D_8008497C, D_8008498C, D_800849A4, D_800849B4, D_800849D4,
    D_800849E4, D_80084A04, D_80084A14, D_80084A3C, D_80084A4C, D_80084A5C,
    D_80084A6C, D_80084A8C, D_80084A9C, D_80084AAC, D_80084AC4, D_80084AD4,
    D_80084AE4, D_80084AF4, D_80084B04, D_80084B2C, D_80084B3C, D_80084B4C,
    D_80084B5C, D_80084B6C, D_80084B7C, D_80084BAC, D_80084BBC, D_80084C04,
    D_80084C14, D_80084C24, D_80084C34, D_80084C44, D_80084C5C, D_80084C6C,
    D_80084C7C, D_80084C8C, D_80084C9C, D_80084CB4, D_80084CC4, D_80084CD4,
    D_80084CE4, D_80084CF4, D_80084D04, D_80084D14, D_80084D2C, D_80084D44,
    D_80084D54, D_80084D64, D_80084D74, D_80084D84, D_80084DB4, D_80084DC4,
    D_80084DE4, D_80084E14, D_80084E4C, D_80084E5C, D_80084E6C,
};

SoundTestEntry SOUNDTST_banks[] = {
    {NAME(0x166C), 1}, /* "ＣＯＭＭＯＮ" */
    {NAME(0x165C), 2}, /* "ＢＡＴＬ００" */
    {NAME(0x164C), 3}, /* "ＢＡＴＬ１０" */
    {NAME(0x163C), 4}, /* "ＢＧＭ００１" */
    {NAME(0x162C), 5}, /* "ＢＧＭ００２" */
    {NAME(0x161C), 6}, /* "ＢＧＭ００３" */
    {NAME(0x160C), 7}, /* "ＢＧＭ００４" */
    {NAME(0x15FC), 8}, /* "ＢＧＭ００５" */
    {NAME(0x15EC), 9}, /* "ＢＧＭ００７" */
    {NAME(0x15DC), 0xA}, /* "ＢＧＭ００８" */
    {NAME(0x15CC), 0xB}, /* "ＢＧＭ００９" */
    {NAME(0x15BC), 0xC}, /* "ＢＧＭ０１０" */
    {NAME(0x15AC), 0xD}, /* "ＢＧＭ０１１" */
    {NAME(0x159C), 0xE}, /* "ＢＧＭ０１２" */
    {NAME(0x158C), 0xF}, /* "ＢＧＭ０１３" */
    {NAME(0x157C), 0x10}, /* "ＢＧＭ０１４" */
    {NAME(0x156C), 0x11}, /* "ＢＧＭ０１５" */
    {NAME(0x155C), 0x12}, /* "ＢＧＭ０１６" */
    {NAME(0x154C), 0x13}, /* "ＢＧＭ０１７" */
    {NAME(0x153C), 0x14}, /* "ＢＧＭ０１８" */
    {NAME(0x152C), 0x15}, /* "ＢＧＭ０１９" */
    {NAME(0x151C), 0x16}, /* "ＢＧＭ０２０" */
    {NAME(0x150C), 0x17}, /* "ＢＧＭ０２１" */
    {NAME(0x14FC), 0x18}, /* "ＢＧＭ０２２" */
    {NAME(0x14EC), 0x19}, /* "ＢＧＭ０２３" */
    {NAME(0x14DC), 0x1A}, /* "ＢＧＭ０２４" */
    {NAME(0x14CC), 0x1B}, /* "ＢＧＭ０２５" */
    {NAME(0x14BC), 0x1C}, /* "ＢＧＭ０２６" */
    {NAME(0x14AC), 0x1D}, /* "ＢＧＭ０２７" */
    {NAME(0x149C), 0x1E}, /* "ＢＧＭ０２８" */
    {NAME(0x148C), 0x1F}, /* "ＢＧＭ０２９" */
    {NAME(0x147C), 0x20}, /* "ＢＧＭ０３０" */
    {NAME(0x146C), 0x21}, /* "ＢＧＭ０３１" */
    {NAME(0x145C), 0x22}, /* "ＢＯＳＳ００" */
    {NAME(0x144C), 0x23}, /* "ＢＯＳＳ０１" */
    {NAME(0x143C), 0x24}, /* "ＢＯＳＳ０２" */
    {NAME(0x142C), 0x25}, /* "ＢＯＳＳ０３" */
    {NAME(0x141C), 0x26}, /* "ＢＯＳＳ０４" */
    {NAME(0x140C), 0x27}, /* "ＣＢＴＬ００" */
    {NAME(0x13FC), 0x28}, /* "ＣＯＮＦＵＳ" */
    {NAME(0x13EC), 0x29}, /* "ＥＮＶ００１" */
    {NAME(0x13DC), 0x2A}, /* "ＥＮＶ００２" */
    {NAME(0x13CC), 0x2B}, /* "ＥＮＶ００３" */
    {NAME(0x13BC), 0x2C}, /* "ＥＮＶ００４" */
    {NAME(0x13AC), 0x2D}, /* "ＥＮＶ００５" */
    {NAME(0x139C), 0x2E}, /* "ＥＮＶ００６" */
    {NAME(0x138C), 0x2F}, /* "ＥＮＶ００７" */
    {NAME(0x137C), 0x30}, /* "ＥＮＶ００８" */
    {NAME(0x136C), 0x31}, /* "ＥＮＶ００９" */
    {NAME(0x135C), 0x32}, /* "ＥＮＶ０１０" */
    {NAME(0x134C), 0x33}, /* "ＥＮＶ０１１" */
    {NAME(0x133C), 0x34}, /* "ＥＮＶ０１２" */
    {NAME(0x132C), 0x35}, /* "ＥＮＶ０１３" */
    {NAME(0x131C), 0x36}, /* "ＥＮＶ０１４" */
    {NAME(0x130C), 0x37}, /* "ＥＮＶ０１５" */
    {NAME(0x12FC), 0x38}, /* "ＥＮＶ０１６" */
    {NAME(0x12EC), 0x39}, /* "ＥＮＶ０１７" */
    {NAME(0x12DC), 0x3A}, /* "ＥＮＶ０１８" */
    {NAME(0x12CC), 0x3B}, /* "ＥＮＶ０１９" */
    {NAME(0x12BC), 0x3C}, /* "ＥＮＶ０２０" */
    {NAME(0x12AC), 0x3D}, /* "ＥＮＶ０２１" */
    {NAME(0x129C), 0x3E}, /* "ＥＮＶ０２２" */
    {NAME(0x128C), 0x3F}, /* "ＥＮＶ０２３" */
    {NAME(0x127C), 0x40}, /* "ＥＮＶ０２４" */
    {NAME(0x126C), 0x41}, /* "ＥＮＶ０２５" */
    {NAME(0x125C), 0x42}, /* "ＥＮＶ２０４" */
    {NAME(0x124C), 0x43}, /* "ＥＮＶ２０５" */
    {NAME(0x123C), 0x44}, /* "ＥＮＶ２０６" */
    {NAME(0x122C), 0x45}, /* "ＥＶＯ＿００" */
    {NAME(0x121C), 0x46}, /* "ＪＯＧ＿００" */
    {NAME(0x120C), 0x47}, /* "ＴＴＬＢＧＭ" */
    {NAME(0), 0},
};

RECT SOUNDTST_screenRect = {0, 0, 320, 240};

Task *SOUNDTST_createSoundTest(void);

void SOUNDTST_updateScene(Task *task, Task **items) {
    switch (task->state) {
    case 0:
    default:
        items[0] = SOUNDTST_createSoundTest();
        task->nextState(task);
        break;
    case 1:
        if (PAD.getPressed(0) & (1 << PAD_START)) {
            GAME_FUNCS.requestMode(0x1500, 0);
            task->nextState(task);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task *SOUNDTST_start(void) {
    return createTask(SOUNDTST_updateScene, sizeof(Task), 4);
}

void SOUNDTST_moveCursor(SoundTest *task, s32 delta, s32 *cursor, s32 *top, s32 count) {
    s32 pos = *cursor + delta;

    if (pos >= 0 && pos < count) {
        *cursor = pos;
        if (pos >= *top + 8) {
            *top = pos - 7;
        }
        if (*top > *cursor) {
            *top = *cursor;
        }
    }
}

void SOUNDTST_playSounds(SoundTest *task, SoundTestWindows *win) {
    SoundTestEntry *list = SOUNDTST_soundLists[task->bankCursor];
    s32 i;
    s32 j;

    switch (task->step) {
    case 0:
    default:
        task->soundCursor = 0;
        task->soundTop = 0;
        task->soundCount = 0;
        while (list[task->soundCount].id != 0) {
            task->soundCount++;
        }
        win->header->setText(win->header, SOUNDTST_banks[task->bankCursor].name);
        task->playing = 0;
        task->nextStep(task);
    case 1:
        break;
    }
    if ((PAD.getPressed(0) | PAD.getRepeated(0)) & (1 << PAD_DOWN)) {
        SOUNDTST_moveCursor(task, 1, &task->soundCursor, &task->soundTop, task->soundCount);
    } else if ((PAD.getPressed(0) | PAD.getRepeated(0)) & (1 << PAD_UP)) {
        SOUNDTST_moveCursor(task, -1, &task->soundCursor, &task->soundTop, task->soundCount);
    } else if (PAD.getPressed(0) & (1 << PAD_SQUARE)) {
        SOUND_STATE.stopAll();
    } else if (PAD.getPressed(0) & (1 << PAD_TRIANGLE)) {
        task->setSubstate(task, 0);
    } else if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
        task->voice = SOUND_STATE.playSound(list[task->soundCursor].id);
        task->playing = 1;
    } else if (task->playing != 0 && !(PAD.getHeld(0) & (1 << PAD_CROSS))) {
        task->playing = 0;
        SOUND_STATE.keyOff(list[task->soundCursor].id, task->voice);
    }
    for (i = 0, j = task->soundTop; i < 8 && list[j].id != 0; i++, j++) {
        win->lines[i]->setText(win->lines[i], list[j].name);
        win->lines[i]->setVisible(win->lines[i], 1);
    }
    for (; i < 8; i++) {
        win->lines[i]->setVisible(win->lines[i], 0);
    }
    win->cursor->setPos(win->cursor, 0x20, (task->soundCursor - task->soundTop) * 16 + 0x46);
}

void SOUNDTST_loadBank(SoundTest *task, SoundTestWindows *win) {
    switch (task->step) {
    case 0:
    default:
        if (task->bank == 1) {
            SOUND_STATE.loadBankInto(0, 1);
        } else {
            SOUND_STATE.loadBank(task->bank);
        }
        task->step++;
    case 1:
        break;
    }
    if (SOUND_STATE.isLoading() == 0) {
        task->nextSubstate(task);
    }
}

void SOUNDTST_selectBank(SoundTest *task, SoundTestWindows *win) {
    s32 i;
    s32 j;

    switch (task->step) {
    case 0:
    default:
        task->bankCount = 0;
        while (SOUNDTST_banks[task->bankCount].id != 0) {
            task->bankCount++;
        }
        win->header->setText(win->header, SOUNDTST_STR_SELECT_VAB);
        task->nextStep(task);
    case 1:
        break;
    }
    if ((PAD.getPressed(0) | PAD.getRepeated(0)) & (1 << PAD_DOWN)) {
        SOUNDTST_moveCursor(task, 1, &task->bankCursor, &task->bankTop, task->bankCount);
    } else if ((PAD.getPressed(0) | PAD.getRepeated(0)) & (1 << PAD_UP)) {
        SOUNDTST_moveCursor(task, -1, &task->bankCursor, &task->bankTop, task->bankCount);
    } else if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
        task->bank = SOUNDTST_banks[task->bankCursor].id;
        task->nextSubstate(task);
    }
    for (i = 0, j = task->bankTop; i < 8 && SOUNDTST_banks[j].id != 0; i++, j++) {
        win->lines[i]->setText(win->lines[i], SOUNDTST_banks[j].name);
        win->lines[i]->setVisible(win->lines[i], 1);
    }
    for (; i < 8; i++) {
        win->lines[i]->setVisible(win->lines[i], 0);
    }
    win->cursor->setPos(win->cursor, 0x20, (task->bankCursor - task->bankTop) * 16 + 0x46);
}

void SOUNDTST_updateSoundTest(SoundTest *task, SoundTestWindows *win) {
    Layer *res;
    s32 i;

    switch (task->state) {
    case 0:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x5000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        res = GFX.funcs.createLayer(&SOUNDTST_screenRect, 1, 0x1000);
        res->setBgColor(res, 0x1F, 0x1F, 0x1F);
        win->title = createTextWindow(0x1000, 1, 0x10, 0x1E);
        win->title->setText(win->title, SOUNDTST_STR_SOUND_TEST);
        win->header = createTextWindow(0x1000, 1, 0x20, 0x32);
        for (i = 0; i < 8; i++) {
            win->lines[i] = createTextWindow(0x1000, 1, 0x30, i * 16 + 0x46);
        }
        win->cursor = createTextWindow(0x1000, 1, 0x20, 0x46);
        win->cursor->setText(win->cursor, SOUNDTST_STR_CURSOR);
        task->nextState(task);
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            SOUNDTST_selectBank(task, win);
            break;
        case 1:
            SOUNDTST_loadBank(task, win);
            break;
        case 2:
            SOUNDTST_playSounds(task, win);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        GAME_FUNCS.requestMode(0x1500, 0);
        break;
    }
}

Task *SOUNDTST_createSoundTest(void) {
    return createTask(SOUNDTST_updateSoundTest, sizeof(SoundTest), sizeof(SoundTestWindows));
}

INCLUDE_RODATA("soundtst/nonmatchings/soundtst", SOUNDTST_entryNames);

INCLUDE_RODATA("soundtst/nonmatchings/soundtst", SOUNDTST_STR_SELECT_VAB);

INCLUDE_RODATA("soundtst/nonmatchings/soundtst", SOUNDTST_STR_SOUND_TEST);

INCLUDE_RODATA("soundtst/nonmatchings/soundtst", SOUNDTST_STR_CURSOR);
