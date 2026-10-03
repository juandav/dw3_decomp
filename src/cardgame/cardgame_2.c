/* The second object of CARDGAME.PRO, from func_800A25E8 to the end of the
   code. The original had two objects: the jump tables of this part are
   aligned to 8 from 0x80083294 (USA), 4 bytes past a multiple of 8, so its
   rodata is a section of its own. Where the first object's code ends is only
   known to be after func_800A1E04, the last function with a jump table before
   it. */

#include "cardgame.h"

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A25E8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A2838);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A2C94);

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
            battle->sides[0].unk20[battle->sides[0].unk15].unk6 = battle->players[side].slots[i].order;
            break;
        }
    }
    return found;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A2E4C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A2F7C);

s32 func_800A30AC(CardBattle *battle, s32 side, s32 index, s32 value) {
    s32 result = 0;

    if (*(index + battle->unk446) != 0) {
        result = value >= battle->players[side].slots[index].unk8;
    }
    return result;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A30FC);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800A33F4);

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
