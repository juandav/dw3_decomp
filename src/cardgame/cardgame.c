/* The first object of CARDGAME.PRO, from the start of the code to
   CARDGAME_runEffectStep (USA), and the overlay's data. CARDGAME.PRO was four objects:
   each one's jump tables are aligned to 8 from the start of its own rodata,
   and they are 4 bytes past a multiple of 8 from 0x80082A04 (USA) to
   0x80082E30 and from 0x80083294 on. Where each object's code starts is only
   known to be between the function with the last jump table of the object
   before and the one with its first; the data is all here. */

#include "cardgame.h"

s32 func_800835C4(s32 index, u32 field, s32 offset) {
    u8 value = 0;

    switch (field) {
    case 0:
        value = D_800A3CF8[index].unk0;
        break;
    case 1:
        value = D_800A3CF8[index].unk1;
        break;
    case 2:
        value = D_800A3CF8[index].unk2;
        break;
    case 3:
        value = D_800A3CF8[index].unk3;
        break;
    case 4:
        value = D_800A3CF8[index].unk4[offset];
        break;
    }
    return value;
}

void func_800836D8(CardBattle *battle, CardScreen *screen, s32 value, s32 score) {
    if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk4 == value) {
        battle->unk4E0 += score;
    }
}

void func_80083714(CardBattle *battle, s32 side, s32 value, s32 score) {
    if (value >= battle->sides[side].pile.unkA) {
        battle->unk4E0 += score;
    }
}

void func_80083758(CardBattle *battle, s32 side, s32 value, s32 score) {
    if (value < battle->sides[side].pile.unkA) {
        battle->unk4E0 += score;
    }
}

void func_8008379C(CardBattle *battle, s32 side, s32 score) {
    if (battle->sides[side].pile.unk8 > 0) {
        battle->unk4E0 += score;
    }
}

void func_800837DC(CardBattle *battle, s32 side, s32 score) {
    if (battle->players[side].slotCount < 6) {
        battle->unk4E0 += score;
    }
}

s32 func_80083820(CardBattle *battle, CardScreen *screen) {
    battle->unk424 -= GFX.funcs.getFrameTime();
    return battle->unk424 <= 0;
}

void func_80083860(CardBattle *battle, CardScreen *screen, s32 which) {
    if (which == 0) {
        battle->unk440 = battle->sides[0].pile.unk4;
    } else {
        battle->unk440 = battle->unk41C;
    }
}

void func_80083880(CardBattle *battle, CardScreen *screen) {
    s32 entry = battle->unk560.unk15 - 1;
    CardSlot *slot;
    s32 i;

    for (i = 0; i < 12; i++) {
        battle->unk46F[i] = 0;
        if (i < 6) {
            if (i >= battle->players[0].slotCount) {
                continue;
            }
            slot = &battle->players[0].slots[i];
        } else {
            if (i - 6 >= battle->players[1].slotCount) {
                continue;
            }
            slot = &battle->players[1].slots[i - 6];
        }
        if (slot->order == battle->unk560.unk20[entry].unk6) {
            battle->unk46F[i] = 1;
        }
    }
}

void func_80083918(CardBattle *battle) {
    s32 best = 0;
    s32 bestIndex = 6;
    s32 value;
    s32 i;

    for (i = 0; i < 12; i++) {
        battle->unk46F[i] = 0;
        if (i >= 6) {
            value = battle->unk820(battle, 1, 1 << (i - 6));
            if (best < value) {
                best = value;
                battle->unk46F[bestIndex] = 0;
                bestIndex = i;
                battle->unk440 = i;
                battle->unk46F[i] = 1;
            }
        }
    }
}

s32 func_800839CC(CardBattle *battle, CardScreen *screen) {
    u8 a = 0;
    u8 b = 0;
    s32 state;

    switch (battle->unk420) {
    case 30:
    case 36:
        b = 0;
        break;
    case 31:
    case 37:
        b = 1;
        break;
    case 32:
    case 33:
    case 38:
        b = 2;
        break;
    case 34:
    case 39:
        b = 3;
        break;
    case 35:
    case 40:
        b = 4;
        break;
    }
    state = battle->unk420;
    if (state >= 30) {
        if (state < 36) {
            a = battle->unk560.unk20[battle->unk560.unk15 - 1].unk4;
        } else if (state < 41) {
            a = battle->unk560.unk20[battle->unk560.unk15 - 1].unk4 ^ 1;
        }
    }
    return CARDGAME_stepColorValue(battle, screen, a, b);
}

