#include "common.h"
#include "stage.h"
void func_800A5C80();
void func_800A56B8();
void func_800A4D38();
extern StageFuncs D_800A8EF0;
void func_800A6248();
extern s32 D_800A6DE8[];

/* The text file of the menus, which the versions number differently */
#if VERSION_US
#define MENU_TEXT 0x10C
#elif VERSION_EU
#define MENU_TEXT 0x112
#endif

/* A list of up to eight options that each open a message */
void func_800A4D38(StageListMenu *task, StageListMenuChildren *children) {
    SpriteDrawer drawer;
    s32 prev;
    s32 i;
    s32 j;
    s32 k;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->tweens[0].duration = 10;
        task->tweens[1].duration = 10;
        for (i = 0; i < 8; i++) {
            children->options[i] = createTextWindow(0x1002, 1, 0xBD, 0x21 + i * 14);
            children->options[i]->setDepth(children->options[i], 1);
        }
        children->cursor = createCursor(0x1002, 1, 0xAF, 0x21);
        children->cursor->setVisible(children->cursor, 0);
        children->message = createTextWindow(0x1002, 1, 0x12, 0xB0);
        children->message->setLines(children->message, 3);
        task->count = 8;
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            D_800A8EF0.start(&task->tweens[0], 1);
            task->substate++;
            break;
        case 1:
            if (D_800A8EF0.update(&task->tweens[0])) {
                for (j = 0; j < task->count; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x1)), j + 1);
                }
                children->cursor->setVisible(children->cursor, 1);
                task->substate++;
            }
            break;
        case 2:
            prev = task->cursor;
            if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
                ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
                       ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
                task->cursor++;
                if (task->cursor > task->count - 1) {
                    task->cursor = task->count - 1;
                }
            }
            if (prev != task->cursor) {
                SOUND.playSound(0x8004513E);
                children->cursor->setPos(children->cursor, 0xAF, task->cursor * 14 + 0x21);
                break;
            }
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                SOUND.playSound(0x8004503C);
                if (task->cursor == task->count - 1) {
                    task->substate = 10;
                } else {
                    task->substate++;
                }
            } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
                SOUND.playSound(0x800450BD);
                task->substate = 10;
            }
            break;
        case 3:
            children->cursor->setStill(children->cursor, 1);
            children->cursor->setPalette(children->cursor, 7);
            D_800A8EF0.start(&task->tweens[1], 1);
            task->substate++;
            break;
        case 4:
            if (D_800A8EF0.update(&task->tweens[1])) {
                children->message->setString(children->message, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x1)), task->cursor + 9);
                children->message->setTypeDelay(children->message, 6);
                task->substate++;
            }
            break;
        case 5:
            if (children->message->isFinished(children->message)) {
                task->substate++;
            } else if (children->message->isWaitingForButton(children->message)) {
                if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                    SOUND.playSound(0x4001C);
                    task->showArrow = 0;
                } else {
                    task->showArrow = 1;
                }
            } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                children->message->showPage(children->message);
            }
            break;
        case 6:
            D_800A8EF0.start(&task->tweens[1], 0);
            children->message->setVisible(children->message, 0);
            task->substate++;
            break;
        case 7:
            if (D_800A8EF0.update(&task->tweens[1])) {
                children->cursor->setStill(children->cursor, 0);
                children->cursor->setPalette(children->cursor, 0);
                task->substate = 2;
            }
            break;
        case 10:
            for (k = 0; k < task->count; k++) {
                children->options[k]->setVisible(children->options[k], 0);
            }
            children->cursor->setVisible(children->cursor, 0);
            D_800A8EF0.start(&task->tweens[0], 0);
            task->substate++;
            break;
        case 11:
            if (D_800A8EF0.update(&task->tweens[0])) {
                task->state = TASK_KILL;
            }
            break;
        }
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x1002, 2);
        drawer.setTexture(0x140, 0);
        drawer.setFollowScroll(0);
        if (task->showArrow) {
            if (GFX.funcs.getTime() - task->arrowTime >= 4) {
                task->arrowTime = GFX.funcs.getTime();
                if (++task->arrowFrame >= 5) {
                    task->arrowFrame = 0;
                }
            }
            drawer.setClutRow(task->arrowFrame);
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), 0xA, 0x124, 0xCD);
            drawer.setClutRow(0);
        }
        if (task->tweens[0].value != 0) {
            if (task->tweens[0].value != 0x1000) {
                drawer.setScale(task->tweens[0].value, 0x1000, 0x1000);
                drawer.setPivot(0x140, 0x56);
            }
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), D_800A6DE8[task->count - 5], 0xA8, 0x18);
        }
        if (task->tweens[1].value != 0) {
            if (task->tweens[1].value != 0x1000) {
                drawer.setScale(task->tweens[1].value, 0x1000, 0x1000);
                drawer.setPivot(0x140, 0x56);
            }
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), 0x45, 0, 0xAC);
        }
        break;
    case TASK_DONE:
        D_800A8EF0.start(&task->tweens[0], 1);
        D_800A8EF0.update(&task->tweens[0]);
        break;
    case TASK_KILL:
        break;
    }
}

void *func_800A568C(void) {
    return createTask(func_800A4D38, 0x84, 0x28);
}

/* A two-option menu: creates the event object of the chosen option */
void func_800A56B8(StageMenu *task, StageMenuChildren *children) {
    SpriteDrawer drawer;
    s32 prev;
    s32 i;
    s32 j;
    s32 k;

    switch (task->state) {
    case TASK_INIT:
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
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            D_800A8EF0.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A8EF0.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x2)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x2)), 1);
                task->substate++;
            }
            break;
        case 2:
            prev = task->cursor;
            if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
                ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
                       ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
                task->cursor++;
                if (task->cursor > 1) {
                    task->cursor = 1;
                }
            }
            if (prev != task->cursor) {
                SOUND.playSound(0x8004513E);
                children->cursor->setPos(children->cursor, 0x12, task->cursor * 14 + 0xBE);
                break;
            }
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                SOUND.playSound(0x8004503C);
                task->substate = 10;
                task->step = 1;
            }
            break;
        case 3:
            children->event = func_80084B80(task->cursor == 0 ? 0xD : 0xE);
            task->substate++;
            break;
        case 4:
            if (children->event == NULL) {
                task->state = TASK_KILL;
            }
            break;
        case 10:
            for (k = 0; k < 2; k++) {
                children->options[k]->setVisible(children->options[k], 0);
            }
            children->cursor->setVisible(children->cursor, 0);
            children->title->setVisible(children->title, 0);
            D_800A8EF0.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A8EF0.update(&task->tween)) {
                if (task->step == 1) {
                    task->substate = 3;
                } else {
                    task->state = TASK_KILL;
                }
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
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), 0x45, 0, 0xAC);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5C54(void) {
    return createTask(func_800A56B8, 0x64, 0x14);
}

/* A two-option menu: creates the event object of the chosen option */
void func_800A5C80(StageMenu *task, StageMenuChildren *children) {
    SpriteDrawer drawer;
    s32 prev;
    s32 i;
    s32 j;
    s32 k;

    switch (task->state) {
    case TASK_INIT:
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
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            D_800A8EF0.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A8EF0.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x35)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x35)), 1);
                task->substate++;
            }
            break;
        case 2:
            prev = task->cursor;
            if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
                ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
                       ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
                task->cursor++;
                if (task->cursor > 1) {
                    task->cursor = 1;
                }
            }
            if (prev != task->cursor) {
                SOUND.playSound(0x8004513E);
                children->cursor->setPos(children->cursor, 0x12, task->cursor * 14 + 0xBE);
                break;
            }
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                SOUND.playSound(0x8004503C);
                task->substate = 10;
                task->step = 1;
            }
            break;
        case 3:
            children->event = func_80084B80(task->cursor == 0 ? 0x3A : 0x5E7);
            task->substate++;
            break;
        case 4:
            if (children->event == NULL) {
                task->state = TASK_KILL;
            }
            break;
        case 10:
            for (k = 0; k < 2; k++) {
                children->options[k]->setVisible(children->options[k], 0);
            }
            children->cursor->setVisible(children->cursor, 0);
            children->title->setVisible(children->title, 0);
            D_800A8EF0.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A8EF0.update(&task->tween)) {
                if (task->step == 1) {
                    task->substate = 3;
                } else {
                    task->state = TASK_KILL;
                }
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
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), 0x45, 0, 0xAC);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A621C(void) {
    return createTask(func_800A5C80, 0x64, 0x14);
}

/* Creates the event object of the story so far, the first that applies */
void func_800A6248(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        do {
            if (GAME_PROGRESS == 0xD && FLAGS_00.checkCondition(0x1C0B, 0)) {
                children[0] = func_80084B80(0x136);
                break;
            }
            if (GAME_PROGRESS == 0x17 && FLAGS_00.checkCondition(0x4050, 1)) {
                children[0] = func_80084B80(0x2AD);
                break;
            }
        } while (0);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A6310(void *owner) {
    StageTask *task = createTask(func_800A6248, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A8EF0.setup();
    return task;
}

void func_800A636C(void) {
    FLAGS_00.applyAction(0x4005, 1);
    FLAGS_00.applyAction(0x1C0B, 1);
}

/* Applies flag action 0x1C26 and sets the game progress to 24 */
void func_800A63B8(void) {
    FLAGS_00.applyAction(0x1C26, 0);
    GAME_PROGRESS = 24;
}

/* the color the setup copies to D_800990B4.unk38 */
const CVECTOR D_800A4D34 = { 0x54, 0x67, 0x96, 0 };

extern s32 D_800A8684[];
extern s32 D_800A8DE8[];
extern s32 D_800A7024[];
extern s32 D_800A8500[];
extern s32 D_800A8EFC[];
extern s32 D_800A7008[];
#if VERSION_US
#define STAGE_TEXT 0xCD
#define STAGE_FILE 0x18D
#define STAGE_ARCHIVE 0x313
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xC5)
#define STAGE_FILE 0x19B
#define STAGE_ARCHIVE 0x322
#endif
void func_800A63EC(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A8684;
    D_800990B4.unk14 = D_800A8DE8;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0x11C00, 0x13400};
    D_800990B4.unk28 = D_800A7024;
    D_800990B4.unk3C = 5;
    D_800990B4.unk40 = 0x60140000;
    D_800990B4.unk4C = D_800A8500;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4D34;
    D_800990B4.events = D_800A8EFC;
    D_800990B4.unk20 = D_800A7008;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS >= 0x14 && GAME_PROGRESS < 0x18) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
    if (GAME_PROGRESS >= 0x27 && GAME_PROGRESS < 0x29) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}

