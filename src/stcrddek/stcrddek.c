#include "stcrddek.h"

extern KeyTabs STCRDDEK_keyPagesJp[];
extern KeyPage STCRDDEK_keyCharsJp[];
extern KeyTabs STCRDDEK_keyPages[];
extern KeyPage STCRDDEK_keyChars[];
extern TextStyle STCRDDEK_nameStyle;
extern NameKeyboard STCRDDEK_keyboard;
extern s32 STCRDDEK_nameAnims[];
extern BigKey STCRDDEK_bigKeys[];
extern s32 STCRDDEK_keyArrowCluts[];
extern s32 STCRDDEK_cursorCluts[];

void initCardDrawer(CardDrawer *obj);
void STCRDDEK_drawDeckCards(DeckCards *task);
void STCRDDEK_loadNextCard(DeckCards *task);
void STCRDDEK_createEditorWindows(DeckEditor *task, DeckEditorChildren *children);
void STCRDDEK_buildCardList(DeckEditor *task);
void STCRDDEK_drawEditor(DeckEditor *task);
void STCRDDEK_stepEditor(DeckEditor *task, DeckEditorChildren *children);
void STCRDDEK_initIdle(DeckIdle *task, void *children);
void STCRDDEK_showNameWindows(NameEntry *task, NameEntryWindows *windows, s32 show);
void STCRDDEK_drawKeyboard(NameEntry *task);
void STCRDDEK_updateKeyboard(NameEntry *task, NameEntryWindows *windows);
void STCRDDEK_updateNameEntry(NameEntry *task, NameEntryWindows *windows);
void STCRDDEK_updateScrollBar(ScrollBar *bar);
Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
ScrollBar *STCRDDEK_createScrollBar(void);
void STCRDDEK_createScreenWindows(DeckScreen *task, DeckScreenChildren *children);
void STCRDDEK_drawScreen(DeckScreen *task);
void STCRDDEK_countCardKinds(DeckScreen *task);
void STCRDDEK_stepScreen(DeckScreen *task, DeckScreenChildren *children);
void STCRDDEK_updateScreen(DeckScreen *task, DeckScreenChildren *children);
DeckScreen *STCRDDEK_createScreen(void);

void STCRDDEK_updateScene(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0xF000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)STCRDDEK_createScreen();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STCRDDEK_start(void) {
    return createTask(STCRDDEK_updateScene, sizeof(Task), 4);
}

void STCRDDEK_startFader(ScreenFade *task, s32 fadeIn, s32 duration) {
    task->setState(task, TASK_RUN);
    task->substate = 1;
    task->fadeIn = fadeIn;
    if (fadeIn == 0) {
        task->level = 0;
        task->levelStep = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->levelStep = -(0xFF00 / duration);
    }
}

void STCRDDEK_drawFader(ScreenFade *task) {
    Layer *layer = GFX.funcs.getLayer(task->layerId);
    u_long *ot = (u_long *)layer->getOtEntry(layer, task->depth);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->code = 0x2A;
    poly->r0 = poly->g0 = poly->b0 = task->level >> 8;
    poly->x0 = poly->x2 = 0;
    poly->x1 = poly->x3 = 320;
    poly->y0 = poly->y1 = 0;
    poly->y2 = poly->y3 = 256;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = 0xE1000245;
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void STCRDDEK_updateFader(ScreenFade *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        if (task->substate == 0) {
            break;
        }
        task->level += task->levelStep;
        if (task->fadeIn == 0) {
            if (task->level > 0xFF00) {
                task->level = 0xFF00;
                task->state = 2;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = 2;
        }
        /* fallthrough */
    case 2:
        STCRDDEK_drawFader(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *STCRDDEK_createFader(void) {
    ScreenFade *task = createTask(STCRDDEK_updateFader, sizeof(ScreenFade), 0);

    task->start = STCRDDEK_startFader;
    task->layerId = 0x1000;
    task->depth = 0;
    return task;
}

void STCRDDEK_drawDeckCards(DeckCards *task) {
    SpriteDrawer sprite;
    CardDrawer card;
    s32 i;
    s32 col;
    s32 row;
    s32 x;
    s32 y;
    s32 sheet;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0);
    sprite.setLayerId(task->layer, task->depth);
    initCardDrawer(&card);
    card.setImagePos(0x140, 0x100);
    card.setClutPos(0x300, 0x100);
    card.setLayer(task->layer, task->depth);
    for (i = 0; i < task->count; i++) {
        card.setCard(GAME.decks[task->editor->deck].cards[i]);
        /* the match depends on col holding the row first */
        col = i / 9;
        row = col;
        col = i - row * 9;
        sheet = FILE_CACHE.getEntry(STCRDDEK_SPRITES);
        x = col * 32 + 0x10;
        y = row * 32 + 0x3A;
        sprite.draw(sheet, card.card[0] + 0x52, x, y);
        card.setCell(col, row);
        card.draw(x, y);
    }
}

void STCRDDEK_loadNextCard(DeckCards *task) {
    CardDrawer card;
    s32 i;

    if (++task->count > 40) {
        task->state = TASK_DONE;
        task->count = 40;
        return;
    }
    initCardDrawer(&card);
    card.setCard(GAME.decks[task->editor->deck].cards[task->count - 1]);
    card.setImagePos(0x140, 0x100);
    card.setClutPos(0x300, 0x100);
    i = task->count - 1;
    card.setCell(i % 9, i / 9);
    card.loadImage();
}

void STCRDDEK_updateDeckCards(DeckCards *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->count = 0;
        break;
    case TASK_RUN:
        STCRDDEK_loadNextCard(task);
    case TASK_DONE:
        STCRDDEK_drawDeckCards(task);
        break;
    case TASK_KILL:
        break;
    }
}

DeckCards *STCRDDEK_createDeckCards(DeckEditor *editor) {
    DeckCards *task = createTask(STCRDDEK_updateDeckCards, sizeof(DeckCards), 0);

    task->layer = 0x1000;
    task->depth = 5;
    task->editor = editor;
    return task;
}

void STCRDDEK_createEditorWindows(DeckEditor *task, DeckEditorChildren *children) {
    s32 i;

    children->title = createTextWindow(task->layer, 1, 0xC1, 0x17);
    children->title->setDepth(children->title, task->depth - 1);
    children->deckName = createTextWindow(task->layer, 1, 0x15, 0x18);
    children->deckName->setDepth(children->deckName, task->depth - 1);
    for (i = 0; i < 6; i++) {
        children->kinds[i] = createTextWindow(task->layer, 1, 0x34 + i * 0x23, 0x29);
        children->kinds[i]->setDepth(children->kinds[i], task->depth - 1);
    }
    children->unk4 = createTextWindow(task->layer, 1, 0x96, 0xCC);
    children->cardName = createTextWindow(task->layer, 1, 0x96, 0xBD);
    children->unk28 = createTextWindow(task->layer, 1, 0x115, 0x26);
    children->unk2C = createTextWindow(task->layer, 1, 0x126, 0x26);
    children->unk40 = createTextWindow(task->layer, 1, 0x50, 0x17);
    children->unk30 = createTextWindow(task->layer, 1, 0xCE, 0x17);
    children->unk34 = createTextWindow(task->layer, 1, 0xF0, 0x17);
    children->unk38 = createTextWindow(task->layer, 1, 0xCE, 0x24);
    children->unk3C = createTextWindow(task->layer, 1, 0xF0, 0x24);
    for (i = 0; i < 8; i++) {
        children->lines[i].name = createTextWindow(task->layer, 1, 0xA3, 0x27 + i * 0xE);
        children->lines[i].name->setDepth(children->lines[i].name, task->depth - 1);
        children->lines[i].label = createTextWindow(task->layer, 1, 0x111, 0x27 + i * 0xE);
        children->lines[i].label->setDepth(children->lines[i].label, task->depth - 1);
        children->lines[i].count = createTextWindow(task->layer, 1, 0x120, 0x27 + i * 0xE);
        children->lines[i].count->setDepth(children->lines[i].count, task->depth - 1);
    }
    children->cursor = createCursor(task->layer, task->depth - 1, 0x89, 0x27);
    children->cursor->setVisible(children->cursor, 0);
    children->listCardName = createTextWindow(task->layer, 1, 0x88, 0xA1);
    children->unk48 = createTextWindow(task->layer, 1, 0x115, 0xA1);
    children->unk4C = createTextWindow(task->layer, 1, 0x126, 0xA1);
    children->unk60 = createTextWindow(task->layer, 1, 0x50, 0xB8);
    children->unk50 = createTextWindow(task->layer, 1, 0xCE, 0xB8);
    children->unk54 = createTextWindow(task->layer, 1, 0xF0, 0xB8);
    children->unk58 = createTextWindow(task->layer, 1, 0xCE, 0xC5);
    children->unk5C = createTextWindow(task->layer, 1, 0xF0, 0xC5);
    children->message = createTextWindow(task->layer, 1, 0x3E, 0x6B);
    children->message->setLines(children->message, 2);
}

void STCRDDEK_showEditorWindows(DeckEditor *task, DeckEditorChildren *children, s32 show) {
    CardDrawer card;
    s32 i;
    s32 id;

    if (show != 0) {
        children->title->setString(children->title, FILE_CACHE_LOAD[0](TEXT_FILE(0x33)), 4);
        children->deckName->setString(children->deckName, GAME.decks[task->deck].name, -1);
        for (i = 0; i < 6; i++) {
            children->kinds[i]->setNumber(children->kinds[i], 0, task->screen->kinds[task->deck][i]);
            children->kinds[i]->setRightAlign(children->kinds[i], 1);
        }
        id = task->blinkTime < 60 ? task->infoShown + 0x1C : 0x1F;
        children->unk4->setString(children->unk4, FILE_CACHE.load(TEXT_FILE(0x33)), id);
        id = GAME.decks[task->deck].cards[task->column + task->row * 9];
        children->cardName->setString(children->cardName, FILE_CACHE.load(TEXT_FILE(0x17)), id);
        if (task->infoShown) {
            initCardDrawer(&card);
            card.setCard(id);
            if (card.getKind()) {
                children->unk28->setVisible(children->unk28, 0);
                children->unk2C->setVisible(children->unk2C, 0);
                children->unk40->setString(children->unk40, FILE_CACHE.load(TEXT_FILE(0x1E)), id);
                children->unk30->setVisible(children->unk30, 0);
                children->unk34->setVisible(children->unk34, 0);
                children->unk38->setVisible(children->unk38, 0);
                children->unk3C->setVisible(children->unk3C, 0);
            } else {
                children->unk28->setString(children->unk28, FILE_CACHE.load(TEXT_FILE(0x33)), 8);
                children->unk2C->setNumber(children->unk2C, 0, card.card[5]);
                children->unk2C->setRightAlign(children->unk2C, 1);
                if (id == 0x45 || id == 0x70 || id == 0x9B || id == 0xC6 || id == 0xF1) {
                    children->unk40->setString(children->unk40, FILE_CACHE_LOAD[0](TEXT_FILE(0x1E)), id);
                    children->unk30->setVisible(children->unk30, 0);
                    children->unk34->setVisible(children->unk34, 0);
                    children->unk38->setVisible(children->unk38, 0);
                    children->unk3C->setVisible(children->unk3C, 0);
                } else {
                    children->unk40->setVisible(children->unk40, 0);
                    children->unk30->setString(children->unk30, FILE_CACHE.load(TEXT_FILE(0x33)), 0x11);
                    children->unk34->setNumber(children->unk34, 0, card.card[1]);
                    children->unk34->setRightAlign(children->unk34, 1);
                    children->unk38->setString(children->unk38, FILE_CACHE.load(TEXT_FILE(0x33)), 0x12);
                    children->unk3C->setNumber(children->unk3C, 0, card.card[2]);
                    children->unk3C->setRightAlign(children->unk3C, 1);
                }
            }
        } else {
            children->unk28->setVisible(children->unk28, 0);
            children->unk2C->setVisible(children->unk2C, 0);
            children->unk40->setVisible(children->unk40, 0);
            children->unk30->setVisible(children->unk30, 0);
            children->unk34->setVisible(children->unk34, 0);
            children->unk38->setVisible(children->unk38, 0);
            children->unk3C->setVisible(children->unk3C, 0);
        }
    } else {
        children->title->setVisible(children->title, 0);
        children->deckName->setVisible(children->deckName, 0);
        for (i = 0; i < 6; i++) {
            children->kinds[i]->setVisible(children->kinds[i], 0);
        }
        children->unk4->setVisible(children->unk4, 0);
        children->cardName->setVisible(children->cardName, 0);
        children->unk28->setVisible(children->unk28, 0);
        children->unk2C->setVisible(children->unk2C, 0);
        children->unk40->setVisible(children->unk40, 0);
        children->unk30->setVisible(children->unk30, 0);
        children->unk34->setVisible(children->unk34, 0);
        children->unk38->setVisible(children->unk38, 0);
        children->unk3C->setVisible(children->unk3C, 0);
    }
}

void STCRDDEK_showCardList(DeckEditor *task, DeckEditorChildren *children, s32 show) {
    s32 i;
    s32 id;

    if (show != 0) {
        for (i = 0; i < 8; i++) {
            id = task->list[task->listTop + i];
            if (id != 0) {
                children->lines[i].name->setString(children->lines[i].name, FILE_CACHE.load(TEXT_FILE(0x17)), id);
                children->lines[i].label->setString(children->lines[i].label, FILE_CACHE.load(TEXT_FILE(0x33)), 8);
                children->lines[i].count->setNumber(children->lines[i].count, 0, task->owned[id]);
                children->lines[i].count->setRightAlign(children->lines[i].count, 1);
            } else {
                children->lines[i].name->setVisible(children->lines[i].name, 0);
                children->lines[i].label->setVisible(children->lines[i].label, 0);
                children->lines[i].count->setVisible(children->lines[i].count, 0);
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            children->lines[i].name->setVisible(children->lines[i].name, 0);
            children->lines[i].label->setVisible(children->lines[i].label, 0);
            children->lines[i].count->setVisible(children->lines[i].count, 0);
        }
    }
}

void STCRDDEK_showListCard(DeckEditor *task, DeckEditorChildren *children, s32 show) {
    CardDrawer card;
    s32 id;

    if (show != 0) {
        id = task->list[task->listTop + task->listCursor];
        children->listCardName->setString(children->listCardName, FILE_CACHE.load(TEXT_FILE(0x17)), id);
        initCardDrawer(&card);
        card.setCard(id);
        if (card.getKind()) {
            children->unk48->setVisible(children->unk48, 0);
            children->unk4C->setVisible(children->unk4C, 0);
            children->unk60->setString(children->unk60, FILE_CACHE.load(TEXT_FILE(0x1E)), id);
            children->unk50->setVisible(children->unk50, 0);
            children->unk54->setVisible(children->unk54, 0);
            children->unk58->setVisible(children->unk58, 0);
            children->unk5C->setVisible(children->unk5C, 0);
        } else {
            children->unk48->setString(children->unk48, FILE_CACHE.load(TEXT_FILE(0x33)), 8);
            children->unk4C->setNumber(children->unk4C, 0, card.card[5]);
            children->unk4C->setRightAlign(children->unk4C, 1);
            if (id == 0x45 || id == 0x70 || id == 0x9B || id == 0xC6 || id == 0xF1) {
                children->unk60->setString(children->unk60, FILE_CACHE_LOAD[0](TEXT_FILE(0x1E)), id);
                children->unk50->setVisible(children->unk50, 0);
                children->unk54->setVisible(children->unk54, 0);
                children->unk58->setVisible(children->unk58, 0);
                children->unk5C->setVisible(children->unk5C, 0);
            } else {
                children->unk60->setVisible(children->unk60, 0);
                children->unk50->setString(children->unk50, FILE_CACHE.load(TEXT_FILE(0x33)), 0x11);
                children->unk54->setNumber(children->unk54, 0, card.card[1]);
                children->unk54->setRightAlign(children->unk54, 1);
                children->unk58->setString(children->unk58, FILE_CACHE.load(TEXT_FILE(0x33)), 0x12);
                children->unk5C->setNumber(children->unk5C, 0, card.card[2]);
                children->unk5C->setRightAlign(children->unk5C, 1);
            }
        }
    } else {
        children->listCardName->setVisible(children->listCardName, 0);
        children->unk48->setVisible(children->unk48, 0);
        children->unk4C->setVisible(children->unk4C, 0);
        children->unk60->setVisible(children->unk60, 0);
        children->unk50->setVisible(children->unk50, 0);
        children->unk54->setVisible(children->unk54, 0);
        children->unk58->setVisible(children->unk58, 0);
        children->unk5C->setVisible(children->unk5C, 0);
    }
}

INCLUDE_ASM("stcrddek/nonmatchings/stcrddek", STCRDDEK_buildCardList);

void STCRDDEK_drawEditor(DeckEditor *task) {
    SpriteDrawer sprite;
    CardDrawer card;
    s32 i;
    s32 id;
    s32 kind;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0);
    sprite.setLayerId(task->layer, task->depth - 2);
    if (task->cursorShown) {
        if (GFX.funcs.getTime() - task->cursorTime >= 5) {
            task->cursorTime = GFX.funcs.getTime();
            if (++task->cursorFrame >= 6) {
                task->cursorFrame = 0;
            }
        }
        sprite.setClutRow(STCRDDEK_cursorCluts[task->cursorFrame]);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x43, (task->column << 5) | 0x10, (task->row << 5) + 0x3A);
        sprite.setClutRow(0);
    }
    if (task->panels[1].level != 0) {
        if (task->panels[1].level != 0x1000) {
            sprite.setScale(task->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x25);
        }
        initCardDrawer(&card);
        id = GAME.decks[task->deck].cards[task->column + task->row * 9];
        card.setCard(id);
        kind = card.getKind();
        if (kind) {
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), kind + 0x11, 0x103, 0x24);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xD, 0xFC, 0x22);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xB, 0x4A, 0x12);
        } else {
            kind = card.card[0];
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), kind + 0x13, 0x103, 0x24);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xD, 0xFC, 0x22);
            if (id == 0x45 || id == 0x70 || id == 0x9B || id == 0xC6 || id == 0xF1) {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0xB, 0x4A, 0x12);
            } else {
                sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xC, 0xC7, 0x12);
            }
        }
    }
    if (task->panels[0].level != 0) {
        sprite.setScale(0x1000, task->panels[0].level, 0x1000);
        if (task->panels[0].level != 0x1000) {
            sprite.setPivot(0xA0, 0x74);
        }
        sprite.setLayerId(task->layer, task->depth);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x40, 0x10, 0x15);
    }
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0);
    sprite.setLayerId(task->layer, task->depth);
    if (task->panels[2].level != 0) {
        if (task->panels[2].level != 0x1000) {
            sprite.setScale(task->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x5C);
        } else {
            /* the match depends on i being set before initCardDrawer */
            i = 0;
            initCardDrawer(&card);
            for (; i < 8; i++) {
                id = task->list[task->listTop + i];
                if (id != 0) {
                    card.setCard(id);
                    if (card.getKind()) {
                        sprite.setClutRow(card.card[0] - 1);
                        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0x4B, 0x94, 0x27 + i * 14);
                    } else {
                        sprite.setClutRow(0);
                        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), card.card[0] + 0x4B, 0x94, 0x27 + i * 14);
                    }
                    sprite.setClutRow(0);
                    sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0x31, 0x94, 0x27 + i * 14);
                }
            }
            if (task->listCount >= 9) {
                if (GFX.funcs.getTime() - task->arrowTime >= 9) {
                    task->arrowTime = GFX.funcs.getTime();
                    task->arrowsShown = 1 - task->arrowsShown;
                }
                if (task->arrowsShown) {
                    if (task->listTop > 0) {
                        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x45, 0x126, 0x22);
                    }
                    if (task->listTop < task->listCount - 8) {
                        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x46, 0x126, 0x8F);
                    }
                }
            }
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x3F, 0x81, 0x1E);
    }
    if (task->panels[3].level != 0) {
        if (task->panels[3].level != 0x1000) {
            sprite.setScale(task->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x25);
        }
        initCardDrawer(&card);
        id = task->list[task->listTop + task->listCursor];
        card.setCard(id);
        kind = card.getKind();
        if (kind) {
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), kind + 0x11, 0x103, 0x9F);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xD, 0xFC, 0x9D);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xB, 0x4A, 0xB3);
        } else {
            kind = card.card[0];
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), kind + 0x13, 0x103, 0x9F);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xD, 0xFC, 0x9D);
            if (id == 0x45 || id == 0x70 || id == 0x9B || id == 0xC6 || id == 0xF1) {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0xB, 0x4A, 0xB3);
            } else {
                sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0xC, 0xC7, 0xB3);
            }
        }
        if (task->panels[3].level != 0x1000) {
            sprite.setPivot(0x140, 0xA8);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0xA, 0x82, 0x9D);
    }
    if (task->panels[4].level != 0) {
        if (task->panels[4].level != 0x1000) {
            sprite.setScale(0x1000, task->panels[4].level, 0x1000);
            sprite.setPivot(0, 0x78);
        }
        sprite.setLayerId(task->layer, task->depth - 3);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x36, 0, 0x64);
    }
}

