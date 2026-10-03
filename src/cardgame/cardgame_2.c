/* The second object of CARDGAME.PRO (see cardgame.c), from CARDGAME_sortOpponentCards
   (USA): its rodata starts at 0x80082A04, 4 bytes past a multiple of 8. */

#include "cardgame.h"

/* Sorts the opponent's cards by unk30A[].unk0, then swaps card unk440 to unk41C */
void CARDGAME_sortOpponentCards(CardBattle *battle) {
    CardBattle30A tmp;
    s16 *cards = battle->sides[1].pile.unk14;
    s16 card;
    s32 i;
    s32 j;
    s32 target;

    for (i = battle->sides[1].pile.unk4; i < 39; i++) {
        for (j = i + 1; j < 40; j++) {
            if (battle->unk30A[i].unk0 > battle->unk30A[j].unk0) {
                card = cards[i];
                cards[i] = cards[j];
                cards[j] = card;
                tmp = battle->unk30A[i];
                battle->unk30A[i] = battle->unk30A[j];
                battle->unk30A[j] = tmp;
            }
        }
    }
    target = battle->unk41C;
    tmp = battle->unk30A[battle->unk440];
    battle->unk30A[battle->unk440] = battle->unk30A[target];
    battle->unk30A[target] = tmp;
    card = cards[battle->unk440];
    cards[battle->unk440] = cards[target];
    cards[target] = card;
    battle->unk440 = target;
}

s32 func_800856C8(CardBattle *battle, s32 index) {
    CardDrawer drawer;
    s32 result = 0;
    s32 kind;

    initCardDrawer(&drawer);
    drawer.setCard(battle->cards[index] + 1);
    kind = drawer.getKind();
    if (kind != 0) {
        if (battle->unk2F8 == 7 || (battle->unk2F8 == 5 && kind == 2)) {
            result = 1;
        }
    }
    return result;
}

s32 func_80085760(CardBattle *battle, u8 *arg1, s32 card) {
    CardDrawer drawer;
    s32 result = 0;

    if (battle->unk2F8 == 6) {
        initCardDrawer(&drawer);
        drawer.setCard(battle->cards[card] + 1);
        if (drawer.card[3] == 0x10) {
            result = arg1[drawer.card[0] - 1] >= drawer.card[5];
        }
    } else {
        result = func_800856C8(battle, card);
    }
    return result;
}

s16 func_80085820(s32 a, s32 b, s32 c) {
#if VERSION_US
    return D_800A4748[0][a][b][c];
#elif VERSION_EU
    return D_800A4748[SHIFT_PAL_SCREEN][a][b][c];
#endif
}

/* Opens the windows of the step CARDGAME_windowSteps[step] once its time is past; the next step */
s32 CARDGAME_openStepWindows(CardBattle *battle, CardScreen *screen, s32 layout, s32 text, s32 time, s32 step) {
    if (CARDGAME_windowSteps[step].time < time) {
        switch (CARDGAME_windowSteps[step].kind) {
        case 0:
            screen->unkEAC(screen, 2, 1, 0, func_80085820(layout, 0, 0), func_80085820(layout, 0, 1));
            screen->unkEAC(screen, 4, 2, 0, func_80085820(layout, 1, 0), func_80085820(layout, 1, 1));
            if (text != 0) {
                screen->unkEAC(screen, 0, 0, text, 0, 0x42);
            }
            if (battle->unk420 == 0x9A) {
                screen->unkEAC(screen, 5, 4, 0x24, 0, 0x14);
            }
            break;
        case 1:
            screen->unkEAC(screen, 3, 1, 0, func_80085820(layout, 2, 0), func_80085820(layout, 2, 1));
            break;
        case 2:
            screen->unkEAC(screen, 1, 3, 0, func_80085820(layout, 3, 0), func_80085820(layout, 3, 1));
            break;
        }
        if (step < 3) {
            step++;
        }
    }
    return step;
}

void func_80085AA8(CardBattle *battle, CardScreen *screen, s32 value) {
#if VERSION_EU
    s32 i;
    s32 found;
#endif

    battle->unk440 = 0;
    battle->stepState = 0;
    if (screen->panels[0].state == 0) {
        battle->unk498.unk5 = 1;
        battle->unk498.unk1 = 1;
        screen->unkEC8(screen);
    }
    battle->unk424 = 0;
    screen->unkDE8 = value;
#if VERSION_US
    screen->unkDF4 = 0;
    screen->unkDE4 = 0;
#elif VERSION_EU
    screen->unkDE4 = 0;
    found = 0;
    for (i = 0; i < battle->sides[0].pile.unkA; i++) {
        if (func_80085760(battle, battle->sides[0].pile.unkC, battle->sides[0].pile.unk64[i])) {
            found = 1;
            break;
        }
    }
    if (found) {
        screen->unkDF4 = 0;
        battle->unk440 = 0;
        battle->unk438 = 2;
    } else {
        screen->unkDF4 = 1;
        battle->unk440 = 1;
        battle->unk438 = 3;
    }
#endif
}

/* Runs the yes/no window that func_80085AA8 sets up: 1 for the first choice, 2 for the second, 0 until then */
s32 CARDGAME_stepYesNo(CardBattle *battle, CardScreen *screen) {
    s32 result = 0;

    switch (battle->stepState) {
    case 0:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 36 && battle->unk498.unk0 == 0) {
#if VERSION_US
            battle->stepState = 1;
            battle->unk424 = 0;
            screen->unkEE4(screen, screen->unkDE8, 1, screen->unkDF4, screen->unkDE4);
#elif VERSION_EU
            battle->unk424 = 0;
            if (battle->unk560.unk15 != 0 && battle->unk438 == 3) {
                battle->stepState = 8;
            } else {
                battle->stepState = 1;
                screen->unkEE4(screen, screen->unkDE8, battle->unk438, screen->unkDF4, screen->unkDE4);
            }
#endif
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_CROSS)) {
            screen->unkEEC(screen);
            battle->stepState = 7;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            battle->unk440 = 1;
            screen->unkEF0(screen, 1);
            screen->unkEEC(screen);
            battle->stepState = 7;
#if VERSION_US
        } else if (PAD_PRESSED(PAD_UP) || PAD_PRESSED(PAD_DOWN)) {
#elif VERSION_EU
        } else if ((PAD_PRESSED(PAD_UP) || PAD_PRESSED(PAD_DOWN)) && battle->unk438 == 2) {
#endif
            SOUND.playSound(0x8004513E);
            battle->unk440 ^= 1;
            screen->unkEF0(screen, battle->unk440);
        } else if ((!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) && PAD_PRESSED(PAD_L1)) ||
                   (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_PRESSED(PAD_R1))) {
            screen->unkEE8(screen);
            battle->stepState = 6;
        } else if (PAD_PRESSED(PAD_CIRCLE)) {
            screen->unkEE8(screen);
            battle->unk424 = 0;
            battle->stepState = 3;
        }
        break;
    case 6:
        if (screen->unkDFA == 0) {
            screen->unkDE4 ^= 2;
#if VERSION_US
            screen->unkEE4(screen, screen->unkDE8, 1, screen->unkDF4, screen->unkDE4);
#elif VERSION_EU
            screen->unkEE4(screen, screen->unkDE8, battle->unk438, screen->unkDF4, screen->unkDE4);
#endif
            battle->stepState = 1;
        }
        break;
    case 7:
        if (screen->unkDFA == 0) {
            if (battle->unk440 == 0) {
                battle->stepState = 9;
                battle->unk498.unk1 = 2;
                screen->unkEC4(screen);
            } else {
                battle->stepState = 8;
            }
        }
        break;
    case 3:
        switch (battle->unk424) {
        case 0:
            if (screen->unkDFA == 0) {
                battle->unk498.unk1 = 2;
                screen->unkEC4(screen);
                battle->unk424 = 1;
            }
            break;
        case 1:
            if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
                battle->unk2F4 = 3;
                battle->unk560.unk0[8] = 0;
                battle->stepState = 4;
            }
            break;
        }
        break;
    case 4:
        battle->unk498.unk5 = 1;
        battle->unk498.unk1 = 1;
        screen->unkEC8(screen);
        battle->stepState = 5;
        battle->unk424 = 0;
        break;
    case 5:
        switch (battle->unk424) {
        case 0:
            if (battle->unk498.unk0 == 0 && screen->panels[0].state == 2) {
#if VERSION_US
                screen->unkEE4(screen, screen->unkDE8, 1, screen->unkDF4, screen->unkDE4);
#elif VERSION_EU
                screen->unkEE4(screen, screen->unkDE8, battle->unk438, screen->unkDF4, screen->unkDE4);
#endif
                battle->unk424 = 1;
            }
            break;
        case 1:
            if (screen->unkDFA == 2) {
                battle->stepState = 2;
            }
            break;
        }
        break;
    case 1:
        if (screen->unkDFA == 2) {
            battle->stepState = 2;
        }
        break;
    case 9:
        if (screen->panels[0].state != 0 || battle->unk498.unk0 != 0) {
            break;
        }
    case 8:
        result = 2;
        if (battle->unk440 == 0) {
            result = 1;
        }
        break;
    }
    return result;
}

void func_800860CC(CardBattle *battle, CardScreen *screen) {
    screen->unkE0C[1].unkE = 0;
    screen->unkE0C[1].unk10 = 0;
    screen->unkE0C[2].unk10 = 0;
    screen->unkE0C[3].unk10 = 0;
    screen->unkE0C[4].unk10 = 0;
}

void func_800860E4(CardBattle *battle, CardScreen *screen, s32 offset) {
    CardDrawer drawer;
    s32 i;
    s32 found;
    s32 card;
    s32 id;

    func_800860CC(battle, screen);
    if (screen->sprites[offset + battle->unk43C].isKind16 != 0) {
        screen->unkE0C[1].unk10 |= screen->sprites[offset + battle->unk43C].unk41;
        screen->unkE0C[1].unk10 |= screen->sprites[offset + battle->unk43C].color << 4;
        screen->unkE0C[1].unkE = 1;
    }
    found = 0;
    if (screen->sprites[offset + battle->unk43C].visible != 3) {
        card = battle->cards[screen->sprites[offset + battle->unk43C].index] + 1;
        screen->unkE0C[2].unk10 = card;
        for (i = 0; i < 5; i++) {
            if (D_800A4AE4[i] == battle->cards[screen->sprites[offset + battle->unk43C].index]) {
                found = 1;
            }
        }
        if (screen->sprites[offset + battle->unk43C].isKind16 != 0 && found == 0) {
            screen->unkE0C[4].unk10 = 500;
            screen->unkE0C[4].unk14[2] = 1;
            screen->unkE0C[4].unk14[0] = screen->sprites[offset + battle->unk43C].unk43;
            screen->unkE0C[4].unk14[1] = screen->sprites[offset + battle->unk43C].unk44;
        } else {
            screen->unkE0C[4].unk14[2] = 0;
            screen->unkE0C[4].unk10 = card;
        }
        id = battle->cards[screen->sprites[offset + battle->unk43C].index];
        initCardDrawer(&drawer);
        drawer.setCard(id + 1);
        switch (drawer.card[6]) {
        case 0:
            screen->unkE0C[3].unk10 = 0;
            break;
        case 1:
            screen->unkE0C[3].unk10 = 0x25;
            break;
        case 2:
            screen->unkE0C[3].unk10 = 0x26;
            break;
        case 3:
            screen->unkE0C[3].unk10 = 0x27;
            break;
        case 4:
            screen->unkE0C[3].unk10 = 0x28;
            break;
        case 5:
            screen->unkE0C[3].unk10 = 0x29;
            break;
        }
    } else {
        screen->unkE0C[4].unk14[2] = 0;
        screen->unkE0C[4].unk10 = 500;
    }
}

void func_800863DC(CardBattle *battle, CardScreen *screen, s32 kind) {
    s32 offset = 0;

    switch (kind) {
    case 1:
        offset = 6;
        break;
    case 2:
        offset = 12;
        break;
    }
    func_800860E4(battle, screen, offset);
}

void func_8008642C(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    s32 i;

    if (pile->unkA != 0) {
        for (i = 0; i < 40; i++) {
            battle->unk446[i] = 0;
            battle->unk46F[i] = 0;
            if (i < pile->unkA) {
                if (func_80085760(battle, pile->unkC, pile->unk64[i])) {
                    battle->unk446[i] = 1;
                    battle->unk498.unk6[i] = 0;
                } else {
                    battle->unk498.unk6[i] = 1;
                }
            }
        }
    } else {
        battle->unk498.unk6[0] = 0;
    }
    screen->unkECC(screen);
    if (pile->unk11 == 0) {
        battle->unk498.unk1 = 5;
        screen->unkEC0(screen, pile->unk11);
    } else {
        battle->unk498.unk1 = 11;
    }
    battle->unk423 = 1;
    func_800860CC(battle, screen);
    battle->unk43C = 0;
    battle->unk440 = -1;
}

void func_80086564(CardBattle *battle, CardScreen *screen, s32 all, s32 arg3) {
    s32 i;

    if (all > 0) {
        for (i = 0; i < 40; i++) {
            battle->unk498.unk6[i] = 0;
        }
    } else {
        battle->unk498.unk6[0] = 0;
    }
    func_800860CC(battle, screen);
    battle->unk423 = 1;
    battle->unk498.unk1 = arg3;
    battle->unk43C = 0;
    battle->unk440 = -1;
}

/* Moves the selection by STEP among COUNT cards: the selected card is raised */
void CARDGAME_moveSelection(CardBattle *battle, CardScreen *screen, s32 count, s32 step) {
    SOUND.playSound(0x4001B);
    screen->unkF0C(screen, battle->unk43C, 5, screen->getHandOffset(count, battle->unk43C) + 0x1800, 0x6100);
    screen->sprites[battle->unk43C].unk48 &= ~1;
    screen->sprites[battle->unk43C].moving = 0;
    battle->unk43C += step;
    screen->unkF0C(screen, battle->unk43C, 1, screen->getHandOffset(count, battle->unk43C) + 0x1800, 0x5C00);
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
}

/* Moves the selection by STEP among the cards of PILE (unk64): the selected card is raised */
void CARDGAME_movePileSelection(CardBattle *battle, CardScreen *screen, CardPile *pile, s32 step) {
    SOUND.playSound(0x4001B);
    screen->unkF0C(screen, battle->unk43C, 5, screen->getHandOffset(pile->unkA, battle->unk43C) + 0x1800, 0x6100);
    screen->sprites[battle->unk43C].unk48 &= ~1;
    screen->sprites[battle->unk43C].moving = 0;
    battle->unk43C += step;
    screen->unkF0C(screen, battle->unk43C, 1, screen->getHandOffset(pile->unkA, battle->unk43C) + 0x1800, 0x5C00);
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
}

void func_800868E0(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    s32 i;

    for (i = 0; i < pile->unkA; i++) {
        if (func_80085760(battle, pile->unkC, pile->unk64[i]) && battle->unk46F[i] == 0) {
            battle->unk446[i] = 1;
            screen->sprites[i].unk49 = 0;
        } else {
            battle->unk446[i] = 0;
            if (battle->unk46F[i] == 0) {
                screen->sprites[i].unk49 = 1;
            } else {
                screen->sprites[i].unk49 = 0;
            }
        }
    }
}

s32 func_800869BC(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    s32 ok = 1;
    s32 i;

    if (battle->unk444 < 6) {
        for (i = 0; i < pile->unkA; i++) {
            if (battle->unk446[i] != 0) {
                ok = 0;
                break;
            }
        }
    }
    return ok;
}

void func_80086A10(CardBattle *battle, CardScreen *screen, CardPile *pile, s32 add, s32 card) {
    CardDrawer drawer;

    initCardDrawer(&drawer);
    drawer.setCard(battle->cards[card] + 1);
    if (drawer.card[0] < 6) {
        if (add) {
            pile->unkC[drawer.card[0] - 1] += drawer.card[5];
        } else {
            pile->unkC[drawer.card[0] - 1] -= drawer.card[5];
        }
        screen->setPanelValue(screen, pile->unk11, drawer.card[0] - 1, pile->unkC[drawer.card[0] - 1]);
    }
}

/* Picks or puts back the selected card of PILE (unk64): 1 picked, 2 put back, 0 neither */
s32 CARDGAME_togglePick(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    s32 result = 0;

    if (battle->unk446[battle->unk43C] != 0) {
        if (battle->unk444 < 6) {
            func_80086A10(battle, screen, pile, 0, pile->unk64[battle->unk43C]);
            battle->unk46F[battle->unk43C] = 1;
            screen->unkF1C(screen, battle->unk43C);
            screen->sprites[battle->unk43C].unk48 |= 2;
            result = 1;
            battle->unk444++;
        }
    } else if (battle->unk46F[battle->unk43C] != 0) {
        func_80086A10(battle, screen, pile, 1, pile->unk64[battle->unk43C]);
        battle->unk46F[battle->unk43C] = 0;
        screen->sprites[battle->unk43C].unk48 &= ~2;
        result = 2;
        battle->unk444--;
    }
    return result;
}

/* Reads the pad while a card of PILE (unk64) is being chosen: Left/Right move, Cross picks, Triangle cancels */
void CARDGAME_readChooseInput(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
    if (PAD_PRESSED(PAD_TRIANGLE)) {
        SOUND.playSound(0x800450BD);
        battle->unk440 = -1;
        battle->unk423 = 14;
    }
    if (PAD_PRESSED(PAD_CIRCLE)) {
        battle->unk423 = 11;
    }
    if (pile->unkA != 0) {
        if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) |
            (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_movePileSelection(battle, screen, pile, -1);
            }
        } else if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) |
                   (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < pile->unkA - 1) {
                CARDGAME_movePileSelection(battle, screen, pile, 1);
            }
        } else if (PAD_PRESSED(PAD_CROSS) && battle->unk446[battle->unk43C] != 0) {
            battle->unk423 = 5;
            battle->unk440 = battle->unk43C;
            battle->unk46F[battle->unk440] = 1;
        }
    }
}

/* Reads the pad while cards of PILE (unk64) are being picked: Left/Right move, Cross picks or puts back, Square and Circle end */
void CARDGAME_readPickInput(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
    if (PAD_PRESSED(PAD_SQUARE)) {
        battle->unk423 = 6;
    }
    if (PAD_PRESSED(PAD_CIRCLE)) {
        battle->unk423 = 11;
    }
    if (pile->unkA != 0) {
        if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) |
            (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_movePileSelection(battle, screen, pile, -1);
            }
        } else if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) |
                   (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < pile->unkA - 1) {
                CARDGAME_movePileSelection(battle, screen, pile, 1);
            }
        } else if (PAD_PRESSED(PAD_CROSS) && CARDGAME_togglePick(battle, screen, pile)) {
            battle->unk423 = 4;
        }
    }
}

