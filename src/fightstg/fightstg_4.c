/* The fourth object of FIGHTSTG.PRO (see fightstg.c), from the stage lights:
   its rodata starts at 0x800825B4 (USA), 4 bytes past a multiple of 8. */

#include "fightstg.h"

void func_8008A270(Lights *task) {
    SVECTOR from;
    SVECTOR to;
    SVECTOR out;
    Layer *layer;
    s32 t;
    s32 i;
    s32 j;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->t = 0x1000;
        task->nextState(task);
        break;
    case TASK_DONE:
        task->setState(task, TASK_RUN);
        task->setSubstate(task, 1);
        /* fallthrough */
    case TASK_RUN:
        switch (task->substate) {
        case 1:
        case 2:
            if (task->t != 0x1000) {
                task->t += task->tStep * GFX_FUNCS.getFrameTime();
                if (task->t < 0x1000) {
                    t = task->t;
                    for (i = 0; i < 3; i++) {
                        from.vx = task->from.lights[i].vx;
                        from.vy = task->from.lights[i].vy;
                        from.vz = task->from.lights[i].vz;
                        to.vx = task->to.lights[i].vx;
                        to.vy = task->to.lights[i].vy;
                        to.vz = task->to.lights[i].vz;
                        D_800A3420.lerp(&from, &to, t, &out);
                        task->current.lights[i].vx = out.vx;
                        task->current.lights[i].vy = out.vy;
                        task->current.lights[i].vz = out.vz;
                        from.vx = task->from.lights[i].r;
                        from.vy = task->from.lights[i].g;
                        from.vz = task->from.lights[i].b;
                        to.vx = task->to.lights[i].r;
                        to.vy = task->to.lights[i].g;
                        to.vz = task->to.lights[i].b;
                        D_800A3420.lerp(&from, &to, t, &out);
                        task->current.lights[i].r = out.vx;
                        task->current.lights[i].g = out.vy;
                        task->current.lights[i].b = out.vz;
                    }
                    from.vx = task->from.ambient[0];
                    from.vy = task->from.ambient[1];
                    from.vz = task->from.ambient[2];
                    to.vx = task->to.ambient[0];
                    to.vy = task->to.ambient[1];
                    to.vz = task->to.ambient[2];
                    D_800A3420.lerp(&from, &to, t, &out);
                    task->current.ambient[0] = out.vx;
                    task->current.ambient[1] = out.vy;
                    task->current.ambient[2] = out.vz;
                } else {
                    task->t = 0x1000;
                    task->current = task->to;
                }
            }
            GsSetLightMode(0);
            for (j = 0; j < 3; j++) {
                GsSetFlatLight(j, &task->current.lights[j]);
            }
            SetBackColor(task->current.ambient[0], task->current.ambient[1], task->current.ambient[2]);
            layer = GFX_FUNCS.getLayer(task->layerId);
            layer->setKeepLightMatrix(layer, 1);
            if (task->t == 0x1000) {
                task->nextSubstate(task);
            }
            break;
        }
        break;
    case TASK_KILL:
        layer = GFX_FUNCS.getLayer(task->layerId);
            layer->setKeepLightMatrix(layer, 0);
        break;
    }
}

void func_8008A61C(Lights *task, LightSet *set) {
    task->current = *set;
    task->setState(task, TASK_DONE);
}

void func_8008A690(Lights *task, LightSet *from, LightSet *to, s32 time) {
    if (from != NULL) {
        task->from = *from;
    } else {
        task->from = task->current;
    }
    task->to = *to;
    task->tStep = 0x1000 / time;
    task->t = task->tStep * GFX_FUNCS.getFrameTime();
    task->setState(task, TASK_DONE);
}

LightSet *func_8008A7EC(Lights *task, s32 stage) {
    return &((FightStageInfo *)FILE_CACHE.load(FILE_FIGHT_STAGES))[stage].lights;
}

void func_8008A838(s32 layerId) {
    Lights *task = createTaskWithId(func_8008A270, sizeof(Lights), 0, 0x13);
    task->set = func_8008A61C;
    task->fade = func_8008A690;
    task->layerId = layerId;
    task->getStageLights = func_8008A7EC;
}

s32 FIGHTSTG_getEyesFrame(Face *task) {
    switch (task->model->motion) {
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        return 2;
    case 2:
        return 1;
    default:
        return 0;
    }
}

void FIGHTSTG_moveFacePart(Face *task, DR_MOVE *prim, s32 part, s32 frame) {
    RECT rect;
    Vec2 pos;

    rect.x = task->parts[part].rect.frames[frame][0] + task->texPos.x;
    rect.y = task->parts[part].rect.frames[frame][1] + task->texPos.y;
    rect.w = task->parts[part].rect.w;
    rect.h = task->parts[part].rect.h;
    pos.x = task->parts[part].rect.x + task->texPos.x;
    pos.y = task->parts[part].rect.y + task->texPos.y;
    SetDrawMove(prim, &rect, pos.x, pos.y);
}

void FIGHTSTG_updateFace(Face *task) {
    Layer *layer;
    u_long *ot;
    DR_MOVE *prim;
    s32 eyes;
    s32 frame;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        if (task->partCount == 0) {
            task->setState(task, TASK_KILL);
        } else {
            task->nextState(task);
        }
        break;
    case TASK_RUN:
        eyes = FIGHTSTG_getEyesFrame(task);
        if (eyes == 0) {
            switch (task->blinkTimer >> 1) {
            case 0:
                task->blinkTimer = (RANDOM.next() & 0x7F) + 60;
            default:
                eyes = 0;
                break;
            case 1:
            case 2:
            case 5:
            case 6:
                eyes = 1;
                break;
            case 3:
            case 4:
                eyes = 2;
                break;
            }
            task->blinkTimer -= D_800A31E8.frames;
            if (task->blinkTimer < 0) {
                task->blinkTimer = 0;
            }
        } else {
            task->blinkTimer = 0;
        }
        task->time += D_800A31E8.frames;
        frame = task->time % 18 / 6;
        layer = GFX.funcs.getLayer(0x1000);
        ot = (u_long *)layer->getOtEntry(layer, 0);
        prim = GFX.funcs.getPrim();
        for (i = 0; i < 2; i++) {
            if (task->parts[i].used && task->parts[i].frame != eyes) {
                task->parts[i].frame = eyes;
                FIGHTSTG_moveFacePart(task, prim, i, eyes);
                addPrim(ot, prim);
                prim++;
            }
        }
        for (i = 2; i < 16; i++) {
            if (task->parts[i].used && task->parts[i].frame != frame) {
                task->parts[i].frame = frame;
                FIGHTSTG_moveFacePart(task, prim, i, frame);
                addPrim(ot, prim);
                prim++;
            }
        }
        GFX_FUNCS.setPrim(prim);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Face *FIGHTSTG_createFace(Model *model, s32 fighter) {
    Face *task;
    FaceRect *rects;
    s32 i;

    if (fighter == 0) {
        return NULL;
    }
    task = createTask(FIGHTSTG_updateFace, sizeof(Face), 0);
    task->model = model;
    task->texPos = model->texPos;
    rects = D_800A32E0.getFace(fighter);
    for (i = 15; i >= 0; i--) {
        task->parts[i].used = 0;
    }
    for (i = 0; i < 16; i++) {
        if (rects[i].x == 0xFF) {
            return task;
        }
        if (rects[i].w != 0) {
            task->parts[i].rect = rects[i];
            task->parts[i].used = 1;
            task->partCount++;
        }
    }
    return task;
}
