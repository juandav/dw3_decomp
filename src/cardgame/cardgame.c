#include "cardgame.h"

extern RECT CARDGAME_screenRect;
extern RECT CARDGAME_fadeRect;
extern CardFileEntry CARDGAME_preloadFiles[];

CardBattle *CARDGAME_createBattle(s32 arg);
void initCardDrawer(CardDrawer *obj);
extern s16 D_800A49D8[];
extern CardOffset CARDGAME_deckCountOffsets[];
extern s16 D_800A4AA0[];
extern CardOffset D_800A485C[];
extern u16 D_800A488C[];
extern CardWindowLayout CARDGAME_windowLayouts[];
Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
void func_80095B44(CardScreen *screen);
void func_80096C78(CardScreen *screen, CardScreenItems *items);
void func_800966FC(CardScreen *screen, CardScreenItems *items, CardScreenE0C *window, s32 index);
void func_80097548(CardScreen *screen, CardScreenItems *items);
void func_80098E28(CardScreen *screen, CardScreenItems *items);
void func_80098EB4(CardScreen *screen, CardScreenItems *items);
void func_8009AA1C(CardScreen *screen, CardScreenItems *items);
void func_8009DCDC();
extern CardBattleMessage D_800A4C20[];
extern s16 D_800A4748[2][3][4][2];
s32 func_80089504(CardBattle *battle);
s32 func_80089548(CardBattle *battle);
void func_8008B0D4(CardBattle *battle, s32 arg1, s32 arg2, s32 arg3);
void func_8008E8B0(CardBattle *battle, s32 arg1, s32 arg2, s32 arg3);
void func_8009DE0C(CardBattle *battle, void *arg1, s32 arg2, s32 arg3);
void func_8009DF5C();
void CARDGAME_setSlot(CardBattle *battle, s32 side, s32 card, s32 index);
void CARDGAME_addCard(CardBattle *battle, s32 side, s32 card);
void func_8009F664();
void func_800A1E04();
void func_800A2838();

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800835C4);

void func_800836D8(CardBattle *battle, s32 side, s32 value, s32 score) {
    if (battle->sides[0].unk20[battle->sides[0].unk15 - 1].unk4 == value) {
        battle->unk4E0 += score;
    }
}

void func_80083714(CardBattle *battle, s32 side, s32 value, s32 score) {
    if (value >= battle->sides[side].unk46) {
        battle->unk4E0 += score;
    }
}

void func_80083758(CardBattle *battle, s32 side, s32 value, s32 score) {
    if (value < battle->sides[side].unk46) {
        battle->unk4E0 += score;
    }
}

void func_8008379C(CardBattle *battle, s32 side, s32 score) {
    if (battle->sides[side].unk44 > 0) {
        battle->unk4E0 += score;
    }
}

void func_800837DC(CardBattle *battle, s32 side, s32 score) {
    if (battle->players[side].slotCount < 6) {
        battle->unk4E0 += score;
    }
}

s32 func_80083820(CardBattle *battle) {
    battle->unk424 -= GFX.funcs.getFrameTime();
    return battle->unk424 <= 0;
}

void func_80083860(CardBattle *battle, s32 arg1, s32 which) {
    if (which == 0) {
        battle->unk440 = battle->sides[0].unk40;
    } else {
        battle->unk440 = battle->unk41C;
    }
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80083880);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80083918);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800839CC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80083AB0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80085578);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800856C8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80085760);

s16 func_80085820(s32 a, s32 b, s32 c) {
#if VERSION_US
    return D_800A4748[0][a][b][c];
#elif VERSION_EU
    return D_800A4748[SHIFT_PAL_SCREEN][a][b][c];
#endif
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008584C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80085AA8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80085B20);

void func_800860CC(CardBattle *battle, CardScreen *screen) {
    screen->unkE0C[1].unkE = 0;
    screen->unkE0C[1].unk10 = 0;
    screen->unkE0C[2].unk10 = 0;
    screen->unkE0C[3].unk10 = 0;
    screen->unkE0C[4].unk10 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800860E4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800863DC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008642C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80086564);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800865D8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80086758);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800868E0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800869BC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80086A10);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80086B0C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80086C60);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80086F68);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80087234);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008747C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80087590);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800885C0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008862C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80088B98);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80088C34);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80088DA4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80088F10);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80089028);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80089548);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80089698);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008A3C8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008B0D4);

