/* The third object of CARDGAME.PRO (see cardgame.c), from func_800941D0
   (USA): its rodata starts at 0x80082E30, a multiple of 8. */

#include "cardgame.h"

void func_800941D0(CardBattle *battle, CardScreen *screen, s32 arg2) {
    battle->unk424 = 0;
    screen->unkEE4(screen, arg2, 0, 0, 1);
    battle->stepState = 1;
}

/* Waits for the message window to open, for cross or triangle, then for the window to close; 1 once it has */
s32 CARDGAME_waitMessage(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    switch (battle->stepState) {
    case 1:
        if (screen->unkDFA == 2) {
            battle->stepState = 2;
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            battle->stepState = 3;
            screen->unkEE8(screen);
        }
        break;
    case 3:
        if (screen->unkDFA == 0) {
            battle->stepState = 4;
        }
        break;
    case 4:
        done = 1;
        break;
    }
    return done;
}

void func_80094380(CardBattle *battle, CardScreen *screen, s32 force) {
    if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk4 == 0 || force) {
        battle->unk560.unk15--;
        screen->unkEC4(screen);
        battle->unk498.unk1 = 2;
        battle->stepState = 1;
    } else {
        battle->stepState = 2;
    }
}

s32 func_800943FC(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    switch (battle->stepState) {
    case 1:
        if (screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
            battle->stepState = 2;
            battle->unk560.unk15++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

void func_80094468(CardBattle *battle, CardScreen *screen, s32 force) {
    if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk4 == 0 || force) {
        screen->unkEC8(screen);
        battle->unk498.unk5 = 1;
        battle->unk498.unk1 = 1;
        battle->stepState = 1;
        battle->unk560.unk15--;
    } else {
        battle->stepState = 2;
    }
}

s32 func_800944E8(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;

    switch (battle->stepState) {
    case 1:
        if (battle->unk498.unk0 == 0 && screen->panels[0].state == 2) {
            battle->stepState = 2;
            battle->unk560.unk15++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

/* Steps each slot's shown values (its sprite's unk43 and unk44) one unit toward the slot's unk6 and unk8, with a sound; 1 once all are there, 2 if a slot's unk8 reached 0 (marked in unk46F) */
s32 func_80094550(CardBattle *battle, CardScreen *screen) {
    s32 done = 0;
    s32 changed = 0;
    s32 side;
    s32 i;
    CardSprite *sprites;

    switch (battle->stepState) {
    case 1:
    default:
        for (i = 0; i < 12; i++) {
            battle->unk46F[i] = 0;
        }
        battle->stepState = 2;
        battle->unk438 = 0;
        break;
    case 2:
        done = 1;
        for (side = 0; side < 2; side++) {
            if (side == 0) {
                sprites = &screen->sprites[0];
            } else {
                sprites = &screen->sprites[6];
            }
            for (i = 0; i < battle->players[side].slotCount; i++) {
                if (sprites[i].unk43 != battle->players[side].slots[i].unk6) {
                    if (sprites[i].unk43 > battle->players[side].slots[i].unk6) {
                        sprites[i].unk43--;
                    } else {
                        sprites[i].unk43++;
                    }
                    done = 0;
                    changed = 1;
                }
                if (sprites[i].unk44 != battle->players[side].slots[i].unk8) {
                    if (sprites[i].unk44 > battle->players[side].slots[i].unk8) {
                        sprites[i].unk44--;
                    } else {
                        sprites[i].unk44++;
                    }
                    done = 0;
                    if (battle->players[side].slots[i].unk8 == 0) {
                        battle->unk46F[i + side * 6] = 1;
                        battle->unk438 = 1;
                    }
                    changed = 1;
                }
            }
        }
        if (done && battle->unk438) {
            done = 2;
        }
        if (changed) {
            SOUND.playSound(0x800452C6);
        }
        break;
    }
    return done;
}

/* Whether the condition kind (1-11) of the card being played holds for its side: 1 if it does */
s32 CARDGAME_checkPlayCondition(CardBattle *battle, CardScreen *screen, s32 kind) {
    CardDrawer drawer;
    CardDrawer drawer2;
    CardDrawer drawer3;
    CardDrawer drawer4;
    s32 ok = 0;
    s32 side = battle->unk560.unk20[battle->unk560.unk15 - 1].unk4;
    s32 other = side ^ 1;
    s32 i;
    s32 slot;
    s32 j;
    CardSlot *p;
    s32 n;
    s32 k;
    s32 valid;

    switch (kind) {
    case 1:
        if (battle->sides[other].pile.unkA == 0) {
            ok = 1;
        }
        break;
    case 2:
        initCardDrawer(&drawer);
        ok = 1;
        for (i = 0; i < battle->sides[other].pile.unkA; i++) {
            drawer.setCard(battle->cards[battle->sides[other].pile.unk64[i]] + 1);
            if (drawer.card[0] == 6 && drawer.card[3] == 0x10) {
                ok = 0;
                break;
            }
        }
        break;
    case 3:
        initCardDrawer(&drawer2);
        ok = 1;
        for (i = 0; i < battle->sides[other].pile.unkA; i++) {
            drawer2.setCard(battle->cards[battle->sides[other].pile.unk64[i]] + 1);
            if (drawer2.card[0] != 5) {
                ok = 0;
                break;
            }
        }
        break;
    case 4:
        if (battle->sides[side].pile.unk6 == 0) {
            ok = 1;
        }
        break;
    case 5:
        if (battle->sides[side].pile.unk8 == 0) {
            ok = 1;
        }
        break;
    case 6:
        if (battle->sides[other].pile.unk8 == 0) {
            ok = 1;
        }
        break;
    case 7:
        initCardDrawer(&drawer3);
        ok = 1;
        for (i = battle->sides[side].pile.unk4; i < 40; i++) {
            drawer3.setCard(battle->cards[battle->sides[side].pile.unk14[i]] + 1);
            if (drawer3.card[3] == 0x10) {
                ok = 0;
                break;
            }
        }
        break;
    case 8:
        initCardDrawer(&drawer4);
        ok = 1;
        for (i = battle->sides[side].pile.unk4; i < 40; i++) {
            drawer4.setCard(battle->cards[battle->sides[side].pile.unk14[i]] + 1);
            if (drawer4.card[3] != 0x10) {
                ok = 0;
                break;
            }
        }
        break;
    case 9:
        ok = 1;
        n = battle->unk560.unk15 - 1;
        for (slot = 0; slot < 12; slot++) {
            battle->unk46F[slot] = 0;
            if (slot < 6) {
                if (slot >= battle->players[0].slotCount) {
                    continue;
                }
                p = &battle->players[0].slots[slot];
            } else {
                if (slot - 6 >= battle->players[1].slotCount) {
                    continue;
                }
                p = &battle->players[1].slots[slot - 6];
            }
            if (p->order == battle->unk560.unk20[n].unk6) {
                ok = 0;
                break;
            }
        }
        break;
    case 10:
        ok = 1;
        for (i = 0; i < 12 && ok == 1; i++) {
            k = i - 6;
            if (i < 6) {
                valid = i < battle->players[0].slotCount;
            } else {
                valid = k < battle->players[1].slotCount;
            }
            if (valid) {
                switch (battle->unk560.unk20[battle->unk560.unk15 - 1].unk5) {
                case 1:
                    if (side == 0) {
                        if (i < 6) {
                            ok = 0;
                        }
                    } else {
                        if (i >= 6) {
                            ok = 0;
                        }
                    }
                    break;
                case 2:
                    if (side == 0) {
                        if (i >= 6) {
                            ok = 0;
                        }
                    } else {
                        if (i < 6) {
                            ok = 0;
                        }
                    }
                    break;
                case 3:
                    ok = 0;
                    break;
                case 4:
                    if (screen->getCardColor(screen, i < 6 ? battle->players[0].slots[i].card : battle->players[1].slots[i - 6].card) != 1) {
                        ok = 0;
                    }
                    break;
                case 5:
                    if (screen->getCardColor(screen, i < 6 ? battle->players[0].slots[i].card : battle->players[1].slots[i - 6].card) != 2) {
                        ok = 0;
                    }
                    break;
                case 6:
                    if (screen->getCardColor(screen, i < 6 ? battle->players[0].slots[i].card : battle->players[1].slots[i - 6].card) == 3) {
                        ok = 0;
                    }
                    break;
                case 7:
                    if (screen->getCardColor(screen, i < 6 ? battle->players[0].slots[i].card : battle->players[1].slots[i - 6].card) != 4) {
                        ok = 0;
                    }
                    break;
                case 8:
                    if (screen->getCardColor(screen, i < 6 ? battle->players[0].slots[i].card : battle->players[1].slots[i - 6].card) == 6) {
                        ok = 0;
                    }
                    break;
                }
            }
        }
        break;
    case 11:
        ok = 1;
        for (j = 0; j < battle->sides[side].pile.unkA; j++) {
            if (battle->unk560.unk20[battle->unk560.unk15 - 1].unk6 == battle->sides[side].pile.unk64[j]) {
                ok = 0;
                break;
            }
        }
        break;
    }
    return ok;
}

/* The mode's task: sets up the display and starts the battle, then returns
   to the field once it is over (or to mode 0x1500 when the mode's low
   bits are set) */
void CARDGAME_updateScene(Task *task, CardBattle **items) {
    TimLoader tim;
    Layer *layer;

    switch (task->state) {
    case 0:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0xA000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        initTimLoader(&tim);
        tim.setImagePos(0x280, 0);
        tim.loadArchive(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16));
        tim.setImagePos(0x340, 0);
        tim.loadArchive(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 1));
        layer = GFX.funcs.createLayer(&CARDGAME_screenRect, 3, 0x100);
        layer->setBgColor(layer, 0x1F, 0x1F, 0x1F);
        items[0] = CARDGAME_createBattle(GAME_FUNCS.getModeArg());
        task->nextState(task);
        break;
    case 1:
        if (items[0]->result == 2) {
            task->setState(task, 2);
            items[0]->setState(items[0], 3);
        }
        break;
    case 2:
        switch (task->substate) {
        case 0:
        default:
            GAME.funcs.requestMode((GAME.funcs.getMode() & 0xF) ? 0x1500 : GAME.fieldMode, 0);
            task->nextSubstate(task);
            break;
        case 1:
            break;
        }
        break;
    case 3:
        break;
    }
}

/* The mode's entry point (MODE_ENTRY_POINTS) */
Task *CARDGAME_start(void) {
    return createTask(CARDGAME_updateScene, sizeof(Task), 4);
}

void CARDGAME_drawMarker(CardMarker *marker) {
    SpriteDrawer drawer;
    s32 row;

    if (marker->scaleX != 0 && marker->scaleY != 0) {
        initSpriteDrawer(&drawer);
        drawer.setPivot(marker->x, marker->y + 19);
        drawer.setScale(marker->scaleX, marker->scaleY, 0x1000);
        if (marker->fast == 0) {
            drawer.setClutRow((marker->time >> 2) % 16);
        } else {
            row = marker->time >> 1;
            if (row >= 7) {
                row = 7;
            }
            drawer.setClutRow(row);
        }
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x280, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0x47, marker->x, marker->y);
        marker->time += GFX.funcs.getFrameTime();
    }
}

void CARDGAME_updateMarker(CardMarker *marker) {
    switch (marker->state) {
    case 0:
    default:
        marker->nextState(marker);
        marker->scaleDuration = 10;
        marker->scaleTime = 10;
        marker->phase = 0;
        marker->scaleX = 0x1000;
        marker->scaleY = 0;
        break;
    case 1:
        switch (marker->phase) {
        case 0:
            marker->scaleY = 0x1000 - (marker->scaleTime << 12) / marker->scaleDuration;
            marker->scaleTime -= GFX.funcs.getFrameTime();
            if (marker->scaleTime <= 0) {
                marker->scaleY = 0x1000;
                marker->phase = 1;
            }
            break;
        case 1:
            break;
        case 2:
            marker->setState(marker, 2);
            break;
        }
        break;
    case 2:
        marker->scaleY = (marker->scaleTime << 12) / marker->scaleDuration;
        marker->scaleTime -= GFX.funcs.getFrameTime();
        if (marker->scaleTime <= 0) {
            marker->scaleY = 0;
            marker->setState(marker, 3);
        }
        break;
    case 3:
        break;
    }
    CARDGAME_drawMarker(marker);
}

void CARDGAME_setMarkerPos(CardMarker *marker, s16 x, s16 y) {
    marker->x = x;
    marker->y = y;
}

void CARDGAME_setMarkerFast(CardMarker *marker) {
    marker->fast = 1;
    marker->time = 0;
}

void CARDGAME_closeMarker(CardMarker *marker) {
    marker->scaleDuration = 5;
    marker->scaleTime = 5;
    marker->phase = 2;
    marker->scaleY = 0x1000;
}

CardMarker *CARDGAME_createMarker(s16 x, s16 y) {
    CardMarker *marker = createTask(CARDGAME_updateMarker, sizeof(CardMarker), 0);

    marker->setPos = CARDGAME_setMarkerPos;
    marker->close = CARDGAME_closeMarker;
    marker->setFast = CARDGAME_setMarkerFast;
    marker->x = x;
    marker->y = y;
    marker->fast = 0;
    return marker;
}

void CARDGAME_drawDeckWindow(CardDeckWindow *window) {
    s16 rows[8] = {0, 1, 2, 3, 2, 1, 0, 0};
    SpriteDrawer frame;
    SpriteDrawer icon;
    s32 i;

    if (window->scaleX != 0 && window->scaleY != 0) {
        initSpriteDrawer(&frame);
        frame.setPivot(window->x, window->y);
        frame.setScale(window->scaleX, window->scaleY, 0x1000);
        frame.setLayerId(0x100, 1);
        frame.setTexture(0x280, 0);
        frame.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0x45, window->x, window->y);
        initSpriteDrawer(&icon);
        icon.setPivot(window->x, window->y);
        if (window->blink != 0) {
            i = window->time >> 1;
            if (i >= 7) {
                i = 7;
            }
            icon.setClutRow(rows[i]);
            window->time += GFX.funcs.getFrameTime();
        }
        icon.setScale(window->scaleX, window->scaleY, 0x1000);
        icon.setLayerId(0x100, 1);
        icon.setTexture(0x280, 0);
        icon.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0x46, window->x, window->y);
    }
}

void CARDGAME_updateDeckWindow(CardDeckWindow *window, TextWindow **texts) {
    s32 i;

    switch (window->state) {
    case 0:
    default:
        window->nextState(window);
        window->scaleDuration = 12;
        window->scaleTime = 12;
        window->phase = 0;
        window->scaleY = 0x1000;
        window->scaleX = 0;
        texts[0] = createTextWindow(0x100, 1, 0, 0);
        texts[0]->setString(texts[0], GAME.decks[window->deck].name, -1);
        texts[0]->setPos(texts[0], window->x + 5, window->y + 3);
        for (i = 0; i < 6; i++) {
            texts[i + 1] = createTextWindow(0x100, 1, 0, 0);
            texts[i + 1]->setPos(texts[i + 1], window->x + CARDGAME_deckCountOffsets[i].x, window->y + CARDGAME_deckCountOffsets[i].y);
            texts[i + 1]->setNumber(texts[i + 1], 0, window->counts[i]);
            texts[i + 1]->setRightAlign(texts[i + 1], 1);
        }
        break;
    case 1:
        switch (window->phase) {
        case 0:
            window->scaleX = 0x1000 - (window->scaleTime << 12) / window->scaleDuration;
            window->scaleTime -= GFX.funcs.getFrameTime();
            if (window->scaleTime <= 0) {
                window->scaleX = 0x1000;
                window->phase = 1;
            }
            break;
        case 1:
            break;
        case 2:
            window->setState(window, 2);
            break;
        }
        break;
    case 2:
        window->scaleX = (window->scaleTime << 12) / window->scaleDuration;
        window->scaleTime -= GFX.funcs.getFrameTime();
        if (window->scaleTime <= 0) {
            window->scaleX = 0;
            window->setState(window, 3);
        }
        break;
    case 3:
        break;
    }
    if (window->phase == 1) {
        texts[0]->setPos(texts[0], window->x + 5, window->y + 3);
        texts[0]->setVisible(texts[0], 1);
        for (i = 0; i < 6; i++) {
            texts[i + 1]->setVisible(texts[i + 1], 1);
            texts[i + 1]->setPos(texts[i + 1], window->x + CARDGAME_deckCountOffsets[i].x, window->y + CARDGAME_deckCountOffsets[i].y);
        }
    } else {
        texts[0]->setVisible(texts[0], 0);
        for (i = 0; i < 6; i++) {
            texts[i + 1]->setVisible(texts[i + 1], 0);
        }
    }
    CARDGAME_drawDeckWindow(window);
}

void CARDGAME_setDeckWindowBlink(CardDeckWindow *window) {
    window->blink = 1;
    window->time = 0;
}

void CARDGAME_closeDeckWindow(CardDeckWindow *window) {
    window->scaleDuration = 6;
    window->scaleTime = 6;
    window->phase = 2;
    window->scaleX = 0x1000;
}

CardDeckWindow *CARDGAME_createDeckWindow(s32 deck, s32 x, s32 y) {
    CardDrawer drawer;
    CardDeckWindow *window;
    s32 i;

    initCardDrawer(&drawer);
    window = createTask(CARDGAME_updateDeckWindow, sizeof(CardDeckWindow), 7 * 4);
    for (i = 0; i < 6; i++) {
        window->counts[i] = 0;
    }
    for (i = 0; i < 40; i++) {
        drawer.setCard(GAME.decks[deck].cards[i]);
        window->counts[drawer.card[0] - 1]++;
    }
    window->setBlink = CARDGAME_setDeckWindowBlink;
    window->deck = deck;
    window->x = x;
    window->y = y;
    window->blink = 0;
    window->close = CARDGAME_closeDeckWindow;
    return window;
}

void func_80095B44(CardScreen *screen) {
    SpriteDrawer drawer;
    s32 row;
    s32 x;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 2);
    row = 0;
    drawer.setTexture(0x340, 0);
    switch (screen->unkE9E) {
    case 1:
        if (screen->unkE9D >= 4) {
            screen->unkE9D -= 4;
            if (++screen->unkE9C >= 11) {
                screen->unkE9C = 11;
                screen->unkE9E = 2;
            }
        }
        row = screen->unkE9C;
        screen->unkE9D += GFX.funcs.getFrameTime();
        break;
    case 2:
        row = 11;
        break;
    case 0:
        break;
    }
    drawer.setClutRow(row);
    x = (screen->time >> 1) & 0x3F;
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0, x, x);
}

void CARDGAME_drawNumber(CardNumber *number, s32 scaled) {
    SpriteDrawer drawer;
    s32 value;
    s32 digit;
    s32 i;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, number->depth);
    drawer.setTexture(0x340, 0);
    if (scaled != 0) {
        drawer.setPivot(number->pivotX, number->pivotY);
        drawer.setScale(number->scaleX, number->scaleY, 0x1000);
    }
    value = number->value;
    for (i = 0; i < number->digits; i++) {
        digit = value % 10;
        if (i == 0 || number->leadingZeros != 0 || digit != 0 || value / 10 != 0) {
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), digit + 0x14,
                        number->x + (number->digits - 1 - i) * 7, number->y);
        }
        value /= 10;
    }
}

void func_80095E14(CardScreen *screen, CardScreenItems *items, s32 index, CardScreenDC0 *p) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    drawer.setPivot(D_800A485C[index].x + 4, D_800A485C[index].y + 23);
    drawer.setScale(0x1000, p->to, 0x1000);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), p->value + 6, D_800A485C[index].x, D_800A485C[index].y);
}

void func_80095EE4(CardScreen *screen, CardScreenItems *items, s32 index, CardScreenDC0 *p) {
    if (p->state != 0) {
        switch (p->state) {
        case 1:
        default:
            p->to = 0x1000 - (p->time << 12) / p->duration;
            p->time -= GFX.funcs.getFrameTime();
            if (p->time <= 0) {
                p->state = 2;
            }
            break;
        case 2:
            p->to = 0x1000;
            break;
        case 3:
            p->time -= GFX.funcs.getFrameTime();
            if (p->time <= 0) {
                p->state = 0;
            }
            p->to = (p->time << 12) / p->duration;
            break;
        }
        func_80095E14(screen, items, index, p);
    }
}

void func_80096018(CardScreen *screen, CardScreenItems *items) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_80095EE4(screen, items, i, &screen->unkDC0[i]);
    }
}

/* Draws the number in a type 3 window: its low four bits, and the sprite
   for its high bits */
static inline void drawWindowCount(CardScreenE0C *window) {
    CardNumber number;
    SpriteDrawer digits;

    number.depth = 1;
    number.digits = 2;
    number.leadingZeros = 0;
    number.x = window->x + 0x18;
    number.y = window->y + 4;
    number.value = window->unk10 & 0xF;
    number.pivotX = window->x + CARDGAME_windowLayouts[window->unkC].x;
    number.pivotY = window->y + CARDGAME_windowLayouts[window->unkC].y;
    number.scaleX = window->from;
    number.scaleY = 0x1000;
    CARDGAME_drawNumber(&number, 1);
    initSpriteDrawer(&digits);
    digits.setLayerId(0x100, 1);
    digits.setTexture(0x280, 0);
    digits.setPivot(window->x + CARDGAME_windowLayouts[window->unkC].x,
                    window->y + CARDGAME_windowLayouts[window->unkC].y);
    digits.setScale(window->from, 0x1000, 0x1000);
    digits.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), (window->unk10 >> 4) * 3 + 0x1D,
                window->x + 6, window->y + 2);
}

