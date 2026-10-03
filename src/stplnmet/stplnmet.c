#include "stplnmet.h"

extern TextStyle STPLNMET_nameStyle;

Task *STPLNMET_createScreen(void);
void func_800828DC(NameScroll *task);
void func_80082B80(NameSparkle *task);
void func_80082D88(NameSparkle *task);
void func_80082F0C(NameDialog *task, NameDialogWindows *windows);
void STPLNMET_updateNameEntry(PlayerNameTask *task, PlayerNameWindows *windows);
void func_800837E8(PlayerNameTask *task, PlayerNameWindows *windows, s32 show);
extern s32 D_80087AAC[];
extern SparkleFrame D_80087AB4[];
void STPLNMET_drawKeyboard(PlayerNameTask *task);
extern s32 STPLNMET_nameAnims[];
extern BigKey STPLNMET_bigKeys[];
extern s32 STPLNMET_keyArrowCluts[];
void STPLNMET_updateKeyboard(PlayerNameTask *task, PlayerNameWindows *windows);
extern KeyTabs STPLNMET_keyPagesJp[];
extern KeyPage STPLNMET_keyCharsJp[];
extern KeyTabs STPLNMET_keyPages[];
extern KeyPage STPLNMET_keyChars[];
extern NameKeyboard STPLNMET_keyboard;
void func_800852D8(PlayerNameTask *task, s32 hide);
void func_80085434(NameConfirm *task, NameConfirmWindows *windows);
void func_800855DC(NameConfirm *task, NameConfirmWindows *windows, s32 show);
void func_80085834(NameConfirm *task);
void func_80085F0C(NameConfirm *task, NameConfirmWindows *windows);
void func_800864F0(PartnerChoice *task, PartnerChoiceWindows *windows);
void func_800866C0(PartnerChoice *task, PartnerChoiceWindows *windows, s32 show);
void func_80086944(PartnerChoice *task);
void func_80087630(PlayerNameScreen *screen, PlayerNameScreenChildren *children);
extern s32 D_80088F30[];
Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
extern s32 D_80088F48[];

void STPLNMET_centerLayer(Task *task, Task **children, Layer *layer, RECT *rect) {
    layer->setOffset(layer, rect->w / 2, rect->h / 2);
    layer->allocCallbacks(layer, 5);
}

void STPLNMET_updateScene(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x19000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 1, 0x1000);
        layer->setBgColor(layer, 1, 1, 1);
        STPLNMET_centerLayer(task, children, layer, &rect);
        GFX.funcs.createLayer(&rect, 3, 0x1001);
        GFX.funcs.moveLayer(0x1001, 0x1000, 1);
        children[0] = STPLNMET_createScreen();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STPLNMET_start(void) {
    return createTask(STPLNMET_updateScene, sizeof(Task), 4);
}

void func_800828DC(NameScroll *task) {
    SpriteDrawer sprite;
    s32 now;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        if (task->loaded != 0) {
            task->times[0] = task->times[1] = GFX.funcs.getTime();
            task->nextState(task);
        }
        break;
    case TASK_RUN:
        initSpriteDrawer(&sprite);
        sprite.setTexture(task->vramX, task->vramY);
        sprite.setLayerId(task->layer, task->depth);
        now = GFX.funcs.getTime();
        for (i = 0; i < 2; i++) {
            if (now - task->times[i] > i + 1) {
                task->pos[i][0] -= 2;
                task->pos[i][1]++;
                if (task->pos[i][0] <= D_80087AAC[i]) {
                    task->pos[i][0] = task->pos[i][1] = 0;
                }
                task->times[i] = now;
            }
            sprite.draw(FILE_CACHE.getEntry(PLNMET_SCROLL), i, task->pos[i][0], task->pos[i][1]);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_SCROLL), 2, 0, 0);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void STPLNMET_loadScroll(NameScroll *task, s32 x, s32 y) {
    TimLoader loader;

    task->vramX = x;
    task->vramY = y;
    initTimLoader(&loader);
    loader.setImagePos(x, y);
    loader.loadArchive(FILE_CACHE_GET_ENTRY[0](FILE_PLNMET_IMAGE << 16));
    task->loaded = 1;
}

void STPLNMET_setScrollLayer(NameScroll *task, s32 layer, s32 depth) {
    task->layer = layer;
    task->depth = depth;
}

NameScroll *STPLNMET_createScroll(void) {
    NameScroll *task = createTask(func_800828DC, sizeof(NameScroll), 0);

    task->load = STPLNMET_loadScroll;
    task->setLayer = STPLNMET_setScrollLayer;
    return task;
}

void func_80082B80(NameSparkle *task) {
    SpriteDrawer sprite;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->frame = 24;
        task->nextState(task);
        break;
    case TASK_RUN:
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x280, 0x100);
        sprite.setLayerId(0x1001, 6);
        if (GFX.funcs.getTime() - task->time > 4) {
            task->time = GFX.funcs.getTime();
            task->frame++;
            if (task->frame >= 36) {
                task->frame = 24;
            }
        }
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), task->frame, 0x33, 0);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), task->frame, 0x78, -0x14);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), task->frame, 0xA7, -0x58);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), task->frame, 0xF8, 0xD);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), task->frame, 0x120, 0);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

NameSparkle *func_80082D5C(void) {
    return createTask(func_80082B80, sizeof(NameSparkle), 0);
}

void func_80082D88(NameSparkle *task) {
    SpriteDrawer sprite;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x280, 0x100);
        sprite.setLayerId(0x1001, 6);
        if (GFX.funcs.getTime() - task->time > D_80087AB4[task->frame].delay) {
            task->time = GFX.funcs.getTime();
            task->frame++;
            if (D_80087AB4[task->frame].sprite == 0) {
                task->frame = 0;
            }
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_MENU), D_80087AB4[task->frame].sprite, 0, 0);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

NameSparkle *func_80082EE0(void) {
    return createTask(func_80082D88, sizeof(NameSparkle), 0);
}

void func_80082F0C(NameDialog *task, NameDialogWindows *windows) {
    SpriteDrawer sprite;

    switch (task->state) {
    case TASK_INIT:
    default:
        windows->text = createTextWindow(0x1001, 1, 0x42, 0x3B);
        windows->text->setLines(windows->text, 3);
        windows->arrow = createTextWindow(0x1001, 1, 0x42, 0x3B);
        task->nextState(task);
        task->setSubstate(task, 1);
        windows->arrow->setString(windows->arrow, FILE_CACHE_LOAD[0](TEXT_FILE(0x8E)), 2);
        windows->arrow->setPalette(windows->arrow, 1);
        windows->arrow->setVisible(windows->arrow, 0);
        windows->text->setTypeSound(windows->text, 0x800454C4);
        task->step = GFX.funcs.getTime();
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 1:
        default:
            if (GFX.funcs.getTime() - task->step > 5) {
                task->step = GFX.funcs.getTime();
                task->clutRow++;
                if (task->clutRow >= 4) {
                    task->clutRow = 3;
                    task->setSubstate(task, 2);
                    task->step = GFX.funcs.getTime();
                    windows->text->setString(windows->text, FILE_CACHE_LOAD[0](TEXT_FILE(0x8E)), 1);
                    windows->text->setPalette(windows->text, 1);
                    windows->text->setTypeDelay(windows->text, 6);
                    windows->arrow->setVisible(windows->arrow, 1);
                }
            }
            break;
        case 2:
            if (windows->text->isFinished(windows->text) != 0) {
                task->setSubstate(task, 3);
                task->step = GFX.funcs.getTime();
                task->clutRow = 4;
                windows->arrow->setVisible(windows->arrow, 0);
                windows->text->setVisible(windows->text, 0);
                break;
            }
            windows->arrow->setPos(windows->arrow, windows->text->cursorX + 0x42, windows->text->cursorY + 0x3B);
            if (windows->text->isWaitingForButton(windows->text) != 0) {
                if (windows->arrow->isVisible(windows->arrow) != 0) {
                    if (GFX.funcs.getTime() - task->step > 16) {
                        task->step = GFX.funcs.getTime();
                        windows->arrow->setVisible(windows->arrow, 0);
                    }
                } else if (GFX.funcs.getTime() - task->step > 8) {
                    task->step = GFX.funcs.getTime();
                    windows->arrow->setVisible(windows->arrow, 1);
                }
            } else {
                windows->arrow->setVisible(windows->arrow, 1);
                task->step = GFX.funcs.getTime();
            }
            if (PAD_PRESSED(PAD_CROSS)) {
                windows->text->showPage(windows->text);
            }
            break;
        case 3:
            if (GFX.funcs.getTime() - task->step > 5) {
                task->clutRow++;
                if (task->clutRow >= 8) {
                    task->clutRow = 7;
                    task->setState(task, TASK_KILL);
                }
            }
            break;
        }
        initSpriteDrawer(&sprite);
        sprite.setLayerId(0x1001, 5);
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 0x38, 0x4B, 0xB8);
        sprite.setClutRow(task->clutRow);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 0xF, 0x38, 0x2F);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