void func_8008B29C(CardBattle *battle, s32 arg1, s32 arg2) {
    func_8008B0D4(battle, arg1, arg2, 0);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008B2BC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008B434);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008B674);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008BC08);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008BCF8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008BEF0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008BFA0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008C064);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008C174);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008C424);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008C5F4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008C88C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008CBAC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008CE6C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008CF50);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D044);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D10C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D194);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D288);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D350);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D3D8);

s32 func_8008D4C4(CardBattle *battle, s32 arg1, s32 duration) {
    battle->unk424 += GFX.funcs.getFrameTime();
    return duration < battle->unk424;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D510);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D6A4);

INCLUDE_RODATA("cardgame/nonmatchings/cardgame", D_80082C94);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008D9B0);

void func_8008DBC8(CardBattle *battle) {
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008DBD4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008E21C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008E4A0);

void func_8008E68C(CardBattle *battle, s32 arg1, s32 side) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = battle->sides[side].unk46;
    battle->unk42C = battle->sides[side].unk42;
    battle->unk430 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008E6CC);

void func_8008E8B0(CardBattle *battle, s32 arg1, s32 arg2, s32 arg3) {
    battle->unk430 = arg3;
    battle->unk434 = arg2;
    battle->unk423 = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008E8C4);

void func_8008EB08(CardBattle *battle, s32 arg1) {
    func_8008E8B0(battle, arg1, -0x80, 0x10);
    battle->unk438 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008EB38);

void func_8008ED28(CardBattle *battle, CardScreen *screen) {
    battle->unk424 = 0;
    battle->stepState = 1;
    screen->unkEA8(screen, battle->sides[0].unk15 - 2);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008ED68);

s32 func_8008EF20(CardBattle *battle) {
    s32 card = battle->sides[0].unk20[battle->sides[0].unk15 - 1].unk0;

    battle->unk305++;
    battle->unk304 = card + 1;
    return 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008EF50);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008F074);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008F4E0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008F630);

void func_8008FD44(CardBattle *battle, s32 arg1, s32 side) {
    battle->unk424 = 0;
    battle->unk434 = 0;
    battle->unk428 = battle->sides[side].unk42;
    battle->unk42C = battle->sides[side].unk44;
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8008FD84);

void func_80090044(CardBattle *battle, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 40; i++) {
        battle->unk46F[i] = 0;
    }
    battle->unk444 = arg2;
    battle->unk445 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80090068);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80090178);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800902A8);

void func_80090B48(CardBattle *battle) {
    battle->unk428 = 0;
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80090B58);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80090C90);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80090DDC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80090F80);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800911F0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800913A0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80091688);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800918A0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80091A94);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80091E60);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80091F10);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800920D4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80092860);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009294C);

void func_80092CE0(CardBattle *battle, s32 arg1, s32 side) {
    battle->unk424 = 0;
    battle->unk428 = battle->players[side].slotCount - 1;
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80092D14);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80092E1C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80092EB0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80093240);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800934E0);

void func_80093A1C(CardBattle *battle) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = 0;
    battle->unk430 = 0;
    battle->unk434 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80093A3C);

void func_80093D6C(CardBattle *battle) {
    battle->stepState = 1;
    battle->unk424 = 0;
    battle->unk428 = 0;
    battle->unk42C = 0;
    battle->unk430 = 0;
    battle->unk434 = 0;
    battle->unk438 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80093D90);

void func_800941D0(CardBattle *battle, CardScreen *screen, s32 arg2) {
    battle->unk424 = 0;
    screen->unkEE4(screen, arg2, 0, 0, 1);
    battle->stepState = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80094224);

void func_80094380(CardBattle *battle, CardScreen *screen, s32 force) {
    if (battle->sides[0].unk20[battle->sides[0].unk15 - 1].unk4 == 0 || force) {
        battle->sides[0].unk15--;
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
            battle->sides[0].unk15++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

void func_80094468(CardBattle *battle, CardScreen *screen, s32 force) {
    if (battle->sides[0].unk20[battle->sides[0].unk15 - 1].unk4 == 0 || force) {
        screen->unkEC8(screen);
        battle->unk498.unk5 = 1;
        battle->unk498.unk1 = 1;
        battle->stepState = 1;
        battle->sides[0].unk15--;
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
            battle->sides[0].unk15++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    return done;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80094550);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800946EC);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80096C78);

void func_8009747C(CardScreen *screen, CardScreenItems *items, s16 scale, s32 x, s32 y) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x100, 1);
    drawer.setTexture(0x340, 0);
    drawer.setPivot(0, 0x86);
    drawer.setScale(scale, 0x1000, 0x1000);
    drawer.draw(FILE_CACHE.getEntry(FILE_CARDGAME_TIMS << 16 | 3), 1, x, y);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80097548);

