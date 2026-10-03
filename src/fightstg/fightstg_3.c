/* The third object of FIGHTSTG.PRO (see fightstg.c): its rodata starts at
   0x80082480 (USA). */

#include "fightstg.h"

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80086180);

Unk80086180 *func_80086780(s32 id, s32 side, s32 arg2) {
    Unk80086180 *task = createTask(func_80086180, sizeof(Unk80086180), 0xC);

    task->key1 = id;
    if (side) {
        task->key2 = 0x10;
    } else {
        task->key2 = 0;
    }
    task->unk64 = arg2;
    return task;
}

void func_800867F0(Task *task, Task **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (GAME_FUNCS.getModeArg()) {
            OVERLAY_FUNCS->loadSubOverlay(FILE_WFIGHTTS);
            D_80042728.unkC = func_80086084();
            children[0] = WFIGHTTS_start();
        } else {
            OVERLAY_FUNCS->loadSubOverlay(FILE_WFIGHTMN);
            children[0] = WFIGHTMN_start();
        }
        D_800A31E8.unkE8(0);
        task->nextState(task);
        break;
    case TASK_RUN:
        D_800A31E8.unkE4();
        break;
    case 2:
    case TASK_KILL:
        break;
    }
}

void func_800868E0(void) {
    createTask(func_800867F0, sizeof(Task), sizeof(Task *));
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_8008690C);

void func_80087304(void) {
    createTask(func_8008690C, 0x6C, 0);
}

void func_80087330(Models *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

s32 func_80087378(Models *task, s32 id) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (task->controls[i].active && task->controls[i].id == id) {
            return i;
        }
    }
    return -1;
}

s32 func_800873BC(Models *task) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (!task->controls[i].active) {
            return i;
        }
    }
    return -1;
}

void func_800873F0(Models *task, s32 id) {
    ModelsChildren *children = task->children;
    s32 i = func_80087378(task, id);

    if (i != -1) {
        children->dying[i] = children->models[i];
        children->models[i] = NULL;
        children->dying[i]->setState(children->dying[i], TASK_KILL);
        task->controls[i].active = 0;
    }
}

void func_80087480(Models *task, s32 id, s32 fighter, s32 arg3) {
    ModelsChildren *children = task->children;
    FighterInfo *info;
    ModelControl *control;
    s32 i;

    func_800873F0(task, id);
    i = func_800873BC(task);
    if (i != -1) {
        info = D_800A32E0.funcs.getInfo(fighter);
        control = &task->controls[i];
        children->models[i] = func_80083F10(info->model, info->motions, D_800A12D0[i], control);
        HEAP.zero(control, sizeof(ModelControl));
        task->controls[i].active = 1;
        task->controls[i].motion = 1;
        task->controls[i].fighter = fighter;
        task->controls[i].id = id;
        task->controls[i].unk34[0].enabled = arg3;
        task->controls[i].unk34[0].alt = 0;
        task->controls[i].unk34[0].arg = 0x1004;
    }
}

ModelControl *func_800875A8(Models *task, s32 id) {
    s32 i = func_80087378(task, id);

    if (i != -1) {
        return &task->controls[i];
    }
    return NULL;
}

void func_800875FC(Models *task, s32 id, s32 newId) {
    func_800873F0(task, newId);
    task->controls[func_80087378(task, id)].id = newId;
}

s32 func_80087664(Models *task, s32 id) {
    s32 i = func_80087378(task, id);

    if (i != -1) {
        return task->controls[i].fighter;
    }
    return 0;
}

