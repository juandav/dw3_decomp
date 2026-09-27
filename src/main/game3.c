#include "game.h"

s32 testBit(u8 *bits, s32 index, s32 set) {
    s32 byte = index >> 3;
    s32 mask = 1 << (index & 7);

    if (set != 0) {
        return (bits[byte] & mask) != 0;
    }
    return (bits[byte] & mask) == 0;
}

void setBit(u8 *bits, s32 index, s32 set) {
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

    if ((GAME.items[7] != 0 || GAME.equippedItems[7] != 0) &&
        (GAME.items[0x59] != 0 || GAME.equippedItems[0x59] != 0) &&
        (GAME.items[0xA7] != 0 || GAME.equippedItems[0xA7] != 0)) {
        ret = 1;
    }
    return ret;
}

s32 checkPartner(u32 op, s32 arg) {
    s32 result = 0;
    s32 i;
    s32 total;
    s32 id;

    switch (op) {
    case 0:
        if (PARTY_SET == arg) {
            result = 1;
        }
        break;
    case 1:
        if (GAME.partners[arg].unlocked != 0) {
            result = 1;
        }
        break;
    case 2:
        for (i = 0; i < 3; i++) {
            if (GAME.funcs.getPartyMember(i) == arg) {
                result = 1;
                break;
            }
        }
        break;
    case 3:
        GAME.partners[arg].unlocked = arg + 3;
        result = 1;
        break;
    case 4:
        if (GAME.partners[arg].unlocked != 0 && GAME.partners[arg].level >= 0x2D) {
            result = 1;
        }
        break;
    case 5:
        total = 0;
        for (i = 0; i < 3; i++) {
            id = GAME.funcs.getPartyMember(i);
            if (id >= 0) {
                total += GAME.funcs.getPartnerStats(id)->level;
            }
        }
        if (total >= arg * 15 + 30) {
            result = 1;
        }
        break;
    case 6:
        if (GAME.partners[arg].unlocked == 0) {
            result = 1;
        }
        break;
    }
    return result;
}

s32 checkMoney(s32 op, s32 item) {
    s32 ret = 0;

    switch (op) {
    case 0:
        if (MONEY_REQUIRED[item] <= GAME.money) {
            ret = 1;
        }
        break;
    case 1:
        GAME.money += MONEY_GAINS[item];
        if (GAME.money > 9999999) {
            GAME.money = 9999999;
        }
        break;
    case 2:
        GAME.money -= MONEY_LOSSES[item];
        if (GAME.money < 0) {
            GAME.money = 0;
        }
        break;
    }
    return ret;
}

s32 checkProgressRange(s32 unused, s32 index) {
    s32 value = GAME_PROGRESS;
    s32 min = PROGRESS_RANGES[index][0];
    s32 max = PROGRESS_RANGES[index][1];
    s32 ret = 0;

    if (value >= min) {
        ret = max >= value;
    }
    return ret;
}

