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

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082D54);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082ECC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082F18);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082FE0);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083210);

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
