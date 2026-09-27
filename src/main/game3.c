#include "game.h"

s32 func_800154F8(u8 *bits, s32 index, s32 set) {
    s32 byte = index >> 3;
    s32 mask = 1 << (index & 7);

    if (set != 0) {
        return (bits[byte] & mask) != 0;
    }
    return (bits[byte] & mask) == 0;
}

void func_8001553C(u8 *bits, s32 index, s32 set) {
    s32 byte = index >> 3;
    s32 mask = 1 << (index & 7);

    if (set) {
        bits[byte] |= mask;
    } else {
        bits[byte] &= ~mask;
    }
}

s32 func_80015584(s32 op, s32 arg) {
    s32 ret = 0;

    if ((D_800484E8.unk7C[7] != 0 || D_800484E8.unk20F[7] != 0) &&
        (D_800484E8.unk7C[0x59] != 0 || D_800484E8.unk20F[0x59] != 0) &&
        (D_800484E8.unk7C[0xA7] != 0 || D_800484E8.unk20F[0xA7] != 0)) {
        ret = 1;
    }
    return ret;
}

s32 func_800155F8(u32 op, s32 arg) {
    s32 result = 0;
    s32 i;
    s32 total;
    s32 id;

    switch (op) {
    case 0:
        if (D_8004AB28 == arg) {
            result = 1;
        }
        break;
    case 1:
        if (D_800484E8.records[arg].unk4 != 0) {
            result = 1;
        }
        break;
    case 2:
        for (i = 0; i < 3; i++) {
            if (D_800484E8.unk270C(i) == arg) {
                result = 1;
                break;
            }
        }
        break;
    case 3:
        D_800484E8.records[arg].unk4 = arg + 3;
        result = 1;
        break;
    case 4:
        if (D_800484E8.records[arg].unk4 != 0 && D_800484E8.records[arg].unk28 >= 0x2D) {
            result = 1;
        }
        break;
    case 5:
        total = 0;
        for (i = 0; i < 3; i++) {
            id = D_800484E8.unk270C(i);
            if (id >= 0) {
                total += D_800484E8.unk2744(id)->unk1C;
            }
        }
        if (total >= arg * 15 + 30) {
            result = 1;
        }
        break;
    case 6:
        if (D_800484E8.records[arg].unk4 == 0) {
            result = 1;
        }
        break;
    }
    return result;
}

s32 func_80015814(s32 op, s32 item) {
    s32 ret = 0;

    switch (op) {
    case 0:
        if (D_800483F8[item] <= D_800484E8.money) {
            ret = 1;
        }
        break;
    case 1:
        D_800484E8.money += D_80048420[item];
        if (D_800484E8.money > 9999999) {
            D_800484E8.money = 9999999;
        }
        break;
    case 2:
        D_800484E8.money -= D_80048440[item];
        if (D_800484E8.money < 0) {
            D_800484E8.money = 0;
        }
        break;
    }
    return ret;
}

s32 func_80015904(s32 arg0, s32 index) {
    s32 value = D_8004AB24;
    s32 min = D_80048468[index][0];
    s32 max = D_80048468[index][1];
    s32 ret = 0;

    if (value >= min) {
        ret = max >= value;
    }
    return ret;
}

s32 func_80015940(s32 arg0, s32 mode) {
    s32 ret = 0;
    s32 on = 0;
    s32 off = 0;
    s32 i;

    for (i = 0x27; i < 0x2E; i++) {
        if (func_800154F8(D_8004AB5F, i, 1) != 0) {
            on++;
        } else {
            off++;
        }
    }
    switch (mode) {
    case 0:
        if (on != 0) {
            ret = 1;
        }
        break;
    case 1:
        if (off >= 2) {
            ret = 1;
        }
        break;
    case 2:
        if (off == 1) {
            ret = 1;
        }
        break;
    }
    return ret;
}

s32 func_80015A34(s32 op, s32 arg) {
    Unk80015A34 *obj = D_8004AF58.unkC(0x16, -1, -1);

    obj->unk2C(obj, 3);
    return 1;
}