NameDialog *func_800834C0(s32 arg) {
    NameDialog *task = createTask(func_80082F0C, sizeof(NameDialog), 8);

    task->unk50 = arg;
    return task;
}

void STPLNMET_startTween(NameTween *fade, s32 fadeIn) {
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

s32 STPLNMET_updateTween(NameTween *fade) {
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

void STPLNMET_createNameWindows(PlayerNameTask *task, PlayerNameWindows *windows) {
    s32 i;

    windows->title = createTextWindow(task->layer, 1, 0x20, 0x1A);
    windows->title->setPalette(windows->title, 4);
    windows->name = createTextWindow(task->layer, 1, 0x4B, 0x40);
    windows->name->setSpacing(windows->name, 0x13, 0);
    windows->name->style = (u8 *)&STPLNMET_nameStyle;
    for (i = 0; i < 3; i++) {
        windows->tabs[i] = createTextWindow(task->layer, 1, 0x2F + i * 0x4E, 0x5B);
        windows->tabs[i]->setDepth(windows->tabs[i], task->depth - 1);
        windows->tabs[i]->setLines(windows->tabs[i], 7);
        windows->tabs[i]->setSpacing(windows->tabs[i], 0xE, 0x12);
        windows->tabs[i]->style = (u8 *)&STPLNMET_nameStyle;
    }
    windows->unk20 = createTextWindow(task->layer, 1, 0xCE, 0xC6);
    windows->unk24 = createTextWindow(task->layer, 1, 0xE1, 0xC6);
    windows->unk28 = createTextWindow(task->layer, 1, 0x13, 0x62);
    windows->unk28->setDepth(windows->unk28, task->depth - 1);
    windows->unk2C = createTextWindow(task->layer, 1, 0x123, 0x62);
    windows->unk2C->setDepth(windows->unk2C, task->depth - 1);
    windows->unk30 = createTextWindow(task->layer, 1, 0x3E, 0x72);
}

void func_800837E8(PlayerNameTask *task, PlayerNameWindows *windows, s32 show) {
    s32 i;

    if (show != 0) {
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x87)), 1);
        windows->name->setText(windows->name, task->name);
        windows->name->setPalette(windows->name, 1);
        for (i = 0; i < 3; i++) {
            windows->tabs[i]->setString(windows->tabs[i], FILE_CACHE.load(TEXT_FILE(0x87)), STPLNMET_keyboard.tabTexts[task->page].texts[i]);
            windows->tabs[i]->setPalette(windows->tabs[i], 1);
        }
        windows->unk20->setString(windows->unk20, FILE_CACHE.load(TEXT_FILE(0x87)), 0xD);
        windows->unk20->setPalette(windows->unk20, 1);
        windows->unk24->setString(windows->unk24, FILE_CACHE.load(TEXT_FILE(0x87)), 0xE);
        windows->unk24->setPalette(windows->unk24, 1);
        if (STPLNMET_keyboard.pageCount >= 2) {
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

/* Draws the keyboard, the cursor, the partner and the name entry's panels */
void STPLNMET_drawKeyboard(PlayerNameTask *task) {
    SpriteDrawer sprite;
    s32 i;
    s32 key;

    initSpriteDrawer(&sprite);
    sprite.setTexture(task->vramX, task->vramY);
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
                sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), 0x27, task->column * 14 + 0x2F + task->column / 5 * 8,
                            task->row * 18 + 0x5A);
            } else {
                for (i = 0; STPLNMET_keyboard.pages[task->page].cells[task->row][task->column + i].kind != 1; i--) {
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
                    STPLNMET_bigKeys[2].sprite = PLNMET_TEXT_SPRITE(0x3C);
                    break;
                case 0x55:
                    key = 3;
                    STPLNMET_bigKeys[3].sprite = PLNMET_TEXT_SPRITE(0x44);
                    break;
                case 0x67:
                    key = 4;
                    STPLNMET_bigKeys[4].sprite = PLNMET_TEXT_SPRITE(0x4C);
                    break;
                }
                sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), STPLNMET_bigKeys[key].sprite, STPLNMET_bigKeys[key].x,
                            STPLNMET_bigKeys[key].y);
            }
            sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), 0x28, task->cursor * 19 + 0x4B, 0x40);
            sprite.setClutRow(0);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setScale(task->unkCC.value, 0x1000, 0x1000);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setPivot(0x18, 0x20);
        }
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x1D, 0x18, 0x15);
        if (task->mode != 2) {
            if (task->unkCC.value != 0x1000) {
                sprite.setPivot(0x20, 0x3F);
            }
            if (task->partner != -1) {
                if (GFX.funcs.getTime() - task->partnerTime >= 13) {
                    task->partnerTime = GFX.funcs.getTime();
                    if (++task->partnerFrame >= 7 || STPLNMET_nameAnims[task->partner * 7 + task->partnerFrame] == -1) {
                        task->partnerFrame = 0;
                    }
                }
                sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), STPLNMET_nameAnims[task->partner * 7 + task->partnerFrame],
                            0x22, 0x30);
            } else {
                sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x36, 0x20, 0x2E);
            }
            if (GFX.funcs.getTime() - task->clutTime >= 5) {
                task->clutTime = GFX.funcs.getTime();
                if (++task->clutRow >= 14) {
                    task->clutRow = 0;
                }
            }
            sprite.setLayerId(task->layer, task->depth - 1);
            sprite.setClutRow(task->clutRow);
            sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x1F, 0x20, 0x2E);
            sprite.setClutRow(0);
            sprite.setLayerId(task->layer, task->depth);
            sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x1E, 0x20, 0x2E);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setPivot(0x20, 0x49);
        }
        if (task->mode != 2) {
            if (PLNMET_JAPANESE) {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), 0x34, 0x4B, 0x40);
            } else {
                sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), 0x37, 0x4B, 0x40);
            }
        } else {
            sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), 0x35, 0x4B, 0x40);
        }
        if (task->unkCC.value != 0x1000) {
            sprite.setScale(0x1000, task->unkCC.value, 0x1000);
        }
        if (STPLNMET_keyboard.pageCount >= 2) {
            if (GFX.funcs.getTime() - task->arrowTime >= 7) {
                task->arrowTime = GFX.funcs.getTime();
                if (++task->arrowFrame >= 6) {
                    task->arrowFrame = 0;
                }
            }
            sprite.setClutRow(STPLNMET_keyArrowCluts[task->arrowFrame]);
            sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x32, 0xA, 0x5E);
            sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x33, 0x119, 0x5E);
            sprite.setClutRow(0);
        }
        sprite.setClutRow(4);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x2C, 0xCB, 0xC3);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x2D, 0xDE, 0xC3);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), PLNMET_TEXT_SPRITE(0x3C), 0xCB, 0x99);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), PLNMET_TEXT_SPRITE(0x44), 0xCB, 0xAE);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), PLNMET_TEXT_SPRITE(0x4C), 0xF6, 0xC3);
        sprite.setClutRow(0);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), 0x25, 0x1D, 0x54);
    }
    sprite.setLayerId(task->layer, task->depth - 1);
    if (task->unkDC.value != 0) {
        if (task->unkDC.value != 0x1000) {
            sprite.setScale(0x1000, task->unkDC.value, 0x1000);
            sprite.setPivot(0, 0x78);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_BANK), 0x26, 0, 0x64);
    }
}