s32 CARDGAME_getHandOffset(s32 count, s32 index) {
    s32 step;

    if (count < 7) {
        step = 0x2900;
    } else {
        step = 0xF600 / count;
    }
    return step * index;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80097880);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800983D0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098930);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098B38);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098C6C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098D3C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098E28);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098EB4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80098F50);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800990F4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800993A8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099494);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099504);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099580);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800996B0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099780);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800998EC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099C00);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099E7C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_80099F7C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009A0BC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009A5CC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009A6C0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009A7E4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009A990);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009AA1C);

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
    screen->panels[side].scaleState = 1;
    screen->panels[side].scaleDuration = 12;
    screen->panels[side].scaleTime = 12;
    screen->panels[side].scale = 0;
}

void func_8009B42C(CardScreen *screen, s32 side) {
    screen->panels[side].scaleState = 3;
    screen->panels[side].scaleDuration = 6;
    screen->panels[side].scaleTime = 6;
    screen->panels[side].scale = 0x1000;
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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009C628);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009C844);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009C92C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009C9B0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009CB30);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009CE0C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009CEB0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009CF6C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009D470);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009D578);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009DCDC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009DE0C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009DF5C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009E020);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009E820);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009E8A8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009EA28);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009ECE8);

void func_8009F458(CardBattle *battle) {
    battle->sides[0].unk14 = 0;
    func_8009DCDC();
    battle->unk814(battle, battle->sides[0].unkA0, battle->sides[0].unk46 << 16, 0);
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009F4A0);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009F664);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009F754);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009F90C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009F9DC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009FA90);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009FBE4);

void func_8009FE5C(CardBattle *battle, CardBattleItems *items) {
    items->screen->unkEC8(items->screen);
    battle->unk498.unk5 = 1;
    battle->unk498.unk1 = 1;
    battle->unk2F9 = 0;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_8009FEA4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A0908);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A096C);

void func_800A0A0C(CardBattle *battle) {
    s32 i = battle->unk2F6;

    battle->unk2F4 = 1;
    battle->unk421 = D_800A4C20[i].text;
    battle->unk2F7 = D_800A4C20[i].unk2;
}

void func_800A0A40(CardBattle *battle) {
    battle->sides[0].unk4D = 0;
    battle->sides[1].unk4D = 1;
    battle->result = 0;
    battle->unk302 = 1;
    battle->unk2F8 = 1;
}

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A0A5C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A0CCC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A0D74);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A1084);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A150C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A1CFC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A1E04);

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

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A25E8);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A2838);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A2C94);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A2DA0);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A2E4C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A2F7C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A30AC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A30FC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A322C);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A3344);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A3398);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A33F4);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A34FC);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A3828);

INCLUDE_ASM("cardgame/nonmatchings/cardgame", func_800A387C);


