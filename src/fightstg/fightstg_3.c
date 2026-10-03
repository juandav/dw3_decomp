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

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800867F0);

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

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80087B14);

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_800824C8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80087CE4);

void func_80088380(void) {
    createTask(func_80087CE4, 0x80, 2 * sizeof(Task *));
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800883AC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800888C8);

void func_80088994(void) {
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_8008899C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80088B5C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80088DEC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80088E8C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80088F78);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80088FC4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800890F8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_800891A4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80089364);

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_80082560);

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_80082568);

INCLUDE_RODATA("fightstg/nonmatchings/fightstg_3", D_80082570);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80089458);

void func_80089F74(s32 key1, s32 key2) {
    Task *task = createTask(func_80089458, 0x74, 6 * sizeof(Task *));

    task->key1 = key1;
    task->key2 = key2;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_80089FBC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_8008A044);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_3", func_8008A188);

void func_8008A22C(void) {
    Unk80089FBC *task = createTask(func_8008A188, sizeof(Unk80089FBC), 0);

    task->unk64 = func_80089FBC;
    task->unk50 = 0x1006;
    task->unk54 = 0;
}