void func_800876B8(Models *task, s32 id) {
    ModelControl *control = func_800875A8(task, id);
    FighterInfo *info;
    s16 z;

    if (control != NULL) {
        info = D_800A32E0.funcs.getInfo(control->fighter);
        if (id < 0x10) {
            control->pos.x = 0;
            control->pos.y = -info->height;
            z = -0x1400 - info->unk10;
            control->rot.y = 0x800;
            control->rot.x = 0;
            control->rot.z = 0;
        } else {
            control->pos.x = 0;
            control->pos.y = -info->height;
            z = info->unk10 + 0x1400;
            control->rot.x = 0;
            control->rot.y = 0;
            control->rot.z = 0;
        }
        control->pos.z = z;
        control->homePos = control->pos;
        control->homeRot = control->rot;
    }
}

void func_800877A4(Models *task, s32 id, s32 motion) {
    ModelControl *control = func_800875A8(task, id);

    if (control != NULL) {
        control->idleMotion = motion;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800877D4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80087870);

void func_80087ACC(s32 arg0, s32 arg1) {
    Unk80087870 *task = createTask(func_80087870, sizeof(Unk80087870), 2 * sizeof(Task *));

    task->unk58 = arg0;
    task->unk5C = arg1;
}

/* The enemy func_80087CE4's task targets: task->target's, or one of the
   others at random (not the active one), -1 for none */
s32 func_80087B14(Unk80087CE4 *task) {
    BattleFighter *enemies = D_800A31E8.fighters[1];
    s32 found[2];
    s32 count;
    s32 active;
    s32 i;

    switch (task->target) {
    case -2:
        if (enemies[0].id == enemies[D_800A31E8.active[1]].id) {
            break;
        }
        if (enemies[0].hp != 0) {
            return 0;
        }
        break;
    case -3:
        if (enemies[1].id == enemies[D_800A31E8.active[1]].id) {
            break;
        }
        if (enemies[1].hp != 0) {
            return 1;
        }
        break;
    case -4:
        if (enemies[2].id == enemies[D_800A31E8.active[1]].id) {
            break;
        }
        if (enemies[2].hp != 0) {
            return 2;
        }
        break;
    default:
        count = 0;
        found[0] = -1;
        found[1] = -1;
        active = D_800A31E8.active[1];
        for (i = 0; i < 3; i++) {
            enemies = &D_800A31E8.fighters[1][i];
            if (active != i && enemies->id != 0 && enemies->hp != 0) {
                found[count++] = i;
            }
        }
        /* the match depends on case 0 and on reusing enemies */
        switch (count) {
        case 0:
            break;
        case 1:
            return found[0];
        case 2:
            return found[RANDOM.next() & 1];
        }
        break;
    }
    return -1;
}

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_800824C8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80087CE4);

void func_80088380(void) {
    createTask(func_80087CE4, 0x80, 2 * sizeof(Task *));
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800883AC);

s32 func_800888C8(u8 kind) {
    BattleFighter *enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
    s32 value = 0;
    BattleTableEntry *entry = D_800A2584(enemy->id);

    switch (kind) {
    case 1:
        value = 1;
        break;
    case 2:
        value = entry->unk8[1];
        break;
    case 3:
        value = entry->unk8[2];
        break;
    case 4:
        value = -1;
        break;
    case 5:
        value = -2;
        break;
    case 6:
        value = -3;
        break;
    case 7:
        value = -4;
        break;
    case 8:
        value = -5;
        break;
    }
    return value;
}

void func_80088994(void) {
}

/* a layer callback; the match depends on taking the task as void * */
void func_8008899C(void *arg, Layer *layer) {
    SpriteAnim *task = arg;
    ShortVec3 screen;
    SpriteDrawer drawer;

    if (task->pos.vz != 0x7FFF && task->pos.vz != -1) {
        D_800A31E8.project(layer, &task->pos, &screen);
    } else {
        screen.x = task->pos.vx;
        screen.y = task->pos.vy;
        if (task->pos.vz != 0x7FFF) {
            screen.z = 0xFFF;
        } else {
            screen.z = 0;
        }
    }
    screen.x += task->x;
    screen.y += task->y;
    initSpriteDrawer(&drawer);
    drawer.setLayer(layer, screen.z);
    drawer.setTexture(task->texPos.x, task->texPos.y);
    if (task->scale.both != 0x10001000) {
        drawer.setScale(task->scale.v[0], task->scale.v[1], 0);
    }
    if (task->clutRow != 0) {
        drawer.setClutRow(task->clutRow);
    }
    if (task->rot.both != 0 || task->rotZ != 0) {
        drawer.setRotation(task->rot.v[0], task->rot.v[1], task->rotZ);
    }
    drawer.setPivot(screen.x, screen.y);
    drawer.draw(FILE_CACHE.getEntry(task->sheet), task->frame, screen.x, screen.y);
}

