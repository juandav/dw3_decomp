/* The last object of FIGHTSTG.PRO (see fightstg.c). The USA version has the
   task of func_800A1048 here, which the European one has in fightstg_5.c;
   the European version has a task of its own here instead, whose jump table
   starts its rodata at 0x800832B8. */

#include "fightstg.h"

#if VERSION_US
#include "camera_turn.h"
#elif VERSION_EU
/* A camera of the European version's own: one of the three lists of shots of
   D_800A46A8, picked at random, from the views of the fighters and the enemy,
   fades to them and a turn, then the enemy's view. The match depends on the
   turn's time * 32, which written as a shift reads only the time's low half */
void func_800A1FE0(Unk800A1FE0 *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->list = RANDOM.next() & 3;
        if (task->list == 3) {
            task->list = 0;
        }
        task->shot = 0;
        task->time = D_800A46A8[task->list][task->shot].time;
        task->setSubstate(task, D_800A46A8[task->list][task->shot].substate);
        task->camera = TASK_REGISTRY.funcs.find(0x12, -1, -1);
        task->models = TASK_REGISTRY.funcs.find(0x14, -1, -1);
        task->view = task->camera->getEnemyView(task->camera);
    case 1:
        if (task->time <= 0) {
            if (D_800A46A8[task->list][++task->shot].time == -1) {
                task->setState(task, 3);
                break;
            }
            task->time = D_800A46A8[task->list][task->shot].time;
            task->setSubstate(task, D_800A46A8[task->list][task->shot].substate);
        }
        switch (task->substate) {
        case 1:
            task->view = task->camera->getFighterView(task->camera, 0x10, 0);
            task->camera->set(task->camera, task->view);
            task->substate = 0;
            break;
        case 2:
            task->view = task->camera->getFighterView(task->camera, 0, 8);
            task->camera->set(task->camera, task->view);
            task->substate = 0;
            break;
        case 3:
            task->view = task->camera->getEnemyView(task->camera);
            task->camera->set(task->camera, task->view);
            task->substate = 0;
            break;
        case 4:
            task->to = *task->camera->getEnemyView(task->camera);
            task->camera->fade(task->camera, NULL, &task->to, task->time);
            task->substate = 0;
            break;
        case 5:
            task->to = *task->camera->getFighterView(task->camera, 0, 10);
            task->camera->fade(task->camera, NULL, &task->to, task->time);
            task->substate = 0;
            break;
        case 6:
            if (task->step == 0) {
                task->view = task->camera->getEnemyView(task->camera);
                task->rx = task->view->rot.vx;
                task->ry = task->view->rot.vy;
                task->view->rot.vx = task->rx - 0x155;
                task->view->rot.vy = task->ry + 0x800;
                task->step++;
            }
            task->view->rot.vx = task->rx - task->time * 0x155 / 64;
            task->view->rot.vy = task->ry + task->time * 32;
            task->camera->set(task->camera, task->view);
            break;
        }
        task->time -= GFX_FUNCS.getFrameTime();
        break;
    case 3:
        task->view = task->camera->getEnemyView(task->camera);
        task->camera->set(task->camera, task->view);
        break;
    case 2:
        break;
    }
}

void func_800A246C(void) {
    createTask(func_800A1FE0, 0xA4, 0);
}
#endif
