#include "common.h"
#include "stage.h"
extern StageFuncs D_800A79EC;
void func_800A60FC();
void func_800A6A94();
extern s32 D_800A7A34[];
extern s32 D_800A7A44[];

/* The text file of the menus */
#define MENU_TEXT 0x158

void func_800A5E44(StageTask *task) {
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

StageTask *func_800A5E8C(void *owner) {
    StageTask *task = createTask(func_800A5E44, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A79EC.setup();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag924", func_800A5EE8);

void func_800A5FFC(StageTween *tween, s32 up) {
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

s32 func_800A6090(StageTween *tween) {
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
void func_800A60FC(StageListMenu *task, StageListMenuChildren *children) {
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
            D_800A79EC.start(&task->tweens[0], 1);
            task->substate++;
            break;
        case 1:
            if (D_800A79EC.update(&task->tweens[0])) {
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
            D_800A79EC.start(&task->tweens[1], 1);
            task->substate++;
            break;
        case 4:
            if (D_800A79EC.update(&task->tweens[1])) {
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
            D_800A79EC.start(&task->tweens[1], 0);
            children->message->setVisible(children->message, 0);
            task->substate++;
            break;
        case 7:
            if (D_800A79EC.update(&task->tweens[1])) {
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
            D_800A79EC.start(&task->tweens[0], 0);
            task->substate++;
            break;
        case 11:
            if (D_800A79EC.update(&task->tweens[0])) {
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
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), D_800A7A34[task->count - 5], 0xA8, 0x18);
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
        D_800A79EC.start(&task->tweens[0], 1);
        D_800A79EC.update(&task->tweens[0]);
        break;
    case TASK_KILL:
        break;
    }
}

void *func_800A6A68(void) {
    return createTask(func_800A60FC, 0x84, 0x28);
}

/* A list of up to eight options that each open a message */
void func_800A6A94(StageListMenu *task, StageListMenuChildren *children) {
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
            D_800A79EC.start(&task->tweens[0], 1);
            task->substate++;
            break;
        case 1:
            if (D_800A79EC.update(&task->tweens[0])) {
                for (j = 0; j < task->count; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x2)), j + 1);
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
            D_800A79EC.start(&task->tweens[1], 1);
            task->substate++;
            break;
        case 4:
            if (D_800A79EC.update(&task->tweens[1])) {
                children->message->setString(children->message, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x2)), task->cursor + 9);
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
            D_800A79EC.start(&task->tweens[1], 0);
            children->message->setVisible(children->message, 0);
            task->substate++;
            break;
        case 7:
            if (D_800A79EC.update(&task->tweens[1])) {
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
            D_800A79EC.start(&task->tweens[0], 0);
            task->substate++;
            break;
        case 11:
            if (D_800A79EC.update(&task->tweens[0])) {
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
            drawer.draw(FILE_CACHE.getEntry(MENU_SPRITES), D_800A7A44[task->count - 5], 0xA8, 0x18);
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
        D_800A79EC.start(&task->tweens[0], 1);
        D_800A79EC.update(&task->tweens[0]);
        break;
    case TASK_KILL:
        break;
    }
}

void *func_800A7400(void) {
    return createTask(func_800A6A94, 0x84, 0x28);
}

void func_800A5EE8();
extern s32 D_800A74FC[];
extern s32 D_800A7504[];
extern s32 D_800A750C[];
extern s32 D_800A7514[];
extern s32 D_800A752C[];
extern s32 D_800A7544[];
extern s32 D_800A755C[];
extern s32 D_800A7574[];
extern s32 D_800A7588[];
extern s32 D_800A759C[];
extern s32 D_800A75B0[];
extern s32 D_800A75C4[];
extern s32 D_800A75D8[];
extern s32 D_800A75EC[];

s32 D_800A742C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1780166, 0x780098, 0x1F80150,
    0x1000140, 0x178016E, 0x7800B8, 0x1F80160,
    0x1000140, 0x1780176, 0x7800D8, 0x1F80170,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0x1000140, 0x1660152, 0x660048, 0x1F70150,
    0x1000140, 0x17E0140, 0x7E0000, 0x1F70160,
};
s32 D_800A74FC[] = {
    0x1906E, 65535,
};
s32 D_800A7504[] = {
    0x1906D, 65535,
};
s32 D_800A750C[] = {
    0x17C00, 65535,
};
s32 D_800A7514[] = {
    0, (s32)D_800A74FC, 35, 0,
    0, 0,
};
s32 D_800A752C[] = {
    0, (s32)D_800A7504, 34, 0,
    0, 0,
};
s32 D_800A7544[] = {
    0, (s32)D_800A750C, 36, 0,
    0, 0,
};
s32 D_800A755C[] = {
    0, 0, 37, 0,
    0, 0,
};
s32 D_800A7574[] = {
    0, (s32)D_800A7514, 0x40020, 0xE800DC,
    1,
};
s32 D_800A7588[] = {
    0, (s32)D_800A752C, 0x50024, 0xD700BB,
    1,
};
s32 D_800A759C[] = {
    0, 0, 0x60059, 0xD9012C,
    5,
};
s32 D_800A75B0[] = {
    0, 0, 0x70070, 0xF100CA,
    1,
};
s32 D_800A75C4[] = {
    0, 0, 0x80071, 0xE000A9,
    1,
};
s32 D_800A75D8[] = {
    0, (s32)D_800A7544, 0x900FE, 0xF8018F,
    1,
};
s32 D_800A75EC[] = {
    0, (s32)D_800A755C, 0xA0177, 0x1070041,
    1,
};
s32 D_800A7600[] = {
    (s32)D_800A7574, (s32)D_800A7588, (s32)D_800A759C, (s32)D_800A75B0,
    (s32)D_800A75C4, (s32)D_800A75D8, (s32)D_800A75EC, 0,
};
s32 D_800A7620[] = {
    0x2400001, 0x2000245, 0x178000A, 237,
    0x10000, 0x50240, 0, 0x1150170,
    0, 0x2400001, 6, 0,
    204, 0x10000, 0x2460240, 0x40100,
    0xC50026, 0, 0x6400001, 0x241F011F,
    0x6E0008, 341, 0x10000, 0x11F0640,
    0x8241F, 0x9500C6, 0, 0x6400001,
    0x241F011F, 0xDD0008, 148, 0x10000,
    0x11F0640, 0x8241F, 0x9500EB, 0,
    0x6400001, 0x241F011F, 0xF90008, 297,
    0x10000, 0x11F0640, 0x8241F, 0xA8010F,
    0, 0x6400001, 0x241F011F, 0x18E0008,
    350, 0x10000, 0x1250640, 0x82A25,
    0x14D0066, 0, 0x6400001, 0x2A250125,
    0xC80008, 134, 0x10000, 0x1250640,
    0x82A25, 0x9100D5, 0, 0x6400001,
    0x2A250125, 0xF20008, 167, 0x10000,
    0x1250640, 0x82A25, 0xE600F8, 0,
    0x6400001, 0x2A250125, 0xFE0008, 280,
    0x10000, 0x1250640, 0x82A25, 0x990109,
    0, 0x6400001, 0x2A250125, 0x1870008,
    343, 0x10000, 0x2B0640, 0,
    0x9700D5, 0, 0x6400001, 43,
    0xF80000, 286, 0x10000, 0x2C0640,
    0, 0x1480068, 0, 0x6400001,
    44, 0xC50000, 141, 0x10000,
    0x2C0640, 0, 0x9E0108, 0,
    0x6400001, 45, 0xEC0000, 159,
    0x10000, 0x2D0640, 0, 0x1570187,
    0, 0x6400001, 0x39320132, 0x13E000E,
    172, 0x10000, 0x12F0640, 0x4312F,
    0xC10131, 0, 0x6400001, 0x3F3B013B,
    0x1620008, 209, 0x10000, 0x2400640,
    0x80900, 0xD90150, 0, 0x6400001,
    0x2000241, 0x1480010, 232, 0x64010000,
    0x20640, 0, 0xBA004F, 0,
    0x6400001, 0x2000242, 0x880006, 185,
    0x10000, 0x2430640, 0x100200, 0xE70132,
    0, 0x6400001, 0x2000244, 0x141000A,
    223, 0x10000, 0x2470640, 0x40100,
    0x7B008C, 0, 0x6400001, 0x1000248,
    0x1330004, 122, 0x10000, 0x2490640,
    0x40100, 0x90015A, 0, 0xA400001,
    0x4C4A014A, 0x111000A, 297, 0x10000,
    0x1560A40, 0xA5856, 0x12C00D7, 0,
    0xA400001, 0x58560156, 0x170000A, 358,
    0x10000, 0x1590A40, 0xA5B59, 0x15B005C,
    0, 0xA400001, 0x5B590159, 0x87000A,
    312, 0x10000, 0x1590A40, 0xA5B59,
    0x1770096, 0, 0xA400001, 0x5B590159,
    0x1A2000A, 326, 0x10000, 1088,
    0, 0x11F008F, 340, 0x4400001,
    1, 0x1460000, 0x1540120, 0x10000,
    0x40440, 0, 0xF0018E, 263,
    0x4400001, 3, 0x210000, 0xEF00C9,
    0, 0, 0, 0,
    0,
};
s32 D_800A79A4[] = {
    65535, 65535, 0x2730001, 0x24C02C8,
    0x640003, 0, 65535, 65535,
    0x2700001, 0x2000410, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
StageFuncs D_800A79EC = { func_800A5EE8, func_800A5FFC, func_800A6090 };
s32 D_800A79F8[] = {
    1602, 0, 0x1580001, (s32)func_800A6A68,
    0, 1604, 0, 0x1580002,
    (s32)func_800A7400, 0, -1, 0,
    0, 0, 0,
};
s32 D_800A7A34[] = {
    28, 27, 25, 36,
};
s32 D_800A7A44[] = {
    28, 27, 25, 36,
};