void STCRDDEK_stepEditor(DeckEditor *task, DeckEditorChildren *children) {
    s32 prev;
#if VERSION_EU
    s32 prevTop;
#endif
    s32 i;
    s32 j;
    s32 id;
    s32 old;
    s32 tmp;

    switch (task->substate) {
    case 0:
    default:
        STCRDDEK_funcs.startFade(&task->panels[0], 1);
        task->substate++;
        break;
    case 1:
        if (STCRDDEK_funcs.updateFade(&task->panels[0])) {
            task->blinkTime = 0;
            STCRDDEK_showEditorWindows(task, children, 1);
            STCRDDEK_buildCardList(task);
            children->cards = STCRDDEK_createDeckCards(task);
            task->substate++;
        }
        break;
    case 2:
        if (children->cards->state == TASK_DONE) {
            task->cursorShown = 1;
            task->substate = 5;
        }
        break;
    case 5:
        prev = task->column + task->row * 9;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            if (--task->column < 0) {
                task->column = 0;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            if (task->row == 4) {
                if (++task->column >= 4) {
                    task->column = 3;
                }
            } else {
                if (++task->column >= 9) {
                    task->column = 8;
                }
            }
        }
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            if (--task->row < 0) {
                task->row = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            task->row++;
            if (task->column >= 4) {
                if (task->row >= 4) {
                    task->row = 3;
                }
            } else {
                if (task->row >= 5) {
                    task->row = 4;
                }
            }
        }
        STCRDDEK_showEditorWindows(task, children, 1);
        if (prev != task->column + task->row * 9) {
            SOUND.playSound(0x4001B);
        } else if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_PRESSED(PAD_R1)) {
            SOUND.playSound(0x4001B);
            task->substate = 10;
        } else if (PAD_PRESSED(PAD_CROSS)) {
            if (task->listCount != 0) {
                SOUND.playSound(0x4001C);
                task->substate = 20;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            task->substate = 50;
        } else if (PAD_PRESSED(PAD_CIRCLE)) {
            SOUND.playSound(0x800450BD);
            task->substate = 30;
        }
        break;
    case 10:
        task->cursorShown = 0;
        task->infoShown = 1 - task->infoShown;
        if (task->infoShown) {
            STCRDDEK_funcs.startFade(&task->panels[1], 1);
            task->substate = 11;
            task->step = 0;
        } else {
            STCRDDEK_showEditorWindows(task, children, 1);
            STCRDDEK_funcs.startFade(&task->panels[1], 0);
            task->substate = 11;
            task->step = 1;
        }
        break;
    case 11:
        if (STCRDDEK_funcs.updateFade(&task->panels[1])) {
            if (task->step == 0) {
                STCRDDEK_showEditorWindows(task, children, 1);
            }
            task->cursorShown = 1;
            task->setSubstate(task, 5);
        }
        break;
    case 20:
        children->cards->state = TASK_KILL;
        STCRDDEK_buildCardList(task);
        STCRDDEK_funcs.startFade(&task->panels[2], 1);
        while (task->list[task->listTop + task->listCursor] == 0) {
            if (--task->listTop < 0) {
                task->listTop = 0;
                if (--task->listCursor < 0) {
                    task->listCursor = 0;
                }
            }
        }
        task->cursorShown = 0;
        STCRDDEK_funcs.startFade(&task->panels[0], 0);
        if (task->infoShown) {
            task->panels[1].level = 0;
            task->infoShown = 0;
        }
        STCRDDEK_showEditorWindows(task, children, 0);
        task->substate++;
        break;
    case 21:
        if (STCRDDEK_funcs.updateFade(&task->panels[0])) {
            task->substate++;
        }
        break;
    case 22:
        if (STCRDDEK_funcs.updateFade(&task->panels[2])) {
            STCRDDEK_showCardList(task, children, 1);
            STCRDDEK_funcs.startFade(&task->panels[3], 1);
            task->substate++;
        }
        break;
    case 23:
        if (STCRDDEK_funcs.updateFade(&task->panels[3])) {
            if (task->listCount >= 9 && children->scrollBar == NULL) {
                children->scrollBar = STCRDDEK_createScrollBar();
                children->scrollBar->setX(children->scrollBar, 0x125, 0xC);
                children->scrollBar->setRange(children->scrollBar, 0x2A, 0x8F);
                children->scrollBar->setCount(children->scrollBar, 8, task->listCount);
                children->scrollBar->setPos(children->scrollBar, task->listCursor);
            }
            children->cursor->setPos(children->cursor, 0x89, task->listCursor * 14 + 0x27);
            children->cursor->setVisible(children->cursor, 1);
            STCRDDEK_showListCard(task, children, 1);
            task->substate++;
        }
        break;
    case 24:
        prev = task->listTop + task->listCursor;
#if VERSION_EU
        prevTop = task->listTop;
#endif
        if (task->listCount >= 9) {
            if ((!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) && PAD_PRESSED(PAD_L1)) ||
                (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) && PAD_REPEATED(PAD_L1))) {
                task->listTop -= 7;
                if (task->listTop < 0) {
                    task->listTop = 0;
                }
            } else if ((!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_PRESSED(PAD_R1)) ||
                       (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_REPEATED(PAD_R1))) {
                s32 k;

                for (k = 0; k < 7; k++) {
                    if (++task->listTop > task->listCount - 8) {
                        task->listTop = task->listCount - 8;
                        break;
                    }
                }
            }
        }
        if (prev == task->listTop + task->listCursor) {
            if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                if (--task->listCursor < 0) {
                    task->listCursor = 0;
                    if (--task->listTop < 0) {
                        task->listTop = 0;
                    }
                }
            } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                if (task->listCount >= 9) {
                    if (++task->listCursor >= 8) {
                        task->listCursor = 7;
                        if (++task->listTop > task->listCount - 8) {
                            task->listTop = task->listCount - 8;
                        }
                    }
                } else {
                    if (++task->listCursor > task->listCount - 1) {
                        task->listCursor = task->listCount - 1;
                    }
                }
            }
        }
#if VERSION_EU
        if (children->scrollBar != NULL && prevTop != task->listTop) {
            children->scrollBar->setPos(children->scrollBar, task->listTop);
        }
#endif
        if (prev != task->listTop + task->listCursor) {
            SOUND.playSound(0x8004513E);
            children->cursor->setPos(children->cursor, 0x89, task->listCursor * 14 + 0x27);
            STCRDDEK_showCardList(task, children, 1);
            STCRDDEK_showListCard(task, children, 1);
#if VERSION_US
            if (children->scrollBar != NULL) {
                children->scrollBar->setPos(children->scrollBar, task->listTop + task->listCursor);
            }
#endif
        } else if (PAD_PRESSED(PAD_CROSS)) {
            id = task->list[task->listTop + task->listCursor];
            old = GAME.decks[task->deck].cards[task->column + task->row * 9];
            SOUND.playSound(0x8004503C);
            if (id != old && GAME.cards[id] - task->owned[id] >= 4) {
                task->substate = 60;
            } else {
                GAME.decks[task->deck].cards[task->column + task->row * 9] = id;
                task->screen->countKinds(task->screen);
                task->substate++;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            task->substate++;
        }
        break;
    case 25:
        STCRDDEK_funcs.startFade(&task->panels[2], 0);
        STCRDDEK_showCardList(task, children, 0);
        STCRDDEK_funcs.startFade(&task->panels[3], 0);
        STCRDDEK_showListCard(task, children, 0);
        children->cursor->setVisible(children->cursor, 0);
        if (children->scrollBar != NULL) {
            children->scrollBar->state = TASK_KILL;
        }
        task->substate++;
        break;
    case 26:
        STCRDDEK_funcs.updateFade(&task->panels[2]);
        if (STCRDDEK_funcs.updateFade(&task->panels[3])) {
            task->listCursor = 0;
            task->listTop = 0;
            task->substate = 0;
        }
        break;
    case 30:
        children->cards->state = TASK_KILL;
        STCRDDEK_buildCardList(task);
        task->counter = 0;
        task->substate++;
        STCRDDEK_funcs.startFade(&task->panels[0], 0);
        task->cursorShown = 0;
        STCRDDEK_funcs.startFade(&task->panels[0], 0);
        task->panels[1].level = 0;
        task->infoShown = 0;
        STCRDDEK_showEditorWindows(task, children, 0);
        break;
    case 31:
        if (STCRDDEK_funcs.updateFade(&task->panels[3])) {
            task->substate++;
        }
        break;
    case 32:
        for (i = 0; i < 39; i++) {
            for (j = i + 1; j < 40; j++) {
                if (GAME.decks[task->deck].cards[i] > GAME.decks[task->deck].cards[j]) {
                    tmp = GAME.decks[task->deck].cards[i];
                    GAME.decks[task->deck].cards[i] = GAME.decks[task->deck].cards[j];
                    GAME.decks[task->deck].cards[j] = tmp;
                }
            }
        }
        task->substate = 0;
        break;
    case 50:
        children->cards->state = TASK_KILL;
        task->cursorShown = 0;
        STCRDDEK_funcs.startFade(&task->panels[0], 0);
        if (task->infoShown) {
            task->panels[1].level = 0;
            task->infoShown = 0;
        }
        STCRDDEK_showEditorWindows(task, children, 0);
        task->substate++;
        break;
    case 51:
        if (STCRDDEK_funcs.updateFade(&task->panels[0])) {
            task->state = TASK_KILL;
        }
        break;
    case 60:
        children->cursor->setPalette(children->cursor, 7);
        children->cursor->setStill(children->cursor, 1);
        STCRDDEK_funcs.startFade(&task->panels[4], 1);
        task->substate++;
        break;
    case 61:
        if (STCRDDEK_funcs.updateFade(&task->panels[4])) {
            children->message->setString(children->message, FILE_CACHE_LOAD[0](TEXT_FILE(0x33)), 0x1E);
            task->substate++;
        }
        break;
    case 62:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            children->message->setVisible(children->message, 0);
            STCRDDEK_funcs.startFade(&task->panels[4], 0);
            task->substate++;
        }
        break;
    case 63:
        if (STCRDDEK_funcs.updateFade(&task->panels[4])) {
            children->cursor->setPalette(children->cursor, 0);
            children->cursor->setStill(children->cursor, 0);
            task->substate = 23;
        }
        break;
    }
    task->blinkTime += GFX_FUNCS.getFrameTime();
    if (task->blinkTime > 120) {
        task->blinkTime -= 120;
    }
}