/* Starts the effect step battle->unk421 asks for, then runs the current one (battle->unk420) */
void CARDGAME_runEffectStep(CardBattle *battle, CardScreen *screen) {
    CardDrawer drawer;
    s32 side = battle->unk560.unk20[battle->unk560.unk15 - 1].unk4;
    s32 nextSide = battle->unk560.unk20[battle->unk560.unk15].unk4;
    s32 other = side ^ 1;
    s32 count;
    s32 result;
    s32 i;
    s32 j;
    s32 index;

    if (battle->unk421 != 0) {
        switch (battle->unk421) {
        case 1:
            battle->unk424 = 45;
            break;
        case 18:
            func_800918A0(battle, screen, 0);
            break;
        case 19:
            func_800918A0(battle, screen, 1);
            break;
        case 20:
            func_80091E60(battle, screen);
            break;
        case 27:
            func_80092E1C(battle, screen);
            break;
        case 21:
            func_80092860(battle, screen, 0);
            break;
        case 22:
            func_80092860(battle, screen, 1);
            break;
        case 23:
            func_80092CE0(battle, screen, 0);
            break;
        case 24:
            func_80092CE0(battle, screen, 1);
            break;
        case 25:
            CARDGAME_showSlotTotal(battle, screen, 0);
            break;
        case 26:
            CARDGAME_showSlotTotal(battle, screen, 1);
            break;
        case 28:
        case 29:
            func_80093D6C(battle, screen);
            break;
        case 30:
        case 31:
        case 32:
        case 34:
        case 35:
            func_8008E8B0(battle, screen, 1, 30);
            break;
        case 33:
            func_8008E8B0(battle, screen, 2, 30);
            break;
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            func_8008E8B0(battle, screen, -2, 30);
            break;
        case 41:
            func_8008EB08(battle, screen);
            break;
        case 47:
            func_800941D0(battle, screen, 0x39);
            break;
        case 48:
            func_800941D0(battle, screen, 0x35);
            break;
        case 49:
            if (side == 0) {
                func_800941D0(battle, screen, 0x3B);
            }
            break;
        case 43:
            func_80094380(battle, screen, 0);
            break;
        case 45:
            func_80094380(battle, screen, 1);
            break;
        case 44:
            func_80094468(battle, screen, 0);
            break;
        case 46:
            func_80094468(battle, screen, 1);
            break;
        case 62:
            func_8008EF50(battle, screen, other, 0);
            break;
        case 63:
            func_8008EF50(battle, screen, side, 0);
            break;
        case 64:
            func_8008EF50(battle, screen, other, 1);
            break;
        case 65:
            func_8008ED28(battle, screen);
            break;
        case 66:
            CARDGAME_takeCardToHand(battle, screen, side, 3);
            break;
        case 67:
            CARDGAME_takeCardToHand(battle, screen, side, 4);
            break;
        case 68:
            func_8008FD44(battle, screen, side);
            break;
        case 69:
            func_80090044(battle, screen, 2);
            break;
        case 70:
            /* up to three, less what the pile already holds: the match depends
               on the subtraction being a statement of its own */
            count = 3;
            count -= battle->sides[side].pile.unkA;
            if (count <= 0) {
                count = 0;
            }
            func_80090044(battle, screen, count);
            break;
        case 71:
            func_80090044(battle, screen, 6);
            break;
        case 72:
            func_80090178(battle, screen, side);
            break;
        case 73:
            func_8008E68C(battle, screen, side);
            break;
        case 76:
            func_8008DBC8(battle, screen);
            break;
        case 77:
        case 78:
            func_80090B48(battle, screen);
            break;
        case 93:
            battle->stepState = 1;
            break;
        case 90:
            func_80093A1C(battle, screen);
            break;
        case 79:
            CARDGAME_putSlotCard(battle, screen, side, 0x50);
            break;
        case 80:
            CARDGAME_putSlotCard(battle, screen, side, 0x51);
            break;
        case 81:
            CARDGAME_putSlotCard(battle, screen, side, 0x52);
            break;
        case 82:
            CARDGAME_putSlotCard(battle, screen, side, 0x53);
            break;
        case 83:
            CARDGAME_putSlotCard(battle, screen, side, 0x54);
            break;
        case 84:
            CARDGAME_putSlotCard(battle, screen, side, 0x55);
            break;
        case 85:
            CARDGAME_putSlotCard(battle, screen, side, 0x56);
            break;
        case 86:
            CARDGAME_takeHandCard(battle, screen, side);
            break;
        case 87:
            CARDGAME_copySlotCard(battle, screen, side);
            break;
        case 88:
            func_8008D3D8(battle, screen, 0);
            break;
        case 89:
            func_8008D3D8(battle, screen, 1);
            break;
        case 94:
            CARDGAME_moveMarkedSlots(battle, screen, 0x000A000A, 1);
            break;
        case 95:
            CARDGAME_moveMarkedSlots(battle, screen, 0x0000001E, 1);
            break;
        case 96:
            CARDGAME_moveMarkedSlots(battle, screen, 0x00320032, 1);
            break;
        case 97:
            CARDGAME_moveMarkedSlots(battle, screen, 0x00140014, 1);
            break;
        case 98:
            CARDGAME_moveMarkedSlots(battle, screen, 0x001E001E, 1);
            break;
        case 99:
            CARDGAME_moveMarkedSlots(battle, screen, 0x0000000A, 1);
            break;
        case 100:
            CARDGAME_moveMarkedSlots(battle, screen, 0x000A0000, 1);
            break;
        case 101:
            CARDGAME_moveMarkedSlots(battle, screen, 0x0000FFC4, 0);
            break;
        case 102:
            CARDGAME_moveMarkedSlots(battle, screen, 0x0000FFF1, 0);
            break;
        case 103:
            CARDGAME_moveMarkedSlots(battle, screen, 0x0000FFE2, 0);
            break;
        case 104:
            CARDGAME_moveMarkedSlots(battle, screen, 0x000AFFF6, 0);
            break;
        case 105:
            CARDGAME_moveMarkedSlots(battle, screen, 0xFF9D0000, 2);
            break;
        case 106:
            battle->unk306 = 1;
            battle->unk424 = 10;
            break;
        case 107:
            battle->unk306 = 2;
            battle->unk424 = 10;
            break;
        case 108:
            battle->unk306 = 3;
            battle->unk424 = 10;
            break;
        case 109:
            battle->unk306 = 4;
            battle->unk424 = 10;
            break;
        case 110:
            battle->unk306 = 5;
            battle->unk424 = 15;
            break;
        case 111:
            battle->unk306 = 6;
            battle->unk424 = 10;
            break;
        case 152:
            func_80085AA8(battle, screen, 14);
            break;
        case 155:
            func_80086564(battle, screen, battle->sides[0].pile.unkA, 5);
            break;
        case 156:
            func_80086564(battle, screen, battle->sides[0].pile.unk6, 9);
            break;
        case 168:
            func_800894F8(battle, screen);
            break;
        case 154:
            func_8008642C(battle, screen, &battle->sides[0].pile);
            break;
        case 157:
            battle->unk444 = 0;
            break;
        case 158:
            func_800885C0(battle, screen);
            break;
        case 153:
            func_8008642C(battle, screen, &battle->sides[battle->unk560.unk19].pile);
            break;
        case 159:
        case 160:
            func_80088B98(battle, screen, 0);
            break;
        case 161:
            func_80088B98(battle, screen, 1);
            break;
        case 162:
            func_80088B98(battle, screen, 2);
            break;
        case 163:
            func_80088B98(battle, screen, 3);
            break;
        case 164:
            func_80088B98(battle, screen, 4);
            break;
        case 165:
            func_80088B98(battle, screen, 5);
            break;
        case 166:
            func_80088B98(battle, screen, 6);
            break;
        case 167:
            func_80088F10(battle, screen);
            break;
        case 172:
            CARDGAME_setupCardChoice(battle, screen, side, 2);
            break;
        case 173:
            CARDGAME_setupCardChoice(battle, screen, other, 1);
            break;
        case 169:
            CARDGAME_setupCardChoice(battle, screen, other, 0);
            break;
        case 170:
            CARDGAME_setupCardChoice(battle, screen, side, 0);
            break;
        case 171:
            CARDGAME_setupCardChoice(battle, screen, side, 3);
            break;
        case 174:
            func_8008A378(battle, screen, 0);
            break;
        case 112:
            func_8008C064(battle, screen, 0);
            break;
        case 113:
            func_8008C064(battle, screen, 0x4000);
            break;
        case 114:
            func_8008C064(battle, screen, 0x2000);
            break;
        case 115:
            func_8008C064(battle, screen, 0x1);
            break;
        case 116:
            func_8008C064(battle, screen, 0x4);
            break;
        case 117:
            func_8008C064(battle, screen, 0x10);
            break;
        case 118:
            func_8008C064(battle, screen, 0x40);
            break;
        case 119:
            func_8008C064(battle, screen, 0x100);
            break;
        case 120:
            func_8008C064(battle, screen, 0x2);
            break;
        case 121:
            func_8008C064(battle, screen, 0x8);
            break;
        case 122:
            func_8008C064(battle, screen, 0x20);
            break;
        case 123:
            func_8008C064(battle, screen, 0x80);
            break;
        case 124:
            func_8008C064(battle, screen, 0x200);
            break;
        case 125:
            func_8008C064(battle, screen, 0x3FF);
            break;
        case 126:
            func_8008C064(battle, screen, 0xF0000);
            break;
        case 127:
            func_8008C064(battle, screen, 0x8000);
            break;
        case 129:
            func_8008C064(battle, screen, 0x400);
            break;
        case 128:
            func_8008C064(battle, screen, 0x1400);
            break;
        case 130:
            func_8008C064(battle, screen, 0x1000);
            break;
        case 131:
            func_8008C424(battle, screen, 0);
            break;
        case 132:
            func_8008C424(battle, screen, 1);
            break;
        case 141:
            func_8008A378(battle, screen, 1);
            break;
        case 142:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 1);
            break;
        case 143:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 2);
            break;
        case 144:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 3);
            break;
        case 145:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 4);
            break;
        case 146:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 5);
            break;
        case 147:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 6);
            break;
        case 148:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 7);
            break;
        case 149:
            CARDGAME_showTargetSlots(battle, screen, nextSide, 8);
            break;
        case 151:
            func_8008B29C(battle, screen, nextSide);
            break;
        }
        battle->unk420 = battle->unk421;
        battle->unk421 = 0;
    }

    switch (battle->unk420) {
    case 0:
        break;
    case 1:
        if (func_80083820(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 2:
        battle->unk2F4 = 2;
        battle->unk4E0 += 2;
        break;
    case 3:
        battle->unk4E2 = 2;
        battle->unk2F4 = 2;
        battle->unk4E4 = battle->unk4E0;
        break;
    case 4:
        battle->unk4E2 = 3;
        battle->unk2F4 = 2;
        battle->unk4E4 = battle->unk4E0;
        break;
    case 5:
        battle->unk4E2 = 5;
        battle->unk2F4 = 2;
        battle->unk4E4 = battle->unk4E0;
        break;
    case 6:
        if (--battle->unk4E2 > 0) {
            battle->unk4E0 = battle->unk4E4;
        }
        battle->unk2F4 = 2;
        break;
    case 7:
        func_800836D8(battle, screen, 1, 1);
        battle->unk2F4 = 2;
        break;
    case 8:
        func_800836D8(battle, screen, 1, 2);
        battle->unk2F4 = 2;
        break;
    case 15:
        initCardDrawer(&drawer);
        for (i = 0; i < battle->sides[other].pile.unkA; i++) {
            drawer.setCard(battle->cards[battle->sides[other].pile.unk64[i]] + 1);
            if (drawer.card[0] != 5) {
                battle->unk4E0 -= 4;
                break;
            }
        }
        battle->unk2F4 = 2;
        break;
    case 9:
        func_80083714(battle, side, 10, 9);
        battle->unk2F4 = 2;
        break;
    case 10:
        func_80083758(battle, side, 10, -9);
        battle->unk2F4 = 2;
        break;
    case 11:
        func_80083714(battle, side, 3, 9);
        battle->unk2F4 = 2;
        break;
    case 12:
        func_80083758(battle, side, 3, -9);
        battle->unk2F4 = 2;
        break;
    case 16:
        func_800837DC(battle, side, 5);
        battle->unk2F4 = 2;
        break;
    case 13:
        func_80083758(battle, side, 2, 4);
        battle->unk2F4 = 2;
        break;
    case 14:
        func_8008379C(battle, other, 2);
        battle->unk2F4 = 2;
        break;
    case 17:
        battle->unk560.unk20[battle->unk560.unk15 - 1].unk4 ^= 1;
        battle->unk2F4 = 2;
        break;
    case 18:
    case 19:
        if (func_80091A94(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 20:
        if (CARDGAME_stepStart(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 27:
        if (func_80092EB0(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 21:
        if (CARDGAME_stepAttack(battle, screen, 0)) {
            battle->unk2F4 = 0;
        }
        break;
    case 22:
        if (CARDGAME_stepAttack(battle, screen, 1)) {
            battle->unk2F4 = 0;
        }
        break;
    case 23:
        if (func_80092D14(battle, screen, 0)) {
            battle->unk2F4 = 0;
        }
        break;
    case 24:
        if (func_80092D14(battle, screen, 1)) {
            battle->unk2F4 = 0;
        }
        break;
    case 25:
        if (func_800934E0(battle, screen, 0)) {
            battle->unk2F4 = 0;
        }
        break;
    case 26:
        if (func_800934E0(battle, screen, 1)) {
            battle->unk2F4 = 0;
        }
        break;
    case 28:
        if (func_80093D90(battle, screen, 0)) {
            battle->unk2F4 = 0;
        }
        break;
    case 29:
        if (func_80093D90(battle, screen, 1)) {
            battle->unk2F4 = 0;
        }
        break;
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
        if (func_800839CC(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 41:
        if (CARDGAME_drainColorValues(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 42:
        if (func_8008EF20(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 43:
    case 45:
        if (func_800943FC(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 44:
    case 46:
        if (func_800944E8(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 47:
        if (side != 0) {
            battle->unk2F4 = 2;
        } else if (CARDGAME_waitMessage(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 48:
        if (CARDGAME_waitMessage(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 49:
        if (side != 0) {
            battle->unk2F4 = 2;
        } else if (CARDGAME_waitMessage(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 52:
        CARDGAME_markPileCardsByColor(battle, screen, side, 3, 0xFD);
        battle->unk2F4 = 2;
        break;
    case 53:
        CARDGAME_markPileCardsByColor(battle, screen, side, 3, 0xFE);
        battle->unk2F4 = 2;
        break;
    case 50:
        CARDGAME_markPileCardsByColor(battle, screen, side, 3, 0xFF);
        battle->unk2F4 = 2;
        break;
    case 51:
        CARDGAME_markPileCardsByColor(battle, screen, other, 3, 0xFF);
        battle->unk2F4 = 2;
        break;
    case 55:
        CARDGAME_markPileCardsByColor(battle, screen, side, 2, 0xFF);
        battle->unk2F4 = 2;
        break;
    case 54:
        CARDGAME_markPileCardsByColor(battle, screen, other, 2, 0xFF);
        battle->unk2F4 = 2;
        break;
    case 56:
        CARDGAME_markPileCardsByColor(battle, screen, other, 2, 0x81);
        battle->unk2F4 = 2;
        break;
    case 57:
        CARDGAME_markPileCardsByColor(battle, screen, other, 2, 0xBF);
        battle->unk2F4 = 2;
        break;
    case 58:
        CARDGAME_markPileCardsByColor(battle, screen, side, 4, 0xFF);
        battle->unk2F4 = 2;
        break;
    case 59:
        CARDGAME_markSlotsByColor(battle, screen, side, 0x3FC);
        battle->unk2F4 = 2;
        break;
    case 60:
        CARDGAME_markSlotsByColor(battle, screen, side, 0x2FC);
        battle->unk2F4 = 2;
        break;
    case 61:
        CARDGAME_markSlotsByColor(battle, screen, side, 0x1FC);
        battle->unk2F4 = 2;
        break;
    case 62:
        if (CARDGAME_discardPickedCard(battle, screen, other, 0)) {
            battle->unk2F4 = 2;
        }
        break;
    case 63:
        if (CARDGAME_discardPickedCard(battle, screen, side, 0)) {
            battle->unk2F4 = 2;
        }
        break;
    case 64:
        if (CARDGAME_discardPickedCard(battle, screen, other, 1)) {
            battle->unk2F4 = 2;
        }
        break;
    case 65:
        if (CARDGAME_discardPrevCard(battle, screen)) {
            battle->unk4DD = 1;
            battle->unk2F4 = 2;
        }
        break;
    case 66:
        if (CARDGAME_drawFromDeck(battle, screen, side, 3)) {
            battle->unk2F4 = 2;
        }
        break;
    case 67:
        if (CARDGAME_drawFromDeck(battle, screen, side, 4)) {
            battle->unk2F4 = 2;
        }
        break;
    case 68:
        if (CARDGAME_returnUsedCards(battle, screen, side)) {
            battle->unk2F4 = 2;
        }
        break;
    case 69:
    case 70:
    case 71:
        if (func_80090068(battle, screen, side)) {
            battle->unk2F4 = 2;
        }
        break;
    case 72:
        if (CARDGAME_drawNewCards(battle, screen, side)) {
            battle->unk2F4 = 2;
        }
        break;
    case 73:
        if (CARDGAME_discardHand(battle, screen, side)) {
            battle->unk2F4 = 2;
        }
        break;
    case 74:
        for (j = 0; j < battle->sides[other].pile.unkA; j++) {
            if (battle->unk446[j] != 0) {
                battle->unk440 = j;
                break;
            }
        }
        battle->unk2F4 = 2;
        break;
    case 75:
        func_80083860(battle, screen, other);
        battle->unk2F4 = 2;
        break;
    case 76:
        if (CARDGAME_removeMarkedSlots(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 77:
        if (func_80090B58(battle, screen, 0)) {
            battle->unk2F4 = 2;
        }
        break;
    case 78:
        if (func_80090B58(battle, screen, 1)) {
            battle->unk2F4 = 2;
        }
        break;
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
        if (CARDGAME_moveSlotCard(battle, screen, side)) {
            battle->unk2F4 = 2;
        }
        break;
    case 87:
        if (CARDGAME_flipSlotCard(battle, screen, side)) {
            battle->unk2F4 = 2;
        }
        break;
    case 88:
        if (func_8008D4C4(battle, screen, 36)) {
            battle->unk2F4 = 2;
        }
        break;
    case 89:
        if (func_8008D4C4(battle, screen, 28)) {
            battle->unk2F4 = 2;
        }
        break;
    case 90:
        if (func_80093A3C(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 91:
        func_80083880(battle, screen);
        battle->unk2F4 = 2;
        break;
    case 92:
        CARDGAME_markTargetSlots(battle, screen);
        battle->unk2F4 = 2;
        break;
    case 93:
        result = func_80094550(battle, screen);
        if (result == 1) {
            battle->unk2F4 = 2;
        } else if (result == 2) {
            battle->unk421 = 77;
        }
        break;
    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
        if (CARDGAME_stepSlotStats(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 106:
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
        if (func_80083820(battle, screen)) {
            battle->unk2F4 = 2;
        }
        break;
    case 112:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 126:
        result = func_8008C174(battle, screen);
        if (result != -1) {
            battle->unk560.unk1A = result;
            battle->unk2F4 = 0;
        }
        break;
    case 127:
        result = func_8008C174(battle, screen);
        if (result != -1) {
            battle->unk560.unk1A = result;
            battle->unk2F4 = 0;
        }
        break;
    case 128:
    case 129:
    case 130:
        result = func_8008C174(battle, screen);
        if (result != -1) {
            battle->unk560.unk1A = result;
            battle->unk2F4 = 0;
        }
        break;
    case 131:
    case 132:
        result = func_8008C5F4(battle, screen);
        if (result != -1) {
            battle->unk560.unk1A = result;
            battle->unk2F4 = 0;
        }
        break;
    case 135:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x180);
        battle->unk421 = 141;
        break;
    case 134:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x1BC);
        battle->unk421 = 141;
        break;
    case 133:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x1FC);
        battle->unk421 = 141;
        break;
    case 138:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x280);
        battle->unk421 = 141;
        break;
    case 137:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x2BC);
        battle->unk421 = 141;
        break;
    case 136:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x2FC);
        battle->unk421 = 141;
        break;
    case 139:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x3FC);
        battle->unk421 = 141;
        break;
    case 140:
        CARDGAME_markSlotsByColor(battle, screen, nextSide, 0x380);
        battle->unk421 = 141;
        break;
    case 141:
        switch (CARDGAME_pickTableCard(battle, screen)) {
        case 1:
            battle->unk560.unk1A = 0;
            battle->unk2F4 = 0;
            break;
        case 2:
            index = battle->unk440;
            if (index < 6) {
                battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->players[0].slots[index].order;
            } else {
                index -= 6;
                battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->players[1].slots[index].order;
            }
            battle->unk560.unk1A = 1;
            battle->unk2F4 = 0;
            break;
        }
        break;
    case 152:
        switch (CARDGAME_stepYesNo(battle, screen)) {
        case 0:
            break;
        case 1:
            battle->unk560.unk1A = 1;
            battle->unk2F4 = 0;
            break;
        case 2:
            battle->unk560.unk1A = 0;
            battle->unk2F4 = 0;
            break;
        }
        break;
    case 153:
        result = CARDGAME_stepChooseCards(battle, screen, &battle->sides[battle->unk560.unk19].pile);
        if (result != -1) {
            battle->unk560.unk1A = result;
            battle->unk2F4 = 0;
        }
        break;
    case 154:
        if (CARDGAME_stepChooseCards(battle, screen, &battle->sides[0].pile) != -1) {
            battle->unk2F4 = 0;
        }
        break;
    case 157:
        if (func_8008BC08(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 155:
    case 156:
        if (CARDGAME_stepChooseCards(battle, screen, &battle->sides[0].pile) != -1) {
            battle->unk2F4 = 3;
        }
        break;
    case 168:
        if (CARDGAME_viewTable(battle, screen)) {
            battle->unk2F4 = 3;
        }
        break;
    case 158:
        if (CARDGAME_stepTally(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 159:
    case 160:
    case 161:
    case 162:
    case 163:
    case 164:
    case 165:
    case 166:
        if (CARDGAME_stepMessage(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 167:
        if (CARDGAME_drawFirstPlayer(battle, screen)) {
            battle->unk2F4 = 0;
        }
        break;
    case 172:
        if (side == 0) {
            if (CARDGAME_chooseCard(battle, screen, 2)) {
                battle->unk2F4 = 2;
            }
        } else {
            func_8008BEF0(battle, screen);
            battle->unk2F4 = 2;
        }
        break;
    case 173:
        if (side == 0) {
            if (CARDGAME_chooseCard(battle, screen, 0)) {
                battle->unk2F4 = 2;
            }
        } else {
            func_8008BFA0(battle, screen);
            battle->unk2F4 = 2;
        }
        break;
    case 169:
        if (side == 0) {
            if (CARDGAME_chooseCard(battle, screen, 0)) {
                battle->unk2F4 = 2;
            }
        } else {
            CARDGAME_pickBestPileCard(battle, screen, 1);
            battle->unk2F4 = 2;
        }
        break;
    case 170:
        if (side == 0) {
            if (CARDGAME_chooseCard(battle, screen, 0)) {
                battle->unk2F4 = 2;
            }
        } else {
            CARDGAME_pickBestPileCard(battle, screen, 0);
            battle->unk2F4 = 2;
        }
        break;
    case 171:
        if (side == 0) {
            if (CARDGAME_chooseCard(battle, screen, 0)) {
                battle->unk2F4 = 2;
            }
        } else {
            CARDGAME_pickBestPileCard(battle, screen, 1);
            battle->unk2F4 = 2;
        }
        break;
    case 174:
        if (side == 0) {
            if (CARDGAME_pickTableCard(battle, screen)) {
                battle->unk2F4 = 2;
            }
        } else {
            func_80083918(battle);
            battle->unk2F4 = 2;
        }
        break;
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
    case 148:
    case 149:
        result = func_8008CBAC(battle, screen);
        if (result != -1) {
            battle->unk560.unk1A = result;
            battle->unk2F4 = 0;
        }
        break;
    case 150:
        CARDGAME_markPileCardsByColor(battle, screen, nextSide, 2, 0xFD);
        battle->unk421 = 151;
        break;
    case 151:
        switch (CARDGAME_chooseCard(battle, screen, 1)) {
        case 1:
            battle->unk560.unk1A = 0;
            battle->unk2F4 = 0;
            break;
        case 2:
            if (nextSide == 0) {
                battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->sides[0].pile.unk64[battle->unk440];
            } else {
                battle->unk560.unk20[battle->unk560.unk15].unk6 = battle->sides[1].pile.unk64[battle->unk440];
            }
            battle->unk560.unk1A = 1;
            battle->unk2F4 = 0;
            break;
        }
        break;
    }
}


CardTableEntry D_800A3CF8[60] = {
    { 0x91, 0x0A, 0x2F, 0x04, { 0x6A, 0x5C, 0x59, 0x4D, 0x4C } },
    { 0x70, 0x00, 0x00, 0x09, { 0x03, 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x4F, 0x06 } },
    { 0x8E, 0x0A, 0x2F, 0x01, { 0x5C, 0x5E } },
    { 0x85, 0x09, 0x2F, 0x00, { 0x5B, 0x5F } },
    { 0x73, 0x00, 0x00, 0x09, { 0x1E } },
    { 0x70, 0x00, 0x00, 0x09, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x50 } },
    { 0x92, 0x0A, 0x2F, 0x05, { 0x6B, 0x5C, 0x4E, 0x4C, 0x03, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x11, 0x06 } },
    { 0x88, 0x09, 0x2F, 0x00, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x5B, 0x57, 0x4C } },
    { 0x83, 0x00, 0x00, 0x09, { 0x41 } },
    { 0x8B, 0x09, 0x2F, 0x00, { 0x5B, 0x4E, 0x4C, 0x03, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x11, 0x06 } },
    { 0x74, 0x00, 0x00, 0x09, { 0x1F } },
    { 0x70, 0x00, 0x00, 0x09, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x51 } },
    { 0x93, 0x0A, 0x2F, 0x06, { 0x6C, 0x5C, 0x60 } },
    { 0x81, 0x04, 0x00, 0x09, { 0x2D, 0x3A, 0xAB, 0x43, 0x2E } },
    { 0x75, 0x00, 0x00, 0x09, { 0x21 } },
    { 0x85, 0x09, 0x2F, 0x00, { 0x5B, 0x61 } },
    { 0x75, 0x00, 0x00, 0x09, { 0x20 } },
    { 0x70, 0x00, 0x00, 0x09, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x52 } },
    { 0x94, 0x0A, 0x2F, 0x07, { 0x6D, 0x5C, 0x58, 0x65, 0x4D, 0x4C } },
    { 0x95, 0x0A, 0x2F, 0x08, { 0x5C, 0x59, 0x4D, 0x4C } },
    { 0x90, 0x0A, 0x2F, 0x03, { 0x5C, 0x58, 0x66, 0x4D, 0x4C } },
    { 0x88, 0x09, 0x2F, 0x00, { 0x5B, 0x58, 0x67, 0x4D, 0x4C } },
    { 0x76, 0x00, 0x00, 0x09, { 0x22 } },
    { 0x70, 0x00, 0x00, 0x09, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x53 } },
    { 0x7F, 0x03, 0x3A, 0x09, { 0x6E, 0x39, 0x4A, 0x3E, 0x0F } },
    { 0x82, 0x05, 0x35, 0x09, { 0x2D, 0x32, 0xAC, 0x42, 0x2E, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A } },
    { 0x89, 0x09, 0x2F, 0x00, { 0x5B, 0x59, 0x4D, 0x4C } },
    { 0x7F, 0x01, 0x33, 0x09, { 0x07, 0x2F, 0x07, 0x2B, 0x36, 0xA9, 0x07, 0x2C, 0x3E } },
    { 0x77, 0x00, 0x00, 0x09, { 0x23 } },
    { 0x70, 0x00, 0x00, 0x09, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x54 } },
    { 0x90, 0x0A, 0x2F, 0x03, { 0x6F, 0x5C, 0x59, 0x4D, 0x4C } },
    { 0x7E, 0x00, 0x00, 0x09, { 0x6F, 0x2A } },
    { 0x72, 0x06, 0x35, 0x09, { 0x6F, 0x04, 0x08, 0x2F, 0x2B, 0x33, 0xAD, 0x07, 0x2C, 0x40, 0x0E, 0x30, 0x02, 0x06 } },
    { 0x82, 0x05, 0x35, 0x09, { 0x6F, 0x49, 0x2D, 0x47, 0x48, 0x2E } },
    { 0x7D, 0x00, 0x00, 0x09, { 0x6F, 0x29 } },
    { 0x80, 0x04, 0x00, 0x09, { 0x44 } },
    { 0x70, 0x00, 0x00, 0x09, { 0x0D, 0x2D, 0x46, 0x48, 0x2E, 0x0B, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0C, 0x11, 0x0D, 0x2D, 0x46, 0x48, 0x2E, 0x0B, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0C, 0x11 } },
    { 0x72, 0x06, 0x35, 0x09, { 0x05, 0x33, 0x4B, 0x40, 0x0E, 0x30, 0x02, 0x06 } },
    { 0x8F, 0x0A, 0x2F, 0x02, { 0x5C, 0x69 } },
    { 0x96, 0x0B, 0x2F, 0x09, { 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x56 } },
    { 0x87, 0x09, 0x2F, 0x00, { 0x5B, 0x62 } },
    { 0x82, 0x05, 0x35, 0x09, { 0x2D, 0x45, 0x48, 0x2E, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A } },
    { 0x82, 0x07, 0x36, 0x09, { 0x2D, 0x34, 0xAC, 0x42, 0x2E, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A } },
    { 0x82, 0x08, 0x37, 0x09, { 0x2D, 0x35, 0xAC, 0x42, 0x2E, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A } },
    { 0x82, 0x05, 0x35, 0x09, { 0x2D, 0x32, 0xAC, 0x42, 0x2E, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F } },
    { 0x72, 0x06, 0x35, 0x09, { 0x03, 0x33, 0x4B, 0x40, 0x0E, 0x30, 0x02, 0x06 } },
    { 0x8A, 0x09, 0x2F, 0x00, { 0x5B, 0x58, 0x67, 0x4D, 0x4C } },
    { 0x84, 0x00, 0x00, 0x09, { 0x41 } },
    { 0x7F, 0x02, 0x38, 0x09, { 0x07, 0x2F, 0x07, 0x2B, 0x38, 0xA9, 0x07, 0x2C, 0x3E } },
    { 0x70, 0x00, 0x00, 0x09, { 0x03, 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x55, 0x06 } },
    { 0x78, 0x00, 0x00, 0x09, { 0x24 } },
    { 0x79, 0x00, 0x00, 0x09, { 0x25 } },
    { 0x7A, 0x00, 0x00, 0x09, { 0x26 } },
    { 0x7B, 0x00, 0x00, 0x09, { 0x27 } },
    { 0x7C, 0x00, 0x00, 0x09, { 0x28 } },
    { 0x8C, 0x09, 0x2F, 0x00, { 0x5B, 0x4E, 0x4C, 0x03, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x11, 0x06 } },
    { 0x8B, 0x09, 0x2F, 0x00, { 0x5B, 0x58, 0x68, 0x4D, 0x4C } },
    { 0x8A, 0x09, 0x2F, 0x00, { 0x5B, 0x4D, 0x4C } },
    { 0x85, 0x09, 0x2F, 0x00, { 0x5B, 0x63 } },
    { 0x85, 0x09, 0x2F, 0x00, { 0x5B, 0x64 } },
};
/* three sets of four positions, then the same moved for SHIFT_PAL_SCREEN */
s16 D_800A4748[2][3][4][2] = {
    {
        {{0x82, 0xD4}, {0x82, 0x67}, {0x82, 0xBF}, {0xFD, 0xBF}},
        {{0x82, 0x1D}, {0x82, 0x61}, {0x82, 0x08}, {0xFD, 0x08}},
        {{0x82, 0xA5}, {0x86, 0x31}, {0x82, 0x90}, {0xFD, 0x90}},
    },
    {
        {{0x82, 0xE0}, {0x82, 0x73}, {0x82, 0xCB}, {0xFD, 0xCB}},
        {{0x82, 0x11}, {0x82, 0x55}, {0x82, -4}, {0xFD, -4}},
        {{0x82, 0xA5}, {0x86, 0x31}, {0x82, 0x90}, {0xFD, 0x90}},
    },
};
s32 CARDGAME_rowSpriteOffsets[] = {
    0, 6, 12, 0,
};
CardBattleStep CARDGAME_windowSteps[] = {{0, 0}, {4, 1}, {8, 2}, {-1, 3}};
u8 D_800A47C8[][2] = {
    {0x01, 0x02}, {0x03, 0x04}, {0x05, 0x06}, {0x07, 0x08},
    {0x09, 0x0A}, {0x0B, 0x0C}, {0x1F, 0x3E}, {0x0B, 0x0C},
};
s32 CARDGAME_coinCardPositions[][2] = {{0x7400, 0x6100}, {0xA400, 0x6100}};
s32 D_800A47E8[] = {5, 6, 7, 0};
s16 D_800A47F8[] = {
    0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
};
s32 D_800A4804[][2] = {{0x11400, 28416}, {0x11400, 22016}};
s32 D_800A4814[][2] = {{20736, 24832}, {33536, 24832}, {46336, 24832}};
s16 CARDGAME_cardWindowPositions[2][2][2] = {{{0x82, 0xBF}, {0x82, 0x1D}}, {{0x82, 0xCB}, {0x82, 0x11}}};
RECT CARDGAME_screenRect = {0, 0, 320, 240};
/* where the deck window's six counts are */
CardOffset CARDGAME_deckCountOffsets[] = {
    {0x24, 0x14}, {0x47, 0x14}, {0x6A, 0x14}, {0x8D, 0x14}, {0xB0, 0x14}, {0xD3, 0x14},
};
#if VERSION_EU
s32 D_800A5958[2][4] = {
    {0x1800, 0x9000, 0x1800, 0x3200},
    {0x1800, 0x9C00, 0x1800, 0x2600},
};
#endif
/* where the three CardScreenDC0 gauges are */
CardOffset D_800A485C[] = {
    {0x49, 0x61}, {0x7B, 0x61}, {0xAD, 0x61},
};
CardWindowLayout CARDGAME_windowLayouts[] = {
    {0x00, 0x0A, 0x02, 2}, {0xBE, 0x0A, 0x03, 2}, {0xBE, 0x18, 0x04, 2},
    {0x43, 0x18, 0x05, 2}, {0x00, 0x1E, 0x37, 2}, {0x140, 0x0A, 0x19, 1},
};
u16 D_800A488C[] = {
    0x0004, 0x0018, 0x0049, 0x0000,
};
s32 D_800A4894[][2] = {{0, 138}, {0, 96}, {0, 50}, {0, 96}};
CardPanelLayout D_800A48B4[2] = {
    {0x1, 0xE, 0x11, 0x2F, {17, 69}, {38, 71}, {249, 71}, {291, 71}, {1, -15}, {30, 52}, {46, 52},
     {78, 52}, {94, 52}, {228, 69}, {270, 69}, {-7, -22}, {11, 67}, {222, 64}, {264, 64}, {-6, -20},
     {23, 48}, {71, 48}},
    {0x1, 0xF, 0x14, 0x30, {17, 14}, {38, 16}, {249, 16}, {291, 16}, {1, 21}, {30, 35}, {46, 35},
     {78, 35}, {94, 35}, {228, 14}, {270, 14}, {-7, -6}, {11, 12}, {222, 9}, {264, 9}, {-6, -5},
     {23, 31}, {71, 31}},
};
u8 D_800A494C[8] = {0, 1, 2, 3, 2, 1, 0, 0};
u8 D_800A4954[8][2] = {
    {0x4D, 0x56}, {0x4E, 0x57}, {0x4F, 0x58}, {0x50, 0x59},
    {0x52, 0x5B}, {0x51, 0x5A}, {0x53, 0x5C}, {0, 0},
};
u8 D_800A4964[] = {
    0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A496C[] = {
    0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A4974[] = {
    0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A497C[] = {
    0x1D, 0x20, 0x23, 0x26, 0x29, 0x00, 0x00, 0x00,
};
u8 D_800A4984[] = {
    0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
};
#if VERSION_EU
u16 D_800A5AA8[] = {
    0x007C, 0x0033, 0x007C, 0x0023, 0x008A, 0x0034, 0x008A, 0x0024,
    0x007C, 0x003F, 0x007C, 0x0017, 0x008A, 0x0040, 0x008A, 0x0018,
};
#endif
s16 D_800A498C[] = {
    -0x100, 0x300, -0x300, 0x100,
};
s16 D_800A4994[] = {
    -0x400, 0x200, -0x200, 0x400,
};
s32 D_800A499C[] = {
    12, 28, 32, 0x7C00A0,
    0x2E0028, 0xFC0020, 0, 65280,
    1, 65535, 0,
};
u8 D_800A49C8[] = {
    0x00, 0x01, 0x02, 0x03,
};
u8 D_800A49CC[] = {
    0x00, 0x01, 0x02, 0x03,
};
u8 D_800A49D0[] = {
    0x00, 0x01, 0x02, 0x03, 0x02, 0x01, 0x00, 0x00,
};
s16 D_800A49D8[] = {
    0x003C, 0x003D, 0x003E, 0x0040, 0x0041, 0x0042, 0x0043, 0x0046,
    0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x0067, 0x0068,
    0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x0070, 0x0071,
    0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079,
    0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x009A, 0x009B,
    0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3,
    0x00A4, 0x00BD, 0x00BE, 0x00BF, 0x00C0, 0x00C2, 0x00C3, 0x00C4,
    0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CD,
    0x00CE, 0x00CF, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00ED, 0x00EE,
    0x00EF, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6,
    0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x0113, 0x0114, 0x0118, 0x0119,
    0x011A, 0x011B, 0x011C, 0x011D, 0x011E, 0x011F, 0x0120, 0x0121,
    0x0122, 0x0124, 0x0125, 0x013A,
};
/* the cards everyone has, after the two decks in the card list */
s16 D_800A4AA0[] = {
    0x050, 0x063, 0x08C, 0x0B8, 0x0E5, 0x0FB, 0x139, 0x13A, 0x13B,
#if VERSION_US
    0x2D2D,
#elif VERSION_EU
    0x0A0D,
#endif
};
CardFileEntry CARDGAME_preloadFiles[] = {
    { 0x2B, 1 },
    { 0x0F, 1 },
#if VERSION_US
    { 2023, 0 },
    { 2024, 0 },
    { 2025, 0 },
    { 2026, 0 },
    { 2027, 0 },
#elif VERSION_EU
    { 2038, 0 },
    { 2039, 0 },
    { 2040, 0 },
    { 2041, 0 },
    { 2042, 0 },
#endif
    { -2, 0 },
    { 0x1D, 1 },
    { 0x16, 1 },
    { 0x6A, 1 },
    { -1, 0 },
};
s16 D_800A4AE4[] = {
    0x0044, 0x006F, 0x009A, 0x00C5, 0x00F0, 0x0000,
};
s16 D_800A4AF0[] = {
    0x005B, 0x005B, 0x0169, 0x016A, 0x016B, 0x016C, 0x016D, 0x016E,
    0x016F, 0x0170, 0x0171, 0x0172, 0x0173, 0x0174, 0x0175, 0x0176,
    0x0177, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E,
    0x017F, 0x0180, 0x0181, 0x0182, 0x0183, 0x0184, 0x0185, 0x0186,
    0x0187, 0x0188, 0x0189, 0x018A,
};
u16 CARDGAME_defaultDeck[] = {
    0x0138, 0x002A, 0x002B, 0x0136, 0x0136, 0x0136, 0x0021, 0x0021,
    0x0050, 0x0029, 0x0031, 0x0031, 0x0031, 0x0031, 0x0031, 0x0031,
    0x0031, 0x0031, 0x0031, 0x0031, 0x0009, 0x0009, 0x0009, 0x0009,
    0x0009, 0x0009, 0x0009, 0x0009, 0x0009, 0x0009, 0x0006, 0x0006,
    0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x0006,
    0x0029, 0x0029, 0x0050, 0x0015, 0x0007, 0x001A, 0x0008, 0x0029,
    0x0002, 0x0008, 0x002E, 0x000D, 0x000D, 0x000D, 0x0036, 0x0050,
    0x000B, 0x000B, 0x0024, 0x000B, 0x0019, 0x000B, 0x0019, 0x001F,
    0x0050, 0x0028, 0x0014, 0x0050, 0x0050, 0x0050, 0x0050, 0x0001,
    0x0001, 0x0139, 0x0023, 0x0018, 0x0018, 0x0050, 0x003B, 0x003A,
};
CardFadeColor D_800A4BD8[] = {
    { 0x80, 0x80, 0x80, 1 }, { 0x00, 0x00, 0x80, 1 }, { 0x00, 0x80, 0x00, 1 },
    { 0x80, 0x00, 0x00, 1 }, { 0x80, 0x80, 0x80, 2 }, { 0x80, 0x80, 0x00, 1 },
};
s16 D_800A4BF0[7][2] = {{0, 0}, {1, 1}, {1, 2}, {1, 0}, {0, 1}, {0, 2}, {0, 0}};
CardOffset CARDGAME_deckWindowPos[3] = {{0x17, 0x50}, {0x17, 0x7D}, {0x17, 0xAA}};
u8 CARDGAME_turnStates[] = {
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};
CardBattleMessage D_800A4C20[] = {
    {0x00, 0}, {0xA6, 2}, {0xA0, 3}, {0xA1, 4}, {0xA2, 5},
    {0xA3, 6}, {0xA4, 7}, {0xA5, 8}, {0xA0, 3}, {0xA0, 3},
};
CardOffset CARDGAME_playedCardPos[2][2] = {{{0x82, 0xBF}, {0x82, 0x1D}}, {{0x82, 0xCB}, {0x82, 0x11}}};
RECT CARDGAME_fadeRect = {0, -15, 320, 260};
s32 CARDGAME_promptText = 0;
s16 CARDGAME_savedPanelScales[2] = {0, 0};
s32 D_800A4C68 = 0;
u8 D_800A4C6C[2][6][2] = {{{0}}};
/* per side, the entries of D_800A4C6C, then (D_800A4C86, a symbol of its
   own) the marked slots; the rest is not used */
u8 D_800A4C84[8] = {0};
CardScreenSave CARDGAME_savedScreenState = {0};