/* The keyboard's input: moving the cursor, turning the pages and typing the name */
void STPLNMET_updateKeyboard(PlayerNameTask *task, PlayerNameWindows *windows) {
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
        STPLNMET_startTween(&task->unkCC, 1);
        task->substate++;
        break;
    case 1:
        if (STPLNMET_updateTween(&task->unkCC)) {
            func_800837E8(task, windows, 1);
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
        if (STPLNMET_keyboard.pageCount >= 2) {
            page = task->page;
            if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) && PAD_PRESSED(PAD_L1)) {
                if (--task->page < 0) {
                    task->page = STPLNMET_keyboard.pageCount - 1;
                }
            } else if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_PRESSED(PAD_R1)) {
                if (++task->page > STPLNMET_keyboard.pageCount - 1) {
                    task->page = 0;
                }
            }
            if (page != task->page) {
                SOUND.playSound(0x4001B);
                func_800837E8(task, windows, 1);
                if (PLNMET_JAPANESE) {
                    newPage = task->page;
                    if (newPage == 0 || newPage == 1) {
                        while (STPLNMET_keyboard.pages[newPage].cells[task->row][task->column].kind != 1) {
                            if (--task->column < 0) {
                                task->column = 14;
                            }
                        }
                    } else {
                        while (STPLNMET_keyboard.pages[newPage].cells[task->row][task->column].kind == 0) {
                            if (--task->row < 0) {
                                task->row = 6;
                            }
                        }
                    }
                }
            }
        }
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            if (STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind < 0) {
                task->column += STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind;
            }
            do {
                if (--task->column < 0) {
                    task->column = 14;
                }
            } while (STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind != 1);
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            if (STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind < 0) {
                task->column += STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind;
            }
            do {
                if (++task->column >= 15) {
                    task->column = 0;
                }
            } while (STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind != 1);
            SOUND.playSound(0x4001B);
        }
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            do {
                if (--task->row < 0) {
                    task->row = 6;
                }
            } while (STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind == 0);
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            do {
                if (++task->row >= 7) {
                    task->row = 0;
                }
            } while (STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].kind == 0);
            SOUND.playSound(0x4001B);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            for (i = 0; STPLNMET_keyboard.pages[task->page].cells[task->row][task->column + i].kind != 1; i--) {
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
                if (task->cursor <= task->maxLength - 1 && task->name[task->cursor] == 0x4081) {
                    if (--task->cursor < 0) {
                        task->cursor = 0;
                    }
                }
                c = ((TextStyle *)windows->name->style)->iconMap[1].code;
                task->name[task->cursor] = (c >> 8) | ((c & 0xFF) << 8);
                windows->name->setText(windows->name, task->name);
                break;
            case 0x55:
                c = ((TextStyle *)windows->name->style)->iconMap[1].code;
                task->name[task->cursor] = (c >> 8) | ((c & 0xFF) << 8);
                if (++task->cursor > task->maxLength - 1) {
                    task->cursor = task->maxLength - 1;
                }
                windows->name->setText(windows->name, task->name);
                break;
            case 0x67:
                for (j = 0; j < task->maxLength; j++) {
                    if (task->name[j] != 0x4081 && task->name[j] != 0) {
                        for (j = 19; j >= 0; j--) {
                            if (task->name[j] != 0x4081) {
                                task->substate = 100;
                                return;
                            }
                            task->name[j] = 0;
                        }
                    }
                }
                task->substate = 20;
                break;
            default:
                glyph = ((TextStyle *)windows->name->style)
                            ->sjisMap[STPLNMET_keyboard.pages[task->page].cells[task->row][task->column].code]
                            .code;
                task->name[task->cursor] = (glyph >> 8) | ((glyph & 0xFF) << 8);
                windows->name->setText(windows->name, task->name);
                if (++task->cursor > task->maxLength - 1) {
                    task->cursor = task->maxLength - 1;
                    task->column = 13;
                    task->row = 6;
                }
                break;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            if (task->cursor <= task->maxLength - 1 && task->name[task->cursor] == 0x4081) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            }
            c = ((TextStyle *)windows->name->style)->iconMap[1].code;
            task->name[task->cursor] = (c >> 8) | ((c & 0xFF) << 8);
            windows->name->setText(windows->name, task->name);
        }
        break;
    case 10:
        func_800837E8(task, windows, 0);
        STPLNMET_startTween(&task->unkCC, 0);
        task->active = 0;
        task->substate++;
        break;
    case 11:
        if (STPLNMET_updateTween(&task->unkCC)) {
            task->state = TASK_DONE;
        }
        break;
    case 20:
        task->active = 0;
        STPLNMET_startTween(&task->unkDC, 1);
        task->substate++;
        break;
    case 21:
        if (STPLNMET_updateTween(&task->unkDC)) {
            windows->unk30->setString(windows->unk30, FILE_CACHE_LOAD[0](TEXT_FILE(0x87)), 0x12);
            task->substate++;
        }
        break;
    case 22:
        if (PAD_PRESSED(PAD_CROSS)) {
            windows->unk30->setVisible(windows->unk30, 0);
            STPLNMET_startTween(&task->unkDC, 0);
            task->substate++;
        }
        break;
    case 23:
        if (STPLNMET_updateTween(&task->unkDC)) {
            task->active = 1;
            task->substate = 2;
        }
        break;
    case 100:
        break;
    }
}