/* Reads the pad while one of COUNT cards is being chosen: Left/Right move, Triangle cancels */
void CARDGAME_readCountInput(CardBattle *battle, CardScreen *screen, s32 count) {
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
    if (PAD_PRESSED(PAD_TRIANGLE)) {
        SOUND.playSound(0x800450BD);
        battle->unk440 = -1;
        battle->unk423 = 10;
    }
    if (count != 0) {
        if (((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) |
             (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) &&
            battle->unk43C > 0) {
            CARDGAME_moveSelection(battle, screen, count, -1);
        }
        if (((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) |
             (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) &&
            battle->unk43C < count - 1) {
            CARDGAME_moveSelection(battle, screen, count, 1);
        }
    }
}

s32 func_8008747C(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    switch (battle->unk424) {
    case 0:
    default:
        screen->scaleSprite(screen, battle->unk43C, 5, 0x1400, 0x1400);
        battle->unk428 = 0;
        battle->unk424++;
        break;
    case 1:
        battle->unk428 += GFX.funcs.getFrameTime();
        if (battle->unk428 >= 5) {
            battle->unk424++;
        }
        break;
    case 2:
        screen->scaleSprite(screen, battle->unk43C, 5, 0x1000, 0x1000);
        battle->unk428 = 0;
        battle->unk424++;
        break;
    case 3:
        battle->unk428 += GFX.funcs.getFrameTime();
        if (battle->unk428 >= 5) {
            done = 1;
        }
        break;
    }
    return done;
}

/* Choosing cards of PILE (unk64) to play: unk423 queues the next step. -1 while it runs, then 0 or 1 */
s32 CARDGAME_stepChooseCards(CardBattle *battle, CardScreen *screen, CardPile *pile) {
    s32 result = -1;
    /* the match depends on a loop variable of its own for most loops:
       sharing them gives GCC 2.8.1 other registers */
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;
    s32 count;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
        case 2:
            switch (battle->unk420) {
            case 0x99:
                if (pile->unk11 != 0) {
                    CARDGAME_promptText = 0x1C;
                } else {
                    CARDGAME_promptText = 0x19;
                }
                break;
            case 0x9D:
                CARDGAME_promptText = 0x1C;
                break;
            case 0x9C:
                CARDGAME_promptText = 0x1B;
                break;
            case 0x9A:
            case 0x9B:
                CARDGAME_promptText = 0x19;
                break;
            }
            battle->unk42C = 0;
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk440 = 0;
            battle->unk444 = 0;
            break;
        case 5:
            SOUND.playSound(0x4001C);
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 4:
            SOUND.playSound(0x4001C);
            break;
        case 14:
            if (pile->unk11 == 0) {
                battle->unk498.unk1 = 6;
                screen->unkEBC(screen, 0);
            } else {
                battle->unk498.unk1 = 12;
            }
            battle->unk428 = 0;
            battle->unk424 = 0;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 0);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            break;
        case 10:
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk498.unk1 = battle->unk498.unk3;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 0);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            break;
        case 6:
            battle->unk428 = 0;
            battle->unk424 = 0;
            CARDGAME_promptText = screen->unkE0C[0].unk10;
            for (i = 0; i < pile->unkA; i++) {
                if (battle->unk46F[i] != 0) {
                    screen->sprites[i].unk49 = 0;
                    screen->sprites[i].unk48 |= 4;
                } else {
                    screen->sprites[i].unk49 = 1;
                }
            }
            break;
        case 7:
            battle->unk440 = 0;
            battle->unk424 = 0;
            break;
        case 3:
        case 8:
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 11:
            battle->unk498.unk1 = battle->unk498.unk3;
            CARDGAME_promptText = screen->unkE0C[0].unk10;
            battle->unk424 = battle->unk498.unk3;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 0);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            if (battle->unk420 == 0x9A) {
                screen->unkEB0(screen, 5);
            }
            if (pile->unk11 == 0) {
                screen->unkEBC(screen, 0);
            }
            break;
        case 13:
            CARDGAME_promptText = 0x19;
            battle->unk428 = 0;
            battle->unk498.unk1 = battle->unk424 - 1;
            switch (battle->unk420) {
            case 0x99:
            case 0x9A:
            case 0x9D:
                for (j = 0; j < pile->unkA; j++) {
                    if (func_80085760(battle, pile->unkC, pile->unk64[j])) {
                        battle->unk498.unk6[j] = 0;
                    } else {
                        battle->unk498.unk6[j] = 1;
                    }
                }
                break;
            }
            screen->unkEAC(screen, 0, 0, CARDGAME_promptText, 0, 0x42);
            screen->unkEAC(screen, 2, 1, 0, 0x82, 0xA5);
            screen->unkEAC(screen, 4, 2, 0, 0x86, 0x31);
            screen->unkEAC(screen, 3, 1, 0, 0x82, 0x90);
            screen->unkEAC(screen, 1, 3, 0, 0xFD, 0x90);
            if (battle->unk420 == 0x9A) {
                screen->unkEAC(screen, 5, 4, 0x24, 0, 0x14);
            }
            if (pile->unk11 == 0) {
                screen->unkEC0(screen, 0);
            }
            break;
        case 9:
            battle->unk428 = 0;
            battle->unk424 = 0;
            for (j = 0; j < pile->unkA; j++) {
                if (func_80085760(battle, pile->unkC, pile->unk64[j])) {
                    screen->sprites[j].unk49 = 0;
                } else {
                    screen->sprites[j].unk49 = 1;
                }
                if (battle->unk46F[j] != 0) {
                    screen->sprites[j].unk49 = 0;
                    screen->sprites[j].unk48 &= ~4;
                }
            }
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }

    switch (battle->stepState) {
    case 1:
        battle->unk42C = CARDGAME_openStepWindows(battle, screen, 2, CARDGAME_promptText, battle->unk424, battle->unk42C);
        func_800860E4(battle, screen, 0);
        if (battle->unk498.unk3C * 4 + 14 < battle->unk424) {
            battle->unk423 = 3;
            screen->unkF0C(screen, 0, 5, 0x1800, 0x5C00);
            screen->sprites[battle->unk43C].unk48 |= 1;
            screen->sprites[battle->unk43C].moving = 1;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        break;
    case 2:
        screen->scaleSprite(screen, 0, 5, 0x1000, 0x1000);
        if (battle->unk424 > 10) {
            battle->unk423 = 3;
            screen->unkF0C(screen, 0, 5, 0x1800, 0x5C00);
            screen->sprites[battle->unk43C].unk48 |= 1;
            screen->sprites[battle->unk43C].moving = 1;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        break;
    case 3:
        switch (battle->unk420) {
        case 0x99:
            CARDGAME_readChooseInput(battle, screen, pile);
            break;
        case 0x9A:
        case 0x9D:
            CARDGAME_readPickInput(battle, screen, pile);
            break;
        case 0x9B:
        case 0x9C:
            CARDGAME_readCountInput(battle, screen, battle->unk498.unk3C);
            break;
        }
        func_800860E4(battle, screen, 0);
        break;
    case 4:
        if (screen->sprites[battle->unk43C].state == 1) {
            func_800868E0(battle, screen, pile);
            if (func_800869BC(battle, screen, pile)) {
                battle->unk423 = 6;
            } else {
                battle->unk423 = 3;
            }
        }
        func_800860E4(battle, screen, 0);
        break;
    case 5:
        if (func_8008747C(battle, screen)) {
            battle->unk423 = 14;
        }
        func_800860E4(battle, screen, 0);
        break;
    case 14:
        if (pile->unkA * 4 + 5 < battle->unk424) {
            battle->unk423 = 0;
            battle->unk421 = 0;
            battle->unk420 = 0;
            battle->unk421 = 0;
            result = battle->unk440 != -1;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        break;
    case 10:
        if (battle->unk498.unk3C * 4 + 14 < battle->unk424) {
            result = 0;
            battle->unk423 = 0;
            battle->unk421 = 0;
            battle->unk420 = 0;
            battle->unk421 = 0;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        break;
    case 6:
        switch (battle->unk424) {
        case 0:
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 0);
            screen->unkEB0(screen, 5);
            screen->unkF08(screen, battle->unk43C, 5, screen->getHandOffset(pile->unkA, battle->unk43C) + 0x1800, 0x6100);
            screen->sprites[battle->unk43C].unk48 &= ~1;
            screen->sprites[battle->unk43C].moving = 0;
            break;
        case 6:
            screen->unkEE4(screen, 15, 1, 0, 2);
            break;
        }
        if (++battle->unk424 > 18) {
            battle->unk423 = 7;
        }
        break;
    case 7:
        if (PAD_PRESSED(PAD_CROSS)) {
            screen->unkEEC(screen);
            if (battle->unk440 == 0) {
                battle->unk423 = 8;
            } else {
                battle->unk423 = 9;
            }
        } else if (PAD_PRESSED(PAD_UP) || PAD_PRESSED(PAD_DOWN)) {
            battle->unk440 ^= 1;
            SOUND.playSound(0x8004513E);
            screen->unkEF0(screen, battle->unk440);
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk440 = 1;
            screen->unkEF0(screen, 1);
            screen->unkEEC(screen);
            battle->unk423 = 9;
        }
        break;
    case 8:
        switch (battle->unk424) {
        case 20:
            count = 0;
            for (k = 0; k < pile->unkA; k++) {
                if (battle->unk46F[k] != 0) {
                    screen->scaleSprite(screen, k, 6, 0x1400, 0x1400);
                    count++;
                }
            }
            if (count != 0) {
                SOUND.playSound(0x4001C);
            }
            break;
        case 25:
            for (m = 0; m < pile->unkA; m++) {
                if (battle->unk46F[m] != 0) {
                    screen->scaleSprite(screen, m, 6, 0x1000, 0x1000);
                }
            }
            break;
        case 35:
            if (pile->unk11 == 0) {
                battle->unk498.unk1 = 6;
                screen->unkEBC(screen, 0);
            } else {
                battle->unk498.unk1 = 12;
            }
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            break;
        }
        if (++battle->unk424 > 45 && battle->unk498.unk0 == 0) {
            result = 1;
        }
        break;
    case 9:
        switch (battle->unk424) {
        case 6:
            break;
        case 18:
            screen->unkEAC(screen, 0, 0, CARDGAME_promptText, 0, 0x42);
            screen->unkEAC(screen, 4, 2, 0, 0x86, 0x31);
            screen->unkEAC(screen, 5, 4, 0x24, 0, 0x14);
            func_800860E4(battle, screen, 0);
            break;
        }
        if (++battle->unk424 > 30) {
            battle->unk423 = 3;
            screen->unkF08(screen, battle->unk43C, 5, screen->getHandOffset(pile->unkA, battle->unk43C) + 0x1800, 0x5C00);
            screen->sprites[battle->unk43C].unk48 |= 1;
            screen->sprites[battle->unk43C].moving = 1;
        }
        break;
    case 11:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            battle->unk423 = 12;
            battle->unk560.unk0[8] = 0;
            battle->unk2F4 = 3;
        }
        break;
    case 12:
        battle->unk423 = 13;
        break;
    case 13:
        if (((pile->unk11 == 0 && screen->panels[0].state == 2) || (pile->unk11 != 0 && ++battle->unk428 > 10)) &&
            battle->unk498.unk0 == 0) {
            battle->unk423 = 3;
            screen->unkF0C(screen, battle->unk43C, 5, screen->getHandOffset(pile->unkA, battle->unk43C) + 0x1800, 0x5C00);
            screen->sprites[battle->unk43C].unk48 |= 1;
            screen->sprites[battle->unk43C].moving = 1;
            for (n = 0; n < pile->unkA; n++) {
                if (battle->unk46F[n] == 1) {
                    screen->sprites[n].unk49 = 0;
                    screen->sprites[n].unk48 |= 2;
                }
            }
        }
        func_800860E4(battle, screen, 0);
        break;
    }
    return result;
}

void func_800885C0(CardBattle *battle, CardScreen *screen) {
    screen->unkECC(screen);
    battle->unk440 = 0;
    battle->stepState = 1;
    screen->unkEC8(screen);
    battle->unk498.unk5 = 1;
    battle->unk498.unk4 = 1;
    battle->unk498.unk1 = 1;
}

/* Turns the opponent's slot cards over, then counts the panels' values 8 and 9 up to each side's pile unk0 and unk2; 1 when done */
s32 CARDGAME_stepTally(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 counting = 0;
    s32 step;

    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            if (battle->players[0].slotCount + battle->players[1].slotCount == 0) {
                battle->stepState = 3;
                battle->unk424 = 0;
                battle->unk428 = 0;
                battle->unk42C = 0;
                battle->unk430 = 0;
                battle->unk434 = 0;
            } else {
                battle->stepState = 2;
                battle->unk424 = 0;
                battle->unk428 = 0;
                battle->unk434 = 0;
                if (battle->players[0].slotCount > battle->players[1].slotCount) {
                    battle->unk42C = battle->players[0].slotCount;
                } else {
                    battle->unk42C = battle->players[1].slotCount;
                }
                battle->unk42C = battle->unk42C * 6 + 18;
            }
        }
        break;
    case 2:
        if (battle->unk434 >= 6) {
            if (battle->unk428 < battle->players[1].slotCount) {
                screen->unkF28(screen, battle->unk428 + 6);
            }
            battle->unk428++;
            battle->unk434 -= 6;
        }
        if (battle->unk424 > battle->unk42C) {
            battle->stepState = 3;
            battle->unk424 = 0;
            battle->unk428 = 0;
            battle->unk42C = 0;
            battle->unk430 = 0;
            battle->unk434 = 0;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk434 += GFX.funcs.getFrameTime();
        break;
    case 3:
        step = battle->sides[0].pile.unk0 / 60;
        battle->unk428 += step != 0 ? step : 1;
        if (battle->unk428 > battle->sides[0].pile.unk0) {
            battle->unk428 = battle->sides[0].pile.unk0;
        } else {
            counting = 1;
        }
        step = battle->sides[0].pile.unk2 / 60;
        battle->unk42C += step != 0 ? step : 1;
        if (battle->unk42C > battle->sides[0].pile.unk2) {
            battle->unk42C = battle->sides[0].pile.unk2;
        } else {
            counting = 1;
        }
        step = battle->sides[1].pile.unk0 / 60;
        battle->unk430 += step != 0 ? step : 1;
        if (battle->unk430 > battle->sides[1].pile.unk0) {
            battle->unk430 = battle->sides[1].pile.unk0;
        } else {
            counting = 1;
        }
        step = battle->sides[1].pile.unk2 / 60;
        battle->unk434 += step != 0 ? step : 1;
        if (battle->unk434 > battle->sides[1].pile.unk2) {
            battle->unk434 = battle->sides[1].pile.unk2;
        } else {
            counting = 1;
        }
        if (battle->unk424++ > 60) {
            battle->stepState = 4;
            battle->unk424 = 0;
            battle->unk428 = battle->sides[0].pile.unk0;
            battle->unk42C = battle->sides[0].pile.unk2;
            battle->unk430 = battle->sides[1].pile.unk0;
            battle->unk434 = battle->sides[1].pile.unk2;
        } else if (counting) {
            SOUND.playSound(0x800452C6);
        }
        screen->setPanelValue(screen, 0, 8, battle->unk428);
        screen->setPanelValue(screen, 0, 9, battle->unk42C);
        screen->setPanelValue(screen, 1, 8, battle->unk430);
        screen->setPanelValue(screen, 1, 9, battle->unk434);
        break;
    case 4:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->unk424 = 90;
        }
        if (++battle->unk424 > 90) {
            screen->unkEC4(screen);
            battle->stepState = 5;
            battle->unk498.unk1 = 2;
        }
        break;
    case 5:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            done = 1;
        }
        break;
    }
    return done;
}

void func_80088B98(CardBattle *battle, CardScreen *screen, s32 index) {
    u8 *entry = D_800A47C8[index];

    screen->unkEE4(screen, entry[1], 0, 0, 1);
    screen->unkEAC(screen, 5, 5, entry[0], 0, 0x42);
    battle->stepState = 1;
}

/* Waits for window 5 to open, then for Cross or Triangle to close it; 1 once it has closed */
s32 CARDGAME_stepMessage(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    switch (battle->stepState) {
    case 1:
        if (screen->unkE0C[5].state == 2) {
            battle->stepState = 2;
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 3;
            screen->unkEB0(screen, 5);
            screen->unkEE8(screen);
        }
        break;
    case 3:
        if (screen->unkE0C[5].state == 0) {
            battle->stepState = 4;
        }
        break;
    case 4:
        done = 1;
        break;
    }
    return done;
}

/* Moves the selection to the other one of the two cards that func_80088F10 lays out */
void CARDGAME_switchCoinCard(CardBattle *battle, CardScreen *screen) {
    SOUND.playSound(0x4001B);
    screen->unkF0C(screen, battle->unk43C, 5, CARDGAME_coinCardPositions[battle->unk43C][0], CARDGAME_coinCardPositions[battle->unk43C][1]);
    screen->sprites[battle->unk43C].unk48 &= ~1;
    screen->sprites[battle->unk43C].moving = 0;
    battle->unk43C ^= 1;
    screen->unkF0C(screen, battle->unk43C, 1, CARDGAME_coinCardPositions[battle->unk43C][0], CARDGAME_coinCardPositions[battle->unk43C][1] - 0x500);
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
}

void func_80088F10(CardBattle *battle, CardScreen *screen) {
    s32 first = RANDOM.next() & 1;

    battle->unk434 = first;
    battle->unk430 = 0;
    battle->unk42C = 0;
    battle->unk428 = 0;
    battle->unk424 = 0;
    screen->addSprite(screen, 0, 0x7400, 0x6100);
    screen->addSprite(screen, 1, 0xA400, 0x6100);
    if (first != 0) {
        screen->setSpriteCard(screen, 0, 0x57);
        screen->setSpriteCard(screen, 1, 0x58);
    } else {
        screen->setSpriteCard(screen, 1, 0x57);
        screen->setSpriteCard(screen, 0, 0x58);
    }
    screen->sprites[0].visible = 2;
    screen->sprites[1].visible = 2;
    screen->sprites[0].scaleX = 0;
    screen->sprites[0].unk49 = 0;
    screen->sprites[0].unk48 = 0;
    screen->sprites[1].scaleX = 0;
    screen->sprites[1].unk49 = 0;
    screen->sprites[1].unk48 = 0;
    battle->unk43C = 0;
    battle->unk440 = 0;
    battle->stepState = 1;
}

/* The draw for who goes first: the two face-down cards open, the player picks
   one with left/right and cross and both turn over; 1 once it is over, with
   unk440 1 if the player won the draw */
s32 CARDGAME_drawFirstPlayer(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    switch (battle->stepState) {
    case 1:
        switch (battle->unk424) {
        case 0:
            screen->scaleSprite(screen, 0, 10, 0x1000, 0x1000);
            break;
        case 4:
            screen->scaleSprite(screen, 1, 10, 0x1000, 0x1000);
            break;
        }
        battle->unk424++;
        if (battle->unk424 >= 15) {
            battle->stepState = 2;
            screen->unkF0C(screen, 0, 5, 0x7400, 0x5C00);
            screen->sprites[0].moving = 1;
            screen->sprites[0].unk48 |= 1;
        }
        break;
    case 2:
        screen->sprites[battle->unk43C].unk48 |= 1;
        screen->sprites[battle->unk43C].moving = 1;
        if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) ||
            (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            CARDGAME_switchCoinCard(battle, screen);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            battle->stepState = 3;
            battle->unk440 = battle->unk43C;
            battle->unk46F[battle->unk440] = 1;
            battle->unk42C = 0;
            battle->unk428 = 0;
            battle->unk424 = 0;
            SOUND.playSound(0x4001C);
        }
        break;
    case 3:
        if (func_8008747C(battle, screen)) {
            battle->stepState = 4;
            battle->unk42C = 0;
            battle->unk428 = 0;
            battle->unk424 = 0;
            screen->unkF28(screen, battle->unk43C);
        }
        break;
    case 4:
        if (battle->unk424 == 20) {
            screen->unkF28(screen, battle->unk43C ^ 1);
#if VERSION_EU
            screen->unkEAC(screen, 5, 5, battle->unk434 == battle->unk440 ? 0x44 : 0x43, 0, 0x42);
            SOUND.playSound(0x40019);
#endif
        }
        /* the result stays up for a while; cross or triangle skips it */
        if (battle->unk424 >= 31 && (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE))) {
#if VERSION_US
            battle->unk424 = 60;
#elif VERSION_EU
            battle->unk424 = 90;
#endif
        }
#if VERSION_US
        battle->unk424++;
        if (battle->unk424 >= 61) {
#elif VERSION_EU
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 91) {
#endif
            battle->stepState = 5;
            battle->unk42C = 0;
            battle->unk428 = 0;
            battle->unk424 = 0;
#if VERSION_EU
            screen->unkEB0(screen, 5);
#endif
        }
        break;
    case 5:
        switch (battle->unk424) {
        case 0:
            screen->scaleSprite(screen, 0, 5, 0, 0x1000);
            break;
        case 4:
            screen->scaleSprite(screen, 1, 5, 0, 0x1000);
            break;
        }
        battle->unk424++;
        if (battle->unk424 >= 15) {
            battle->stepState = 6;
        }
        break;
    case 6:
        if (battle->unk434 == battle->unk440) {
            battle->unk440 = 1;
        } else {
            battle->unk440 = 0;
        }
        done = 1;
        break;
    }
    return done;
}

void func_800894F8(CardBattle *battle, CardScreen *screen) {
    battle->unk423 = 1;
}

s32 func_80089504(CardBattle *battle, CardScreen *screen) {
    s32 n;

    if (battle->players[0].slotCount > battle->players[1].slotCount) {
        n = battle->players[0].slotCount;
    } else {
        n = battle->players[1].slotCount;
    }
    if (n < 3) {
        n = 3;
    }
    return n * 8 + 14;
}

