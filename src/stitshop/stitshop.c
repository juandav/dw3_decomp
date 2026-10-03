#include "stitshop.h"

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
ItemShop *func_8008B77C(void);
void func_8008B614();
void func_8008B7E0(void);
s32 func_8008B880(void);
void func_8008B908(PanelAnim *fade, s32 fadeIn);
s32 func_8008B99C(PanelAnim *fade);
void func_8008BA08(ShopLerp *lerp, s32 from, s32 to, s32 frames);
s32 func_8008BA48(ShopLerp *lerp);

void func_800829B4(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x14000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)func_8008B77C();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_80082AB0(void) {
    return createTask(func_800829B4, sizeof(Task), 4);
}

void func_80082ADC(ScreenFade *task, s32 fadeIn, s32 duration) {
    task->setState(task, TASK_RUN);
    task->substate = 1;
    task->fadeIn = fadeIn;
    if (fadeIn == 0) {
        task->level = 0;
        task->levelStep = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->levelStep = -(0xFF00 / duration);
    }
}

void func_80082B64(ScreenFade *task) {
    Layer *layer = GFX.funcs.getLayer(task->layerId);
    u_long *ot = (u_long *)layer->getOtEntry(layer, task->depth);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->code = 0x2A;
    poly->r0 = poly->g0 = poly->b0 = task->level >> 8;
    poly->x0 = poly->x2 = 0;
    poly->x1 = poly->x3 = 320;
    poly->y0 = poly->y1 = 0;
    poly->y2 = poly->y3 = 256;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = 0xE1000245;
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void func_80082CA8(ScreenFade *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        if (task->substate == 0) {
            break;
        }
        task->level += task->levelStep;
        if (task->fadeIn == 0) {
            if (task->level > 0xFF00) {
                task->level = 0xFF00;
                task->state = 2;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = 2;
        }
        /* fallthrough */
    case 2:
        func_80082B64(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *func_80082D5C(void) {
    ScreenFade *task = createTask(func_80082CA8, sizeof(ScreenFade), 0);

    task->start = func_80082ADC;
    task->layerId = 0x1000;
    task->depth = 6;
    return task;
}

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80082DA4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80082E90);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80082F94);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800830DC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008361C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80084FCC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80085070);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800850A8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800850FC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80085254);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80085684);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800869F8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80086AA0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80086AD8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80086B2C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80086CE4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008700C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800873E8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800875AC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087D5C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087E00);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087EB0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087ED8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087F1C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087F64);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087FD0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088094);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088150);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800884A4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088578);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088638);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008879C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088960);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089104);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800894EC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089774);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008988C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089AE0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089DE8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A46C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A5E8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A91C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A9A4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A9C0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A9F8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AAB0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AB04);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008ABA4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AC8C);

#if VERSION_EU
/* The European splat cuts func_8008AC8C, func_8008AF88 and func_8008B614
 * where the names config/eu/symbols.txt gives three FIELDSTG functions for
 * the executable fall */
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AEB4);
#endif

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AF88);

#if VERSION_EU
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B2C4);
#endif

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B614);

#if VERSION_EU
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B320);
#endif

void func_8008B728(ItemShop *shop) {
    ItemShopWindows *win = shop->children;

    win->money->setNumber(win->money, 0, GAME.money);
    win->money->setRightAlign(win->money, 1);
}

ItemShop *func_8008B77C(void) {
    ItemShop *shop = createTask(func_8008B614, sizeof(ItemShop), sizeof(ItemShopWindows));

    shop->showMoney = func_8008B728;
    shop->layer = 0x1000;
    shop->shop = GAME_FUNCS.getModeArg();
    return shop;
}

void func_8008B7E0(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry((FILE_SHOP_SPRITES + 1) << 16));
    FILE_CACHE.request(TEXT_FILE(0x72));
    FILE_CACHE.request(TEXT_FILE(0x6B));
    FILE_CACHE.request(TEXT_FILE(0x64));
    FILE_CACHE.request(TEXT_FILE(0x95));
}

s32 func_8008B880(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x72)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x6B)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x64)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x95)) != 0;
}

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B908);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B99C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BA08);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BA48);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BAB4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BAF8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BB3C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BE2C);

extern s32 D_8008C1E4[];
extern s32 D_8008C1FC[];
extern s32 D_8008C224[];
extern s32 D_8008C24C[];
extern s32 D_8008C274[];
extern s32 D_8008C27C[];
extern s32 D_8008C294[];
extern s32 D_8008C2BC[];
extern s32 D_8008C2D4[];
extern s32 D_8008C2FC[];
extern s32 D_8008C324[];
extern s32 D_8008C34C[];
extern s32 D_8008C374[];
extern s32 D_8008C3A0[];
extern s32 D_8008C3C8[];
extern s32 D_8008C3F4[];
extern s32 D_8008C41C[];
extern s32 D_8008C444[];
extern s32 D_8008C470[];
extern s32 D_8008C4B4[];
extern s32 D_8008C4D4[];
extern s32 D_8008C4FC[];
extern s32 D_8008C528[];
extern s32 D_8008C550[];
extern s32 D_8008C578[];
extern s32 D_8008C5A4[];
extern s32 D_8008C5CC[];
extern s32 D_8008C5F4[];
extern s32 D_8008C620[];
extern s32 D_8008C648[];
extern s32 D_8008C674[];
void func_8008BAB4();
void func_8008BAF8();
void func_8008BB3C();
void func_8008BE2C();

