#include "stcrdabm.h"

extern s32 D_80085168[6];
extern CardAlbumFuncs D_80085180;

void initCardDrawer(CardDrawer *obj);
void func_800825A8(CardAlbumFader *fader);
void func_8008290C(CardAlbumGrid *grid, s32 previous);
s32 func_80082ECC(CardAlbumGrid *grid);
void func_80083820(CardAlbum *album, CardAlbumWindows *win, s32 show);
void func_80083C4C(CardAlbum *album);

void func_80082520(CardAlbumFader *fader, s32 fadeIn, s32 frames) {
    fader->setState(fader, 1);
    fader->substate = 1;
    fader->fadeIn = fadeIn;
    if (fadeIn == 0) {
        fader->level = 0;
        fader->levelStep = 0xFF00 / frames;
    } else {
        fader->level = 0xFF00;
        fader->levelStep = -(0xFF00 / frames);
    }
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800825A8);

void func_800826EC(CardAlbumFader *fader) {
    switch (fader->state) {
    case 0:
    default:
        fader->nextState(fader);
        break;
    case 1:
        if (fader->substate == 0) {
            break;
        }
        fader->level += fader->levelStep;
        if (fader->fadeIn == 0) {
            if (fader->level > 0xFF00) {
                fader->level = 0xFF00;
                fader->state = 2;
            }
        } else if (fader->level < 0) {
            fader->level = 0;
            fader->state = 2;
        }
    case 2:
        func_800825A8(fader);
    case 3:
        break;
    }
}

CardAlbumFader *func_800827A0(void) {
    CardAlbumFader *fader = createTask(func_800826EC, sizeof(CardAlbumFader), 0);

    fader->start = func_80082520;
    fader->layer = 0x1000;
    fader->depth = 0;
    return fader;
}

void func_800827E4(CardAlbumGrid *grid) {
    CardDrawer icon;
    s32 card;
    s32 col;
    s32 row;

    initCardDrawer(&icon);
    icon.setImagePos(0x140, 0x100);
    icon.setClutPos(0x300, 0x100);
    card = grid->first;
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 6 && card < CARD_COUNT; col++) {
            icon.setCard(card++);
            icon.setCell(col, row);
            icon.loadImage();
        }
    }
}

void func_800828AC(CardAlbumGrid *grid, s32 first) {
    grid->prevFirst = grid->first;
    grid->first = first;
    grid->turned = 0;
    grid->frame = 0;
    grid->setState(grid, 2);
}

void func_800828E4(CardAlbumGrid *grid) {
    grid->setSubstate(grid, 1);
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_8008290C);

void func_80082D54(CardAlbumGrid *grid) {
    SpriteDrawer sprite;
    s32 i;
    s32 card;
    s32 col;
    s32 row;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(grid->layer, grid->depth - 1);
    sprite.setTexture(0x280, 0);
    for (i = 0; i < grid->turned; i++) {
        card = grid->first + i;
        col = i % 6;
        row = i / 6;
        if (GAME.cardsSeen[card] != 0 || card >= CARD_COUNT) {
            sprite.setClutRow(grid->frame);
        } else {
            sprite.setClutRow(0);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 6, col * 42 + 0x23, row * 54 + 0x32);
    }
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082ECC);

void func_80082F18(CardAlbumGrid *grid) {
    switch (grid->substate) {
    case 0:
        break;
    case 1:
        if (grid->shown != 0) {
            grid->shown--;
            grid->nextSubstate(grid);
            grid->counter = GFX_FUNCS.getTime();
        } else {
            grid->state = 3;
        }
        break;
    case 2:
        if (GFX_FUNCS.getTime() - grid->counter >= 2) {
            grid->substate = 1;
        }
        break;
    }
}

void func_80082FE0(CardAlbumGrid *grid) {
    switch (grid->state) {
    case 0:
    default:
        grid->nextState(grid);
        grid->first = 1;
        func_800828AC(grid, 1);
        break;
    case 1:
        func_80082F18(grid);
        func_8008290C(grid, 0);
        break;
    case 2:
        switch (grid->substate) {
        case 0:
        default:
            if (++grid->turned < ALBUM_PAGE_CARDS) {
                grid->nextSubstate(grid);
                grid->counter = GFX_FUNCS.getTime();
            } else {
                grid->turned = ALBUM_PAGE_CARDS;
                grid->substate = 2;
            }
            break;
        case 1:
            if (GFX_FUNCS.getTime() - grid->counter >= 2) {
                grid->substate = grid->step;
            }
            break;
        case 2:
            func_800827E4(grid);
            grid->shown = ALBUM_PAGE_CARDS;
            grid->time = GFX_FUNCS.getTime();
            grid->nextSubstate(grid);
            if (func_80082ECC(grid) != 0) {
                SOUND_STATE.playSound(0x4001C);
            }
            break;
        case 3:
            if (GFX.funcs.getTime() - grid->time >= 2) {
                grid->time = GFX.funcs.getTime();
                if (++grid->frame >= 11) {
                    grid->state = 1;
                }
            }
            break;
        }
        func_80082D54(grid);
        if (grid->substate < 3) {
            func_8008290C(grid, 1);
        } else {
            func_8008290C(grid, 0);
        }
        break;
    case 3:
        break;
    }
}

CardAlbumGrid *func_80083210(CardAlbum *album) {
    CardAlbumGrid *grid = createTask(func_80082FE0, sizeof(CardAlbumGrid), 0);

    grid->setPage = func_800828AC;
    grid->hide = func_800828E4;
    grid->layer = 0x1000;
    grid->depth = 6;
    grid->album = album;
    return grid;
}

Task *func_80084DB8(void);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083270);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083368);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083394);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800835AC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083820);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083C4C);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084314);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084384);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084C8C);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084DB8);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084DF4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084ED4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084FBC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80085050);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800850BC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800850FC);