/* Moves the highlight of a row of cards (kind 0, 1 or 2) by delta */
void CARDGAME_moveTableHighlight(CardBattle *battle, CardScreen *screen, s32 kind, s32 delta) {
    s32 offset = 0;

    SOUND.playSound(0x4001B);
    switch (kind) {
    case 1:
        offset = 6;
        break;
    case 2:
        offset = 12;
        break;
    }
    screen->sprites[offset + battle->unk43C].unk48 &= ~1;
    screen->sprites[offset + battle->unk43C].moving = 0;
    battle->unk43C += delta;
    screen->sprites[offset + battle->unk43C].unk48 |= 1;
    screen->sprites[offset + battle->unk43C].moving = 1;
}

/* Lets the player look over the cards out on the table: the two players' rows
   and the row of the cards played (up and down change rows, left and right
   move along one, triangle leaves); 1 once it is over */
s32 CARDGAME_viewTable(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
            CARDGAME_savedPanelScales[0] = screen->panels[0].scale.state;
            CARDGAME_savedPanelScales[1] = screen->panels[1].scale.state;
            screen->panels[0].scale.state = 0;
            screen->panels[1].scale.state = 0;
            battle->unk498.unk5 = 1;
            battle->unk498.unk1 = 1;
            battle->unk42C = func_80089504(battle, screen);
            battle->unk43C = 0;
            screen->unkECC(screen);
            screen->unkEC8(screen);
            func_800860CC(battle, screen);
            break;
        case 2:
            func_800860CC(battle, screen);
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk434 = 0;
            break;
        case 4:
            func_800860CC(battle, screen);
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk434 = 1;
            break;
        case 3:
            func_800860CC(battle, screen);
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk434 = 2;
            break;
        case 8:
            screen->sprites[battle->unk43C].unk48 &= ~1;
            screen->sprites[battle->unk43C].moving = 0;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 9:
            screen->sprites[battle->unk43C + 12].unk48 &= ~1;
            screen->sprites[battle->unk43C + 12].moving = 0;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 10:
            screen->sprites[battle->unk43C + 6].unk48 &= ~1;
            screen->sprites[battle->unk43C + 6].moving = 0;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 11:
            screen->unkEC4(screen);
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk498.unk1 = 2;
            break;
        case 12:
            screen->unkEE4(screen, 0x17, 0, 0, 1);
            break;
        case 14:
            screen->unkEE8(screen);
            screen->unkEC4(screen);
            break;
        case 15:
            /* nothing to set up: it ends */
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }
    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            if (battle->players[0].slotCount != 0) {
                battle->unk423 = 2;
                battle->unk434 = 0;
            } else if (battle->players[1].slotCount != 0) {
                battle->unk423 = 4;
                battle->unk434 = 1;
            } else if (battle->unk560.unk15 > 0) {
                battle->unk423 = 3;
                battle->unk434 = 2;
            } else {
                battle->unk423 = 12;
                battle->unk434 = 3;
            }
        }
        break;
    case 2:
    case 3:
    case 4:
        battle->unk428 = CARDGAME_openStepWindows(battle, screen, battle->unk434, 0, battle->unk424, battle->unk428);
        func_800860E4(battle, screen, CARDGAME_rowSpriteOffsets[battle->unk434]);
        battle->unk424++;
        if (battle->unk424 >= 11) {
            CARDGAME_moveTableHighlight(battle, screen, battle->unk434, 0);
            battle->unk423 = D_800A47E8[battle->unk434];
        }
        break;
    case 5:
        if (PAD_PRESSED(PAD_UP) && (battle->unk560.unk15 > 0 || battle->players[1].slotCount != 0)) {
            battle->unk423 = 8;
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < battle->players[0].slotCount - 1) {
                CARDGAME_moveTableHighlight(battle, screen, 0, 1);
            }
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_moveTableHighlight(battle, screen, 0, -1);
            }
        }
        func_800863DC(battle, screen, 0);
        if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk423 = 11;
        }
        break;
    case 6:
        if (PAD_PRESSED(PAD_DOWN) && (battle->unk560.unk15 > 0 || battle->players[0].slotCount != 0)) {
            battle->unk423 = 10;
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < battle->players[1].slotCount - 1) {
                CARDGAME_moveTableHighlight(battle, screen, 1, 1);
            }
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_moveTableHighlight(battle, screen, 1, -1);
            }
        }
        func_800863DC(battle, screen, 1);
        if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk423 = 11;
        }
        break;
    case 7:
        if (PAD_PRESSED(PAD_UP)) {
            if (battle->players[1].slotCount != 0) {
                battle->unk42C = 1;
                battle->unk423 = 9;
            }
        } else if (PAD_PRESSED(PAD_DOWN) && battle->players[0].slotCount != 0) {
            battle->unk42C = 0;
            battle->unk423 = 9;
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < battle->unk560.unk15 - 1) {
                CARDGAME_moveTableHighlight(battle, screen, 2, 1);
            }
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_moveTableHighlight(battle, screen, 2, -1);
            }
        }
        if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk423 = 11;
        }
        func_800863DC(battle, screen, 2);
        break;
    case 8:
        battle->unk424++;
        if (battle->unk424 >= 11) {
            if (battle->unk560.unk15 > 0) {
                battle->unk423 = 3;
                battle->unk43C /= 2;
                if (battle->unk43C > battle->unk560.unk15 - 1) {
                    battle->unk43C = battle->unk560.unk15 - 1;
                }
            } else if (battle->players[1].slotCount != 0) {
                battle->unk423 = 4;
                if (battle->unk43C > battle->players[1].slotCount - 1) {
                    battle->unk43C = battle->players[1].slotCount - 1;
                }
            }
        }
        break;
    case 9:
        battle->unk424++;
        if (battle->unk424 >= 11) {
            battle->unk43C = battle->unk43C * 2 + 1;
            if (battle->unk42C != 0) {
                battle->unk423 = 4;
                if (battle->unk43C > battle->players[1].slotCount - 1) {
                    battle->unk43C = battle->players[1].slotCount - 1;
                }
            } else {
                battle->unk423 = 2;
                if (battle->unk43C > battle->players[0].slotCount - 1) {
                    battle->unk43C = battle->players[0].slotCount - 1;
                }
            }
        }
        break;
    case 10:
        battle->unk424++;
        if (battle->unk424 >= 11) {
            if (battle->unk560.unk15 > 0) {
                battle->unk423 = 3;
                battle->unk43C /= 2;
                if (battle->unk43C > battle->unk560.unk15 - 1) {
                    battle->unk43C = battle->unk560.unk15 - 1;
                }
            } else if (battle->players[0].slotCount != 0) {
                battle->unk423 = 2;
                if (battle->unk43C > battle->players[0].slotCount - 1) {
                    battle->unk43C = battle->players[0].slotCount - 1;
                }
            }
        }
        break;
    case 11:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            battle->unk423 = 15;
        }
        break;
    case 12:
        if (screen->unkDFA == 2) {
            battle->unk423 = 13;
        }
        break;
    case 13:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->unk423 = 14;
        }
        break;
    case 14:
        if (screen->unkDFA == 0) {
            battle->unk423 = 15;
        }
        break;
    case 15:
        screen->panels[0].scale.state = CARDGAME_savedPanelScales[0];
        screen->panels[1].scale.state = CARDGAME_savedPanelScales[1];
        done = 1;
        break;
    }
    return done;
}

void func_8008A378(CardBattle *battle, CardScreen *screen, s32 arg2) {
    battle->unk438 = arg2;
    battle->unk423 = 1;
}

s32 func_8008A388(CardBattle *battle, CardScreen *screen) {
    return func_80089504(battle, screen);
}

void func_8008A3A8(CardBattle *battle, CardScreen *screen, s32 kind, s32 delta) {
    CARDGAME_moveTableHighlight(battle, screen, kind, delta);
}

/* Lets the player pick a card out on the table (unk445 bit 0: in their own
   row, bit 1: in the opponent's): 2 once one is picked (its sprite in
   unk440), 1 if there was none or the player backed out */
s32 CARDGAME_pickTableCard(CardBattle *battle, CardScreen *screen) {
    s32 result = 0;
    s32 i;
    /* the match depends on a second loop variable: GCC 2.8.1 gives the first
       two loops other registers than it gives i */
    s32 j;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
            if (battle->unk438 != 0) {
                for (j = 0; j < 3; j++) {
                    battle->unk498.unk6[j + 12] = 1;
                }
                for (j = 0; j < 12; j++) {
                    if (battle->unk446[j] != 0) {
                        battle->unk498.unk6[j] = 0;
                    } else {
                        battle->unk498.unk6[j] = 1;
                    }
                }
                battle->unk498.unk1 = 1;
                battle->unk43C = 0;
                screen->unkECC(screen);
                screen->unkEC8(screen);
                screen->addSprite(screen, 15, 0xE500, 0x6100);
                screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
                screen->sprites[15].scaleX = 0;
                screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
            } else {
                for (i = 0; i < 3; i++) {
                    screen->sprites[i + 12].unk49 = 1;
                }
                for (i = 0; i < 12; i++) {
                    if (battle->unk446[i] != 0) {
                        screen->sprites[i].unk49 = 0;
                    } else {
                        screen->sprites[i].unk49 = 1;
                    }
                }
            }
            battle->unk42C = func_8008A388(battle, screen);
            func_800860CC(battle, screen);
            break;
        case 2:
            func_800860CC(battle, screen);
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk434 = 0;
            break;
        case 3:
            func_800860CC(battle, screen);
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk434 = 1;
            break;
        case 7:
            screen->sprites[battle->unk43C].unk48 &= ~1;
            screen->sprites[battle->unk43C].moving = 0;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 8:
            screen->sprites[battle->unk43C + 6].unk48 &= ~1;
            screen->sprites[battle->unk43C + 6].moving = 0;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 6:
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            screen->unkF1C(screen, battle->unk440);
            SOUND.playSound(0x4001C);
            break;
        case 9:
            screen->unkEC4(screen);
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            battle->unk498.unk1 = 2;
            screen->scaleSprite(screen, 15, 8, 0, 0x1000);
            break;
        case 10:
            screen->unkEC4(screen);
            battle->unk498.unk1 = 2;
            screen->scaleSprite(screen, 15, 8, 0, 0x1000);
            break;
        case 14:
            /* nothing to set up */
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }
    switch (battle->stepState) {
    case 1:
        if (battle->unk438 == 0 || (screen->panels[0].state == 2 && battle->unk498.unk0 == 0)) {
            if (battle->unk445 & 1) {
                if (battle->players[0].slotCount != 0) {
                    battle->unk423 = 2;
                    battle->unk434 = 0;
                } else {
                    battle->unk445 &= ~1;
                }
            }
            if (battle->unk445 & 2) {
                if (battle->players[1].slotCount != 0) {
                    battle->unk423 = 3;
                    battle->unk434 = 1;
                } else {
                    battle->unk445 &= ~2;
                }
            }
            if (battle->unk445 == 0) {
                battle->unk423 = 12;
                battle->unk434 = 3;
            }
        }
        break;
    case 2:
    case 3:
        battle->unk428 = CARDGAME_openStepWindows(battle, screen, battle->unk434, 0, battle->unk424, battle->unk428);
        func_800860E4(battle, screen, CARDGAME_rowSpriteOffsets[battle->unk434]);
        battle->unk424++;
        if (battle->unk424 >= 11) {
            switch (battle->unk434) {
            case 0:
                func_8008A3A8(battle, screen, 0, 0);
                battle->unk423 = 4;
                break;
            case 1:
                func_8008A3A8(battle, screen, 1, 0);
                battle->unk423 = 5;
                break;
            }
        }
        break;
    case 4:
        if ((battle->unk445 & 2) && PAD_PRESSED(PAD_UP) && battle->players[1].slotCount != 0) {
            battle->unk423 = 7;
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < battle->players[0].slotCount - 1) {
                CARDGAME_moveTableHighlight(battle, screen, 0, 1);
            }
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_moveTableHighlight(battle, screen, 0, -1);
            }
        }
        func_800863DC(battle, screen, 0);
        if (battle->unk438 != 0 && PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk423 = 9;
        }
        if (PAD_PRESSED(PAD_CROSS) && battle->unk446[battle->unk43C] != 0) {
            battle->unk423 = 6;
            battle->unk440 = battle->unk43C;
        }
        break;
    case 5:
        if ((battle->unk445 & 1) && PAD_PRESSED(PAD_DOWN) && battle->players[0].slotCount != 0) {
            battle->unk423 = 8;
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
            if (battle->unk43C < battle->players[1].slotCount - 1) {
                CARDGAME_moveTableHighlight(battle, screen, 1, 1);
            }
        }
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
            if (battle->unk43C > 0) {
                CARDGAME_moveTableHighlight(battle, screen, 1, -1);
            }
        }
        func_800863DC(battle, screen, 1);
        if (battle->unk438 != 0 && PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk423 = 9;
        } else if (PAD_PRESSED(PAD_CROSS) && battle->unk446[battle->unk43C + 6] != 0) {
            battle->unk423 = 6;
            battle->unk440 = battle->unk43C + 6;
        }
        break;
    case 6:
        if (screen->sprites[battle->unk440].state == 1) {
            if (battle->unk438 == 0) {
                for (i = 0; i < 3; i++) {
                    screen->sprites[i + 12].unk49 = 0;
                }
                for (i = 0; i < 12; i++) {
                    screen->sprites[i].unk49 = 0;
                }
            }
            battle->unk423 = 14;
        }
        break;
    case 7:
        battle->unk424++;
        if (battle->unk424 >= 11) {
            battle->unk423 = 3;
            if (battle->unk43C > battle->players[1].slotCount - 1) {
                battle->unk43C = battle->players[1].slotCount - 1;
            }
        }
        break;
    case 8:
        battle->unk424++;
        if (battle->unk424 >= 11) {
            battle->unk423 = 2;
            if (battle->unk43C > battle->players[0].slotCount - 1) {
                battle->unk43C = battle->players[0].slotCount - 1;
            }
        }
        break;
    case 11:
        battle->unk423 = 14;
        break;
    case 9:
    case 10:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            battle->unk423 = 13;
        }
        break;
    case 12:
        if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk423 = 10;
        }
        break;
    case 13:
        result = 1;
        break;
    case 14:
        for (i = 0; i < 15; i++) {
            battle->unk46F[i] = 0;
        }
        result = 2;
        battle->unk46F[battle->unk440] = 1;
        break;
    }
    return result;
}

/* Sets up CARDGAME_chooseCard's choice of one of a side's cards: kind 0 among
   pile.unk64 (unkA of them), 1 and 2 among pile.unk14 (unk8), 3 among
   pile.unk78 (unk6) */
void CARDGAME_setupCardChoice(CardBattle *battle, CardScreen *screen, s32 side, s32 kind) {
    s32 i;

    switch (kind) {
    case 0:
        battle->unk438 = side != 0 ? 11 : 5;
        battle->unk434 = battle->sides[side].pile.unkA;
        break;
    case 1:
    case 2:
        if (side == 0) {
            battle->unk438 = 7;
            battle->unk814(battle, battle->sides[0].pile.unk14, battle->sides[0].pile.unk4 | (40 << 16), 2);
        } else {
            battle->unk438 = 13;
            if (kind != 2) {
                battle->unk814(battle, battle->sides[1].pile.unk14, battle->sides[1].pile.unk4 | (40 << 16), 3);
            }
        }
        battle->unk434 = battle->sides[side].pile.unk8;
        break;
    case 3:
        battle->unk438 = side != 0 ? 15 : 9;
        battle->unk434 = battle->sides[side].pile.unk6;
        break;
    }
    for (i = 0; i < 40; i++) {
        if (i < battle->unk434) {
            battle->unk46F[i] = 0;
            if (battle->unk446[i] != 0) {
                battle->unk498.unk6[i] = 0;
            } else {
                battle->unk498.unk6[i] = 1;
            }
        }
    }
    battle->unk423 = 1;
    func_800860CC(battle, screen);
    battle->unk43C = 0;
    battle->unk440 = -1;
}

void func_8008B29C(CardBattle *battle, CardScreen *screen, s32 side) {
    CARDGAME_setupCardChoice(battle, screen, side, 0);
}

/* Moves the highlight along the hand by delta, raising the highlighted card */
void CARDGAME_moveHandHighlight(CardBattle *battle, CardScreen *screen, s32 delta) {
    SOUND.playSound(0x4001B);
    screen->unkF0C(screen, battle->unk43C, 5, screen->getHandOffset(battle->unk434, battle->unk43C) + 0x1800, 0x6100);
    screen->sprites[battle->unk43C].unk48 &= ~1;
    screen->sprites[battle->unk43C].moving = 0;
    battle->unk43C += delta;
    screen->unkF0C(screen, battle->unk43C, 1, screen->getHandOffset(battle->unk434, battle->unk43C) + 0x1800, 0x5C00);
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
}

/* Moves the highlight along the hand with left and right; cross picks a playable card */
void CARDGAME_browseHand(CardBattle *battle, CardScreen *screen) {
    screen->sprites[battle->unk43C].unk48 |= 1;
    screen->sprites[battle->unk43C].moving = 1;
    if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_LEFT))) | (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_LEFT)))) {
        if (battle->unk43C > 0) {
            CARDGAME_moveHandHighlight(battle, screen, -1);
        }
    } else if ((PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT))) | (PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_RIGHT)))) {
        if (battle->unk43C < battle->unk434 - 1) {
            CARDGAME_moveHandHighlight(battle, screen, 1);
        }
    } else if (PAD_PRESSED(PAD_CROSS) && battle->unk446[battle->unk43C] != 0) {
        battle->unk423 = 3;
    }
    battle->unk445 = 0;
}

/* Lets a player pick a card of a row (set up by CARDGAME_setupCardChoice): 2 once one is
   picked, 1 if the player backed out with triangle (mode 1), else 0 */
s32 CARDGAME_chooseCard(CardBattle *battle, CardScreen *screen, s32 mode) {
    s32 result = 0;
    s32 card;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
            battle->unk498.unk1 = battle->unk438;
            switch (battle->unk438) {
            case 5:
                D_800A4C68 = 0x19;
                break;
            case 7:
                D_800A4C68 = 0x1A;
                break;
            case 13:
                D_800A4C68 = 0x1D;
                break;
            case 9:
                D_800A4C68 = 0x1B;
                break;
            case 11:
            case 15:
                D_800A4C68 = 0x1C;
                break;
            }
            if (mode == 2) {
                screen->unkEC0(screen, 0);
            }
            battle->unk42C = 0;
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk440 = 0;
            battle->unk444 = 0;
            break;
        case 3:
            SOUND.playSound(0x4001C);
            /* fallthrough */
        case 2:
            battle->unk428 = 0;
            battle->unk424 = 0;
            break;
        case 4:
            if (mode == 1) {
                screen->scaleSprite(screen, 15, 8, 0, 0x1000);
            }
            battle->unk428 = 0;
            battle->unk424 = 0;
            battle->unk498.unk1 = battle->unk498.unk3;
            screen->unkEB0(screen, 4);
            screen->unkEB0(screen, 0);
            screen->unkEB0(screen, 1);
            screen->unkEB0(screen, 2);
            screen->unkEB0(screen, 3);
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }
    switch (battle->stepState) {
    case 1:
        battle->unk42C = CARDGAME_openStepWindows(battle, screen, 2, D_800A4C68, battle->unk424, battle->unk42C);
        func_800860E4(battle, screen, 0);
        if (battle->unk424 == 2 && mode == 1) {
#if VERSION_US
            screen->addSprite(screen, 15, 0x1800, 0x9000);
#elif VERSION_EU
            screen->addSprite(screen, 15, D_800A5958[SHIFT_PAL_SCREEN][0], D_800A5958[SHIFT_PAL_SCREEN][1]);
#endif
            screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
            screen->sprites[15].scaleX = 0;
            screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
        }
        if (battle->unk498.unk3C * 4 + 14 < battle->unk424) {
            battle->unk423 = 2;
            screen->unkF0C(screen, 0, 5, 0x1800, 0x5C00);
            screen->sprites[battle->unk43C].unk48 |= 1;
            screen->sprites[battle->unk43C].moving = 1;
        }
        battle->unk424++;
        break;
    case 2:
        CARDGAME_browseHand(battle, screen);
        if (mode == 1 && PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            battle->unk445 = 1;
            battle->unk423 = 4;
        }
        func_800860E4(battle, screen, 0);
        break;
    case 3:
        if (func_8008747C(battle, screen)) {
            battle->unk445 = 2;
            battle->unk423 = 4;
            if (mode == 2) {
                screen->unkEBC(screen, 0);
            }
        }
        func_800860E4(battle, screen, 0);
        break;
    case 4:
        if (battle->unk434 * 4 + 5 < battle->unk424++) {
            battle->unk440 = battle->unk43C;
            switch (battle->unk438) {
            case 7:
                /* the picked card goes to the top of the hand */
                card = battle->sides[0].pile.unk14[battle->sides[0].pile.unk4];

                battle->sides[0].pile.unk14[battle->sides[0].pile.unk4] = battle->sides[0].pile.unk14[battle->sides[0].pile.unk4 + battle->unk440];
                battle->sides[0].pile.unk14[battle->sides[0].pile.unk4 + battle->unk440] = card;
                battle->unk440 = battle->sides[0].pile.unk4;
                battle->unk810(battle, battle->sides[0].pile.unk4 + 1, battle->sides[0].pile.unk8 - 1);
                break;
            case 13:
                battle->unk440 = battle->unk30A[battle->unk440 + battle->sides[1].pile.unk4].unk0;
                CARDGAME_sortOpponentCards(battle);
                break;
            }
            battle->unk46F[battle->unk440] = 1;
            result = battle->unk445;
            battle->unk423 = 0;
            battle->unk421 = 0;
            battle->unk420 = 0;
            battle->unk421 = 0;
        }
        break;
    }
    return result;
}

