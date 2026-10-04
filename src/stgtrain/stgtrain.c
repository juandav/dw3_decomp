/* The first object of STGTRAIN.PRO, and the overlay's data. STGTRAIN.PRO
   was at least three objects: each one's jump tables are aligned to 8 from
   the start of its own rodata, and the tables at 0x8008251C and 0x800825E8
   (USA) each start right where the one before ends, 4 bytes past a multiple
   of 8, so each one starts a new object. Where each object's code starts is
   only known to be between the function with the last jump table of the
   object before and the one with its first: here at the training result's
   functions (stgtrain_2.c) and the session's (stgtrain_3.c). */

#include "stgtrain.h"

/* Sets the sprite bank and where the sprites start in it */
void func_800827F0(TrainSprite *sprite, TrainSpriteBank *bank, s32 offset) {
    sprite->bank = bank;
    sprite->bankOffset = offset;
    sprite->unk84 = bank->unk2;
    sprite->unk86 = bank->unk4;
}

/* Starts an animation from its first frame */
void func_80082810(TrainSprite *sprite, TrainAnim *anim) {
    if (anim != NULL) {
        sprite->anim = anim;
        sprite->frame = 0;
        sprite->frameTime = 0;
        sprite->frameCount = anim->frameCount;
        sprite->flags = 0;
    }
}

void func_80082838(TrainSprite *sprite, s32 layerId, s32 depth) {
    sprite->layerId = layerId;
    sprite->depth = depth;
}

void func_80082844(TrainSprite *sprite, s32 x, s32 y) {
    sprite->x = x;
    sprite->y = y;
}

void func_80082850(TrainSprite *sprite, s32 x, s32 y) {
    sprite->imageX = x;
    sprite->imageY = y;
}

void func_8008285C(TrainSprite *sprite, s32 x, s32 y) {
    sprite->clutX = x;
    sprite->clutY = y;
}

void func_80082868(TrainSprite *sprite, s32 x, s32 y, s32 z) {
    sprite->scale.vx = x;
    sprite->scale.vy = y;
    sprite->scale.vz = z;
    sprite->transformed = 1;
}

void func_80082880(TrainSprite *sprite, s32 x, s32 y) {
    sprite->pivotX = x;
    sprite->pivotY = y;
}

void func_8008288C(TrainSprite *sprite, s16 x, s16 y, s16 z) {
    sprite->rotation.vx = x;
    sprite->rotation.vy = y;
    sprite->rotation.vz = z;
    sprite->transformed = 1;
}

s32 func_800828A4(TrainSprite *sprite) {
    return sprite->flags & 0x7FFFFFFF;
}

void func_800828B8(TrainSprite *sprite, s32 paused) {
    if (paused) {
        sprite->flags |= 0x80000000;
    } else {
        sprite->flags &= 0x7FFFFFFF;
    }
}

/*
 * The animated sprite's update: state 1 advances the animation, unless it
 * is paused, and draws the frame's sprite, its parts from the last to the
 * first, as sprites or, scaled and rotated about the pivot, as quads.
 * The match depends on frame holding the animation before its frames.
 */