void STPLNMET_updateNameEntry(PlayerNameTask *task, PlayerNameWindows *windows) {
    TimLoader loader;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        initTimLoader(&loader);
        loader.setImagePos(task->vramX, task->vramY);
        loader.loadArchive(FILE_CACHE_GET_ENTRY[0](FILE_PLNMET_KEYBOARD << 16));
        if (PLNMET_JAPANESE) {
            STPLNMET_keyboard.pageCount = 3;
            STPLNMET_keyboard.tabTexts = STPLNMET_keyPagesJp;
            STPLNMET_keyboard.pages = STPLNMET_keyCharsJp;
        } else {
            STPLNMET_keyboard.pageCount = 1;
            STPLNMET_keyboard.tabTexts = STPLNMET_keyPages;
            STPLNMET_keyboard.pages = STPLNMET_keyChars;
        }
        task->unkBC.duration = 10;
        task->unkDC.duration = 10;
        task->unkCC.duration = 10;
        STPLNMET_createNameWindows(task, windows);
        break;
    case TASK_RUN:
        STPLNMET_updateKeyboard(task, windows);
        STPLNMET_drawKeyboard(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void STPLNMET_setNameVram(PlayerNameTask *task, s32 x, s32 y) {
    task->vramX = x;
    task->vramY = y;
}

void STPLNMET_setName(PlayerNameTask *task, char *name) {
    TextTools conv;
    s32 i;

    initTextTools(&conv);
    conv.convert(task->name, name, 0);
    for (i = strlen((char *)task->name) >> 1; i < task->maxLength; i++) {
        task->name[i] = 0x4081;
    }
}

void STPLNMET_getName(PlayerNameTask *task, char *out) {
    TextTools conv;
    s32 i;

    for (i = 0; i < task->maxLength * 2; i++) {
        out[i] = 0;
    }
    for (i = task->maxLength - 1; i >= 0 && task->name[i] == 0x4081; i--) {
        task->name[i] = 0;
    }
    for (i = 0; i < task->maxLength && task->name[i] == 0x4081; i++) {
    }
    initTextTools(&conv);
    conv.convert(out, &task->name[i], 1);
}

void func_800852CC(PlayerNameTask *task) {
    task->substate = 10;
}

void func_800852D8(PlayerNameTask *task, s32 hide) {
    PlayerNameWindows *windows = task->children;
    s32 i;

    if (hide != 0) {
        task->state = TASK_DONE;
        func_800837E8(task, windows, 0);
        for (i = task->maxLength - 1; i >= 0 && task->name[i] == 0x4081; i--) {
        }
        if (i == task->maxLength - 1) {
            task->cursor = i;
        } else {
            task->cursor = i + 1;
        }
    } else {
        task->state = TASK_RUN;
        task->substate = 2;
        func_800837E8(task, windows, 1);
    }
}

PlayerNameTask *STPLNMET_createNameEntry(char *name) {
    PlayerNameTask *task = createTask(STPLNMET_updateNameEntry, sizeof(PlayerNameTask), sizeof(PlayerNameWindows));

    task->getName = STPLNMET_getName;
    task->unkF0 = func_800852D8;
    task->unkF4 = func_800852CC;
    task->layer = 0x1001;
    task->depth = 6;
    task->mode = 0;
    task->partner = -1;
#if VERSION_US
    task->maxLength = 8;
#elif VERSION_EU
    /* five full-width characters in Japanese */
    if (LANGUAGE == 0) {
        task->maxLength = 5;
    } else {
        task->maxLength = 8;
    }
#endif
    STPLNMET_setName(task, name);
    STPLNMET_setNameVram(task, 0x140, 0x100);
    return task;
}

void func_80085434(NameConfirm *task, NameConfirmWindows *windows) {
    windows->title = createTextWindow(task->layer, 1, 0x20, 0x1A);
    windows->title->setPalette(windows->title, 4);
    windows->name = createTextWindow(task->layer, 1, 0x61, 0x42);
    windows->name->setPalette(windows->name, 1);
    windows->unk8 = createTextWindow(task->layer, 1, 0x40, 0x60);
    windows->unk8->setPalette(windows->unk8, 1);
    windows->unkC = createTextWindow(task->layer, 1, 0x5A, 0xA9);
    windows->unkC->setPalette(windows->unkC, 1);
    windows->yes = createTextWindow(task->layer, 1, 0x6B, 0xB9);
    windows->yes->setPalette(windows->yes, 1);
    windows->no = createTextWindow(task->layer, 1, 0x6B, 0xC7);
    windows->no->setPalette(windows->no, 1);
    windows->cursor = createCursor(task->layer, task->depth - 2, 0x5A, 0xB9);
    windows->cursor->setPalette(windows->cursor, 1);
    windows->cursor->setVisible(windows->cursor, 0);
    windows->unk10 = createTextWindow(task->layer, 1, 0xE3, 0xA9);
    windows->unk10->setPalette(windows->unk10, 1);
}

void func_800855DC(NameConfirm *task, NameConfirmWindows *windows, s32 show) {
    u16 *name;
    s32 i;

    if (show != 0) {
        windows->title->setString(windows->title, FILE_CACHE_LOAD[0](TEXT_FILE(0x8E)), 0x15);
        name = task->name;
        for (i = 0; name[i] == 0x4081; i++) {
        }
        windows->name->setText(windows->name, &name[i]);
        windows->unk8->setString(windows->unk8, FILE_CACHE.load(TEXT_FILE(0x8E)), task->choice + 10);
        windows->unkC->setString(windows->unkC, FILE_CACHE.load(TEXT_FILE(0x8E)), 0x16);
        windows->yes->setString(windows->yes, FILE_CACHE.load(TEXT_FILE(0x8E)), 0x17);
        windows->no->setString(windows->no, FILE_CACHE.load(TEXT_FILE(0x8E)), 0x18);
        windows->cursor->setPos(windows->cursor, 0x5A, task->cursor * 14 + 0xB9);
        windows->cursor->setVisible(windows->cursor, 1);
    } else {
        windows->title->setVisible(windows->title, 0);
        windows->name->setVisible(windows->name, 0);
        windows->unk8->setVisible(windows->unk8, 0);
        windows->unkC->setVisible(windows->unkC, 0);
        windows->yes->setVisible(windows->yes, 0);
        windows->no->setVisible(windows->no, 0);
        windows->cursor->setVisible(windows->cursor, 0);
        windows->unk10->setVisible(windows->unk10, 0);
    }
}

void func_80085834(NameConfirm *task) {
    SpriteDrawer sprite;
    SVECTOR out[4];
    SVECTOR in[4];
    s32 *partners;
    PartnerAnim *anim;
    POLY_G4 *poly;
    u_long *ot;
    Layer *layer;
    s32 i;
    s32 j;

    partners = STPLNMET_funcs.choices[task->choice];
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    if (GFX.funcs.getTime() - task->clutTime > 4) {
        task->clutTime = GFX.funcs.getTime();
        task->clutRow++;
        if (task->clutRow >= 14) {
            task->clutRow = 0;
        }
    }
    if (task->tweenA.level != 0) {
        if (task->tweenA.level != 0x1000) {
            sprite.setScale(task->tweenA.level, 0x1000, 0x1000);
            sprite.setPivot(0x37, 0x42);
        }
        sprite.setLayerId(task->layer, task->depth);
        sprite.setClutRow(task->clutRow);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 6, 0x37, 0x2F);
        sprite.setClutRow(0);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 2, 0x37, 0x2F);
    }
    if (GFX.funcs.getTime() - task->frameTime > 12) {
        task->frameTime = GFX.funcs.getTime();
        for (i = 0; i < 3; i++) {
            anim = &STPLNMET_funcs.anims[partners[i]];
            task->frames[i]++;
            if (task->frames[i] >= 8 || anim->frames[task->frames[i]] == -1) {
                task->frames[i] = 0;
            }
        }
    }
    if (task->tweenB.level != 0) {
        sprite.setLayerId(task->layer, task->depth);
        if (task->tweenB.level == 0x1000) {
            sprite.setTexture(0x140, 0x100);
            for (i = 0; i < 3; i++) {
                anim = &STPLNMET_funcs.anims[partners[i]];
                sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), anim->frames[task->frames[i]], 0x57 + i * 0x38, 0x6C);
            }
        }
        sprite.setTexture(0x280, 0x100);
        if (task->tweenB.level != 0x1000) {
            sprite.setScale(0x1000, task->tweenB.level, 0x1000);
            sprite.setPivot(0xA0, 0x78);
        }
        sprite.setLayerId(task->layer, task->depth - 1);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 10, 0x37, 0x59);
        sprite.setLayerId(task->layer, task->depth);
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 9, 0x37, 0x59);
        if (task->tweenB.level != 0x1000) {
            sprite.setPivot(0xA0, 0xBE);
        }
        sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 1, 0, 0xA2);
    }
    if (task->substate == 1 || task->substate == 2) {
        sprite.setLayerId(task->layer, task->depth - 1);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_MENU), 0x37, 0x51, 0xBF);
        task->scale.vy = task->scale.vz = 0x1000;
        if (task->progress == 100) {
            task->scale.vx = 0x1000;
        } else {
            task->scale.vx = task->progress * 41;
        }
        RotMatrixYXZ_gte(&task->rot, &task->matrix);
        ScaleMatrix(&task->matrix, &task->scale);
        layer = GFX.funcs.getLayer(task->layer);
        ot = (u_long *)layer->getOtEntry(layer, task->depth - 1);
        poly = GFX.funcs.getPrim();
        setPolyG4(poly);
        setRGB0(poly, 0x7F, 0x32, 0xF2);
        setRGB1(poly, 0xD1, 0x2F, 0xDE);
        setRGB2(poly, 0x7F, 0x32, 0xF2);
        setRGB3(poly, 0xD1, 0x2F, 0xDE);
        in[1].vx = in[3].vx = 0x98;
        in[0].vy = in[1].vy = 0xBC;
        in[0].vx = in[2].vx = 0;
        in[2].vy = in[3].vy = 0xC8;
        in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
        for (j = 0; j < 4; j++) {
            ApplyMatrixSV(&task->matrix, &in[j], &out[j]);
            out[j].vx += 0x54;
            out[j].vy += 6;
        }
        setXY4(poly, out[0].vx, out[0].vy, out[1].vx, out[1].vy, out[2].vx, out[2].vy, out[3].vx, out[3].vy);
        addPrim(ot, poly);
        GFX.funcs.setPrim(poly + 1);
    }
}

void func_80085F0C(NameConfirm *task, NameConfirmWindows *windows) {
    s32 old;

    switch (task->substate) {
    case 0:
    default:
        old = task->cursor;
        if (PAD_PRESSED(PAD_UP)) {
            task->cursor = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            task->cursor = 1;
        }
        if (old != task->cursor) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0x5A, task->cursor * 14 + 0xB9);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (task->cursor == 0) {
                task->substate = 1;
                task->progress = 0;
                windows->yes->setVisible(windows->yes, 0);
                windows->no->setVisible(windows->no, 0);
                windows->cursor->setVisible(windows->cursor, 0);
                windows->unkC->setString(windows->unkC, FILE_CACHE.load(TEXT_FILE(0x8E)), 0x1D);
                windows->unk10->setString(windows->unk10, FILE_CACHE.load(TEXT_FILE(0x8E)), 0x19);
                windows->unk10->setNumber(windows->unk10, 1, task->progress);
                windows->unk10->setRightAlign(windows->unk10, 1);
            } else {
                task->substate = 200;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            task->substate = 200;
        }
        break;
    case 1:
        task->progress++;
        if (task->progress > 100) {
            task->progress = 100;
            windows->unkC->setString(windows->unkC, FILE_CACHE_LOAD[0](TEXT_FILE(0x8E)), 0x1E);
            SOUND.playSound(0x80045341);
            task->nextSubstate(task);
        } else {
            SOUND.playSound(0x800452C6);
        }
        windows->unk10->setNumber(windows->unk10, 1, task->progress);
        windows->unk10->setRightAlign(windows->unk10, 1);
        break;
    case 2:
        task->step++;
        if (task->step > 120) {
            task->substate = 100;
        }
        break;
    case 50:
        STPLNMET_funcs.startFade(&task->tweenA, 0);
        STPLNMET_funcs.startFade(&task->tweenB, 0);
        func_800855DC(task, windows, 0);
        task->substate++;
        break;
    case 51:
        STPLNMET_funcs.updateFade(&task->tweenA);
        if (STPLNMET_funcs.updateFade(&task->tweenB) != 0) {
            task->state = TASK_KILL;
        }
        break;
    case 100:
    case 200:
        break;
    }
}

void func_80086370(NameConfirm *task, s32 hide) {
    NameConfirmWindows *windows = task->children;
    s32 i;

    if (hide != 0) {
        task->state = TASK_DONE;
        func_800855DC(task, windows, 0);
    } else {
        task->state = TASK_RUN;
        task->substate = 0;
        for (i = 2; i >= 0; i--) {
            task->frames[i] = 0;
        }
        task->cursor = 0;
        func_800855DC(task, windows, 1);
    }
}

void func_800863DC(NameConfirm *task) {
    task->substate = 50;
}