s32 func_8008BC08(CardBattle *battle, CardScreen *screen) {
    s32 i;
    s32 card;

    for (i = 0; i < battle->sides[1].pile.unkA; i++) {
        battle->unk46F[i] = 0;
        if (battle->unk444 < 6 && func_80085760(battle, battle->sides[1].pile.unkC, battle->sides[1].pile.unk64[i])) {
            card = battle->sides[1].pile.unk64[i];
            if (battle->unk35C[card - 40].unk0 != 5) {
                func_80086A10(battle, screen, &battle->sides[1].pile, 0, card);
                battle->unk46F[i] = 1;
                battle->unk444++;
            }
        }
    }
    return 1;
}

/* Sets unk440 to the unk446-marked card of the pile unk438 picks with the highest image unk8 (the lowest when lowest != 0), or -1 */
void CARDGAME_pickBestPileCard(CardBattle *battle, CardScreen *screen, s32 lowest) {
    CardDrawer drawer;
    CardImageHeader *header;
    CardImageHeader *current;
    s32 count = 0;
    s32 card;
    s32 best;
    s32 i;

    /* the match depends on cases 11 and 13 having bodies of their own in
       both switches */
    switch (battle->unk438) {
    case 5:
        count = battle->sides[0].pile.unkA;
        break;
    case 7:
        count = battle->sides[0].pile.unk8;
        break;
    case 11:
        count = battle->sides[1].pile.unkA;
        break;
    case 13:
        count = battle->sides[1].pile.unkA;
        break;
    case 9:
        count = battle->sides[0].pile.unk6;
        break;
    case 15:
        count = battle->sides[1].pile.unk6;
        break;
    }
    header = NULL;
    card = 0;
    initCardDrawer(&drawer);
    best = -1;
    for (i = 0; i < count; i++) {
        if (battle->unk446[i] != 0) {
            switch (battle->unk438) {
            case 5:
                card = battle->sides[0].pile.unk64[i];
                break;
            case 7:
                card = battle->sides[0].pile.unk14[i];
                break;
            case 11:
                card = battle->sides[1].pile.unk64[i];
                break;
            case 13:
                card = battle->sides[1].pile.unk64[i];
                break;
            case 9:
                card = battle->sides[0].pile.unk78[i];
                break;
            case 15:
                card = battle->sides[1].pile.unk78[i];
                break;
            }
            drawer.setCard(battle->cards[card] + 1);
            current = (CardImageHeader *)drawer.card;
            if (best != -1) {
                if (lowest == 0) {
                    if (current->unk8 >= header->unk8) {
                        best = i;
                        header = current;
                    }
                } else if (current->unk8 < header->unk8) {
                    best = i;
                    header = current;
                }
            } else {
                best = i;
                header = current;
            }
        }
    }
    battle->unk440 = best;
}

void func_8008BEF0(CardBattle *battle, CardScreen *screen) {
    s32 i;
    s32 found = 0;

    for (i = battle->sides[1].pile.unk4; i < battle->unk41B; i++) {
        if (battle->unk446[i - battle->sides[1].pile.unk4] != 0) {
            battle->unk440 = i;
            found = 1;
            break;
        }
    }
    if (!found) {
        for (i = 39; battle->sides[1].pile.unk4 < i; i--) {
            if (battle->unk446[i - battle->sides[1].pile.unk4] != 0) {
                break;
            }
        }
        battle->unk440 = i;
    }
    battle->unk46F[battle->unk440] = 1;
}

/* Picks the player's card with the lowest header value unk8 */
void func_8008BFA0(CardBattle *battle, CardScreen *screen) {
    CardDrawer drawer;
    s32 best = battle->sides[0].pile.unk4;
    s32 lowest;
    s32 i;

    initCardDrawer(&drawer);
    lowest = 400;
    for (i = battle->sides[0].pile.unk4; i < 40; i++) {
        drawer.setCard(battle->cards[battle->sides[0].pile.unk14[i]] + 1);
        if (((CardImageHeader *)drawer.card)->unk8 < lowest) {
            lowest = ((CardImageHeader *)drawer.card)->unk8;
            best = i;
        }
    }
    battle->unk440 = best;
}

void func_8008C064(CardBattle *battle, CardScreen *screen, s32 arg2) {
    s32 i;

    screen->unkECC(screen);
    screen->setPanelFlags(screen, arg2);
    battle->unk440 = 0;
    battle->stepState = 1;
    battle->unk438 = arg2;
    screen->addSprite(screen, 15, 0xE500, 0x6100);
    screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
    screen->sprites[15].scaleX = 0;
    screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
    screen->unkEC8(screen);
    battle->unk498.unk5 = 2;
    battle->unk498.unk6[15] = 0;
    for (i = 0; i < 15; i++) {
        battle->unk46F[i] = 0;
    }
    battle->unk498.unk1 = 1;
}

/* The steps of func_8008C064: confirming is allowed when the pile the panel flags (unk438) pick has cards; 1 then, 0 on leaving with triangle, -1 until then */
s32 func_8008C174(CardBattle *battle, CardScreen *screen) {
    s32 result = -1;

    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            battle->stepState = 2;
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_CROSS)) {
            switch (battle->unk438) {
            case 0x400:
            case 0x1400:
                if (battle->sides[0].pile.unk6 != 0) {
                    result = 1;
                }
                break;
            case 0x1000:
                if (battle->sides[0].pile.unk8 != 0) {
                    result = 1;
                }
                break;
            case 0x4000:
                if (battle->sides[0].pile.unkA != 0) {
                    result = 1;
                }
                break;
            case 0x2000:
                if (battle->sides[1].pile.unk8 != 0) {
                    result = 1;
                }
                break;
            case 0x8000:
                if (battle->sides[1].pile.unkA != 0) {
                    result = 1;
                }
                break;
            default:
                result = 1;
                break;
            }
            if (result == 1) {
                SOUND.playSound(0x4001C);
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->unkEC4(screen);
            battle->unk440 = 1;
            battle->stepState = 3;
            screen->scaleSprite(screen, 15, 4, 0, 0x1000);
            battle->unk498.unk1 = 2;
        }
        break;
    case 3:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            screen->removeSprite(screen, 15);
            screen->clearPanelFlags(screen);
            result = 0;
        }
        break;
    }
    return result;
}

/* Shows the last card played as sprite 15; with mode 0, or mode 1 and a colour 6 card before it, the card before it can be picked too */
void func_8008C424(CardBattle *battle, CardScreen *screen, s32 mode) {
    CardDrawer drawer;
    s32 i;
    s32 j;
    s32 ok;
    s32 card;
    s32 sprite;

    screen->unkECC(screen);
    battle->unk440 = 0;
    battle->stepState = 1;
    battle->unk438 = 0;
    screen->addSprite(screen, 15, 0xE500, 0x6100);
    screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
    screen->sprites[15].scaleX = 0;
    screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
    screen->unkEC8(screen);
    for (i = 0; i < 15; i++) {
        battle->unk498.unk6[i] = 1;
    }
    battle->unk498.unk6[15] = 0;
    for (j = 0; j < 15; j++) {
        battle->unk46F[j] = 0;
    }
    if (battle->unk560.unk15 != 0) {
        ok = 0;
        if (mode == 0) {
            ok = 1;
        } else if (mode == 1) {
            card = battle->unk560.unk20[battle->unk560.unk15 - 1].unk0;
            initCardDrawer(&drawer);
            drawer.setCard(battle->cards[card] + 1);
            if (drawer.card[0] == 6) {
                ok = 1;
            }
        }
        if (ok) {
            sprite = battle->unk560.unk15 + 11;
            screen->sprites[sprite].unk48 |= 1;
            battle->unk498.unk6[sprite] = 0;
            battle->unk438 = 1;
        }
    }
    battle->unk498.unk1 = 1;
}

/* The steps of func_8008C424: confirming takes the card before the last one played, if it can be taken; 1 then, 0 on leaving with triangle, -1 until then */
s32 func_8008C5F4(CardBattle *battle, CardScreen *screen) {
    s32 result = -1;
    s32 sprite;

    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            battle->stepState = 2;
            if (battle->unk560.unk15 != 0) {
                screen->sprites[battle->unk560.unk15 + 11].unk48 |= 1;
            }
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_CROSS)) {
            if (battle->unk438 == 1) {
                SOUND.playSound(0x4001C);
                sprite = battle->unk560.unk15 + 11;
                screen->sprites[sprite].unk48 &= ~1;
                battle->unk46F[sprite] = battle->unk560.unk15 + 1;
                result = 1;
                battle->unk560.unk20[battle->unk560.unk15 - 1].unk2 = battle->unk560.unk15;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->unkEC4(screen);
            battle->unk440 = 1;
            battle->stepState = 3;
            screen->scaleSprite(screen, 15, 4, 0, 0x1000);
            battle->unk498.unk1 = 2;
        }
        break;
    case 3:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            screen->removeSprite(screen, 15);
            screen->clearPanelFlags(screen);
            result = 0;
        }
        break;
    }
    return result;
}

/* Shows the card being played as sprite 15 and lets the slots out that its target picks (a side of owner's, both, or a card colour) be chosen: unk46F marks them, unk438 is 1 if there are any */
void CARDGAME_showTargetSlots(CardBattle *battle, CardScreen *screen, s32 owner, s32 target) {
    s32 i;
    s32 ok;
    s32 card;
    s32 j;

    screen->unkECC(screen);
    battle->unk440 = 0;
    battle->stepState = 1;
    screen->addSprite(screen, 15, 0xE500, 0x6100);
    screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
    screen->sprites[15].scaleX = 0;
    screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
    screen->unkEC8(screen);
    battle->unk438 = 0;
    for (i = 0, ok = 0; i < 12; i++, ok = 0) {
        battle->unk46F[i] = 0;
        battle->unk498.unk6[i] = 1;
        screen->sprites[i].unk48 &= ~1;
        if (i < 6) {
            if (i >= battle->players[0].slotCount) {
                continue;
            }
            card = battle->players[0].slots[i].card;
        } else {
            if (i - 6 >= battle->players[1].slotCount) {
                continue;
            }
            card = battle->players[1].slots[i - 6].card;
        }
        switch (target) {
        case 1:
            if (owner == 0) {
                if (i < 6) {
                    ok = 1;
                }
            } else if (i >= 6) {
                ok = 1;
            }
            break;
        case 2:
            if (owner == 0) {
                if (i >= 6) {
                    ok = 1;
                }
            } else if (i < 6) {
                ok = 1;
            }
            break;
        case 3:
            ok = 1;
            break;
        case 4:
            if (screen->getCardColor(screen, card) != 1) {
                ok = 1;
            }
            break;
        case 5:
            if (screen->getCardColor(screen, card) != 2) {
                ok = 1;
            }
            break;
        case 6:
            if (screen->getCardColor(screen, card) == 3) {
                ok = 1;
            }
            break;
        case 7:
            if (screen->getCardColor(screen, card) != 4) {
                ok = 1;
            }
            break;
        case 8:
            if (screen->getCardColor(screen, card) == 6) {
                ok = 1;
            }
            break;
        }
        if (ok) {
            battle->unk46F[i] = 1;
            battle->unk498.unk6[i] = 0;
            battle->unk438 = 1;
        }
    }
    for (j = 0; j < 3; j++) {
        battle->unk498.unk6[j + 12] = 1;
    }
    battle->unk498.unk6[15] = 0;
    battle->unk498.unk1 = 1;
}

/* The steps of CARDGAME_showTargetSlots: highlights the marked slots (unk46F); confirming needs one (unk438); 1 then, 0 on leaving with triangle, -1 until then */
s32 func_8008CBAC(CardBattle *battle, CardScreen *screen) {
    s32 result = -1;
    s32 i;

    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            battle->stepState = 2;
            for (i = 0; i < 12; i++) {
                if (battle->unk46F[i] != 0) {
                    screen->sprites[i].unk48 |= 1;
                }
            }
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_CROSS)) {
            if (battle->unk438 != 0) {
                SOUND.playSound(0x4001C);
                result = 1;
                for (i = 0; i < 12; i++) {
                    if (battle->unk46F[i] != 0) {
                        screen->sprites[i].unk48 &= ~1;
                    }
                }
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->unkEC4(screen);
            battle->unk440 = 1;
            battle->stepState = 3;
            screen->scaleSprite(screen, 15, 4, 0, 0x1000);
            battle->unk498.unk1 = 2;
        }
        break;
    case 3:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            screen->removeSprite(screen, 15);
            screen->clearPanelFlags(screen);
            result = 0;
            for (i = 0; i < 12; i++) {
                if (battle->unk46F[i] != 0) {
                    screen->sprites[i].unk48 &= ~1;
                }
            }
        }
        break;
    }
    return result;
}

/* Counts a card of the colour it has on a side's panel (at most 99); 1 if it has one */
s32 CARDGAME_addColorCount(CardBattle *battle, CardScreen *screen, s32 side, s32 card) {
    CardDrawer drawer;
    CardPile *pile = &battle->sides[side].pile;
    s32 color;
    s32 done = 0;

    initCardDrawer(&drawer);
    drawer.setCard(battle->cards[card] + 1);
    color = drawer.card[0] - 1;
    if (color < 5) {
        if (pile->unkC[color] < 99) {
            pile->unkC[color]++;
        }
        screen->setPanelValue(screen, side, color, pile->unkC[color]);
        done = 1;
    }
    return done;
}

s32 func_8008CF50(CardBattle *battle, CardScreen *screen, s32 index) {
    s32 done = 0;

    switch (battle->unk424) {
    case 0:
    default:
        screen->unkF30(screen, index);
        battle->unk424 = 1;
        break;
    case 1:
        if (screen->sprites[index].state == 1) {
            battle->unk424 = 2;
            screen->scaleSprite(screen, index, 5, 0, 0x1000);
        }
        break;
    case 2:
        if (screen->sprites[index].state == 1) {
            done = 1;
        }
        break;
    }
    return done;
}

void func_8008D044(CardBattle *battle, CardScreen *screen, s32 side, s32 index) {
    switch (battle->players[side].slots[index].side) {
    case 0:
        battle->sides[0].pile.unk78[battle->sides[0].pile.unk6] = battle->players[side].slots[index].card;
        battle->sides[0].pile.unk6++;
        screen->setPanelValue(screen, 0, 7, battle->sides[0].pile.unk6);
        break;
    case 1:
        battle->sides[1].pile.unk78[battle->sides[1].pile.unk6] = battle->players[side].slots[index].card;
        battle->sides[1].pile.unk6++;
        screen->setPanelValue(screen, 1, 7, battle->sides[1].pile.unk6);
        break;
    }
}

s32 func_8008D10C(CardBattle *battle, CardScreen *screen, s32 side, s32 index) {
    s32 ok = 0;

    if (func_8008CF50(battle, screen, side != 0 ? index + 6 : index)) {
        func_8008D044(battle, screen, side, index);
        ok = 1;
    }
    return ok;
}

s32 func_8008D194(CardBattle *battle, CardScreen *screen, s32 index) {
    s32 done = 0;

    switch (battle->unk424) {
    case 0:
    default:
        battle->unk424 = 1;
        screen->sprites[index].moving = 1;
        screen->unkF08(screen, index, 15, -0x5000, 0x6100);
        screen->setSpriteScale(screen, index, 0x1200, 0x1200);
        break;
    case 1:
        if (screen->sprites[index].state == 1) {
            screen->sprites[index].moving = 0;
            screen->sprites[index].scaleX = 0;
            done = 1;
        }
        break;
    }
    return done;
}

void func_8008D288(CardBattle *battle, CardScreen *screen, s32 side, s32 index) {
    switch (battle->players[side].slots[index].side) {
    case 0:
        battle->sides[0].pile.unk64[battle->sides[0].pile.unkA] = battle->players[side].slots[index].card;
        battle->sides[0].pile.unkA++;
        screen->setPanelValue(screen, 0, 6, battle->sides[0].pile.unkA);
        break;
    case 1:
        battle->sides[1].pile.unk64[battle->sides[1].pile.unkA] = battle->players[side].slots[index].card;
        battle->sides[1].pile.unkA++;
        screen->setPanelValue(screen, 1, 6, battle->sides[1].pile.unkA);
        break;
    }
}

s32 func_8008D350(CardBattle *battle, CardScreen *screen, s32 side, s32 index) {
    s32 ok = 0;

    if (func_8008D194(battle, screen, side != 0 ? index + 6 : index)) {
        func_8008D288(battle, screen, side, index);
        ok = 1;
    }
    return ok;
}

/* Calls the screen's unkF38 on the flagged cards in play and plays a sound if
   there were any */
void func_8008D3D8(CardBattle *battle, CardScreen *screen, s32 arg2) {
    s32 found = 0;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (battle->unk46F[i] != 0) {
            if (i < 6) {
                if (i < battle->players[0].slotCount) {
                    screen->unkF38(screen, i, arg2);
                    found = 1;
                }
            } else if (i - 6 < battle->players[1].slotCount) {
                screen->unkF38(screen, i, arg2);
                found = 1;
            }
        }
    }
    if (found) {
        switch (arg2) {
        case 0:
        default:
            SOUND.playSound(0x9C0001);
            break;
        case 1:
            SOUND.playSound(0x9C0000);
            break;
        }
    }
    battle->unk424 = 0;
}

s32 func_8008D4C4(CardBattle *battle, CardScreen *screen, s32 duration) {
    battle->unk424 += GFX.funcs.getFrameTime();
    return duration < battle->unk424;
}

/* Starts moving the marked slots (unk46F) by an offset packed as x << 16 | y */
void CARDGAME_moveMarkedSlots(CardBattle *battle, CardScreen *screen, s32 offset, s32 mode) {
    s16 dx = offset >> 16;
    s16 dy = offset;
    s32 i;

    battle->unk424 = 0;
    battle->unk428 = dx;
    battle->unk42C = dy;
    battle->unk430 = dx;
    if (dx < 0) {
        battle->unk430 = -dx;
    }
    battle->unk434 = dy;
    if (dy < 0) {
        battle->unk434 = -dy;
    }
    for (i = 0; i < 12; i++) {
        if (battle->unk46F[i] != 0) {
            if (i < 6) {
                if (i >= battle->players[0].slotCount) {
                    continue;
                }
                battle->players[0].slots[i].unk2 += dx;
                battle->players[0].slots[i].unk4 += dy;
                if (mode == 2) {
                    battle->players[0].slots[i].unk2 = battle->players[0].slots[i].unk6 * -1;
                }
            } else {
                if (i - 6 >= battle->players[1].slotCount) {
                    continue;
                }
                battle->players[1].slots[i - 6].unk2 += dx;
                battle->players[1].slots[i - 6].unk4 += dy;
                if (mode == 2) {
                    battle->players[1].slots[i - 6].unk2 = battle->players[1].slots[i - 6].unk6 * -1;
                }
            }
            if (mode == 0) {
                screen->unkF30(screen, i);
            } else {
                screen->unkF34(screen, i);
            }
        }
    }
}