void STCRDDEK_updateEditor(DeckEditor *task, DeckEditorChildren *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        STCRDDEK_createEditorWindows(task, children);
        task->panels[0].duration = 10;
        task->panels[1].duration = 10;
        task->panels[2].duration = 10;
        task->panels[3].duration = 10;
        task->panels[4].duration = 10;
        break;
    case TASK_RUN:
        STCRDDEK_stepEditor(task, children);
        STCRDDEK_drawEditor(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

DeckEditor *STCRDDEK_createEditor(DeckScreen *screen, s32 deck) {
    DeckEditor *task = createTask(STCRDDEK_updateEditor, sizeof(DeckEditor), 0xD4);

    task->layer = 0x1000;
    task->depth = 6;
    task->screen = screen;
    task->deck = deck;
    return task;
}

void STCRDDEK_initIdle(DeckIdle *task, void *children) {
}

void STCRDDEK_drawIdle(DeckIdle *task) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(task->layer, task->depth);
}

void STCRDDEK_stepIdle(DeckIdle *task, void *children) {
    if (PAD_PRESSED(PAD_TRIANGLE)) {
        task->state = TASK_KILL;
    }
}

void STCRDDEK_updateIdle(DeckIdle *task, void *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        STCRDDEK_initIdle(task, children);
        break;
    case TASK_RUN:
        STCRDDEK_stepIdle(task, children);
        STCRDDEK_drawIdle(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

DeckIdle *STCRDDEK_createIdle(void *parent) {
    DeckIdle *task = createTask(STCRDDEK_updateIdle, sizeof(DeckIdle), 0);

    task->layer = 0x1000;
    task->depth = 6;
    task->parent = parent;
    return task;
}

void STCRDDEK_startTween(NameTween *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn != 0) {
        SOUND.playSound(0x40019);
        fade->value = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        SOUND.playSound(0x4001A);
        fade->value = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

s32 STCRDDEK_updateTween(NameTween *fade) {
    if (fade->active == 0) {
        return 1;
    }
    fade->value += fade->step;
    if (fade->step > 0) {
        if (fade->value > 0x1000) {
            fade->value = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->value < 0) {
        fade->value = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

void STCRDDEK_createNameWindows(NameEntry *task, NameEntryWindows *windows) {
    s32 i;

    windows->title = createTextWindow(task->layer, 1, 0x20, 0x1A);
    windows->title->setPalette(windows->title, 4);
    windows->name = createTextWindow(task->layer, 1, 0x4B, 0x40);
    windows->name->setSpacing(windows->name, 0x13, 0);
    windows->name->style = (u8 *)&STCRDDEK_nameStyle;
    for (i = 0; i < 3; i++) {
        windows->tabs[i] = createTextWindow(task->layer, 1, 0x2F + i * 0x4E, 0x5B);
        windows->tabs[i]->setDepth(windows->tabs[i], task->depth - 1);
        windows->tabs[i]->setLines(windows->tabs[i], 7);
        windows->tabs[i]->setSpacing(windows->tabs[i], 0xE, 0x12);
        windows->tabs[i]->style = (u8 *)&STCRDDEK_nameStyle;
    }
    windows->unk20 = createTextWindow(task->layer, 1, 0xCE, 0xC6);
    windows->unk24 = createTextWindow(task->layer, 1, 0xE1, 0xC6);
    windows->unk28 = createTextWindow(task->layer, 1, 0x13, 0x62);
    windows->unk28->setDepth(windows->unk28, task->depth - 1);
    windows->unk2C = createTextWindow(task->layer, 1, 0x123, 0x62);
    windows->unk2C->setDepth(windows->unk2C, task->depth - 1);
    windows->unk30 = createTextWindow(task->layer, 1, 0x3E, 0x72);
}

void STCRDDEK_showNameWindows(NameEntry *task, NameEntryWindows *windows, s32 show) {
    s32 i;

    if (show != 0) {
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x87)), 1);
        windows->name->setText(windows->name, task->text);
        windows->name->setPalette(windows->name, 1);
        for (i = 0; i < 3; i++) {
            windows->tabs[i]->setString(windows->tabs[i], FILE_CACHE.load(TEXT_FILE(0x87)),
                                        STCRDDEK_keyboard.tabTexts[task->page].texts[i]);
            windows->tabs[i]->setPalette(windows->tabs[i], 1);
        }
        windows->unk20->setString(windows->unk20, FILE_CACHE.load(TEXT_FILE(0x87)), 0xD);
        windows->unk20->setPalette(windows->unk20, 1);
        windows->unk24->setString(windows->unk24, FILE_CACHE.load(TEXT_FILE(0x87)), 0xE);
        windows->unk24->setPalette(windows->unk24, 1);
        if (STCRDDEK_keyboard.pageCount >= 2) {
            windows->unk28->setString(windows->unk28, FILE_CACHE.load(TEXT_FILE(0x87)), 0x10);
            windows->unk28->setPalette(windows->unk28, 1);
            windows->unk2C->setString(windows->unk2C, FILE_CACHE.load(TEXT_FILE(0x87)), 0x11);
            windows->unk2C->setPalette(windows->unk2C, 1);
        }
    } else {
        windows->title->setVisible(windows->title, 0);
        windows->name->setVisible(windows->name, 0);
        for (i = 0; i < 3; i++) {
            windows->tabs[i]->setVisible(windows->tabs[i], 0);
        }
        windows->unk20->setVisible(windows->unk20, 0);
        windows->unk24->setVisible(windows->unk24, 0);
        windows->unk28->setVisible(windows->unk28, 0);
        windows->unk2C->setVisible(windows->unk2C, 0);
    }
}

void STCRDDEK_drawKeyboard(NameEntry *task) {
    SpriteDrawer sprite;
    s32 i;
    s32 key;

    initSpriteDrawer(&sprite);
    sprite.setTexture(task->imageX, task->imageY);
    sprite.setLayerId(task->layer, task->depth);
    if (task->unkCC.value != 0) {
        if (task->active) {
            if (GFX.funcs.getTime() - task->keyTime >= 5) {
                task->keyTime = GFX.funcs.getTime();
                if (++task->keyFrame >= 4) {
                    task->keyFrame = 0;
                }
            }
            sprite.setClutRow(task->keyFrame);
            if (task->column < 10 || task->row < 3) {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), 0x27, task->column * 14 + 0x2F + task->column / 5 * 8,
                            task->row * 18 + 0x5A);
            } else {
                for (i = 0; STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column + i].kind != 1; i--) {
                }
                switch (task->column + i + task->row * 15) {
                case 0x64:
                default:
                    key = 0;
                    break;
                case 0x65:
                    key = 1;
                    break;
                case 0x46:
                    key = 2;
                    STCRDDEK_bigKeys[2].sprite = NAME_ENTRY_TEXT_SPRITE(0x3C);
                    break;
                case 0x55:
                    key = 3;
                    STCRDDEK_bigKeys[3].sprite = NAME_ENTRY_TEXT_SPRITE(0x44);
                    break;
                case 0x67:
                    key = 4;
                    STCRDDEK_bigKeys[4].sprite = NAME_ENTRY_TEXT_SPRITE(0x4C);
                    break;
                }
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), STCRDDEK_bigKeys[key].sprite, STCRDDEK_bigKeys[key].x,
                            STCRDDEK_bigKeys[key].y);
            }
            sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), 0x28, task->cursor * 19 + 0x4B, 0x40);
            sprite.setClutRow(0);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setScale(task->unkCC.value, 0x1000, 0x1000);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setPivot(0x18, 0x20);
        }
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x1D, 0x18, 0x15);
        if (task->mode != 2) {
            if (task->unkCC.value != 0x1000) {
                sprite.setPivot(0x20, 0x3F);
            }
            if (task->partner != -1) {
                if (GFX.funcs.getTime() - task->partnerTime >= 13) {
                    task->partnerTime = GFX.funcs.getTime();
                    if (++task->partnerFrame >= 7 || STCRDDEK_nameAnims[task->partner * 7 + task->partnerFrame] == -1) {
                        task->partnerFrame = 0;
                    }
                }
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), STCRDDEK_nameAnims[task->partner * 7 + task->partnerFrame],
                            0x22, 0x30);
            } else {
                sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x36, 0x20, 0x2E);
            }
            if (GFX.funcs.getTime() - task->clutTime >= 5) {
                task->clutTime = GFX.funcs.getTime();
                if (++task->clutRow >= 14) {
                    task->clutRow = 0;
                }
            }
            sprite.setLayerId(task->layer, task->depth - 1);
            sprite.setClutRow(task->clutRow);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x1F, 0x20, 0x2E);
            sprite.setClutRow(0);
            sprite.setLayerId(task->layer, task->depth);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x1E, 0x20, 0x2E);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setPivot(0x20, 0x49);
        }
        if (task->mode != 2) {
            if (NAME_ENTRY_JAPANESE) {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), 0x34, 0x4B, 0x40);
            } else {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), 0x37, 0x4B, 0x40);
            }
        } else {
            sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), 0x35, 0x4B, 0x40);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setScale(0x1000, task->unkCC.value, 0x1000);
        }
        if (STCRDDEK_keyboard.pageCount >= 2) {
            if (GFX.funcs.getTime() - task->arrowTime >= 7) {
                task->arrowTime = GFX.funcs.getTime();
                if (++task->arrowFrame >= 6) {
                    task->arrowFrame = 0;
                }
            }
            sprite.setClutRow(STCRDDEK_keyArrowCluts[task->arrowFrame]);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x32, 0xA, 0x5E);
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x33, 0x119, 0x5E);
            sprite.setClutRow(0);
        }
        sprite.setClutRow(4);
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x2C, 0xCB, 0xC3);
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x2D, 0xDE, 0xC3);
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), NAME_ENTRY_TEXT_SPRITE(0x3C), 0xCB, 0x99);
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), NAME_ENTRY_TEXT_SPRITE(0x44), 0xCB, 0xAE);
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), NAME_ENTRY_TEXT_SPRITE(0x4C), 0xF6, 0xC3);
        sprite.setClutRow(0);
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_KEY_SPRITES), 0x25, 0x1D, 0x54);
    }
    sprite.setLayerId(task->layer, task->depth - 1);
    if (task->unkDC.value != 0) {
        if (task->unkDC.value != 0x1000) {
            sprite.setScale(0x1000, task->unkDC.value, 0x1000);
            sprite.setPivot(0, 0x78);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_KEY_SPRITES), 0x26, 0, 0x64);
    }
}