void func_800863E8(NameConfirm *task, NameConfirmWindows *windows) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        func_80085434(task, windows);
        task->tweenA.duration = 10;
        task->tweenA.level = 0x1000;
        task->tweenB.duration = 10;
        task->tweenB.level = 0x1000;
        func_80086370(task, 1);
        break;
    case TASK_RUN:
        func_80085F0C(task, windows);
        func_80085834(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

NameConfirm *func_80086490(s32 arg) {
    NameConfirm *task = createTask(func_800863E8, sizeof(NameConfirm), sizeof(NameConfirmWindows));

    task->hide = func_80086370;
    task->unkE0 = func_800863DC;
    task->layer = 0x1001;
    task->depth = 6;
    task->unk50 = arg;
    return task;
}

void func_800864F0(PartnerChoice *task, PartnerChoiceWindows *windows) {
    s32 i;

    windows->title = createTextWindow(task->layer, 1, 0x20, 0x1A);
    windows->title->setPalette(windows->title, 4);
    for (i = 0; i < 3; i++) {
        windows->labels[i] = createTextWindow(task->layer, 1, 0x1A, 0x34 + i * 0x18);
        windows->labels[i]->setPalette(windows->labels[i], 1);
    }
    windows->name = createTextWindow(task->layer, 1, 0x3A, 0x32);
    windows->name->setPalette(windows->name, 4);
    windows->text = createTextWindow(task->layer, 1, 0x3A, 0xC2);
    windows->text->setLines(windows->text, 3);
    windows->text->setPalette(windows->text, 1);
    for (i = 0; i < 3; i++) {
        windows->partners[i].name = createTextWindow(task->layer, 2, 0x72, 0x43 + i * 0x2A);
        windows->partners[i].name->setPalette(windows->partners[i].name, 5);
        windows->partners[i].text = createTextWindow(task->layer, 1, 0x72, 0x4F + i * 0x2A);
        windows->partners[i].text->setLines(windows->partners[i].text, 2);
        windows->partners[i].text->setPalette(windows->partners[i].text, 1);
    }
}

void func_800866C0(PartnerChoice *task, PartnerChoiceWindows *windows, s32 show) {
    s32 i;
    s32 *partners;

    if (show != 0) {
        partners = STPLNMET_funcs.choices[task->choice];
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x8E)), 6);
        for (i = 0; i < 3; i++) {
            windows->labels[i]->setString(windows->labels[i], FILE_CACHE.load(TEXT_FILE(0x8E)), i + 7);
        }
        windows->name->setString(windows->name, FILE_CACHE.load(TEXT_FILE(0x8E)), task->choice + 10);
        windows->text->setString(windows->text, FILE_CACHE.load(TEXT_FILE(0x8E)), task->choice + 26);
        for (i = 0; i < 3; i++) {
            windows->partners[i].name->setString(windows->partners[i].name, FILE_CACHE.load(TEXT_FILE(0x4F)), partners[i] + 1);
            windows->partners[i].text->setString(windows->partners[i].text, FILE_CACHE.load(TEXT_FILE(0x8E)), partners[i] + 13);
        }
        return;
    }
    windows->title->setVisible(windows->title, 0);
    for (i = 0; i < 3; i++) {
        windows->labels[i]->setVisible(windows->labels[i], 0);
    }
    windows->name->setVisible(windows->name, 0);
    windows->text->setVisible(windows->text, 0);
    for (i = 0; i < 3; i++) {
        windows->partners[i].name->setVisible(windows->partners[i].name, 0);
        windows->partners[i].text->setVisible(windows->partners[i].text, 0);
    }
}

void func_80086944(PartnerChoice *task) {
    SpriteDrawer sprite;
    s32 *partners = STPLNMET_funcs.choices[task->choice];
    PartnerAnim *anim;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layer, task->depth);
    if (GFX.funcs.getTime() - task->frameTime > 12) {
        task->frameTime = GFX.funcs.getTime();
        for (i = 0; i < 3; i++) {
            anim = &STPLNMET_funcs.anims[partners[i]];
            task->frames[i]++;
            if (task->frames[i] >= 8 || anim->frames[task->frames[i]] == -1) {
                task->frames[i] = 0;
            }
        }
    }
    sprite.setTexture(0x140, 0x100);
    for (i = 0; i < 3; i++) {
        anim = &STPLNMET_funcs.anims[partners[i]];
        sprite.draw(FILE_CACHE.getEntry(PLNMET_BANK), anim->frames[task->frames[i]], 0x41, 0x40 + i * 0x2A);
    }
    sprite.setTexture(0x280, 0x100);
    sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 7, 0x10, 0x2C);
    sprite.setLayerId(task->layer, task->depth - 1);
    sprite.draw(FILE_CACHE.getEntry(PLNMET_MENU), 8, 0x10, 0x2C);
    if (GFX.funcs.getTime() - task->arrowTime > 8) {
        task->arrowTime = GFX.funcs.getTime();
        task->arrowFrame++;
        if (task->arrowFrame >= 6) {
            task->arrowFrame = 0;
        }
    }
    sprite.setClutRow(D_80088F30[task->arrowFrame]);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_MENU), 0x32, 0x10, 0x30 + task->choice * 0x18);
}

void func_80086C74(PartnerChoice *task, PartnerChoiceWindows *windows) {
    s32 old = task->choice;
    s32 i;

    if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
        task->choice--;
        if (task->choice < 0) {
            task->choice = 0;
        }
    } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
        task->choice++;
        if (task->choice > 2) {
            task->choice = 2;
        }
    }
    if (old != task->choice) {
        SOUND.playSound(0x4001B);
        func_800866C0(task, windows, 1);
        for (i = 2; i >= 0; i--) {
            task->frames[i] = 0;
        }
    }
    if (PAD_PRESSED(PAD_CROSS)) {
        SOUND.playSound(0x4001C);
        task->substate = 100;
        return;
    }
    if (PAD_PRESSED(PAD_TRIANGLE)) {
        SOUND.playSound(0x800450BD);
        task->substate = 200;
        task->choice = 0;
    }
}

void func_80086EE0(PartnerChoice *task, s32 hide) {
    PartnerChoiceWindows *windows = task->children;

    if (hide != 0) {
        task->state = TASK_DONE;
        func_800866C0(task, windows, 0);
    } else {
        task->state = TASK_RUN;
        task->substate = 0;
        func_800866C0(task, windows, 1);
    }
}

void func_80086F30(PartnerChoice *task, PartnerChoiceWindows *windows) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        func_800864F0(task, windows);
        func_80086EE0(task, 1);
        break;
    case TASK_RUN:
        func_80086C74(task, windows);
        func_80086944(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

PartnerChoice *func_80086FC0(s32 arg) {
    PartnerChoice *task = createTask(func_80086F30, sizeof(PartnerChoice), sizeof(PartnerChoiceWindows));

    task->hide = func_80086EE0;
    task->layer = 0x1001;
    task->depth = 6;
    task->unk50 = arg;
    return task;
}

void func_80087014(PlayerNameScreen *screen, PlayerNameScreenChildren *children) {
    s32 i;

    for (i = 0; i < 3; i++) {
        children->tabs[i] = createTextWindow(screen->layer, 3, D_80088F48[i], 0x12);
        children->tabs[i]->setString(children->tabs[i], FILE_CACHE.load(TEXT_FILE(0x8E)), i + 3);
        children->tabs[i]->setPalette(children->tabs[i], 1);
        children->tabs[i]->setVisible(children->tabs[i], 0);
    }
}

void func_800870EC(PlayerNameScreen *screen, PlayerNameScreenChildren *children, s32 show) {
    s32 i;

    for (i = 0; i < 3; i++) {
        children->tabs[i]->setVisible(children->tabs[i], show);
        if (screen->page == i) {
            children->tabs[i]->setPalette(children->tabs[i], 0);
        } else {
            children->tabs[i]->setPalette(children->tabs[i], 1);
        }
    }
}

void func_80087194(PlayerNameScreen *screen, PlayerNameScreenChildren *children) {
    switch (screen->substate) {
    case 0:
        children->scroll = STPLNMET_createScroll();
        children->scroll->load(children->scroll, 0x1C0, 0x100);
        children->scroll->setLayer(children->scroll, screen->layer, 6);
        children->sparkleA = func_80082D5C();
        children->sparkleB = func_80082EE0();
        children->dialog = func_800834C0((s32)screen);
        screen->substate++;
        break;
    case 1:
        if (children->dialog == NULL) {
            STPLNMET_funcs.startFade(&screen->fade, 1);
            children->name = STPLNMET_createNameEntry(PLAYER_NAME);
            children->partners = func_80086FC0((s32)screen);
            children->confirm = func_80086490((s32)screen);
            screen->page = 0;
            screen->nextSubstate(screen);
        }
        break;
    case 2:
        switch (screen->step) {
        case 0:
        default:
            if (STPLNMET_funcs.updateFade(&screen->fade) != 0) {
                func_800870EC(screen, children, 1);
            }
            if (children->name->substate == 100) {
                children->name->unkF0(children->name, 1);
                children->partners->hide(children->partners, 0);
                screen->page = 1;
                func_800870EC(screen, children, 1);
                screen->step++;
            }
            break;
        case 1:
            if (children->partners->substate == 100) {
                children->partners->hide(children->partners, 1);
                children->confirm->choice = children->partners->choice;
                children->confirm->name = children->name->name;
                children->confirm->hide(children->confirm, 0);
                screen->page = 2;
                func_800870EC(screen, children, 1);
                screen->step++;
            } else if (children->partners->substate == 200) {
                children->partners->hide(children->partners, 1);
                children->name->unkF0(children->name, 0);
                screen->page = 0;
                func_800870EC(screen, children, 1);
                screen->step--;
            }
            break;
        case 2:
            if (children->confirm->substate == 100) {
                children->confirm->unkE0(children->confirm);
                STPLNMET_funcs.startFade(&screen->fade, 0);
                func_800870EC(screen, children, 0);
                screen->step++;
            } else if (children->confirm->substate == 200) {
                children->confirm->hide(children->confirm, 1);
                children->partners->hide(children->partners, 0);
                screen->page = 1;
                func_800870EC(screen, children, 1);
                screen->step--;
            }
            break;
        case 3:
            if (STPLNMET_funcs.updateFade(&screen->fade) != 0 && children->confirm == NULL) {
                children->name->getName(children->name, GAME.name);
                GAME.funcs.setParty(children->partners->choice);
                screen->state = TASK_KILL;
            }
            break;
        }
        break;
    }
}

void func_80087568(PlayerNameScreen *screen) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    sprite.setLayerId(screen->layer, screen->depth);
    if (screen->fade.level != 0) {
        if (screen->fade.level != 0x1000) {
            sprite.setScale(screen->fade.level, 0x1000, 0x1000);
            sprite.setPivot(0x18, 0x20);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](PLNMET_MENU), screen->page + 12, 0x18, 0x15);
    }
}

