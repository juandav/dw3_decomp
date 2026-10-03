#include "common.h"
#include "stage.h"
void func_800A58C8();
void func_800A5300();
void func_800A4D38();
extern StageFuncs D_800A7010;
void func_800A5E90();

/* The text file of the menus, which the versions number differently */
#if VERSION_US
#define MENU_TEXT 0x10C
#elif VERSION_EU
#define MENU_TEXT 0x112
#endif

/* A two-option menu: creates the event object of the chosen option */
void func_800A4D38(StageMenu *task, StageMenuChildren *children) {
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
            D_800A7010.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7010.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x36)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x36)), 1);
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
            children->event = func_80084B80(task->cursor == 0 ? 0x35 : 0x5E9);
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
            D_800A7010.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7010.update(&task->tween)) {
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

void *func_800A52D4(void) {
    return createTask(func_800A4D38, 0x64, 0x14);
}

/* A two-option menu: creates the event object of the chosen option */
void func_800A5300(StageMenu *task, StageMenuChildren *children) {
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
            D_800A7010.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7010.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x37)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x37)), 1);
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
            children->event = func_80084B80(task->cursor == 0 ? 0x37 : 0x5EB);
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
            D_800A7010.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7010.update(&task->tween)) {
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

void *func_800A589C(void) {
    return createTask(func_800A5300, 0x64, 0x14);
}

/* A two-option menu: creates the event object of the chosen option */
void func_800A58C8(StageMenu *task, StageMenuChildren *children) {
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
            D_800A7010.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7010.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x38)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x38)), 1);
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
            children->event = func_80084B80(task->cursor == 0 ? 0x38 : 0x5ED);
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
            D_800A7010.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7010.update(&task->tween)) {
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

void *func_800A5E64(void) {
    return createTask(func_800A58C8, 0x64, 0x14);
}

void func_800A5E90(StageTask *task) {
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

StageTask *func_800A5ED8(void *owner) {
    StageTask *task = createTask(func_800A5E90, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7010.setup();
    return task;
}

/* the color the setup copies to D_800990B4.unk38 */
const CVECTOR D_800A4D34 = { 0x54, 0x67, 0x96, 0 };

extern s32 D_800A6C44[];
extern s32 D_800A6FC8[];
extern s32 D_800A63DC[];
extern s32 D_800A6BC4[];
extern s32 D_800A701C[];
#if VERSION_US
#define STAGE_TEXT 0xF0
#define STAGE_FILE 0x18F
#define STAGE_ARCHIVE 0x2C7
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE8)
#define STAGE_FILE 0x19D
#define STAGE_ARCHIVE 0x2D6
#endif
void func_800A5F34(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16 | 1;
    D_800990B4.unk10 = D_800A6C44;
    D_800990B4.unk14 = D_800A6FC8;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0x10200, 0x15700};
    D_800990B4.unk28 = D_800A63DC;
    D_800990B4.unk3C = 0x33;
    D_800990B4.unk40 = 0x60CC0000;
    D_800990B4.unk4C = D_800A6BC4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4D34;
    D_800990B4.events = D_800A701C;
    D_8009A70C.setFile(0, STAGE_FILE << 16);
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

void func_800A608C(StageTween *tween, s32 up) {
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

s32 func_800A6120(StageTween *tween) {
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

void func_800A5F34();
extern s32 D_800A651C[];
extern s32 D_800A6524[];
extern s32 D_800A652C[];
extern s32 D_800A6538[];
extern s32 D_800A6540[];
extern s32 D_800A654C[];
extern s32 D_800A6554[];
extern s32 D_800A655C[];
extern s32 D_800A6564[];
extern s32 D_800A656C[];
extern s32 D_800A6574[];
extern s32 D_800A657C[];
extern s32 D_800A6584[];
extern s32 D_800A658C[];
extern s32 D_800A6594[];
extern s32 D_800A659C[];
extern s32 D_800A65A4[];
extern s32 D_800A65AC[];
extern s32 D_800A65B4[];
extern s32 D_800A65BC[];
extern s32 D_800A65C4[];
extern s32 D_800A65CC[];
extern s32 D_800A65D4[];
extern s32 D_800A65DC[];
extern s32 D_800A65E4[];
extern s32 D_800A65EC[];
extern s32 D_800A65F4[];
extern s32 D_800A6854[];
extern s32 D_800A65FC[];
extern s32 D_800A6860[];
extern s32 D_800A662C[];
extern s32 D_800A6868[];
extern s32 D_800A6650[];
extern s32 D_800A6870[];
extern s32 D_800A6674[];
extern s32 D_800A687C[];
extern s32 D_800A6698[];
extern s32 D_800A6884[];
extern s32 D_800A66B0[];
extern s32 D_800A688C[];
extern s32 D_800A66C8[];
extern s32 D_800A6894[];
extern s32 D_800A66E0[];
extern s32 D_800A689C[];
extern s32 D_800A66F8[];
extern s32 D_800A68A4[];
extern s32 D_800A6710[];
extern s32 D_800A68AC[];
extern s32 D_800A6728[];
extern s32 D_800A68B4[];
extern s32 D_800A6740[];
extern s32 D_800A68BC[];
extern s32 D_800A6758[];
extern s32 D_800A68C4[];
extern s32 D_800A6770[];
extern s32 D_800A68CC[];
extern s32 D_800A6788[];
extern s32 D_800A68D4[];
extern s32 D_800A67A0[];
extern s32 D_800A68DC[];
extern s32 D_800A67B8[];
extern s32 D_800A68E8[];
extern s32 D_800A67DC[];
extern s32 D_800A68F0[];
extern s32 D_800A68F8[];
extern s32 D_800A6900[];
extern s32 D_800A6908[];
extern s32 D_800A6910[];
extern s32 D_800A6918[];
extern s32 D_800A6920[];
extern s32 D_800A67F4[];
extern s32 D_800A6928[];
extern s32 D_800A680C[];
extern s32 D_800A6930[];
extern s32 D_800A6824[];
extern s32 D_800A6938[];
extern s32 D_800A6940[];
extern s32 D_800A683C[];
extern s32 D_800A6948[];
extern s32 D_800A6950[];
extern s32 D_800A6958[];
extern s32 D_800A696C[];
extern s32 D_800A6980[];
extern s32 D_800A6994[];
extern s32 D_800A69A8[];
extern s32 D_800A69BC[];
extern s32 D_800A69D0[];
extern s32 D_800A69E4[];
extern s32 D_800A69F8[];
extern s32 D_800A6A0C[];
extern s32 D_800A6A20[];
extern s32 D_800A6A34[];
extern s32 D_800A6A48[];
extern s32 D_800A6A5C[];
extern s32 D_800A6A70[];
extern s32 D_800A6A84[];
extern s32 D_800A6A98[];
extern s32 D_800A6AAC[];
extern s32 D_800A6AC0[];
extern s32 D_800A6AD4[];
extern s32 D_800A6AE8[];
extern s32 D_800A6AFC[];
extern s32 D_800A6B10[];
extern s32 D_800A6B24[];
extern s32 D_800A6B38[];
extern s32 D_800A6B4C[];
extern s32 D_800A6B60[];
extern s32 D_800A6B74[];
extern s32 D_800A6B88[];
extern s32 D_800A6B9C[];
extern s32 D_800A6BB0[];
extern s32 D_800A618C[];
extern s32 D_800A6214[];
extern s32 D_800A6294[];
extern s32 D_800A630C[];
extern s32 D_800A6394[];
extern s32 D_800A63AC[];
extern s32 D_800A63C4[];

s32 D_800A618C[] = {
    0x1E0300, 0x1E0300, 512, 0x240001,
    0x3010002, 0x1E0300, 0x32D0101, 0x20338,
    0x1E0300, 512, 0x20002, 0x3010004,
    0x1E0300, 512, 0x20003, 0x3010004,
    0x1E0300, 512, 0x200004, 0x3010004,
    0x1E0300, 512, 0x20005, 0x3010004,
    0x1E0300, 0x32D0101, 0x20339, 0x1E0300,
    0x1E0300, 512, 0x240007, 0x3010002,
    0x1E0300,
#if VERSION_US
    0x3E00000,
#elif VERSION_EU
    0,
#endif
};
s32 D_800A6214[] = {
    0x20102, 0xF800BA, 0x1000005, 0xDC0020,
    0x10100E8, 0x10020, 0x1010001, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000005,
    0x200001E, 0x10000, 0x20020, 0x3000301,
    0x101001E, 0x338032D, 0x3000002, 0x200001E,
    0x20000, 0x4032D, 0x3000301, 0x101001E,
    0x339032D, 0x3000002, 0x300001E, 0x200001E,
    0x30000, 0x20020, 0x3000301, 30,
};
s32 D_800A6294[] = {
    0x1E0300, 0x1E0300, 512, 0x200001,
    0x3010002, 0x1E0300, 0x32D0101, 0x20338,
    0x1E0300, 512, 0x20002, 0x3010004,
    0x1E0300, 512, 0x200003, 0x3010004,
    0x1E0300, 512, 0x20004, 0x3010004,
    0x1E0300, 0x32D0101, 0x20339, 0x1E0300,
    0x1E0300, 512, 0x200005, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A630C[] = {
    0x1E0300, 0x1E0300, 512, 0x200001,
    0x3010002, 0x1E0300, 0x32D0101, 0x20338,
    0x1E0300, 512, 0x20002, 0x3010004,
    0x1E0300, 512, 0x200003, 0x3010004,
    0x1E0300, 512, 0x20004, 0x3010004,
    0x1E0300, 512, 0x20005, 0x3010004,
    0x1E0300, 0x32D0101, 0x20339, 0x1E0300,
    0x1E0300, 512, 0x200006, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A6394[] = {
    0x3C0300, 512, 0x240001, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A63AC[] = {
    0x3C0300, 512, 0x200001, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A63C4[] = {
    0x3C0300, 512, 0x200001, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A63DC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x178016E, 0x7800B8, 0x1F70150,
    0x1000140, 0x1780176, 0x7800D8, 0x1F70160,
    0x1000140, 0x17E0140, 0x7E0000, 0x1F70170,
    0x1000140, 0x1800160, 0x800080, 0x1F60150,
    0x1000140, 0x17E0148, 0x7E0020, 0x1F60160,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0x1000140, 0x19E0150, 0x9E0040, 0x1F60170,
    0x1000140, 0x1A00158, 0xA00060, 0x1F50140,
    0x1000140, 0x1A00166, 0xA00098, 0x1F50150,
    0x1000140, 0x1A0016E, 0xA000B8, 0x1F50160,
    0x1000140, 0x1A00176, 0xA000D8, 0x1F50170,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A651C[] = {
    6662, 65535,
};
s32 D_800A6524[] = {
    0x11A06, 65535,
};
s32 D_800A652C[] = {
    0x11A06, 28685, 65535,
};
s32 D_800A6538[] = {
    0x19007, 65535,
};
s32 D_800A6540[] = {
    0x11A06, 0x1700D, 65535,
};
s32 D_800A654C[] = {
    0x19008, 65535,
};
s32 D_800A6554[] = {
    28685, 65535,
};
s32 D_800A655C[] = {
    0x19007, 65535,
};
s32 D_800A6564[] = {
    0x1700D, 65535,
};
s32 D_800A656C[] = {
    0x19008, 65535,
};
s32 D_800A6574[] = {
    28685, 65535,
};
s32 D_800A657C[] = {
    0x19007, 65535,
};
s32 D_800A6584[] = {
    0x1700D, 65535,
};
s32 D_800A658C[] = {
    0x19008, 65535,
};
s32 D_800A6594[] = {
    6663, 65535,
};
s32 D_800A659C[] = {
    0x11A07, 65535,
};
s32 D_800A65A4[] = {
    0x11A07, 65535,
};
s32 D_800A65AC[] = {
    0x19005, 65535,
};
s32 D_800A65B4[] = {
    0x19005, 65535,
};
s32 D_800A65BC[] = {
    28685, 65535,
};
s32 D_800A65C4[] = {
    0x19005, 65535,
};
s32 D_800A65CC[] = {
    6660, 65535,
};
s32 D_800A65D4[] = {
    0x11A04, 65535,
};
s32 D_800A65DC[] = {
    0x11A04, 65535,
};
s32 D_800A65E4[] = {
    0x17C00, 65535,
};
s32 D_800A65EC[] = {
    0x17C00, 65535,
};
s32 D_800A65F4[] = {
    0x17C00, 65535,
};
s32 D_800A65FC[] = {
    (s32)D_800A651C, (s32)D_800A6524, 2, (s32)D_800A652C,
    (s32)D_800A6538, 1055, (s32)D_800A6540, (s32)D_800A654C,
    1055, 0, 0, 0,
};
s32 D_800A662C[] = {
    (s32)D_800A6554, (s32)D_800A655C, 1060, (s32)D_800A6564,
    (s32)D_800A656C, 1060, 0, 0,
    0,
};
s32 D_800A6650[] = {
    (s32)D_800A6574, (s32)D_800A657C, 1055, (s32)D_800A6584,
    (s32)D_800A658C, 1055, 0, 0,
    0,
};
s32 D_800A6674[] = {
    (s32)D_800A6594, (s32)D_800A659C, 3, (s32)D_800A65A4,
    (s32)D_800A65AC, 1056, 0, 0,
    0,
};
s32 D_800A6698[] = {
    0, (s32)D_800A65B4, 1061, 0,
    0, 0,
};
s32 D_800A66B0[] = {
    (s32)D_800A65BC, (s32)D_800A65C4, 1056, 0,
    0, 0,
};
s32 D_800A66C8[] = {
    0, 0, 1, 0,
    0, 0,
};
s32 D_800A66E0[] = {
    0, 0, 408, 0,
    0, 0,
};
s32 D_800A66F8[] = {
    0, 0, 399, 0,
    0, 0,
};
s32 D_800A6710[] = {
    0, 0, 400, 0,
    0, 0,
};
s32 D_800A6728[] = {
    0, 0, 401, 0,
    0, 0,
};
s32 D_800A6740[] = {
    0, 0, 402, 0,
    0, 0,
};
s32 D_800A6758[] = {
    0, 0, 403, 0,
    0, 0,
};
s32 D_800A6770[] = {
    0, 0, 404, 0,
    0, 0,
};
s32 D_800A6788[] = {
    0, 0, 405, 0,
    0, 0,
};
s32 D_800A67A0[] = {
    0, 0, 406, 0,
    0, 0,
};
s32 D_800A67B8[] = {
    (s32)D_800A65CC, (s32)D_800A65D4, 4, (s32)D_800A65DC,
    (s32)D_800A65E4, 241, 0, 0,
    0,
};
s32 D_800A67DC[] = {
    0, (s32)D_800A65EC, 1062, 0,
    0, 0,
};
s32 D_800A67F4[] = {
    0, 0, 1057, 0,
    0, 0,
};
s32 D_800A680C[] = {
    0, 0, 1058, 0,
    0, 0,
};
s32 D_800A6824[] = {
    0, (s32)D_800A65F4, 1059, 0,
    0, 0,
};
s32 D_800A683C[] = {
    0, 0, 407, 0,
    0, 0,
};
s32 D_800A6854[] = {
    0x17022, 24598, 65535,
};
s32 D_800A6860[] = {
    0x16016, 65535,
};
s32 D_800A6868[] = {
    0x1602B, 65535,
};
s32 D_800A6870[] = {
    24598, 0x17022, 65535,
};
s32 D_800A687C[] = {
    0x16016, 65535,
};
s32 D_800A6884[] = {
    0x1602B, 65535,
};
s32 D_800A688C[] = {
    0x16004, 65535,
};
s32 D_800A6894[] = {
    0x1602B, 65535,
};
s32 D_800A689C[] = {
    0x17015, 65535,
};
s32 D_800A68A4[] = {
    0x1600C, 65535,
};
s32 D_800A68AC[] = {
    0x1600E, 65535,
};
s32 D_800A68B4[] = {
    0x17016, 65535,
};
s32 D_800A68BC[] = {
    0x16016, 65535,
};
s32 D_800A68C4[] = {
    0x17018, 65535,
};
s32 D_800A68CC[] = {
    0x17019, 65535,
};
s32 D_800A68D4[] = {
    0x16026, 65535,
};
s32 D_800A68DC[] = {
    24598, 0x17022, 65535,
};
s32 D_800A68E8[] = {
    0x1602B, 65535,
};
s32 D_800A68F0[] = {
    0x1701E, 65535,
};
s32 D_800A68F8[] = {
    0x1602B, 65535,
};
s32 D_800A6900[] = {
    0x17022, 65535,
};
s32 D_800A6908[] = {
    0x1602B, 65535,
};
s32 D_800A6910[] = {
    0x17022, 65535,
};
s32 D_800A6918[] = {
    0x1602B, 65535,
};
s32 D_800A6920[] = {
    0x1701A, 65535,
};
s32 D_800A6928[] = {
    0x1701A, 65535,
};
s32 D_800A6930[] = {
    0x1701A, 65535,
};
s32 D_800A6938[] = {
    0x1701A, 65535,
};
s32 D_800A6940[] = {
    0x1701A, 65535,
};
s32 D_800A6948[] = {
    0x1701A, 65535,
};
s32 D_800A6950[] = {
    0x1701A, 65535,
};
s32 D_800A6958[] = {
    (s32)D_800A6854, (s32)D_800A65FC, 0x40020, 0xD700BB,
    1,
};
s32 D_800A696C[] = {
    (s32)D_800A6860, (s32)D_800A662C, 0x40020, 0xD700BB,
    1,
};
s32 D_800A6980[] = {
    (s32)D_800A6868, (s32)D_800A6650, 0x40020, 0xD700BB,
    1,
};
s32 D_800A6994[] = {
    (s32)D_800A6870, (s32)D_800A6674, 0x50024, 0xE800DC,
    1,
};
s32 D_800A69A8[] = {
    (s32)D_800A687C, (s32)D_800A6698, 0x50024, 0xE800DC,
    1,
};
s32 D_800A69BC[] = {
    (s32)D_800A6884, (s32)D_800A66B0, 0x50024, 0xE800DC,
    1,
};
s32 D_800A69D0[] = {
    (s32)D_800A688C, (s32)D_800A66C8, 0x60032, 0x1070041,
    7,
};
s32 D_800A69E4[] = {
    (s32)D_800A6894, (s32)D_800A66E0, 0x60032, 0x1070041,
    7,
};
s32 D_800A69F8[] = {
    (s32)D_800A689C, (s32)D_800A66F8, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A0C[] = {
    (s32)D_800A68A4, (s32)D_800A6710, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A20[] = {
    (s32)D_800A68AC, (s32)D_800A6728, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A34[] = {
    (s32)D_800A68B4, (s32)D_800A6740, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A48[] = {
    (s32)D_800A68BC, (s32)D_800A6758, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A5C[] = {
    (s32)D_800A68C4, (s32)D_800A6770, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A70[] = {
    (s32)D_800A68CC, (s32)D_800A6788, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A84[] = {
    (s32)D_800A68D4, (s32)D_800A67A0, 0x60032, 0x1070041,
    7,
};
s32 D_800A6A98[] = {
    (s32)D_800A68DC, (s32)D_800A67B8, 0x70043, 0xF8018F,
    1,
};
s32 D_800A6AAC[] = {
    (s32)D_800A68E8, (s32)D_800A67DC, 0x70043, 0xF8018F,
    1,
};
s32 D_800A6AC0[] = {
    (s32)D_800A68F0, 0, 0x80059, 0xD9012C,
    5,
};
s32 D_800A6AD4[] = {
    (s32)D_800A68F8, 0, 0x80059, 0xD9012C,
    5,
};
s32 D_800A6AE8[] = {
    (s32)D_800A6900, 0, 0x90070, 0xE000A9,
    0,
};
s32 D_800A6AFC[] = {
    (s32)D_800A6908, 0, 0x90070, 0xE000A9,
    0,
};
s32 D_800A6B10[] = {
    (s32)D_800A6910, 0, 0xA0071, 0xF100CA,
    0,
};
s32 D_800A6B24[] = {
    (s32)D_800A6918, 0, 0xA0071, 0xF100CA,
    0,
};
s32 D_800A6B38[] = {
    (s32)D_800A6920, (s32)D_800A67F4, 0xB009D, 0xD700BB,
    1,
};
s32 D_800A6B4C[] = {
    (s32)D_800A6928, (s32)D_800A680C, 0xC009E, 0xE800DC,
    1,
};
s32 D_800A6B60[] = {
    (s32)D_800A6930, (s32)D_800A6824, 0xD009F, 0xF8018F,
    1,
};
s32 D_800A6B74[] = {
    (s32)D_800A6938, 0, 0xE00A0, 0xD9012C,
    5,
};
s32 D_800A6B88[] = {
    (s32)D_800A6940, (s32)D_800A683C, 0xF00A1, 0x1070041,
    7,
};
s32 D_800A6B9C[] = {
    (s32)D_800A6948, 0, 0x10010E, 0xE000A9,
    0,
};
s32 D_800A6BB0[] = {
    (s32)D_800A6950, 0, 0x11010F, 0xF100CA,
    0,
};
s32 D_800A6BC4[] = {
    (s32)D_800A6958, (s32)D_800A696C, (s32)D_800A6980, (s32)D_800A6994,
    (s32)D_800A69A8, (s32)D_800A69BC, (s32)D_800A69D0, (s32)D_800A69E4,
    (s32)D_800A69F8, (s32)D_800A6A0C, (s32)D_800A6A20, (s32)D_800A6A34,
    (s32)D_800A6A48, (s32)D_800A6A5C, (s32)D_800A6A70, (s32)D_800A6A84,
    (s32)D_800A6A98, (s32)D_800A6AAC, (s32)D_800A6AC0, (s32)D_800A6AD4,
    (s32)D_800A6AE8, (s32)D_800A6AFC, (s32)D_800A6B10, (s32)D_800A6B24,
    (s32)D_800A6B38, (s32)D_800A6B4C, (s32)D_800A6B60, (s32)D_800A6B74,
    (s32)D_800A6B88, (s32)D_800A6B9C, (s32)D_800A6BB0, 0,
};
s32 D_800A6C44[] = {
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
s32 D_800A6FC8[] = {
    65535, 65535, 0x2030001, 0x24C02C8,
    0x640003, 0, 65535, 65535,
    0x2000001, 0x2000410, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
StageFuncs D_800A7010 = { func_800A5F34, func_800A608C, func_800A6120 };
s32 D_800A701C[] = {
    53, (s32)D_800A618C,
#if VERSION_US
    0x10B000D,
#elif VERSION_EU
    0x112000D,
#endif
    0, 0, 54, (s32)D_800A6214,
#if VERSION_US
    0x10B000E,
#elif VERSION_EU
    0x112000E,
#endif
    0, 0, 55, (s32)D_800A6294,
#if VERSION_US
    0x10B000F,
#elif VERSION_EU
    0x112000F,
#endif
    0, 0, 56, (s32)D_800A630C,
#if VERSION_US
    0x10B0010,
#elif VERSION_EU
    0x1120010,
#endif
    0, 0, 1512, 0,
#if VERSION_US
    0x10B0036,
#elif VERSION_EU
    0x1120036,
#endif
    (s32)func_800A52D4, 0, 1513, (s32)D_800A6394,
#if VERSION_US
    0x10B0031,
#elif VERSION_EU
    0x1120031,
#endif
    0, 0, 1514, 0,
#if VERSION_US
    0x10B0037,
#elif VERSION_EU
    0x1120037,
#endif
    (s32)func_800A589C, 0, 1515, (s32)D_800A63AC,
#if VERSION_US
    0x10B0032,
#elif VERSION_EU
    0x1120032,
#endif
    0, 0, 1516, 0,
#if VERSION_US
    0x10B0038,
#elif VERSION_EU
    0x1120038,
#endif
    (s32)func_800A5E64, 0, 1517, (s32)D_800A63C4,
#if VERSION_US
    0x10B0033,
#elif VERSION_EU
    0x1120033,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
