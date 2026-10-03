/* The fifth object of FIELDSTG.PRO (see fieldstg.c): its rodata starts at
   0x800825E0 (USA). */

#include "fieldstg.h"

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
            task->actor->unk78 = task->entry->unkA;
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

Unk80087FDC *func_800881A0(s32 arg0, void *entries) {
    Unk80087FDC *task = createTask(func_80087FDC, sizeof(Unk80087FDC), 8);

    task->unk50 = arg0;
    return task;
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

/* Animates and draws the map's objects that are in view */
void func_8008878C(Unk8008878C *task, Unk8008BFE8 **children) {
    MapObject *object;
    MapObject *entry;
    Layer *layer;
    SpriteDrawer sprite;
    RECT view;
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    u8 margin;
    s32 back;

    switch (task->state) {
    case 0:
    default:
        count = 0;
        for (entry = task->unk54; entry->y != 0; entry++) {
            if (entry->id == 0xFF) {
                count++;
            }
        }
        if (count != 0) {
            *children = func_8008BFE8(count);
        }
        task->nextState(task);
        break;
    case 1:
        object = task->unk54;
        layer = GFX_FUNCS.getLayer(0x1002);
        layer->getViewRect(layer, &view);
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x140, 0x100);
        sprite.setAltClut(0, 0x1F0);
        for (i = 0; object->unk2 != 0; object++, i++) {
            if (object->unk0 == 0) {
                continue;
            }
            x = object->id == 0xFF ? object->x - 50 : object->x;
            y = object->id == 0xFF ? object->y - 100 : object->y;
            margin = object->unk2;
            if (x >= view.x - margin && view.x + view.w >= x && y >= view.y - margin && view.y + view.h >= y) {
                switch (object->anim) {
                case 1:
                    if (object->animTime < 0x100) {
                        object->frame++;
                        if (object->frame > object->animLast) {
                            object->frame = object->animFirst;
                        }
                        object->animTime = object->animDelay << 8;
                    } else {
                        object->animTime -= 0x100;
                    }
                    break;
                case 2:
                    if (object->animTime < 0x100) {
                        object->clutRow++;
                        if (object->clutRow > object->animLast) {
                            object->clutRow = object->animFirst;
                        }
                        object->animTime = object->animDelay << 8;
                    } else {
                        object->animTime -= 0x100;
                    }
                    break;
                case 3:
                    if (object->animTime & 0x8000) {
                        back = 0x8000;
                        object->animTime &= 0x7FFF;
                        if (object->animTime < 0x100) {
                            object->clutRow--;
                            object->animTime = object->animDelay << 8;
                            if (object->clutRow == (u8)(object->animFirst - 1)) {
                                object->clutRow = object->animFirst + 1;
                                back = 0;
                            }
                        } else {
                            object->animTime -= 0x100;
                        }
                        object->animTime |= back;
                    } else if (object->animTime < 0x100) {
                        object->clutRow++;
                        object->animTime = object->animDelay << 8;
                        if (object->clutRow == object->animLast + 1) {
                            object->clutRow = object->animLast - 1;
                            object->animTime |= 0x8000;
                        }
                    } else {
                        object->animTime -= 0x100;
                    }
                    break;
                }
                if (object->unkE != 0) {
                    layer->addSortedCallback(layer, func_80088640, task, object->unkE, i);
                } else {
                    sprite.setLayerId(0x1002, object->depth);
                    sprite.setClutRow(object->clutRow);
                    if (D_800990B4.unk38.cd != 0) {
                        sprite.setColor(&D_800990B4.unk38);
                    }
                    sprite.draw(FILE_CACHE_GET_ENTRY[0](task->unk50), object->frame, object->x, object->y);
                }
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Unk8008878C *func_80088BE4(s32 arg0, MapObject *arg1) {
    Unk8008878C *task = createTask(func_8008878C, sizeof(Unk8008878C), 4);

    task->unk54 = arg1;
    task->unk50 = arg0;
    return task;
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

/* The task (func_80088E4C's) goes unused */
void func_80088CD0(Task *task) {
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

/* The task (func_80088E4C's) goes unused */
void func_80088D5C(Task *task) {
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

/* Loads the field's files, a step at a time: 1 once done */
s32 func_80088E4C(Task *task) {
    TimLoader sprites;
    TimLoader loader;

    switch (task->step) {
    case 0:
        switch (task->counter) {
        case 0:
        default:
            FILE_CACHE_REQUEST(FIELD_SPRITES_FILE);
            task->tickCounter(task);
        case 1:
            if (FILE_CACHE.isLoading(FIELD_SPRITES_FILE) != 0) {
                return 0;
            }
            initTimLoader(&sprites);
            sprites.setImagePos(0x200, 0x100);
            sprites.loadArchive(FILE_CACHE.getEntry((FIELD_SPRITES_FILE << 16) | 2));
            sprites.setImagePos(0x240, 0x100);
            sprites.loadArchive(FILE_CACHE.getEntry((FIELD_SPRITES_FILE << 16) | 3));
            task->nextStep(task);
            break;
        }
        break;
    case 1:
        switch (task->counter) {
        case 0:
        default:
            if (D_800990B4.unk18 == 0 && D_800990B4.unk1C == 0) {
                task->nextStep(task);
                break;
            }
            if (D_800990B4.unk18 != 0) {
                FILE_CACHE_REQUEST(D_800990B4.unk18 >> 16);
            }
            if (D_800990B4.unkC != 0) {
                FILE_CACHE_REQUEST(D_800990B4.unkC >> 16);
            }
            if (D_800990B4.unk1C != 0) {
                FILE_CACHE_REQUEST(D_800990B4.unk1C);
            }
            task->tickCounter(task);
        case 1:
            if (D_800990B4.unk18 != 0) {
                if (FILE_CACHE.isLoading(D_800990B4.unk18 >> 16) != 0) {
                    return 0;
                }
                initTimLoader(&loader);
                loader.setClutPos(0, 0x1F0);
                loader.setImagePos(0x140, 0x100);
                loader.loadArchive(FILE_CACHE.getEntry(D_800990B4.unk18));
            }
            task->tickCounter(task);
        case 2:
            if (D_800990B4.unk1C != 0) {
                if (FILE_CACHE.isLoading(D_800990B4.unk1C) != 0) {
                    return 0;
                }
                initTimLoader(&loader);
                loader.setClutPos(0, 0x1F0);
                loader.setImagePos(0x140, 0x100);
                loader.loadArchive(FILE_CACHE.load(D_800990B4.unk1C));
            }
            task->tickCounter(task);
        case 3:
            if (D_800990B4.unkC != 0 && FILE_CACHE.isLoading(D_800990B4.unkC >> 16) != 0) {
                return 0;
            }
            task->nextStep(task);
            break;
        }
        break;
    case 2:
        if (D_800990B4.unk1C != 0) {
            FILE_CACHE.free(D_800990B4.unk1C);
        }
        task->nextStep(task);
    case 3:
        FILE_CACHE.request(FILE_MENU_SPRITES);
        FILE_CACHE.request(D_800990B4.unk44);
        FILE_CACHE.request(TEXT_FILE(0xB1));
        func_80088D5C(task);
        func_80088CD0(task);
        task->nextStep(task);
        return 1;
    default:
        return 1;
    }
    return 0;
}

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

Task *func_800892E8(s32 arg0) {
    Task *task = createTask(func_8008926C, 0x54, 0);

    task->key2 = arg0;
    return task;
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

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_800896C0);

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
            GAME.fieldPos = children->actors[0]->pos;
            GAME.fieldDir = children->actors[0]->dir;
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

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_8008A154);

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
        D_800990B4.unk64.x = arg2;
        D_800990B4.unk64.y = arg3;
        D_800990B4.unk6C = arg4;
    }
}

void func_8008AEB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8008AE18(arg0, arg1, arg2, arg3, arg4, 0);
}

extern Encounter D_800939E0[]; /* fieldstg.c's s32 words */

/*
 * Starts encounter D_800939E0[encounter]: the field task (id 7) goes to state 2
 * with mode 0x600, or 0xE0A (USA 0xE09) at GAME_PROGRESS 0x2B, and
 * D_80042728 takes the encounter's enemies and bytes. Enemies 0x1C9-0x1D0
 * always give an item (unk50), which the field mode and a roll pick: odd
 * ones (1 in 32 for the rarer item), even ones (1 in 16).
 */
void func_8008AEDC(s32 encounter) {
    FieldTask *task = TASK_FUNCS.find(7, -1, -1);
    s32 i;
    s32 next;
    s32 mode;
    s32 roll;

    if (task != NULL) {
        D_800990B4.unk58 = 1;
        D_800990B4.unk5C = 1;
#if VERSION_EU
        next = 0xE0A;
#else
        next = 0xE09;
#endif
        if (GAME_PROGRESS != 0x2B) {
            next = 0x600;
        }
        task->unk5C = next;
        task->unk60 = 0;
        task->setState(task, 2);
        D_80042728.unk10 = encounter;
        D_80042728.unk3C = D_800939E0[encounter].unkC;
        D_80042728.unk3D = D_800939E0[encounter].unkD;
        for (i = 0; i < 12; i++) {
            D_80042728.unk3E[i] = D_800939E0[encounter].unkE[i];
        }
        for (i = 0; i < 3; i++) {
            D_80042728.enemies[i] = *D_800939E0[encounter].enemies[i];
        }
        D_80042728.unk4C = 0;
        if ((u32)(D_80042728.enemies[0].fighter - 0x1C9) < 8) {
            D_80042728.unk4C = 1;
            mode = GAME.funcs.getMode();
            if (D_80042728.enemies[0].fighter & 1) {
                roll = RANDOM.next() & 0x1F;
                switch (mode) {
                case 0x21D:
                default:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x177;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x22A:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x179;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x233:
                case 0x235:
                case 0x237:
                case 0x23A:
                case 0x23B:
                case 0x23C:
                case 0x24A:
                case 0x24C:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x17A;
                    } else {
                        D_80042728.unk50 = 0x187;
                    }
                    break;
#if VERSION_EU
                case 0x28C:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x17F;
                    } else {
                        D_80042728.unk50 = 0x188;
                    }
                    break;
                case 0x28D:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x179;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x28E:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x178;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x28F:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x17E;
                    } else {
                        D_80042728.unk50 = 0x188;
                    }
                    break;
                case 0x290:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x180;
                    } else {
                        D_80042728.unk50 = 0x189;
                    }
                    break;
                case 0x291:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x181;
                    } else {
                        D_80042728.unk50 = 0x189;
                    }
                    break;
                case 0x296:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x182;
                    } else {
                        D_80042728.unk50 = 0x189;
                    }
                    break;
                case 0x298:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17C;
                        } else {
                            D_80042728.unk50 = 0x187;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x183;
                    } else {
                        D_80042728.unk50 = 0x18A;
                    }
                    break;
                case 0x299:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17F;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x185;
                    } else {
                        D_80042728.unk50 = 0x18A;
                    }
                    break;