void func_80087630(PlayerNameScreen *screen, PlayerNameScreenChildren *children) {
    switch (screen->state) {
    case TASK_INIT:
    default:
        switch (screen->substate) {
        case 0:
        default:
            STPLNMET_funcs.loadFiles();
            SOUND_STATE.loadBank(0x20);
            screen->substate++;
            break;
        case 1:
            if (STPLNMET_funcs.filesLoading() == 0) {
                func_80087014(screen, children);
                screen->fade.duration = 10;
                screen->setState(screen, TASK_DONE);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_80087194(screen, children);
        func_80087568(screen);
        break;
    case TASK_DONE:
        if (SOUND_STATE.isLoading() == 0) {
            SOUND_STATE.playSound(0x60800000);
            screen->setState(screen, TASK_RUN);
        }
        break;
    case TASK_KILL:
        SOUND_STATE.stopSound(0x60800000);
        GAME.funcs.requestMode(0x2D8, 0);
        break;
    }
}

Task *STPLNMET_createScreen(void) {
    PlayerNameScreen *screen = createTask(func_80087630, sizeof(PlayerNameScreen), 0x28);

    screen->layer = 0x1001;
    screen->depth = 5;
    return (Task *)screen;
}

void STPLNMET_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry(FILE_PLNMET_SPRITES << 16));
    FILE_CACHE.request(TEXT_FILE(0x8E));
    FILE_CACHE.request(TEXT_FILE(0x4F));
    FILE_CACHE.request(TEXT_FILE(0x87));
    FILE_CACHE.request(FILE_PLNMET_KEYBOARD);
}

s32 STPLNMET_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x8E)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x4F)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x87)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(FILE_PLNMET_KEYBOARD) != 0;
}

