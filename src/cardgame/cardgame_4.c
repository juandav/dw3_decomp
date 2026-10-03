/* The fourth object of CARDGAME.PRO (see cardgame.c), from CARDGAME_checkComputerCondition
   (USA): its rodata starts at 0x80083294, 4 bytes past a multiple of 8. */

#include "cardgame.h"

/* Checks the condition id (0x70 to 0x96) of a card for the computer; returns 1 if it holds */
s32 CARDGAME_checkComputerCondition(CardBattle *battle, CardScreen *screen, s32 id) {
    CardDrawer drawer;
    s32 result = 0;
    s32 card;

    switch (id) {
    case 0x70:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7B:
    case 0x7C:
    case 0x7D:
    case 0x7E:
        result = 1;
        break;
    case 0x80:
    case 0x81:
        if (CARDGAME_markPileCardsByColor(battle, screen, 1, 4, 0xFF)) {
            result = 1;
        }
        break;
    case 0x83:
        if (battle->unk560.unk15 != 0) {
            result = 1;
        }
        break;
    case 0x84:
        if (battle->unk560.unk15 != 0) {
            card = battle->unk560.unk20[battle->unk560.unk15 - 1].unk0;
            initCardDrawer(&drawer);
            drawer.setCard(battle->cards[card] + 1);
            if (drawer.card[0] == 6) {
                result = 1;
            }
        }
        break;
    case 0x72:
        if (CARDGAME_markPileCardsByColor(battle, screen, 0, 3, 0xFF)) {
            result = 1;
        }
        break;
    case 0x82:
        if (CARDGAME_markPileCardsByColor(battle, screen, 1, 3, 0xFF)) {
            result = 1;
        }
        break;
    case 0x71:
        if (CARDGAME_markPileCardsByColor(battle, screen, 1, 2, 0xFF)) {
            result = 1;
        }
        break;
    case 0x7F:
        if (CARDGAME_markPileCardsByColor(battle, screen, 0, 2, 0xFF)) {
            result = 1;
        }
        break;
    case 0x96:
        if (CARDGAME_markPileCardsByColor(battle, screen, 1, 2, 0xFD)) {
            result = 1;
        }
        break;
    case 0x85:
    case 0x8E:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x1FC)) {
            result = 1;
        }
        break;
    case 0x87:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x180)) {
            result = 1;
        }
        break;
    case 0x88:
    case 0x8F:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x2FC)) {
            result = 1;
        }
        break;
    case 0x89:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x2BC)) {
            result = 1;
        }
        break;
    case 0x8A:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x280)) {
            result = 1;
        }
        break;
    case 0x8B:
    case 0x90:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x3FC)) {
            result = 1;
        }
        break;
    case 0x8C:
    case 0x95:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x380)) {
            result = 1;
        }
        break;
    case 0x91:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x3F8)) {
            result = 1;
        }
        break;
    case 0x92:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x3F4)) {
            result = 1;
        }
        break;
    case 0x93:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x310)) {
            result = 1;
        }
        break;
    case 0x94:
        if (CARDGAME_markSlotsByColor(battle, screen, 1, 0x3DC)) {
            result = 1;
        }
        break;
    }
    return result;
}

