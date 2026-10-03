/* The sixth object of STSTATUS.PRO (see ststatus.c), the first screen
   (func_80091318): its rodata starts at 0x800829D0 (USA). */

#include "ststatus.h"

void func_8008DEF8(StatusScreen0 *screen, StatusScreen0Windows *windows);
void func_8008EE2C(StatusScreen0 *screen);
void func_8008F7A0(StatusScreen0 *screen, StatusScreen0Windows *windows);

/* Creates the first screen's windows */
void func_8008DEF8(StatusScreen0 *screen, StatusScreen0Windows *windows) {
    WindowPos *pos;
    s32 i;
    s32 j;

    pos = &STSTATUS_data.layout[11];
    windows->title = createTextWindow(screen->layer, 1, pos->x, pos->y);
    pos = &STSTATUS_data.layout[12];
    windows->help = createTextWindow(screen->layer, 1, pos->x, pos->y);
    windows->kind = createTextWindow(screen->layer, 1, pos->x, pos->y + 14);
    windows->answers[0] = createTextWindow(screen->layer, 1, pos->x + 0x10, pos->y + 14);
    windows->answers[1] = createTextWindow(screen->layer, 1, pos->x + 0x42, pos->y + 14);
    windows->answerCursor = createCursor(screen->layer, screen->depth - 1, pos->x, pos->y + 14);
    windows->answerCursor->setVisible(windows->answerCursor, 0);
    for (j = 0; j < 3; j++) {
        pos = &STSTATUS_data.layout[0];
        windows->pages[j].name = createTextWindow(screen->layer, 1, pos->x, pos->y + j * 46);
        pos = &STSTATUS_data.layout[1];
        for (i = 0; i < 5; i++, pos++) {
            windows->pages[j].labels[i] = createTextWindow(screen->layer, 3, pos->x, pos->y + j * 46);
        }
        pos = &STSTATUS_data.layout[6];
        for (i = 0; i < 5; i++, pos++) {
            windows->pages[j].values[i] = createTextWindow(screen->layer, 3, pos->x, pos->y + j * 46);
        }
    }
    windows->money = createTextWindow(screen->layer, 3, 0x42, 0xA6);
    windows->moneyLabel = createTextWindow(screen->layer, 3, 0x46, 0xA6);
    pos = &STSTATUS_data.layout[15];
    for (i = 0; i < 5; i++) {
        windows->options[i] = createTextWindow(screen->layer, 1, pos->x, pos->y + i * 14);
    }
    windows->optionCursor = createCursor(screen->layer, screen->depth - 1, 0xB0, screen->option * 14 + 0x31);
    windows->optionCursor->setVisible(windows->optionCursor, 0);
    windows->itemName = createTextWindow(screen->layer, 1, 0x25, 0xAE);
    windows->equippedLabel = createTextWindow(screen->layer, 1, 0xA1, 0xAF);
    windows->equipped = createTextWindow(screen->layer, 1, 0xE0, 0xAF);
    windows->ownedLabel = createTextWindow(screen->layer, 1, 0xEA, 0xAF);
    windows->owned = createTextWindow(screen->layer, 1, 0x128, 0xAF);
}

/* As func_800830AC */
void func_8008E2B0(StatusScreen *screen, StatusPagesB *windows, s32 member, s32 show) {
    PartnerTotals stats;
    WindowPos *layout;
    s32 id;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(member);
        GAME.funcs.computeStats(id, &stats);
        windows->pages[member].name->setString(windows->pages[member].name, GAME.funcs.getPartnerStats(id), -1);
        layout = &STSTATUS_data.layout[1];
        for (i = 0; i < 5; i++, layout++) {
            windows->pages[member].labels[i]->setString(windows->pages[member].labels[i],
                                                        FILE_CACHE.load(TEXT_FILE(0xB1)), layout->string);
        }
        for (i = 0; i < 5; i++) {
            windows->pages[member].values[i]->setNumber(windows->pages[member].values[i], 0, stats.stats[D_80099BB8[i]]);
            windows->pages[member].values[i]->setRightAlign(windows->pages[member].values[i], 1);
        }
    } else {
        windows->pages[member].name->setVisible(windows->pages[member].name, 0);
        for (i = 0; i < 5; i++) {
            windows->pages[member].labels[i]->setVisible(windows->pages[member].labels[i], 0);
        }
        for (i = 0; i < 5; i++) {
            windows->pages[member].values[i]->setVisible(windows->pages[member].values[i], 0);
        }
    }
}