u8 D_800A3CF8[] = {
    0x91, 0x0A, 0x2F, 0x04, 0x6A, 0x5C, 0x59, 0x4D,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x03, 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x4F,
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x8E, 0x0A, 0x2F, 0x01, 0x5C, 0x5E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x85, 0x09, 0x2F, 0x00,
    0x5B, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x73, 0x00, 0x00, 0x09, 0x1E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x92, 0x0A, 0x2F, 0x05, 0x6B, 0x5C, 0x4E, 0x4C,
    0x03, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07,
    0x2C, 0x3F, 0x0A, 0x11, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x09, 0x2F, 0x00,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x5B, 0x57,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x83, 0x00, 0x00, 0x09, 0x41, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x8B, 0x09, 0x2F, 0x00,
    0x5B, 0x4E, 0x4C, 0x03, 0x09, 0x08, 0x2F, 0x2B,
    0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x11, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x74, 0x00, 0x00, 0x09, 0x1F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x51, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x93, 0x0A, 0x2F, 0x06, 0x6C, 0x5C, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x81, 0x04, 0x00, 0x09,
    0x2D, 0x3A, 0xAB, 0x43, 0x2E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x75, 0x00, 0x00, 0x09, 0x21, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x85, 0x09, 0x2F, 0x00,
    0x5B, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x75, 0x00, 0x00, 0x09, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x52, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x94, 0x0A, 0x2F, 0x07, 0x6D, 0x5C, 0x58, 0x65,
    0x4D, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x95, 0x0A, 0x2F, 0x08,
    0x5C, 0x59, 0x4D, 0x4C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x0A, 0x2F, 0x03, 0x5C, 0x58, 0x66, 0x4D,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x09, 0x2F, 0x00,
    0x5B, 0x58, 0x67, 0x4D, 0x4C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x76, 0x00, 0x00, 0x09, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x53, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0x03, 0x3A, 0x09, 0x6E, 0x39, 0x4A, 0x3E,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x82, 0x05, 0x35, 0x09,
    0x2D, 0x32, 0xAC, 0x42, 0x2E, 0x09, 0x08, 0x2F,
    0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x89, 0x09, 0x2F, 0x00, 0x5B, 0x59, 0x4D, 0x4C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x01, 0x33, 0x09,
    0x07, 0x2F, 0x07, 0x2B, 0x36, 0xA9, 0x07, 0x2C,
    0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x77, 0x00, 0x00, 0x09, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x54, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x0A, 0x2F, 0x03, 0x6F, 0x5C, 0x59, 0x4D,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x09,
    0x6F, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x72, 0x06, 0x35, 0x09, 0x6F, 0x04, 0x08, 0x2F,
    0x2B, 0x33, 0xAD, 0x07, 0x2C, 0x40, 0x0E, 0x30,
    0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x82, 0x05, 0x35, 0x09,
    0x6F, 0x49, 0x2D, 0x47, 0x48, 0x2E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7D, 0x00, 0x00, 0x09, 0x6F, 0x29, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x09,
    0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x70, 0x00, 0x00, 0x09, 0x0D, 0x2D, 0x46, 0x48,
    0x2E, 0x0B, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07,
    0x2C, 0x3F, 0x0C, 0x11, 0x0D, 0x2D, 0x46, 0x48,
    0x2E, 0x0B, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07,
    0x2C, 0x3F, 0x0C, 0x11, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x72, 0x06, 0x35, 0x09,
    0x05, 0x33, 0x4B, 0x40, 0x0E, 0x30, 0x02, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x0A, 0x2F, 0x02, 0x5C, 0x69, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x96, 0x0B, 0x2F, 0x09,
    0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x56, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x87, 0x09, 0x2F, 0x00, 0x5B, 0x62, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x82, 0x05, 0x35, 0x09,
    0x2D, 0x45, 0x48, 0x2E, 0x09, 0x08, 0x2F, 0x2B,
    0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x82, 0x07, 0x36, 0x09, 0x2D, 0x34, 0xAC, 0x42,
    0x2E, 0x09, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07,
    0x2C, 0x3F, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x82, 0x08, 0x37, 0x09,
    0x2D, 0x35, 0xAC, 0x42, 0x2E, 0x09, 0x08, 0x2F,
    0x2B, 0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x82, 0x05, 0x35, 0x09, 0x2D, 0x32, 0xAC, 0x42,
    0x2E, 0x08, 0x2F, 0x2B, 0x37, 0xAA, 0x07, 0x2C,
    0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x72, 0x06, 0x35, 0x09,
    0x03, 0x33, 0x4B, 0x40, 0x0E, 0x30, 0x02, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x8A, 0x09, 0x2F, 0x00, 0x5B, 0x58, 0x67, 0x4D,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x09,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0x02, 0x38, 0x09, 0x07, 0x2F, 0x07, 0x2B,
    0x38, 0xA9, 0x07, 0x2C, 0x3E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x09,
    0x03, 0x10, 0x31, 0x3D, 0xAE, 0x4D, 0x4C, 0x55,
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x78, 0x00, 0x00, 0x09, 0x24, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x09,
    0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7A, 0x00, 0x00, 0x09, 0x26, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x09,
    0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7C, 0x00, 0x00, 0x09, 0x28, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x8C, 0x09, 0x2F, 0x00,
    0x5B, 0x4E, 0x4C, 0x03, 0x09, 0x08, 0x2F, 0x2B,
    0x37, 0xAA, 0x07, 0x2C, 0x3F, 0x0A, 0x11, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x8B, 0x09, 0x2F, 0x00, 0x5B, 0x58, 0x68, 0x4D,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x8A, 0x09, 0x2F, 0x00,
    0x5B, 0x4D, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x85, 0x09, 0x2F, 0x00, 0x5B, 0x63, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x85, 0x09, 0x2F, 0x00,
    0x5B, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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
s32 D_800A47A8[] = {
    0, 6, 12, 0,
};
u16 D_800A47B8[] = {
    0x0000, 0x0000, 0x0004, 0x0001, 0x0008, 0x0002, 0xFFFF, 0x0003,
};
u8 D_800A47C8[] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x1F, 0x3E, 0x0B, 0x0C,
};
s32 D_800A47D8[] = {
    29696, 24832, 41984, 24832,
};
u8 D_800A47E8[] = {
    0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u16 D_800A47F8[] = {
    0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
};
s32 D_800A4804[] = {
    0x11400, 28416, 0x11400, 22016,
};
s32 D_800A4814[] = {
    20736, 24832, 33536, 24832,
    46336, 24832,
};
u16 D_800A482C[] = {
    0x0082, 0x00BF, 0x0082, 0x001D, 0x0082, 0x00CB, 0x0082, 0x0011,
};
RECT CARDGAME_screenRect = {0, 0, 320, 240};
/* where the deck window's six counts are */
CardOffset CARDGAME_deckCountOffsets[] = {
    {0x24, 0x14}, {0x47, 0x14}, {0x6A, 0x14}, {0x8D, 0x14}, {0xB0, 0x14}, {0xD3, 0x14},
};
#if VERSION_EU
s32 D_800A5958[] = {
    0x1800, 0x9000, 0x1800, 0x3200,
    0x1800, 0x9C00, 0x1800, 0x2600,
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
s32 D_800A4894[] = {
    0, 138, 0, 96,
    0, 50, 0, 96,
};
s32 D_800A48B4[] = {
    0x2F110E01, 0x450011, 0x470026, 0x4700F9,
    0x470123, 0xFFF10001, 0x34001E, 0x34002E,
    0x34004E, 0x34005E, 0x4500E4, 0x45010E,
    0xFFEAFFF9, 0x43000B, 0x4000DE, 0x400108,
    0xFFECFFFA, 0x300017, 0x300047, 0x30140F01,
    0xE0011, 0x100026, 0x1000F9, 0x100123,
    0x150001, 0x23001E, 0x23002E, 0x23004E,
    0x23005E, 0xE00E4, 0xE010E, 0xFFFAFFF9,
    0xC000B, 0x900DE, 0x90108, 0xFFFBFFFA,
    0x1F0017, 0x1F0047,
};
u8 D_800A494C[] = {
    0x00, 0x01, 0x02, 0x03, 0x02, 0x01, 0x00, 0x00,
    0x4D, 0x56, 0x4E, 0x57, 0x4F, 0x58, 0x50, 0x59,
    0x52, 0x5B, 0x51, 0x5A, 0x53, 0x5C, 0x00, 0x00,
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
u16 D_800A498C[] = {
    0xFF00, 0x0300, 0xFD00, 0x0100,
};
u16 D_800A4994[] = {
    0xFC00, 0x0200, 0xFE00, 0x0400,
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
u16 D_800A4AE4[] = {
    0x0044, 0x006F, 0x009A, 0x00C5, 0x00F0, 0x0000,
};
u16 D_800A4AF0[] = {
    0x005B, 0x005B, 0x0169, 0x016A, 0x016B, 0x016C, 0x016D, 0x016E,
    0x016F, 0x0170, 0x0171, 0x0172, 0x0173, 0x0174, 0x0175, 0x0176,
    0x0177, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E,
    0x017F, 0x0180, 0x0181, 0x0182, 0x0183, 0x0184, 0x0185, 0x0186,
    0x0187, 0x0188, 0x0189, 0x018A,
};
u16 D_800A4B38[] = {
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
u8 D_800A4BD8[] = {
    0x80, 0x80, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01,
    0x00, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01,
    0x80, 0x80, 0x80, 0x02, 0x80, 0x80, 0x00, 0x01,
};
u16 D_800A4BF0[] = {
    0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000,
    0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0000,
};
u16 D_800A4C0C[] = {
    0x0017, 0x0050, 0x0017, 0x007D, 0x0017, 0x00AA,
};
u8 D_800A4C18[] = {
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};
CardBattleMessage D_800A4C20[] = {
    {0x00, 0}, {0xA6, 2}, {0xA0, 3}, {0xA1, 4}, {0xA2, 5},
    {0xA3, 6}, {0xA4, 7}, {0xA5, 8}, {0xA0, 3}, {0xA0, 3},
};
u16 D_800A4C48[] = {
    0x0082, 0x00BF, 0x0082, 0x001D, 0x0082, 0x00CB, 0x0082, 0x0011,
};
RECT CARDGAME_fadeRect = {0, -15, 320, 260};
s32 D_800A4C60 = 0;
s32 D_800A4C64 = 0;
s32 D_800A4C68 = 0;
s32 D_800A4C6C[] = {
    0, 0, 0, 0,
    0, 0,
};
s32 D_800A4C84[] = {
    0, 0,
};
s32 D_800A4C8C[] = {
    0, 0, 0, 0,
    0, 0,
};