/* Counts the marked slots' unk6 and unk8 up or down by one a frame (sign of unk428/unk42C, for unk430/unk434 frames, clamped to 0..99) with their sprites; when both are over, marks the slots whose unk8 reached 0 */
s32 CARDGAME_stepSlotStats(CardBattle *battle, CardScreen *screen) {
    s32 done = 1;
    s32 i;

    if (battle->unk424 < battle->unk430) {
        for (i = 0; i < 12; i++) {
            if (battle->unk46F[i] != 0) {
                if (i < 6) {
                    if (i < battle->players[0].slotCount) {
                        if (battle->unk428 > 0) {
                            if (battle->players[0].slots[i].unk6 < 99) {
                                battle->players[0].slots[i].unk6++;
                                screen->sprites[i].unk43++;
                            }
                        } else if (battle->players[0].slots[i].unk6 > 0) {
                            battle->players[0].slots[i].unk6--;
                            screen->sprites[i].unk43--;
                        }
                    }
                } else if (i - 6 < battle->players[1].slotCount) {
                    if (battle->unk428 > 0) {
                        if (battle->players[1].slots[i - 6].unk6 < 99) {
                            battle->players[1].slots[i - 6].unk6++;
                            screen->sprites[i].unk43++;
                        }
                    } else if (battle->players[1].slots[i - 6].unk6 > 0) {
                        battle->players[1].slots[i - 6].unk6--;
                        screen->sprites[i].unk43--;
                    }
                }
            }
        }
        done = 0;
    }
    if (battle->unk424 < battle->unk434) {
        for (i = 0; i < 12; i++) {
            if (battle->unk46F[i] != 0) {
                if (i < 6) {
                    if (i < battle->players[0].slotCount) {
                        if (battle->unk42C > 0) {
                            if (battle->players[0].slots[i].unk8 < 99) {
                                battle->players[0].slots[i].unk8++;
                                screen->sprites[i].unk44++;
                            }
                        } else if (battle->players[0].slots[i].unk8 > 0) {
                            battle->players[0].slots[i].unk8--;
                            screen->sprites[i].unk44--;
                        }
                    }
                } else if (i - 6 < battle->players[1].slotCount) {
                    if (battle->unk42C > 0) {
                        if (battle->players[1].slots[i - 6].unk8 < 99) {
                            battle->players[1].slots[i - 6].unk8++;
                            screen->sprites[i].unk44++;
                        }
                    } else if (battle->players[1].slots[i - 6].unk8 > 0) {
                        battle->players[1].slots[i - 6].unk8--;
                        screen->sprites[i].unk44--;
                    }
                }
            }
        }
        done = 0;
    }
    battle->unk424++;
    if (done != 0) {
        for (i = 0; i < 12; i++) {
            battle->unk46F[i] = 0;
            if (i < 6) {
                if (i < battle->players[0].slotCount && battle->players[0].slots[i].unk8 <= 0) {
                    battle->unk46F[i] = 1;
                }
            } else if (i - 6 < battle->players[1].slotCount && battle->players[1].slots[i - 6].unk8 <= 0) {
                battle->unk46F[i] = 1;
            }
        }
    }
    return done;
}

/* Marks in unk46F the slots out that the last card played applies to, by its target (unk560.unk20[].unk5): a side, both, or a card colour */
void CARDGAME_markTargetSlots(CardBattle *battle, CardScreen *screen) {
    s32 i;
    s32 n;
    s32 owner;
    s32 card;

    n = battle->unk560.unk15 - 1;
    owner = battle->unk560.unk20[n].unk4;
    for (i = 0; i < 12; i++) {
        battle->unk46F[i] = 0;
        if (i < 6) {
            if (i >= battle->players[0].slotCount) {
                continue;
            }
            card = battle->players[0].slots[i].card;
        } else {
            if (i - 6 >= battle->players[1].slotCount) {
                continue;
            }
            card = battle->players[1].slots[i - 6].card;
        }
        switch (battle->unk560.unk20[n].unk5) {
        case 1:
            if (owner == 0) {
                if (i < 6) {
                    battle->unk46F[i] = 1;
                }
            } else if (i >= 6) {
                battle->unk46F[i] = 1;
            }
            break;
        case 2:
            if (owner == 0) {
                if (i >= 6) {
                    battle->unk46F[i] = 1;
                }
            } else if (i < 6) {
                battle->unk46F[i] = 1;
            }
            break;
        case 3:
            battle->unk46F[i] = 1;
            break;
        case 4:
            if (screen->getCardColor(screen, card) != 1) {
                battle->unk46F[i] = 1;
            }
            break;
        case 5:
            if (screen->getCardColor(screen, card) != 2) {
                battle->unk46F[i] = 1;
            }
            break;
        case 6:
            if (screen->getCardColor(screen, card) == 3) {
                battle->unk46F[i] = 1;
            }
            break;
        case 7:
            if (screen->getCardColor(screen, card) != 4) {
                battle->unk46F[i] = 1;
            }
            break;
        case 8:
            if (screen->getCardColor(screen, card) == 6) {
                battle->unk46F[i] = 1;
            }
            break;
        }
    }
}

void func_8008DBC8(CardBattle *battle, CardScreen *screen) {
    battle->stepState = 1;
}

/* Removes the slots marked in unk46F: slides the cards after them left on screen, then moves their slots and sprites down and shrinks slotCount; 1 when over */
s32 CARDGAME_removeMarkedSlots(CardBattle *battle, CardScreen *screen) {
    s32 result = 0;
    s32 side, i, j, count;
    /* the match depends on case 3 having variables of its own */
    s32 player, k;
    s32 from, to;
    s8 *marks;
    s8 mark;
    CardSprite sprite;

    switch (battle->stepState) {
    case 1:
        D_800A4C86[0] = D_800A4C86[1] = 0;
        D_800A4C84[0] = D_800A4C84[1] = 0;
        for (side = 0; side < 2; side++) {
            marks = &battle->unk46F[side * 6];
            for (i = 0; i < battle->players[side].slotCount; i++) {
                if (marks[i] == 1) {
                    D_800A4C86[side]++;
                }
            }
            count = 0;
            for (i = 0; i < battle->players[side].slotCount - 1; i++) {
                if (marks[i] == 1) {
                    for (j = i + 1; j < battle->players[side].slotCount; j++) {
                        if (marks[j] == 0) {
                            mark = marks[i];
                            marks[i] = marks[j];
                            marks[j] = mark;
                            D_800A4C6C[side][count][0] = i;
                            D_800A4C6C[side][count][1] = j;
                            count++;
                            break;
                        }
                    }
                }
            }
            D_800A4C84[side] = count;
            if (side == 0) {
                for (i = 0; i < count; i++) {
#if VERSION_US
                    screen->unkF08(screen, D_800A4C6C[0][i][1], 10, D_800A4C6C[0][i][0] * 0x2900 + 0x1800, 0x9000);
#elif VERSION_EU
                    screen->unkF08(screen, D_800A4C6C[0][i][1], 10,
                                   D_800A5958[SHIFT_PAL_SCREEN][0] + D_800A4C6C[0][i][0] * 0x2900,
                                   D_800A5958[SHIFT_PAL_SCREEN][1]);
#endif
                }
            } else {
                for (i = 0; i < count; i++) {
#if VERSION_US
                    screen->unkF08(screen, D_800A4C6C[1][i][1] + 6, 10, D_800A4C6C[1][i][0] * 0x2900 + 0x1800, 0x3200);
#elif VERSION_EU
                    screen->unkF08(screen, D_800A4C6C[1][i][1] + 6, 10,
                                   D_800A5958[SHIFT_PAL_SCREEN][2] + D_800A4C6C[1][i][0] * 0x2900,
                                   D_800A5958[SHIFT_PAL_SCREEN][3]);
#endif
                }
            }
        }
        if (D_800A4C86[0] + D_800A4C86[1] != 0) {
            battle->stepState = 2;
            battle->unk424 = 20;
        } else {
            battle->stepState = 4;
        }
        break;
    case 2:
        battle->unk424 -= GFX_FUNCS.getFrameTime();
        if (battle->unk424 <= 0) {
            battle->stepState = 3;
        }
        break;
    case 3:
        for (player = 0; player < 2; player++) {
            for (k = 0; k < D_800A4C84[player]; k++) {
                from = D_800A4C6C[player][k][0];
                to = D_800A4C6C[player][k][1];
                battle->players[player].slots[from] = battle->players[player].slots[to];
                from += player * 6;
                to += player * 6;
                sprite = screen->sprites[from];
                screen->sprites[from] = screen->sprites[to];
                screen->sprites[to] = sprite;
            }
            battle->players[player].slotCount -= D_800A4C86[player];
            for (k = 0; k < 6; k++) {
                if (k >= battle->players[player].slotCount) {
                    screen->removeSprite(screen, player * 6 + k);
                    screen->sprites[player * 6 + k].scaleX = 0;
                }
            }
        }
        battle->stepState = 4;
        break;
    case 4:
        result = 1;
        break;
    }
    return result;
}

/* Marks in unk446 the cards of a side's unk64 (kind 2), unk14 (3) or unk78 (4) whose colour has its bit (D_800A47F8) in flags (kind 16 cards only with flags bit 0, the others with bit 1); 1 if any */
s32 CARDGAME_markPileCardsByColor(CardBattle *battle, CardScreen *screen, s32 side, s32 kind, s32 flags) {
    CardDrawer drawer;
    s32 found;
    s32 count = 0;
    s32 card;
    s32 i;
    s32 ok;
    s32 j;
    s32 id;

    found = 0;
    switch (kind) {
    case 2:
        count = battle->sides[side].pile.unkA;
        break;
    case 3:
        count = battle->sides[side].pile.unk8;
        break;
    case 4:
        count = battle->sides[side].pile.unk6;
        break;
    }
    card = 0;
    for (i = 0; i < count; i++) {
        battle->unk446[i] = 0;
        switch (kind) {
        case 2:
            card = battle->sides[side].pile.unk64[i];
            break;
        case 3:
            card = battle->sides[side].pile.unk14[i + battle->sides[side].pile.unk4];
            break;
        case 4:
            card = battle->sides[side].pile.unk78[i];
            break;
        }
        id = battle->cards[card];
        ok = 0;
        initCardDrawer(&drawer);
        drawer.setCard(id + 1);
        if (drawer.card[3] == 0x10) {
            ok = flags & 1;
        } else if (flags & 2) {
            ok = 1;
        }
        if (ok) {
            for (j = 0; j < 6; j++) {
                if ((flags & D_800A47F8[j]) && drawer.card[0] == j + 1) {
                    battle->unk446[i] = 1;
                    found = 1;
                    break;
                }
            }
        }
    }
    return found;
}

/* Marks in unk446 the slots of the sides flags picks (0x100 its own, 0x200 the other) whose card colour has its bit (D_800A47F8) in flags; 1 if any */
s32 CARDGAME_markSlotsByColor(CardBattle *battle, CardScreen *screen, s32 arg2, s32 flags) {
    CardDrawer drawer;
    s32 found = 0;
    s32 card = 0;
    s32 i;
    s32 skip;
    s32 j;

    initCardDrawer(&drawer);
    battle->unk445 = 0;
    for (i = 0, skip = 0; i < 15; i++, skip = 0) {
        battle->unk446[i] = 0;
        if (i < 6) {
            if ((arg2 == 0 && (flags & 0x100)) || (arg2 != 0 && (flags & 0x200))) {
                battle->unk445 |= 1;
                if (i < battle->players[0].slotCount) {
                    card = battle->players[0].slots[i].card;
                } else {
                    skip = 1;
                }
            } else {
                skip = 1;
            }
        } else if (i < 12) {
            if ((arg2 == 0 && (flags & 0x200)) || (arg2 != 0 && (flags & 0x100))) {
                battle->unk445 |= 2;
                if (i - 6 < battle->players[1].slotCount) {
                    card = battle->players[1].slots[i - 6].card;
                } else {
                    skip = 1;
                }
            } else {
                skip = 1;
            }
        } else {
            skip = 1;
        }
        if (!skip) {
            drawer.setCard(battle->cards[card] + 1);
            for (j = 0; j < 6; j++) {
                if ((flags & D_800A47F8[j]) && drawer.card[0] == j + 1) {
                    battle->unk446[i] = 1;
                    found = 1;
                    break;
                }
            }
        }
    }
    return found;
}

void func_8008E68C(CardBattle *battle, CardScreen *screen, s32 side) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = battle->sides[side].pile.unkA;
    battle->unk42C = battle->sides[side].pile.unk6;
    battle->unk430 = 0;
}

/* Counts a side's unk64 cards over to unk78 on its panel, one every 7 frames, then moves them; 1 when done */
s32 CARDGAME_discardHand(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;
    s32 more;
    s32 i;

    switch (battle->stepState) {
    case 1:
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk430 += GFX.funcs.getFrameTime();
        if (battle->unk430 >= 7) {
            more = 0;
            if (battle->unk428 > 0) {
                more = 1;
                battle->unk428--;
                battle->unk42C++;
            }
            if (!more) {
                battle->stepState = 2;
            }
            screen->setPanelValue(screen, side, 6, battle->unk428);
            screen->setPanelValue(screen, side, 7, battle->unk42C);
            battle->unk430 -= 7;
        }
        break;
    case 2:
        for (i = 0; i < battle->sides[side].pile.unkA; i++) {
            battle->sides[side].pile.unk78[battle->sides[side].pile.unk6] = battle->sides[side].pile.unk64[i];
            battle->sides[side].pile.unk6++;
        }
        battle->sides[side].pile.unkA = 0;
        done = 1;
        break;
    }
    return done;
}

void func_8008E8B0(CardBattle *battle, CardScreen *screen, s32 arg2, s32 arg3) {
    battle->unk430 = arg3;
    battle->unk434 = arg2;
    battle->unk423 = 1;
}

