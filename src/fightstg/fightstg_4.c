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

INCLUDE_ASM("fightstg/nonmatchings/fightstg_4", func_8008A898);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_4", func_8008A8E0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_4", func_8008A980);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_4", func_8008AC88);