s32 checkFlagCount(s32 unused, s32 mode) {
    s32 ret = 0;
    s32 on = 0;
    s32 off = 0;
    s32 i;

    for (i = 0x27; i < 0x2E; i++) {
        if (testBit(FLAGS_1C, i, 1) != 0) {
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
    Task *obj = TASK_FUNCS.find(0x16, -1, -1);

    obj->setSubstate(obj, 3);
    return 1;
}

s32 checkSpecialCondition(s32 id, s32 expected) {
    u8 *p;
    s32 result = 0;
    s32 op;
    s32 arg;

    for (p = SPECIAL_CONDITIONS; *p != 0xFF; p += 3) {
        if (*p == id) {
            op = p[1] & 0xF;
            arg = p[2];
            switch (p[1] & 0xF0) {
            case 0x00:
                result = func_80015584(op, arg);
                break;
            case 0x10:
                result = checkPartner(op, arg);
                break;
            case 0x20:
                result = checkMoney(op, arg);
                break;
            case 0x30:
                result = checkProgressRange(op, arg);
                break;
            case 0x40:
                result = checkFlagCount(op, arg);
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

s32 checkProgress(s32 value, s32 mode) {
    if (mode != 0) {
        if (GAME_PROGRESS == value) {
            return 1;
        }
    } else {
        if (GAME_PROGRESS != value) {
            return 1;
        }
    }
    return 0;
}

s32 checkItem(s32 index, s32 mode) {
    if (mode != 0) {
        if (GAME.items[index] != 0 || GAME.equippedItems[index] != 0) {
            return 1;
        }
    } else {
        if (GAME.items[index] == 0 && GAME.equippedItems[index] == 0) {
            return 1;
        }
    }
    return 0;
}

s32 checkCard(s32 item, s32 have) {
    if (have != 0) {
        if (GAME.cards[item] != 0) {
            return 1;
        }
    } else {
        if (GAME.cards[item] == 0) {
            return 1;
        }
    }
    return 0;
}

extern s32 PARTY_STAT_THRESHOLDS[];

s32 checkPartyStat(s32 index, s32 mode) {
    PartnerTotals buf;
    s32 total = 0;
    s32 i;
    s32 id;

    for (i = 0; i < 3; i++) {
        id = GAME.funcs.getPartyMember(i);
        if (id >= 0) {
            GAME.funcs.computeStats(id, &buf);
            total += buf.stats[11];
        }
    }
    if (mode != 0) {
        if (total >= PARTY_STAT_THRESHOLDS[index]) {
            return 1;
        }
    } else {
        if (total < PARTY_STAT_THRESHOLDS[index]) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015D90(s32 id, s32 arg1) {
    if (id < 30) {
        if (GAME.unk44 == id + 1) {
            return 1;
        }
    } else {
        if (GAME.unk46 == id - 29) {
            return 1;
        }
    }
    return 0;
}

s32 unequipItem(s32 partner, s32 item) {
    PartnerStats *d = &PARTNER_STATS[partner];
    u8 *info = GET_ITEM(item)->data;
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

void changeItem(s32 item, s32 add) {
    s32 i;

    if (add != 0) {
        if (++GAME.items[item] >= 100) {
            GAME.items[item] = 99;
        }
    } else if (GAME.items[item] != 0) {
        if (--GAME.items[item] < 0) {
            GAME.items[item] = 0;
        }
    } else if (GAME.equippedItems[item] != 0) {
        for (i = 0; i < 3; i++) {
            if (unequipItem(GAME.funcs.getPartyMember(i), item) != 0) {
                goto found;
            }
        }
        for (i = 0; i < 8; i++) {
            if (GAME.partners[i].unlocked >= 3 && unequipItem(i, item) != 0) {
                break;
            }
        }
    found:
        GAME.equippedItems[item]--;
    }
}

void changeCard(s32 card, s32 add) {
    if (add != 0) {
        GAME_FUNCS.addCards(card, 1);
        return;
    }
    GAME.cards[card]--;
    if (GAME.cards[card] < 0) {
        GAME.cards[card] = 0;
    }
}

void func_8001602C(s32 arg0, s32 arg1) {
    func_8008AEB4(0x700, arg0 * 2 + arg1 + 1, 0, 0, 0);
}

/*
 * Event scripts test conditions and run actions given as (code, value)
 * pairs. code >> 9 picks the kind, code & 0x1FF the flag or item:
 *   groups 0x00-0x40 (code >> 8 & ~1): flag bitsets FLAGS_00..FLAGS_40
 *   0x60 GAME_PROGRESS, 0x70 SPECIAL_CONDITIONS, 0x72 party stat totals,
 *   0x80-0x8E items, 0x92 cards. A condition holds when it equals value.
 */
s32 checkCondition(u16 code, u16 value) {
    u16 group = (code >> 8) & 0xFE;
    s32 id = code & 0x1FF;
    u16 arg = value;

    if (group == 0x00) {
        return testBit(FLAGS_00, id, arg);
    } else if (group == 0x02) {
        return testBit(FLAGS_02, id, arg);
    } else if (group == 0x04) {
        return testBit(FLAGS_04, id, arg);
    } else if (group == 0x06) {
        return testBit(FLAGS_06, id, arg);
    } else if (group == 0x08) {
        return testBit(FLAGS_08, id, arg);
    } else if (group == 0x0A) {
        return testBit(FLAGS_0A, id, arg);
    } else if (group == 0x0C) {
        return testBit(FLAGS_0C, id, arg);
    } else if (group == 0x0E) {
        return testBit(FLAGS_0E, id, arg);
    } else if (group == 0x10) {
        return testBit(FLAGS_10, id, arg);
    } else if (group == 0x18) {
        return testBit(FLAGS_18, id, arg);
    } else if (group == 0x1A) {
        return testBit(FLAGS_1A, id, arg);
    } else if (group == 0x1C) {
        return testBit(FLAGS_1C, id, arg);
    } else if (group == 0x20) {
        return testBit(FLAGS_20, id, arg);
    } else if (group == 0x40) {
        return testBit(FLAGS_40, id, arg);
    } else if (group == 0x60) {
        return checkProgress(id, arg);
    } else if (group == 0x70) {
        return checkSpecialCondition(id, arg);
    } else if (group == 0x72) {
        return checkPartyStat(id, arg);
    } else if (group == 0x7E) {
        return func_80015D90(id, arg);
    } else if (group >= 0x80 && group < 0x8F) {
        return checkItem(id, arg);
    } else if (group == 0x92) {
        return checkCard(id, arg);
    }
    return 1;
}

extern void (*D_8009A6EC)(s32 id);
void func_8008B2C4(s32 id);
void func_8008B320(void);

/*
 * Actions: the same flag groups (set to value), 0x70 special actions, 0x74
 * an overlay hook, 0x76/0x78, 0x7A, 0x7C, 0x94 mode changes through the
 * overlay (0x8008AEB4), 0x80-0x8E give/take an item, 0x92 a card.
 */
void applyAction(s32 code, s32 value) {
    u16 group = (code >> 8) & ~1;
    s32 id = code & 0x1FF;

    if (group == 0x00) {
        setBit(FLAGS_00, id, value);
    }
    if (group == 0x02) {
        setBit(FLAGS_02, id, value);
    }
    if (group == 0x04) {
        setBit(FLAGS_04, id, value);
    }
    if (group == 0x06) {
        setBit(FLAGS_06, id, value);
    }
    if (group == 0x08) {
        setBit(FLAGS_08, id, value);
    }
    if (group == 0x0A) {
        setBit(FLAGS_0A, id, value);
    }
    if (group == 0x0C) {
        setBit(FLAGS_0C, id, value);
    }
    if (group == 0x0E) {
        setBit(FLAGS_0E, id, value);
    }
    if (group == 0x10) {
        setBit(FLAGS_10, id, value);
    }
    if (group == 0x18) {
        setBit(FLAGS_18, id, value);
    }
    if (group == 0x1A) {
        setBit(FLAGS_1A, id, value);
    }
    if (group == 0x1C) {
        setBit(FLAGS_1C, id, value);
    }
    if (group == 0x20) {
        setBit(FLAGS_20, id, value);
    }
    if (group == 0x40) {
        setBit(FLAGS_40, id, value);
    }
    if (group == 0x70) {
        checkSpecialCondition(id, 1);
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
        changeItem(id, value);
    }
    if (group == 0x90) {
        func_8008B2C4(id);
    }
    if (group == 0x92) {
        changeCard(id, value);
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

/* All the (code, value) pairs until 0xFFFF must hold */
s32 checkConditions(u16 *list) {
    u16 a;

    for (a = *list; a != 0xFFFF; a = *list) {
        list++;
        if (!checkCondition(a, *list++)) {
            return 0;
        }
    }
    return 1;
}

void applyActions(u16 *list) {
    u16 a;

    for (a = *list; a != 0xFFFF; a = *list) {
        list++;
        applyAction(a, *list++);
    }
}

void updateModeFlags(void) {
    s32 i;
    u8 *p;

    if (GAME_CLEAR_TEMP_FLAGS != 0) {
        for (i = 2, p = &FLAGS_00[i]; i >= 0; i--) {
            *p-- = 0;
        }
        applyAction(0x12, 0);
    }
    if (GAME_FUNCS.getPrevMode() == 0x700) {
        applyAction(0x11, 1);
        applyAction(0x12, 1);
        if (PENDING_FLAG_10 != 0) {
            applyAction(0x10, 1);
        } else {
            applyAction(0x10, 0);
        }
        PENDING_FLAG_10 = 0;
    }
}

/* Clears the save data and sets up a new game */
void newGame(void) {
    HEAP.zero(&GAME, 0x26BC);
    GAME.mode = 0xE01;
    GAME.nextMode = 0xE01;
    GAME.unk4 = 1;
    GAME.unk26CC = 1;
    GAME.unk26CD = 8;
    GAME.unk26CF = 60;
    GAME.modeArg = 0;
    GAME.unk26CE = 0;
    GAME.unkC = -1;
    initNewGameData();
    GAME.unk30 = (RANDOM.next() & 0x1FF) + 0x200;
}

/* Makes the requested mode current (main calls it before recreating the mode task) */
void commitMode(void) {
    s32 prev;

    if (GAME.nextMode != 0) {
        prev = GAME.mode;
        GAME.mode = GAME.nextMode;
        GAME.nextMode = 0;
        GAME.prevMode = prev;
    }
}

s32 getPrevMode(void) {
    return GAME_PREV_MODE;
}

s32 getMode(void) {
    return GAME_MODE;
}

s32 getModeArg(void) {
    return GAME_MODE_ARG;
}

void requestMode(s32 mode, s32 arg) {
    GAME.nextMode = mode;
    GAME.modeArg = arg;
}

s32 isModeChangePending(void) {
    return GAME_NEXT_MODE != 0;
}

void initNewGameData(void) {
    TextTools cls;
    s32 i;
    s32 j;
    u16 *dst;
    u16 *src;
    DigimonData *e;

    initTextTools(&cls);
    strcpy(GAME.name, cls.getString(FILE_CACHE.load(0x87), 0xB));
    GAME.party[0] = -1;
    GAME.party[1] = -1;
    GAME.party[2] = -1;
    for (j = 0; j < 3; j++) {
        strcpy(GAME.decks[j].name, cls.getString(FILE_CACHE.load(0x33), j + 0x16));
    }
    GAME.funcs.giveStarterDeck();
    for (i = 0; i < 8; i++) {
        e = &DIGIMON_DATA[i];
        strcpy(GAME.partners[i].name, cls.getString(FILE_CACHE.load(0x4F), e->nameId));
        GAME.partners[i].level = 1;
        GAME.partners[i].hp = GAME.partners[i].maxHp = e->hp;
        GAME.partners[i].mp = GAME.partners[i].maxMp = e->mp;
        /* battleStats, reached from the name like the ROM does */
        dst = (u16 *)(GAME.partners[i].name + 0x28);
        src = e->battleStats;
        for (j = 0; j < 6; j++) {
            *dst++ = *src++;
        }
        src = e->resistances;
        for (j = 0; j < 7; j++) {
            *dst++ = *src++;
        }
    }
}

s32 getPartyMember(u32 index) {
    if (index >= 3) {
        return -1;
    }
    return GAME.party[index];
}

void setParty(s32 set) {
    s32 i;
    u8 partner;

    for (i = 0; i < 3; i++) {
        partner = STARTER_PARTIES[set][i];
        GAME.party[i] = partner;
        GAME.partners[partner].unlocked = partner + 3;
    }
    PARTY_SET = set;
}

void addCards(s32 item, s32 count) {
    GAME.cardsSeen[item] = 1;
    GAME.cards[item] += count;
    if (GAME.cards[item] >= 10) {
        GAME.cards[item] = 9;
    }
}

void giveStarterDeck(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        addCards(STARTER_DECK[i], 1);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 40; i++) {
            GAME.decks[j].cards[i] = STARTER_DECK[i];
        }
    }
}

void resetPlayTime(void) {
    GAME.playTimeMaxed = 0;
    GAME.playSeconds = 0;
    GAME.playMinutes = 0;
    GAME.playHours = 0;
    GAME.playFrames = 0;
}

void updatePlayTime(void) {
    if ((GAME.playFrames >> 8) >= 60) {
        GAME.playFrames &= 0xFF;
        if (++GAME.playSeconds >= 60) {
            GAME.playSeconds = 0;
            if (++GAME.playMinutes >= 60) {
                GAME.playMinutes = 0;
                if (++GAME.playHours >= 1000) {
                    GAME.playHours = 999;
                    GAME.playMinutes = 59;
                    GAME.playSeconds = 59;
                    GAME.playTimeMaxed = 1;
                }
            }
        }
    }
}

s32 getPartyPartner(u32 index) {
    if (index >= 3) {
        return -1;
    }
    return GAME.partners[GAME.party[index]].unlocked - 3;
}

void setStat(s32 partner, u32 stat, s16 value) {
    PartnerStats *d = &PARTNER_STATS[partner];
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

void addStat(s32 partner, u32 stat, s32 delta) {
    PartnerStats *d = &PARTNER_STATS[partner];
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
extern Equip4 EQUIP_SETS[];
extern s16 EQUIP_SET_BONUSES[][6];

void addStatBonus(s16 *p, s32 stat, s32 delta);

/* A partner's stats with its equipment (and its equipment set bonus) added */
void computeStats(s32 partner, s16 *out) {
    s16 *equip;
    s32 i;
    s32 j;
    ItemInfo *info;
    ItemData *data;
    u8 type;
    u8 stat;
    s32 amount;

    GameState *save = &GAME;
    PartnerStats *d;

    *(StatBlock *)out = *(StatBlock *)&save->partners[partner].level;
    d = &PARTNER_STATS[partner];
    equip = d->equip;
    for (i = 0; i < 6; i++) {
        if (equip[i] > 0) {
            info = GET_ITEM(equip[i]);
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
                        addStatBonus(out, stat, (s16)amount);
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
                        addStatBonus(out, stat, (s16)amount);
                    }
                }
            } else if ((u8)(type - 21) < 4) {
                stat = data->acc.stat;
                amount = data->acc.amount;
                if (stat != 0) {
                    addStatBonus(out, stat, (s16)amount);
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
    if (equip[0] == EQUIP_SETS[partner].v[0] && equip[1] == EQUIP_SETS[partner].v[1] &&
        equip[2] == EQUIP_SETS[partner].v[2] && equip[3] == EQUIP_SETS[partner].v[3]) {
        for (i = 0; i < 6; i++) {
            out[i + 6] += EQUIP_SET_BONUSES[partner][i];
        }
    }
}

void addStatBonus(s16 *p, s32 stat, s32 delta) {
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
