#include "wfightts.h"

extern RECT WFIGHTTS_screen;
extern s32 WFIGHTTS_stageCursor;
extern s32 WFIGHTTS_stageScroll;
extern char *WFIGHTTS_stageNames[];
extern s16 D_800A8224[][2];
extern s32 D_800A8240[];
extern s32 D_800A8250[];
extern s32 D_800A8260;
extern s32 D_800A8278;
extern s32 D_800A827C[];
extern char *D_800A8284[];
extern char *D_800A82B4[];
extern s32 D_800A84EC[];
extern s32 D_800A852C[];
extern s32 D_800A8560;
extern s32 D_800A8564;
extern BattleTestCursors WFIGHTTS_motionCursors;
extern BattleTestCursors WFIGHTTS_effectCursors;
extern char *D_800A83A4[];
extern char *D_800A849C[];

/* FIGHTSTG's */
Task *func_80092124(void);
Unk800911C8 *func_800919EC(s32 layer);
FightStage *func_80086128(s32 id, s32 fadeInTime);
Models *func_800877D4(void);
Task *func_8008A838(s32 layer);
void func_80092154(s32 arg0);
void *func_80086780(s32 digimon, s32 arg1, s32 arg2);
void *func_80089F74(s32 digimon, s32 arg1);
void *func_800A120C(void);
BattleTestMove *func_8008C090(void);
void *func_80087ACC(s32 arg0, s32 arg1);

void func_800A5A54(BattleTest *task, BattleTestChildren *children);
BattleTestList *func_800A6E80(s32 *side, s32 *pick);
BattleTestList *func_800A72EC(s32 *side, s32 *pick);
BattleTestStageList *WFIGHTTS_createStageList(s32 *result);
BattleTestMotions *func_800A7B9C(s32 *side, s32 *motion);
BattleTestEffects *func_800A81D0(s32 *side, s32 *effect);
void func_800A6954();
void func_800A6ECC();
void WFIGHTTS_stageList();
void func_800A764C();
void func_800A7BE8();

/* Sets up the display and the battle test's layers */
void WFIGHTTS_initLayers(void) {
    Layer *layer;

    GFX.funcs.reset();
    GFX.funcs.allocPrimBuffers(0x19000);
    GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 1, 0x1000);
    layer->setOffset(layer, 0xA0, 0x78);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 1, 0x1001);
    layer->setOffset(layer, 0xA0, 0x78);
    layer->allocCallbacks(layer, 100);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 8, 0x1002);
    layer->setOffset(layer, WFIGHTTS_screen.w / 2, WFIGHTTS_screen.h / 2);
    layer->allocCallbacks(layer, 40);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 1, 0x1003);
    layer->setOffset(layer, 0xA0, 0x78);
    layer->allocCallbacks(layer, 100);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 12, 0x1004);
    layer->setOffset(layer, 0xA0, 0x78);
    layer->allocCallbacks(layer, 100);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 1, 0x1005);
    layer->setOffset(layer, 0, 0);
    layer = GFX.funcs.createLayer(&WFIGHTTS_screen, 1, 0x1006);
    layer->setOffset(layer, 0, 0);
    layer->allocCallbacks(layer, 5);
}

/* Loads the battle test's images into VRAM */
void WFIGHTTS_loadImages(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x200, 0);
    loader.loadArchive(FILE_CACHE.getEntry(FILE_BATTLE_IMAGES << 16 | 1));
    loader.setImagePos(0, 0xF4);
    loader.load(FILE_CACHE.getEntry(FILE_BATTLE_IMAGES << 16));
    loader.setImagePos(0x140, 0x100);
    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_1));
    loader.setImagePos(0x1C0, 0x100);
    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_2));
    loader.setImagePos(0x200, 0x100);
    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_3));
    loader.setImagePos(0x240, 0x100);
    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_4));
}

/* The battle test: sets up the battle, then runs its pages. Page 0 plays
   things on CROSS (back to the last list), R1, R2 and L2; the lists pick the
   fighters, the camera, the stage, a motion and an effect. SELECT cycles
   D_800A8260 and R2 with the pad moves the display */
