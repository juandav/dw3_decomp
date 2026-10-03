/* The camera's turn around the fighters, a task that both versions have:
   the USA version in fightstg_7.c, the European one in fightstg_5.c. Each
   includes this file where its object has the task. */

BattleScript *func_8008C090(void);

/* Turns the camera around the fighters, from the first fighter's view 0xB,
   over stage 0x17, with the battle script's task as the child; the European
   version moves on to state 2 after 240 frames, where the camera
   keeps turning */
void func_800A1048(Unk800A1048 *task, BattleScript **children) {
    BattleCamera *camera = task->camera;
    FightStage *stage;
    Models *models;
    s32 z;

    switch (task->state) {
    case 0:
    default:
        camera = TASK_REGISTRY.funcs.find(0x12, -1, -1);
        task->camera = camera;
        camera->getFighterView(camera, 0, 0xB);
        z = D_800A3438.vrz;
        D_800A3438.vrz = 0;
        D_800A3438.vpz -= z;
        D_800A3438.tz = z;
        stage = TASK_REGISTRY.funcs.find(0x15, -1, -1);
        stage->setStage(stage, 0x17, 0x1E, 0x1E);
        models = TASK_REGISTRY.funcs.find(0x14, -1, -1);
        models->get(models, 0x10)->unk34[0].enabled = 0;
        D_800A31E8.unkE8(2);
        *children = func_8008C090();
        (*children)->index = 3;
        (*children)->unk50 = 0;
        task->nextState(task);
    case 1:
#if VERSION_EU
        task->substate += GFX_FUNCS.getFrameTime();
        if (task->substate >= 240) {
            task->setState(task, 2);
        }
    case 2:
#endif
        D_800A3438.rot.vy += GFX_FUNCS.getFrameTime() * 2;
        camera->set(camera, &D_800A3438);
        break;
    case 3:
        D_800A31E8.unkE8(0);
        break;
#if VERSION_US
    case 2:
        break;
#endif
    }
}

void func_800A120C(void) {
    createTask(func_800A1048, 0x54, sizeof(Task *));
}
