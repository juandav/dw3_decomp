/* The second object of FIELDSTG.PRO (see fieldstg.c): its rodata starts at
   0x800824C4 (USA). */

#include "fieldstg.h"

/*
 * A lift made of the map objects 2 and 3: on state 2 it shakes, moves the
 * objects and the player 0x7F pixels up or down a pixel every other frame,
 * shakes again and flips unk58.
 */
void func_800834A0(Unk800834A0 *task) {
    MapObject *object;
    MapObject *left;
    MapObject *right;
    Actor *player;
    s32 offset;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        for (object = (MapObject *)D_800990B4.unk10; object->unk2 != 0; object++) {
            switch (object->id) {
            case 2:
                task->right = object;
                task->rightBaseY = object->y;
                if (task->unk58) {
                    object->y -= 0x7F;
                }
                object->unk0 = 0;
                break;
            case 3:
                task->left = object;
                task->leftBaseY = object->y;
                if (task->unk58) {
                    object->y -= 0x7F;
                }
                object->unk0 = 1;
                break;
            }
        }
        task->unk58 = 0;
        break;
    case 1:
        break;
    case 2:
        left = task->left;
        right = task->right;
        player = TASK_FUNCS.find(5, -1, 0);
        switch (task->substate) {
        case 0:
        default:
            right->unk0 = 1;
            task->time = 0;
            task->leftY = left->y;
            task->rightY = right->y;
            task->playerY = player->pos.y;
            SOUND.playSound(0x8004103C);
            task->nextSubstate(task);
            break;
        case 1:
            task->time += GFX_FUNCS.getFrameTime();
            if (task->time >= 30) {
                task->shake = 0;
                task->nextSubstate(task);
                SOUND.playSound(0x01080001);
            }
            break;
        case 2:
        case 4:
            offset = D_80095E84[task->shake];
            if (offset != 1000) {
                left->y = task->leftY + offset;
                right->y = task->rightY + offset;
                player->pos.y = task->playerY + offset;
                task->shake++;
            } else {
                task->nextSubstate(task);
                task->shake = 0;
            }
            break;
        case 3:
            task->shake++;
            if (task->shake >= 0xFE) {
                if (task->unk58) {
                    left->y = task->leftBaseY;
                    right->y = task->rightBaseY;
                    player->pos.y = task->playerY + 0x7F00;
                } else {
                    left->y = task->leftBaseY - 0x7F;
                    right->y = task->rightBaseY - 0x7F;
                    player->pos.y = task->playerY - 0x7F00;
                }
                task->leftY = left->y;
                task->rightY = right->y;
                task->playerY = player->pos.y;
                task->nextSubstate(task);
                task->shake = 0;
            } else if (task->shake & 1) {
                if (task->unk58) {
                    left->y++;
                    right->y++;
                    player->pos.y += 0x100;
                } else {
                    left->y--;
                    right->y--;
                    player->pos.y -= 0x100;
                }
            }
            break;
        case 5:
            right->unk0 = 0;
            task->setState(task, 1);
            task->unk58 ^= 1;
            break;
        }
        break;
    case 3:
        break;
    }
}

void func_800838BC(Unk800834A0 *task, s32 arg1) {
    if (task != NULL) {
        switch (arg1) {
        case 0x348:
            task->setState(task, 2);
            task->unk58 = 0;
            break;
        case 0x349:
            task->setState(task, 2);
            task->unk58 = 1;
            break;
        }
    }
}

Unk800834A0 *func_80083930(s32 id) {
    Unk800834A0 *task = createTaskWithId(func_800834A0, sizeof(Unk800834A0), 0, id);

    if (FLAGS_00.checkCondition(0x1C3D, 1)) {
        task->unk58 = 1;
    } else {
        task->unk58 = 0;
    }
    return task;
}

/*
 * A yes/no question of the story (func_80083F8C to func_80084294 make one
 * per type): asks D_80095E98[type]'s question and starts the event of the
 * answer.
 */