void func_8008E4EC(StatusScreen0 *screen, StatusScreen0Windows *windows, s32 show) {
    if (show != 0) {
        windows->moneyLabel->setString(windows->moneyLabel, FILE_CACHE.load(TEXT_FILE(0xB1)), 5);
        windows->money->setNumber(windows->money, 0, GAME.money);
        windows->money->setRightAlign(windows->money, 1);
    } else {
        windows->moneyLabel->setVisible(windows->moneyLabel, 0);
        windows->money->setVisible(windows->money, 0);
    }
}

void func_8008E59C(StatusScreen0 *screen, StatusScreen0Windows *windows, s32 show) {
    WindowPos *layout;
    s32 i;

    if (show != 0) {
        layout = &STSTATUS_data.layout[15];
        for (i = 0; i < 5; i++) {
            windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0xB1)),
                                           layout->string + i);
        }
    } else {
        for (i = 0; i < 5; i++) {
            windows->options[i]->setVisible(windows->options[i], 0);
        }
    }
}

/* Shows or hides the chosen item's name and how many are equipped and owned */
void func_8008E668(StatusScreen0 *screen, s32 show) {
    StatusScreen0Windows *windows = screen->children;

    if (show) {
        windows->itemName->setString(windows->itemName, FILE_CACHE.load(TEXT_FILE(0x6B)), screen->item);
        windows->equippedLabel->setString(windows->equippedLabel, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x20);
        windows->equipped->setNumber(windows->equipped, 0, GAME.equippedItems[screen->item]);
        windows->equipped->setRightAlign(windows->equipped, 1);
        windows->ownedLabel->setString(windows->ownedLabel, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x16);
        windows->owned->setNumber(windows->owned, 0, GAME.items[screen->item]);
        windows->owned->setRightAlign(windows->owned, 1);
        screen->itemShown = 1;
    } else {
        windows->itemName->setVisible(windows->itemName, 0);
        windows->equippedLabel->setVisible(windows->equippedLabel, 0);
        windows->equipped->setVisible(windows->equipped, 0);
        windows->ownedLabel->setVisible(windows->ownedLabel, 0);
        windows->owned->setVisible(windows->owned, 0);
        screen->itemShown = 0;
    }
}

/* The help line: 1 the chosen item and the kind of a weapon, 2 a question
   with two answers, -2 hides the answers, -1 the kind, others all */
void func_8008E828(StatusScreen0 *screen, s32 mode) {
    StatusScreen0Windows *windows = screen->children;
    ItemInfo *info;
    u8 *data;

    if (mode == 1) {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x64)), screen->item);
        info = GET_ITEM[0](screen->item);
        if (info->type >= 2 && info->type <= 14) {
            data = info->data;
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099BCC[data[2]]);
        }
    } else if (mode == -1) {
        windows->kind->setVisible(windows->kind, 0);
    } else if (mode == 2) {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x31);
        windows->answers[0]->setString(windows->answers[0], FILE_CACHE.load(TEXT_FILE(0xB1)), 0x32);
        windows->answers[1]->setString(windows->answers[1], FILE_CACHE.load(TEXT_FILE(0xB1)), 0x33);
        windows->answerCursor->setVisible(windows->answerCursor, 1);
    } else if (mode == -2) {
        windows->answers[0]->setVisible(windows->answers[0], 0);
        windows->answers[1]->setVisible(windows->answers[1], 0);
        windows->answerCursor->setVisible(windows->answerCursor, 0);
    } else {
        windows->help->setVisible(windows->help, 0);
        windows->kind->setVisible(windows->kind, 0);
    }
}

void func_8008EA38(StatusScreen0 *screen, s32 show) {
    if (show != 0) {
        STSTATUS_data.funcs.startFade(&screen->fade, 1);
        return;
    }
    STSTATUS_data.funcs.startFade(&screen->fade, 0);
    func_8008E668(screen, 0);
    func_8008E828(screen, 0);
}

s32 func_8008EAAC(StatusScreen0 *screen) {
    return STSTATUS_data.funcs.updateFade(&screen->fade) != 0;
}

