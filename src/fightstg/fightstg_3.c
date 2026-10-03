/* The third object of FIGHTSTG.PRO (see fightstg.c): its rodata starts at
   0x80082480 (USA). */

#include "fightstg.h"

/* A fighter's entrance: loads its model and adds it, then shows it behind a fade
   (func_80092494) and turns the camera to it; fighter 0x1D2 changes the fight
   stage and 0x1D3 the music. The match depends on substate 7's own ModelControl
   pointer. */
void func_80086180(Unk80086180 *task, Unk80092350 **children) {
    Models *models = task->models;
    BattleCamera *camera = task->camera;
    FightStage *stage = task->stage;
    s32 is1D2 = task->key1 == 0x1D2;
    s32 is1D3 = task->key1 == 0x1D3;
    ModelControl *control;
    ModelControl *entering;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            models = TASK_REGISTRY.funcs.find(0x14, -1, -1);
            task->models = models;
            task->camera = TASK_REGISTRY.funcs.find(0x12, -1, -1);
            task->stage = TASK_REGISTRY.funcs.find(0x15, -1, -1);
            task->file = D_800A32E0.funcs.getInfo(task->key1)->model >> 16;
            FILE_CACHE.request(task->file);
            task->nextSubstate(task);
        case 1:
            if (FILE_CACHE.isLoading(task->file) != 0) {
                break;
            }
            models->add(models, task->key2 + 1, task->key1, 0);
            if (!is1D2 && !is1D3) {
                task->nextState(task);
                break;
            }
            task->nextSubstate(task);
        case 2:
            switch (task->step) {
            case 0:
            default:
                if (is1D2) {
                    FILE_CACHE.request(FILE_ENTRANCE_1D2);
                } else {
                    SOUND_STATE.fadeOut(0x60900000);
                    SOUND_STATE.loadBank(0x26);
                }
                task->nextStep(task);
                break;
            case 1:
                if (is1D2) {
                    if (FILE_CACHE.isLoading(FILE_ENTRANCE_1D2) == 0) {
                        task->nextState(task);
                    }
                } else if (SOUND_STATE.isLoading() == 0) {
                    task->nextState(task);
                }
                break;
            }
            break;
        }
        break;
    case 1:
        switch (task->substate) {
        case 0:
            camera->fade(camera, NULL, camera->getFighterView(camera, task->key2, task->key2 != 0 ? 2 : 10), 60);
            task->nextSubstate(task);
        case 1:
            task->counter += GFX_FUNCS.getFrameTime();
            switch (task->step) {
            case 0:
            default:
                if (task->counter < 30) {
                    break;
                }
                models->get(models, task->key2 == 0 ? 0x10 : 0)->unk34[0].enabled = 0;
                task->step++;
            case 1:
                if (task->counter >= 60) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 2:
            SOUND.playSound(0xA0045EC9);
            *children = func_80092494(60);
            task->nextSubstate(task);
        case 3:
            if ((*children)->substate == 0) {
                break;
            }
            task->nextSubstate(task);
            task->done = 1;
            models->setId(models, task->key2 + 1, task->key2);
            models->face(models, task->key2);
            control = models->get(models, task->key2);
            control->unk34[0].arg = 0x1004;
            control->unk34[0].enabled = 1;
            control->unk34[0].alt = 0;
            control->motion = 13;
            camera->set(camera, camera->getFighterView(camera, task->key2, task->key2 != 0 ? 2 : 10));
            if (is1D2) {
                D_80042728.unkC = 0x16;
                stage->setStage(stage, 0x16, 1, 1);
            }
            if (is1D3) {
                D_80042728.unk14 = 0x60980000;
                SOUND.playSound(0x60980000);
            }
            break;
        case 4:
            func_8009245C(*children, 60);
            task->nextSubstate(task);
        case 5:
            if (*children != NULL) {
                break;
            }
            task->nextSubstate(task);
        case 6:
            task->step += GFX_FUNCS.getFrameTime();
            if (is1D2 ? task->step < 10 : task->step < 120) {
                break;
            }
            task->nextSubstate(task);
        case 7:
            camera->fade(camera, NULL, camera->getEnemyView(camera), task->key2 != 0 ? 1 : 60);
            entering = models->get(models, task->key2);
            if (task->unk64 != 0) {
                entering->motion = 2;
            } else {
                entering->motion = 1;
            }
            models->get(models, task->key2 == 0 ? 0x10 : 0)->unk34[0].enabled = 1;
            task->setState(task, 3);
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

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

/* A camera that plays lists of shots (D_800A1258): turns around the fighters,
   fixed views and views of one side with the other side's model hidden */
void func_8008690C(Unk8008690C *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->list = 3;
        task->shot = 0;
        task->time = D_800A1258[task->list][task->shot].time;
        task->setSubstate(task, D_800A1258[task->list][task->shot].substate);
        task->camera = TASK_REGISTRY.funcs.find(0x12, -1, -1);
        task->models = TASK_REGISTRY.funcs.find(0x14, -1, -1);
        task->view = task->camera->getEnemyView(task->camera);
        task->ry = task->view->rot.vy;
        break;
    case 1:
        if (task->time <= 0) {
            task->models->get(task->models, 0)->unk34[0].enabled = 1;
            task->models->get(task->models, 0x10)->unk34[0].enabled = 1;
            if (D_800A1258[task->list][++task->shot].time == -1) {
                task->list = D_800A12B8[task->list][RANDOM.next() % 3];
                task->shot = 0;
            }
            task->time = D_800A1258[task->list][task->shot].time;
            task->setSubstate(task, D_800A1258[task->list][task->shot].substate);
        }
        switch (task->substate) {
        case 1:
        default:
            if (task->step == 0) {
                task->view = task->camera->getEnemyView(task->camera);
                task->turned = 0;
                task->step++;
                if ((D_80042728.unkC & 0xF) != 4) {
                    task->view->rot.vy = task->ry;
                }
            }
            task->view->rot.vy += GFX.funcs.getFrameTime() * 2;
            task->turned += GFX.funcs.getFrameTime() * 2;
            if (task->view->rot.vy >= 0x1000) {
                task->view->rot.vy -= 0x1000;
            }
            task->ry = task->view->rot.vy;
            if ((D_80042728.unkC & 0xF) == 4 && task->turned > 0x800) {
                task->time = 0;
            }
            break;
        case 2:
            if (task->step == 0) {
                task->view = task->camera->getEnemyView(task->camera);
                task->view->vpx = -0x1E80;
                task->view->vpy = -0x500;
                task->view->vpz = 0;
                task->view->vrx = 0;
                task->view->vry = 0x500;
                task->view->vrz = 0;
                task->view->proj = 0x98;
                task->step++;
            }
            break;
        case 3:
            if (task->step == 0) {
                task->models->get(task->models, 0x10)->unk34[0].enabled = 0;
                task->view = task->camera->getFighterView(task->camera, 0, 8);
                task->view->tz -= 0x1400;
                task->view->vpz += 0x1400;
                task->view->vrz += 0x1400;
                task->speed = 1;
                task->step++;
            }
            task->view->rot.vy += GFX_FUNCS.getFrameTime() * task->speed;
            if (task->view->rot.vy >= 0x1000) {
                task->view->rot.vy -= 0x1000;
            }
            break;
        case 4:
            if (task->step == 0) {
                task->models->get(task->models, 0)->unk34[0].enabled = 0;
                task->view = task->camera->getFighterView(task->camera, 0x10, 0);
                task->view->tz += 0x1400;
                task->view->vpz -= 0x1400;
                task->view->vrz -= 0x1400;
                task->speed = 1;
                task->step++;
            }
            task->view->rot.vy -= GFX_FUNCS.getFrameTime() * task->speed;
            if (task->view->rot.vy < 0) {
                task->view->rot.vy += 0x1000;
            }
            break;
        case 5:
            if (task->step == 0) {
                task->models->get(task->models, 0x10)->unk34[0].enabled = 0;
                task->view = task->camera->getFighterView(task->camera, 0, 8);
                task->view->tz -= 0x1400;
                task->view->vpz += 0x1400;
                task->view->vrz += 0x1400;
                task->speed = 1;
                task->step++;
                task->view->rot.vy += 0xE3;
            }
            task->view->rot.vy -= GFX_FUNCS.getFrameTime() * task->speed;
            if (task->view->rot.vy < 0) {
                task->view->rot.vy += 0x1000;
            }
            break;
        case 6:
            if (task->step == 0) {
                task->models->get(task->models, 0)->unk34[0].enabled = 0;
                task->view = task->camera->getFighterView(task->camera, 0x10, 0);
                task->view->tz += 0x1400;
                task->view->vpz -= 0x1400;
                task->view->vrz -= 0x1400;
                task->speed = 1;
                task->step++;
                task->view->rot.vy -= 0xE3;
            }
            task->view->rot.vy += GFX_FUNCS.getFrameTime() * task->speed;
            if (task->view->rot.vy >= 0x1000) {
                task->view->rot.vy -= 0x1000;
            }
            break;
        case 7:
            if (task->step == 0) {
                task->models->get(task->models, 0x10)->unk34[0].enabled = 0;
                task->view = task->camera->getFighterView(task->camera, 0, 10);
                task->step++;
            }
            break;
        case 8:
            if (task->step == 0) {
                task->models->get(task->models, 0x10)->unk34[0].enabled = 0;
                task->view = task->camera->getFighterView(task->camera, 0, 8);
                task->step++;
            }
            break;
        case 9:
            if (task->step == 0) {
                task->view = task->camera->getEnemyView(task->camera);
                task->view->vpx = -0x1400;
                task->view->vpy = -0x2800;
                task->view->vpz = 0;
                task->view->vrx = 0;
                task->view->vry = 0;
                task->view->vrz = 0;
                task->view->proj = 0xC8;
                task->speed = 1;
                task->view->rot.vy -= 0x155;
                task->step++;
            }
            task->view->rot.vy += GFX_FUNCS.getFrameTime() * task->speed;
            if (task->view->rot.vy >= 0x1000) {
                task->view->rot.vy -= 0x1000;
            }
            break;
        case 10:
            if (task->step == 0) {
                task->view = task->camera->getEnemyView(task->camera);
                task->step++;
            }
            break;
        }
        if (task->view != NULL) {
            task->camera->set(task->camera, task->view);
        }
        task->time -= GFX_FUNCS.getFrameTime();
        break;
    case 3:
        task->models->get(task->models, 0)->unk34[0].enabled = 1;
        task->models->get(task->models, 0x10)->unk34[0].enabled = 1;
        task->view = task->camera->getEnemyView(task->camera);
        task->camera->set(task->camera, task->view);
        break;
    case 2:
        break;
    }
}

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

Task *func_8008C090(void);

const SVECTOR D_800824C8 = { 0, 120, 0x7FFF, 0 };

void func_80087870(Unk80087870 *task, Task **children) {
    BattleCamera *camera = task->camera;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            task->models = TASK_REGISTRY.funcs.find(0x14, -1, -1);
            task->camera = TASK_REGISTRY.funcs.find(0x12, -1, -1);
            task->nextSubstate(task);
        case 1:
            switch (task->step) {
            case 0:
            default:
                FIGHTSTG_findEffectSheet(0x33, &task->unk60, &task->sheet, &task->texPos);
                task->nextStep(task);
            case 1:
                if (FILE_CACHE.isLoading(task->sheet >> 16) == 0) {
                    task->nextState(task);
                }
                break;
            }
            break;
        }
        break;
    case 1:
        switch (task->substate) {
        case 0:
            camera->set(camera, camera->getEnemyView(camera));
            children[0] = (Task *)FIGHTSTG_startSpriteEffect(0x33, (SVECTOR *)&D_800824C8);
            SOUND.playSound(0x800429BF);
            task->nextSubstate(task);
        case 1:
            task->counter += GFX_FUNCS.getFrameTime();
            if (task->counter < 10) {
                break;
            }
            children[1] = func_8008C090();
            ((BattleScript *)children[1])->unk50 = 0;
            ((BattleScript *)children[1])->index = task->unk58 + 1;
            ((BattleScript *)children[1])->unk74 = task->unk5C;
            task->nextSubstate(task);
        case 2:
            if (children[1] == NULL) {
                task->setState(task, 3);
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

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

s32 func_80087B14(Unk80087CE4 *task);
s32 func_800883AC(u8 condition, s16 arg);
s32 func_800888C8(u8 kind);
/* in other objects, some of them void where they are defined */
Unk80097F8C *func_80099400();
Task *func_8008C8B8(s32 arg0);
Task *func_80090050(s32 arg0, s32 arg1);
void func_8009B5F8(s32 arg0);
void func_8009B634(s32 arg0);
void func_8009B678(u8 side);
s32 func_800A9840(u8 id, s32 damage); /* WFIGHTMN's */

/* The enemy's turn: a message when its HP is under a tenth, then one for flags 8, 2
   or 4, or else the first action of its battle table entry whose condition holds,
   and what its target makes it do: attack, a technique, a switch to another enemy
   (func_80087B14) or a message. The match depends on the goto into the flag 4
   branch, the case -1 next to default, and the enemies pointers of substates 4 and 5. */
void func_80087CE4(Unk80087CE4 *task, Unk80097F8C **children) {
    BattleFighter *fighter;
    BattleTableEntry *entry;
    Unk800427D6 *tech;
    s32 message;
    s32 index;
    s32 pick;
    s32 i;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            if (D_800A31E8.unkD6 == 1) {
                BattleFighter *enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];

                if (enemy->hp < (s16)(enemy->maxHp / 10)) {
                    *children = func_80099400();
                    task->lines[0] = 0x5F;
                    task->lines[1] = 0x10;
                    (*children)->unkAC(*children, 2, task->lines);
                    func_8009B634(0);
                    task->substate++;
                } else {
                    task->nextState(task);
                }
            } else {
                task->nextState(task);
            }
            break;
        case 1:
            if (*children == NULL) {
                task->state = 3;
            }
            break;
        }
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                index = D_800A25F0.funcs.find(4, 0x10, D_800A31E8.active[1]);
                if (index >= 0) {
                    *children = func_80099400();
                    task->lines[0] = 0x60;
                    task->lines[1] = 0x10;
                    (*children)->unkAC(*children, 2, task->lines);
                    D_800A25F0.events[index].type = 0;
                    task->step++;
                } else {
                    task->nextSubstate(task);
                }
                break;
            case 1:
                if (*children == NULL) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 1:
            fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
            if (fighter->flags & 8) {
                *children = func_80099400();
                message = 0x90;
                goto show;
            }
            if ((fighter->flags & 2) && D_800A3308.unkDC(0x10) != 0) {
                *children = func_80099400();
                message = 0x56;
                goto show;
            }
            if (fighter->flags & 4) {
                *children = func_80099400();
                message = RANDOM.next() % 8 + 0x83;
            show:
                task->lines[0] = message;
                task->lines[1] = 0x10;
                (*children)->unkAC(*children, 2, task->lines);
                task->setSubstate(task, 3);
                break;
            }
            i = 0;
            entry = D_800A2584(fighter->id);
            for (; i < 3; i++) {
                if (func_800883AC(entry->actions[i].condition, entry->actions[i].conditionArg) != 0) {
                    break;
                }
            }
            task->target = func_800888C8(entry->actions[i].target);
            task->substate++;
            break;
        case 2:
            if (task->target > 0) {
                if (task->target == 1) {
                    *children = (Unk80097F8C *)func_8008C8B8(0x10);
                } else {
                    fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                    tech = &D_800427D6[task->target];
                    if (fighter->mp >= tech->mp) {
                        *children = (Unk80097F8C *)func_80090050(0x10, task->target);
                        fighter->mp -= tech->mp;
                    } else {
                        *children = func_80099400();
                        task->lines[0] = 0x8D;
                        task->lines[1] = 0x10;
                        (*children)->unkAC(*children, 2, task->lines);
                    }
                }
                task->substate = 3;
            } else if (task->target < 0) {
                switch (task->target) {
                case -1:
                default:
                    func_8009B678(0x10);
                    *children = func_80099400();
                    task->lines[0] = 0x5E;
                    task->lines[1] = 0x10;
                    (*children)->unkAC(*children, 2, task->lines);
                    task->substate = 3;
                    break;
                case -2:
                case -3:
                case -4:
                case -5:
                    pick = func_80087B14(task);
                    if (pick != -1) {
                        task->unk7C = pick;
                        *children = func_80099400();
                        task->lines[0] = 0x4D;
                        (*children)->unkAC(*children, 1, task->lines);
                        task->substate = 5;
                    } else {
                        *children = func_80099400();
                        task->lines[0] = 0x8E;
                        task->lines[1] = 0x10;
                        (*children)->unkAC(*children, 2, task->lines);
                        task->substate = 3;
                    }
                    break;
                }
            }
            break;
        case 3:
            if (*children == NULL) {
                task->state = 3;
                func_8009B5F8(D_800A25F0.funcs.getDelay(0x10, 0));
            }
            break;
        case 4:
            if (*children == NULL) {
                BattleFighter *enemies = D_800A31E8.fighters[1];
                BattleTableEntry *enemy = D_800A2584(enemies[D_800A31E8.active[1]].id);

                *children = func_80099400();
                task->lines[0] = enemy->nameId;
                (*children)->unkAC(*children, 0xD, task->lines);
                task->substate = 3;
            }
            break;
        case 5:
            if (*children == NULL) {
                BattleFighter *enemies = D_800A31E8.fighters[1];

                *children = (Unk80097F8C *)func_80086780(enemies[task->unk7C].id, 1, 0);
                func_800A9840(0x10, 0);
                task->substate = 6;
            }
            break;
        case 6:
            if (((Unk80086180 *)*children)->done) {
                D_800A31E8.active[1] = task->unk7C;
                task->substate = 4;
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void func_80088380(void) {
    createTask(func_80087CE4, 0x80, 2 * sizeof(Task *));
}

/* Whether the condition of an enemy's action holds (BattleTableAction): always, a
   chance in 128, the enemy's or the partner's HP over or under a share, its MP, the
   partner's Digimon or flags, the other enemies, the battle and the enemy's boosts.
   The match depends on the one fighter pointer that the cases set as they need it,
   on case 1 keeping its roll in the same variable as the HP share, and on case 10's
   own loop counter. */
s32 func_800883AC(u8 condition, s16 arg) {
    BattleFighter *fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
    s32 result = 0;
    s32 percent;
    s32 j;
    DigimonData *digimon;
    s32 i;

    switch (condition) {
    case 0:
    default:
        result = 1;
        break;
    case 1:
        percent = RANDOM.next() % 128;
        if (percent < arg) {
            result = 1;
        }
        break;
    case 2:
        percent = arg * 100 / 128;
        if (fighter->hp < (s16)(fighter->maxHp / 100) * percent) {
            result = 1;
        }
        break;
    case 3:
        percent = arg * 100 / 128;
        if (fighter->hp >= (s16)(fighter->maxHp / 100) * percent) {
            result = 1;
        }
        break;
    case 4:
        if (fighter->mp < arg) {
            result = 1;
        }
        break;
    case 5:
        if (fighter->mp >= arg) {
            result = 1;
        }
        break;
    case 6:
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        percent = arg * 100 / 128;
        if (fighter->hp < (s16)(fighter->maxHp / 100) * percent) {
            result = 1;
        }
        break;
    case 7:
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        percent = arg * 100 / 128;
        if (fighter->hp >= (s16)(fighter->maxHp / 100) * percent) {
            result = 1;
        }
        break;
    case 8:
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        for (i = 0, digimon = DIGIMON_DATA; i < 8; i++, digimon++) {
            if (fighter->id == digimon->id) {
                result = 1;
                break;
            }
        }
        break;
    case 9:
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        if (fighter->flags & 8) {
            result = 1;
        }
        break;
    case 10:
        fighter = D_800A31E8.fighters[1];
        if (arg == 0) {
            for (j = 0; j < 3; j++) {
                if (j != D_800A31E8.active[1] && fighter[j].id != 0 && fighter[j].hp != 0) {
                    result = 1;
                    break;
                }
            }
        } else {
            for (j = 0; j < 3; j++) {
                if (j != D_800A31E8.active[1] && fighter[j].id == arg && fighter[j].hp != 0) {
                    result = 1;
                    break;
                }
            }
        }
        break;
    case 11:
        if (D_800A31E8.unkD0 == arg) {
            result = 1;
        }
        break;
    case 12:
        if (D_80042728.unk10 == arg) {
            result = 1;
        }
        break;
    case 13:
        if (D_80042728.unk3D == arg) {
            result = 1;
        }
        break;
    case 14:
        if (fighter->unkE != 0) {
            result = 1;
        }
        break;
    case 15:
        if (fighter->boosts[0] < 0) {
            result = 1;
        }
        break;
    case 16:
        if (fighter->boosts[1] < 0) {
            result = 1;
        }
        break;
    case 17:
        if (fighter->boosts[2] < 0) {
            result = 1;
        }
        break;
    case 18:
        if (fighter->unk4 % arg == 0) {
            result = 1;
        }
        break;
    }
    return result;
}

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

/* where func_80089458's effects are */
const SVECTOR D_80082560 = { 0, 0, 0x7FFF, 0 };
const SVECTOR D_80082568 = { 160, 120, 0x7FFF, 0 };
const SVECTOR D_80082570 = { -160, -120, -1, 0 };

/* A partner Digimon's change: a stage of its own, the new Digimon's model in
   front of a sprite effect, the old one wiped away by the clips of layers 0x1004
   and 0x1003, and a fade back to the battle. The match depends on the block
   of its own for substate 2's control, on z read and then negated, on the
   if/else of the motion, on clip1.h written before clip1.y in substate 3 and on
   the layers kept in blocks of their own */
void func_80089458(Unk80089458 *task, Unk80089458Children *children) {
    Models *models = task->models;
    BattleCamera *camera = task->camera;
    FightStage *stage = task->stage;
    TimLoader loader;
    ModelControl *control;
    s32 z;
    s32 t;
    s16 y;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                SOUND_STATE.loadBank(0x45);
                task->nextStep(task);
            case 1:
                if (SOUND_STATE.isLoading() == 0) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 1:
            models = TASK_REGISTRY.funcs.find(0x14, -1, -1);
            task->models = models;
            task->camera = TASK_REGISTRY.funcs.find(0x12, -1, -1);
            task->stage = TASK_REGISTRY.funcs.find(0x15, -1, -1);
            task->file = D_800A32E0.funcs.getInfo(task->key1)->model >> 16;
            FILE_CACHE.request(task->file);
            task->idleMotion = models->get(models, 0)->idleMotion;
            task->nextSubstate(task);
        case 2:
            if (FILE_CACHE.isLoading(task->file) != 0) {
                break;
            }
            FILE_CACHE.request(FILE_CHANGE);
            task->nextSubstate(task);
        case 3:
            if (FILE_CACHE.isLoading(FILE_CHANGE) != 0) {
                break;
            }
            initTimLoader(&loader);
            loader.setImagePos(0x300, 0x100);
            loader.loadArchive(FILE_CACHE.getEntry((FILE_CHANGE << 16) | 5));
            task->nextState(task);
            break;
        }
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            stage->setStage(stage, task->key2 != 0 ? 0x1F : 0x1C, 0x20, 0x20);
            task->nextSubstate(task);
        case 1:
            switch (task->step) {
            case 0:
            default:
                if (stage->state == 2) {
                    break;
                }
                SOUND.playSound(0x41140000);
                models->add(models, 1, task->key1, 0);
                task->nextStep(task);
            case 1:
                task->counter += GFX_FUNCS.getFrameTime();
                if (task->counter >= 180) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 2:
            {
                ModelControl *control;

                task->clip0.x = 0;
                task->clip0.y = 0;
                task->clip0.w = 320;
                task->clip0.h = 240;
                task->clip1.x = 0;
                task->clip1.y = 240;
                task->clip1.w = 320;
                task->clip1.h = 0;
                control = models->get(models, 0);
                camera->getFighterView(camera, 0, 9);
                z = control->homePos.z;
                z = -z;
                D_800A3438.vpz += z;
                D_800A3438.vrz += z;
                camera->set(camera, &D_800A3438);
                control->unk34[1].enabled = 1;
                control->unk34[1].alt = 1;
                control->unk34[1].arg = 0x1003;
                control->pos.x = 0;
                control->pos.z = 0;
                control->rot.x = 0;
                control->rot.y = 0x800;
                control->rot.z = 0;
                control->pos.y = control->homePos.y;
                if (task->key2 != 0) {
                    control->motion = 14;
                } else {
                    control->motion = 13;
                }
                models->get(models, 0x10)->unk34[0].enabled = 0;
                if (task->key2 == 0) {
                    children->effects[0] = FIGHTSTG_startSpriteEffect(1000, (SVECTOR *)&D_80082560);
                    children->effects[1] = FIGHTSTG_startSpriteEffect(1001, (SVECTOR *)&D_80082560);
                } else {
                    children->effects[0] = FIGHTSTG_startSpriteEffect(1007, (SVECTOR *)&D_80082560);
                }
            }
            task->nextSubstate(task);
        case 3:
            t = GFX.funcs.getFrameTime();
            task->clip0.h -= t * 2;
            task->clip1.h += t * 2;
            task->clip1.y -= t * 2;
            if (task->clip1.y <= 0) {
                task->clip0.h = 0;
                task->clip1.h = 240;
                task->clip1.y = 0;
                models->get(models, 0)->unk34[0].enabled = 0;
                children->effects[2] = FIGHTSTG_startSpriteEffect(1002, (SVECTOR *)&D_80082568);
                task->nextSubstate(task);
            }
            {
                Layer *layer = GFX.funcs.getLayer(0x1004);

                layer->setClipPos(layer, task->clip0.x, task->clip0.y);
                layer->setClipSize(layer, task->clip0.w, task->clip0.h);
                layer = GFX.funcs.getLayer(0x1003);
                layer->setClipPos(layer, task->clip1.x, task->clip1.y);
                layer->setClipSize(layer, task->clip1.w, task->clip1.h);
            }
            break;
        case 4:
            task->counter += GFX_FUNCS.getFrameTime();
            if (task->counter >= 120) {
                task->nextSubstate(task);
            }
            break;
        case 5:
            switch (task->step) {
            case 0:
            default:
                children->fade = func_80092494(32);
                task->nextStep(task);
                break;
            case 1:
                if (children->fade->substate != 0) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 6:
            models->setId(models, 1, 0);
            control = models->get(models, 0);
            control->unk34[0].enabled = 1;
            control->unk34[0].arg = 0x1004;
            control->unk34[0].alt = 0;
            control->unk34[1].enabled = 1;
            control->unk34[1].alt = 1;
            control->unk34[1].arg = 0x1003;
            models->face(models, 0);
            camera->getFighterView(camera, 0, 9);
            z = control->homePos.z;
            z = -z;
            D_800A3438.vpz += z;
            D_800A3438.vrz += z;
            camera->set(camera, &D_800A3438);
            control->pos.x = 0;
            control->pos.z = 0;
            control->rot.x = 0;
            control->rot.y = 0x800;
            control->rot.z = 0;
            control->pos.y = control->homePos.y;
            task->clip0.x = 0;
            task->clip0.y = 0;
            task->clip0.w = 320;
            task->clip0.h = 0;
            task->clip1.x = 0;
            task->clip1.y = 0;
            task->clip1.w = 320;
            task->clip1.h = 240;
            task->nextSubstate(task);
        case 7:
            switch (task->step) {
            case 0:
            default:
                children->fade->setState(children->fade, 2);
                task->nextStep(task);
                break;
            case 1:
                if (children->fade == NULL) {
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 8:
            t = GFX_FUNCS.getFrameTime();
            task->clip0.h += t * 2;
            task->clip1.y += t * 2;
            task->clip1.h -= t * 2;
            if (task->clip0.h >= 240) {
                task->clip0.h = 240;
                task->clip1.y = 240;
                task->clip1.h = 0;
                models->get(models, 0)->unk34[1].enabled = 0;
                children->effects[3] = FIGHTSTG_startSpriteEffect(task->key2 == 0 ? 1003 : 1008, (SVECTOR *)&D_80082570);
                task->nextSubstate(task);
            }
            {
                Layer *layer = GFX.funcs.getLayer(0x1004);

                layer->setClipPos(layer, task->clip0.x, task->clip0.y);
                layer->setClipSize(layer, task->clip0.w, task->clip0.h);
                layer = GFX.funcs.getLayer(0x1003);
                layer->setClipPos(layer, task->clip1.x, task->clip1.y);
                layer->setClipSize(layer, task->clip1.w, task->clip1.h);
            }
            break;
        case 9:
            models->get(models, 0)->motion = 13;
            task->nextSubstate(task);
        case 10:
            task->counter += GFX_FUNCS.getFrameTime();
            if (task->counter >= 180) {
                task->nextSubstate(task);
            }
            break;
        case 11:
            stage->setStage(stage, D_80042728.unkC, 0x20, 0x20);
            task->nextSubstate(task);
        case 12:
            if (stage->state != 2) {
                models->face(models, 0);
                camera->set(camera, camera->getFighterView(camera, 0, 9));
                task->nextSubstate(task);
            }
            break;
        case 13:
            task->nextSubstate(task);
            break;
        case 14:
            switch (task->step) {
            case 0:
            default:
                models->get(models, 0x10)->unk34[0].enabled = 1;
                models->get(models, 0)->motion = task->key2 != 0 || task->idleMotion == 0 ? 1 : 2;
                camera->fade(camera, NULL, camera->getEnemyView(camera), 60);
                SOUND.playSound(D_80042728.unk14);
                task->nextStep(task);
                break;
            case 1:
                task->counter += GFX_FUNCS.getFrameTime();
                if (task->counter >= 60) {
                    task->setState(task, 3);
                }
                break;
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

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