void STCRDDEK_updateKeyboard(NameEntry *task, NameEntryWindows *windows) {
    s32 page;
    s32 newPage;
    s32 i;
    s32 key;
    s32 j;
    u16 c;
    u32 glyph; /* the match depends on this u32 copy of c, which orders the loads of the key's glyph */

    switch (task->substate) {
    case 0:
    default:
        STCRDDEK_startTween(&task->unkCC, 1);
        task->substate++;
        break;
    case 1:
        if (STCRDDEK_updateTween(&task->unkCC)) {
            STCRDDEK_showNameWindows(task, windows, 1);
            task->active = 1;
            task->substate++;
        }
        break;
    case 2:
        if (PAD_PRESSED(PAD_START)) {
            SOUND.playSound(0x4001B);
            task->column = 13;
            task->row = 6;
            break;
        }
        if (STCRDDEK_keyboard.pageCount >= 2) {
            page = task->page;
            if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) && PAD_PRESSED(PAD_L1)) {
                if (--task->page < 0) {
                    task->page = STCRDDEK_keyboard.pageCount - 1;
                }
            } else if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_PRESSED(PAD_R1)) {
                if (++task->page > STCRDDEK_keyboard.pageCount - 1) {
                    task->page = 0;
                }
            }
            if (page != task->page) {
                SOUND.playSound(0x4001B);
                STCRDDEK_showNameWindows(task, windows, 1);
                if (NAME_ENTRY_JAPANESE) {
                    newPage = task->page;
                    if (newPage == 0 || newPage == 1) {
                        while (STCRDDEK_keyboard.pages[newPage].cells[task->row][task->column].kind != 1) {
                            if (--task->column < 0) {
                                task->column = 14;
                            }
                        }
                    } else {
                        while (STCRDDEK_keyboard.pages[newPage].cells[task->row][task->column].kind == 0) {
                            if (--task->row < 0) {
                                task->row = 6;
                            }
                        }
                    }
                }
            }
        }
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            if (STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind < 0) {
                task->column += STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind;
            }
            do {
                if (--task->column < 0) {
                    task->column = 14;
                }
            } while (STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind != 1);
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            if (STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind < 0) {
                task->column += STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind;
            }
            do {
                if (++task->column >= 15) {
                    task->column = 0;
                }
            } while (STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind != 1);
            SOUND.playSound(0x4001B);
        }
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            do {
                if (--task->row < 0) {
                    task->row = 6;
                }
            } while (STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind == 0);
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            do {
                if (++task->row >= 7) {
                    task->row = 0;
                }
            } while (STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].kind == 0);
            SOUND.playSound(0x4001B);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            for (i = 0; STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column + i].kind != 1; i--) {
            }
            key = task->row * 15 + task->column + i;
            SOUND.playSound(0x4001C);
            switch (key) {
            case 0x64:
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
                break;
            case 0x65:
                if (++task->cursor > task->maxLength - 1) {
                    task->cursor = task->maxLength - 1;
                }
                break;
            case 0x46:
                if (task->cursor <= task->maxLength - 1 && task->text[task->cursor] == 0x4081) {
                    if (--task->cursor < 0) {
                        task->cursor = 0;
                    }
                }
                c = ((TextStyle *)windows->name->style)->iconMap[1].code;
                task->text[task->cursor] = (c >> 8) | ((c & 0xFF) << 8);
                windows->name->setText(windows->name, task->text);
                break;
            case 0x55:
                c = ((TextStyle *)windows->name->style)->iconMap[1].code;
                task->text[task->cursor] = (c >> 8) | ((c & 0xFF) << 8);
                if (++task->cursor > task->maxLength - 1) {
                    task->cursor = task->maxLength - 1;
                }
                windows->name->setText(windows->name, task->text);
                break;
            case 0x67:
                for (j = 0; j < task->maxLength; j++) {
                    if (task->text[j] != 0x4081 && task->text[j] != 0) {
                        for (j = 19; j >= 0; j--) {
                            if (task->text[j] != 0x4081) {
                                task->substate = 100;
                                return;
                            }
                            task->text[j] = 0;
                        }
                    }
                }
                task->substate = 20;
                break;
            default:
                glyph = ((TextStyle *)windows->name->style)
                            ->sjisMap[STCRDDEK_keyboard.pages[task->page].cells[task->row][task->column].code]
                            .code;
                task->text[task->cursor] = (glyph >> 8) | ((glyph & 0xFF) << 8);
                windows->name->setText(windows->name, task->text);
                if (++task->cursor > task->maxLength - 1) {
                    task->cursor = task->maxLength - 1;
                    task->column = 13;
                    task->row = 6;
                }
                break;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            if (task->cursor <= task->maxLength - 1 && task->text[task->cursor] == 0x4081) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            }
            c = ((TextStyle *)windows->name->style)->iconMap[1].code;
            task->text[task->cursor] = (c >> 8) | ((c & 0xFF) << 8);
            windows->name->setText(windows->name, task->text);
        }
        break;
    case 10:
        STCRDDEK_showNameWindows(task, windows, 0);
        STCRDDEK_startTween(&task->unkCC, 0);
        task->active = 0;
        task->substate++;
        break;
    case 11:
        if (STCRDDEK_updateTween(&task->unkCC)) {
            task->state = TASK_DONE;
        }
        break;
    case 20:
        task->active = 0;
        STCRDDEK_startTween(&task->unkDC, 1);
        task->substate++;
        break;
    case 21:
        if (STCRDDEK_updateTween(&task->unkDC)) {
            windows->unk30->setString(windows->unk30, FILE_CACHE_LOAD[0](TEXT_FILE(0x87)), 0x12);
            task->substate++;
        }
        break;
    case 22:
        if (PAD_PRESSED(PAD_CROSS)) {
            windows->unk30->setVisible(windows->unk30, 0);
            STCRDDEK_startTween(&task->unkDC, 0);
            task->substate++;
        }
        break;
    case 23:
        if (STCRDDEK_updateTween(&task->unkDC)) {
            task->active = 1;
            task->substate = 2;
        }
        break;
    case 100:
        break;
    }
}

void STCRDDEK_updateNameEntry(NameEntry *task, NameEntryWindows *windows) {
    TimLoader loader;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        initTimLoader(&loader);
        loader.setImagePos(task->imageX, task->imageY);
        loader.loadArchive(FILE_CACHE_GET_ENTRY[0](STCRDDEK_FILE_KEYBOARD << 16));
        if (NAME_ENTRY_JAPANESE) {
            STCRDDEK_keyboard.pageCount = 3;
            STCRDDEK_keyboard.tabTexts = STCRDDEK_keyPagesJp;
            STCRDDEK_keyboard.pages = STCRDDEK_keyCharsJp;
        } else {
            STCRDDEK_keyboard.pageCount = 1;
            STCRDDEK_keyboard.tabTexts = STCRDDEK_keyPages;
            STCRDDEK_keyboard.pages = STCRDDEK_keyChars;
        }
        task->unkBC.duration = 10;
        task->unkDC.duration = 10;
        task->unkCC.duration = 10;
        STCRDDEK_createNameWindows(task, windows);
        break;
    case TASK_RUN:
        STCRDDEK_updateKeyboard(task, windows);
        STCRDDEK_drawKeyboard(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void STCRDDEK_setNameVram(NameEntry *entry, s32 x, s32 y) {
    entry->imageX = x;
    entry->imageY = y;
}

void STCRDDEK_setName(NameEntry *entry, char *text) {
    TextTools tools;
    s32 i;

    initTextTools(&tools);
    tools.convert(entry->text, text, 0);
    for (i = strlen((char *)entry->text) >> 1; i < entry->maxLength; i++) {
        entry->text[i] = SJIS_SPACE;
    }
}

void STCRDDEK_getName(NameEntry *entry, char *dst) {
    TextTools tools;
    s32 i;

    for (i = 0; i < entry->maxLength * 2; i++) {
        dst[i] = 0;
    }
    for (i = entry->maxLength - 1; i >= 0; i--) {
        if (entry->text[i] != SJIS_SPACE) {
            break;
        }
        entry->text[i] = 0;
    }
    for (i = 0; i < entry->maxLength; i++) {
        if (entry->text[i] != SJIS_SPACE) {
            break;
        }
    }
    initTextTools(&tools);
    tools.convert(dst, &entry->text[i], 1);
}

void STCRDDEK_closeNameEntry(NameEntry *entry) {
    entry->substate = 10;
}

NameEntry *STCRDDEK_createNameEntry(char *text) {
    NameEntry *entry = createTask(STCRDDEK_updateNameEntry, sizeof(NameEntry), sizeof(NameEntryWindows));

    entry->getText = STCRDDEK_getName;
    entry->close = STCRDDEK_closeNameEntry;
    entry->layer = 0x1000;
    entry->depth = 3;
    entry->mode = 2;
    entry->maxLength = 10;
    entry->partner = -1;
    STCRDDEK_setName(entry, text);
    STCRDDEK_setNameVram(entry, 0x280, 0x100);
    return entry;
}

void STCRDDEK_setScrollBarX(ScrollBar *bar, s32 x, s32 width) {
    bar->x = x;
    bar->width = width;
}

void STCRDDEK_setScrollBarRange(ScrollBar *bar, s32 top, s32 bottom) {
    bar->top = top;
    bar->bottom = bottom;
    bar->hasRange = 1;
}

void STCRDDEK_setScrollBarCount(ScrollBar *bar, s32 pageSize, s32 count) {
    bar->pageSize = pageSize;
    bar->count = count;
    bar->hasCount = 1;
}

void STCRDDEK_setScrollBarPos(ScrollBar *bar, s32 pos) {
    bar->pos = pos;
}

void STCRDDEK_updateScrollBar(ScrollBar *bar) {
    Layer *layer;
    u_long *ot;
    POLY_F4 *poly;
    s32 range;
#if VERSION_US
    s32 pages;
#endif

    switch (bar->state) {
    case TASK_INIT:
    default:
        if (bar->hasRange != 0 && bar->hasCount != 0) {
#if VERSION_US
            bar->nextState(bar);
            pages = bar->count / bar->pageSize + (bar->count % bar->pageSize != 0);
            range = (bar->bottom - bar->top) << 8;
            bar->size = range / pages;
            bar->posStep = range / bar->count;
#elif VERSION_EU
            range = (bar->bottom - bar->top) << 8;
            bar->size = range / bar->count * bar->pageSize;
            bar->posStep = range / bar->count;
            bar->nextState(bar);
#endif
        }
        break;
    case TASK_RUN:
        layer = GFX.funcs.getLayer(bar->layer);
        ot = (u_long *)layer->getOtEntry(layer, bar->depth);
        poly = GFX.funcs.getPrim();
        if (bar->pos < bar->count - 1) {
            bar->y = bar->top + ((bar->pos * bar->posStep) >> 8);
            if (bar->bottom - (bar->size >> 8) < bar->y) {
                bar->y = bar->bottom - (bar->size >> 8);
            }
        } else {
            bar->y = bar->bottom - (bar->size >> 8);
        }
        setlen(poly, 5);
        poly->code = 0x28;
        poly->r0 = poly->g0 = poly->b0 = 0xFF;
        poly->x0 = poly->x2 = bar->x;
        poly->x1 = poly->x3 = bar->x + bar->width;
        poly->y0 = poly->y1 = bar->y;
        poly->y2 = poly->y3 = bar->y + (bar->size >> 8);
        addPrim(ot, poly);
        GFX.funcs.setPrim(poly + 1);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

ScrollBar *STCRDDEK_createScrollBar(void) {
    ScrollBar *bar = createTask(STCRDDEK_updateScrollBar, sizeof(ScrollBar), 0);

    bar->setX = STCRDDEK_setScrollBarX;
    bar->setRange = STCRDDEK_setScrollBarRange;
    bar->setCount = STCRDDEK_setScrollBarCount;
    bar->setPos = STCRDDEK_setScrollBarPos;
    bar->layer = 0x1000;
    bar->depth = 3;
    return bar;
}

INCLUDE_ASM("stcrddek/nonmatchings/stcrddek", STCRDDEK_createScreenWindows);

void STCRDDEK_showDeckRow(DeckScreen *task, DeckScreenChildren *children, s32 deck, s32 show) {
    s32 i;

    if (show != 0) {
        children->rows[deck].name->setString(children->rows[deck].name, GAME.decks[deck].name, -1);
        for (i = 0; i < 6; i++) {
            children->rows[deck].counts[i]->setNumber(children->rows[deck].counts[i], 0, task->kinds[deck][i]);
            children->rows[deck].counts[i]->setRightAlign(children->rows[deck].counts[i], 1);
        }
    } else {
        children->rows[deck].name->setVisible(children->rows[deck].name, 0);
        for (i = 0; i < 6; i++) {
            children->rows[deck].counts[i]->setVisible(children->rows[deck].counts[i], 0);
        }
    }
}

void STCRDDEK_drawScreen(DeckScreen *task) {
    SpriteDrawer sprite;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layer, task->depth);
    sprite.setTexture(0x280, 0);
    if (task->tick) {
        task->scroll = ++task->scroll < 96 ? task->scroll : 0;
        task->tick = 0;
    } else {
        task->tick = 1;
    }
    sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 8, task->scroll, task->scroll);
    sprite.setLayerId(task->layer, task->depth - 1);
    if (task->panels[0].level != 0) {
        if (task->panels[0].level != 0x1000) {
            sprite.setScale(task->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x22);
        }
        sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0x30, 0x7B, 0x1C);
    }
    for (i = 0; i < 3; i++) {
        if (task->rowPanels[i].level != 0) {
            sprite.setScale(task->rowPanels[i].level, 0x1000, 0x1000);
            if (task->rowPanels[i].level != 0x1000) {
                sprite.setPivot(0x17, 0x63 + i * 0x2D);
            }
            sprite.draw(FILE_CACHE.getEntry(STCRDDEK_SPRITES), 0x41, 0x17, 0x50 + i * 0x2D);
        }
    }
    if (task->panels[1].level != 0) {
        sprite.setScale(task->panels[1].level, 0x1000, 0x1000);
        if (task->panels[1].level != 0x1000) {
            sprite.setPivot(0x140, 0x37);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x2D, 0x92, 0x1C);
    }
    if (task->panels[2].level != 0) {
        sprite.setLayerId(task->layer, task->depth - 2);
        sprite.setScale(0x1000, task->panels[2].level, 0x1000);
        if (task->panels[2].level != 0x1000) {
            sprite.setPivot(0x17, task->deck * 0x2D + 0x63);
        }
        if (task->chosen == 0) {
            if (GFX.funcs.getTime() - task->cursorTime >= 5) {
                task->cursorTime = GFX.funcs.getTime();
                if (++task->cursorFrame >= 16) {
                    task->cursorFrame = 0;
                }
            }
            sprite.setClutRow(task->cursorFrame);
            sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x42, 0x17, task->deck * 0x2D + 0x50);
        } else {
            sprite.draw(FILE_CACHE_GET_ENTRY[0](STCRDDEK_SPRITES), 0x44, 0x17, task->deck * 0x2D + 0x50);
        }
    }
}

void STCRDDEK_countCardKinds(DeckScreen *task) {
    CardDrawer card;
    s32 d;
    s32 i;

    initCardDrawer(&card);
    for (d = 0; d < 3; d++) {
        for (i = 0; i < 6; i++) {
            task->kinds[d][i] = 0;
        }
        for (i = 0; i < 40; i++) {
            card.setCard(GAME.decks[d].cards[i]);
            task->kinds[d][card.card[0] - 1]++;
        }
    }
}