void func_80096080(CardScreen *screen, CardScreenItems *items, CardScreenE0C *window) {
    s32 offset = 0;

    if (window->unkC == 2 && window->unk14[2] == 1) {
        offset = 0x45;
    }
    if (window->state == 2 && window->unkC == 3 && window->unkE != 0) {
        drawWindowCount(window);
    }
    {
    SpriteDrawer frame;

    if (CARDGAME_windowLayouts[window->unkC].kind == 2) {
        initSpriteDrawer(&frame);
        frame.setLayerId(0x100, 1);
        frame.setTexture(0x340, 0);
        if (window->from != 0x1000) {
            frame.setPivot(window->x + CARDGAME_windowLayouts[window->unkC].x,
                           window->y + CARDGAME_windowLayouts[window->unkC].y);
            frame.setScale(window->from, 0x1000, 0x1000);
        }
        frame.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), CARDGAME_windowLayouts[window->unkC].sprite,
                   window->x + offset, window->y);
    } else {
        initSpriteDrawer(&frame);
        frame.setLayerId(0x100, 1);
        frame.setTexture(0x280, 0);
        if (window->from != 0x1000) {
            frame.setPivot(window->x + CARDGAME_windowLayouts[window->unkC].x,
                           window->y + CARDGAME_windowLayouts[window->unkC].y);
            frame.setScale(window->from, 0x1000, 0x1000);
        }
        frame.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), CARDGAME_windowLayouts[window->unkC].sprite,
                   window->x + offset, window->y);
    }
    }
}

void func_8009642C(CardScreen *screen, CardScreenItems *items, CardScreenE0C *window) {
    s32 values[2];
    s32 i;

    values[0] = window->unk14[0];
    values[1] = window->unk14[1];
    for (i = 0; i < 2; i++) {
        items->texts[i]->setPos(items->texts[i], window->x + 0x67, window->y + 4 + i * 13);
        items->texts[i]->setNumber(items->texts[i], 0, values[i]);
        items->texts[i]->setRightAlign(items->texts[i], 1);
    }
}

void func_80096504(CardScreen *screen, CardScreenE0C *window, TextWindow *text, s32 file, s32 index) {
    if (window->unk10 != 0) {
        text->setPos(text, window->x + D_800A488C[index], window->y + 4);
        text->setString(text, FILE_CACHE.load(file), window->unk10);
    } else {
        text->setVisible(text, 0);
    }
}

void func_800965D8(CardScreen *screen, CardScreenItems *items, CardScreenE0C *window, TextWindow *text, s32 file) {
    TextTools tools;
    s32 width;

    if (window->unk10 != 0) {
        text->setString(text, FILE_CACHE.load(file), window->unk10);
        initTextTools(&tools);
        width = tools.measure(text->text, text->style, text->spacingX);
        if (window->unk10 == 0x1F) {
            text->setPalette(text, 3);
        } else {
            text->setPalette(text, 0);
        }
        text->setVisible(text, 1);
        text->setPos(text, 0xA0 - width / 2, window->y + 4);
    } else {
        text->setVisible(text, 0);
    }
}

void func_800966FC(CardScreen *screen, CardScreenItems *items, CardScreenE0C *window, s32 index) {
    if (window->state == 0) {
        return;
    }
    switch (window->state) {
    case 1:
    default:
        window->from = 0x1000 - (window->time << 12) / window->duration;
        window->time -= GFX.funcs.getFrameTime();
        if (window->time <= 0) {
            window->state = 2;
            switch (index) {
            case 0:
                func_80096504(screen, window, items->moreTexts[2], TEXT_FILE(0x10), 1);
                break;
            case 2:
                func_80096504(screen, window, items->moreTexts[4], TEXT_FILE(0x17), 0);
                break;
            case 3:
                func_80096504(screen, window, items->moreTexts[3], TEXT_FILE(0x10), 0);
                break;
            case 5:
                if (window->unkC == 5) {
                    func_800965D8(screen, items, window, items->moreTexts[0], TEXT_FILE(0x10));
                } else {
                    func_80096504(screen, window, items->moreTexts[0], TEXT_FILE(0x10), window->unk10 != 0x24);
                }
                break;
            case 1:
            case 4:
                break;
            }
        }
        break;
    case 2:
        window->from = 0x1000;
        switch (index) {
        case 2:
            func_80096504(screen, window, items->moreTexts[4], TEXT_FILE(0x17), 0);
            break;
        case 3:
            func_80096504(screen, window, items->moreTexts[3], TEXT_FILE(0x10), 0);
            break;
        case 4:
            if (window->unk10 == 0x1F4) {
                if (window->unk14[2] == 0) {
                    window->unk10 = 0x2A;
                    func_80096504(screen, window, items->moreTexts[5], TEXT_FILE(0x10), 1);
                } else {
                    window->unk10 = 0x40;
                    func_8009642C(screen, items, window);
                    func_80096504(screen, window, items->moreTexts[5], TEXT_FILE(0x10), 2);
                }
            } else {
                items->texts[0]->setVisible(items->texts[0], 0);
                items->texts[1]->setVisible(items->texts[1], 0);
                func_80096504(screen, window, items->moreTexts[5], TEXT_FILE(0x1E), 0);
            }
            break;
        }
        break;
    case 3:
        switch (index) {
        case 0:
            items->moreTexts[2]->setVisible(items->moreTexts[2], 0);
            break;
        case 2:
            items->moreTexts[4]->setVisible(items->moreTexts[4], 0);
            break;
        case 3:
            items->moreTexts[3]->setVisible(items->moreTexts[3], 0);
            break;
        case 4:
            items->texts[0]->setVisible(items->texts[0], 0);
            items->texts[1]->setVisible(items->texts[1], 0);
            items->moreTexts[5]->setVisible(items->moreTexts[5], 0);
            break;
        case 5:
            items->moreTexts[0]->setVisible(items->moreTexts[0], 0);
            break;
        case 1:
            break;
        }
        window->time -= GFX.funcs.getFrameTime();
        if (window->time <= 0) {
            window->state = 0;
        }
        window->from = (window->time << 12) / window->duration;
        break;
    }
    func_80096080(screen, items, window);
}

void func_80096A9C(CardScreen *screen, CardScreenItems *items) {
    s32 i;

    for (i = 0; i < 6; i++) {
        func_800966FC(screen, items, &screen->unkE0C[i], i);
    }
}

void func_80096B04(CardScreen *screen, CardScreenItems *items, s16 scale, s32 x, s32 y) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x280, 0);
    drawer.setPivot(0, 0x78);
    drawer.setScale(scale, 0x1000, 0x1000);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0x1A, x, y);
}

void func_80096BD0(CardScreen *screen, CardScreenItems *items, s32 x, s32 y) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x280, 0);
    drawer.setScale(0x1000, 0x1000, 0x1000);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0x18, x, y);
}

/* The message window: it opens at place unkDE4, shows message unkDE8 with the cursor, then closes */
void CARDGAME_updateMessageWindow(CardScreen *screen, CardScreenItems *items) {
    TextTools tools;
    s16 scale;
    s32 t;
    s32 i;
    s32 x;

    if (screen->unkDFA == 0) {
        return;
    }
    switch (screen->unkDFA) {
    case 1:
    default:
        t = screen->unkDF0 << 12;
        scale = 0x1000 - (screen->unkDF2 != 0 ? t / screen->unkDF2 : t);
        screen->unkDF0 -= GFX.funcs.getFrameTime();
        if (screen->unkDF0 <= 0) {
            screen->unkDFA = 2;
#if VERSION_US
            if (screen->unkDFB != 0) {
                items->cursor->setVisible(items->cursor, 1);
                items->cursor->setPos(items->cursor, 0x14, D_800A4894[screen->unkDE4][1] + 0x11 + screen->unkDF4 * 14);
                items->moreTexts[7]->setString(items->moreTexts[7], FILE_CACHE_LOAD[0](TEXT_FILE(0x10)), 0x18);
                items->moreTexts[7]->setPos(items->moreTexts[7], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 0x12);
            } else {
                items->moreTexts[7]->setVisible(items->moreTexts[7], 0);
                items->cursor->setVisible(items->cursor, 0);
            }
#elif VERSION_EU
            switch (screen->unkDFB) {
            case 0:
            default:
                items->moreTexts[7]->setVisible(items->moreTexts[7], 0);
                items->cursor->setVisible(items->cursor, 0);
                break;
            case 1:
                items->cursor->setVisible(items->cursor, 1);
                items->cursor->setPos(items->cursor, 0x14, D_800A4894[screen->unkDE4][1] + 0x11 + screen->unkDF4 * 14);
                items->moreTexts[7]->setString(items->moreTexts[7], FILE_CACHE_LOAD[0](TEXT_FILE(0x10)), 0x18);
                items->moreTexts[7]->setPos(items->moreTexts[7], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 0x12);
                break;
            case 2:
            case 3:
                items->cursor->setVisible(items->cursor, 1);
                items->cursor->setPos(items->cursor, 0x14, D_800A4894[screen->unkDE4][1] + 0x11 + screen->unkDF4 * 14);
                items->moreTexts[7]->setString(items->moreTexts[7], FILE_CACHE.load(TEXT_FILE(0x10)), 0x45);
                if (screen->unkDFB == 3) {
                    items->moreTexts[7]->setPalette(items->moreTexts[7], 7);
                }
                items->moreTexts[7]->setPos(items->moreTexts[7], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 0x12);
                items->texts[0]->setString(items->texts[0], FILE_CACHE.load(TEXT_FILE(0x10)), 0x46);
                items->texts[0]->setRightAlign(items->texts[0], 0);
                items->texts[0]->setPos(items->texts[0], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 0x20);
                break;
            }
#endif
            if (screen->unkDE4 == 3) {
                items->moreTexts[1]->setPos(items->moreTexts[1], D_800A4894[3][0] + 0x40, D_800A4894[3][1] + 4);
                items->moreTexts[1]->setString(items->moreTexts[1], FILE_CACHE.load(TEXT_FILE(0x10)), 0x42);
                items->moreTexts[7]->setString(items->moreTexts[7], FILE_CACHE.load(TEXT_FILE(0x6B)), screen->unkDE8);
                items->moreTexts[7]->setPos(items->moreTexts[7], D_800A4894[screen->unkDE4][0] + 0x40, D_800A4894[screen->unkDE4][1] + 0x12);
            } else if (screen->unkDE8 != 0) {
                items->moreTexts[1]->setPos(items->moreTexts[1], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 4);
                items->moreTexts[1]->setString(items->moreTexts[1], FILE_CACHE.load(TEXT_FILE(0x10)), screen->unkDE8);
                if (screen->unkDE8 == 0x13) {
                    items->moreTexts[7]->setString(items->moreTexts[7], FILE_CACHE.load(TEXT_FILE(0x10)), 0x2B);
                    items->moreTexts[7]->setPos(items->moreTexts[7], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 0x12);
                    initTextTools(&tools);
                    x = tools.measure(items->moreTexts[7]->text, items->moreTexts[7]->style, items->moreTexts[7]->spacingX) + 0x1B;
                    for (i = 0; i < 2; i++) {
                        items->texts[i]->setPos(items->texts[i], D_800A4894[screen->unkDE4][0] + x + 0xE, D_800A4894[screen->unkDE4][1] + 0x12 + i * 14);
                        items->texts[i]->setNumber(items->texts[i], 0, screen->panels[i].unk44);
                        items->texts[i]->setRightAlign(items->texts[i], 0);
                    }
                } else if (screen->unkDE8 == 0x3E) {
                    items->texts[0]->setPos(items->texts[0], D_800A4894[screen->unkDE4][0] + 0x3E, D_800A4894[screen->unkDE4][1] + 4);
                    items->texts[0]->setNumber(items->texts[0], 0, screen->unk5E);
                    items->texts[0]->setRightAlign(items->texts[0], 1);
                    items->texts[1]->setString(items->texts[1], FILE_CACHE.load(TEXT_FILE(0x2C)), (screen->unk5C + 1) / 2);
                    items->texts[1]->setPos(items->texts[1], D_800A4894[screen->unkDE4][0] + 0x1B, D_800A4894[screen->unkDE4][1] + 0x12);
                }
            } else {
                items->moreTexts[1]->setVisible(items->moreTexts[1], 0);
            }
        }
        break;
    case 2:
        scale = 0x1000;
        if (screen->unkDE4 == 3) {
            func_80096BD0(screen, items, 0x1C, 0x64);
        }
        if (screen->unkDFB != 0) {
            items->cursor->setPos(items->cursor, 0x14, D_800A4894[screen->unkDE4][1] + 0x11 + screen->unkDF4 * 14);
        }
        break;
    case 4:
        scale = 0x1000;
        items->cursor->setPos(items->cursor, 0x14 - rsin((screen->unkDF0 << 12) / 20) / 512, D_800A4894[screen->unkDE4][1] + 0x11 + screen->unkDF4 * 14);
        screen->unkDF0 -= GFX.funcs.getFrameTime();
        if (screen->unkDF0 <= 0) {
            items->cursor->setVisible(items->cursor, 0);
            screen->unkEE8(screen);
            items->cursor->setIdleDelay(items->cursor, 0x20);
            screen->unkDFA = 5;
        }
        break;
    case 5:
        items->cursor->setVisible(items->cursor, 0);
        items->moreTexts[1]->setVisible(items->moreTexts[1], 0);
#if VERSION_EU
        items->moreTexts[7]->setPalette(items->moreTexts[7], 0);
#endif
        items->moreTexts[7]->setVisible(items->moreTexts[7], 0);
        items->texts[0]->setVisible(items->texts[0], 0);
        items->texts[1]->setVisible(items->texts[1], 0);
        items->texts[2]->setVisible(items->texts[2], 0);
        screen->unkDF0 -= GFX.funcs.getFrameTime();
        if (screen->unkDF0 <= 0) {
            screen->unkDFA = 0;
        }
        scale = (screen->unkDF0 << 12) / screen->unkDF2;
        break;
    }
    func_80096B04(screen, items, scale, D_800A4894[screen->unkDE4][0], D_800A4894[screen->unkDE4][1]);
}

void func_8009747C(CardScreen *screen, CardScreenItems *items, s16 scale, s32 x, s32 y) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    drawer.setPivot(0, 0x86);
    drawer.setScale(scale, 0x1000, 0x1000);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 1, x, y);
}

/* A menu window (CardScreen.unkE00): it opens, shows text file 0x10 with the
   cursor on row unkE04, then closes */
void func_80097548(CardScreen *screen, CardScreenItems *items) {
    s16 scale;
    s32 t;

    if (screen->unkE0A == 0) {
        return;
    }
    switch (screen->unkE0A) {
    case 1:
    default:
        t = screen->unkE00 << 12;
        scale = 0x1000 - (screen->unkE02 != 0 ? t / screen->unkE02 : t);
        screen->unkE00 -= GFX.funcs.getFrameTime();
        if (screen->unkE00 <= 0) {
            screen->unkE0A = 2;
            items->cursor->setVisible(items->cursor, 1);
            items->cursor->setPos(items->cursor, 10, screen->unkE04 * 14 + 0x65);
            items->moreTexts[6]->setString(items->moreTexts[6], FILE_CACHE_LOAD[0](TEXT_FILE(0x10)), 0x20);
            items->moreTexts[6]->setPos(items->moreTexts[6], 0x18, 0x65);
        }
        break;
    case 2:
        scale = 0x1000;
        items->cursor->setPos(items->cursor, 10, screen->unkE04 * 14 + 0x65);
        break;
    case 4:
        scale = 0x1000;
        items->cursor->setPos(items->cursor, 10 - rsin((screen->unkE00 << 12) / 20) / 512, screen->unkE04 * 14 + 0x65);
        screen->unkE00 -= GFX.funcs.getFrameTime();
        if (screen->unkE00 <= 0) {
            items->cursor->setVisible(items->cursor, 0);
            screen->unkEF8(screen);
            items->cursor->setIdleDelay(items->cursor, 0x20);
            screen->unkE0A = 5;
        }
        break;
    case 5:
        items->cursor->setVisible(items->cursor, 0);
        items->moreTexts[6]->setVisible(items->moreTexts[6], 0);
        screen->unkE00 -= GFX.funcs.getFrameTime();
        if (screen->unkE00 <= 0) {
            screen->unkE0A = 0;
        }
        scale = (screen->unkE00 << 12) / screen->unkE02;
        break;
    }
    func_8009747C(screen, items, scale, 0, 0x60);
}

s32 CARDGAME_getHandOffset(s32 count, s32 index) {
    s32 step;

    if (count < 7) {
        step = 0x2900;
    } else {
        step = 0xF600 / count;
    }
    return step * index;
}

/* Draws a side's panel (CardScreen.panels): its lights, bars, numbers and parts, which blink by its flags */
void CARDGAME_drawPanel(CardPanel *panel, CardScreenItems *items, s32 side) {
    s32 y;
    s32 imageY;

    y = panel->y;
    imageY = panel->unk3E;
#if VERSION_EU
    if (SHIFT_PAL_SCREEN) {
        if (side == 0) {
            y += 12;
            imageY += 12;
        } else {
            y -= 12;
            imageY -= 12;
        }
    }
#endif
    /* the lights */
    {
        SpriteDrawer drawer;
        s32 t;
        s32 i;

        t = panel->unk8 % 36;
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x340, 0);
        drawer.setClutRow(D_800A494C[t / 6]);
        for (i = 0; i < 5; i++) {
            if (panel->flags[i] != 0) {
                drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0xD, panel->x + D_800A48B4[side].flagLights.x + i * 0x2A, y + D_800A48B4[side].flagLights.y);
            }
        }
        if (panel->flags[8] != 0) {
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0xC, panel->x + D_800A48B4[side].unk44.x, y + D_800A48B4[side].unk44.y);
        }
        if (panel->flags[9] != 0) {
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0xC, panel->x + D_800A48B4[side].unk48.x, y + D_800A48B4[side].unk48.y);
        }
        if (panel->flags[6] != 0) {
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0xE, panel->x + D_800A48B4[side].unk38.x, y + D_800A48B4[side].unk38.y);
        }
        if (panel->flags[7] != 0) {
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0xE, panel->x + D_800A48B4[side].unk3C.x, y + D_800A48B4[side].unk3C.y);
        }
        if (panel->flags[5] != 0) {
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0xF, panel->unk20 + D_800A48B4[side].unk40.x, panel->unk22 + D_800A48B4[side].unk40.y);
        }
    }
    /* the bars and the numbers */
    {
        SpriteDrawer drawer;
        CardNumber number;
        s32 t;
        s32 i;

        t = panel->unk8 % 24;
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x340, 0);
        if (panel->flags[8] != 0) {
            drawer.setClutRow(t / 6 + 1);
        } else {
            drawer.setClutRow(0);
        }
#if VERSION_US
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), D_800A4954[1][0], panel->x + D_800A48B4[side].unk18.x, y + D_800A48B4[side].unk18.y);
#elif VERSION_EU
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), D_800A4954[LANGUAGE][0], panel->x + D_800A48B4[side].unk18.x, y + D_800A48B4[side].unk18.y);
#endif
        if (panel->flags[9] != 0) {
            drawer.setClutRow(t / 6 + 1);
        } else {
            drawer.setClutRow(0);
        }
#if VERSION_US
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), D_800A4954[1][1], panel->x + D_800A48B4[side].unk20.x, y + D_800A48B4[side].unk20.y);
#elif VERSION_EU
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), D_800A4954[LANGUAGE][1], panel->x + D_800A48B4[side].unk20.x, y + D_800A48B4[side].unk20.y);
#endif

        number.depth = 1;
        number.x = panel->x + D_800A48B4[side].unkC.x;
        number.y = D_800A48B4[side].unkC.y + y;
        number.digits = 2;
        number.leadingZeros = 1;
        number.value = panel->unk18[5];
        CARDGAME_drawNumber(&number, 0);
        number.x = panel->x + D_800A48B4[side].unk10.x;
        number.y = D_800A48B4[side].unk10.y + y;
        number.digits = 2;
        number.leadingZeros = 1;
        number.value = panel->unk18[6];
        CARDGAME_drawNumber(&number, 0);
        number.x = panel->x + D_800A48B4[side].unk1C.x;
        number.y = D_800A48B4[side].unk1C.y + y;
        number.digits = 3;
        number.leadingZeros = 0;
        number.value = panel->unk10;
        CARDGAME_drawNumber(&number, 0);
        number.x = panel->x + D_800A48B4[side].unk24.x;
        number.y = D_800A48B4[side].unk24.y + y;
        number.digits = 3;
        number.leadingZeros = 0;
        number.value = panel->unk12;
        CARDGAME_drawNumber(&number, 0);
        for (i = 0; i < 5; i++) {
            number.x = panel->x + D_800A48B4[side].flagNumbers.x + i * 0x2A;
            number.y = D_800A48B4[side].flagNumbers.y + y;
            number.digits = 2;
            number.leadingZeros = 1;
            number.value = panel->unk18[i];
            CARDGAME_drawNumber(&number, 0);
        }
        number.x = panel->unk20 + D_800A48B4[side].unk14.x;
        number.y = panel->unk22 + D_800A48B4[side].unk14.y;
        number.digits = 2;
        number.leadingZeros = 1;
        number.value = panel->unk28;
        CARDGAME_drawNumber(&number, 0);
    }
    /* the image, the blinking parts and the frame */
    {
        SpriteDrawer drawer;
        s32 t;
        s32 frame;
        s32 boxFrame;
        s32 iconT;
        s32 iconFrame;
        s32 i;

        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x280, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A48B4[side].unk2 + panel->unk44, panel->unk3C, imageY);
        t = panel->unk8 % 30;
        if (panel->flags[7] != 0) {
            frame = t / 6;
        } else {
            frame = 0;
        }
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A4964[frame] + 9, panel->x + D_800A48B4[side].unk2C.x, y + D_800A48B4[side].unk2C.y);
        t = panel->unk8 % 30;
        if (panel->flags[6] != 0) {
            frame = t / 6;
        } else {
            frame = 0;
        }
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A496C[frame] + 6, panel->x + D_800A48B4[side].unk28.x, y + D_800A48B4[side].unk28.y);
        t = panel->unk8 % 30;
        if (panel->flags[5] != 0) {
            boxFrame = t / 6;
        } else {
            boxFrame = 0;
        }
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A4974[boxFrame] + 0x31, panel->unk20, panel->unk22);
        iconT = panel->unk8 % 30;
        for (i = 0; i < 5; i++) {
            if (panel->flags[i] != 0) {
                iconFrame = iconT / 6;
            } else {
                iconFrame = 0;
            }
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A497C[i] + D_800A4984[iconFrame], panel->x + D_800A48B4[side].flagIcons.x + i * 0x2A, y + D_800A48B4[side].flagIcons.y);
        }
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A48B4[side].unk3, panel->unk20 + D_800A48B4[side].unk30.x, panel->unk22 + D_800A48B4[side].unk30.y);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), D_800A48B4[side].frame, panel->x, y);
    }
    panel->unk8 = (panel->unk8 + GFX.funcs.getFrameTime()) & 0xFFFF;
}