void func_80083998(ChoiceTask *task, ChoiceChildren *children) {
    SpriteDrawer drawer;
    s32 prev;
    s32 i;
    s32 j;
    s32 k;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->tween.duration = 10;
        for (i = 0; i < 2; i++) {
            children->options[i] = createTextWindow(0x1002, 1, 0x1C, 0xBE + i * 14);
            children->options[i]->setDepth(children->options[i], 1);
        }
        children->cursor = createCursor(0x1002, 1, 0x12, 0xBE);
        children->cursor->setVisible(children->cursor, 0);
        children->title = createTextWindow(0x1002, 1, 0x12, 0xB0);
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            D_80098B70(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_80098B74(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(D_80095E98[task->type].text + (TEXT_FILE(1) << 16)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE_GET_ENTRY[0](D_80095E98[task->type].text + (TEXT_FILE(1) << 16)), 1);
                task->substate++;
            }
            break;
        case 2:
            prev = task->selection;
            if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                if (--task->selection < 0) {
                    task->selection = 0;
                }
            } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                task->selection++;
                if (task->selection > 1) {
                    task->selection = 1;
                }
            }
            if (prev != task->selection) {
                SOUND.playSound(0x8004513E);
                children->cursor->setPos(children->cursor, 0x12, task->selection * 14 + 0xBE);
                break;
            }
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x8004503C);
                task->substate = 10;
            }
            break;
        case 3:
            children->event = func_80084B80(task->selection == 0 ? D_80095E98[task->type].events[0] : D_80095E98[task->type].events[1]);
            task->substate++;
            break;
        case 4:
            if (children->event == NULL) {
                task->state = 3;
            }
            break;
        case 10:
            for (k = 0; k < 2; k++) {
                children->options[k]->setVisible(children->options[k], 0);
            }
            children->cursor->setVisible(children->cursor, 0);
            children->title->setVisible(children->title, 0);
            D_80098B70(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_80098B74(&task->tween)) {
                task->substate = 3;
            }
            break;
        }
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x1002, 2);
        drawer.setTexture(0x140, 0);
        drawer.setFollowScroll(0);
        if (task->tween.value != 0) {
            if (task->tween.value != 0x1000) {
                drawer.setScale(task->tween.value, 0x1000, 0x1000);
                drawer.setPivot(0, 0xC3);
            }
            drawer.draw(FILE_CACHE_GET_ENTRY[0](FILE_MENU_SPRITES << 16), 0x45, 0, 0xAC);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void func_80083F8C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 0;
}

void func_80083FBC(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 1;
}

void func_80083FF0(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 2;
}

void func_80084024(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 3;
}

void func_80084058(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 4;
}

void func_8008408C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 5;
}

void func_800840C0(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 6;
}

void func_800840F4(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 7;
}

void func_80084128(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 8;
}

void func_8008415C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 9;
}

void func_80084190(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 10;
}

void func_800841C4(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 11;
}

void func_800841F8(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 12;
}

void func_8008422C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 13;
}

void func_80084260(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 14;
}

void func_80084294(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 15;
}

/*
 * Runs the story events: marks the map object 1 for the progresses that have
 * one, then starts the first event of D_80095F18 whose progress, flag and
 * condition hold, and its next script once the first one ends.
 */
void func_800842C8(Unk800842C8 *task, Unk800842C8Children *children) {
    MapObject *object;
    ProgressEvent *event;
    s32 i;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->script = 0;
        for (object = (MapObject *)D_800990B4.unk10; object->unk2 != 0; object++) {
            if (object->id == 1) {
                break;
            }
        }
        switch (GAME_PROGRESS) {
        case 5:
        case 8:
        case 12:
        case 14:
        case 16:
        case 22:
        case 24:
        case 26:
        case 28:
        case 30:
        case 31:
        case 34:
        case 36:
        case 37:
        case 38:
        case 39:
            object->unk0 = 1;
            break;
        default:
            object->unk0 = 0;
            break;
        }
        children->unk0 = func_80083930(0x33A);
        for (i = 0; D_80095F18[i].progress != -1; i++) {
            event = &D_80095F18[i];
            if (GAME.progress == event->progress && FLAGS_00.checkCondition(event->flag, 0) &&
                FLAGS_00.checkCondition(event->condition, 1)) {
                children->script = func_80084B80(event->script);
                task->script = event->nextScript;
                break;
            }
        }
        break;
    case 1:
        if (children->script == NULL && task->script != 0) {
            children->script = func_80084B80(task->script);
            task->script = 0;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Unk800842C8 *func_800844B8(s32 arg0) {
    Unk800842C8 *task = createTask(func_800842C8, sizeof(Unk800842C8), 8);

    task->unk50 = arg0;
    FIELDSTG_initFuncs[0]();
    return task;
}