void STCRDDEK_stepScreen(DeckScreen *task, DeckScreenChildren *children) {
    s32 prevDeck;
    s32 prevChoice;
    ScreenFade *fader;

    switch (task->substate) {
    case 0:
    default:
        STCRDDEK_countCardKinds(task);
        STCRDDEK_funcs.startFade(&task->panels[0], 1);
        STCRDDEK_funcs.startFade(&task->rowPanels[0], 1);
        task->chosen = 0;
        task->substate++;
        break;
    case 1:
        STCRDDEK_funcs.updateFade(&task->panels[0]);
        if (STCRDDEK_funcs.updateFade(&task->rowPanels[0])) {
            children->title->setString(children->title, FILE_CACHE_LOAD[0](TEXT_FILE(0x33)), 0x19);
            STCRDDEK_showDeckRow(task, children, 0, 1);
            STCRDDEK_funcs.startFade(&task->rowPanels[1], 1);
            task->substate++;
        }
        break;
    case 2:
        if (STCRDDEK_funcs.updateFade(&task->rowPanels[1])) {
            STCRDDEK_showDeckRow(task, children, 1, 1);
            STCRDDEK_funcs.startFade(&task->rowPanels[2], 1);
            STCRDDEK_funcs.startFade(&task->panels[2], 1);
            task->substate++;
        }
        break;
    case 3:
        STCRDDEK_funcs.updateFade(&task->panels[2]);
        if (STCRDDEK_funcs.updateFade(&task->rowPanels[2])) {
            STCRDDEK_showDeckRow(task, children, 2, 1);
            task->substate++;
        }
        break;
    case 4:
        prevDeck = task->deck;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            if (--task->deck < 0) {
                task->deck = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (++task->deck >= 3) {
                task->deck = 2;
            }
        }
        if (prevDeck != task->deck) {
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            task->substate = 10;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            task->setSubstate(task, 100);
        }
        break;
    case 10:
        task->chosen = 1;
        children->title->setVisible(children->title, 0);
        STCRDDEK_funcs.startFade(&task->panels[0], 0);
        task->substate++;
        break;
    case 11:
        if (STCRDDEK_funcs.updateFade(&task->panels[0])) {
            children->title->setVisible(children->title, 0);
            STCRDDEK_funcs.startFade(&task->panels[1], 1);
            task->substate++;
        }
        break;
    case 12:
        if (STCRDDEK_funcs.updateFade(&task->panels[1])) {
            task->renaming = 0;
            children->cursor->setPos(children->cursor, 0x9A, 0x23);
            children->cursor->setVisible(children->cursor, 1);
            children->unk5C[0]->setString(children->unk5C[0], FILE_CACHE.load(TEXT_FILE(0x33)), 0x1A);
            children->unk5C[1]->setString(children->unk5C[1], FILE_CACHE.load(TEXT_FILE(0x33)), 0x1B);
            task->substate++;
        }
        break;
    case 13:
        prevChoice = task->renaming;
        if (PAD_PRESSED(PAD_UP)) {
            task->renaming = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            task->renaming = 1;
        }
        if (prevChoice != task->renaming) {
            SOUND.playSound(0x8004513E);
            children->cursor->setPos(children->cursor, 0x9A, task->renaming * 14 + 0x23);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            task->setSubstate(task, 50);
            task->step = 1;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            task->substate = 15;
        }
        break;
    case 15:
        children->cursor->setVisible(children->cursor, 0);
        children->unk5C[0]->setVisible(children->unk5C[0], 0);
        children->unk5C[1]->setVisible(children->unk5C[1], 0);
        STCRDDEK_funcs.startFade(&task->panels[1], 0);
        task->substate++;
        break;
    case 16:
        if (STCRDDEK_funcs.updateFade(&task->panels[1])) {
            STCRDDEK_funcs.startFade(&task->panels[0], 1);
            task->substate++;
        }
        break;
    case 17:
        if (STCRDDEK_funcs.updateFade(&task->panels[0])) {
            children->title->setString(children->title, FILE_CACHE_LOAD[0](TEXT_FILE(0x33)), 0x19);
            task->chosen = 0;
            task->setSubstate(task, 4);
        }
        break;
    case 50:
        if (task->step) {
            children->cursor->setStill(children->cursor, 1);
            children->cursor->setPalette(children->cursor, 7);
        }
        STCRDDEK_funcs.startFade(&task->panels[2], 0);
        STCRDDEK_funcs.startFade(&task->rowPanels[2], 0);
        STCRDDEK_showDeckRow(task, children, 2, 0);
        task->substate++;
        break;
    case 51:
        STCRDDEK_funcs.updateFade(&task->panels[2]);
        if (STCRDDEK_funcs.updateFade(&task->rowPanels[2])) {
            STCRDDEK_funcs.startFade(&task->rowPanels[1], 0);
            STCRDDEK_showDeckRow(task, children, 1, 0);
            task->substate++;
        }
        break;
    case 52:
        if (STCRDDEK_funcs.updateFade(&task->rowPanels[1])) {
            if (task->step) {
                children->cursor->setStill(children->cursor, 0);
                children->cursor->setPalette(children->cursor, 0);
                children->cursor->setVisible(children->cursor, 0);
                children->unk5C[0]->setVisible(children->unk5C[0], 0);
                children->unk5C[1]->setVisible(children->unk5C[1], 0);
                STCRDDEK_funcs.startFade(&task->panels[1], 0);
            } else {
                children->title->setVisible(children->title, 0);
                STCRDDEK_funcs.startFade(&task->panels[0], 0);
            }
            STCRDDEK_funcs.startFade(&task->rowPanels[0], 0);
            STCRDDEK_showDeckRow(task, children, 0, 0);
            task->substate++;
        }
        break;
    case 53:
        if (task->step) {
            STCRDDEK_funcs.updateFade(&task->panels[1]);
        } else {
            STCRDDEK_funcs.updateFade(&task->panels[0]);
        }
        if (STCRDDEK_funcs.updateFade(&task->rowPanels[0])) {
            task->substate++;
        }
        break;
    case 54:
        if (task->step) {
            if (task->renaming == 0) {
                children->name = (NameEntry *)STCRDDEK_createEditor(task, task->deck);
            } else {
                children->name = STCRDDEK_createNameEntry(GAME.decks[task->deck].name);
            }
            task->setState(task, TASK_DONE);
        } else {
            task->state = TASK_KILL;
        }
        break;
    case 100:
        children->fader = fader = STCRDDEK_createFader();
        fader->start(fader, 0, 10);
        task->substate++;
        break;
    case 101:
        if (children->fader->state == 2) {
            task->substate = 54;
        }
        break;
    }
}

void STCRDDEK_updateScreen(DeckScreen *task, DeckScreenChildren *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        switch (task->substate) {
        case 0:
        default:
            STCRDDEK_funcs.loadFiles();
            task->substate++;
            break;
        case 1:
            if (STCRDDEK_funcs.filesLoading() == 0) {
                STCRDDEK_createScreenWindows(task, children);
                task->panels[0].duration = 10;
                task->rowPanels[0].duration = 10;
                task->rowPanels[1].duration = 10;
                task->rowPanels[2].duration = 10;
                task->panels[1].duration = 10;
                task->panels[2].duration = 10;
                task->nextState(task);
            }
            break;
        }
        break;
    case TASK_RUN:
        STCRDDEK_stepScreen(task, children);
        STCRDDEK_drawScreen(task);
        break;
    case TASK_DONE:
        if (task->renaming != 0) {
            switch (task->substate) {
            case 0:
            default:
                if (children->name->substate == 100) {
                    children->name->getText(children->name, GAME.decks[task->deck].name);
                    children->name->close(children->name);
                    task->substate++;
                }
                break;
            case 1:
                if (children->name->state == TASK_DONE) {
                    children->name->state = TASK_KILL;
                    task->setState(task, TASK_RUN);
                }
                break;
            }
        } else if (children->name == NULL) {
            task->setState(task, TASK_RUN);
        }
        STCRDDEK_drawScreen(task);
        break;
    case TASK_KILL:
        GAME.funcs.requestMode(GAME.funcs.getPrevMode(), GAME.funcs.getModeArg());
        break;
    }
}

DeckScreen *STCRDDEK_createScreen(void) {
    DeckScreen *task = createTask(STCRDDEK_updateScreen, sizeof(DeckScreen), 0x6C);

    task->countKinds = STCRDDEK_countCardKinds;
    task->layer = 0x1000;
    task->depth = 7;
    return task;
}

void STCRDDEK_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0);
    loader.loadArchive(FILE_CACHE.getEntry(STCRDDEK_IMAGES));
    FILE_CACHE.request(STCRDDEK_FILE_CARDS);
    FILE_CACHE.request(STCRDDEK_FILE_CARDS + 1);
    FILE_CACHE.request(STCRDDEK_FILE_CARDS + 2);
    FILE_CACHE.request(STCRDDEK_FILE_CARDS + 3);
    FILE_CACHE.request(STCRDDEK_FILE_CARDS + 4);
    FILE_CACHE.request(TEXT_FILE(0x17));
    FILE_CACHE.request(TEXT_FILE(0x1E));
    FILE_CACHE.request(TEXT_FILE(0x33));
    FILE_CACHE.request(TEXT_FILE(0x87));
    FILE_CACHE.request(STCRDDEK_FILE_KEYBOARD);
}

s32 STCRDDEK_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x17)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x1E)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x33)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x87)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(STCRDDEK_FILE_KEYBOARD) != 0;
}

