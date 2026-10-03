#include "fieldstg.h"

void func_80082F1C(Task *task) {
    switch (task->state) {
    case 0:
    case 1:
    default:
        if (task->substate == 1) {
            func_80090154();
            task->setSubstate(task, 0);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80082F84);

void func_80083470(void) {
    createTaskWithId(func_80082F1C, sizeof(Task), 0, 0x32D);
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_800834A0);

void func_800838BC(Unk800834A0 *task, s32 arg1) {
    if (task != NULL) {
        switch (arg1) {
        case 0x348:
            task->setState(task, 2);
            task->unk58 = 0;
            break;
        case 0x349:
            task->setState(task, 2);
            task->unk58 = 1;
            break;
        }
    }
}

Unk800834A0 *func_80083930(s32 id) {
    Unk800834A0 *task = createTaskWithId(func_800834A0, sizeof(Unk800834A0), 0, id);

    if (FLAGS_00.checkCondition(0x1C3D, 1)) {
        task->unk58 = 1;
    } else {
        task->unk58 = 0;
    }
    return task;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80083998);

void func_80083F8C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 0;
}

void func_80083FBC(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 1;
}

void func_80083FF0(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 2;
}

void func_80084024(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 3;
}

void func_80084058(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 4;
}

void func_8008408C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 5;
}

void func_800840C0(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 6;
}

void func_800840F4(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 7;
}

void func_80084128(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 8;
}

void func_8008415C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 9;
}

void func_80084190(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 10;
}

void func_800841C4(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 11;
}

void func_800841F8(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 12;
}

void func_8008422C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 13;
}

void func_80084260(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 14;
}

void func_80084294(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 15;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_800842C8);

Unk800842C8 *func_800844B8(s32 arg0) {
    Unk800842C8 *task = createTask(func_800842C8, sizeof(Unk800842C8), 8);

    task->unk50 = arg0;
    FIELDSTG_initFuncs[0]();
    return task;
}

s32 func_80084514(Unk80084654 *arg0, s32 id) {
    s32 i;

    if (id < 0x320) {
        for (i = 0; i < 30; i++) {
            if (arg0->entries[i].id == 0) {
                break;
            }
            if (arg0->entries[i].id == id) {
                return arg0->entries[i].value;
            }
        }
    }
    return 0;
}

s32 func_80084558(Unk80084654 *task, s16 *op, Unk80084654Children *children) {
    s32 id = op[1];
    s32 arg1 = op[2];
    s32 arg2 = op[3];
    Actor *actor;
    s32 target;
    s32 i;

    if (id < 0x320) {
        actor = (Actor *)func_80084514(task, id);
        if (actor != NULL) {
            actor->unk148(actor, arg1, arg2);
        }
    } else {
        target = (s32)TASK_FUNCS.find(id, -1, -1);
        if (target == 0) {
            for (i = 0; i < 10; i++) {
                if (children->scripts[i] == 0) {
                    children->scripts[i] = func_80091730(id);
                    if (children->scripts[i] != 0) {
                        target = children->scripts[i];
                    }
                    break;
                }
            }
        }
        if (target != 0) {
            func_80091774(target, id, arg1, arg2);
        }
    }
    return 4;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80084654);

Unk80084654 *func_80084B80(s32 id) {
    Unk80084654 *task = createTask(func_80084654, sizeof(Unk80084654), 0x38);
    Unk80084B80Entry *entry;
    Task *other;
    s32 text;

    for (entry = D_800990B4.unk24; entry->id != -1; entry++) {
        if (entry->id == id) {
            task->unk50 = id;
            task->unk54 = entry->unk4;
            task->unk58 = entry->unkC;
            task->unk5C = entry->unk10;
            D_800990B4.unk48 = text = entry->text;
            if (text != 0) {
                D_800990B4.unk48 = text + (TEXT_FILE(1) << 16);
                FILE_CACHE.request(entry->text >> 16);
            }
            D_800990B4.unk58 = 1;
            if (id < 8000 || id >= 9000) {
                other = TASK_FUNCS.find(5, -1, 0);
                if (other != NULL && other->state == 1) {
                    other->setSubstate(other, 1);
                }
            }
            break;
        }
    }
    if (D_800990B4.unk58 == 0) {
        task->setState(task, 3);
    }
    return task;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80084D0C);

void func_80085240(s32 arg0) {
    Unk80084D0C *task = createTask(func_80084D0C, sizeof(Unk80084D0C), 0);

    task->unk50 = arg0;
}

s32 func_80085278(Unk80085278 *anim, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[anim->anim.index];
    s32 elapsed = GFX_FUNCS.getFrameTime();

    if (elapsed > 4) {
        elapsed = 4;
    }
    if (depth == 0) {
        anim->anim.timer -= elapsed;
    }
    if (anim->anim.timer <= 0) {
        frame++;
        anim->anim.index++;
        anim->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            return 0xFF;
        }
        func_80085278(anim, frames, depth + 1);
    }
    return frame->frame;
}

void func_80085350(Unk80085350 *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    SpriteDrawer sprite;
    s32 i;
    s32 j;
    s32 frame;

    switch (task->state) {
        default:
        case 0:
            for (i = 0; i < 4; i++) {
                task->anims[i].active = 1;
                task->anims[i].anim.index = 0;
                task->anims[i].anim.timer = D_800961E4[task->set][i][0].duration;
            }
            task->nextState(task);
            break;
        case 1:
            for (j = 0; j < 4; j++) {
                if (task->anims[j].active != 0) {
                    frame = func_80085278(&task->anims[j], D_800961E4[task->set][j], 0);
                    switch (frame) {
                        case 0x12C:
                            break;
                        case 0xFF:
                            task->anims[j].active = 0;
                            break;
                        default:
                            initSpriteDrawer(&sprite);
                            sprite.setTexture(0x240, 0x100);
                            sprite.setLayer(layer, 0);
                            sprite.setClutRow(0);
                            sprite.draw(FILE_CACHE.getEntry(FIELD_SPRITES_FILE << 16 | 1), frame, task->x, task->y);
                            break;
                    }
                }
            }
            if (task->anims[0].active == 0 && task->anims[1].active == 0 && task->anims[2].active == 0
                && task->anims[3].active == 0) {
                task->setState(task, 3);
            }
            break;
        case 2:
        case 3:
            break;
    }
}

void func_80085588(s32 arg0, s32 arg1, s32 arg2) {
    Unk80085350 *task = createTask(func_80085350, sizeof(Unk80085350), 0);

    task->x = arg0;
    task->y = arg1;
    task->set = arg2;
}

StreamTask *func_800855E0(StreamPool *pool) {
    s32 i;
    s32 oldest = GFX_FUNCS.getTime();
    StreamTask *found = pool->tasks[0];

    for (i = 0; i < 30; i++) {
        if (pool->tasks[i]->time <= oldest) {
            oldest = pool->tasks[i]->time;
            found = pool->tasks[i];
        }
    }
    return found;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80085650);

void func_800857DC(Layer *layer, s32 x, s32 y, s32 level) {
    Point scroll;
    SPRT *prim;
    u_long *ot;
    s32 i;
    s32 shade;

    ot = (u_long *)layer->getOtEntry(layer, 0);
    shade = level >> 8;
    layer->getScroll(layer, &scroll);
    prim = GFX_FUNCS.getPrim();
    for (i = 0; i < 4; i++) {
        SetSprt(prim);
        if (shade != 0xFF) {
            SetSemiTrans(prim, 1);
        }
        prim->r0 = prim->g0 = prim->b0 = shade;
        prim->x0 = x - scroll.x + ((i & 1) << 6);
        prim->y0 = y - scroll.y + ((i << 5) & 0x40);
        prim->u0 = D_800990B4.unk28->u;
        prim->v0 = D_800990B4.unk28->v;
        prim->w = 0x40;
        prim->h = 0x40;
        prim->clut = GetClut(D_800990B4.unk28->clutX, D_800990B4.unk28->clutY);
        addPrim(ot, prim);
        prim++;
        SetDrawTPage((DR_TPAGE *)prim, 0, 1, GetTPage(0, 1, D_800990B4.unk28->x, D_800990B4.unk28->y));
        addPrim(ot, prim);
        prim = (SPRT *)((DR_TPAGE *)prim + 1);
    }
    GFX_FUNCS.setPrim(prim);
}

StreamTask *func_80085A00(StreamPool *pool, s32 frame) {
    s32 i;
    StreamTask *task;

    for (i = 0; i < 30; i++) {
        task = pool->tasks[i];
        if (task->getFrame(task) == frame) {
            return task;
        }
    }
    return NULL;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80085A78);

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80085EEC);

void func_80086144(Unk80086144 *task, StreamPool *pool) {
    s32 *header;
    s32 count;
    s32 i;
    s32 j;
    Layer *layer;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            if (CD_READER.isBusy() == 0) {
                task->unk54 = HEAP.alloc(0x800, 2);
                CD_READER.read(task->unk64, 0, 1, task->unk54, NULL);
                task->nextSubstate(task);
            }
            break;
        case 1:
            if (CD_READER.isBusy() != 1) {
                header = task->unk54;
                task->unk68 = header[1];
                task->unk6C = header[2];
                task->unk70 = header[3] / 2048;
                count = task->unk68 * task->unk6C;
                task->unk104 = HEAP.alloc(count * sizeof(MapTile), 2);
                for (j = 0; j < count; j++) {
                    task->unk104[j].unk0 = ((u16 *)header)[j + 8];
                    task->unk104[j].unk4 = ((u16 *)header)[j + 8] >> 11;
                }
                HEAP.free(task->unk54);
                task->unk54 = NULL;
                for (i = 0; i < 30; i++) {
                    pool->tasks[i] = func_80086B54(task->unk70 << 11, task->unk64);
                }
                for (i = 0; i < 12; i++) {
                    task->unk74[i].unk0 = -1;
                    task->unk74[i].unk4 = 0;
                }
                pool->decompressor = createDecompressor();
                task->nextState(task);
            }
            break;
        }
        break;
    case 1:
        layer = GFX_FUNCS.getLayer(0x1002);
        layer->getScroll(layer, &task->scroll);
        func_80085EEC(task);
        func_80085A78(task, pool);
        func_80085650(task, pool);
        break;
    case 2:
        break;
    case 3:
        if (task->unk54 != NULL) {
            HEAP.free(task->unk54);
        }
        if (task->unk104 != NULL) {
            HEAP.free(task->unk104);
        }
        break;
    }
}

Point *func_800863F4(Unk80086144 *arg0) {
    D_8009A938.x = arg0->unk68 << 7;
    D_8009A938.y = arg0->unk6C << 7;
    return &D_8009A938;
}

void func_80086418(s32 arg0) {
    Unk80086144 *task = createTaskWithId(func_80086144, sizeof(Unk80086144), 0x7C, 4);

    task->unk64 = arg0;
    task->unk130 = func_800863F4;
}

void func_80086460(s32 id, s32 level) {
    Layer *layer = GFX_FUNCS.getLayer(id);
    s32 x;
    s32 y;

    if (layer != NULL) {
        for (y = 0; y < 0xF0; y += 0x80) {
            for (x = 0; x < 0x140; x += 0x80) {
                func_800857DC(layer, x, y, level);
            }
        }
    }
}

void func_800864E8(StreamTask *task) {
    task->time = GFX_FUNCS.getTime();
}

void func_80086518(StreamTask *task, s32 frame, s32 size) {
    if (task->frame != frame) {
        task->frame = frame;
        task->loaded = 0;
        task->unk70 = -1;
        task->sector = frame * task->frameSectors + 1;
        CD_READER.read(task->file, task->sector, size, task->buffer, &task->loaded);
        task->unk54 = 0;
    }
    func_800864E8(task);
}

s32 func_800865A0(StreamTask *task) {
    return task->loaded;
}

void func_800865AC(StreamTask *task, Layer *layer, s32 x, s32 y) {
    Point scroll;
    SPRT *prim;
    u_long *ot;
    s32 i;
    s32 j;

    layer->getScroll(layer, &scroll);
    prim = GFX_FUNCS.getPrim();
    for (i = 0; i < 3; i++) {
        ot = (u_long *)layer->getOtEntry(layer, D_8009638C[i]);
        for (j = 0; j < 5; j++) {
            if (task->sprites[i][j].visible) {
                SetSprt(prim);
                if (i == 2 || D_800990B4.unk38.cd != 0) {
                    prim->r0 = D_800990B4.unk38.r;
                    prim->g0 = D_800990B4.unk38.g;
                    prim->b0 = D_800990B4.unk38.b;
                } else {
                    prim->r0 = 0x80;
                    prim->g0 = 0x80;
                    prim->b0 = 0x80;
                }
                prim->x0 = task->sprites[i][j].x + x - scroll.x;
                prim->y0 = task->sprites[i][j].y + y - scroll.y;
                prim->w = task->sprites[i][j].w;
                prim->h = task->sprites[i][j].h;
                prim->clut = getClut(task->clutX, task->clutY);
                prim->u0 = task->sprites[i][j].u;
                prim->v0 = task->imageY + task->sprites[i][j].v;
                addPrim(ot, prim);
                prim++;
            }
        }
        SetDrawTPage((DR_TPAGE *)prim, 0, 1, GetTPage(1, 0, task->imageX, task->imageY));
        addPrim(ot, prim);
        prim = (SPRT *)((DR_TPAGE *)prim + 1);
    }
    GFX_FUNCS.setPrim(prim);
    func_800864E8(task);
}

void func_80086858(StreamTask *task, s32 slot, StreamSource *source) {
    task->slot = slot;
    task->source = source;
    source->unk7C(source, task->buffer, 0x2800);
    task->setSubstate(task, 1);
}

void func_800868AC(StreamTask *task) {
    TimLoader loader;
    s32 i;
    s32 j;
    s32 count;
    s32 *data = task->unk230;
    s32 slot = task->slot;
    s16 *p = (s16 *)(data + 1);

    for (i = 0; i < 3; i++) {
        count = *(s32 *)p;
        p += 2;
        for (j = 0; j < count; j++) {
            task->sprites[i][j].visible = 1;
            task->sprites[i][j].x = *p++;
            task->sprites[i][j].y = *p++;
            task->sprites[i][j].u = *p++;
            task->sprites[i][j].v = *p++;
            task->sprites[i][j].w = *p++;
            task->sprites[i][j].h = *p++;
        }
        for (; j < 5; j++) {
            task->sprites[i][j].visible = 0;
        }
    }
    task->unk70 = slot;
    task->imageX = D_80096398[slot].x;
    task->imageY = D_80096398[slot].y;
    task->clutX = 0;
    task->clutY = slot + 0xF0;
    initTimLoader(&loader);
    loader.setImagePos(task->imageX, task->imageY);
    loader.setClutPos(task->clutX, task->clutY);
    loader.load(FILE_CACHE.getArchiveEntry(0, (s32)data));
    func_800864E8(task);
}

void func_80086A3C(StreamTask *task) {
    task->unk70 = -1;
}

s32 func_80086A48(StreamTask *task) {
    return task->unk70;
}

s32 func_80086A54(StreamTask *task) {
    return task->frame;
}

void func_80086A60(StreamTask *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            task->unk230 = task->source->unk78(task->source);
            if (task->unk230 != NULL) {
                func_800868AC(task);
                task->setSubstate(task, 0);
            }
            break;
        }
        if (task->unk54 == 0 && task->loaded != 0) {
            task->unk54 = GFX_FUNCS.getTime();
        }
        break;
    case 2:
        break;
    case 3:
        HEAP.free(task->buffer);
        break;
    }
}

StreamTask *func_80086B54(s32 size, s32 file) {
    StreamTask *task = createTask(func_80086A60, sizeof(StreamTask), 0);

    task->seek = func_80086518;
    task->draw = func_800865AC;
    task->setSource = func_80086858;
    task->getFrame = func_80086A54;
    task->isLoaded = func_800865A0;
    task->unk248 = func_80086A48;
    task->unk24C = func_80086A3C;
    task->updateTime = func_800864E8;
    task->file = file;
    task->frameSectors = size / 2048;
    task->buffer = HEAP.allocHigh(size, 2);
    task->frame = -1;
    task->unk70 = -1;
    task->loaded = 1;
    return task;
}

void func_80086C4C(Task *task, Task **children) {
    s32 mode;

    switch (task->state) {
        default:
        case 0:
            mode = GAME.funcs.getMode();
            if (GAME.unk26D4 != mode) {
                GAME.unk26D4 = mode;
                GAME.clearTempFlags = 1;
#if VERSION_EU
                GAME.unk26F8 = 0x10;
#endif
            } else {
                GAME.clearTempFlags = 0;
            }
            children[0] = func_8008ADE8();
            task->nextState(task);
            break;
        case 1:
        case 2:
        case 3:
            break;
    }
}

void func_80086CF4(void) {
    createTask(func_80086C4C, sizeof(Task), 0xC);
}

void func_80086D20(Task *task, AreaNameWindows *windows) {
    s16 mode = GAME_FUNCS.getMode();
    s32 i;

    for (i = 0; D_800963F8[i].mode != 0; i++) {
        if (D_800963F8[i].mode == mode) {
            windows->area = createTextWindow(0x1003, 1, 0x80, 0x1A);
            windows->area->setString(windows->area, FILE_CACHE.load(TEXT_FILE(0xAA)), D_800963F8[i].area);
            windows->area->setTypeDelay(windows->area, 5);
            windows->place = createTextWindow(0x1003, 1, 0x28, 0x44);
            windows->place->setString(windows->place, FILE_CACHE.load(TEXT_FILE(0xB8)), D_800963F8[i].place);
            windows->place->setTypeDelay(windows->place, 5);
            break;
        }
    }
}

/* Stretches a box toward from-to along one axis. The match depends on each
   case having its own variables. */
void func_80086E64(Unk800870D4 *task, Unk800870D4Box *box) {
    switch (box->stretch) {
    case 1: {
        s32 start = box->pos.vx;
        s32 end = start + box->size.vx;
        s32 from = box->from;
        s32 to = box->to;
        s32 speed = box->speed;

        if (start < from) {
            start += speed;
            if (start > from) {
                start = from;
            }
        } else if (start > from) {
            start -= speed;
            if (start < from) {
                start = from;
            }
        }
        if (end < to) {
            end += speed;
            if (end > to) {
                end = to;
            }
        } else if (end > to) {
            end -= speed;
            if (end < to) {
                end = to;
            }
        }
        box->pos.vx = start;
        box->size.vx = end - start;
        if (start == from && end == to) {
            box->stretch = 0;
        }
        break;
    }
    case 2: {
        s32 start = box->pos.vy;
        s32 end = start + box->size.vy;
        s32 from = box->from;
        s32 to = box->to;
        s32 speed = box->speed;

        if (start < from) {
            start += speed;
            if (start > from) {
                start = from;
            }
        } else if (start > from) {
            start -= speed;
            if (start < from) {
                start = from;
            }
        }
        if (end < to) {
            end += speed;
            if (end > to) {
                end = to;
            }
        } else if (end > to) {
            end -= speed;
            if (end < to) {
                end = to;
            }
        }
        box->pos.vy = start;
        box->size.vy = end - start;
        if (start == from && end == to) {
            box->stretch = 0;
        }
        break;
    }
    }
}

void func_80086FB4(Unk800870D4 *task, u_long *ot, DVECTOR pos, DVECTOR size, s32 color) {
    POLY_F4 *poly = GFX.funcs.getPrim();

    setlen(poly, 5);
    *(s32 *)&poly->r0 = color;
    poly->code = 0x28;
    poly->x0 = pos.vx;
    poly->x1 = pos.vx + size.vx;
    poly->x2 = pos.vx;
    poly->x3 = pos.vx + size.vx;
    poly->y0 = pos.vy;
    poly->y1 = pos.vy;
    poly->y2 = pos.vy + size.vy;
    poly->y3 = pos.vy + size.vy;
    addPrim(ot, poly);
    GFX.funcs.setPrim(poly + 1);
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_800870D4);

Task *func_800874C8(s32 arg0) {
    Task *task = createTaskWithId(func_800870D4, sizeof(Unk800870D4), 8, 9);

    task->key1 = arg0;
    D_800990B4.unk54 = 1;
    return task;
}

s32 func_80087510(Unk800876E4 *task) {
    task->time -= GFX_FUNCS.getFrameTime();
    if (task->time < 0) {
        task->frame += 2;
        if (D_80096920[task->key2][task->frame] == 0xFF) {
            task->frame = 0;
        }
        task->time = D_80096920[task->key2][task->frame + 1];
    }
    return D_80096920[task->key2][task->frame];
}

void func_800875DC(Unk800876E4 *task) {
    SpriteDrawer sprite;
    Point pos;
    s32 frame;

    pos.x = task->actor->tile.x;
    pos.y = task->actor->tile.y - (task->actor->unk64 >> 8);
    initSpriteDrawer(&sprite);
    sprite.setLayerId(0x1002, 1);
    sprite.setTexture(0x200, 0x100);
    if (task->substate == 2) {
        frame = func_80087510(task);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), frame, pos.x, pos.y - 0x1B);
    }
    sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), task->unk60 >> 2, pos.x, pos.y - 0x1B);
}

void func_800876E4(Unk800876E4 *task) {
    switch (task->state) {
        default:
        case 0:
            if (task->actor == NULL) {
                task->actor = TASK_FUNCS.find(5, -1, 0);
                if (task->actor == NULL) {
                    break;
                }
            }
            if (task->key1 == 0) {
                task->unk54 = 0xC8;
                task->unk58 = 0xD4;
                task->unk5C = 0xDC;
            } else {
                task->unk54 = 0x104;
                task->unk58 = 0x10C;
                task->unk5C = 0x114;
            }
            if (task->key2 != 1) {
                SOUND.playSound(0x40007);
            }
            task->nextState(task);
            /* fallthrough */
        case 1:
            if (D_800990B4.unk50 != 0) {
                break;
            }
            switch (task->substate) {
                default:
                case 0:
                    task->unk60 = task->unk54;
                    task->nextSubstate(task);
                    /* fallthrough */
                case 1:
                    task->unk60 += GFX_FUNCS.getFrameTime();
                    if (task->unk60 >= task->unk58) {
                        task->unk60 = task->unk58;
                        task->nextSubstate(task);
                    }
                    break;
                case 2:
                    break;
            }
            func_800875DC(task);
            break;
        case 2:
            task->unk60 += GFX_FUNCS.getFrameTime();
            if (task->unk60 >= task->unk5C) {
                task->unk60 = task->unk5C;
                task->setState(task, 3);
            }
            func_800875DC(task);
            break;
        case 3:
            break;
    }
}

Unk800876E4 *func_800878A4(s32 arg0, s32 arg1, s32 arg2) {
    Unk800876E4 *task = createTaskWithId(func_800876E4, sizeof(Unk800876E4), 0, arg2);
    task->key1 = arg0;
    task->key2 = arg1;
    return task;
}

void func_800878F0(s32 arg0) {
    func_800878A4(0, 0, arg0);
}

void func_80087918(Unk800876E4 *task, s32 command, s32 id) {
    if (task != NULL) {
        switch (command) {
        case 0x325:
            task->key2 = 0;
            break;
        case 0x327:
            task->key2 = 1;
            break;
        case 0x326:
            task->setState(task, 2);
            break;
        }
        if (command == 0x325 || command == 0x327) {
            task->actor = TASK_FUNCS.find(5, id, -1);
        }
    }
}

s32 func_800879E8(Unk80087FDC *task) {
    Actor *actor = task->actor;
    Point tile;
    u32 cell;
    s32 type;

    tile = actor->tile;
    cell = (u8)D_8009A70C.getCell(7, &tile);
    if (cell == 0) {
        return 0;
    }
    task->dir = cell >> 5;
    task->index = cell & 0x1F;
    task->entry = &task->entries[task->index];
    type = task->entry->type;
    switch (type) {
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        return 1;
    }
    return D_80096984[task->dir][actor->dir] != 0;
}

s32 func_80087ACC(Unk80087FDC *task, Unk80087FDCChildren *children) {
#if VERSION_EU
    s32 arg;
#endif

    if (task->entry->conditions[0][0] != 0xFFFF
        && FLAGS_00.checkCondition(task->entry->conditions[0][0], task->entry->conditions[0][1]) == 0) {
        return 0;
    }
    if (task->entry->conditions[1][0] != 0xFFFF
        && FLAGS_00.checkCondition(task->entry->conditions[1][0], task->entry->conditions[1][1]) == 0) {
        return 0;
    }
    switch (task->entry->type) {
        case 5:
            task->actor->unk78[0] = task->entry->unkA;
            GAME.unk26E0 = task->entry->unkA;
            return 0;
        case 6:
            D_8009A70C.unk54(task->entry->unkA);
            return 0;
        case 8:
            if (children->script == NULL) {
                children->script = func_80084B80(task->entry->unkA);
            }
            return 0;
        case 11:
            task->actor->unk150(task->actor, task->dir);
            return 0;
        case 12:
            task->actor->unk154(task->actor);
            return 0;
        case 13:
            task->actor->unk158(task->actor, &task->entry->unkA);
            return 0;
    }
#if VERSION_US
    if (children->anim != NULL) {
        children->anim->setState(children->anim, 1);
        return 1;
    }
    switch (task->entry->type) {
        default:
            children->anim = func_800878A4(0, 0, 6);
            break;
        case 2:
        case 3:
            children->anim = func_800878A4(0, 2, 6);
            break;
        case 4:
            children->anim = func_800878A4(0, 4, 6);
            break;
        case 7:
            children->anim = func_800878A4(0, 5, 6);
            break;
        case 1:
            if (task->dir == 4) {
                children->anim = func_800878A4(0, 10, 6);
            } else {
                children->anim = func_800878A4(0, (task->dir >> 1) + 6, 6);
            }
            break;
    }
#elif VERSION_EU
    /* the European version restarts a running animation on the new row */
    switch (task->entry->type) {
        default:
            arg = 0;
            break;
        case 2:
        case 3:
            arg = 2;
            break;
        case 4:
            arg = 4;
            break;
        case 7:
            arg = 5;
            break;
        case 1:
            if (task->dir == 4) {
                arg = 10;
            } else {
                arg = (task->dir >> 1) + 6;
            }
            break;
    }
    if (children->anim != NULL) {
        children->anim->setState(children->anim, 1);
        children->anim->key2 = arg;
        children->anim->frame = 0;
        children->anim->time = 0;
    } else {
        children->anim = func_800878A4(0, arg, 6);
    }
#endif
    return 1;
}

const Point D_80082624 = {0, 0};

void func_80087D28(Unk80087FDC *task) {
    MapObject *object;
    s32 id;

    switch (task->entry->type) {
        case 1:
            task->actor->unk110(task->actor, task->dir);
            func_8008AEB4(task->entry->unkA, -1, task->entry->unkC << 8, task->entry->unkE << 8, task->entry->unk10);
            if (task->entry->unk12 != 0) {
                object = (MapObject *)D_800990B4.unk10;
                id = task->entry->unk12;
                for (; object->unk2 != 0; object++) {
                    if (object->id == id) {
                        object->unk0 = 0;
                    }
                }
            }
            GAME.unk44 = task->entry->unk14;
            GAME.unk46 = task->entry->unk16;
            break;
        case 14:
            task->actor->unk158(task->actor, &task->entry->unkA);
            func_8008AE18(task->entry->unkA, -1, task->entry->unkC << 8, task->entry->unkE << 8, task->entry->unk10,
                          0x3C);
            break;
        case 2:
            task->actor->unk114(task->actor, task->dir, task->entry->unkC, task->entry->unkE,
                                (task->entry->unkA - 1) * 16);
            break;
        case 3:
            task->actor->unk118(task->actor, task->dir == 1 ? 5 : 3, task->entry->unkC, task->entry->unkE,
                                (task->entry->unkA - 1) * 16);
            break;
        case 4:
            task->actor->unk11C(task->actor, task->dir, D_80082624, task->entry->unkA * 16);
            break;
        case 7:
            task->actor->unk120(task->actor, task->dir, (Point){task->entry->unkA, task->entry->unkC});
            break;
        case 10:
            task->actor->unk124(task->actor, &task->entry->unkA, 0);
            break;
        case 9:
            task->actor->unk124(task->actor, &task->entry->unkA, 1);
            break;
    }
}

void func_80087FDC(Unk80087FDC *task, Unk80087FDCChildren *children) {
    task->entries = D_800990B4.unk14;
    switch (task->state) {
        default:
        case 0:
            task->actor = TASK_FUNCS.find(5, -1, 0);
            if (task->actor != NULL) {
                task->nextState(task);
            }
            break;
        case 1:
            if (D_800990B4.unk58 != 0 || D_800990B4.unk54 != 0) {
                break;
            }
            switch (task->substate) {
                default:
                case 0:
                    if (func_800879E8(task) != 0 && func_80087ACC(task, children) != 0) {
                        task->nextSubstate(task);
                    }
                    break;
                case 1:
                    if (func_800879E8(task) == 0) {
                        task->setSubstate(task, 0);
                        children->anim->setState(children->anim, 2);
                    } else if ((PAD.getPressed(0) & 0x2000) && D_800990B4.unk54 == 0) {
                        children->anim->setState(children->anim, 3);
                        func_80087D28(task);
                        task->nextSubstate(task);
                    }
                    break;
                case 2:
                    if (task->actor->substate < 5) {
                        task->setSubstate(task, 0);
                    }
                    break;
            }
            break;
        case 2:
        case 3:
            break;
    }
}

void func_800881A0(s32 arg0) {
    Unk80087FDC *task = createTask(func_80087FDC, sizeof(Unk80087FDC), 8);

    task->unk50 = arg0;
}

void func_800881D8(Unk800882D8 *task, Point *out) {
    Point pos;

    pos.x = task->actor->tile.x;
    pos.y = task->actor->tile.y;
    if (task->actor->key1 == 0xD6) {
        pos.y -= 0x15;
    }
    D_8009A434[0](&pos);
    if (task->unk58 == 2 || task->unk58 == 3) {
        pos.x -= 0xB;
    } else {
        pos.x += 0xB;
    }
    if (task->unk58 == 0 || task->unk58 == 2) {
        pos.y -= 0x13;
    } else {
        pos.y -= 7;
    }
    *out = pos;
}

void func_800882D8(Unk800882D8 *task, void **box) {
    Point pos;
    Point newPos;
    TalkBox *talkBox;

    switch (task->state) {
    case 0:
    default:
        if (task->unk5C != 0) {
            *box = createMessageBox(0x1004, task->text, task->unk54);
        } else {
            func_800881D8(task, &pos);
            *box = createTalkBox(0x1004, pos.x, pos.y, task->text, task->unk54, task->unk58);
        }
        task->nextState(task);
        break;
    case 1:
        if (*box == NULL) {
            task->setState(task, 3);
        } else if (task->unk5C == 0) {
            func_800881D8(task, &newPos);
            talkBox = *box;
            talkBox->setPos(talkBox, newPos.x, newPos.y);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Unk800882D8 *func_800883F4(Actor *actor, s32 arg1, s32 arg2, s32 arg3) {
    Unk800882D8 *task = createTask(func_800882D8, sizeof(Unk800882D8), 4);

    task->actor = actor;
    task->unk54 = arg1;
    task->unk58 = arg2;
    task->unk5C = arg3;
    task->text = FILE_CACHE_GET_ENTRY[0](D_800990B4.unk48);
    return task;
}

Unk800882D8 *func_8008848C(Actor *actor, s32 arg1) {
    Unk800882D8 *task = createTask(func_800882D8, sizeof(Unk800882D8), 4);
    Point pos;

    task->actor = actor;
    task->unk54 = arg1;
    task->text = (s32)FILE_CACHE_LOAD[0](D_800990B4.unk44);
    pos = actor->tile;
    D_8009A434[0](&pos);
    switch (actor->dir) {
        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
        default:
            if (pos.x >= 0xA0) {
                task->unk58 = 0;
            } else {
                task->unk58 = 2;
            }
            break;
        case 3:
        case 4:
        case 5:
            if (pos.x >= 0xA0) {
                task->unk58 = 1;
            } else {
                task->unk58 = 3;
            }
            break;
    }
    switch (task->unk58) {
        case 0:
            if (pos.y < 0x79) {
                task->unk58 = 1;
            }
            break;
        case 2:
            if (pos.y < 0x79) {
                task->unk58 = 3;
            }
            break;
        case 1:
            if (pos.y >= 0xAC) {
                task->unk58 = 0;
            }
            break;
        case 3:
            if (pos.y >= 0xAC) {
                task->unk58 = 2;
            }
            break;
    }
    task->unk5C = 0;
    return task;
}

void func_80088640(Unk8008878C *task, Layer *layer, s32 index) {
    MapObject *object = &task->unk54[index];
    SpriteDrawer sprite;

    if (task->state == 1) {
        initSpriteDrawer(&sprite);
        sprite.setAltClut(0, 0x1F0);
        sprite.setLayer(layer, object->depth);
        if (object->id != 0xFF) {
            sprite.setTexture(0x140, 0x100);
            sprite.setClutRow(object->clutRow);
            if (D_800990B4.unk38.cd != 0) {
                sprite.setColor(&D_800990B4.unk38);
            }
            sprite.draw(FILE_CACHE_GET_ENTRY[0](task->unk50), object->frame, object->x, object->y);
        } else {
            sprite.setTexture(0x200, 0x100);
            sprite.setClutRow(object->clutRow);
            sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), object->frame, object->x, object->y);
        }
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008878C);

void func_80088BE4(s32 arg0, MapObject *arg1) {
    Unk8008878C *task = createTask(func_8008878C, sizeof(Unk8008878C), 4);

    task->unk54 = arg1;
    task->unk50 = arg0;
}

void *func_80088C2C(void) {
    u8 *entry = D_8009A940;
    s32 found = 0;

    for (; entry[2] != 0; entry += 0x12) {
        if (entry[1] == D_8009A944) {
            found = 1;
            break;
        }
    }
    D_8009A940 = entry + 0x12;
    if (found) {
        return entry;
    }
    return NULL;
}

void func_80088C9C(s32 arg0) {
    D_8009A944 = arg0;
    D_8009A940 = D_800990B4.unk10;
    func_80088C2C();
}

void func_80088CD0(void) {
    s32 mode = GAME_FUNCS.getMode();
    s32 found = 0;
    s32 i;

    for (i = 0; D_800969C4[i] != 0; i++) {
        if (D_800969C4[i] == (s16)mode) {
            found = 1;
            break;
        }
    }
    if (found) {
        FILE_CACHE_REQUEST(TEXT_FILE(0x5D));
    }
}

void func_80088D5C(void) {
    Unk80087FDCEntry *entry = D_800990B4.unk14;
    s32 loadFile3 = 0;
    s32 loadFile0 = 0;
    s32 loadFile1 = 0;

    for (; entry->type != 0; entry++) {
        switch (entry->type) {
        case 2:
        case 3:
            loadFile3 = 1;
            break;
        case 4:
            loadFile0 = 1;
            break;
        case 7:
            loadFile1 = 1;
            break;
        }
    }
    if (loadFile3) {
        FILE_CACHE_REQUEST(FIELD_EXIT_FILES + 3);
    }
    if (loadFile0) {
        FILE_CACHE_REQUEST(FIELD_EXIT_FILES);
    }
    if (loadFile1) {
        FILE_CACHE_REQUEST(FIELD_EXIT_FILES + 1);
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80088E4C);

void func_8008926C(Task *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->substate = task->key2;
    case 1:
        if (func_80088E4C(task) != 0) {
            task->setState(task, 3);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void func_800892E8(s32 arg0) {
    Task *task = createTask(func_8008926C, 0x54, 0);

    task->key2 = arg0;
}

void func_80089320(Unk80089320 *task) {
    SpriteDrawer sprite;
    Point pos;
    u8 (*anim)[2];
    Actor *actor;
    s32 step;
    s32 time;

    switch (task->state) {
    default:
    case 0:
        task->nextState(task);
    case 1:
        if (task->step == 0) {
            task->anim = D_80096A7C[task->substate];
            task->animStep = 0;
            task->animTime = 0;
            switch (task->substate) {
            case 1:
            case 3:
                SOUND.playSound(0x40009);
                break;
            }
            task->nextStep(task);
        }
        if (task->actor != NULL && task->actor->state == 1) {
            step = task->animStep;
            time = task->animTime;
            time += GFX_FUNCS.getFrameTime();
            anim = task->anim;
            if (anim[step][1] < time) {
                time -= anim[step][1];
                step++;
                if (anim[step][0] == 0xFF) {
                    step = anim[step][1];
                }
                task->frame = anim[step][0];
                task->animStep = step;
            }
            task->animTime = time;
            actor = task->actor;
            switch (actor->substate) {
            case 0x45:
                if (actor->unk8C != 0) {
                    pos.x = actor->tile.x + D_80096A8C[D_80096ACC][0];
                } else {
                    pos.x = actor->tile.x - D_80096A8C[D_80096ACC][0];
                }
                pos.y = actor->tile.y + D_80096A8C[D_80096ACC][1];
                if (D_80096A8C[D_80096ACC + 1][0] != 0) {
                    D_80096ACC++;
                }
                break;
            case 0x44:
                if (D_80096ACC == 0) {
                    D_80096ACC = 0xE;
                }
                if (actor->unk8C != 0) {
                    pos.x = actor->tile.x + D_80096A8C[D_80096ACC][0];
                } else {
                    pos.x = actor->tile.x - D_80096A8C[D_80096ACC][0];
                }
                pos.y = actor->tile.y + D_80096A8C[D_80096ACC][1];
                if (D_80096ACC != 1) {
                    D_80096ACC--;
                }
                break;
            default:
                pos.x = actor->tile.x;
                D_80096ACC = 0;
                pos.y = actor->tile.y;
                break;
            }
            initSpriteDrawer(&sprite);
            sprite.setTexture(0x200, 0x100);
            sprite.setLayerId(0x1002, 2);
            sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), task->frame, pos.x, pos.y);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Unk80089320 *func_80089668(Actor *actor) {
    Unk80089320 *task;

    if (GAME_FUNCS.getMode() < 0x2D7) {
        task = createTaskWithId(func_80089320, sizeof(Unk80089320), 0, 0x16);
        task->actor = actor;
        return task;
    }
    return NULL;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_800896C0);

void func_80089D28(FieldTask *task, FieldChildren *children) {
    Vec2 clip;
    Layer *layer;
    Actor *actor;
    Actor *player;
    s32 width;
    s32 height;

    switch (task->substate) {
    default:
    case 0:
        FILE_CACHE.markCached();
        player = TASK_FUNCS.find(5, -1, 0);
        if (player != NULL && player->tile.x != 0) {
            task->unk6C = 1;
        } else {
            task->unk6C = 0;
        }
        task->width = 0x140;
        task->fade = 0;
        task->height = 0xF0;
        task->nextSubstate(task);
    case 1:
        layer = GFX_FUNCS.getLayer(0x1002);
        layer->setBgColor(layer, 1, 1, 1);
        task->width -= 10;
        task->height -= 7;
        if (task->width <= 0) {
            layer->setBgColor(layer, 0, 0, 0);
            task->width = 0;
            task->height = 0;
            task->nextSubstate(task);
        }
        actor = TASK_FUNCS.find(5, -1, 0);
        layer->getScroll(layer, &clip);
        if (task->unk6C != 0) {
            clip.x = actor->tile.x - clip.x;
            clip.y = actor->tile.y - clip.y;
        } else {
            clip.x = 0xA0;
            clip.y = 0x78;
        }
        clip.x -= task->width / 2;
        if (clip.x < 0) {
            clip.x = 0;
        }
        clip.y -= task->height / 2;
        if (clip.y < 0) {
            clip.y = 0;
        }
        layer->setClipPos(layer, clip.x, clip.y);
        width = task->width;
        height = task->height;
        if (clip.x + width > 0x140) {
            width = 0x140 - clip.x;
        }
        if (clip.y + height > 0xF0) {
            height = 0xF0 - clip.y;
        }
        layer->setClipSize(layer, width, height);
        func_80086460(0x1001, task->fade);
        if (task->fade != 0x8000) {
            task->fade += 0x400;
        }
        break;
    case 2:
        layer = GFX_FUNCS.getLayer(0x1001);
        switch (task->step) {
        default:
        case 0:
            task->width = 0;
            task->height = 0;
            task->step++;
        case 1:
            break;
        }
        task->width += 8;
        layer->setClipPos(layer, task->width, task->height);
        layer->setClipSize(layer, (0xA0 - task->width) * 2, (0x78 - task->height) * 2);
        if (task->width > 0xA0) {
            GAME.funcs.requestMode(task->unk5C, task->unk60);
            GAME.fieldMode = GAME.funcs.getMode();
            GAME.fieldPos = children->player->pos;
            GAME.fieldDir = children->player->dir;
            task->nextSubstate(task);
        }
        func_80086460(0x1001, 0x8000);
        break;
    case 3:
        break;
    }
}

s32 func_8008A0F4(void) {
    if (GAME.funcs.getMode() == 0x22D) {
        return 1;
    }
    return GAME.funcs.getMode() == 0x2DE;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008A154);

Task *func_8008ADE8(void) {
    return createTaskWithId(func_8008A154, 0x80, 0x7C, 7);
}

void func_8008AE18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    FieldTask *task = TASK_FUNCS.find(7, -1, -1);

    if (task != NULL) {
        task->unk5C = arg0;
        task->unk60 = arg1;
        task->unk68 = arg5;
        task->setState(task, 2);
        D_800990B4.unk64 = arg2;
        D_800990B4.unk68 = arg3;
        D_800990B4.unk6C = arg4;
    }
}

void func_8008AEB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8008AE18(arg0, arg1, arg2, arg3, arg4, 0);
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008AEDC);

s32 func_8008B258(void) {
    Battle *battle = D_800990B4.unk20->battles[3]->battles[5];

    D_80042728.unkC = battle->unk4;
    D_80042728.unk14 = battle->unk8;
    func_8008AEDC(battle->unk0);
    FLAGS_00.applyAction(0xF, 1);
    return 0;
}

void func_8008B2C4(s32 index) {
    FieldChildren *children = ((Task *)TASK_FUNCS.find(7, -1, -1))->children;

    children->unkC = func_80084B80(D_80096C38[index]);
}

void func_8008B320(void) {
    FieldTask *task = TASK_FUNCS.find(7, -1, -1);
    FieldChildren *children = task->children;

    D_800990B4.unk50 = 1;
    D_800990B4.unk58 = 1;
    children->unk10 = createInn(0x1002);
    task->setSubstate(task, 2);
}

void func_8008B398(s32 arg0, Point *pos, s32 arg2) {
    FieldTask *task = TASK_FUNCS.find(7, -1, -1);

    task->unk70 = arg0;
    task->unk74.x = pos->x;
    task->unk74.y = pos->y;
    task->unk7C = arg2;
    task->setSubstate(task, 3);
}

s32 func_8008B410(s32 angle, s32 radius) {
    return rsin(angle >> 2) * radius / 4096;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008B450);

Unk8008B450 *func_8008B930(Actor *actor, s32 arg1) {
    Unk8008B450 *task = createTask(func_8008B450, sizeof(Unk8008B450), 0);

    task->actor = actor;
    task->unk54 = arg1;
    if (GAME.funcs.getMode() == 0x26C) {
#if VERSION_US
        func_800A4EE8();
#elif VERSION_EU
        func_800A6024();
#endif
    }
    if (GAME.funcs.getMode() == 0x2D4) {
#if VERSION_US
        func_800A4EE8();
#elif VERSION_EU
        func_800A6024();
#endif
    }
    return task;
}

void func_8008B9D8(Unk8008B9D8 *task) {
    SpriteDrawer sprite;
    s32 dx;
    s32 dy;
    s32 sprites;

    switch (task->state) {
        default:
        case 0:
            dx = task->from.x - task->to.x;
            if (dx < 0) {
                dx = -dx;
            }
            dy = task->from.y - task->to.y;
            if (dy < 0) {
                dy = -dy;
            }
            if (dx < 0x80 && dy < 0x80) {
                task->speed = 3;
                task->frame = 0x52;
            } else if (dx < 0x100 && dy < 0x100) {
                task->speed = 6;
                task->frame = 0x51;
            } else {
                task->speed = 0xC;
                task->frame = 0x50;
            }
            task->nextState(task);
            /* fallthrough */
        case 1:
            sprites = FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16 | 1);
            initSpriteDrawer(&sprite);
            sprite.setLayerId(0x1002, 0);
            sprite.setTexture(0x240, 0x100);
            sprite.setFollowScroll(0);
            sprite.setClutRow(task->time / task->speed % 10);
            sprite.draw(sprites, task->frame, 0xF8, 0xA8);
            sprite.draw(sprites, 0x4F, 0xF8, 0xA8);
            task->time += GFX_FUNCS.getFrameTime();
            if (task->time >= 0x78) {
                task->setState(task, 3);
            }
            break;
        case 2:
        case 3:
            break;
    }
}

Unk8008B9D8 *func_8008BBD4(Point from, Point to) {
    Unk8008B9D8 *task = createTask(func_8008B9D8, sizeof(Unk8008B9D8), 0);

    task->from = from;
    task->to = to;
    return task;
}

void func_8008BC30(Unk8008BFE8 *task) {
    s32 index = RANDOM.next() % task->count;

    GAME.unk26E4 = index;
    task->entries[index].unk10 = 1;
    task->pos = task->entries[index].pos;
}

void func_8008BCAC(Unk8008BFE8 *task, Unk8008BFE8Children *children) {
    MapObject *objects;
    s32 step;
    s32 time;
    s32 i;

    switch (task->state) {
    default:
    case 0:
        FILE_CACHE_REQUEST(FIELD_EXIT_FILES + 2);
        task->nextState(task);
        break;
    case 1:
        break;
    case 2:
        if (task->substate == 0) {
            children->unk0 = func_8008C564(task->unk5C);
            task->nextSubstate(task);
        } else if (task->substate != 0x80) {
            if (task->substate < 0x14) {
                task->substate = task->substate + GFX_FUNCS.getFrameTime() + 1;
            } else {
                if (task->unk5C == 0) {
                    if (task->entries[task->unk58].unk10 != 0) {
                        if ((RANDOM.next() & 0x7F) < 0x66) {
                            D_8009A6EC[0](3);
                        } else {
                            D_8009A6EC[0](6);
                        }
                        func_8008BC30(task);
                    } else {
                        if (children->unk4 != NULL) {
                            children->unk4->destroy(children->unk4);
                        }
                        children->unk4 = func_8008BBD4(task->pos, task->entries[task->unk58].pos);
                    }
                }
                task->setSubstate(task, 0x80);
            }
        }
        step = task->step;
        time = task->counter;
        time += GFX_FUNCS.getFrameTime();
        if (D_80096D14[step][1] < time) {
            time -= D_80096D14[step][1];
            step++;
            if (D_80096D14[step][0] == 0xFF) {
                task->setState(task, 1);
                return;
            }
            task->entries[task->unk58].unk0 = D_80096D14[step][0];
            task->step = step;
        }
        task->counter = time;
        objects = (MapObject *)D_800990B4.unk10;
        for (i = 0; i < task->count; i++) {
            if (task->entries[i].unk0 != 0) {
                if (task->unk58 == i) {
                    objects[task->entries[i].unk4].frame = task->entries[i].unk0;
                } else {
                    objects[task->entries[i].unk4].frame = 0x38;
                }
            }
        }
        break;
    case 3:
        if (task->entries != NULL) {
            HEAP.free(task->entries);
        }
        break;
    }
}

Unk8008BFE8 *func_8008BFE8(s32 count) {
    Unk8008BFE8 *task = createTaskWithId(func_8008BCAC, sizeof(Unk8008BFE8), 8, 0xB);
    MapObject *object;
    s32 i;
    s32 n;
    s32 index;

    task->count = count;
    object = (MapObject *)D_800990B4.unk10;
    task->entries = HEAP.alloc(count * sizeof(Unk8008BFE8Entry), 2);
    i = 0;
    n = 0;
    for (; object->y != 0; object++, i++) {
        if (object->id == 0xFF) {
            task->entries[n].pos.x = object->x;
            task->entries[n].pos.y = object->y;
            task->entries[n].unk4 = i;
            task->entries[n].unk0 = 0x38;
            task->entries[n].unk10 = 0;
            n++;
        }
    }
    if (n != 0) {
        if (GAME.clearTempFlags != 0) {
            func_8008BC30(task);
        } else {
            index = GAME.unk26E4;
            task->entries[index].unk10 = 1;
            task->pos = task->entries[index].pos;
        }
    }
    return task;
}

Unk8008BFE8 *func_8008C160(Point *pos, s32 select) {
    Unk8008BFE8 *task = TASK_FUNCS.find(0xB, -1, -1);
    s32 i;

    if (task != NULL) {
        for (i = 0; i < task->count; i++) {
            if (pos->x >= task->entries[i].pos.x - 10 && task->entries[i].pos.x + 10 >= pos->x
                && pos->y >= task->entries[i].pos.y - 10 && task->entries[i].pos.y + 10 >= pos->y) {
                if (select) {
                    task->unk58 = i;
                    task->unk5C = 0;
                }
                return task;
            }
        }
    }
    return NULL;
}

void func_8008C23C(void) {
    Unk8008BFE8 *task = TASK_FUNCS.find(0xB, -1, -1);
    s32 i;

    if (task != NULL) {
        for (i = 0; i < task->count; i++) {
            if (task->entries[i].pos.x >= 1000) {
                task->unk58 = i;
                task->unk5C = 1;
                task->setState(task, 2);
            }
        }
    }
}

void func_8008C2F4(Unk8008C388 *task, Layer *layer) {
    SpriteDrawer sprite;

    if (task->state == 1) {
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x200, 0x100);
        sprite.setLayer(layer, 4);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), task->frame, task->x, task->y);
    }
}

void func_8008C388(Unk8008C388 *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    Actor *actor;
    s32 step;
    s32 time;
    u8 *anim;

    switch (task->state) {
        default:
        case 0:
            if (task->key1 != 0) {
                actor = TASK_FUNCS.find(5, 0x11B, -1);
            } else {
                actor = TASK_FUNCS.find(5, -1, 0);
            }
            if (actor == NULL) {
                break;
            }
            task->x = actor->tile.x;
            task->y = actor->tile.y;
            task->dir = actor->dir;
            task->anim = D_80096DAC[task->dir];
            task->nextState(task);
            SOUND.playSound(0x80045C44);
            /* fallthrough */
        case 1:
            step = task->step;
            time = task->counter;
            time += GFX_FUNCS.getFrameTime();
            anim = task->anim;
            if (anim[step * 2 + 1] < time) {
                time -= anim[step * 2 + 1];
                step++;
                if (anim[step * 2] == 0xFF) {
                    task->setState(task, 3);
                    break;
                }
                task->frame = anim[step * 2];
                task->step = step;
            }
            task->counter = time;
            if (task->frame != 0) {
                layer->addSortedCallback(layer, func_8008C2F4, task, task->y + D_80096DCC[task->dir], 0);
            }
            break;
        case 2:
        case 3:
            break;
    }
}

Unk8008C388 *func_8008C564(s32 arg0) {
    Unk8008C388 *task = createTask(func_8008C388, sizeof(Unk8008C388), 0);

    task->key1 = arg0;
    return task;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008C59C);

Unk8008C59C *func_8008C9F8(Point pos) {
    Unk8008C59C *task = createTask(func_8008C59C, sizeof(Unk8008C59C), 0);

    task->pos = pos;
    return task;
}

void func_8008CA3C(Unk8008CC4C *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    Unk80086144 *map;
    Point *size;
    s32 x;
    s32 y;
    s32 shake;

    x = task->unk54.x - 0xA0;
    y = task->unk54.y - 0x8C;
    if (task->hasBounds == 0) {
        map = TASK_FUNCS.find(4, -1, -1);
        if (map != NULL) {
            if (map->state == 1) {
                size = map->unk130(map);
                task->bounds = *size;
                task->hasBounds = 1;
            }
        } else if (GAME_FUNCS.getMode() != 0x2DE) {
            task->bounds.x = 0x7FFF;
            task->bounds.y = 0x7FFF;
        } else {
            task->bounds.x = 0x500;
            task->bounds.y = 0x400;
        }
    }
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (task->bounds.x - 0x140 < x) {
        x = task->bounds.x - 0x140;
    }
    if (task->bounds.y - 0xF0 < y) {
        y = task->bounds.y - 0xF0;
    }
    shake = 0;
    if (task->shaking != 0) {
        task->shake = (task->shake + 1) & 3;
        shake = task->shake + 1;
        if (task->voice == -1) {
            task->voice = SOUND_STATE.playSound(0xA00431BF);
        }
    } else if (task->voice != -1) {
        SOUND_STATE.keyOff(0xA00431BF, task->voice);
        task->voice = -1;
    }
    layer->setScroll(layer, (D_80096E6C[shake].x + x) << 8, (D_80096E6C[shake].y + y) << 8);
}

void func_8008CC4C(Unk8008CC4C *task) {
    Point delta;
    Point sign;

    switch (task->state) {
        default:
        case 0:
            task->unk50 = TASK_FUNCS.find(5, -1, 0);
            task->unk80 = 1;
            if (task->unk50 != NULL) {
                task->nextState(task);
            }
            break;
        case 1:
            switch (task->substate) {
                case 0:
                    task->unk54.x = task->unk50->tile.x;
                    task->unk54.y = task->unk50->tile.y - (task->unk50->unk64 >> 8);
                    if ((task->step == 0) & (task->unk80 == 0)) {
                        task->nextStep(task);
                    }
                    break;
                case 1:
                    task->unk54.x = task->unk88;
                    task->unk54.y = task->unk8C;
                    if ((task->step == 0) & (task->unk80 == 0)) {
                        task->nextStep(task);
                    }
                    break;
            }
            if (task->step == 1) {
                sign.x = 1;
                sign.y = 1;
                delta.x = task->unk54.x - task->unk68.x;
                if (delta.x < 0) {
                    sign.x = -1;
                    delta.x = -delta.x;
                }
                delta.y = task->unk54.y - task->unk68.y;
                if (delta.y < 0) {
                    sign.y = -1;
                    delta.y = -delta.y;
                }
                if (delta.x != 0 && delta.y != 0) {
                    if (delta.x > 4) {
                        delta.x /= 4;
                    } else if (delta.x > 2) {
                        delta.x /= 2;
                    } else {
                        delta.x = 1;
                    }
                    task->unk54.x = task->unk68.x += delta.x * sign.x;
                    if (delta.y > 4) {
                        delta.y /= 4;
                    } else if (delta.y > 2) {
                        delta.y /= 2;
                    } else {
                        delta.y = 1;
                    }
                    task->unk54.y = task->unk68.y += delta.y * sign.y;
                } else {
                    task->nextStep(task);
                }
            }
            func_8008CA3C(task);
            break;
        case 2:
            break;
        case 3:
            if (task->voice != -1) {
                SOUND_STATE.keyOff(0xA00431BF, task->voice);
                task->voice = -1;
            }
            break;
    }
}

void func_8008CF0C(void) {
    Unk8008CC4C *task = createTaskWithId(func_8008CC4C, sizeof(Unk8008CC4C), 0, 0x10);

    task->voice = -1;
}

void func_8008CF44(s32 arg0, s32 arg1) {
    Unk8008CC4C *task = TASK_REGISTRY.funcs.find(0x10, -1, -1);

    if (task != NULL) {
        task->unk7C = 0;
        task->unk80 = arg0;
        task->unk84 = arg1;
        task->unk50 = TASK_REGISTRY.funcs.find(5, arg1, -1);
        task->unk68 = task->unk54;
        task->setSubstate(task, 0);
    }
}

void func_8008CFF4(s32 arg0, s32 arg1, s32 arg2) {
    Unk8008CC4C *task = TASK_FUNCS.find(0x10, -1, -1);

    if (task != NULL) {
        task->unk7C = 0;
        task->unk80 = arg0;
        task->unk88 = arg1;
        task->unk8C = arg2;
        task->unk68 = task->unk54;
        task->setSubstate(task, 1);
    }
}

void func_8008D07C(s32 arg0) {
    Unk8008CC4C *task = TASK_FUNCS.find(0x10, -1, -1);

    if (task != NULL) {
        task->shaking = arg0;
    }
}

s32 func_8008D0C0(Actor *actor, s32 x, s32 y, Point offset) {
    s32 blocked = 0;
    Point pos;
    u8 cell;

    pos.x = (actor->pos.x >> 8) + x;
    pos.y = (actor->pos.y >> 8) + y;
    cell = D_8009A70C.unk58(&pos);
    if (cell != 0) {
        cell = D_8009A70C.getCell(GAME.unk26D8, &pos);
    }
    if (actor->unk64 != 0 && cell != 1) {
        switch (cell) {
        case 2:
            if (actor->unk64 < 0x2000) {
                cell = 0;
            }
            break;
        case 3:
            if (actor->unk64 < 0x3000) {
                cell = 0;
            }
            break;
        case 4:
            if (actor->unk64 < 0x4000) {
                cell = 0;
            }
            break;
        case 5:
            if (actor->unk64 < 0x5000) {
                cell = 0;
            }
            break;
        case 6:
            if (actor->unk64 < 0x6000) {
                cell = 0;
            }
            break;
        }
        switch (cell) {
        case 18:
            if (actor->unk64 > 0x6000) {
                cell = 0;
            }
            break;
        case 19:
            if (actor->unk64 > 0x5000) {
                cell = 0;
            }
            break;
        case 20:
            if (actor->unk64 > 0x4000) {
                cell = 0;
            }
            break;
        case 21:
            if (actor->unk64 > 0x3000) {
                cell = 0;
            }
            break;
        case 22:
            if (actor->unk64 > 0x2000) {
                cell = 0;
            }
            break;
        }
        if (cell == 0) {
            blocked = 1;
        }
    }
    if (cell == 0) {
        actor->pos.x -= offset.x;
        actor->pos.y -= offset.y;
    }
    return blocked;
}

s32 func_8008D2A0(Actor *actor) {
    s32 blocked = 0;
    s32 i;
    u8 probe;
    u8 *sign;
    Point offset;

    for (i = 0; i < 5; i++) {
        probe = D_80096E94[actor->dir][i];
        sign = D_80096F3C[probe];
        offset.x = (sign[0] & 1) * actor->unk68 / 2;
        if (sign[0] & 0x80) {
            offset.x = -offset.x;
        }
        offset.y = (sign[1] & 1) * actor->unk68 / 4;
        if (sign[1] & 0x80) {
            offset.y = -offset.y;
        }
        if (func_8008D0C0(actor, D_80096EBC[probe].x, D_80096EBC[probe].y, offset)) {
            blocked = 1;
        }
    }
    return blocked;
}

void func_8008D3F0(Actor *actor, s32 pad) {
    if (pad != 0 && D_800990B4.unk50 == 0) {
        actor->dir = D_80096F5C[pad];
        if (actor->unkBC != 0) {
            if (actor->substate != 2) {
                actor->setSubstate(actor, 2);
            }
        } else if (actor->substate != 3) {
            actor->setSubstate(actor, 3);
        }
    } else {
        if (actor->substate == 2) {
            actor->setSubstate(actor, 1);
        }
        if (actor->substate == 3) {
            actor->setSubstate(actor, 4);
        }
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008D4C4);

s32 func_8008D580(Actor *actor, Point *pos) {
    Actor *target;
    s32 i;
    s32 result;

    target = func_8008D4C4(pos);
    result = 0;
    if (target != NULL && target->state == 1) {
        if (target->key1 != 0x180) {
            if (target->key1 != 0x181) {
                if (target->key1 != 0x182) {
                    for (i = 0; D_80096F9C[i][0] != 0; i++) {
                        if (target->key1 == D_80096F9C[i][0]) {
                            target = TASK_FUNCS.find(5, D_80096F9C[i][1], -1);
                            break;
                        }
                    }
                    switch (target->key1) {
                        case 0x148:
                        case 0x15F:
                        case 0x160:
                            if (target->substate != 0x4E) {
                                target->setSubstate(target, 0x4E);
                                result = 1;
                                target->unk88 = (s32)actor;
                                actor->setSubstate(actor, 0x4D);
                                actor->unk108 = NULL;
                            }
                            break;
                        default:
                            target->setSubstate(target, 0x4A);
                            target->unk88 = (s32)actor;
                            actor->setSubstate(actor, actor->unk84 != 0 ? 0x4C : 1);
                            actor->unk108 = NULL;
                            result = D_800990B4.unk60 = 1;
                            break;
                    }
                }
            }
        }
    }
    return result;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008D710);

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008DB60);

void func_8008DCF8(Actor *actor) {
    s32 held = PAD.getHeld(0);

    if (held & (1 << PAD_UP)) {
        if (actor->substate != 0x41) {
            actor->setSubstate(actor, 0x41);
        }
    } else if (held & (1 << PAD_DOWN)) {
        if (actor->substate != 0x42) {
            actor->setSubstate(actor, 0x42);
        }
    } else if (actor->substate != 0x40) {
        actor->setSubstate(actor, 0x40);
    }
}

void func_8008DD9C(Actor *actor) {
    Trail *trail;
    Actor *leader;

    if (actor->trail->leader == NULL) {
        actor->trail->leader = TASK_FUNCS.find(5, -1, 0);
    }
    leader = actor->trail->leader;
    if (leader != NULL) {
        trail = actor->trail;
        switch (leader->substate) {
            case 2:
            case 3:
            case 5:
            case 0x4F:
            case 0x50:
                trail->steps[trail->head].x = leader->pos.x;
                trail->steps[trail->head].y = leader->pos.y;
                trail->steps[trail->head].dir = leader->dir;
                trail->head = (trail->head + 1) & 0x3F;
                actor->pos.x = trail->steps[trail->tail].x;
                actor->pos.y = trail->steps[trail->tail].y;
                actor->dir = trail->steps[trail->tail].dir;
                trail->tail = (trail->tail + 1) & 0x3F;
                break;
        }
        switch (leader->substate) {
            case 2:
            case 3:
            case 5:
                if (actor->substate != 3) {
                    actor->setSubstate(actor, 3);
                }
                break;
            case 0x4F:
                if (actor->substate != 1) {
                    actor->setSubstate(actor, 1);
                }
                break;
            default:
                if (actor->substate == 3) {
                    actor->setSubstate(actor, 4);
                }
                break;
        }
        actor->unk78[0] = leader->unk78[0];
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008DFE0);

void func_8008E1A4(Actor *actor) {
    s32 x;
    s32 y;
    s32 tx;
    s32 ty;
    s32 pad;

    if (actor->unkEC != 0) {
        x = actor->pos.x >> 8;
        y = actor->pos.y >> 8;
        tx = actor->unkF0;
        ty = actor->unkF4;
        if (x >> 1 != tx >> 1 || y >> 1 != ty >> 1) {
            pad = 0;
            if (x < tx) {
                pad = 1 << PAD_RIGHT;
            } else if (x > tx) {
                pad = 1 << PAD_LEFT;
            }
            if (y < ty) {
                pad |= 1 << PAD_DOWN;
            } else if (y > ty) {
                pad |= 1 << PAD_UP;
            }
            actor->unkBC = 1;
            func_8008D3F0(actor, pad >> 4);
        } else {
            actor->pos.x = actor->unkF0 << 8;
            actor->unkEC = 0;
            actor->pos.y = actor->unkF4 << 8;
            actor->dir = actor->unkF8;
            actor->setSubstate(actor, 1);
        }
    }
}

void func_8008E284(Actor *actor, s32 arg1, s32 arg2, s32 arg3) {
    actor->unkEC = 1;
    actor->unkF0 = arg1;
    actor->unkF4 = arg2;
    actor->unkF8 = arg3;
}

s32 func_8008E29C(Actor *actor) {
    return actor->unkEC;
}

void func_8008E2A8(Actor *actor) {
    actor->unk108 = func_8008E1A4;
}

void func_8008E2B8(Actor *actor) {
    switch (actor->key2) {
    case 0:
        actor->unk108 = func_8008DB60;
        actor->unkBC = 0;
        break;
    case 1:
        actor->unk108 = NULL;
        break;
    case 2:
    case 4:
    case 8:
        actor->unk108 = func_8008DD9C;
        break;
    }
}

void func_8008E318(Actor *actor, s32 dir) {
    actor->unk108 = NULL;
    actor->setSubstate(actor, 5);
    actor->dir = dir;
}

void func_8008E358(Actor *actor, s32 dir) {
    if (actor->substate != 0x4F) {
        actor->unk108 = NULL;
        actor->setSubstate(actor, 0x4F);
        actor->dir = dir;
    }
}

void func_8008E3A4(Actor *actor) {
    if (actor->substate == 0x4F) {
        actor->setSubstate(actor, 0x50);
    }
}

void func_8008E3DC(Actor *actor, s32 dir, s32 x, s32 y, s32 arg4) {
    actor->unk108 = NULL;
    actor->setSubstate(actor, 0x43);
    actor->dir = dir;
    actor->pos.x = x << 8;
    actor->pos.y = y << 8;
    actor->unk90 = 0;
    actor->unk94 = arg4 << 8;
    if (dir != 5) {
        actor->unk8C = 1;
    } else {
        actor->unk8C = 0;
    }
    func_80090154();
    D_800990B4.unk60 = 1;
}

void func_8008E488(Actor *actor, s32 dir, s32 x, s32 y, s32 arg4) {
    actor->unk108 = NULL;
    actor->setSubstate(actor, 0x44);
    actor->dir = dir;
    actor->pos.x = x << 8;
    actor->pos.y = y << 8;
    actor->unk90 = actor->unk94 = arg4 << 8;
    if (dir != 5) {
        actor->unk8C = 1;
    } else {
        actor->unk8C = 0;
    }
    actor->unk74 = 0;
    func_80090154();
    D_800990B4.unk60 = 1;
}

void func_8008E534(Actor *actor, s32 dir, Point pos, s32 arg4) {
    s32 value;

    actor->unk108 = NULL;
    actor->setSubstate(actor, 0x47);
    actor->dir = dir;
    if (dir != 7) {
        actor->unk8C = 0;
    } else {
        actor->unk8C = 1;
    }
    value = arg4 << 8;
    actor->unk94 = value;
    actor->unk74 = 0;
    actor->unk90 = value;
    func_80090154();
    D_800990B4.unk60 = 1;
}

void func_8008E5B8(Actor *actor, s32 dir, Point offset) {
    void **children;
    Actor *other;
    Point pos;
    s32 i;

    D_800990B4.unk58 = 1;
    actor->unk108 = NULL;
    actor->setSubstate(actor, 0x48);
    actor->dir = dir;
    for (i = 0; i < 3; i++) {
        other = TASK_REGISTRY.funcs.find(5, -1, D_80096FDC[i]);
        if (other != NULL) {
            other->dir = dir;
        }
    }
    children = actor->children;
    pos.x = actor->tile.x + offset.x;
    pos.y = actor->tile.y + offset.y;
    children[2] = func_8008C9F8(pos);
}

void func_8008E698(Actor *actor, s32 arg1, s32 arg2) {
    actor->unk108 = NULL;
    actor->setSubstate(actor, 1);
    actor->dir = 0;
    D_800990B4.unk58 = 1;
    func_8008B398(arg2, &actor->tile, arg1);
}

void func_8008E700(Actor *actor, s32 arg1) {
    void **children;

    actor->unk108 = func_8008E1A4;
    actor->setSubstate(actor, 1);
    actor->dir = 0;
    D_800990B4.unk58 = 1;
    children = actor->children;
    children[2] = func_8008B930(actor, arg1);
}

void func_8008E768(Actor *actor, s32 arg1) {
    actor->unkA0 = arg1;
    actor->unkCC = 0;
    actor->unkD0 = 0;
    actor->unkE8 = 0;
}

void func_8008E77C(Actor *actor, s32 arg1, s32 dir) {
    actor->unkEC = 0;
    actor->setSubstate(actor, 0);
    actor->dir = dir;
    func_8008E768(actor, arg1);
}

s32 func_8008E7D4(Actor *actor) {
    return actor->unkE8;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008E7E0);

void func_8008EC6C(Actor *actor, s32 arg1) {
    actor->dir = arg1;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008EC74);

void func_8008F014(Actor *actor) {
    actor->unk108 = func_8008DB60;
    actor->unk90 = 0;
}

void func_8008F028(Task *task, s32 arg1, s32 arg2) {
    if (task->key2 == 0) {
        if (arg1 != 0) {
            if ((task->counter & 7) == 0) {
                if (task->key1 != 0x146) {
                    if (task->key1 != 0x147) {
                        SOUND.playSound(0x8004583C);
                    }
                } else if ((task->counter & 0x1F) == 0) {
                    SOUND.playSound(0x80045FCB);
                }
                if (arg2 != 0) {
                    D_8009A6E8();
                }
            }
        } else if ((task->counter & 0x1F) == 0) {
            SOUND.playSound(0x8004583C);
        }
        task->counter++;
    }
}

void func_8008F11C(Task *task) {
    if (task->key2 == 0) {
        if ((task->counter & 0xF) == 0) {
            SOUND.playSound(0x800458BD);
        }
        task->counter++;
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_8008F184);

void func_80090154(void) {
    s32 i;
    Actor *actor;

    for (i = 0; i < 3; i++) {
        actor = TASK_REGISTRY.funcs.find(5, -1, D_80096FE8[i]);
        if (actor != NULL) {
            actor->unk108 = func_8008DFE0;
        }
    }
}

void func_800901D4(void) {
    s32 i;
    Actor *actor;

    for (i = 0; i < 3; i++) {
        actor = TASK_REGISTRY.funcs.find(5, -1, D_80096FF4[i]);
        if (actor != NULL) {
            actor->unk108 = func_8008DD9C;
        }
    }
}

void func_80090254(Actor *actor, Point *out) {
    Point *delta = &D_80097000[actor->dir];

    out->x = actor->tile.x + delta->x;
    out->y = actor->tile.y + delta->y;
}

void func_80090294(Actor *actor, Unk80089320 **children) {
    Layer *layer;

    switch (actor->state) {
        default:
        case 0:
            if (actor->unk9C == 0 || FILE_CACHE.isLoading(actor->unk9C >> 16) == 0) {
                if (actor->key2 == 0) {
                    *children = func_80089668(actor);
                }
                actor->nextState(actor);
            }
            break;
        case 1:
            if ((actor->key2 & 0xE) || D_800990B4.unk54 == 0) {
                if (actor->unk108 != NULL) {
                    actor->unk108(actor);
                }
            }
            func_8008F184(actor, children);
            actor->tile.x = actor->pos.x >> 8;
            actor->tile.y = (actor->pos.y - actor->unk90) >> 8;
            if (actor->unk9C != 0) {
                func_8008EC74(actor);
                if (actor->tile.x + actor->tile.y != 0) {
                    layer = GFX_FUNCS.getLayer(0x1002);
                    layer->addSortedCallback(layer, func_8008E7E0, actor, actor->tile.y, 0);
                }
            }
            break;
        case 2:
            break;
        case 3:
            GAME.unk26EC = actor->unk64;
            if (actor->unkC8 != -1) {
                SOUND.keyOff(0xA0045F4A, actor->unkC8);
            }
            if (actor->trail != NULL) {
                HEAP.free(actor->trail);
            }
            break;
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80090450);

void func_80090864(void) {
    FLAGS_00.applyAction(0x707E, 1);
    FLAGS_00.applyAction(0x8B19, 1);
    FLAGS_00.applyAction(0x400, 1);
}

void func_800908C4(void) {
    FLAGS_00.applyAction(0x400, 1);
}

void func_800908F0(void) {
    FLAGS_00.applyAction(0x707E, 1);
    FLAGS_00.applyAction(0x8B1F, 1);
    FLAGS_00.applyAction(0x401, 1);
}

void func_80090950(void) {
    FLAGS_00.applyAction(0x401, 1);
}

void func_8009097C(void) {
    FLAGS_00.applyAction(0x707F, 1);
    FLAGS_00.applyAction(0x8B1A, 1);
    FLAGS_00.applyAction(0x402, 1);
}

void func_800909DC(void) {
    FLAGS_00.applyAction(0x402, 1);
}

void func_80090A08(void) {
    FLAGS_00.applyAction(0x707F, 1);
    FLAGS_00.applyAction(0x8B20, 1);
    FLAGS_00.applyAction(0x403, 1);
}

void func_80090A68(void) {
    FLAGS_00.applyAction(0x403, 1);
}

void func_80090A94(void) {
    FLAGS_00.applyAction(0x7080, 1);
    FLAGS_00.applyAction(0x8489, 1);
    FLAGS_00.applyAction(0x404, 1);
}

void func_80090AF4(void) {
    FLAGS_00.applyAction(0x404, 1);
}

void func_80090B20(void) {
    FLAGS_00.applyAction(0x7080, 1);
    FLAGS_00.applyAction(0x8495, 1);
    FLAGS_00.applyAction(0x405, 1);
}

void func_80090B80(void) {
    FLAGS_00.applyAction(0x405, 1);
}

void func_80090BAC(void) {
    FLAGS_00.applyAction(0x7081, 1);
    FLAGS_00.applyAction(0x847C, 1);
    FLAGS_00.applyAction(0x406, 1);
}

void func_80090C0C(void) {
    FLAGS_00.applyAction(0x406, 1);
}

void func_80090C38(void) {
    FLAGS_00.applyAction(0x7081, 1);
    FLAGS_00.applyAction(0x8462, 1);
    FLAGS_00.applyAction(0x407, 1);
}

void func_80090C98(void) {
    FLAGS_00.applyAction(0x407, 1);
}

void func_80090CC4(void) {
    FLAGS_00.applyAction(0x7082, 1);
    FLAGS_00.applyAction(0x8ADE, 1);
    FLAGS_00.applyAction(0x408, 1);
}

void func_80090D24(void) {
    FLAGS_00.applyAction(0x408, 1);
}

void func_80090D50(void) {
    FLAGS_00.applyAction(0x7082, 1);
    FLAGS_00.applyAction(0x8AE8, 1);
    FLAGS_00.applyAction(0x409, 1);
}

void func_80090DB0(void) {
    FLAGS_00.applyAction(0x409, 1);
}

void func_80090DDC(void) {
    FLAGS_00.applyAction(0x7083, 1);
    FLAGS_00.applyAction(0x8AF4, 1);
    FLAGS_00.applyAction(0x40A, 1);
}

void func_80090E3C(void) {
    FLAGS_00.applyAction(0x40A, 1);
}

void func_80090E68(void) {
    FLAGS_00.applyAction(0x7083, 1);
    FLAGS_00.applyAction(0x8AF3, 1);
    FLAGS_00.applyAction(0x40B, 1);
}

void func_80090EC8(void) {
    FLAGS_00.applyAction(0x40B, 1);
}

void func_80090EF4(void) {
    FLAGS_00.applyAction(0x7084, 1);
    FLAGS_00.applyAction(0x8B01, 1);
    FLAGS_00.applyAction(0x40C, 1);
}

void func_80090F54(void) {
    FLAGS_00.applyAction(0x40C, 1);
}

void func_80090F80(void) {
    FLAGS_00.applyAction(0x7085, 1);
    FLAGS_00.applyAction(0x8B0D, 1);
    FLAGS_00.applyAction(0x40D, 1);
}

void func_80090FE0(void) {
    FLAGS_00.applyAction(0x40D, 1);
}

void func_8009100C(void) {
    FLAGS_00.applyAction(0x7086, 1);
    FLAGS_00.applyAction(0x8B02, 1);
    FLAGS_00.applyAction(0x40E, 1);
}

void func_8009106C(void) {
    FLAGS_00.applyAction(0x40E, 1);
}

void func_80091098(void) {
    FLAGS_00.applyAction(0x7087, 1);
    FLAGS_00.applyAction(0x8B0F, 1);
    FLAGS_00.applyAction(0x40F, 1);
}

void func_800910F8(void) {
    FLAGS_00.applyAction(0x40F, 1);
}

INCLUDE_RODATA("fieldstg/nonmatchings/fieldstg", D_80082E88);

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80091124);

void func_80091298(Tween *tween, s32 in) {
    tween->active = 1;
    if (in) {
        SOUND.playSound(0x40019);
        tween->value = 0;
        tween->step = 0x1000 / tween->duration;
    } else {
        SOUND.playSound(0x4001A);
        tween->value = 0x1000;
        tween->step = -(0x1000 / tween->duration * 2);
    }
}

s32 func_8009132C(Tween *tween) {
    if (tween->active == 0) {
        return 1;
    }
    tween->value += tween->step;
    if (tween->step > 0) {
        if (tween->value > 0x1000) {
            tween->value = 0x1000;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < 0) {
        tween->value = 0;
        tween->active = 0;
        return 1;
    }
    return 0;
}

s32 func_80091398(s32 index) {
    return FIELDSTG_fileEntries[index];
}

u8 func_800913B4(s32 index) {
    return D_80099758[index];
}

void func_800913CC(void) {
    StageEntry *entry;
    s32 mode;

#if VERSION_US
    entry = D_800998E4;
#elif VERSION_EU
    if (GAME_PROGRESS != 0x2D) {
        entry = D_8009A884;
    } else {
        entry = D_800998E4;
    }
#endif
    mode = GAME_FUNCS.getMode();
    HEAP.zero(&D_800990B4, 100);
    while (1) {
        if (entry->mode == mode) {
            D_800990B4.stageFile = entry->file;
            D_800990B4.stageInit = entry->init;
            break;
        }
        if ((++entry)->mode == 0) {
            break;
        }
    }
    if (entry->mode == 0) {
        while (1) {
        }
    }
}

void *func_80091490(u8 *list, s32 id) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (*(s32 *)(list + 4) == id) {
            return list;
        }
        list += 0x1C;
    }
    return NULL;
}

void func_800914C0(void) {
    HEAP.zero(&D_8009A424, 8);
}

Actor *func_800914F0(s32 arg0) {
    return TASK_FUNCS.find(5, arg0, -1);
}

void func_80091520(s32 time, s32 *pc) {
    if (time != 0 && D_8009A424.active == 0) {
        D_8009A424.active = 1;
        D_8009A424.time = time;
    }
    D_8009A424.time -= GFX_FUNCS.getFrameTime();
    if (D_8009A424.time <= 0) {
        D_8009A424.time = 0;
        D_8009A424.active = 0;
        (*pc)++;
    }
}

void func_800915B0(s32 id, s32 *pc) {
    Actor *actor = func_800914F0(id);

    if (actor->unk138(actor) != 0) {
        (*pc)++;
    }
}

void func_800915FC(s32 id, s32 *pc) {
    Actor *actor = func_800914F0(id);

    if (actor->unk140(actor) == 0) {
        (*pc)++;
    }
}

void func_80091648(Point *pos) {
    Point scroll;
    Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getScroll(layer, &scroll);
    pos->x -= scroll.x;
    pos->y -= scroll.y;
}

void func_800916B4(void) {
    Actor *actor = func_800914F0(1);

    if (actor == NULL) {
        actor = func_800914F0(2);
    }
    actor->unk10C = 0;
}

ScriptCommand *func_800916E8(s32 id) {
    ScriptCommand *cmd;

    for (cmd = D_8009A448; cmd->id != 0; cmd++) {
        if (cmd->id == id) {
            return cmd;
        }
    }
    return NULL;
}

s32 func_80091730(s32 id) {
    ScriptCommand *cmd = func_800916E8(id);
    s32 ret = 0;

    if (cmd != NULL) {
        ret = cmd->create(id);
    }
    return ret;
}

void func_80091774(s32 arg0, s32 id, s32 arg2, s32 arg3) {
    ScriptCommand *cmd = func_800916E8(id);

    if (cmd != NULL && cmd->handle != NULL) {
        cmd->handle(arg0, arg2, arg3);
    }
}

void func_800917D8(void) {
    s32 value = RANDOM.next() % 2304;

    if (value < 0x100) {
        GAME.unk30 = value;
    } else {
        GAME.unk30 = (value + 0x100) / 2;
    }
}

void func_80091854(void) {
    Actor *actor = TASK_FUNCS.find(5, -1, 0);
    Point tile;
    s32 area;
    s32 index;
    Battle *battle;

    tile = actor->tile;
    area = (u8)D_8009A70C.getCell(4, &tile) - 1;
    index = RANDOM.next() & 7;
    battle = D_800990B4.unk20->battles[area]->battles[index];
    D_80042728.unkC = battle->unk4;
    D_80042728.unk14 = battle->unk8;
    func_8008AEDC(battle->unk0);
}

void func_80091910(void) {
    Actor *actor;
    Point tile;
    s32 area;
    s32 rate;

    if (D_8009A70C.files[4] != 0 && D_800990B4.unk20 != NULL && D_800990B4.unk5C == 0 &&
        D_800990B4.unk58 == 0 && D_800990B4.unk60 == 0 && D_800990B4.unk54 == 0) {
        actor = TASK_FUNCS.find(5, -1, 0);
        tile = actor->tile;
        area = (u8)D_8009A70C.getCell(4, &tile);
        if (area != 0) {
            area--;
            rate = D_8009A6F4[D_800990B4.unk20->battles[area]->count];
            GAME.unk30 -= rate;
            if (GAME.unk30 <= 0) {
                if (D_80042728.unk0 != 0) {
                    func_80091854();
                }
                func_800917D8();
            }
        }
    }
}

void func_80091A4C(s32 index) {
    Battle *battle;

    if (D_800990B4.unk20 != NULL) {
        battle = D_800990B4.unk20->battles[3]->battles[index];
        D_80042728.unkC = battle->unk4;
        D_80042728.unk14 = battle->unk8;
        func_8008AEDC(battle->unk0);
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg", func_80091AA8);

void func_80091B78(s32 index, s32 value) {
    D_8009A70C.files[index] = value;
}

void func_80091B90(s32 arg0) {
    if (GAME.clearTempFlags != 0) {
        GAME.unk26D8 = arg0;
    }
}

void func_80091BB4(s32 arg0) {
    GAME.unk26D8 = arg0;
}

s32 func_80091BC0(s32 index, Point *pos) {
    s32 x;
    s32 y;
    s32 i;

    if (func_80091AA8(index) == 0) {
        return 1;
    }
    y = pos->y;
    x = pos->x;
    /* the match depends on the * 4 being a statement of its own */
    i = D_8009A70C.grid[y / 128 * D_8009A70C.width + x / 128];
    i *= 4;
    if (y & 0x40) {
        i += 2;
    }
    i = D_8009A70C.cells64[(x & 0x40) ? i + 1 : i];
    i *= 4;
    if (y & 0x20) {
        i += 2;
    }
    i = D_8009A70C.cells32[(x & 0x20) ? i + 1 : i];
    i *= 4;
    if (y & 0x10) {
        i += 2;
    }
    i = D_8009A70C.cells16[(x & 0x10) ? i + 1 : i];
    i *= 4;
    if (y & 8) {
        i += 2;
    }
    i = D_8009A70C.cells8[(x & 8) ? i + 1 : i];
    return D_8009A70C.pixels[i * 64 + (y & 7) * 8 + (x & 7)];
}

/* Whether nothing stands at pos: no character's box (gathered once a frame)
   and no object. The match depends on the boxes' variables being local to
   their blocks. */
s32 func_80091D3C(Point *pos) {
    s32 frame = GFX_FUNCS.getFrameCount();
    Actor *actor;
    s32 i;

    if (frame != D_8009A768) {
        actor = TASK_REGISTRY.funcs.find(5, -1, 1);
        for (i = 0; actor != NULL; i++) {
            s32 width = actor->unk80;

            D_8009AA4C[i].left = actor->tile.x - width;
            D_8009AA4C[i].right = actor->tile.x + width;
            width /= 2;
            D_8009AA4C[i].top = actor->tile.y - width;
            D_8009AA4C[i].bottom = actor->tile.y + width;
            actor = TASK_REGISTRY.funcs.findNext();
        }
        D_8009AB8C = i;
        D_8009A768 = frame;
    }
    for (i = 0; i < D_8009AB8C; i++) {
        if (pos->x >= D_8009AA4C[i].left && D_8009AA4C[i].right >= pos->x && pos->y >= D_8009AA4C[i].top
            && D_8009AA4C[i].bottom >= pos->y) {
            s32 dx = pos->x - D_8009AA4C[i].left;
            s32 dy = pos->y - D_8009AA4C[i].top;
            s32 width = D_8009AA4C[i].right - D_8009AA4C[i].left;
            s32 height = D_8009AA4C[i].bottom - D_8009AA4C[i].top;
            s32 halfWidth = width / 2;
            s32 halfHeight = height / 2;
            s32 ratio = width / height;

            if (halfWidth < dx) {
                dx = halfWidth - (dx - halfWidth);
            }
            if (halfHeight < dy) {
                dy = halfHeight - (dy - halfHeight);
            }
            if (dx >= halfWidth - dy * ratio) {
                return 0;
            }
        }
    }
    return func_8008C160(pos, 0) == NULL;
}

void func_80091F4C(Point *pos, s32 scale, s32 index, Point *out) {
    s32 cell = (u8)func_80091BC0(GAME.unk26D8, pos);
    s32 row = cell & 0xF;
    s32 dir;
    s32 sign;

    row -= row != 0;
    dir = (cell & 0x10) ? D_8009A92C[index] : index;
    sign = (cell & 0x10) ? -1 : 1;
    out->x = D_8009A76C[row][dir].x * scale * sign / 4096;
    out->y = D_8009A76C[row][dir].y * scale / 4096;
}

void func_8009204C(s32 arg0, s32 scale, s32 index, Point *out) {
    out->x = D_8009A76C[0][index].x * scale / 4096;
    out->y = D_8009A76C[0][index].y * scale / 4096;
}

/*
 * The field's data, after the code that uses it: its tables point to each
 * other and to the functions above (and to the stage overlay's, at fixed
 * addresses). The versions differ where #if says.
 */

extern s32 D_800920A8[];
extern s32 D_800920B4[];
extern s32 D_800920C0[];
extern s32 D_800920CC[];
extern s32 D_800920D8[];
extern s32 D_800920E4[];
extern s32 D_800920F0[];
extern s32 D_800920FC[];
extern s32 D_80092108[];
extern s32 D_80092114[];
extern s32 D_80092120[];
extern s32 D_8009212C[];
extern s32 D_80092138[];
extern s32 D_80092144[];
extern s32 D_80092150[];
extern s32 D_8009215C[];
extern s32 D_80092168[];
extern s32 D_80092174[];
extern s32 D_80092180[];
extern s32 D_8009218C[];
extern s32 D_80092198[];
extern s32 D_800921A4[];
extern s32 D_800921B0[];
extern s32 D_800921BC[];
extern s32 D_800921C8[];
extern s32 D_800921D4[];
extern s32 D_800921E0[];
extern s32 D_800921EC[];
extern s32 D_800921F8[];
extern s32 D_80092204[];
extern s32 D_80092210[];
extern s32 D_8009221C[];
extern s32 D_80092228[];
extern s32 D_80092234[];
extern s32 D_80092240[];
extern s32 D_8009224C[];
extern s32 D_80092258[];
extern s32 D_80092264[];
extern s32 D_80092270[];
extern s32 D_8009227C[];
extern s32 D_80092288[];
extern s32 D_80092294[];
extern s32 D_800922A0[];
extern s32 D_800922AC[];
extern s32 D_800922B8[];
extern s32 D_800922C4[];
extern s32 D_800922D0[];
extern s32 D_800922DC[];
extern s32 D_800922E8[];
extern s32 D_800922F4[];
extern s32 D_80092300[];
extern s32 D_8009230C[];
extern s32 D_80092318[];
extern s32 D_80092324[];
extern s32 D_80092330[];
extern s32 D_8009233C[];
extern s32 D_80092348[];
extern s32 D_80092354[];
extern s32 D_80092360[];
extern s32 D_8009236C[];
extern s32 D_80092378[];
extern s32 D_80092384[];
extern s32 D_80092390[];
extern s32 D_8009239C[];
extern s32 D_800923A8[];
extern s32 D_800923B4[];
extern s32 D_800923C0[];
extern s32 D_800923CC[];
extern s32 D_800923D8[];
extern s32 D_800923E4[];
extern s32 D_800923F0[];
extern s32 D_800923FC[];
extern s32 D_80092408[];
extern s32 D_80092414[];
extern s32 D_80092420[];
extern s32 D_8009242C[];
extern s32 D_80092438[];
extern s32 D_80092444[];
extern s32 D_80092450[];
extern s32 D_8009245C[];
extern s32 D_80092468[];
extern s32 D_80092474[];
extern s32 D_80092480[];
extern s32 D_8009248C[];
extern s32 D_80092498[];
extern s32 D_800924A4[];
extern s32 D_800924B0[];
extern s32 D_800924BC[];
extern s32 D_800924C8[];
extern s32 D_800924D4[];
extern s32 D_800924E0[];
extern s32 D_800924EC[];
extern s32 D_800924F8[];
extern s32 D_80092504[];
extern s32 D_80092510[];
extern s32 D_8009251C[];
extern s32 D_80092528[];
extern s32 D_80092534[];
extern s32 D_80092540[];
extern s32 D_8009254C[];
extern s32 D_80092558[];
extern s32 D_80092564[];
extern s32 D_80092570[];
extern s32 D_8009257C[];
extern s32 D_80092588[];
extern s32 D_80092594[];
extern s32 D_800925A0[];
extern s32 D_800925AC[];
extern s32 D_800925B8[];
extern s32 D_800925C4[];
extern s32 D_800925D0[];
extern s32 D_800925DC[];
extern s32 D_800925E8[];
extern s32 D_800925F4[];
extern s32 D_80092600[];
extern s32 D_8009260C[];
extern s32 D_80092618[];
extern s32 D_80092624[];
extern s32 D_80092630[];
extern s32 D_8009263C[];
extern s32 D_80092648[];
extern s32 D_80092654[];
extern s32 D_80092660[];
extern s32 D_8009266C[];
extern s32 D_80092678[];
extern s32 D_80092684[];
extern s32 D_80092690[];
extern s32 D_8009269C[];
extern s32 D_800926A8[];
extern s32 D_800926B4[];
extern s32 D_800926C0[];
extern s32 D_800926CC[];
extern s32 D_800926D8[];
extern s32 D_800926E4[];
extern s32 D_800926F0[];
extern s32 D_800926FC[];
extern s32 D_80092708[];
extern s32 D_80092714[];
extern s32 D_80092720[];
extern s32 D_8009272C[];
extern s32 D_80092738[];
extern s32 D_80092744[];
extern s32 D_80092750[];
extern s32 D_8009275C[];
extern s32 D_80092768[];
extern s32 D_80092774[];
extern s32 D_80092780[];
extern s32 D_8009278C[];
extern s32 D_80092798[];
extern s32 D_800927A4[];
extern s32 D_800927B0[];
extern s32 D_800927BC[];
extern s32 D_800927C8[];
extern s32 D_800927D4[];
extern s32 D_800927E0[];
extern s32 D_800927EC[];
extern s32 D_800927F8[];
extern s32 D_80092804[];
extern s32 D_80092810[];
extern s32 D_8009281C[];
extern s32 D_80092828[];
extern s32 D_80092834[];
extern s32 D_80092840[];
extern s32 D_8009284C[];
extern s32 D_80092858[];
extern s32 D_80092864[];
extern s32 D_80092870[];
extern s32 D_8009287C[];
extern s32 D_80092888[];
extern s32 D_80092894[];
extern s32 D_800928A0[];
extern s32 D_800928AC[];
extern s32 D_800928B8[];
extern s32 D_800928C4[];
extern s32 D_800928D0[];
extern s32 D_800928DC[];
extern s32 D_800928E8[];
extern s32 D_800928F4[];
extern s32 D_80092900[];
extern s32 D_8009290C[];
extern s32 D_80092918[];
extern s32 D_80092924[];
extern s32 D_80092930[];
extern s32 D_8009293C[];
extern s32 D_80092948[];
extern s32 D_80092954[];
extern s32 D_80092960[];
extern s32 D_8009296C[];
extern s32 D_80092978[];
extern s32 D_80092984[];
extern s32 D_80092990[];
extern s32 D_8009299C[];
extern s32 D_800929A8[];
extern s32 D_800929B4[];
extern s32 D_800929C0[];
extern s32 D_800929CC[];
extern s32 D_800929D8[];
extern s32 D_800929E4[];
extern s32 D_800929F0[];
extern s32 D_800929FC[];
extern s32 D_80092A08[];
extern s32 D_80092A14[];
extern s32 D_80092A20[];
extern s32 D_80092A2C[];
extern s32 D_80092A38[];
extern s32 D_80092A44[];
extern s32 D_80092A50[];
extern s32 D_80092A5C[];
extern s32 D_80092A68[];
extern s32 D_80092A74[];
extern s32 D_80092A80[];
extern s32 D_80092A8C[];
extern s32 D_80092A98[];
extern s32 D_80092AA4[];
extern s32 D_80092AB0[];
extern s32 D_80092ABC[];
extern s32 D_80092AC8[];
extern s32 D_80092AD4[];
extern s32 D_80092AE0[];
extern s32 D_80092AEC[];
extern s32 D_80092AF8[];
extern s32 D_80092B04[];
extern s32 D_80092B10[];
extern s32 D_80092B1C[];
extern s32 D_80092B28[];
extern s32 D_80092B34[];
extern s32 D_80092B40[];
extern s32 D_80092B4C[];
extern s32 D_80092B58[];
extern s32 D_80092B64[];
extern s32 D_80092B70[];
extern s32 D_80092B7C[];
extern s32 D_80092B88[];
extern s32 D_80092B94[];
extern s32 D_80092BA0[];
extern s32 D_80092BAC[];
extern s32 D_80092BB8[];
extern s32 D_80092BC4[];
extern s32 D_80092BD0[];
extern s32 D_80092BDC[];
extern s32 D_80092BE8[];
extern s32 D_80092BF4[];
extern s32 D_80092C00[];
extern s32 D_80092C0C[];
extern s32 D_80092C18[];
extern s32 D_80092C24[];
extern s32 D_80092C30[];
extern s32 D_80092C3C[];
extern s32 D_80092C48[];
extern s32 D_80092C54[];
extern s32 D_80092C60[];
extern s32 D_80092C6C[];
extern s32 D_80092C78[];
extern s32 D_80092C84[];
extern s32 D_80092C90[];
extern s32 D_80092C9C[];
extern s32 D_80092CA8[];
extern s32 D_80092CB4[];
extern s32 D_80092CC0[];
extern s32 D_80092CCC[];
extern s32 D_80092CD8[];
extern s32 D_80092CE4[];
extern s32 D_80092CF0[];
extern s32 D_80092CFC[];
extern s32 D_80092D08[];
extern s32 D_80092D14[];
extern s32 D_80092D20[];
extern s32 D_80092D2C[];
extern s32 D_80092D38[];
extern s32 D_80092D44[];
extern s32 D_80092D50[];
extern s32 D_80092D5C[];
extern s32 D_80092D68[];
extern s32 D_80092D74[];
extern s32 D_80092D80[];
extern s32 D_80092D8C[];
extern s32 D_80092D98[];
extern s32 D_80092DA4[];
extern s32 D_80092DB0[];
extern s32 D_80092DBC[];
extern s32 D_80092DC8[];
extern s32 D_80092DD4[];
extern s32 D_80092DE0[];
extern s32 D_80092DEC[];
extern s32 D_80092DF8[];
extern s32 D_80092E04[];
extern s32 D_80092E10[];
extern s32 D_80092E1C[];
extern s32 D_80092E28[];
extern s32 D_80092E34[];
extern s32 D_80092E40[];
extern s32 D_80092E4C[];
extern s32 D_80092E58[];
extern s32 D_80092E64[];
extern s32 D_80092E70[];
extern s32 D_80092E7C[];
extern s32 D_80092E88[];
extern s32 D_80092E94[];
extern s32 D_80092EA0[];
extern s32 D_80092EAC[];
extern s32 D_80092EB8[];
extern s32 D_80092EC4[];
extern s32 D_80092ED0[];
extern s32 D_80092EDC[];
extern s32 D_80092EE8[];
extern s32 D_80092EF4[];
extern s32 D_80092F00[];
extern s32 D_80092F0C[];
extern s32 D_80092F18[];
extern s32 D_80092F24[];
extern s32 D_80092F30[];
extern s32 D_80092F3C[];
extern s32 D_80092F48[];
extern s32 D_80092F54[];
extern s32 D_80092F60[];
extern s32 D_80092F6C[];
extern s32 D_80092F78[];
extern s32 D_80092F84[];
extern s32 D_80092F90[];
extern s32 D_80092F9C[];
extern s32 D_80092FA8[];
extern s32 D_80092FB4[];
extern s32 D_80092FC0[];
extern s32 D_80092FCC[];
extern s32 D_80092FD8[];
extern s32 D_80092FE4[];
extern s32 D_80092FF0[];
extern s32 D_80092FFC[];
extern s32 D_80093008[];
extern s32 D_80093014[];
extern s32 D_80093020[];
extern s32 D_8009302C[];
extern s32 D_80093038[];
extern s32 D_80093044[];
extern s32 D_80093050[];
extern s32 D_8009305C[];
extern s32 D_80093068[];
extern s32 D_80093074[];
extern s32 D_80093080[];
extern s32 D_8009308C[];
extern s32 D_80093098[];
extern s32 D_800930A4[];
extern s32 D_800930B0[];
extern s32 D_800930BC[];
extern s32 D_800930C8[];
extern s32 D_800930D4[];
extern s32 D_800930E0[];
extern s32 D_800930EC[];
extern s32 D_800930F8[];
extern s32 D_80093104[];
extern s32 D_80093110[];
extern s32 D_8009311C[];
extern s32 D_80093128[];
extern s32 D_80093134[];
extern s32 D_80093140[];
extern s32 D_8009314C[];
extern s32 D_80093158[];
extern s32 D_80093164[];
extern s32 D_80093170[];
extern s32 D_8009317C[];
extern s32 D_80093188[];
extern s32 D_80093194[];
extern s32 D_800931A0[];
extern s32 D_800931AC[];
extern s32 D_800931B8[];
extern s32 D_800931C4[];
extern s32 D_800931D0[];
extern s32 D_800931DC[];
extern s32 D_800931E8[];
extern s32 D_800931F4[];
extern s32 D_80093200[];
extern s32 D_8009320C[];
extern s32 D_80093218[];
extern s32 D_80093224[];
extern s32 D_80093230[];
extern s32 D_8009323C[];
extern s32 D_80093248[];
extern s32 D_80093254[];
extern s32 D_80093260[];
extern s32 D_8009326C[];
extern s32 D_80093278[];
extern s32 D_80093284[];
extern s32 D_80093290[];
extern s32 D_8009329C[];
extern s32 D_800932A8[];
extern s32 D_800932B4[];
extern s32 D_800932C0[];
extern s32 D_800932CC[];
extern s32 D_800932D8[];
extern s32 D_800932E4[];
extern s32 D_800932F0[];
extern s32 D_800932FC[];
extern s32 D_80093308[];
extern s32 D_80093314[];
extern s32 D_80093320[];
extern s32 D_8009332C[];
extern s32 D_80093338[];
extern s32 D_80093344[];
extern s32 D_80093350[];
extern s32 D_8009335C[];
extern s32 D_80093368[];
extern s32 D_80093374[];
extern s32 D_80093380[];
extern s32 D_8009338C[];
extern s32 D_80093398[];
extern s32 D_800933A4[];
extern s32 D_800933B0[];
extern s32 D_800933BC[];
extern s32 D_800933C8[];
extern s32 D_800933D4[];
extern s32 D_800933E0[];
extern s32 D_800933EC[];
extern s32 D_800933F8[];
extern s32 D_80093404[];
extern s32 D_80093410[];
extern s32 D_8009341C[];
extern s32 D_80093428[];
extern s32 D_80093434[];
extern s32 D_80093440[];
extern s32 D_8009344C[];
extern s32 D_80093458[];
extern s32 D_80093464[];
extern s32 D_80093470[];
extern s32 D_8009347C[];
extern s32 D_80093488[];
extern s32 D_80093494[];
extern s32 D_800934A0[];
extern s32 D_800934AC[];
extern s32 D_800934B8[];
extern s32 D_800934C4[];
extern s32 D_800934D0[];
extern s32 D_800934DC[];
extern s32 D_800934E8[];
extern s32 D_800934F4[];
extern s32 D_80093500[];
extern s32 D_8009350C[];
extern s32 D_80093518[];
extern s32 D_80093524[];
extern s32 D_80093530[];
extern s32 D_8009353C[];
extern s32 D_80093548[];
extern s32 D_80093554[];
extern s32 D_80093560[];
extern s32 D_8009356C[];
extern s32 D_80093578[];
extern s32 D_80093584[];
extern s32 D_80093590[];
extern s32 D_8009359C[];
extern s32 D_800935A8[];
extern s32 D_800935B4[];
extern s32 D_800935C0[];
extern s32 D_800935CC[];
extern s32 D_800935D8[];
extern s32 D_800935E4[];
extern s32 D_800935F0[];
extern s32 D_800935FC[];
extern s32 D_80093608[];
extern s32 D_80093614[];
extern s32 D_80093620[];
extern s32 D_8009362C[];
extern s32 D_80093638[];
extern s32 D_80093644[];
extern s32 D_80093650[];
extern s32 D_8009365C[];
extern s32 D_80093668[];
extern s32 D_80093674[];
extern s32 D_80093680[];
extern s32 D_8009368C[];
extern s32 D_80093698[];
extern s32 D_800936A4[];
extern s32 D_800936B0[];
extern s32 D_800936BC[];
extern s32 D_800936C8[];
extern s32 D_800936D4[];
extern s32 D_800936E0[];
extern s32 D_800936EC[];
extern s32 D_800936F8[];
extern s32 D_80093704[];
extern s32 D_80093710[];
extern s32 D_8009371C[];
extern s32 D_80093728[];
extern s32 D_80093734[];
extern s32 D_80093740[];
extern s32 D_8009374C[];
extern s32 D_80093758[];
extern s32 D_80093764[];
extern s32 D_80093770[];
extern s32 D_8009377C[];
extern s32 D_80093788[];
extern s32 D_80093794[];
extern s32 D_800937A0[];
extern s32 D_800937AC[];
extern s32 D_800937B8[];
extern s32 D_800937C4[];
extern s32 D_800937D0[];
extern s32 D_800937DC[];
extern s32 D_800937E8[];
extern s32 D_800937F4[];
extern s32 D_80093800[];
extern s32 D_8009380C[];
extern s32 D_80093818[];
extern s32 D_80093824[];
extern s32 D_80093830[];
extern s32 D_8009383C[];
extern s32 D_80093848[];
extern s32 D_80093854[];
extern s32 D_80093860[];
extern s32 D_8009386C[];
extern s32 D_80093878[];
extern s32 D_80093884[];
extern s32 D_80093890[];
extern s32 D_8009389C[];
extern s32 D_800938A8[];
extern s32 D_800938B4[];
extern s32 D_800938C0[];
extern s32 D_800938CC[];
extern s32 D_800938D8[];
extern s32 D_800938E4[];
extern s32 D_800938F0[];
extern s32 D_800938FC[];
extern s32 D_80093908[];
extern s32 D_80093914[];
extern s32 D_80093920[];
extern s32 D_8009392C[];
extern s32 D_80093938[];
extern s32 D_80093944[];
extern s32 D_80093950[];
extern s32 D_8009395C[];
extern s32 D_80093968[];
extern s32 D_80093974[];
extern s32 D_80093980[];
extern s32 D_8009398C[];
extern s32 D_80093998[];
extern s32 D_800939A4[];
extern s32 D_800939B0[];
extern s32 D_800939BC[];
extern s32 D_800939C8[];
extern s32 D_800939D4[];
extern AnimFrame D_800960C8[];
extern AnimFrame D_8009614C[];
extern AnimFrame D_80096174[];
extern AnimFrame D_800961B4[];
extern AnimFrame D_80096160[];
extern AnimFrame D_80096194[];
extern s32 D_8009AA08[];
extern s32 D_8009A9D8[];
extern s32 D_8009A9A8[];
extern s32 D_8009A978[];
extern s32 D_8009A94C[];
extern s32 D_8009A954[];
extern s32 D_8009A95C[];
extern s32 D_8009A964[];
extern s32 D_8009A96C;
extern s32 D_8009A970[];
extern s32 D_8009A9A0[];
extern s32 D_8009A9D0[];
extern s32 D_8009AA00[];
extern s32 D_8009AA34;
extern s32 D_8009AA2C[];
extern s32 D_8009AA24[];
extern s32 D_8009AA1C[];
extern s32 D_8009AA10[];
extern s32 D_8009A9E0[];
extern s32 D_8009A9B0[];
extern s32 D_8009A984[];
extern s32 D_8009A98C[];
extern s32 D_8009A994;
extern s32 D_8009A998[];
extern s32 D_8009A9C8[];
extern s32 D_8009A9FC;
extern s32 D_8009A9F4[];
extern s32 D_8009A9E8[];
extern s32 D_8009A9BC;
extern u8 D_80096D2C[];
extern u8 D_80096D3C[];
extern u8 D_80096D4C[];
extern u8 D_80096D5C[];
extern u8 D_80096D6C[];
extern u8 D_80096D7C[];
extern u8 D_80096D8C[];
extern u8 D_80096D9C[];
extern s32 D_80096DEC[];
extern s32 D_80096DF8[];
extern s32 D_80096E04[];
extern s32 D_80096E10[];
extern s32 D_80096E1C[];
extern s32 D_80096E28[];
extern s32 D_80096E34[];
extern s32 D_80096E40[];
extern s32 D_800971A0[];
extern s32 D_800971A8[];
extern s32 D_800971B4[];
extern s32 D_800971BC[];
extern s32 D_800971C8[];
extern s32 D_800971D0[];
extern s32 D_800971DC[];
extern s32 D_800971E4[];
extern s32 D_80097B50[];
extern s32 D_80097B58[];
extern s32 D_80097B60[];
extern s32 D_80097B68[];
extern s32 D_80097B70[];
extern s32 D_80097B78[];
extern s32 D_80097B80[];
extern s32 D_80097B88[];
extern s32 D_80097B90[];
extern s32 D_80097B98[];
extern s32 D_80097BA0[];
extern s32 D_80097BA8[];
extern s32 D_80097BB0[];
extern s32 D_80097BB8[];
extern s32 D_80097BC0[];
extern s32 D_80097BC8[];
extern s32 D_800971F0[];
extern s32 D_80097BD0[];
extern s32 D_80097208[];
extern s32 D_80097BD8[];
extern s32 D_80097220[];
extern s32 D_80097BE0[];
extern s32 D_80097238[];
extern s32 D_80097BE8[];
extern s32 D_80097250[];
extern s32 D_80097BF0[];
extern s32 D_80097268[];
extern s32 D_80097BF8[];
extern s32 D_80097280[];
extern s32 D_80097C00[];
extern s32 D_80097298[];
extern s32 D_80097C08[];
extern s32 D_800972B0[];
extern s32 D_80097C10[];
extern s32 D_800972C8[];
extern s32 D_80097C18[];
extern s32 D_800972E0[];
extern s32 D_80097C20[];
extern s32 D_800972F8[];
extern s32 D_80097C28[];
extern s32 D_80097310[];
extern s32 D_80097C30[];
extern s32 D_80097328[];
extern s32 D_80097C38[];
extern s32 D_80097340[];
extern s32 D_80097C40[];
extern s32 D_80097358[];
extern s32 D_80097C48[];
extern s32 D_80097370[];
extern s32 D_80097C50[];
extern s32 D_80097388[];
extern s32 D_80097C58[];
extern s32 D_800973A0[];
extern s32 D_80097C60[];
extern s32 D_800973B8[];
extern s32 D_80097C68[];
extern s32 D_800973D0[];
extern s32 D_80097C70[];
extern s32 D_800973E8[];
extern s32 D_80097C78[];
extern s32 D_80097400[];
extern s32 D_80097C80[];
extern s32 D_80097418[];
extern s32 D_80097C88[];
extern s32 D_80097430[];
extern s32 D_80097C90[];
extern s32 D_80097448[];
extern s32 D_80097C98[];
extern s32 D_80097460[];
extern s32 D_80097CA0[];
extern s32 D_80097478[];
extern s32 D_80097CA8[];
extern s32 D_80097490[];
extern s32 D_80097CB0[];
extern s32 D_800974A8[];
extern s32 D_80097CB8[];
extern s32 D_800974C0[];
extern s32 D_80097CC0[];
extern s32 D_800974D8[];
extern s32 D_80097CC8[];
extern s32 D_800974F0[];
extern s32 D_80097CD0[];
extern s32 D_80097508[];
extern s32 D_80097CD8[];
extern s32 D_80097520[];
extern s32 D_80097CE0[];
extern s32 D_80097538[];
extern s32 D_80097CE8[];
extern s32 D_80097550[];
extern s32 D_80097CF0[];
extern s32 D_80097568[];
extern s32 D_80097CF8[];
extern s32 D_80097580[];
extern s32 D_80097D00[];
extern s32 D_80097598[];
extern s32 D_80097D08[];
extern s32 D_800975B0[];
extern s32 D_80097D10[];
extern s32 D_800975C8[];
extern s32 D_80097D18[];
extern s32 D_800975E0[];
extern s32 D_80097D20[];
extern s32 D_800975F8[];
extern s32 D_80097D28[];
extern s32 D_80097610[];
extern s32 D_80097D30[];
extern s32 D_80097628[];
extern s32 D_80097D38[];
extern s32 D_80097640[];
extern s32 D_80097D40[];
extern s32 D_80097658[];
extern s32 D_80097D48[];
extern s32 D_80097670[];
extern s32 D_80097D50[];
extern s32 D_80097688[];
extern s32 D_80097D58[];
extern s32 D_800976A0[];
extern s32 D_80097D60[];
extern s32 D_800976B8[];
extern s32 D_80097D68[];
extern s32 D_800976D0[];
extern s32 D_80097D70[];
extern s32 D_800976E8[];
extern s32 D_80097D78[];
extern s32 D_80097700[];
extern s32 D_80097D80[];
extern s32 D_80097718[];
extern s32 D_80097D88[];
extern s32 D_80097730[];
extern s32 D_80097D90[];
extern s32 D_80097748[];
extern s32 D_80097D98[];
extern s32 D_80097760[];
extern s32 D_80097DA0[];
extern s32 D_80097778[];
extern s32 D_80097DA8[];
extern s32 D_80097790[];
extern s32 D_80097DB0[];
extern s32 D_800977A8[];
extern s32 D_80097DB8[];
extern s32 D_800977C0[];
extern s32 D_80097DC0[];
extern s32 D_800977D8[];
extern s32 D_80097DC8[];
extern s32 D_800977F0[];
extern s32 D_80097DD0[];
extern s32 D_80097808[];
extern s32 D_80097DD8[];
extern s32 D_80097820[];
extern s32 D_80097DE0[];
extern s32 D_80097838[];
extern s32 D_80097DE8[];
extern s32 D_80097850[];
extern s32 D_80097DF0[];
extern s32 D_80097868[];
extern s32 D_80097DF8[];
extern s32 D_80097880[];
extern s32 D_80097E00[];
extern s32 D_80097898[];
extern s32 D_80097E08[];
extern s32 D_800978B0[];
extern s32 D_80097E10[];
extern s32 D_800978C8[];
extern s32 D_80097E18[];
extern s32 D_800978E0[];
extern s32 D_80097E20[];
extern s32 D_800978F8[];
extern s32 D_80097E28[];
extern s32 D_80097910[];
extern s32 D_80097E30[];
extern s32 D_80097928[];
extern s32 D_80097E38[];
extern s32 D_80097940[];
extern s32 D_80097E40[];
extern s32 D_80097958[];
extern s32 D_80097E48[];
extern s32 D_80097970[];
extern s32 D_80097E50[];
extern s32 D_80097988[];
extern s32 D_80097E58[];
extern s32 D_800979A0[];
extern s32 D_80097E60[];
extern s32 D_800979B8[];
extern s32 D_80097E68[];
extern s32 D_800979D0[];
extern s32 D_80097E70[];
extern s32 D_800979E8[];
extern s32 D_80097E78[];
extern s32 D_80097A00[];
extern s32 D_80097E80[];
extern s32 D_80097A18[];
extern s32 D_80097E88[];
extern s32 D_80097A30[];
extern s32 D_80097E90[];
extern s32 D_80097A48[];
extern s32 D_80097E98[];
extern s32 D_80097A60[];
extern s32 D_80097EA0[];
extern s32 D_80097A78[];
extern s32 D_80097EEC[];
extern s32 D_80097A9C[];
extern s32 D_80097EF4[];
extern s32 D_80097AC0[];
extern s32 D_80097EFC[];
extern s32 D_80097F04[];
extern s32 D_80097AD8[];
extern s32 D_80097F0C[];
extern s32 D_80097AF0[];
extern s32 D_80097F14[];
extern s32 D_80097B08[];
extern s32 D_80097F1C[];
extern s32 D_80097B20[];
extern s32 D_80097F24[];
extern s32 D_80097B38[];
extern s32 D_80097F2C[];
extern s32 D_80097F40[];
extern s32 D_80097F54[];
extern s32 D_80097F68[];
extern s32 D_80097F7C[];
extern s32 D_80097F90[];
extern s32 D_80097FA4[];
extern s32 D_80097FB8[];
extern s32 D_80097FCC[];
extern s32 D_80097FE0[];
extern s32 D_80097FF4[];
extern s32 D_80098008[];
extern s32 D_8009801C[];
extern s32 D_80098030[];
extern s32 D_80098044[];
extern s32 D_80098058[];
extern s32 D_8009806C[];
extern s32 D_80098080[];
extern s32 D_80098094[];
extern s32 D_800980A8[];
extern s32 D_800980BC[];
extern s32 D_800980D0[];
extern s32 D_800980E4[];
extern s32 D_800980F8[];
extern s32 D_8009810C[];
extern s32 D_80098120[];
extern s32 D_80098134[];
extern s32 D_80098148[];
extern s32 D_8009815C[];
extern s32 D_80098170[];
extern s32 D_80098184[];
extern s32 D_80098198[];
extern s32 D_800981AC[];
extern s32 D_800981C0[];
extern s32 D_800981D4[];
extern s32 D_800981E8[];
extern s32 D_800981FC[];
extern s32 D_80098210[];
extern s32 D_80098224[];
extern s32 D_80098238[];
extern s32 D_8009824C[];
extern s32 D_80098260[];
extern s32 D_80098274[];
extern s32 D_80098288[];
extern s32 D_8009829C[];
extern s32 D_800982B0[];
extern s32 D_800982C4[];
extern s32 D_800982D8[];
extern s32 D_800982EC[];
extern s32 D_80098300[];
extern s32 D_80098314[];
extern s32 D_80098328[];
extern s32 D_8009833C[];
extern s32 D_80098350[];
extern s32 D_80098364[];
extern s32 D_80098378[];
extern s32 D_8009838C[];
extern s32 D_800983A0[];
extern s32 D_800983B4[];
extern s32 D_800983C8[];
extern s32 D_800983DC[];
extern s32 D_800983F0[];
extern s32 D_80098404[];
extern s32 D_80098418[];
extern s32 D_8009842C[];
extern s32 D_80098440[];
extern s32 D_80098454[];
extern s32 D_80098468[];
extern s32 D_8009847C[];
extern s32 D_80098490[];
extern s32 D_800984A4[];
extern s32 D_800984B8[];
extern s32 D_800984CC[];
extern s32 D_800984E0[];
extern s32 D_800984F4[];
extern s32 D_80098508[];
extern s32 D_8009851C[];
extern s32 D_80098530[];
extern s32 D_80098544[];
extern s32 D_80098558[];
extern s32 D_8009856C[];
extern s32 D_80098580[];
extern s32 D_80098594[];
extern s32 D_800985A8[];
extern s32 D_800985BC[];
extern s32 D_800985D0[];
extern s32 D_800985E4[];
extern s32 D_800985F8[];
extern s32 D_8009860C[];
extern s32 D_80098620[];
extern s32 D_80098634[];
extern s32 D_80098648[];
extern s32 D_8009865C[];
extern s32 D_80098670[];
extern s32 D_80098684[];
extern s32 D_80098698[];
extern s32 D_800986AC[];
extern s32 D_800986C0[];
extern s32 D_800986D4[];
extern s32 D_800986E8[];
extern s32 D_800986FC[];
extern s32 D_80098710[];
extern s32 D_80098724[];
extern s32 D_80098738[];
extern s32 D_8009874C[];
extern s32 D_80098760[];
extern s32 D_80098774[];
extern s32 D_80098788[];
extern s32 D_8009879C[];
extern s32 D_800987B0[];
extern s32 D_800987C4[];
extern s32 D_800987D8[];
extern s32 D_800987EC[];
extern s32 D_80098800[];
extern s32 D_80098814[];
void func_80091124();
void func_80082F84();
void func_80091910();
s32 func_80091BC0(s32, Point *);
s32 func_80091D3C(Point *pos);
#if VERSION_EU
extern s32 D_800940A4[];
extern s32 D_800940B0[];
extern s32 D_80096E4C[];
#endif

s32 D_800920A8[] = {
    0, 0, 0,
};
s32 D_800920B4[] = {
    358, 0x330000C, 0x10270F,
};
s32 D_800920C0[] = {
    124, 0x390000E, 0x10270F,
};
s32 D_800920CC[] = {
    172, 0x1F80009, 0x16270F,
};
s32 D_800920D8[] = {
    8, 0x240000B, 0x17270F,
};
s32 D_800920E4[] = {
    207, 0x2AC000E, 0x14270F,
};
s32 D_800920F0[] = {
    222, 0x264000C, 0x1B270F,
};
s32 D_800920FC[] = {
    77, 0x2AC000E, 0x16270F,
};
s32 D_80092108[] = {
    119, 0x3180011, 0xE00C8,
};
s32 D_80092114[] = {
    11, 0x300001B, 0x11270F,
};
s32 D_80092120[] = {
    11, 0x300001B, 0x11270F,
};
s32 D_8009212C[] = {
    400, 0x4C8001D, 0xE270F,
};
s32 D_80092138[] = {
    208, 0x4C8001D, 0x10270F,
};
s32 D_80092144[] = {
    13, 0x440001D, 0x12270F,
};
s32 D_80092150[] = {
    356, 0x6F00020, 0x100118,
};
s32 D_8009215C[] = {
    70, 0x6F00020, 0x10270F,
};
s32 D_80092168[] = {
    141, 0x7500022, 0x10270F,
};
s32 D_80092174[] = {
    399, 0x3900021, 0x10270F,
};
s32 D_80092180[] = {
    302, 0x57C0022, 0x10270F,
};
s32 D_8009218C[] = {
    437, 0xC180026, 0x100028,
};
s32 D_80092198[] = {
    337, 0x8700028, 0x10270F,
};
s32 D_800921A4[] = {
    436, 0x900002B, 0x1003C0,
};
s32 D_800921B0[] = {
    443, 0x960002D, 0x10270F,
};
s32 D_800921BC[] = {
    138, 0x6540028, 0x12270F,
};
s32 D_800921C8[] = {
    402, 0x9B40029, 0x10270F,
};
s32 D_800921D4[] = {
    237, 0x6E4002C, 0x10270F,
};
s32 D_800921E0[] = {
    444, 0x990002E, 0x10270F,
};
s32 D_800921EC[] = {
    425, 0x6780029, 0x10270F,
};
s32 D_800921F8[] = {
    202, 0x6C0002B, 0x10270F,
};
s32 D_80092204[] = {
    238, 0x72C002E, 0x11270F,
};
s32 D_80092210[] = {
    447, 0x9C0002F, 0x10270F,
};
s32 D_8009221C[] = {
    270, 0x708002D, 0x11270F,
};
s32 D_80092228[] = {
    65, 0x72C002E, 0x110128,
};
s32 D_80092234[] = {
    360, 0x7980031, 0x12270F,
};
s32 D_80092240[] = {
    23, 0x4B0002D, 0x11270F,
};
s32 D_8009224C[] = {
    427, 0x4C8002E, 0x11270F,
};
s32 D_80092258[] = {
    409, 0x5100031, 0x11270F,
};
s32 D_80092264[] = {
    9, 0x4B0002D, 0x11270F,
};
s32 D_80092270[] = {
    189, 0x4E0002F, 0x11270F,
};
s32 D_8009227C[] = {
    104, 0x5280032, 0x110708,
};
s32 D_80092288[] = {
    244, 0x4C8002E, 0x13270F,
};
s32 D_80092294[] = {
    135, 0x4F80030, 0x12270F,
};
s32 D_800922A0[] = {
    429, 0x5280032, 0x11270F,
};
s32 D_800922AC[] = {
    24, 0x750002F, 0x11270F,
};
s32 D_800922B8[] = {
    410, 0x5100031, 0x110004,
};
s32 D_800922C4[] = {
    115, 0x5400033, 0x11270F,
};
s32 D_800922D0[] = {
    445, 0xB400037, 0x10270F,
};
s32 D_800922DC[] = {
    446, 0xBA00039, 0x100008,
};
s32 D_800922E8[] = {
    108, 0x7980031, 0x12270F,
};
s32 D_800922F4[] = {
    193, 0x7BC0032, 0x12270F,
};
s32 D_80092300[] = {
    428, 0x8040034, 0x11270F,
};
s32 D_8009230C[] = {
    190, 0x7BC0032, 0x11270F,
};
s32 D_80092318[] = {
    215, 0x8040034, 0x11270F,
};
s32 D_80092324[] = {
    231, 0x84C0036, 0x10270F,
};
s32 D_80092330[] = {
    431, 0x7BC0032, 0x11270F,
};
s32 D_8009233C[] = {
    434, 0x5580034, 0x11270F,
};
s32 D_80092348[] = {
    433, 0x5880036, 0x10270F,
};
s32 D_80092354[] = {
    327, 0x5580034, 0x11270F,
};
s32 D_80092360[] = {
    327, 0x5580034, 0x11270F,
};
s32 D_8009236C[] = {
    247, 0x5A00037, 0x10270F,
};
s32 D_80092378[] = {
    312, 0x46D0036, 0x11270F,
};
s32 D_80092384[] = {
    228, 0x5B80038, 0x10270F,
};
s32 D_80092390[] = {
    245, 0x5E8003A, 0x11270F,
};
s32 D_8009239C[] = {
    178, 0x270F0063, 0x1D270F,
};
s32 D_800923A8[] = {
    448, 0xAE00035, 0x10270F,
};
s32 D_800923B4[] = {
    432, 0x5880036, 0x10270F,
};
s32 D_800923C0[] = {
    236, 0x5D00039, 0x11270F,
};
s32 D_800923CC[] = {
    438, 0xC30003C, 0x10270F,
};
s32 D_800923D8[] = {
    439, 0x11700039, 0x10270F,
};
s32 D_800923E4[] = {
    440, 0xBA00039, 0x10270F,
};
s32 D_800923F0[] = {
    441, 0xBA00039, 0x10270F,
};
s32 D_800923FC[] = {
    32, 0x780001, 0x10270F,
};
s32 D_80092408[] = {
    206, 0x780001, 0x10270F,
};
s32 D_80092414[] = {
    197, 0xA80003, 0x10270F,
};
s32 D_80092420[] = {
    132, 0xC00004, 0x10270F,
};
s32 D_8009242C[] = {
    217, 0x1380008, 0x10270F,
};
s32 D_80092438[] = {
    4, 0x900002, 0x10270F,
};
s32 D_80092444[] = {
    25, 0xC00004, 0x10270F,
};
s32 D_80092450[] = {
    51, 0x900002, 0x10270F,
};
s32 D_8009245C[] = {
    67, 0xA80003, 0x10270F,
};
s32 D_80092468[] = {
    198, 0xA80003, 0x10270F,
};
s32 D_80092474[] = {
    166, 0xC00004, 0x10270F,
};
s32 D_80092480[] = {
    80, 0xC00004, 0x10270F,
};
s32 D_8009248C[] = {
    277, 0x1F80010, 0x10270F,
};
s32 D_80092498[] = {
    172, 0xF00005, 0x10270F,
};
s32 D_800924A4[] = {
    137, 0x1B0000D, 0x10270F,
};
s32 D_800924B0[] = {
    222, 0xF00005, 0x10270F,
};
s32 D_800924BC[] = {
    8, 0x1080006, 0x10270F,
};
s32 D_800924C8[] = {
    203, 0x18C0006, 0x10270F,
};
s32 D_800924D4[] = {
    7, 0x1080006, 0x10270F,
};
s32 D_800924E0[] = {
    110, 0x1380008, 0x10270F,
};
s32 D_800924EC[] = {
    49, 0x1380008, 0x10270F,
};
s32 D_800924F8[] = {
    37, 0x1500009, 0x10270F,
};
s32 D_80092504[] = {
    223, 0x360001F, 0x10270F,
};
s32 D_80092510[] = {
    50, 0x1B0000D, 0x10270F,
};
s32 D_8009251C[] = {
    207, 0x168000A, 0x10270F,
};
s32 D_80092528[] = {
    35, 0x2280012, 0x10270F,
};
s32 D_80092534[] = {
    208, 0x330001D, 0x10270F,
};
s32 D_80092540[] = {
    210, 0x2580014, 0x100078,
};
s32 D_8009254C[] = {
    220, 0x300001B, 0x10270F,
};
s32 D_80092558[] = {
    221, 0x4380028, 0x10270F,
};
s32 D_80092564[] = {
    241, 0x2B80018, 0x10270F,
};
s32 D_80092570[] = {
    119, 0x2580014, 0x1000C8,
};
s32 D_8009257C[] = {
    10, 0x198000C, 0x10270F,
};
s32 D_80092588[] = {
    212, 0x2A00017, 0x10270F,
};
s32 D_80092594[] = {
    42, 0x2580014, 0x100040,
};
s32 D_800925A0[] = {
    34, 0x2580014, 0x10270F,
};
s32 D_800925AC[] = {
    136, 0x3CC0016, 0x10270F,
};
s32 D_800925B8[] = {
    108, 0x498002C, 0x10270F,
};
s32 D_800925C4[] = {
    273, 0x4B0002D, 0x10270F,
};
s32 D_800925D0[] = {
    28, 0x2880016, 0x10270F,
};
s32 D_800925DC[] = {
    334, 0x2880016, 0x10270F,
};
s32 D_800925E8[] = {
    13, 0x1E00019, 0x10270F,
};
s32 D_800925F4[] = {
    435, 0x330001D, 0x10270F,
};
s32 D_80092600[] = {
    176, 0x2A00017, 0x100096,
};
s32 D_8009260C[] = {
    122, 0x2A00017, 0x100150,
};
s32 D_80092618[] = {
    143, 0x2B80018, 0x10270F,
};
s32 D_80092624[] = {
    40, 0x2B80018, 0x10270F,
};
s32 D_80092630[] = {
    11, 0x2D00019, 0x10270F,
};
s32 D_8009263C[] = {
    39, 0x2E8001A, 0x10270F,
};
s32 D_80092648[] = {
    227, 0x4E0002F, 0x10270F,
};
s32 D_80092654[] = {
    171, 0x4E0002F, 0x10270F,
};
s32 D_80092660[] = {
    139, 0x300001B, 0x10010E,
};
s32 D_8009266C[] = {
    134, 0x300001B, 0x10270F,
};
s32 D_80092678[] = {
    54, 0x4C8002E, 0x10270F,
};
s32 D_80092684[] = {
    14, 0x330001D, 0x10270F,
};
s32 D_80092690[] = {
    76, 0x348001E, 0x10270F,
};
s32 D_8009269C[] = {
    53, 0x330001D, 0x10270F,
};
s32 D_800926A8[] = {
    173, 0x360001F, 0x10270F,
};
s32 D_800926B4[] = {
    175, 0x3D80024, 0x10270F,
};
s32 D_800926C0[] = {
    238, 0x480002B, 0x10270F,
};
s32 D_800926CC[] = {
    200, 0x3A80022, 0x10270F,
};
s32 D_800926D8[] = {
    121, 0x4080026, 0x10270F,
};
s32 D_800926E4[] = {
    302, 0x3C00023, 0x10270F,
};
s32 D_800926F0[] = {
    364, 0x3C00023, 0x10270F,
};
s32 D_800926FC[] = {
    365, 0x4B0002D, 0x10270F,
};
s32 D_80092708[] = {
    226, 0x3A80022, 0x10270F,
};
s32 D_80092714[] = {
    140, 0x3D80024, 0x10270F,
};
s32 D_80092720[] = {
    138, 0x3D80024, 0x10270F,
};
s32 D_8009272C[] = {
    24, 0x708002D, 0x10270F,
};
s32 D_80092738[] = {
    224, 0x3F00025, 0x10270F,
};
s32 D_80092744[] = {
    225, 0x498002C, 0x10270F,
};
s32 D_80092750[] = {
    61, 0x3C00023, 0x10270F,
};
s32 D_8009275C[] = {
    165, 0x3A80022, 0x10270F,
};
s32 D_80092768[] = {
    170, 0x3D80024, 0x100060,
};
s32 D_80092774[] = {
    244, 0x4200027, 0x10270F,
};
s32 D_80092780[] = {
    126, 0x3D80024, 0x10270F,
};
s32 D_8009278C[] = {
    38, 0x4500029, 0x10270F,
};
s32 D_80092798[] = {
    69, 0x4500029, 0x10270F,
};
s32 D_800927A4[] = {
    9, 0x4500029, 0x10270F,
};
s32 D_800927B0[] = {
    52, 0x4500029, 0x10270F,
};
s32 D_800927BC[] = {
    23, 0x4500029, 0x10270F,
};
s32 D_800927C8[] = {
    94, 0x480002B, 0x10270F,
};
s32 D_800927D4[] = {
    41, 0x4C8002E, 0x10270F,
};
s32 D_800927E0[] = {
    270, 0x480002B, 0x10270F,
};
s32 D_800927EC[] = {
    327, 0x5100031, 0x10270F,
};
s32 D_800927F8[] = {
    189, 0x480002B, 0x10270F,
};
s32 D_80092804[] = {
    135, 0x480002B, 0x10270F,
};
s32 D_80092810[] = {
    237, 0x498002C, 0x10270F,
};
s32 D_8009281C[] = {
    229, 0x498002C, 0x10270F,
};
s32 D_80092828[] = {
    204, 0x498002C, 0x10270F,
};
s32 D_80092834[] = {
    281, 0x480002B, 0x10270F,
};
s32 D_80092840[] = {
    202, 0x480002B, 0x10270F,
};
s32 D_8009284C[] = {
    360, 0x498002C, 0x10270F,
};
s32 D_80092858[] = {
    60, 0x498002C, 0x10270F,
};
s32 D_80092864[] = {
    231, 0x5880036, 0x10270F,
};
s32 D_80092870[] = {
    215, 0x5100031, 0x10270F,
};
s32 D_8009287C[] = {
    269, 0x4B0002D, 0x10270F,
};
s32 D_80092888[] = {
    177, 0x4B0002D, 0x10270F,
};
s32 D_80092894[] = {
    65, 0x498002C, 0x100128,
};
s32 D_800928A0[] = {
    250, 0x4B0002D, 0x10270F,
};
s32 D_800928AC[] = {
    193, 0x4B0002D, 0x10270F,
};
s32 D_800928B8[] = {
    245, 0x5A00037, 0x10270F,
};
s32 D_800928C4[] = {
    272, 0x4E0002F, 0x10270F,
};
s32 D_800928D0[] = {
    190, 0x4F80030, 0x10270F,
};
s32 D_800928DC[] = {
    228, 0x5B80038, 0x10270F,
};
s32 D_800928E8[] = {
    115, 0x4E0002F, 0x10270F,
};
s32 D_800928F4[] = {
    236, 0x5A00037, 0x10270F,
};
s32 D_80092900[] = {
    251, 0x5B80038, 0x10270F,
};
s32 D_8009290C[] = {
    312, 0x40D0031, 0x10270F,
};
s32 D_80092918[] = {
    247, 0x5A00037, 0x10270F,
};
s32 D_80092924[] = {
    382, 0x8940038, 0x10270F,
};
s32 D_80092930[] = {
    77, 0x1500009, 0x10270F,
};
s32 D_8009293C[] = {
    395, 0x348001E, 0x10270F,
};
s32 D_80092948[] = {
    396, 0x1380008, 0x10270F,
};
s32 D_80092954[] = {
    397, 0x2700015, 0x10270F,
};
s32 D_80092960[] = {
    398, 0x2880016, 0x10270F,
};
s32 D_8009296C[] = {
    399, 0x2600021, 0x10270F,
};
s32 D_80092978[] = {
    400, 0x3900021, 0x10270F,
};
s32 D_80092984[] = {
    401, 0x2400013, 0x10270F,
};
s32 D_80092990[] = {
    402, 0x6780029, 0x10270F,
};
s32 D_8009299C[] = {
    403, 0x2700015, 0x10270F,
};
s32 D_800929A8[] = {
    404, 0x3F00025, 0x10270F,
};
s32 D_800929B4[] = {
    405, 0x2880016, 0x10270F,
};
s32 D_800929C0[] = {
    406, 0x3D80024, 0x10270F,
};
s32 D_800929CC[] = {
    407, 0x3F00025, 0x100168,
};
s32 D_800929D8[] = {
    408, 0x3C00023, 0x10270F,
};
s32 D_800929E4[] = {
    409, 0x4E0002F, 0x10270F,
};
s32 D_800929F0[] = {
    89, 0x468002A, 0x10270F,
};
s32 D_800929FC[] = {
    410, 0x4C8002E, 0x100004,
};
s32 D_80092A08[] = {
    411, 0x4F80030, 0x10270F,
};
s32 D_80092A14[] = {
    412, 0x4C8002E, 0x10270F,
};
s32 D_80092A20[] = {
    413, 0x360001F, 0x10270F,
};
s32 D_80092A2C[] = {
    414, 0x4200027, 0x10270F,
};
s32 D_80092A38[] = {
    415, 0x480002B, 0x10270F,
};
s32 D_80092A44[] = {
    416, 0x480002B, 0x10270F,
};
s32 D_80092A50[] = {
    417, 0x498002C, 0x10270F,
};
s32 D_80092A5C[] = {
    418, 0x4380028, 0x10270F,
};
s32 D_80092A68[] = {
    419, 0x480002B, 0x10270F,
};
s32 D_80092A74[] = {
    420, 0x4B0002D, 0x10270F,
};
s32 D_80092A80[] = {
    421, 0x3780020, 0x10270F,
};
s32 D_80092A8C[] = {
    422, 0x4380028, 0x10270F,
};
s32 D_80092A98[] = {
    423, 0x4F80030, 0x10270F,
};
s32 D_80092AA4[] = {
    424, 0x3D80024, 0x10270F,
};
s32 D_80092AB0[] = {
    425, 0x4500029, 0x10270F,
};
s32 D_80092ABC[] = {
    426, 0x750002F, 0x10270F,
};
s32 D_80092AC8[] = {
    427, 0x498002C, 0x10270F,
};
s32 D_80092AD4[] = {
    428, 0x4F80030, 0x10270F,
};
s32 D_80092AE0[] = {
    429, 0x4F80030, 0x10270F,
};
s32 D_80092AEC[] = {
    430, 0x498002C, 0x10270F,
};
s32 D_80092AF8[] = {
    104, 0x4F80030, 0x100708,
};
s32 D_80092B04[] = {
    431, 0x750002F, 0x10270F,
};
s32 D_80092B10[] = {
    432, 0x5880036, 0x10270F,
};
s32 D_80092B1C[] = {
    433, 0x5880036, 0x10270F,
};
s32 D_80092B28[] = {
    434, 0x5100031, 0x10270F,
};
s32 D_80092B34[] = {
    14, 0x330001D, 0x10270F,
};
s32 D_80092B40[] = {
    53, 0x330001D, 0x10270F,
};
s32 D_80092B4C[] = {
    435, 0x330001D, 0x10270F,
};
s32 D_80092B58[] = {
    76, 0x348001E, 0x10270F,
};
s32 D_80092B64[] = {
    435, 0x330001D, 0x10270F,
};
s32 D_80092B70[] = {
    76, 0x348001E, 0x10270F,
};
s32 D_80092B7C[] = {
    76, 0x348001E, 0x10270F,
};
s32 D_80092B88[] = {
    334, 0x3780020, 0x16270F,
};
s32 D_80092B94[] = {
    139, 0x330001D, 0x11010E,
};
s32 D_80092BA0[] = {
    134, 0x330001D, 0x11270F,
};
s32 D_80092BAC[] = {
    225, 0x498002C, 0x10270F,
};
s32 D_80092BB8[] = {
    229, 0x498002C, 0x10270F,
};
s32 D_80092BC4[] = {
    41, 0x4C8002E, 0x10270F,
};
s32 D_80092BD0[] = {
    245, 0x5A00037, 0x10270F,
};
s32 D_80092BDC[] = {
    251, 0x5B80038, 0x10270F,
};
s32 D_80092BE8[] = {
    427, 0x4F80030, 0x11270F,
};
s32 D_80092BF4[] = {
    411, 0x5280032, 0x11270F,
};
s32 D_80092C00[] = {
    411, 0x5280032, 0x11270F,
};
s32 D_80092C0C[] = {
    412, 0x5280032, 0x11270F,
};
s32 D_80092C18[] = {
    231, 0x5280032, 0xF270F,
};
s32 D_80092C24[] = {
    228, 0x5400033, 0xF270F,
};
s32 D_80092C30[] = {
    247, 0x5580034, 0xF270F,
};
s32 D_80092C3C[] = {
    178, 0xAE00035, 0x10270F,
};
s32 D_80092C48[] = {
    231, 0x5280032, 0xF270F,
};
s32 D_80092C54[] = {
    228, 0x5400033, 0xF270F,
};
s32 D_80092C60[] = {
    51, 0x640001, 0xC270F,
};
s32 D_80092C6C[] = {
    4, 0xC00004, 0x15270F,
};
s32 D_80092C78[] = {
    25, 0xC00004, 0x10270F,
};
s32 D_80092C84[] = {
    198, 0xF00005, 0x17270F,
};
s32 D_80092C90[] = {
    67, 0x4380028, 0x67270F,
};
s32 D_80092C9C[] = {
    51, 0x4380028, 0x78270F,
};
s32 D_80092CA8[] = {
    137, 0x4B0002D, 0x2C270F,
};
s32 D_80092CB4[] = {
    32, 0x1080006, 0x23270F,
};
s32 D_80092CC0[] = {
    32, 0x1200007, 0x26270F,
};
s32 D_80092CCC[] = {
    166, 0x1500009, 0x1C270F,
};
s32 D_80092CD8[] = {
    80, 0x1200007, 0x18270F,
};
s32 D_80092CE4[] = {
    34, 0x1380008, 0x8270F,
};
s32 D_80092CF0[] = {
    197, 0x1080006, 0x19270F,
};
s32 D_80092CFC[] = {
    132, 0x1200007, 0x18270F,
};
s32 D_80092D08[] = {
    110, 0x1200007, 0xF270F,
};
s32 D_80092D14[] = {
    206, 0x1500009, 0x2D270F,
};
s32 D_80092D20[] = {
    49, 0x4380028, 0x37270F,
};
s32 D_80092D2C[] = {
    50, 0x4380028, 0x28270F,
};
s32 D_80092D38[] = {
    7, 0x5280032, 0x50270F,
};
s32 D_80092D44[] = {
    4, 0x1080006, 0x1D270F,
};
s32 D_80092D50[] = {
    198, 0x1200007, 0x1B270F,
};
s32 D_80092D5C[] = {
    77, 0x1200007, 0xE270F,
};
s32 D_80092D68[] = {
    51, 0x1200007, 0x20270F,
};
s32 D_80092D74[] = {
    137, 0x1200007, 0xB270F,
};
s32 D_80092D80[] = {
    396, 0x1200007, 0xF270F,
};
s32 D_80092D8C[] = {
    203, 0x21C000A, 0x16270F,
};
s32 D_80092D98[] = {
    136, 0x21C000A, 0x9270F,
};
s32 D_80092DA4[] = {
    28, 0x168000A, 0x9270F,
};
s32 D_80092DB0[] = {
    176, 0x180000B, 0x90096,
};
s32 D_80092DBC[] = {
    217, 0x168000A, 0x12270F,
};
s32 D_80092DC8[] = {
    37, 0x168000A, 0x11270F,
};
s32 D_80092DD4[] = {
    10, 0x4380028, 0x2A270F,
};
s32 D_80092DE0[] = {
    50, 0x468002A, 0x2A270F,
};
s32 D_80092DEC[] = {
    35, 0x4200027, 0x1F270F,
};
s32 D_80092DF8[] = {
    197, 0x2100011, 0x32270F,
};
s32 D_80092E04[] = {
    132, 0x2100011, 0x2C270F,
};
s32 D_80092E10[] = {
    110, 0x2280012, 0x1C270F,
};
s32 D_80092E1C[] = {
    32, 0x1500009, 0x2D270F,
};
s32 D_80092E28[] = {
    166, 0x168000A, 0x1E270F,
};
s32 D_80092E34[] = {
    166, 0x168000A, 0x1E270F,
};
s32 D_80092E40[] = {
    206, 0x4500029, 0x93270F,
};
s32 D_80092E4C[] = {
    170, 0x3F00025, 0x100060,
};
s32 D_80092E58[] = {
    223, 0x4080026, 0x13270F,
};
s32 D_80092E64[] = {
    364, 0x4200027, 0x12270F,
};
s32 D_80092E70[] = {
    210, 0x3F00025, 0x1B0078,
};
s32 D_80092E7C[] = {
    14, 0x4080026, 0x14270F,
};
s32 D_80092E88[] = {
    407, 0x4200027, 0x110168,
};
s32 D_80092E94[] = {
    51, 0x3D80024, 0x6D270F,
};
s32 D_80092EA0[] = {
    395, 0x4200027, 0x14270F,
};
s32 D_80092EAC[] = {
    226, 0x4380028, 0x12270F,
};
s32 D_80092EB8[] = {
    126, 0x4380028, 0x12270F,
};
s32 D_80092EC4[] = {
    138, 0x4380028, 0x12270F,
};
s32 D_80092ED0[] = {
    140, 0x4500029, 0x12270F,
};
s32 D_80092EDC[] = {
    405, 0x4080026, 0x19270F,
};
s32 D_80092EE8[] = {
    408, 0x4500029, 0x12270F,
};
s32 D_80092EF4[] = {
    121, 0x4500029, 0x11270F,
};
s32 D_80092F00[] = {
    197, 0x4500029, 0x69270F,
};
s32 D_80092F0C[] = {
    132, 0x4500029, 0x5C270F,
};
s32 D_80092F18[] = {
    110, 0x468002A, 0x3A270F,
};
s32 D_80092F24[] = {
    206, 0x468002A, 0x96270F,
};
s32 D_80092F30[] = {
    51, 0x5D00039, 0xA5270F,
};
s32 D_80092F3C[] = {
    396, 0x5E8003A, 0x4E270F,
};
s32 D_80092F48[] = {
    395, 0x618003C, 0x1E270F,
};
s32 D_80092F54[] = {
    203, 0x69C002A, 0x44270F,
};
s32 D_80092F60[] = {
    136, 0x69C002A, 0x1C270F,
};
s32 D_80092F6C[] = {
    8, 0x468002A, 0x44270F,
};
s32 D_80092F78[] = {
    166, 0x4500029, 0x5C270F,
};
s32 D_80092F84[] = {
    397, 0x480002B, 0x1E270F,
};
s32 D_80092F90[] = {
    39, 0x468002A, 0x18270F,
};
s32 D_80092F9C[] = {
    210, 0x3A80022, 0x190078,
};
s32 D_80092FA8[] = {
    14, 0x3C00023, 0x13270F,
};
s32 D_80092FB4[] = {
    35, 0x3C00023, 0x1C270F,
};
s32 D_80092FC0[] = {
    241, 0x3A80022, 0x16270F,
};
s32 D_80092FCC[] = {
    165, 0x3D80024, 0x11270F,
};
s32 D_80092FD8[] = {
    37, 0x3C00023, 0x2E270F,
};
s32 D_80092FE4[] = {
    223, 0x3C00023, 0x12270F,
};
s32 D_80092FF0[] = {
    364, 0x3D80024, 0x10270F,
};
s32 D_80092FFC[] = {
    122, 0x3C00023, 0x170150,
};
s32 D_80093008[] = {
    143, 0x3C00023, 0x16270F,
};
s32 D_80093014[] = {
    61, 0x3C00023, 0x10270F,
};
s32 D_80093020[] = {
    408, 0x3C00023, 0x10270F,
};
s32 D_8009302C[] = {
    121, 0x3C00023, 0xF270F,
};
s32 D_80093038[] = {
    220, 0x3D80024, 0x14270F,
};
s32 D_80093044[] = {
    221, 0x3D80024, 0xF270F,
};
s32 D_80093050[] = {
    126, 0x3D80024, 0x10270F,
};
s32 D_8009305C[] = {
    8, 0x3A80022, 0x39270F,
};
s32 D_80093068[] = {
    140, 0x3F00025, 0x10270F,
};
s32 D_80093074[] = {
    170, 0x498002C, 0x130060,
};
s32 D_80093080[] = {
    223, 0x498002C, 0x16270F,
};
s32 D_8009308C[] = {
    404, 0x4B0002D, 0x13270F,
};
s32 D_80093098[] = {
    4, 0x498002C, 0x83270F,
};
s32 D_800930A4[] = {
    198, 0x498002C, 0x70270F,
};
s32 D_800930B0[] = {
    424, 0x4B0002D, 0x14270F,
};
s32 D_800930BC[] = {
    210, 0x480002B, 0x1F0078,
};
s32 D_800930C8[] = {
    14, 0x498002C, 0x17270F,
};
s32 D_800930D4[] = {
    269, 0x4B0002D, 0x10270F,
};
s32 D_800930E0[] = {
    397, 0x4B0002D, 0x1F270F,
};
s32 D_800930EC[] = {
    171, 0x4C8002E, 0x10270F,
};
s32 D_800930F8[] = {
    126, 0x498002C, 0x13270F,
};
s32 D_80093104[] = {
    138, 0x4B0002D, 0x14270F,
};
s32 D_80093110[] = {
    212, 0x4B0002D, 0x1D270F,
};
s32 D_8009311C[] = {
    28, 0x498002C, 0x1D270F,
};
s32 D_80093128[] = {
    176, 0x498002C, 0x1C0096,
};
s32 D_80093134[] = {
    229, 0x4C8002E, 0x11270F,
};
s32 D_80093140[] = {
    395, 0x498002C, 0x16270F,
};
s32 D_8009314C[] = {
    226, 0x4B0002D, 0x15270F,
};
s32 D_80093158[] = {
    60, 0x4C8002E, 0x11270F,
};
s32 D_80093164[] = {
    224, 0x4B0002D, 0x13270F,
};
s32 D_80093170[] = {
    225, 0x4C8002E, 0x11270F,
};
s32 D_8009317C[] = {
    419, 0x4B0002D, 0x11270F,
};
s32 D_80093188[] = {
    54, 0x4C8002E, 0x10270F,
};
s32 D_80093194[] = {
    176, 0x5580034, 0x210096,
};
s32 D_800931A0[] = {
    229, 0x5700035, 0x13270F,
};
s32 D_800931AC[] = {
    41, 0x5700035, 0x12270F,
};
s32 D_800931B8[] = {
    203, 0x8040034, 0x53270F,
};
s32 D_800931C4[] = {
    8, 0x5580034, 0x53270F,
};
s32 D_800931D0[] = {
    409, 0x5880036, 0x12270F,
};
s32 D_800931DC[] = {
    206, 0x5580034, 0xB6270F,
};
s32 D_800931E8[] = {
    365, 0x5700035, 0x13270F,
};
s32 D_800931F4[] = {
    197, 0x5580034, 0x82270F,
};
s32 D_80093200[] = {
    132, 0x5580034, 0x72270F,
};
s32 D_8009320C[] = {
    110, 0x5700035, 0x47270F,
};
s32 D_80093218[] = {
    224, 0x5580034, 0x16270F,
};
s32 D_80093224[] = {
    225, 0x5580034, 0x13270F,
};
s32 D_80093230[] = {
    281, 0x5700035, 0x13270F,
};
s32 D_8009323C[] = {
    226, 0x5580034, 0x17270F,
};
s32 D_80093248[] = {
    60, 0x5580034, 0x13270F,
};
s32 D_80093254[] = {
    423, 0x5700035, 0x12270F,
};
s32 D_80093260[] = {
    122, 0x5700035, 0x210150,
};
s32 D_8009326C[] = {
    143, 0x5700035, 0x20270F,
};
s32 D_80093278[] = {
    250, 0x5880036, 0x13270F,
};
s32 D_80093284[] = {
    405, 0x5A00037, 0x24270F,
};
s32 D_80093290[] = {
    425, 0x5D00039, 0x16270F,
};
s32 D_8009329C[] = {
    428, 0x618003C, 0x14270F,
};
s32 D_800932A8[] = {
    364, 0x5700035, 0x17270F,
};
s32 D_800932B4[] = {
    177, 0x5700035, 0x13270F,
};
s32 D_800932C0[] = {
    206, 0x5700035, 0xBA270F,
};
s32 D_800932CC[] = {
    365, 0x5880036, 0x13270F,
};
s32 D_800932D8[] = {
    32, 0x780001, 0x10270F,
};
s32 D_800932E4[] = {
    32, 0x780001, 0x10270F,
};
s32 D_800932F0[] = {
    32, 0x780001, 0x10270F,
};
s32 D_800932FC[] = {
    32, 0x780001, 0x10270F,
};
s32 D_80093308[] = {
    32, 0x780001, 0x10270F,
};
s32 D_80093314[] = {
    32, 0x780001, 0x10270F,
};
s32 D_80093320[] = {
    32, 0x780001, 0x10270F,
};
s32 D_8009332C[] = {
    32, 0x780001, 0x10270F,
};
s32 D_80093338[] = {
    32, 0x780001, 0x10270F,
};
#if VERSION_US
s32 D_80093344[] = {
    32, 0x780001, 0x10270F,
};
#elif VERSION_EU
s32 D_80093344[] = {
    141, 0x11D0005A, 0x27270F,
};
s32 D_800940A4[] = {
    436, 0x12C0005F, 0x2103C0,
};
s32 D_800940B0[] = {
    382, 0x1D400063, 0x1B270F,
};
#endif
s32 D_80093350[] = {
    203, 0x2AC000E, 0x1C270F,
};
s32 D_8009335C[] = {
    51, 0x168000A, 0x28270F,
};
s32 D_80093368[] = {
    32, 0x1080006, 0x23270F,
};
s32 D_80093374[] = {
    449, 0x4200011, 0x10270F,
};
s32 D_80093380[] = {
    451, 0x5D0001A, 0x10270F,
};
s32 D_8009338C[] = {
    452, 0x630001C, 0x10270F,
};
s32 D_80093398[] = {
    453, 0x660001D, 0x10270F,
};
s32 D_800933A4[] = {
    454, 0x630001C, 0x10270F,
};
s32 D_800933B0[] = {
    456, 0x630001C, 0x10270F,
};
s32 D_800933BC[] = {
    455, 0x630001C, 0x10270F,
};
s32 D_800933C8[] = {
    450, 0x4800013, 0x10270F,
};
s32 D_800933D4[] = {
    51, 0xF00005, 0x1B270F,
};
s32 D_800933E0[] = {
    395, 0x1200007, 0x5270F,
};
#if VERSION_US
s32 D_800933EC[] = {
    203, 0x18C0006, 0x10270F,
};
s32 D_800933F8[] = {
    136, 0x3CC0016, 0x10270F,
};
s32 D_80093404[] = {
    8, 0x1080006, 0x10270F,
};
s32 D_80093410[] = {
    166, 0xC00004, 0x10270F,
};
s32 D_8009341C[] = {
    397, 0x2700015, 0x10270F,
};
s32 D_80093428[] = {
    39, 0x2E8001A, 0x10270F,
};
s32 D_80093434[] = {
    210, 0x2580014, 0x100078,
};
s32 D_80093440[] = {
    14, 0x330001D, 0x10270F,
};
s32 D_8009344C[] = {
    35, 0x2280012, 0x10270F,
};
s32 D_80093458[] = {
    241, 0x2B80018, 0x10270F,
};
s32 D_80093464[] = {
    165, 0x3A80022, 0x10270F,
};
s32 D_80093470[] = {
    37, 0x1500009, 0x10270F,
};
s32 D_8009347C[] = {
    223, 0x360001F, 0x10270F,
};
s32 D_80093488[] = {
    364, 0x3C00023, 0x10270F,
};
#elif VERSION_EU
s32 D_800933EC[] = {
    281, 0x480002B, 0x10270F,
};
s32 D_800933F8[] = {
    202, 0x480002B, 0x10270F,
};
s32 D_80093404[] = {
    204, 0x498002C, 0x10270F,
};
s32 D_80093410[] = {
    229, 0x498002C, 0x10270F,
};
s32 D_8009341C[] = {
    24, 0x708002D, 0x10270F,
};
#endif
s32 D_80093494[] = {
    122, 0x2A00017, 0x100150,
};
s32 D_800934A0[] = {
    143, 0x2B80018, 0x10270F,
};
s32 D_800934AC[] = {
    61, 0x3C00023, 0x10270F,
};
s32 D_800934B8[] = {
    408, 0x3C00023, 0x10270F,
};
s32 D_800934C4[] = {
    121, 0x4080026, 0x10270F,
};
s32 D_800934D0[] = {
    220, 0x300001B, 0x10270F,
};
s32 D_800934DC[] = {
    221, 0x4380028, 0x10270F,
};
s32 D_800934E8[] = {
    126, 0x3D80024, 0x10270F,
};
s32 D_800934F4[] = {
    8, 0x1080006, 0x10270F,
};
s32 D_80093500[] = {
    140, 0x3D80024, 0x10270F,
};
s32 D_8009350C[] = {
    170, 0x3D80024, 0x100060,
};
s32 D_80093518[] = {
    223, 0x360001F, 0x10270F,
};
s32 D_80093524[] = {
    404, 0x3F00025, 0x10270F,
};
s32 D_80093530[] = {
    4, 0x900002, 0x10270F,
};
s32 D_8009353C[] = {
    198, 0xA80003, 0x10270F,
};
s32 D_80093548[] = {
    424, 0x3D80024, 0x10270F,
};
s32 D_80093554[] = {
    210, 0x2580014, 0x100078,
};
s32 D_80093560[] = {
    14, 0x330001D, 0x10270F,
};
s32 D_8009356C[] = {
    269, 0x4B0002D, 0x10270F,
};
s32 D_80093578[] = {
    397, 0x2700015, 0x10270F,
};
s32 D_80093584[] = {
    171, 0x4E0002F, 0x10270F,
};
s32 D_80093590[] = {
    126, 0x3D80024, 0x10270F,
};
s32 D_8009359C[] = {
    138, 0x3D80024, 0x10270F,
};
s32 D_800935A8[] = {
    212, 0x2A00017, 0x10270F,
};
s32 D_800935B4[] = {
    28, 0x2880016, 0x10270F,
};
s32 D_800935C0[] = {
    176, 0x2A00017, 0x100096,
};
s32 D_800935CC[] = {
    229, 0x498002C, 0x10270F,
};
s32 D_800935D8[] = {
    395, 0x348001E, 0x10270F,
};
s32 D_800935E4[] = {
    226, 0x3A80022, 0x10270F,
};
s32 D_800935F0[] = {
    60, 0x498002C, 0x10270F,
};
s32 D_800935FC[] = {
    224, 0x3F00025, 0x10270F,
};
s32 D_80093608[] = {
    225, 0x498002C, 0x10270F,
};
s32 D_80093614[] = {
    419, 0x480002B, 0x10270F,
};
s32 D_80093620[] = {
    54, 0x4C8002E, 0x10270F,
};
s32 D_8009362C[] = {
    176, 0x2A00017, 0x100096,
};
s32 D_80093638[] = {
    229, 0x498002C, 0x10270F,
};
s32 D_80093644[] = {
    41, 0x4C8002E, 0x10270F,
};
s32 D_80093650[] = {
    203, 0x18C0006, 0x10270F,
};
s32 D_8009365C[] = {
    8, 0x1080006, 0x10270F,
};
s32 D_80093668[] = {
    409, 0x4E0002F, 0x10270F,
};
s32 D_80093674[] = {
    206, 0x780001, 0x10270F,
};
s32 D_80093680[] = {
    365, 0x4B0002D, 0x10270F,
};
s32 D_8009368C[] = {
    197, 0xA80003, 0x10270F,
};
s32 D_80093698[] = {
    132, 0xC00004, 0x10270F,
};
s32 D_800936A4[] = {
    110, 0x1380008, 0x10270F,
};
s32 D_800936B0[] = {
    224, 0x3F00025, 0x10270F,
};
s32 D_800936BC[] = {
    225, 0x498002C, 0x10270F,
};
s32 D_800936C8[] = {
    281, 0x480002B, 0x10270F,
};
s32 D_800936D4[] = {
    226, 0x3A80022, 0x10270F,
};
s32 D_800936E0[] = {
    60, 0x498002C, 0x10270F,
};
s32 D_800936EC[] = {
    423, 0x4F80030, 0x10270F,
};
s32 D_800936F8[] = {
    122, 0x2A00017, 0x100150,
};
s32 D_80093704[] = {
    143, 0x2B80018, 0x10270F,
};
s32 D_80093710[] = {
    250, 0x4B0002D, 0x10270F,
};
s32 D_8009371C[] = {
    405, 0x2880016, 0x10270F,
};
s32 D_80093728[] = {
    425, 0x4500029, 0x10270F,
};
s32 D_80093734[] = {
    428, 0x4F80030, 0x10270F,
};
s32 D_80093740[] = {
    364, 0x3C00023, 0x10270F,
};
s32 D_8009374C[] = {
    177, 0x4B0002D, 0x10270F,
};
s32 D_80093758[] = {
    206, 0x780001, 0x10270F,
};
s32 D_80093764[] = {
    365, 0x4B0002D, 0x10270F,
};
#if VERSION_US
s32 D_80093770[] = {
    172, 0xF00005, 0x10270F,
};
s32 D_8009377C[] = {
    8, 0x1080006, 0x10270F,
};
s32 D_80093788[] = {
    207, 0x168000A, 0x10270F,
};
s32 D_80093794[] = {
    222, 0xF00005, 0x10270F,
};
s32 D_800937A0[] = {
    77, 0x1500009, 0x10270F,
};
s32 D_800937AC[] = {
    119, 0x2580014, 0x1000C8,
};
s32 D_800937B8[] = {
    400, 0x3900021, 0x10270F,
};
s32 D_800937C4[] = {
    208, 0x330001D, 0x10270F,
};
s32 D_800937D0[] = {
    13, 0x1E00019, 0x10270F,
};
s32 D_800937DC[] = {
    270, 0x480002B, 0x10270F,
};
s32 D_800937E8[] = {
    65, 0x498002C, 0x100128,
};
s32 D_800937F4[] = {
    360, 0x498002C, 0x10270F,
};
s32 D_80093800[] = {
    138, 0x3D80024, 0x10270F,
};
s32 D_8009380C[] = {
    402, 0x6780029, 0x10270F,
};
s32 D_80093818[] = {
    237, 0x498002C, 0x10270F,
};
s32 D_80093824[] = {
    425, 0x4500029, 0x10270F,
};
s32 D_80093830[] = {
    202, 0x480002B, 0x10270F,
};
s32 D_8009383C[] = {
    238, 0x480002B, 0x10270F,
};
s32 D_80093848[] = {
    108, 0x498002C, 0x10270F,
};
s32 D_80093854[] = {
    193, 0x4B0002D, 0x10270F,
};
s32 D_80093860[] = {
    428, 0x4F80030, 0x10270F,
};
s32 D_8009386C[] = {
    190, 0x4F80030, 0x10270F,
};
s32 D_80093878[] = {
    215, 0x5100031, 0x10270F,
};
s32 D_80093884[] = {
    231, 0x5880036, 0x10270F,
};
s32 D_80093890[] = {
    358, 0x330000C, 0x10270F,
};
s32 D_8009389C[] = {
    124, 0x390000E, 0x10270F,
};
s32 D_800938A8[] = {
    356, 0x6F00020, 0x100118,
};
s32 D_800938B4[] = {
    70, 0x6F00020, 0x10270F,
};
#elif VERSION_EU
s32 D_80093770[] = {
    449, 0xC30003C, 0x2F270F,
};
s32 D_8009377C[] = {
    451, 0xC30003C, 0x22270F,
};
s32 D_80093788[] = {
    450, 0xD200041, 0x2F270F,
};
s32 D_80093794[] = {
    453, 0xC30003C, 0x1F270F,
};
s32 D_800937A0[] = {
    358, 0xE100046, 0x47270F,
};
s32 D_800937AC[] = {
    124, 0xF00004B, 0x43270F,
};
s32 D_800937B8[] = {
    237, 0xFF00050, 0x1C270F,
};
s32 D_800937C4[] = {
    425, 0xA8C0046, 0x1A270F,
};
s32 D_800937D0[] = {
    437, 0x1680004B, 0x1E0028,
};
s32 D_800937DC[] = {
    337, 0xFF00050, 0x1E270F,
};
s32 D_800937E8[] = {
    193, 0xA8C0046, 0x18270F,
};
s32 D_800937F4[] = {
    432, 0xB40004B, 0x16270F,
};
s32 D_80093800[] = {
    356, 0xFF00050, 0x250118,
};
s32 D_8009380C[] = {
    215, 0xA8C0046, 0x16270F,
};
s32 D_80093818[] = {
    70, 0xF00004B, 0x23270F,
};
s32 D_80093824[] = {
    24, 0x17E80050, 0x1B270F,
};
s32 D_80093830[] = {
    452, 0xC30003C, 0x20270F,
};
s32 D_8009383C[] = {
    454, 0xE100046, 0x24270F,
};
s32 D_80093848[] = {
    455, 0xE100046, 0x24270F,
};
s32 D_80093854[] = {
    456, 0x6F00046, 0x10270F,
};
#endif
s32 D_800938C0[] = {
    141, 0x7500022, 0x10270F,
};
s32 D_800938CC[] = {
    337, 0x8700028, 0x10270F,
};
s32 D_800938D8[] = {
    436, 0x930002C, 0x1003C0,
};
#if VERSION_US
s32 D_800938E4[] = {
    443, 0x960002D, 0x10270F,
};
s32 D_800938F0[] = {
    444, 0x990002E, 0x10270F,
};
s32 D_800938FC[] = {
    447, 0x9C0002F, 0x10270F,
};
s32 D_80093908[] = {
    445, 0xB400037, 0x10270F,
};
s32 D_80093914[] = {
    446, 0xBA00039, 0x100008,
};
s32 D_80093920[] = {
    448, 0xAE00035, 0x10270F,
};
#elif VERSION_EU
s32 D_800938E4[] = {
    443, 0xD200041, 0x16270F,
};
s32 D_800938F0[] = {
    444, 0xD200041, 0x16270F,
};
s32 D_800938FC[] = {
    447, 0xE100046, 0x17270F,
};
s32 D_80093908[] = {
    445, 0xE100046, 0x14270F,
};
s32 D_80093914[] = {
    446, 0xF00004B, 0x150008,
};
s32 D_80093920[] = {
    448, 0xF00004B, 0x16270F,
};
#endif
s32 D_8009392C[] = {
    465, 0x318001C, 0x10270F,
};
s32 D_80093938[] = {
    436, 0x3C0000F, 0x703C0,
};
s32 D_80093944[] = {
    442, 0x13B00041, 0x10270F,
};
s32 D_80093950[] = {
    466, 0xE100046, 0x10270F,
};
s32 D_8009395C[] = {
    467, 0x15180046, 0x10270F,
};
s32 D_80093968[] = {
    466, 0xE100046, 0x10270F,
};
s32 D_80093974[] = {
    467, 0x15180046, 0x10270F,
};
s32 D_80093980[] = {
    457, 0x1200007, 0x10270F,
};
s32 D_8009398C[] = {
    458, 0x198000C, 0x10270F,
};
s32 D_80093998[] = {
    459, 0x2100011, 0x10270F,
};
s32 D_800939A4[] = {
    460, 0x300001B, 0x10270F,
};
s32 D_800939B0[] = {
    461, 0x3F00025, 0x10270F,
};
s32 D_800939BC[] = {
    462, 0x468002A, 0x10270F,
};
s32 D_800939C8[] = {
    463, 0x4E0002F, 0x10270F,
};
s32 D_800939D4[] = {
    464, 0x4E0002F, 0x10270F,
};
#if VERSION_US
s32 D_800939E0[] = {
    (s32)D_800920A8, (s32)D_800920A8, (s32)D_800920A8, 0,
    0, 0, 0, (s32)D_800920B4,
    (s32)D_800920A8, (s32)D_800920A8, 512, 0x10101,
    0, 256, (s32)D_800920C0, (s32)D_800920A8,
    (s32)D_800920A8, 512, 0x10101, 0,
    256, (s32)D_800920CC, (s32)D_800920D8, (s32)D_800920E4,
    512, 0x10101, 0, 256,
    (s32)D_800920F0, (s32)D_800920FC, (s32)D_80092108, 639,
    0x10101, 0, 256, (s32)D_80092114,
    (s32)D_80092120, (s32)D_800920A8, 512, 0x10100,
    0, 256, (s32)D_8009212C, (s32)D_80092138,
    (s32)D_80092144, 0x1000200, 0x10101, 0,
    256, (s32)D_80092150, (s32)D_800920A8, (s32)D_800920A8,
    0x1000200, 0x10101, 0, 256,
    (s32)D_8009215C, (s32)D_800920A8, (s32)D_800920A8, 0x1000200,
    0x10001, 0, 256, (s32)D_80092168,
    (s32)D_800920A8, (s32)D_800920A8, 0x1000200, 0x10101,
    0x1010000, 257, (s32)D_80092174, (s32)D_80092180,
    (s32)D_8009218C, 0x1010200, 0x10101, 0x1010100,
    257, (s32)D_80092198, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x10101, 0, 256,
    (s32)D_800921A4, (s32)D_800920A8, (s32)D_800920A8, 0x1000200,
    0x10100, 0x1010000, 257, (s32)D_800921B0,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x10101,
    0, 256, (s32)D_800921BC, (s32)D_800921C8,
    (s32)D_800921D4, 0x1000200, 0x10101, 0,
    256, (s32)D_800921E0, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010001, 257,
    (s32)D_800921EC, (s32)D_800921F8, (s32)D_80092204, 0x100027F,
    0x10101, 0, 256, (s32)D_80092210,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x10101,
    0, 256, (s32)D_8009221C, (s32)D_80092228,
    (s32)D_80092234, 0x1000200, 0x10101, 0,
    256, (s32)D_80092240, (s32)D_8009224C, (s32)D_80092258,
    512, 0x10001, 0, 256,
    (s32)D_80092264, (s32)D_80092270, (s32)D_8009227C, 512,
    0x10001, 0, 256, (s32)D_80092288,
    (s32)D_80092294, (s32)D_800922A0, 512, 0x10001,
    0, 256, (s32)D_800922AC, (s32)D_800922B8,
    (s32)D_800922C4, 0x10200, 0x10101, 0,
    256, (s32)D_800922D0, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 1, 256,
    (s32)D_800922DC, (s32)D_800920A8, (s32)D_800920A8, 512,
    0x10000, 0, 256, (s32)D_800922E8,
    (s32)D_800922F4, (s32)D_80092300, 0x1010200, 0x10101,
    0, 256, (s32)D_8009230C, (s32)D_80092318,
    (s32)D_80092324, 0x1010200, 0x10101, 0x1010000,
    257, (s32)D_80092330, (s32)D_8009233C, (s32)D_80092348,
    512, 0x10001, 0, 256,
    (s32)D_80092354, (s32)D_80092360, (s32)D_8009236C, 512,
    0x10001, 0, 256, (s32)D_80092378,
    (s32)D_80092384, (s32)D_80092390, 512, 0x10001,
    0, 256, (s32)D_8009239C, (s32)D_800920A8,
    (s32)D_800920A8, 0x101027F, 0x1010101, 0x1010101,
    257, (s32)D_800923A8, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x10101, 0x1010000, 257,
    (s32)D_800923B4, (s32)D_800923C0, (s32)D_800923CC, 0x1010200,
    0x1010101, 0x1010001, 257, (s32)D_800923D8,
    (s32)D_800923E4, (s32)D_800923F0, 0x1010200, 0x1010101,
    0x1000101, 256, (s32)D_800923FC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092408, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092414, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092420,
    (s32)D_800920A8, (s32)D_800920A8, 268, 0,
    0, 0, (s32)D_8009242C, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 0,
    0, (s32)D_80092438, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092444, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092450,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009245C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092468, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092474, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092480,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009248C, (s32)D_800920A8,
    (s32)D_800920A8, 260, 0, 0,
    0, (s32)D_80092498, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800924A4, (s32)D_800920A8, (s32)D_800920A8, 272,
    0, 0, 0, (s32)D_800924B0,
    (s32)D_800920A8, (s32)D_800920A8, 288, 0,
    0, 0, (s32)D_800924BC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800924C8, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_800924D4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800924E0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800924EC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800924F8, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092504, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092510,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_8009251C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092528, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092534, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092540,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009254C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092558, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092564, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092570,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_8009257C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092588, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092594, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_800925A0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800925AC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800925B8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800925C4, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_800925D0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800925DC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800925E8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800925F4, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092600,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009260C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092618, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092624, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092630,
    (s32)D_800920A8, (s32)D_800920A8, 268, 0,
    0, 0, (s32)D_8009263C, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 0,
    0, (s32)D_80092648, (s32)D_800920A8, (s32)D_800920A8,
    288, 0, 0, 0,
    (s32)D_80092654, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_80092660,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009266C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092678, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092684, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092690,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_8009269C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800926A8, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_800926B4, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_800926C0,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_800926CC, (s32)D_800920A8,
    (s32)D_800920A8, 260, 0, 0,
    0, (s32)D_800926D8, (s32)D_800920A8, (s32)D_800920A8,
    288, 0, 0, 0,
    (s32)D_800926E4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800926F0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800926FC, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 256,
    0, (s32)D_80092708, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092714, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092720,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009272C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092738, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 0, 0,
    (s32)D_80092744, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092750,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009275C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092768, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 0, 0,
    (s32)D_80092774, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092780,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009278C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092798, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 0, 0,
    (s32)D_800927A4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800927B0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800927BC, (s32)D_800920A8,
    (s32)D_800920A8, 272, 0, 0,
    0, (s32)D_800927C8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800927D4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800927E0,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_800927EC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800927F8, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092804, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092810,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009281C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092828, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092834, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_80092840,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009284C, (s32)D_800920A8,
    (s32)D_800920A8, 260, 0, 0,
    0, (s32)D_80092858, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092864, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092870,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009287C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092888, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 256, 0,
    (s32)D_80092894, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800928A0,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_800928AC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800928B8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800928C4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800928D0,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_800928DC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800928E8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800928F4, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092900,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_8009290C, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 0,
    0, (s32)D_80092918, (s32)D_800920A8, (s32)D_800920A8,
    256, 0, 0, 0,
    (s32)D_80092924, (s32)D_800920A8, (s32)D_800920A8, 383,
    0, 0, 0, (s32)D_80092930,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_8009293C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092948, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092954, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092960,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009296C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092978, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092984, (s32)D_800920A8, (s32)D_800920A8, 288,
    0, 0, 0, (s32)D_80092990,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_8009299C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800929A8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800929B4, (s32)D_800920A8, (s32)D_800920A8, 288,
    0, 0, 0, (s32)D_800929C0,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_800929CC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800929D8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800929E4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800929F0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800929FC, (s32)D_800920A8,
    (s32)D_800920A8, 288, 0, 0,
    0, (s32)D_80092A08, (s32)D_800920A8, (s32)D_800920A8,
    256, 0, 0, 0,
    (s32)D_80092A14, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092A20,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_80092A2C, (s32)D_800920A8,
    (s32)D_800920A8, 276, 0, 0,
    0, (s32)D_80092A38, (s32)D_800920A8, (s32)D_800920A8,
    280, 0, 0, 0,
    (s32)D_80092A44, (s32)D_800920A8, (s32)D_800920A8, 284,
    0, 0, 0, (s32)D_80092A50,
    (s32)D_800920A8, (s32)D_800920A8, 288, 0,
    0, 0, (s32)D_80092A5C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092A68, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092A74, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092A80,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_80092A8C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092A98, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 256, 0,
    (s32)D_80092AA4, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092AB0,
    (s32)D_800920A8, (s32)D_800920A8, 288, 0,
    256, 0, (s32)D_80092ABC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092AC8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092AD4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 256, 0, (s32)D_80092AE0,
    (s32)D_800920A8, (s32)D_800920A8, 268, 0,
    0, 0, (s32)D_80092AEC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092AF8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092B04, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092B10,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_80092B1C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 256,
    0, (s32)D_80092B28, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092B34, (s32)D_80092B40, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092B4C,
    (s32)D_80092B58, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_80092B64, (s32)D_80092B70,
    (s32)D_80092B7C, 768, 0, 0,
    256, (s32)D_80092B88, (s32)D_800920A8, (s32)D_800920A8,
    0x1000300, 0x10101, 0, 256,
    (s32)D_80092B94, (s32)D_80092BA0, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092BAC,
    (s32)D_80092BB8, (s32)D_80092BC4, 768, 0,
    0, 256, (s32)D_80092BD0, (s32)D_80092BDC,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80092BE8, (s32)D_80092BF4, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092C00, (s32)D_80092C0C, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092C18,
    (s32)D_80092C24, (s32)D_80092C30, 768, 0,
    0, 256, (s32)D_80092C3C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1000300, 0x10101, 0,
    256, (s32)D_80092C48, (s32)D_80092C54, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092C60, (s32)D_800920A8, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092C6C,
    (s32)D_80092C78, (s32)D_80092C84, 768, 0,
    0, 256, (s32)D_80092C90, (s32)D_80092C9C,
    (s32)D_80092CA8, 768, 0, 0,
    256, (s32)D_80092CB4, (s32)D_80092CC0, (s32)D_80092CCC,
    768, 0, 0, 256,
    (s32)D_80092CD8, (s32)D_80092CE4, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092CF0,
    (s32)D_80092CFC, (s32)D_80092D08, 768, 0,
    0, 256, (s32)D_80092D14, (s32)D_800920A8,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80092D20, (s32)D_80092D2C, (s32)D_80092D38,
    768, 0, 0, 256,
    (s32)D_80092D44, (s32)D_80092D50, (s32)D_80092D5C, 768,
    0, 0, 256, (s32)D_80092D68,
    (s32)D_80092D74, (s32)D_80092D80, 768, 0,
    0, 256, (s32)D_80092D8C, (s32)D_80092D98,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80092DA4, (s32)D_80092DB0, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092DBC, (s32)D_80092DC8, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092DD4,
    (s32)D_80092DE0, (s32)D_80092DEC, 768, 0,
    0, 256, (s32)D_80092DF8, (s32)D_80092E04,
    (s32)D_80092E10, 768, 0, 0,
    256, (s32)D_80092E1C, (s32)D_80092E28, (s32)D_80092E34,
    768, 0, 0, 256,
    (s32)D_80092E40, (s32)D_800920A8, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092E4C,
    (s32)D_80092E58, (s32)D_80092E64, 768, 0,
    0, 256, (s32)D_80092E70, (s32)D_80092E7C,
    (s32)D_80092E88, 768, 0, 0,
    256, (s32)D_80092E94, (s32)D_80092EA0, (s32)D_80092EAC,
    768, 0, 0, 256,
    (s32)D_80092EB8, (s32)D_80092EC4, (s32)D_80092ED0, 768,
    0, 0, 256, (s32)D_80092EDC,
    (s32)D_80092EE8, (s32)D_80092EF4, 768, 0,
    0, 256, (s32)D_80092F00, (s32)D_80092F0C,
    (s32)D_80092F18, 768, 0, 0,
    256, (s32)D_80092F24, (s32)D_800920A8, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092F30, (s32)D_80092F3C, (s32)D_80092F48, 768,
    0, 0, 256, (s32)D_80092F54,
    (s32)D_80092F60, (s32)D_80092F6C, 768, 0,
    0, 256, (s32)D_80092F78, (s32)D_80092F84,
    (s32)D_80092F90, 768, 0, 0,
    256, (s32)D_80092F9C, (s32)D_80092FA8, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092FB4, (s32)D_80092FC0, (s32)D_80092FCC, 768,
    0, 0, 256, (s32)D_80092FD8,
    (s32)D_80092FE4, (s32)D_80092FF0, 768, 0,
    0, 256, (s32)D_80092FFC, (s32)D_80093008,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80093014, (s32)D_80093020, (s32)D_8009302C,
    768, 0, 0, 256,
    (s32)D_80093038, (s32)D_80093044, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80093050,
    (s32)D_8009305C, (s32)D_80093068, 768, 0,
    0, 256, (s32)D_80093074, (s32)D_80093080,
    (s32)D_8009308C, 768, 0, 0,
    256, (s32)D_80093098, (s32)D_800930A4, (s32)D_800930B0,
    768, 0, 0, 256,
    (s32)D_800930BC, (s32)D_800930C8, (s32)D_800930D4, 768,
    0, 0, 256, (s32)D_800930E0,
    (s32)D_800930EC, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_800930F8, (s32)D_80093104,
    (s32)D_80093110, 768, 0, 0,
    256, (s32)D_8009311C, (s32)D_80093128, (s32)D_80093134,
    768, 0, 0, 256,
    (s32)D_80093140, (s32)D_8009314C, (s32)D_80093158, 768,
    0, 0, 256, (s32)D_80093164,
    (s32)D_80093170, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_8009317C, (s32)D_80093188,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80093194, (s32)D_800931A0, (s32)D_800931AC,
    768, 0, 0, 256,
    (s32)D_800931B8, (s32)D_800931C4, (s32)D_800931D0, 768,
    0, 0, 256, (s32)D_800931DC,
    (s32)D_800931E8, (s32)D_800920A8, 768, 0,
    256, 256, (s32)D_800931F4, (s32)D_80093200,
    (s32)D_8009320C, 768, 0, 0,
    256, (s32)D_80093218, (s32)D_80093224, (s32)D_80093230,
    768, 0, 0, 256,
    (s32)D_8009323C, (s32)D_80093248, (s32)D_80093254, 768,
    0, 0, 256, (s32)D_80093260,
    (s32)D_8009326C, (s32)D_80093278, 768, 0,
    0, 256, (s32)D_80093284, (s32)D_80093290,
    (s32)D_8009329C, 0x1010300, 0x1010101, 0x1010001,
    257, (s32)D_800932A8, (s32)D_800932B4, (s32)D_800920A8,
    768, 0, 256, 256,
    (s32)D_800932C0, (s32)D_800932CC, (s32)D_800920A8, 768,
    0, 256, 256, (s32)D_800932D8,
    (s32)D_800920A8, (s32)D_800920A8, 1024, 0,
    0, 256, (s32)D_800932E4, (s32)D_800920A8,
    (s32)D_800920A8, 1024, 0, 0,
    256, (s32)D_800932F0, (s32)D_800920A8, (s32)D_800920A8,
    1024, 0, 0, 256,
    (s32)D_800932FC, (s32)D_800920A8, (s32)D_800920A8, 1024,
    0, 0, 256, (s32)D_80093308,
    (s32)D_800920A8, (s32)D_800920A8, 1024, 0,
    0, 256, (s32)D_80093314, (s32)D_800920A8,
    (s32)D_800920A8, 1024, 0, 0,
    256, (s32)D_80093320, (s32)D_800920A8, (s32)D_800920A8,
    1024, 0, 0, 256,
    (s32)D_8009332C, (s32)D_800920A8, (s32)D_800920A8, 1024,
    0, 0, 256, (s32)D_80093338,
    (s32)D_800920A8, (s32)D_800920A8, 1024, 0,
    0, 256, (s32)D_80093344, (s32)D_800920A8,
    (s32)D_800920A8, 1024, 0, 0,
    256, (s32)D_80093350, (s32)D_8009335C, (s32)D_80093368,
    512, 0x10000, 0, 256,
    (s32)D_80093374, (s32)D_800920A8, (s32)D_800920A8, 512,
    0, 0, 256, (s32)D_80093380,
    (s32)D_800920A8, (s32)D_800920A8, 512, 0,
    0, 256, (s32)D_8009338C, (s32)D_800920A8,
    (s32)D_800920A8, 512, 0, 0,
    256, (s32)D_80093398, (s32)D_800920A8, (s32)D_800920A8,
    512, 0, 0, 256,
    (s32)D_800933A4, (s32)D_800920A8, (s32)D_800920A8, 512,
    0, 0, 256, (s32)D_800933B0,
    (s32)D_800920A8, (s32)D_800920A8, 512, 0,
    0, 256, (s32)D_800933BC, (s32)D_800920A8,
    (s32)D_800920A8, 512, 0, 0,
    256, (s32)D_800933C8, (s32)D_800920A8, (s32)D_800920A8,
    512, 0, 0, 256,
    (s32)D_800933D4, (s32)D_800933E0, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_800933EC,
    (s32)D_800933F8, (s32)D_80093404, 768, 0,
    0, 256, (s32)D_80093410, (s32)D_8009341C,
    (s32)D_80093428, 768, 0, 0,
    256, (s32)D_80093434, (s32)D_80093440, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_8009344C, (s32)D_80093458, (s32)D_80093464, 768,
    0, 0, 256, (s32)D_80093470,
    (s32)D_8009347C, (s32)D_80093488, 768, 0,
    0, 256, (s32)D_80093494, (s32)D_800934A0,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_800934AC, (s32)D_800934B8, (s32)D_800934C4,
    768, 0, 0, 256,
    (s32)D_800934D0, (s32)D_800934DC, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_800934E8,
    (s32)D_800934F4, (s32)D_80093500, 768, 0,
    0, 256, (s32)D_8009350C, (s32)D_80093518,
    (s32)D_80093524, 768, 0, 0,
    256, (s32)D_80093530, (s32)D_8009353C, (s32)D_80093548,
    768, 0, 0, 256,
    (s32)D_80093554, (s32)D_80093560, (s32)D_8009356C, 768,
    0, 0, 256, (s32)D_80093578,
    (s32)D_80093584, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_80093590, (s32)D_8009359C,
    (s32)D_800935A8, 768, 0, 0,
    256, (s32)D_800935B4, (s32)D_800935C0, (s32)D_800935CC,
    768, 0, 0, 256,
    (s32)D_800935D8, (s32)D_800935E4, (s32)D_800935F0, 768,
    0, 0, 256, (s32)D_800935FC,
    (s32)D_80093608, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_80093614, (s32)D_80093620,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_8009362C, (s32)D_80093638, (s32)D_80093644,
    768, 0, 0, 256,
    (s32)D_80093650, (s32)D_8009365C, (s32)D_80093668, 768,
    0, 0, 256, (s32)D_80093674,
    (s32)D_80093680, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_8009368C, (s32)D_80093698,
    (s32)D_800936A4, 768, 0, 0,
    256, (s32)D_800936B0, (s32)D_800936BC, (s32)D_800936C8,
    768, 0, 0, 256,
    (s32)D_800936D4, (s32)D_800936E0, (s32)D_800936EC, 768,
    0, 0, 256, (s32)D_800936F8,
    (s32)D_80093704, (s32)D_80093710, 768, 0,
    0, 256, (s32)D_8009371C, (s32)D_80093728,
    (s32)D_80093734, 768, 0, 0,
    256, (s32)D_80093740, (s32)D_8009374C, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80093758, (s32)D_80093764, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80093770,
    (s32)D_8009377C, (s32)D_80093788, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_80093794, (s32)D_800937A0,
    (s32)D_800937AC, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_800937B8, (s32)D_800937C4, (s32)D_800937D0,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_800937DC, (s32)D_800937E8, (s32)D_800937F4, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_80093800,
    (s32)D_8009380C, (s32)D_80093818, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_80093824, (s32)D_80093830,
    (s32)D_8009383C, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_80093848, (s32)D_80093854, (s32)D_80093860,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_8009386C, (s32)D_80093878, (s32)D_80093884, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_80093890,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_8009389C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_800938A8, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_800938B4, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_800938C0,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_800938CC, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_800938D8, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_800938E4, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_800938F0,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_800938FC, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_80093908, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_80093914, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_80093920,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_8009392C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010300, 0x1010101, 0x1010101,
    257, (s32)D_80093938, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_80093944, (s32)D_80093950, (s32)D_8009395C, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_80093968,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_80093974, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_80093980, (s32)D_800920A8, (s32)D_800920A8,
    0x1000508, 257, 256, 0,
    (s32)D_8009398C, (s32)D_800920A8, (s32)D_800920A8, 0x1000508,
    257, 256, 0, (s32)D_80093998,
    (s32)D_800920A8, (s32)D_800920A8, 0x1000510, 257,
    256, 0, (s32)D_800939A4, (s32)D_800920A8,
    (s32)D_800920A8, 0x1000510, 257, 256,
    0, (s32)D_800939B0, (s32)D_800920A8, (s32)D_800920A8,
    0x1000518, 257, 256, 0,
    (s32)D_800939BC, (s32)D_800920A8, (s32)D_800920A8, 0x1000518,
    257, 256, 0, (s32)D_800939C8,
    (s32)D_800920A8, (s32)D_800920A8, 0x1000520, 257,
    256, 0, (s32)D_800939D4, (s32)D_800920A8,
    (s32)D_800920A8, 0x1000520, 257, 256,
    0,
};
#elif VERSION_EU
s32 D_800939E0[] = {
    (s32)D_800920A8, (s32)D_800920A8, (s32)D_800920A8, 0,
    0, 0, 0, (s32)D_800920B4,
    (s32)D_800920A8, (s32)D_800920A8, 512, 0x10101,
    0, 256, (s32)D_800920C0, (s32)D_800920A8,
    (s32)D_800920A8, 512, 0x10101, 0,
    256, (s32)D_800920CC, (s32)D_800920D8, (s32)D_800920E4,
    512, 0x10101, 0, 256,
    (s32)D_800920F0, (s32)D_800920FC, (s32)D_80092108, 639,
    0x10101, 0, 256, (s32)D_80092114,
    (s32)D_80092120, (s32)D_800920A8, 512, 0x10100,
    0, 256, (s32)D_8009212C, (s32)D_80092138,
    (s32)D_80092144, 0x1000200, 0x10101, 0,
    256, (s32)D_80092150, (s32)D_800920A8, (s32)D_800920A8,
    0x1000200, 0x10101, 0, 256,
    (s32)D_8009215C, (s32)D_800920A8, (s32)D_800920A8, 0x1000200,
    0x10001, 0, 256, (s32)D_80092168,
    (s32)D_800920A8, (s32)D_800920A8, 0x1000200, 0x10101,
    0x1010000, 257, (s32)D_80092174, (s32)D_80092180,
    (s32)D_8009218C, 0x1010200, 0x10101, 0x1010100,
    257, (s32)D_80092198, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x10101, 0, 256,
    (s32)D_800921A4, (s32)D_800920A8, (s32)D_800920A8, 0x1000200,
    0x10100, 0x1010000, 257, (s32)D_800921B0,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x10101,
    0, 256, (s32)D_800921BC, (s32)D_800921C8,
    (s32)D_800921D4, 0x1000200, 0x10101, 0,
    256, (s32)D_800921E0, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010001, 257,
    (s32)D_800921EC, (s32)D_800921F8, (s32)D_80092204, 0x100027F,
    0x10101, 0, 256, (s32)D_80092210,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x10101,
    0, 256, (s32)D_8009221C, (s32)D_80092228,
    (s32)D_80092234, 0x1000200, 0x10101, 0,
    256, (s32)D_80092240, (s32)D_8009224C, (s32)D_80092258,
    512, 0x10001, 0, 256,
    (s32)D_80092264, (s32)D_80092270, (s32)D_8009227C, 512,
    0x10001, 0, 256, (s32)D_80092288,
    (s32)D_80092294, (s32)D_800922A0, 512, 0x10001,
    0, 256, (s32)D_800922AC, (s32)D_800922B8,
    (s32)D_800922C4, 0x10200, 0x10101, 0,
    256, (s32)D_800922D0, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 1, 256,
    (s32)D_800922DC, (s32)D_800920A8, (s32)D_800920A8, 512,
    0x10000, 0, 256, (s32)D_800922E8,
    (s32)D_800922F4, (s32)D_80092300, 0x1010200, 0x10101,
    0, 256, (s32)D_8009230C, (s32)D_80092318,
    (s32)D_80092324, 0x1010200, 0x10101, 0x1010000,
    257, (s32)D_80092330, (s32)D_8009233C, (s32)D_80092348,
    512, 0x10001, 0, 256,
    (s32)D_80092354, (s32)D_80092360, (s32)D_8009236C, 512,
    0x10001, 0, 256, (s32)D_80092378,
    (s32)D_80092384, (s32)D_80092390, 512, 0x10001,
    0, 256, (s32)D_8009239C, (s32)D_800920A8,
    (s32)D_800920A8, 0x101027F, 0x1010101, 0x1010101,
    257, (s32)D_800923A8, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x10101, 0x1010000, 257,
    (s32)D_800923B4, (s32)D_800923C0, (s32)D_800923CC, 0x1010200,
    0x1010101, 0x1010001, 257, (s32)D_800923D8,
    (s32)D_800923E4, (s32)D_800923F0, 0x1010200, 0x1010101,
    0x1000101, 256, (s32)D_800923FC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092408, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092414, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092420,
    (s32)D_800920A8, (s32)D_800920A8, 268, 0,
    0, 0, (s32)D_8009242C, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 0,
    0, (s32)D_80092438, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092444, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092450,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009245C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092468, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092474, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092480,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009248C, (s32)D_800920A8,
    (s32)D_800920A8, 260, 0, 0,
    0, (s32)D_80092498, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800924A4, (s32)D_800920A8, (s32)D_800920A8, 272,
    0, 0, 0, (s32)D_800924B0,
    (s32)D_800920A8, (s32)D_800920A8, 288, 0,
    0, 0, (s32)D_800924BC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800924C8, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_800924D4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800924E0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800924EC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800924F8, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092504, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092510,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_8009251C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092528, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092534, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092540,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009254C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092558, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092564, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092570,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_8009257C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092588, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092594, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_800925A0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800925AC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800925B8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800925C4, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_800925D0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800925DC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800925E8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800925F4, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092600,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009260C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092618, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092624, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092630,
    (s32)D_800920A8, (s32)D_800920A8, 268, 0,
    0, 0, (s32)D_8009263C, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 0,
    0, (s32)D_80092648, (s32)D_800920A8, (s32)D_800920A8,
    288, 0, 0, 0,
    (s32)D_80092654, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_80092660,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009266C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092678, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092684, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092690,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_8009269C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800926A8, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_800926B4, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_800926C0,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_800926CC, (s32)D_800920A8,
    (s32)D_800920A8, 260, 0, 0,
    0, (s32)D_800926D8, (s32)D_800920A8, (s32)D_800920A8,
    288, 0, 0, 0,
    (s32)D_800926E4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800926F0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800926FC, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 256,
    0, (s32)D_80092708, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092714, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092720,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009272C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092738, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 0, 0,
    (s32)D_80092744, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092750,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009275C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092768, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 0, 0,
    (s32)D_80092774, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092780,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009278C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092798, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 0, 0,
    (s32)D_800927A4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800927B0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800927BC, (s32)D_800920A8,
    (s32)D_800920A8, 272, 0, 0,
    0, (s32)D_800927C8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800927D4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800927E0,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_800927EC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800927F8, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092804, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092810,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009281C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092828, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092834, (s32)D_800920A8, (s32)D_800920A8, 268,
    0, 0, 0, (s32)D_80092840,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009284C, (s32)D_800920A8,
    (s32)D_800920A8, 260, 0, 0,
    0, (s32)D_80092858, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092864, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092870,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009287C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092888, (s32)D_800920A8, (s32)D_800920A8,
    268, 0, 256, 0,
    (s32)D_80092894, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800928A0,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_800928AC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800928B8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800928C4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800928D0,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_800928DC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800928E8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800928F4, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092900,
    (s32)D_800920A8, (s32)D_800920A8, 256, 0,
    0, 0, (s32)D_8009290C, (s32)D_800920A8,
    (s32)D_800920A8, 268, 0, 0,
    0, (s32)D_80092918, (s32)D_800920A8, (s32)D_800920A8,
    256, 0, 0, 0,
    (s32)D_80092924, (s32)D_800920A8, (s32)D_800920A8, 383,
    0, 0, 0, (s32)D_80092930,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_8009293C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092948, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092954, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_80092960,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_8009296C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092978, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 0, 0,
    (s32)D_80092984, (s32)D_800920A8, (s32)D_800920A8, 288,
    0, 0, 0, (s32)D_80092990,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_8009299C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_800929A8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800929B4, (s32)D_800920A8, (s32)D_800920A8, 288,
    0, 0, 0, (s32)D_800929C0,
    (s32)D_800920A8, (s32)D_800920A8, 260, 0,
    0, 0, (s32)D_800929CC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_800929D8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_800929E4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 0, 0, (s32)D_800929F0,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_800929FC, (s32)D_800920A8,
    (s32)D_800920A8, 288, 0, 0,
    0, (s32)D_80092A08, (s32)D_800920A8, (s32)D_800920A8,
    256, 0, 0, 0,
    (s32)D_80092A14, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092A20,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_80092A2C, (s32)D_800920A8,
    (s32)D_800920A8, 276, 0, 0,
    0, (s32)D_80092A38, (s32)D_800920A8, (s32)D_800920A8,
    280, 0, 0, 0,
    (s32)D_80092A44, (s32)D_800920A8, (s32)D_800920A8, 284,
    0, 0, 0, (s32)D_80092A50,
    (s32)D_800920A8, (s32)D_800920A8, 288, 0,
    0, 0, (s32)D_80092A5C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092A68, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092A74, (s32)D_800920A8, (s32)D_800920A8, 256,
    0, 0, 0, (s32)D_80092A80,
    (s32)D_800920A8, (s32)D_800920A8, 272, 0,
    0, 0, (s32)D_80092A8C, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092A98, (s32)D_800920A8, (s32)D_800920A8,
    272, 0, 256, 0,
    (s32)D_80092AA4, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092AB0,
    (s32)D_800920A8, (s32)D_800920A8, 288, 0,
    256, 0, (s32)D_80092ABC, (s32)D_800920A8,
    (s32)D_800920A8, 256, 0, 0,
    0, (s32)D_80092AC8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092AD4, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 256, 0, (s32)D_80092AE0,
    (s32)D_800920A8, (s32)D_800920A8, 268, 0,
    0, 0, (s32)D_80092AEC, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 0,
    0, (s32)D_80092AF8, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 0, 0,
    (s32)D_80092B04, (s32)D_800920A8, (s32)D_800920A8, 260,
    0, 0, 0, (s32)D_80092B10,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    0, 0, (s32)D_80092B1C, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 256,
    0, (s32)D_80092B28, (s32)D_800920A8, (s32)D_800920A8,
    260, 0, 0, 0,
    (s32)D_80092B34, (s32)D_80092B40, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092B4C,
    (s32)D_80092B58, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_80092B64, (s32)D_80092B70,
    (s32)D_80092B7C, 768, 0, 0,
    256, (s32)D_80092B88, (s32)D_800920A8, (s32)D_800920A8,
    0x1000300, 0x10101, 0, 256,
    (s32)D_80092B94, (s32)D_80092BA0, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092BAC,
    (s32)D_80092BB8, (s32)D_80092BC4, 768, 0,
    0, 256, (s32)D_80092BD0, (s32)D_80092BDC,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80092BE8, (s32)D_80092BF4, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092C00, (s32)D_80092C0C, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092C18,
    (s32)D_80092C24, (s32)D_80092C30, 768, 0,
    0, 256, (s32)D_80092C3C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1000300, 0x10101, 0,
    256, (s32)D_80092C48, (s32)D_80092C54, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092C60, (s32)D_800920A8, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092C6C,
    (s32)D_80092C78, (s32)D_80092C84, 768, 0,
    0, 256, (s32)D_80092C90, (s32)D_80092C9C,
    (s32)D_80092CA8, 768, 0, 0,
    256, (s32)D_80092CB4, (s32)D_80092CC0, (s32)D_80092CCC,
    768, 0, 0, 256,
    (s32)D_80092CD8, (s32)D_80092CE4, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092CF0,
    (s32)D_80092CFC, (s32)D_80092D08, 768, 0,
    0, 256, (s32)D_80092D14, (s32)D_800920A8,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80092D20, (s32)D_80092D2C, (s32)D_80092D38,
    768, 0, 0, 256,
    (s32)D_80092D44, (s32)D_80092D50, (s32)D_80092D5C, 768,
    0, 0, 256, (s32)D_80092D68,
    (s32)D_80092D74, (s32)D_80092D80, 768, 0,
    0, 256, (s32)D_80092D8C, (s32)D_80092D98,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80092DA4, (s32)D_80092DB0, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092DBC, (s32)D_80092DC8, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092DD4,
    (s32)D_80092DE0, (s32)D_80092DEC, 768, 0,
    0, 256, (s32)D_80092DF8, (s32)D_80092E04,
    (s32)D_80092E10, 768, 0, 0,
    256, (s32)D_80092E1C, (s32)D_80092E28, (s32)D_80092E34,
    768, 0, 0, 256,
    (s32)D_80092E40, (s32)D_800920A8, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80092E4C,
    (s32)D_80092E58, (s32)D_80092E64, 768, 0,
    0, 256, (s32)D_80092E70, (s32)D_80092E7C,
    (s32)D_80092E88, 768, 0, 0,
    256, (s32)D_80092E94, (s32)D_80092EA0, (s32)D_80092EAC,
    768, 0, 0, 256,
    (s32)D_80092EB8, (s32)D_80092EC4, (s32)D_80092ED0, 768,
    0, 0, 256, (s32)D_80092EDC,
    (s32)D_80092EE8, (s32)D_80092EF4, 768, 0,
    0, 256, (s32)D_80092F00, (s32)D_80092F0C,
    (s32)D_80092F18, 768, 0, 0,
    256, (s32)D_80092F24, (s32)D_800920A8, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092F30, (s32)D_80092F3C, (s32)D_80092F48, 768,
    0, 0, 256, (s32)D_80092F54,
    (s32)D_80092F60, (s32)D_80092F6C, 768, 0,
    0, 256, (s32)D_80092F78, (s32)D_80092F84,
    (s32)D_80092F90, 768, 0, 0,
    256, (s32)D_80092F9C, (s32)D_80092FA8, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80092FB4, (s32)D_80092FC0, (s32)D_80092FCC, 768,
    0, 0, 256, (s32)D_80092FD8,
    (s32)D_80092FE4, (s32)D_80092FF0, 768, 0,
    0, 256, (s32)D_80092FFC, (s32)D_80093008,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80093014, (s32)D_80093020, (s32)D_8009302C,
    768, 0, 0, 256,
    (s32)D_80093038, (s32)D_80093044, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80093050,
    (s32)D_8009305C, (s32)D_80093068, 768, 0,
    0, 256, (s32)D_80093074, (s32)D_80093080,
    (s32)D_8009308C, 768, 0, 0,
    256, (s32)D_80093098, (s32)D_800930A4, (s32)D_800930B0,
    768, 0, 0, 256,
    (s32)D_800930BC, (s32)D_800930C8, (s32)D_800930D4, 768,
    0, 0, 256, (s32)D_800930E0,
    (s32)D_800930EC, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_800930F8, (s32)D_80093104,
    (s32)D_80093110, 768, 0, 0,
    256, (s32)D_8009311C, (s32)D_80093128, (s32)D_80093134,
    768, 0, 0, 256,
    (s32)D_80093140, (s32)D_8009314C, (s32)D_80093158, 768,
    0, 0, 256, (s32)D_80093164,
    (s32)D_80093170, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_8009317C, (s32)D_80093188,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_80093194, (s32)D_800931A0, (s32)D_800931AC,
    768, 0, 0, 256,
    (s32)D_800931B8, (s32)D_800931C4, (s32)D_800931D0, 768,
    0, 0, 256, (s32)D_800931DC,
    (s32)D_800931E8, (s32)D_800920A8, 768, 0,
    256, 256, (s32)D_800931F4, (s32)D_80093200,
    (s32)D_8009320C, 768, 0, 0,
    256, (s32)D_80093218, (s32)D_80093224, (s32)D_80093230,
    768, 0, 0, 256,
    (s32)D_8009323C, (s32)D_80093248, (s32)D_80093254, 768,
    0, 0, 256, (s32)D_80093260,
    (s32)D_8009326C, (s32)D_80093278, 768, 0,
    0, 256, (s32)D_80093284, (s32)D_80093290,
    (s32)D_8009329C, 0x1010300, 0x1010101, 0x1010001,
    257, (s32)D_800932A8, (s32)D_800932B4, (s32)D_800920A8,
    768, 0, 256, 256,
    (s32)D_800932C0, (s32)D_800932CC, (s32)D_800920A8, 768,
    0, 256, 256, (s32)D_800932D8,
    (s32)D_800920A8, (s32)D_800920A8, 1024, 0,
    0, 256, (s32)D_800932E4, (s32)D_800920A8,
    (s32)D_800920A8, 1024, 0, 0,
    256, (s32)D_800932F0, (s32)D_800920A8, (s32)D_800920A8,
    1024, 0, 0, 256,
    (s32)D_800932FC, (s32)D_800920A8, (s32)D_800920A8, 1024,
    0, 0, 256, (s32)D_80093308,
    (s32)D_800920A8, (s32)D_800920A8, 1024, 0,
    0, 256, (s32)D_80093314, (s32)D_800920A8,
    (s32)D_800920A8, 1024, 0, 0,
    256, (s32)D_80093320, (s32)D_800920A8, (s32)D_800920A8,
    1024, 0, 0, 256,
    (s32)D_8009332C, (s32)D_800920A8, (s32)D_800920A8, 1024,
    0, 0, 256, (s32)D_80093338,
    (s32)D_800920A8, (s32)D_800920A8, 1024, 0,
    0, 256, (s32)D_80093344, (s32)D_800940A4,
    (s32)D_800940B0, 0x1010400, 0x1010101, 0x1010001,
    257, (s32)D_80093350, (s32)D_8009335C, (s32)D_80093368,
    512, 0x10000, 0, 256,
    (s32)D_80093374, (s32)D_800920A8, (s32)D_800920A8, 512,
    0, 0, 256, (s32)D_80093380,
    (s32)D_800920A8, (s32)D_800920A8, 512, 0,
    0, 256, (s32)D_8009338C, (s32)D_800920A8,
    (s32)D_800920A8, 512, 0, 0,
    256, (s32)D_80093398, (s32)D_800920A8, (s32)D_800920A8,
    512, 0, 0, 256,
    (s32)D_800933A4, (s32)D_800920A8, (s32)D_800920A8, 512,
    0, 0, 256, (s32)D_800933B0,
    (s32)D_800920A8, (s32)D_800920A8, 512, 0,
    0, 256, (s32)D_800933BC, (s32)D_800920A8,
    (s32)D_800920A8, 512, 0, 0,
    256, (s32)D_800933C8, (s32)D_800920A8, (s32)D_800920A8,
    512, 0, 0, 256,
    (s32)D_800933D4, (s32)D_800933E0, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_800933EC,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    256, 0, (s32)D_800933F8, (s32)D_800920A8,
    (s32)D_800920A8, 264, 0, 256,
    0, (s32)D_80093404, (s32)D_800920A8, (s32)D_800920A8,
    264, 0, 256, 0,
    (s32)D_80093410, (s32)D_800920A8, (s32)D_800920A8, 264,
    0, 256, 0, (s32)D_8009341C,
    (s32)D_800920A8, (s32)D_800920A8, 264, 0,
    256, 0, (s32)D_80093494, (s32)D_800934A0,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_800934AC, (s32)D_800934B8, (s32)D_800934C4,
    768, 0, 0, 256,
    (s32)D_800934D0, (s32)D_800934DC, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_800934E8,
    (s32)D_800934F4, (s32)D_80093500, 768, 0,
    0, 256, (s32)D_8009350C, (s32)D_80093518,
    (s32)D_80093524, 768, 0, 0,
    256, (s32)D_80093530, (s32)D_8009353C, (s32)D_80093548,
    768, 0, 0, 256,
    (s32)D_80093554, (s32)D_80093560, (s32)D_8009356C, 768,
    0, 0, 256, (s32)D_80093578,
    (s32)D_80093584, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_80093590, (s32)D_8009359C,
    (s32)D_800935A8, 768, 0, 0,
    256, (s32)D_800935B4, (s32)D_800935C0, (s32)D_800935CC,
    768, 0, 0, 256,
    (s32)D_800935D8, (s32)D_800935E4, (s32)D_800935F0, 768,
    0, 0, 256, (s32)D_800935FC,
    (s32)D_80093608, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_80093614, (s32)D_80093620,
    (s32)D_800920A8, 768, 0, 0,
    256, (s32)D_8009362C, (s32)D_80093638, (s32)D_80093644,
    768, 0, 0, 256,
    (s32)D_80093650, (s32)D_8009365C, (s32)D_80093668, 768,
    0, 0, 256, (s32)D_80093674,
    (s32)D_80093680, (s32)D_800920A8, 768, 0,
    0, 256, (s32)D_8009368C, (s32)D_80093698,
    (s32)D_800936A4, 768, 0, 0,
    256, (s32)D_800936B0, (s32)D_800936BC, (s32)D_800936C8,
    768, 0, 0, 256,
    (s32)D_800936D4, (s32)D_800936E0, (s32)D_800936EC, 768,
    0, 0, 256, (s32)D_800936F8,
    (s32)D_80093704, (s32)D_80093710, 768, 0,
    0, 256, (s32)D_8009371C, (s32)D_80093728,
    (s32)D_80093734, 768, 0, 0,
    256, (s32)D_80093740, (s32)D_8009374C, (s32)D_800920A8,
    768, 0, 0, 256,
    (s32)D_80093758, (s32)D_80093764, (s32)D_800920A8, 768,
    0, 0, 256, (s32)D_80093770,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010000, 257, (s32)D_8009377C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010000,
    257, (s32)D_80093788, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010000, 257,
    (s32)D_80093794, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010000, 257, (s32)D_800937A0,
    (s32)D_800937AC, (s32)D_800937B8, 0x1010200, 0x1010101,
    0x1010001, 257, (s32)D_800937C4, (s32)D_800937D0,
    (s32)D_800937DC, 0x101027F, 0x1010101, 0x1010001,
    257, (s32)D_800937E8, (s32)D_800937F4, (s32)D_80093800,
    0x1010200, 0x1010101, 0x1010001, 257,
    (s32)D_8009380C, (s32)D_80093818, (s32)D_80093824, 0x1010200,
    0x1010101, 0x1010001, 257, (s32)D_80093830,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010000, 257, (s32)D_8009383C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010000,
    257, (s32)D_80093848, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010000, 257,
    (s32)D_80093854, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010000, 257, (s32)D_800938C0,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_800938CC, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_800938D8, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_800938E4, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010000, 257, (s32)D_800938F0,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010000, 257, (s32)D_800938FC, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010000,
    257, (s32)D_80093908, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010000, 257,
    (s32)D_80093914, (s32)D_800920A8, (s32)D_800920A8, 0x1010200,
    0x1010101, 0x1010000, 257, (s32)D_80093920,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010000, 257, (s32)D_8009392C, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010300, 0x1010101, 0x1010101,
    257, (s32)D_80093938, (s32)D_800920A8, (s32)D_800920A8,
    0x1010200, 0x1010101, 0x1010101, 257,
    (s32)D_80093944, (s32)D_80093950, (s32)D_8009395C, 0x1010200,
    0x1010101, 0x1010101, 257, (s32)D_80093968,
    (s32)D_800920A8, (s32)D_800920A8, 0x1010200, 0x1010101,
    0x1010101, 257, (s32)D_80093974, (s32)D_800920A8,
    (s32)D_800920A8, 0x1010200, 0x1010101, 0x1010101,
    257, (s32)D_80093980, (s32)D_800920A8, (s32)D_800920A8,
    0x1000508, 257, 256, 0,
    (s32)D_8009398C, (s32)D_800920A8, (s32)D_800920A8, 0x1000508,
    257, 256, 0, (s32)D_80093998,
    (s32)D_800920A8, (s32)D_800920A8, 0x1000510, 257,
    256, 0, (s32)D_800939A4, (s32)D_800920A8,
    (s32)D_800920A8, 0x1000510, 257, 256,
    0, (s32)D_800939B0, (s32)D_800920A8, (s32)D_800920A8,
    0x1000518, 257, 256, 0,
    (s32)D_800939BC, (s32)D_800920A8, (s32)D_800920A8, 0x1000518,
    257, 256, 0, (s32)D_800939C8,
    (s32)D_800920A8, (s32)D_800920A8, 0x1000520, 257,
    256, 0, (s32)D_800939D4, (s32)D_800920A8,
    (s32)D_800920A8, 0x1000520, 257, 256,
    0,
};
#endif
u16 D_80095E84[] = {
    0x0001, 0x0002, 0x0001, 0x0000, 0xFFFF, 0xFFFE, 0xFFFF, 0x0000,
    0x03E8, 0x0000,
};
#if VERSION_US
s32 D_80095E98[] = {
    0x1120002, 0x5360535, 0x1120005, 0x53B053A,
    0x1120009, 0x540053F, 0x112000D, 0x5450544,
    0x1120011, 0x54A0549, 0x1120015, 0x54F054E,
    0x1120019, 0x5540553, 0x112001D, 0x5590558,
    0x1120021, 0x55E055D, 0x1120025, 0x5630562,
    0x1120029, 0x5680567, 0x112002D, 0x56D056C,
    0x1120031, 0x5720571, 0x1120035, 0x5770576,
    0x1120039, 0x57C057B, 0x112003D, 0x5810580,
};
#elif VERSION_EU
s32 D_80095E98[] = {
    0x1190002, 0x5360535, 0x1190005, 0x53B053A,
    0x1190009, 0x540053F, 0x119000D, 0x5450544,
    0x1190011, 0x54A0549, 0x1190015, 0x54F054E,
    0x1190019, 0x5540553, 0x119001D, 0x5590558,
    0x1190021, 0x55E055D, 0x1190025, 0x5630562,
    0x1190029, 0x5680567, 0x119002D, 0x56D056C,
    0x1190031, 0x5720571, 0x1190035, 0x5770576,
    0x1190039, 0x57C057B, 0x119003D, 0x5810580,
};
#endif
ProgressEvent D_80095F18[] = {
    {5, 0x400, 0x7074, 0x533, 0x534},
    {8, 0x401, 0x7074, 0x538, 0x539},
    {12, 0x402, 0x7075, 0x53D, 0x53E},
    {14, 0x403, 0x7075, 0x542, 0x543},
    {16, 0x404, 0x7076, 0x547, 0x548},
    {22, 0x405, 0x7076, 0x54C, 0x54D},
    {24, 0x406, 0x7077, 0x551, 0x552},
    {26, 0x407, 0x7077, 0x556, 0x557},
    {28, 0x408, 0x7078, 0x55B, 0x55C},
    {30, 0x409, 0x7078, 0x560, 0x561},
    {31, 0x40A, 0x7079, 0x565, 0x566},
    {34, 0x40B, 0x7079, 0x56A, 0x56B},
    {36, 0x40C, 0x707A, 0x56F, 0x570},
    {37, 0x40D, 0x707B, 0x574, 0x575},
    {38, 0x40E, 0x707C, 0x579, 0x57A},
    {39, 0x40F, 0x707D, 0x57E, 0x57F},
    {-1, 0, 0, 0, 0},
};
u16 D_80096028[] = {
    0x0000, 0x0001, 0x0000, 0x000D, 0x0001, 0x000E, 0x0002, 0x000F,
    0x0003, 0x000E, 0x0000, 0x000D, 0x0001, 0x000E, 0x0002, 0x000F,
    0x0003, 0x000E, 0x0000, 0x0006, 0x0001, 0x0006, 0x0002, 0x0006,
    0x0004, 0x0007, 0x0005, 0x0005, 0x0006, 0x0004, 0x0007, 0x0004,
    0x0008, 0x0004, 0x0009, 0x0004, 0xFFFF, 0xFFFF,
};
u16 D_80096074[] = {
    0x0000, 0x0001, 0x0001, 0x0008, 0x0002, 0x0006, 0x0003, 0x0004,
    0x0004, 0x0004, 0x0003, 0x0004, 0x0004, 0x0004, 0x0003, 0x0006,
    0x0004, 0x0004, 0x0003, 0x0004, 0xFFFF, 0x0007,
};
u16 D_800960A0[] = {
    0x0000, 0x0001, 0x0009, 0x0012, 0x0005, 0x0004, 0x0006, 0x0005,
    0x0007, 0x0004, 0x0008, 0x0004, 0x0006, 0x0004, 0x0007, 0x0004,
    0x0008, 0x0004, 0xFFFF, 0x0005,
};
AnimFrame D_800960C8[] = {
    {0, 4}, {1, 4}, {2, 4}, {3, 4},
    {4, 4}, {5, 4}, {6, 4}, {7, 4},
    {8, 4}, {9, 4}, {10, 4}, {11, 4},
    {12, 4}, {13, 4}, {14, 4}, {15, 4},
    {16, 4}, {17, 4}, {18, 4}, {19, 4},
    {20, 4}, {21, 4}, {22, 4}, {23, 4},
    {24, 4}, {25, 4}, {26, 4}, {27, 4},
    {28, 4}, {29, 4}, {30, 4}, {31, 4},
    {0xFF, 999},
};
AnimFrame D_8009614C[] = {
    {0x12C, 28}, {32, 4}, {33, 24}, {34, 4},
    {0xFF, 999},
};
AnimFrame D_80096160[] = {
    {0x12C, 28}, {35, 4}, {36, 24}, {37, 4},
    {0xFF, 999},
};
AnimFrame D_80096174[] = {
    {0x12C, 104}, {38, 4}, {39, 4}, {40, 4},
    {41, 4}, {42, 4}, {43, 4}, {0xFF, 999},
};
AnimFrame D_80096194[] = {
    {0x12C, 104}, {44, 4}, {45, 4}, {46, 4},
    {47, 4}, {48, 4}, {49, 4}, {0xFF, 0},
};
AnimFrame D_800961B4[] = {
    {0x12C, 128}, {50, 4}, {51, 4}, {52, 4},
    {53, 4}, {54, 4}, {55, 4}, {56, 4},
    {57, 4}, {58, 4}, {59, 4}, {0xFF, 999},
};
AnimFrame *D_800961E4[][4] = {
    {D_800960C8, D_8009614C, D_80096174, D_800961B4},
    {D_800960C8, D_80096160, D_80096194, D_800961B4},
};
u8 D_80096204[] = {
    0x19, 0x0E, 0x09, 0x0A, 0x0B, 0x0F, 0x1A, 0x0C,
    0x06, 0x07, 0x08, 0x0D, 0x1B, 0x10, 0x02, 0x00,
    0x03, 0x11, 0x1C, 0x12, 0x04, 0x01, 0x05, 0x13,
    0x1D, 0x14, 0x15, 0x16, 0x17, 0x18, 0x14, 0x0C,
    0x0D, 0x0E, 0x0F, 0x15, 0x10, 0x08, 0x09, 0x0A,
    0x0B, 0x11, 0x12, 0x04, 0x00, 0x01, 0x05, 0x13,
    0x16, 0x06, 0x02, 0x03, 0x07, 0x17, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x19, 0x0C, 0x09, 0x0A,
    0x0B, 0x0D, 0x1A, 0x0E, 0x02, 0x01, 0x03, 0x0F,
    0x1B, 0x10, 0x04, 0x00, 0x05, 0x11, 0x1C, 0x12,
    0x06, 0x07, 0x08, 0x13, 0x1D, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x10, 0x0C, 0x0D, 0x0E, 0x0F, 0x11,
    0x12, 0x04, 0x02, 0x03, 0x05, 0x13, 0x14, 0x06,
    0x00, 0x01, 0x07, 0x15, 0x16, 0x08, 0x09, 0x0A,
    0x0B, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x0C, 0x0A,
    0x0E, 0x10, 0x12, 0x14, 0x08, 0x06, 0x02, 0x00,
    0x04, 0x15, 0x09, 0x07, 0x03, 0x01, 0x05, 0x16,
    0x0D, 0x0B, 0x0F, 0x11, 0x13, 0x17, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x0C, 0x0A, 0x0E, 0x10,
    0x12, 0x14, 0x08, 0x04, 0x00, 0x01, 0x06, 0x15,
    0x09, 0x05, 0x02, 0x03, 0x07, 0x16, 0x0D, 0x0B,
    0x0F, 0x11, 0x13, 0x17, 0x17, 0x0F, 0x11, 0x13,
    0x15, 0x19, 0x0C, 0x09, 0x03, 0x01, 0x06, 0x1A,
    0x0D, 0x0A, 0x04, 0x00, 0x07, 0x1B, 0x0E, 0x0B,
    0x05, 0x02, 0x08, 0x1C, 0x18, 0x10, 0x12, 0x14,
    0x16, 0x1D, 0x0F, 0x11, 0x13, 0x15, 0x17, 0x19,
    0x0C, 0x04, 0x02, 0x07, 0x09, 0x1A, 0x0D, 0x05,
    0x00, 0x01, 0x0A, 0x1B, 0x0E, 0x06, 0x03, 0x08,
    0x0B, 0x1C, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1D,
    0x0C, 0x0F, 0x10, 0x11, 0x13, 0x15, 0x0D, 0x06,
    0x08, 0x0A, 0x0B, 0x17, 0x0E, 0x07, 0x02, 0x00,
    0x04, 0x19, 0x12, 0x09, 0x03, 0x01, 0x05, 0x1B,
    0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1D, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x08, 0x0A, 0x0C, 0x0D,
    0x0E, 0x10, 0x09, 0x04, 0x00, 0x01, 0x06, 0x12,
    0x0B, 0x05, 0x02, 0x03, 0x07, 0x14, 0x0F, 0x11,
    0x13, 0x15, 0x16, 0x17, 0x19, 0x09, 0x0C, 0x0D,
    0x0F, 0x11, 0x1A, 0x0A, 0x03, 0x02, 0x05, 0x13,
    0x1B, 0x0B, 0x01, 0x00, 0x07, 0x15, 0x1C, 0x0E,
    0x04, 0x06, 0x08, 0x17, 0x1D, 0x10, 0x12, 0x14,
    0x16, 0x18, 0x0C, 0x0F, 0x10, 0x12, 0x13, 0x15,
    0x0D, 0x04, 0x03, 0x05, 0x08, 0x17, 0x0E, 0x02,
    0x00, 0x01, 0x0A, 0x19, 0x11, 0x06, 0x07, 0x09,
    0x0B, 0x1C, 0x14, 0x16, 0x18, 0x1A, 0x1B, 0x1D,
};
u8 D_8009636C[] = {
    0x00, 0x01, 0x02, 0x01, 0x01, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x02, 0x02, 0x01, 0x02, 0x02, 0x03,
};
u8 D_8009637C[] = {
    0x02, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01,
    0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};
s32 D_8009638C[] = {
    7, 3, 11,
};
Point D_80096398[] = {
    {640, 0},
    {640, 128},
    {768, 0},
    {768, 128},
    {896, 0},
    {896, 128},
    {640, 256},
    {640, 384},
    {768, 256},
    {768, 384},
    {896, 256},
    {896, 384},
};
AreaName D_800963F8[] = {
    {11, 1, 512},
    {11, 118, 624},
    {11, 1, 513},
    {11, 118, 625},
    {11, 2, 514},
    {11, 119, 626},
    {1, 3, 515},
    {6, 3, 627},
    {1, 3, 516},
    {11, 1, 517},
    {11, 118, 628},
    {1, 4, 518},
    {6, 4, 629},
    {1, 5, 519},
    {6, 5, 630},
    {1, 6, 520},
    {6, 6, 631},
    {1, 7, 521},
    {6, 7, 632},
    {1, 8, 522},
    {6, 120, 633},
    {1, 135, 523},
    {6, 135, 634},
    {1, 9, 524},
    {6, 121, 635},
    {1, 10, 525},
    {6, 122, 636},
    {1, 11, 526},
    {6, 11, 637},
    {1, 12, 527},
    {6, 12, 638},
    {1, 13, 528},
    {6, 13, 639},
    {1, 14, 529},
    {6, 14, 640},
    {1, 15, 530},
    {6, 15, 641},
    {1, 16, 531},
    {6, 16, 642},
    {1, 17, 532},
    {6, 17, 643},
    {1, 18, 533},
    {6, 18, 644},
    {1, 19, 534},
    {6, 19, 645},
    {1, 20, 535},
    {6, 20, 646},
    {1, 21, 536},
    {6, 21, 647},
    {1, 22, 537},
    {6, 22, 648},
    {1, 23, 538},
    {6, 23, 649},
    {1, 24, 539},
    {6, 123, 650},
    {1, 25, 540},
    {6, 25, 651},
    {11, 26, 541},
    {11, 26, 652},
    {11, 27, 542},
    {11, 27, 653},
    {11, 28, 543},
    {11, 28, 654},
    {11, 29, 544},
    {11, 29, 655},
    {12, 30, 545},
    {12, 30, 656},
    {12, 31, 546},
    {12, 31, 657},
    {12, 32, 547},
    {12, 32, 658},
    {12, 33, 548},
    {12, 33, 659},
    {12, 34, 549},
    {12, 34, 660},
    {12, 35, 550},
    {12, 35, 661},
    {12, 36, 551},
    {12, 36, 662},
    {12, 37, 552},
    {12, 37, 663},
    {12, 38, 553},
    {12, 38, 664},
    {12, 39, 554},
    {12, 39, 665},
    {12, 40, 555},
    {12, 40, 666},
    {12, 41, 556},
    {12, 41, 667},
    {12, 42, 557},
    {12, 43, 558},
    {12, 124, 668},
    {2, 44, 559},
    {7, 44, 669},
    {2, 45, 560},
    {7, 125, 670},
    {2, 46, 561},
    {7, 46, 671},
    {13, 47, 562},
    {13, 47, 672},
    {13, 48, 563},
    {13, 48, 673},
    {13, 49, 564},
    {13, 49, 674},
    {13, 50, 565},
    {13, 50, 675},
    {13, 51, 566},
    {13, 52, 567},
    {13, 52, 676},
    {13, 53, 568},
    {13, 53, 677},
    {13, 54, 569},
    {13, 54, 678},
    {13, 55, 570},
    {13, 55, 679},
    {13, 56, 571},
    {13, 56, 680},
    {13, 57, 572},
    {13, 57, 681},
    {13, 58, 573},
    {13, 58, 682},
    {13, 59, 574},
    {13, 126, 683},
    {3, 60, 575},
    {8, 127, 684},
    {3, 61, 576},
    {8, 128, 685},
    {13, 62, 577},
    {13, 129, 686},
    {13, 63, 578},
    {13, 63, 687},
    {13, 64, 579},
    {13, 64, 580},
    {13, 64, 688},
    {16, 66, 581},
    {16, 67, 582},
    {14, 68, 583},
    {14, 68, 689},
    {14, 69, 584},
    {14, 69, 690},
    {14, 70, 585},
    {14, 70, 691},
    {14, 71, 586},
    {14, 71, 692},
    {14, 72, 587},
    {14, 72, 693},
    {14, 73, 588},
    {14, 73, 694},
    {14, 74, 589},
    {14, 74, 695},
    {14, 75, 590},
    {14, 75, 696},
    {14, 76, 591},
    {14, 76, 697},
    {14, 77, 592},
    {14, 77, 698},
    {14, 78, 593},
    {14, 78, 699},
    {14, 79, 594},
    {14, 79, 700},
    {14, 80, 595},
    {14, 80, 701},
    {14, 81, 596},
    {14, 81, 702},
    {14, 83, 597},
    {14, 83, 703},
    {14, 83, 598},
    {14, 84, 599},
    {14, 84, 704},
    {14, 85, 600},
    {14, 86, 705},
    {14, 86, 601},
    {14, 86, 706},
    {14, 87, 602},
    {14, 87, 707},
    {14, 88, 603},
    {14, 88, 708},
    {14, 89, 604},
    {14, 89, 709},
    {14, 90, 605},
    {14, 130, 710},
    {4, 91, 606},
    {9, 131, 711},
    {4, 92, 607},
    {4, 93, 608},
    {9, 93, 712},
    {15, 94, 609},
    {15, 94, 713},
    {15, 95, 610},
    {15, 95, 714},
    {15, 96, 611},
    {15, 96, 715},
    {15, 97, 612},
    {15, 97, 716},
    {15, 98, 613},
    {15, 98, 717},
    {15, 99, 614},
    {15, 99, 718},
    {15, 100, 615},
    {15, 100, 719},
    {15, 101, 616},
    {15, 101, 720},
    {15, 102, 617},
    {15, 102, 721},
    {15, 103, 618},
    {15, 103, 722},
    {15, 104, 619},
    {15, 104, 723},
    {15, 105, 620},
    {15, 105, 724},
    {15, 106, 621},
    {15, 107, 622},
    {15, 107, 725},
    {15, 108, 623},
    {15, 132, 726},
    {17, 109, 727},
    {17, 110, 728},
    {17, 106, 729},
    {18, 112, 730},
    {18, 113, 731},
    {18, 114, 732},
    {19, 115, 733},
    {19, 116, 734},
    {19, 117, 735},
    {21, 133, 736},
    {21, 133, 737},
    {21, 133, 738},
    {21, 133, 739},
    {21, 133, 740},
    {21, 133, 741},
    {21, 133, 742},
    {21, 133, 743},
    {21, 134, 744},
    {21, 134, 745},
    {21, 134, 746},
    {21, 134, 747},
    {21, 134, 748},
    {21, 134, 749},
    {21, 134, 750},
    {0, 0, 0},
};
s32 D_800967B8[] = {
    0, 0x290140, 0x10000, 0xFFE400,
    1, 124, 320, 8,
    0, 0, 0x570000, 320,
    0xFFE400, 2, 86, 88,
    2, 0, 0, 0,
    0xF00002, 0xFFE400, 1, 31,
    32, 2, 0, 0,
    0, 0xF00001, 0xFFE400, 1,
    13, 14, 2, 0,
    0, 227, 1, 0xFFE400,
    2, 0, 240, 16,
    0, 0, 0x280140, 0x30000,
    0xC83E3E, 1, 124, 320,
    8, 0, 0, 0x570000,
    320, 0xC83E3E, 2, 81,
    93, 2, 0, 0,
    0, 0xF00008, 0xC83E3E, 1,
    27, 36, 2, 0,
    0, 0x10007D, 116, 0x800000,
    2, 16, 47, 2,
    0, 0, 0x570000, 320,
    0x800000, 2, 66, 97,
    2, 0,
};
u8 D_80096920[][9] = {
    {0x00, 0x3C, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x0A, 0x02, 0x0A, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x03, 0x16, 0x04, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x05, 0x04, 0x06, 0x05, 0x07, 0x04, 0x35, 0x3C, 0xFF},
    {0x08, 0x16, 0x09, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x0A, 0x16, 0x0B, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x16, 0x11, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x0E, 0x16, 0x0F, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x0C, 0x16, 0x0D, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x12, 0x16, 0x13, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x45, 0x16, 0x46, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
};
#if VERSION_US
u8 D_80096983 = 0x8E;
#elif VERSION_EU
u8 D_80096983 = 0x03;
#endif
u8 D_80096984[][8] = {
    {0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
};
s16 D_800969C4[] = {
    0x020A, 0x0223, 0x022F, 0x0238, 0x023F, 0x025B, 0x025D, 0x0263,
    0x026F, 0x026D, 0x0279, 0x0292, 0x029D, 0x02A5, 0x02AC, 0x02C4,
    0x02C6, 0x02CB, 0x02D6, 0x0249, 0x02B3, 0x0000,
};
u8 D_800969F0[][2] = {
    {0x23, 8}, {0x24, 8}, {0x25, 8}, {0x26, 8},
    {0xFF, 0}, {0x00, 0},
};
u8 D_800969FC[][2] = {
    {0x23, 3}, {0x27, 4}, {0x28, 4}, {0x2D, 4},
    {0x2E, 4}, {0x2F, 3}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x31, 2},
    {0x2B, 2}, {0x29, 2}, {0x2A, 2}, {0xFF, 19},
};
u8 D_80096A2C[][2] = {
    {0x29, 6}, {0x2E, 3}, {0x30, 3}, {0x28, 6},
    {0x2C, 8}, {0x23, 8}, {0x24, 8}, {0x25, 8},
    {0x26, 8}, {0xFF, 5},
};
u8 D_80096A40[][2] = {
    {0x23, 3}, {0x27, 4}, {0x28, 4}, {0x2D, 4},
    {0x2E, 4}, {0x2F, 3}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2F, 2},
    {0x2E, 2}, {0x2D, 2}, {0x28, 3}, {0x23, 3},
    {0x23, 8}, {0x24, 8}, {0x25, 8}, {0x26, 8},
    {0xFF, 24}, {0x00, 0},
};
u8 (*D_80096A7C[])[2] = {
    D_800969F0, D_800969FC, D_80096A2C, D_80096A40,
};
s16 D_80096A8C[][2] = {
    {-5, -4}, {-5, -4}, {-5, -4}, {-5, -9},
    {-6, -13}, {-8, -17}, {-10, -20}, {-12, -23},
    {-13, -23}, {-14, -23}, {-15, -22}, {-16, -21},
    {-17, -20}, {-16, -22}, {-16, -22}, {0, 0},
};
s32 D_80096ACC = 0;
s32 D_80096AD0[] = {
    (s32)D_8009AA08, -1, 192, (s32)D_8009A9D8,
    -1, 128, (s32)D_8009A9A8, -1,
    64, (s32)D_8009A978, -1, 0,
    (s32)D_8009A94C, 1, 40, (s32)D_8009A954,
    1, 80, (s32)D_8009A95C, 1,
    120, (s32)D_8009A964, 1, 160,
    (s32)&D_8009A96C, 1, 200, (s32)D_8009A970,
    1, 64, (s32)D_8009A9A0, 1,
    128, (s32)D_8009A9D0, 1, 192,
    (s32)D_8009AA00, 1, 256, (s32)&D_8009AA34,
    -1, 160, (s32)D_8009AA2C, -1,
    120, (s32)D_8009AA24, -1, 80,
    (s32)D_8009AA1C, -1, 40, (s32)D_8009AA10,
    -1, 192, (s32)D_8009A9E0, -1,
    128, (s32)D_8009A9B0, -1, 64,
    (s32)D_8009A984, 1, 80, (s32)D_8009A98C,
    1, 120, (s32)&D_8009A994, 1,
    160, (s32)D_8009A998, 1, 128,
    (s32)D_8009A9C8, 1, 192, (s32)&D_8009A9FC,
    -1, 120, (s32)D_8009A9F4, -1,
    80, (s32)D_8009A9E8, -1, 192,
    (s32)&D_8009A9BC, 1, 120, 0,
    0, 0,
};
#if VERSION_US
s16 D_80096C38[] = {
    1522, 1200, 1201, 8, 9, 1512, 54, 1514,
    1516, 140, 142, 1205, 1210, 1211, 1215, 1220,
    1221, 1457, 1458, 1230, 1231, 1235, 1236, 1240,
    1241, 1245, 1510, 1518, 1520, 1250, 1251, 240,
    205, 290, 67, 890, 560, 1265, 1267, 1269,
    1271, 1273, 1275, 1277, 1279, 300, 70, 60,
    1299, 1301, 1302, 1303, 1304, 1260, 1262, 950,
    1281, 1283, 1285, 1287, 1289, 1291, 320, 320,
    695, 375, 260, 690, 430, 820, 735, 1310,
    736, 750, 745, 895, 1320, 1325, 13, 14,
    1421, 1423, 1425, 1427, 1429, 1430, 1436, 1438,
    1440, 1442, 1444, 1445, 1415, 220, 510, 143,
    144, 1450, 1321, 1326, 1455, 1459, 1460, 1461,
    1462, 1463, 1464, 1431, 1446, -20560,
};
u8 D_80096D14[][2] = {
    {0x00, 0x00},
    {0x39, 0x06},
    {0x3A, 0x04},
    {0x3B, 0x04},
    {0x3C, 0x08},
    {0x3D, 0x08},
    {0x3E, 0x08},
    {0x3F, 0x0A},
    {0x40, 0x08},
    {0x38, 0x08},
    {0xFF, 0x00},
    {0x62, 0x28},
};
#elif VERSION_EU
s16 D_80096C38[] = {
    1522, 1200, 1201, 8, 9, 1512, 54, 1514,
    1516, 140, 142, 1205, 1210, 1211, 1215, 1220,
    1221, 1457, 1458, 1230, 1231, 1235, 1236, 1240,
    1241, 1245, 1510, 1518, 1520, 1250, 1251, 240,
    205, 290, 67, 890, 560, 1265, 1267, 1269,
    1271, 1273, 1275, 1277, 1279, 300, 70, 60,
    1299, 1301, 1302, 1303, 1304, 1260, 1262, 950,
    1281, 1283, 1285, 1287, 1289, 1291, 320, 320,
    695, 375, 260, 690, 430, 820, 735, 1310,
    736, 750, 745, 895, 1320, 1325, 13, 14,
    1421, 1423, 1425, 1427, 1429, 1430, 1436, 1438,
    1440, 1442, 1444, 1445, 1415, 220, 510, 143,
    144, 1450, 1321, 1326, 1455, 1459, 1460, 1461,
    1462, 1463, 1464, 1431, 1446, 1602, 1604, 1606,
    1612, 1614, 1616, 1618, 1620, 1622, 1624, 1626,
    1628, 1646, 1648, 785,
};
u8 D_80096D14[][2] = {
    {0x00, 0x00},
    {0x39, 0x06},
    {0x3A, 0x04},
    {0x3B, 0x04},
    {0x3C, 0x08},
    {0x3D, 0x08},
    {0x3E, 0x08},
    {0x3F, 0x0A},
    {0x40, 0x08},
    {0x38, 0x08},
    {0xFF, 0x00},
    {0x05, 0x00},
};
#endif
u8 D_80096D2C[] = {
    0x00, 0x08, 0x5B, 0x04, 0x5C, 0x04, 0x5D, 0x04,
    0x5E, 0x04, 0x5F, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D3C[] = {
    0x00, 0x08, 0x56, 0x04, 0x57, 0x04, 0x58, 0x04,
    0x59, 0x04, 0x5A, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D4C[] = {
    0x00, 0x08, 0x51, 0x04, 0x52, 0x04, 0x53, 0x04,
    0x54, 0x04, 0x55, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D5C[] = {
    0x00, 0x08, 0x4C, 0x04, 0x4D, 0x04, 0x4E, 0x04,
    0x4F, 0x04, 0x50, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D6C[] = {
    0x00, 0x08, 0x47, 0x04, 0x48, 0x04, 0x49, 0x04,
    0x4A, 0x04, 0x4B, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D7C[] = {
    0x00, 0x08, 0x14, 0x04, 0x15, 0x04, 0x16, 0x04,
    0x17, 0x04, 0x18, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D8C[] = {
    0x00, 0x08, 0x19, 0x04, 0x1A, 0x04, 0x1B, 0x04,
    0x1C, 0x04, 0x1D, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D9C[] = {
    0x00, 0x08, 0x1E, 0x04, 0x1F, 0x04, 0x20, 0x04,
    0x21, 0x04, 0x22, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 *D_80096DAC[] = {
    D_80096D2C, D_80096D3C, D_80096D4C, D_80096D5C,
    D_80096D6C, D_80096D7C, D_80096D8C, D_80096D9C,
};
s32 D_80096DCC[] = {
    1, 1, 1, -1,
    -1, -1, 1, 1,
};
s32 D_80096DEC[] = {
    0, 0xAAAA0000, 0xAAA95,
};
s32 D_80096DF8[] = {
    0x950015AA, 0x150015AA, 0x56AA5400,
};
s32 D_80096E04[] = {
    0xAAAA56AA, 682, 0xAAA80000,
};
s32 D_80096E10[] = {
    0x2AAA80, 0xAAAAAAA8, 0x5400AAAA,
};
s32 D_80096E1C[] = {
    0xAAAAAAAA, 0xAAA95AAA, 0xAAAAAAAA,
};
s32 D_80096E28[] = {
    2730, 0xAAA80000, 0x56AAAAAA,
};
s32 D_80096E34[] = {
    0xAAAAAAAA, 0xAAAAAAAA, 0xAAA8002A,
};
s32 D_80096E40[] = {
    0, 0xAAAAA555, 0xAAAAAAAA,
};
#if VERSION_US
s32 D_80096E4C[] = {
    (s32)D_80096DEC, (s32)D_80096DF8, (s32)D_80096E04, (s32)D_80096E10,
    (s32)D_80096E1C, (s32)D_80096E28, (s32)D_80096E34, (s32)D_80096E40,
};
#elif VERSION_EU
s32 D_80096E4C[] = {
    0, 0, 0,
};
s32 D_80097B14[] = {
    (s32)D_80096DEC, (s32)D_80096DF8, (s32)D_80096E04, (s32)D_80096E10,
    (s32)D_80096E1C, (s32)D_80096E28, (s32)D_80096E34, (s32)D_80096E40,
    (s32)D_80096E4C,
};
#endif
Point D_80096E6C[] = {
    {0, 0},
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1},
};
u8 D_80096E94[][5] = {
    {0x0A, 0x05, 0x04, 0x06, 0x03},
    {0x0E, 0x06, 0x05, 0x07, 0x04},
    {0x0B, 0x07, 0x06, 0x00, 0x05},
    {0x0F, 0x07, 0x00, 0x06, 0x01},
    {0x08, 0x00, 0x01, 0x07, 0x02},
    {0x0C, 0x02, 0x01, 0x03, 0x00},
    {0x09, 0x02, 0x03, 0x01, 0x04},
    {0x0D, 0x03, 0x04, 0x02, 0x05},
};
Point D_80096EBC[] = {
    {-6, -8},
    {6, -8},
    {8, -6},
    {8, 6},
    {6, 8},
    {-6, 8},
    {-8, 6},
    {-8, -6},
    {0, -8},
    {8, 0},
    {0, 8},
    {-8, 0},
    {8, -8},
    {8, 8},
    {-8, 8},
    {-8, -8},
};
u8 D_80096F3C[][2] = {
    {0x00, 0x81},
    {0x00, 0x81},
    {0x01, 0x00},
    {0x01, 0x00},
    {0x00, 0x01},
    {0x00, 0x01},
    {0x81, 0x00},
    {0x81, 0x00},
    {0x00, 0x81},
    {0x01, 0x00},
    {0x00, 0x01},
    {0x81, 0x00},
    {0x01, 0x81},
    {0x01, 0x01},
    {0x81, 0x01},
    {0x81, 0x81},
};
s32 D_80096F5C[] = {
    0, 4, 6, 5,
    0, 0, 7, 0,
    2, 3, 0, 0,
    1, 0, 0, 0,
};
s16 D_80096F9C[][2] = {
    {0x0070, 0x0020},
    {0x0071, 0x0024},
    {0x00DB, 0x0014},
    {0x00DC, 0x00CE},
    {0x00DD, 0x0029},
    {0x00DE, 0x0028},
    {0x00DF, 0x002A},
    {0x00E0, 0x0019},
    {0x00E1, 0x0033},
    {0x0100, 0x0034},
    {0x010C, 0x010B},
    {0x010E, 0x009D},
    {0x010F, 0x009E},
    {0x011C, 0x004B},
    {0x0120, 0x000C},
    {0x0000, 0x0000},
};
s32 D_80096FDC[] = {
    2, 4, 8,
};
s32 D_80096FE8[] = {
    2, 4, 8,
};
s32 D_80096FF4[] = {
    2, 4, 8,
};
Point D_80097000[] = {
    {0, 16},
    {-11, 11},
    {-16, 0},
    {-11, -11},
    {0, -16},
    {11, -11},
    {16, 0},
    {11, 11},
};
s32 D_80097040[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x10001C0, 0x13E01E2, 0x3E0288, 0x1FE0160,
    0x10001C0, 0x13E01EA, 0x3E02A8, 0x1FE0170,
    0x10001C0, 0x13E01F2, 0x3E02C8, 0x1FD0140,
    0x10001C0, 0x14001CA, 0x400228, 0x1FD0150,
    0x10001C0, 0x15C01D2, 0x5C0248, 0x1FD0160,
    0x10001C0, 0x15C01DA, 0x5C0268, 0x1FD0170,
    0x10001C0, 0x16201C0, 0x620200, 0x1FC0140,
    0x1000180, 0x1DB01A0, 0xDB0180, 0x1FC0150,
    0, 0, 0, 0,
    0x10001C0, 0x18A01C0, 0x8A0200, 0x1FC0160,
    0x10001C0, 0x19601EA, 0x9602A8, 0x1FC0170,
    0x10001C0, 0x19801C8, 0x980220, 0x1FB0140,
    0x10001C0, 0x19901DC, 0x990270, 0x1FB0150,
    0x10001C0, 0x19C01D0, 0x9C0240, 0x1FB0160,
    0x10001C0, 0x1A601F2, 0xA602C8, 0x1FB0170,
    0x10001C0, 0x1AA01C0, 0xAA0200, 0x1FA0140,
};
s32 D_800971A0[] = {
    7229, 65535,
};
s32 D_800971A8[] = {
    0x1904C, 0x11C3D, 65535,
};
s32 D_800971B4[] = {
    0x11C3D, 65535,
};
s32 D_800971BC[] = {
    0x1904D, 7229, 65535,
};
s32 D_800971C8[] = {
    7229, 65535,
};
s32 D_800971D0[] = {
    0x1904C, 0x11C3D, 65535,
};
s32 D_800971DC[] = {
    0x11C3D, 65535,
};
s32 D_800971E4[] = {
    0x1904D, 7229, 65535,
};
s32 D_800971F0[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097208[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097220[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097238[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097250[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097268[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097280[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097298[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972B0[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972C8[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972E0[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972F8[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097310[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097328[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097340[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097358[] = {
    0, 0, 29, 0,
    0, 0,
};
s32 D_80097370[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097388[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973A0[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973B8[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973D0[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973E8[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097400[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097418[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097430[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097448[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097460[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097478[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097490[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800974A8[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800974C0[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800974D8[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800974F0[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097508[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097520[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097538[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097550[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097568[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097580[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097598[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975B0[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975C8[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975E0[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975F8[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097610[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097628[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097640[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097658[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097670[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097688[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976A0[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976B8[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976D0[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976E8[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097700[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097718[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097730[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097748[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097760[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097778[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097790[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800977A8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800977C0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800977D8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800977F0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097808[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097820[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097838[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097850[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097868[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097880[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097898[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978B0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978C8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978E0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978F8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097910[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097928[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097940[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097958[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097970[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097988[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979A0[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979B8[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979D0[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979E8[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A00[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A18[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A30[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A48[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A60[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A78[] = {
    (s32)D_800971A0, (s32)D_800971A8, 97, (s32)D_800971B4,
    (s32)D_800971BC, 98, 0, 0,
    0,
};
s32 D_80097A9C[] = {
    (s32)D_800971C8, (s32)D_800971D0, 97, (s32)D_800971DC,
    (s32)D_800971E4, 98, 0, 0,
    0,
};
s32 D_80097AC0[] = {
    0, 0, 192, 0,
    0, 0,
};
s32 D_80097AD8[] = {
    0, 0, 193, 0,
    0, 0,
};
s32 D_80097AF0[] = {
    0, 0, 194, 0,
    0, 0,
};
s32 D_80097B08[] = {
    0, 0, 195, 0,
    0, 0,
};
s32 D_80097B20[] = {
    0, 0, 196, 0,
    0, 0,
};
s32 D_80097B38[] = {
    0, 0, 197, 0,
    0, 0,
};
s32 D_80097B50[] = {
    0x16008, 65535,
};
s32 D_80097B58[] = {
    0x1600E, 65535,
};
s32 D_80097B60[] = {
    0x16016, 65535,
};
s32 D_80097B68[] = {
    0x1601A, 65535,
};
s32 D_80097B70[] = {
    0x1601E, 65535,
};
s32 D_80097B78[] = {
    0x16022, 65535,
};
s32 D_80097B80[] = {
    0x16025, 65535,
};
s32 D_80097B88[] = {
    0x16005, 65535,
};
s32 D_80097B90[] = {
    0x1600C, 65535,
};
s32 D_80097B98[] = {
    0x16010, 65535,
};
s32 D_80097BA0[] = {
    0x16018, 65535,
};
s32 D_80097BA8[] = {
    0x1601C, 65535,
};
s32 D_80097BB0[] = {
    0x1601F, 65535,
};
s32 D_80097BB8[] = {
    0x16024, 65535,
};
s32 D_80097BC0[] = {
    0x16026, 65535,
};
s32 D_80097BC8[] = {
    0x16008, 65535,
};
s32 D_80097BD0[] = {
    0x1600C, 65535,
};
s32 D_80097BD8[] = {
    0x1600E, 65535,
};
s32 D_80097BE0[] = {
    0x16010, 65535,
};
s32 D_80097BE8[] = {
    0x16016, 65535,
};
s32 D_80097BF0[] = {
    0x16018, 65535,
};
s32 D_80097BF8[] = {
    0x1601A, 65535,
};
s32 D_80097C00[] = {
    0x1601C, 65535,
};
s32 D_80097C08[] = {
    0x1601E, 65535,
};
s32 D_80097C10[] = {
    0x1601F, 65535,
};
s32 D_80097C18[] = {
    0x16022, 65535,
};
s32 D_80097C20[] = {
    0x16024, 65535,
};
s32 D_80097C28[] = {
    0x16025, 65535,
};
s32 D_80097C30[] = {
    0x16026, 65535,
};
s32 D_80097C38[] = {
    0x16005, 65535,
};
s32 D_80097C40[] = {
    0x16009, 65535,
};
s32 D_80097C48[] = {
    0x1600C, 65535,
};
s32 D_80097C50[] = {
    0x16008, 65535,
};
s32 D_80097C58[] = {
    0x1600E, 65535,
};
s32 D_80097C60[] = {
    0x16010, 65535,
};
s32 D_80097C68[] = {
    0x16016, 65535,
};
s32 D_80097C70[] = {
    0x16018, 65535,
};
s32 D_80097C78[] = {
    0x1601A, 65535,
};
s32 D_80097C80[] = {
    0x1601C, 65535,
};
s32 D_80097C88[] = {
    0x1601E, 65535,
};
s32 D_80097C90[] = {
    0x1601F, 65535,
};
s32 D_80097C98[] = {
    0x16022, 65535,
};
s32 D_80097CA0[] = {
    0x16024, 65535,
};
s32 D_80097CA8[] = {
    0x16025, 65535,
};
s32 D_80097CB0[] = {
    0x16005, 65535,
};
s32 D_80097CB8[] = {
    0x16026, 65535,
};
s32 D_80097CC0[] = {
    0x16005, 65535,
};
s32 D_80097CC8[] = {
    0x16008, 65535,
};
s32 D_80097CD0[] = {
    0x1600C, 65535,
};
s32 D_80097CD8[] = {
    0x1600E, 65535,
};
s32 D_80097CE0[] = {
    0x16010, 65535,
};
s32 D_80097CE8[] = {
    0x16016, 65535,
};
s32 D_80097CF0[] = {
    0x16018, 65535,
};
s32 D_80097CF8[] = {
    0x1601A, 65535,
};
s32 D_80097D00[] = {
    0x1601C, 65535,
};
s32 D_80097D08[] = {
    0x1601E, 65535,
};
s32 D_80097D10[] = {
    0x1601F, 65535,
};
s32 D_80097D18[] = {
    0x16022, 65535,
};
s32 D_80097D20[] = {
    0x16024, 65535,
};
s32 D_80097D28[] = {
    0x16025, 65535,
};
s32 D_80097D30[] = {
    0x16026, 65535,
};
s32 D_80097D38[] = {
    0x1600C, 65535,
};
s32 D_80097D40[] = {
    0x16010, 65535,
};
s32 D_80097D48[] = {
    0x16018, 65535,
};
s32 D_80097D50[] = {
    0x1601C, 65535,
};
s32 D_80097D58[] = {
    0x1601F, 65535,
};
s32 D_80097D60[] = {
    0x16024, 65535,
};
s32 D_80097D68[] = {
    0x16026, 65535,
};
s32 D_80097D70[] = {
    0x16005, 65535,
};
s32 D_80097D78[] = {
    0x16008, 65535,
};
s32 D_80097D80[] = {
    0x1600E, 65535,
};
s32 D_80097D88[] = {
    0x16016, 65535,
};
s32 D_80097D90[] = {
    0x1601A, 65535,
};
s32 D_80097D98[] = {
    0x1601E, 65535,
};
s32 D_80097DA0[] = {
    0x16022, 65535,
};
s32 D_80097DA8[] = {
    0x16025, 65535,
};
s32 D_80097DB0[] = {
    0x16005, 65535,
};
s32 D_80097DB8[] = {
    0x1600C, 65535,
};
s32 D_80097DC0[] = {
    0x16008, 65535,
};
s32 D_80097DC8[] = {
    0x1600E, 65535,
};
s32 D_80097DD0[] = {
    0x16010, 65535,
};
s32 D_80097DD8[] = {
    0x16016, 65535,
};
s32 D_80097DE0[] = {
    0x16018, 65535,
};
s32 D_80097DE8[] = {
    0x1601A, 65535,
};
s32 D_80097DF0[] = {
    0x1601C, 65535,
};
s32 D_80097DF8[] = {
    0x1601E, 65535,
};
s32 D_80097E00[] = {
    0x1601F, 65535,
};
s32 D_80097E08[] = {
    0x16022, 65535,
};
s32 D_80097E10[] = {
    0x16024, 65535,
};
s32 D_80097E18[] = {
    0x16025, 65535,
};
s32 D_80097E20[] = {
    0x16026, 65535,
};
s32 D_80097E28[] = {
    0x16005, 65535,
};
s32 D_80097E30[] = {
    0x1600C, 65535,
};
s32 D_80097E38[] = {
    0x16010, 65535,
};
s32 D_80097E40[] = {
    0x16018, 65535,
};
s32 D_80097E48[] = {
    0x1601A, 65535,
};
s32 D_80097E50[] = {
    0x1601C, 65535,
};
s32 D_80097E58[] = {
    0x1601E, 65535,
};
s32 D_80097E60[] = {
    0x1601F, 65535,
};
s32 D_80097E68[] = {
    0x16022, 65535,
};
s32 D_80097E70[] = {
    0x16024, 65535,
};
s32 D_80097E78[] = {
    0x16025, 65535,
};
s32 D_80097E80[] = {
    0x16026, 65535,
};
s32 D_80097E88[] = {
    0x16008, 65535,
};
s32 D_80097E90[] = {
    0x1600E, 65535,
};
s32 D_80097E98[] = {
    0x16016, 65535,
};
s32 D_80097EA0[] = {
    0x17009, 24581, 24584, 24588,
    24590, 24592, 24598, 24600,
    24602, 24604, 24606, 24607,
    24610, 24612, 24613, 24614,
    24615, 7229, 65535,
};
s32 D_80097EEC[] = {
    0x11C3D, 65535,
};
s32 D_80097EF4[] = {
    0x16027, 65535,
};
s32 D_80097EFC[] = {
    0x16027, 65535,
};
s32 D_80097F04[] = {
    0x16027, 65535,
};
s32 D_80097F0C[] = {
    0x16027, 65535,
};
s32 D_80097F14[] = {
    0x16027, 65535,
};
s32 D_80097F1C[] = {
    0x16027, 65535,
};
s32 D_80097F24[] = {
    0x16027, 65535,
};
s32 D_80097F2C[] = {
    (s32)D_80097B50, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F40[] = {
    (s32)D_80097B58, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F54[] = {
    (s32)D_80097B60, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F68[] = {
    (s32)D_80097B68, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F7C[] = {
    (s32)D_80097B70, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F90[] = {
    (s32)D_80097B78, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FA4[] = {
    (s32)D_80097B80, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FB8[] = {
    (s32)D_80097B88, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FCC[] = {
    (s32)D_80097B90, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FE0[] = {
    (s32)D_80097B98, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FF4[] = {
    (s32)D_80097BA0, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098008[] = {
    (s32)D_80097BA8, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_8009801C[] = {
    (s32)D_80097BB0, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098030[] = {
    (s32)D_80097BB8, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098044[] = {
    (s32)D_80097BC0, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098058[] = {
    (s32)D_80097BC8, (s32)D_800971F0, 0x50032, 0x19200C0,
    5,
};
s32 D_8009806C[] = {
    (s32)D_80097BD0, (s32)D_80097208, 0x50032, 0x19200C0,
    5,
};
s32 D_80098080[] = {
    (s32)D_80097BD8, (s32)D_80097220, 0x50032, 0x19200C0,
    5,
};
s32 D_80098094[] = {
    (s32)D_80097BE0, (s32)D_80097238, 0x50032, 0x19200C0,
    5,
};
s32 D_800980A8[] = {
    (s32)D_80097BE8, (s32)D_80097250, 0x50032, 0x19200C0,
    5,
};
s32 D_800980BC[] = {
    (s32)D_80097BF0, (s32)D_80097268, 0x50032, 0x19200C0,
    5,
};
s32 D_800980D0[] = {
    (s32)D_80097BF8, (s32)D_80097280, 0x50032, 0x19200C0,
    5,
};
s32 D_800980E4[] = {
    (s32)D_80097C00, (s32)D_80097298, 0x50032, 0x19200C0,
    5,
};
s32 D_800980F8[] = {
    (s32)D_80097C08, (s32)D_800972B0, 0x50032, 0x19200C0,
    5,
};
s32 D_8009810C[] = {
    (s32)D_80097C10, (s32)D_800972C8, 0x50032, 0x19200C0,
    5,
};
s32 D_80098120[] = {
    (s32)D_80097C18, (s32)D_800972E0, 0x50032, 0x19200C0,
    5,
};
s32 D_80098134[] = {
    (s32)D_80097C20, (s32)D_800972F8, 0x50032, 0x19200C0,
    5,
};
s32 D_80098148[] = {
    (s32)D_80097C28, (s32)D_80097310, 0x50032, 0x19200C0,
    5,
};
s32 D_8009815C[] = {
    (s32)D_80097C30, (s32)D_80097328, 0x50032, 0x19200C0,
    5,
};
s32 D_80098170[] = {
    (s32)D_80097C38, (s32)D_80097340, 0x50032, 0x19200C0,
    5,
};
s32 D_80098184[] = {
    (s32)D_80097C40, (s32)D_80097358, 0x60033, 0x8B00F2,
    1,
};
s32 D_80098198[] = {
    (s32)D_80097C48, (s32)D_80097370, 0x70034, 0x178012F,
    5,
};
s32 D_800981AC[] = {
    (s32)D_80097C50, (s32)D_80097388, 0x70034, 0x178012F,
    5,
};
s32 D_800981C0[] = {
    (s32)D_80097C58, (s32)D_800973A0, 0x70034, 0x178012F,
    5,
};
s32 D_800981D4[] = {
    (s32)D_80097C60, (s32)D_800973B8, 0x70034, 0x178012F,
    5,
};
s32 D_800981E8[] = {
    (s32)D_80097C68, (s32)D_800973D0, 0x70034, 0x178012F,
    5,
};
s32 D_800981FC[] = {
    (s32)D_80097C70, (s32)D_800973E8, 0x70034, 0x178012F,
    5,
};
s32 D_80098210[] = {
    (s32)D_80097C78, (s32)D_80097400, 0x70034, 0x178012F,
    5,
};
s32 D_80098224[] = {
    (s32)D_80097C80, (s32)D_80097418, 0x70034, 0x178012F,
    5,
};
s32 D_80098238[] = {
    (s32)D_80097C88, (s32)D_80097430, 0x70034, 0x178012F,
    5,
};
s32 D_8009824C[] = {
    (s32)D_80097C90, (s32)D_80097448, 0x70034, 0x178012F,
    5,
};
s32 D_80098260[] = {
    (s32)D_80097C98, (s32)D_80097460, 0x70034, 0x178012F,
    5,
};
s32 D_80098274[] = {
    (s32)D_80097CA0, (s32)D_80097478, 0x70034, 0x178012F,
    5,
};
s32 D_80098288[] = {
    (s32)D_80097CA8, (s32)D_80097490, 0x70034, 0x178012F,
    5,
};
s32 D_8009829C[] = {
    (s32)D_80097CB0, (s32)D_800974A8, 0x70034, 0x178012F,
    5,
};
s32 D_800982B0[] = {
    (s32)D_80097CB8, (s32)D_800974C0, 0x70034, 0x178012F,
    5,
};
s32 D_800982C4[] = {
    (s32)D_80097CC0, (s32)D_800974D8, 0x80035, 0x17000E0,
    5,
};
s32 D_800982D8[] = {
    (s32)D_80097CC8, (s32)D_800974F0, 0x80035, 0x17000E0,
    5,
};
s32 D_800982EC[] = {
    (s32)D_80097CD0, (s32)D_80097508, 0x80035, 0x17000E0,
    5,
};
s32 D_80098300[] = {
    (s32)D_80097CD8, (s32)D_80097520, 0x80035, 0x17000E0,
    5,
};
s32 D_80098314[] = {
    (s32)D_80097CE0, (s32)D_80097538, 0x80035, 0x17000E0,
    5,
};
s32 D_80098328[] = {
    (s32)D_80097CE8, (s32)D_80097550, 0x80035, 0x17000E0,
    5,
};
s32 D_8009833C[] = {
    (s32)D_80097CF0, (s32)D_80097568, 0x80035, 0x17000E0,
    5,
};
s32 D_80098350[] = {
    (s32)D_80097CF8, (s32)D_80097580, 0x80035, 0x17000E0,
    5,
};
s32 D_80098364[] = {
    (s32)D_80097D00, (s32)D_80097598, 0x80035, 0x17000E0,
    5,
};
s32 D_80098378[] = {
    (s32)D_80097D08, (s32)D_800975B0, 0x80035, 0x17000E0,
    5,
};
s32 D_8009838C[] = {
    (s32)D_80097D10, (s32)D_800975C8, 0x80035, 0x17000E0,
    5,
};
s32 D_800983A0[] = {
    (s32)D_80097D18, (s32)D_800975E0, 0x80035, 0x17000E0,
    5,
};
s32 D_800983B4[] = {
    (s32)D_80097D20, (s32)D_800975F8, 0x80035, 0x17000E0,
    5,
};
s32 D_800983C8[] = {
    (s32)D_80097D28, (s32)D_80097610, 0x80035, 0x17000E0,
    5,
};
s32 D_800983DC[] = {
    (s32)D_80097D30, (s32)D_80097628, 0x80035, 0x17000E0,
    5,
};
s32 D_800983F0[] = {
    (s32)D_80097D38, (s32)D_80097640, 0x90036, 0x1800100,
    5,
};
s32 D_80098404[] = {
    (s32)D_80097D40, (s32)D_80097658, 0x90036, 0x1800100,
    5,
};
s32 D_80098418[] = {
    (s32)D_80097D48, (s32)D_80097670, 0x90036, 0x1800100,
    5,
};
s32 D_8009842C[] = {
    (s32)D_80097D50, (s32)D_80097688, 0x90036, 0x1800100,
    5,
};
s32 D_80098440[] = {
    (s32)D_80097D58, (s32)D_800976A0, 0x90036, 0x1800100,
    5,
};
s32 D_80098454[] = {
    (s32)D_80097D60, (s32)D_800976B8, 0x90036, 0x1800100,
    5,
};
s32 D_80098468[] = {
    (s32)D_80097D68, (s32)D_800976D0, 0x90036, 0x1800100,
    5,
};
s32 D_8009847C[] = {
    (s32)D_80097D70, (s32)D_800976E8, 0x90036, 0x1800100,
    5,
};
s32 D_80098490[] = {
    (s32)D_80097D78, (s32)D_80097700, 0x90036, 0x1800100,
    5,
};
s32 D_800984A4[] = {
    (s32)D_80097D80, (s32)D_80097718, 0x90036, 0x1800100,
    5,
};
s32 D_800984B8[] = {
    (s32)D_80097D88, (s32)D_80097730, 0x90036, 0x1800100,
    5,
};
s32 D_800984CC[] = {
    (s32)D_80097D90, (s32)D_80097748, 0x90036, 0x1800100,
    5,
};
s32 D_800984E0[] = {
    (s32)D_80097D98, (s32)D_80097760, 0x90036, 0x1800100,
    5,
};
s32 D_800984F4[] = {
    (s32)D_80097DA0, (s32)D_80097778, 0x90036, 0x1800100,
    5,
};
s32 D_80098508[] = {
    (s32)D_80097DA8, (s32)D_80097790, 0x90036, 0x1800100,
    5,
};
s32 D_8009851C[] = {
    (s32)D_80097DB0, (s32)D_800977A8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098530[] = {
    (s32)D_80097DB8, (s32)D_800977C0, 0xA0037, 0x1680110,
    5,
};
s32 D_80098544[] = {
    (s32)D_80097DC0, (s32)D_800977D8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098558[] = {
    (s32)D_80097DC8, (s32)D_800977F0, 0xA0037, 0x1680110,
    5,
};
s32 D_8009856C[] = {
    (s32)D_80097DD0, (s32)D_80097808, 0xA0037, 0x1680110,
    5,
};
s32 D_80098580[] = {
    (s32)D_80097DD8, (s32)D_80097820, 0xA0037, 0x1680110,
    5,
};
s32 D_80098594[] = {
    (s32)D_80097DE0, (s32)D_80097838, 0xA0037, 0x1680110,
    5,
};
s32 D_800985A8[] = {
    (s32)D_80097DE8, (s32)D_80097850, 0xA0037, 0x1680110,
    5,
};
s32 D_800985BC[] = {
    (s32)D_80097DF0, (s32)D_80097868, 0xA0037, 0x1680110,
    5,
};
s32 D_800985D0[] = {
    (s32)D_80097DF8, (s32)D_80097880, 0xA0037, 0x1680110,
    5,
};
s32 D_800985E4[] = {
    (s32)D_80097E00, (s32)D_80097898, 0xA0037, 0x1680110,
    5,
};
s32 D_800985F8[] = {
    (s32)D_80097E08, (s32)D_800978B0, 0xA0037, 0x1680110,
    5,
};
s32 D_8009860C[] = {
    (s32)D_80097E10, (s32)D_800978C8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098620[] = {
    (s32)D_80097E18, (s32)D_800978E0, 0xA0037, 0x1680110,
    5,
};
s32 D_80098634[] = {
    (s32)D_80097E20, (s32)D_800978F8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098648[] = {
    (s32)D_80097E28, (s32)D_80097910, 0xB0039, 0x198012F,
    5,
};
s32 D_8009865C[] = {
    (s32)D_80097E30, (s32)D_80097928, 0xB0039, 0x198012F,
    5,
};
s32 D_80098670[] = {
    (s32)D_80097E38, (s32)D_80097940, 0xB0039, 0x198012F,
    5,
};
s32 D_80098684[] = {
    (s32)D_80097E40, (s32)D_80097958, 0xB0039, 0x198012F,
    5,
};
s32 D_80098698[] = {
    (s32)D_80097E48, (s32)D_80097970, 0xB0039, 0x198012F,
    5,
};
s32 D_800986AC[] = {
    (s32)D_80097E50, (s32)D_80097988, 0xB0039, 0x198012F,
    5,
};
s32 D_800986C0[] = {
    (s32)D_80097E58, (s32)D_800979A0, 0xB0039, 0x198012F,
    5,
};
s32 D_800986D4[] = {
    (s32)D_80097E60, (s32)D_800979B8, 0xB0039, 0x198012F,
    5,
};
s32 D_800986E8[] = {
    (s32)D_80097E68, (s32)D_800979D0, 0xB0039, 0x198012F,
    5,
};
s32 D_800986FC[] = {
    (s32)D_80097E70, (s32)D_800979E8, 0xB0039, 0x198012F,
    5,
};
s32 D_80098710[] = {
    (s32)D_80097E78, (s32)D_80097A00, 0xB0039, 0x198012F,
    5,
};
s32 D_80098724[] = {
    (s32)D_80097E80, (s32)D_80097A18, 0xB0039, 0x198012F,
    5,
};
s32 D_80098738[] = {
    (s32)D_80097E88, (s32)D_80097A30, 0xB0039, 0x198012F,
    5,
};
s32 D_8009874C[] = {
    (s32)D_80097E90, (s32)D_80097A48, 0xB0039, 0x198012F,
    5,
};
s32 D_80098760[] = {
    (s32)D_80097E98, (s32)D_80097A60, 0xB0039, 0x198012F,
    5,
};
s32 D_80098774[] = {
    (s32)D_80097EA0, (s32)D_80097A78, 0xC003F, 0x18800B0,
    1,
};
s32 D_80098788[] = {
    (s32)D_80097EEC, (s32)D_80097A9C, 0xC003F, 0x10900B0,
    1,
};
s32 D_8009879C[] = {
    (s32)D_80097EF4, (s32)D_80097AC0, 0xD009D, 0x1800100,
    5,
};
s32 D_800987B0[] = {
    (s32)D_80097EFC, 0, 0xE009E, 0x1490150,
    1,
};
s32 D_800987C4[] = {
    (s32)D_80097F04, (s32)D_80097AD8, 0xF009F, 0x198012F,
    5,
};
s32 D_800987D8[] = {
    (s32)D_80097F0C, (s32)D_80097AF0, 0x1000A0, 0x1680110,
    5,
};
s32 D_800987EC[] = {
    (s32)D_80097F14, (s32)D_80097B08, 0x1100A1, 0x17000E0,
    5,
};
s32 D_80098800[] = {
    (s32)D_80097F1C, (s32)D_80097B20, 0x1200A2, 0x178012F,
    5,
};
s32 D_80098814[] = {
    (s32)D_80097F24, (s32)D_80097B38, 0x1300AE, 0x19200C0,
    5,
};
s32 D_80098828[] = {
    (s32)D_80097F2C, (s32)D_80097F40, (s32)D_80097F54, (s32)D_80097F68,
    (s32)D_80097F7C, (s32)D_80097F90, (s32)D_80097FA4, (s32)D_80097FB8,
    (s32)D_80097FCC, (s32)D_80097FE0, (s32)D_80097FF4, (s32)D_80098008,
    (s32)D_8009801C, (s32)D_80098030, (s32)D_80098044, (s32)D_80098058,
    (s32)D_8009806C, (s32)D_80098080, (s32)D_80098094, (s32)D_800980A8,
    (s32)D_800980BC, (s32)D_800980D0, (s32)D_800980E4, (s32)D_800980F8,
    (s32)D_8009810C, (s32)D_80098120, (s32)D_80098134, (s32)D_80098148,
    (s32)D_8009815C, (s32)D_80098170, (s32)D_80098184, (s32)D_80098198,
    (s32)D_800981AC, (s32)D_800981C0, (s32)D_800981D4, (s32)D_800981E8,
    (s32)D_800981FC, (s32)D_80098210, (s32)D_80098224, (s32)D_80098238,
    (s32)D_8009824C, (s32)D_80098260, (s32)D_80098274, (s32)D_80098288,
    (s32)D_8009829C, (s32)D_800982B0, (s32)D_800982C4, (s32)D_800982D8,
    (s32)D_800982EC, (s32)D_80098300, (s32)D_80098314, (s32)D_80098328,
    (s32)D_8009833C, (s32)D_80098350, (s32)D_80098364, (s32)D_80098378,
    (s32)D_8009838C, (s32)D_800983A0, (s32)D_800983B4, (s32)D_800983C8,
    (s32)D_800983DC, (s32)D_800983F0, (s32)D_80098404, (s32)D_80098418,
    (s32)D_8009842C, (s32)D_80098440, (s32)D_80098454, (s32)D_80098468,
    (s32)D_8009847C, (s32)D_80098490, (s32)D_800984A4, (s32)D_800984B8,
    (s32)D_800984CC, (s32)D_800984E0, (s32)D_800984F4, (s32)D_80098508,
    (s32)D_8009851C, (s32)D_80098530, (s32)D_80098544, (s32)D_80098558,
    (s32)D_8009856C, (s32)D_80098580, (s32)D_80098594, (s32)D_800985A8,
    (s32)D_800985BC, (s32)D_800985D0, (s32)D_800985E4, (s32)D_800985F8,
    (s32)D_8009860C, (s32)D_80098620, (s32)D_80098634, (s32)D_80098648,
    (s32)D_8009865C, (s32)D_80098670, (s32)D_80098684, (s32)D_80098698,
    (s32)D_800986AC, (s32)D_800986C0, (s32)D_800986D4, (s32)D_800986E8,
    (s32)D_800986FC, (s32)D_80098710, (s32)D_80098724, (s32)D_80098738,
    (s32)D_8009874C, (s32)D_80098760, (s32)D_80098774, (s32)D_80098788,
    (s32)D_8009879C, (s32)D_800987B0, (s32)D_800987C4, (s32)D_800987D8,
    (s32)D_800987EC, (s32)D_80098800, (s32)D_80098814, 0,
};
s32 D_800989F8[] = {
    0x2440101, 0x1000252, 0x1380004, 282,
    0x2010000, 0x14A0240, 0x4514A, 0x1660087,
    0, 0x6400001, 0x433E013E, 0x1650004,
    161, 0x10000, 0x10640, 0,
    0x1A100C0, 0, 0x6400001, 0x7020102,
    0x1650004, 161, 0x3010000, 1741,
    0, 0x15200A0, 0, 0xA400001,
    0x49440144, 0x1650004, 241, 0x10000,
    0x1080A40, 0x40D08, 0xF10165, 0,
    0xA400001, 0x130F010F, 0x3E0004, 326,
    0x10000, 0x140A48, 0, 0xCA0080,
    0, 0xA490001, 21, 0xC80000,
    183, 0x10000, 0x1320440, 0x43732,
    0xA10165, 200, 0x8400001, 0x3D380138,
    0x1650004, 0x11800F1, 0, 0,
    0, 0, 0,
};
s32 D_80098AF4[] = {
    65535, 65535, 0x2010001, 0xF40368,
    1, 0, 65535, 65535,
    0x2120001, 0xA502FE, 1, 0,
    65535, 65535, 0x10006, 0,
    0, 0, 65535, 65535,
    0x80005, 0, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*FIELDSTG_initFuncs[])(void) = {func_80091124};
s32 D_80098B70 = (s32)func_80091298;
s32 D_80098B74 = (s32)func_8009132C;
#if VERSION_US
s32 D_80098B78[] = {
    1320, 0x800A4CA4, 0x1120040, 0,
    0, 1325, 0x800A4D88, 0x1120041,
    0, 0, 1331, 0x800A4E6C,
    0x1120000, 0, 0, 1332,
    0, 0, (s32)func_80083F8C, 0,
    1333, 0x800A4FE8, 0x1120001, 0,
    (s32)func_80090864, 1334, 0x800A5180, 0x1120003,
    0, (s32)func_800908C4, 1336, 0x800A5264,
    0x1120004, 0, 0, 1337,
    0, 0, (s32)func_80083FBC, 0,
    1338, 0x800A53E0, 0x1120006, 0,
    (s32)func_800908F0, 1339, 0x800A5578, 0x1120007,
    0, (s32)func_80090950, 1341, 0x800A565C,
    0x1120008, 0, 0, 1342,
    0, 0, (s32)func_80083FF0, 0,
    1343, 0x800A57D8, 0x112000A, 0,
    (s32)func_8009097C, 1344, 0x800A5970, 0x112000B,
    0, (s32)func_800909DC, 1346, 0x800A5A54,
    0x112000C, 0, 0, 1347,
    0, 0, (s32)func_80084024, 0,
    1348, 0x800A5BD0, 0x112000E, 0,
    (s32)func_80090A08, 1349, 0x800A5D68, 0x112000F,
    0, (s32)func_80090A68, 1351, 0x800A5E4C,
    0x1120010, 0, 0, 1352,
    0, 0, (s32)func_80084058, 0,
    1353, 0x800A5FC8, 0x1120012, 0,
    (s32)func_80090A94, 1354, 0x800A6160, 0x1120013,
    0, (s32)func_80090AF4, 1356, 0x800A624C,
    0x1120014, 0, 0, 1357,
    0, 0, (s32)func_8008408C, 0,
    1358, 0x800A63C8, 0x1120016, 0,
    (s32)func_80090B20, 1359, 0x800A6560, 0x1120017,
    0, (s32)func_80090B80, 1361, 0x800A6644,
    0x1120018, 0, 0, 1362,
    0, 0, (s32)func_800840C0, 0,
    1363, 0x800A67C0, 0x112001A, 0,
    (s32)func_80090BAC, 1364, 0x800A6960, 0x112001B,
    0, (s32)func_80090C0C, 1366, 0x800A6A44,
    0x112001C, 0, 0, 1367,
    0, 0, (s32)func_800840F4, 0,
    1368, 0x800A6BC0, 0x112001E, 0,
    (s32)func_80090C38, 1369, 0x800A6D58, 0x112001F,
    0, (s32)func_80090C98, 1371, 0x800A6E3C,
    0x1120020, 0, 0, 1372,
    0, 0, (s32)func_80084128, 0,
    1373, 0x800A6FB8, 0x1120022, 0,
    (s32)func_80090CC4, 1374, 0x800A7150, 0x1120023,
    0, (s32)func_80090D24, 1376, 0x800A7234,
    0x1120024, 0, 0, 1377,
    0, 0, (s32)func_8008415C, 0,
    1378, 0x800A73B0, 0x1120026, 0,
    (s32)func_80090D50, 1379, 0x800A7548, 0x1120027,
    0, (s32)func_80090DB0, 1381, 0x800A762C,
    0x1120028, 0, 0, 1382,
    0, 0, (s32)func_80084190, 0,
    1383, 0x800A77A8, 0x112002A, 0,
    (s32)func_80090DDC, 1384, 0x800A7940, 0x112002B,
    0, (s32)func_80090E3C, 1386, 0x800A7A24,
    0x112002C, 0, 0, 1387,
    0, 0, (s32)func_800841C4, 0,
    1388, 0x800A7BA0, 0x112002E, 0,
    (s32)func_80090E68, 1389, 0x800A7D4C, 0x112002F,
    0, (s32)func_80090EC8, 1391, 0x800A7E30,
    0x1120030, 0, 0, 1392,
    0, 0, (s32)func_800841F8, 0,
    1393, 0x800A7FAC, 0x1120032, 0,
    (s32)func_80090EF4, 1394, 0x800A8134, 0x1120033,
    0, (s32)func_80090F54, 1396, 0x800A8218,
    0x1120034, 0, 0, 1397,
    0, 0, (s32)func_8008422C, 0,
    1398, 0x800A8398, 0x1120036, 0,
    (s32)func_80090F80, 1399, 0x800A8520, 0x1120037,
    0, (s32)func_80090FE0, 1401, 0x800A8604,
    0x1120038, 0, 0, 1402,
    0, 0, (s32)func_80084260, 0,
    1403, 0x800A8780, 0x112003A, 0,
    (s32)func_8009100C, 1404, 0x800A8928, 0x112003B,
    0, (s32)func_8009106C, 1406, 0x800A8A0C,
    0x112003C, 0, 0, 1407,
    0, 0, (s32)func_80084294, 0,
    1408, 0x800A8B8C, 0x112003E, 0,
    (s32)func_80091098, 1409, 0x800A8D24, 0x112003F,
    0, (s32)func_800910F8, -1, 0,
    0, 0, 0,
};
#elif VERSION_EU
s32 D_80098B78[] = {
    1320, 0x800A5DE0, 0x1190040, 0,
    0, 1325, 0x800A5EC4, 0x1190041,
    0, 0, 1331, 0x800A5FA8,
    0x1190000, 0, 0, 1332,
    0, 0, (s32)func_80083F8C, 0,
    1333, 0x800A6124, 0x1190001, 0,
    (s32)func_80090864, 1334, 0x800A62BC, 0x1190003,
    0, (s32)func_800908C4, 1336, 0x800A63A0,
    0x1190004, 0, 0, 1337,
    0, 0, (s32)func_80083FBC, 0,
    1338, 0x800A651C, 0x1190006, 0,
    (s32)func_800908F0, 1339, 0x800A66B4, 0x1190007,
    0, (s32)func_80090950, 1341, 0x800A6798,
    0x1190008, 0, 0, 1342,
    0, 0, (s32)func_80083FF0, 0,
    1343, 0x800A6914, 0x119000A, 0,
    (s32)func_8009097C, 1344, 0x800A6AAC, 0x119000B,
    0, (s32)func_800909DC, 1346, 0x800A6B90,
    0x119000C, 0, 0, 1347,
    0, 0, (s32)func_80084024, 0,
    1348, 0x800A6D0C, 0x119000E, 0,
    (s32)func_80090A08, 1349, 0x800A6EA4, 0x119000F,
    0, (s32)func_80090A68, 1351, 0x800A6F88,
    0x1190010, 0, 0, 1352,
    0, 0, (s32)func_80084058, 0,
    1353, 0x800A7104, 0x1190012, 0,
    (s32)func_80090A94, 1354, 0x800A729C, 0x1190013,
    0, (s32)func_80090AF4, 1356, 0x800A7388,
    0x1190014, 0, 0, 1357,
    0, 0, (s32)func_8008408C, 0,
    1358, 0x800A7504, 0x1190016, 0,
    (s32)func_80090B20, 1359, 0x800A769C, 0x1190017,
    0, (s32)func_80090B80, 1361, 0x800A7780,
    0x1190018, 0, 0, 1362,
    0, 0, (s32)func_800840C0, 0,
    1363, 0x800A78FC, 0x119001A, 0,
    (s32)func_80090BAC, 1364, 0x800A7A9C, 0x119001B,
    0, (s32)func_80090C0C, 1366, 0x800A7B80,
    0x119001C, 0, 0, 1367,
    0, 0, (s32)func_800840F4, 0,
    1368, 0x800A7CFC, 0x119001E, 0,
    (s32)func_80090C38, 1369, 0x800A7E94, 0x119001F,
    0, (s32)func_80090C98, 1371, 0x800A7F78,
    0x1190020, 0, 0, 1372,
    0, 0, (s32)func_80084128, 0,
    1373, 0x800A80F4, 0x1190022, 0,
    (s32)func_80090CC4, 1374, 0x800A828C, 0x1190023,
    0, (s32)func_80090D24, 1376, 0x800A8370,
    0x1190024, 0, 0, 1377,
    0, 0, (s32)func_8008415C, 0,
    1378, 0x800A84EC, 0x1190026, 0,
    (s32)func_80090D50, 1379, 0x800A8684, 0x1190027,
    0, (s32)func_80090DB0, 1381, 0x800A8768,
    0x1190028, 0, 0, 1382,
    0, 0, (s32)func_80084190, 0,
    1383, 0x800A88E4, 0x119002A, 0,
    (s32)func_80090DDC, 1384, 0x800A8A7C, 0x119002B,
    0, (s32)func_80090E3C, 1386, 0x800A8B60,
    0x119002C, 0, 0, 1387,
    0, 0, (s32)func_800841C4, 0,
    1388, 0x800A8CDC, 0x119002E, 0,
    (s32)func_80090E68, 1389, 0x800A8E88, 0x119002F,
    0, (s32)func_80090EC8, 1391, 0x800A8F6C,
    0x1190030, 0, 0, 1392,
    0, 0, (s32)func_800841F8, 0,
    1393, 0x800A90E8, 0x1190032, 0,
    (s32)func_80090EF4, 1394, 0x800A9270, 0x1190033,
    0, (s32)func_80090F54, 1396, 0x800A9354,
    0x1190034, 0, 0, 1397,
    0, 0, (s32)func_8008422C, 0,
    1398, 0x800A94D4, 0x1190036, 0,
    (s32)func_80090F80, 1399, 0x800A965C, 0x1190037,
    0, (s32)func_80090FE0, 1401, 0x800A9740,
    0x1190038, 0, 0, 1402,
    0, 0, (s32)func_80084260, 0,
    1403, 0x800A98BC, 0x119003A, 0,
    (s32)func_8009100C, 1404, 0x800A9A64, 0x119003B,
    0, (s32)func_8009106C, 1406, 0x800A9B48,
    0x119003C, 0, 0, 1407,
    0, 0, (s32)func_80084294, 0,
    1408, 0x800A9CC8, 0x119003E, 0,
    (s32)func_80091098, 1409, 0x800A9E60, 0x119003F,
    0, (s32)func_800910F8, -1, 0,
    0, 0, 0,
};
#endif
FieldState D_800990B4 = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, {0}, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    func_800913CC, func_80091398, func_800913B4, func_80091490,
};
#if VERSION_US
s32 FIELDSTG_fileEntries[] = {
    0, 0x17800CA, 0x1790070, 0x17A0071,
    0x17B005F, 0x17C005F, 0x17D0073, 0x17E006E,
    0x17F006B, 0x1800072, 0x181009B, 0x18200A8,
    0x18300AD, 0x184003D, 0x184003D, 0x184003D,
    0x185002A, 0x3050020, 0x3040020, 0x3690020,
    0x2E60010, 0x30D002D, 0x2E70010, 0x2E50021,
    0x2E8001E, 0x30A0010, 0x30B0021, 0x308000E,
    0x3780007, 0x4160012, 0x2D30020, 0x3180008,
    0x3F10014, 0x3EC0015, 0x2EC003C, 0x2EB0037,
    0x3F10014, 0x30C0020, 0x30C0020, 0x30C0020,
    0x2FC0004, 0x2FD0004, 0x2FE0004, 0x2FB0020,
    0x2FB0020, 0x3070020, 0x3050020, 0x3060020,
    0x2F60015, 0x3030020, 0x3010020, 0x3040020,
    0x3000020, 0x3020020, 0x2FF0020, 0x3690020,
    0x3670020, 0x3680025, 0x3750020, 0x3760008,
    0x2D60020, 0x3660008, 0x40B0005, 0,
    0x2ED0032, 0x2EE003B, 0x2EF005A, 0x2E0001E,
    0x30B0021, 0x3490020, 0x3490020, 0x3490020,
    0x3490020, 0x3490020, 0x3490020, 0x40A0014,
    0x40A0014, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x3EC0015, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x3EC0015, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x40A0014, 0x3F10014, 0x3770004, 0x4160012,
    0x4160012, 0x4160012, 0x4160012, 0x4160012,
    0x4160012, 0x3640012, 0x3640012, 0x4E40004,
    0x4090008, 0x5410042, 0x4E50032, 0x63B0032,
    0x4E0002E, 0x3630037, 0x63C006E, 0x63E006E,
    0x4E20020, 0x3470020, 0x3470020, 0x30C0020,
    0, 0, 0x63D0008, 0x3460020,
    0x3460020, 0x3460020, 0x3D30032, 0x3470020,
    0x2E60010, 0x2E60010, 0x2D70020, 0x37B0008,
    0x37C0008, 0x41D0008, 0x37E0008, 0x37D0008,
    0x4080008, 0x41C0008, 0x7C20011, 0x7C30011,
    0x3650008, 0x3DE000F, 0x309000F, 0x34D000E,
    0x34B0010, 0x34E000E, 0x40C0011, 0x34A0012,
    0x34C000E, 0x2D50020, 0x2D80022, 0x2D90020,
    0x2DB0020, 0x2DC0020, 0x2DA0022, 0x3610009,
    0x3610009, 0x3610009, 0x3DF0008, 0x3DC000A,
    0x3480020, 0x7870002, 0x7860008, 0x7860008,
    0x7860008, 0x402002D, 0x402002D, 0x402002D,
    0x402002D, 0x402002D, 0x402002D, 0x2FB0020,
    0x3490020, 0x3DD0008, 0x4050008, 0x4040009,
    0x4010006, 0x4060009, 0x4030008, 0x37A0009,
    0x3790009, 0x4070009, 0x402002D, 0x402002D,
    0x402002D, 0x402002D, 0x2E90026, 0x2EA0026,
    0x7830032, 0x7840032, 0x785003A, 0x7300008,
    0x3640012, 0x3640012, 0x3640012, 0x3640012,
    0x3640012, 0x3640012, 0x3640012, 0x3640012,
    0x3600016, 0x3620012, 0x3440023, 0x3440023,
    0x3440023, 0x799000C, 0, 0,
    0x2DE001E, 0x2DF001E, 0x2E1001E, 0x2E2001E,
    0x2DF001E, 0x2D4001E, 0x4160012, 0x3620012,
    0x3450022, 0x3450022, 0x36A0020, 0x36A0020,
    0x36A0020, 0x72E0019, 0x7980021, 0x7C60013,
    0x7C60013, 0x7C60013, 0x7C60013, 0,
    0, 0, 0, 0,
    0, 0, 0x2EC003C, 0x2EC003C,
    0x2EB0037, 0x2EB0037, 0x30C0020, 0x2ED0032,
    0x2ED0032, 0x2EF005A, 0x2EF005A, 0x2EE003B,
    0x2EE003B, 0x785003A, 0x785003A, 0x7840032,
    0x7840032, 0x7830032, 0x7830032, 0x3DA0008,
    0x3DA0008, 0x3DA0008, 0x3DA0008, 0x3DA0008,
    0x3DA0008, 0x3DA0008, 0x3DA0008, 0x402002D,
    0x3490020, 0x3490020, 0x2E0001E, 0x2DD001C,
    0, 0x3460020, 0x4E10020, 0x3460020,
    0x3460020, 0x3D40008, 0x3DB0008, 0x3D70008,
    0x3D90008, 0x3D80008, 0x4E30004, 0x3780007,
    0, 0x3490020, 0, 0,
    0x3D30032, 0x3D30032, 0x3D30032, 0x3D30032,
    0x3D30032, 0x3D30032, 0x3D30032, 0x3D30032,
    0x3030020, 0x402002D, 0x79E0029, 0x72F0026,
    0, 0x3630037, 0x3DC000A, 0x79B0004,
    0, 0, 0, 0,
    0, 0x3690020, 0x3070020, 0x4160012,
    0x4160012, 0x3640012, 0x3620012, 0x3460020,
    0x1800072, 0x3440023, 0x3440023, 0x3460020,
    0x3460020, 0x3460020, 0x3490020, 0x3490020,
    0x3490020, 0x3490020, 0x3490020, 0x3490020,
    0x3440023, 0x3440023, 0x402002D, 0x3040020,
    0x8060008, 0x7C5002D, 0x7C4002D, 0x79A0002,
    0x4160012, 0x4160012, 0x4160012, 0x3640012,
    0x3640012, 0x3640012, 0x3D6005F, 0x3D50023,
    0x828000E, 0x72C0037, 0x72D0037, 0x7C70005,
    0x7C80008, 0x4E6006E, 0x4E6006E, 0x4E6006E,
    0x4E6006E, 0x4E6006E, 0x4E6006E, 0x4E6006E,
    0x3EC0015, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x3EC0015, 0x3630037, 0x3630037, 0x3EC0015,
    0x3630037, 0x3630037, 0x3630037, 0x828000E,
    0x828000E, 0x828000E, 0x828000E, 0x828000E,
    0x828000E, 0x828000E, 0x828000E, 0x828000E,
    0x828000E, 0x4160012, 0x4160012, 0x3640012,
    0x3640012, 0x8830019, 0x8830019, 0x8880019,
    0x8880019, 0x8840014, 0x8840014, 0x8860032,
    0x8860032, 0x8850019, 0x8850019, 0x8800019,
    0x8800019, 0x8820014, 0x8810014, 0x8810014,
    0x8810014, 0x30C0020, 0x30C0020, 0x30C0020,
    0x88B0002, 0x88B0002, 0x88B0002, 0x3640012,
    0x3640012, 0x88F0008, 0x30C0020, 0x30C0020,
    0x72E0019,
};
u8 D_80099758[] = {
    0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x28,
    0x20, 0x20, 0x28, 0x20, 0x20, 0x28, 0x38, 0x28,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x20, 0x20, 0x40, 0x20,
    0x20, 0x20, 0x20, 0x18, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x20, 0x20, 0x28, 0x30, 0x20, 0x18, 0x20,
    0x18, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x50, 0x40, 0x30, 0x48, 0x40,
    0x40, 0x28, 0x10, 0x18, 0x30, 0x38, 0x28, 0x20,
    0x20, 0x20, 0x28, 0x30, 0x20, 0x28, 0x20, 0x20,
    0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x20, 0x28,
    0x20, 0x28, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x18, 0x18, 0x20, 0x18, 0x18, 0x20, 0x28, 0x20,
    0x30, 0x30, 0x28, 0x28, 0x28, 0x40, 0x38, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x18, 0x38,
    0x20, 0x20, 0x18, 0x20, 0x20, 0x38, 0x38, 0x40,
    0x50, 0x48, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x38, 0x38, 0x20, 0x20, 0x20, 0x20, 0x30, 0x18,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x14, 0x20, 0x20, 0x14,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x28, 0x20,
    0x50, 0x20, 0x20, 0x14, 0x14, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x38, 0x38, 0x38, 0x38, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x38, 0x38,
    0x40, 0x40, 0x40, 0x38, 0x38, 0x14, 0x20, 0x20,
    0x40, 0x00, 0x00, 0x00,
};
StageEntry D_800998E4[] = {
    {512, 451, (void *)0x800A4D40},
    {513, 509, (void *)0x800A4CF0},
    {514, 452, (void *)0x800A5058},
    {515, 453, (void *)0x800A6310},
    {516, 545, (void *)0x800A52A0},
    {517, 549, (void *)0x800A4CF0},
    {518, 454, (void *)0x800A5ED8},
    {519, 455, (void *)0x800A5178},
    {520, 456, (void *)0x800A4CEC},
    {521, 580, (void *)0x800A4F20},
    {522, 457, (void *)0x800A4CEC},
    {523, 652, (void *)0x800A4CEC},
    {524, 458, (void *)0x800A4CEC},
    {525, 459, (void *)0x800A4CEC},
    {526, 460, (void *)0x800A4CEC},
    {527, 461, (void *)0x800A4CEC},
    {528, 462, (void *)(s32)func_800844B8},
    {529, 463, (void *)0x800A58DC},
    {530, 464, (void *)0x800A4CF0},
    {531, 465, (void *)0x800A535C},
    {532, 679, (void *)0x800A4D70},
    {533, 670, (void *)0x800A4CEC},
    {534, 859, (void *)0x800A4DA4},
    {535, 833, (void *)0x800A4D9C},
    {536, 829, (void *)0x800A526C},
    {537, 821, (void *)0x800A5C40},
    {538, 1014, (void *)0x800A4CEC},
    {539, 662, (void *)0x800A4D4C},
    {540, 1084, (void *)0x800A4F2C},
    {541, 466, (void *)0x800A4CF0},
    {542, 467, (void *)0x800A4D00},
    {543, 915, (void *)0x800A4CF0},
    {544, 919, (void *)0x800A4CF0},
    {545, 468, (void *)0x800A4CEC},
    {546, 469, (void *)0x800A4CEC},
    {547, 480, (void *)0x800A4CEC},
    {548, 526, (void *)0x800A4CEC},
    {549, 470, (void *)0x800A4CEC},
    {550, 471, (void *)0x800A4EDC},
    {551, 685, (void *)0x800A4CF0},
    {552, 1220, (void *)0x800A4D48},
    {553, 478, (void *)0x800A4D7C},
    {554, 1019, (void *)0x800A4D50},
    {555, 558, (void *)0x800A4F5C},
    {556, 910, (void *)0x800A4CF0},
    {557, 1245, (void *)0x800A5E84},
    {558, 1257, (void *)0x800A4D38},
    {559, 551, (void *)0x800A4CEC},
    {560, 481, (void *)0x800A4CEC},
    {561, 472, (void *)0x800A4CEC},
    {562, 878, (void *)0x800A4D14},
    {563, 1282, (void *)0x800A4D48},
    {564, 906, (void *)0x800A4D48},
    {565, 898, (void *)0x800A4F98},
    {566, 853, (void *)0x800A5EE0},
    {567, 473, (void *)0x800A4CF0},
    {568, 518, (void *)0x800A4CEC},
    {569, 482, (void *)0x800A4E4C},
    {570, 856, (void *)0x800A50F4},
    {571, 935, (void *)0x800A4CF0},
    {572, 1008, (void *)0x800A4D8C},
    {573, 952, (void *)0x800A4CEC},
    {574, 1023, (void *)0x800A4CEC},
    {575, 525, (void *)0x800A4CEC},
    {576, 532, (void *)0x800A4D38},
    {577, 948, (void *)0x800A4D44},
    {578, 574, (void *)0x800A4CEC},
    {579, 646, (void *)0x800A4D44},
    {580, 1349, (void *)0x800A4D4C},
    {581, 1394, (void *)0x800A4CEC},
    {582, 559, (void *)0x800A5848},
    {583, 1119, (void *)0x800A4D48},
    {584, 529, (void *)0x800A4F94},
    {585, 674, (void *)0x800A4CF0},
    {586, 1292, (void *)0x800A4D44},
    {587, 1045, (void *)0x800A4CF0},
    {588, 1138, (void *)0x800A4D38},
    {589, 1419, (void *)0x800A4D6C},
    {590, 1276, (void *)0x800A4D4C},
    {591, 1277, (void *)0x800A4CEC},
    {592, 1278, (void *)0x800A4CEC},
    {593, 1266, (void *)0x800A4CEC},
    {594, 1142, (void *)0x800A4D2C},
    {595, 1201, (void *)0x800A4CEC},
    {596, 1358, (void *)0x800A4D3C},
    {597, 1149, (void *)0x800A51D8},
    {598, 1150, (void *)0x800A50C8},
    {599, 1157, (void *)0x800A4F94},
    {600, 1165, (void *)0x800A50B8},
    {601, 1169, (void *)0x800A50B8},
    {602, 1177, (void *)0x800A4F94},
    {603, 1343, (void *)0x800A4CEC},
    {604, 1161, (void *)0x800A4D38},
    {605, 1208, (void *)0x800A4CF0},
    {606, 1185, (void *)0x800A4D38},
    {607, 1488, (void *)0x800A5318},
    {608, 1209, (void *)0x800A4D1C},
    {609, 1496, (void *)0x800A4CEC},
    {610, 1504, (void *)0x800A4CEC},
    {611, 1512, (void *)0x800A4CEC},
    {612, 1520, (void *)0x800A4CEC},
    {613, 666, (void *)0x800A4CEC},
    {614, 1528, (void *)0x800A4CEC},
    {615, 1540, (void *)0x800A4CEC},
    {616, 1548, (void *)0x800A4CEC},
    {617, 1556, (void *)(s32)func_800A4EE8},
    {618, 1603, (void *)0x800A4DA8},
    {619, 1605, (void *)0x800A4FFC},
    {620, 1607, (void *)0x800A517C},
    {621, 1609, (void *)0x800A52E8},
    {622, 1610, (void *)0x800A4D30},
    {623, 1615, (void *)0x800A4CEC},
    {624, 508, (void *)0x800A4CF0},
    {625, 510, (void *)0x800A4CF0},
    {626, 520, (void *)0x800A4D84},
    {627, 521, (void *)0x800A4CF0},
    {628, 575, (void *)0x800A4CF0},
    {629, 577, (void *)0x800A4CF0},
    {630, 578, (void *)0x800A518C},
    {631, 579, (void *)0x800A4CEC},
    {632, 609, (void *)0x800A4F20},
    {633, 624, (void *)0x800A4CEC},
    {634, 657, (void *)0x800A4CEC},
    {635, 682, (void *)0x800A4CEC},
    {636, 686, (void *)0x800A4CEC},
    {637, 687, (void *)0x800A4CEC},
    {638, 643, (void *)0x800A4CEC},
    {639, 696, (void *)0x800A5210},
    {640, 794, (void *)0x800A4CEC},
    {641, 795, (void *)0x800A4CF0},
    {642, 811, (void *)0x800A4CEC},
    {643, 815, (void *)0x800A4CEC},
    {644, 825, (void *)0x800A4CEC},
    {645, 860, (void *)0x800A4CEC},
    {646, 861, (void *)0x800A4CEC},
    {647, 920, (void *)0x800A5024},
    {648, 921, (void *)0x800A5C94},
    {649, 1015, (void *)0x800A4CEC},
    {650, 1061, (void *)0x800A4CF0},
    {651, 1104, (void *)0x800A4F2C},
    {652, 1105, (void *)0x800A4CF0},
    {653, 1106, (void *)0x800A4CEC},
    {654, 1107, (void *)0x800A4CEC},
    {655, 1124, (void *)0x800A4CEC},
    {656, 1134, (void *)0x800A4CEC},
    {657, 1173, (void *)0x800A4CEC},
    {658, 1181, (void *)0x800A4CEC},
    {659, 1189, (void *)0x800A4CEC},
    {660, 1193, (void *)0x800A4CEC},
    {661, 1215, (void *)0x800A4D48},
    {662, 1219, (void *)0x800A4CF0},
    {663, 1225, (void *)0x800A4CEC},
    {664, 1229, (void *)0x800A4CEC},
    {665, 1233, (void *)0x800A4CF0},
    {666, 1243, (void *)0x800A4F48},
    {667, 1244, (void *)0x800A4CF0},
    {668, 1262, (void *)0x800A4DE0},
    {669, 1284, (void *)0x800A4CEC},
    {670, 1288, (void *)0x800A4CEC},
    {671, 1296, (void *)0x800A4CEC},
    {672, 1300, (void *)0x800A4CF0},
    {673, 1304, (void *)0x800A4CF0},
    {674, 1308, (void *)0x800A4CF0},
    {675, 1312, (void *)0x800A4CF0},
    {676, 1316, (void *)0x800A4CF0},
    {677, 1335, (void *)0x800A4CEC},
    {678, 1336, (void *)0x800A4CEC},
    {679, 1337, (void *)0x800A50B8},
    {680, 1338, (void *)0x800A4CF0},
    {681, 1339, (void *)0x800A4CEC},
    {682, 1344, (void *)0x800A4CEC},
    {683, 1370, (void *)0x800A4CEC},
    {684, 1374, (void *)0x800A4CEC},
    {685, 1378, (void *)0x800A4D38},
    {686, 1382, (void *)0x800A6324},
    {687, 1386, (void *)0x800A4CEC},
    {688, 1390, (void *)0x800A4D44},
    {689, 1398, (void *)0x800A4CEC},
    {690, 1402, (void *)0x800A4CEC},
    {691, 1406, (void *)0x800A4CEC},
    {692, 1410, (void *)0x800A4CEC},
    {693, 1414, (void *)0x800A4CEC},
    {694, 1415, (void *)0x800A4CEC},
    {695, 1423, (void *)0x800A4CEC},
    {696, 1427, (void *)0x800A4CEC},
    {697, 1431, (void *)0x800A4CEC},
    {698, 1435, (void *)0x800A4CEC},
    {699, 1439, (void *)0x800A4CEC},
    {700, 1443, (void *)0x800A4D44},
    {701, 1447, (void *)0x800A4CEC},
    {702, 1451, (void *)0x800A4D48},
    {703, 1455, (void *)0x800A4CEC},
    {704, 1459, (void *)0x800A4CEC},
    {705, 1463, (void *)0x800A4E18},
    {706, 1467, (void *)0x800A4E18},
    {707, 1471, (void *)0x800A4CEC},
    {708, 1475, (void *)0x800A4CEC},
    {709, 1479, (void *)0x800A4CEC},
    {710, 1483, (void *)0x800A4CF0},
    {711, 1487, (void *)0x800A4D2C},
    {712, 1492, (void *)0x800A4CEC},
    {713, 1500, (void *)0x800A4CEC},
    {714, 1508, (void *)0x800A4CEC},
    {715, 1516, (void *)0x800A4CEC},
    {716, 1524, (void *)0x800A4CEC},
    {717, 1527, (void *)0x800A4CEC},
    {718, 1536, (void *)0x800A4CEC},
    {719, 1544, (void *)0x800A4CEC},
    {720, 1552, (void *)0x800A4CEC},
    {721, 1572, (void *)(s32)func_800A4EE8},
    {722, 1604, (void *)0x800A4DA8},
    {723, 1606, (void *)0x800A4FFC},
    {724, 1608, (void *)0x800A517C},
    {725, 1611, (void *)0x800A4D64},
    {726, 1619, (void *)0x800A4CEC},
    {727, 474, (void *)0x800A6474},
    {728, 475, (void *)0x800A5574},
    {729, 476, (void *)0x800A51E0},
    {730, 1623, (void *)0x800A5518},
    {731, 1627, (void *)0x800A5890},
    {732, 1631, (void *)0x800A5A08},
    {733, 1635, (void *)0x800A52DC},
    {734, 1639, (void *)0x800A5048},
    {735, 1643, (void *)0x800A5024},
    {736, 1649, (void *)0x800A4E14},
    {737, 1653, (void *)0x800A4E1C},
    {738, 1657, (void *)0x800A4E14},
    {739, 1681, (void *)0x800A4E14},
    {740, 1685, (void *)0x800A4E14},
    {741, 1689, (void *)0x800A4E14},
    {742, 1693, (void *)0x800A4E14},
    {743, 1705, (void *)0x800A4E14},
    {744, 1697, (void *)0x800A4E18},
    {745, 1701, (void *)0x800A4E18},
    {746, 1661, (void *)0x800A4E18},
    {747, 1674, (void *)0x800A4E18},
    {748, 1675, (void *)0x800A4E18},
    {749, 1676, (void *)0x800A4E18},
    {750, 1677, (void *)0x800A4E18},
    {0, 0, 0},
};
#elif VERSION_EU
s32 FIELDSTG_fileEntries[] = {
    0, 0x18600CA, 0x1870070, 0x1880071,
    0x189005F, 0x18A005F, 0x18B0073, 0x18C006E,
    0x18D006B, 0x18E0072, 0x18F009B, 0x19000A8,
    0x19100AD, 0x192003D, 0x192003D, 0x192003D,
    0x193002A, 0x3140020, 0x3130020, 0x3790020,
    0x2F50010, 0x31C002D, 0x2F60010, 0x2F40021,
    0x2F7001E, 0x3190010, 0x31A0021, 0x317000E,
    0x3880007, 0x4260012, 0x2E20020, 0x3270008,
    0x4010014, 0x3FC0015, 0x2FB003C, 0x2FA0037,
    0x4010014, 0x31B0020, 0x31B0020, 0x31B0020,
    0x30B0004, 0x30C0004, 0x30D0004, 0x30A0020,
    0x30A0020, 0x3160020, 0x3140020, 0x3150020,
    0x3050015, 0x3120020, 0x3100020, 0x3130020,
    0x30F0020, 0x3110020, 0x30E0020, 0x3790020,
    0x3770020, 0x3780025, 0x3850020, 0x3860008,
    0x2E50020, 0x3760008, 0x41B0005, 0,
    0x2FC0032, 0x2FD003B, 0x2FE005A, 0x2EF001E,
    0x31A0021, 0x3580020, 0x3580020, 0x3580020,
    0x3580020, 0x3580020, 0x3580020, 0x41A0014,
    0x41A0014, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x3FC0015, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x3FC0015, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x41A0014, 0x4010014, 0x3870004, 0x4260012,
    0x4260012, 0x4260012, 0x4260012, 0x4260012,
    0x4260012, 0x3740012, 0x3740012, 0x4F40004,
    0x4190008, 0x5510042, 0x4F50032, 0x64B0032,
    0x4F0002E, 0x3730037, 0x64C006E, 0x64E006E,
    0x4F20020, 0x3560020, 0x3560020, 0x31B0020,
    0, 0, 0x64D0008, 0x3550020,
    0x3550020, 0x3550020, 0x3E30032, 0x3560020,
    0x2F50010, 0x2F50010, 0x2E60020, 0x38B0008,
    0x38C0008, 0x42D0008, 0x38E0008, 0x38D0008,
    0x4180008, 0x42C0008, 0x7D10011, 0x7D20011,
    0x3750008, 0x3EE000F, 0x318000F, 0x35C000E,
    0x35A0010, 0x35D000E, 0x41C0011, 0x3590012,
    0x35B000E, 0x2E40020, 0x2E70022, 0x2E80020,
    0x2EA0020, 0x2EB0020, 0x2E90022, 0x3710009,
    0x3710009, 0x3710009, 0x3EF0008, 0x3EC000A,
    0x3570020, 0x7960002, 0x7950008, 0x7950008,
    0x7950008, 0x412002D, 0x412002D, 0x412002D,
    0x412002D, 0x412002D, 0x412002D, 0x30A0020,
    0x3580020, 0x3ED0008, 0x4150008, 0x4140009,
    0x4110006, 0x4160009, 0x4130008, 0x38A0009,
    0x3890009, 0x4170009, 0x412002D, 0x412002D,
    0x412002D, 0x412002D, 0x2F80026, 0x2F90026,
    0x7920032, 0x7930032, 0x794003A, 0x7400008,
    0x3740012, 0x3740012, 0x3740012, 0x3740012,
    0x3740012, 0x3740012, 0x3740012, 0x3740012,
    0x3700016, 0x3720012, 0x3530023, 0x3530023,
    0x3530023, 0x7A8000C, 0, 0,
    0x2ED001E, 0x2EE001E, 0x2F0001E, 0x2F1001E,
    0x2EE001E, 0x2E3001E, 0x4260012, 0x3720012,
    0x3540022, 0x3540022, 0x37A0020, 0x37A0020,
    0x37A0020, 0x73E0019, 0x7A70021, 0x7D50013,
    0x7D50013, 0x7D50013, 0x7D50013, 0,
    0, 0, 0, 0,
    0, 0, 0x2FB003C, 0x2FB003C,
    0x2FA0037, 0x2FA0037, 0x31B0020, 0x2FC0032,
    0x2FC0032, 0x2FE005A, 0x2FE005A, 0x2FD003B,
    0x2FD003B, 0x794003A, 0x794003A, 0x7930032,
    0x7930032, 0x7920032, 0x7920032, 0x3EA0008,
    0x3EA0008, 0x3EA0008, 0x3EA0008, 0x3EA0008,
    0x3EA0008, 0x3EA0008, 0x3EA0008, 0x412002D,
    0x3580020, 0x3580020, 0x2EF001E, 0x2EC001C,
    0, 0x3550020, 0x4F10020, 0x3550020,
    0x3550020, 0x3E40008, 0x3EB0008, 0x3E70008,
    0x3E90008, 0x3E80008, 0x4F30004, 0x3880007,
    0, 0x3580020, 0, 0,
    0x3E30032, 0x3E30032, 0x3E30032, 0x3E30032,
    0x3E30032, 0x3E30032, 0x3E30032, 0x3E30032,
    0x3120020, 0x412002D, 0x7AD0029, 0x73F0026,
    0, 0x3730037, 0x3EC000A, 0x7AA0004,
    0, 0, 0, 0,
    0, 0x3790020, 0x3160020, 0x4260012,
    0x4260012, 0x3740012, 0x3720012, 0x3550020,
    0x18E0072, 0x3530023, 0x3530023, 0x3550020,
    0x3550020, 0x3550020, 0x3580020, 0x3580020,
    0x3580020, 0x3580020, 0x3580020, 0x3580020,
    0x3530023, 0x3530023, 0x412002D, 0x3130020,
    0x8150008, 0x7D4002D, 0x7D3002D, 0x7A90002,
    0x4260012, 0x4260012, 0x4260012, 0x3740012,
    0x3740012, 0x3740012, 0x3E6005F, 0x3E50023,
    0x839000E, 0x73C0037, 0x73D0037, 0x7D60005,
    0x7D70008, 0x4F6006E, 0x4F6006E, 0x4F6006E,
    0x4F6006E, 0x4F6006E, 0x4F6006E, 0x4F6006E,
    0x3FC0015, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x3FC0015, 0x3730037, 0x3730037, 0x3FC0015,
    0x3730037, 0x3730037, 0x3730037, 0x839000E,
    0x839000E, 0x839000E, 0x839000E, 0x839000E,
    0x839000E, 0x839000E, 0x839000E, 0x839000E,
    0x839000E, 0x4260012, 0x4260012, 0x3740012,
    0x3740012, 0x8940019, 0x8940019, 0x8990019,
    0x8990019, 0x8950014, 0x8950014, 0x8970032,
    0x8970032, 0x8960019, 0x8960019, 0x8910019,
    0x8910019, 0x8930014, 0x8920014, 0x8920014,
    0x8920014, 0x31B0020, 0x31B0020, 0x31B0020,
    0x89C0002, 0x89C0002, 0x89C0002, 0x3740012,
    0x3740012, 0x8A00008, 0x31B0020, 0x31B0020,
    0x73E0019, 0x3EB0008, 0x3E90008, 0x3E70008,
    0x3E80008, 0x3E40008, 0x4F30004, 0x3140020,
    0x3780025, 0x3110020, 0x30F0020, 0x3100020,
    0x8960019, 0x8970032,
};
u8 D_80099758[] = {
    0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x28,
    0x20, 0x20, 0x28, 0x20, 0x20, 0x28, 0x38, 0x28,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x20, 0x20, 0x40, 0x20,
    0x20, 0x20, 0x20, 0x18, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x20, 0x20, 0x28, 0x30, 0x20, 0x18, 0x20,
    0x18, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x50, 0x40, 0x30, 0x48, 0x40,
    0x40, 0x28, 0x10, 0x18, 0x30, 0x38, 0x28, 0x20,
    0x20, 0x20, 0x28, 0x30, 0x20, 0x28, 0x20, 0x20,
    0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x20, 0x28,
    0x20, 0x28, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x18, 0x18, 0x20, 0x18, 0x18, 0x20, 0x28, 0x20,
    0x30, 0x30, 0x28, 0x28, 0x28, 0x40, 0x38, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x18, 0x38,
    0x20, 0x20, 0x18, 0x20, 0x20, 0x38, 0x38, 0x40,
    0x50, 0x48, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x38, 0x38, 0x20, 0x20, 0x20, 0x20, 0x30, 0x18,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x14, 0x20, 0x20, 0x14,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x28, 0x20,
    0x50, 0x20, 0x20, 0x14, 0x14, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x38, 0x38, 0x38, 0x38, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x38, 0x38,
    0x40, 0x40, 0x40, 0x38, 0x38, 0x14, 0x20, 0x20,
    0x40, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x00, 0x00,
};
StageEntry D_800998E4[] = {
    {624, 1851, (void *)0x800A5E2C},
    {625, 2217, (void *)0x800A5E2C},
    {626, 2219, (void *)0x800A5E2C},
    {627, 2220, (void *)0x800A5E2C},
    {629, 2221, (void *)0x800A5E8C},
    {630, 2222, (void *)0x800A5E64},
    {631, 2223, (void *)0x800A5E28},
    {632, 2224, (void *)0x800A60BC},
    {633, 2225, (void *)0x800A5E28},
    {634, 2226, (void *)0x800A5E28},
    {635, 2227, (void *)0x800A5E28},
    {636, 2228, (void *)0x800A5E28},
    {637, 2229, (void *)0x800A5E28},
    {638, 2230, (void *)0x800A5E28},
    {639, 2231, (void *)0x800A633C},
    {640, 2232, (void *)0x800A5E88},
    {641, 2233, (void *)0x800A5E2C},
    {642, 2234, (void *)0x800A5E28},
    {650, 2235, (void *)0x800A5E2C},
    {651, 2236, (void *)0x800A5E28},
    {652, 2237, (void *)0x800A5E2C},
    {653, 2238, (void *)0x800A5E28},
    {654, 2239, (void *)0x800A5E2C},
    {655, 2240, (void *)0x800A5E2C},
    {656, 2241, (void *)0x800A5E28},
    {657, 2242, (void *)0x800A5E28},
    {658, 2243, (void *)0x800A5E28},
    {659, 2244, (void *)0x800A5E28},
    {660, 2245, (void *)0x800A5E28},
    {661, 2246, (void *)0x800A5FC8},
    {662, 2247, (void *)0x800A5E2C},
    {663, 2248, (void *)0x800A5E2C},
    {664, 2249, (void *)0x800A5E28},
    {665, 2250, (void *)0x800A5E2C},
    {666, 2251, (void *)0x800A6038},
    {667, 2252, (void *)0x800A5E2C},
    {668, 2253, (void *)0x800A5E28},
    {669, 2254, (void *)0x800A5E28},
    {670, 2255, (void *)0x800A5E28},
    {671, 2256, (void *)0x800A5E28},
    {736, 2257, (void *)0x800A5F58},
    {737, 2258, (void *)0x800A5F58},
    {738, 2259, (void *)0x800A5F58},
    {739, 2260, (void *)0x800A5F58},
    {740, 2261, (void *)0x800A5F58},
    {741, 2262, (void *)0x800A5F58},
    {742, 2263, (void *)0x800A5F58},
    {743, 2264, (void *)0x800A5F58},
    {744, 2265, (void *)0x800A5F54},
    {745, 2266, (void *)0x800A5F54},
    {746, 2267, (void *)0x800A5F54},
    {747, 2268, (void *)0x800A5F54},
    {748, 2269, (void *)0x800A5F54},
    {749, 2270, (void *)0x800A5F54},
    {750, 2271, (void *)0x800A5F54},
};
StageEntry D_8009A884[] = {
    {512, 466, (void *)0x800A5E7C},
    {513, 523, (void *)0x800A5E2C},
    {514, 467, (void *)0x800A6194},
    {515, 468, (void *)0x800A74A4},
    {516, 536, (void *)0x800A63DC},
    {517, 560, (void *)0x800A5E2C},
    {518, 469, (void *)0x800A7074},
    {519, 470, (void *)0x800A62B4},
    {520, 471, (void *)0x800A5E28},
    {521, 594, (void *)0x800A605C},
    {522, 472, (void *)0x800A5E28},
    {523, 639, (void *)0x800A5E28},
    {524, 473, (void *)0x800A5E28},
    {525, 474, (void *)0x800A5E28},
    {526, 475, (void *)0x800A5E28},
    {527, 476, (void *)0x800A5E28},
    {528, 477, (void *)(s32)func_800844B8},
    {529, 478, (void *)0x800A6A58},
    {530, 479, (void *)0x800A5E2C},
    {531, 480, (void *)0x800A64B8},
    {532, 694, (void *)0x800A5EAC},
    {533, 685, (void *)0x800A5E28},
    {534, 840, (void *)0x800A5EE0},
    {535, 848, (void *)0x800A5ED8},
    {536, 844, (void *)0x800A63A8},
    {537, 836, (void *)0x800A6D7C},
    {538, 936, (void *)0x800A5E28},
    {539, 677, (void *)0x800A5E88},
    {540, 1031, (void *)0x800A6068},
    {541, 481, (void *)0x800A5E2C},
    {542, 482, (void *)0x800A5E3C},
    {543, 931, (void *)0x800A5E2C},
    {544, 935, (void *)0x800A5E2C},
    {545, 483, (void *)0x800A5E28},
    {546, 484, (void *)0x800A5E28},
    {547, 495, (void *)0x800A5E28},
    {548, 541, (void *)0x800A5E28},
    {549, 485, (void *)0x800A5E28},
    {550, 486, (void *)0x800A6018},
    {551, 700, (void *)0x800A5E2C},
    {552, 1231, (void *)0x800A5E84},
    {553, 493, (void *)0x800A5EB8},
    {554, 1035, (void *)0x800A5E8C},
    {555, 573, (void *)0x800A6098},
    {556, 926, (void *)0x800A5E2C},
    {557, 1259, (void *)0x800A6FC0},
    {558, 1260, (void *)0x800A5E74},
    {559, 566, (void *)0x800A5E28},
    {560, 496, (void *)0x800A5E28},
    {561, 487, (void *)0x800A5E28},
    {562, 894, (void *)0x800A5E50},
    {563, 1298, (void *)0x800A5E84},
    {564, 922, (void *)0x800A5E84},
    {565, 914, (void *)0x800A60D4},
    {566, 868, (void *)0x800A701C},
    {567, 488, (void *)0x800A5E2C},
    {568, 533, (void *)0x800A5E28},
    {569, 497, (void *)0x800A5F88},
    {570, 871, (void *)0x800A6230},
    {571, 951, (void *)0x800A5E2C},
    {572, 1024, (void *)0x800A5EC8},
    {573, 968, (void *)0x800A5E28},
    {574, 1039, (void *)0x800A5E28},
    {575, 540, (void *)0x800A5E28},
    {576, 547, (void *)0x800A5E74},
    {577, 964, (void *)0x800A5E80},
    {578, 589, (void *)0x800A5E28},
    {579, 661, (void *)0x800A5E80},
    {580, 1365, (void *)0x800A5E88},
    {581, 1402, (void *)0x800A5E28},
    {582, 574, (void *)0x800A6984},
    {583, 1135, (void *)0x800A5E84},
    {584, 544, (void *)0x800A60D0},
    {585, 689, (void *)0x800A5E2C},
    {586, 1308, (void *)0x800A5E80},
    {587, 1061, (void *)0x800A5E2C},
    {588, 1154, (void *)0x800A5E74},
    {589, 1430, (void *)0x800A5EA8},
    {590, 1292, (void *)0x800A5E88},
    {591, 1293, (void *)0x800A5E28},
    {592, 1294, (void *)0x800A5E28},
    {593, 1282, (void *)0x800A5E28},
    {594, 1158, (void *)0x800A5E68},
    {595, 1217, (void *)0x800A5E28},
    {596, 1374, (void *)0x800A5E78},
    {597, 1165, (void *)0x800A6314},
    {598, 1166, (void *)0x800A6204},
    {599, 1173, (void *)0x800A60D0},
    {600, 1181, (void *)0x800A61F4},
    {601, 1185, (void *)0x800A61F4},
    {602, 1193, (void *)0x800A60D0},
    {603, 1359, (void *)0x800A5E28},
    {604, 1177, (void *)0x800A5E74},
    {605, 1224, (void *)0x800A5E2C},
    {606, 1201, (void *)0x800A5E74},
    {607, 1499, (void *)0x800A6454},
    {608, 1225, (void *)0x800A5E58},
    {609, 1504, (void *)0x800A5E28},
    {610, 1512, (void *)0x800A5E28},
    {611, 1520, (void *)0x800A5E28},
    {612, 1528, (void *)0x800A5E28},
    {613, 681, (void *)0x800A5E28},
    {614, 1540, (void *)0x800A5E28},
    {615, 1544, (void *)0x800A5E28},
    {616, 1556, (void *)0x800A5E28},
    {617, 1564, (void *)(s32)func_800A6024},
    {618, 1572, (void *)0x800A5EE4},
    {619, 1619, (void *)0x800A6138},
    {620, 1621, (void *)0x800A62B8},
    {621, 1623, (void *)0x800A6424},
    {622, 1624, (void *)0x800A5E6C},
    {623, 1626, (void *)0x800A5E28},
    {624, 522, (void *)0x800A5E2C},
    {625, 524, (void *)0x800A5E2C},
    {626, 525, (void *)0x800A5EC0},
    {627, 535, (void *)0x800A5E2C},
    {628, 564, (void *)0x800A5E2C},
    {629, 590, (void *)0x800A5E2C},
    {630, 592, (void *)0x800A62C8},
    {631, 593, (void *)0x800A5E28},
    {632, 595, (void *)0x800A605C},
    {633, 624, (void *)0x800A5E28},
    {634, 667, (void *)0x800A5E28},
    {635, 672, (void *)0x800A5E28},
    {636, 697, (void *)0x800A5E28},
    {637, 701, (void *)0x800A5E28},
    {638, 658, (void *)0x800A5E28},
    {639, 702, (void *)0x800A634C},
    {640, 711, (void *)0x800A5E28},
    {641, 809, (void *)0x800A5E2C},
    {642, 810, (void *)0x800A5E28},
    {643, 826, (void *)0x800A5E28},
    {644, 830, (void *)0x800A5E28},
    {645, 874, (void *)0x800A5E28},
    {646, 875, (void *)0x800A5E28},
    {647, 876, (void *)0x800A6160},
    {648, 877, (void *)0x800A6DD0},
    {649, 937, (void *)0x800A5E28},
    {650, 1030, (void *)0x800A5E2C},
    {651, 1077, (void *)0x800A6068},
    {652, 1100, (void *)0x800A5E2C},
    {653, 1120, (void *)0x800A5E28},
    {654, 1121, (void *)0x800A5E28},
    {655, 1122, (void *)0x800A5E28},
    {656, 1123, (void *)0x800A5E28},
    {657, 1140, (void *)0x800A5E28},
    {658, 1150, (void *)0x800A5E28},
    {659, 1189, (void *)0x800A5E28},
    {660, 1197, (void *)0x800A5E28},
    {661, 1205, (void *)0x800A5E84},
    {662, 1209, (void *)0x800A5E2C},
    {663, 1235, (void *)0x800A5E28},
    {664, 1236, (void *)0x800A5E28},
    {665, 1241, (void *)0x800A5E2C},
    {666, 1245, (void *)0x800A6084},
    {667, 1249, (void *)0x800A5E2C},
    {668, 1261, (void *)0x800A5F1C},
    {669, 1273, (void *)0x800A5E28},
    {670, 1278, (void *)0x800A5E28},
    {671, 1300, (void *)0x800A5E28},
    {672, 1304, (void *)0x800A5E2C},
    {673, 1312, (void *)0x800A5E2C},
    {674, 1316, (void *)0x800A5E2C},
    {675, 1320, (void *)0x800A5E2C},
    {676, 1324, (void *)0x800A5E2C},
    {677, 1328, (void *)0x800A5E28},
    {678, 1332, (void *)0x800A5E28},
    {679, 1351, (void *)0x800A61F4},
    {680, 1352, (void *)0x800A5E2C},
    {681, 1353, (void *)0x800A5E28},
    {682, 1354, (void *)0x800A5E28},
    {683, 1355, (void *)0x800A5E28},
    {684, 1360, (void *)0x800A5E28},
    {685, 1386, (void *)0x800A5E74},
    {686, 1390, (void *)0x800A7460},
    {687, 1394, (void *)0x800A5E28},
    {688, 1398, (void *)0x800A5E80},
    {689, 1406, (void *)0x800A5E28},
    {690, 1410, (void *)0x800A5E28},
    {691, 1414, (void *)0x800A5E28},
    {692, 1418, (void *)0x800A5E28},
    {693, 1422, (void *)0x800A5E28},
    {694, 1426, (void *)0x800A5E28},
    {695, 1431, (void *)0x800A5E28},
    {696, 1435, (void *)0x800A5E28},
    {697, 1439, (void *)0x800A5E28},
    {698, 1443, (void *)0x800A5E28},
    {699, 1447, (void *)0x800A5E28},
    {700, 1451, (void *)0x800A5E80},
    {701, 1455, (void *)0x800A5E28},
    {702, 1459, (void *)0x800A5E84},
    {703, 1463, (void *)0x800A5E28},
    {704, 1467, (void *)0x800A5E28},
    {705, 1471, (void *)0x800A5F54},
    {706, 1475, (void *)0x800A5F54},
    {707, 1479, (void *)0x800A5E28},
    {708, 1483, (void *)0x800A5E28},
    {709, 1487, (void *)0x800A5E28},
    {710, 1491, (void *)0x800A5E2C},
    {711, 1495, (void *)0x800A5E68},
    {712, 1503, (void *)0x800A5E28},
    {713, 1508, (void *)0x800A5E28},
    {714, 1516, (void *)0x800A5E28},
    {715, 1524, (void *)0x800A5E28},
    {716, 1532, (void *)0x800A5E28},
    {717, 1536, (void *)0x800A5E28},
    {718, 1543, (void *)0x800A5E28},
    {719, 1552, (void *)0x800A5E28},
    {720, 1560, (void *)0x800A5E28},
    {721, 1568, (void *)(s32)func_800A6024},
    {722, 1588, (void *)0x800A5EE4},
    {723, 1620, (void *)0x800A6138},
    {724, 1622, (void *)0x800A62B8},
    {725, 1625, (void *)0x800A5EA0},
    {726, 1627, (void *)0x800A5E28},
    {727, 489, (void *)0x800A75B0},
    {728, 490, (void *)0x800A66B0},
    {729, 491, (void *)0x800A631C},
    {730, 1631, (void *)0x800A6654},
    {731, 1635, (void *)0x800A69CC},
    {732, 1639, (void *)0x800A6B44},
    {733, 1643, (void *)0x800A6418},
    {734, 1647, (void *)0x800A6184},
    {735, 1651, (void *)0x800A6160},
    {736, 1655, (void *)0x800A5F50},
    {737, 1659, (void *)0x800A5F58},
    {738, 1665, (void *)0x800A5F50},
    {739, 1669, (void *)0x800A5F50},
    {740, 1673, (void *)0x800A5F50},
    {741, 1697, (void *)0x800A5F50},
    {742, 1701, (void *)0x800A5F50},
    {743, 1705, (void *)0x800A5F50},
    {744, 1709, (void *)0x800A5F54},
    {745, 1713, (void *)0x800A5F54},
    {746, 1677, (void *)0x800A5F54},
    {747, 1690, (void *)0x800A5F54},
    {748, 1691, (void *)0x800A5F54},
    {749, 1692, (void *)0x800A5F54},
    {750, 1693, (void *)0x800A5F54},
    {0, 0, 0},
};
#endif
ScriptTimer D_8009A424 = {0, 0, func_800914C0, func_800914F0};
void (*D_8009A434[])() = {
    func_80091648, func_80091520, func_800915B0, func_800915FC,
    func_800916B4,
};
/* The script commands (func_800916E8), up to the first id 0. Most of their
   functions are the stage overlay's, at fixed addresses, and they take
   different arguments */
#if VERSION_US
ScriptCommand D_8009A448[] = {
    {800, (void *)0x800A5E50, (void *)0x800A5E04},
    {801, (void *)0x800A6360, (void *)0x800A6314},
    {802, (void *)0x800A5220, 0},
    {803, (void *)func_800878F0, (void *)func_80087918},
    {804, (void *)func_800878F0, (void *)func_80087918},
    {805, (void *)func_800878F0, (void *)func_80087918},
    {806, (void *)func_800878F0, (void *)func_80087918},
    {807, (void *)0x800A53D4, (void *)0x800A5404},
    {808, (void *)0x800A5120, (void *)0x800A50E8},
    {809, (void *)0x800A4FCC, (void *)0x800A4F94},
    {810, (void *)0x800A50C0, (void *)0x800A500C},
    {811, (void *)0x800A595C, (void *)0x800A5850},
    {812, 0, (void *)0x800A5D4C},
    {813, (void *)func_80083470, (void *)func_80082F84},
    {814, (void *)0x800A5270, (void *)0x800A5140},
    {815, (void *)0x800A50A4, (void *)0x800A5038},
    {816, (void *)0x800A50F4, 0},
    {817, (void *)0x800A5128, 0},
    {818, (void *)0x800A5160, 0},
    {819, (void *)0x800A5198, 0},
    {820, (void *)0x800A51D0, 0},
    {821, (void *)0x800A5208, 0},
    {822, (void *)0x800A5240, 0},
    {823, (void *)0x800A5278, 0},
    {824, (void *)0x800A52B0, 0},
    {825, (void *)0x800A52E8, 0},
    {826, (void *)func_80083930, (void *)func_800838BC},
    {827, (void *)0x800A5150, (void *)0x800A50DC},
    {828, (void *)0x800A4ED4, 0},
    {829, (void *)0x800A4EEC, (void *)0x800A4EB4},
    {830, (void *)0x800A4E8C, (void *)0x800A4E54},
    {831, (void *)0x800A5498, (void *)0x800A545C},
    {832, (void *)0x800A5A1C, (void *)0x800A59E0},
    {833, (void *)0x800A4E24, (void *)0x800A4E54},
    {834, (void *)0x800A4E24, (void *)0x800A4E54},
    {835, (void *)0x800A509C, 0},
    {836, 0, (void *)0x800A5044},
    {837, 0, (void *)0x800A5038},
    {838, (void *)0x800A62A8, 0},
    {839, (void *)0x800A53D4, 0},
    {840, 0, (void *)0x800A5288},
    {841, 0, (void *)0x800A4E28},
    {842, 0, (void *)0x800A503C},
    {843, 0, (void *)0x800A503C},
    {844, 0, (void *)0x800A503C},
    {845, 0, (void *)0x800A5680},
    {846, 0, (void *)0x800A5034},
    {847, 0, (void *)0x800A51C8},
    {848, (void *)0x800A5758, (void *)0x800A5644},
    {849, (void *)0x800A505C, 0},
    {850, 0, (void *)0x800A4EDC},
    {851, 0, (void *)0x800A4EDC},
    {852, (void *)0x800A6190, 0},
    {853, (void *)0x800A4E78, 0},
    {0, 0, 0},
    {0, 0, (void *)func_800917D8},
};
#elif VERSION_EU
ScriptCommand D_8009A448[] = {
    {800, (void *)0x800A6F8C, (void *)0x800A6F40},
    {801, (void *)0x800A749C, (void *)0x800A7450},
    {802, (void *)0x800A635C, 0},
    {803, (void *)func_800878F0, (void *)func_80087918},
    {804, (void *)func_800878F0, (void *)func_80087918},
    {805, (void *)func_800878F0, (void *)func_80087918},
    {806, (void *)func_800878F0, (void *)func_80087918},
    {807, (void *)0x800A6510, (void *)0x800A6540},
    {808, (void *)0x800A625C, (void *)0x800A6224},
    {809, (void *)0x800A6108, (void *)0x800A60D0},
    {810, (void *)0x800A61FC, (void *)0x800A6148},
    {811, (void *)0x800A6A98, (void *)0x800A698C},
    {812, 0, (void *)0x800A6E88},
    {813, (void *)func_80083470, (void *)func_80082F84},
    {814, (void *)0x800A63AC, (void *)0x800A627C},
    {815, (void *)0x800A61E0, (void *)0x800A6174},
    {816, (void *)0x800A6230, 0},
    {817, (void *)0x800A6264, 0},
    {818, (void *)0x800A629C, 0},
    {819, (void *)0x800A62D4, 0},
    {820, (void *)0x800A630C, 0},
    {821, (void *)0x800A6344, 0},
    {822, (void *)0x800A637C, 0},
    {823, (void *)0x800A63B4, 0},
    {824, (void *)0x800A63EC, 0},
    {825, (void *)0x800A6424, 0},
    {826, (void *)func_80083930, (void *)func_800838BC},
    {827, (void *)0x800A628C, (void *)0x800A6218},
    {828, (void *)0x800A6010, 0},
    {829, (void *)0x800A6028, (void *)0x800A5FF0},
    {830, (void *)0x800A5FC8, (void *)0x800A5F90},
    {831, (void *)0x800A65D4, (void *)0x800A6598},
    {832, (void *)0x800A6B58, (void *)0x800A6B1C},
    {833, (void *)0x800A5F60, (void *)0x800A5F90},
    {834, (void *)0x800A5F60, (void *)0x800A5F90},
    {835, (void *)0x800A61D8, 0},
    {836, 0, (void *)0x800A6180},
    {837, 0, (void *)0x800A6174},
    {838, (void *)0x800A73E4, 0},
    {839, (void *)0x800A6510, 0},
    {840, 0, (void *)0x800A63C4},
    {841, 0, (void *)0x800A5F64},
    {842, 0, (void *)0x800A6178},
    {843, 0, (void *)0x800A6178},
    {844, 0, (void *)0x800A6178},
    {845, 0, (void *)0x800A67BC},
    {846, 0, (void *)0x800A6170},
    {847, 0, (void *)0x800A6304},
    {848, (void *)0x800A6894, (void *)0x800A6780},
    {849, (void *)0x800A6198, 0},
    {850, 0, (void *)0x800A6018},
    {851, 0, (void *)0x800A6018},
    {852, (void *)0x800A72CC, 0},
    {853, (void *)0x800A5FB4, 0},
    {854, (void *)0x800A609C, 0},
    {855, (void *)0x800A639C, 0},
    {0, 0, 0},
    {0, 0, (void *)func_800917D8},
};
#endif
void (*D_8009A6E8)() = func_80091910;
void (*D_8009A6EC[])() = {
    func_80091A4C, func_80091854,
};
s32 D_8009A6F4[] = {
    2000, 3, 4, 6,
    9, 18,
};
FieldMap D_8009A70C = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_80091B78,
    func_80091BC0,
    func_80091F4C,
    func_8009204C,
    func_80091B90,
    func_80091BB4,
    func_80091D3C,
};
s32 D_8009A768 = -1;
Point D_8009A76C[][8] = {
    {
        {0, 2048},
        {-2896, 1448},
        {-4096, 0},
        {-2896, -1448},
        {0, -2048},
        {2896, -1448},
        {4096, 0},
        {2896, 1448},
    },
    {
        {599, 3405},
        {-2048, 3368},
        {-3496, 1358},
        {-2896, -1448},
        {-600, -3405},
        {2048, -3368},
        {3495, -1358},
        {2896, 1448},
    },
    {
        {155, 2865},
        {-2676, 2606},
        {-3940, 818},
        {-2896, -1448},
        {-156, -2866},
        {2676, -2606},
        {3939, -819},
        {2896, 1448},
    },
    {
        {68, 2616},
        {-2799, 2254},
        {-4027, 569},
        {-2896, -1448},
        {-69, -2618},
        {2797, -2254},
        {4026, -571},
        {2896, 1448},
    },
    {
        {273, 3081},
        {-2509, 2911},
        {-3822, 1034},
        {-2896, -1448},
        {-274, -3082},
        {2509, -2911},
        {3821, -1035},
        {2896, 1448},
    },
    {
        {344, 3178},
        {-2409, 3047},
        {-3751, 1130},
        {-2896, -1448},
        {-345, -3179},
        {2409, -3047},
        {3750, -1132},
        {2896, 1448},
    },
    {
        {9, 2271},
        {-2882, 1764},
        {-4086, 224},
        {-2896, -1448},
        {-10, -2272},
        {2882, -1764},
        {4085, -225},
        {2896, 1448},
    },
};
u8 D_8009A92C[] = {
    0x00, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
};
u16 D_8009A934[] = {
    0x0000, 0x0000,
};
Point D_8009A938 = {0, 0};
u8 *D_8009A940 = NULL;
s32 D_8009A944 = 0;
s32 D_8009A948 = 0;
s32 D_8009A94C[] = {
    0, 0,
};
s32 D_8009A954[] = {
    0, 0,
};
s32 D_8009A95C[] = {
    0, 0,
};
s32 D_8009A964[] = {
    0, 0,
};
s32 D_8009A96C = 0;
s32 D_8009A970[] = {
    0, 0,
};
s32 D_8009A978[] = {
    0, 0, 0,
};
s32 D_8009A984[] = {
    0, 0,
};
s32 D_8009A98C[] = {
    0, 0,
};
s32 D_8009A994 = 0;
s32 D_8009A998[] = {
    0, 0,
};
s32 D_8009A9A0[] = {
    0, 0,
};
s32 D_8009A9A8[] = {
    0, 0,
};
s32 D_8009A9B0[] = {
    0, 0, 0,
};
s32 D_8009A9BC = 0;
s32 D_8009A9C0[] = {
    0, 0,
};
s32 D_8009A9C8[] = {
    0, 0,
};
s32 D_8009A9D0[] = {
    0, 0,
};
s32 D_8009A9D8[] = {
    0, 0,
};
s32 D_8009A9E0[] = {
    0, 0,
};
s32 D_8009A9E8[] = {
    0, 0, 0,
};
s32 D_8009A9F4[] = {
    0, 0,
};
s32 D_8009A9FC = 0;
s32 D_8009AA00[] = {
    0, 0,
};
s32 D_8009AA08[] = {
    0, 0,
};
s32 D_8009AA10[] = {
    0, 0, 0,
};
s32 D_8009AA1C[] = {
    0, 0,
};
s32 D_8009AA24[] = {
    0, 0,
};
s32 D_8009AA2C[] = {
    0, 0,
};
s32 D_8009AA34 = 0;
s32 D_8009AA38[] = {
    0, 0,
};
u16 D_8009AA40[] = {
    0x0000, 0x0000, 0x0000, 0x0000,
};
#if VERSION_US
u16 D_8009AA48[] = {
    0x0000, 0x0000,
};
#elif VERSION_EU
u16 D_8009AA48[] = {
    0x0000, 0x4E49,
};
#endif
Box D_8009AA4C[20] = {{0}};
s32 D_8009AB8C = 0;