#else
                case 0x28C:
                case 0x28D:
                case 0x28E:
                case 0x28F:
                case 0x290:
                case 0x291:
                case 0x296:
                case 0x298:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x17C;
                    } else {
                        D_80042728.unk50 = 0x187;
                    }
                    break;
                case 0x299:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x17F;
                    } else {
                        D_80042728.unk50 = 0x188;
                    }
                    break;
#endif
                case 0x2A1:
                case 0x2A3:
                case 0x2A4:
                case 0x2A7:
                case 0x2A8:
                case 0x2A9:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x180;
                    } else {
                        D_80042728.unk50 = 0x189;
                    }
                    break;
                case 0x261:
                case 0x262:
                case 0x265:
                case 0x266:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x181;
                    } else {
                        D_80042728.unk50 = 0x189;
                    }
                    break;
                case 0x2B4:
                case 0x2B6:
                case 0x2C9:
                case 0x2CA:
                case 0x2CD:
                case 0x2CE:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x184;
                    } else {
                        D_80042728.unk50 = 0x18A;
                    }
                    break;
                }
            } else {
                roll = RANDOM.next() & 0xF;
                switch (mode) {
                case 0x201:
                default:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x177;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x234:
                case 0x235:
                case 0x237:
                case 0x23A:
                case 0x23B:
                case 0x23C:
                case 0x23D:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x178;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x247:
                case 0x249:
                case 0x24B:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x17B;
                    } else {
                        D_80042728.unk50 = 0x187;
                    }
                    break;
#if VERSION_EU
                case 0x271:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x177;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x28C:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x17A;
                    } else {
                        D_80042728.unk50 = 0x187;
                    }
                    break;
                case 0x28D:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x179;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x28E:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x178;
                    } else {
                        D_80042728.unk50 = 0x186;
                    }
                    break;
                case 0x28F:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x17B;
                    } else {
                        D_80042728.unk50 = 0x187;
                    }
                    break;
                case 0x290:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x184;
                    } else {
                        D_80042728.unk50 = 0x18A;
                    }
                    break;
                case 0x296:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x17C;
                    } else {
                        D_80042728.unk50 = 0x187;
                    }
                    break;
                case 0x299:
                    if (GAME_PROGRESS != 0x2D) {
                        if (roll != 0) {
                            D_80042728.unk50 = 0x17D;
                        } else {
                            D_80042728.unk50 = 0x188;
                        }
                    } else if (roll != 0) {
                        D_80042728.unk50 = 0x17D;
                    } else {
                        D_80042728.unk50 = 0x188;
                    }
                    break;