/* Uses the chosen item on the chosen party member */
void func_8008EAD4(StatusScreen0 *screen, StatusScreen0Windows *windows) {
    s32 amount = 0;
    StatusItemEffect *effect = (StatusItemEffect *)GET_ITEM[0](screen->item)->data;
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(screen->member));
    StatusStatItem *entry;
    s16 *values;
    s32 i;
    s32 result = 0;

    switch (effect->kind) {
    case 0:
        break;
    case 1:
        if ((s16)stats->stats[2] < (s16)stats->stats[3]) {
            stats->stats[2] += effect->amount;
            amount = effect->amount;
            if ((s16)stats->stats[2] > (s16)stats->stats[3]) {
                stats->stats[2] = stats->stats[3];
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x52);
                result = 2;
            } else {
                result = 1;
            }
        }
        break;
    case 17:
        if (stats->stats[1] < 99) {
            stats->stats[1] += effect->amount;
            amount = effect->amount;
            result = 1;
            if (stats->stats[1] > 99) {
                stats->stats[1] = 99;
            }
        }
        break;
    default:
        for (i = 0; D_80099BF0[i].kind != -1; i++) {
            entry = &D_80099BF0[i];
            if (effect->kind == entry->kind) {
                values = stats->stats;
                if (values[entry->stat] < entry->max) {
                    amount = RANDOM.next() % effect->amount + 1;
                    values[entry->stat] += amount;
                    if (values[entry->stat] > entry->max) {
                        values[entry->stat] = entry->max;
                    }
                    result = 1;
                }
                break;
            }
        }
        break;
    }
    if (result != 0) {
        if (result == 1) {
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), effect->kind + 0x52);
            windows->help->setNumber(windows->help, 1, amount);
        }
        GAME.items[screen->item]--;
        func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, screen->member, 1);
        SOUND.playSound(0x40014);
    } else {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x6A);
        SOUND.playSound(0x4001C);
    }
}

/* Draws the partners' portraits and frames, the item, the cursor and the help arrow */
void func_8008EE2C(StatusScreen0 *screen) {
    SpriteDrawer sprite;
    s32 id;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layer, screen->depth);
    if (GFX.funcs.getTime() - screen->frameTime >= 13) {
        screen->frameTime = GFX.funcs.getTime();
        for (i = 0; i < screen->count; i++) {
            id = GAME.funcs.getPartyMember(i);
            screen->frames[i]++;
            if (STSTATUS_data.partnerAnims[id].frames[screen->frames[i]] == -1 ||
                screen->frames[i] >= 7) {
                screen->frames[i] = 0;
            }
        }
    }
    for (i = 0; i < screen->count; i++) {
        if (screen->pageFades[i].level != 0) {
            if (screen->pageFades[i].level != 0x1000) {
                sprite.setScale(screen->pageFades[i].level, screen->pageFades[i].level, 0x1000);
                sprite.setPivot(0x7C, i * 0x2E + 0x27);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            id = GAME.funcs.getPartyMember(i);
            sprite.setTexture(0x280, 0x100);
            sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16),
                        STSTATUS_data.partnerAnims[id].frames[screen->frames[i]], 0x6B,
                        i * 0x2E + 0x13);
        }
    }
    sprite.setTexture(0x140, 0);
    for (i = 0; i < screen->count; i++) {
        if (screen->pageFades[i].level != 0) {
            /* both branches draw the frame's last part: the match depends on it */
            if (screen->pageFades[i].level != 0x1000) {
                sprite.setScale(screen->pageFades[i].level, 0x1000, 0x1000);
                sprite.setPivot(0, i * 0x2E + 0x25);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, i * 0x2E + 0x11);
                sprite.setScale(screen->pageFades[i].level, screen->pageFades[i].level, 0x1000);
                sprite.setPivot(0x7C, i * 0x2E + 0x27);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, i * 0x2E + 0x13);
                sprite.setScale(screen->pageFades[i].level, 0x1000, 0x1000);
                sprite.setPivot(0, i * 0x2E + 0x25);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, i * 0x2E + 0x11);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, i * 0x2E + 0x11);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, i * 0x2E + 0x13);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, i * 0x2E + 0x11);
            }
        }
    }
    if (screen->fades[0].level != 0) {
        if (screen->fades[0].level != 0x1000) {
            sprite.setScale(screen->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x19);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x18, 0x22, 0xD);
    }
    if (screen->fades2[0].level != 0) {
        if (screen->fades2[0].level != 0x1000) {
            sprite.setScale(screen->fades2[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x52);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x1C, 0xA8, 0x28);
    }
    if (screen->fades2[1].level != 0) {
        if (screen->fades2[1].level != 0x1000) {
            sprite.setScale(screen->fades2[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xA8);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x1A, 0, 0x9E);
    }
    if (screen->fades[1].level != 0) {
        if (screen->blink) {
            if (GFX.funcs.getTime() - screen->blinkTime >= 4) {
                screen->blinkTime = GFX.funcs.getTime();
                screen->blinkFrame++;
                if (screen->blinkFrame >= 5) {
                    screen->blinkFrame = 0;
                }
            }
            sprite.setTexture(0x140, 0);
            sprite.setClutRow(screen->blinkFrame);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xA, 0x123, 0xD6);
            sprite.setClutRow(0);
        }
        if (screen->fades[1].level != 0x1000) {
            sprite.setScale(screen->fades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xD3);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x20, 0, 0xC2);
    }
    if (screen->fade.level != 0) {
        if (screen->fade.level != 0x1000) {
            sprite.setScale(screen->fade.level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xB2);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            sprite.setTexture(0x140, 0);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(screen->item), 0x16, 0xAE);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x2F, 0xF, 0xA5);
    }
    if (screen->cursorShown) {
        if (GFX.funcs.getTime() - screen->cursorTime >= 9) {
            screen->cursorTime = GFX.funcs.getTime();
            screen->cursorFrame++;
            if (screen->cursorFrame >= 8) {
                screen->cursorFrame = 0;
            }
        }
        sprite.setScale(0x1000, 0x1000, 0x1000);
        sprite.setLayerId(screen->layer, screen->depth - 1);
        sprite.setClutRow(screen->cursorFrame);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x1E, 0, screen->member * 0x2E + 0x11);
    }
}