void func_800828E8(TrainSprite *sprite) {
    SVECTOR out;
    SVECTOR in[4];
    TrainAnimFrame *frame;
    u8 *p;
    TrainSpritePart *part;
    s32 n;
    s32 count;
    s32 i;
    s32 j;
    s32 k;
    s32 state;
    u16 info;
    u16 w;
    u16 h;
    u16 tpage;
    u16 prevTpage;
    u16 clut;
    s32 transform;
    u8 u;
    u8 v;
    s32 x;
    s32 y;
    void *prim;

    state = sprite->state;
    switch (state) {
    case 0:
    default:
        sprite->nextState(sprite);
        sprite->frameTime = GFX.funcs.getTime();
        break;
    case 1:
        if (sprite->bank == NULL) {
            break;
        }
        if (sprite->anim == NULL) {
            break;
        }
        frame = (TrainAnimFrame *)sprite->anim;
        frame = ((TrainAnim *)frame)->frames;
        frame += sprite->frame;
        if (sprite->flags >= 0 && GFX.funcs.getTime() - sprite->frameTime > frame->duration) {
            sprite->frameTime = GFX.funcs.getTime();
            if (++sprite->frame >= sprite->frameCount - 1) {
                sprite->frame = sprite->frameCount - 1;
                sprite->flags = 1;
            }
            frame = (TrainAnimFrame *)sprite->anim;
            frame = ((TrainAnim *)frame)->frames;
            frame += sprite->frame;
        }
        p = (u8 *)sprite->bank;
        p += sprite->bankOffset;
        count = frame->sprite;
        for (i = 0; i < count; i++) {
            n = *(s32 *)p;
            p += sizeof(s32);
            for (j = 0; j < n; j++) {
                p += sizeof(TrainSpritePart);
            }
        }
        tpage = 0;
        prevTpage = 0;
        transform = 0;
        if (sprite->transformed) {
            if (sprite->scale.vx == 0 && sprite->scale.vy == 0) {
                break;
            }
            if (sprite->scale.vx == 0x1000 && sprite->scale.vy == 0x1000) {
                sprite->transformed = 0;
            } else {
                transform = 1;
                RotMatrixYXZ_gte(&sprite->rotation, &sprite->matrix);
                ScaleMatrix(&sprite->matrix, &sprite->scale);
            }
        }
        sprite->layer = GFX.funcs.getLayer(sprite->layerId);
        sprite->ot = (u_long *)sprite->layer->getOtEntry(sprite->layer, sprite->depth);
        prim = GFX.funcs.getPrim();
        n = *(s32 *)p;
        p += sizeof(s32);
        for (i = 0; i < n; i++) {
            p += sizeof(TrainSpritePart);
        }
        part = (TrainSpritePart *)p;
        for (i = 0; i < n; i++) {
            part--;
            info = part->tpage;
            clut = getClut(sprite->clutX + (info & 0x1F) * 16, sprite->clutY + ((part->clut & 0x7FC0) >> 6));
            tpage = getTPage(info >> 7, info >> 5, sprite->imageX + (info & 0x1F) * 64, sprite->imageY);
            u = part->u;
            x = part->x;
            y = part->y;
            v = part->v;
            w = part->w;
            h = part->h;
            if (!transform) {
                if (i == 0) {
                    prevTpage = tpage;
                }
                if (prevTpage != tpage) {
                    SetDrawTPage(prim, 0, 1, prevTpage);
                    addPrim(sprite->ot, prim);
                    prim = (DR_TPAGE *)prim + 1;
                    prevTpage = tpage;
                }
                setSprt((SPRT *)prim);
                if ((s16)part->clut & 0x8000) {
                    setSemiTrans((SPRT *)prim, 1);
                }
                setRGB0((SPRT *)prim, 0x80, 0x80, 0x80);
                ((SPRT *)prim)->x0 = x + (frame->x + sprite->x);
                ((SPRT *)prim)->y0 = y + (frame->y + sprite->y);
                ((SPRT *)prim)->u0 = u;
                ((SPRT *)prim)->v0 = v;
                ((SPRT *)prim)->w = w;
                ((SPRT *)prim)->h = h;
                ((SPRT *)prim)->clut = clut;
                addPrim(sprite->ot, prim);
                prim = (SPRT *)prim + 1;
            } else {
                setPolyFT4((POLY_FT4 *)prim);
                if ((s16)part->clut & 0x8000) {
                    setSemiTrans((POLY_FT4 *)prim, 1);
                }
                setRGB0((POLY_FT4 *)prim, 0x80, 0x80, 0x80);
                in[0].vx = in[2].vx = x + (frame->x + sprite->x) - sprite->pivotX;
                in[1].vx = in[3].vx = in[0].vx + w;
                in[0].vy = in[1].vy = y + (frame->y + sprite->y) - sprite->pivotY;
                in[2].vy = in[3].vy = in[0].vy + h;
                in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
                for (k = 0; k < 4; k++) {
                    ApplyMatrixSV(&sprite->matrix, &in[k], &out);
                    (&((POLY_FT4 *)prim)->x0)[k * 4] = out.vx + sprite->pivotX;
                    (&((POLY_FT4 *)prim)->y0)[k * 4] = out.vy + sprite->pivotY;
                }
                ((POLY_FT4 *)prim)->u0 = ((POLY_FT4 *)prim)->u2 = u;
                ((POLY_FT4 *)prim)->u1 = ((POLY_FT4 *)prim)->u3 = w + u - 1;
                ((POLY_FT4 *)prim)->v0 = ((POLY_FT4 *)prim)->v1 = v;
                ((POLY_FT4 *)prim)->v2 = ((POLY_FT4 *)prim)->v3 = h + v - 1;
                ((POLY_FT4 *)prim)->tpage = tpage;
                ((POLY_FT4 *)prim)->clut = clut;
                addPrim(sprite->ot, prim);
                prim = (POLY_FT4 *)prim + 1;
            }
        }
        if (!transform) {
            SetDrawTPage(prim, 0, 1, tpage);
            addPrim(sprite->ot, prim);
            prim = (DR_TPAGE *)prim + 1;
        }
        GFX.funcs.setPrim(prim);
        break;
    case 2:
    case 3:
        break;
    }
}

/* Creates an animated sprite */
TrainSprite *func_80083018(void) {
    TrainSprite *sprite = createTask(func_800828E8, sizeof(TrainSprite), 0);
    sprite->setBank = func_800827F0;
    sprite->setAnim = func_80082810;
    sprite->setPos = func_80082844;
    sprite->setImagePos = func_80082850;
    sprite->setLayer = func_80082838;
    sprite->setClutPos = func_8008285C;
    sprite->setScale = func_80082868;
    sprite->setPivot = func_80082880;
    sprite->setRotation = func_8008288C;
    sprite->getFlags = func_800828A4;
    sprite->setPaused = func_800828B8;
    return sprite;
}