/* Scores the cards in a side's slots, counting runs of the same card */
s32 CARDGAME_scoreHand(CardBattle *battle, s32 side, s32 mask) {
    CardSortEntry entries[6];
    CardSortEntry tmp;
    CardDrawer drawer;
    s32 count;
    s32 total6;
    s32 total8;
    s32 rest6;
    s32 rest8;
    s32 sum6;
    s32 sum8;
    s32 skip;
    s32 i;
    s32 j;

    total6 = 0;
    rest6 = 0;
    rest8 = 0;
    count = battle->players[side].slotCount;
    initCardDrawer(&drawer);
    total8 = 0;
    for (i = 0; i < count; i++) {
        entries[i].card = battle->cards[battle->players[side].slots[i].card];
        entries[i].slot = i;
    }
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (entries[i].card > entries[j].card) {
                tmp = entries[i];
                entries[i] = entries[j];
                entries[j] = tmp;
            }
        }
    }
    j = 0;
    i = (mask >> entries[0].slot) & 1;
    sum6 = battle->players[side].slots[entries[0].slot].unk6;
    sum8 = battle->players[side].slots[entries[0].slot].unk8;
    for (skip = 0; i < count - 1; i++, skip = 0) {
        drawer.setCard(entries[i].card + 1);
        if ((mask >> entries[i + 1].slot) & 1) {
            if (i == count - 2) {
                break;
            }
            skip = 1;
        }
        if (((CardImageHeader *)drawer.card)->unkA != 0 && entries[i].card == entries[i + 1 + skip].card) {
            j++;
            sum6 += battle->players[side].slots[entries[i + skip].slot].unk6;
            sum8 += battle->players[side].slots[entries[i + skip].slot].unk8;
        } else if (j < 2) {
            j = 0;
            if (i + 1 + skip < count) {
                sum6 = battle->players[side].slots[entries[i + 1 + skip].slot].unk6;
                sum8 = battle->players[side].slots[entries[i + 1 + skip].slot].unk8;
            } else {
                sum6 = 0;
                sum8 = 0;
            }
        } else {
            total6 += sum6;
            total8 += sum8;
            if (i + 1 + skip < count) {
                sum6 = battle->players[side].slots[entries[i + 1 + skip].slot].unk6;
                sum8 = battle->players[side].slots[entries[i + 1 + skip].slot].unk8;
            } else {
                sum6 = 0;
                sum8 = 0;
            }
            if (j >= 3) {
                total6 += 20;
                total8 += 20;
                j = 0;
                break;
            }
            j = 0;
        }
        if (skip) {
            i++;
        }
    }
    if (j >= 2) {
        total6 += sum6;
        total8 += sum8;
        if (j >= 3) {
            total6 += 20;
            total8 += 20;
        }
    }
    for (i = 0; i < count; i++) {
        if (!((mask >> i) & 1)) {
            rest6 += battle->players[side].slots[i].unk6;
            rest8 += battle->players[side].slots[i].unk8;
        }
    }
    return rest6 + rest8 + total6 + total8;
}

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
            value = CARDGAME_scoreHand(battle, side, 1 << i);
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

s32 func_800A2E4C(CardBattle *battle, s32 side) {
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
    return func_800A2DA0(battle, side);
}

s32 func_800A2F7C(CardBattle *battle, s32 side) {
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
    return func_800A2DA0(battle, side);
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

/* Picks the opponent's flagged card with the lowest header value unk8; 1 if
   there is one */
s32 func_800A322C(CardBattle *battle) {
    CardDrawer drawer;
    s32 lowest = 500;
    s32 best = lowest;
    s8 *flags = battle->unk446;
    s32 found;
    s32 i;

    found = 0;
    initCardDrawer(&drawer);
    for (i = 0; i < battle->sides[1].pile.unkA; i++) {
        if (flags[i] != 0) {
            drawer.setCard(battle->cards[battle->sides[1].pile.unk64[i]] + 1);
            found = 1;
            if (((CardImageHeader *)drawer.card)->unk8 < lowest) {
                lowest = ((CardImageHeader *)drawer.card)->unk8;
                best = i;
            }
        }
    }
    if (found == 1) {
        battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->sides[1].pile.unk64[best];
    }
    return found;
}

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

s32 func_800A33F4(CardBattle *battle, CardScreen *screen, s32 id) {
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

/* Compares two cards by the rule of the current record entry; returns 1 if the second one wins */
s32 CARDGAME_compareCards(CardBattle *battle, s32 id1, s32 id2, s32 flip) {
    s32 index = 0;
    s32 result = 0;
    s32 value;
    s32 bonus;
    s32 i;

    if (flip == 0) {
        value = func_800A3344(battle, id2);
        bonus = func_800A3398(battle, id1);
    } else {
        value = func_800A3344(battle, id1);
        bonus = func_800A3398(battle, id2);
    }
    switch (battle->unk560.unk20[battle->unk560.unk15 - 1].unk5) {
    case 0:
        for (i = 0; i < 12; i++) {
            if (i < 6) {
                if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk6 == battle->players[0].slots[i].order) {
                    index = i;
                    break;
                }
            } else {
                if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk6 == battle->players[1].slots[i - 6].order) {
                    index = i - 6;
                    break;
                }
            }
        }
        if (flip == 0) {
            if (func_800A30AC(battle, 0, index, value)) {
                result = 1;
                battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->players[0].slots[index].order;
            }
        } else {
            if (func_800A30AC(battle, 1, index, value) && !func_800A30AC(battle, 1, index, value - bonus)) {
                result = 1;
                battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->players[1].slots[index].order;
            }
        }
        break;
    case 1:
        if (flip == 0) {
            func_800A30FC(battle, 0, value, 0);
            func_800A2C94(battle, 0);
            if (func_800A2DA0(battle, 0)) {
                result = 1;
            }
        }
        break;
    case 3:
        if (flip == 0) {
            func_800A30FC(battle, 0, value, 0);
            func_800A2C94(battle, 0);
            if (func_800A2DA0(battle, 0)) {
                result = 1;
            }
        } else {
            if (func_800A30FC(battle, 1, value, 0) && func_800A2DA0(battle, 1)) {
                result = 1;
            }
        }
        break;
    case 6:
        if (flip == 0) {
            func_800A30FC(battle, 0, value, 0);
            func_800A2C94(battle, 0);
            if (func_800A2E4C(battle, 0)) {
                result = 1;
            }
        }
        break;
    case 7:
        if (flip != 0) {
            func_800A2C94(battle, 1);
            if (func_800A30FC(battle, 1, value, 0) && func_800A2F7C(battle, 1)) {
                result = 1;
            }
        }
        break;
    }
    return result;
}