void FIGHTSTG_updateSpriteAnim(SpriteAnim *task) {
    s16 *data;
    s16 *values;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->flags = *task->data++;
        task->stride = *task->data++;
        task->duration = *task->data++;
        for (i = 0; i < 9; i++) {
            (&task->frame)[i] = *task->data++;
        }
        task->nextState(task);
        /* fallthrough */
    case TASK_RUN:
        data = task->data + task->time * task->stride;
        if (task->flags & 1) {
            task->frame = *data++;
        }
        if (task->flags & 2) {
            task->clutRow = *data++;
        }
        if (task->flags & 4) {
            task->x = *data++;
        }
        if (task->flags & 8) {
            task->y = *data++;
        }
        if (task->flags & 0x10) {
            task->scale.v[0] = *data++;
        }
        if (task->flags & 0x20) {
            task->scale.v[1] = *data++;
        }
        if (task->flags & 0x40) {
            task->rot.v[0] = *data++;
        }
        if (task->flags & 0x80) {
            task->rot.v[1] = *data++;
        }
        if (task->flags & 0x100) {
            task->rotZ = *data;
        }
        if (task->scale.v[0] != 0 && task->scale.v[1] != 0) {
            Layer *layer = GFX_FUNCS.getLayer(task->layerId);

            layer->addCallback(layer, func_8008899C, task);
        }
        task->time += D_800A31E8.frames;
        if (task->time >= task->duration) {
            task->setState(task, TASK_DONE);
        }
        break;
    case TASK_DONE:
        task->nextState(task);
        break;
    case TASK_KILL:
        break;
    }
}

SpriteAnim *FIGHTSTG_createSpriteAnim(s16 *data, SVECTOR *pos, s32 sheet, Vec2 *texPos, s32 layerId) {
    SpriteAnim *task = createTask(FIGHTSTG_updateSpriteAnim, sizeof(SpriteAnim), 0);

    task->data = data;
    task->pos = *pos;
    task->sheet = sheet;
    task->texPos = *texPos;
    task->layerId = layerId;
    return task;
}

void FIGHTSTG_updateEffectModel(EffectModel *task, Model **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->control.unk34[0].enabled = 1;
        task->control.unk34[0].arg = 0x1004;
        task->control.fighter = 0;
        task->control.unk34[0].alt = 0;
        task->control.pos.x = task->pos.vx;
        task->control.pos.y = task->pos.vy;
        task->control.pos.z = task->pos.vz;
        task->control.rot.x = task->rot.vx;
        task->control.rot.y = task->rot.vy;
        task->control.rot.z = task->rot.vz;
        children[0] = func_80083F44(task->file, task->motionFile, task->texPos, &task->control);
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->control.motionDone) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

s32 FIGHTSTG_getEffectModelFile(s32 id) {
    EffectModelEntry *entry;

    for (entry = D_800A12F0; entry->id != 0; entry++) {
        if (entry->id == id) {
            return entry->file >> 16;
        }
    }
    return 0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80088FC4);