/* The mode's root task: sets up the display and starts the screen */
void func_800830C8(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x14000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        rect.x = 0x7B;
        rect.y = 0x53;
        rect.w = 0xA8;
        rect.h = 0x58;
        GFX.funcs.createLayer(&rect, 3, 0x1001);
        GFX.funcs.moveLayer(0x1001, 0x1000, 1);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        GFX.funcs.createLayer(&rect, 3, 0x1002);
        GFX.funcs.moveLayer(0x1002, 0x1001, 1);
        children[0] = (Task *)func_800854FC();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_80083258(void) {
    return createTask(func_800830C8, sizeof(Task), 4);
}

/* Creates the screen's text windows */
void func_80083284(TrainScreen *screen, TrainScreenWindows *win) {
    s32 i;

    win->name = createTextWindow(screen->layerId, 1, 0x33, 0x13);
    win->level[0] = createTextWindow(screen->layerId, 3, 0x33, 0x22);
    win->level[1] = createTextWindow(screen->layerId, 3, 0x50, 0x22);
    win->hp[0] = createTextWindow(screen->layerId, 3, 0x33, 0x2C);
    win->hp[1] = createTextWindow(screen->layerId, 3, 0x5D, 0x2C);
    win->hp[2] = createTextWindow(screen->layerId, 3, 0x80, 0x2C);
    win->mp[0] = createTextWindow(screen->layerId, 3, 0x33, 0x35);
    win->mp[1] = createTextWindow(screen->layerId, 3, 0x5D, 0x35);
    win->mp[2] = createTextWindow(screen->layerId, 3, 0x80, 0x35);
    win->slashes[0] = createTextWindow(screen->layerId, 3, 0x5F, 0x2C);
    win->slashes[1] = createTextWindow(screen->layerId, 3, 0x5F, 0x35);
    for (i = 0; i < 6; i++) {
        win->stats[i] = createTextWindow(screen->layerId, 1, 0x33, i * 0xE + 0x4F);
    }
    for (i = 0; i < 7; i++) {
        win->resistances[i] = createTextWindow(screen->layerId, 1, 0x5D, i * 0xE + 0x4F);
    }
    win->unk60[0] = createTextWindow(screen->layerId, 1, 0x10, 0xBB);
    win->unk60[1] = createTextWindow(screen->layerId, 1, 0x2C, 0xBB);
    win->unk68 = createTextWindow(screen->layerId, 1, 0xA1, 0x17);
    win->unk6C = createTextWindow(screen->layerId, 1, 0xAE, 0x49);
}

/* Shows or hides the selected partner's name, level, HP and MP */
void func_800834A8(TrainScreen *screen, TrainScreenWindows *win, s32 show) {
    TrainTotals totals;
    PartnerVitals *vitals;
    s32 partner;
    s32 i;

    if (show) {
        partner = GAME.funcs.getPartyMember(screen->partner);
        vitals = GAME.funcs.getPartnerStats(partner);
        GAME.funcs.computeStats(partner, (PartnerTotals *)&totals);
        win->name->setString(win->name, vitals, -1);
        win->level[0]->setString(win->level[0], FILE_CACHE.load(STGTRAIN_TEXT), 1);
        win->level[1]->setNumber(win->level[1], 0, totals.level);
        win->level[1]->setRightAlign(win->level[1], 1);
        win->hp[0]->setString(win->hp[0], FILE_CACHE.load(STGTRAIN_TEXT), 2);
        win->hp[1]->setNumber(win->hp[1], 0, totals.hp);
        win->hp[2]->setNumber(win->hp[2], 0, totals.maxHp);
        for (i = 1; i < 3; i++) {
            win->hp[i]->setPalette(win->hp[i], 0);
            win->hp[i]->setRightAlign(win->hp[i], 1);
        }
        win->mp[0]->setString(win->mp[0], FILE_CACHE.load(STGTRAIN_TEXT), 3);
        win->mp[1]->setNumber(win->mp[1], 0, totals.mp);
        win->mp[2]->setNumber(win->mp[2], 0, totals.maxMp);
        for (i = 1; i < 3; i++) {
            win->mp[i]->setPalette(win->mp[i], 0);
            win->mp[i]->setRightAlign(win->mp[i], 1);
        }
        for (i = 0; i < 2; i++) {
            win->slashes[i]->setString(win->slashes[i], FILE_CACHE.load(STGTRAIN_TEXT), 0x43);
        }
    } else {
        win->name->setVisible(win->name, 0);
        for (i = 0; i < 2; i++) {
            win->level[i]->setVisible(win->level[i], 0);
            win->slashes[i]->setVisible(win->slashes[i], 0);
        }
        for (i = 0; i < 3; i++) {
            win->hp[i]->setVisible(win->hp[i], 0);
        }
        for (i = 0; i < 3; i++) {
            win->mp[i]->setVisible(win->mp[i], 0);
        }
    }
}

/* Shows or hides the selected partner's stats and resistances */
void func_800837D8(TrainScreen *screen, TrainScreenWindows *win, s32 show) {
    TrainTotals totals;
    s32 i;

    if (show) {
        GAME.funcs.computeStats(GAME.funcs.getPartyMember(screen->partner), (PartnerTotals *)&totals);
        for (i = 0; i < 6; i++) {
            win->stats[i]->setNumber(win->stats[i], 0, totals.stats[i]);
            win->stats[i]->setRightAlign(win->stats[i], 1);
            win->stats[i]->setPalette(win->stats[i], 0);
        }
        if (totals.boosted[0] != 0) {
            win->stats[0]->setPalette(win->stats[0], 6);
        }
        if (totals.boosted[1] != 0) {
            win->stats[1]->setPalette(win->stats[1], 6);
        }
        if (totals.boosted[2] != 0) {
            win->stats[4]->setPalette(win->stats[4], 6);
        }
        for (i = 0; i < 7; i++) {
            win->resistances[i]->setNumber(win->resistances[i], 0, totals.resistances[i]);
            win->resistances[i]->setRightAlign(win->resistances[i], 1);
            win->resistances[i]->setPalette(win->resistances[i], 0);
        }
    } else {
        for (i = 0; i < 6; i++) {
            win->stats[i]->setVisible(win->stats[i], 0);
        }
        for (i = 0; i < 7; i++) {
            win->resistances[i]->setVisible(win->resistances[i], 0);
        }
    }
}

void func_800839E4(TrainScreen *screen, TrainScreenWindows *win, s32 show) {
    TrainTotals totals;
    s32 i;

    if (show) {
        GAME.funcs.computeStats(GAME.funcs.getPartyMember(screen->partner), (PartnerTotals *)&totals);
        win->unk60[0]->setString(win->unk60[0], FILE_CACHE.load(STGTRAIN_TEXT), 4);
        win->unk60[1]->setNumber(win->unk60[1], 0, totals.unk2);
        win->unk60[1]->setRightAlign(win->unk60[1], 1);
    } else {
        for (i = 0; i < 2; i++) {
            win->unk60[i]->setVisible(win->unk60[i], 0);
        }
    }
}

/*
 * Shows the selected partner's stats, in colour where they differ from
 * before (NULL: just shows them). The MP label is given win->mp[3] (that
 * is, slashes[0]) as its window, as in the original. The match depends on
 * the stats and resistances being read as *(totals.stats + i).
 */
void func_80083ADC(TrainScreen *screen, TrainTotals *before) {
    TrainScreenWindows *win = screen->children;
    TrainTotals totals;
    s32 partner;
    s32 i;

    if (before == NULL) {
        func_800834A8(screen, win, 1);
        func_800837D8(screen, win, 1);
        return;
    }
    partner = GAME.funcs.getPartyMember(screen->partner);
    GAME.funcs.getPartnerStats(partner);
    GAME.funcs.computeStats(partner, (PartnerTotals *)&totals);
    win->hp[0]->setString(win->hp[0], FILE_CACHE.load(STGTRAIN_TEXT), 2);
    win->hp[1]->setNumber(win->hp[1], 0, totals.hp);
    win->hp[2]->setNumber(win->hp[2], 0, totals.maxHp);
    for (i = 1; i < 3; i++) {
        win->hp[i]->setRightAlign(win->hp[i], 1);
    }
    if (before->maxHp < totals.maxHp) {
        win->hp[2]->setPalette(win->hp[2], 1);
    } else if (totals.maxHp < before->maxHp) {
        win->hp[2]->setPalette(win->hp[2], 5);
    } else {
        win->hp[2]->setPalette(win->hp[2], 0);
    }
    win->mp[0]->setString(win->mp[i], FILE_CACHE.load(STGTRAIN_TEXT), 3);
    win->mp[1]->setNumber(win->mp[1], 0, totals.mp);
    win->mp[2]->setNumber(win->mp[2], 0, totals.maxMp);
    for (i = 1; i < 3; i++) {
        win->mp[i]->setRightAlign(win->mp[i], 1);
    }
    if (before->maxMp < totals.maxMp) {
        win->mp[2]->setPalette(win->mp[2], 1);
    } else if (totals.maxMp < before->maxMp) {
        win->mp[2]->setPalette(win->mp[2], 5);
    } else {
        win->mp[2]->setPalette(win->mp[2], 0);
    }
    for (i = 0; i < 2; i++) {
        win->slashes[i]->setString(win->slashes[i], FILE_CACHE.load(STGTRAIN_TEXT), 0x43);
    }
    if (totals.boosted[0] != 0) {
        win->stats[0]->setPalette(win->stats[0], 6);
    }
    if (totals.boosted[1] != 0) {
        win->stats[1]->setPalette(win->stats[1], 6);
    }
    if (totals.boosted[2] != 0) {
        win->stats[4]->setPalette(win->stats[4], 6);
    }
    for (i = 0; i < 6; i++) {
        win->stats[i]->setNumber(win->stats[i], 0, *(totals.stats + i));
        win->stats[i]->setRightAlign(win->stats[i], 1);
        if (before->stats[i] < *(totals.stats + i)) {
            win->stats[i]->setPalette(win->stats[i], 1);
        } else if (*(totals.stats + i) < before->stats[i]) {
            win->stats[i]->setPalette(win->stats[i], 5);
        }
    }
    for (i = 0; i < 7; i++) {
        win->resistances[i]->setNumber(win->resistances[i], 0, *(totals.resistances + i));
        win->resistances[i]->setRightAlign(win->resistances[i], 1);
        if (before->resistances[i] < *(totals.resistances + i)) {
            win->resistances[i]->setPalette(win->resistances[i], 1);
        } else if (*(totals.resistances + i) < before->resistances[i]) {
            win->resistances[i]->setPalette(win->resistances[i], 5);
        }
    }
}

/* Draws the screen: the panels, the party's sprites and the sign */
void func_80083F8C(TrainScreen *screen) {
    SpriteDrawer sprite;
    s32 i;
    s32 partner;

    for (i = 0; i < screen->partyCount; i++) {
        if (GFX.funcs.getTime() - screen->anims[i].time >= 0xD) {
            screen->anims[i].time = GFX.funcs.getTime();
            screen->anims[i].frame++;
            partner = GAME.funcs.getPartyMember(i);
            if (screen->anims[i].frame >= 7 || D_8008B72C[partner][screen->anims[i].frame] == -1) {
                screen->anims[i].frame = 0;
            }
        }
    }
    partner = GAME.funcs.getPartyMember(screen->partner);
    if (GFX.funcs.getTime() - screen->time >= 0xD) {
        screen->time = GFX.funcs.getTime();
        screen->frame++;
        if (screen->frame >= 7 || D_8008B72C[partner][screen->frame] == -1) {
            screen->frame = 0;
        }
    }
    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layerId, screen->depth);
    if (screen->panels[0].level != 0) {
        if (screen->panels[0].level != 0x1000) {
            sprite.setScale(screen->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x2B);
        } else {
            sprite.setTexture(0x240, 0x100);
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), D_8008B72C[partner][screen->frame], 0x10, 0x16);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xE, 0, 0xF);
        sprite.setTexture(0x240, 0x100);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x1F, 0, 0xF);
    }
    if (screen->panels[1].level != 0) {
        if (screen->panels[1].level != 0x1000) {
            sprite.setScale(screen->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x7F);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xF, 0, 0x4B);
        sprite.setTexture(0x240, 0x100);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x20, 0, 0x4B);
    }
    if (screen->panels[2].level != 0) {
        if (screen->panels[2].level != 0x1000) {
            sprite.setScale(screen->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xC1);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x21, 0, 0xB6);
    }
    if (screen->panels[5].level != 0) {
        for (i = 0; i < screen->partyCount; i++) {
            if (screen->panels[5].level != 0x1000) {
                sprite.setScale(screen->panels[5].level, 0x1000, 0x1000);
                sprite.setPivot(i * 0x30 + 0xB4, 0x8A);
            }
            partner = GAME.funcs.getPartyMember(i);
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), D_8008B72C[partner][screen->anims[i].frame], i * 0x30 + 0xA4, 0x81);
        }
    }
    if (screen->cursorShown != 0) {
        if (GFX.funcs.getTime() - screen->cursorTime >= 0xB) {
            screen->cursorTime = GFX.funcs.getTime();
            screen->cursorClut++;
            if (screen->cursorClut >= 4) {
                screen->cursorClut = 0;
            }
        }
        sprite.setLayerId(screen->layerId, screen->depth - 2);
        sprite.setTexture(0x140, 0);
        sprite.setClutRow(screen->cursorClut);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xD, screen->partner * 0x30 + 0xA4, 0x65);
        sprite.setClutRow(0);
    }
    if (screen->panels[6].level != 0) {
        if (screen->panels[6].level != 0x1000) {
            sprite.setScale(screen->panels[6].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x8A);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setLayerId(screen->layerId, screen->depth - 1);
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x10, 0x8F, 0x5F);
        sprite.setLayerId(screen->layerId, screen->depth);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x11, 0x8F, 0x5F);
        sprite.setTexture(0x240, 0x100);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x24, 0x8F, 0x5F);
    }
    if (screen->panels[3].level != 0) {
        if (screen->panels[3].level != 0x1000) {
            sprite.setScale(screen->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x1D);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x27, 0x8F, 0xF);
    }
    if (screen->panels[4].level != 0) {
        if (screen->panels[4].level != 0x1000) {
            sprite.setScale(screen->panels[4].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x4E);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x22, 0x92, 0x43);
    }
    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layerId, 7);
    sprite.setTexture(0x240, 0x100);
    if (screen->signTick != 0) {
        screen->signPos++;
        screen->signPos = screen->signPos < 0x60 ? screen->signPos : 0;
        screen->signTick = 0;
    } else {
        screen->signTick = 1;
    }
    sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), screen->sign, screen->signPos, screen->signPos);
}