/* Moves a side's panel between its shown and hidden places: in (state 1), out (3), or only x/y in or out (4, 5) */
void CARDGAME_slidePanel(CardPanel *panel, CardScreenItems *items, s32 side) {
    s32 shownX;
    s32 shownY;
    s32 hiddenX;
    s32 hiddenY;
    s32 shown20;
    s32 hidden20;
    s32 shown22;
    s32 hidden22;
    s32 shown3C;
    s32 hidden3C;
    s32 shown3E;
    s32 hidden3E;

    if (side == 0) {
        shownX = 0;
        shownY = 0x8D;
        hiddenX = 0;
        hiddenY = 0xF1;
        shown20 = 0x120;
        shown22 = 0x8F;
        hidden20 = 0x147;
        hidden22 = 0x8F;
        shown3C = 0x113;
        shown3E = 0xBD;
        hidden3E = 0xBD;
        /* the match depends on setting it in both branches, not once after them */
        hidden3C = 0x13A;
    } else {
        shownX = 0;
        shownY = 0;
        hiddenX = 0;
        hiddenY = -100;
        shown20 = 0x120;
        shown22 = 0x50;
        hidden20 = 0x147;
        hidden22 = 0x50;
        shown3C = 0x113;
        shown3E = 0x26;
        hidden3E = 0x26;
        hidden3C = 0x13A;
    }
    /* the match depends on the empty case 0 */
    switch (panel->unk6) {
    case 1:
        panel->unk6 = 0;
        break;
    case 2:
        panel->unk6 = 0;
        break;
    case 0:
        break;
    }
    switch (panel->state) {
    case 1:
        if ((panel->time -= GFX.funcs.getFrameTime()) > 0) {
            panel->x = shownX - (shownX - hiddenX) * panel->time / panel->duration;
            panel->y = shownY - (shownY - hiddenY) * panel->time / panel->duration;
            panel->unk20 = shown20 - (shown20 - hidden20) * panel->time / panel->duration;
            panel->unk22 = shown22 - (shown22 - hidden22) * panel->time / panel->duration;
            panel->unk3C = shown3C - (shown3C - hidden3C) * panel->time / panel->duration;
            panel->unk3E = shown3E - (shown3E - hidden3E) * panel->time / panel->duration;
        } else {
            panel->state = 2;
            panel->time = 0;
            panel->duration = 0;
            panel->x = shownX;
            panel->y = shownY;
            panel->unk20 = shown20;
            panel->unk22 = shown22;
            panel->unk3C = shown3C;
            panel->unk3E = shown3E;
        }
        break;
    case 3:
        if ((panel->time -= GFX.funcs.getFrameTime()) > 0) {
            panel->x = hiddenX - (hiddenX - shownX) * panel->time / panel->duration;
            panel->y = hiddenY - (hiddenY - shownY) * panel->time / panel->duration;
            panel->unk20 = hidden20 - (hidden20 - shown20) * panel->time / panel->duration;
            panel->unk22 = hidden22 - (hidden22 - shown22) * panel->time / panel->duration;
            panel->unk3C = hidden3C - (hidden3C - shown3C) * panel->time / panel->duration;
            panel->unk3E = hidden3E - (hidden3E - shown3E) * panel->time / panel->duration;
        } else {
            panel->state = 0;
            panel->unk6 = 1;
            panel->time = 0;
            panel->duration = 0;
            panel->x = hiddenX;
            panel->y = hiddenY;
            panel->unk20 = hidden20;
            panel->unk22 = hidden22;
            panel->unk3C = hidden3C;
            panel->unk3E = hidden3C; /* not hidden3E */
        }
        break;
    case 4:
        panel->unk20 = hidden20;
        panel->unk22 = hidden22;
        panel->unk3C = hidden3C;
        panel->unk3E = hidden3C;
        if ((panel->time -= GFX.funcs.getFrameTime()) > 0) {
            panel->x = shownX - (shownX - hiddenX) * panel->time / panel->duration;
            panel->y = shownY - (shownY - hiddenY) * panel->time / panel->duration;
        } else {
            panel->state = 2;
            panel->time = 0;
            panel->duration = 0;
            panel->x = shownX;
            panel->y = shownY;
        }
        break;
    case 5:
        panel->unk20 = hidden20;
        panel->unk22 = hidden22;
        panel->unk3C = hidden3C;
        panel->unk3E = hidden3C;
        if ((panel->time -= GFX.funcs.getFrameTime()) > 0) {
            panel->x = hiddenX - (hiddenX - shownX) * panel->time / panel->duration;
            panel->y = hiddenY - (hiddenY - shownY) * panel->time / panel->duration;
        } else {
            panel->state = 0;
            panel->unk6 = 1;
            panel->time = 0;
            panel->duration = 0;
            panel->x = hiddenX;
            panel->y = hiddenY;
        }
        break;
    case 0:
    case 2:
        break;
    }
}

/* Draws a side's panel icon at the panel's open or close scale, and once the
   panel is open (state 2) its label; the European version takes both
   positions from D_800A5AA8, by SHIFT_PAL_SCREEN */
void func_80098930(CardScreen *screen, CardScreenItems *items, s32 side, CardPanelScale *scale) {
    SpriteDrawer drawer;
    s32 iconX;
    s32 iconY;
    s32 textX;
    s32 textY;

#if VERSION_US
    if (side == 0) {
        iconX = 0x7C;
        iconY = 0x33;
        textX = 0x8A;
        textY = 0x34;
    } else {
        iconX = 0x7C;
        iconY = 0x23;
        textX = 0x8A;
        textY = 0x24;
    }
#elif VERSION_EU
    if (side == 0) {
        iconX = D_800A5AA8[SHIFT_PAL_SCREEN][0][0].x;
        iconY = D_800A5AA8[SHIFT_PAL_SCREEN][0][0].y;
        textX = D_800A5AA8[SHIFT_PAL_SCREEN][1][0].x;
        textY = D_800A5AA8[SHIFT_PAL_SCREEN][1][0].y;
    } else {
        iconX = D_800A5AA8[SHIFT_PAL_SCREEN][0][1].x;
        iconY = D_800A5AA8[SHIFT_PAL_SCREEN][0][1].y;
        textX = D_800A5AA8[SHIFT_PAL_SCREEN][1][1].x;
        textY = D_800A5AA8[SHIFT_PAL_SCREEN][1][1].y;
    }
#endif
    if (scale->state != 0) {
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x280, 0);
        drawer.setPivot(screen->panels[side].x + iconX, screen->panels[side].y + iconY);
        drawer.setScale(scale->value, 0x1000, 0x1000);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), side == 0 ? 0x44 : 0x43,
                    screen->panels[side].x + iconX, screen->panels[side].y + iconY);
    }
    if (scale->state == 2) {
        items->panelTexts[side]->setPos(items->panelTexts[side], screen->panels[side].x + textX,
                                        screen->panels[side].y + textY);
        items->panelTexts[side]->setString(items->panelTexts[side], FILE_CACHE.load(TEXT_FILE(0x10)), 0x3F);
    } else {
        items->panelTexts[side]->setVisible(items->panelTexts[side], 0);
    }
}

void func_80098B38(CardScreen *screen, CardScreenItems *items, s32 side, CardPanelScale *scale) {
    switch (scale->state) {
    case 1:
        scale->value = 0x1000 - (scale->time << 12) / scale->duration;
        scale->time -= GFX.funcs.getFrameTime();
        if (scale->time <= 0) {
            scale->state = 2;
        }
        break;
    case 3:
        scale->value = (scale->time << 12) / scale->duration;
        scale->time -= GFX.funcs.getFrameTime();
        if (scale->time <= 0) {
            scale->state = 0;
        }
        break;
    case 0:
        break;
    case 2:
        break;
    }
    func_80098930(screen, items, side, scale);
}

void func_80098C6C(CardScreenCE8 *window) {
    window->unkE -= GFX.funcs.getFrameTime();
    if (window->unkE != 0) {
        window->x = window->unk8 - (window->unk8 - window->startX) * window->unkE / window->unkF;
        window->y = window->unkA - (window->unkA - window->startY) * window->unkE / window->unkF;
    } else {
        window->state = 1;
        window->unkF = 0;
        window->unkE = 0;
        window->x = window->unk8;
        window->y = window->unkA;
    }
}

void func_80098D3C(CardScreenCE8 *window) {
    SpriteDrawer drawer;
    s32 row;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    switch (++window->unkC >> 2) {
    default:
        window->unkC = 0;
    case 0:
        row = 0;
        break;
    case 1:
        row = 3;
        break;
    case 2:
        row = 1;
        break;
    }
    drawer.setClutRow(row);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 8, window->x, window->y);
}

void func_80098E28(CardScreen *screen, CardScreenItems *items) {
    u32 i;
    s32 two;

    i = 0;
    two = 2;
    for (; i < 12; i++) {
        if (screen->unkCE8[i].state != 0) {
            if (screen->unkCE8[i].state == two) {
                func_80098C6C(&screen->unkCE8[i]);
            }
            func_80098D3C(&screen->unkCE8[i]);
        }
    }
}

void func_80098EB4(CardScreen *screen, CardScreenItems *items) {
    func_80098B38(screen, items, 0, &screen->panels[0].scale);
    func_80098B38(screen, items, 1, &screen->panels[1].scale);
    CARDGAME_slidePanel(&screen->panels[0], items, 0);
    CARDGAME_slidePanel(&screen->panels[1], items, 1);
    CARDGAME_drawPanel(&screen->panels[0], items, 0);
    CARDGAME_drawPanel(&screen->panels[1], items, 1);
}

/* Moves and scales a sprite towards its targets; at the end it plays a sound (unless in state 3) and goes to state 1 */
void CARDGAME_moveSprite(CardScreen *screen, CardSprite *sprite) {
    sprite->time -= GFX.funcs.getFrameTime();
    if (sprite->time > 0) {
        if (sprite->x != sprite->targetX || sprite->y != sprite->targetY) {
            sprite->x = sprite->targetX - (sprite->targetX - sprite->startX) * sprite->time / sprite->duration;
            sprite->y = sprite->targetY - (sprite->targetY - sprite->startY) * sprite->time / sprite->duration;
        }
        /* both scales, read as one word */
        if (*(s32 *)&sprite->scaleX != *(s32 *)&sprite->targetScaleX) {
            sprite->scaleX = sprite->targetScaleX - (sprite->targetScaleX - sprite->startScaleX) * sprite->time / sprite->duration;
            sprite->scaleY = sprite->targetScaleY - (sprite->targetScaleY - sprite->startScaleY) * sprite->time / sprite->duration;
        }
    } else {
        if (sprite->state != 3) {
            SOUND.playSound(0x800460BD);
        }
        sprite->state = 1;
        sprite->time = 0;
        sprite->duration = 0;
        sprite->x = sprite->targetX;
        sprite->y = sprite->targetY;
        sprite->scaleX = sprite->targetScaleX;
        sprite->scaleY = sprite->targetScaleY;
        if (sprite->unk48 == 0) {
            sprite->moving = 0;
        }
    }
}

/* Flies a sprite from start to target along an arc while scaling it; at the end it swaps start and target, goes to state 2 with 2.5 times the time, and returns 1 */
s32 CARDGAME_flySprite(CardScreen *screen, CardSprite *sprite) {
    s32 done = 0;
    s32 dy;
    s32 offset;
    s32 startX;
    s32 startY;
    s32 scaledDy;
    s16 scaleX;
    s16 scaleY;

    if (sprite->unk30 > 0) {
        sprite->unk30 -= GFX.funcs.getFrameTime();
        sprite->scaleX = 0x1C00 - sprite->unk30 * 0xC0;
        sprite->scaleY = 0x1C00 - sprite->unk30 * 0xC0;
        if (sprite->unk30 <= 0) {
            sprite->unk48 |= 5;
            SOUND.playSound(0x8004603C);
            sprite->targetScaleX = 0x1200;
            sprite->targetScaleY = 0x1200;
            sprite->startScaleX = sprite->scaleX = 0x1C00;
            sprite->startScaleY = sprite->scaleY = 0x1C00;
            sprite->unk30 = 0;
        }
        return 0;
    }
    sprite->time -= GFX.funcs.getFrameTime();
    if (sprite->time > 0) {
        dy = sprite->targetY - sprite->startY;
        scaledDy = dy * sprite->time;
        sprite->x = sprite->targetX - (sprite->targetX - sprite->startX) * sprite->time / sprite->duration;
        sprite->y = sprite->targetY - scaledDy / sprite->duration;
        offset = rsin((sprite->time << 12) / (sprite->duration * 2)) * 0x1C00;
        sprite->y += (dy > 0 ? -offset : offset) / 0x1000;
        sprite->scaleX = sprite->targetScaleX - (sprite->targetScaleX - sprite->startScaleX) * sprite->time / sprite->duration;
        sprite->scaleY = sprite->targetScaleY - (sprite->targetScaleY - sprite->startScaleY) * sprite->time / sprite->duration;
    } else {
        startX = sprite->startX;
        startY = sprite->startY;
        sprite->x = sprite->startX = sprite->targetX;
        sprite->y = sprite->startY = sprite->targetY;
        sprite->targetX = startX;
        sprite->targetY = startY;
        scaleX = sprite->targetScaleX;
        scaleY = sprite->targetScaleY;
        sprite->state = 2;
        sprite->targetScaleX = 0x1000;
        sprite->targetScaleY = 0x1000;
        sprite->scaleX = scaleX;
        sprite->scaleY = scaleY;
        sprite->unk48 &= ~5;
        sprite->time = sprite->duration = sprite->duration * 2 + sprite->duration / 2;
        sprite->startScaleX = sprite->scaleX;
        sprite->startScaleY = sprite->scaleY;
        done = 1;
    }
    return done;
}

s32 func_800993A8(CardScreen *screen, CardSprite *sprite) {
    s32 done = 0;

    sprite->x = sprite->startX + D_800A498C[sprite->time & 7];
    sprite->scaleY = rsin((sprite->time << 12) / 24) / 16 + 0x1000;
    sprite->time += GFX.funcs.getFrameTime();
    if (sprite->time >= 12) {
        sprite->state = 1;
        sprite->moving = 0;
        sprite->unk47 = 0;
        sprite->scaleY = 0x1000;
        sprite->x = sprite->startX;
        done = 1;
    }
    return done;
}

/* Ends a sprite's move and puts it in STATE */
static inline void resetSprite(CardSprite *sprite, s32 state) {
    sprite->state = state;
    sprite->duration = 0;
    sprite->time = 0;
    sprite->moving = 0;
    sprite->unk47 = 0;
}

s32 func_80099494(CardScreen *screen, CardSprite *sprite) {
    s32 done = 0;

    sprite->time += GFX.funcs.getFrameTime();
    if (sprite->time >= 10) {
        resetSprite(sprite, 11);
        done = 1;
    }
    return done;
}

s32 func_80099504(CardScreen *screen, CardSprite *sprite, s32 duration) {
    s32 done = 0;

    sprite->time += GFX.funcs.getFrameTime();
    if (sprite->time >= duration) {
        resetSprite(sprite, 1);
        done = 1;
    }
    return done;
}

s32 func_80099580(CardScreen *screen, CardSprite *sprite) {
    s32 done;

    sprite->x = sprite->startX + D_800A4994[sprite->time & 7];
    sprite->y = sprite->startY + D_800A4994[RANDOM.next() & 7];
    done = 0;
    sprite->scaleY = 0x1000 - rsin((sprite->time << 12) / 24) / 8;
    sprite->time += GFX.funcs.getFrameTime();
    if (sprite->time >= 12) {
        sprite->state = 1;
        sprite->moving = 0;
        sprite->scaleY = 0x1000;
        sprite->unk47 = 0;
        sprite->x = sprite->startX;
        sprite->y = sprite->startY;
        done = 1;
    }
    return done;
}

/* The end of a sprite's flip (func_800996B0) */
static inline void endSpriteFlip(CardSprite *sprite, s32 state) {
    sprite->state = state;
    sprite->moving = 0;
    sprite->scaleX = 0x1000;
}

s32 func_800996B0(CardScreen *screen, CardSprite *sprite) {
    s32 done = 0;

    sprite->scaleX = 0x1000 - rsin((sprite->time << 12) / 24);
    sprite->time += GFX.funcs.getFrameTime();
    if (sprite->duration == 0 && sprite->time >= 7) {
        sprite->duration = 1;
        sprite->visible ^= 3;
    }
    if (sprite->time >= 12) {
        endSpriteFlip(sprite, 1);
        done = 1;
    }
    return done;
}

/* Draws a card's picture: a one-part sprite sheet (D_800A499C) made on the fly,
   the 32x32 cell `index` of an 8-row grid with the card's own CLUT row */
void func_80099780(CardSprite *sprite) {
    SpriteDrawer drawer;
    s16 *frame;
    SpritePart *part;
    s32 u;
    s32 v;
    s32 *sheet;

    u = sprite->index / 8 * 32;
    v = sprite->index % 8 * 32;
    sheet = D_800A499C;
    frame = (s16 *)((u8 *)sheet + sheet[2]);
    frame[0] = 1;
    frame[2] = -1;
    frame[1] = sprite->index;
    frame[3] = 0;
    frame[4] = 4;
    frame[5] = 2;
    part = (SpritePart *)((u8 *)sheet + sheet[0]);
    part->u = u;
    part->v = v;
    part->w = 32;
    part->h = 32;
    part->clutX = 0;
    part->clutY = 0x100;
    part->mode = 1;
    initSpriteDrawer(&drawer);
    if (*(s32 *)&sprite->scaleX != 0x10001000) {
        drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
        drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
    }
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x140, 0x100);
    drawer.setAltClut(0x300, 0x100);
    drawer.draw(sheet, 0, sprite->x >> 8, sprite->y >> 8);
}

/* Draws a sprite's effect animation (unk47 1-4, frames 0x28-0x4C of the fourth TIM) and ends it when its time runs out */
void func_800998EC(CardScreen *screen, CardSprite *sprite) {
    SpriteDrawer drawer;

    if (sprite->visible != 0 && sprite->unk47 != 0) {
        initSpriteDrawer(&drawer);
        /* both scales at 0x1000, read as one word */
        if (*(s32 *)&sprite->scaleX != 0x10001000) {
            drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
            drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
        }
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x340, 0);
        switch (sprite->unk47) {
        case 1:
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), D_800A49C8[(screen->time >> 2) & 3] + 0x28,
                        sprite->x >> 8, sprite->y >> 8);
            break;
        case 2:
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), D_800A49CC[(sprite->unk34 >> 2) % 4] + 0x2C,
                        sprite->x >> 8, sprite->y >> 8);
            if (sprite->unk34 >= 8) {
                sprite->unk47 = 0;
                sprite->unk34 = 0;
            }
            sprite->unk34 += GFX.funcs.getFrameTime();
            break;
        case 3:
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), (sprite->unk34 >> 1) % 9 + 0x3C,
                        sprite->x >> 8, sprite->y >> 8);
            if (sprite->unk34++ >= 36) {
                sprite->unk47 = 0;
                sprite->unk34 = 0;
            }
            sprite->unk34 += GFX.funcs.getFrameTime();
            break;
        case 4:
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), (sprite->unk34 >> 1) % 7 + 0x46,
                        sprite->x >> 8, sprite->y >> 8);
            if (sprite->unk34 >= 28) {
                sprite->unk47 = 0;
                sprite->unk34 = 0;
            }
            sprite->unk34 += GFX.funcs.getFrameTime();
            break;
        }
    }
}

/* Draws the highlights over a sprite (unk48 bits 0-2), with a cycling palette */
void func_80099C00(CardScreen *screen, CardSprite *sprite) {
    SpriteDrawer drawer;

    if (sprite->visible != 0) {
        if (sprite->unk48 & 6) {
            initSpriteDrawer(&drawer);
            if (sprite->unk48 & 4) {
                drawer.setClutRow(D_800A49D0[(screen->time >> 2) % 6] + 5);
            } else {
                drawer.setClutRow(4);
            }
            /* both scales at 0x1000, read as one word */
            if (*(s32 *)&sprite->scaleX != 0x10001000) {
                drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
                drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
            }
            drawer.setLayerId(0x100, 1);
            drawer.setTexture(0x340, 0);
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 8, sprite->x >> 8, sprite->y >> 8);
        }
        if (sprite->unk48 & 1) {
            initSpriteDrawer(&drawer);
            drawer.setClutRow(D_800A49D0[(screen->time >> 2) % 6]);
            /* both scales at 0x1000, read as one word */
            if (*(s32 *)&sprite->scaleX != 0x10001000) {
                drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
                drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
            }
            drawer.setLayerId(0x100, 1);
            drawer.setTexture(0x340, 0);
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 8, sprite->x >> 8, sprite->y >> 8);
        }
    }
}