s32 func_800A3828(CardBattle *battle, s32 kind) {
    s32 i;

    for (i = 0; i < battle->sides[1].pile.unkA; i++) {
        if (battle->unk35C[battle->sides[1].pile.unk64[i] - 40].unk0 == kind) {
            break;
        }
    }
    return i;
}

/* Picks the computer's next card, flagging it in unk46F; returns 1 if one was found */
s32 CARDGAME_pickComputerCard(CardBattle *battle, CardScreen *screen) {
    CardDrawer drawer;
    s32 found = 0;
    CardImageHeader *prevCard;
    CardImageHeader *header;
    s32 prev;
    s32 listed;
    s32 kind;
    s32 flip;
    s32 start;
    s32 index;
    s16 card;
    s32 playerScore;
    s32 computerScore;
    s32 i;

    for (i = 0; i < battle->sides[1].pile.unkA; i++) {
        battle->unk46F[i] = 0;
    }
    if (battle->unk560.unk15 == 0) {
        if (battle->unk2F8 == 5) {
            start = func_800A3828(battle, 1);
            kind = 1;
        } else {
            start = func_800A3828(battle, 3);
            playerScore = CARDGAME_scoreHand(battle, 0, 0);
            computerScore = CARDGAME_scoreHand(battle, 1, 0);
            kind = 3;
            if ((battle->unk305 & 1) || playerScore < computerScore) {
                return 0;
            }
        }
        for (i = start; i < battle->sides[1].pile.unkA; i++) {
            index = battle->sides[1].pile.unk64[i];
            if (battle->unk35C[index - 40].unk0 == kind && func_800856C8(battle, index)) {
                card = battle->cards[index];
                if (CARDGAME_checkComputerCondition(battle, screen, func_800835C4(card, 0, 0)) && func_800A33F4(battle, screen, card)) {
                    battle->unk46F[i] = 1;
                    found = 1;
                    break;
                }
            }
        }
    } else {
        listed = 0;
        for (i = 0; battle->unk400[i] != 0xFF; i++) {
            if (battle->unk400[i] == battle->cards[battle->unk560.unk20[battle->unk560.unk15 - 1].unk0]) {
                listed = 1;
                break;
            }
        }
        if (listed) {
            for (i = func_800A3828(battle, 4); i < battle->sides[1].pile.unkA; i++) {
                index = battle->sides[1].pile.unk64[i];
                if (func_800856C8(battle, index)) {
                    card = battle->cards[index];
                    if (CARDGAME_checkComputerCondition(battle, screen, func_800835C4(card, 0, 0)) && func_800A33F4(battle, screen, card)) {
                        battle->unk46F[i] = 1;
                        found = 1;
                        break;
                    }
                }
            }
        }
        if (found == 0) {
            initCardDrawer(&drawer);
            prev = battle->unk560.unk20[battle->unk560.unk15 - 1].unk0;
            drawer.setCard(battle->cards[prev] + 1);
            prevCard = (CardImageHeader *)drawer.card;
            if (prevCard->kind == 3 || prevCard->kind == 9) {
                start = func_800A3828(battle, 3);
                kind = 3;
                for (i = start; i < battle->sides[1].pile.unkA; i++) {
                    index = battle->sides[1].pile.unk64[i];
                    if ((battle->unk35C[index - 40].unk0 == kind || battle->unk35C[index - 40].unk0 == 4) && battle->unk35C[index - 40].unk1 != 0) {
                        drawer.setCard(battle->cards[index] + 1);
                        header = (CardImageHeader *)drawer.card;
                        if (prevCard->kind == 3) {
                            if (header->kind != 9) {
                                continue;
                            }
                            flip = 0;
                        } else {
                            if (header->kind != 3) {
                                continue;
                            }
                            flip = 1;
                        }
                        if (func_800856C8(battle, index) && CARDGAME_checkComputerCondition(battle, screen, func_800835C4(battle->cards[index], 0, 0)) && CARDGAME_compareCards(battle, prev, index, flip)) {
                            battle->unk46F[i] = 1;
                            found = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return found;
}