s32 D_8008C0D4[] = {
    1, 2, 3, 4,
};
s32 D_8008C0E4[] = {
    23, 172, 23, 186,
    23, 200, 65, 200,
    23, 214, 65, 214,
};
s32 D_8008C114[] = {
    6, 7, 8, 9,
    10, 11, 12, 13,
    14, 15, 16, 17,
    18,
};
s32 D_8008C148[] = {
    0, 35, 36, 37,
    38, 39, 40, 41,
    42,
};
s32 D_8008C16C[] = {
    17, 1, 5, 18,
    6, 25, 13, 24,
    4, 12, 29, 30,
    16, 21, 9, 19,
    2, 7, 20, 8,
    26, 14, 23, 3,
    11, 27, 28, 15,
    22, 10,
};
s32 D_8008C1E4[] = {
    0x6A005C, 0xA7009D, 0xD700BE, 0xEC00E2,
    0x10600F9, 275,
};
s32 D_8008C1FC[] = {
    0x1260124, 0x12A0128, 0x12E012C, 0x1310130,
    0x1330132, 0x1350134, 0x1370136, 0x1390138,
    0x13B013A, 0,
};
s32 D_8008C224[] = {
    0x42002B, 0x450043, 0x470046, 0x490048,
    0x4B004A, 0x4D004C, 0x4F004E, 0x510050,
    0x530052, 84,
};
s32 D_8008C24C[] = {
    0x6E0060, 0x86007A, 0xA10093, 0xB200AB,
    0xC200B9, 0xD100C9, 0xE600DB, 0xFD00F0,
    0x117010A, 0,
};
s32 D_8008C274[] = {
    0x2C002B, 0,
};
s32 D_8008C27C[] = {
    0x6B005D, 0xA8009E, 0xD800BF, 0xED00E3,
    0x10700FA, 276,
};
s32 D_8008C294[] = {
    0x42002B, 0x450043, 0x470046, 0x490048,
    0x4B004A, 0x4D004C, 0x4F004E, 0x510050,
    0x530052, 84,
};
s32 D_8008C2BC[] = {
    0x6C005E, 0xA9009F, 0xD900C0, 0xEE00E4,
    0x10800FB, 277,
};
s32 D_8008C2D4[] = {
    0x1260124, 0x12A0128, 0x12E012C, 0x1310130,
    0x1330132, 0x1350134, 0x1370136, 0x1390138,
    0x13B013A, 0,
};
s32 D_8008C2FC[] = {
    0x42002B, 0x450043, 0x470046, 0x490048,
    0x4B004A, 0x4D004C, 0x4F004E, 0x510050,
    0x530052, 84,
};
s32 D_8008C324[] = {
    0x6D005F, 0x840078, 0xA00091, 0xB000AA,
    0xC100B7, 0xCF00C7, 0xE500DA, 0xFC00EF,
    0x1160109, 0,
};
s32 D_8008C34C[] = {
    0x6D005F, 0x840078, 0xA00091, 0xB000AA,
    0xC100B7, 0xCF00C7, 0xE500DA, 0xFC00EF,
    0x1160109, 0,
};
s32 D_8008C374[] = {
    0x2C002B, 0x430042, 0x460045, 0x480047,
    0x4A0049, 0x4C004B, 0x4E004D, 0x50004F,
    0x520051, 0x540053, 0,
};
s32 D_8008C3A0[] = {
    0x6F0061, 0x87007B, 0xA20094, 0xB300AC,
    0xC300BA, 0xD200CA, 0xE700DC, 0xFE00F1,
    0x118010B, 0,
};
s32 D_8008C3C8[] = {
    0x2C002B, 0x430042, 0x460045, 0x480047,
    0x4A0049, 0x4C004B, 0x4E004D, 0x50004F,
    0x520051, 0x540053, 0,
};
s32 D_8008C3F4[] = {
    0x730065, 0x8C007F, 0xA60098, 0xB600AF,
    0xC600BD, 0xD600CE, 0xEB00E1, 0x10500F8,
    0x1230112, 0,
};
s32 D_8008C41C[] = {
    0x1270125, 0x12B0129, 0x12F012D, 0x1310130,
    0x1330132, 0x1350134, 0x1370136, 0x1390138,
    0x13B013A, 0,
};
s32 D_8008C444[] = {
    0x2C002B, 0x42002D, 0x450043, 0x470046,
    0x490048, 0x4B004A, 0x4D004C, 0x4F004E,
    0x510050, 0x530052, 84,
};
s32 D_8008C470[] = {
    0x700062, 0x88007C, 0x950089, 0xCB00A3,
    0xDD00D3, 0xE800DE, 0xF300F2, 0xF500F4,
    0x10000FF, 0x1020101, 0x10D010C, 0x10F010E,
    0x11A0119, 0x11C011B, 0x11E011D, 0x120011F,
    0,
};
s32 D_8008C4B4[] = {
    0x30002F, 0x320031, 0x340033, 0x360035,
    0x380037, 0x3A0039, 0x3C003B, 61,
};
s32 D_8008C4D4[] = {
    0x6E0060, 0x86007A, 0xA10093, 0xB200AB,
    0xC200B9, 0xD100C9, 0xE600DB, 0xFD00F0,
    0x117010A, 0,
};
s32 D_8008C4FC[] = {
    0x2C002B, 0x430042, 0x460045, 0x480047,
    0x4A0049, 0x4C004B, 0x4E004D, 0x50004F,
    0x520051, 0x540053, 0,
};
s32 D_8008C528[] = {
    0x6F0061, 0x87007B, 0xA20094, 0xB300AC,
    0xC300BA, 0xD200CA, 0xE700DC, 0xFE00F1,
    0x118010B, 0,
};
s32 D_8008C550[] = {
    0x1260124, 0x12A0128, 0x12E012C, 0x1310130,
    0x1330132, 0x1350134, 0x1370136, 0x1390138,
    0x13B013A, 0,
};
s32 D_8008C578[] = {
    0x2C002B, 0x430042, 0x460045, 0x480047,
    0x4A0049, 0x4C004B, 0x4E004D, 0x50004F,
    0x520051, 0x540053, 0,
};
s32 D_8008C5A4[] = {
    0x710063, 0x8A007D, 0xA40096, 0xB400AD,
    0xC400BB, 0xD400CC, 0xE900DF, 0x10300F6,
    0x1210110, 0,
};
s32 D_8008C5CC[] = {
    0x720064, 0x8B007E, 0xA50097, 0xB500AE,
    0xC500BC, 0xD500CD, 0xEA00E0, 0x10400F7,
    0x1220111, 0,
};
s32 D_8008C5F4[] = {
    0x2C002B, 0x430042, 0x460045, 0x480047,
    0x4A0049, 0x4C004B, 0x4E004D, 0x50004F,
    0x520051, 0x540053, 0,
};
s32 D_8008C620[] = {
    0x720064, 0x8B007E, 0xA50097, 0xB500AE,
    0xC500BC, 0xD500CD, 0xEA00E0, 0x10400F7,
    0x1220111, 0,
};
s32 D_8008C648[] = {
    0x2C002B, 0x430042, 0x460045, 0x480047,
    0x4A0049, 0x4C004B, 0x4E004D, 0x50004F,
    0x520051, 0x540053, 0,
};
s32 D_8008C674[] = {
    0x20001, 0x40003, 0x60005, 0x80007,
    0xA0009, 0xC000B, 0xE000D, 0x10000F,
    0x120011, 0x140013, 0x160015, 0x180017,
    0x1A0019, 0x1C001B, 0x1E001D, 0x20001F,
    0x220021, 0x240023, 0x260025, 0x280027,
    0x2A0029, 0x18A0168, 0x18C018B, 0x18E018D,
    0x190018F, 0x1920191, 0,
};
s32 D_8008C6E0[] = {
    11, (s32)D_8008C1E4, 18, (s32)D_8008C1FC,
    19, (s32)D_8008C224, 18, (s32)D_8008C24C,
    2, (s32)D_8008C274, 11, (s32)D_8008C27C,
    19, (s32)D_8008C294, 11, (s32)D_8008C2BC,
    18, (s32)D_8008C2D4, 19, (s32)D_8008C2FC,
    18, (s32)D_8008C324, 18, (s32)D_8008C34C,
    20, (s32)D_8008C374, 18, (s32)D_8008C3A0,
    20, (s32)D_8008C3C8, 18, (s32)D_8008C3F4,
    18, (s32)D_8008C41C, 21, (s32)D_8008C444,
    32, (s32)D_8008C470, 15, (s32)D_8008C4B4,
    18, (s32)D_8008C4D4, 20, (s32)D_8008C4FC,
    18, (s32)D_8008C528, 18, (s32)D_8008C550,
    20, (s32)D_8008C578, 18, (s32)D_8008C5A4,
    18, (s32)D_8008C5CC, 20, (s32)D_8008C5F4,
    18, (s32)D_8008C620, 20, (s32)D_8008C648,
    52, (s32)D_8008C674,
};
s32 D_8008C7D8 = 0;
s32 D_8008C7DC = (s32)func_8008B7E0;
s32 D_8008C7E0 = (s32)func_8008B880;
s32 D_8008C7E4 = (s32)func_8008B908;
s32 D_8008C7E8[] = {
    (s32)func_8008B99C, (s32)func_8008BA08, (s32)func_8008BA48, (s32)func_8008BAB4,
};
s32 D_8008C7F8[] = {
    (s32)func_8008BAF8, (s32)func_8008BB3C, (s32)func_8008BE2C,
};