void STCRDDEK_startFade(PanelAnim *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn != 0) {
        SOUND.playSound(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        SOUND.playSound(0x4001A);
        fade->level = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

s32 STCRDDEK_updateFade(PanelAnim *fade) {
    if (fade->active == 0) {
        return 1;
    }
    fade->level += fade->step;
    if (fade->step > 0) {
        if (fade->level > 0x1000) {
            fade->level = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->level < 0) {
        fade->level = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

void STCRDDEK_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STCRDDEK_updateLerp(MenuLerp *lerp) {
    if (lerp->active == 0) {
        return 1;
    }
    lerp->fixed += lerp->step;
    lerp->value = lerp->fixed >> 8;
    if (lerp->step > 0) {
        if (lerp->target < lerp->value) {
            lerp->value = lerp->target;
            lerp->active = 0;
            return 1;
        }
    } else if (lerp->value < lerp->target) {
        lerp->value = lerp->target;
        lerp->active = 0;
        return 1;
    }
    return 0;
}

extern s32 D_8008995C[];
extern s32 D_8008A340[];
void STCRDDEK_loadFiles(void);
s32 STCRDDEK_filesLoading(void);
void STCRDDEK_startFade(PanelAnim *fade, s32 fadeIn);
s32 STCRDDEK_updateFade(PanelAnim *fade);
void STCRDDEK_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames);
s32 STCRDDEK_updateLerp(MenuLerp *lerp);

s32 STCRDDEK_cursorCluts[] = {
    0, 1, 2, 3,
    2, 1,
};
/* the European version's differs */
#if VERSION_US
s32 D_8008995C[] = {
    0x30126001, 0x40C08E8, 0x10C0603, 0xE8301268,
    0x3040C08, 0x70010C06, 0x8E83012, 0x603040C,
    0x1578010C, 0xC08E830, 0xC060304, 0x30158001,
    0x40C08E8, 0x10C0603, 0xE8301588, 0x3040C08,
    0x90010C06, 0x8E83015, 0x603040C, 0x1598010C,
    0xC08E830, 0xC060304, 0x3015A001, 0x40C08E8,
    0x10C0603, 0xE83015A8, 0x3040C08, 0xB0010C06,
    0x8E83015, 0x603040C, 0x15B8010C, 0xC08E830,
    0xC060304, 0x3015C001, 0x40C08E8, 0x10C0603,
    0xE83015C8, 0x3040C08, 0xD0010C06, 0x8E83015,
    0x603040C, 0x15D8010C, 0xC08E830, 0xC060304,
    0x3015E001, 0x40C08E8, 0x10C0603, 0xE83015E8,
    0x3040C08, 0x20010C06, 0x4E8303F, 0x303050C,
    0x15F0010C, 0xC08E830, 0xC060304, 0x301E0001,
    0x40C08E8, 0x10C0603, 0xE8301E08, 0x3040C08,
    0x10010C06, 0x8E8301E, 0x603040C, 0x1E18010C,
    0xC08E830, 0xC060304, 0x301E2001, 0x40C08E8,
    0x10C0603, 0xE8301E28, 0x3040C08, 0x30010C06,
    0x8E8301E, 0x603040C, 0x1E38010C, 0xC08E830,
    0xC060304, 0x301E4001, 0x40C08E8, 0x10C0603,
    0xE8301E48, 0x3040C08, 0x50010C06, 0x8E8301E,
    0x603040C, 0x1E58010C, 0xC08E830, 0xC060305,
    0x301E6001, 0x40C08E8, 0x10C0603, 0xE8301E68,
    0x3040C08, 0x70010C06, 0x8E8301E, 0x603050C,
    0x2178010C, 0xC08E830, 0xC060304, 0x30218001,
    0x50C08E8, 0x10C0503, 0xE8302188, 0x3050C08,
    0x90010C05, 0x8E83021, 0x503050C, 0x2198010C,
    0xC08E830, 0xC050305, 0x3021A001, 0x50C08E8,
    0x10C0503, 0xE83021A8, 0x3050C08, 0xB0010C05,
    0x8E83021, 0x603040C, 0x21B8010C, 0xC08E830,
    0xC050305, 0x303F2401, 0x70C04E8, 0x10C0103,
    0xE8303F28, 0x3050C04, 0xC0010C04, 0x8E83021,
    0x503050C, 0x3F2C010C, 0xC04E830, 0xC030306,
    0x3021C801, 0x40C08E8, 0x10C0603, 0xE83021D0,
    0x3050C08, 0xD8010C05, 0x8E83021, 0x503050C,
    0x21E0010C, 0xC08E830, 0xC050305, 0x3021E801,
    0x50C08E8, 0x10C0503, 0xE8303F30, 0x3060C04,
    0xF0010C04, 0x8E83021, 0x503050C, 0x3F34010C,
    0xC04E830, 0xC040306, 0x302A0001, 0x50C08E8,
    0x10C0603, 0xE8302A08, 0x3050C08, 0x10010C05,
    0x8E8302A, 0x603040C, 0x2A18010C, 0xC08E830,
    0xC050305, 0x302A2001, 0x50C08E8, 0x10C0503,
    0xE8302A28, 0x3050C08, 0xD8000C05, 0xCE8304A,
    0x803030C, 0x4AE4000C, 0xC0CE830, 0xC090303,
    0x304AF000, 0x40C0CE8, 0xC0803, 0xE8304C00,
    0x3030C0C, 0xC000C09, 0xCE8304C, 0x603040C,
    0x4C18000C, 0xC0CE830, 0xC070304, 0x304C2400,
    0x40C0CE8, 0xC0803, 0xE8304C30, 0x3030C0C,
    0x3C000C09, 0xCE8304C, 0x903030C, 0x4D9C000C,
    0xC0CE830, 0xC090303, 0x304DA800, 0x30C0CE8,
    0xC0A03, 0xE8304E48, 0x3030C0C, 0x54000C0A,
    0xCE83054, 0x903030C, 0x5460000C, 0xC0CE830,
    0xC090303, 0x30546C00, 0x30C0CE8, 0xC0603,
    0xE8305478, 0x3030C0C, 0x84000C08, 0xCE83056,
    0x903030C, 0x5690000C, 0xC0CE830, 0xC0A0303,
    0x3056B400, 0x30C0CE8, 0xC0803, 0xE83056C0,
    0x3030C0C, 0xCC000C09, 0xCE83056, 0x803030C,
    0x56D8000C, 0xC0CE830, 0xC0A0303, 0x3056E400,
    0x30C0CE8, 0xC0803, 0xE83056F0, 0x3030C0C,
    3080, 0xCE83058, 0x803030C, 0x580C000C,
    0xC0CE830, 0xC090303, 0x30581800, 0x30C0CE8,
    0xC0903, 0xE8305824, 0x3030C0C, 0x30000C09,
    0xCE83058, 0x903030C, 0x583C000C, 0xC0CE830,
    0xC090303, 0x30599C00, 0x30C0CE8, 0xC0903,
    0xE83059A8, 0x3030C0C, 0x48000C09, 0xCE8305A,
    0x803030C, 0x6054000C, 0xC0CE830, 0xC090303,
    0x30606000, 0x40C0CE8, 0xC0703, 0xE830606C,
    0x3030C0C, 0x78000C09, 0xCE83060, 0xA03030C,
    0x6284000C, 0xC0CE830, 0xC090303, 0x30629000,
    0x30C0CE8, 0xC0903, 0xE83062B4, 0x3030C0C,
    0xC0000C08, 0xCE83062, 0xA03030C, 0x62CC000C,
    0xC0CE830, 0xC0A0303, 0x3062D800, 0x30C0CE8,
    0xC0903, 0xE83062E4, 0x3030C0C, 0xF0000C0A,
    0xCE83062, 0xA03030C, 0x6400000C, 0xC0CE830,
    0xC0A0303, 0x30640C00, 0x30C0CE8, 0xC0903,
    0xE8306418, 0x3030C0C, 0x24000C0A, 0xCE83064,
    0xB03030C, 0x6430000C, 0xC0CE830, 0xC0A0303,
    0x30643C00, 0x30C0CE8, 0xC0A03, 0xE830659C,
    0x3030C0C, 0xA800090A, 0xCE83065, 0xA03030C,
    0x6648000C, 0xC0CE830, 0xC0A0302, 0x306C5400,
    0x30C0CE8, 0xC0A03, 0xE8306C60, 0x3030C0C,
    0x6C000C0A, 0xCE8306C, 0xA03030C, 0x6C78000C,
    0xC0CE830, 0xC0A0303, 0x306E8400, 0x30C0CE8,
    0xC0903, 0xE8306E90, 0x3030C0C, 0xB4000C0A,
    0xCE8306E, 0xA03030C, 0x6EC0000C, 0xC0CE830,
    0xC090303, 0x306ECC00, 0x30C0CE8, 0xC0A03,
    0xE8306ED8, 0x3030C0C, 0xE4000C0A, 0xCE8306E,
    0xA03030C, 0x6EF0000C, 0xC0CE830, 0xC090303,
    0x30700000, 0x30C0CE8, 0xC0803, 0xE830700C,
    0x3030C0C, 0x18000C0A, 0xCE83070, 0x703040C,
    0x7024000C, 0xC0CE830, 0xC0A0303, 0x30703000,
    0x30C0CE8, 0xC0803, 0xE830703C, 0x3030C0C,
    0x9C000C09, 0xCE83071, 0x903030C, 0x71A8000C,
    0xC0CE830, 0xC070304, 0x30724800, 0x30C0CE8,
    0xC0903, 0xE8307854, 0x3030C0C, 0x60000C0A,
    0xCE83078, 0x903030C, 0x786C000C, 0xC0CE830,
    0xC070304, 0x30787800, 0x30C0CE8, 0xC0A03,
    0xE8307A84, 0x3030C0C, 0x90000C09, 0xCE8307A,
    0xA03030C, 0x7AB4000C, 0xC0CE830, 0xC080304,
    0x307AC000, 0x30C0CE8, 0xC0A03, 0xE8307ACC,
    0x3040C0C, 0xD8000C07, 0xCE8307A, 0x903030C,
    0x7AE4000C, 0xC0CE830, 0xC070304, 0x307AF000,
    0x30C0CE8, 0xC0903, 0xE8307C00, 0x3040C0C,
    0xC000C07, 0xCE8307C, 0xA03030C, 0x7C18000C,
    0xC0CE830, 0xC080304, 0x307C2400, 0x30C0CE8,
    0xC0A03, 0xE8307C30, 0x3030C0C, 0x3C000C09,
    0xCE8307C, 0xA03030C, 0x7D9C000C, 0xC0CE830,
    0xC0A0303, 0x307DA800, 0x30C0CE8, 0xC0A03,
    0xE8307E48, 0x3030C0C, 0x54000C09, 0xCE83084,
    0xA03030C, 0x8460000C, 0xC0CE830, 0xC0A0303,
    0x30846C00, 0x30C0CE8, 0xC0A03, 0xE8308478,
    0x3030C0C, 0x84000C09, 0xCE83086, 0x903030C,
    0x8690000C, 0xC0CE830, 0xC0A0303, 0x3086B400,
    0x30C0CE8, 0x10C0A03, 0xE830B074, 0x3030C0C,
    0x9C010C0A, 0xCE830B0, 0xA03030C, 0xB380010C,
    0xC0CE830, 0xC0A0303, 0x30B38C01, 0x30C0CE8,
    0x10C0A03, 0xE83053E8, 0x3030C0C, 3082,
    0xCE83088, 0xA03030C, 0x880C000C, 0xC0CE830,
    0xC090303, 0x30881800, 0x30C0CE8, 0xC0A03,
    0xE8308824, 0x3030C0C, 0x30000C08, 0xCE83088,
    0xA03030C, 0x883C000C, 0xC0CE830, 0xC0A0303,
    0x30899C00, 0x30C0CE8, 0xC0A03, 0xE83089A8,
    0x3030C0C, 0x48000C07, 0xCE8308A, 0x903030C,
    0x9054000C, 0xC0CE830, 0xC0A0303, 0x30906000,
    0x30C0CE8, 0xC0A03, 0xE830906C, 0x3030C0C,
    0x30010C0A, 0x8E8302A, 0x503040C, 0x2A38010C,
    0xC08E830, 0xC060305, 0x30907800, 0x30C0CE8,
    0xC0A03, 0xE8309284, 0x3030C0C, 0x90000C0A,
    0xCE83092, 0x903030C, 0x92B4000C, 0xC0CE830,
    0xC090303, 0x30540001, 0x40C0CE8, 0x10C0703,
    0xE830540C, 0x3030C0C, 0xCC010C09, 0xCE83054,
    0xA03030C, 0xA040010C, 0xC0CE830, 0xC0A0303,
    0x3054D801, 0x30C0CE8, 0xC0803, 0xE8309400,
    0x3030C0C, 0xC000C09, 0xCE83094, 0x903030C,
    0x9418000C, 0xC0CE830, 0xC090303, 0x30942400,
    0x30C0CE8, 0xC0A03, 0xE8309430, 0x3030C0C,
    0x3C000C0A, 0xCE83094, 0xA03030C, 0x959C000C,
    0xC0CE830, 0xC0A0303, 0x3095A800, 0x20C0CE8,
    0xC0A03, 0xE8309648, 0x3030C0C, 0x54000C09,
    0xCE8309C, 0xA03030C, 0x9C60000C, 0xC0CE830,
    0xC0A0303, 0x309C6C00, 0x30C0CE8, 0xC0A03,
    0xE8309C78, 0x3040C0C, 0x84000C07, 0xCE8309E,
    0xA03030C, 0x9E90000C, 0xC0CE830, 0xC080303,
    0x309EB400, 0x30C0CE8, 0x10C0A03, 0xE8304558,
    0x3040C0C, 0x64010C07, 0xCE83045, 0xA03030C,
    0x4770010C, 0xC0CE830, 0xC080303, 0x30477C01,
    0x30C0CE8, 0x10C0A03, 0xE8304788, 0x3040C0C,
    3078, 0xCE830A0, 0x803040C, 0xA00C000C,
    0xC0CE830, 0xC090303, 0x30A01800, 0x40C0CE8,
    0xC0703, 0xE830A024, 0x3030C0C, 0x30000C0A,
    0xCE830A0, 0x803040C, 0xA03C000C, 0xC0CE830,
    0xC080303, 0x30A19C00, 0x40C0CE8, 0xC0703,
    0xE830A1A8, 0x3030C0C, 0x48000C09, 0xCE830A2,
    0x803030C, 0xA854000C, 0xC0CE830, 0xC090303,
    0x30A86000, 0x30C0CE8, 0x10C0A03, 0xE8300988,
    0x3040C08, 0xA0010C07, 0x8E83009, 0x703040C,
    0x38F8000C, 0xC04E830, 0xC040305, 0x3009B001,
    0x50C08E8, 0xC0503, 0xE8303C60, 0x3040C0C,
    3081,
};
#elif VERSION_EU
s32 D_8008995C[] = {
    0x30126001, 0x40C08E8, 0x10C0603, 0xE8301268,
    0x3040C08, 0x70010C06, 0x8E83012, 0x603040C,
    0x1578010C, 0xC08E830, 0xC060304, 0x30158001,
    0x40C08E8, 0x10C0603, 0xE8301588, 0x3040C08,
    0x90010C06, 0x8E83015, 0x603040C, 0x1598010C,
    0xC08E830, 0xC060304, 0x3015A001, 0x40C08E8,
    0x10C0603, 0xE83015A8, 0x3040C08, 0xB0010C06,
    0x8E83015, 0x603040C, 0x15B8010C, 0xC08E830,
    0xC060304, 0x3015C001, 0x40C08E8, 0x10C0603,
    0xE83015C8, 0x3040C08, 0xD0010C06, 0x8E83015,
    0x603040C, 0x15D8010C, 0xC08E830, 0xC060304,
    0x3015E001, 0x40C08E8, 0x10C0603, 0xE83015E8,
    0x3040C08, 0x20010C06, 0x4E8303F, 0x303050C,
    0x15F0010C, 0xC08E830, 0xC060304, 0x301E0001,
    0x40C08E8, 0x10C0603, 0xE8301E08, 0x3040C08,
    0x10010C06, 0x8E8301E, 0x603040C, 0x1E18010C,
    0xC08E830, 0xC060304, 0x301E2001, 0x40C08E8,
    0x10C0603, 0xE8301E28, 0x3040C08, 0x30010C06,
    0x8E8301E, 0x603040C, 0x1E38010C, 0xC08E830,
    0xC060304, 0x301E4001, 0x40C08E8, 0x10C0603,
    0xE8301E48, 0x3040C08, 0x50010C06, 0x8E8301E,
    0x603040C, 0x1E58010C, 0xC08E830, 0xC060305,
    0x301E6001, 0x40C08E8, 0x10C0603, 0xE8301E68,
    0x3040C08, 0x70010C06, 0x8E8301E, 0x603050C,
    0x2178010C, 0xC08E830, 0xC060304, 0x30218001,
    0x50C08E8, 0x10C0503, 0xE8302188, 0x3050C08,
    0x90010C05, 0x8E83021, 0x503050C, 0x2198010C,
    0xC08E830, 0xC050305, 0x3021A001, 0x50C08E8,
    0x10C0503, 0xE83021A8, 0x3050C08, 0xB0010C05,
    0x8E83021, 0x603040C, 0x21B8010C, 0xC08E830,
    0xC050305, 0x303F2401, 0x70C04E8, 0x10C0103,
    0xE830B97C, 0x3050C04, 0xC0010C04, 0x8E83021,
    0x503050C, 0x3EF8000C, 0xC04E830, 0xC030306,
    0x3021C801, 0x40C08E8, 0x10C0603, 0xE83021D0,
    0x3050C08, 0xD8010C05, 0x8E83021, 0x503050C,
    0x21E0010C, 0xC08E830, 0xC050305, 0x3021E801,
    0x50C08E8, 0x10C0503, 0xE83078D4, 0x3060C04,
    0xF0010C04, 0x8E83021, 0x503050C, 0x47CC010C,
    0xC04E830, 0xC040306, 0x302A0001, 0x50C08E8,
    0x10C0603, 0xE8302A08, 0x3050C08, 0x10010C05,
    0x8E8302A, 0x603040C, 0x2A18010C, 0xC08E830,
    0xC050305, 0x302A2001, 0x50C08E8, 0x10C0503,
    0xE8302A28, 0x3050C08, 0xD8000C05, 0xCE8304A,
    0x803030C, 0x4AE4000C, 0xC0CE830, 0xC090303,
    0x304AF000, 0x40C0CE8, 0xC0803, 0xE8304C00,
    0x3030C0C, 0xC000C09, 0xCE8304C, 0x603040C,
    0x4C18000C, 0xC0CE830, 0xC070304, 0x304C2400,
    0x40C0CE8, 0xC0803, 0xE8304C30, 0x3030C0C,
    0x3C000C09, 0xCE8304C, 0x903030C, 0x4D9C000C,
    0xC0CE830, 0xC090303, 0x304DA800, 0x30C0CE8,
    0xC0A03, 0xE8304E48, 0x3030C0C, 0x54000C0A,
    0xCE83054, 0x903030C, 0x5460000C, 0xC0CE830,
    0xC090303, 0x30546C00, 0x30C0CE8, 0xC0603,
    0xE8305478, 0x3030C0C, 0x84000C08, 0xCE83054,
    0x903030C, 0x5690000C, 0xC0CE830, 0xC0A0303,
    0x3056B400, 0x30C0CE8, 0xC0803, 0xE83056C0,
    0x3030C0C, 0xCC000C09, 0xCE83056, 0x803030C,
    0x56D8000C, 0xC0CE830, 0xC0A0303, 0x3056E400,
    0x30C0CE8, 0xC0803, 0xE83056F0, 0x3030C0C,
    3080, 0xCE83058, 0x803030C, 0x580C000C,
    0xC0CE830, 0xC090303, 0x30581800, 0x30C0CE8,
    0xC0903, 0xE8305824, 0x3030C0C, 0x30000C09,
    0xCE83058, 0x903030C, 0x583C000C, 0xC0CE830,
    0xC090303, 0x30599C00, 0x30C0CE8, 0xC0903,
    0xE83059A8, 0x3030C0C, 0x48000C09, 0xCE8305A,
    0x803030C, 0x6054000C, 0xC0CE830, 0xC090303,
    0x30606000, 0x40C0CE8, 0xC0703, 0xE830606C,
    0x3030C0C, 0x78000C09, 0xCE83060, 0xA03030C,
    0x6084000C, 0xC0CE830, 0xC090303, 0x30629000,
    0x30C0CE8, 0xC0903, 0xE83062B4, 0x3030C0C,
    0xC0000C08, 0xCE83062, 0xA03030C, 0x62CC000C,
    0xC0CE830, 0xC0A0303, 0x3062D800, 0x30C0CE8,
    0xC0903, 0xE83062E4, 0x3030C0C, 0xF0000C0A,
    0xCE83062, 0xA03030C, 0x6400000C, 0xC0CE830,
    0xC0A0303, 0x30640C00, 0x30C0CE8, 0xC0903,
    0xE8306418, 0x3030C0C, 0x24000C0A, 0xCE83064,
    0xB03030C, 0x6430000C, 0xC0CE830, 0xC0A0303,
    0x30643C00, 0x30C0CE8, 0xC0A03, 0xE830659C,
    0x3030C0C, 0xA800090A, 0xCE83065, 0xA03030C,
    0x6648000C, 0xC0CE830, 0xC0A0302, 0x306C5400,
    0x30C0CE8, 0xC0A03, 0xE8306C60, 0x3030C0C,
    0x6C000C0A, 0xCE8306C, 0xA03030C, 0x6C78000C,
    0xC0CE830, 0xC0A0303, 0x306C8400, 0x30C0CE8,
    0xC0903, 0xE8306E90, 0x3030C0C, 0xB4000C0A,
    0xCE8306E, 0xA03030C, 0x6EC0000C, 0xC0CE830,
    0xC090303, 0x306ECC00, 0x30C0CE8, 0xC0A03,
    0xE8306ED8, 0x3030C0C, 0xE4000C0A, 0xCE8306E,
    0xA03030C, 0x6EF0000C, 0xC0CE830, 0xC090303,
    0x30700000, 0x30C0CE8, 0xC0803, 0xE830700C,
    0x3030C0C, 0x18000C0A, 0xCE83070, 0x703040C,
    0x7024000C, 0xC0CE830, 0xC0A0303, 0x30703000,
    0x30C0CE8, 0xC0803, 0xE830703C, 0x3030C0C,
    0x9C000C09, 0xCE83071, 0x903030C, 0x71A8000C,
    0xC0CE830, 0xC070304, 0x30724800, 0x30C0CE8,
    0xC0903, 0xE8307854, 0x3030C0C, 0x60000C0A,
    0xCE83078, 0x903030C, 0x786C000C, 0xC0CE830,
    0xC070304, 0x30787800, 0x30C0CE8, 0xC0A03,
    0xE8307884, 0x3030C0C, 0x90000C09, 0xCE8307A,
    0xA03030C, 0x7AB4000C, 0xC0CE830, 0xC080304,
    0x307AC000, 0x30C0CE8, 0xC0A03, 0xE8307ACC,
    0x3040C0C, 0xD8000C07, 0xCE8307A, 0x903030C,
    0x7AE4000C, 0xC0CE830, 0xC070304, 0x307AF000,
    0x30C0CE8, 0xC0903, 0xE8307C00, 0x3040C0C,
    0xC000C07, 0xCE8307C, 0xA03030C, 0x7C18000C,
    0xC0CE830, 0xC080304, 0x307C2400, 0x30C0CE8,
    0xC0A03, 0xE8307C30, 0x3030C0C, 0x3C000C09,
    0xCE8307C, 0xA03030C, 0x7D9C000C, 0xC0CE830,
    0xC0A0303, 0x307DA800, 0x30C0CE8, 0xC0A03,
    0xE8307E48, 0x3030C0C, 0x54000C09, 0xCE83084,
    0xA03030C, 0x8460000C, 0xC0CE830, 0xC0A0303,
    0x30846C00, 0x30C0CE8, 0xC0A03, 0xE8308478,
    0x3030C0C, 0x84000C09, 0xCE83084, 0x903030C,
    0x8690000C, 0xC0CE830, 0xC0A0303, 0x3086B400,
    0x30C0CE8, 0x10C0A03, 0xE830C958, 0x3030C0C,
    0xB8010C0A, 0xCE83053, 0xA03030C, 0x53DC010C,
    0xC0CE830, 0xC0A0303, 0x3053D001, 0x30C0CE8,
    0x10C0A03, 0xE83053E8, 0x3030C0C, 3082,
    0xCE83088, 0xA03030C, 0x880C000C, 0xC0CE830,
    0xC090303, 0x30881800, 0x30C0CE8, 0xC0A03,
    0xE8308824, 0x3030C0C, 0x30000C08, 0xCE83088,
    0xA03030C, 0x883C000C, 0xC0CE830, 0xC0A0303,
    0x30899C00, 0x30C0CE8, 0xC0A03, 0xE83089A8,
    0x3030C0C, 0x48000C07, 0xCE8308A, 0x903030C,
    0x9054000C, 0xC0CE830, 0xC0A0303, 0x30906000,
    0x30C0CE8, 0xC0A03, 0xE830906C, 0x3030C0C,
    0x30010C0A, 0x8E8302A, 0x503040C, 0x2A38010C,
    0xC08E830, 0xC060305, 0x30907800, 0x30C0CE8,
    0xC0A03, 0xE8309084, 0x3030C0C, 0x90000C0A,
    0xCE83092, 0x903030C, 0x92B4000C, 0xC0CE830,
    0xC090303, 0x30570001, 0x40C0CE8, 0x10C0703,
    0xE830570C, 0x3030C0C, 0xB4000C09, 0xCE830AA,
    0xA03030C, 0xE658010C, 0xC0CE830, 0xC0A0303,
    0x3047D001, 0x30C0CE8, 0xC0803, 0xE8309400,
    0x3030C0C, 0xC000C09, 0xCE83094, 0x903030C,
    0x9418000C, 0xC0CE830, 0xC090303, 0x30942400,
    0x30C0CE8, 0xC0A03, 0xE8309430, 0x3030C0C,
    0x3C000C0A, 0xCE83094, 0xA03030C, 0x959C000C,
    0xC0CE830, 0xC0A0303, 0x3095A800, 0x20C0CE8,
    0xC0A03, 0xE8309648, 0x3030C0C, 0x54000C09,
    0xCE8309C, 0xA03030C, 0x9C60000C, 0xC0CE830,
    0xC0A0303, 0x309C6C00, 0x30C0CE8, 0xC0A03,
    0xE8309C78, 0x3040C0C, 0x84000C07, 0xCE8309C,
    0xA03030C, 0x9E90000C, 0xC0CE830, 0xC080303,
    0x309EB400, 0x30C0CE8, 0x10C0A03, 0xE83053C4,
    0x3040C0C, 0x58010C07, 0xCE830F2, 0xA03030C,
    0xF318000C, 0xC0CE830, 0xC080303, 0x30F32400,
    0x30C0CE8, 0x10C0A03, 0xE830C1D4, 0x3040C0C,
    3078, 0xCE830A0, 0x803040C, 0xA00C000C,
    0xC0CE830, 0xC090303, 0x30A01800, 0x40C0CE8,
    0xC0703, 0xE830A024, 0x3030C0C, 0x30000C0A,
    0xCE830A0, 0x803040C, 0xA03C000C, 0xC0CE830,
    0xC080303, 0x30A19C00, 0x40C0CE8, 0xC0703,
    0xE830A1A8, 0x3030C0C, 0x48000C09, 0xCE830A2,
    0x803030C, 0xA854000C, 0xC0CE830, 0xC090303,
    0x30A86000, 0x30C0CE8, 0x10C0A03, 0xE8300988,
    0x3040C08, 0xA0010C07, 0x8E83009, 0x703040C,
    0x9CC8010C, 0xC04E830, 0xC040305, 0x3009B001,
    0x50C08E8, 0xC0503, 0xE8303C60, 0x3040C0C,
    3081,
};
#endif
/* the European version's differs */
#if VERSION_US
s32 D_8008A340[] = {
    0x3014F400, 0x30C08E8, 0xC0603, 0xE83020F4,
    0x3030C08, 0xF4000C07, 0x8E8302C, 0x703030C,
    0x978010C, 0xC08E830, 0xC080303, 0x30098001,
    0x30C08E8, 0x10C0703, 0xE8300988, 0x3040C08,
    0x90010C07, 0x8E83009, 0x703030C, 0x998010C,
    0xC08E830, 0xC070303, 0x3009A001, 0x40C08E8,
    0xC0703, 0xE83038F8, 0x3050C04, 0xF8010C04,
    0x4E83009, 0x403030C, 0x9A8010C, 0xC08E830,
    0xC070303, 0x3009B001, 0x50C08E8, 0x10C0503,
    0xE83009B8, 0x3050C08, 0xC0010C05, 0x8E83009,
    0x603030C, 0x9C8010C, 0xC08E830, 0xC060303,
    0x303C6000, 0x40C0CE8, 0xC0903, 0xE8303C6C,
    0x3030C0C, 0xCC010C0C, 0x8E83081, 0xC03030C,
    0x9D0010C, 0xC08E830, 0xC0B0303, 0x3015F801,
    0x30C04E8, 0x10C0403, 0xE83021F8, 0x3030C04,
    0xF8010C04, 0x4E8302D, 0x403030C, 0x39F8010C,
    0xC04E830, 0xC040303, 0x3009D801, 0x30C08E8,
    0x10C0803, 0xE83009E0, 0x3050C08, 0xE8010C05,
    0x8E83009, 0x703030C, 0x9F0010C, 0xC08E830,
    0xC070303, 0x30120001, 0x30C08E8, 0x10C0603,
    0xE8301208, 0x3030C08, 0x10010C06, 0x8E83012,
    0x703030C, 0x1218010C, 0xC08E830, 0xC070303,
    0x30122001, 0x30C08E8, 0x10C0703, 0xE8301228,
    0x3030C08, 0x78000C07, 0xCE8303C, 0xC03030C,
    0x3EEC000C, 0xC0CE830, 0xC0C0303, 0x303E9000,
    0x30C0CA1, 0xC0C03, 0xA0303EBC, 0x3030C0C,
    0xC8000C0C, 0xC9F303E, 0xC03030C, 0x3ED4000C,
    0xC0C9E30, 0xC0C0303, 0x303EE000, 0x30C0C9D,
    0x10C0C03, 0xE8301230, 0x3030C08, 0x38010C0C,
    0x8E83012, 0x803030C, 0x419C000C, 0xC0C9C30,
    0xC0C0303, 0x3041A800, 0x30C0C9B, 0xC0C03,
    0x9A304854, 0x3030C0C, 0x60000C0C, 0xCE83048,
    0xA03030C, 0x486C000C, 0xC0C9930, 0xC0C0303,
    0x30487800, 0x30C0C98, 0xC0C03, 0xE8304A84,
    0x3030C0C, 0x90000C0A, 0xC97304A, 0xC03030C,
    0x4AB4000C, 0xC0CE830, 0xC0B0303, 0x304AC000,
    0x30C0C96, 0xC0C03, 0x95304ACC, 0x3030C0C,
    0x40010C0C, 0x8E83012, 0x703030C, 0x1248010C,
    0xC08E830, 0xC070303, 0x30125001, 0x30C08E8,
    0x10C0803, 0xE8301258, 0x3030C08, 0x8C000C08,
    0x4E8303E, 0xC00000C, 0x3C84000C, 0xC08E830,
    0xC0C0000, 0x30A86C00, 0xC08E8, 0xC0C00,
    0xE830A874, 3080, 0x7C000C0C, 0x8E830A8,
    0xC00000C, 0xAA84000C, 0xC08E830, 0xC0C0000,
    0x30AA8C00, 0xC08E8, 0xC0C00, 0xE830AA94,
    3080, 0xB4000C0C, 0x8E830AA, 0xC00000C,
    0xAC00000C, 0xC08E830, 0xC0C0000, 0x3084C001,
    0xC08E8, 0x10C0C00, 0xE83085D4, 3080,
    0xDC010C0C, 0x8E83085, 0xC00000C, 0x85E4010C,
    0xC08E830, 0xC0C0000, 0x3087AC01, 0xC08E8,
    0x10C0C00, 0xE83087B4, 3080, 0x80010C0C,
    0x8E8308B, 0xC00000C, 0x8B88010C, 0xC08E830,
    0xC0C0000, 0x308B9001, 0xC08E8, 0x10C0C00,
    0xE8308B98, 3080, 0xA0010C0C, 0x8E8308B,
    0xC00000C, 0x8DC8010C, 0xC08E830, 0xC0C0000,
    0x30A63801, 0xC08E8, 0x10C0C00, 0xE830AC40,
    3080, 0x48010C0C, 0x8E830AF, 0xC00000C,
    0xAF50010C, 0xC08E830, 0xC0C0000, 0x30BB5001,
    0xC08E8, 0x10C0C00, 0xE830BC98, 3080,
    0xA0010C0C, 0x8E830BC, 0xC00000C, 0xBF88010C,
    0xC08E830, 0xC0C0000, 0x30BF9001, 0xC08E8,
    0x10C0C00, 0xE830C168, 3080, 0xCC010C0C,
    0x8E830C3, 0xC00000C, 0xC3D4010C, 0xC08E830,
    0xC0C0000, 0x30C3DC01, 0xC08E8, 0x10C0C00,
    0xE830C3E4, 3080, 0xEC010C0C, 0x8E830C3,
    0xC00000C, 0xC5A8010C, 0xC08E830, 0xC0C0000,
    0x30C5B001, 0xC08E8, 0x10C0C00, 0xE830C5B8,
    3080, 0xC0010C0C, 0x8E830C5, 0xC00000C,
    0xC5F4010C, 0xC08E830, 0xC0C0000, 0x30C75001,
    0xC08E8, 0x10C0C00, 0xE830C898, 3080,
    0xA0010C0C, 0x8E830C8, 0xC00000C, 0xC958010C,
    0xC08E830, 0xC0C0000, 0x30C96001, 0xC08E8,
    0x10C0C00, 0xE830CB88, 3080, 0x90010C0C,
    0x8E830CB, 0xC00000C, 0xCD68010C, 0xC08E830,
    0xC0C0000, 0x30CFC801, 0xC08E8, 0x10C0C00,
    0xE830CFD0, 3080, 0xD8010C0C, 0x8E830CF,
    0xC00000C, 0xCFE0010C, 0xC08E830, 0xC0C0000,
    0x30CFE801, 0xC08E8, 0x10C0C00, 0xE830D1A8,
    3080, 3084,
};
#elif VERSION_EU
s32 D_8008A340[] = {
    0x303C8400, 0x30C08E8, 0xC0603, 0xE83020F4,
    0x3030C08, 0xF4000C07, 0x8E8302C, 0x703030C,
    0x978010C, 0xC08E830, 0xC080303, 0x30098001,
    0x30C08E8, 0x10C0703, 0xE8300988, 0x3040C08,
    0x90010C07, 0x8E83009, 0x703030C, 0x998010C,
    0xC08E830, 0xC070303, 0x3009A001, 0x40C08E8,
    0x10C0703, 0xE8309CC8, 0x3050C04, 0x3C010C04,
    0x4E83054, 0x403030C, 0x9A8010C, 0xC08E830,
    0xC070303, 0x3009B001, 0x50C08E8, 0x10C0503,
    0xE83009B8, 0x3050C08, 0xC0010C05, 0x8E83009,
    0x603030C, 0x9C8010C, 0xC08E830, 0xC060303,
    0x303C6000, 0x40C0CE8, 0xC0903, 0xE8303C6C,
    0x3030C0C, 0xA4010C0C, 0x8E830CD, 0xC03030C,
    0x9D0010C, 0xC08E830, 0xC0B0303, 0x30537801,
    0x30C04E8, 0x10C0403, 0xE830A8F8, 0x3030C04,
    0x1C010C04, 0x4E83099, 0x403030C, 0x8D1C010C,
    0xC04E830, 0xC040303, 0x3009D801, 0x30C08E8,
    0x10C0803, 0xE83009E0, 0x3050C08, 0xE8010C05,
    0xCE03009, 0x703030C, 0xF208010C, 0xC08E830,
    0xC070303, 0x30120001, 0x30C08E8, 0x10C0603,
    0xE8301208, 0x3030C08, 0x10010C06, 0x8E83012,
    0x703030C, 0x1218010C, 0xC08E830, 0xC070303,
    0x30122001, 0x30C08E8, 0x10C0703, 0xE8301228,
    0x3030C08, 0x78000C07, 0xCE8303C, 0xC03030C,
    0x3EEC000C, 0xC0CE830, 0xC0C0303, 0x303E9000,
    0x30C0C99, 0xC0C03, 0x98303EBC, 0x3030C0C,
    0xC8000C0C, 0xC97303E, 0xC03030C, 0x3ED4000C,
    0xC0C9630, 0xC0C0303, 0x303EE000, 0x30C0C95,
    0x10C0C03, 0xE8301230, 0x3030C08, 0x38010C0C,
    0x8E83012, 0x803030C, 0x419C000C, 0xC0C9430,
    0xC0C0303, 0x3041A800, 0x30C0C93, 0xC0C03,
    0x92304854, 0x3030C0C, 0x60000C0C, 0xCE03048,
    0xA03030C, 0x486C000C, 0xC0C9130, 0xC0C0303,
    0x30487800, 0x30C0C90, 0xC0C03, 0xE0304884,
    0x3030C0C, 0x90000C0A, 0xC8F304A, 0xC03030C,
    0x4AB4000C, 0xC0CE030, 0xC0B0303, 0x304AC000,
    0x30C0C8E, 0xC0C03, 0x8D304ACC, 0x3030C0C,
    0x40010C0C, 0x8E83012, 0x703030C, 0x1248010C,
    0xC08E830, 0xC070303, 0x30125001, 0x30C08E8,
    0x10C0803, 0xE8301258, 0x3030C08, 0xC8010C08,
    0x4E83087, 0xC00000C, 0xF338000C, 0xC08E830,
    0xC0C0000, 0x30A86C00, 0xC08E8, 0xC0C00,
    0xE830A874, 3080, 0x7C000C0C, 0x8E830A8,
    0xC00000C, 0x14F4000C, 0xC08E830, 0xC0C0000,
    0x303F2801, 0xC08E8, 0x10C0C00, 0xE830CDBC,
    3080, 0xF4010C0C, 0x8E83009, 0xC00000C,
    0xAC00000C, 0xC08E830, 0xC0C0000, 0x30C99C01,
    0xC08E8, 0x10C0C00, 0xE830B580, 3080,
    0xAC010C0C, 0x8E830CD, 0xC00000C, 0xCDC4010C,
    0xC08E830, 0xC0C0000, 0x30C99401, 0xC08E8,
    0x10C0C00, 0xE830C1C4, 3080, 0x78010C0C,
    0x8E830F1, 0xC00000C, 0xAC10000C, 0xC08E830,
    0xC0C0000, 0x30D97801, 0xC08E8, 0x10C0C00,
    0xE8309CC0, 3080, 0x10C0C, 0x8E830F2,
    0xC00000C, 0xF340000C, 0xC08E830, 0xC0C0000,
    0x30A63801, 0xC08E8, 0x10C0C00, 0xE830C1B4,
    3080, 0x40010C0C, 0x8E830AF, 0xC00000C,
    0xA850010C, 0xC08E830, 0xC0C0000, 0x30B45001,
    0xC08E8, 0x10C0C00, 0xE8303F38, 3080,
    0xA4010C0C, 0x8E83097, 0xC00000C, 0x3F10010C,
    0xC08E830, 0xC0C0000, 0x303F0801, 0xC08E8,
    0x10C0C00, 0xE830AF48, 3080, 0x80010C0C,
    0x8E830C1, 0xC00000C, 0xA3A4010C, 0xC08E830,
    0xC0C0000, 0x30CDCC01, 0xC08E8, 0x10C0C00,
    0xE83087C0, 3080, 0xA4010C0C, 0x8E8308B,
    0xC00000C, 0xF210010C, 0xC08E830, 0xC0C0000,
    0x30C1A401, 0xC08E8, 0x10C0C00, 0xE830CDB4,
    3080, 0x30010C0C, 0x8E8303F, 0xC00000C,
    0xE578010C, 0xC08E830, 0xC0C0000, 0x30C05001,
    0xC08E8, 0x10C0C00, 0xE830CD78, 3080,
    0xCC010C0C, 0x8E830C1, 0xC00000C, 0xEA50010C,
    0xC08E830, 0xC0C0000, 0x30DE5001, 0xC08E8,
    0x10C0C00, 0xE8303F00, 3080, 0x8000C0C,
    0x8E830AC, 0xC00000C, 0x3F18010C, 0xC08E830,
    0xC0C0000, 0x30C1AC01, 0xC08E8, 0x10C0C00,
    0xE830C1BC, 3080, 0x18010C0C, 0x8E830F2,
    0xC00000C, 0x9CCC010C, 0xC08E830, 0xC0C0000,
    0x3087CC01, 0xC08E8, 0xC0C00, 0xE830F330,
    3080, 3084,
};
#endif
/* the European version reads these two for language 0 */
KeyTabs STCRDDEK_keyPagesJp[] = {
    { { 2, 3, 4 } },
    { { 5, 6, 7 } },
    { { 8, 9, 10 } },
};
KeyPage STCRDDEK_keyCharsJp[] = {
    { {
        { { 1, 0x43 }, { 1, 0x45 }, { 1, 0x47 }, { 1, 0x49 }, { 1, 0x4B }, { 1, 0x85 }, { 0, 0x00 }, { 1, 0x87 }, { 0, 0x00 }, { 1, 0x89 }, { 1, 0x72 }, { 1, 0x75 }, { 1, 0x78 }, { 1, 0x7B }, { 1, 0x7E } },
        { { 1, 0x4C }, { 1, 0x4E }, { 1, 0x50 }, { 1, 0x52 }, { 1, 0x54 }, { 1, 0x8A }, { 1, 0x8B }, { 1, 0x8C }, { 1, 0x8D }, { 1, 0x8E }, { 1, 0x42 }, { 1, 0x44 }, { 1, 0x46 }, { 1, 0x48 }, { 1, 0x4A } },
        { { 1, 0x56 }, { 1, 0x58 }, { 1, 0x5A }, { 1, 0x5C }, { 1, 0x5E }, { 1, 0x90 }, { 0, 0x00 }, { 1, 0x91 }, { 0, 0x00 }, { 1, 0x92 }, { 1, 0x84 }, { 1, 0x86 }, { 1, 0x88 }, { 1, 0x64 }, { 0, 0x00 } },
        { { 1, 0x60 }, { 1, 0x62 }, { 1, 0x65 }, { 1, 0x67 }, { 1, 0x69 }, { 1, 0x4D }, { 1, 0x4F }, { 1, 0x51 }, { 1, 0x53 }, { 1, 0x55 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 } },
        { { 1, 0x6B }, { 1, 0x6C }, { 1, 0x6D }, { 1, 0x6E }, { 1, 0x6F }, { 1, 0x57 }, { 1, 0x59 }, { 1, 0x5B }, { 1, 0x5D }, { 1, 0x5F }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 1, 0x70 }, { 1, 0x73 }, { 1, 0x76 }, { 1, 0x79 }, { 1, 0x7C }, { 1, 0x61 }, { 1, 0x63 }, { 1, 0x66 }, { 1, 0x68 }, { 1, 0x6A }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 1, 0x7F }, { 1, 0x80 }, { 1, 0x81 }, { 1, 0x82 }, { 1, 0x83 }, { 1, 0x71 }, { 1, 0x74 }, { 1, 0x77 }, { 1, 0x7A }, { 1, 0x7D }, { 1, 0x00 }, { 1, 0x00 }, { -1, 0x00 }, { 1, 0x00 }, { -1, 0x00 } },
    } },
    { {
        { { 1, 0x94 }, { 1, 0x96 }, { 1, 0x98 }, { 1, 0x9A }, { 1, 0x9C }, { 1, 0xD6 }, { 0, 0x00 }, { 1, 0xD8 }, { 0, 0x00 }, { 1, 0xDA }, { 1, 0xC3 }, { 1, 0xC6 }, { 1, 0xC9 }, { 1, 0xCC }, { 1, 0xCF } },
        { { 1, 0x9D }, { 1, 0x9F }, { 1, 0xA1 }, { 1, 0xA3 }, { 1, 0xA5 }, { 1, 0xDB }, { 1, 0xDC }, { 1, 0xDD }, { 1, 0xDE }, { 1, 0xDF }, { 1, 0x93 }, { 1, 0x95 }, { 1, 0x97 }, { 1, 0x99 }, { 1, 0x9B } },
        { { 1, 0xA7 }, { 1, 0xA9 }, { 1, 0xAB }, { 1, 0xAD }, { 1, 0xAF }, { 1, 0xE1 }, { 0, 0x00 }, { 1, 0xE2 }, { 0, 0x00 }, { 1, 0xE3 }, { 1, 0xD5 }, { 1, 0xD7 }, { 1, 0xD9 }, { 1, 0xB5 }, { 1, 0xE4 } },
        { { 1, 0xB1 }, { 1, 0xB3 }, { 1, 0xB6 }, { 1, 0xB8 }, { 1, 0xBA }, { 1, 0x9E }, { 1, 0xA0 }, { 1, 0xA2 }, { 1, 0xA4 }, { 1, 0xA6 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 } },
        { { 1, 0xBC }, { 1, 0xBD }, { 1, 0xBE }, { 1, 0xBF }, { 1, 0xC0 }, { 1, 0xA8 }, { 1, 0xAA }, { 1, 0xAC }, { 1, 0xAE }, { 1, 0xB0 }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 1, 0xC1 }, { 1, 0xC4 }, { 1, 0xC7 }, { 1, 0xCA }, { 1, 0xCD }, { 1, 0xB2 }, { 1, 0xB4 }, { 1, 0xB7 }, { 1, 0xB9 }, { 1, 0xBB }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 1, 0xD0 }, { 1, 0xD1 }, { 1, 0xD2 }, { 1, 0xD3 }, { 1, 0xD4 }, { 1, 0xC2 }, { 1, 0xC5 }, { 1, 0xC8 }, { 1, 0xCB }, { 1, 0xCE }, { 1, 0x00 }, { 1, 0x00 }, { -1, 0x00 }, { 1, 0x00 }, { -1, 0x00 } },
    } },
    { {
        { { 1, 0x0E }, { 1, 0x0F }, { 1, 0x10 }, { 1, 0x11 }, { 1, 0x12 }, { 1, 0x28 }, { 1, 0x29 }, { 1, 0x2A }, { 1, 0x2B }, { 1, 0x2C }, { 1, 0x04 }, { 1, 0x05 }, { 1, 0x06 }, { 1, 0x07 }, { 1, 0x08 } },
        { { 1, 0x13 }, { 1, 0x14 }, { 1, 0x15 }, { 1, 0x16 }, { 1, 0x17 }, { 1, 0x2D }, { 1, 0x2E }, { 1, 0x2F }, { 1, 0x30 }, { 1, 0x31 }, { 1, 0x09 }, { 1, 0x0A }, { 1, 0x0B }, { 1, 0x0C }, { 1, 0x0D } },
        { { 1, 0x18 }, { 1, 0x19 }, { 1, 0x1A }, { 1, 0x1B }, { 1, 0x1C }, { 1, 0x32 }, { 1, 0x33 }, { 1, 0x34 }, { 1, 0x35 }, { 1, 0x36 }, { 1, 0xE8 }, { 1, 0xE9 }, { 1, 0xE5 }, { 1, 0xE6 }, { 1, 0xE7 } },
        { { 1, 0x1D }, { 1, 0x1E }, { 1, 0x1F }, { 1, 0x20 }, { 1, 0x21 }, { 1, 0x37 }, { 1, 0x38 }, { 1, 0x39 }, { 1, 0x3A }, { 1, 0x3B }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 } },
        { { 1, 0x22 }, { 1, 0x23 }, { 1, 0x24 }, { 1, 0x25 }, { 1, 0x26 }, { 1, 0x3C }, { 1, 0x3D }, { 1, 0x3E }, { 1, 0x3F }, { 1, 0x40 }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 1, 0x27 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 1, 0x41 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 1, 0x00 }, { 1, 0x00 }, { -1, 0x00 }, { 1, 0x00 }, { -1, 0x00 } },
    } },
};
KeyTabs STCRDDEK_keyPages[] = {
    { { 8, 9, 10 } },
};
KeyPage STCRDDEK_keyChars[] = {
    { {
        { { 1, 0x0E }, { 1, 0x0F }, { 1, 0x10 }, { 1, 0x11 }, { 1, 0x12 }, { 1, 0x28 }, { 1, 0x29 }, { 1, 0x2A }, { 1, 0x2B }, { 1, 0x2C }, { 1, 0x04 }, { 1, 0x05 }, { 1, 0x06 }, { 1, 0x07 }, { 1, 0x08 } },
        { { 1, 0x13 }, { 1, 0x14 }, { 1, 0x15 }, { 1, 0x16 }, { 1, 0x17 }, { 1, 0x2D }, { 1, 0x2E }, { 1, 0x2F }, { 1, 0x30 }, { 1, 0x31 }, { 1, 0x09 }, { 1, 0x0A }, { 1, 0x0B }, { 1, 0x0C }, { 1, 0x0D } },
        { { 1, 0x18 }, { 1, 0x19 }, { 1, 0x1A }, { 1, 0x1B }, { 1, 0x1C }, { 1, 0x32 }, { 1, 0x33 }, { 1, 0x34 }, { 1, 0x35 }, { 1, 0x36 }, { 1, 0xE8 }, { 1, 0xE9 }, { 1, 0xE5 }, { 1, 0xE6 }, { 1, 0xE7 } },
        { { 1, 0x1D }, { 1, 0x1E }, { 1, 0x1F }, { 1, 0x20 }, { 1, 0x21 }, { 1, 0x37 }, { 1, 0x38 }, { 1, 0x39 }, { 1, 0x3A }, { 1, 0x3B }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 } },
        { { 1, 0x22 }, { 1, 0x23 }, { 1, 0x24 }, { 1, 0x25 }, { 1, 0x26 }, { 1, 0x3C }, { 1, 0x3D }, { 1, 0x3E }, { 1, 0x3F }, { 1, 0x40 }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 1, 0x27 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 1, 0x41 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 1, 0x00 }, { -1, 0x00 }, { -2, 0x00 }, { -3, 0x00 }, { -4, 0x00 } },
        { { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 0, 0x00 }, { 1, 0x00 }, { 1, 0x00 }, { -1, 0x00 }, { 1, 0x00 }, { -1, 0x00 } },
    } },
};
TextStyle STCRDDEK_nameStyle = {
    0xFF, 14, {0}, (s32)D_8008995C, (s32)D_8008A340,
    FONT_GLYPH_MAP, FONT_ICON_MAP,
    234, 114,
};
s32 STCRDDEK_nameAnims[] = {
    7, 8, 9, 10,
    9, 8, -1, 14,
    15, 16, 15, -1,
    -1, -1, 11, 12,
    13, 12, -1, -1,
    -1, 3, 4, 5,
    6, 5, 4, -1,
    25, 26, 27, 28,
    27, 26, -1, 0,
    1, 2, 1, -1,
    -1, -1, 17, 18,
    19, 20, 19, 18,
    -1, 21, 22, 23,
    24, 23, 22, -1,
};
BigKey STCRDDEK_bigKeys[] = {
    { 44, 203, 195 }, { 45, 222, 195 }, { 60, 203, 153 }, { 68, 203, 174 }, { 76, 246, 195 },
};
s32 STCRDDEK_keyArrowCluts[] = {
    0, 1, 2, 3,
    2, 1,
};
DeckFuncs STCRDDEK_funcs = {
    STCRDDEK_loadFiles, STCRDDEK_filesLoading, STCRDDEK_startFade,
    STCRDDEK_updateFade, STCRDDEK_startLerp, STCRDDEK_updateLerp,
};
NameKeyboard STCRDDEK_keyboard = {0};