void func_80099E7C(CardScreen *screen, CardSprite *sprite) {
    SpriteDrawer drawer;

    if (sprite->visible != 0 && sprite->unk46 != 0) {
        initSpriteDrawer(&drawer);
        /* both scales at 0x1000, read as one word */
        if (*(s32 *)&sprite->scaleX != 0x10001000) {
            drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
            drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
        }
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x280, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), sprite->unk46 + 0x33, (sprite->x >> 8) + 3, (sprite->y >> 8) + 2);
    }
}

/* Draws a card's marks that are set (unk3E[0..2]: sprites 0x37 to 0x39), in a row 8 pixels apart */
void CARDGAME_drawSpriteMarks(CardScreen *screen, CardSprite *sprite) {
    SpriteDrawer drawer;
    s32 i;
    s32 n;

    if (sprite->visible != 0) {
        for (i = 0, n = 0; i < 3; i++) {
            if (sprite->unk3E[i] != 0) {
                initSpriteDrawer(&drawer);
                /* both scales at 0x1000, read as one word */
                if (*(s32 *)&sprite->scaleX != 0x10001000) {
                    drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
                    drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
                }
                drawer.setLayerId(0x100, 1);
                drawer.setTexture(0x280, 0);
                drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), i + 0x37, (sprite->x >> 8) + 3 + n * 8, (sprite->y >> 8) + 0x15);
                n++;
            }
        }
    }
}

/* Draws a card's two numbers (unk43 and unk44) and the sprite between them */
static inline void drawCardNumbers(CardSprite *sprite) {
    CardNumber number;
    SpriteDrawer drawer;

    number.depth = 1;
    number.digits = 2;
    number.leadingZeros = 0;
    number.x = (sprite->x >> 8) + 4;
    number.y = (sprite->y >> 8) + 0x21;
    number.value = sprite->unk43;
    number.pivotX = (sprite->x >> 8) + 0x14;
    number.pivotY = (sprite->y >> 8) + 0x17;
    number.scaleX = sprite->scaleX;
    number.scaleY = sprite->scaleY;
    CARDGAME_drawNumber(&number, 1);
    number.x = (sprite->x >> 8) + 0x17;
    number.y = (sprite->y >> 8) + 0x21;
    number.value = sprite->unk44;
    number.pivotX = (sprite->x >> 8) + 0x14;
    number.pivotY = (sprite->y >> 8) + 0x17;
    number.scaleX = sprite->scaleX;
    number.scaleY = sprite->scaleY;
    CARDGAME_drawNumber(&number, 1);
    initSpriteDrawer(&drawer);
    /* both scales at 0x1000, read as one word */
    if (*(s32 *)&sprite->scaleX != 0x10001000) {
        drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
        drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
    }
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0x1F, (sprite->x >> 8) + 0x12, (sprite->y >> 8) + 0x21);
}

/* Draws the mark (sprite 0x1E) of a card that is not of kind 16 */
static inline void drawCardMark(CardSprite *sprite) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    /* both scales at 0x1000, read as one word */
    if (*(s32 *)&sprite->scaleX != 0x10001000) {
        drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
        drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
    }
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 0x1E, (sprite->x >> 8) + 4, (sprite->y >> 8) + 0x21);
}

/* Draws a card sprite: its frame (visible 1, with the numbers or the mark and the image) or its back (visible 2 or 3) */
void CARDGAME_drawSpriteCard(CardScreen *screen, CardSprite *sprite) {
    /* the match depends on the early return together with the empty case 0 */
    if (sprite->visible == 0) {
        return;
    }
    switch (sprite->visible) {
    case 0:
        break;
    case 1:
        if (sprite->isKind16 != 0) {
            drawCardNumbers(sprite);
        } else {
            drawCardMark(sprite);
        }
        {
            SpriteDrawer drawer;

            initSpriteDrawer(&drawer);
            /* both scales at 0x1000, read as one word */
            if (*(s32 *)&sprite->scaleX != 0x10001000) {
                drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
                drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
            }
            drawer.setLayerId(0x100, 1);
            drawer.setTexture(0x280, 0);
            drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), sprite->unk49 == 1 ? sprite->color + 0x3C : sprite->color,
                        sprite->x >> 8, sprite->y >> 8);
        }
        func_80099780(sprite);
        break;
    case 2: {
        SpriteDrawer drawer;

        initSpriteDrawer(&drawer);
        /* both scales at 0x1000, read as one word */
        if (*(s32 *)&sprite->scaleX != 0x10001000) {
            drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
            drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
        }
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x280, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0x10, sprite->x >> 8, sprite->y >> 8);
        break;
    }
    case 3: {
        SpriteDrawer drawer;

        initSpriteDrawer(&drawer);
        /* both scales at 0x1000, read as one word */
        if (*(s32 *)&sprite->scaleX != 0x10001000) {
            drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
            drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
        }
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x280, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 2), 0xC, sprite->x >> 8, sprite->y >> 8);
        break;
    }
    }
}

void func_8009A5CC(CardScreen *screen, CardSprite *sprite) {
    SpriteDrawer drawer;

    if (sprite->visible != 0 && sprite->unk49 != 0) {
        initSpriteDrawer(&drawer);
        /* both scales at 0x1000, read as one word */
        if (*(s32 *)&sprite->scaleX != 0x10001000) {
            drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
            drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
        }
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x340, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 10, sprite->x >> 8, sprite->y >> 8);
    }
}

void func_8009A6C0(CardScreen *screen, CardSprite *sprite) {
    SpriteDrawer drawer;

    if (sprite->visible != 0 && sprite->state == 11) {
        initSpriteDrawer(&drawer);
        drawer.setClutRow((sprite->duration / 2) % 5);
        drawer.setPivot((sprite->x >> 8) + 0x14, (sprite->y >> 8) + 0x17);
        drawer.setScale(sprite->scaleX, sprite->scaleY, 0x1000);
        drawer.setLayerId(0x100, 1);
        drawer.setTexture(0x340, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 9, sprite->x >> 8, sprite->y >> 8);
    }
}

/* Runs a sprite's animation for its state; sets bit 0 of unk54 while one runs */
void func_8009A7E4(CardScreen *screen, CardScreenItems *items, CardSprite *sprite) {
    switch (sprite->state) {
    case 0:
        sprite->visible = 0;
        break;
    case 2:
    case 3:
        screen->unk54 |= 1;
        CARDGAME_moveSprite(screen, sprite);
        break;
    case 4:
        screen->unk54 |= 1;
        func_800996B0(screen, sprite);
        break;
    case 5:
        screen->unk54 |= 1;
        if (CARDGAME_flySprite(screen, sprite) != 0) {
            screen->unk54 |= 2;
        }
        break;
    case 6:
        screen->unk54 |= 1;
        func_80099580(screen, sprite);
        break;
    case 7:
        screen->unk54 |= 1;
        func_800993A8(screen, sprite);
        break;
    case 8:
        screen->unk54 |= 1;
        func_80099494(screen, sprite);
        break;
    case 11:
        screen->unk54 |= 1;
        sprite->duration += GFX.funcs.getFrameTime();
        if (sprite->duration >= 11) {
            sprite->state = 1;
        }
        break;
    case 9:
        func_80099504(screen, sprite, 36);
        screen->unk54 |= 1;
        break;
    case 10:
        func_80099504(screen, sprite, 28);
        screen->unk54 |= 1;
        break;
    case 1:
        break;
    }
}

void func_8009A990(CardScreen *screen, CardSprite *sprite) {
    if (sprite->scaleX != 0 && sprite->scaleY != 0) {
        func_80099C00(screen, sprite);
        CARDGAME_drawSpriteMarks(screen, sprite);
        func_80099E7C(screen, sprite);
        func_800998EC(screen, sprite);
        func_8009A5CC(screen, sprite);
        CARDGAME_drawSpriteCard(screen, sprite);
    }
}

void func_8009AA1C(CardScreen *screen, CardScreenItems *items) {
    s32 i;
    s32 pass;

    for (i = 39; i >= 0; i--) {
        func_8009A7E4(screen, items, &screen->sprites[i]);
        func_8009A6C0(screen, &screen->sprites[i]);
    }
    for (pass = 0; pass < 2; pass++) {
        for (i = 39; i >= 0; i--) {
            if ((pass == 0 && screen->sprites[i].moving != 0) || (pass != 0 && screen->sprites[i].moving == 0)) {
                func_8009A990(screen, &screen->sprites[i]);
            }
        }
    }
}

void CARDGAME_updateScreen(CardScreen *screen, CardScreenItems *items) {
    switch (screen->state) {
    case 0:
    default:
        screen->nextState(screen);
        items->cursor = createCursor(0x100, 0, 0, 0);
        items->cursor->setVisible(items->cursor, 0);
        items->texts[0] = createTextWindow(0x100, 1, 0, 0);
        items->texts[1] = createTextWindow(0x100, 1, 0, 0);
        items->texts[2] = createTextWindow(0x100, 1, 0, 0);
        items->panelTexts[0] = createTextWindow(0x100, 1, 0, 0);
        items->panelTexts[1] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[0] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[1] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[1]->setLines(items->moreTexts[1], 3);
        items->moreTexts[2] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[3] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[4] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[5] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[5]->setLines(items->moreTexts[5], 3);
        items->moreTexts[6] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[6]->setLines(items->moreTexts[6], 5);
        items->moreTexts[7] = createTextWindow(0x100, 1, 0, 0);
        items->moreTexts[7]->setLines(items->moreTexts[7], 2);
        break;
    case 1:
        screen->time += GFX.funcs.getFrameTime();
        screen->unk54 = 0;
        func_80098E28(screen, items);
        func_80097548(screen, items);
        CARDGAME_updateMessageWindow(screen, items);
        func_80096A9C(screen, items);
        func_8009AA1C(screen, items);
        func_80096018(screen, items);
        func_80095B44(screen);
        func_80098EB4(screen, items);
        break;
    case 3:
        break;
    }
}

void func_8009AD94(CardScreen *screen, s32 index, s16 value) {
    screen->unkDC0[index].from = 0x1000;
    screen->unkDC0[index].state = 1;
    screen->unkDC0[index].to = 0;
    screen->unkDC0[index].value = value;
    screen->unkDC0[index].duration = 10;
    screen->unkDC0[index].time = 10;
}

void func_8009ADCC(CardScreen *screen, s32 index) {
    screen->unkDC0[index].from = 0x1000;
    screen->unkDC0[index].to = 0x1000;
    screen->unkDC0[index].state = 3;
    screen->unkDC0[index].duration = 5;
    screen->unkDC0[index].time = 5;
}

void func_8009AE00(CardScreen *screen, s32 index, s16 arg2, s32 arg3, s32 x, s32 y) {
    SOUND.playSound(0x40019);
    screen->unkE0C[index].x = x;
    screen->unkE0C[index].y = y;
    screen->unkE0C[index].from = 0;
    screen->unkE0C[index].to = 0x1000;
    screen->unkE0C[index].state = 1;
    screen->unkE0C[index].unkC = arg2;
    screen->unkE0C[index].unk10 = arg3;
    screen->unkE0C[index].duration = 12;
    screen->unkE0C[index].time = 12;
}

void func_8009AEB0(CardScreen *screen, s32 index) {
    SOUND.playSound(0x4001A);
    screen->unkE0C[index].from = 0x1000;
    screen->unkE0C[index].to = 0x1000;
    screen->unkE0C[index].state = 3;
    screen->unkE0C[index].duration = 6;
    screen->unkE0C[index].time = 6;
}

s32 func_8009AF20(CardScreen *screen, s32 index, s16 x, s16 y) {
    screen->unkCE8[index].state = 1;
    screen->unkCE8[index].x = x;
    screen->unkCE8[index].y = y;
    screen->unkCE8[index].unkA = 0;
    screen->unkCE8[index].unk8 = 0;
    screen->unkCE8[index].startY = 0;
    screen->unkCE8[index].startX = 0;
    screen->unkCE8[index].unkF = 0;
    screen->unkCE8[index].unkE = 0;
    screen->unkCE8[index].unkC = 0;
    return 0;
}

s32 func_8009AF64(CardScreen *screen, s32 index, u8 arg2, s16 arg3, s32 arg4) {
    screen->unkCE8[index].state = 2;
    screen->unkCE8[index].unk8 = arg3;
    screen->unkCE8[index].unkF = arg2;
    screen->unkCE8[index].unkE = arg2;
    screen->unkCE8[index].unkA = arg4;
    screen->unkCE8[index].startX = screen->unkCE8[index].x;
    screen->unkCE8[index].startY = screen->unkCE8[index].y;
    return 0;
}

void func_8009AFA8(CardScreen *screen, s32 arg1, s32 arg2, s16 arg3, s32 arg4) {
    SOUND.playSound(0x40019);
    screen->unkDF2 = 12;
    screen->unkDF0 = 12;
    screen->unkDF4 = arg3;
    screen->unkDE8 = arg1;
    screen->unkDFB = arg2;
    screen->unkDE4 = arg4;
    screen->unkDFA = 1;
}

void func_8009B030(CardScreen *screen) {
    SOUND.playSound(0x4001A);
    screen->unkDF2 = 6;
    screen->unkDF0 = 6;
    screen->unkDFA = 5;
}

void func_8009B078(CardScreen *screen) {
    SOUND.playSound(0x8004503C);
    screen->unkDF2 = 10;
    screen->unkDF0 = 10;
    screen->unkDFA = 4;
}

void func_8009B0C0(CardScreen *screen, s32 value) {
    screen->unkDF4 = value;
}

void func_8009B0C8(CardScreen *screen, s16 value) {
    SOUND.playSound(0x40019);
    screen->unkE02 = 12;
    screen->unkE00 = 12;
    screen->unkE04 = value;
    screen->unkE0A = 1;
}

void func_8009B120(CardScreen *screen) {
    SOUND.playSound(0x4001A);
    screen->unkE02 = 6;
    screen->unkE00 = 6;
    screen->unkE0A = 5;
}

void func_8009B168(CardScreen *screen) {
    SOUND.playSound(0x8004503C);
    screen->unkE02 = 10;
    screen->unkE00 = 10;
    screen->unkE0A = 4;
}

void func_8009B1B0(CardScreen *screen, s16 value) {
    screen->unkE04 = value;
}

void func_8009B1B8(CardScreen *screen) {
    screen->panels[0].state = 0;
    screen->panels[0].duration = 0;
    screen->panels[0].time = 0;
    screen->panels[0].x = 0;
    screen->panels[0].y = 0xF1;
    screen->panels[0].unk20 = 0x147;
    screen->panels[0].unk22 = 0x8F;
    screen->panels[0].unk3C = 0x140;
    screen->panels[0].unk3E = 0xBD;
    screen->panels[1].state = 0;
    screen->panels[1].duration = 0;
    screen->panels[1].time = 0;
    screen->panels[1].x = 0;
    screen->panels[1].y = -100;
    screen->panels[1].unk20 = 0x147;
    screen->panels[1].unk22 = 0x50;
    screen->panels[1].unk3C = 0x140;
    screen->panels[1].unk3E = 0x26;
}

void func_8009B224(CardScreen *screen) {
    screen->panels[0].state = 1;
    screen->panels[0].unk6 = 2;
    screen->panels[0].duration = 20;
    screen->panels[0].time = 20;
    screen->panels[0].x = 0;
    screen->panels[0].y = 0xF1;
    screen->panels[0].unk20 = 0x147;
    screen->panels[0].unk22 = 0x8F;
    screen->panels[0].unk3C = 0x140;
    screen->panels[0].unk3E = 0xBD;
    screen->panels[1].state = 1;
    screen->panels[1].duration = 20;
    screen->panels[1].time = 20;
    screen->panels[1].x = 0;
    screen->panels[1].y = -100;
    screen->panels[1].unk20 = 0xF9;
    screen->panels[1].unk22 = 0x50;
    screen->panels[1].unk3C = 0x140;
    screen->panels[1].unk3E = 0x26;
}

void func_8009B2A4(CardScreen *screen) {
    screen->panels[0].state = 3;
    screen->panels[0].duration = 10;
    screen->panels[0].time = 10;
    screen->panels[0].x = 0;
    screen->panels[0].y = 0x8D;
    screen->panels[0].unk20 = 0x120;
    screen->panels[0].unk22 = 0x8F;
    screen->panels[0].unk3C = 0x113;
    screen->panels[0].unk3E = 0xBD;
    screen->panels[1].state = 3;
    screen->panels[1].duration = 10;
    screen->panels[1].time = 10;
    screen->panels[1].x = 0;
    screen->panels[1].y = 0;
    screen->panels[1].unk20 = 0x120;
    screen->panels[1].unk22 = 0x50;
    screen->panels[1].unk3C = 0x113;
    screen->panels[1].unk3E = 0x26;
}

void func_8009B314(CardScreen *screen, s32 side) {
    screen->panels[side].state = 4;
    screen->panels[side ^ 1].state = 0;
    screen->panels[side].unk6 = 2;
    screen->panels[side].duration = 10;
    screen->panels[side].time = 10;
    if (side == 0) {
        screen->panels[0].x = 0;
        screen->panels[0].y = 0xF1;
    } else {
        screen->panels[side].x = 0;
        screen->panels[side].y = -100;
    }
}

void func_8009B38C(CardScreen *screen, s32 side) {
    screen->panels[side].state = 5;
    screen->panels[side ^ 1].state = 0;
    screen->panels[side].duration = 5;
    screen->panels[side].time = 5;
    if (side == 0) {
        screen->panels[0].x = 0;
        screen->panels[0].y = 0x8D;
    } else {
        screen->panels[side].x = 0;
        screen->panels[side].y = 0;
    }
}

void func_8009B3F8(CardScreen *screen, s32 side) {
    screen->panels[side].scale.state = 1;
    screen->panels[side].scale.duration = 12;
    screen->panels[side].scale.time = 12;
    screen->panels[side].scale.value = 0;
}

void func_8009B42C(CardScreen *screen, s32 side) {
    screen->panels[side].scale.state = 3;
    screen->panels[side].scale.duration = 6;
    screen->panels[side].scale.time = 6;
    screen->panels[side].scale.value = 0x1000;
}

s32 CARDGAME_addSprite(CardScreen *screen, s32 index, s32 x, s32 y) {
    HEAP.zero(&screen->sprites[index], sizeof(CardSprite));
    screen->sprites[index].visible = 1;
    screen->sprites[index].state = 1;
    screen->sprites[index].x = x;
    screen->sprites[index].y = y;
    screen->sprites[index].targetScaleX = 0x1000;
    screen->sprites[index].scaleX = 0x1000;
    screen->sprites[index].targetScaleY = 0x1000;
    screen->sprites[index].scaleY = 0x1000;
    screen->sprites[index].index = 0;
    screen->sprites[index].color = 0;
    screen->sprites[index].slot = index;
    screen->sprites[index].unk43 = 0;
    screen->sprites[index].unk44 = 0;
    screen->sprites[index].unk47 = 0;
    screen->sprites[index].unk49 = 0;
    screen->sprites[index].moving = 0;
    return 0;
}

s32 func_8009B52C(CardScreen *screen, s32 index) {
    SOUND.playSound(0x8004613E);
    screen->sprites[index].state = 4;
    screen->sprites[index].time = 0;
    screen->sprites[index].duration = 0;
    screen->sprites[index].scaleX = 0x1000;
    screen->sprites[index].scaleY = 0x1000;
    screen->sprites[index].moving = 0;
    return 0;
}

s32 func_8009B5A8(CardScreen *screen, s32 index) {
    SOUND.playSound(0x9C0003);
    screen->sprites[index].state = 6;
    screen->sprites[index].scaleX = 0x1000;
    screen->sprites[index].scaleY = 0x1000;
    screen->sprites[index].time = 0;
    screen->sprites[index].duration = 0;
    screen->sprites[index].unk47 = 1;
    screen->sprites[index].moving = 0;
    screen->sprites[index].startX = screen->sprites[index].x;
    screen->sprites[index].startY = screen->sprites[index].y;
    return 0;
}

s32 func_8009B63C(CardScreen *screen, s32 index) {
    SOUND.playSound(0x9C0003);
    screen->sprites[index].state = 7;
    screen->sprites[index].time = 0;
    screen->sprites[index].duration = 0;
    screen->sprites[index].unk47 = 1;
    screen->sprites[index].moving = 0;
    screen->sprites[index].startX = screen->sprites[index].x;
    screen->sprites[index].startY = screen->sprites[index].y;
    return 0;
}

s32 func_8009B6C4(CardScreen *screen, s32 index) {
    SOUND.playSound(0x40014);
    screen->sprites[index].state = 8;
    screen->sprites[index].time = 0;
    screen->sprites[index].duration = 0;
    screen->sprites[index].unk47 = 2;
    screen->sprites[index].moving = 0;
    screen->sprites[index].startX = screen->sprites[index].x;
    screen->sprites[index].startY = screen->sprites[index].y;
    return 0;
}

s32 func_8009B74C(CardScreen *screen, s32 index, s32 arg2) {
    switch (arg2) {
    case 0:
    default:
        screen->sprites[index].state = 9;
        screen->sprites[index].unk47 = 3;
        break;
    case 1:
        screen->sprites[index].unk47 = 4;
        screen->sprites[index].state = 10;
        break;
    }
    screen->sprites[index].time = 0;
    screen->sprites[index].duration = 0;
    screen->sprites[index].moving = 0;
    screen->sprites[index].startX = screen->sprites[index].x;
    screen->sprites[index].startY = screen->sprites[index].y;
    return 0;
}

