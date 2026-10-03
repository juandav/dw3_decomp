/* The second object of FIGHTSTG.PRO (see fightstg.c), the fight stage: its
   rodata starts at 0x80082464 (USA), 4 bytes past a multiple of 8. */

#include "fightstg.h"

void func_80085974(FightStage *task, Model **children) {
    u8 color[3];
    Model *model;
    Layer *layer;

    D_800A3420.lerp(&task->colorFrom, &task->colorTo, task->fade, &task->color);
    color[0] = task->color.vx;
    color[1] = task->color.vy;
    color[2] = task->color.vz;
    model = children[0];
    model->setColor(model, 1, color);
    D_800A3420.lerp(&task->bgFrom, &task->bgTo, task->fade, &task->bg);
    layer = GFX_FUNCS.getLayer(0x1000);
    if (task->bg.vx != 0 || task->bg.vy != 0 || task->bg.vz != 0) {
        layer->setBgColor(layer, (u8)task->bg.vx, (u8)task->bg.vy, (u8)task->bg.vz);
    } else {
        layer->setBgColor(layer, 1, 1, 1);
    }
}

const Vec2 D_80082464 = { 0x280, 0 };

void func_80085A84(FightStage *task, Model **children) {
    FightStageInfo *stages = (FightStageInfo *)FILE_CACHE.load(FILE_FIGHT_STAGES);
    Lights *lights;
    Model *model;
    Layer *layer;
    u8 color[3];
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        /* fallthrough */
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            task->control.unk34[0].enabled = 1;
            task->control.unk34[0].arg = 0x1002;
            task->control.fighter = 0;
            task->control.unk34[0].alt = 0;
            children[0] = func_80083F44(stages[task->stage].model, stages[task->stage].motions, D_80082464, &task->control);
            if (stages[task->stage].music != -1) {
                task->voice = SOUND.playSound(D_800A1238[stages[task->stage].music]);
            }
            lights = TASK_FUNCS.find(0x13, -1, -1);
            if (lights != NULL) {
                lights->fade(lights, NULL, lights->getStageLights(lights, task->stage), task->fadeInTime);
            }
            task->nextSubstate(task);
            /* fallthrough */
        case 1:
            if (children[0]->state == TASK_RUN) {
                for (i = 0; i < 8; i++) {
                    if (stages[task->stage].unk10[i] == 0) {
                        break;
                    }
                    model = children[0];
                    model->unk2630(model, stages[task->stage].unk10[i], 1);
                }
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
                model = children[0];
                model->setColor(model, 1, color);
                layer = GFX_FUNCS.getLayer(0x1000);
                layer->setBgColor(layer, 1, 1, 1);
                task->nextSubstate(task);
            }
            break;
        case 2:
            task->colorTo.vz = 0x80;
            task->colorTo.vy = 0x80;
            task->colorTo.vx = 0x80;
            task->colorFrom.vz = 0;
            task->colorFrom.vy = 0;
            task->colorFrom.vx = 0;
            task->bgTo.vx = stages[task->stage].bgColor[0];
            task->bgTo.vy = stages[task->stage].bgColor[1];
            task->bgTo.vz = stages[task->stage].bgColor[2];
            task->bgFrom.vz = 0;
            task->bgFrom.vy = 0;
            task->bgFrom.vx = 0;
            task->fade = 0;
            task->fadeStep = 0x1000 / task->fadeInTime;
            task->nextSubstate(task);
            /* fallthrough */
        case 3:
            task->fade += task->fadeStep * GFX_FUNCS.getFrameTime();
            if (task->fade > 0x1000) {
                task->fade = 0x1000;
            }
            func_80085974(task, children);
            if (task->fade == 0x1000) {
                task->nextSubstate(task);
            }
            break;
        case 4:
            break;
        }
        break;
    case TASK_DONE:
        switch (task->substate) {
        case 0:
        default:
            FILE_CACHE.request((s16)(stages[task->stage].model >> 16));
            task->colorFrom.vz = 0x80;
            task->colorFrom.vy = 0x80;
            task->colorFrom.vx = 0x80;
            task->colorTo.vz = 0;
            task->colorTo.vy = 0;
            task->colorTo.vx = 0;
            task->bgTo.vz = 0;
            task->bgTo.vy = 0;
            task->bgTo.vx = 0;
            task->bgFrom.vx = stages[task->prevStage].bgColor[0];
            task->bgFrom.vy = stages[task->prevStage].bgColor[1];
            task->bgFrom.vz = stages[task->prevStage].bgColor[2];
            task->fade = 0;
            task->fadeStep = 0x1000 / task->fadeOutTime;
            task->nextSubstate(task);
            /* fallthrough */
        case 1:
            task->fade += task->fadeStep * GFX_FUNCS.getFrameTime();
            if (task->fade > 0x1000) {
                task->fade = 0x1000;
            }
            func_80085974(task, children);
            if (task->fade == 0x1000) {
                children[0]->setState(children[0], TASK_KILL);
                task->setState(task, TASK_RUN);
                if (stages[task->prevStage].music != -1) {
                    SOUND.keyOff(D_800A1238[stages[task->prevStage].music], task->voice);
                }
            }
            break;
        }
        break;
    case TASK_KILL:
        break;
    }
}

void func_80086040(FightStage *task, s32 id, s32 fadeOutTime, s32 fadeInTime) {
    if (task->stage != id) {
        task->prevStage = task->stage;
        task->stage = id;
        task->fadeOutTime = fadeOutTime;
        task->fadeInTime = fadeInTime;
        task->setState(task, TASK_DONE);
    }
}

s32 func_80086084(void) {
    return RANDOM.next() % 27 + 1;
}

s16 func_800860DC(s32 id) {
    return (s16)(((FightStageInfo *)FILE_CACHE_LOAD[0](FILE_FIGHT_STAGES))[id].motions >> 16);
}

FightStage *func_80086128(s32 id, s32 fadeInTime) {
    FightStage *task = createTaskWithId(func_80085A84, sizeof(FightStage), 4, 0x15);

    task->setStage = func_80086040;
    task->stage = id;
    task->fadeInTime = fadeInTime;
    return task;
}