/* Moves a side's colour value (pile.unkC[color]) one step each unk430 frames towards using up unk434 (up to 99, down to 0), on its panel; 1 when done */
s32 CARDGAME_stepColorValue(CardBattle *battle, CardScreen *screen, s32 side, s32 color) {
    s32 done = 0;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
            screen->setPanelFlags(screen, 1 << (color * 2) << side);
            battle->unk424 = 0;
            battle->unk428 = 0;
            break;
        case 2:
            screen->clearPanelFlags(screen);
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }
    switch (battle->stepState) {
    case 1:
        if (battle->unk424 == battle->unk430 / 2) {
            if (battle->unk434 > 0) {
                if (battle->sides[side].pile.unkC[color] < 99) {
                    battle->sides[side].pile.unkC[color]++;
                }
                battle->unk434--;
                SOUND.playSound(0x800452C6);
            } else {
                if (battle->sides[side].pile.unkC[color] != 0) {
                    battle->sides[side].pile.unkC[color]--;
                }
                battle->unk434++;
                SOUND.playSound(0x800452C6);
            }
            screen->setPanelValue(screen, side, color, battle->sides[side].pile.unkC[color]);
        }
        battle->unk424++;
        if (battle->unk424 > battle->unk430) {
            if (battle->unk434 == 0 || battle->sides[side].pile.unkC[color] == 0) {
                battle->unk423 = 2;
            } else {
                battle->unk423 = 1;
            }
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

void func_8008EB08(CardBattle *battle, CardScreen *screen) {
    func_8008E8B0(battle, screen, -0x80, 0x10);
    battle->unk438 = 0;
}

/* Counts both sides' colour values (pile.unkC) down by one each unk430 frames, on the panels, until they are all 0; 1 when done */
s32 CARDGAME_drainColorValues(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 side;
    s32 i;
    s32 any;
    s32 j;
    s32 k;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
            screen->setPanelFlags(screen, 0x3FF);
            battle->unk424 = 0;
            battle->unk428 = 0;
            break;
        case 2:
            screen->clearPanelFlags(screen);
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }
    switch (battle->stepState) {
    case 1:
        if (battle->unk424 == battle->unk430 / 2) {
            for (side = 0; side < 2; side++) {
                for (i = 0; i < 5; i++) {
                    if (battle->sides[side].pile.unkC[i] != 0) {
                        battle->sides[side].pile.unkC[i]--;
                    }
                    screen->setPanelValue(screen, side, i, battle->sides[side].pile.unkC[i]);
                }
            }
        }
        battle->unk424++;
        if (battle->unk424 > battle->unk430) {
            any = 0;
            for (j = 0; j < 2; j++) {
                for (k = 0; k < 5; k++) {
                    if (battle->sides[j].pile.unkC[k] != 0) {
                        any = 1;
                    }
                }
            }
            if (any) {
                battle->unk423 = 1;
            } else {
                battle->unk423 = 2;
            }
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

void func_8008ED28(CardBattle *battle, CardScreen *screen) {
    battle->unk424 = 0;
    battle->stepState = 1;
    screen->unkEA8(screen, battle->unk560.unk15 - 2);
}

/* Puts the card played before the last one (unk560.unk20[unk15 - 2]) on its side's unk78 once its sprite has turned; 1 when done */
s32 CARDGAME_discardPrevCard(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 side;
    s32 n;
    s32 i;

    switch (battle->stepState) {
    case 1:
        if (func_8008CF50(battle, screen, battle->unk560.unk15 + 10)) {
            battle->unk428 = 10;
            battle->stepState = 2;
            side = battle->unk560.unk20[battle->unk560.unk15 - 2].unk4;
            battle->sides[side].pile.unk78[battle->sides[side].pile.unk6] = battle->unk560.unk20[battle->unk560.unk15 - 2].unk0;
            battle->sides[side].pile.unk6++;
            screen->setPanelValue(screen, 0, 7, battle->sides[0].pile.unk6);
            screen->setPanelValue(screen, 1, 7, battle->sides[1].pile.unk6);
        }
        break;
    case 2:
        battle->unk428 -= GFX_FUNCS.getFrameTime();
        if (battle->unk428 <= 0) {
            battle->stepState = 3;
            n = battle->unk560.unk15 - 1;
            if (n >= 2) {
                battle->unk560.unk20[battle->unk560.unk15 - 3].unk2 = 0;
            }
            for (i = 0; i < 15; i++) {
                screen->sprites[i].unk3E[n - 1] = 0;
            }
        }
        break;
    case 3:
        done = 1;
        break;
    }
    return done;
}

s32 func_8008EF20(CardBattle *battle, CardScreen *screen) {
    s32 card = battle->unk560.unk20[battle->unk560.unk15 - 1].unk0;

    battle->unk305++;
    battle->unk304 = card + 1;
    return 1;
}

void func_8008EF50(CardBattle *battle, CardScreen *screen, s32 side, s32 which) {
    s32 card;

    screen->addSprite(screen, 17, 0xE500, 0x6100);
    card = 0;
    screen->sprites[17].scaleX = 0;
    switch (which) {
    case 0:
        card = battle->sides[side].pile.unk64[battle->unk440];
        battle->unk438 = card;
        break;
    case 1:
        card = battle->sides[side].pile.unk14[battle->unk440];
        battle->unk438 = card;
        break;
    }
    screen->setSpriteCard(screen, 17, card);
    screen->scaleSprite(screen, 17, 8, 0x1000, 0x1000);
    battle->unk424 = 0;
    battle->stepState = 1;
}

/* Moves sprite 17 to the side's spot, then puts card unk438 on the side's unk78 pile and takes entry unk440 out of the pile it came from (from 0: unk64, from 1: unk14 after unk4); 1 when over */
s32 CARDGAME_discardPickedCard(CardBattle *battle, CardScreen *screen, s32 side, s32 from) {
    s32 done = 0;
    /* the match depends on the loops of from 1 having a variable of their own */
    s32 i, j;

    switch (battle->stepState) {
    case 1:
        battle->unk424 += GFX_FUNCS.getFrameTime();
        if (battle->unk424 >= 21) {
            screen->unkF08(screen, 17, 10, D_800A4804[side][0], D_800A4804[side][1]);
            screen->setSpriteScale(screen, 17, 0, 0);
            battle->stepState = 2;
        }
        break;
    case 2:
        if (screen->sprites[17].state == 1) {
            battle->stepState = 3;
            battle->unk424 = 0;
            battle->sides[side].pile.unk78[battle->sides[side].pile.unk6] = battle->unk438;
            battle->sides[side].pile.unk6++;
            switch (from) {
            case 0:
                for (i = battle->unk440; i < battle->sides[side].pile.unkA - 1; i++) {
                    battle->sides[side].pile.unk64[i] = battle->sides[side].pile.unk64[i + 1];
                }
                screen->setPanelValue(screen, side, 6, --battle->sides[side].pile.unkA);
                break;
            case 1:
                if (side == 0) {
                    for (i = battle->unk440; i >= battle->sides[side].pile.unk4 + 1; i--) {
                        battle->sides[side].pile.unk14[i] = battle->sides[side].pile.unk14[i - 1];
                    }
                    battle->sides[side].pile.unk4++;
                    battle->sides[side].pile.unk8--;
                } else {
                    for (j = battle->unk440; j >= battle->sides[side].pile.unk4 + 1; j--) {
                        battle->sides[side].pile.unk14[j] = battle->sides[side].pile.unk14[j - 1];
                        battle->unk30A[j] = battle->unk30A[j - 1];
                    }
                    if (++battle->unk41B >= 40) {
                        battle->unk41B = 39;
                    }
                    if (++battle->unk41C >= 40) {
                        battle->unk41C = 39;
                    }
                    battle->sides[side].pile.unk4++;
                    battle->sides[side].pile.unk8--;
                    for (j = 39; j >= 0; j--) {
                        battle->unk30A[j].unk0 = j;
                    }
                }
                screen->setPanelValue(screen, side, 5, battle->sides[side].pile.unk8);
                break;
            }
            screen->setPanelValue(screen, side, 7, battle->sides[side].pile.unk6);
        }
        break;
    case 3:
        battle->unk424 += GFX_FUNCS.getFrameTime();
        if (battle->unk424 >= 46) {
            battle->stepState = 4;
        }
        break;
    case 4:
        done = 1;
        break;
    }
    return done;
}

/* Adds card unk440 of a side's unk78 (which 4) or unk14 to its unk64 */
void CARDGAME_takeCardToHand(CardBattle *battle, CardScreen *screen, s32 side, s32 which) {
    s32 card;
    s32 i;

    battle->unk438 = battle->sides[side].pile.unkA;
    if (which == 4) {
        card = battle->sides[side].pile.unk78[battle->unk440];
    } else {
        card = battle->sides[side].pile.unk14[battle->unk440];
    }
    battle->sides[side].pile.unk64[battle->sides[side].pile.unkA] = card;
    battle->sides[side].pile.unkA++;
    if (battle->unk438 != 0) {
        if (side == 0) {
            battle->unk498.unk1 = 5;
        } else {
            battle->unk498.unk1 = 11;
            battle->unk498.unk4 = 1;
        }
    } else if (side == 0) {
        battle->unk498.unk1 = 17;
    } else {
        battle->unk498.unk1 = 18;
        battle->unk498.unk4 = 1;
    }
    screen->unkEC0(screen, side);
    for (i = 0; i < 40; i++) {
        battle->unk498.unk6[i] = 0;
    }
    battle->stepState = 1;
}

/* Moves the card just put in the hand into place, then takes card unk440 out of the deck (or out of the used pile when which is 4) */
s32 CARDGAME_drawFromDeck(CardBattle *battle, CardScreen *screen, s32 side, s32 which) {
    CardDrawer drawer;
    s32 done = 0;
    /* the match depends on a variable of its own for most loops and states */
    s32 ready;
    s32 closed;
    s32 index;
    s32 top;
    s32 last;
    s32 card;
    s32 drawn;
    s32 i;
    s32 j;
    s32 k;
    s32 swap;
    s32 x;

    switch (battle->stepState) {
    case 1:
        ready = 0;
        if (side == 0) {
            ready = screen->panels[0].state == 2;
        } else if (screen->panels[1].state == 2) {
            ready = 1;
        }
        last = battle->sides[side].pile.unkA - 1;
        screen->sprites[last].x = 0x14A00;
        if (ready && battle->unk498.unk0 == 0) {
            x = screen->getHandOffset(battle->sides[side].pile.unkA, last);
            screen->sprites[last].scaleX = 0x1000;
            screen->unkF08(screen, last, 15, x + 0x1800, 0x6100);
            battle->stepState = 2;
        }
        break;
    case 2:
        index = battle->sides[side].pile.unkA - 1;
        if (screen->sprites[index].state == 1) {
            if (which == 4) {
                for (i = battle->unk440; i < battle->sides[side].pile.unk6 - 1; i++) {
                    battle->sides[side].pile.unk78[i] = battle->sides[side].pile.unk78[i + 1];
                }
                battle->sides[side].pile.unk6--;
                battle->stepState = 4;
                battle->unk424 = 45;
            } else {
                if (side == 0) {
                    for (j = battle->unk440; j >= battle->sides[0].pile.unk4 + 1; j--) {
                        battle->sides[0].pile.unk14[j] = battle->sides[0].pile.unk14[j - 1];
                    }
                } else {
                    if (battle->unk440 < battle->unk41B) {
                        for (i = battle->unk440; i >= battle->sides[1].pile.unk4 + 1; i--) {
                            battle->sides[1].pile.unk14[i] = battle->sides[1].pile.unk14[i - 1];
                            battle->unk30A[i] = battle->unk30A[i - 1];
                        }
                    } else {
                        i = battle->unk440;
                        if (battle->unk30A[i].unk1 == 7) {
                            for (; i >= battle->sides[1].pile.unk4 + 1; i--) {
                                battle->sides[1].pile.unk14[i] = battle->sides[1].pile.unk14[i - 1];
                                battle->unk30A[i] = battle->unk30A[i - 1];
                            }
                            battle->unk41B++;
                            battle->unk41C++;
                        } else {
                            swap = battle->sides[1].pile.unk14[i];
                            battle->sides[1].pile.unk14[i] = battle->sides[1].pile.unk14[39];
                            battle->sides[1].pile.unk14[39] = swap;
                            for (i = 39; i >= battle->sides[1].pile.unk4 + 1; i--) {
                                battle->sides[1].pile.unk14[i] = battle->sides[1].pile.unk14[i - 1];
                                battle->unk30A[i] = battle->unk30A[i - 1];
                            }
                            battle->unk41B++;
                            battle->unk41C++;
                        }
                    }
                    for (k = 39; k >= 0; k--) {
                        battle->unk30A[k].unk0 = k;
                    }
                }
                battle->sides[side].pile.unk4++;
                battle->sides[side].pile.unk8--;
                card = battle->sides[side].pile.unk64[index];
                initCardDrawer(&drawer);
                drawer.setCard(battle->cards[card] + 1);
                if (drawer.card[0] < 6) {
                    battle->stepState = 3;
                    screen->unkF1C(screen, index);
                } else {
                    battle->stepState = 4;
                    battle->unk424 = 45;
                }
            }
            screen->setPanelValue(screen, 0, 5, battle->sides[0].pile.unk8);
            screen->setPanelValue(screen, 0, 6, battle->sides[0].pile.unkA);
            screen->setPanelValue(screen, 0, 7, battle->sides[0].pile.unk6);
            screen->setPanelValue(screen, 1, 5, battle->sides[1].pile.unk8);
            screen->setPanelValue(screen, 1, 6, battle->sides[1].pile.unkA);
            screen->setPanelValue(screen, 1, 7, battle->sides[1].pile.unk6);
        }
        break;
    case 3:
        top = battle->sides[side].pile.unkA - 1;
        if (screen->sprites[top].state == 1) {
            battle->stepState = 4;
            battle->unk424 = 45;
            drawn = battle->sides[side].pile.unk64[top];
            initCardDrawer(&drawer);
            drawer.setCard(battle->cards[drawn] + 1);
            if (drawer.card[0] < 6) {
                if (battle->sides[side].pile.unkC[drawer.card[0] - 1] < 99) {
                    battle->sides[side].pile.unkC[drawer.card[0] - 1]++;
                }
                screen->setPanelValue(screen, side, drawer.card[0] - 1, battle->sides[side].pile.unkC[drawer.card[0] - 1]);
            }
        }
        break;
    case 4:
        battle->unk424 -= GFX.funcs.getFrameTime();
        if (battle->unk424 <= 0) {
            battle->stepState = 5;
            screen->unkEBC(screen, side);
            battle->unk498.unk1 = battle->unk498.unk3;
        }
        break;
    case 5:
        closed = 0;
        if (side == 0) {
            closed = screen->panels[0].state == 0;
        } else if (screen->panels[1].state == 0) {
            closed = 1;
        }
        if (closed && battle->unk498.unk0 == 0) {
            battle->stepState = 6;
        }
        break;
    case 6:
        done = 1;
        break;
    }
    return done;
}

void func_8008FD44(CardBattle *battle, CardScreen *screen, s32 side) {
    battle->unk424 = 0;
    battle->unk434 = 0;
    battle->unk428 = battle->sides[side].pile.unk6;
    battle->unk42C = battle->sides[side].pile.unk8;
    battle->stepState = 1;
}

/* Counts the panel values 7 down into 5, then puts the side's unk78 cards back
   into its deck (unk14); 1 once done */
s32 CARDGAME_returnUsedCards(CardBattle *battle, CardScreen *screen, s32 side) {
    CardPile *pile;
    s16 *deck;
    s16 *used;
    s32 done = 0;
    s32 more;
    s32 i;
    s32 j;

    switch (battle->stepState) {
    case 1:
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk434 += GFX.funcs.getFrameTime();
        if (battle->unk434 >= 7) {
            more = 0;
            if (battle->unk428 > 0) {
                more = 1;
                battle->unk428--;
                battle->unk42C++;
            }
            if (!more) {
                battle->stepState = 2;
            }
            screen->setPanelValue(screen, side, 7, battle->unk428);
            screen->setPanelValue(screen, side, 5, battle->unk42C);
            battle->unk434 -= 7;
        }
        break;
    case 2:
        pile = &battle->sides[side].pile;
        deck = pile->unk14;
        used = pile->unk78;
        if (side == 0) {
            j = pile->unk4 - 1;
            for (i = pile->unk6 - 1; i >= 0; i--) {
                deck[j--] = used[i];
                pile->unk4--;
                pile->unk8++;
            }
            pile->unk6 = 0;
            battle->unk810(battle, pile->unk4, pile->unk8);
        } else {
            for (i = pile->unk6 - 1; i >= 0; i--) {
                pile->unk4--;
                pile->unk8++;
                for (j = pile->unk4; j < 40; j++) {
                    deck[j] = deck[j + 1];
                    battle->unk30A[j] = battle->unk30A[j + 1];
                }
                battle->unk41B--;
                battle->unk41C--;
                deck[39] = used[i];
                battle->unk30A[39].unk1 = 7;
            }
            for (i = 39; i >= 0; i--) {
                battle->unk30A[i].unk0 = i;
            }
            pile->unk6 = 0;
        }
        done = 1;
        break;
    }
    return done;
}

void func_80090044(CardBattle *battle, CardScreen *screen, s32 arg2) {
    s32 i;

    for (i = 0; i < 40; i++) {
        battle->unk46F[i] = 0;
    }
    battle->unk444 = arg2;
    battle->unk445 = 0;
}

s32 func_80090068(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 i;
    u8 n;
    s32 k;
    s32 m;

    if (battle->unk444 != 0) {
        if (side == 0) {
            n = 0;
            for (i = battle->sides[0].pile.unk4; i < battle->sides[0].pile.unk4 + battle->unk444; i++) {
                if (i >= 40) {
                    battle->unk445 = 1;
                    battle->unk444 = n;
                    break;
                }
                battle->unk46F[i] = 1;
                n++;
            }
        } else {
            k = battle->sides[1].pile.unk4;
            m = 39;
            if (battle->unk444 > battle->sides[1].pile.unk8) {
                battle->unk445 = 1;
                battle->unk444 = battle->sides[1].pile.unk8;
            }
            for (i = 0; i < battle->unk444; i++) {
                if (battle->unk30A[k].unk1 == battle->unk300 * 2 + 2) {
                    battle->unk46F[k] = 1;
                    k++;
                } else {
                    battle->unk46F[m] = 1;
                    m--;
                }
            }
        }
    }
    return 1;
}

void func_80090178(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 i;
    s32 card;
    s32 j;

    battle->unk438 = battle->sides[side].pile.unkA;
#if VERSION_EU
    battle->unk42C = 0;
#endif
    for (i = battle->sides[side].pile.unk4; i < 40; i++) {
        if (battle->unk46F[i] != 0) {
            card = battle->sides[side].pile.unk14[i];
            battle->sides[side].pile.unk64[battle->sides[side].pile.unkA] = card;
            battle->sides[side].pile.unkA++;
#if VERSION_EU
            battle->unk42C = 1;
#endif
        }
    }
    for (j = 0; j < 40; j++) {
        battle->unk498.unk6[j] = 0;
    }
    if (battle->unk438 != 0) {
        if (side == 0) {
            battle->unk498.unk1 = 5;
        } else {
            battle->unk498.unk1 = 11;
            battle->unk498.unk4 = 1;
        }
    } else {
        if (side == 0) {
            battle->unk498.unk1 = 17;
        } else {
            battle->unk498.unk1 = 18;
            battle->unk498.unk4 = 1;
        }
    }
    screen->unkEC0(screen, side);
    battle->stepState = 1;
}

/* Moves the cards drawn into the hand (from unk438 on) into place one at a time, counting their colours and taking each flagged card (unk46F) out of the deck */
s32 CARDGAME_drawNewCards(CardBattle *battle, CardScreen *screen, s32 side) {
    CardDrawer drawer;
    s32 done = 0;
    s32 ready;
    s32 closed;
    s32 card;
    s32 found;
    /* the match depends on a loop variable of its own for most loops */
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;
    s32 swap;
    s32 x;

    switch (battle->stepState) {
    case 1:
        ready = 0;
        if (side == 0) {
            ready = screen->panels[0].state == 2;
        } else if (screen->panels[1].state == 2) {
            ready = 1;
        }
        for (k = battle->unk438; k < battle->sides[side].pile.unkA; k++) {
            screen->sprites[k].x = 0x14A00;
        }
        if (ready && battle->unk498.unk0 == 0) {
#if VERSION_US
            battle->stepState = 2;
#elif VERSION_EU
            if (battle->unk42C == 0) {
                screen->unkEE4(screen, 0x35, 0, 0, side == 0 ? 2 : 0);
                battle->stepState = 5;
            } else {
                battle->stepState = 2;
            }
#endif
            battle->unk424 = 0;
            battle->unk428 = battle->unk438;
        }
        break;
    case 2:
        x = screen->getHandOffset(battle->sides[side].pile.unkA, battle->unk428);
        screen->sprites[battle->unk428].scaleX = 0x1000;
        screen->unkF08(screen, battle->unk428, 15, x + 0x1800, 0x6100);
        battle->stepState = 3;
        break;
    case 3:
        if (screen->sprites[battle->unk428].state == 1) {
            card = battle->sides[side].pile.unk64[battle->unk428];
            initCardDrawer(&drawer);
            drawer.setCard(battle->cards[card] + 1);
            if (drawer.card[0] < 6) {
                if (battle->sides[side].pile.unkC[drawer.card[0] - 1] < 99) {
                    battle->sides[side].pile.unkC[drawer.card[0] - 1]++;
                }
                screen->setPanelValue(screen, side, drawer.card[0] - 1, battle->sides[side].pile.unkC[drawer.card[0] - 1]);
                screen->unkF1C(screen, battle->unk428);
                battle->stepState = 4;
            } else {
                battle->unk428++;
                if (battle->unk428 < battle->sides[side].pile.unkA) {
                    battle->stepState = 2;
                } else if (battle->unk445 != 0) {
                    screen->unkEE4(screen, 0x35, 0, 0, side == 0 ? 2 : 0);
                    battle->stepState = 5;
                } else {
                    battle->unk424 = 45;
                    battle->stepState = 8;
                }
            }
            for (i = 39, found = 0; i >= 0; i--) {
                if (battle->unk46F[i] != 0) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                battle->unk46F[i] = 0;
                if (side == 0) {
                    for (m = i; m >= battle->sides[0].pile.unk4 + 1; m--) {
                        battle->sides[0].pile.unk14[m] = battle->sides[0].pile.unk14[m - 1];
                        battle->unk46F[m] = battle->unk46F[m - 1];
                    }
                } else {
                    if (i < battle->unk41B) {
                        for (j = i; j >= battle->sides[1].pile.unk4 + 1; j--) {
                            battle->sides[1].pile.unk14[j] = battle->sides[1].pile.unk14[j - 1];
                            battle->unk46F[j] = battle->unk46F[j - 1];
                            battle->unk30A[j] = battle->unk30A[j - 1];
                        }
                    } else {
                        if (battle->unk30A[i].unk1 == 7) {
                            for (j = i; j >= battle->sides[1].pile.unk4 + 1; j--) {
                                battle->sides[1].pile.unk14[j] = battle->sides[1].pile.unk14[j - 1];
                                battle->unk46F[j] = battle->unk46F[j - 1];
                                battle->unk30A[j] = battle->unk30A[j - 1];
                            }
                            battle->unk41B++;
                            battle->unk41C++;
                        } else {
                            swap = battle->sides[1].pile.unk14[i];
                            battle->sides[1].pile.unk14[i] = battle->sides[1].pile.unk14[39];
                            battle->sides[1].pile.unk14[39] = swap;
                            for (j = 39; j >= battle->sides[1].pile.unk4 + 1; j--) {
                                battle->sides[1].pile.unk14[j] = battle->sides[1].pile.unk14[j - 1];
                                battle->unk46F[j] = battle->unk46F[j - 1];
                                battle->unk30A[j] = battle->unk30A[j - 1];
                            }
                            battle->unk41B++;
                            battle->unk41C++;
                        }
                    }
                    for (n = 39; n >= 0; n--) {
                        battle->unk30A[n].unk0 = n;
                    }
                }
                battle->sides[side].pile.unk4++;
                battle->sides[side].pile.unk8--;
            }
        }
        break;
    case 4:
        if (screen->sprites[battle->unk428].state == 1) {
            battle->unk428++;
            if (battle->unk428 < battle->sides[side].pile.unkA) {
                battle->stepState = 2;
            } else if (battle->unk445 != 0) {
                screen->unkEE4(screen, 0x35, 0, 0, side == 0 ? 2 : 0);
                battle->stepState = 5;
            } else {
                battle->unk424 = 45;
                battle->stepState = 8;
            }
        }
        break;
    case 5:
        if (screen->unkDFA == 2) {
            battle->stepState = 6;
        }
        break;
    case 6:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 7;
            screen->unkEE8(screen);
        }
        break;
    case 7:
        if (screen->unkDFA == 0) {
            battle->unk424 = 45;
            battle->stepState = 8;
        }
        break;
    case 8:
        screen->setPanelValue(screen, 0, 5, battle->sides[0].pile.unk8);
        screen->setPanelValue(screen, 0, 6, battle->sides[0].pile.unkA);
        screen->setPanelValue(screen, 0, 7, battle->sides[0].pile.unk6);
        screen->setPanelValue(screen, 1, 5, battle->sides[1].pile.unk8);
        screen->setPanelValue(screen, 1, 6, battle->sides[1].pile.unkA);
        screen->setPanelValue(screen, 1, 7, battle->sides[1].pile.unk6);
        battle->unk424 -= GFX_FUNCS.getFrameTime();
        if (battle->unk424 <= 0) {
            battle->stepState = 9;
            screen->unkEBC(screen, side);
            battle->unk498.unk1 = battle->unk498.unk3;
        }
        break;
    case 9:
        closed = 0;
        if (side == 0) {
            closed = screen->panels[0].state == 0;
        } else if (screen->panels[1].state == 0) {
            closed = 1;
        }
        if (closed && battle->unk498.unk0 == 0) {
            battle->stepState = 10;
        }
        break;
    case 10:
        done = 1;
        break;
    }
    return done;
}

void func_80090B48(CardBattle *battle, CardScreen *screen) {
    battle->unk428 = 0;
    battle->stepState = 1;
}

s32 func_80090B58(CardBattle *battle, CardScreen *screen, s32 which) {
    s32 done = 0;
    s32 i;
    s32 ok;

    switch (battle->stepState) {
    case 1:
        for (i = battle->unk428; i < 12; i++) {
            if (battle->unk46F[i] != 0) {
                battle->stepState = 2;
                battle->unk424 = 0;
                battle->unk428 = i;
                battle->unk42C = i >= 6;
                battle->unk430 = i;
                if (i >= 6) {
                    battle->unk430 = i - 6;
                }
                break;
            }
        }
        if (i >= 12) {
            battle->stepState = 3;
        }
        break;
    case 2:
        if (which == 0) {
            ok = func_8008D10C(battle, screen, battle->unk42C, battle->unk430);
        } else {
            ok = func_8008D350(battle, screen, battle->unk42C, battle->unk430);
        }
        if (ok) {
            battle->stepState = 1;
            battle->unk428++;
        }
        break;
    case 3:
        done = 1;
        break;
    }
    return done;
}

void func_80090C90(CardBattle *battle, CardScreen *screen, s32 arg2, s32 index) {
    s32 i;
    s32 color;
    s32 n;
    n = battle->unk560.unk15 - 1;
    color = screen->sprites[index].color + 1;
    for (i = 0; i < n; i++) {
        screen->sprites[index].unk3E[i] = 0;
        switch (battle->unk560.unk20[i].unk5) {
        case 1:
            if (battle->unk560.unk20[i].unk4 == 0) {
                if (index < 6) {
                    screen->sprites[index].unk3E[i] = 1;
                }
            } else if (index >= 6) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        case 2:
            if (battle->unk560.unk20[i].unk4 == 0) {
                if (index >= 6) {
                    screen->sprites[index].unk3E[i] = 1;
                }
            } else if (index < 6) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        case 3:
            screen->sprites[index].unk3E[i] = 1;
            break;
        case 4:
            if (color != 1) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        case 5:
            if (color != 2) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        case 6:
            if (color == 3) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        case 7:
            if (color != 4) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        case 8:
            if (color == 6) {
                screen->sprites[index].unk3E[i] = 1;
            }
            break;
        }
    }
}

/* Puts a card in the side's next slot (owned by side 2) and shows it */
void CARDGAME_putSlotCard(CardBattle *battle, CardScreen *screen, s32 side, s32 card) {
    CardDrawer drawer;
    CardPlayer *player = &battle->players[side];
    s32 index = player->slotCount;
    s32 slot = index;

    if (side != 0) {
        index += 6;
    }
    initCardDrawer(&drawer);
    drawer.setCard(battle->cards[card] + 1);
    player->slots[slot].unk6 = drawer.card[1];
    player->slots[slot].unk8 = drawer.card[2];
    player->slots[slot].unk2 = 0;
    player->slots[slot].unk4 = 0;
    player->slots[slot].card = card;
    player->slots[slot].owner = side;
    player->slots[slot].side = 2;
    player->slots[slot].order = battle->slotCount++;
    screen->addSprite(screen, index, 0xE500, 0x6100);
    screen->setSpriteCard(screen, index, card);
    screen->sprites[index].unk43 = player->slots[slot].unk6;
    screen->sprites[index].unk44 = player->slots[slot].unk8;
    screen->sprites[index].scaleX = 0;
    func_80090C90(battle, screen, side, index);
    battle->stepState = 1;
    screen->scaleSprite(screen, index, 20, 0x1000, 0x1000);
}

/* Takes the card the last record names out of the side's hand into its next
   slot and shows it */
void CARDGAME_takeHandCard(CardBattle *battle, CardScreen *screen, s32 side) {
    CardPlayer *player = &battle->players[side];
    CardPile *pile = &battle->sides[side].pile;
    s32 index = player->slotCount;
    s32 slot = index;
    s32 i;
    s32 j;

    if (side != 0) {
        index += 6;
    }
    for (i = 0; i < pile->unkA; i++) {
        if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk6 == pile->unk64[i]) {
            battle->addCard(battle, side, battle->unk560.unk20[battle->unk560.unk15 - 1].unk6);
            break;
        }
    }
    for (j = i; j < pile->unkA - 1; j++) {
        pile->unk64[j] = pile->unk64[j + 1];
    }
    pile->unkA--;
    player->slotCount--;
    screen->addSprite(screen, index, 0xE500, 0x6100);
    screen->setSpriteCard(screen, index, player->slots[slot].card);
    for (i = 0; i < 5; i++) {
        func_8009F754(battle, &player->slots[slot], side, i);
    }
    screen->sprites[index].unk43 = player->slots[slot].unk6;
    screen->sprites[index].unk44 = player->slots[slot].unk8;
    screen->sprites[index].scaleX = 0;
    func_80090C90(battle, screen, side, index);
    battle->stepState = 1;
    screen->setPanelValue(screen, side, 6, pile->unkA);
    screen->scaleSprite(screen, index, 20, 0x1000, 0x1000);
}

/* Moves the side's next slot card into place; 1 once it is there */
s32 CARDGAME_moveSlotCard(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;
    CardPlayer *player = &battle->players[side];
    s32 index = player->slotCount;
    s32 x;
    s32 y;

    if (side != 0) {
        index += 6;
    }
#if VERSION_US
    x = player->slotCount * 0x2900 + 0x1800;
    y = 0x3200;
    if (side == 0) {
        y = 0x9000;
    }
#elif VERSION_EU
    if (side == 0) {
        x = D_800A5958[SHIFT_PAL_SCREEN][0] + player->slotCount * 0x2900;
    } else {
        x = D_800A5958[SHIFT_PAL_SCREEN][2] + player->slotCount * 0x2900;
    }
    if (side == 0) {
        y = D_800A5958[SHIFT_PAL_SCREEN][1];
    } else {
        y = D_800A5958[SHIFT_PAL_SCREEN][3];
    }
#endif
    switch (battle->stepState) {
    case 1:
        if (screen->sprites[index].state == 1) {
            screen->unkF1C(screen, index);
            battle->stepState = 2;
        }
        break;
    case 2:
        if (screen->sprites[index].state == 1) {
            screen->unkF08(screen, index, 20, x, y);
            screen->sprites[index].moving = 1;
            battle->stepState = 3;
        }
        break;
    case 3:
        if (screen->sprites[index].state == 1) {
            battle->stepState = 4;
            screen->sprites[index].moving = 0;
            player->slotCount++;
        }
        break;
    case 4:
        done = 1;
        break;
    }
    return done;
}

/* Copies the first marked slot card (unk46F) into the side's next slot */
void CARDGAME_copySlotCard(CardBattle *battle, CardScreen *screen, s32 side) {
    CardPlayer *player = &battle->players[side];
    s32 index = player->slotCount;
    s32 slot = index;
    CardSlot *src;
    s32 from;
    s32 i;

    if (side != 0) {
        index += 6;
    }
    from = 0;
    src = &player->slots[slot];
    for (i = 0; i < 12; i++) {
        if (i < 6) {
            if (i >= battle->players[0].slotCount) {
                continue;
            }
            src = &battle->players[0].slots[i];
        } else {
            if (i - 6 >= battle->players[1].slotCount) {
                continue;
            }
            src = &battle->players[1].slots[i - 6];
        }
        if (battle->unk46F[i] != 0) {
            from = i;
            break;
        }
    }
    player->slots[slot] = *src;
    screen->addSprite(screen, index, 0xE500, 0x6100);
    screen->setSpriteCard(screen, index, player->slots[slot].card);
    screen->sprites[index] = screen->sprites[from];
    screen->sprites[index].scaleX = 0;
    func_80090C90(battle, screen, side, index);
    for (i = 0; i < battle->unk560.unk15 - 1; i++) {
        if (battle->unk560.unk20[i].unk5 == 0 && screen->sprites[from].unk3E[i] != 0) {
            screen->sprites[index].unk3E[i] = 1;
        }
    }
    battle->stepState = 1;
    screen->scaleSprite(screen, from, 5, 0, 0x1000);
    battle->unk424 = 7;
}

/* Waits unk424 frames, then flips the side's next slot card over and moves it
   into place; 1 once it is there */
s32 CARDGAME_flipSlotCard(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;
    CardPlayer *player = &battle->players[side];
    s32 index = player->slotCount;
    s32 x;
    s32 y;

    if (side != 0) {
        index += 6;
    }
#if VERSION_US
    x = player->slotCount * 0x2900 + 0x1800;
    y = 0x3200;
    if (side == 0) {
        y = 0x9000;
    }
#elif VERSION_EU
    if (side == 0) {
        x = D_800A5958[SHIFT_PAL_SCREEN][0] + player->slotCount * 0x2900;
    } else {
        x = D_800A5958[SHIFT_PAL_SCREEN][2] + player->slotCount * 0x2900;
    }
    if (side == 0) {
        y = D_800A5958[SHIFT_PAL_SCREEN][1];
    } else {
        y = D_800A5958[SHIFT_PAL_SCREEN][3];
    }
#endif
    switch (battle->stepState) {
    case 1:
        battle->unk424 -= GFX.funcs.getFrameTime();
        if (battle->unk424 <= 0) {
            screen->scaleSprite(screen, index, 5, 0x1000, 0x1000);
            battle->stepState = 2;
        }
        break;
    case 2:
        if (screen->sprites[index].state == 1) {
            screen->unkF1C(screen, index);
            battle->stepState = 3;
        }
        break;
    case 3:
        if (screen->sprites[index].state == 1) {
            screen->unkF08(screen, index, 20, x, y);
            screen->sprites[index].moving = 1;
            battle->stepState = 4;
        }
        break;
    case 4:
        if (screen->sprites[index].state == 1) {
            battle->stepState = 5;
            screen->sprites[index].moving = 0;
            player->slotCount++;
        }
        break;
    case 5:
        done = 1;
        break;
    }
    return done;
}

void func_800918A0(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 i;
    s32 j;

    if (side == 0 || screen->panels[0].state == 0) {
        if (screen->panels[0].state == 0) {
            screen->unkECC(screen);
            battle->unk440 = 0;
            screen->addSprite(screen, 15, 0xE500, 0x6100);
            screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
            screen->sprites[15].scaleX = 0;
            screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
            screen->unkEC8(screen);
            battle->unk498.unk5 = 1;
            battle->unk498.unk6[15] = 0;
            if (side == 0) {
                for (j = 0; j < 15; j++) {
                    battle->unk46F[j] = 0;
                }
            }
            battle->unk498.unk1 = 1;
            battle->stepState = 1;
        } else {
            screen->unkF08(screen, 15, 10, D_800A4814[battle->unk560.unk15][0], D_800A4814[battle->unk560.unk15][1]);
#if VERSION_US
            battle->stepState = 3;
#elif VERSION_EU
            battle->stepState = 5;
#endif
            battle->unk424 = 0;
        }
    } else {
        screen->addSprite(screen, 15, 0xE500, 0x6100);
        screen->setSpriteCard(screen, 15, battle->unk560.unk20[battle->unk560.unk15].unk0);
        screen->sprites[15].scaleX = 0;
        screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
        battle->stepState = 2;
        battle->unk424 = 0;
#if VERSION_EU
        battle->unk428 = 0;
#endif
    }
    screen->clearPanelFlags(screen);
    for (i = 0; i < 15; i++) {
        screen->sprites[i].unk49 = 0;
    }
}

/* Card 15 goes off and the marked slot cards turn over; it then lands in
   sprite 12 + CardBattle560.unk15. 1 once done */
s32 func_80091A94(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 i;
    s32 j;
#if VERSION_EU
    s32 card;
#endif

    switch (battle->stepState) {
#if VERSION_US
    case 2:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 21) {
            screen->unkF08(screen, 15, 10, D_800A4814[battle->unk560.unk15][0], D_800A4814[battle->unk560.unk15][1]);
            battle->stepState = 3;
            battle->unk424 = 0;
        }
        break;
#elif VERSION_EU
    case 2:
        screen->unkE0C[1].unkE = 0;
        screen->unkE0C[1].unk10 = 0;
        screen->unkE0C[2].unk10 = 0;
        screen->unkE0C[3].unk10 = 0;
        screen->unkE0C[4].unk10 = 0;
        battle->unk428 = CARDGAME_openStepWindows(battle, screen, 2, 0, battle->unk424, battle->unk428);
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 21) {
            battle->unk424 = 0;
            battle->unk428 = 0;
            battle->stepState = 3;
        }
        break;
    case 3:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 4;
        }
        card = battle->cards[battle->unk560.unk20[battle->unk560.unk15].unk0] + 1;
        screen->unkE0C[4].unk14[2] = 0;
        screen->unkE0C[2].unk10 = card;
        screen->unkE0C[4].unk10 = card;
        break;
    case 4:
        screen->unkF08(screen, 15, 10, D_800A4814[battle->unk560.unk15][0], D_800A4814[battle->unk560.unk15][1]);
        screen->unkEB0(screen, 4);
        screen->unkEB0(screen, 1);
        screen->unkEB0(screen, 2);
        screen->unkEB0(screen, 3);
        battle->stepState = 5;
        battle->unk424 = 0;
        battle->unk428 = 0;
        break;
#endif
    case 1:
        if (screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            screen->unkF08(screen, 15, 10, D_800A4814[battle->unk560.unk15][0], D_800A4814[battle->unk560.unk15][1]);
            battle->stepState = 3 + CARD_INFO_STEPS;
            battle->unk424 = 0;
        }
        break;
    case 3 + CARD_INFO_STEPS:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 12) {
            battle->unk424 = 0;
            battle->stepState = 4 + CARD_INFO_STEPS;
            screen->unkF1C(screen, 15);
            for (i = 0; i < 15; i++) {
                if (battle->unk46F[i] != 0) {
                    screen->unkF1C(screen, i);
                }
            }
        }
        break;
    case 4 + CARD_INFO_STEPS:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 21) {
            battle->stepState = 5 + CARD_INFO_STEPS;
            battle->unk424 = 0;
            screen->scaleSprite(screen, 15, 5, 0, 0x1000);
            for (j = 0; j < 15; j++) {
                if (battle->unk46F[j] != 0) {
                    screen->sprites[j].unk3E[battle->unk560.unk15] = 1;
                }
            }
        }
        break;
    case 5 + CARD_INFO_STEPS:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 7) {
            battle->unk424 = 0;
            screen->sprites[15].unk46 = battle->unk560.unk15 + 1;
            screen->scaleSprite(screen, 15, 8, 0x1000, 0x1000);
            battle->stepState = 6 + CARD_INFO_STEPS;
            screen->unkEA4(screen, battle->unk560.unk15, battle->unk560.unk19);
        }
        break;
    case 6 + CARD_INFO_STEPS:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 11) {
            battle->unk424 = 0;
            battle->stepState = 7 + CARD_INFO_STEPS;
            screen->sprites[battle->unk560.unk15 + 12] = screen->sprites[15];
            screen->removeSprite(screen, 15);
            for (j = 0; j < 12; j++) {
                screen->sprites[j].unk48 &= ~1;
            }
        }
        break;
    case 7 + CARD_INFO_STEPS:
        done = 1;
        break;
    }
    return done;
}

