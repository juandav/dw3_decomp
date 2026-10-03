#include "common.h"
#include "stage.h"
extern StageFuncs D_800A7B1C;
void func_800A60D8();
void func_800A6A30();
extern s32 D_800A7B64[];
extern s32 D_800A7B74[];

/* The text file of the menus */
#define MENU_TEXT 0x158

void func_800A5E40(StageTask *task) {
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

StageTask *func_800A5E88(void *owner) {
    StageTask *task = createTask(func_800A5E40, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7B1C.setup();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag935", func_800A5EE4);

void func_800A5FD8(StageTween *tween, s32 up) {
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

s32 func_800A606C(StageTween *tween) {
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

/* A list of up to eight options that each open a message */
void func_800A60D8(StageListMenu *task, StageListMenuChildren *children) {
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
            D_800A7B1C.start(&task->tweens[0], 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7B1C.update(&task->tweens[0])) {
                for (j = 0; j < task->count; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x8)), j + 1);
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
            D_800A7B1C.start(&task->tweens[1], 1);
            task->substate++;
            break;
        case 4:
            if (D_800A7B1C.update(&task->tweens[1])) {
                children->message->setString(children->message, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x8)), task->cursor + 9);
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
            D_800A7B1C.start(&task->tweens[1], 0);
            children->message->setVisible(children->message, 0);
            task->substate++;
            break;
        case 7:
            if (D_800A7B1C.update(&task->tweens[1])) {
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
            D_800A7B1C.start(&task->tweens[0], 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7B1C.update(&task->tweens[0])) {
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
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), D_800A7B64[task->count - 5], 0xA8, 0x18);
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
    case TASK_KILL:
        break;
    }
}

void *func_800A6A04(void) {
    return createTask(func_800A60D8, 0x84, 0x28);
}

/* A list of up to eight options that each open a message */
void func_800A6A30(StageListMenu *task, StageListMenuChildren *children) {
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
            D_800A7B1C.start(&task->tweens[0], 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7B1C.update(&task->tweens[0])) {
                for (j = 0; j < task->count; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x9)), j + 1);
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
            D_800A7B1C.start(&task->tweens[1], 1);
            task->substate++;
            break;
        case 4:
            if (D_800A7B1C.update(&task->tweens[1])) {
                children->message->setString(children->message, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x9)), task->cursor + 9);
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
            D_800A7B1C.start(&task->tweens[1], 0);
            children->message->setVisible(children->message, 0);
            task->substate++;
            break;
        case 7:
            if (D_800A7B1C.update(&task->tweens[1])) {
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
            D_800A7B1C.start(&task->tweens[0], 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7B1C.update(&task->tweens[0])) {
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
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), D_800A7B74[task->count - 5], 0xA8, 0x18);
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
        D_800A7B1C.start(&task->tweens[0], 1);
        D_800A7B1C.update(&task->tweens[0]);
        break;
    case TASK_KILL:
        break;
    }
}

void *func_800A739C(void) {
    return createTask(func_800A6A30, 0x84, 0x28);
}

