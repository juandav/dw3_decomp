/* The second object of CARDGAME.PRO (see cardgame.c), from func_80085578
   (USA): its rodata starts at 0x80082A04, 4 bytes past a multiple of 8. */

#include "cardgame.h"

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80085578);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008584C);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80085B20);

void func_800860CC(CardBattle *battle, CardScreen *screen) {
    screen->unkE0C[1].unkE = 0;
    screen->unkE0C[1].unk10 = 0;
    screen->unkE0C[2].unk10 = 0;
    screen->unkE0C[3].unk10 = 0;
    screen->unkE0C[4].unk10 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800860E4);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800865D8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80086758);

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

s32 func_800869BC(CardBattle *battle, s32 arg1, CardPile *pile) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80086B0C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80086C60);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80086F68);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80087234);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80087590);

void func_800885C0(CardBattle *battle, CardScreen *screen) {
    screen->unkECC(screen);
    battle->unk440 = 0;
    battle->stepState = 1;
    screen->unkEC8(screen);
    battle->unk498.unk5 = 1;
    battle->unk498.unk4 = 1;
    battle->unk498.unk1 = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008862C);

void func_80088B98(CardBattle *battle, CardScreen *screen, s32 index) {
    u8 *entry = D_800A47C8[index];

    screen->unkEE4(screen, entry[1], 0, 0, 1);
    screen->unkEAC(screen, 5, 5, entry[0], 0, 0x42);
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80088C34);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80088DA4);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80089028);

void func_800894F8(CardBattle *battle) {
    battle->unk423 = 1;
}

s32 func_80089504(CardBattle *battle) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80089548);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80089698);

void func_8008A378(CardBattle *battle, s32 arg1, s32 arg2) {
    battle->unk438 = arg2;
    battle->unk423 = 1;
}

s32 func_8008A388(CardBattle *battle) {
    return func_80089504(battle);
}

s32 func_8008A3A8(CardBattle *battle) {
    return func_80089548(battle);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008A3C8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008B0D4);

void func_8008B29C(CardBattle *battle, s32 arg1, s32 arg2) {
    func_8008B0D4(battle, arg1, arg2, 0);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008B2BC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008B434);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008B674);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008BCF8);

void func_8008BEF0(CardBattle *battle) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008BFA0);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008C174);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008C424);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008C5F4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008C88C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008CBAC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008CE6C);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008D3D8);

s32 func_8008D4C4(CardBattle *battle, s32 arg1, s32 duration) {
    battle->unk424 += GFX.funcs.getFrameTime();
    return duration < battle->unk424;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008D510);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008D6A4);

INCLUDE_RODATA("cardgame/nonmatchings/cardgame_2", D_80082C94);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008D9B0);

void func_8008DBC8(CardBattle *battle) {
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008DBD4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008E21C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008E4A0);

void func_8008E68C(CardBattle *battle, s32 arg1, s32 side) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = battle->sides[side].pile.unkA;
    battle->unk42C = battle->sides[side].pile.unk6;
    battle->unk430 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008E6CC);

void func_8008E8B0(CardBattle *battle, s32 arg1, s32 arg2, s32 arg3) {
    battle->unk430 = arg3;
    battle->unk434 = arg2;
    battle->unk423 = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008E8C4);

void func_8008EB08(CardBattle *battle, s32 arg1) {
    func_8008E8B0(battle, arg1, -0x80, 0x10);
    battle->unk438 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008EB38);

void func_8008ED28(CardBattle *battle, CardScreen *screen) {
    battle->unk424 = 0;
    battle->stepState = 1;
    screen->unkEA8(screen, battle->unk560.unk15 - 2);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008ED68);

s32 func_8008EF20(CardBattle *battle) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008F074);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008F4E0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008F630);

void func_8008FD44(CardBattle *battle, s32 arg1, s32 side) {
    battle->unk424 = 0;
    battle->unk434 = 0;
    battle->unk428 = battle->sides[side].pile.unk6;
    battle->unk42C = battle->sides[side].pile.unk8;
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8008FD84);

void func_80090044(CardBattle *battle, s32 arg1, s32 arg2) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800902A8);

void func_80090B48(CardBattle *battle) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80090DDC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80090F80);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800911F0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800913A0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80091688);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800918A0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80091A94);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80091F10);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800920D4);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_8009294C);

void func_80092CE0(CardBattle *battle, s32 arg1, s32 side) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80092EB0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80093240);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_800934E0);

void func_80093A1C(CardBattle *battle) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = 0;
    battle->unk430 = 0;
    battle->unk434 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80093A3C);

void func_80093D6C(CardBattle *battle) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = 0;
    battle->unk430 = 0;
    battle->unk434 = 0;
    battle->unk438 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_2", func_80093D90);