s32 CARDGAME_setSpriteScaleTarget(CardScreen *screen, s32 index, s32 duration, s32 scaleX, s32 scaleY, s32 instant) {
    screen->sprites[index].targetScaleX = scaleX;
    screen->sprites[index].targetScaleY = scaleY;
    screen->sprites[index].startScaleX = screen->sprites[index].scaleX;
    screen->sprites[index].startScaleY = screen->sprites[index].scaleY;
    if (instant != 1) {
        screen->sprites[index].duration = duration;
        screen->sprites[index].time = duration;
        screen->sprites[index].state = 2;
        screen->sprites[index].moving = 1;
        screen->sprites[index].targetX = screen->sprites[index].x;
        screen->sprites[index].targetY = screen->sprites[index].y;
    }
    return 0;
}

void CARDGAME_setSpriteScale(CardScreen *screen, s32 index, s32 scaleX, s32 scaleY) {
    CARDGAME_setSpriteScaleTarget(screen, index, 0, scaleX, scaleY, 1);
}

void CARDGAME_scaleSprite(CardScreen *screen, s32 index, s32 duration, s32 scaleX, s32 scaleY) {
    CARDGAME_setSpriteScaleTarget(screen, index, duration, scaleX, scaleY, 0);
}

void CARDGAME_setSpriteMove(CardScreen *screen, s32 index, s32 duration, s32 x, s32 y) {
    screen->sprites[index].targetX = x;
    screen->sprites[index].duration = duration;
    screen->sprites[index].time = duration;
    screen->sprites[index].targetY = y;
    screen->sprites[index].startX = screen->sprites[index].x;
    screen->sprites[index].startY = screen->sprites[index].y;
}

void func_8009B8F4(CardScreen *screen, s32 index, s32 duration, s32 x, s32 y) {
    SOUND.playSound(0x8004603C);
    screen->sprites[index].state = 2;
    CARDGAME_setSpriteMove(screen, index, duration, x, y);
}

void func_8009B990(CardScreen *screen, s32 index, s32 duration, s32 x, s32 y) {
    screen->sprites[index].state = 3;
    CARDGAME_setSpriteMove(screen, index, duration, x, y);
}

s32 func_8009B9D4(CardScreen *screen, s32 index, s32 duration, s32 x, s32 y) {
    screen->sprites[index].state = 5;
    screen->sprites[index].unk30 = 16;
    screen->sprites[index].scaleX = 0x1000;
    screen->sprites[index].scaleY = 0x1000;
    screen->sprites[index].targetX = x;
    screen->sprites[index].duration = duration;
    screen->sprites[index].time = duration;
    screen->sprites[index].targetY = y;
    screen->sprites[index].startX = screen->sprites[index].x;
    screen->sprites[index].startY = screen->sprites[index].y;
    return 0;
}

void CARDGAME_setPanelValue(CardScreen *screen, s32 side, u32 which, s32 value) {
    switch (which) {
    case 0:
        screen->panels[side].unk18[0] = value;
        break;
    case 1:
        screen->panels[side].unk18[1] = value;
        break;
    case 2:
        screen->panels[side].unk18[2] = value;
        break;
    case 3:
        screen->panels[side].unk18[3] = value;
        break;
    case 4:
        screen->panels[side].unk18[4] = value;
        break;
    case 5:
        screen->panels[side].unk18[5] = value;
        break;
    case 6:
        screen->panels[side].unk18[6] = value;
        break;
    case 7:
        screen->panels[side].unk28 = value;
        break;
    case 8:
        screen->panels[side].unk10 = value;
        break;
    case 9:
        screen->panels[side].unk12 = value;
        break;
    }
}

void CARDGAME_setPanelFlags(CardScreen *screen, s32 bits) {
    if (bits & 1) {
        screen->panels[0].flags[0] = 1;
    }
    if (bits & 4) {
        screen->panels[0].flags[1] = 1;
    }
    if (bits & 0x10) {
        screen->panels[0].flags[2] = 1;
    }
    if (bits & 0x40) {
        screen->panels[0].flags[3] = 1;
    }
    if (bits & 0x100) {
        screen->panels[0].flags[4] = 1;
    }
    if (bits & 0x400) {
        screen->panels[0].flags[5] = 1;
    }
    if (bits & 0x1000) {
        screen->panels[0].flags[6] = 1;
    }
    if (bits & 0x4000) {
        screen->panels[0].flags[7] = 1;
    }
    if (bits & 0x10000) {
        screen->panels[0].flags[8] = 1;
    }
    if (bits & 0x40000) {
        screen->panels[0].flags[9] = 1;
    }
    if (bits & 2) {
        screen->panels[1].flags[0] = 1;
    }
    if (bits & 8) {
        screen->panels[1].flags[1] = 1;
    }
    if (bits & 0x20) {
        screen->panels[1].flags[2] = 1;
    }
    if (bits & 0x80) {
        screen->panels[1].flags[3] = 1;
    }
    if (bits & 0x200) {
        screen->panels[1].flags[4] = 1;
    }
    if (bits & 0x800) {
        screen->panels[1].flags[5] = 1;
    }
    if (bits & 0x2000) {
        screen->panels[1].flags[6] = 1;
    }
    if (bits & 0x8000) {
        screen->panels[1].flags[7] = 1;
    }
    if (bits & 0x20000) {
        screen->panels[1].flags[8] = 1;
    }
    if (bits & 0x80000) {
        screen->panels[1].flags[9] = 1;
    }
}

void CARDGAME_clearPanelFlags(CardScreen *screen) {
    HEAP.zero(screen->panels[0].flags, sizeof(screen->panels[0].flags));
    HEAP.zero(screen->panels[1].flags, sizeof(screen->panels[1].flags));
}

s32 CARDGAME_removeSprite(CardScreen *screen, s32 index) {
    screen->sprites[index].state = 0;
    screen->sprites[index].visible = 0;
    screen->sprites[index].index = 0;
    return 0;
}

s32 func_8009BD7C(CardScreen *screen, s32 index) {
    SOUND.playSound(0x4001C);
    screen->sprites[index].state = 11;
    screen->sprites[index].duration = 0;
    screen->sprites[index].time = 0;
    return 0;
}

void CARDGAME_dealSprites(CardScreen *screen, s16 duration, s16 count, s32 x, s32 y) {
    s32 i;
    s32 sx;

    for (i = 0; i < count; i++) {
        sx = x + CARDGAME_getHandOffset(count, i);
        if (duration == 0) {
            CARDGAME_addSprite(screen, i, sx, y);
        } else {
            func_8009B8F4(screen, i, duration, sx, y);
        }
    }
}

s32 CARDGAME_getCardColor(CardScreen *screen, s32 index) {
    CardDrawer drawer;

    initCardDrawer(&drawer);
    drawer.setCard(screen->cards[index] + 1);
    return drawer.card[0];
}

void CARDGAME_setSpriteCard(CardScreen *screen, s32 sprite, s32 index) {
    CardDrawer drawer;

    initCardDrawer(&drawer);
    drawer.setCard(screen->cards[index] + 1);
    screen->sprites[sprite].index = index;
    screen->sprites[sprite].unk43 = drawer.card[1];
    screen->sprites[sprite].unk44 = drawer.card[2];
    screen->sprites[sprite].unk41 = drawer.card[5];
    screen->sprites[sprite].color = drawer.card[0] - 1;
    if (drawer.card[3] == 0x10) {
        screen->sprites[sprite].isKind16 = 1;
    } else {
        screen->sprites[sprite].isKind16 = 0;
    }
}

void CARDGAME_loadCardImage(TimLoader *loader, u8 *image, s32 slot) {
    loader->setImagePos(0x140 + slot / 8 * 16, 0x100 + slot % 8 * 32);
    loader->setClutPos(0x300, 0x100 + slot);
    loader->load(image);
}

s32 func_8009C094(s32 index) {
    return D_800A49D8[index];
}

s32 CARDGAME_loadCardImages(s16 *dst, s16 *player, s16 *opponent) {
    TimLoader loader;
    CardDrawer drawer;
    s32 i;
    s32 count = 0;

    initCardDrawer(&drawer);
    initTimLoader(&loader);
    for (i = 0; i < 40; i++) {
        count++;
        drawer.setCard(player[i] + 1);
        CARDGAME_loadCardImage(&loader, drawer.card + 12, i);
        dst[i] = player[i];
    }
    for (i = 0; i < 40; i++) {
        count++;
        drawer.setCard(opponent[i] + 1);
        CARDGAME_loadCardImage(&loader, drawer.card + 12, i + 40);
        dst[i + 40] = opponent[i];
    }
    for (i = 0; i < 9; i++) {
        count++;
        drawer.setCard(D_800A4AA0[i] + 1);
        CARDGAME_loadCardImage(&loader, drawer.card + 12, i + 80);
        dst[i + 80] = D_800A4AA0[i];
    }
    for (i = 0; i < 100; i++) {
        drawer.setCard(func_8009C094(i) + 1);
        count++;
        CARDGAME_loadCardImage(&loader, drawer.card + 12, i + 89);
        dst[i + 89] = func_8009C094(i);
    }
    return count;
}

CardScreen *CARDGAME_createScreen(s16 *cards) {
    CardScreen *screen = createTask(CARDGAME_updateScreen, sizeof(CardScreen), 14 * 4);

    screen->setPanelValue = CARDGAME_setPanelValue;
    screen->unkEA4 = func_8009AD94;
    screen->unkEA8 = func_8009ADCC;
    screen->unkEAC = func_8009AE00;
    screen->unkEB0 = func_8009AEB0;
    screen->setPanelFlags = CARDGAME_setPanelFlags;
    screen->clearPanelFlags = CARDGAME_clearPanelFlags;
    screen->unkEE4 = func_8009AFA8;
    screen->unkEE8 = func_8009B030;
    screen->unkEF0 = func_8009B0C0;
    screen->unkEEC = func_8009B078;
    screen->unkEF4 = func_8009B0C8;
    screen->unkEF8 = func_8009B120;
    screen->unkEFC = func_8009B168;
    screen->unkF00 = func_8009B1B0;
    screen->getHandOffset = CARDGAME_getHandOffset;
    screen->unkEDC = func_8009AF20;
    screen->unkEE0 = func_8009AF64;
    screen->unkF08 = func_8009B8F4;
    screen->unkF0C = func_8009B990;
    screen->unkF10 = func_8009B9D4;
    screen->unkF2C = func_8009B5A8;
    screen->unkF30 = func_8009B63C;
    screen->unkF34 = func_8009B6C4;
    screen->unkF38 = func_8009B74C;
    screen->unkF28 = func_8009B52C;
    screen->addSprite = CARDGAME_addSprite;
    screen->removeSprite = CARDGAME_removeSprite;
    screen->unkF1C = func_8009BD7C;
    screen->setSpriteScale = CARDGAME_setSpriteScale;
    screen->scaleSprite = CARDGAME_scaleSprite;
    screen->dealSprites = CARDGAME_dealSprites;
    screen->cards = cards;
    screen->unkEC4 = func_8009B2A4;
    screen->unkEC8 = func_8009B224;
    screen->unkEBC = func_8009B38C;
    screen->unkED0 = func_8009B3F8;
    screen->unkED4 = func_8009B42C;
    screen->unkEC0 = func_8009B314;
    screen->unkECC = func_8009B1B8;
    screen->setSpriteCard = CARDGAME_setSpriteCard;
    screen->getCardColor = CARDGAME_getCardColor;
    screen->loadCardImages = CARDGAME_loadCardImages;
    return screen;
}

/* Requests the files of CARDGAME_preloadFiles one after the other, and ends after the
   last */