void func_80091E60(CardBattle *battle, CardScreen *screen) {
    battle->sides[0].pile.unkA = 0;
    battle->sides[1].pile.unkA = 0;
    screen->setPanelValue(screen, 0, 6, battle->sides[0].pile.unkA);
    screen->setPanelValue(screen, 1, 6, battle->sides[1].pile.unkA);
    screen->setPanelValue(screen, 0, 5, battle->sides[0].pile.unk8);
    screen->setPanelValue(screen, 1, 5, battle->sides[1].pile.unk8);
    battle->unk440 = 0;
    battle->unk423 = 1;
}

/* Deals six cards from each side's deck into its hand and puts them on the
   table, face down */
void CARDGAME_dealHands(CardBattle *battle, CardScreen *screen) {
    s32 side;
    s32 i;
    s32 j;

    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk434 = 0;
    battle->unk42C = battle->sides[0].pile.unk8;
    battle->unk430 = battle->sides[1].pile.unk8;
    for (side = 0; side < 2; side++) {
        for (j = 0; j < 6; j++) {
            battle->sides[side].pile.unk64[j] = battle->sides[side].pile.unk14[battle->sides[side].pile.unk4];
            battle->sides[side].pile.unkA++;
            battle->sides[side].pile.unk4++;
            battle->sides[side].pile.unk8--;
        }
    }
    for (i = 0; i < 6; i++) {
#if VERSION_US
        screen->addSprite(screen, i, 0x16000, 0x9000);
#elif VERSION_EU
        screen->addSprite(screen, i, D_800A5958[SHIFT_PAL_SCREEN][0] + 0x14800, D_800A5958[SHIFT_PAL_SCREEN][1]);
#endif
        screen->setSpriteCard(screen, i, battle->sides[0].pile.unk64[i]);
        screen->sprites[i].visible = 2;
        screen->sprites[i].scaleY = 0;
        screen->sprites[i].scaleX = 0;
    }
    for (i = 0; i < 6; i++) {
#if VERSION_US
        screen->addSprite(screen, i + 6, 0x16000, 0x3200);
#elif VERSION_EU
        screen->addSprite(screen, i + 6, D_800A5958[SHIFT_PAL_SCREEN][2] + 0x14800, D_800A5958[SHIFT_PAL_SCREEN][3]);
#endif
        screen->setSpriteCard(screen, i + 6, battle->sides[1].pile.unk64[i]);
        screen->sprites[i + 6].visible = 2;
        screen->sprites[i + 6].scaleY = 0;
        screen->sprites[i + 6].scaleX = 0;
    }
}

/* The start of a card battle: deals six cards to each side, turns them over and counts their colours (a deck with fewer than six cards shows a message instead); 1 when it ends */
s32 CARDGAME_stepStart(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    if (battle->unk423 != 0) {
        switch (battle->unk423) {
        case 1:
            screen->unkEC8(screen);
            break;
        case 2:
            CARDGAME_dealHands(battle, screen);
            break;
        case 3:
        case 4:
            battle->unk424 = 0;
            battle->unk428 = 0;
            battle->unk434 = 0;
            break;
        case 5:
            battle->unk424 = 0;
            battle->unk428 = 0;
            battle->unk434 = 0;
            screen->unkEC4(screen);
            break;
        case 6:
            screen->setPanelFlags(screen, 0x1000);
            screen->unkEE4(screen, 0x21, 0, 1, 1);
            battle->unk440 = 1;
            break;
        case 7:
            SOUND.playSound(0x6004001E);
            screen->setPanelFlags(screen, 0x2000);
            screen->unkEE4(screen, 0x22, 0, 1, 1);
            battle->unk440 = 2;
            break;
        case 9:
            battle->unk424 = 0;
            battle->unk428 = 0;
            battle->unk434 = 0;
            screen->unkEC4(screen);
            screen->unkEE8(screen);
            break;
        case 11:
            screen->unkEE4(screen, battle->unk2EC, 0, 0, 3);
            break;
        case 8:
        case 10:
        case 12:
            /* nothing to set up */
            break;
        }
        battle->stepState = battle->unk423;
        battle->unk423 = 0;
    }

    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 2) {
            if (battle->sides[0].pile.unk8 < 6) {
                battle->unk423 = 6;
            } else if (battle->sides[1].pile.unk8 < 6) {
                battle->unk423 = 7;
            } else {
                battle->unk423 = 2;
            }
        }
        break;
    case 2:
        if (battle->unk434 >= 7) {
            if (battle->unk428 < 6) {
#if VERSION_US
                screen->unkF08(screen, battle->unk428, 20, battle->unk428 * 0x2900 + 0x1800, 0x9000);
#elif VERSION_EU
                screen->unkF08(screen, battle->unk428, 20, D_800A5958[SHIFT_PAL_SCREEN][0] + battle->unk428 * 0x2900, D_800A5958[SHIFT_PAL_SCREEN][1]);
#endif
                screen->setSpriteScale(screen, battle->unk428, 0x1000, 0x1000);
#if VERSION_US
                screen->unkF08(screen, battle->unk428 + 6, 20, battle->unk428 * 0x2900 + 0x1800, 0x3200);
#elif VERSION_EU
                screen->unkF08(screen, battle->unk428 + 6, 20, D_800A5958[SHIFT_PAL_SCREEN][2] + battle->unk428 * 0x2900, D_800A5958[SHIFT_PAL_SCREEN][3]);
#endif
                screen->setSpriteScale(screen, battle->unk428 + 6, 0x1000, 0x1000);
                battle->unk428++;
                battle->unk42C--;
                battle->unk430--;
                screen->setPanelValue(screen, 0, 6, battle->unk428);
                screen->setPanelValue(screen, 1, 6, battle->unk428);
                screen->setPanelValue(screen, 0, 5, battle->unk42C);
                screen->setPanelValue(screen, 1, 5, battle->unk430);
            }
            battle->unk434 -= 7;
        }
        if (battle->unk424 > 60) {
            battle->unk423 = 3;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk434 += GFX.funcs.getFrameTime();
        break;
    case 3:
        if (battle->unk434 >= 7) {
            if (battle->unk428 < 6) {
                screen->unkF28(screen, battle->unk428);
                battle->unk428++;
            }
            battle->unk434 -= 7;
        }
        if (battle->unk424 > 65) {
            battle->unk423 = 4;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk434 += GFX.funcs.getFrameTime();
        break;
    case 4:
        if (battle->unk434 >= 7) {
            if (battle->unk428 < 6) {
                if (CARDGAME_addColorCount(battle, screen, 0, battle->sides[0].pile.unk64[battle->unk428])) {
                    screen->unkF1C(screen, battle->unk428);
                }
                if (CARDGAME_addColorCount(battle, screen, 1, battle->sides[1].pile.unk64[battle->unk428])) {
                    screen->unkF1C(screen, battle->unk428 + 6);
                }
                battle->unk428++;
            }
            battle->unk434 -= 7;
        }
        if (battle->unk424 > 80) {
            battle->unk423 = 5;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk434 += GFX.funcs.getFrameTime();
        break;
    case 5:
        if (battle->unk434 >= 3) {
            if (battle->unk428 < 6) {
                screen->scaleSprite(screen, battle->unk428, 5, 0, 0x1000);
                screen->scaleSprite(screen, battle->unk428 + 6, 5, 0, 0x1000);
                battle->unk428++;
            }
            battle->unk434 -= 3;
        }
        if (battle->unk424 > 40) {
            battle->unk423 = 10;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk434 += GFX.funcs.getFrameTime();
        break;
    case 6:
    case 7:
        if (screen->unkDFA == 2) {
            battle->unk423 = 8;
        }
        break;
    case 8:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->unk423 = 9;
        }
        break;
    case 9:
        if (screen->unkDFA == 0 && screen->panels[0].state == 0) {
            battle->unk423 = 10;
        }
        break;
    case 10:
        if (battle->unk440 == 2) {
            battle->unk423 = 11;
        } else {
            done = 1;
        }
        break;
    case 11:
        if (screen->unkDFA == 2) {
            battle->unk423 = 12;
        }
        break;
    case 12:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            done = 1;
        }
        break;
    }
    return done;
}

