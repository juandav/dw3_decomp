/* The second object of CARDGAME.PRO, from func_800A25E8 to the end of the
   code. The original had two objects: the jump tables of this part are
   aligned to 8 from 0x80083294 (USA), 4 bytes past a multiple of 8, so its
   rodata is a section of its own. Where the first object's code ends is only
   known to be after func_800A1E04, the last function with a jump table before
   it. */

#include "cardgame.h"

s32 func_800A2838(CardBattle *battle, s32 side, s32 mask);
s32 func_800A30FC(CardBattle *battle, s32 side, s32 value, s32 keep);
s32 func_800A322C(CardBattle *battle);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A25E8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A2838);

void func_800A2C94(CardBattle *battle, s32 side) {
    s32 best = 0xFFF;
    s32 bestIndex = 0;
    s8 *flags;
    s32 i;
    s32 value;

    if (side == 1) {
        flags = &battle->unk446[6];
    } else {
        flags = battle->unk446;
    }
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (flags[i] != 0) {
            value = func_800A2838(battle, side, 1 << i);
            if (best >= value) {
                best = value;
                flags[bestIndex] = 0;
                bestIndex = i;
                flags[i] = 1;
            } else {
                flags[i] = 0;
            }
        }
    }
}

s32 func_800A2DA0(CardBattle *battle, s32 side) {
    s32 found = 0;
    s8 *flags;
    s32 i;

    if (side == 1) {
        flags = &battle->unk446[6];
    } else {
        flags = battle->unk446;
    }
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (flags[i] != 0) {
            found = 1;
            battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->players[side].slots[i].order;
            break;
        }
    }
    return found;
}

void func_800A2E4C(CardBattle *battle, s32 side) {
    CardDrawer drawer;
    s8 *flags;
    s32 i;

    initCardDrawer(&drawer);
    flags = battle->unk446;
    if (side == 1) {
        flags = &battle->unk446[6];
    }
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (flags[i] != 0) {
            drawer.setCard(battle->cards[battle->players[side].slots[i].card] + 1);
            if (drawer.card[0] != 3) {
                flags[i] = 0;
            }
        }
    }
    func_800A2DA0(battle, side);
}

void func_800A2F7C(CardBattle *battle, s32 side) {
    CardDrawer drawer;
    s8 *flags;
    s32 i;

    initCardDrawer(&drawer);
    flags = battle->unk446;
    if (side == 1) {
        flags = &battle->unk446[6];
    }
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (flags[i] != 0) {
            drawer.setCard(battle->cards[battle->players[side].slots[i].card] + 1);
            if (drawer.card[0] != 4) {
                flags[i] = 0;
            }
        }
    }
    func_800A2DA0(battle, side);
}

s32 func_800A30AC(CardBattle *battle, s32 side, s32 index, s32 value) {
    s32 result = 0;

    if (*(index + battle->unk446) != 0) {
        result = value >= battle->players[side].slots[index].unk8;
    }
    return result;
}

s32 func_800A30FC(CardBattle *battle, s32 side, s32 value, s32 keep) {
    s32 result = 0;
    s32 last = 0;
    s8 *flags;
    s32 i;
    s32 any;

    if (side == 1) {
        flags = &battle->unk446[6];
    } else {
        flags = battle->unk446;
    }
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (flags[i] != 0) {
            last = i;
            if (value < battle->players[side].slots[i].unk8) {
                flags[i] = 0;
            }
        }
    }
    any = 0;
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (flags[i] != 0) {
            any = 1;
            break;
        }
    }
    if (!any) {
        if (keep == 0) {
            flags[last] = 1;
        }
        result = 1;
    }
    return result;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A322C);

s32 func_800A3344(CardBattle *battle, s32 id) {
    s32 value = 0;

    switch (id) {
    case 0x12:
        value = 60;
        break;
    case 0x14:
        value = 15;
        break;
    case 0x38:
        value = 10;
        break;
    case 0x15:
    case 0x2E:
        value = 30;
        break;
    }
    return value;
}

s32 func_800A3398(CardBattle *battle, s32 id) {
    s32 value = 0;

    switch (id) {
    case 2:
        value = 15;
        break;
    case 12:
        value = 50;
        break;
    case 15:
        value = 20;
        break;
    case 3:
    case 40:
        value = 30;
        break;
    case 58:
        value = 10;
        break;
    }
    return value;
}

s32 func_800A33F4(CardBattle *battle, s32 arg1, s32 id) {
    s32 done = 0;

    switch (id) {
    case 0x27:
        if (func_800A322C(battle)) {
            done = 1;
        }
        break;
    case 0x07:
    case 0x09:
    case 0x1A:
    case 0x37:
    case 0x39:
        func_800A2C94(battle, 0);
        if (func_800A2DA0(battle, 0)) {
            done = 1;
        }
        break;
    case 0x15:
    case 0x2E:
        func_800A30FC(battle, 0, 30, 0);
        func_800A2C94(battle, 0);
        if (func_800A2DA0(battle, 0)) {
            done = 1;
        }
        break;
    case 0x38:
        func_800A30FC(battle, 0, 10, 0);
        func_800A2C94(battle, 0);
        if (func_800A2DA0(battle, 0)) {
            done = 1;
        }
        break;
    case 0x28:
        if (func_800A2DA0(battle, 1)) {
            done = 1;
        }
        break;
    case 0x03:
    case 0x0F:
    case 0x3A:
    case 0x3B:
        if (battle->players[1].slotCount != 0) {
            battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->players[1].slots[0].order;
            done = 1;
        }
        break;
    default:
        done = 1;
        break;
    }
    return done;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A34FC);

s32 func_800A3828(CardBattle *battle, s32 kind) {
    s32 i;

    for (i = 0; i < battle->sides[1].pile.unkA; i++) {
        if (battle->unk35C[battle->sides[1].pile.unk64[i] - 40].unk0 == kind) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A387C);