void CARDGAME_tickPreloader(CardPreloader *task) {
    switch (task->state) {
    case 0:
    default:
        task->index = 0;
        task->setState(task, 1);
        task->ready = 0;
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            task->file = CARDGAME_preloadFiles[task->index].file;
            if (CARDGAME_preloadFiles[task->index].isText != 0) {
                task->file += TEXT_FILE(1);
            }
            FILE_CACHE.request(task->file);
            task->substate++;
        case 1:
            break;
        }
        if (FILE_CACHE.isLoading(task->file) == 0) {
            if (CARDGAME_preloadFiles[++task->index].file == -2) {
                task->index++;
                task->ready = 1;
            }
            if (CARDGAME_preloadFiles[task->index].file == -1) {
                task->setState(task, 3);
            }
            task->substate = 0;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

CardPreloader *CARDGAME_startPreloader(void) {
    return createTask(CARDGAME_tickPreloader, sizeof(CardPreloader), 0);
}

/* Loads the opponent's data (FILE_CARDGAME_OPPONENTS, entry arg - 1): its deck and its card order */
void CARDGAME_loadOpponent(CardBattle *battle, CardBattleItems *items) {
    CardOpponent *opponent;
    s32 i;

    battle->opponents = (CardOpponent *)FILE_CACHE.load(FILE_CARDGAME_OPPONENTS);
    opponent = &battle->opponents[battle->arg - 1];
    battle->unk2E9 = opponent->unkC8;
    battle->unk2EC = D_800A4AF0[opponent->unkCC];
    for (i = 0; i < 40; i++) {
        battle->unk30A[i].unk0 = i;
        battle->unk30A[i].unk1 = opponent->cards[i].unk2;
        battle->unk35C[i].unk0 = opponent->cards[i].unk3;
        battle->unk35C[i].unk1 = (opponent->cards[i].card & 0x8000) != 0;
        switch (battle->unk35C[i].unk0) {
        case 1:
            battle->unk35C[i].unk2 = i + 400;
            break;
        case 2:
            battle->unk35C[i].unk2 = i + 300;
            break;
        case 3:
            battle->unk35C[i].unk2 = i + 500;
            break;
        case 4:
            battle->unk35C[i].unk2 = i + 200;
            break;
        case 5:
            battle->unk35C[i].unk2 = i + 600;
            break;
        case 6:
            battle->unk35C[i].unk2 = i + 100;
            break;
        case 7:
            battle->unk35C[i].unk2 = i + 700;
            break;
        }
    }
    for (i = 0; i < 27; i++) {
        if (opponent->unkA0[i] == 0) {
            battle->unk400[i] = 7;
            battle->unk400[i + 1] = 8;
            battle->unk400[i + 2] = 24;
            battle->unk400[i + 3] = 31;
            battle->unk400[i + 4] = 32;
            battle->unk400[i + 5] = 0;
            battle->unk400[i + 6] = 6;
            battle->unk400[i + 7] = 12;
            battle->unk400[i + 8] = 18;
            battle->unk400[i + 9] = 27;
            battle->unk400[i + 10] = 30;
            battle->unk400[i + 11] = 33;
            battle->unk400[i + 12] = 37;
            battle->unk400[i + 13] = 38;
            battle->unk400[i + 14] = 0xFF;
            break;
        }
        battle->unk400[i] = opponent->unkA0[i] - 1;
    }
    for (i = 0; i < 40; i++) {
        battle->unk248[i] = (opponent->cards[i].card & 0xFFF) - 1;
    }
}

void func_8009C844(CardBattle *battle) {
    s32 i;
    s32 j;
    s32 swap;
    s32 tmp;
    s32 ka;
    s32 kb;
    s32 va;
    s32 vb;

    for (i = 0; i < battle->sides[1].pile.unkA - 1; i++) {
        swap = 0;
        for (j = i + 1; j < battle->sides[1].pile.unkA; j++, swap = 0) {
            ka = battle->unk35C[battle->sides[1].pile.unk64[i] - 40].unk0;
            kb = battle->unk35C[battle->sides[1].pile.unk64[j] - 40].unk0;
            va = battle->unk35C[battle->sides[1].pile.unk64[i] - 40].unk2;
            vb = battle->unk35C[battle->sides[1].pile.unk64[j] - 40].unk2;
            if (kb < ka || (ka == kb && vb < va)) {
                swap = 1;
            }
            if (swap) {
                tmp = battle->sides[1].pile.unk64[i];
                battle->sides[1].pile.unk64[i] = battle->sides[1].pile.unk64[j];
                battle->sides[1].pile.unk64[j] = tmp;
            }
        }
    }
}

void func_8009C92C(CardBattle *battle, CardBattleItems *items) {
    s32 i;

    for (i = battle->sides[1].pile.unk4; i < 40; i++) {
        if (battle->unk300 * 2 + 2 < battle->unk30A[i].unk1) {
            break;
        }
    }
    battle->unk41B = i;
    for (i = 40; i > 0; i--) {
        if (battle->unk30A[i - 1].unk1 != 7) {
            break;
        }
    }
    battle->unk41C = i;
}

/* Puts side 1's hand (unk64) back on its pile and renumbers the pile's cards */
void func_8009C9B0(CardBattle *battle, CardBattleItems *items) {
    CardPile *pile = &battle->sides[1].pile;
    s32 start = pile->unk4;
    s32 i;
    s32 j;
    s16 card;

    while (pile->unkA > 0) {
        pile->unk14[--pile->unk4] = pile->unk64[--pile->unkA];
        pile->unk8++;
    }
    if (start != pile->unk4) {
        for (i = pile->unk4; i < start; i++) {
            battle->unk30A[i].unk1 = battle->unk300 * 2 + 1;
        }
    }
    for (i = 0; i < 40; i++) {
        j = pile->unk4;
        if (battle->unk30A[j].unk1 > battle->unk300 * 2 + 2) {
            break;
        }
        card = pile->unk14[j];
        while (j < battle->unk41C - 1) {
            pile->unk14[j] = pile->unk14[j + 1];
            battle->unk30A[j].unk1 = battle->unk30A[j + 1].unk1;
            j++;
        }
        pile->unk14[battle->unk41C - 1] = card;
        battle->unk30A[battle->unk41C - 1].unk1 = 7;
    }
    for (i = 39; i >= 0; i--) {
        battle->unk30A[i].unk0 = i;
    }
}

/* Lays out the cards of one of a side's piles (which: 0 the hand, unk64; 1 unk78; 2 unk14 from unk4) as sprites in a row */
void CARDGAME_layOutPile(CardBattle *battle, CardBattleItems *items, s32 side, s32 which) {
    CardScreen *screen = items->screen;
    CardBattle498 *p = &battle->unk498;
    s32 i;

    switch (which) {
    case 0:
        p->unk3C = battle->sides[side].pile.unkA;
        break;
    case 1:
        p->unk3C = battle->sides[side].pile.unk6;
        break;
    case 2:
        p->unk3C = battle->sides[side].pile.unk8;
        break;
    }
    p->unk30 = 0;
    p->unk34 = 0;
    p->unk38 = 0;
    p->unk40 = p->unk3C * 4 + 10;
    if (p->unk3C != 0) {
        for (i = 0; i < 40; i++) {
            if (i < p->unk3C) {
                screen->addSprite(screen, i, screen->getHandOffset(p->unk3C, i) + 0x1800, 0x6100);
                switch (which) {
                case 0:
                    screen->setSpriteCard(screen, i, battle->sides[side].pile.unk64[i]);
                    break;
                case 1:
                    screen->setSpriteCard(screen, i, battle->sides[side].pile.unk78[i]);
                    break;
                case 2:
                    screen->setSpriteCard(screen, i, battle->sides[side].pile.unk14[battle->sides[side].pile.unk4 + i]);
                    break;
                }
                if (p->unk4 != 0) {
                    screen->sprites[i].visible = 2;
                }
                screen->sprites[i].scaleX = 0;
                items->screen->sprites[i].unk49 = battle->unk498.unk6[i];
            } else {
                screen->removeSprite(screen, i);
            }
        }
        p->unk4 = 0;
    } else {
        p->unk4 = 0;
        screen->addSprite(screen, 0, screen->getHandOffset(p->unk3C, 0) + 0x1800, 0x6100);
        screen->sprites[0].visible = 3;
        screen->sprites[0].scaleX = 0;
        for (i = 1; i < 40; i++) {
            screen->removeSprite(screen, i);
        }
    }
}

s32 func_8009CE0C(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    if (battle->unk4E8 == 0) {
        battle->unk498.unk1 = 2;
        items->screen->unkEC4(items->screen);
        battle->unk4E8++;
    }
    if (items->screen->panels[0].state == 0 && battle->unk498.unk0 == 0) {
        done = 1;
    }
    return done;
}

void func_8009CEB0(CardBattle *battle, CardBattleItems *items, s32 side, s32 which) {
    CardBattle498 *p = &battle->unk498;

    switch (which) {
    case 0:
        p->unk3C = battle->sides[side].pile.unkA;
        break;
    case 1:
        p->unk3C = battle->sides[side].pile.unk6;
        break;
    case 2:
        p->unk3C = battle->sides[side].pile.unk8;
        break;
    }
    p->unk30 = 0;
    p->unk34 = 0;
    p->unk38 = 0;
    p->unk40 = p->unk3C * 4 + 10;
}

/* Lays out the slots as sprites (0-5 player 0's, 6-11 player 1's) and each unk560.unk20 entry (12 on), marking in unk3E[entry] the slot sprites it applies to (by unk5) */
void CARDGAME_layOutSlots(CardBattle *battle, CardBattleItems *items) {
    CardScreen *screen = items->screen;
    CardSlot *slot;
    CardSprite *sprite;
    s32 i;
    s32 j;
    s32 first;
    s32 index;
    s32 card;

    for (i = 0; i < 6; i++) {
        if (i >= battle->players[0].slotCount) {
            break;
        }
#if VERSION_US
        screen->addSprite(screen, i, 0x1800 + i * 0x2900, 0x9000);
#elif VERSION_EU
        screen->addSprite(screen, i, D_800A5958[SHIFT_PAL_SCREEN][0] + i * 0x2900, D_800A5958[SHIFT_PAL_SCREEN][1]);
#endif
        screen->setSpriteCard(screen, i, battle->players[0].slots[i].card);
        screen->sprites[i].unk43 = battle->players[0].slots[i].unk6;
        screen->sprites[i].unk44 = battle->players[0].slots[i].unk8;
        screen->sprites[i].scaleX = 0;
    }
    for (i = 0; i < 6; i++) {
        if (i >= battle->players[1].slotCount) {
            break;
        }
#if VERSION_US
        screen->addSprite(screen, i + 6, 0x1800 + i * 0x2900, 0x3200);
#elif VERSION_EU
        screen->addSprite(screen, i + 6, D_800A5958[SHIFT_PAL_SCREEN][2] + i * 0x2900, D_800A5958[SHIFT_PAL_SCREEN][3]);
#endif
        screen->setSpriteCard(screen, i + 6, battle->players[1].slots[i].card);
        screen->sprites[i + 6].unk43 = battle->players[1].slots[i].unk6;
        screen->sprites[i + 6].unk44 = battle->players[1].slots[i].unk8;
        screen->sprites[i + 6].scaleX = 0;
        if (battle->unk498.unk4 != 0) {
            screen->sprites[i + 6].visible = 2;
        }
    }
    battle->unk498.unk4 = 0;
    for (i = 0; i < battle->unk560.unk15; i++) {
        screen->addSprite(screen, i + 12, 0x5100 + i * 0x3200, 0x6100);
        screen->setSpriteCard(screen, i + 12, battle->unk560.unk20[i].unk0);
        screen->sprites[i + 12].scaleX = 0;
        screen->sprites[i + 12].unk46 = i + 1;
        screen->sprites[i + 12].unk3E[0] = 0;
        screen->sprites[i + 12].unk3E[1] = 0;
        screen->sprites[i + 12].unk3E[2] = 0;
        screen->sprites[i + 12].moving = 0;
        if (battle->unk560.unk20[i].unk2 != 0) {
            screen->sprites[i + 12].unk3E[battle->unk560.unk20[i].unk2] = 1;
        }
        switch (battle->unk560.unk20[i].unk5) {
        case 0:
            for (j = 0; j < 12; j++) {
                if (j < 6) {
                    if (j >= battle->players[0].slotCount) {
                        continue;
                    }
                    slot = &battle->players[0].slots[j];
                } else {
                    index = j - 6;
                    if (index >= battle->players[1].slotCount) {
                        continue;
                    }
                    slot = &battle->players[1].slots[index];
                }
                if (slot->order == battle->unk560.unk20[i].unk6) {
                    screen->sprites[j].unk3E[i] = 1;
                }
            }
            break;
        case 1:
            first = 0;
            if (battle->unk560.unk20[i].unk4 != 0) {
                first = 6;
            }
            sprite = &screen->sprites[first];
            for (j = 0; j < 6; j++) {
                sprite[j].unk3E[i] = 1;
            }
            break;
        case 2:
            first = 0;
            if (battle->unk560.unk20[i].unk4 == 0) {
                first = 6;
            }
            sprite = &screen->sprites[first];
            for (j = 0; j < 6; j++) {
                sprite[j].unk3E[i] = 1;
            }
            break;
        case 3:
            for (j = 0; j < 12; j++) {
                screen->sprites[j].unk3E[i] = 1;
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            for (j = 0; j < 12; j++) {
                if (j < 6) {
                    card = battle->players[0].slots[j].card;
                } else {
                    card = battle->players[1].slots[j - 6].card;
                }
                switch (battle->unk560.unk20[i].unk5) {
                case 4:
                    if (screen->getCardColor(screen, card) != 1) {
                        screen->sprites[j].unk3E[i] = 1;
                    }
                    break;
                case 5:
                    if (screen->getCardColor(screen, card) != 2) {
                        screen->sprites[j].unk3E[i] = 1;
                    }
                    break;
                case 6:
                    if (screen->getCardColor(screen, card) == 3) {
                        screen->sprites[j].unk3E[i] = 1;
                    }
                    break;
                case 7:
                    if (screen->getCardColor(screen, card) != 4) {
                        screen->sprites[j].unk3E[i] = 1;
                    }
                    break;
                case 8:
                    if (screen->getCardColor(screen, card) == 6) {
                        screen->sprites[j].unk3E[i] = 1;
                    }
                    break;
                }
            }
            break;
        case 9:
            break;
        }
    }
}

void func_8009D470(CardBattle *battle, CardBattleItems *items) {
    s32 frames;
    CardFader *fader;
    s32 i;

    if (battle->unk306 != 0) {
        i = battle->unk306 - 1;
        frames = 10;
        fader = CARDGAME_createFader(D_800A4BD8[i].blend);
        items->unk0[1] = fader;
        fader->setColor(fader, D_800A4BD8[i].r, D_800A4BD8[i].g, D_800A4BD8[i].b);
        if (D_800A4BD8[i].blend == 2) {
            frames = 15;
        }
        ((CardFader *)items->unk0[1])->start(items->unk0[1], 0, 0, 0, frames, 1);
        battle->unk306 = 0;
    }
}

void func_8009D53C(CardBattle *battle) {
    CardBattle498 *p = &battle->unk498;
    u8 state = p->unk5;
    s32 i;

    if (state != 0) {
        for (i = 0; i < 15; i++) {
            battle->unk498.unk6[i] = state == 2;
        }
        p->unk5 = 0;
    }
}

/* Starts (unk498.unk1) and runs (unk498.unk0) the screen's card animations: the hands', the record's and a pile's sprites scaling in or out */
void CARDGAME_updateCardAnims(CardBattle *battle, CardBattleItems *items) {
    CardBattle498 *p = &battle->unk498;
    CardScreen *screen = items->screen;
    s32 index = 0;
    s32 count;
    s32 i;

    if (p->unk1 != 0) {
        switch (p->unk1) {
        case 1:
            CARDGAME_layOutSlots(battle, items);
            p->unk30 = 3;
            p->unk34 = 0;
            p->unk38 = 4;
            p->unk40 = (battle->players[0].slotCount > battle->players[1].slotCount ? battle->players[0].slotCount : battle->players[1].slotCount) * 8;
            for (i = 0; i < 40; i++) {
                items->screen->sprites[i].unk49 = battle->unk498.unk6[i];
            }
            break;
        case 3:
            p->unk30 = 3;
            p->unk34 = 0;
            p->unk38 = 4;
            p->unk40 = battle->unk560.unk15 * 10;
            break;
        case 2:
            p->unk30 = 3;
            p->unk34 = 0;
            p->unk38 = 4;
            p->unk40 = (battle->players[0].slotCount > battle->players[1].slotCount ? battle->players[0].slotCount : battle->players[1].slotCount) * 5;
            break;
        case 4:
            p->unk30 = 3;
            p->unk34 = 0;
            p->unk38 = 4;
            p->unk40 = battle->unk560.unk15 * 5 + 22;
            break;
        case 5:
        case 17:
            index++;
        case 7:
            index++;
        case 9:
            index++;
        case 11:
        case 18:
            index++;
        case 13:
            index++;
        case 15:
            index++;
            CARDGAME_layOutPile(battle, items, D_800A4BF0[index][0], D_800A4BF0[index][1]);
            break;
        case 6:
            func_8009CEB0(battle, items, 0, 0);
            break;
        case 10:
            func_8009CEB0(battle, items, 0, 1);
            break;
        case 8:
            func_8009CEB0(battle, items, 0, 2);
            break;
        case 16:
            func_8009CEB0(battle, items, 1, 1);
            break;
        case 14:
            func_8009CEB0(battle, items, 1, 2);
            break;
        case 12:
            func_8009CEB0(battle, items, 1, 0);
            break;
        }
        p->unk3 = p->unk1 + 1;
        p->unk0 = p->unk1;
        p->unk1 = 0;
    }
    switch (p->unk0) {
    case 1:
        if (p->unk38 >= 4) {
            if (p->unk34 < battle->players[0].slotCount) {
                items->screen->scaleSprite(items->screen, p->unk34, 10, 0x1000, 0x1000);
            }
            if (p->unk34 < battle->players[1].slotCount) {
                items->screen->scaleSprite(items->screen, p->unk34 + 6, 10, 0x1000, 0x1000);
            }
            p->unk34++;
            p->unk38 -= 4;
        }
        p->unk30 += GFX.funcs.getFrameTime();
        p->unk38 += GFX.funcs.getFrameTime();
        if (p->unk40 < p->unk30) {
            p->unk1 = 3;
        }
        break;
    case 3:
        if (p->unk38 >= 4) {
            if (p->unk34 < battle->unk560.unk15) {
                items->screen->scaleSprite(items->screen, p->unk34 + 12, 10, 0x1000, 0x1000);
            }
            if (p->unk34 - 1 < battle->unk560.unk15 && p->unk34 - 1 >= 0) {
                items->screen->unkEA4(items->screen, p->unk34 - 1, battle->unk560.unk20[p->unk34 - 1].unk4);
            }
            p->unk34++;
            p->unk38 -= 4;
        }
        p->unk30 += GFX.funcs.getFrameTime();
        p->unk38 += GFX.funcs.getFrameTime();
        if (p->unk40 < p->unk30) {
            p->unk0 = 0;
        }
        break;
    case 2:
        if (p->unk38 >= 4) {
            if (p->unk34 < battle->players[0].slotCount) {
                items->screen->scaleSprite(items->screen, p->unk34, 5, 0, 0x1000);
            }
            if (p->unk34 < battle->players[1].slotCount) {
                items->screen->scaleSprite(items->screen, p->unk34 + 6, 5, 0, 0x1000);
            }
            p->unk34++;
            p->unk38 -= 4;
        }
        p->unk30 += GFX.funcs.getFrameTime();
        p->unk38 += GFX.funcs.getFrameTime();
        if (p->unk40 < p->unk30) {
            p->unk1 = 4;
        }
        break;
    case 4:
        if (p->unk38 >= 4) {
            if (p->unk34 < battle->unk560.unk15) {
                items->screen->scaleSprite(items->screen, p->unk34 + 12, 5, 0, 0x1000);
                items->screen->unkEA8(items->screen, p->unk34);
            }
            p->unk34++;
            p->unk38 -= 4;
        }
        p->unk30 += GFX.funcs.getFrameTime();
        p->unk38 += GFX.funcs.getFrameTime();
        if (p->unk40 < p->unk30) {
            p->unk0 = 0;
        }
        break;
    case 5:
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
        count = p->unk3C;
        if (count == 0) {
            count = 1;
        }
        if (p->unk34 < count && p->unk38 >= 4) {
            screen->scaleSprite(screen, p->unk34, 10, 0x1000, 0x1000);
            p->unk34++;
            p->unk38 -= 4;
        }
        if (p->unk30 > p->unk40) {
            p->unk0 = 0;
        }
        p->unk30 += GFX.funcs.getFrameTime();
        p->unk38 += GFX.funcs.getFrameTime();
        break;
    case 6:
    case 8:
    case 10:
    case 12:
    case 14:
    case 16:
        count = p->unk3C;
        if (count == 0) {
            count = 1;
        }
        if (p->unk34 < count && p->unk38 >= 4) {
            screen->scaleSprite(screen, p->unk34, 5, 0, 0x1000);
            p->unk34++;
            p->unk38 -= 4;
        }
        if (p->unk30 > p->unk40) {
            p->unk0 = 0;
        }
        p->unk30 += GFX.funcs.getFrameTime();
        p->unk38 += GFX.funcs.getFrameTime();
        break;
    case 17:
        p->unk0 = 0;
        p->unk3 = 6;
        break;
    case 18:
        p->unk0 = 0;
        p->unk3 = 12;
        break;
    }
}

void func_8009DCDC(CardBattle *battle, CardBattleItems *items) {
    s32 side;
    s32 i;

    for (side = 0; side < 2; side++) {
        for (i = 0; i < 5; i++) {
            items->screen->setPanelValue(items->screen, side, i, battle->sides[side].pile.unkC[i]);
        }
        items->screen->setPanelValue(items->screen, side, 5, battle->sides[side].pile.unk8);
        items->screen->setPanelValue(items->screen, side, 6, battle->sides[side].pile.unkA);
        items->screen->setPanelValue(items->screen, side, 7, battle->sides[side].pile.unk6);
        items->screen->setPanelValue(items->screen, side, 8, battle->sides[side].pile.unk0);
        items->screen->setPanelValue(items->screen, side, 9, battle->sides[side].pile.unk2);
    }
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009DE0C);

void func_8009DF5C(CardBattle *battle, s32 base, s32 n) {
    CardPile *pile = &battle->sides[0].pile;
    s32 i;
    s32 a;
    s32 b;
    s32 tmp;

    if (n >= 2) {
        for (i = 0; i < 40; i++) {
            a = RANDOM.next() % n + base;
            b = RANDOM.next() % n + base;
            tmp = pile->unk14[a];
            pile->unk14[a] = pile->unk14[b];
            pile->unk14[b] = tmp;
        }
    }
}

/* Chooses the player's deck: opens the three deck windows and a marker, Up/Down/Cross pick one, then loads both decks' cards; 1 once done */
s32 CARDGAME_chooseDeck(CardBattle *battle, CardBattleItems *items) {
    CardPreloader *preloader;
    CardPile *pile;
    s32 i;
    s32 done = 0;

    switch (battle->unk2F9) {
    case 0:
    default:
        preloader = items->unk0[0];
        if (preloader == NULL) {
            battle->unk2F9++;
        } else if (preloader->state == 1 && preloader->ready != 0) {
            battle->unk2F9++;
        }
        break;
    case 1:
        items->screen->unkEAC(items->screen, 5, 5, 0x41, 0, 0x26);
        SOUND.playSound(0x40019);
        items->deckWindows[0] = CARDGAME_createDeckWindow(0, CARDGAME_deckWindowPos[0].x, CARDGAME_deckWindowPos[0].y);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 2:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 11) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 3:
        SOUND.playSound(0x40019);
        items->deckWindows[1] = CARDGAME_createDeckWindow(1, CARDGAME_deckWindowPos[1].x, CARDGAME_deckWindowPos[1].y);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 4:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 11) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 5:
        SOUND.playSound(0x40019);
        items->deckWindows[2] = CARDGAME_createDeckWindow(2, CARDGAME_deckWindowPos[2].x, CARDGAME_deckWindowPos[2].y);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 6:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 11) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 7:
        items->marker = CARDGAME_createMarker(CARDGAME_deckWindowPos[0].x, CARDGAME_deckWindowPos[0].y);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 8:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 11) {
            battle->unk2FC = 0;
            battle->unk2EA = 0;
            battle->unk2F9++;
        }
        break;
    case 9:
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_UP))) |
            (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_UP)))) {
            if (battle->unk2EA > 0) {
                battle->unk2EA--;
                SOUND.playSound(0x4001B);
            }
        } else if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_DOWN))) |
                   (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_DOWN)))) {
            if (battle->unk2EA < 2) {
                battle->unk2EA++;
                SOUND.playSound(0x4001B);
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            battle->unk2FC = 0;
            battle->unk2F9++;
            items->deckWindows[battle->unk2EA]->setBlink(items->deckWindows[battle->unk2EA]);
            items->marker->setFast(items->marker);
        }
        items->marker->setPos(items->marker, CARDGAME_deckWindowPos[battle->unk2EA].x, CARDGAME_deckWindowPos[battle->unk2EA].y);
        break;
    case 10:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 15) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 11:
        items->marker->close(items->marker);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 13:
        SOUND.playSound(0x4001A);
        items->deckWindows[0]->close(items->deckWindows[0]);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 14:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 4) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 15:
        SOUND.playSound(0x4001A);
        items->deckWindows[1]->close(items->deckWindows[1]);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 16:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 4) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 17:
        SOUND.playSound(0x4001A);
        items->deckWindows[2]->close(items->deckWindows[2]);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 18:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 4) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 19:
        items->screen->unkEB0(items->screen, 5);
        battle->unk2FC = 0;
        battle->unk2F9++;
        break;
    case 12:
    case 20:
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 6) {
            battle->unk2FC = 0;
            battle->unk2F9++;
        }
        break;
    case 21:
        if (GAME.decks[battle->unk2EA].cards[0] != 0) {
            for (i = 0; i < 40; i++) {
                battle->unk298[i] = GAME.decks[battle->unk2EA].cards[i] - 1;
            }
        } else {
            for (i = 0; i < 40; i++) {
                battle->unk298[i] = CARDGAME_defaultDeck[i];
            }
        }
        battle->cardCount = items->screen->loadCardImages(battle->cards, battle->unk298, battle->unk248);
        for (i = 0; i < 40; i++) {
            battle->sides[0].pile.unk14[i] = i;
            battle->sides[1].pile.unk14[i] = i + 40;
        }
        battle->unk300 = 0;
        func_8009C92C(battle, items);
        battle->sides[1].pile.unk8 = 40;
        battle->sides[0].pile.unk8 = 40;
        battle->sides[1].pile.unk4 = 0;
        battle->sides[0].pile.unk4 = 0;
        func_8009DCDC(battle, items);
        pile = &battle->sides[0].pile;
        battle->unk810(battle, pile->unk4, pile->unk8);
        done = 1;
        break;
    }
    return done;
}

s32 func_8009E7D0(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    if (battle->unk2F9 == 0) {
        battle->unk421 = 0xA7;
        battle->unk2F4 = 1;
        battle->unk2F9 = 1;
    } else {
        if (battle->unk440 == 0) {
            battle->unk2F5 = 0;
        } else {
            battle->unk2F5 = 1;
        }
        done = 1;
    }
    return done;
}

s32 func_8009E820(CardBattle *battle, CardBattleItems *items) {
    s32 result = 0;

    if (battle->unk2F9 == 0) {
        battle->unk421 = 0x14;
        battle->unk2F4 = 1;
        battle->unk2F9++;
    } else {
        switch (battle->unk440) {
        case 0:
            result = 1;
            break;
        case 1:
            result = 2;
            break;
        case 2:
            result = 3;
            break;
        }
    }
    return result;
}

/* Takes the first flagged card out of the hand of side unk560.unk19 into the record entry unk560.unk20[unk15]; returns its condition id */
s32 CARDGAME_takeFlaggedCard(CardBattle *battle, CardBattleItems *items) {
    s32 i;
    s32 j;
    s32 side;
    s32 card;
    s16 index;

    for (i = 0; i < 10; i++) {
        if (battle->unk46F[i] != 0) {
            break;
        }
    }
    side = battle->unk560.unk19;
    card = battle->cards[battle->sides[side].pile.unk64[i]];
    battle->unk560.unk20[battle->unk560.unk15].unk4 = side;
    index = battle->sides[side].pile.unk64[i];
    battle->unk560.unk20[battle->unk560.unk15].unk0 = index;
    battle->unk560.unk20[battle->unk560.unk15].unk5 = func_800835C4(battle->cards[index], 3, 0);
    for (j = i; j < battle->sides[side].pile.unkA - 1; j++) {
        battle->sides[side].pile.unk64[j] = battle->sides[side].pile.unk64[j + 1];
    }
    battle->sides[side].pile.unkA--;
    return func_800835C4(card, 0, 0);
}

/* Flags (unk46F) the slots that the current record entry's target kind (unk560.unk20[unk15].unk5) picks */
void func_8009EA28(CardBattle *battle, CardScreen *screen) {
    CardSlot *slot;
    s32 card;
    s32 i;

    for (i = 0; i < 12; i++) {
        battle->unk46F[i] = 0;
        switch (battle->unk560.unk20[battle->unk560.unk15].unk5) {
        case 0:
            if (i < 6) {
                if (i >= battle->players[0].slotCount) {
                    break;
                }
                slot = &battle->players[0].slots[i];
            } else {
                if (i - 6 >= battle->players[1].slotCount) {
                    break;
                }
                slot = &battle->players[1].slots[i - 6];
            }
            if (slot->order == battle->unk560.unk20[battle->unk560.unk15].unk6) {
                battle->unk46F[i] = 1;
            }
            break;
        case 2:
            if (i < 6 && i < battle->players[0].slotCount) {
                battle->unk46F[i] = 1;
            }
            break;
        case 1:
            if (i >= 6 && i - 6 < battle->players[1].slotCount) {
                battle->unk46F[i] = 1;
            }
            break;
        case 3:
            battle->unk46F[i] = 1;
            break;
        case 4:
            if (i < 6) {
                card = battle->players[0].slots[i].card;
            } else {
                card = battle->players[1].slots[i - 6].card;
            }
            if (screen->getCardColor(screen, card) != 1) {
                battle->unk46F[i] = 1;
            }
            break;
        case 5:
            if (i < 6) {
                card = battle->players[0].slots[i].card;
            } else {
                card = battle->players[1].slots[i - 6].card;
            }
            if (screen->getCardColor(screen, card) != 2) {
                battle->unk46F[i] = 1;
            }
            break;
        case 6:
            if (i < 6) {
                card = battle->players[0].slots[i].card;
            } else {
                card = battle->players[1].slots[i - 6].card;
            }
            if (screen->getCardColor(screen, card) == 3) {
                battle->unk46F[i] = 1;
            }
            break;
        case 7:
            if (i < 6) {
                card = battle->players[0].slots[i].card;
            } else {
                card = battle->players[1].slots[i - 6].card;
            }
            if (screen->getCardColor(screen, card) != 4) {
                battle->unk46F[i] = 1;
            }
            break;
        case 8:
            if (i < 6) {
                card = battle->players[0].slots[i].card;
            } else {
                card = battle->players[1].slots[i - 6].card;
            }
            if (screen->getCardColor(screen, card) == 6) {
                battle->unk46F[i] = 1;
            }
            break;
        case 9:
            break;
        }
    }
}