#else
                case 0x271:
                case 0x28C:
                case 0x28D:
                case 0x28E:
                case 0x28F:
                case 0x290:
                case 0x296:
                case 0x299:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x17D;
                    } else {
                        D_80042728.unk50 = 0x188;
                    }
                    break;
#endif
                case 0x2A2:
                case 0x2A3:
                case 0x2A4:
                case 0x2A7:
                case 0x2A8:
                case 0x2A9:
                case 0x2AA:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x17E;
                    } else {
                        D_80042728.unk50 = 0x188;
                    }
                    break;
                case 0x266:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x182;
                    } else {
                        D_80042728.unk50 = 0x189;
                    }
                    break;
                case 0x2B1:
                case 0x2B3:
                case 0x2B5:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x183;
                    } else {
                        D_80042728.unk50 = 0x18A;
                    }
                    break;
                case 0x2CE:
                    if (roll != 0) {
                        D_80042728.unk50 = 0x185;
                    } else {
                        D_80042728.unk50 = 0x18A;
                    }
                    break;
                }
            }
        }
    }
}

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

void func_8008B398(s32 arg0, Point *pos, FieldWarp *arg2) {
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

/* Sends an actor from the nearest task with id 0x17 (y counts twice in the
 * distance) to its dest tile: the actor walks to the task, sets it to state 2,
 * waits for it to leave that state, then moves along a quarter sine, spinning,
 * until it lands; without such a task it ends at once. The match depends on
 * the distance written twice. */
void func_8008B450(Unk8008B450 *task) {
    Point pos;
    Point near;
    Task *t;
    Task *found;
    s32 best;
    s32 dx;
    s32 dy;
    s32 d;

    switch (task->state) {
    case 0:
    default:
        best = 0x8000;
        found = NULL;
        pos.x = task->actor->tile.x;
        pos.y = task->actor->tile.y;
        for (t = TASK_REGISTRY.funcs.find(0x17, -1, -1); t != NULL; t = TASK_REGISTRY.funcs.findNext()) {
            dx = pos.x - t->key1;
            if (dx < 0) {
                dx = -dx;
            }
            dy = pos.y - t->key2;
            if (dy < 0) {
                dy = -dy;
            }
            if (dx + dy * 2 < best) {
                found = t;
                near.x = t->key1;
                best = dx + dy * 2;
                near.y = found->key2;
            }
        }
        if (found == NULL) {
            task->setState(task, 3);
            break;
        }
        task->from = found;
        task->start.x = near.x + 0x14;
        task->start.y = near.y + 0xD;
        task->nextState(task);
    case 1:
        switch (task->substate) {
        case 0:
            switch (task->step) {
            case 0:
                task->actor->unk13C(task->actor, task->start.x, task->start.y, 0);
                func_80090154();
                task->nextStep(task);
            case 1:
                if (task->actor->unk140(task->actor) == 0) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 1:
            switch (task->step) {
            case 0:
            default:
                task->from->setState(task->from, 2);
                SOUND.playSound(0x4001D);
                task->nextStep(task);
            case 1:
                if (task->from->state != 2) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 2:
            switch (task->step) {
            case 0:
            default:
                task->negX = 0;
                task->dist.x = task->dest[1] - task->start.x;
                if (task->dist.x < 0) {
                    task->dist.x = -task->dist.x;
                    task->negX = 1;
                }
                task->negY = 0;
                task->dist.y = task->dest[2] - task->start.y;
                if (task->dist.y < 0) {
                    task->dist.y = -task->dist.y;
                    task->negY = 1;
                }
                task->nextStep(task);
            case 1:
                task->counter += GFX_FUNCS.getFrameTime() * 24;
                if (task->counter > 0x1000) {
                    task->counter = 0x1000;
                    task->actor->tile.x = task->dest[1];
                    task->actor->pos.x = task->actor->tile.x << 8;
                    task->actor->tile.y = task->dest[2];
                    task->actor->pos.y = task->actor->tile.y << 8;
                    task->nextSubstate(task);
                    break;
                }
                d = func_8008B410(task->counter, task->dist.x);
                if (task->negX) {
                    task->actor->tile.x = task->start.x - d;
                } else {
                    task->actor->tile.x = task->start.x + d;
                }
                task->actor->pos.x = task->actor->tile.x << 8;
                d = func_8008B410(task->counter, task->dist.y);
                if (task->negY) {
                    task->actor->tile.y = task->start.y - d;
                } else {
                    task->actor->tile.y = task->start.y + d;
                }
                task->actor->pos.y = task->actor->tile.y << 8;
                task->actor->dir = (GFX_FUNCS.getTime() >> 1) & 7;
                task->actor->unk74 = 0;
                break;
            }
            break;
        default:
            task->setState(task, 3);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        task->actor->dir = 0;
        task->actor->unk74 = 1;
        D_800990B4.unk58 = 0;
        task->actor->unk130(task->actor);
        func_800901D4();
        break;
    }
}

Unk8008B450 *func_8008B930(Actor *actor, s32 arg1) {
    Unk8008B450 *task = createTask(func_8008B450, sizeof(Unk8008B450), 0);

    task->actor = actor;
    task->dest = (s16 *)arg1;
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

/* A gauge game: a cursor runs back and forth along one of the gauge rows until
 * cross is pressed, then slows down and stops; the cell it stops on (2 bits)
 * fails (0) or calls D_8009A6EC[0] with 4 (1) or 7 (2). In Europe the rows are
 * random only while GAME.unk26F8 lasts, then it is row 8, all zeros. The match
 * depends on the cell read and shifted as two statements. */
void func_8008C59C(Unk8008C59C *task) {
    SpriteDrawer drawer;
    SpriteDrawer gauge;
    s32 sprites;
    s32 gaugeSprites;
    u8 cell;
    s32 index;
    s32 shift;

    switch (task->state) {
    case 0:
    default:
#if VERSION_EU
        if (GAME.unk26F8 > 0) {
            task->row = RANDOM.next() & 7;
            GAME.unk26F8--;
        } else {
            task->row = 8;
        }
#else
        task->row = RANDOM.next() & 7;
#endif
        task->speed = 0x100;
        task->nextState(task);
    case 1:
        switch (task->substate) {
        case 0:
        default:
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step > 0x5A) {
                task->nextSubstate(task);
            }
            break;
        case 1:
            switch (task->step) {
            case 0:
            default:
                if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
                    if (!(RANDOM.next() & 3)) {
                        task->setStep(task, 2);
                    } else {
                        task->setStep(task, 1);
                    }
                    SOUND.playSound(0x4001B);
                }
                break;
            case 1:
                task->speed -= 0x10;
                if (task->speed == 0) {
                    task->setStep(task, 3);
                }
                break;
            case 2:
                task->speed -= 4;
                if (task->speed == 0) {
                    task->setStep(task, 3);
                }
                break;
            case 3:
#if VERSION_EU
                index = task->cursor >> 10;
                shift = (task->cursor >> 7) & 6;
                cell = FIELDSTG_gaugeRows[task->row][index];
                cell = (cell >> shift) & 3;
                if (task->counter < 0x3C) {
                    if (task->counter == 0 && cell == 1) {
                        SOUND.playSound(0x80045341);
                    }
                    task->counter += GFX_FUNCS.getFrameTime();
                    break;
                }
#else
                task->counter += GFX_FUNCS.getFrameTime();
                if (task->counter < 0x3C) {
                    break;
                }
                index = task->cursor >> 10;
                shift = (task->cursor >> 7) & 6;
                cell = FIELDSTG_gaugeRows[task->row][index];
                cell = (cell >> shift) & 3;
#endif
                switch (cell) {
                case 0:
                default:
                    task->setState(task, 3);
                    break;
                case 1:
                    D_8009A6EC[0](4);
                    task->setState(task, 2);
                    break;
                case 2:
                    D_8009A6EC[0](7);
                    task->setState(task, 2);
                    break;
                }
                break;
            }
            if (task->back) {
                task->cursor -= task->speed;
                if (task->cursor <= 0) {
                    task->cursor = 0;
                    task->back = 0;
                }
            } else {
                task->cursor += task->speed;
                if (task->cursor >= 0x3000) {
                    task->cursor = 0x3000;
                    task->back = 1;
                }
            }
            sprites = FILE_CACHE.getEntry(FIELD_SPRITES_FILE << 16);
            initSpriteDrawer(&drawer);
            drawer.setLayerId(0x1002, 4);
            drawer.setTexture(0x200, 0x100);
            drawer.draw(sprites, GFX_FUNCS.getTime() % 48 / 12 + 0x60, task->pos.x, task->pos.y);
            gaugeSprites = FILE_CACHE.getEntry((FIELD_SPRITES_FILE << 16) | 1);
            initSpriteDrawer(&gauge);
            gauge.setLayerId(0x1002, 0);
            gauge.setTexture(0x240, 0x100);
            gauge.setFollowScroll(0);
            gauge.draw(gaugeSprites, 0x3D, (task->cursor >> 8) + 0x18, 0xC0);
            gauge.draw(gaugeSprites, task->row + 0x3E, 0x18, 0xC0);
            gauge.draw(gaugeSprites, 0x3C, 0x18, 0xC0);
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

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

Unk8008CC4C *func_8008CF0C(void) {
    Unk8008CC4C *task = createTaskWithId(func_8008CC4C, sizeof(Unk8008CC4C), 0, 0x10);

    task->voice = -1;
    return task;
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

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_8008D4C4);

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
                                target->unk88 = actor;
                                actor->setSubstate(actor, 0x4D);
                                actor->unk108 = NULL;
                            }
                            break;
                        default:
                            target->setSubstate(target, 0x4A);
                            target->unk88 = actor;
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

/* The player's flight: it rises unless triangle is held (substate 0x4B),
   left and right turn, and cross, low enough, acts on what the player faces;
   the map's cells hold floors (2 to 6) and ceilings (18 to 22). The match
   depends on the button's shift and mask as two statements. */
void func_8008D710(Actor *actor) {
    Point facing;
    Point pos;
    s32 held;
    s32 pressed;
    s32 cell;
    s32 stop;
    s32 height;

    held = PAD.getHeld(0);
    pressed = (u32)PAD.getPressed(0) >> PAD_CROSS;
    pressed &= 1;
    if (D_800990B4.unk50 != 0 || D_800990B4.unk58 != 0 || D_800990B4.unk5C != 0) {
        return;
    }
    if (pressed && actor->unk64 < 0x2000) {
        actor->getFacingTile(actor, &facing);
        if (func_8008D580(actor, &facing)) {
            actor->unkC4 = 0;
            actor->unk68 = 0;
            if (actor->unkC8 != -1) {
                SOUND.keyOff(0xA0045F4A, actor->unkC8);
                actor->unkC8 = -1;
            }
            return;
        }
    }
    if (held & (1 << PAD_TRIANGLE)) {
        if (actor->substate != 0x4B) {
            actor->setSubstate(actor, 0x4B);
        }
        if (actor->unkC8 == -1) {
            actor->unkC8 = SOUND.playSound(0xA0045F4A);
        }
    } else {
        if (actor->substate == 0x4B) {
            actor->setSubstate(actor, 0x4C);
        }
        if (actor->unkC8 != -1) {
            SOUND.keyOff(0xA0045F4A, actor->unkC8);
            actor->unkC8 = -1;
        }
    }
    if (!(GFX_FUNCS.getFrameCount() & 7)) {
        if (held & (1 << PAD_RIGHT)) {
            actor->unkC0 = 1;
            actor->dir = (actor->dir + 1) & 7;
        } else if (held & (1 << PAD_LEFT)) {
            actor->unkC0 = 1;
            actor->dir = (actor->dir - 1) & 7;
        }
    }
    if (actor->substate == 0x4B) {
        if (actor->unkC4 > -0xC0) {
            actor->unkC4 -= 4;
        } else {
            actor->unkC4 = -0xC0;
        }
    } else {
        if (actor->unkC4 < 0x80) {
            actor->unkC4 += 4;
        } else {
            actor->unkC4 = 0x80;
        }
    }
    stop = 0;
    height = 0;
    pos.x = actor->pos.x >> 8;
    pos.y = actor->pos.y >> 8;
    cell = D_8009A70C.getCell(GAME.unk26D8, &pos);
    actor->unk64 += actor->unkC4;
    if (actor->unkC4 > 4) {
        switch ((u8)cell) {
        case 18:
            if (actor->unk64 > 0x6000) {
                stop = 1;
            }
            break;
        case 19:
            if (actor->unk64 > 0x5000) {
                stop = 1;
            }
            break;
        case 20:
            if (actor->unk64 > 0x4000) {
                stop = 1;
            }
            break;
        case 21:
            if (actor->unk64 > 0x3000) {
                stop = 1;
            }
            break;
        case 22:
            if (actor->unk64 > 0x2000) {
                stop = 1;
            }
            break;
        }
    } else {
        switch ((u8)cell) {
        case 2:
            if (actor->unk64 < 0x2000) {
                stop = 1;
                height = 0x200C;
            }
            break;
        case 3:
            if (actor->unk64 < 0x3000) {
                stop = 1;
                height = 0x300C;
            }
            break;
        case 4:
            if (actor->unk64 < 0x4000) {
                stop = 1;
                height = 0x400C;
            }
            break;
        case 5:
            if (actor->unk64 < 0x5000) {
                stop = 1;
                height = 0x500C;
            }
            break;
        case 6:
            if (actor->unk64 < 0x6000) {
                stop = 1;
                height = 0x600C;
            }
            break;
        }
    }
    if (stop || actor->unk64 > 0x7000 || actor->unk64 < 0x1800) {
        if (height != 0) {
            actor->unk64 = height;
        }
        actor->unkC4 = 0;
    }
    if (actor->unk64 >= 0x7000) {
        actor->unk64 = 0x7000;
    }
    if (actor->unk64 <= 0x1800) {
        actor->unk64 = 0x1800;
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_8008DB60);

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
        actor->unk78 = leader->unk78;
    }
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_8008DFE0);

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

void func_8008E698(Actor *actor, FieldWarp *arg1, s32 arg2) {
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

/* The layer's sorted callback that draws an actor: its frame from its image,
 * mirrored for the directions 5 and up, and, when it has one, its shadow, a
 * sprite with its own texture page. The match depends on the shadow's y offset
 * cast to s16. */
void func_8008E7E0(void *arg, void *arg2) {
    Actor *actor = arg;
    Layer *layer = arg2;
    ActorImage *image = actor->image;
    Point pos;
    Point scroll;
    u_long *ot;
    POLY_FT4 *poly;
    FieldImage *shadow;
    s32 x;

    if (actor->state == 1) {
        ot = (u_long *)layer->getOtEntry(layer, actor->unk78);
        pos = actor->tile;
        layer->getScroll(layer, &scroll);
        pos.x -= scroll.x;
        pos.y -= scroll.y;
        poly = GFX_FUNCS.getPrim();
        pos.y -= actor->unk64 >> 8;
        setPolyFT4(poly);
        setRGB0(poly, 0x80, 0x80, 0x80);
        x = actor->unkD4[2];
        if (actor->dir >= 5) {
            x = -(actor->unkE4 + x);
        }
        poly->x0 = pos.x + x;
        poly->x1 = actor->unkE4 + (pos.x + x);
        poly->x2 = pos.x + x;
        poly->x3 = actor->unkE4 + (pos.x + x);
        poly->y0 = actor->unkD4[3] + pos.y;
        poly->y1 = actor->unkD4[3] + pos.y;
        poly->y2 = actor->unkE6 + (actor->unkD4[3] + pos.y);
        poly->y3 = actor->unkE6 + (actor->unkD4[3] + pos.y);
        if (actor->dir < 5) {
            poly->u0 = image->u;
            poly->u1 = actor->unkE4 + image->u;
            poly->u2 = image->u;
            poly->u3 = actor->unkE4 + image->u;
        } else {
            poly->x1--;
            poly->x3--;
            poly->u0 = actor->unkE4 + image->u - 1;
            poly->u1 = image->u;
            poly->u2 = actor->unkE4 + image->u - 1;
            poly->u3 = image->u;
        }
        poly->v0 = image->v;
        poly->v1 = image->v;
        poly->v2 = actor->unkE6 + image->v;
        poly->v3 = actor->unkE6 + image->v;
        poly->clut = getClut(image->clutX, image->clutY);
        poly->tpage = getTPage(0, 0, image->x, image->y);
        addPrim(ot, poly);
        pos.y += actor->unk64 >> 8;
        poly++;
        if (actor->unk74 != 0) {
            ot = (u_long *)layer->getOtEntry(layer, actor->unk78 + 1);
            shadow = actor->unk70;
            setSprt((SPRT *)poly);
            setRGB0((SPRT *)poly, 0x80, 0x80, 0x80);
            ((SPRT *)poly)->x0 = pos.x - 16;
            ((SPRT *)poly)->y0 = pos.y + (s16)((actor->unk90 >> 8) - 8);
            ((SPRT *)poly)->u0 = shadow->shadow.u;
            ((SPRT *)poly)->v0 = shadow->shadow.v;
            ((SPRT *)poly)->w = 0x20;
            ((SPRT *)poly)->h = 0x10;
            ((SPRT *)poly)->clut = getClut(shadow->shadow.clutX, shadow->shadow.clutY);
            addPrim(ot, poly);
            poly = (POLY_FT4 *)((SPRT *)poly + 1);
            SetDrawTPage((DR_TPAGE *)poly, 0, 1, GetTPage(0, 0, shadow->shadow.x, shadow->shadow.y));
            addPrim(ot, poly);
            poly = (POLY_FT4 *)((DR_TPAGE *)poly + 1);
        }
        GFX_FUNCS.setPrim(poly);
    }
}

void func_8008EC6C(Actor *actor, s32 arg1) {
    actor->dir = arg1;
}

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_8008EC74);

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

/* The voice of the sound 0xA064683C (s16; its unit defines it as halfwords,
   for the European padding after it) */
extern s16 D_8009AA48;

/*
 * Runs an actor's action, its substate: the walks, the moves of 0x44 to 0x47
 * (which shift it by a tile, left or right by unk8C), the talk of 0x4A (the
 * first of the character's talks whose conditions hold) and the events up to
 * 0x50. The
 * match depends on the talks' loop testing both of its ends with a break at
 * its top, and on the moves of a tile adding a choice of two steps.
 */
void func_8008F184(Actor *actor, ActorChildren *children) {
    Point move2;
    Point move3;
    Point move4;
    Point move5;
    Point move6;
    FieldTalk *talk;
    Actor *other;
    s32 isX;

    switch (actor->substate) {
    case 1:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 1;
            func_8008E768(actor, 1);
            actor->nextStep(actor);
        case 1:
            break;
        }
        break;
    case 2:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 1;
            func_8008E768(actor, 4);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (!(actor->key2 & 0xE)) {
            D_8009A70C.unk48(&actor->tile, actor->unk68 >> 2, actor->dir, &move2);
            actor->pos.x += move2.x;
            actor->pos.y += move2.y;
        }
        func_8008F028((Task *)actor, 0, 0);
        break;
    case 3:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 1;
            func_8008E768(actor, 5);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (!(actor->key2 & 0xE)) {
            D_8009A70C.unk48(&actor->tile, actor->unk68, actor->dir, &move3);
            actor->pos.x += move3.x;
            actor->pos.y += move3.y;
        }
        func_8008F028((Task *)actor, 1, 1);
        if (GAME.funcs.getMode() != 0x22D && actor->key2 == 0) {
            func_8008D2A0(actor);
        }
        break;
    case 0x4C:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 1;
            func_8008E768(actor, 1);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unk68 != 0) {
            actor->unk68 -= 8;
            if (actor->unk68 < 0) {
                actor->unk68 = 0;
            }
            D_8009A70C.unk4C(&actor->tile, actor->unk68, actor->dir, &move4);
            actor->pos.x += move4.x;
            actor->pos.y += move4.y;
            func_8008D2A0(actor);
        }
        break;
    case 0x4B:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 1;
            func_8008E768(actor, 4);
            actor->unk68 = 0;
            actor->nextStep(actor);
        case 1:
            break;
        }
        actor->unk68 += 8;
#if VERSION_EU
        if (NTSC_MODE != 0) {
            if (actor->unk68 > 0x200) {
                actor->unk68 = 0x200;
            }
        } else if (actor->unk68 > 0x266) {
            actor->unk68 = 0x266;
        }
#else
        if (actor->unk68 > 0x200) {
            actor->unk68 = 0x200;
        }
#endif
        D_8009A70C.unk4C(&actor->tile, actor->unk68, actor->dir, &move4);
        actor->pos.x += move4.x;
        actor->pos.y += move4.y;
        func_8008F028((Task *)actor, 1, 1);
        func_8008D2A0(actor);
        break;
    case 4:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 6);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 != 0) {
            actor->setSubstate(actor, 1);
        }
        break;
    case 5:
        switch (actor->step) {
        case 0:
        default:
            D_800990B4.unk60 = 1;
            if (actor->unk84 == 0) {
                func_8008E768(actor, 5);
            }
            actor->nextStep(actor);
        case 1:
            break;
        }
        D_8009A70C.unk48(&actor->tile, actor->unk68, actor->dir, &move5);
        actor->pos.x += move5.x;
        actor->pos.y += move5.y;
        if (actor->unk84 == 0) {
            func_8008F028((Task *)actor, 1, 0);
        }
        break;
    case 0x4F:
        switch (actor->step) {
        case 0:
        default:
            D_800990B4.unk60 = 1;
            func_8008E768(actor, 1);
            D_8009AA48 = SOUND.playSound(0xA064683C);
            actor->nextStep(actor);
        case 1:
            break;
        }
        D_8009A70C.unk48(&actor->tile, actor->unk68, actor->dir, &move6);
        actor->pos.x += move6.x;
        actor->pos.y += move6.y;
        break;
    case 0x50:
        if (actor->step == 0) {
            SOUND.keyOff(0xA064683C, D_8009AA48);
        }
        actor->step += GFX.funcs.getFrameTime();
        if (actor->step >= 0x1E) {
            D_800990B4.unk60 = 0;
            actor->setSubstate(actor, 1);
            func_8008F014(actor);
        }
        break;
    case 0x40:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 0x20);
            actor->nextStep(actor);
        case 1:
            break;
        }
        break;
    case 0x41:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 0x1A);
            actor->nextStep(actor);
        case 1:
            break;
        }
        actor->unk90 += 0x100;
        if (actor->unk90 >= actor->unk94) {
            actor->unk90 = actor->unk94;
            actor->setSubstate(actor, 0x45);
            actor->unk108 = NULL;
        }
        func_8008F11C((Task *)actor);
        break;
    case 0x42:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 0x1B);
            actor->nextStep(actor);
        case 1:
            break;
        }
        actor->unk90 -= 0x100;
        if (actor->unk90 <= 0) {
            actor->unk90 = 0;
            actor->setSubstate(actor, 0x46);
            actor->unk108 = NULL;
        }
        func_8008F11C((Task *)actor);
        break;
    case 0x43:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 0x1C);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 != 0) {
            actor->setSubstate(actor, 0x40);
            actor->unk108 = func_8008DCF8;
        }
        break;
    case 0x44:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 0;
            func_8008E768(actor, 0x1E);
            actor->pos.x += actor->unk8C != 0 ? 0x1000 : -0x1000;
            actor->pos.y += 0x1800 + actor->unk94;
            func_8008CF44(0, 2);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 == 0) {
            break;
        }
        actor->setSubstate(actor, 0x40);
        actor->unk108 = func_8008DCF8;
    case 0:
    default:
        actor->unk74 = 1;
        break;
    case 0x46:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 0x1F);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 != 0) {
            actor->setSubstate(actor, 1);
            func_8008F014(actor);
            func_800901D4();
            actor->dir = 0;
            D_800990B4.unk60 = 0;
        }
        break;
    case 0x45:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 0;
            func_8008E768(actor, 0x1D);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 != 0) {
            actor->setSubstate(actor, 1);
            actor->unk74 = 1;
            func_8008E768(actor, 1);
            func_800901D4();
            func_8008F014(actor);
            actor->pos.x += actor->unk8C != 0 ? -0x1000 : 0x1000;
            actor->pos.y -= 0x1800 + actor->unk94;
            func_8008CF44(0, 2);
            D_800990B4.unk60 = 0;
        }
        break;
    case 0x47:
        switch (actor->step) {
        case 0:
        default:
            actor->unk74 = 0;
            func_8008E768(actor, 0x16);
            actor->pos.y += actor->unk94;
            actor->pos.x += actor->unk8C != 0 ? 0x1000 : -0x1000;
            actor->nextStep(actor);
        case 1:
            if (actor->unkE8 == 0) {
                break;
            }
            func_8008E768(actor, 0x17);
            actor->nextStep(actor);
        case 2:
            actor->unk74 = 1;
            actor->unk90 -= 0x300;
            if (actor->unkA0 == 0x17 && actor->unk94 - actor->unk90 > 0x1800) {
                func_8008E768(actor, 0x18);
            }
            if (actor->unk90 <= 0) {
                actor->unk90 = 0;
                func_8008E768(actor, 0x19);
                SOUND.playSound(0x8004593E);
                actor->nextStep(actor);
            }
            break;
        case 3:
            if (actor->unkE8 != 0) {
                actor->setSubstate(actor, 1);
                func_8008E768(actor, 1);
                func_8008F014(actor);
                func_800901D4();
                D_800990B4.unk60 = 0;
            }
            break;
        }
        break;
    case 0x48:
        switch (actor->step) {
        case 0:
        default:
            func_8008E768(actor, 0x11);
            actor->nextStep(actor);
        case 1:
            if (actor->unkE8 == 0) {
                break;
            }
            func_8008E768(actor, 0x13);
            SOUND.playSound(0x80045CC5);
            actor->nextStep(actor);
        case 2:
            if (actor->unkE8 == 0) {
                break;
            }
            func_8008E768(actor, 0x14);
            SOUND.playSound(0x80045D46);
            actor->nextStep(actor);
        case 3:
            if (children->unk8 != NULL) {
                break;
            }
            children->unk4 = func_800878A4(0, 1, 6);
            func_8008E768(actor, 0x12);
            actor->nextStep(actor);
        case 4:
            actor->counter += GFX.funcs.getFrameTime();
            if (actor->counter < 0x3C) {
                break;
            }
            children->unk4->setState(children->unk4, 2);
            func_8008E768(actor, 0x15);
            actor->nextStep(actor);
        case 5:
            if (actor->unkE8 != 0) {
                actor->setSubstate(actor, 1);
                func_8008E768(actor, 1);
                func_8008F014(actor);
                D_800990B4.unk58 = 0;
            }
            break;
        }
        break;
    case 0x49:
        switch (actor->step) {
        case 0:
        default:
            actor->unk108 = NULL;
            func_8008E768(actor, 8);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 != 0) {
            actor->setSubstate(actor, 1);
            func_8008E768(actor, 1);
            func_8008F014(actor);
            D_800990B4.unk60 = 0;
        }
        break;
    case 0x4A:
        isX = 0;
        if (actor->key1 == 0x21 || (actor->key1 >= 0x4D && actor->key1 < 0x58) ||
            (actor->key1 >= 0x154 && actor->key1 < 0x159) || actor->key1 == 0x15B) {
            isX = 1;
        }
        switch (actor->step) {
        case 0:
        default:
            talk = actor->entry->talks;
            while (1) {
                if (talk->conditions == NULL) {
                    break;
                }
                if (FLAGS_00.checkConditions(talk->conditions) == 1) {
                    break;
                }
                talk++;
            }
            actor->unkFC = (s32)talk->actions;
            if (!isX && actor->unk100 == 0) {
                actor->dir = (actor->unk88->dir + 4) & 7;
            }
            if (actor->unk9C != 0 && !isX) {
                children->unkC = func_8008848C(actor, talk->unk8);
            } else {
                children->unkC = func_8008848C(actor->unk88, talk->unk8);
            }
            if (isX) {
                func_8008E768(actor, 0x41);
                SOUND.playSound(0x80045DC7);
            }
            actor->nextStep(actor);
            break;
        case 1:
            if (children->unkC == NULL) {
                if (!isX) {
                    actor->setSubstate(actor, 1);
                } else {
                    actor->setState(actor, 3);
                }
                other = actor->unk88;
                if (other->unk84 == 0) {
                    func_8008F014(other);
                } else {
                    other->unk108 = func_8008D710;
                }
                if (actor->unkFC != 0) {
                    FLAGS_00.applyActions((u16 *)actor->unkFC);
                }
                D_800990B4.unk60 = 0;
            }
            break;
        }
        break;
    case 0x4D:
        switch (actor->step) {
        case 0:
        default:
#if VERSION_EU
            D_800990B4.unk60 = 1;
#endif
            actor->unk108 = NULL;
            func_8008E768(actor, 0x45);
            actor->nextStep(actor);
        case 1:
            break;
        }
        if (actor->unkE8 != 0) {
            actor->setSubstate(actor, 1);
            func_8008E768(actor, 1);
            func_8008F014(actor);
#if VERSION_EU
            D_800990B4.unk60 = 0;
#endif
        }
        break;
    case 0x4E:
        switch (actor->step) {
        case 0:
        default:
            if (actor->counter < 0x14) {
                actor->counter += GFX.funcs.getFrameTime();
                break;
            }
            func_8008E768(actor, 0x54);
            SOUND.playSound(0x800446C9);
#if VERSION_EU
            switch (actor->key1) {
            case 0x148:
                FLAGS_00.applyAction(8, 1);
                break;
            case 0x15F:
                FLAGS_00.applyAction(9, 1);
                break;
            case 0x160:
                FLAGS_00.applyAction(0xA, 1);
                break;
            }
#endif
            actor->nextStep(actor);
        case 1:
            if (actor->unkE8 != 0) {
#if VERSION_US
                switch (actor->key1) {
                case 0x148:
                    FLAGS_00.applyAction(8, 1);
                    break;
                case 0x15F:
                    FLAGS_00.applyAction(9, 1);
                    break;
                case 0x160:
                    FLAGS_00.applyAction(0xA, 1);
                    break;
                }
#endif
                actor->setState(actor, 3);
            }
            break;
        }
        break;
    }
}

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

void func_80090294(Actor *actor, ActorChildren *children) {
    Layer *layer;

    switch (actor->state) {
        default:
        case 0:
            if (actor->unk9C == 0 || FILE_CACHE.isLoading(actor->unk9C >> 16) == 0) {
                if (actor->key2 == 0) {
                    children->anim = func_80089668(actor);
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

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_80090450);

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

INCLUDE_RODATA("fieldstg/nonmatchings/fieldstg_5", D_80082E88);

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_80091124);

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

s32 func_800913B4(s32 index) {
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

INCLUDE_ASM("fieldstg/nonmatchings/fieldstg_5", func_80091AA8);

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

void func_8009204C(Point *pos, s32 scale, s32 index, Point *out) {
    out->x = D_8009A76C[0][index].x * scale / 4096;
    out->y = D_8009A76C[0][index].y * scale / 4096;
}