void func_800A5EE4();
extern s32 D_800A74B8[];
extern s32 D_800A74C0[];
extern s32 D_800A74CC[];
extern s32 D_800A74D8[];
extern s32 D_800A74E4[];
extern s32 D_800A74F4[];
extern s32 D_800A7500[];
extern s32 D_800A7508[];
extern s32 D_800A7514[];
extern s32 D_800A751C[];
extern s32 D_800A7528[];
extern s32 D_800A7534[];
extern s32 D_800A7540[];
extern s32 D_800A7550[];
extern s32 D_800A755C[];
extern s32 D_800A7564[];
extern s32 D_800A7570[];
extern s32 D_800A7578[];
extern s32 D_800A7584[];
extern s32 D_800A7590[];
extern s32 D_800A759C[];
extern s32 D_800A75AC[];
extern s32 D_800A75B8[];
extern s32 D_800A75C0[];
extern s32 D_800A75CC[];
extern s32 D_800A75D4[];
extern s32 D_800A75DC[];
extern s32 D_800A75E8[];
extern s32 D_800A75F4[];
extern s32 D_800A7600[];
extern s32 D_800A7610[];
extern s32 D_800A761C[];
extern s32 D_800A7624[];
extern s32 D_800A7630[];
extern s32 D_800A7638[];
extern s32 D_800A7640[];
extern s32 D_800A77F0[];
extern s32 D_800A7658[];
extern s32 D_800A77F8[];
extern s32 D_800A7670[];
extern s32 D_800A7800[];
extern s32 D_800A76AC[];
extern s32 D_800A7808[];
extern s32 D_800A76C4[];
extern s32 D_800A7810[];
extern s32 D_800A7700[];
extern s32 D_800A7818[];
extern s32 D_800A7718[];
extern s32 D_800A7754[];
extern s32 D_800A7820[];
extern s32 D_800A776C[];
extern s32 D_800A7828[];
extern s32 D_800A7784[];
extern s32 D_800A7830[];
extern s32 D_800A77C0[];
extern s32 D_800A7838[];
extern s32 D_800A77D8[];
extern s32 D_800A7840[];
extern s32 D_800A7854[];
extern s32 D_800A7868[];
extern s32 D_800A787C[];
extern s32 D_800A7890[];
extern s32 D_800A78A4[];
extern s32 D_800A78B8[];
extern s32 D_800A78CC[];
extern s32 D_800A78E0[];
extern s32 D_800A78F4[];
extern s32 D_800A7908[];
extern s32 D_800A791C[];
extern s32 D_800A7930[];
extern s32 D_800A7944[];