/* Runs the rounds of plays (state unk560.unk14): each side in turn plays a card, the computer through CARDGAME_pickComputerCard; 1 once over */
s32 CARDGAME_playRounds(CardBattle *battle, CardBattleItems *items) {
    s32 condition;
    s32 side;
    s32 i;
    s32 done = 0;

    switch (battle->unk560.unk14) {
    case 0:
    default:
        battle->unk560.unk14 = 16;
        battle->unk560.unk15 = 0;
        battle->unk560.unk17 = 0;
        battle->unk560.unk20[0].unk2 = 0;
        battle->unk560.unk20[1].unk2 = 0;
        battle->unk560.unk20[2].unk2 = 0;
        battle->unk498.unk5 = 1;
        battle->unk498.unk1 = 1;
        battle->unk560.unk18 = battle->unk560.unk19 = battle->unk2F5;
        items->screen->unkEC8(items->screen);
        break;
    case 16:
        if (items->screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            battle->unk560.unk14 = 17;
            items->screen->unkEAC(items->screen, 5, 5, battle->unk2F8 == 5 ? 0x3C : 0x3D, 0, 0x6E);
        }
        break;
    case 17:
        if (items->screen->unkE0C[5].state == 2) {
            if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
                battle->unk560.unk14 = 18;
                items->screen->unkEB0(items->screen, 5);
            }
        }
        break;
    case 18:
        if (items->screen->unkE0C[5].state == 0) {
            battle->unk560.unk14 = 1;
        }
        break;
    case 1:
        switch (battle->unk560.unk15) {
        case 0:
        case 2:
            if (battle->unk560.unk18 != 0) {
                battle->unk560.unk14 = 3;
            } else {
                battle->unk560.unk14 = 2;
            }
            break;
        case 1:
            if (battle->unk560.unk18 != 0) {
                battle->unk560.unk14 = 2;
            } else {
                battle->unk560.unk14 = 3;
            }
            break;
        default:
            battle->unk560.unk14 = 12;
            break;
        }
        if (battle->unk560.unk15 != 0) {
            battle->unk560.unk17 = 0;
        }
        battle->unk560.unk1A = -1;
        items->screen->setPanelValue(items->screen, 0, 6, battle->sides[0].pile.unkA);
        items->screen->setPanelValue(items->screen, 1, 6, battle->sides[1].pile.unkA);
        break;
    case 3:
        func_8009C844(battle);
        if (CARDGAME_pickComputerCard(battle, items->screen)) {
            condition = CARDGAME_takeFlaggedCard(battle, items);
            if (condition == 0x83 || condition == 0x84) {
                for (i = 0; i < 15; i++) {
                    battle->unk46F[i] = 0;
                }
                battle->unk46F[battle->unk560.unk15 + 11] = 1;
                battle->unk560.unk20[battle->unk560.unk15 - 1].unk2 = 1;
            }
            if (battle->unk560.unk17 != 0) {
                SOUND.playSound(0x40019);
                items->screen->unkED4(items->screen, 0);
            }
            battle->unk560.unk14 = 9;
            func_8009EA28(battle, items->screen);
        } else if (battle->unk560.unk15 == 0) {
            battle->unk560.unk14 = 11;
            battle->unk560.unk1C = 20;
            battle->unk560.unk17++;
            SOUND.playSound(0x40019);
            items->screen->unkED0(items->screen, 1);
        } else {
            battle->unk560.unk14 = 12;
        }
        break;
    case 2:
        if (battle->unk560.unk1A == -1) {
            battle->unk2F4 = 1;
            battle->unk421 = 0x98;
            battle->unk814(battle, battle->sides[0].pile.unk64, battle->sides[0].pile.unkA << 16, 0);
        } else if (battle->unk560.unk1A != 0) {
            battle->unk560.unk14 = CARDGAME_turnStates[battle->unk560.unk19 + 2];
            battle->unk560.unk1A = -1;
            if (battle->unk560.unk17 != 0) {
                items->screen->panels[1].scale.state = 0;
            }
        } else if (battle->unk560.unk15 == 0) {
            battle->unk560.unk14 = 11;
            battle->unk560.unk1C = 20;
            battle->unk560.unk17++;
            SOUND.playSound(0x40019);
            items->screen->unkED0(items->screen, 0);
        } else {
            battle->unk560.unk14 = 12;
        }
        break;
    case 4:
    case 5:
        if (battle->unk560.unk1A == -1) {
            battle->unk2F4 = 1;
            battle->unk421 = 0x99;
        } else if (battle->unk560.unk1A != 0) {
            battle->unk560.unk14 = CARDGAME_turnStates[battle->unk560.unk19 + 4];
            battle->unk560.unk1A = -1;
        } else {
            battle->unk560.unk14 = CARDGAME_turnStates[battle->unk560.unk19];
            battle->unk560.unk1A = -1;
            if (battle->unk560.unk17 != 0) {
                items->screen->panels[1].scale.state = 2;
            }
        }
        break;
    case 6:
    case 7:
        if (battle->unk560.unk1A == -1) {
            battle->unk421 = CARDGAME_takeFlaggedCard(battle, items);
            battle->unk2F4 = 1;
        } else if (battle->unk560.unk1A != 0) {
            battle->unk560.unk14 = CARDGAME_turnStates[battle->unk560.unk19 + 6];
        } else {
            side = battle->unk560.unk19;
            battle->sides[side].pile.unk64[battle->sides[side].pile.unkA] = battle->unk560.unk20[battle->unk560.unk15].unk0;
            battle->sides[side].pile.unkA++;
            battle->unk814(battle, battle->sides[0].pile.unk64, battle->sides[0].pile.unkA << 16, 0);
            battle->unk560.unk14 = CARDGAME_turnStates[battle->unk560.unk19 + 2];
            battle->unk560.unk1A = -1;
        }
        break;
    case 9:
        battle->unk421 = 0x13;
        battle->unk2F4 = 1;
        battle->unk560.unk14 = 10;
        break;
    case 8:
        battle->unk421 = 0x12;
        battle->unk2F4 = 1;
        battle->unk560.unk14 = 10;
        break;
    case 10:
        battle->unk560.unk14 = 1;
        battle->unk560.unk19 ^= 1;
        battle->unk560.unk15++;
        break;
    case 11:
        if (--battle->unk560.unk1C <= 0) {
            battle->unk560.unk14 = 14;
        }
        break;
    case 12:
        if (battle->unk560.unk15 > 0) {
            battle->unk2F4 = 2;
            battle->unk560.unk14 = 13;
            battle->unk4DC = 0;
            battle->unk4EC = 0;
            battle->unk4E8 = 0;
            battle->unk4DE = battle->unk560.unk15;
        } else {
            battle->unk560.unk14 = 14;
        }
        break;
    case 13:
        battle->unk560.unk14 = 12;
        break;
    case 14:
        battle->unk560.unk14 = 1;
        battle->unk560.unk15 = 0;
        battle->unk560.unk20[0].unk2 = 0;
        battle->unk560.unk20[1].unk2 = 0;
        battle->unk560.unk20[2].unk2 = 0;
        battle->unk560.unk18 ^= 1;
        battle->unk560.unk19 = battle->unk560.unk18;
        battle->unk560.unk16++;
        if (battle->unk560.unk17 >= 2) {
            battle->unk560.unk14 = 15;
            battle->unk4E8 = 0;
        }
        break;
    case 15:
        items->screen->unkED4(items->screen, 0);
        items->screen->unkED4(items->screen, 1);
        if (func_8009CE0C(battle, items)) {
            done = 1;
        }
        break;
    }
    return done;
}

void func_8009F458(CardBattle *battle, CardBattleItems *items) {
    battle->unk560.unk14 = 0;
    func_8009DCDC(battle, items);
    battle->unk814(battle, battle->sides[0].pile.unk64, battle->sides[0].pile.unkA << 16, 0);
}

void func_8009F4A0(CardBattle *battle, CardPile *pile) {
    s32 i;
    s32 j;

    for (i = pile->unkA - 1; i >= 0; i--) {
        if (battle->unk46F[i] != 0) {
            for (j = i; j < pile->unkA - 1; j++) {
                pile->unk64[j] = pile->unk64[j + 1];
            }
            pile->unkA--;
        }
    }
}

void CARDGAME_setSlot(CardBattle *battle, s32 side, s32 card, s32 index) {
    CardDrawer drawer;
    CardPlayer *player = &battle->players[side];

    initCardDrawer(&drawer);
    drawer.setCard(battle->cards[card] + 1);
    player->slots[index].unk6 = drawer.card[1];
    player->slots[index].unk8 = drawer.card[2];
    player->slots[index].unk2 = 0;
    player->slots[index].unk4 = 0;
    player->slots[index].card = card;
    player->slots[index].owner = side;
    player->slots[index].side = side;
    player->slots[index].order = battle->slotCount++;
}

void CARDGAME_addCard(CardBattle *battle, s32 side, s32 card) {
    CardPlayer *player = &battle->players[side];

    CARDGAME_setSlot(battle, side, card, player->slotCount++);
}

void func_8009F664(CardBattle *battle, s32 side) {
    CardPlayer *player = &battle->players[side];
    CardPile *pile = &battle->sides[side].pile;
    s32 i;

    player->slotCount = 0;
    for (i = 0; i < pile->unkA; i++) {
        if (player->slotCount < battle->unk444 && battle->unk46F[i] != 0) {
            CARDGAME_addCard(battle, side, pile->unk64[i]);
        }
    }
    func_8009F4A0(battle, pile);
}

/* Sets the values of a slot that holds the pass-th card of D_800A4AE4 from the battle's counts (0 to 99) */
void func_8009F754(CardBattle *battle, CardSlot *slot, s32 side, s32 pass) {
    CardSide *cardSide = &battle->sides[side];
    CardPlayer *player = &battle->players[side];
    s32 values[2];
    s32 i;
    s32 base;

    if (battle->cards[slot->card] == D_800A4AE4[pass]) {
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                base = slot->unk2;
            } else {
                base = slot->unk4;
            }
            switch (pass) {
            case 0:
                values[i] = player->slotCount * 20 + base;
                break;
            case 1:
                values[i] = cardSide->pile.unkA * 10 + 10 + base;
                break;
            case 2:
                values[i] = cardSide->pile.unk6 * 20 + 10 + base;
                break;
            case 3:
                values[i] = (battle->players[0].slotCount + battle->players[1].slotCount) * 10 + base;
                break;
            case 4:
                values[i] = (battle->sides[0].pile.unk6 + battle->sides[1].pile.unk6) * 10 + 10 + base;
                break;
            }
            if (values[i] >= 99) {
                values[i] = 99;
            }
            if (values[i] <= 0) {
                values[i] = 0;
            }
        }
        slot->unk6 = values[0];
        slot->unk8 = values[1];
    }
}

s32 func_8009F90C(CardBattle *battle) {
    s32 found = 0;
    s32 pass;
    s32 side;
    s32 i;
    CardPlayer *player;

    for (pass = 0; pass < 5; pass++) {
        for (side = 0; side < 2; side++) {
            player = &battle->players[side];
            for (i = 0; i < player->slotCount; i++) {
                found = 1;
                func_8009F754(battle, &player->slots[i], side, pass);
            }
        }
    }
    return found;
}

void func_8009F9DC(CardBattle *battle, s32 side) {
    s32 i;

    battle->sides[side].pile.unk0 = 0;
    battle->sides[side].pile.unk2 = 0;
    for (i = 0; i < battle->players[side].slotCount; i++) {
        battle->sides[side].pile.unk0 += battle->players[side].slots[i].unk6;
        battle->sides[side].pile.unk2 += battle->players[side].slots[i].unk8;
    }
}

/* A battle step: each side puts out its flagged cards (unk818) between messages 0x9A, 0x9D and 0x9E; 1 once done */
s32 func_8009FA90(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    switch (battle->unk2F9) {
    case 0:
        battle->unk421 = 0x9A;
        battle->unk2F4 = 1;
        battle->unk2F9 = 1;
        break;
    case 1:
        battle->unk818(battle, 0);
        battle->unk2F9 = 2;
        items->screen->setPanelValue(items->screen, 0, 6, battle->sides[0].pile.unkA);
        break;
    case 2:
        func_8009C844(battle);
        battle->unk421 = 0x9D;
        battle->unk2F4 = 1;
        battle->unk2F9 = 3;
        break;
    case 3:
        battle->unk818(battle, 1);
        battle->unk2F9 = 4;
        func_8009F90C(battle);
        func_8009F9DC(battle, 1);
        func_8009F9DC(battle, 0);
        items->screen->setPanelValue(items->screen, 1, 6, battle->sides[1].pile.unkA);
        break;
    case 4:
        battle->unk421 = 0x9E;
        battle->unk2F4 = 1;
        battle->unk2F9 = 5;
        break;
    case 5:
        done = 1;
        break;
    }
    return done;
}

/* Finds three or more of one card (with a header unkA) among a side's slots, by id from start: flags them in unk446; the index after them or -1 */
s32 CARDGAME_findCardSet(CardBattle *battle, s32 side, s32 start) {
    CardSortEntry entries[6];
    CardSortEntry tmp;
    CardDrawer drawer;
    s32 count;
    s32 value;
    s32 result;
    s32 i;
    s32 j;
    s32 k;

    result = -1;
    value = 0x51;
    count = battle->players[side].slotCount;
    initCardDrawer(&drawer);
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
    for (i = start; i < count - 1; i++) {
        drawer.setCard(entries[i].card + 1);
        if (((CardImageHeader *)drawer.card)->unkA != 0 && entries[i].card == entries[i + 1].card) {
            value = ((CardImageHeader *)drawer.card)->unkA;
            j++;
        } else if (j < 2) {
            j = 0;
        } else {
            break;
        }
    }
    if (j >= 2) {
        for (k = 0; k < count; k++) {
            battle->unk446[k] = 0;
        }
        for (; j >= 0; j--) {
            battle->unk446[entries[i - j].slot] = 1;
        }
        battle->unk438 = value;
        result = i + 1;
    }
    return result;
}

void func_8009FE5C(CardBattle *battle, CardBattleItems *items) {
    items->screen->unkEC8(items->screen);
    battle->unk498.unk5 = 1;
    battle->unk498.unk1 = 1;
    battle->unk2F9 = 0;
}

/* The end of a round: shows both sides' cards, gives the round to the higher total (pile.unk2) and the battle to the first side with two rounds; 1 for the next round, 2 once the battle is over */
s32 CARDGAME_endRound(CardBattle *battle, CardBattleItems *items) {
    CardScreen *screen = items->screen;
    s32 result = 0;
    CardFader *fader;
    s32 side;
    s32 done;

    switch (battle->unk2F9) {
    case 0:
        if (items->screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
            battle->unk2F9 = 1;
            battle->unk2FC = 0;
        }
        break;
    case 1:
        battle->unk2FC = CARDGAME_findCardSet(battle, 0, battle->unk2FC);
        if (battle->unk2FC == -1) {
            battle->unk2F9 = 2;
            battle->unk2FC = 0;
        } else {
            battle->unk421 = 0x19;
            battle->unk2F4 = 1;
        }
        break;
    case 2:
        battle->unk2FC = CARDGAME_findCardSet(battle, 1, battle->unk2FC);
        if (battle->unk2FC == -1) {
            battle->unk2F9 = 8;
        } else {
            battle->unk421 = 0x1A;
            battle->unk2F4 = 1;
        }
        break;
    case 8:
        if (battle->unk304 != 0) {
            battle->unk421 = 0x1B;
            battle->unk2F4 = 1;
            battle->unk305--;
        }
        if (battle->unk305 == 0) {
            battle->unk2F9 = 9;
        } else {
            battle->unk2F9 = 8;
        }
        break;
    case 9:
        if (battle->players[0].slotCount == 0 || battle->players[1].slotCount == 0) {
            if (battle->sides[0].pile.unk2 > battle->sides[1].pile.unk2) {
                battle->unk301 = 0;
            } else {
                battle->unk301 = 1;
            }
            battle->unk2F9 = 11;
            if (battle->players[battle->unk301].slotCount == 0 && battle->players[battle->unk301 ^ 1].slotCount != 0) {
                battle->unk2F9 = 10;
                battle->unk2FC = 0;
            }
        } else {
            battle->unk2F9 = 3;
            screen->unkEAC(screen, 5, 5, 13, 0, 110);
        }
        break;
    case 3:
        if (screen->unkE0C[5].state == 2) {
            battle->unk2F9 = 4;
        }
        break;
    case 4:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1 ||
            (PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            battle->unk2F9 = 5;
            screen->unkEB0(screen, 5);
        }
        break;
    case 5:
        if (screen->unkE0C[5].state == 0) {
            battle->unk2F9 = 6;
        }
        break;
    case 6:
        battle->unk421 = 0x15;
        battle->unk2F4 = 1;
        battle->unk2F9 = 7;
        break;
    case 7:
        battle->unk421 = 0x16;
        battle->unk2F4 = 1;
        battle->unk2F9 = 10;
        battle->unk2FC = 0;
        break;
    case 10:
        if (battle->sides[0].pile.unk2 > battle->sides[1].pile.unk2) {
            battle->unk421 = 0x18;
            battle->unk301 = 0;
        } else {
            battle->unk421 = 0x17;
            battle->unk301 = 1;
        }
        battle->unk2F4 = 1;
        battle->unk2F9 = 11;
        battle->unk2FC = 0;
        break;
    case 11:
        side = battle->unk301;
        if (battle->unk2FC & 1) {
            items->screen->panels[side].unk44 = battle->sides[side].pile.unk12 + 1;
        } else {
            items->screen->panels[side].unk44 = battle->sides[side].pile.unk12;
        }
        if (battle->unk2FC == 0) {
            SOUND.playSound(0x9C0002);
            fader = CARDGAME_createFader(1);
            items->unk0[1] = fader;
            fader->setColor(fader, 0x80, 0x80, 0x80);
            ((CardFader *)items->unk0[1])->start(items->unk0[1], 0, 0, 0, 10, 1);
        }
        battle->unk2FC += GFX.funcs.getFrameTime();
        if (battle->unk2FC >= 51) {
            items->screen->panels[side].unk44 = battle->sides[side].pile.unk12 + 1;
            battle->sides[side].pile.unk12++;
            battle->unk2F9 = 12;
            if (battle->unk301 == 0) {
                screen->unkEAC(screen, 5, 5, 16, 0, 110);
            } else if (battle->sides[0].pile.unk2 != battle->sides[1].pile.unk2) {
                screen->unkEAC(screen, 5, 5, 17, 0, 110);
            } else {
                screen->unkEE4(screen, 18, 0, 0, 1);
            }
        }
        break;
    case 12:
        if (battle->sides[0].pile.unk2 != battle->sides[1].pile.unk2) {
            done = screen->unkE0C[5].state == 2;
        } else {
            done = screen->unkDFA == 2;
        }
        if (done) {
            battle->unk2F9 = 13;
        }
        break;
    case 13:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1 ||
            (PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            if (battle->sides[0].pile.unk2 != battle->sides[1].pile.unk2) {
                screen->unkEB0(screen, 5);
            } else {
                screen->unkEE8(screen);
            }
            battle->unk2F9 = 14;
        }
        break;
    case 14:
        if (battle->sides[0].pile.unk2 != battle->sides[1].pile.unk2) {
            done = screen->unkE0C[5].state == 0;
        } else {
            done = screen->unkDFA == 0;
        }
        if (done) {
            battle->unk2F9 = 15;
            screen->unkEE4(screen, 19, 0, 0, 1);
        }
        break;
    case 15:
        if (screen->unkDFA == 2) {
            battle->unk2F9 = 16;
        }
        break;
    case 16:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1 ||
            (PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            screen->unkEE8(screen);
            battle->unk2F9 = 17;
        }
        break;
    case 17:
        if (screen->unkDFA == 0) {
            if (battle->sides[0].pile.unk12 >= 2) {
                SOUND.playSound(0x6004001E);
                screen->unkEAC(screen, 5, 5, 21, 0, 110);
                battle->unk2F9 = 19;
                battle->unk302 = 0;
            } else if (battle->sides[1].pile.unk12 >= 2) {
                screen->unkEAC(screen, 5, 5, 22, 0, 110);
                battle->unk2F9 = 19;
                battle->unk302 = 1;
            } else {
                battle->unk2F9 = 18;
            }
        }
        break;
    case 18:
        if (battle->unk301 == 0) {
            battle->unk421 = 0x1C;
        } else {
            battle->unk421 = 0x1D;
        }
        battle->unk2F4 = 1;
        battle->unk2F9 = 26;
        break;
    case 19:
        if (screen->unkE0C[5].state == 2) {
            battle->unk2F9 = 20;
        }
        break;
    case 20:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1 ||
            (PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            if (battle->unk301 == 0) {
                screen->unkEB0(screen, 5);
                battle->unk2F9 = 21;
                battle->unk4E8 = 0;
            } else {
                battle->unk2F9 = 25;
            }
        }
        break;
    case 21:
        if (screen->unkE0C[5].state == 0 && func_8009CE0C(battle, items)) {
            battle->unk2F9 = 22;
            screen->unkEE4(screen, battle->unk2EC, 0, 0, 3);
        }
        break;
    case 22:
        if (screen->unkDFA == 2) {
            battle->unk2F9 = 23;
        }
        break;
    case 23:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1 ||
            (PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            battle->unk2F9 = 25;
        }
        break;
    case 25:
        result = 2;
        break;
    case 26:
        result = 1;
        break;
    }
    return result;
}

void func_800A0908(CardPile *pile) {
    while (pile->unkA > 0) {
        pile->unk14[--pile->unk4] = pile->unk64[--pile->unkA];
        pile->unk8++;
    }
}

void func_800A096C(CardBattle *battle, CardBattleItems *items) {
    CardPile *pile = &battle->sides[0].pile;

    func_800A0908(pile);
    func_8009C9B0(battle, items);
#if VERSION_US
    func_8009C92C(battle, items);
#endif
    battle->unk810(battle, pile->unk4, pile->unk8);
    battle->unk304 = 0;
    battle->unk305 = 0;
    battle->sides[0].pile.unk0 = 0;
    battle->sides[0].pile.unk2 = 0;
    battle->sides[1].pile.unk0 = 0;
    battle->sides[1].pile.unk2 = 0;
    func_8009DCDC(battle, items);
    battle->unk300++;
#if VERSION_EU
    func_8009C92C(battle, items);
#endif
}