void func_800A5A54(BattleTest *task, BattleTestChildren *children) {
    Unk80091618 unused; /* unused, but it is in the original stack frame */
    s32 list = 0;
    s32 pressed;
    s32 arg;
    FighterInfo *partner;
    EnemyFighterInfo *enemy;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            FILE_CACHE.freeAll();
            WFIGHTTS_initLayers();
            task->nextSubstate(task);
        case 1:
            switch (task->step) {
            case 0:
            default:
                SOUND.loadBank(2);
                task->nextStep(task);
            case 1:
                if (SOUND_STATE.isLoading() == 0) {
                    SOUND_STATE.playSound(0x60080000);
                    D_80042728.unk14 = 0x60080000;
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 2:
            WFIGHTTS_loadImages();
            task->nextSubstate(task);
        case 3:
            switch (task->step) {
            case 0:
            default:
                children->commands = func_80092124();
                children->unk8 = func_800919EC(0x1001);
                children->stage = func_80086128(D_80042728.unkC, 60);
                children->models = func_800877D4();
                children->lights = func_8008A838(0x1001);
                task->nextStep(task);
                break;
            case 1:
                arg = GAME_FUNCS.getModeArg();
                children->models->add(children->models, 0, D_800A8224[arg][0], 1);
                children->models->face(children->models, 0);
                children->models->add(children->models, 0x10, D_800A8224[arg][1], 1);
                children->models->face(children->models, 0x10);
                children->unk8->unkF8(children->unk8, children->unk8->unk100(children->unk8));
                func_80092154(0);
                task->page = 1;
                task->nextState(task);
                break;
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
                func_80092154(0);
                task->nextStep(task);
            case 1:
                pressed = PAD.getPressed(0);
                if (pressed & 0x2000) {
                    func_80092154(0);
                    task->setSubstate(task, task->page);
                }
                if ((pressed & 0x800) && children->task == NULL) {
                    children->task = func_80086780(0x94, 0, 0);
                }
                if ((pressed & 0x200) && children->task == NULL) {
                    children->task = func_80089F74(0x3B, 0);
                }
                if ((pressed & 0x100) && children->task == NULL) {
                    children->task = func_800A120C();
                }
                break;
            }
            break;
        case 1:
            list = 1;
            switch (task->step) {
            case 0:
            default:
                task->page = 1;
                children->fighters = func_800A6E80(&task->side, &task->fighter);
                task->nextStep(task);
                break;
            case 1:
                if (PAD.getPressed(0) & 0x400) {
                    task->setSubstate(task, 2);
                    children->fighters->setState(children->fighters, 3);
                } else if (PAD.getPressed(0) & 0x800) {
                    task->setSubstate(task, 5);
                    children->fighters->setState(children->fighters, 3);
                } else if (children->fighters == NULL) {
                    if (task->side != -1) {
                        if (task->side == 0) {
                            children->models->add(children->models, 0, task->fighter, 1);
                            children->models->face(children->models, 0);
                        } else {
                            children->models->add(children->models, 0x10, task->fighter, 1);
                            children->models->face(children->models, 0x10);
                        }
                        children->unk8->unkF8(children->unk8, children->unk8->unk100(children->unk8));
                    }
                    task->setSubstate(task, 0);
                }
                break;
            }
            break;
        case 2:
            list = 1;
            switch (task->step) {
            case 0:
            default:
                task->page = 2;
                children->cameras = func_800A72EC(&task->side, &task->camera);
                task->nextStep(task);
                break;
            case 1:
                if (PAD.getPressed(0) & 0x400) {
                    children->cameras->setState(children->cameras, 3);
                    task->setSubstate(task, 3);
                } else if (PAD.getPressed(0) & 0x800) {
                    children->cameras->setState(children->cameras, 3);
                    task->setSubstate(task, 1);
                } else if (children->cameras == NULL) {
                    if (task->side != -1) {
                        if (task->side == 0) {
                            partner = D_800A32E0.funcs.getInfo(children->models->getFighter(children->models, 0));
                            D_800A84EC[0] = partner->camPos[task->camera].x;
                            D_800A84EC[1] = -partner->camPos[task->camera].y;
                            D_800A84EC[2] = -partner->camPos[task->camera].z;
                            D_800A84EC[3] = partner->camRef[task->camera].x;
                            D_800A84EC[4] = -partner->camRef[task->camera].y;
                            D_800A84EC[5] = -partner->camRef[task->camera].z;
                            D_800A84EC[11] = 0;
                            D_800A84EC[12] = partner->camProj[task->camera];
                            children->unk8->unkFC(children->unk8, 0, D_800A84EC, 60);
                        } else {
                            enemy = (EnemyFighterInfo *)D_800A32E0.funcs.getInfo(children->models->getFighter(children->models, 0x10));
                            D_800A852C[0] = enemy->camPos[task->camera].x;
                            D_800A852C[1] = -enemy->camPos[task->camera].y;
                            D_800A852C[2] = -enemy->camPos[task->camera].z;
                            D_800A852C[3] = enemy->camRef[task->camera].x;
                            D_800A852C[4] = -enemy->camRef[task->camera].y;
                            D_800A852C[5] = -enemy->camRef[task->camera].z;
                            D_800A852C[11] = 0;
                            D_800A852C[12] = enemy->camProj[task->camera];
                            children->unk8->unkFC(children->unk8, 0, D_800A852C, 60);
                        }
                    }
                    task->setSubstate(task, 0);
                }
                break;
            }
            break;
        case 3:
            list = 1;
            switch (task->step) {
            case 0:
            default:
                task->page = 3;
                children->stages = WFIGHTTS_createStageList(&task->stage);
                task->nextStep(task);
                break;
            case 1:
                if (PAD.getPressed(0) & 0x400) {
                    children->stages->setState(children->stages, 3);
                    task->setSubstate(task, 4);
                } else if (PAD.getPressed(0) & 0x800) {
                    children->stages->setState(children->stages, 3);
                    task->setSubstate(task, 2);
                } else if (children->stages == NULL) {
                    if (task->stage != -1) {
                        D_80042728.unkC = task->stage;
                        children->stage->setStage(children->stage, task->stage, 60, 60);
                    }
                    task->setSubstate(task, 0);
                }
                break;
            }
            break;
        case 4:
            list = 1;
            switch (task->step) {
            case 0:
            default:
                task->page = 4;
                children->motions = func_800A7B9C(&task->side, &task->motion);
                task->nextStep(task);
                break;
            case 1:
                if (PAD.getPressed(0) & 0x400) {
                    children->motions->setState(children->motions, 3);
                    task->setSubstate(task, 5);
                } else if (PAD.getPressed(0) & 0x800) {
                    children->motions->setState(children->motions, 3);
                    task->setSubstate(task, 3);
                } else if (children->motions == NULL) {
                    /* match depends on the call in each branch */
                    if (task->side == -1) {
                        task->setSubstate(task, 0);
                    } else {
                        children->models->get(children->models, (task->side != 0) * 0x10)->motion = task->motion;
                        task->setSubstate(task, 0);
                    }
                }
                break;
            }
            break;
        case 5:
            list = 1;
            switch (task->step) {
            case 0:
            default:
                task->page = 5;
                children->effects = func_800A81D0(&task->side, &task->effect);
                task->nextStep(task);
                break;
            case 1:
                if (PAD.getPressed(0) & 0x400) {
                    children->effects->setState(children->effects, 3);
                    task->setSubstate(task, 1);
                } else if (PAD.getPressed(0) & 0x800) {
                    children->effects->setState(children->effects, 3);
                    task->setSubstate(task, 4);
                } else if (children->effects == NULL) {
                    if (task->side == -1) {
                        task->setSubstate(task, 0);
                    } else {
                        if (task->effect != 0x12) {
                            children->task = func_8008C090();
                            children->task->kind = task->effect;
                            children->task->actor = task->side;
                            children->task->hits[0] = 3;
                            children->task->hits[1] = 3;
                            children->task->hits[2] = 3;
                            children->task->hits[3] = 2;
                            children->task->unk68 = -1;
                            children->task->unk70 = 0x39;
                        } else {
                            children->task = func_80087ACC(1, 0);
                        }
                        task->nextStep(task);
                    }
                }
                break;
            case 2:
                list = 0;
                if (children->task == NULL) {
                    task->setSubstate(task, 0);
                }
                break;
            }
            break;
        }
        if (list) {
            D_800A31E8.unkF4(0x1005, 1, D_800A8240, D_800A8250);
        }
        if (PAD.getPressed(0) & 1) {
            if (++D_800A8260 == 4) {
                D_800A8260 = 0;
            }
            D_800A31E8.unkE8(D_800A8260);
        }
        if ((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R2)) & 1) {
            if ((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1) {
                D_800A8560 -= 10;
            } else if ((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1) {
                D_800A8560 += 10;
            } else if ((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) {
                D_800A8564 -= 10;
            } else if ((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) {
                D_800A8564 += 10;
            } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_START)) & 1) {
                D_800A8564 = 0;
                D_800A8560 = 0;
            }
            GFX_FUNCS.setDisplayArea(D_800A8560, D_800A8564, 0x140, 0xF0);
        } else {
            GFX_FUNCS.setDisplayMode(0x140, 0xF0, 0, 0);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task *WFIGHTTS_start(void) {
    return createTaskWithId(func_800A5A54, 0, 0, 0);
}

INCLUDE_ASM("wfightts/nonmatchings/wfightts", func_800A6954);

BattleTestList *func_800A6E80(s32 *side, s32 *pick) {
    BattleTestList *task = createTask(func_800A6954, sizeof(BattleTestList), 0x70);

    task->side = side;
    task->pick = pick;
    *pick = 0;
    return task;
}

/* The camera list: the partner's 12 cameras on the right and the enemy's 3
   on the left (RIGHT and LEFT pick the list, UP and DOWN the camera, ten at
   a time with R1 held); CROSS sets the side to 0 or 1 and the camera,
   TRIANGLE the side to -1. Match depends on the loop around the pad
   handling, whose breaks leave it early */
void func_800A6ECC(BattleTestList *task, TextWindow **windows) {
    s32 pressed;
    s32 steps;
    s32 i;
    s32 j;
    s32 k;

    switch (task->state) {
    case 0:
    default:
        for (i = 0; i < 12; i++) {
            windows[i] = createTextWindow(0x1005, 1, 0xB4, 0x28 + i * 12);
        }
        for (i = 0; i < 3; i++) {
            windows[12 + i] = createTextWindow(0x1005, 1, 0x14, 0x28 + i * 12);
        }
        task->nextState(task);
        break;
    case 1:
        pressed = PAD.getPressed(0) | PAD.getRepeated(0);
        if (PAD.getHeld(0) & 0x800) {
            steps = 10;
        } else {
            steps = 1;
        }
        while (1) {
            if (pressed & 0x20) {
                D_800A8278 = 0;
                break;
            }
            if (pressed & 0x80) {
                D_800A8278 = 1;
                break;
            }
            if (pressed & 0x10) {
                for (k = 0; k < steps; k++) {
                    if (D_800A827C[D_800A8278] != 0) {
                        D_800A827C[D_800A8278]--;
                    }
                }
                break;
            }
            if (pressed & 0x40) {
                for (k = 0; k < steps; k++) {
                    if (D_800A827C[D_800A8278] != (D_800A8278 != 0 ? 2 : 11)) {
                        D_800A827C[D_800A8278]++;
                    }
                }
                break;
            }
            if (pressed & 0x2000) {
                *task->side = D_800A8278;
                *task->pick = D_800A827C[D_800A8278];
                task->setState(task, TASK_KILL);
            }
            if (pressed & 0x4000) {
                *task->side = -1;
                task->setState(task, TASK_KILL);
            }
            break;
        }
        for (j = 0; j < 12; j++) {
            if (D_800A8278 == 0 && D_800A827C[0] == j && (GFX.funcs.getTime() & 8)) {
                windows[j]->setVisible(windows[j], 0);
            } else {
                windows[j]->setVisible(windows[j], 1);
                windows[j]->setText(windows[j], D_800A8284[j]);
            }
        }
        for (j = 0; j < 3; j++) {
            if (D_800A8278 == 1 && D_800A827C[1] == j && (GFX.funcs.getTime() & 8)) {
                windows[12 + j]->setVisible(windows[12 + j], 0);
            } else {
                windows[12 + j]->setVisible(windows[12 + j], 1);
                windows[12 + j]->setText(windows[12 + j], D_800A82B4[j]);
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

BattleTestList *func_800A72EC(s32 *side, s32 *pick) {
    BattleTestList *task = createTask(func_800A6ECC, sizeof(BattleTestList), 0x3C);

    task->side = side;
    task->pick = pick;
    *pick = 0;
    return task;
}

/* The fight stage list: 14 of the 55 stages at a time (UP and DOWN, ten at a
   time with SQUARE held); it sets *result to the stage, 1-55, or to -1 */
void WFIGHTTS_stageList(BattleTestStageList *task, TextWindow **windows) {
    s32 pressed;
    s32 steps;
    s32 i;
    s32 j;
    s32 n;

    switch (task->state) {
    case 0:
    default:
        for (n = 0; n < 14; n++) {
            windows[n] = createTextWindow(0x1005, 1, 0xB4, 0x28 + n * 12);
        }
        task->nextState(task);
        break;
    case 1:
        pressed = PAD.getPressed(0) | PAD.getRepeated(0);
        if (PAD.getHeld(0) & 0x8000) {
            steps = 10;
        } else {
            steps = 1;
        }
        if (pressed & 0x10) {
            for (j = 0; j < steps; j++) {
                if (WFIGHTTS_stageCursor != 0) {
                    WFIGHTTS_stageCursor--;
                } else if (WFIGHTTS_stageScroll != 0) {
                    WFIGHTTS_stageScroll--;
                }
            }
        } else if (pressed & 0x40) {
            for (j = 0; j < steps; j++) {
                if (WFIGHTTS_stageCursor != 13) {
                    WFIGHTTS_stageCursor++;
                } else if (WFIGHTTS_stageScroll != 41) {
                    WFIGHTTS_stageScroll++;
                }
            }
        } else {
            if (pressed & 0x2000) {
                *task->result = WFIGHTTS_stageScroll + WFIGHTTS_stageCursor + 1;
                task->setState(task, TASK_KILL);
            }
            if (pressed & 0x4000) {
                *task->result = -1;
                task->setState(task, TASK_KILL);
            }
        }
        for (i = 0; i < 14; i++) {
            if (WFIGHTTS_stageCursor == i && (GFX.funcs.getTime() & 8)) {
                windows[i]->setVisible(windows[i], 0);
            } else {
                windows[i]->setVisible(windows[i], 1);
                windows[i]->setText(windows[i], WFIGHTTS_stageNames[i + WFIGHTTS_stageScroll]);
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

BattleTestStageList *WFIGHTTS_createStageList(s32 *result) {
    BattleTestStageList *task = createTask(WFIGHTTS_stageList, sizeof(BattleTestStageList), 0x38);

    task->result = result;
    return task;
}

/* The motion list: the partner's motions on the right and the enemy's on the
   left, fourteen shown at a time (RIGHT and LEFT pick the list, UP and DOWN
   the motion, ten at a time with SQUARE held); CROSS sets the side and the
   motion plus 1, TRIANGLE the side to -1. The cursors stay while the
   fighters do. Match depends on the loop around the pad handling, whose
   breaks leave it early */
void func_800A764C(BattleTestMotions *task, BattleTestWindows *windows) {
    Models *models;
    BattleTestMotionList *list;
    s32 *motions;
    s32 pressed;
    s32 steps;
    s32 fighter;
    s32 x; /* unused, but it is in the original stack frame */
    s32 n;
    s32 i;
    s32 side;
    s32 j;
    s32 k;
    s32 m;

    switch (task->state) {
    case 0:
    default:
        models = TASK_FUNCS.find(0x14, -1, -1);
        for (i = 0; i < 2; i++) {
            list = &task->lists[i];
            fighter = models->getFighter(models, i * 16);
            if (WFIGHTTS_motionCursors.fighter[i] != fighter) {
                WFIGHTTS_motionCursors.fighter[i] = fighter;
                WFIGHTTS_motionCursors.cursor[i] = 0;
                WFIGHTTS_motionCursors.scroll[i] = 0;
            }
            D_800A32E0.funcs.getInfo(fighter);
            motions = (s32 *)FILE_CACHE.getEntry(D_800A32E0.unk10->motions);
            list->count = 0;
            for (j = 0; j < 0x3E; j++) {
                if (motions[j] != 0) {
                    list->motions[list->count] = j;
                    list->count++;
                }
            }
            n = list->count;
            if (n >= 15) {
                n = 14;
            }
            list->shown = n;
            for (j = 0; j < list->shown; j++) {
                windows->windows[i][j] = createTextWindow(0x1005, 1, 0xB4 - i * 0xA0, 0x28 + j * 12);
            }
        }
        task->nextState(task);
        break;
    case 1:
        pressed = PAD.getPressed(0) | PAD.getRepeated(0);
        if (PAD.getHeld(0) & 0x8000) {
            steps = 10;
        } else {
            steps = 1;
        }
        while (1) {
            if (pressed & 0x20) {
                WFIGHTTS_motionCursors.side = 0;
                break;
            }
            if (pressed & 0x80) {
                WFIGHTTS_motionCursors.side = 1;
                break;
            }
            if (pressed & 0x10) {
                for (k = 0; k < steps; k++) {
                    if (WFIGHTTS_motionCursors.cursor[WFIGHTTS_motionCursors.side] != 0) {
                        WFIGHTTS_motionCursors.cursor[WFIGHTTS_motionCursors.side]--;
                    } else if (WFIGHTTS_motionCursors.scroll[WFIGHTTS_motionCursors.side] != 0) {
                        WFIGHTTS_motionCursors.scroll[WFIGHTTS_motionCursors.side]--;
                    }
                }
                break;
            }
            if (pressed & 0x40) {
                for (k = 0; k < steps; k++) {
                    if (WFIGHTTS_motionCursors.cursor[WFIGHTTS_motionCursors.side] != task->lists[WFIGHTTS_motionCursors.side].shown - 1) {
                        WFIGHTTS_motionCursors.cursor[WFIGHTTS_motionCursors.side]++;
                    } else if (WFIGHTTS_motionCursors.scroll[WFIGHTTS_motionCursors.side] != task->lists[WFIGHTTS_motionCursors.side].count - task->lists[WFIGHTTS_motionCursors.side].shown) {
                        WFIGHTTS_motionCursors.scroll[WFIGHTTS_motionCursors.side]++;
                    }
                }
                break;
            }
            if (pressed & 0x4000) {
                *task->side = -1;
                task->setState(task, TASK_KILL);
                break;
            }
            if (pressed & 0x2000) {
                *task->side = WFIGHTTS_motionCursors.side;
                *task->motion = task->lists[WFIGHTTS_motionCursors.side].motions[WFIGHTTS_motionCursors.scroll[WFIGHTTS_motionCursors.side] + WFIGHTTS_motionCursors.cursor[WFIGHTTS_motionCursors.side]] + 1;
                task->setState(task, TASK_KILL);
            }
            break;
        }
        for (side = 0; side < 2; side++) {
            for (m = 0; m < task->lists[side].shown; m++) {
                if (WFIGHTTS_motionCursors.side == side && WFIGHTTS_motionCursors.cursor[side] == m && (GFX.funcs.getTime() & 8)) {
                    windows->windows[side][m]->setVisible(windows->windows[side][m], 0);
                } else {
                    windows->windows[side][m]->setVisible(windows->windows[side][m], 1);
                    windows->windows[side][m]->setText(windows->windows[side][m], D_800A83A4[task->lists[side].motions[m + WFIGHTTS_motionCursors.scroll[side]]]);
                }
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

BattleTestMotions *func_800A7B9C(s32 *side, s32 *motion) {
    BattleTestMotions *task = createTaskWithId(func_800A764C, sizeof(BattleTestMotions), 0x70, 0xFFFF);

    task->side = side;
    task->motion = motion;
    return task;
}

/* The effect list, like the motion list (func_800A764C): CROSS sets the side
   and the effect, on any but a fighter's "none". Match depends on the loop
   around the pad handling, whose breaks leave it early */
void func_800A7BE8(BattleTestEffects *task, BattleTestWindows *windows) {
    Models *models;
    BattleTestEffectList *list;
    s32 *effects;
    s32 pressed;
    s32 steps;
    s32 fighter;
    s32 x; /* unused, but it is in the original stack frame */
    s32 n;
    s32 i;
    s32 side;
    s32 j;
    s32 k;
    s32 m;

    switch (task->state) {
    case 0:
    default:
        models = TASK_FUNCS.find(0x14, -1, -1);
        for (i = 0; i < 2; i++) {
            list = &task->lists[i];
            fighter = models->getFighter(models, i * 16);
            if (WFIGHTTS_effectCursors.fighter[i] != fighter) {
                WFIGHTTS_effectCursors.fighter[i] = fighter;
                WFIGHTTS_effectCursors.cursor[i] = 0;
                WFIGHTTS_effectCursors.scroll[i] = 0;
            }
            D_800A32E0.funcs.getInfo(fighter);
            if (D_800A32E0.unk10->unk8 != 0) {
                effects = (s32 *)FILE_CACHE_GET_ENTRY[0](D_800A32E0.unk10->unk8);
                if (effects[0] == 0) {
                    list->effects[0] = 0;
                    list->count = 1;
                    list->shown = 1;
                } else {
                    list->count = 0;
                    for (j = 0; j < 0x13; j++) {
                        if (effects[j] != 0) {
                            list->effects[list->count] = j + 1;
                            list->count++;
                        }
                    }
                }
                n = list->count;
                if (n >= 15) {
                    n = 14;
                }
                list->shown = n;
            } else {
                list->effects[0] = 0;
                list->count = 1;
                list->shown = 1;
            }
            for (j = 0; j < list->shown; j++) {
                windows->windows[i][j] = createTextWindow(0x1005, 1, 0xB4 - i * 0xA0, 0x28 + j * 12);
            }
        }
        task->nextState(task);
        break;
    case 1:
        pressed = PAD.getPressed(0) | PAD.getRepeated(0);
        if (PAD.getHeld(0) & 0x8000) {
            steps = 10;
        } else {
            steps = 1;
        }
        while (1) {
            if (pressed & 0x20) {
                WFIGHTTS_effectCursors.side = 0;
                break;
            }
            if (pressed & 0x80) {
                WFIGHTTS_effectCursors.side = 1;
                break;
            }
            if (pressed & 0x10) {
                for (k = 0; k < steps; k++) {
                    if (WFIGHTTS_effectCursors.cursor[WFIGHTTS_effectCursors.side] != 0) {
                        WFIGHTTS_effectCursors.cursor[WFIGHTTS_effectCursors.side]--;
                    } else if (WFIGHTTS_effectCursors.scroll[WFIGHTTS_effectCursors.side] != 0) {
                        WFIGHTTS_effectCursors.scroll[WFIGHTTS_effectCursors.side]--;
                    }
                }
                break;
            }
            if (pressed & 0x40) {
                for (k = 0; k < steps; k++) {
                    if (WFIGHTTS_effectCursors.cursor[WFIGHTTS_effectCursors.side] != task->lists[WFIGHTTS_effectCursors.side].shown - 1) {
                        WFIGHTTS_effectCursors.cursor[WFIGHTTS_effectCursors.side]++;
                    } else if (WFIGHTTS_effectCursors.scroll[WFIGHTTS_effectCursors.side] != task->lists[WFIGHTTS_effectCursors.side].count - task->lists[WFIGHTTS_effectCursors.side].shown) {
                        WFIGHTTS_effectCursors.scroll[WFIGHTTS_effectCursors.side]++;
                    }
                }
                break;
            }
            if (pressed & 0x4000) {
                *task->side = -1;
                task->setState(task, TASK_KILL);
                break;
            }
            if (pressed & 0x2000) {
                if (task->lists[WFIGHTTS_effectCursors.side].effects[WFIGHTTS_effectCursors.scroll[WFIGHTTS_effectCursors.side] + WFIGHTTS_effectCursors.cursor[WFIGHTTS_effectCursors.side]] != 0) {
                    *task->side = WFIGHTTS_effectCursors.side;
                    *task->effect = task->lists[WFIGHTTS_effectCursors.side].effects[WFIGHTTS_effectCursors.scroll[WFIGHTTS_effectCursors.side] + WFIGHTTS_effectCursors.cursor[WFIGHTTS_effectCursors.side]] - 1;
                    task->setState(task, TASK_KILL);
                }
            }
            break;
        }
        for (side = 0; side < 2; side++) {
            for (m = 0; m < task->lists[side].shown; m++) {
                if (WFIGHTTS_effectCursors.side == side && WFIGHTTS_effectCursors.cursor[side] == m && (GFX.funcs.getTime() & 8)) {
                    windows->windows[side][m]->setVisible(windows->windows[side][m], 0);
                } else {
                    windows->windows[side][m]->setVisible(windows->windows[side][m], 1);
                    windows->windows[side][m]->setText(windows->windows[side][m], D_800A849C[task->lists[side].effects[m + WFIGHTTS_effectCursors.scroll[side]]]);
                }
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

BattleTestEffects *func_800A81D0(s32 *side, s32 *effect) {
    BattleTestEffects *task = createTaskWithId(func_800A7BE8, sizeof(BattleTestEffects), 0x70, 0xFFFF);

    task->side = side;
    task->effect = effect;
    return task;
}

/* The strings of the tables below, as GCC emitted them: each table's last
   to first, and each padded to a word. The padding after a table's last
   string isn't zeros but what the assembler left there, which differs
   between the versions; the size leaves out the closing NUL */
const char WFIGHTTS_strings[0x9C0] =
    /* 0x000 デッド */
    "\x83\x66\x83\x62\x83\x68\0\0"
    /* 0x008 かいふく */
    "\x82\xA9\x82\xA2\x82\xD3\x82\xAD\0\0\0\0"
    /* 0x014 キメポーズ */
    "\x83\x4C\x83\x81\x83\x7C\x81\x5B\x83\x59\0\0"
    /* 0x020 ダメージ */
    "\x83\x5F\x83\x81\x81\x5B\x83\x57\0\0\0\0"
    /* 0x02C Ｓフェイスアップ */
    "\x82\x72\x83\x74\x83\x46\x83\x43\x83\x58\x83\x41\x83\x62\x83\x76\0\0\0\0"
    /* 0x040 フェイスアップ */
    "\x83\x74\x83\x46\x83\x43\x83\x58\x83\x41\x83\x62\x83\x76\0\0"
    /* 0x050 たたかう−６ */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\x81\x7C\x82\x55\0\0\0\0"
    /* 0x060 たたかう−５ */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\x81\x7C\x82\x54\0\0\0\0"
    /* 0x070 たたかう−４ */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\x81\x7C\x82\x53\0\0\0\0"
    /* 0x080 たたかう−３ */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\x81\x7C\x82\x52\0\0\0\0"
    /* 0x090 たたかう−２ */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\x81\x7C\x82\x51\0\0\0\0"
    /* 0x0A0 たたかう−１ */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\x81\x7C\x82\x50"
#if VERSION_US
    "\0\0\x62\xAC"
#elif VERSION_EU
    "\0\0\x62\x10"
#endif
    /* 0x0B0 ＭＥＦＴ００５５ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x54\x82\x54\0\0\0\0"
    /* 0x0C4 ＭＥＦＴ００５４ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x54\x82\x53\0\0\0\0"
    /* 0x0D8 ＭＥＦＴ００５３ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x54\x82\x52\0\0\0\0"
    /* 0x0EC ＭＥＦＴ００５２ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x54\x82\x51\0\0\0\0"
    /* 0x100 ＭＥＦＴ００５１ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x54\x82\x50\0\0\0\0"
    /* 0x114 ＭＥＦＴ００５０ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x54\x82\x4F\0\0\0\0"
    /* 0x128 ＭＥＦＴ００４９ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x58\0\0\0\0"
    /* 0x13C ＭＥＦＴ００４８ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x57\0\0\0\0"
    /* 0x150 ＭＥＦＴ００４７ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x56\0\0\0\0"
    /* 0x164 ＭＥＦＴ００４６ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x55\0\0\0\0"
    /* 0x178 ＭＥＦＴ００４５ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x54\0\0\0\0"
    /* 0x18C ＭＥＦＴ００４４ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x53\0\0\0\0"
    /* 0x1A0 ＭＥＦＴ００４３ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x52\0\0\0\0"
    /* 0x1B4 ＭＥＦＴ００４２ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x51\0\0\0\0"
    /* 0x1C8 ＭＥＦＴ００４１ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x50\0\0\0\0"
    /* 0x1DC ＭＥＦＴ００４０ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x53\x82\x4F\0\0\0\0"
    /* 0x1F0 ＭＥＦＴ００３９ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x58\0\0\0\0"
    /* 0x204 ＭＥＦＴ００３８ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x57\0\0\0\0"
    /* 0x218 ＭＥＦＴ００３７ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x56\0\0\0\0"
    /* 0x22C ＭＥＦＴ００３６ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x55\0\0\0\0"
    /* 0x240 ＭＥＦＴ００３５ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x54\0\0\0\0"
    /* 0x254 ＭＥＦＴ００３４ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x53\0\0\0\0"
    /* 0x268 ＭＥＦＴ００３３ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x52\0\0\0\0"
    /* 0x27C ＭＥＦＴ００３２ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x51\0\0\0\0"
    /* 0x290 ＭＥＦＴ００３１ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x50\0\0\0\0"
    /* 0x2A4 ＭＥＦＴ００３０ */
    "\x82\x6C\x82\x64\x82\x65\x82\x73\x82\x4F\x82\x4F\x82\x52\x82\x4F\0\0\0\0"
    /* 0x2B8 ＭＦＳＴＧ０２９ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x58\0\0\0\0"
    /* 0x2CC ＭＦＳＴＧ０２８ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x57\0\0\0\0"
    /* 0x2E0 ＭＦＳＴＧ０２７ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x56\0\0\0\0"
    /* 0x2F4 ＭＦＳＴＧ０２６ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x55\0\0\0\0"
    /* 0x308 ＭＦＳＴＧ０２５ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x54\0\0\0\0"
    /* 0x31C ＭＦＳＴＧ０２４ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x53\0\0\0\0"
    /* 0x330 ＭＦＳＴＧ０２３ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x52\0\0\0\0"
    /* 0x344 ＭＦＳＴＧ０２２ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x51\0\0\0\0"
    /* 0x358 ＭＦＳＴＧ０２１ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x50\0\0\0\0"
    /* 0x36C ＭＦＳＴＧ０２０ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x51\x82\x4F\0\0\0\0"
    /* 0x380 ＭＦＳＴＧ０１９ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x58\0\0\0\0"
    /* 0x394 ＭＦＳＴＧ０１８ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x57\0\0\0\0"
    /* 0x3A8 ＭＦＳＴＧ０１７ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x56\0\0\0\0"
    /* 0x3BC ＭＦＳＴＧ０１６ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x55\0\0\0\0"
    /* 0x3D0 ＭＦＳＴＧ０１５ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x54\0\0\0\0"
    /* 0x3E4 ＭＦＳＴＧ０１４ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x53\0\0\0\0"
    /* 0x3F8 ＭＦＳＴＧ０１３ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x52\0\0\0\0"
    /* 0x40C ＭＦＳＴＧ０１２ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x51\0\0\0\0"
    /* 0x420 ＭＦＳＴＧ０１１ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x50\0\0\0\0"
    /* 0x434 ＭＦＳＴＧ０１０ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x50\x82\x4F\0\0\0\0"
    /* 0x448 ＭＦＳＴＧ００９ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x58\0\0\0\0"
    /* 0x45C ＭＦＳＴＧ００８ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x57\0\0\0\0"
    /* 0x470 ＭＦＳＴＧ００７ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x56\0\0\0\0"
    /* 0x484 ＭＦＳＴＧ００６ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x55\0\0\0\0"
    /* 0x498 ＭＦＳＴＧ００５ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x54\0\0\0\0"
    /* 0x4AC ＭＦＳＴＧ００４ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x53\0\0\0\0"
    /* 0x4C0 ＭＦＳＴＧ００３ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x52\0\0\0\0"
    /* 0x4D4 ＭＦＳＴＧ００２ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x51\0\0\0\0"
    /* 0x4E8 ＭＦＳＴＧ００１ */
    "\x82\x6C\x82\x65\x82\x72\x82\x73\x82\x66\x82\x4F\x82\x4F\x82\x50"
#if VERSION_US
    "\0\xFF\0\0"
#elif VERSION_EU
    "\0\xF8\x40\0"
#endif
    /* 0x4FC ジョグレス−５ */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\x81\x7C\x82\x54\0\0"
    /* 0x50C ジョグレス−４ */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\x81\x7C\x82\x53\0\0"
    /* 0x51C ジョグレス−３ */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\x81\x7C\x82\x52\0\0"
    /* 0x52C ジョグレス−２ */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\x81\x7C\x82\x51\0\0"
    /* 0x53C ジョグレス−１ */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\x81\x7C\x82\x50\0\0"
    /* 0x54C ジョグレス−０ */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\x81\x7C\x82\x4F\0\0"
    /* 0x55C ヒッサツ−５ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\x81\x7C\x82\x54\0\0\0\0"
    /* 0x56C ヒッサツ−４ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\x81\x7C\x82\x53\0\0\0\0"
    /* 0x57C ヒッサツ−３ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\x81\x7C\x82\x52\0\0\0\0"
    /* 0x58C ヒッサツ−２ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\x81\x7C\x82\x51\0\0\0\0"
    /* 0x59C ヒッサツ−１ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\x81\x7C\x82\x50\0\0\0\0"
    /* 0x5AC ヒッサツ−０ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\x81\x7C\x82\x4F\0\0\0\0"
    /* 0x5BC ワ：マ：カ−５ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\x81\x7C\x82\x54\0\0"
    /* 0x5CC ワ：マ：カ−４ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\x81\x7C\x82\x53\0\0"
    /* 0x5DC ワ：マ：カ−３ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\x81\x7C\x82\x52\0\0"
    /* 0x5EC ワ：マ：カ−２ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\x81\x7C\x82\x51\0\0"
    /* 0x5FC ワ：マ：カ−１ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\x81\x7C\x82\x50\0\0"
    /* 0x60C ワ：マ：カ−０ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\x81\x7C\x82\x4F\0\0"
    /* 0x61C ワ：マ：ウ−５ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x7C\x82\x54\0\0"
    /* 0x62C ワ：マ：ウ−４ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x7C\x82\x53\0\0"
    /* 0x63C ワ：マ：ウ−３ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x7C\x82\x52\0\0"
    /* 0x64C ワ：マ：ウ−２ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x7C\x82\x51\0\0"
    /* 0x65C ワ：マ：ウ−１ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x7C\x82\x50\0\0"
    /* 0x66C ワ：マ：ウ−０ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x7C\x82\x4F\0\0"
    /* 0x67C ワ：ブ：３−５ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\x81\x7C\x82\x54\0\0"
    /* 0x68C ワ：ブ：３−４ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\x81\x7C\x82\x53\0\0"
    /* 0x69C ワ：ブ：３−３ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\x81\x7C\x82\x52\0\0"
    /* 0x6AC ワ：ブ：３−２ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\x81\x7C\x82\x51\0\0"
    /* 0x6BC ワ：ブ：３−１ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\x81\x7C\x82\x50\0\0"
    /* 0x6CC ワ：ブ：３−０ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\x81\x7C\x82\x4F\0\0"
    /* 0x6DC ワ：ブ：２−５ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\x81\x7C\x82\x54\0\0"
    /* 0x6EC ワ：ブ：２−４ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\x81\x7C\x82\x53\0\0"
    /* 0x6FC ワ：ブ：２−３ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\x81\x7C\x82\x52\0\0"
    /* 0x70C ワ：ブ：２−２ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\x81\x7C\x82\x51\0\0"
    /* 0x71C ワ：ブ：２−１ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\x81\x7C\x82\x50\0\0"
    /* 0x72C ワ：ブ：２−０ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\x81\x7C\x82\x4F\0\0"
    /* 0x73C ワ：ブ：１−５ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\x81\x7C\x82\x54\0\0"
    /* 0x74C ワ：ブ：１−４ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\x81\x7C\x82\x53\0\0"
    /* 0x75C ワ：ブ：１−３ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\x81\x7C\x82\x52\0\0"
    /* 0x76C ワ：ブ：１−２ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\x81\x7C\x82\x51\0\0"
    /* 0x77C ワ：ブ：１−１ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\x81\x7C\x82\x50\0\0"
    /* 0x78C ワ：ブ：１−０ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\x81\x7C\x82\x4F\0\0"
    /* 0x79C タタカウ−５ */
    "\x83\x5E\x83\x5E\x83\x4A\x83\x45\x81\x7C\x82\x54\0\0\0\0"
    /* 0x7AC タタカウ−４ */
    "\x83\x5E\x83\x5E\x83\x4A\x83\x45\x81\x7C\x82\x53\0\0\0\0"
    /* 0x7BC タタカウ−３ */
    "\x83\x5E\x83\x5E\x83\x4A\x83\x45\x81\x7C\x82\x52\0\0\0\0"
    /* 0x7CC タタカウ−２ */
    "\x83\x5E\x83\x5E\x83\x4A\x83\x45\x81\x7C\x82\x51\0\0\0\0"
    /* 0x7DC タタカウ−１ */
    "\x83\x5E\x83\x5E\x83\x4A\x83\x45\x81\x7C\x82\x50\0\0\0\0"
    /* 0x7EC タタカウ−０ */
    "\x83\x5E\x83\x5E\x83\x4A\x83\x45\x81\x7C\x82\x4F\0\0\0\0"
    /* 0x7FC いかり */
    "\x82\xA2\x82\xA9\x82\xE8\0\0"
    /* 0x804 キメポーズ */
    "\x83\x4C\x83\x81\x83\x7C\x81\x5B\x83\x59\0\0"
    /* 0x810 おきあがり */
    "\x82\xA8\x82\xAB\x82\xA0\x82\xAA\x82\xE8\0\0"
    /* 0x81C デッド */
    "\x83\x66\x83\x62\x83\x68\0\0"
    /* 0x824 Ｌダメージ−５ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\x81\x7C\x82\x54\0\0"
    /* 0x834 Ｌダメージ−４ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\x81\x7C\x82\x53\0\0"
    /* 0x844 Ｌダメージ−３ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\x81\x7C\x82\x52\0\0"
    /* 0x854 Ｌダメージ−２ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\x81\x7C\x82\x51\0\0"
    /* 0x864 Ｌダメージ−１ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\x81\x7C\x82\x50\0\0"
    /* 0x874 Ｌダメージ−０ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\x81\x7C\x82\x4F\0\0"
    /* 0x884 Ｓダメージ */
    "\x82\x72\x83\x5F\x83\x81\x81\x5B\x83\x57\0\0"
    /* 0x890 ガード */
    "\x83\x4B\x81\x5B\x83\x68\0\0"
    /* 0x898 ウェイト−１ */
    "\x83\x45\x83\x46\x83\x43\x83\x67\x81\x7C\x82\x50\0\0\0\0"
    /* 0x8A8 ウェイト−０ */
    "\x83\x45\x83\x46\x83\x43\x83\x67\x81\x7C\x82\x4F"
#if VERSION_US
    "\0\x02\xC3\x02"
#elif VERSION_EU
    "\0\xF8\x40\0"
#endif
    /* 0x8B8 ＰＲＯ：どく */
    "\x82\x6F\x82\x71\x82\x6E\x81\x46\x82\xC7\x82\xAD\0\0\0\0"
    /* 0x8C8 ステータス：ダア */
    "\x83\x58\x83\x65\x81\x5B\x83\x5E\x83\x58\x81\x46\x83\x5F\x83\x41\0\0\0\0"
    /* 0x8DC ステータス：ダ */
    "\x83\x58\x83\x65\x81\x5B\x83\x5E\x83\x58\x81\x46\x83\x5F\0\0"
    /* 0x8EC フィールド：コ */
    "\x83\x74\x83\x42\x81\x5B\x83\x8B\x83\x68\x81\x46\x83\x52\0\0"
    /* 0x8FC アイテム：ダ */
    "\x83\x41\x83\x43\x83\x65\x83\x80\x81\x46\x83\x5F\0\0\0\0"
    /* 0x90C ワ：マ：ウ：３ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\x81\x46\x82\x52\0\0"
    /* 0x91C ジョグレス */
    "\x83\x57\x83\x87\x83\x4F\x83\x8C\x83\x58\0\0"
    /* 0x928 ヒッサツ */
    "\x83\x71\x83\x62\x83\x54\x83\x63\0\0\0\0"
    /* 0x934 ワ：マ：カ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x4A\0\0"
    /* 0x940 ワ：マ：ウ */
    "\x83\x8F\x81\x46\x83\x7D\x81\x46\x83\x45\0\0"
    /* 0x94C ワ：ブ：３ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x52\0\0"
    /* 0x958 ワ：ブ：２ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x51\0\0"
    /* 0x964 ワ：ブ：１ */
    "\x83\x8F\x81\x46\x83\x75\x81\x46\x82\x50\0\0"
    /* 0x970 たたかう */
    "\x82\xBD\x82\xBD\x82\xA9\x82\xA4\0\0\0\0"
    /* 0x97C ガード */
    "\x83\x4B\x81\x5B\x83\x68\0\0"
    /* 0x984 デッド */
    "\x83\x66\x83\x62\x83\x68\0\0"
    /* 0x98C Ｌダメージ */
    "\x82\x6B\x83\x5F\x83\x81\x81\x5B\x83\x57\0\0"
    /* 0x998 Ｓダメージ */
    "\x82\x72\x83\x5F\x83\x81\x81\x5B\x83\x57\0\0"
    /* 0x9A4 ウェイト */
    "\x83\x45\x83\x46\x83\x43\x83\x67\0\0\0\0"
    /* 0x9B0 −ＮＯＮＥ− */
    "\x81\x7C\x82\x6D\x82\x6E\x82\x6D\x82\x64\x81\x7C"
#if VERSION_US
    "\0\0\0\0";
#elif VERSION_EU
    "\0\0\x84\x8E";
#endif
#define WFIGHTTS_STR(offset) ((char *)WFIGHTTS_strings + (offset))

/* The screen, for the layers */
RECT WFIGHTTS_screen = { 0, 0, 0x140, 0xF0 };
/* The partner and the enemy the battle test starts with, by the mode's
   argument */
s16 D_800A8224[][2] = {
    {0x017A, 0x01B9}, {0x016E, 0x0073}, {0x0103, 0x00CA}, {0x016E, 0x01B4},
    {0x0091, 0x00C5}, {0x001F, 0x0089}, {0x0097, 0x006C},
};
s32 D_800A8240[] = {
    0, 320, 0xF00000, 0xF00140,
};
s32 D_800A8250[] = {
    0x808080, 0x808080, 0x808080, 0x808080,
};
s32 D_800A8260 = 0;
s32 D_800A8264 = 0;
s32 D_800A8268 = 0;
s32 D_800A826C = 0;
s32 D_800A8270 = 0;
s32 D_800A8274 = 0;
s32 D_800A8278 = 0;
s32 D_800A827C[] = {
    0, 0,
};
char *D_800A8284[] = {
    WFIGHTTS_STR(0x0A0), WFIGHTTS_STR(0x090), WFIGHTTS_STR(0x080), WFIGHTTS_STR(0x070),
    WFIGHTTS_STR(0x060), WFIGHTTS_STR(0x050), WFIGHTTS_STR(0x040), WFIGHTTS_STR(0x02C),
    WFIGHTTS_STR(0x020), WFIGHTTS_STR(0x014), WFIGHTTS_STR(0x008), WFIGHTTS_STR(0x000),
};
char *D_800A82B4[] = {
    WFIGHTTS_STR(0x020), WFIGHTTS_STR(0x014), WFIGHTTS_STR(0x008),
};
s32 WFIGHTTS_stageCursor = 0;
s32 WFIGHTTS_stageScroll = 0;
char *WFIGHTTS_stageNames[] = {
    WFIGHTTS_STR(0x4E8), WFIGHTTS_STR(0x4D4), WFIGHTTS_STR(0x4C0), WFIGHTTS_STR(0x4AC),
    WFIGHTTS_STR(0x498), WFIGHTTS_STR(0x484), WFIGHTTS_STR(0x470), WFIGHTTS_STR(0x45C),
    WFIGHTTS_STR(0x448), WFIGHTTS_STR(0x434), WFIGHTTS_STR(0x420), WFIGHTTS_STR(0x40C),
    WFIGHTTS_STR(0x3F8), WFIGHTTS_STR(0x3E4), WFIGHTTS_STR(0x3D0), WFIGHTTS_STR(0x3BC),
    WFIGHTTS_STR(0x3A8), WFIGHTTS_STR(0x394), WFIGHTTS_STR(0x380), WFIGHTTS_STR(0x36C),
    WFIGHTTS_STR(0x358), WFIGHTTS_STR(0x344), WFIGHTTS_STR(0x330), WFIGHTTS_STR(0x31C),
    WFIGHTTS_STR(0x308), WFIGHTTS_STR(0x2F4), WFIGHTTS_STR(0x2E0), WFIGHTTS_STR(0x2CC),
    WFIGHTTS_STR(0x2B8), WFIGHTTS_STR(0x2A4), WFIGHTTS_STR(0x290), WFIGHTTS_STR(0x27C),
    WFIGHTTS_STR(0x268), WFIGHTTS_STR(0x254), WFIGHTTS_STR(0x240), WFIGHTTS_STR(0x22C),
    WFIGHTTS_STR(0x218), WFIGHTTS_STR(0x204), WFIGHTTS_STR(0x1F0), WFIGHTTS_STR(0x1DC),
    WFIGHTTS_STR(0x1C8), WFIGHTTS_STR(0x1B4), WFIGHTTS_STR(0x1A0), WFIGHTTS_STR(0x18C),
    WFIGHTTS_STR(0x178), WFIGHTTS_STR(0x164), WFIGHTTS_STR(0x150), WFIGHTTS_STR(0x13C),
    WFIGHTTS_STR(0x128), WFIGHTTS_STR(0x114), WFIGHTTS_STR(0x100), WFIGHTTS_STR(0x0EC),
    WFIGHTTS_STR(0x0D8), WFIGHTTS_STR(0x0C4), WFIGHTTS_STR(0x0B0),
};
char *D_800A83A4[] = {
    WFIGHTTS_STR(0x8A8), WFIGHTTS_STR(0x898), WFIGHTTS_STR(0x890), WFIGHTTS_STR(0x884),
    WFIGHTTS_STR(0x874), WFIGHTTS_STR(0x864), WFIGHTTS_STR(0x854), WFIGHTTS_STR(0x844),
    WFIGHTTS_STR(0x834), WFIGHTTS_STR(0x824), WFIGHTTS_STR(0x81C), WFIGHTTS_STR(0x810),
    WFIGHTTS_STR(0x804), WFIGHTTS_STR(0x7FC), WFIGHTTS_STR(0x7EC), WFIGHTTS_STR(0x7DC),
    WFIGHTTS_STR(0x7CC), WFIGHTTS_STR(0x7BC), WFIGHTTS_STR(0x7AC), WFIGHTTS_STR(0x79C),
    WFIGHTTS_STR(0x78C), WFIGHTTS_STR(0x77C), WFIGHTTS_STR(0x76C), WFIGHTTS_STR(0x75C),
    WFIGHTTS_STR(0x74C), WFIGHTTS_STR(0x73C), WFIGHTTS_STR(0x72C), WFIGHTTS_STR(0x71C),
    WFIGHTTS_STR(0x70C), WFIGHTTS_STR(0x6FC), WFIGHTTS_STR(0x6EC), WFIGHTTS_STR(0x6DC),
    WFIGHTTS_STR(0x6CC), WFIGHTTS_STR(0x6BC), WFIGHTTS_STR(0x6AC), WFIGHTTS_STR(0x69C),
    WFIGHTTS_STR(0x68C), WFIGHTTS_STR(0x67C), WFIGHTTS_STR(0x66C), WFIGHTTS_STR(0x65C),
    WFIGHTTS_STR(0x64C), WFIGHTTS_STR(0x63C), WFIGHTTS_STR(0x62C), WFIGHTTS_STR(0x61C),
    WFIGHTTS_STR(0x60C), WFIGHTTS_STR(0x5FC), WFIGHTTS_STR(0x5EC), WFIGHTTS_STR(0x5DC),
    WFIGHTTS_STR(0x5CC), WFIGHTTS_STR(0x5BC), WFIGHTTS_STR(0x5AC), WFIGHTTS_STR(0x59C),
    WFIGHTTS_STR(0x58C), WFIGHTTS_STR(0x57C), WFIGHTTS_STR(0x56C), WFIGHTTS_STR(0x55C),
    WFIGHTTS_STR(0x54C), WFIGHTTS_STR(0x53C), WFIGHTTS_STR(0x52C), WFIGHTTS_STR(0x51C),
    WFIGHTTS_STR(0x50C), WFIGHTTS_STR(0x4FC),
};
char *D_800A849C[] = {
    WFIGHTTS_STR(0x9B0), WFIGHTTS_STR(0x9A4), WFIGHTTS_STR(0x998), WFIGHTTS_STR(0x98C),
    WFIGHTTS_STR(0x984), WFIGHTTS_STR(0x97C), WFIGHTTS_STR(0x970), WFIGHTTS_STR(0x964),
    WFIGHTTS_STR(0x958), WFIGHTTS_STR(0x94C), WFIGHTTS_STR(0x940), WFIGHTTS_STR(0x934),
    WFIGHTTS_STR(0x928), WFIGHTTS_STR(0x91C), WFIGHTTS_STR(0x90C), WFIGHTTS_STR(0x8FC),
    WFIGHTTS_STR(0x8EC), WFIGHTTS_STR(0x8DC), WFIGHTTS_STR(0x8C8), WFIGHTTS_STR(0x8B8),
};
s32 D_800A84EC[] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A852C[] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0,
};
s32 D_800A8560 = 0;
s32 D_800A8564 = 0;
BattleTestCursors WFIGHTTS_motionCursors = { { 0, 0 }, 0, { 0, 0 }, { 0, 0 } };
BattleTestCursors WFIGHTTS_effectCursors = { { 0, 0 }, 0, { 0, 0 }, { 0, 0 } };