void func_80092860(CardBattle *battle, CardScreen *screen, s32 side) {
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = battle->sides[side].pile.unk0;
    battle->unk430 = battle->sides[side ^ 1].pile.unk2 << 8;
    battle->sides[side ^ 1].pile.unk2 -= battle->sides[side].pile.unk0;
    if (battle->sides[side ^ 1].pile.unk2 < 0) {
        battle->sides[side ^ 1].pile.unk2 = 0;
    }
    if (battle->players[side].slotCount != 0) {
        battle->unk434 = (battle->unk430 - (battle->sides[side ^ 1].pile.unk2 << 8)) / (battle->players[side].slotCount * 28 - 16);
        if (battle->unk434 == 0) {
            battle->unk434 = 1;
        }
    } else {
        battle->unk434 = 1;
    }
    battle->stepState = 1;
}

/* The side's slot cards go over one by one (every 27 frames) while the panels
   count its attack (8) and the other side's unk2 (9) down; 1 once done */
s32 CARDGAME_stepAttack(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;
    s32 other = side ^ 1;
    s32 index;
    s32 value;
#if VERSION_EU
    s32 x;
#endif
    s32 i;

    switch (battle->stepState) {
    case 1:
        if (battle->unk424 % 27 == 0 && battle->unk428 < battle->players[side].slotCount) {
            index = battle->unk428;
            if (side != 0) {
                index += 6;
            }
#if VERSION_US
            screen->unkF10(screen, index, 6, (battle->players[other].slotCount - 1) * 0x1480 + 0x1800, 0x6100);
#elif VERSION_EU
            x = D_800A5958[SHIFT_PAL_SCREEN][0] + (battle->players[other].slotCount - 1) * 0x1480;
            if (SHIFT_PAL_SCREEN) {
                screen->unkF10(screen, index, 6, x, side != 0 ? 0x6D00 : 0x5500);
            } else {
                screen->unkF10(screen, index, 6, x, 0x6100);
            }
#endif
            battle->unk428++;
            screen->sprites[index].moving = 1;
        }
        if (battle->unk424 >= 16) {
            value = 0;
            if (battle->unk424 < battle->players[side].slotCount * 28) {
                value = battle->unk42C - (battle->unk42C / (battle->players[side].slotCount * 56 + 1) + 1) * battle->unk424;
                if (value < 0) {
                    value = 0;
                }
            }
            screen->setPanelValue(screen, side, 8, value);
            if (battle->unk424 < battle->players[side].slotCount * 28) {
                battle->unk430 -= battle->unk434;
                if (battle->unk430 < battle->sides[other].pile.unk2 << 8) {
                    battle->unk430 = battle->sides[other].pile.unk2 << 8;
                }
            } else {
                battle->unk430 = battle->sides[other].pile.unk2 << 8;
            }
            screen->setPanelValue(screen, other, 9, battle->unk430 >> 8);
        }
        if (screen->unk54 & 2) {
            for (i = 0; i < battle->players[other].slotCount; i++) {
                screen->unkF2C(screen, side == 0 ? i + 6 : i);
            }
        }
        battle->unk424++;
        if (battle->unk424 > battle->players[side].slotCount * 28 + 25) {
            battle->stepState = 2;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

void func_80092CE0(CardBattle *battle, CardScreen *screen, s32 side) {
    battle->unk424 = 0;
    battle->unk428 = battle->players[side].slotCount - 1;
    battle->stepState = 1;
}

s32 func_80092D14(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;

    switch (battle->stepState) {
    case 1:
        if (func_8008D10C(battle, screen, side, battle->unk428)) {
            battle->unk424 = 0;
            if (--battle->unk428 < 0) {
                battle->stepState = 2;
                battle->players[side].slotCount = 0;
            }
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

/* The value going from FROM to TO in DURATION, at TIME, never past TO */
s32 CARDGAME_interpolate(s32 to, s32 from, s32 duration, s32 time) {
    s32 delta = to - from;
    s32 inRange;

    if (time == duration || from == to) {
        return to;
    }
    from += delta * time / duration;
    if (delta > 0) {
        inRange = from < to;
    } else {
        inRange = from > to;
    }
    if (!inRange) {
        from = to;
    }
    return from;
}

void func_80092E1C(CardBattle *battle, CardScreen *screen) {
    screen->addSprite(screen, 0x11, 0x8300, 0x6100);
    screen->setSpriteCard(screen, 0x11, battle->unk304 - 1);
    screen->sprites[0x11].scaleX = 0;
    screen->scaleSprite(screen, 0x11, 10, 0x1000, 0x1000);
    battle->stepState = 1;
}

/* Swaps the two sides' pile unk0 and unk2, counting the panels' values 8 and 9 over to each other, then shows message 0x2D until cross or triangle; 1 once done */
s32 func_80092EB0(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 unk0;
    s32 unk2;

    switch (battle->stepState) {
    case 1:
        if (screen->sprites[0x11].state == 1) {
            screen->unkF1C(screen, 0x11);
            battle->stepState = 2;
        }
        break;
    case 2:
        if (screen->sprites[0x11].state == 1) {
            battle->stepState = 3;
            battle->unk424 = 0;
        }
        break;
    case 3:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 < 15) {
            screen->setPanelValue(screen, 0, 8, CARDGAME_interpolate(battle->sides[1].pile.unk0, battle->sides[0].pile.unk0, 15, battle->unk424));
            screen->setPanelValue(screen, 0, 9, CARDGAME_interpolate(battle->sides[1].pile.unk2, battle->sides[0].pile.unk2, 15, battle->unk424));
            screen->setPanelValue(screen, 1, 8, CARDGAME_interpolate(battle->sides[0].pile.unk0, battle->sides[1].pile.unk0, 15, battle->unk424));
            screen->setPanelValue(screen, 1, 9, CARDGAME_interpolate(battle->sides[0].pile.unk2, battle->sides[1].pile.unk2, 15, battle->unk424));
        } else {
            unk0 = battle->sides[0].pile.unk0;
            battle->sides[0].pile.unk0 = battle->sides[1].pile.unk0;
            battle->sides[1].pile.unk0 = unk0;
            unk2 = battle->sides[0].pile.unk2;
            battle->sides[0].pile.unk2 = battle->sides[1].pile.unk2;
            battle->sides[1].pile.unk2 = unk2;
            screen->setPanelValue(screen, 0, 8, battle->sides[0].pile.unk0);
            screen->setPanelValue(screen, 0, 9, battle->sides[0].pile.unk2);
            screen->setPanelValue(screen, 1, 8, battle->sides[1].pile.unk0);
            screen->setPanelValue(screen, 1, 9, battle->sides[1].pile.unk2);
            screen->scaleSprite(screen, 0x11, 10, 0, 0x1000);
            battle->stepState = 4;
        }
        break;
    case 4:
        if (screen->sprites[0x11].state == 1) {
            battle->stepState = 5;
            screen->unkEE4(screen, 0x2D, 0, 0, 1);
        }
        break;
    case 5:
        if (screen->unkDFA == 2) {
            battle->stepState = 6;
        }
        break;
    case 6:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 7;
            screen->unkEE8(screen);
        }
        break;
    case 7:
        if (screen->unkDFA == 0) {
            battle->stepState = 8;
        }
        break;
    case 8:
        done = 1;
        break;
    }
    return done;
}

/* Adds up the marked slots' unk6 and unk8 (at most 99, 20 more for four or more slots) and shows them on sprite 0x11 with card unk438, looked for among the card list's last 100 cards */
void CARDGAME_showSlotTotal(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 i;
    s32 card;
    s32 slot;
    s32 count = 0;
    s32 index;
    s32 base;

    battle->unk42C = 0;
    battle->unk430 = 0;
    for (i = 0; i < battle->players[side].slotCount; i++) {
        if (battle->unk446[i] != 0) {
            battle->unk42C += battle->players[side].slots[i].unk6;
            if (battle->unk42C >= 100) {
                battle->unk42C = 99;
            }
            battle->unk430 += battle->players[side].slots[i].unk8;
            if (battle->unk430 >= 100) {
                battle->unk430 = 99;
            }
            count++;
        }
    }
    if (count >= 4) {
        battle->unk42C += 20;
        if (battle->unk42C >= 100) {
            battle->unk42C = 99;
        }
        battle->unk430 += 20;
        if (battle->unk430 >= 100) {
            battle->unk430 = 99;
        }
    }
    screen->addSprite(screen, 0x11, 0x8300, 0x6100);
    index = 0;
    for (card = 89; card < battle->cardCount; card++) {
        if (battle->cards[card] == battle->unk438 - 1) {
            index = card;
            break;
        }
    }
    if (index == 0) {
        index = 87;
        battle->unk438 = 0x13B;
    }
    screen->setSpriteCard(screen, 0x11, index);
    screen->sprites[0x11].color = 5;
    screen->sprites[0x11].unk43 = battle->unk42C;
    screen->sprites[0x11].unk44 = battle->unk430;
    base = 0;
    if (side != 0) {
        base = 6;
    }
    for (slot = 0; slot < battle->players[side].slotCount; slot++) {
        if (battle->unk446[slot] != 0) {
            screen->sprites[base + slot].unk48 |= 4;
        }
    }
    screen->sprites[0x11].scaleX = 0;
    battle->unk424 = 0;
    battle->stepState = 1;
}

/* Takes the marked slots' sprites away, shows card unk438 in window 2 for 90 frames (or until cross or triangle), then adds unk42C and unk430 to the side's pile unk0 and unk2, counting the panel values up; 1 once done */
s32 func_800934E0(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;
    s32 base;
    s32 i;
    s32 first;
    s32 j;

    switch (battle->stepState) {
    case 1:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 21) {
            battle->stepState = 2;
            base = 0;
            if (side != 0) {
                base = 6;
            }
            for (i = 0; i < battle->players[side].slotCount; i++) {
                if (battle->unk446[i] != 0) {
                    screen->unkF1C(screen, base + i);
                    battle->unk434 = base + i;
                }
            }
        }
        break;
    case 2:
        if (screen->sprites[battle->unk434].state == 1) {
            screen->scaleSprite(screen, 0x11, 10, 0x1000, 0x1000);
            battle->stepState = 3;
            first = 0;
            if (side != 0) {
                first = 6;
            }
            for (j = 0; j < battle->players[side].slotCount; j++) {
                if (battle->unk446[j] != 0) {
                    screen->sprites[first + j].unk48 &= ~4;
                }
            }
        }
        break;
    case 3:
        if (screen->sprites[0x11].state == 1) {
            battle->stepState = 4;
#if VERSION_US
            screen->unkEAC(screen, 2, 1, battle->unk438, CARDGAME_cardWindowPositions[0][side][0], CARDGAME_cardWindowPositions[0][side][1]);
#elif VERSION_EU
            screen->unkEAC(screen, 2, 1, battle->unk438, CARDGAME_cardWindowPositions[SHIFT_PAL_SCREEN][side][0], CARDGAME_cardWindowPositions[SHIFT_PAL_SCREEN][side][1]);
#endif
        }
        break;
    case 4:
        if (screen->unkE0C[2].state == 2) {
            battle->stepState = 5;
            battle->unk424 = 90;
        }
        break;
    case 5:
        battle->unk424 -= GFX.funcs.getFrameTime();
        if (battle->unk424 <= 0 || PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 6;
            screen->unkEB0(screen, 2);
        }
        break;
    case 6:
        if (screen->unkE0C[2].state == 0) {
            screen->unkF1C(screen, 0x11);
            battle->stepState = 7;
        }
        break;
    case 7:
        if (screen->sprites[0x11].state == 1) {
            battle->stepState = 8;
            battle->unk424 = 0;
        }
        break;
    case 8:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 < 20) {
            screen->setPanelValue(screen, side, 8, CARDGAME_interpolate(battle->sides[side].pile.unk0 + battle->unk42C, battle->sides[side].pile.unk0, 20, battle->unk424));
            screen->setPanelValue(screen, side, 9, CARDGAME_interpolate(battle->sides[side].pile.unk2 + battle->unk430, battle->sides[side].pile.unk2, 20, battle->unk424));
        } else {
            battle->sides[side].pile.unk0 += battle->unk42C;
            battle->sides[side].pile.unk2 += battle->unk430;
            screen->setPanelValue(screen, side, 8, battle->sides[side].pile.unk0);
            screen->setPanelValue(screen, side, 9, battle->sides[side].pile.unk2);
            screen->scaleSprite(screen, 0x11, 10, 0, 0x1000);
            battle->stepState = 9;
        }
        break;
    case 9:
        if (screen->sprites[0x11].state == 1) {
            battle->stepState = 10;
        }
        break;
    case 10:
        done = 1;
        break;
    }
    return done;
}

void func_80093A1C(CardBattle *battle, CardScreen *screen) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = 0;
    battle->unk430 = 0;
    battle->unk434 = 0;
}

/* Adds up both players' slots' unk6 and unk8 and counts the panels' values 8 and 9 over to the totals, which become the sides' pile unk0 and unk2; 1 once done */
s32 func_80093A3C(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 i;

    switch (battle->stepState) {
    case 1:
        for (i = 0; i < battle->players[0].slotCount; i++) {
            battle->unk428 += battle->players[0].slots[i].unk6;
            battle->unk42C += battle->players[0].slots[i].unk8;
        }
        for (i = 0; i < battle->players[1].slotCount; i++) {
            battle->unk430 += battle->players[1].slots[i].unk6;
            battle->unk434 += battle->players[1].slots[i].unk8;
        }
        if (battle->sides[0].pile.unk0 == battle->unk428 && battle->sides[0].pile.unk2 == battle->unk42C &&
            battle->sides[1].pile.unk0 == battle->unk430 && battle->sides[1].pile.unk2 == battle->unk434) {
            battle->stepState = 4;
        } else {
            battle->unk424 = 0;
            battle->stepState = 2;
        }
        break;
    case 2:
        battle->unk424 += GFX.funcs.getFrameTime();
        if (battle->unk424 < 15) {
            SOUND.playSound(0x800452C6);
            screen->setPanelValue(screen, 0, 8, CARDGAME_interpolate(battle->unk428, battle->sides[0].pile.unk0, 15, battle->unk424));
            screen->setPanelValue(screen, 0, 9, CARDGAME_interpolate(battle->unk42C, battle->sides[0].pile.unk2, 15, battle->unk424));
            screen->setPanelValue(screen, 1, 8, CARDGAME_interpolate(battle->unk430, battle->sides[1].pile.unk0, 15, battle->unk424));
            screen->setPanelValue(screen, 1, 9, CARDGAME_interpolate(battle->unk434, battle->sides[1].pile.unk2, 15, battle->unk424));
        } else {
            battle->sides[0].pile.unk0 = battle->unk428;
            battle->sides[0].pile.unk2 = battle->unk42C;
            battle->sides[1].pile.unk0 = battle->unk430;
            battle->sides[1].pile.unk2 = battle->unk434;
            screen->setPanelValue(screen, 0, 8, battle->sides[0].pile.unk0);
            screen->setPanelValue(screen, 0, 9, battle->sides[0].pile.unk2);
            screen->setPanelValue(screen, 1, 8, battle->sides[1].pile.unk0);
            screen->setPanelValue(screen, 1, 9, battle->sides[1].pile.unk2);
            battle->stepState = 3;
        }
        break;
    case 3:
        battle->stepState = 4;
        break;
    case 4:
        done = 1;
        break;
    }
    return done;
}

void func_80093D6C(CardBattle *battle, CardScreen *screen) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = 0;
    battle->unk430 = 0;
    battle->unk434 = 0;
    battle->unk438 = 0;
}

/* Takes the side's slots away one by one, then moves both sides' pile unkA into unk8 one at a time (the panels' values 6 and 5) and shows window 5 until cross or triangle; 1 once done */
s32 func_80093D90(CardBattle *battle, CardScreen *screen, s32 side) {
    s32 done = 0;
    s32 index;
    s32 counting;

    switch (battle->stepState) {
    case 1:
        if (battle->unk438 >= 3) {
            if (battle->unk428 < battle->players[side].slotCount) {
                index = battle->unk428;
                if (side != 0) {
                    index += 6;
                }
                screen->scaleSprite(screen, index, 4, 0, 0x1000);
                func_8008D044(battle, screen, side, battle->unk428);
                battle->unk428++;
            }
            battle->unk438 -= 3;
        }
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk438 += GFX.funcs.getFrameTime();
        if (battle->unk424 >= 61) {
            battle->players[side].slotCount = 0;
            battle->unk424 = 0;
            battle->stepState = 2;
            battle->unk438 = 0;
            battle->unk428 = battle->sides[0].pile.unkA;
            battle->unk42C = battle->sides[0].pile.unk8;
            battle->unk430 = battle->sides[1].pile.unkA;
            battle->unk434 = battle->sides[1].pile.unk8;
        }
        break;
    case 2:
        battle->unk424 += GFX.funcs.getFrameTime();
        battle->unk438 += GFX.funcs.getFrameTime();
        if (battle->unk438 >= 3) {
            counting = 0;
            if (battle->unk428 > 0) {
                counting = 1;
                battle->unk428--;
                battle->unk42C++;
            }
            if (battle->unk430 > 0) {
                counting = 1;
                battle->unk430--;
                battle->unk434++;
            }
            if (!counting) {
                battle->stepState = 4;
                screen->unkEAC(screen, 5, 5, 20, 0, 110);
            } else {
                SOUND.playSound(0x800452C6);
            }
            screen->setPanelValue(screen, 0, 6, battle->unk428);
            screen->setPanelValue(screen, 0, 5, battle->unk42C);
            screen->setPanelValue(screen, 1, 6, battle->unk430);
            screen->setPanelValue(screen, 1, 5, battle->unk434);
            battle->unk438 -= 3;
        }
        break;
    case 3:
        if (screen->unkE0C[5].state == 2) {
            battle->stepState = 4;
        }
        break;
    case 4:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 5;
            screen->unkEB0(screen, 5);
        }
        break;
    case 5:
        if (screen->unkE0C[5].state == 0) {
            battle->stepState = 6;
            screen->unkEC4(screen);
        }
        break;
    case 6:
        if (screen->panels[0].state == 0) {
            battle->stepState = 7;
        }
        break;
    case 7:
        done = 1;
        break;
    }
    return done;
}