/* The training screen: opens the panels, picks the partner, runs the menu
   and the trainings, and closes everything when leaving */
void func_800848D0(TrainScreen *screen, TrainScreenWindows *win) {
    s32 i;
    s32 partner;

    switch (screen->substate) {
    case 0:
    default:
        D_8008C4D4.startFade(&screen->panels[0], 1);
        D_8008C4D4.startFade(&screen->panels[3], 1);
        screen->substate++;
        break;
    case 1:
        D_8008C4D4.updateFade(&screen->panels[3]);
        if (D_8008C4D4.updateFade(&screen->panels[0])) {
            func_800834A8(screen, win, 1);
            win->unk68->setString(win->unk68, FILE_CACHE.load(STGTRAIN_TEXT), 5);
            D_8008C4D4.startFade(&screen->panels[1], 1);
            D_8008C4D4.startFade(&screen->panels[4], 1);
            screen->substate++;
        }
        break;
    case 2:
        D_8008C4D4.updateFade(&screen->panels[4]);
        if (D_8008C4D4.updateFade(&screen->panels[1])) {
            func_800837D8(screen, win, 1);
            win->unk6C->setString(win->unk6C, FILE_CACHE.load(STGTRAIN_TEXT), 6);
            D_8008C4D4.startFade(&screen->panels[2], 1);
            D_8008C4D4.startFade(&screen->panels[6], 1);
            screen->substate++;
        }
        break;
    case 3:
        D_8008C4D4.updateFade(&screen->panels[6]);
        if (D_8008C4D4.updateFade(&screen->panels[2])) {
            func_800839E4(screen, win, 1);
            D_8008C4D4.startFade(&screen->panels[5], 1);
            screen->substate++;
        }
        break;
    case 4:
        if (D_8008C4D4.updateFade(&screen->panels[5])) {
            screen->cursorShown = 1;
            screen->substate++;
        }
        break;
    case 5:
        partner = screen->partner;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            screen->partner--;
            if (screen->partner < 0) {
                screen->partner = 0;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            screen->partner++;
            if (screen->partner > screen->partyCount - 1) {
                screen->partner = screen->partyCount - 1;
            }
        }
        if (partner != screen->partner) {
            SOUND.playSound(0x4001B);
            func_800834A8(screen, win, 1);
            func_800837D8(screen, win, 1);
            func_800839E4(screen, win, 1);
            screen->frame = 0;
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            screen->substate = 0x14;
            if (win->menu != NULL) {
                win->menu->state = TASK_KILL;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->substate = 0x32;
        }
        break;
    case 0xA:
        if (win->menu == NULL) {
            win->menu = func_8008AD40(screen);
            screen->substate++;
        }
        break;
    case 0xB:
        if (win->menu == NULL) {
            screen->substate = 0x1E;
        } else if (win->menu->state == TASK_DONE) {
            screen->unk78 = 0;
            win->menu->state = TASK_KILL;
            screen->substate = 0x19;
        }
        break;
    case 0x14:
        screen->panels[5].level = 0;
        D_8008C4D4.startFade(&screen->panels[6], 0);
        screen->cursorShown = 0;
        D_8008C4D4.startFade(&screen->panels[4], 0);
        win->unk6C->setVisible(win->unk6C, 0);
        D_8008C4D4.startFade(&screen->panels[3], 0);
        win->unk68->setVisible(win->unk68, 0);
        screen->substate++;
        break;
    case 0x15:
        D_8008C4D4.updateFade(&screen->panels[6]);
        D_8008C4D4.updateFade(&screen->panels[4]);
        if (D_8008C4D4.updateFade(&screen->panels[3])) {
            screen->substate = 0xA;
        }
        break;
    case 0x19:
        D_8008C4D4.startFade(&screen->panels[3], 1);
        screen->substate++;
        break;
    case 0x1A:
        if (D_8008C4D4.updateFade(&screen->panels[3])) {
            win->unk68->setString(win->unk68, FILE_CACHE.load(STGTRAIN_TEXT), 5);
            D_8008C4D4.startFade(&screen->panels[4], 1);
            screen->substate++;
        }
        break;
    case 0x1B:
        if (D_8008C4D4.updateFade(&screen->panels[4])) {
            win->unk6C->setString(win->unk6C, FILE_CACHE.load(STGTRAIN_TEXT), 6);
            D_8008C4D4.startFade(&screen->panels[6], 1);
            screen->substate++;
        }
        break;
    case 0x1C:
        if (D_8008C4D4.updateFade(&screen->panels[6])) {
            D_8008C4D4.startFade(&screen->panels[5], 1);
            screen->substate = 4;
        }
        break;
    case 0x1E:
        if (win->session == NULL) {
            win->session = func_80088CA8(screen);
            screen->substate++;
            D_8008C4D4.requestFile(screen->unk78);
        }
        break;
    case 0x1F:
        if (win->session->substate == 0x23) {
            if (win->result != NULL) {
                win->result->state = TASK_KILL;
            } else {
                screen->substate = 0x23;
                func_800839E4(screen, win, 1);
            }
        } else if (win->session->state == TASK_DONE) {
            win->session->state = TASK_KILL;
            screen->substate = 0xA;
        }
        break;
    case 0x23:
        if (D_8008C4D4.getFile() != NULL && win->result == NULL) {
            win->result = func_800875E8(screen, GAME.funcs.getPartyMember(screen->partner), screen->unk78);
            screen->substate++;
        }
        break;
    case 0x24:
        if (win->result == NULL) {
            win->session->finish(win->session);
            screen->substate++;
        }
        break;
    case 0x25:
        if (win->session == NULL) {
            func_800837D8(screen, win, 1);
            screen->substate = 0x19;
        }
        break;
    case 0x32:
        win->fade = func_80085898();
        win->fade->start(win->fade, 0, 30);
        screen->panels[5].level = 0;
        for (i = 0; i < 3; i++) {
            D_8008C4D4.startFade(&screen->panels[i], 0);
        }
        func_800834A8(screen, win, 0);
        func_800837D8(screen, win, 0);
        func_800839E4(screen, win, 0);
        D_8008C4D4.startFade(&screen->panels[6], 0);
        screen->cursorShown = 0;
        D_8008C4D4.startFade(&screen->panels[4], 0);
        win->unk6C->setVisible(win->unk6C, 0);
        D_8008C4D4.startFade(&screen->panels[3], 0);
        win->unk68->setVisible(win->unk68, 0);
        screen->substate++;
        break;
    case 0x33:
        for (i = 0; i < 3; i++) {
            D_8008C4D4.updateFade(&screen->panels[i]);
        }
        D_8008C4D4.updateFade(&screen->panels[6]);
        D_8008C4D4.updateFade(&screen->panels[4]);
        if (D_8008C4D4.updateFade(&screen->panels[3])) {
            screen->substate++;
        }
        break;
    case 0x34:
        if (win->fade->state == TASK_DONE) {
            screen->state = TASK_KILL;
        }
        break;
    }
}

/* The training screen's update: loads its files, then runs the menu */
void func_800852E4(TrainScreen *screen, TrainScreenWindows *win) {
    s32 i;

    switch (screen->state) {
    case TASK_INIT:
    default:
        switch (screen->substate) {
        case 0:
        default:
            D_8008C4D4.loadFiles();
            FILE_CACHE.request(STGTRAIN_TEXT);
            SOUND_STATE.loadBank(0x21);
            screen->substate++;
            break;
        case 1:
            if (FILE_CACHE.isLoading(STGTRAIN_TEXT) == 0) {
                screen->nextState(screen);
                func_80083284(screen, win);
                for (i = 0; i < 3; i++) {
                    if (GAME.funcs.getPartyMember(i) != -1) {
                        screen->partyCount++;
                    }
                }
                for (i = 2; i >= 0; i--) {
                    screen->panels[i].duration = 10;
                }
                screen->panels[3].duration = 10;
                screen->panels[4].duration = 10;
                screen->panels[6].duration = 10;
                screen->panels[5].duration = 8;
                screen->setState(screen, TASK_DONE);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_800848D0(screen, win);
        func_80083F8C(screen);
        break;
    case TASK_DONE:
        if (SOUND_STATE.isLoading() == 0) {
            SOUND_STATE.playSound(0x60840002);
            screen->setState(screen, TASK_RUN);
        }
        break;
    case TASK_KILL:
        SOUND_STATE.stopSound(0x60840002);
        GAME.funcs.requestMode(GAME.fieldMode, 0);
        break;
    }
}

/* Creates the training screen */
TrainScreen *func_800854FC(void) {
    TrainScreen *screen = createTask(func_800852E4, sizeof(TrainScreen), 0x80);
    s32 sign;

    screen->showStats = func_80083ADC;
    screen->layerId = 0x1000;
    screen->depth = 6;
    /* the gym's sign, by the stage the player came from */
    switch (GAME.funcs.getPrevMode()) {
    case 0x23D: /* South Cape */
        sign = 0x2E;
        break;
    case 0x24B: /* North Wind Wasteland East */
        sign = 0x2F;
        break;
    case 0x267: /* the Legendary Gym */
        sign = 0x30;
        break;
    case 0x28C: /* Central Park, in Amaterasu */
        sign = 0x31;
        break;
    case 0x2AA: /* South Cape, in Amaterasu */
        sign = 0x32;
        break;
    case 0x2B5: /* North Wind Wasteland East, in Amaterasu */
        sign = 0x33;
        break;
    case 0x2CF: /* the Legendary Gym, in Amaterasu */
        sign = 0x34;
        break;
    case 0x21D: /* Central Park */
    default:
        sign = 0x2D;
        break;
    }
    screen->sign = sign;
    return screen;
}

void func_80085618(ScreenFade *task, s32 fadeIn, s32 duration) {
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

void func_800856A0(ScreenFade *task) {
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

void func_800857E4(ScreenFade *task) {
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
        func_800856A0(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *func_80085898(void) {
    ScreenFade *task = createTask(func_800857E4, sizeof(ScreenFade), 0);

    task->start = func_80085618;
    task->layerId = 0x1000;
    task->depth = 6;
    return task;
}

extern TrainGain D_8008B884[];
extern TrainGain D_8008B8CC[];
extern TrainGain D_8008B914[];
extern TrainInfo D_8008C0EC[];
void func_8008ADAC(void);
void func_8008AE04(PanelAnim *fade, s32 fadeIn);
s32 func_8008AE98(PanelAnim *fade);
void func_8008AF04(MenuLerp *lerp, s32 from, s32 to, s32 frames);
s32 func_8008AF44(MenuLerp *lerp);
s32 func_8008AFB0(s32 index);
u8 *func_8008B040(void);
void func_8008B0D8(void);
s32 func_8008B298(s32 set);
s32 func_8008B35C(s32 set, s32 *pos);
s32 func_8008B56C(s32 index);
s32 func_8008B588(s32 index);
s32 func_8008B5AC(s32 index);
TrainSpriteBank *func_8008B5C8(s32 set);
s32 func_8008B5EC(s32 set);
s32 func_8008B610(s32 set);
TrainAnim *func_8008B634(s32 set, s32 i);
s32 *func_8008B660(s32 index);
s32 *func_8008B6D0(s32 index, s32 id);

/* The partners' sprites while they wait, by partner: -1 ends a loop */
s32 D_8008B72C[8][7] = {
    {7, 8, 9, 10, 9, 8, -1},
    {14, 15, 16, 15, -1, -1, -1},
    {11, 12, 13, 12, -1, -1, -1},
    {3, 4, 5, 6, 5, 4, -1},
    {25, 26, 27, 28, 27, 26, -1},
    {0, 1, 2, 1, -1, -1, -1},
    {17, 18, 19, 20, 19, 18, -1},
    {21, 22, 23, 24, 23, 22, -1},
};
/* The battle stats a training raises, by [training >= 13][unkD8][level] */
TrainGain D_8008B80C[] = {
    {1, 2}, {7, 2}, {14, 3},
    {2, 0}, {10, 0}, {20, 0},
    {1, 2}, {6, 3}, {11, 5},
    {4, 0}, {22, 0}, {48, 0},
};
/* What a training may lower another battle stat by, by level */
TrainGain D_8008B86C[] = {
    {1, 0}, {2, 3}, {4, 3},
};
/* The resistance gains, by [unkD8 ? (training < 13 ? 1 : 2) : 0][level] */
TrainGain D_8008B884[] = {
    {1, 0}, {1, 0}, {2, 0},
    {4, 2}, {8, 0}, {12, 0},
    {8, 2}, {20, 0}, {30, 0},
};
TrainGain D_8008B8CC[] = {
    {1, 2}, {2, 0}, {3, 0},
    {6, 3}, {12, 0}, {18, 0},
    {12, 4}, {30, 0}, {40, 0},
};
TrainGain D_8008B914[] = {
    {2, 0}, {2, 0}, {4, 0},
    {8, 4}, {12, 0}, {25, 0},
    {16, 5}, {30, 0}, {50, 0},
};
/* The resistance gain tables, by the Digimon's affinity and the
   resistance's value (under 100, under 300, more) */
TrainGain *D_8008B95C[] = {
    D_8008B884, D_8008B8CC, D_8008B8CC, D_8008B884,
    D_8008B8CC, D_8008B8CC, D_8008B8CC, D_8008B8CC,
    D_8008B8CC, D_8008B914, D_8008B914, D_8008B8CC,
    D_8008B914, D_8008B914, D_8008B8CC,
};
/* The max HP and MP gains, indexed like the resistances */
TrainGain D_8008B998[] = {
    {1, 2}, {2, 0}, {4, 0},
    {6, 4}, {10, 0}, {20, 0},
    {13, 5}, {20, 0}, {40, 0},
};
s32 D_8008B9E0[] = {
    1, 5, 10,
};
/* The trainings of each gym level, by D_8008B6D0: {id, ?}, 0 ends */
s32 D_8008B9EC[14][16][2] = {
    {
        {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0},
    },
    {
        {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {8, 0x5000A}, {9, 0x1000B},
        {10, 0x4000C}, {0, 0}, {0, 0}, {0, 0},
    },
    {
        {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {8, 0x5000A}, {9, 0x1000B},
        {10, 0x4000C}, {12, 0x3000E}, {0, 0}, {0, 0},
    },
    {
        {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {8, 0x5000A}, {9, 0x1000B},
        {10, 0x4000C}, {11, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {8, 0x5000A}, {9, 0x1000B},
        {10, 0x4000C}, {11, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {20, 0x5000A}, {9, 0x1000B},
        {10, 0x4000C}, {11, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {17, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {20, 0x5000A}, {9, 0x1000B},
        {10, 0x4000C}, {11, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {19, 0x20009}, {8, 0x5000A}, {9, 0x1000B},
        {22, 0x4000C}, {11, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {17, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {19, 0x20009}, {20, 0x5000A}, {9, 0x1000B},
        {22, 0x4000C}, {11, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {8, 0x5000A}, {21, 0x1000B},
        {10, 0x4000C}, {23, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {17, 5}, {0, 0}, {0, 0}, {0, 0},
        {6, 0x100008}, {7, 0x20009}, {20, 0x5000A}, {21, 0x1000B},
        {10, 0x4000C}, {23, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {5, 5}, {0, 0}, {0, 0}, {0, 0},
        {18, 0x100008}, {19, 0x20009}, {8, 0x5000A}, {21, 0x1000B},
        {22, 0x4000C}, {23, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {17, 5}, {0, 0}, {0, 0}, {0, 0},
        {18, 0x100008}, {19, 0x20009}, {20, 0x5000A}, {21, 0x1000B},
        {22, 0x4000C}, {23, 0xF000D}, {12, 0x3000E}, {0, 0},
    },
    {
        {13, 1}, {14, 2}, {15, 3}, {16, 4},
        {17, 5}, {0, 0}, {0, 0}, {0, 0},
        {18, 0x100008}, {19, 0x20009}, {20, 0x5000A}, {21, 0x1000B},
        {22, 0x4000C}, {23, 0xF000D}, {24, 0x3000E}, {0, 0},
    },
};
/* The trainings: their name and description in the text file, and the
   frames of their icon */
TrainInfo D_8008C0EC[] = {
    {0, 0, {0, 0, 0, 0}},
    {19, 43, {0, 1, 2, 3}},
    {20, 44, {4, 5, 6, 7}},
    {21, 45, {8, 9, 10, 11}},
    {22, 46, {12, 13, 14, 15}},
    {23, 47, {16, 17, 18, 19}},
    {29, 53, {20, 21, 22, 23}},
    {30, 54, {24, 25, 26, 27}},
    {31, 55, {28, 29, 30, 31}},
    {32, 56, {32, 33, 34, 35}},
    {33, 57, {36, 37, 38, 39}},
    {34, 58, {40, 41, 42, 43}},
    {35, 59, {95, 96, 97, 98}},
    {24, 48, {45, 46, 47, 48}},
    {25, 49, {49, 50, 51, 52}},
    {26, 50, {53, 54, 55, 56}},
    {27, 51, {57, 58, 59, 60}},
    {28, 52, {61, 62, 63, 64}},
    {36, 60, {65, 66, 67, 68}},
    {37, 61, {71, 72, 73, 74}},
    {38, 62, {75, 76, 77, 78}},
    {39, 63, {79, 80, 81, 82}},
    {40, 64, {83, 84, 85, 86}},
    {41, 65, {87, 88, 89, 90}},
    {42, 66, {91, 92, 93, 94}},
};
/* the discs number their files differently */
#if VERSION_US
TrainFile D_8008C344[] = {
    {591, 82, 31, 0},
    {591, 82, 31, 0},
    {1070, 79, 31, 0},
    {625, 78, 27, 0},
    {626, 79, 24, 1},
    {627, 79, 31, 0},
    {628, 79, 31, 0},
    {755, 79, 31, 0},
    {756, 81, 31, 1},
    {1071, 79, 31, 0},
    {629, 47, 35, 1},
    {630, 79, 31, 0},
    {757, 79, 31, 1},
    {591, 82, 31, 0},
    {1070, 79, 31, 0},
    {625, 78, 27, 0},
    {626, 79, 24, 1},
    {627, 79, 31, 0},
    {628, 79, 31, 0},
    {755, 79, 31, 0},
    {756, 81, 31, 1},
    {1071, 79, 31, 0},
    {629, 47, 35, 1},
    {630, 79, 31, 0},
    {757, 79, 31, 1},
};
#elif VERSION_EU
TrainFile D_8008C344[] = {
    {606, 82, 31, 0},
    {606, 82, 31, 0},
    {1086, 79, 31, 0},
    {640, 78, 27, 0},
    {641, 79, 24, 1},
    {642, 79, 31, 0},
    {643, 79, 31, 0},
    {770, 79, 31, 0},
    {771, 81, 31, 1},
    {1087, 79, 31, 0},
    {644, 47, 35, 1},
    {645, 79, 31, 0},
    {772, 79, 31, 1},
    {606, 82, 31, 0},
    {1086, 79, 31, 0},
    {640, 78, 27, 0},
    {641, 79, 24, 1},
    {642, 79, 31, 0},
    {643, 79, 31, 0},
    {770, 79, 31, 0},
    {771, 81, 31, 1},
    {1087, 79, 31, 0},
    {644, 47, 35, 1},
    {645, 79, 31, 0},
    {772, 79, 31, 1},
};
#endif
TrainState D_8008C4D4 = {
    0, NULL, 0, {{0}}, D_8008C0EC,
    func_8008ADAC, func_8008AE04, func_8008AE98, func_8008AF04,
    func_8008AF44, func_8008AFB0, func_8008B040, func_8008B0D8,
    func_8008B298, func_8008B35C, func_8008B56C, func_8008B588,
    func_8008B5AC, func_8008B5C8, func_8008B5EC, func_8008B610,
    func_8008B634, func_8008B660, func_8008B6D0,
};
TrainCursor D_8008C800 = {NULL};
TrainCursor D_8008C804 = {NULL};
TrainCursor D_8008C808 = {NULL};
TrainCursor D_8008C80C = {NULL};