s32 FIGHTSTG_findEffectSheet(s32 effect, s32 *unk0, s32 *sheet, Vec2 *texPos) {
    SpriteEffectEntry *entry;

    for (entry = D_800A1C44; entry->id != -1; entry++) {
        if (entry->id == effect) {
            *unk0 = D_800A1914[entry->sheet].unk0;
            *sheet = D_800A1914[entry->sheet].sheet;
            *texPos = D_800A1914[entry->sheet].texPos;
            return 1;
        }
    }
    return 0;
}

void FIGHTSTG_updateSpriteEffect(SpriteEffect *task, SpriteAnim **children) {
    s32 *archive;
    s32 layerId;
    s32 count;
    s32 i;
    s32 j;
    s32 done;

    switch (task->state) {
    case TASK_INIT:
    default:
        archive = (s32 *)FILE_CACHE.getEntry(task->file);
        layerId = 0x1004;
        if (task->effect >= 1000 && task->effect < 1003) {
            layerId = 0x1006;
        }
        if (task->effect == 1007) {
            layerId = 0x1006;
        }
        for (count = 0; count < 30; count++) {
            if (archive[count] == 0) {
                break;
            }
        }
        for (i = 0; i < count; i++) {
            children[i] = FIGHTSTG_createSpriteAnim((s16 *)FILE_CACHE.getArchiveEntry(i, (s32)archive), &task->pos,
                                        D_800A1914[task->sheet].sheet, &D_800A1914[task->sheet].texPos, layerId);
        }
        task->count = count;
        task->nextState(task);
        break;
    case TASK_RUN:
        done = 1;
        for (j = 0; j < task->count; j++) {
            if (children[j] != NULL) {
                done = 0;
                break;
            }
        }
        if (done) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

SpriteEffect *FIGHTSTG_startSpriteEffect(s32 effect, SVECTOR *pos) {
    SpriteEffect *task = createTask(FIGHTSTG_updateSpriteEffect, sizeof(SpriteEffect), 30 * sizeof(Task *));
    SpriteEffectEntry *entry;

    task->effect = -1;
    for (entry = D_800A1C44; entry->id != -1; entry++) {
        if (entry->id == effect) {
            task->effect = effect;
            task->sheet = entry->sheet;
            task->file = entry->file;
            task->pos = *pos;
        }
    }
    if (task->effect == -1) {
        task->setState(task, TASK_KILL);
    }
    return task;
}

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_80082560);

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_80082568);

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_80082570);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80089458);

void func_80089F74(s32 key1, s32 key2) {
    Task *task = createTask(func_80089458, 0x74, 6 * sizeof(Task *));

    task->key1 = key1;
    task->key2 = key2;
}

void FIGHTSTG_startScreenFade(ScreenFade *task, s32 fadeIn, s32 duration) {
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

/* A full-screen rectangle that subtracts the level from the screen */
void FIGHTSTG_drawScreenFade(ScreenFade *task) {
    Layer *layer;
    u_long *ot;
    POLY_F4 *poly;
    DR_TPAGE *mode;

    layer = GFX.funcs.getLayer(task->layerId);
    ot = (u_long *)layer->getOtEntry(layer, task->depth);
    poly = GFX.funcs.getPrim();
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

void FIGHTSTG_updateScreenFade(ScreenFade *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->state = TASK_RUN;
        break;
    case TASK_RUN:
        if (task->substate == 0) {
            break;
        }
        task->level += task->levelStep;
        if (task->fadeIn == 0) {
            if (task->level > 0xFF00) {
                task->level = 0xFF00;
                task->state = TASK_DONE;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = TASK_DONE;
        }
        FIGHTSTG_drawScreenFade(task);
        break;
    case TASK_DONE:
        FIGHTSTG_drawScreenFade(task);
        break;
    case TASK_KILL:
        break;
    }
}

void FIGHTSTG_createScreenFade(void) {
    ScreenFade *task = createTask(FIGHTSTG_updateScreenFade, sizeof(ScreenFade), 0);

    task->start = FIGHTSTG_startScreenFade;
    task->layerId = 0x1006;
    task->depth = 0;
}