void STPLNMET_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STPLNMET_updateFade(PanelAnim *fade) {
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

void STPLNMET_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STPLNMET_updateLerp(MenuLerp *lerp) {
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

/* the executable's Shift-JIS maps of its fonts */
extern GlyphMap D_8004D7B8[];
extern GlyphMap D_8004DB64[];

s32 D_80087AAC[] = {
    -176, -190,
};
SparkleFrame D_80087AB4[] = {
    { 4, 60 },
    { 4, 61 },
    { 4, 62 },
    { 4, 63 },
    { 4, 64 },
    { 4, 65 },
    { 4, 66 },
    { 4, 67 },
    { 4, 68 },
    { 80, 69 },
    { 4, 60 },
    { 4, 70 },
    { 4, 71 },
    { 4, 72 },
    { 4, 73 },
    { 4, 74 },
    { 4, 75 },
    { 4, 68 },
    { 4, 60 },
    { 4, 61 },
    { 4, 62 },
    { 4, 63 },
    { 4, 64 },
    { 4, 65 },
    { 4, 66 },
    { 4, 67 },
    { 4, 68 },
    { 56, 69 },
    { 0, 0 },
};
/* The name font (STPLNMET_nameStyle): its glyphs and icons */
#if VERSION_US
Glyph STPLNMET_nameGlyphs[230] = {
    { 0x01, 96, 18, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 104, 18, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 112, 18, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 120, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 128, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 136, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 144, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 152, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 160, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 168, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 176, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 184, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 192, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 200, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 208, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 216, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 224, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 232, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 32, 63, 48, 232, 4, 12, 5, 3, 3, 12 },
    { 0x01, 240, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 0, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 8, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 16, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 24, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 32, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 40, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 48, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 56, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 64, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 72, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 80, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 88, 30, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x01, 96, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 104, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 112, 30, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x01, 120, 33, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 128, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 136, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 144, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 152, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 160, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 168, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 176, 33, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 184, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 36, 63, 48, 232, 4, 12, 7, 3, 1, 12 },
    { 0x01, 40, 63, 48, 232, 4, 12, 5, 3, 4, 12 },
    { 0x01, 192, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 44, 63, 48, 232, 4, 12, 6, 3, 3, 12 },
    { 0x01, 200, 33, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 208, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 216, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 224, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 232, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 48, 63, 48, 232, 4, 12, 6, 3, 4, 12 },
    { 0x01, 240, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 52, 63, 48, 232, 4, 12, 6, 3, 4, 12 },
    { 0x01, 0, 42, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x01, 8, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 16, 42, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 24, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 32, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 40, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x00, 216, 74, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 228, 74, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 240, 74, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 0, 76, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 12, 76, 48, 232, 12, 12, 4, 3, 6, 12 },
    { 0x00, 24, 76, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 36, 76, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 48, 76, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 60, 76, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 156, 77, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 168, 77, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 72, 78, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 84, 84, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 96, 84, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 108, 84, 48, 232, 12, 12, 3, 3, 6, 12 },
    { 0x00, 120, 84, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 132, 86, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 86, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 192, 86, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 204, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 216, 86, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 228, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 240, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 0, 88, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 12, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 36, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 48, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 60, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 156, 89, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 168, 89, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 72, 90, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 84, 96, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 96, 96, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 108, 96, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 120, 96, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 98, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 98, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 180, 98, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 192, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 204, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 216, 98, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 228, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 240, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 0, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 12, 100, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 36, 100, 48, 232, 12, 12, 3, 3, 11, 12 },
    { 0x00, 48, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 60, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 101, 48, 232, 12, 12, 3, 3, 10, 9 },
    { 0x00, 168, 101, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 72, 102, 48, 232, 12, 12, 2, 3, 10, 12 },
    { 0x00, 84, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 120, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 110, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 192, 110, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 204, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 216, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 228, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 240, 110, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 0, 112, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 12, 112, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 24, 112, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 36, 112, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 112, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 60, 112, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 156, 113, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 168, 113, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 72, 114, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 120, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 120, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 108, 120, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 120, 120, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 122, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 122, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 122, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 192, 122, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 204, 122, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 216, 122, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 228, 122, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 240, 122, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 0, 124, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 12, 124, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 24, 124, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 36, 124, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 124, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 60, 124, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 125, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 168, 125, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 72, 126, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 132, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 132, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 132, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 120, 132, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 132, 134, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 134, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 134, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 116, 176, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 156, 176, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 128, 179, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 140, 179, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 232, 83, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 0, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 12, 136, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 36, 136, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 48, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 60, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 137, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 168, 137, 48, 232, 12, 12, 3, 3, 7, 12 },
    { 0x00, 72, 138, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 48, 42, 48, 232, 8, 12, 4, 3, 5, 12 },
    { 0x01, 56, 42, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x00, 120, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 146, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 144, 146, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 180, 146, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x01, 0, 84, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x01, 12, 84, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x01, 204, 84, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 64, 160, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 216, 84, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 0, 148, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 12, 148, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 148, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 36, 148, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 148, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 60, 148, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 149, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 168, 149, 48, 232, 12, 12, 2, 3, 10, 12 },
    { 0x00, 72, 150, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 120, 156, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 132, 158, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 144, 158, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 180, 158, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 88, 69, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x01, 100, 69, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 112, 71, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x01, 124, 71, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 136, 71, 48, 232, 12, 12, 4, 3, 6, 12 },
    { 0x00, 0, 160, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 12, 160, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 160, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 36, 160, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 160, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 60, 160, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 156, 161, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 168, 161, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 72, 162, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 84, 168, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 96, 168, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 136, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x01, 160, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x00, 248, 56, 48, 232, 4, 12, 5, 3, 4, 12 },
    { 0x01, 176, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x00, 96, 60, 48, 232, 12, 12, 4, 3, 9, 12 },
};
#elif VERSION_EU
Glyph STPLNMET_nameGlyphs[230] = {
    { 0x01, 96, 18, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 104, 18, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 112, 18, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 120, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 128, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 136, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 144, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 152, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 160, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 168, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 176, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 184, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 192, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 200, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 208, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 216, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 224, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 232, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 32, 63, 48, 232, 4, 12, 5, 3, 3, 12 },
    { 0x01, 240, 21, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 0, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 8, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 16, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 24, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 32, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 40, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 48, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 56, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 64, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 72, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 80, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 88, 30, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x01, 96, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 104, 30, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 112, 30, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x01, 120, 33, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 128, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 136, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 144, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 152, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 160, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 168, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 176, 33, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 184, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 36, 63, 48, 232, 4, 12, 7, 3, 1, 12 },
    { 0x01, 124, 185, 48, 232, 4, 12, 5, 3, 4, 12 },
    { 0x01, 192, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x00, 248, 62, 48, 232, 4, 12, 6, 3, 3, 12 },
    { 0x01, 200, 33, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 208, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 216, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 224, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 232, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 212, 120, 48, 232, 4, 12, 6, 3, 4, 12 },
    { 0x01, 240, 33, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 204, 71, 48, 232, 4, 12, 6, 3, 4, 12 },
    { 0x01, 0, 42, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x01, 8, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 16, 42, 48, 232, 8, 12, 4, 3, 6, 12 },
    { 0x01, 24, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 32, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 40, 42, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x00, 216, 74, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 228, 74, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 240, 74, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 0, 76, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 12, 76, 48, 232, 12, 12, 4, 3, 6, 12 },
    { 0x00, 24, 76, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 36, 76, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 48, 76, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 60, 76, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 156, 77, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 168, 77, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 72, 78, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 84, 84, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 96, 84, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 108, 84, 48, 232, 12, 12, 3, 3, 6, 12 },
    { 0x00, 120, 84, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 132, 84, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 86, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 192, 86, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 204, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 216, 86, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 228, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 240, 86, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 0, 88, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 12, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 36, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 48, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 60, 88, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 156, 89, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 168, 89, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 72, 90, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 84, 96, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 96, 96, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 108, 96, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 120, 96, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 96, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 98, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 180, 98, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 192, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 204, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 216, 98, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 228, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 240, 98, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 0, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 12, 100, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 36, 100, 48, 232, 12, 12, 3, 3, 11, 12 },
    { 0x00, 48, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 60, 100, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 101, 48, 232, 12, 12, 3, 3, 10, 9 },
    { 0x00, 168, 101, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 72, 102, 48, 232, 12, 12, 2, 3, 10, 12 },
    { 0x00, 84, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 120, 108, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 108, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 192, 110, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 204, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 216, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 228, 110, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 240, 110, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 0, 112, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 12, 112, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 24, 112, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 36, 112, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 112, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 60, 112, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 156, 113, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 168, 113, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 72, 114, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 120, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 120, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 108, 120, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 120, 120, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 120, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 122, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 122, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 192, 122, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 204, 122, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 216, 122, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 228, 122, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 240, 122, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 0, 124, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 12, 124, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 24, 124, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 36, 124, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 124, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 60, 124, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 125, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 168, 125, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 72, 126, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 132, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 132, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 132, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 120, 132, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 132, 132, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 144, 134, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 180, 134, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 88, 201, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 184, 83, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 220, 83, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 208, 83, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 232, 83, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 0, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 12, 136, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 36, 136, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 48, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 60, 136, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 137, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 168, 137, 48, 232, 12, 12, 3, 3, 7, 12 },
    { 0x00, 72, 138, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 48, 42, 48, 232, 8, 12, 4, 3, 5, 12 },
    { 0x01, 56, 42, 48, 232, 8, 12, 5, 3, 6, 12 },
    { 0x00, 120, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 132, 144, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 144, 146, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 180, 146, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x01, 0, 87, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x01, 12, 87, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 180, 170, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 88, 230, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 208, 71, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 0, 148, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 12, 148, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 148, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 36, 148, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 148, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 60, 148, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 156, 149, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 168, 149, 48, 232, 12, 12, 2, 3, 10, 12 },
    { 0x00, 72, 150, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 84, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 96, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 120, 156, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 132, 156, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 144, 158, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 180, 158, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 196, 83, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x01, 88, 242, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 24, 243, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 36, 243, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 212, 193, 48, 232, 12, 12, 4, 3, 6, 12 },
    { 0x00, 0, 160, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 12, 160, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 24, 160, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 36, 160, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 48, 160, 48, 232, 12, 12, 4, 3, 8, 12 },
    { 0x00, 60, 160, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 156, 161, 48, 232, 12, 12, 4, 3, 7, 12 },
    { 0x00, 168, 161, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 72, 162, 48, 232, 12, 12, 3, 3, 8, 12 },
    { 0x00, 84, 168, 48, 232, 12, 12, 3, 3, 9, 12 },
    { 0x00, 96, 168, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x01, 136, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x01, 160, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x01, 200, 156, 48, 232, 4, 12, 5, 3, 4, 12 },
    { 0x01, 176, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x00, 96, 60, 48, 232, 12, 12, 4, 3, 9, 12 },
};
#endif
#if VERSION_US
Glyph STPLNMET_nameIcons[114] = {
    { 0x00, 244, 20, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x00, 244, 32, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x00, 244, 44, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 120, 9, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 128, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 136, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x01, 144, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 152, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 160, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x00, 248, 56, 48, 232, 4, 12, 5, 3, 4, 12 },
    { 0x01, 248, 9, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 168, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 176, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 184, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 192, 9, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x01, 200, 9, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x00, 96, 60, 48, 232, 12, 12, 4, 3, 9, 12 },
    { 0x00, 108, 60, 48, 232, 12, 12, 3, 3, 12, 12 },
    { 0x01, 204, 129, 48, 232, 8, 12, 3, 3, 12, 12 },
    { 0x01, 208, 9, 48, 232, 8, 12, 3, 3, 11, 12 },
    { 0x01, 248, 21, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 248, 33, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 248, 45, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 248, 57, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 216, 9, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 224, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 232, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 240, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 0, 18, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x01, 8, 18, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x01, 16, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 24, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 32, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 40, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x00, 120, 60, 48, 232, 12, 12, 3, 3, 12, 12 },
    { 0x00, 236, 62, 48, 232, 12, 12, 3, 3, 12, 12 },
    { 0x00, 144, 62, 48, 161, 12, 12, 3, 3, 12, 12 },
    { 0x00, 188, 62, 48, 160, 12, 12, 3, 3, 12, 12 },
    { 0x00, 200, 62, 48, 159, 12, 12, 3, 3, 12, 12 },
    { 0x00, 212, 62, 48, 158, 12, 12, 3, 3, 12, 12 },
    { 0x00, 224, 62, 48, 157, 12, 12, 3, 3, 12, 12 },
    { 0x01, 48, 18, 48, 232, 8, 12, 3, 3, 12, 12 },
    { 0x01, 56, 18, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x00, 156, 65, 48, 156, 12, 12, 3, 3, 12, 12 },
    { 0x00, 168, 65, 48, 155, 12, 12, 3, 3, 12, 12 },
    { 0x00, 84, 72, 48, 154, 12, 12, 3, 3, 12, 12 },
    { 0x00, 96, 72, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 72, 48, 153, 12, 12, 3, 3, 12, 12 },
    { 0x00, 120, 72, 48, 152, 12, 12, 3, 3, 12, 12 },
    { 0x00, 132, 74, 48, 232, 12, 12, 3, 3, 10, 12 },
    { 0x00, 144, 74, 48, 151, 12, 12, 3, 3, 12, 12 },
    { 0x00, 180, 74, 48, 232, 12, 12, 3, 3, 11, 12 },
    { 0x00, 192, 74, 48, 150, 12, 12, 3, 3, 12, 12 },
    { 0x00, 204, 74, 48, 149, 12, 12, 3, 3, 12, 12 },
    { 0x01, 64, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 72, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 80, 18, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 88, 18, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x00, 140, 62, 48, 232, 4, 12, 0, 0, 12, 12 },
    { 0x00, 132, 60, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 108, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 116, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 124, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 132, 170, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 140, 170, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 148, 170, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 180, 170, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 0, 172, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 192, 132, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 212, 133, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 220, 133, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 228, 133, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 172, 135, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 180, 135, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 128, 139, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 136, 139, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 144, 139, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 152, 139, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 160, 139, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 200, 141, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 56, 166, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 64, 172, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 72, 175, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 175, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 187, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 152, 188, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 160, 188, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 136, 191, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 144, 191, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 104, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 204, 195, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 212, 195, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 220, 195, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 228, 195, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 236, 195, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 168, 197, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 176, 197, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 184, 197, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 192, 197, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 244, 197, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 199, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 152, 200, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 160, 200, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 88, 201, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 96, 201, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 136, 203, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 144, 203, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 104, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 200, 207, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 208, 207, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 216, 207, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 224, 207, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 232, 207, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 168, 209, 48, 232, 8, 12, 0, 0, 12, 12 },
};
#elif VERSION_EU
Glyph STPLNMET_nameIcons[114] = {
    { 0x00, 132, 60, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x00, 244, 32, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x00, 244, 44, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 120, 9, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 128, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 136, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x01, 144, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 152, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 160, 9, 48, 232, 8, 12, 4, 3, 7, 12 },
    { 0x01, 200, 156, 48, 232, 4, 12, 5, 3, 4, 12 },
    { 0x01, 60, 84, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 168, 9, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 176, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 184, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 192, 9, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x01, 200, 9, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x00, 96, 60, 48, 232, 12, 12, 4, 3, 9, 12 },
    { 0x00, 108, 60, 48, 232, 12, 12, 3, 3, 12, 12 },
    { 0x01, 164, 205, 48, 232, 8, 12, 3, 3, 12, 12 },
    { 0x01, 208, 9, 48, 232, 8, 12, 3, 3, 11, 12 },
    { 0x01, 120, 83, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 248, 168, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 28, 153, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 28, 141, 48, 232, 4, 12, 3, 3, 4, 12 },
    { 0x01, 216, 9, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 224, 9, 48, 232, 8, 12, 5, 3, 5, 12 },
    { 0x01, 232, 9, 48, 224, 12, 12, 3, 3, 7, 12 },
    { 0x01, 8, 242, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 0, 18, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x01, 8, 18, 48, 232, 8, 12, 3, 3, 6, 12 },
    { 0x01, 16, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 24, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 32, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 40, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x00, 120, 60, 48, 232, 12, 12, 3, 3, 12, 12 },
    { 0x00, 236, 62, 48, 232, 12, 12, 3, 3, 12, 12 },
    { 0x00, 144, 62, 48, 153, 12, 12, 3, 3, 12, 12 },
    { 0x00, 188, 62, 48, 152, 12, 12, 3, 3, 12, 12 },
    { 0x00, 200, 62, 48, 151, 12, 12, 3, 3, 12, 12 },
    { 0x00, 212, 62, 48, 150, 12, 12, 3, 3, 12, 12 },
    { 0x00, 224, 62, 48, 149, 12, 12, 3, 3, 12, 12 },
    { 0x01, 48, 18, 48, 232, 8, 12, 3, 3, 12, 12 },
    { 0x01, 56, 18, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x00, 156, 65, 48, 148, 12, 12, 3, 3, 12, 12 },
    { 0x00, 168, 65, 48, 147, 12, 12, 3, 3, 12, 12 },
    { 0x00, 84, 72, 48, 146, 12, 12, 3, 3, 12, 12 },
    { 0x00, 96, 72, 48, 224, 12, 12, 3, 3, 10, 12 },
    { 0x00, 108, 72, 48, 145, 12, 12, 3, 3, 12, 12 },
    { 0x00, 120, 72, 48, 144, 12, 12, 3, 3, 12, 12 },
    { 0x00, 132, 72, 48, 224, 12, 12, 3, 3, 10, 12 },
    { 0x00, 144, 74, 48, 143, 12, 12, 3, 3, 12, 12 },
    { 0x00, 180, 74, 48, 224, 12, 12, 3, 3, 11, 12 },
    { 0x00, 192, 74, 48, 142, 12, 12, 3, 3, 12, 12 },
    { 0x00, 204, 74, 48, 141, 12, 12, 3, 3, 12, 12 },
    { 0x01, 64, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 72, 18, 48, 232, 8, 12, 3, 3, 7, 12 },
    { 0x01, 80, 18, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 88, 18, 48, 232, 8, 12, 3, 3, 8, 12 },
    { 0x01, 200, 135, 48, 232, 4, 12, 0, 0, 12, 12 },
    { 0x00, 56, 243, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 108, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 116, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 124, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 244, 20, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 40, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 188, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 244, 9, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 0, 172, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 156, 201, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 128, 181, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 172, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 196, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 148, 201, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 196, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 120, 241, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 16, 172, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 120, 217, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 192, 156, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 0, 242, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 64, 243, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 56, 166, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 180, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 64, 175, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 168, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 180, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 56, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 164, 151, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 16, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 8, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 72, 175, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 128, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 164, 163, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 204, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 192, 135, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 164, 139, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 16, 242, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 164, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 180, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 48, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 120, 229, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 192, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 120, 205, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 204, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 234, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 80, 222, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 0, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 8, 172, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 24, 63, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 172, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 188, 193, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 24, 242, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 204, 156, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x01, 204, 135, 48, 232, 8, 12, 0, 0, 12, 12 },
    { 0x00, 48, 243, 48, 232, 8, 12, 0, 0, 12, 12 },
};
#endif
/* The keyboard's pages and characters in Japanese (LANGUAGE 0), which only
 * the European version uses */
KeyTabs STPLNMET_keyPagesJp[] = {
    { { 2, 3, 4 } },
    { { 5, 6, 7 } },
    { { 8, 9, 10 } },
};
KeyPage STPLNMET_keyCharsJp[] = {
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
/* The keyboard's pages and characters */
KeyTabs STPLNMET_keyPages[] = {
    { { 8, 9, 10 } },
};
KeyPage STPLNMET_keyChars[] = {
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
/* The font of the name and the keyboard */
TextStyle STPLNMET_nameStyle = {
    0xFF, 14, { 0, 0 }, (s32)STPLNMET_nameGlyphs, (s32)STPLNMET_nameIcons,
    D_8004D7B8, D_8004DB64, 0xEA, 0x72,
};
/* The partner's animation beside the name: 7 frames per partner, -1 ends one */
s32 STPLNMET_nameAnims[] = {
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
/* The keys bigger than a cell, where the keyboard cursor highlights them */
BigKey STPLNMET_bigKeys[] = {
    { 44, 203, 195 }, { 45, 222, 195 }, { 60, 203, 153 }, { 68, 203, 174 }, { 76, 246, 195 },
};
/* The CLUT rows the page arrows cycle through */
s32 STPLNMET_keyArrowCluts[] = {
    0, 1, 2, 3,
    2, 1,
};
s32 D_80088F30[] = {
    0, 1, 2, 3,
    2, 1,
};
s32 D_80088F48[] = {
    0xE4, 0x100, 0x11C,
};
PartnerAnim STPLNMET_partnerAnims[] = {
    { { 7, 8, 9, 10, 9, 8, -1 } },
    { { 14, 15, 16, 15, -1, -1, -1 } },
    { { 11, 12, 13, 12, -1, -1, -1 } },
    { { 3, 4, 5, 6, 5, 4, -1 } },
    { { 25, 26, 27, 28, 27, 26, -1 } },
    { { 0, 1, 2, 1, -1, -1, -1 } },
    { { 17, 18, 19, 20, 19, 18, -1 } },
    { { 21, 22, 23, 24, 23, 22, -1 } },
};
s32 STPLNMET_partnerChoices[3][3] = {
    { 0, 6, 7 },
    { 2, 3, 6 },
    { 1, 5, 7 },
};
PlayerNameFuncs STPLNMET_funcs = {
    STPLNMET_partnerAnims, STPLNMET_partnerChoices, STPLNMET_loadFiles, STPLNMET_filesLoading,
    STPLNMET_startFade, STPLNMET_updateFade, STPLNMET_startLerp, STPLNMET_updateLerp,
};
NameKeyboard STPLNMET_keyboard = { 0 };