/* Starts TWEEN from 0 up to 0x1000 (UP) or from 0x1000 down to 0 at twice the speed */
void func_800A6550(StageTween *tween, s32 up) {
    tween->active = 1;
    if (up) {
        SOUND.playSound(0x40019);
        tween->step = 0x1000 / tween->duration;
        tween->value = 0;
    } else {
        SOUND.playSound(0x4001A);
        tween->value = 0x1000;
        tween->step = -(0x1000 / tween->duration * 2);
    }
}

/* Steps TWEEN; returns 1 once it has stopped */
s32 func_800A65E4(StageTween *tween) {
    if (tween->active == 0) {
        return 1;
    }
    tween->value += tween->step;
    if (tween->step > 0) {
        if (tween->value > 0x1000) {
            tween->value = 0x1000;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < 0) {
        tween->value = 0;
        tween->active = 0;
        return 1;
    }
    return 0;
}

void func_800A63EC();
void func_800A63B8();
extern s32 D_800A6DF8[];
extern s32 D_800A6E04[];
extern s32 D_800A6E10[];
extern s32 D_800A6E1C[];
extern s32 D_800A6E28[];
extern s32 D_800A6E34[];
extern s32 D_800A6E40[];
extern s32 D_800A6E4C[];
extern s32 D_800A6E7C[];
extern s32 D_800A6E88[];
extern s32 D_800A6E94[];
extern s32 D_800A6EA0[];
extern s32 D_800A6EAC[];
extern s32 D_800A6EB8[];
extern s32 D_800A6EC4[];
extern s32 D_800A6ED0[];
extern s32 D_800A6F00[];
extern s32 D_800A6F0C[];
extern s32 D_800A6F18[];
extern s32 D_800A6F24[];
extern s32 D_800A6F30[];
extern s32 D_800A6F3C[];
extern s32 D_800A6F48[];
extern s32 D_800A6F54[];
extern s32 D_800A6F84[];
extern s32 D_800A6F90[];
extern s32 D_800A6F9C[];
extern s32 D_800A6FA8[];
extern s32 D_800A6FB4[];
extern s32 D_800A6FC0[];
extern s32 D_800A6FCC[];
extern s32 D_800A6FD8[];
extern s32 D_800A6E58[];
extern s32 D_800A6EDC[];
extern s32 D_800A6F60[];
extern s32 D_800A6FE4[];
extern s32 D_800A7214[];
extern s32 D_800A721C[];
extern s32 D_800A7224[];
extern s32 D_800A722C[];
extern s32 D_800A7234[];
extern s32 D_800A723C[];
extern s32 D_800A7244[];
extern s32 D_800A724C[];
extern s32 D_800A7254[];
extern s32 D_800A725C[];
extern s32 D_800A7264[];
extern s32 D_800A726C[];
extern s32 D_800A7274[];
extern s32 D_800A727C[];
extern s32 D_800A7284[];
extern s32 D_800A728C[];
extern s32 D_800A7294[];
extern s32 D_800A7A58[];
extern s32 D_800A729C[];
extern s32 D_800A7A60[];
extern s32 D_800A72C0[];
extern s32 D_800A7A6C[];
extern s32 D_800A72D8[];
extern s32 D_800A7A74[];
extern s32 D_800A72F0[];
extern s32 D_800A7A7C[];
extern s32 D_800A7308[];
extern s32 D_800A7A84[];
extern s32 D_800A732C[];
extern s32 D_800A7A90[];
extern s32 D_800A7344[];
extern s32 D_800A7A98[];
extern s32 D_800A735C[];
extern s32 D_800A7AA0[];
extern s32 D_800A7374[];
extern s32 D_800A7AA8[];
extern s32 D_800A738C[];
extern s32 D_800A7AB0[];
extern s32 D_800A73A4[];
extern s32 D_800A7AB8[];
extern s32 D_800A73BC[];
extern s32 D_800A7AC0[];
extern s32 D_800A73D4[];
extern s32 D_800A7AC8[];
extern s32 D_800A73EC[];
extern s32 D_800A7AD0[];
extern s32 D_800A7404[];
extern s32 D_800A7AD8[];
extern s32 D_800A741C[];
extern s32 D_800A7AE0[];
extern s32 D_800A7434[];
extern s32 D_800A7AE8[];
extern s32 D_800A744C[];
extern s32 D_800A7AF0[];
extern s32 D_800A7464[];
extern s32 D_800A7AF8[];
extern s32 D_800A747C[];
extern s32 D_800A7B00[];
extern s32 D_800A7B08[];
extern s32 D_800A7494[];
extern s32 D_800A7B10[];
extern s32 D_800A74AC[];
extern s32 D_800A7B18[];
extern s32 D_800A74C4[];
extern s32 D_800A7B20[];
extern s32 D_800A74DC[];
extern s32 D_800A7B2C[];
extern s32 D_800A74F4[];
extern s32 D_800A7B34[];
extern s32 D_800A750C[];
extern s32 D_800A7B3C[];
extern s32 D_800A7524[];
extern s32 D_800A7B44[];
extern s32 D_800A753C[];
extern s32 D_800A7B4C[];
extern s32 D_800A7554[];
extern s32 D_800A7B54[];
extern s32 D_800A756C[];
extern s32 D_800A7B5C[];
extern s32 D_800A7584[];
extern s32 D_800A7B64[];
extern s32 D_800A759C[];
extern s32 D_800A7B6C[];
extern s32 D_800A75B4[];
extern s32 D_800A7B74[];
extern s32 D_800A75CC[];
extern s32 D_800A7B7C[];
extern s32 D_800A75E4[];
extern s32 D_800A7B84[];
extern s32 D_800A75FC[];
extern s32 D_800A7B8C[];
extern s32 D_800A7614[];
extern s32 D_800A7B94[];
extern s32 D_800A762C[];
extern s32 D_800A7B9C[];
extern s32 D_800A7BA4[];
extern s32 D_800A7644[];
extern s32 D_800A7BAC[];
extern s32 D_800A765C[];
extern s32 D_800A7BB4[];
extern s32 D_800A7674[];
extern s32 D_800A7BBC[];
extern s32 D_800A768C[];
extern s32 D_800A7BC4[];
extern s32 D_800A76A4[];
extern s32 D_800A7BCC[];
extern s32 D_800A76BC[];
extern s32 D_800A7BD4[];
extern s32 D_800A76D4[];
extern s32 D_800A7BDC[];
extern s32 D_800A76EC[];
extern s32 D_800A7BE4[];
extern s32 D_800A7704[];
extern s32 D_800A7BEC[];
extern s32 D_800A771C[];
extern s32 D_800A7BF4[];
extern s32 D_800A7734[];
extern s32 D_800A7BFC[];
extern s32 D_800A774C[];
extern s32 D_800A7C04[];
extern s32 D_800A7764[];
extern s32 D_800A7C0C[];
extern s32 D_800A777C[];
extern s32 D_800A7C14[];
extern s32 D_800A7794[];
extern s32 D_800A7C1C[];
extern s32 D_800A7C24[];
extern s32 D_800A77AC[];
extern s32 D_800A7C2C[];
extern s32 D_800A77C4[];
extern s32 D_800A7C34[];
extern s32 D_800A77DC[];
extern s32 D_800A7C3C[];
extern s32 D_800A77F4[];
extern s32 D_800A7C44[];
extern s32 D_800A780C[];
extern s32 D_800A7C4C[];
extern s32 D_800A7824[];
extern s32 D_800A7C54[];
extern s32 D_800A783C[];
extern s32 D_800A7C5C[];
extern s32 D_800A7854[];
extern s32 D_800A7C64[];
extern s32 D_800A786C[];
extern s32 D_800A7C6C[];
extern s32 D_800A7C74[];
extern s32 D_800A7C80[];
extern s32 D_800A7C8C[];
extern s32 D_800A7C98[];
extern s32 D_800A7CA0[];
extern s32 D_800A7CAC[];
extern s32 D_800A7CB4[];
extern s32 D_800A7884[];
extern s32 D_800A7CBC[];
extern s32 D_800A789C[];
extern s32 D_800A7CC4[];
extern s32 D_800A78B4[];
extern s32 D_800A7CCC[];
extern s32 D_800A78CC[];
extern s32 D_800A7CD4[];
extern s32 D_800A78E4[];
extern s32 D_800A7CDC[];
extern s32 D_800A78FC[];
extern s32 D_800A7CE4[];
extern s32 D_800A7914[];
extern s32 D_800A7CF4[];
extern s32 D_800A7D00[];
extern s32 D_800A7938[];
extern s32 D_800A7D08[];
extern s32 D_800A7950[];
extern s32 D_800A7D10[];
extern s32 D_800A7D18[];
extern s32 D_800A7D20[];
extern s32 D_800A7D28[];
extern s32 D_800A7968[];
extern s32 D_800A7D30[];
extern s32 D_800A7980[];
extern s32 D_800A7D38[];
extern s32 D_800A7998[];
extern s32 D_800A7D40[];
extern s32 D_800A79B0[];
extern s32 D_800A7D48[];
extern s32 D_800A79C8[];
extern s32 D_800A7D50[];
extern s32 D_800A79E0[];
extern s32 D_800A7D58[];
extern s32 D_800A79F8[];
extern s32 D_800A7D60[];
extern s32 D_800A7A10[];
extern s32 D_800A7D68[];
extern s32 D_800A7A28[];
extern s32 D_800A7D70[];
extern s32 D_800A7A40[];
extern s32 D_800A7D78[];
extern s32 D_800A7D80[];
extern s32 D_800A7D94[];
extern s32 D_800A7DA8[];
extern s32 D_800A7DBC[];
extern s32 D_800A7DD0[];
extern s32 D_800A7DE4[];
extern s32 D_800A7DF8[];
extern s32 D_800A7E0C[];
extern s32 D_800A7E20[];
extern s32 D_800A7E34[];
extern s32 D_800A7E48[];
extern s32 D_800A7E5C[];
extern s32 D_800A7E70[];
extern s32 D_800A7E84[];
extern s32 D_800A7E98[];
extern s32 D_800A7EAC[];
extern s32 D_800A7EC0[];
extern s32 D_800A7ED4[];
extern s32 D_800A7EE8[];
extern s32 D_800A7EFC[];
extern s32 D_800A7F10[];
extern s32 D_800A7F24[];
extern s32 D_800A7F38[];
extern s32 D_800A7F4C[];
extern s32 D_800A7F60[];
extern s32 D_800A7F74[];
extern s32 D_800A7F88[];
extern s32 D_800A7F9C[];
extern s32 D_800A7FB0[];
extern s32 D_800A7FC4[];
extern s32 D_800A7FD8[];
extern s32 D_800A7FEC[];
extern s32 D_800A8000[];
extern s32 D_800A8014[];
extern s32 D_800A8028[];
extern s32 D_800A803C[];
extern s32 D_800A8050[];
extern s32 D_800A8064[];
extern s32 D_800A8078[];
extern s32 D_800A808C[];
extern s32 D_800A80A0[];
extern s32 D_800A80B4[];
extern s32 D_800A80C8[];
extern s32 D_800A80DC[];
extern s32 D_800A80F0[];
extern s32 D_800A8104[];
extern s32 D_800A8118[];
extern s32 D_800A812C[];
extern s32 D_800A8140[];
extern s32 D_800A8154[];
extern s32 D_800A8168[];
extern s32 D_800A817C[];
extern s32 D_800A8190[];
extern s32 D_800A81A4[];
extern s32 D_800A81B8[];
extern s32 D_800A81CC[];
extern s32 D_800A81E0[];
extern s32 D_800A81F4[];
extern s32 D_800A8208[];
extern s32 D_800A821C[];
extern s32 D_800A8230[];
extern s32 D_800A8244[];
extern s32 D_800A8258[];
extern s32 D_800A826C[];
extern s32 D_800A8280[];
extern s32 D_800A8294[];
extern s32 D_800A82A8[];
extern s32 D_800A82BC[];
extern s32 D_800A82D0[];
extern s32 D_800A82E4[];
extern s32 D_800A82F8[];
extern s32 D_800A830C[];
extern s32 D_800A8320[];
extern s32 D_800A8334[];
extern s32 D_800A8348[];
extern s32 D_800A835C[];
extern s32 D_800A8370[];
extern s32 D_800A8384[];
extern s32 D_800A8398[];
extern s32 D_800A83AC[];
extern s32 D_800A83C0[];
extern s32 D_800A83D4[];
extern s32 D_800A83E8[];
extern s32 D_800A83FC[];
extern s32 D_800A8410[];
extern s32 D_800A8424[];
extern s32 D_800A8438[];
extern s32 D_800A844C[];
extern s32 D_800A8460[];
extern s32 D_800A8474[];
extern s32 D_800A8488[];
extern s32 D_800A849C[];
extern s32 D_800A84B0[];
extern s32 D_800A84C4[];
extern s32 D_800A84D8[];
extern s32 D_800A84EC[];
extern s32 D_800A6650[];
extern s32 D_800A66A8[];
extern s32 D_800A6724[];
extern s32 D_800A6788[];
extern s32 D_800A67F4[];
extern s32 D_800A686C[];
extern s32 D_800A69EC[];
extern s32 D_800A6A48[];
extern s32 D_800A6AA4[];
extern s32 D_800A6DD0[];

s32 D_800A6650[] = {
    0x10600, 0x1020002, 0x1600002, 0x50110,
    0x200100, 0xFF0180, 0x200101, 0x10001,
    0x240100, 0xF701B2, 0x240101, 0x70001,
    0x20302, 0x20101, 0x50001, 0x1E0300,
    512, 0x200001, 0x3010000, 0x2040304,
    0x1100160, 5,
};
s32 D_800A66A8[] = {
    0x10600, 0x1020002, 0x1600002, 0x50110,
    0x200100, 0xFF0180, 0x200101, 0x10001,
    0x240100, 0xF701B2, 0x240101, 0x70001,
    0x20302, 0x20101, 0x50001, 0x1E0300,
    512, 0x200001, 0x3010000, 0x1E0300,
    0x20101, 0x10001, 0x1E0300, 512,
    0x20002, 0x3010003, 0x1E0300, 0x20102,
    0x1180150, 0x3020001, 2,
};
s32 D_800A6724[] = {
    0x10600, 0x1010002, 0x10002, 0x1010001,
    0x3250323, 0x1010002, 0x337032D, 0x3000002,
    0x101003C, 0x3260323, 0x3000002, 0x102001E,
    0xB20002, 0x50167, 0x20302, 0x20101,
    0x50001, 0x1E0300, 512, 0x20001,
    0x3010002, 0x20101, 0x50001, 0x1E0300,
#if VERSION_US
    0,
#elif VERSION_EU
    0x5DE00000,
#endif
};
s32 D_800A6788[] = {
    0x10600, 0x1010002, 0x10002, 0x1010007,
    0x3250323, 0x1010002, 0x337032D, 0x3000002,
    0x101003C, 0x3260323, 0x3000002, 0x102001E,
    0x27F0002, 0x3022D, 0x20302, 0x20101,
    0x30001, 0x3230101, 0x20326, 0x1E0300,
    512, 0x20001, 0x3010002, 0x20101,
    0x30001, 0x1E0300,
#if VERSION_US
    0,
#elif VERSION_EU
    0x4A5F0000,
#endif
};
s32 D_800A67F4[] = {
    0x1E0300, 0x1E0300, 512, 0x200001,
    0x3010002, 0x1E0300, 0x32D0101, 0x20338,
    0x1E0300, 512, 0x20002, 0x3010004,
    0x1E0300, 512, 0x200003, 0x3010004,
    0x1E0300, 512, 0x20004, 0x3010004,
    0x1E0300, 0x32D0101, 0x20339, 0x1E0300,
    0x1E0300, 512, 0x200005, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A686C[] = {
    0x10600, 0x100006A, 0x1800020, 0x10100FF,
    0x10020, 0x1000001, 0x1B20024, 0x10100F7,
    0x10024, 0x1000007, 0x29F002D, 0x1010178,
    0x1002D, 0x1000007, 0x1780031, 0x10100D5,
    0x10031, 0x1000007, 0x2170036, 0x1010133,
    0x10036, 0x1000001, 0x1480037, 0x1010104,
    0x10037, 0x1000006, 0x1220041, 0x1010159,
    0x10041, 0x1000005, 0x13D006A, 0x1010137,
    0x1006A, 0x1000003, 0x11D006B, 0x1010127,
    0x1006B, 0x3000007, 0x2000078, 0x10000,
    0x3006A, 0x3000301, 0x200001E, 0x20000,
    107, 0x3000301, 0x200001E, 0x30000,
    0x3006A, 0x3000301, 0x200001E, 0x40000,
    107, 0x3000301, 0x200001E, 0x50000,
    0x3006A, 0x3000301, 0x200001E, 0x60000,
    107, 0x6000301, 0x6B0000, 0x6B0101,
    0x30001, 0x1E0300, 0x6A0101, 0x40001,
    0x6B0102, 0xD8011D, 0x3020004, 0x102006B,
    0x14A006B, 0x500C4, 0x6B0302, 0x32D0101,
    0x6B034F, 0xC0300, 0x6B0102, 0xA4018A,
    0x3020005, 0x101006B, 0x355032D, 0x300006B,
    0x600001E, 0x6A0000, 0x6B0100, 0,
    0x6B0101, 1, 0x1E0300, 512,
    0x6A0007, 0x3010000, 0x1E0300, 0,
};
s32 D_800A69EC[] = {
    0x10600, 0x101006A, 0x1006A, 0x1010001,
    0x3250323, 0x300006A, 0x101003C, 0x3260323,
    0x300006A, 0x102001E, 0xE8006A, 0x5014C,
    0x6A0302, 0x6A0101, 0x50001, 0x1E0300,
    512, 0x6A0001, 0x3010003, 0x6A0101,
    0x50001, 0x1E0300, 0,
};
s32 D_800A6A48[] = {
    0x10600, 0x101006A, 0x1006A, 0x1010007,
    0x3250323, 0x300006A, 0x101003C, 0x3260323,
    0x300006A, 0x102001E, 0x268006A, 0x3021C,
    0x6A0302, 0x6A0101, 0x30001, 0x1E0300,
    512, 0x6A0001, 0x3010001, 0x6A0101,
    0x30001, 0x1E0300, 0,
};
s32 D_800A6AA4[] = {
    0x20100, 0xA4018A, 0x20101, 0x10001,
    0x32D0101, 0x2034F, 0x1E0300, 0x20102,
    0xC4014A, 0x1000001, 0x18A00B3, 0x10100A4,
    0x100B3, 0x3020001, 0x1020002, 0x12A0002,
    0x500D4, 0xB30102, 0xC4014A, 0x3020001,
    0x10100B3, 0x10002, 0x1010005, 0x100B3,
    0x1010001, 0x355032D, 0x3000002, 0x1020006,
    0x11A0002, 0x100DC, 0xB30102, 0xCC013A,
    0x3020001, 0x1010002, 0x10002, 0x1010005,
    0x100B3, 0x3000001, 0x200001E, 0x10000,
    0x10002, 0x20101, 0x50007, 0x1020301,
    0x11A0002, 0x400FC, 0xC0300, 512,
    0xB30002, 0x1020002, 0x11A00B3, 220,
    0x1010301, 0x10002, 0x1010004, 0x3250323,
    0x3000002, 0x101003C, 0x3260323, 0x3000002,
    0x200001E, 0x30000, 0x10002, 0x20101,
    0x40007, 0x1010301, 0x10002, 0x3000004,
    0x101001E, 0x3270323, 0x3000002, 0x101003C,
    0x3260323, 0x3000002, 0x200001E, 0x40000,
    0x200B3, 0x3000301, 0x200001E, 0x50000,
    0x10002, 0x20101, 0x40007, 0x1010301,
    0x10002, 0x3000004, 0x200001E, 0x60000,
    0x200B3, 0x3000301, 0x200001E, 0x70000,
    0x10002, 0x20101, 0x40007, 0x1010301,
    0x10002, 0x3000004, 0x200001E, 0x80000,
    0x200B3, 0x3000301, 0x200001E, 0x90000,
    0x10002, 0x1010301, 0x10002, 0x3000004,
    0x101001E, 0x3270323, 0x3000002, 0x101003C,
    0x3260323, 0x3000002, 0x101003C, 0x3250323,
    0x3000002, 0x101003C, 0x10002, 0x1010004,
    0x3260323, 0x3000002, 0x200001E, 0xA0000,
    0x10002, 0x20101, 0x40007, 0x1010301,
    0x10002, 0x3000004, 0x101001E, 0x3250323,
    0x30000B3, 0x101003C, 0x3260323, 0x30000B3,
    0x101001E, 0x100B3, 0x3020000, 0x30000B3,
    0x200001E, 0xB0000, 0x200B3, 0x3000301,
    0x200001E, 0xC0000, 0x10002, 0x20101,
    0x40007, 0x1010301, 0x10002, 0x3000004,
    0x200001E, 0xD0000, 0x200B3, 0x3000301,
    0x200001E, 0xE0000, 0x10002, 0x20101,
    0x40007, 0x1010301, 0x10002, 0x3000004,
    0x200001E, 0xF0000, 0x200B3, 0x3000301,
    0x200001E, 0x100000, 0x10002, 0x20101,
    0x40007, 0x1010301, 0x10002, 0x3000004,
    0x200001E, 0x110000, 0x200B3, 0x3000301,
    0x101001E, 0x10002, 0x1010000, 0x100B3,
    0x3000005, 0x102001E, 0x11A0002, 304,
    0xB30102, 0xC4014A, 0x3020005, 0x1020002,
    0x9A0002, 0x10170, 0xB30102, 0xA4018A,
    0x1010005, 0x34F032D, 0x3000002, 0x304000C,
    0x3E80200, 0x100EC, 0,
};
s32 D_800A6DD0[] = {
    0x3C0300, 512, 0x200001, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A6DE8[] = {
    28, 27, 25, 36,
};
s32 D_800A6DF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E04[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E34[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E58[] = {
    0, (s32)D_800A6DF8, (s32)D_800A6E04, (s32)D_800A6E10,
    (s32)D_800A6E1C, (s32)D_800A6E28, (s32)D_800A6E34, (s32)D_800A6E40,
    (s32)D_800A6E4C,
};
s32 D_800A6E7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ED0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EDC[] = {
    0, (s32)D_800A6E7C, (s32)D_800A6E88, (s32)D_800A6E94,
    (s32)D_800A6EA0, (s32)D_800A6EAC, (s32)D_800A6EB8, (s32)D_800A6EC4,
    (s32)D_800A6ED0,
};
s32 D_800A6F00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F24[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F30[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F60[] = {
    0, (s32)D_800A6F00, (s32)D_800A6F0C, (s32)D_800A6F18,
    (s32)D_800A6F24, (s32)D_800A6F30, (s32)D_800A6F3C, (s32)D_800A6F48,
    (s32)D_800A6F54,
};
s32 D_800A6F84[] = {
    188, 15, 0x60080000,
};
s32 D_800A6F90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FE4[] = {
    0, (s32)D_800A6F84, (s32)D_800A6F90, (s32)D_800A6F9C,
    (s32)D_800A6FA8, (s32)D_800A6FB4, (s32)D_800A6FC0, (s32)D_800A6FCC,
    (s32)D_800A6FD8,
};
s32 D_800A7008[] = {
    132, 0, 0, (s32)D_800A6E58,
    (s32)D_800A6EDC, (s32)D_800A6F60, (s32)D_800A6FE4,
};
s32 D_800A7024[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x10001B4, 464, 0x1F80170,
    0x10001C0, 0x16E01E8, 0x6E02A0, 0x1F70140,
    0x1000140, 0x1390178, 0x3900E0, 0x1F70150,
    0x1000180, 0x1B901B6, 0xB901D8, 0x1F70160,
    0x10001C0, 0x16E01E0, 0x6E0280, 0x1F70170,
    0x10001C0, 0x16E01C0, 0x6E0200, 0x1F60140,
    0x1000180, 0x1A001A0, 0xA00180, 0x1F60150,
    0x1000180, 0x1C801A0, 0xC80180, 0x1F60160,
    0x10001C0, 0x16E01D8, 0x6E0260, 0x1F60170,
    0x10001C0, 0x16E01C8, 0x6E0220, 0x1F50140,
    0x10001C0, 0x19601C8, 0x960220, 0x1F50160,
    0x10001C0, 0x1B601E8, 0xB602A0, 0x1F50170,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0x10001C0, 0x19601D0, 0x960240, 0x1F40140,
    0x10001C0, 0x19601D8, 0x960260, 0x1F40150,
    0x10001C0, 0x19601E0, 0x960280, 0x1F40160,
    0x1000140, 0x1390170, 0x3900C0, 0x1F40170,
    0x10001C0, 0x1B601C0, 0xB60200, 0x1F30150,
    0x10001C0, 0x1B601C8, 0xB60220, 0x1F30160,
    0x10001C0, 0x1B601D0, 0xB60240, 0x1F30170,
    0x10001C0, 0x1B601D8, 0xB60260, 0x1F20140,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0x1000140, 0x1390168, 0x3900A0, 0x1F20150,
};
s32 D_800A7214[] = {
    6656, 65535,
};
s32 D_800A721C[] = {
    0x11A00, 65535,
};
s32 D_800A7224[] = {
    0x11A00, 65535,
};
s32 D_800A722C[] = {
    0x19004, 65535,
};
s32 D_800A7234[] = {
    0x1901A, 65535,
};
s32 D_800A723C[] = {
    0x1901A, 65535,
};
s32 D_800A7244[] = {
    0x1901A, 65535,
};
s32 D_800A724C[] = {
    6656, 65535,
};
s32 D_800A7254[] = {
    0x11A00, 65535,
};
s32 D_800A725C[] = {
    0x11A00, 65535,
};
s32 D_800A7264[] = {
    0x19003, 65535,
};
s32 D_800A726C[] = {
    0x19003, 65535,
};
s32 D_800A7274[] = {
    0x19003, 65535,
};
s32 D_800A727C[] = {
    36867, 65535,
};
s32 D_800A7284[] = {
    6678, 65535,
};
s32 D_800A728C[] = {
    0x11A16, 65535,
};
s32 D_800A7294[] = {
    0x11A16, 65535,
};
s32 D_800A729C[] = {
    (s32)D_800A7214, (s32)D_800A721C, 103, (s32)D_800A7224,
    (s32)D_800A722C, 1158, 0, 0,
    0,
};
s32 D_800A72C0[] = {
    0, (s32)D_800A7234, 103, 0,
    0, 0,
};
s32 D_800A72D8[] = {
    0, (s32)D_800A723C, 1065, 0,
    0, 0,
};
s32 D_800A72F0[] = {
    0, (s32)D_800A7244, 1067, 0,
    0, 0,
};
s32 D_800A7308[] = {
    (s32)D_800A724C, (s32)D_800A7254, 102, (s32)D_800A725C,
    (s32)D_800A7264, 52, 0, 0,
    0,
};
s32 D_800A732C[] = {
    0, (s32)D_800A726C, 52, 0,
    0, 0,
};
s32 D_800A7344[] = {
    0, (s32)D_800A7274, 53, 0,
    0, 0,
};
s32 D_800A735C[] = {
    0, (s32)D_800A727C, 55, 0,
    0, 0,
};
s32 D_800A7374[] = {
    0, 0, 17, 0,
    0, 0,
};
s32 D_800A738C[] = {
    0, 0, 329, 0,
    0, 0,
};
s32 D_800A73A4[] = {
    0, 0, 420, 0,
    0, 0,
};
s32 D_800A73BC[] = {
    0, 0, 422, 0,
    0, 0,
};
s32 D_800A73D4[] = {
    0, 0, 421, 0,
    0, 0,
};
s32 D_800A73EC[] = {
    0, 0, 423, 0,
    0, 0,
};
s32 D_800A7404[] = {
    0, 0, 424, 0,
    0, 0,
};
s32 D_800A741C[] = {
    0, 0, 425, 0,
    0, 0,
};
s32 D_800A7434[] = {
    0, 0, 430, 0,
    0, 0,
};
s32 D_800A744C[] = {
    0, 0, 426, 0,
    0, 0,
};
s32 D_800A7464[] = {
    0, 0, 427, 0,
    0, 0,
};
s32 D_800A747C[] = {
    0, 0, 428, 0,
    0, 0,
};
s32 D_800A7494[] = {
    0, 0, 14, 0,
    0, 0,
};
s32 D_800A74AC[] = {
    0, 0, 328, 0,
    0, 0,
};
s32 D_800A74C4[] = {
    0, 0, 409, 0,
    0, 0,
};
s32 D_800A74DC[] = {
    0, 0, 16, 0,
    0, 0,
};
s32 D_800A74F4[] = {
    0, 0, 327, 0,
    0, 0,
};
s32 D_800A750C[] = {
    0, 0, 398, 0,
    0, 0,
};
s32 D_800A7524[] = {
    0, 0, 13, 0,
    0, 0,
};
s32 D_800A753C[] = {
    0, 0, 331, 0,
    0, 0,
};
s32 D_800A7554[] = {
    0, 0, 442, 0,
    0, 0,
};
s32 D_800A756C[] = {
    0, 0, 444, 0,
    0, 0,
};
s32 D_800A7584[] = {
    0, 0, 443, 0,
    0, 0,
};
s32 D_800A759C[] = {
    0, 0, 445, 0,
    0, 0,
};
s32 D_800A75B4[] = {
    0, 0, 446, 0,
    0, 0,
};
s32 D_800A75CC[] = {
    0, 0, 447, 0,
    0, 0,
};
s32 D_800A75E4[] = {
    0, 0, 452, 0,
    0, 0,
};
s32 D_800A75FC[] = {
    0, 0, 448, 0,
    0, 0,
};
s32 D_800A7614[] = {
    0, 0, 449, 0,
    0, 0,
};
s32 D_800A762C[] = {
    0, 0, 450, 0,
    0, 0,
};
s32 D_800A7644[] = {
    0, 0, 240, 0,
    0, 0,
};
s32 D_800A765C[] = {
    0, 0, 332, 0,
    0, 0,
};
s32 D_800A7674[] = {
    0, 0, 453, 0,
    0, 0,
};
s32 D_800A768C[] = {
    0, 0, 239, 0,
    0, 0,
};
s32 D_800A76A4[] = {
    0, 0, 330, 0,
    0, 0,
};
s32 D_800A76BC[] = {
    0, 0, 431, 0,
    0, 0,
};
s32 D_800A76D4[] = {
    0, 0, 465, 0,
    0, 0,
};
s32 D_800A76EC[] = {
    0, 0, 467, 0,
    0, 0,
};
s32 D_800A7704[] = {
    0, 0, 468, 0,
    0, 0,
};
s32 D_800A771C[] = {
    0, 0, 466, 0,
    0, 0,
};
s32 D_800A7734[] = {
    0, 0, 469, 0,
    0, 0,
};
s32 D_800A774C[] = {
    0, 0, 474, 0,
    0, 0,
};
s32 D_800A7764[] = {
    0, 0, 470, 0,
    0, 0,
};
s32 D_800A777C[] = {
    0, 0, 471, 0,
    0, 0,
};
s32 D_800A7794[] = {
    0, 0, 472, 0,
    0, 0,
};
s32 D_800A77AC[] = {
    0, 0, 478, 0,
    0, 0,
};
s32 D_800A77C4[] = {
    0, 0, 479, 0,
    0, 0,
};
s32 D_800A77DC[] = {
    0, 0, 477, 0,
    0, 0,
};
s32 D_800A77F4[] = {
    0, 0, 476, 0,
    0, 0,
};
s32 D_800A780C[] = {
    0, 0, 480, 0,
    0, 0,
};
s32 D_800A7824[] = {
    0, 0, 485, 0,
    0, 0,
};
s32 D_800A783C[] = {
    0, 0, 481, 0,
    0, 0,
};
s32 D_800A7854[] = {
    0, 0, 482, 0,
    0, 0,
};
s32 D_800A786C[] = {
    0, 0, 483, 0,
    0, 0,
};
s32 D_800A7884[] = {
    0, 0, 1066, 0,
    0, 0,
};
s32 D_800A789C[] = {
    0, 0, 54, 0,
    0, 0,
};
s32 D_800A78B4[] = {
    0, 0, 429, 0,
    0, 0,
};
s32 D_800A78CC[] = {
    0, 0, 451, 0,
    0, 0,
};
s32 D_800A78E4[] = {
    0, 0, 473, 0,
    0, 0,
};
s32 D_800A78FC[] = {
    0, 0, 484, 0,
    0, 0,
};
s32 D_800A7914[] = {
    (s32)D_800A7284, (s32)D_800A728C, 79, (s32)D_800A7294,
    0, 1160, 0, 0,
    0,
};
s32 D_800A7938[] = {
    0, 0, 676, 0,
    0, 0,
};
s32 D_800A7950[] = {
    0, 0, 675, 0,
    0, 0,
};
s32 D_800A7968[] = {
    0, 0, 56, 0,
    0, 0,
};
s32 D_800A7980[] = {
    0, 0, 58, 0,
    0, 0,
};
s32 D_800A7998[] = {
    0, 0, 59, 0,
    0, 0,
};
s32 D_800A79B0[] = {
    0, 0, 57, 0,
    0, 0,
};
s32 D_800A79C8[] = {
    0, 0, 60, 0,
    0, 0,
};
s32 D_800A79E0[] = {
    0, 0, 61, 0,
    0, 0,
};
s32 D_800A79F8[] = {
    0, 0, 65, 0,
    0, 0,
};
s32 D_800A7A10[] = {
    0, 0, 62, 0,
    0, 0,
};
s32 D_800A7A28[] = {
    0, 0, 63, 0,
    0, 0,
};
s32 D_800A7A40[] = {
    0, 0, 64, 0,
    0, 0,
};
s32 D_800A7A58[] = {
    0x16002, 65535,
};
s32 D_800A7A60[] = {
    0x17022, 24598, 65535,
};
s32 D_800A7A6C[] = {
    0x16016, 65535,
};
s32 D_800A7A74[] = {
    0x1602B, 65535,
};
s32 D_800A7A7C[] = {
    0x16002, 65535,
};
s32 D_800A7A84[] = {
    0x17022, 24598, 65535,
};
s32 D_800A7A90[] = {
    0x16016, 65535,
};
s32 D_800A7A98[] = {
    0x1602B, 65535,
};
s32 D_800A7AA0[] = {
    0x16002, 65535,
};
s32 D_800A7AA8[] = {
    0x16004, 65535,
};
s32 D_800A7AB0[] = {
    0x17015, 65535,
};
s32 D_800A7AB8[] = {
    0x1600D, 65535,
};
s32 D_800A7AC0[] = {
    0x1600C, 65535,
};
s32 D_800A7AC8[] = {
    0x1600E, 65535,
};
s32 D_800A7AD0[] = {
    0x17016, 65535,
};
s32 D_800A7AD8[] = {
    0x16016, 65535,
};
s32 D_800A7AE0[] = {
    0x1602B, 65535,
};
s32 D_800A7AE8[] = {
    0x17018, 65535,
};
s32 D_800A7AF0[] = {
    0x17019, 65535,
};
s32 D_800A7AF8[] = {
    0x16026, 65535,
};
s32 D_800A7B00[] = {
    0x16017, 65535,
};
s32 D_800A7B08[] = {
    0x16002, 65535,
};
s32 D_800A7B10[] = {
    0x16004, 65535,
};
s32 D_800A7B18[] = {
    0x17015, 65535,
};
s32 D_800A7B20[] = {
    0x16002, 32768, 65535,
};
s32 D_800A7B2C[] = {
    0x16004, 65535,
};
s32 D_800A7B34[] = {
    0x17015, 65535,
};
s32 D_800A7B3C[] = {
    0x16002, 65535,
};
s32 D_800A7B44[] = {
    0x16004, 65535,
};
s32 D_800A7B4C[] = {
    0x17015, 65535,
};
s32 D_800A7B54[] = {
    0x1600D, 65535,
};
s32 D_800A7B5C[] = {
    0x1600C, 65535,
};
s32 D_800A7B64[] = {
    0x1600E, 65535,
};
s32 D_800A7B6C[] = {
    0x17016, 65535,
};
s32 D_800A7B74[] = {
    0x16016, 65535,
};
s32 D_800A7B7C[] = {
    0x1602B, 65535,
};
s32 D_800A7B84[] = {
    0x17018, 65535,
};
s32 D_800A7B8C[] = {
    0x17019, 65535,
};
s32 D_800A7B94[] = {
    0x16026, 65535,
};
s32 D_800A7B9C[] = {
    0x16017, 65535,
};
s32 D_800A7BA4[] = {
    0x16002, 65535,
};
s32 D_800A7BAC[] = {
    0x16004, 65535,
};
s32 D_800A7BB4[] = {
    0x17015, 65535,
};
s32 D_800A7BBC[] = {
    0x16002, 65535,
};
s32 D_800A7BC4[] = {
    0x16004, 65535,
};
s32 D_800A7BCC[] = {
    0x17015, 65535,
};
s32 D_800A7BD4[] = {
    0x1600C, 65535,
};
s32 D_800A7BDC[] = {
    0x1600E, 65535,
};
s32 D_800A7BE4[] = {
    0x17016, 65535,
};
s32 D_800A7BEC[] = {
    0x1600D, 65535,
};
s32 D_800A7BF4[] = {
    0x16016, 65535,
};
s32 D_800A7BFC[] = {
    0x1602B, 65535,
};
s32 D_800A7C04[] = {
    0x17018, 65535,
};
s32 D_800A7C0C[] = {
    0x17019, 65535,
};
s32 D_800A7C14[] = {
    0x16026, 65535,
};
s32 D_800A7C1C[] = {
    0x16017, 65535,
};
s32 D_800A7C24[] = {
    0x1600E, 65535,
};
s32 D_800A7C2C[] = {
    0x17016, 65535,
};
s32 D_800A7C34[] = {
    0x1600D, 65535,
};
s32 D_800A7C3C[] = {
    0x1600C, 65535,
};
s32 D_800A7C44[] = {
    0x16016, 65535,
};
s32 D_800A7C4C[] = {
    0x1602B, 65535,
};
s32 D_800A7C54[] = {
    0x17018, 65535,
};
s32 D_800A7C5C[] = {
    0x17019, 65535,
};
s32 D_800A7C64[] = {
    0x16026, 65535,
};
s32 D_800A7C6C[] = {
    0x16017, 65535,
};
s32 D_800A7C74[] = {
    0x1600D, 7181, 65535,
};
s32 D_800A7C80[] = {
    0x1600D, 7181, 65535,
};
s32 D_800A7C8C[] = {
    0x17009, 28698, 65535,
};
s32 D_800A7C98[] = {
    0x16002, 65535,
};
s32 D_800A7CA0[] = {
    0x17009, 28698, 65535,
};
s32 D_800A7CAC[] = {
    0x16002, 65535,
};
s32 D_800A7CB4[] = {
    0x1701A, 65535,
};
s32 D_800A7CBC[] = {
    0x1701A, 65535,
};
s32 D_800A7CC4[] = {
    0x1701A, 65535,
};
s32 D_800A7CCC[] = {
    0x1701A, 65535,
};
s32 D_800A7CD4[] = {
    0x1701A, 65535,
};
s32 D_800A7CDC[] = {
    0x1701A, 65535,
};
s32 D_800A7CE4[] = {
    0x11A15, 0x1600C, 32783, 65535,
};
s32 D_800A7CF4[] = {
    0x1600D, 0x11C0D, 65535,
};
s32 D_800A7D00[] = {
    0x16004, 65535,
};
s32 D_800A7D08[] = {
    0x16004, 65535,
};
s32 D_800A7D10[] = {
    0x16017, 65535,
};
s32 D_800A7D18[] = {
    0x1701A, 65535,
};
s32 D_800A7D20[] = {
    0x1701A, 65535,
};
s32 D_800A7D28[] = {
    0x1600C, 65535,
};
s32 D_800A7D30[] = {
    0x1600E, 65535,
};
s32 D_800A7D38[] = {
    0x17016, 65535,
};
s32 D_800A7D40[] = {
    0x1600D, 65535,
};
s32 D_800A7D48[] = {
    0x16016, 65535,
};
s32 D_800A7D50[] = {
    0x17018, 65535,
};
s32 D_800A7D58[] = {
    0x1602B, 65535,
};
s32 D_800A7D60[] = {
    0x17019, 65535,
};
s32 D_800A7D68[] = {
    0x16026, 65535,
};
s32 D_800A7D70[] = {
    0x1701A, 65535,
};
s32 D_800A7D78[] = {
    0x16017, 65535,
};
s32 D_800A7D80[] = {
    (s32)D_800A7A58, (s32)D_800A729C, 0x40020, 0xFF0180,
    1,
};
s32 D_800A7D94[] = {
    (s32)D_800A7A60, (s32)D_800A72C0, 0x40020, 0xFF0180,
    1,
};
s32 D_800A7DA8[] = {
    (s32)D_800A7A6C, (s32)D_800A72D8, 0x40020, 0xFF0180,
    1,
};
s32 D_800A7DBC[] = {
    (s32)D_800A7A74, (s32)D_800A72F0, 0x40020, 0xFF0180,
    1,
};
s32 D_800A7DD0[] = {
    (s32)D_800A7A7C, (s32)D_800A7308, 0x50024, 0xF701B2,
    7,
};
s32 D_800A7DE4[] = {
    (s32)D_800A7A84, (s32)D_800A732C, 0x50024, 0xF701B2,
    7,
};
s32 D_800A7DF8[] = {
    (s32)D_800A7A90, (s32)D_800A7344, 0x50024, 0xF701B2,
    7,
};
s32 D_800A7E0C[] = {
    (s32)D_800A7A98, (s32)D_800A735C, 0x50024, 0xF701B2,
    7,
};
s32 D_800A7E20[] = {
    (s32)D_800A7AA0, (s32)D_800A7374, 0x6002D, 0x16B02AC,
    7,
};
s32 D_800A7E34[] = {
    (s32)D_800A7AA8, (s32)D_800A738C, 0x6002D, 0x16B02AC,
    7,
};
s32 D_800A7E48[] = {
    (s32)D_800A7AB0, (s32)D_800A73A4, 0x6002D, 0x16B02AC,
    7,
};
s32 D_800A7E5C[] = {
    (s32)D_800A7AB8, (s32)D_800A73BC, 0x6002D, 0x16B02AC,
    7,
};
s32 D_800A7E70[] = {
    (s32)D_800A7AC0, (s32)D_800A73D4, 0x6002D, 0x1F90211,
    5,
};
s32 D_800A7E84[] = {
    (s32)D_800A7AC8, (s32)D_800A73EC, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7E98[] = {
    (s32)D_800A7AD0, (s32)D_800A7404, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7EAC[] = {
    (s32)D_800A7AD8, (s32)D_800A741C, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7EC0[] = {
    (s32)D_800A7AE0, (s32)D_800A7434, 0x6002D, 0x1610131,
    7,
};
s32 D_800A7ED4[] = {
    (s32)D_800A7AE8, (s32)D_800A744C, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7EE8[] = {
    (s32)D_800A7AF0, (s32)D_800A7464, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7EFC[] = {
    (s32)D_800A7AF8, (s32)D_800A747C, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7F10[] = {
    (s32)D_800A7B00, 0, 0x6002D, 0x1F90211,
    7,
};
s32 D_800A7F24[] = {
    (s32)D_800A7B08, (s32)D_800A7494, 0x7002E, 0x1670187,
    1,
};
s32 D_800A7F38[] = {
    (s32)D_800A7B10, (s32)D_800A74AC, 0x7002E, 0x1670187,
    1,
};
s32 D_800A7F4C[] = {
    (s32)D_800A7B18, (s32)D_800A74C4, 0x7002E, 0x1670187,
    1,
};
s32 D_800A7F60[] = {
    (s32)D_800A7B20, (s32)D_800A74DC, 0x8002F, 0x1F50269,
    1,
};
s32 D_800A7F74[] = {
    (s32)D_800A7B2C, (s32)D_800A74F4, 0x8002F, 0x1F50269,
    1,
};
s32 D_800A7F88[] = {
    (s32)D_800A7B34, (s32)D_800A750C, 0x8002F, 0x1F50269,
    1,
};
s32 D_800A7F9C[] = {
    (s32)D_800A7B3C, (s32)D_800A7524, 0x90031, 0xDD0169,
    7,
};
s32 D_800A7FB0[] = {
    (s32)D_800A7B44, (s32)D_800A753C, 0x90031, 0xDD0169,
    7,
};
s32 D_800A7FC4[] = {
    (s32)D_800A7B4C, (s32)D_800A7554, 0x90031, 0xDD0169,
    7,
};
s32 D_800A7FD8[] = {
    (s32)D_800A7B54, (s32)D_800A756C, 0x90031, 0xDD0169,
    7,
};
s32 D_800A7FEC[] = {
    (s32)D_800A7B5C, (s32)D_800A7584, 0x90031, 0x10100C1,
    7,
};
s32 D_800A8000[] = {
    (s32)D_800A7B64, (s32)D_800A759C, 0x90031, 0x10100C1,
    7,
};
s32 D_800A8014[] = {
    (s32)D_800A7B6C, (s32)D_800A75B4, 0x90031, 0x10100C1,
    7,
};
s32 D_800A8028[] = {
    (s32)D_800A7B74, (s32)D_800A75CC, 0x90031, 0x10100C1,
    7,
};
s32 D_800A803C[] = {
    (s32)D_800A7B7C, (s32)D_800A75E4, 0x90031, 0x1670187,
    7,
};
s32 D_800A8050[] = {
    (s32)D_800A7B84, (s32)D_800A75FC, 0x90031, 0x10100C1,
    7,
};
s32 D_800A8064[] = {
    (s32)D_800A7B8C, (s32)D_800A7614, 0x90031, 0x10100C1,
    7,
};
s32 D_800A8078[] = {
    (s32)D_800A7B94, (s32)D_800A762C, 0x90031, 0x10100C1,
    7,
};
s32 D_800A808C[] = {
    (s32)D_800A7B9C, 0, 0x90031, 0x10100C1,
    7,
};
s32 D_800A80A0[] = {
    (s32)D_800A7BA4, (s32)D_800A7644, 0xA0033, 0x1F90211,
    7,
};
s32 D_800A80B4[] = {
    (s32)D_800A7BAC, (s32)D_800A765C, 0xA0033, 0x1F90211,
    7,
};
s32 D_800A80C8[] = {
    (s32)D_800A7BB4, (s32)D_800A7674, 0xA0033, 0x1F90211,
    7,
};
s32 D_800A80DC[] = {
    (s32)D_800A7BBC, (s32)D_800A768C, 0xB0034, 0x10100C1,
    7,
};
s32 D_800A80F0[] = {
    (s32)D_800A7BC4, (s32)D_800A76A4, 0xB0034, 0x10100C1,
    7,
};
s32 D_800A8104[] = {
    (s32)D_800A7BCC, (s32)D_800A76BC, 0xB0034, 0x10100C1,
    7,
};
s32 D_800A8118[] = {
    (s32)D_800A7BD4, (s32)D_800A76D4, 0xC0036, 0x1330217,
    1,
};
s32 D_800A812C[] = {
    (s32)D_800A7BDC, (s32)D_800A76EC, 0xC0036, 0x1330217,
    1,
};
s32 D_800A8140[] = {
    (s32)D_800A7BE4, (s32)D_800A7704, 0xC0036, 0x1330217,
    1,
};
s32 D_800A8154[] = {
    (s32)D_800A7BEC, (s32)D_800A771C, 0xC0036, 0x1330217,
    1,
};
s32 D_800A8168[] = {
    (s32)D_800A7BF4, (s32)D_800A7734, 0xC0036, 0x1330217,
    1,
};
s32 D_800A817C[] = {
    (s32)D_800A7BFC, (s32)D_800A774C, 0xC0036, 0x10100C1,
    7,
};
s32 D_800A8190[] = {
    (s32)D_800A7C04, (s32)D_800A7764, 0xC0036, 0x1330217,
    1,
};
s32 D_800A81A4[] = {
    (s32)D_800A7C0C, (s32)D_800A777C, 0xC0036, 0x1330217,
    1,
};
s32 D_800A81B8[] = {
    (s32)D_800A7C14, (s32)D_800A7794, 0xC0036, 0x1330217,
    1,
};
s32 D_800A81CC[] = {
    (s32)D_800A7C1C, 0, 0xC0036, 0x1330217,
    1,
};
s32 D_800A81E0[] = {
    (s32)D_800A7C24, (s32)D_800A77AC, 0xD0037, 0x1040148,
    6,
};
s32 D_800A81F4[] = {
    (s32)D_800A7C2C, (s32)D_800A77C4, 0xD0037, 0x1040148,
    6,
};
s32 D_800A8208[] = {
    (s32)D_800A7C34, (s32)D_800A77DC, 0xD0037, 0x1040148,
    6,
};
s32 D_800A821C[] = {
    (s32)D_800A7C3C, (s32)D_800A77F4, 0xD0037, 0x1040148,
    6,
};
s32 D_800A8230[] = {
    (s32)D_800A7C44, (s32)D_800A780C, 0xD0037, 0x1040148,
    6,
};
s32 D_800A8244[] = {
    (s32)D_800A7C4C, (s32)D_800A7824, 0xD0037, 0x16B02AC,
    3,
};
s32 D_800A8258[] = {
    (s32)D_800A7C54, (s32)D_800A783C, 0xD0037, 0x1040148,
    6,
};
s32 D_800A826C[] = {
    (s32)D_800A7C5C, (s32)D_800A7854, 0xD0037, 0x1040148,
    6,
};
s32 D_800A8280[] = {
    (s32)D_800A7C64, (s32)D_800A786C, 0xD0037, 0x1040148,
    6,
};
s32 D_800A8294[] = {
    (s32)D_800A7C6C, 0, 0xD0037, 0x1040148,
    6,
};
s32 D_800A82A8[] = {
    (s32)D_800A7C74, 0, 0xE006A, 0,
    1,
};
s32 D_800A82BC[] = {
    (s32)D_800A7C80, 0, 0xF006B, 0,
    1,
};
s32 D_800A82D0[] = {
    (s32)D_800A7C8C, 0, 0x100070, 0x10C0168,
    1,
};
s32 D_800A82E4[] = {
    (s32)D_800A7C98, 0, 0x100070, 0x10C0168,
    1,
};
s32 D_800A82F8[] = {
    (s32)D_800A7CA0, 0, 0x110071, 0xFE01C2,
    7,
};
s32 D_800A830C[] = {
    (s32)D_800A7CAC, 0, 0x110071, 0xFE01C2,
    7,
};
s32 D_800A8320[] = {
    (s32)D_800A7CB4, (s32)D_800A7884, 0x12009D, 0xFF0180,
    1,
};
s32 D_800A8334[] = {
    (s32)D_800A7CBC, (s32)D_800A789C, 0x13009E, 0xF701B2,
    7,
};
s32 D_800A8348[] = {
    (s32)D_800A7CC4, (s32)D_800A78B4, 0x14009F, 0x1F90211,
    7,
};
s32 D_800A835C[] = {
    (s32)D_800A7CCC, (s32)D_800A78CC, 0x1500A0, 0x10100C1,
    7,
};
s32 D_800A8370[] = {
    (s32)D_800A7CD4, (s32)D_800A78E4, 0x1600A2, 0x1330217,
    1,
};
s32 D_800A8384[] = {
    (s32)D_800A7CDC, (s32)D_800A78FC, 0x1700AE, 0x1040148,
    6,
};
s32 D_800A8398[] = {
    (s32)D_800A7CE4, (s32)D_800A7914, 0x1800B2, 0x127011D,
    5,
};
s32 D_800A83AC[] = {
    (s32)D_800A7CF4, 0, 0x1800B2, 0,
    1,
};
s32 D_800A83C0[] = {
    (s32)D_800A7D00, (s32)D_800A7938, 0x1800B2, 0x127011D,
    7,
};
s32 D_800A83D4[] = {
    (s32)D_800A7D08, (s32)D_800A7950, 0x1900B3, 0x1310134,
    3,
};
s32 D_800A83E8[] = {
    (s32)D_800A7D10, 0, 0x1900B3, 0,
    1,
};
s32 D_800A83FC[] = {
    (s32)D_800A7D18, 0, 0x1A010E, 0x10C0168,
    1,
};
s32 D_800A8410[] = {
    (s32)D_800A7D20, 0, 0x1B010F, 0xFE01C2,
    7,
};
s32 D_800A8424[] = {
    (s32)D_800A7D28, (s32)D_800A7968, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A8438[] = {
    (s32)D_800A7D30, (s32)D_800A7980, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A844C[] = {
    (s32)D_800A7D38, (s32)D_800A7998, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A8460[] = {
    (s32)D_800A7D40, (s32)D_800A79B0, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A8474[] = {
    (s32)D_800A7D48, (s32)D_800A79C8, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A8488[] = {
    (s32)D_800A7D50, (s32)D_800A79E0, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A849C[] = {
    (s32)D_800A7D58, (s32)D_800A79F8, 0x1C0175, 0x1F50269,
    5,
};
s32 D_800A84B0[] = {
    (s32)D_800A7D60, (s32)D_800A7A10, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A84C4[] = {
    (s32)D_800A7D68, (s32)D_800A7A28, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A84D8[] = {
    (s32)D_800A7D70, (s32)D_800A7A40, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A84EC[] = {
    (s32)D_800A7D78, 0, 0x1C0175, 0x1610131,
    5,
};
s32 D_800A8500[] = {
    (s32)D_800A7D80, (s32)D_800A7D94, (s32)D_800A7DA8, (s32)D_800A7DBC,
    (s32)D_800A7DD0, (s32)D_800A7DE4, (s32)D_800A7DF8, (s32)D_800A7E0C,
    (s32)D_800A7E20, (s32)D_800A7E34, (s32)D_800A7E48, (s32)D_800A7E5C,
    (s32)D_800A7E70, (s32)D_800A7E84, (s32)D_800A7E98, (s32)D_800A7EAC,
    (s32)D_800A7EC0, (s32)D_800A7ED4, (s32)D_800A7EE8, (s32)D_800A7EFC,
    (s32)D_800A7F10, (s32)D_800A7F24, (s32)D_800A7F38, (s32)D_800A7F4C,
    (s32)D_800A7F60, (s32)D_800A7F74, (s32)D_800A7F88, (s32)D_800A7F9C,
    (s32)D_800A7FB0, (s32)D_800A7FC4, (s32)D_800A7FD8, (s32)D_800A7FEC,
    (s32)D_800A8000, (s32)D_800A8014, (s32)D_800A8028, (s32)D_800A803C,
    (s32)D_800A8050, (s32)D_800A8064, (s32)D_800A8078, (s32)D_800A808C,
    (s32)D_800A80A0, (s32)D_800A80B4, (s32)D_800A80C8, (s32)D_800A80DC,
    (s32)D_800A80F0, (s32)D_800A8104, (s32)D_800A8118, (s32)D_800A812C,
    (s32)D_800A8140, (s32)D_800A8154, (s32)D_800A8168, (s32)D_800A817C,
    (s32)D_800A8190, (s32)D_800A81A4, (s32)D_800A81B8, (s32)D_800A81CC,
    (s32)D_800A81E0, (s32)D_800A81F4, (s32)D_800A8208, (s32)D_800A821C,
    (s32)D_800A8230, (s32)D_800A8244, (s32)D_800A8258, (s32)D_800A826C,
    (s32)D_800A8280, (s32)D_800A8294, (s32)D_800A82A8, (s32)D_800A82BC,
    (s32)D_800A82D0, (s32)D_800A82E4, (s32)D_800A82F8, (s32)D_800A830C,
    (s32)D_800A8320, (s32)D_800A8334, (s32)D_800A8348, (s32)D_800A835C,
    (s32)D_800A8370, (s32)D_800A8384, (s32)D_800A8398, (s32)D_800A83AC,
    (s32)D_800A83C0, (s32)D_800A83D4, (s32)D_800A83E8, (s32)D_800A83FC,
    (s32)D_800A8410, (s32)D_800A8424, (s32)D_800A8438, (s32)D_800A844C,
    (s32)D_800A8460, (s32)D_800A8474, (s32)D_800A8488, (s32)D_800A849C,
    (s32)D_800A84B0, (s32)D_800A84C4, (s32)D_800A84D8, (s32)D_800A84EC,
    0,
};
s32 D_800A8684[] = {
    0x2400001, 0x1000236, 0xF30004, 69,
    0x10000, 0x2370240, 0x40100, 0x1160322,
    0, 0x2400001, 0x1000233, 0x1C90004,
    129, 0x10000, 0x2320240, 0x160300,
    0xD40153, 0, 0x2400001, 0x3000232,
    0x1740016, 196, 0x10000, 0x2320240,
    0x160300, 0xF40193, 0, 0x2400001,
    0x3000232, 0x1B30016, 228, 0x10000,
    0x2550240, 0x120700, 0x750182, 0,
    0x2400001, 0x7000255, 0x2220012, 197,
    0x10000, 0x2550240, 0x120700, 0xC502A2,
    0, 0x2400001, 0x7000256, 0x23D0012,
    209, 0x10000, 0x2560240, 0x120700,
    0xD10265, 0, 0x2400001, 0x7000257,
    0x970012, 129, 0x10000, 0x2570240,
    0x120700, 0x6F019B, 0, 0x2400001,
    0x7000257, 0x2890012, 200, 0x10000,
    0x2550640, 0x120700, 0x69000A, 0,
    0x6400001, 0x7000255, 0x2A0012, 121,
    0x10000, 0x2550640, 0x120700, 0x89004A,
    0, 0x6400001, 0x7000255, 0x1220012,
    69, 0x10000, 0x2550640, 0x120700,
    0x550142, 0, 0x6400001, 0x7000255,
    0x1620012, 101, 0x10000, 0x2550640,
    0x120700, 0xA501E2, 0, 0x6400001,
    0x7000255, 0x2020012, 181, 0x10000,
    0x2550640, 0x120700, 0xD502C2, 0,
    0x6400001, 0x7000255, 0x2E20012, 229,
    0x10000, 0x2550640, 0x120700, 0xF50302,
    0, 0x6400001, 0x7000257, 0x770012,
    145, 0x10000, 0x2580640, 0x120700,
    0xE80087, 0, 0x6400001, 0x7000258,
    0x9B0012, 222, 0x10000, 0x2580640,
    0x120700, 0xD400AF, 0, 0x6400001,
    0x7000258, 0xC30012, 202, 0x10000,
    0x2580640, 0x120700, 0xC000D7, 0,
    0x6400001, 0x7000258, 0xEB0012, 182,
    0x10000, 0x2580640, 0x120700, 0xAC00FF,
    0, 0x6400001, 0x7000258, 0x1130012,
    162, 0x10000, 0x2580640, 0x120700,
    0x980127, 0, 0x6406601, 4,
    0x14F0000, 141, 0x65010000, 0x50640,
    0, 0xE501FF, 0, 0x6406401,
    6, 0x2E00000, 326, 0x10000,
    0x2340640, 0x40300, 0xB30072, 0,
    0x6400001, 0x3000235, 0x1080004, 130,
    0x10000, 0x2590640, 0x40300, 0xB001AD,
    0, 0x6400001, 0x54510151, 0x2490008,
    335, 0x10000, 0x14D0640, 0x8504D,
    0x14F0249, 0, 0xA400001, 0x3A380138,
    0x1C000A, 519, 0x10000, 0x1380A40,
    0xA3A38, 0x1EC0051, 0, 0xA400001,
    0x3A380138, 0xB7000A, 442, 0x10000,
    0x1380A40, 0xA3A38, 0x1A800ED, 0,
    0xA400001, 0x3A380138, 0x290000A, 492,
    0x10000, 0x1380A40, 0xA3A38, 0x1AF02F0,
    0, 0xA400001, 0x3D3B013B, 0x37000A,
    506, 0x10000, 0x13B0A40, 0xA3D3B,
    0x1ED0064, 0, 0xA400001, 0x3D3B013B,
    0x97000A, 461, 0x10000, 0x13B0A40,
    0xA3D3B, 0x1BD00CA, 0, 0xA400001,
    0x3D3B013B, 0x128000A, 424, 0x10000,
    0x13B0A40, 0xA3D3B, 0x1F80291, 0,
    0xA400001, 0x403E013E, 0x103000A, 428,
    0x10000, 0x13E0A40, 0xA403E, 0x1B1016E,
    0, 0xA400001, 0x403E013E, 0x246000A,
    411, 0x10000, 0x13E0A40, 0xA403E,
    0x1BA0295, 0, 0xA400001, 0x403E013E,
    0x2A2000A, 537, 0x10000, 0x13E0A40,
    0xA403E, 0x21A02B6, 0, 0xA400001,
    0x403E013E, 0x30A000A, 417, 0x10000,
    0x1410A40, 0xA4341, 0x20501C1, 0,
    0xA400001, 0x43410141, 0x1F5000A, 544,
    0x10000, 0x1410A40, 0xA4341, 0x1630212,
    0, 0xA400001, 0x43410141, 0x222000A,
    354, 0x10000, 0x1410A40, 0xA4341,
    0x250027C, 0, 0xA400001, 0x43410141,
    0x293000A, 600, 0x10000, 0x1440A40,
    0xA4644, 0x12F0057, 0, 0xA400001,
    0x46440144, 0x82000A, 322, 0x10000,
    0x1440A40, 0xA4644, 0x26602AA, 0,
    0xA400001, 0x49470147, 0x3D000A, 292,
    0x10000, 0x1470A40, 0xA4947, 0x1480071,
    0, 0xA400001, 0x49470147, 0x1DA000A,
    531, 0x10000, 0x1470A40, 0xA4947,
    0x22A0211, 0, 0xA400001, 0x4C4A014A,
    0x1B5000A, 427, 0x10000, 0x14A0A40,
    0xA4C4A, 0x1A501C7, 0, 0xA400001,
    0x4C4A014A, 0x260000A, 405, 0x10000,
    0x14A0A40, 0xA4C4A, 0x18C0272, 0,
    0xA400001, 0x4C4A014A, 0x28E000A, 525,
    0x10000, 0x14A0A40, 0xA4C4A, 0x1A802B3,
    0, 0x4400001, 0, 0x900000,
    0xA0006E, 0x10000, 0x10440, 0,
    0x940167, 193, 0x4400001, 2,
    0x2170000, 0x11900EC, 0x10000, 0x30440,
    0, 0x14C02F7, 376, 0x4500001,
    7, 0x1B90000, 0x1C20159, 0x10000,
    0x80440, 0, 0x1BC01D0, 496,
    0x4400001, 9, 0x2530000, 0x1DE01BA,
    0x10000, 0xA0440, 0, 0x1030180,
    279, 0x4400001, 11, 0x1910000,
    0x10F00FA, 0x10000, 0xC0440, 0,
    0xFB0170, 270, 0x4400001, 13,
    0x1A10000, 0x10800F3, 0x10000, 0xE0440,
    0, 0xF20160, 262, 0x4400001,
    15, 0x1B10000, 0xFF00E9, 0x10000,
    0x100440, 0, 0xE50150, 255,
    0x4400001, 17, 0x1C10000, 0xF700E3,
    0x10000, 0x120440, 0, 0xE30140,
    247, 0x4400001, 19, 0x1510000,
    0xF000DB, 0x10000, 0x140440, 0,
    0xD00161, 231, 0x4400001, 21,
    0x1710000, 0xDF00CB, 0x10000, 0x160440,
    0, 0xC00181, 215, 0x4400001,
    23, 0x1910000, 0xCF00BB, 0x10000,
    0x180440, 0, 0x13D01F3, 334,
    0, 0, 0, 0,
    0,
};
s32 D_800A8DE8[] = {
    65535, 65535, 0x2000001, 0xEC03E8,
    1, 0, 65535, 65535,
    0x2060001, 0xF00070, 7, 0,
    65535, 65535, 0x2070001, 0x1CC0058,
    0x640005, 0, 65535, 65535,
    0x2080001, 0x1340069, 0x650005, 0,
    65535, 65535, 0x2140001, 0x2BC01F8,
    0x660005, 0, 65535, 65535,
    0x2170001, 0x1D401D8, 3, 0,
    0x16002, 65535, 0x140008, 0,
    0, 0, 0x16002, 65535,
    0x1E0008, 0, 0, 0,
    0x1600D, 65535, 0x1400008, 0,
    0, 0, 0x1600D, 65535,
    0x14A0008, 0, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
StageFuncs D_800A8EF0 = { func_800A63EC, func_800A6550, func_800A65E4 };
s32 D_800A8EFC[] = {
    8, 0,
#if VERSION_US
    0x10B0001,
#elif VERSION_EU
    0x1120001,
#endif
    (s32)func_800A568C, 0, 9, 0,
#if VERSION_US
    0x10B0002,
#elif VERSION_EU
    0x1120002,
#endif
    (s32)func_800A5C54, 0, 13, (s32)D_800A6650,
#if VERSION_US
    0x10B0006,
#elif VERSION_EU
    0x1120006,
#endif
    0, 0, 14, (s32)D_800A66A8,
#if VERSION_US
    0x10B0007,
#elif VERSION_EU
    0x1120007,
#endif
    0, 0, 20, (s32)D_800A6724,
#if VERSION_US
    0x10B0008,
#elif VERSION_EU
    0x1120008,
#endif
    0, 0, 30, (s32)D_800A6788,
#if VERSION_US
    0x10B0009,
#elif VERSION_EU
    0x1120009,
#endif
    0, 0, 58, (s32)D_800A67F4,
#if VERSION_US
    0x10B0012,
#elif VERSION_EU
    0x1120012,
#endif
    0, 0, 310, (s32)D_800A686C,
#if VERSION_US
    0x10B001C,
#elif VERSION_EU
    0x112001C,
#endif
    0, (s32)func_800A636C, 320, (s32)D_800A69EC,
#if VERSION_US
    0x10B001D,
#elif VERSION_EU
    0x112001D,
#endif
    0, 0, 330, (s32)D_800A6A48,
#if VERSION_US
    0x10B001E,
#elif VERSION_EU
    0x112001E,
#endif
    0, 0, 685, (s32)D_800A6AA4,
#if VERSION_US
    0x10B0022,
#elif VERSION_EU
    0x1120022,
#endif
    0, (s32)func_800A63B8, 1510, 0,
#if VERSION_US
    0x10B0035,
#elif VERSION_EU
    0x1120035,
#endif
    (s32)func_800A621C, 0, 1511, (s32)D_800A6DD0,
#if VERSION_US
    0x10B0030,
#elif VERSION_EU
    0x1120030,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