void func_800A0A0C(CardBattle *battle, CardBattleItems *items) {
    s32 i = battle->unk2F6;

    battle->unk2F4 = 1;
    battle->unk421 = D_800A4C20[i].text;
    battle->unk2F7 = D_800A4C20[i].unk2;
}

void func_800A0A40(CardBattle *battle, CardBattleItems *items) {
    battle->sides[0].pile.unk11 = 0;
    battle->sides[1].pile.unk11 = 1;
    battle->result = 0;
    battle->unk302 = 1;
    battle->unk2F8 = 1;
}

/* Runs the battle's current phase (unk2F8), after switching to the one asked for in unk2F7; 1 once the battle is over */
s32 CARDGAME_runPhase(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    if (battle->unk2F7 != 0) {
        switch (battle->unk2F7) {
        case 1:
        case 2:
            battle->unk2F9 = 0;
            battle->unk2FC = 0;
            break;
        case 3:
        case 4:
        case 6:
            battle->unk2F9 = 0;
            break;
        case 5:
        case 7:
            func_8009F458(battle, items);
            break;
        case 8:
            func_8009FE5C(battle, items);
            break;
        case 9:
            func_800A096C(battle, items);
            break;
        }
        battle->unk2F6 = battle->unk2F8;
        battle->unk2F8 = battle->unk2F7;
        battle->unk2F7 = 0;
    }
    switch (battle->unk2F8) {
    case 1:
        switch (battle->unk2F9) {
        case 0:
        default:
            items->screen->unkE9E = 1;
            battle->unk2F9 = 1;
            break;
        case 1:
            if (items->screen->unkE9E == 2) {
                battle->unk2F7 = 10;
            }
            break;
        }
        break;
    case 2:
        if (CARDGAME_chooseDeck(battle, items)) {
            battle->unk2F7 = 10;
        }
        break;
    case 3:
        if (func_8009E7D0(battle, items)) {
            battle->unk2F7 = 10;
        }
        break;
    case 4:
        switch (func_8009E820(battle, items)) {
        case 1:
            battle->unk2F7 = 10;
            break;
        case 2:
            battle->unk302 = 1;
            done = 1;
            break;
        case 3:
            battle->unk302 = 0;
            done = 1;
            break;
        }
        break;
    case 5:
    case 7:
        if (CARDGAME_playRounds(battle, items)) {
            battle->unk2F7 = 10;
        }
        break;
    case 6:
        if (func_8009FA90(battle, items)) {
            battle->unk2F7 = 10;
        }
        break;
    case 8:
        switch (CARDGAME_endRound(battle, items)) {
        case 1:
            battle->unk2F7 = 9;
            break;
        case 2:
            done = 1;
            break;
        }
        break;
    case 9:
        battle->unk2F7 = 10;
        break;
    case 10:
        func_800A0A0C(battle, items);
        break;
    }
    return done;
}

s32 func_800A0CCC(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    if (battle->unk4E8 == 0) {
        battle->unk498.unk5 = 1;
        battle->unk498.unk1 = 1;
        items->screen->unkEC8(items->screen);
        battle->unk4E8++;
    }
    if (items->screen->panels[0].state == 2 && battle->unk498.unk0 == 0) {
        done = 1;
    }
    return done;
}

/* Shows the last card played (unk560.unk20) in window 2 for 35 frames (Cross cuts it short), then scales its sprite away; 1 once done */
s32 CARDGAME_showPlayedCard(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;
    s32 place;
    s32 i;

    switch (battle->unk4E8) {
    case 0:
        battle->unk4E8 = 1;
        battle->unk4EC = 0;
        place = battle->unk560.unk20[battle->unk560.unk15 - 1].unk4;
#if VERSION_US
        items->screen->unkEAC(items->screen, 2, 1, battle->cards[battle->unk560.unk20[battle->unk560.unk15 - 1].unk0] + 1,
                              CARDGAME_playedCardPos[0][place].x, CARDGAME_playedCardPos[0][place].y);
#elif VERSION_EU
        items->screen->unkEAC(items->screen, 2, 1, battle->cards[battle->unk560.unk20[battle->unk560.unk15 - 1].unk0] + 1,
                              CARDGAME_playedCardPos[SHIFT_PAL_SCREEN][place].x, CARDGAME_playedCardPos[SHIFT_PAL_SCREEN][place].y);
#endif
        for (i = 0; i < 15; i++) {
            items->screen->sprites[i].moving = 0;
        }
        break;
    case 1:
        if (battle->unk4EC >= 20 && (PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
            battle->unk4EC = 35;
        }
        battle->unk4EC += GFX.funcs.getFrameTime();
        if (battle->unk4EC >= 35) {
            items->screen->unkEB0(items->screen, 2);
            items->screen->scaleSprite(items->screen, battle->unk560.unk15 + 11, 8, 0x1400, 0x1400);
            items->screen->unkEA8(items->screen, battle->unk560.unk15 - 1);
            battle->unk4E8 = 2;
            battle->unk4EC = 0;
            SOUND.playSound(0x8004603C);
        }
        break;
    case 2:
        battle->unk4EC += GFX.funcs.getFrameTime();
        if (battle->unk4EC >= 8) {
            items->screen->unkF1C(items->screen, battle->unk560.unk15 + 11);
            battle->unk4E8 = 3;
            battle->unk4EC = 0;
        }
        break;
    case 3:
        battle->unk4EC += GFX.funcs.getFrameTime();
        if (battle->unk4EC >= 15) {
            items->screen->scaleSprite(items->screen, battle->unk560.unk15 + 11, 4, 0, 0);
            battle->unk4E8 = 5;
            battle->unk4EC = 0;
            SOUND.playSound(0x8004603C);
        }
        break;
    case 5:
        battle->unk4EC += GFX.funcs.getFrameTime();
        if (battle->unk4EC >= 15) {
            done = 1;
        }
        break;
    }
    return done;
}

/* Plays out the last card played (unk560.unk20): its effect and its messages, then puts it in its side's pile.unk78; 1 once done */
u8 CARDGAME_resolveCard(CardBattle *battle, CardBattleItems *items) {
    u8 done = 0;
    s16 card;
    s32 i;
    s32 text;
    s32 index;
    s32 side;
    s8 count;

    switch (battle->unk4DC) {
    case 0:
    default:
        if (func_8009F90C(battle)) {
            battle->unk421 = 0x5D;
            battle->unk2F4 = 1;
            battle->unk4DC = 1;
            break;
        }
        battle->unk4DC = 3;
    case 3:
        if (items->screen->panels[0].state == 0) {
            battle->unk4DC = 4;
        } else {
            battle->unk4DC = 5;
            battle->unk4EC = 0;
            battle->unk4E8 = 0;
            battle->unk4DD = 0;
        }
        break;
    case 1:
        battle->unk421 = 0x4C;
        battle->unk2F4 = 1;
        battle->unk4DC = 2;
        break;
    case 2:
        battle->unk421 = 0x5A;
        battle->unk2F4 = 1;
        battle->unk4DC = 3;
        break;
    case 4:
        if (func_800A0CCC(battle, items)) {
            battle->unk4DC = 5;
            battle->unk4EC = 0;
            battle->unk4E8 = 0;
            battle->unk4DD = 0;
        }
        break;
    case 5:
        if (CARDGAME_showPlayedCard(battle, items)) {
            battle->unk4DC = 6;
            battle->unk4EC = 0;
            battle->unk4E8 = 0;
        }
        break;
    case 6:
        card = battle->cards[battle->unk560.unk20[battle->unk560.unk15 - 1].unk0];
        if (CARDGAME_checkPlayCondition(battle, items->screen, func_800835C4(card, 1, 0))) {
            items->screen->unkEE4(items->screen, func_800835C4(card, 2, 0), 0, 1, 1);
            battle->unk4DC = 8;
        } else {
            battle->unk4E0 = 0;
            battle->unk4DC = 7;
        }
        break;
    case 7:
        text = func_800835C4(battle->cards[battle->unk560.unk20[battle->unk560.unk15 - 1].unk0], 4, battle->unk4E0);
        if (text != 0) {
            battle->unk421 = text;
            battle->unk2F4 = 1;
            battle->unk4E0++;
        } else {
            if (battle->unk560.unk15 >= 2) {
                battle->unk560.unk20[battle->unk560.unk15 - 2].unk2 = 0;
            }
            for (i = 0; i < 12; i++) {
                items->screen->sprites[i].unk3E[battle->unk560.unk15 - 1] = 0;
            }
            battle->unk4DC = 10;
        }
        break;
    case 8:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1 ||
            (PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            items->screen->unkEE8(items->screen);
            battle->unk4DC = 9;
        }
        break;
    case 9:
        if (items->screen->unkDFA == 0) {
            battle->unk4DC = 12;
        }
        break;
    case 10:
        battle->unk421 = 0x5A;
        battle->unk2F4 = 1;
        battle->unk4DC = 11;
        break;
    case 11:
        battle->unk4DC = 12;
        break;
    case 12:
        index = battle->unk560.unk20[battle->unk560.unk15 - 1].unk0;
        side = battle->unk560.unk20[battle->unk560.unk15 - 1].unk4;
        if (battle->cards[index] != 13) {
            battle->sides[side].pile.unk78[battle->sides[side].pile.unk6] = index;
            battle->sides[side].pile.unk6++;
        }
        count = battle->unk560.unk15;
        battle->unk560.unk15 = count - 1;
        if (battle->unk4DD != 0) {
            battle->unk560.unk15 = count - 2;
        }
        battle->unk4DC = 13;
        battle->unk4EC = 0;
        battle->unk4E8 = 0;
        break;
    case 13:
        func_8009DCDC(battle, items);
        battle->unk4DC = 14;
        break;
    case 14:
        if (func_8009F90C(battle)) {
            battle->unk421 = 0x5D;
            battle->unk2F4 = 1;
            battle->unk4DC = 15;
        } else {
            done = 1;
        }
        break;
    case 15:
        battle->unk421 = 0x4C;
        battle->unk2F4 = 1;
        battle->unk4DC = 16;
        break;
    case 16:
        battle->unk421 = 0x5A;
        battle->unk2F4 = 1;
        battle->unk4DC = 17;
        break;
    case 17:
        done = 1;
        break;
    }
    return done;
}

/* The battle menu (unk560.unk8 its state): three help messages, back, and quitting after a yes/no question; 1 when closed, 2 to quit */
s32 CARDGAME_runBattleMenu(CardBattle *battle, CardBattleItems *items) {
    s32 result = 0;
    s32 cursor;

    switch (battle->unk560.unk8) {
    case 1:
    default:
        /* save the battle state and the screen's, restored in case 15 */
        *(CardBattleSave *)battle->unk4F0 = *(CardBattleSave *)&battle->unk420;
        battle->unk560.unk9 = 0;
        CARDGAME_savedScreenState = *(CardScreenSave *)&items->screen->unkDE4;
        items->screen->unkEF4(items->screen, 0);
        battle->unk560.unk8 = 2;
        break;
    case 2:
        if (items->screen->unkE0A == 2) {
            battle->unk560.unk8 = 3;
        }
        break;
    case 3:
        if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_UP))) |
            (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_UP)))) {
            cursor = battle->unk560.unk9 - 1;
            if (cursor < 0) {
                cursor = 4;
            }
            battle->unk560.unk9 = cursor;
            SOUND.playSound(0x8004513E);
        } else if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_DOWN))) |
                   (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_DOWN)))) {
            battle->unk560.unk9 = (u8)(battle->unk560.unk9 + 1) % 5;
            SOUND.playSound(0x8004513E);
        }
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
            items->screen->unkEFC(items->screen);
            battle->unk560.unk8 = 4;
        } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            SOUND.playSound(0x800450BD);
            items->screen->unkEF8(items->screen);
            battle->unk560.unk8 = 4;
            battle->unk560.unk9 = 3;
        }
        items->screen->unkF00(items->screen, battle->unk560.unk9);
        break;
    case 4:
        if (items->screen->unkE0A == 0) {
            switch (battle->unk560.unk9) {
            case 0:
                battle->unk560.unk8 = 5;
                break;
            case 1:
                battle->unk560.unk8 = 6;
                break;
            case 2:
                battle->unk560.unk8 = 7;
                break;
            case 3:
                battle->unk560.unk8 = 15;
                break;
            case 4:
                items->screen->unkEE4(items->screen, 0x2C, 1, 0, 1);
                battle->unk560.unk8 = 8;
                break;
            }
        }
        break;
    case 5:
        battle->unk421 = 0x9B;
        battle->unk2F4 = 1;
        battle->unk560.unk8 = 11;
        break;
    case 6:
        battle->unk421 = 0xA8;
        battle->unk2F4 = 1;
        battle->unk560.unk8 = 12;
        break;
    case 7:
        battle->unk421 = 0x9C;
        battle->unk2F4 = 1;
        battle->unk560.unk8 = 13;
        break;
    case 8:
        if (items->screen->unkDFA == 2) {
            battle->unk560.unk8 = 9;
        }
        break;
    case 9:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
            items->screen->unkEEC(items->screen);
            battle->unk560.unk8 = 10;
        } else if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_UP))) |
                   (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_UP)))) {
            if (items->screen->unkDF4 != 0) {
                SOUND.playSound(0x8004513E);
            }
            items->screen->unkDF4 = 0;
        } else if ((PAD.getPressed(0) & (1 << PAD.getButtonBit(0, PAD_DOWN))) |
                   (PAD.getRepeated(0) & (1 << PAD.getButtonBit(0, PAD_DOWN)))) {
            if (items->screen->unkDF4 != 1) {
                SOUND.playSound(0x8004513E);
            }
            items->screen->unkDF4 = 1;
        } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            SOUND.playSound(0x800450BD);
            items->screen->unkDF4 = 1;
            items->screen->unkEEC(items->screen);
            items->screen->unkDF4 = 1;
            battle->unk560.unk8 = 10;
        }
        break;
    case 10:
        if (items->screen->unkDFA == 0) {
            if (items->screen->unkDF4 == 0) {
                result = 2;
            } else {
                battle->unk560.unk8 = 14;
            }
        }
        break;
    case 11:
    case 12:
    case 13:
    case 14:
        items->screen->unkEF4(items->screen, battle->unk560.unk9);
        battle->unk560.unk8 = 2;
        break;
    case 15:
        *(CardBattleSave *)&battle->unk420 = *(CardBattleSave *)battle->unk4F0;
        result = 1;
        *(CardScreenSave *)&items->screen->unkDE4 = CARDGAME_savedScreenState;
        battle->unk560.unk8 = 0;
        break;
    }
    return result;
}

s32 func_800A1CFC(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    func_8009D53C(battle);
    CARDGAME_updateCardAnims(battle, items);
    func_8009D470(battle, items);
    switch (battle->unk2F4) {
    case 0:
    default:
        if (CARDGAME_runPhase(battle, items)) {
            done = 1;
        }
        break;
    case 1:
        CARDGAME_runEffectStep(battle, items->screen);
        break;
    case 2:
        if (CARDGAME_resolveCard(battle, items)) {
            battle->unk2F4 = 0;
        }
        break;
    case 3:
        switch (CARDGAME_runBattleMenu(battle, items)) {
        case 1:
            battle->unk2F4 = 1;
            break;
        case 2:
            done = 1;
            break;
        }
        break;
    }
    return done;
}

/* The card battle task: sets up the battle and fades in, runs it (func_800A1CFC), then fades out and gives the player the item unk2EC for a win; result 2 once over */
void CARDGAME_updateBattle(CardBattle *battle, CardBattleItems *items) {
    TimLoader tim;
    CardFader *fader;

    switch (battle->state) {
    case 0:
    default:
        if (SOUND_STATE.isLoading() == 0) {
            FILE_CACHE.load(FILE_CARDGAME_TIMS);
            func_800A0A40(battle, items);
            CARDGAME_loadOpponent(battle, items);
            items->screen = CARDGAME_createScreen(battle->cards);
            items->unk0[0] = CARDGAME_startPreloader();
            items->screen->unkECC(items->screen);
            items->screen->unk5E = battle->unk2E9;
            items->screen->unk5C = battle->arg;
            initTimLoader(&tim);
            tim.setImagePos(0x280, 0);
            tim.loadArchive(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16));
            fader = CARDGAME_createFader(2);
            items->unk0[1] = fader;
            fader->setColor(fader, 0xFF, 0xFF, 0xFF);
            ((CardFader *)items->unk0[1])->start(items->unk0[1], 0, 0, 0, 100, 0);
            battle->setState(battle, 2);
            SOUND_STATE.playSound(0x609C0004);
        }
        break;
    case 1:
        if (func_800A1CFC(battle, items)) {
            fader = CARDGAME_createFader(2);
            items->unk0[1] = fader;
            fader->setColor(fader, 0, 0, 0);
            ((CardFader *)items->unk0[1])->start(items->unk0[1], 0xFF, 0xFF, 0xFF, 100, 0);
            battle->setState(battle, 2);
            battle->result = 1;
        }
        break;
    case 2:
        if (battle->substate == 0 && ((CardFader *)items->unk0[1])->isDone(items->unk0[1])) {
            ((CardFader *)items->unk0[1])->kill(items->unk0[1]);
            if (battle->result != 0) {
                if (battle->result != 2) {
                    if (battle->unk302 == 0) {
                        if (GAME.items[battle->unk2EC] < 99) {
                            GAME.items[battle->unk2EC]++;
                        }
                        PENDING_FLAG_10 = 1;
                    } else {
                        PENDING_FLAG_10 = 0;
                    }
                }
                battle->result = 2;
            } else {
                battle->setState(battle, 1);
            }
            battle->substate = 1;
        }
        break;
    case 3:
        if (battle->unk302 == 0) {
            SOUND_STATE.stopSound(0x6004001E);
        } else {
            SOUND_STATE.stopSound(0x609C0004);
        }
        break;
    }
}

CardBattle *CARDGAME_createBattle(s32 arg) {
    CardBattle *battle = createTask(CARDGAME_updateBattle, sizeof(CardBattle), 7 * 4);

    battle->unk810 = func_8009DF5C;
    battle->unk814 = func_8009DE0C;
    battle->unk818 = func_8009F664;
    battle->addCard = CARDGAME_addCard;
    battle->unk820 = CARDGAME_scoreHand;
    battle->arg = arg;
    SOUND.loadBank(0x27);
    return battle;
}

/* Draws the fader over RECT, in layer 0x100 */
void CARDGAME_drawFader(CardFader *fader, RECT rect) {
    Layer *layer = GFX.funcs.getLayer(0x100);
    u_long *ot = (u_long *)layer->getOtEntry(layer, 0);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    poly->r0 = fader->color[0];
    poly->g0 = fader->color[1];
    poly->b0 = fader->color[2];
    setlen(poly, 5);
    poly->code = 0x2A;
    poly->x0 = rect.x;
    poly->x1 = rect.x + rect.w;
    poly->x2 = rect.x;
    poly->x3 = rect.x + rect.w;
    poly->y0 = rect.y;
    poly->y1 = rect.y;
    poly->y2 = rect.y + rect.h;
    poly->y3 = rect.y + rect.h;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = ((fader->blend & 3) << 5) | 0xE1000205;
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

/* Moves the colour towards the target as the time runs out */
void CARDGAME_stepFader(CardFader *fader) {
    s32 i;

    fader->time -= GFX.funcs.getFrameTime();
    if (fader->time > 0) {
        for (i = 0; i < 3; i++) {
            fader->color[i] = fader->target[i] - (fader->target[i] - fader->from[i]) * fader->time / fader->duration;
        }
        return;
    }
    if (fader->killWhenDone != 0) {
        fader->mode = 2;
        return;
    }
    fader->mode = 0;
    fader->color[0] = fader->target[0];
    fader->color[1] = fader->target[1];
    fader->color[2] = fader->target[2];
}

/* Sets the colour at once */
void CARDGAME_setFaderColor(CardFader *fader, u8 r, u8 g, u8 b) {
    fader->color[0] = r;
    fader->color[1] = g;
    fader->color[2] = b;
}

/* Fades from the current colour to r, g, b in FRAMES vsyncs; the task
   ends at the end when KILLWHENDONE is set */
void CARDGAME_startFade(CardFader *fader, u8 r, u8 g, u8 b, s32 frames, s32 killWhenDone) {
    s32 i;

    for (i = 0; i < 3; i++) {
        fader->from[i] = fader->color[i];
    }
    fader->target[0] = r;
    fader->target[1] = g;
    fader->target[2] = b;
    fader->time = frames;
    fader->duration = frames;
    fader->mode = 1;
    fader->killWhenDone = killWhenDone;
}

/* 1 once the fade has reached its colour */
s32 CARDGAME_isFadeDone(CardFader *fader) {
    return fader->mode == 0;
}

/* Ends the task */
void CARDGAME_killFader(CardFader *fader) {
    fader->mode = 2;
}

void CARDGAME_tickFader(CardFader *fader) {
    switch (fader->state) {
    case 0:
    default:
        fader->nextState(fader);
        break;
    case 1:
        if (fader->mode == 1) {
            CARDGAME_stepFader(fader);
        }
        CARDGAME_drawFader(fader, CARDGAME_fadeRect);
        if (fader->mode == 2) {
            fader->setState(fader, 3);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/* Creates a fader, with the semi-transparency rate BLEND */
CardFader *CARDGAME_createFader(u8 blend) {
    CardFader *fader = createTask(CARDGAME_tickFader, sizeof(CardFader), 4);

    fader->setColor = CARDGAME_setFaderColor;
    fader->start = CARDGAME_startFade;
    fader->isDone = CARDGAME_isFadeDone;
    fader->blend = blend;
    fader->kill = CARDGAME_killFader;
    return fader;
}