/* The first screen's update: opens the pages, picks an item list, then
   the party member to use the chosen item on, and closes them */
void func_8008F7A0(StatusScreen0 *screen, StatusScreen0Windows *windows) {
    s32 old;
    s32 done;
    s32 i;
    s32 j; /* case 12's: the match depends on it not being i */

    switch (screen->substate) {
    case 0:
    default:
        switch (screen->count) {
        case 1:
        default:
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 1);
            if (screen->step == 0) {
                STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            }
            STSTATUS_data.funcs.startFade(&screen->fades2[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades2[0], 1);
            break;
        case 2:
        case 3:
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 1);
            break;
        }
        screen->substate = screen->count;
        break;
    case 1:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        if (screen->step == 0) {
            STSTATUS_data.funcs.updateFade(&screen->fades[1]);
        }
        STSTATUS_data.funcs.updateFade(&screen->fades2[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x14);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x1B);
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_8008E4EC(screen, windows, 1);
            func_8008E59C(screen, windows, 1);
            windows->optionCursor->setVisible(windows->optionCursor, 1);
            screen->substate = 10;
        }
        break;
    case 2:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            if (screen->step == 0) {
                STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            }
            STSTATUS_data.funcs.startFade(&screen->fades2[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades2[0], 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x14);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            screen->substate = 4;
        }
        break;
    case 4:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (screen->step == 0) {
            STSTATUS_data.funcs.updateFade(&screen->fades[1]);
        }
        STSTATUS_data.funcs.updateFade(&screen->fades2[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            func_8008E59C(screen, windows, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x1B);
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_8008E4EC(screen, windows, 1);
            windows->optionCursor->setVisible(windows->optionCursor, 1);
            screen->substate = 10;
        }
        break;
    case 3:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades2[0], 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x14);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            screen->substate = 5;
        }
        break;
    case 5:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 1);
            if (screen->step == 0) {
                STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            }
            STSTATUS_data.funcs.startFade(&screen->fades2[1], 1);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            func_8008E59C(screen, windows, 1);
            screen->substate++;
        }
        break;
    case 6:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        if (screen->step == 0) {
            STSTATUS_data.funcs.updateFade(&screen->fades[1]);
        }
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[1])) {
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 2, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x1B);
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            windows->optionCursor->setVisible(windows->optionCursor, 1);
            func_8008E4EC(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 10:
        old = screen->option;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->option--;
            if (screen->option < 0) {
                screen->option = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->option++;
            if (screen->option >= 5) {
                screen->option = 4;
            }
        }
        if (old != screen->option) {
            SOUND.playSound(0x8004513E);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x1B);
            windows->optionCursor->setPos(windows->optionCursor, 0xB0, screen->option * 0xE + 0x31);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            screen->itemCount = ITEM_FUNCS->list(D_80099BA4[screen->option], screen->items);
            if (screen->itemCount <= 0) {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x64);
            } else {
                screen->substate = 11;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->substate = 0x32;
        }
        break;
    case 11:
        for (i = 0; i < screen->count; i++) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[i], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, i, 0);
        }
        STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
        windows->title->setVisible(windows->title, 0);
        windows->help->setVisible(windows->help, 0);
        windows->kind->setVisible(windows->kind, 0);
        STSTATUS_data.funcs.startFade(&screen->fades2[1], 0);
        windows->moneyLabel->setVisible(windows->moneyLabel, 0);
        windows->money->setVisible(windows->money, 0);
        STSTATUS_data.funcs.startFade(&screen->fades2[0], 0);
        for (i = 0; i < 5; i++) {
            windows->options[i]->setVisible(windows->options[i], 0);
        }
        windows->optionCursor->setVisible(windows->optionCursor, 0);
        screen->substate++;
        break;
    case 12:
        for (j = 0; j < screen->count; j++) {
            STSTATUS_data.funcs.updateFade(&screen->pageFades[j]);
        }
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades2[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            windows->panel = func_80092B0C(screen, screen->option, 0);
            func_8008EA38(screen, 1);
            screen->substate = 15;
        }
        break;
    case 15:
        if (func_8008EAAC(screen)) {
            screen->substate++;
        }
        break;
    case 0x10:
        if (windows->panel == NULL) {
            if (screen->unk7C == -1) {
                screen->substate = 0;
                screen->step = 1;
            } else if (screen->unk7C == -2) {
                screen->substate = 0x28;
            } else {
                screen->setSubstate(screen, 0x14);
            }
        }
        break;
    case 0x14:
        STSTATUS_data.funcs.startFade(&screen->pageFades[0], 1);
        STSTATUS_data.funcs.startFade(&screen->fades[0], 1);
        screen->substate++;
        break;
    case 0x15:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            if (screen->count != 1) {
                STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
                screen->substate++;
            } else {
                screen->substate = 0x18;
            }
        }
        break;
    case 0x16:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            if (screen->count == 2) {
                screen->substate = 0x18;
            } else {
                STSTATUS_data.funcs.startFade(&screen->pageFades[2], 1);
                screen->substate++;
            }
        }
        break;
    case 0x17:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[2])) {
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 2, 1);
            screen->substate++;
        }
        break;
    case 0x18:
        screen->cursorShown = 1;
        screen->substate++;
        break;
    case 0x19:
        old = screen->member;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->member--;
            if (screen->member < 0) {
                screen->member = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->member++;
            if (screen->member > screen->count - 1) {
                screen->member = screen->count - 1;
            }
        }
        if (old != screen->member) {
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            func_8008EA38(screen, 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
            func_8008EAD4(screen, windows);
            screen->substate = 0x64;
            screen->step = 0;
            screen->blink = 1;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->step = 1;
            screen->substate++;
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
        }
        break;
    case 0x1A:
        screen->cursorShown = 0;
        done = STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        if (func_8008EAAC(screen) && done) {
            screen->substate++;
        }
        break;
    case 0x1B:
        switch (screen->count) {
        case 1:
        default:
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            windows->title->setVisible(windows->title, 0);
            screen->substate = 0x1E;
            break;
        case 2:
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 0);
            screen->substate = 0x1D;
            break;
        case 3:
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 2, 0);
            screen->substate = 0x1C;
            break;
        }
        break;
    case 0x1C:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[2])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 0);
            screen->substate++;
        }
        break;
    case 0x1D:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            windows->title->setVisible(windows->title, 0);
            screen->substate++;
        }
        break;
    case 0x1E:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[0])) {
            if (screen->step == 0) {
                func_8008EA38(screen, 1);
            }
            windows->panel = func_80092B0C(screen, screen->option, screen->item);
            screen->substate = 15;
        }
        break;
    case 0x28:
        screen->state = 3;
        break;
    case 0x64:
        screen->cursorShown = 0;
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        if (func_8008EAAC(screen)) {
            screen->substate++;
        }
        break;
    case 0x65:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            screen->itemCount = ITEM_FUNCS->list(D_80099BA4[screen->option], screen->items);
            if (screen->itemCount <= 0) {
                screen->nextSubstate(screen);
                STSTATUS_data.funcs.startFade(&screen->fades[0], 1);
                STSTATUS_data.funcs.startFade(&screen->fades2[1], 1);
                STSTATUS_data.funcs.startFade(&screen->fades2[0], 1);
            } else {
                screen->substate = 0x1B;
            }
            screen->blink = 0;
        }
        break;
    case 0x66:
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades2[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x14);
            func_8008E59C(screen, windows, 1);
            func_8008E4EC(screen, windows, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x1B);
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            windows->optionCursor->setVisible(windows->optionCursor, 1);
            screen->substate = 10;
        }
        break;
    case 0x6E:
        windows->optionCursor->setStill(windows->optionCursor, 1);
        windows->optionCursor->setPalette(windows->optionCursor, 7);
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x64);
        screen->substate++;
        break;
    case 0x6F:
        if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            windows->optionCursor->setStill(windows->optionCursor, 0);
            windows->optionCursor->setPalette(windows->optionCursor, 0);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), screen->option + 0x1B);
            screen->substate = 10;
        }
        break;
    case 0x32:
        switch (screen->count) {
        case 1:
        default:
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades2[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades2[0], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            windows->title->setVisible(windows->title, 0);
            windows->help->setVisible(windows->help, 0);
            windows->kind->setVisible(windows->kind, 0);
            windows->moneyLabel->setVisible(windows->moneyLabel, 0);
            windows->money->setVisible(windows->money, 0);
            func_8008E59C(screen, windows, 0);
            break;
        case 2:
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades2[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades2[0], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 0);
            windows->help->setVisible(windows->help, 0);
            windows->kind->setVisible(windows->kind, 0);
            windows->moneyLabel->setVisible(windows->moneyLabel, 0);
            windows->money->setVisible(windows->money, 0);
            func_8008E59C(screen, windows, 0);
            break;
        case 3:
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades2[1], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 2, 0);
            windows->help->setVisible(windows->help, 0);
            windows->kind->setVisible(windows->kind, 0);
            windows->moneyLabel->setVisible(windows->moneyLabel, 0);
            windows->money->setVisible(windows->money, 0);
            break;
        }
        windows->optionCursor->setVisible(windows->optionCursor, 0);
        screen->substate = screen->count + 0x32;
        break;
    case 0x33:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades[1]);
        STSTATUS_data.funcs.updateFade(&screen->fades2[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            screen->state = 3;
        }
        break;
    case 0x34:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        STSTATUS_data.funcs.updateFade(&screen->fades[1]);
        STSTATUS_data.funcs.updateFade(&screen->fades2[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            screen->substate = 0x36;
        }
        break;
    case 0x36:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            screen->state = 3;
        }
        break;
    case 0x35:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        STSTATUS_data.funcs.updateFade(&screen->fades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            STSTATUS_data.funcs.startFade(&screen->fades2[0], 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 0);
            func_8008E59C(screen, windows, 0);
            screen->substate = 0x37;
        }
        break;
    case 0x37:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades2[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
            func_8008E2B0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            screen->substate++;
        }
        break;
    case 0x38:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            screen->state = 3;
        }
        break;
    }
}

void func_800911E4(StatusScreen0 *screen, StatusScreen0Windows *windows) {
    s32 duration;
    s32 i;

    switch (screen->state) {
    case 0:
    default:
        screen->nextState(screen);
        for (i = 0; i < 3; i++) {
            if (GAME.funcs.getPartyMember(i) >= 0) {
                screen->count++;
            }
        }
        for (i = 0; i < screen->count; i++) {
            screen->pageFades[i].duration = 10;
        }
        duration = 10; /* the match depends on this temporary */
        for (i = 1; i >= 0; i--) {
            screen->fades[i].duration = duration;
        }
        screen->fades2[0].duration = 10;
        screen->fades2[1].duration = 10;
        screen->fade.duration = 10;
        func_8008DEF8(screen, windows);
        break;
    case 1:
        func_8008F7A0(screen, windows);
        func_8008EE2C(screen);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_80091318(FieldMenuScreen *menu, s32 extra) {
    StatusScreen0 *screen = createTask(func_800911E4, sizeof(StatusScreen0), 0xD4);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}