s32 D_800A73C8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1D80140, 0xD80000, 0x1FB0160,
    0x1000180, 0x15901B0, 0x5901C0, 0x1FB0170,
    0x1000180, 0x15D01A0, 0x5D0180, 0x1FA0150,
    0x1000180, 0x15D01A8, 0x5D01A0, 0x1FA0160,
    0x1000180, 0x1710190, 0x710140, 0x1FA0170,
    0x1000180, 0x1710198, 0x710160, 0x1F90140,
    0x1000180, 0x10001B4, 464, 0x1F90150,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A74B8[] = {
    0x19073, 65535,
};
s32 D_800A74C0[] = {
    0x10011, 16, 65535,
};
s32 D_800A74CC[] = {
    17, 3, 65535,
};
s32 D_800A74D8[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A74E4[] = {
    17, 16, 3, 65535,
};
s32 D_800A74F4[] = {
    17, 3, 65535,
};
s32 D_800A7500[] = {
    0x10003, 65535,
};
s32 D_800A7508[] = {
    17, 0x10003, 65535,
};
s32 D_800A7514[] = {
    0x17824, 65535,
};
s32 D_800A751C[] = {
    0x10011, 16, 65535,
};
s32 D_800A7528[] = {
    17, 1, 65535,
};
s32 D_800A7534[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A7540[] = {
    17, 16, 1, 65535,
};
s32 D_800A7550[] = {
    17, 1, 65535,
};
s32 D_800A755C[] = {
    0x10001, 65535,
};
s32 D_800A7564[] = {
    17, 0x10001, 65535,
};
s32 D_800A7570[] = {
    0x1782D, 65535,
};
s32 D_800A7578[] = {
    0x10011, 16, 65535,
};
s32 D_800A7584[] = {
    17, 2, 65535,
};
s32 D_800A7590[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A759C[] = {
    17, 16, 2, 65535,
};
s32 D_800A75AC[] = {
    17, 2, 65535,
};
s32 D_800A75B8[] = {
    0x10002, 65535,
};
s32 D_800A75C0[] = {
    0x10002, 17, 65535,
};
s32 D_800A75CC[] = {
    0x17844, 65535,
};
s32 D_800A75D4[] = {
    0x19072, 65535,
};
s32 D_800A75DC[] = {
    0x10011, 16, 65535,
};
s32 D_800A75E8[] = {
    17, 0, 65535,
};
s32 D_800A75F4[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A7600[] = {
    17, 0, 16, 65535,
};
s32 D_800A7610[] = {
    17, 0, 65535,
};
s32 D_800A761C[] = {
    0x10000, 65535,
};
s32 D_800A7624[] = {
    17, 0x10000, 65535,
};
s32 D_800A7630[] = {
    0x17834, 65535,
};
s32 D_800A7638[] = {
    0x17A43, 65535,
};
s32 D_800A7640[] = {
    0, (s32)D_800A74B8, 67, 0,
    0, 0,
};
s32 D_800A7658[] = {
    0, 0, 81, 0,
    0, 0,
};
s32 D_800A7670[] = {
    (s32)D_800A74C0, (s32)D_800A74CC, 83, (s32)D_800A74D8,
    (s32)D_800A74E4, 84, (s32)D_800A74F4, (s32)D_800A7500,
    81, (s32)D_800A7508, (s32)D_800A7514, 82,
    0, 0, 0,
};
s32 D_800A76AC[] = {
    0, 0, 73, 0,
    0, 0,
};
s32 D_800A76C4[] = {
    (s32)D_800A751C, (s32)D_800A7528, 75, (s32)D_800A7534,
    (s32)D_800A7540, 76, (s32)D_800A7550, (s32)D_800A755C,
    73, (s32)D_800A7564, (s32)D_800A7570, 74,
    0, 0, 0,
};
s32 D_800A7700[] = {
    0, 0, 77, 0,
    0, 0,
};
s32 D_800A7718[] = {
    (s32)D_800A7578, (s32)D_800A7584, 79, (s32)D_800A7590,
    (s32)D_800A759C, 80, (s32)D_800A75AC, (s32)D_800A75B8,
    77, (s32)D_800A75C0, (s32)D_800A75CC, 78,
    0, 0, 0,
};
s32 D_800A7754[] = {
    0, (s32)D_800A75D4, 68, 0,
    0, 0,
};
s32 D_800A776C[] = {
    0, 0, 69, 0,
    0, 0,
};
s32 D_800A7784[] = {
    (s32)D_800A75DC, (s32)D_800A75E8, 71, (s32)D_800A75F4,
    (s32)D_800A7600, 72, (s32)D_800A7610, (s32)D_800A761C,
    69, (s32)D_800A7624, (s32)D_800A7630, 70,
    0, 0, 0,
};
s32 D_800A77C0[] = {
    0, (s32)D_800A7638, 66, 0,
    0, 0,
};
s32 D_800A77D8[] = {
    0, 0, 137, 0,
    0, 0,
};
s32 D_800A77F0[] = {
    33170, 65535,
};
s32 D_800A77F8[] = {
    0x18192, 65535,
};
s32 D_800A7800[] = {
    33170, 65535,
};
s32 D_800A7808[] = {
    0x18192, 65535,
};
s32 D_800A7810[] = {
    33170, 65535,
};
s32 D_800A7818[] = {
    0x18192, 65535,
};
s32 D_800A7820[] = {
    33170, 65535,
};
s32 D_800A7828[] = {
    0x18192, 65535,
};
s32 D_800A7830[] = {
    0x18192, 65535,
};
s32 D_800A7838[] = {
    33170, 65535,
};
s32 D_800A7840[] = {
    0, (s32)D_800A7640, 0x4002E, 0xB000FF,
    3,
};
s32 D_800A7854[] = {
    (s32)D_800A77F0, (s32)D_800A7658, 0x5002F, 0xE700AD,
    7,
};
s32 D_800A7868[] = {
    (s32)D_800A77F8, (s32)D_800A7670, 0x5002F, 0xE700AD,
    7,
};
s32 D_800A787C[] = {
    (s32)D_800A7800, (s32)D_800A76AC, 0x60031, 0xDB00C6,
    7,
};
s32 D_800A7890[] = {
    (s32)D_800A7808, (s32)D_800A76C4, 0x60031, 0xDB00C6,
    7,
};
s32 D_800A78A4[] = {
    (s32)D_800A7810, (s32)D_800A7700, 0x70032, 0x10100E0,
    3,
};
s32 D_800A78B8[] = {
    (s32)D_800A7818, (s32)D_800A7718, 0x70032, 0x10100E0,
    3,
};
s32 D_800A78CC[] = {
    0, (s32)D_800A7754, 0x80033, 0x93015C,
    1,
};
s32 D_800A78E0[] = {
    (s32)D_800A7820, (s32)D_800A776C, 0x90034, 0xF400FA,
    3,
};
s32 D_800A78F4[] = {
    (s32)D_800A7828, (s32)D_800A7784, 0x90034, 0xF400FA,
    3,
};
s32 D_800A7908[] = {
    (s32)D_800A7830, (s32)D_800A77C0, 0xA00CE, 0x93017B,
    7,
};
s32 D_800A791C[] = {
    (s32)D_800A7838, (s32)D_800A77D8, 0xA00CE, 0x93017B,
    7,
};
s32 D_800A7930[] = {
    0, 0, 0xB00DC, 0xA3017B,
    7,
};
s32 D_800A7944[] = {
    0, 0, 0xC00E1, 0x9E015B,
    3,
};
s32 D_800A7958[] = {
    (s32)D_800A7840, (s32)D_800A7854, (s32)D_800A7868, (s32)D_800A787C,
    (s32)D_800A7890, (s32)D_800A78A4, (s32)D_800A78B8, (s32)D_800A78CC,
    (s32)D_800A78E0, (s32)D_800A78F4, (s32)D_800A7908, (s32)D_800A791C,
    (s32)D_800A7930, (s32)D_800A7944, 0,
};
s32 D_800A7994[] = {
    0x6400001, 0x500023B, 0x1AC0008, 75,
    0x10000, 0x23D0640, 0x80300, 0xB00041,
    0, 0x6400001, 0x300023A, 0x1A90008,
    67, 0x10000, 0x1320640, 0x83932,
    0x4B01AC, 0, 0x4400001, 0x300023C,
    0x1D60008, 0xB00095, 0x10000, 1088,
    0, 0xEF0056, 258, 0x4400001,
    1, 0xA00000, 0xF800DC, 0x10000,
    0x20440, 0, 0xCC00C0, 232,
    0x4400001, 3, 0x1400000, 0xE700C9,
    0x10000, 0x40440, 0, 0xB90123,
    209, 0x4400001, 5, 0x1600000,
    0xA80093, 0x10000, 0x60440, 0,
    0x8C0173, 160, 0x4400001, 7,
    0x1500000, 0xA0008B, 0x10000, 0x80440,
    0, 0x830181, 153, 0x4400001,
    9, 0x1400000, 0x990083, 0x10000,
    0xA0440, 0, 0x7B0191, 144,
    0x4400001, 11, 0x1300000, 0x900075,
    0x10000, 0xC0440, 0, 0x9501D0,
    176, 0, 0, 0,
    0, 0,
};
s32 D_800A7AEC[] = {
    65535, 65535, 0x2710001, 0xA001F0,
    7, 0, 65535, 65535,
    0, 0, 0, 0,
};
StageFuncs D_800A7B1C = { func_800A5EE4, func_800A5FD8, func_800A606C };
s32 D_800A7B28[] = {
    1616, 0, 0x1580008, (s32)func_800A6A04,
    0, 1618, 0, 0x1580009,
    (s32)func_800A739C, 0, -1, 0,
    0, 0, 0,
};
s32 D_800A7B64[] = {
    28, 27, 25, 36,
};
s32 D_800A7B74[] = {
    28, 27, 25, 36,
};
