/* The third object of CARDGAME.PRO (see cardgame.c), from func_800941D0
   (USA): its rodata starts at 0x80082E30, a multiple of 8. */

#include "cardgame.h"

void func_800941D0(CardBattle *battle, CardScreen *screen, s32 arg2) {
    battle->unk424 = 0;
    screen->unkEE4(screen, arg2, 0, 0, 1);
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80094224);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80094550);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800946EC);

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
                func_80096504(screen, window, items->texts[7], TEXT_FILE(0x10), 1);
                break;
            case 2:
                func_80096504(screen, window, items->texts[9], TEXT_FILE(0x17), 0);
                break;
            case 3:
                func_80096504(screen, window, items->texts[8], TEXT_FILE(0x10), 0);
                break;
            case 5:
                if (window->unkC == 5) {
                    func_800965D8(screen, items, window, items->texts[5], TEXT_FILE(0x10));
                } else {
                    func_80096504(screen, window, items->texts[5], TEXT_FILE(0x10), window->unk10 != 0x24);
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
            func_80096504(screen, window, items->texts[9], TEXT_FILE(0x17), 0);
            break;
        case 3:
            func_80096504(screen, window, items->texts[8], TEXT_FILE(0x10), 0);
            break;
        case 4:
            if (window->unk10 == 0x1F4) {
                if (window->unk14[2] == 0) {
                    window->unk10 = 0x2A;
                    func_80096504(screen, window, items->texts[10], TEXT_FILE(0x10), 1);
                } else {
                    window->unk10 = 0x40;
                    func_8009642C(screen, items, window);
                    func_80096504(screen, window, items->texts[10], TEXT_FILE(0x10), 2);
                }
            } else {
                items->texts[0]->setVisible(items->texts[0], 0);
                items->texts[1]->setVisible(items->texts[1], 0);
                func_80096504(screen, window, items->texts[10], TEXT_FILE(0x1E), 0);
            }
            break;
        }
        break;
    case 3:
        switch (index) {
        case 0:
            items->texts[7]->setVisible(items->texts[7], 0);
            break;
        case 2:
            items->texts[9]->setVisible(items->texts[9], 0);
            break;
        case 3:
            items->texts[8]->setVisible(items->texts[8], 0);
            break;
        case 4:
            items->texts[0]->setVisible(items->texts[0], 0);
            items->texts[1]->setVisible(items->texts[1], 0);
            items->texts[10]->setVisible(items->texts[10], 0);
            break;
        case 5:
            items->texts[5]->setVisible(items->texts[5], 0);
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80096C78);

void func_8009747C(CardScreen *screen, CardScreenItems *items, s16 scale, s32 x, s32 y) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    drawer.setPivot(0, 0x86);
    drawer.setScale(scale, 0x1000, 0x1000);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 1, x, y);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80097548);

s32 CARDGAME_getHandOffset(s32 count, s32 index) {
    s32 step;

    if (count < 7) {
        step = 0x2900;
    } else {
        step = 0xF600 / count;
    }
    return step * index;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80097880);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800983D0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80098930);

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
    func_800983D0(&screen->panels[0], items, 0);
    func_800983D0(&screen->panels[1], items, 1);
    func_80097880(&screen->panels[0], items, 0);
    func_80097880(&screen->panels[1], items, 1);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80098F50);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800990F4);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80099780);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800998EC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80099C00);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80099E7C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_80099F7C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009A0BC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009A5CC);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009A7E4);

void func_8009A990(CardScreen *screen, CardSprite *sprite) {
    if (sprite->scaleX != 0 && sprite->scaleY != 0) {
        func_80099C00(screen, sprite);
        func_80099F7C(screen, sprite);
        func_80099E7C(screen, sprite);
        func_800998EC(screen, sprite);
        func_8009A5CC(screen, sprite);
        func_8009A0BC(screen, sprite);
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
        items->texts[3] = createTextWindow(0x100, 1, 0, 0);
        items->texts[4] = createTextWindow(0x100, 1, 0, 0);
        items->texts[5] = createTextWindow(0x100, 1, 0, 0);
        items->texts[6] = createTextWindow(0x100, 1, 0, 0);
        items->texts[6]->setLines(items->texts[6], 3);
        items->texts[7] = createTextWindow(0x100, 1, 0, 0);
        items->texts[8] = createTextWindow(0x100, 1, 0, 0);
        items->texts[9] = createTextWindow(0x100, 1, 0, 0);
        items->texts[10] = createTextWindow(0x100, 1, 0, 0);
        items->texts[10]->setLines(items->texts[10], 3);
        items->texts[11] = createTextWindow(0x100, 1, 0, 0);
        items->texts[11]->setLines(items->texts[11], 5);
        items->texts[12] = createTextWindow(0x100, 1, 0, 0);
        items->texts[12]->setLines(items->texts[12], 2);
        break;
    case 1:
        screen->time += GFX.funcs.getFrameTime();
        screen->unk54 = 0;
        func_80098E28(screen, items);
        func_80097548(screen, items);
        func_80096C78(screen, items);
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

void func_8009AFA8(CardScreen *screen, s32 arg1, u8 arg2, s16 arg3, s32 arg4) {
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

void func_8009B0C0(CardScreen *screen, s16 value) {
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

u8 CARDGAME_getCardColor(CardScreen *screen, s32 index) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009C628);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009C9B0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009CB30);

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

void func_8009CEB0(CardBattle *battle, s32 arg1, s32 side, s32 which) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009CF6C);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009D578);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009E020);

s32 func_8009E7D0(CardBattle *battle) {
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

s32 func_8009E820(CardBattle *battle) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009E8A8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009EA28);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009ECE8);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009F754);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009FA90);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009FBE4);

void func_8009FE5C(CardBattle *battle, CardBattleItems *items) {
    items->screen->unkEC8(items->screen);
    battle->unk498.unk5 = 1;
    battle->unk498.unk1 = 1;
    battle->unk2F9 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_8009FEA4);

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

void func_800A0A0C(CardBattle *battle) {
    s32 i = battle->unk2F6;

    battle->unk2F4 = 1;
    battle->unk421 = D_800A4C20[i].text;
    battle->unk2F7 = D_800A4C20[i].unk2;
}

void func_800A0A40(CardBattle *battle) {
    battle->sides[0].pile.unk11 = 0;
    battle->sides[1].pile.unk11 = 1;
    battle->result = 0;
    battle->unk302 = 1;
    battle->unk2F8 = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800A0A5C);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800A0D74);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800A1084);

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800A150C);

s32 func_800A1CFC(CardBattle *battle, CardBattleItems *items) {
    s32 done = 0;

    func_8009D53C(battle);
    func_8009D578(battle, items);
    func_8009D470(battle, items);
    switch (battle->unk2F4) {
    case 0:
    default:
        if (func_800A0A5C(battle, items)) {
            done = 1;
        }
        break;
    case 1:
        func_80083AB0(battle, items->screen);
        break;
    case 2:
        if (func_800A1084(battle, items)) {
            battle->unk2F4 = 0;
        }
        break;
    case 3:
        switch (func_800A150C(battle, items)) {
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame_3", func_800A1E04);

CardBattle *CARDGAME_createBattle(s32 arg) {
    CardBattle *battle = createTask(func_800A1E04, sizeof(CardBattle), 7 * 4);

    battle->unk810 = func_8009DF5C;
    battle->unk814 = func_8009DE0C;
    battle->unk818 = func_8009F664;
    battle->addCard = CARDGAME_addCard;
    battle->unk820 = func_800A2838;
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