s32 func_80015A78(s32 id, s32 expected) {
    u8 *p;
    s32 result = 0;
    s32 op;
    s32 arg;

    for (p = D_8004829C; *p != 0xFF; p += 3) {
        if (*p == id) {
            op = p[1] & 0xF;
            arg = p[2];
            switch (p[1] & 0xF0) {
            case 0x00:
                result = func_80015584(op, arg);
                break;
            case 0x10:
                result = func_800155F8(op, arg);
                break;
            case 0x20:
                result = func_80015814(op, arg);
                break;
            case 0x30:
                result = func_80015904(op, arg);
                break;
            case 0x40:
                result = func_80015940(op, arg);
                break;
            case 0x50:
                result = func_80015A34(op, arg);
                break;
            }
            break;
        }
    }
    return expected == result;
}

s32 func_80015BB0(s32 value, s32 mode) {
    if (mode != 0) {
        if (D_8004AB24 == value) {
            return 1;
        }
    } else {
        if (D_8004AB24 != value) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015BEC(s32 index, s32 mode) {
    if (mode != 0) {
        if (D_800484E8.unk7C[index] != 0 || D_800484E8.unk20F[index] != 0) {
            return 1;
        }
    } else {
        if (D_800484E8.unk7C[index] == 0 && D_800484E8.unk20F[index] == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015C58(s32 item, s32 have) {
    if (have != 0) {
        if (D_800484E8.itemCounts[item] != 0) {
            return 1;
        }
    } else {
        if (D_800484E8.itemCounts[item] == 0) {
            return 1;
        }
    }
    return 0;
}

extern s32 D_800484AC[];

s32 func_80015CA4(s32 index, s32 mode) {
    Unk2728 buf;
    s32 total = 0;
    s32 i;
    s32 id;

    for (i = 0; i < 3; i++) {
        id = D_800484E8.unk270C(i);
        if (id >= 0) {
            D_800484E8.unk2728(id, &buf);
            total += buf.unk16;
        }
    }
    if (mode != 0) {
        if (total >= D_800484AC[index]) {
            return 1;
        }
    } else {
        if (total < D_800484AC[index]) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015D90(s32 id, s32 arg1) {
    if (id < 30) {
        if (D_800484E8.unk44 == id + 1) {
            return 1;
        }
    } else {
        if (D_800484E8.unk46 == id - 29) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015DD8(s32 slot, s32 item) {
    Unk80048C50 *d = &D_80048C50[slot];
    u8 *info = D_800427A4(item)->data;
    s16 *equip = d->equip;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (equip[i] == item) {
            if (info[2] == 7) {
                d->equip[2] = 0;
                d->equip[3] = 0;
            } else {
                equip[i] = 0;
            }
            return 1;
        }
    }
    return 0;
}

void func_80015E8C(s32 item, s32 add) {
    s32 i;

    if (add != 0) {
        if (++D_800484E8.unk7C[item] >= 100) {
            D_800484E8.unk7C[item] = 99;
        }
    } else if (D_800484E8.unk7C[item] != 0) {
        if (--D_800484E8.unk7C[item] < 0) {
            D_800484E8.unk7C[item] = 0;
        }
    } else if (D_800484E8.unk20F[item] != 0) {
        for (i = 0; i < 3; i++) {
            if (func_80015DD8(D_800484E8.unk270C(i), item) != 0) {
                goto found;
            }
        }
        for (i = 0; i < 8; i++) {
            if (D_800484E8.records[i].unk4 >= 3 && func_80015DD8(i, item) != 0) {
                break;
            }
        }
    found:
        D_800484E8.unk20F[item]--;
    }
}

void func_80015FC8(s32 item, s32 arg1) {
    if (arg1 != 0) {
        D_8004ABD8.unk24(item, 1);
        return;
    }
    D_800484E8.itemCounts[item]--;
    if (D_800484E8.itemCounts[item] < 0) {
        D_800484E8.itemCounts[item] = 0;
    }
}

void func_8001602C(s32 arg0, s32 arg1) {
    func_8008AEB4(0x700, arg0 * 2 + arg1 + 1, 0, 0, 0);
}

s32 func_80016064(u16 code, u16 value) {
    u16 group = (code >> 8) & 0xFE;
    s32 id = code & 0x1FF;
    u16 arg = value;

    if (group == 0x00) {
        return func_800154F8(D_80048280, id, arg);
    } else if (group == 0x02) {
        return func_800154F8(D_8004AB2C, id, arg);
    } else if (group == 0x04) {
        return func_800154F8(D_8004AB39, id, arg);
    } else if (group == 0x06) {
        return func_800154F8(D_8004AB3B, id, arg);
    } else if (group == 0x08) {
        return func_800154F8(D_8004AB3C, id, arg);
    } else if (group == 0x0A) {
        return func_800154F8(D_8004AB3D, id, arg);
    } else if (group == 0x0C) {
        return func_800154F8(D_8004AB3F, id, arg);
    } else if (group == 0x0E) {
        return func_800154F8(D_8004AB47, id, arg);
    } else if (group == 0x10) {
        return func_800154F8(D_8004AB53, id, arg);
    } else if (group == 0x18) {
        return func_800154F8(D_8004AB55, id, arg);
    } else if (group == 0x1A) {
        return func_800154F8(D_8004AB56, id, arg);
    } else if (group == 0x1C) {
        return func_800154F8(D_8004AB5F, id, arg);
    } else if (group == 0x20) {
        return func_800154F8(D_8004AB6A, id, arg);
    } else if (group == 0x40) {
        return func_800154F8(D_8004AB88, id, arg);
    } else if (group == 0x60) {
        return func_80015BB0(id, arg);
    } else if (group == 0x70) {
        return func_80015A78(id, arg);
    } else if (group == 0x72) {
        return func_80015CA4(id, arg);
    } else if (group == 0x7E) {
        return func_80015D90(id, arg);
    } else if (group >= 0x80 && group < 0x8F) {
        return func_80015BEC(id, arg);
    } else if (group == 0x92) {
        return func_80015C58(id, arg);
    }
    return 1;
}

extern void (*D_8009A6EC)(s32 id);
void func_8008B2C4(s32 id);
void func_8008B320(void);

void func_80016260(s32 code, s32 value) {
    u16 group = (code >> 8) & ~1;
    s32 id = code & 0x1FF;

    if (group == 0x00) {
        func_8001553C(D_80048280, id, value);
    }
    if (group == 0x02) {
        func_8001553C(D_8004AB2C, id, value);
    }
    if (group == 0x04) {
        func_8001553C(D_8004AB39, id, value);
    }
    if (group == 0x06) {
        func_8001553C(D_8004AB3B, id, value);
    }
    if (group == 0x08) {
        func_8001553C(D_8004AB3C, id, value);
    }
    if (group == 0x0A) {
        func_8001553C(D_8004AB3D, id, value);
    }
    if (group == 0x0C) {
        func_8001553C(D_8004AB3F, id, value);
    }
    if (group == 0x0E) {
        func_8001553C(D_8004AB47, id, value);
    }
    if (group == 0x10) {
        func_8001553C(D_8004AB53, id, value);
    }
    if (group == 0x18) {
        func_8001553C(D_8004AB55, id, value);
    }
    if (group == 0x1A) {
        func_8001553C(D_8004AB56, id, value);
    }
    if (group == 0x1C) {
        func_8001553C(D_8004AB5F, id, value);
    }
    if (group == 0x20) {
        func_8001553C(D_8004AB6A, id, value);
    }
    if (group == 0x40) {
        func_8001553C(D_8004AB88, id, value);
    }
    if (group == 0x70) {
        func_80015A78(id, 1);
    }
    if (group == 0x74) {
        D_8009A6EC(id);
    }
    if (group == 0x76) {
        func_8001602C(id, 0);
    }
    if (group == 0x78) {
        func_8001602C(id, 1);
    }
    if (group >= 0x80 && group < 0x8F) {
        func_80015E8C(id, value);
    }
    if (group == 0x90) {
        func_8008B2C4(id);
    }
    if (group == 0x92) {
        func_80015FC8(id, value);
    }
    if (group == 0x94) {
        func_8008AEB4(0xA00, id, 0, 0, 0);
    }
    if (group == 0x7A) {
        if ((u16)id < 30) {
            func_8008AEB4(0xF00, (u16)id, 0, 0, 0);
        } else if ((u32)(id - 0x31) < 0x13 || (u32)(id - 0x46) < 5) {
            func_8008AEB4(0x1300, (u16)id, 0, 0, 0);
        } else {
            func_8008B320();
        }
    }
    if (group == 0x7C) {
        if ((u16)id == 0) {
            func_8008AEB4(0xD00, 0, 0, 0, 0);
        } else if ((u16)id == 1) {
            func_8008AEB4(0xB00, 0, 0, 0, 0);
        }
    }
}

s32 func_800165D8(u16 *list) {
    u16 a;

    for (a = *list; a != 0xFFFF; a = *list) {
        list++;
        if (!func_80016064(a, *list++)) {
            return 0;
        }
    }
    return 1;
}

void func_8001663C(u16 *list) {
    u16 a;

    for (a = *list; a != 0xFFFF; a = *list) {
        list++;
        func_80016260(a, *list++);
    }
}

void func_80016694(void) {
    s32 i;
    u8 *p;

    if (D_8004ABB8 != 0) {
        for (i = 2, p = &D_80048280[i]; i >= 0; i--) {
            *p-- = 0;
        }
        func_80016260(0x12, 0);
    }
    if (D_8004ABD8.unk18() == 0x700) {
        func_80016260(0x11, 1);
        func_80016260(0x12, 1);
        if (D_80048284 != 0) {
            func_80016260(0x10, 1);
        } else {
            func_80016260(0x10, 0);
        }
        D_80048284 = 0;
    }
}

void func_80016748(void) {
    D_8004AD84.bzero(&D_800484E8, 0x26BC);
    D_800484E8.unk26BC = 0xE01;
    D_800484E8.unk26C0 = 0xE01;
    D_800484E8.unk4 = 1;
    D_800484E8.unk26CC = 1;
    D_800484E8.unk26CD = 8;
    D_800484E8.unk26CF = 60;
    D_800484E8.unk26C8 = 0;
    D_800484E8.unk26CE = 0;
    D_800484E8.unkC = -1;
    func_80016860();
    D_800484E8.unk30 = (D_8004D3B0.rand() & 0x1FF) + 0x200;
}

void func_800167DC(void) {
    s32 prev;

    if (D_800484E8.unk26C0 != 0) {
        prev = D_800484E8.unk26BC;
        D_800484E8.unk26BC = D_800484E8.unk26C0;
        D_800484E8.unk26C0 = 0;
        D_800484E8.unk26C4 = prev;
    }
}

s32 func_8001680C(void) {
    return D_8004ABAC;
}

s32 func_8001681C(void) {
    return D_8004ABA4;
}

s32 func_8001682C(void) {
    return D_8004ABB0;
}

void func_8001683C(s32 arg0, s32 arg1) {
    D_800484E8.unk26C0 = arg0;
    D_800484E8.unk26C8 = arg1;
}

s32 func_80016850(void) {
    return D_8004ABA8 != 0;
}

void func_80016860(void) {
    Obj8001F8F8 cls;
    s32 i;
    s32 j;
    u16 *dst;
    u16 *src;
    Unk8003EB68 *e;

    func_8001F8F8(&cls);
    strcpy(D_800484E8.name, cls.unk0(D_80044744.getText(0x87), 0xB));
    D_800484E8.unk70[0] = -1;
    D_800484E8.unk70[1] = -1;
    D_800484E8.unk70[2] = -1;
    for (j = 0; j < 3; j++) {
        strcpy(D_800484E8.unk628[j].name, cls.unk0(D_80044744.getText(0x33), j + 0x16));
    }
    D_800484E8.unk2718();
    for (i = 0; i < 8; i++) {
        e = &D_8003EB68[i];
        strcpy(D_800484E8.records[i].name, cls.unk0(D_80044744.getText(0x4F), e->nameId));
        D_800484E8.records[i].unk28 = 1;
        D_800484E8.records[i].unk2C = D_800484E8.records[i].unk2E = e->unk3F;
        D_800484E8.records[i].unk30 = D_800484E8.records[i].unk32 = e->unk40;
        /* unk34, reached from the name like the ROM does */
        dst = (u16 *)(D_800484E8.records[i].name + 0x28);
        src = e->unk2;
        for (j = 0; j < 6; j++) {
            *dst++ = *src++;
        }
        src = e->unkE;
        for (j = 0; j < 7; j++) {
            *dst++ = *src++;
        }
    }
}

s32 func_80016A30(u32 index) {
    if (index >= 3) {
        return -1;
    }
    return D_800484E8.unk70[index];
}

void func_80016A5C(s32 set) {
    s32 i;
    u8 slot;

    for (i = 0; i < 3; i++) {
        slot = D_8004AC38[set][i];
        D_800484E8.unk70[i] = slot;
        D_800484E8.records[slot].unk4 = slot + 3;
    }
    D_8004AB28 = set;
}

void func_80016AC8(s32 item, s32 count) {
    D_800484E8.itemFlags[item] = 1;
    D_800484E8.itemCounts[item] += count;
    if (D_800484E8.itemCounts[item] >= 10) {
        D_800484E8.itemCounts[item] = 9;
    }
}

void func_80016B08(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        func_80016AC8(D_8004AC44[i], 1);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 40; i++) {
            D_800484E8.unk628[j].items[i] = D_8004AC44[i];
        }
    }
}

void func_80016BA8(void) {
    D_800484E8.playTimeMaxed = 0;
    D_800484E8.playSeconds = 0;
    D_800484E8.playMinutes = 0;
    D_800484E8.playHours = 0;
    D_800484E8.playFrames = 0;
}

void func_80016BC8(void) {
    if ((D_800484E8.playFrames >> 8) >= 60) {
        D_800484E8.playFrames &= 0xFF;
        if (++D_800484E8.playSeconds >= 60) {
            D_800484E8.playSeconds = 0;
            if (++D_800484E8.playMinutes >= 60) {
                D_800484E8.playMinutes = 0;
                if (++D_800484E8.playHours >= 1000) {
                    D_800484E8.playHours = 999;
                    D_800484E8.playMinutes = 59;
                    D_800484E8.playSeconds = 59;
                    D_800484E8.playTimeMaxed = 1;
                }
            }
        }
    }
}

s32 func_80016C74(u32 index) {
    if (index >= 3) {
        return -1;
    }
    return D_800484E8.records[D_800484E8.unk70[index]].unk4 - 3;
}

void func_80016CC4(s32 slot, u32 stat, s16 value) {
    Unk80048C50 *d = &D_80048C50[slot];
    s16 *p = d->stats;

    if (stat < 19) {
        p += stat;
        *p = value;
        if (value < 0) {
            *p = 0;
            return;
        }
        if (stat < 2) {
            if (value >= 100) {
                *p = 99;
            }
        } else if (stat - 2 < 4) {
            if (value >= 10000) {
                *p = 9999;
            }
        } else if (value >= 1000) {
            *p = 999;
        }
    }
}

void func_80016D64(s32 slot, u32 stat, s32 delta) {
    Unk80048C50 *d = &D_80048C50[slot];
    s16 *stats = d->stats;
    s16 value;

    if (stat < 19) {
        stats += stat;
        value = *stats + delta;
        *stats = value;
        if (value < 0) {
            *stats = 0;
        } else if (stat < 2) {
            if (value >= 100) {
                *stats = 99;
            }
        } else if (stat - 2 < 4) {
            if (value >= 10000) {
                *stats = 9999;
            }
        } else if (value >= 1000) {
            *stats = 999;
        }
    }
}

typedef struct StatBlock {
    s16 v[22];
} StatBlock;

typedef union ItemData {
    struct {
        /* 0x0 */ s16 unk0;
        /* 0x2 */ s16 unk2[2];
        /* 0x6 */ u16 amounts[2];
        /* 0xA */ s16 atk;
        /* 0xC */ u8 stats[2];
    } weapon;
    struct {
        /* 0x0 */ s16 unk0;
        /* 0x2 */ s16 unk2[2];
        /* 0x6 */ u16 amounts[2];
        /* 0xA */ u8 stats[2];
        /* 0xC */ s16 def;
    } armor;
    struct {
        /* 0x0 */ s16 unk0;
        /* 0x2 */ s16 unk2[2];
        /* 0x6 */ u16 amount;
        /* 0x8 */ u8 stat;
    } acc;
} ItemData;

typedef struct Equip4 {
    s16 v[4];
} Equip4;
extern Equip4 D_8004ACE4[];
extern s16 D_8004AD24[][6];

void func_80017214(s16 *p, s32 stat, s32 delta);

void func_80016E10(s32 slot, s16 *out) {
    s16 *equip;
    s32 i;
    s32 j;
    ItemInfo *info;
    ItemData *data;
    u8 type;
    u8 stat;
    s32 amount;

    Unk800484E8 *save = &D_800484E8;
    Unk80048C50 *d;

    *(StatBlock *)out = *(StatBlock *)&save->records[slot].unk28;
    d = &D_80048C50[slot];
    equip = d->equip;
    for (i = 0; i < 6; i++) {
        if (equip[i] > 0) {
            info = D_800427A4(equip[i]);
            type = info->type;
            data = (ItemData *)info->data;
            if ((u8)(type - 2) < 13) {
                out[6] += data->weapon.atk;
                if (out[6] >= 1000) {
                    out[6] = 999;
                }
                for (j = 0; j < 2; j++) {
                    stat = *(j + data->weapon.stats);
                    amount = data->weapon.amounts[j];
                    if (stat != 0) {
                        func_80017214(out, stat, (s16)amount);
                    }
                }
            } else if ((u8)(type - 15) < 6) {
                out[7] += data->armor.def;
                if (out[7] >= 1000) {
                    out[7] = 999;
                }
                for (j = 0; j < 2; j++) {
                    stat = *(j + data->armor.stats);
                    amount = data->armor.amounts[j];
                    if (stat != 0) {
                        func_80017214(out, stat, (s16)amount);
                    }
                }
            } else if ((u8)(type - 21) < 4) {
                stat = data->acc.stat;
                amount = data->acc.amount;
                if (stat != 0) {
                    func_80017214(out, stat, (s16)amount);
                }
            } else {
                continue;
            }
            out[11] += data->weapon.unk0;
            if (out[11] >= 1000) {
                out[11] = 999;
            }
        }
    }
    out[6] -= out[19];
    if (out[6] < 0) {
        out[6] = 0;
    }
    out[7] -= out[20];
    if (out[7] < 0) {
        out[7] = 0;
    }
    out[10] -= out[21];
    if (out[10] < 0) {
        out[10] = 0;
    }
    if (equip[0] == D_8004ACE4[slot].v[0] && equip[1] == D_8004ACE4[slot].v[1] &&
        equip[2] == D_8004ACE4[slot].v[2] && equip[3] == D_8004ACE4[slot].v[3]) {
        for (i = 0; i < 6; i++) {
            out[i + 6] += D_8004AD24[slot][i];
        }
    }
}

void func_80017214(s16 *p, s32 stat, s32 delta) {
    s32 i;
    s16 value;

    if (stat == 7) {
        for (i = 0; i < 6; i++) {
            value = p[i + 6] + delta;
            p[i + 6] = value;
            if (value >= 1000) {
                p[i + 6] = 999;
            }
        }
    } else if (stat - 1 < 6U) {
        value = p[stat + 5] + delta;
        p[stat + 5] = value;
        if (value >= 1000) {
            p[stat + 5] = 999;
        }
    } else if (stat - 8 < 7U) {
        value = p[stat + 4] + delta;
        p[stat + 4] = value;
        if (value >= 1000) {
            p[stat + 4] = 999;
        }
    }
}
