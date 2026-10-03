#include "common.h"
#include "stage.h"
extern s32 D_800A67DC[];
extern s32 D_800A6404[];
extern u8 D_800A5780[];
extern u8 D_800A6758[];
extern u8 D_800A64D0[];
extern StageFuncs D_800A67D0;
void func_800A529C();
void func_800A53B8();
void func_800A4CD4();

/* The text file of the menus, which the versions number differently */
#if VERSION_US
#define MENU_TEXT 0x10C
#elif VERSION_EU
#define MENU_TEXT 0x112
#endif

/* A two-option menu: creates the event object of the chosen option */
void func_800A4CD4(StageMenu *task, StageMenuChildren *children) {
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
            D_800A67D0.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A67D0.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x39)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x39)), 1);
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
            children->event = func_80084B80(task->cursor == 0 ? 0x39 : 0x5F3);
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
            D_800A67D0.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A67D0.update(&task->tween)) {
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

void *func_800A5270(void) {
    return createTask(func_800A4CD4, 0x64, 0x14);
}

/* Creates the event object while flags 0x7201, 0x8008 and 0x701A are clear */
void func_800A529C(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (FLAGS_00.checkCondition(0x7201, 0) && FLAGS_00.checkCondition(0x8008, 0) && FLAGS_00.checkCondition(0x701A, 0)) {
            children[0] = func_80084B80(0x42);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A535C(void *owner) {
    StageTask *task = createTask(func_800A529C, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A67D0.setup();
    return task;
}

#if VERSION_US
void func_800A53B8(void) {
    D_800990B4.unk44 = 0xCD;
    D_800990B4.unk8 = 0x1A4;
    D_800990B4.unkC = 0x1A50000;
    D_800990B4.unk10 = D_800A64D0;
    D_800990B4.unk14 = D_800A6758;
    D_800990B4.unk1C = 0x3C3;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1BB00;
    D_800990B4.unk30 = 0xF400;
    D_800990B4.unk28 = D_800A5780;
    D_800990B4.unk3C = 8;
    D_800990B4.unk40 = 0x60200000;
    D_800990B4.unk4C = D_800A6404;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A67DC;
    D_8009A70C.setFile(0, 0x1A50002);
    D_8009A70C.setFile(7, 0x1A50001);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag280", func_800A53B8);
#endif

void func_800A54A4(StageTween *tween, s32 up) {
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

s32 func_800A5538(StageTween *tween) {
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

extern s32 D_800A58A0[];
extern s32 D_800A58A8[];
extern s32 D_800A58B0[];
extern s32 D_800A58B8[];
extern s32 D_800A58C4[];
extern s32 D_800A58CC[];
extern s32 D_800A58DC[];
extern s32 D_800A58E8[];
extern s32 D_800A58F8[];
extern s32 D_800A5900[];
extern s32 D_800A5908[];
extern s32 D_800A5914[];
extern s32 D_800A5920[];
extern s32 D_800A592C[];
extern s32 D_800A5934[];
extern s32 D_800A5940[];
extern s32 D_800A594C[];
extern s32 D_800A5E44[];
extern s32 D_800A5958[];
extern s32 D_800A5E54[];
extern s32 D_800A5970[];
extern s32 D_800A5E64[];
extern s32 D_800A5988[];
extern s32 D_800A5E74[];
extern s32 D_800A59A0[];
extern s32 D_800A5E84[];
extern s32 D_800A59B8[];
extern s32 D_800A5E94[];
extern s32 D_800A59D0[];
extern s32 D_800A5EA4[];
extern s32 D_800A59E8[];
extern s32 D_800A5EB4[];
extern s32 D_800A5A00[];
extern s32 D_800A5EC4[];
extern s32 D_800A5A18[];
extern s32 D_800A5ECC[];
extern s32 D_800A5A30[];
extern s32 D_800A5ED4[];
extern s32 D_800A5A48[];
extern s32 D_800A5EDC[];
extern s32 D_800A5A60[];
extern s32 D_800A5EE4[];
extern s32 D_800A5A78[];
extern s32 D_800A5EEC[];
extern s32 D_800A5A90[];
extern s32 D_800A5EF4[];
extern s32 D_800A5AA8[];
extern s32 D_800A5EFC[];
extern s32 D_800A5AC0[];
extern s32 D_800A5F04[];
extern s32 D_800A5AD8[];
extern s32 D_800A5F0C[];
extern s32 D_800A5AF0[];
extern s32 D_800A5F14[];
extern s32 D_800A5B08[];
extern s32 D_800A5F1C[];
extern s32 D_800A5B20[];
extern s32 D_800A5F24[];
extern s32 D_800A5B38[];
extern s32 D_800A5F2C[];
extern s32 D_800A5B50[];
extern s32 D_800A5F34[];
extern s32 D_800A5B68[];
extern s32 D_800A5F3C[];
extern s32 D_800A5B80[];
extern s32 D_800A5F44[];
extern s32 D_800A5B98[];
extern s32 D_800A5F4C[];
extern s32 D_800A5BB0[];
extern s32 D_800A5F54[];
extern s32 D_800A5BC8[];
extern s32 D_800A5F5C[];
extern s32 D_800A5BE0[];
extern s32 D_800A5F64[];
extern s32 D_800A5BF8[];
extern s32 D_800A5F6C[];
extern s32 D_800A5C10[];
extern s32 D_800A5F74[];
extern s32 D_800A5C28[];
extern s32 D_800A5F7C[];
extern s32 D_800A5C40[];
extern s32 D_800A5F84[];
extern s32 D_800A5C58[];
extern s32 D_800A5F8C[];
extern s32 D_800A5C70[];
extern s32 D_800A5F94[];
extern s32 D_800A5C88[];
extern s32 D_800A5F9C[];
extern s32 D_800A5CA0[];
extern s32 D_800A5FA4[];
extern s32 D_800A5CB8[];
extern s32 D_800A5FAC[];
extern s32 D_800A5CD0[];
extern s32 D_800A5FB4[];
extern s32 D_800A5CE8[];
extern s32 D_800A5FBC[];
extern s32 D_800A5D00[];
extern s32 D_800A5FC4[];
extern s32 D_800A5D18[];
extern s32 D_800A5FCC[];
extern s32 D_800A5D30[];
extern s32 D_800A5FD4[];
extern s32 D_800A5D48[];
extern s32 D_800A5FDC[];
extern s32 D_800A5D60[];
extern s32 D_800A5FE4[];
extern s32 D_800A5D9C[];
extern s32 D_800A5FF0[];
extern s32 D_800A5DCC[];
extern s32 D_800A5FFC[];
extern s32 D_800A5DFC[];
extern s32 D_800A6008[];
extern s32 D_800A5E14[];
extern s32 D_800A6014[];
extern s32 D_800A5E2C[];
extern s32 D_800A601C[];
extern s32 D_800A6030[];
extern s32 D_800A6044[];
extern s32 D_800A6058[];
extern s32 D_800A606C[];
extern s32 D_800A6080[];
extern s32 D_800A6094[];
extern s32 D_800A60A8[];
extern s32 D_800A60BC[];
extern s32 D_800A60D0[];
extern s32 D_800A60E4[];
extern s32 D_800A60F8[];
extern s32 D_800A610C[];
extern s32 D_800A6120[];
extern s32 D_800A6134[];
extern s32 D_800A6148[];
extern s32 D_800A615C[];
extern s32 D_800A6170[];
extern s32 D_800A6184[];
extern s32 D_800A6198[];
extern s32 D_800A61AC[];
extern s32 D_800A61C0[];
extern s32 D_800A61D4[];
extern s32 D_800A61E8[];
extern s32 D_800A61FC[];
extern s32 D_800A6210[];
extern s32 D_800A6224[];
extern s32 D_800A6238[];
extern s32 D_800A624C[];
extern s32 D_800A6260[];
extern s32 D_800A6274[];
extern s32 D_800A6288[];
extern s32 D_800A629C[];
extern s32 D_800A62B0[];
extern s32 D_800A62C4[];
extern s32 D_800A62D8[];
extern s32 D_800A62EC[];
extern s32 D_800A6300[];
extern s32 D_800A6314[];
extern s32 D_800A6328[];
extern s32 D_800A633C[];
extern s32 D_800A6350[];
extern s32 D_800A6364[];
extern s32 D_800A6378[];
extern s32 D_800A638C[];
extern s32 D_800A63A0[];
extern s32 D_800A63B4[];
extern s32 D_800A63C8[];
extern s32 D_800A63DC[];
extern s32 D_800A63F0[];
extern s32 D_800A55A4[];
extern s32 D_800A5634[];
extern s32 D_800A56AC[];
extern s32 D_800A574C[];

s32 D_800A55A4[] = {
    0x20102, 0xB00180, 0x1010003, 0x1010B,
    0x1010007, 0x337032D, 0x3020002, 0x3000002,
    0x200001E, 0x10000, 0x2010B, 0x3000301,
    0x101001E, 0x338032D, 0x3000002, 0x200001E,
    0x20000, 0x40002, 0x3000301, 0x200001E,
    0x30000, 0x4010B, 0x3000301, 0x200001E,
    0x40000, 0x40002, 0x3000301, 0x101001E,
    0x339032D, 0x3000002, 0x300001E, 0x200001E,
    0x50000, 0x2010B, 0x3000301, 30,
};
s32 D_800A5634[] = {
    0x20100, 0xF40218, 0x20101, 0x30001,
    0x2D0100, 0xE401F6, 0x2D0101, 0x70001,
    0x1E0300, 0x20102, 0xF10210, 0x3020003,
    0x1010002, 0x10002, 0x3000003, 0x300001E,
    0x200001E, 0x10000, 45, 0x3000301,
    0x101001E, 0x10002, 0x3000007, 0x102001E,
    0x22B0002, 0x700FC, 0x1E0300, 0x2010304,
    0xD80180, 7,
};
s32 D_800A56AC[] = {
    0x20102, 0xD0014F, 0x1000003, 0x1310118,
    0x10100C1, 0x10118, 0x1010007, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000003,
    0x200001E, 0x10000, 0x20118, 0x1010301,
    0x10118, 0x3000007, 0x101001E, 0x10002,
    0x3000005, 0x102001E, 0x1680002, 0x500C4,
    0x20302, 0x20101, 0x10001, 0x1180102,
    0xE00170, 0x3020007, 0x1020118, 0x14F0002,
    0x300D0, 0x1180101, 0x30001, 0x20302,
    0x20101, 0x30001, 0x1E0300, 0,
};
s32 D_800A574C[] = {
    0x20102, 0xB00180, 0x1010003, 0x1010B,
    0x1010007, 0x337032D, 0x3020002, 0x3000002,
    0x200001E, 0x10000, 0x2010B, 0x3000301,
    30,
};
u8 D_800A5780[] = {
    0x00, 0x02, 0x00, 0x01, 0x1C, 0x02, 0xA6, 0x01,
    0x70, 0x00, 0xA6, 0x00, 0x30, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x16, 0x02, 0x38, 0x01,
    0x58, 0x00, 0x38, 0x00, 0x00, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x08, 0x02, 0xBC, 0x01,
    0x20, 0x00, 0xBC, 0x00, 0x10, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x10, 0x02, 0xBC, 0x01,
    0x40, 0x00, 0xBC, 0x00, 0x20, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0xBC, 0x01,
    0x00, 0x00, 0xBC, 0x00, 0x30, 0x02, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x78, 0x01, 0x7A, 0x01,
    0xE0, 0x00, 0x7A, 0x00, 0x60, 0x01, 0xFF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x58, 0x01, 0x82, 0x01,
    0x60, 0x00, 0x82, 0x00, 0x70, 0x01, 0xFF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x70, 0x01, 0x7A, 0x01,
    0xC0, 0x00, 0x7A, 0x00, 0x60, 0x01, 0xFE, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x40, 0x01, 0x82, 0x01,
    0x00, 0x00, 0x82, 0x00, 0x70, 0x01, 0xFE, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x60, 0x01, 0x89, 0x01,
    0x80, 0x00, 0x89, 0x00, 0x40, 0x01, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x68, 0x01, 0x89, 0x01,
    0xA0, 0x00, 0x89, 0x00, 0x50, 0x01, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x58, 0x01, 0xA2, 0x01,
    0x60, 0x00, 0xA2, 0x00, 0x60, 0x01, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x70, 0x01, 0xA2, 0x01,
    0xC0, 0x00, 0xA2, 0x00, 0x70, 0x01, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x48, 0x01, 0x82, 0x01,
    0x20, 0x00, 0x82, 0x00, 0x40, 0x01, 0xFC, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x01, 0x00, 0x01, 0x50, 0x01, 0x82, 0x01,
    0x40, 0x00, 0x82, 0x00, 0x50, 0x01, 0xFC, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x60, 0x01, 0xA9, 0x01,
    0x80, 0x00, 0xA9, 0x00, 0x60, 0x01, 0xFC, 0x01,
};
s32 D_800A58A0[] = {
    0x19000, 65535,
};
s32 D_800A58A8[] = {
    6661, 65535,
};
s32 D_800A58B0[] = {
    0x11A05, 65535,
};
s32 D_800A58B8[] = {
    0x11A05, 29186, 65535,
};
s32 D_800A58C4[] = {
    0x19000, 65535,
};
s32 D_800A58CC[] = {
    0x11A05, 0x17202, 32776, 65535,
};
s32 D_800A58DC[] = {
    0x18008, 0x17013, 65535,
};
s32 D_800A58E8[] = {
    0x11A05, 0x17202, 0x18008, 65535,
};
s32 D_800A58F8[] = {
    0x19000, 65535,
};
s32 D_800A5900[] = {
    32776, 65535,
};
s32 D_800A5908[] = {
    0x18008, 0, 65535,
};
s32 D_800A5914[] = {
    0x19022, 0x10000, 65535,
};
s32 D_800A5920[] = {
    0x18008, 0x10000, 65535,
};
s32 D_800A592C[] = {
    32776, 65535,
};
s32 D_800A5934[] = {
    0, 0x18008, 65535,
};
s32 D_800A5940[] = {
    0x19022, 0x10000, 65535,
};
s32 D_800A594C[] = {
    0x18008, 0x10000, 65535,
};
s32 D_800A5958[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A5970[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A5988[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A59A0[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A59B8[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A59D0[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A59E8[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A5A00[] = {
    0, 0, 138, 0,
    0, 0,
};
s32 D_800A5A18[] = {
    0, 0, 1129, 0,
    0, 0,
};
s32 D_800A5A30[] = {
    0, 0, 1137, 0,
    0, 0,
};
s32 D_800A5A48[] = {
    0, 0, 1130, 0,
    0, 0,
};
s32 D_800A5A60[] = {
    0, 0, 1131, 0,
    0, 0,
};
s32 D_800A5A78[] = {
    0, 0, 1132, 0,
    0, 0,
};
s32 D_800A5A90[] = {
    0, 0, 1133, 0,
    0, 0,
};
s32 D_800A5AA8[] = {
    0, 0, 1139, 0,
    0, 0,
};
s32 D_800A5AC0[] = {
    0, 0, 1134, 0,
    0, 0,
};
s32 D_800A5AD8[] = {
    0, 0, 1135, 0,
    0, 0,
};
s32 D_800A5AF0[] = {
    0, 0, 1136, 0,
    0, 0,
};
s32 D_800A5B08[] = {
    0, 0, 1140, 0,
    0, 0,
};
s32 D_800A5B20[] = {
    0, 0, 1148, 0,
    0, 0,
};
s32 D_800A5B38[] = {
    0, 0, 1141, 0,
    0, 0,
};
s32 D_800A5B50[] = {
    0, 0, 1142, 0,
    0, 0,
};
s32 D_800A5B68[] = {
    0, 0, 1143, 0,
    0, 0,
};
s32 D_800A5B80[] = {
    0, 0, 1144, 0,
    0, 0,
};
s32 D_800A5B98[] = {
    0, 0, 1150, 0,
    0, 0,
};
s32 D_800A5BB0[] = {
    0, 0, 1147, 0,
    0, 0,
};
s32 D_800A5BC8[] = {
    0, 0, 1145, 0,
    0, 0,
};
s32 D_800A5BE0[] = {
    0, 0, 1146, 0,
    0, 0,
};
s32 D_800A5BF8[] = {
    0, 0, 1118, 0,
    0, 0,
};
s32 D_800A5C10[] = {
    0, 0, 1127, 0,
    0, 0,
};
s32 D_800A5C28[] = {
    0, 0, 1119, 0,
    0, 0,
};
s32 D_800A5C40[] = {
    0, 0, 1120, 0,
    0, 0,
};
s32 D_800A5C58[] = {
    0, 0, 1121, 0,
    0, 0,
};
s32 D_800A5C70[] = {
    0, 0, 1122, 0,
    0, 0,
};
s32 D_800A5C88[] = {
    0, 0, 1128, 0,
    0, 0,
};
s32 D_800A5CA0[] = {
    0, 0, 1123, 0,
    0, 0,
};
s32 D_800A5CB8[] = {
    0, 0, 1125, 0,
    0, 0,
};
s32 D_800A5CD0[] = {
    0, 0, 1124, 0,
    0, 0,
};
s32 D_800A5CE8[] = {
    0, 0, 139, 0,
    0, 0,
};
s32 D_800A5D00[] = {
    0, 0, 1126, 0,
    0, 0,
};
s32 D_800A5D18[] = {
    0, 0, 1138, 0,
    0, 0,
};
s32 D_800A5D30[] = {
    0, 0, 1149, 0,
    0, 0,
};
s32 D_800A5D48[] = {
    0, (s32)D_800A58A0, 312, 0,
    0, 0,
};
s32 D_800A5D60[] = {
    (s32)D_800A58A8, (s32)D_800A58B0, 50, (s32)D_800A58B8,
    (s32)D_800A58C4, 312, (s32)D_800A58CC, (s32)D_800A58DC,
    313, (s32)D_800A58E8, (s32)D_800A58F8, 312,
    0, 0, 0,
};
s32 D_800A5D9C[] = {
    (s32)D_800A5900, 0, 163, (s32)D_800A5908,
    (s32)D_800A5914, 162, (s32)D_800A5920, 0,
    164, 0, 0, 0,
};
s32 D_800A5DCC[] = {
    (s32)D_800A592C, 0, 163, (s32)D_800A5934,
    (s32)D_800A5940, 162, (s32)D_800A594C, 0,
    164, 0, 0, 0,
};
s32 D_800A5DFC[] = {
    0, 0, 164, 0,
    0, 0,
};
s32 D_800A5E14[] = {
    0, 0, 164, 0,
    0, 0,
};
s32 D_800A5E2C[] = {
    0, 0, 165, 0,
    0, 0,
};
s32 D_800A5E44[] = {
    0x17022, 32776, 29185, 65535,
};
s32 D_800A5E54[] = {
    0x18008, 0x17022, 29185, 65535,
};
s32 D_800A5E64[] = {
    32776, 0x1602B, 29185, 65535,
};
s32 D_800A5E74[] = {
    0x18008, 0x1602B, 29185, 65535,
};
s32 D_800A5E84[] = {
    0x17022, 32776, 0x17201, 65535,
};
s32 D_800A5E94[] = {
    0x17022, 0x18008, 0x17201, 65535,
};
s32 D_800A5EA4[] = {
    0x1602B, 32776, 0x17201, 65535,
};
s32 D_800A5EB4[] = {
    0x1602B, 0x18008, 0x17201, 65535,
};
s32 D_800A5EC4[] = {
    0x16004, 65535,
};
s32 D_800A5ECC[] = {
    0x16026, 65535,
};
s32 D_800A5ED4[] = {
    0x17015, 65535,
};
s32 D_800A5EDC[] = {
    0x1600C, 65535,
};
s32 D_800A5EE4[] = {
    0x1600E, 65535,
};
s32 D_800A5EEC[] = {
    0x17016, 65535,
};
s32 D_800A5EF4[] = {
    0x1602B, 65535,
};
s32 D_800A5EFC[] = {
    0x16016, 65535,
};
s32 D_800A5F04[] = {
    0x17018, 65535,
};
s32 D_800A5F0C[] = {
    0x17019, 65535,
};
s32 D_800A5F14[] = {
    0x16004, 65535,
};
s32 D_800A5F1C[] = {
    0x16026, 65535,
};
s32 D_800A5F24[] = {
    0x17015, 65535,
};
s32 D_800A5F2C[] = {
    0x1600C, 65535,
};
s32 D_800A5F34[] = {
    0x1600E, 65535,
};
s32 D_800A5F3C[] = {
    0x17016, 65535,
};
s32 D_800A5F44[] = {
    0x1602B, 65535,
};
s32 D_800A5F4C[] = {
    0x17019, 65535,
};
s32 D_800A5F54[] = {
    0x16016, 65535,
};
s32 D_800A5F5C[] = {
    0x17018, 65535,
};
s32 D_800A5F64[] = {
    0x16004, 65535,
};
s32 D_800A5F6C[] = {
    0x16026, 65535,
};
s32 D_800A5F74[] = {
    0x17015, 65535,
};
s32 D_800A5F7C[] = {
    0x1600C, 65535,
};
s32 D_800A5F84[] = {
    0x1600E, 65535,
};
s32 D_800A5F8C[] = {
    0x17016, 65535,
};
s32 D_800A5F94[] = {
    0x1602B, 65535,
};
s32 D_800A5F9C[] = {
    0x16016, 65535,
};
s32 D_800A5FA4[] = {
    0x17019, 65535,
};
s32 D_800A5FAC[] = {
    0x17018, 65535,
};
s32 D_800A5FB4[] = {
    0x1701A, 65535,
};
s32 D_800A5FBC[] = {
    0x1701A, 65535,
};
s32 D_800A5FC4[] = {
    0x1701A, 65535,
};
s32 D_800A5FCC[] = {
    0x1701A, 65535,
};
s32 D_800A5FD4[] = {
    0x18008, 65535,
};
s32 D_800A5FDC[] = {
    32776, 65535,
};
s32 D_800A5FE4[] = {
    0x17022, 32776, 65535,
};
s32 D_800A5FF0[] = {
    0x1602B, 32776, 65535,
};
s32 D_800A5FFC[] = {
    0x18008, 0x17022, 65535,
};
s32 D_800A6008[] = {
    0x18008, 0x1602B, 65535,
};
s32 D_800A6014[] = {
    0x1701A, 65535,
};
s32 D_800A601C[] = {
    (s32)D_800A5E44, (s32)D_800A5958, 0x4002D, 0xE401F6,
    7,
};
s32 D_800A6030[] = {
    (s32)D_800A5E54, (s32)D_800A5970, 0x4002D, 0xF501D7,
    5,
};
s32 D_800A6044[] = {
    (s32)D_800A5E64, (s32)D_800A5988, 0x4002D, 0xE401F6,
    7,
};
s32 D_800A6058[] = {
    (s32)D_800A5E74, (s32)D_800A59A0, 0x4002D, 0xF501D7,
    5,
};
s32 D_800A606C[] = {
    (s32)D_800A5E84, (s32)D_800A59B8, 0x4002D, 0xF501D7,
    5,
};
s32 D_800A6080[] = {
    (s32)D_800A5E94, (s32)D_800A59D0, 0x4002D, 0xF501D7,
    5,
};
s32 D_800A6094[] = {
    (s32)D_800A5EA4, (s32)D_800A59E8, 0x4002D, 0xF501D7,
    5,
};
s32 D_800A60A8[] = {
    (s32)D_800A5EB4, (s32)D_800A5A00, 0x4002D, 0xF501D7,
    5,
};
s32 D_800A60BC[] = {
    (s32)D_800A5EC4, (s32)D_800A5A18, 0x5002E, 0x1280160,
    5,
};
s32 D_800A60D0[] = {
    (s32)D_800A5ECC, (s32)D_800A5A30, 0x5002E, 0x1280160,
    5,
};
s32 D_800A60E4[] = {
    (s32)D_800A5ED4, (s32)D_800A5A48, 0x5002E, 0x1280160,
    5,
};
s32 D_800A60F8[] = {
    (s32)D_800A5EDC, (s32)D_800A5A60, 0x5002E, 0x1280160,
    5,
};
s32 D_800A610C[] = {
    (s32)D_800A5EE4, (s32)D_800A5A78, 0x5002E, 0x1280160,
    5,
};
s32 D_800A6120[] = {
    (s32)D_800A5EEC, (s32)D_800A5A90, 0x5002E, 0x1280160,
    5,
};
s32 D_800A6134[] = {
    (s32)D_800A5EF4, (s32)D_800A5AA8, 0x5002E, 0x1280160,
    5,
};
s32 D_800A6148[] = {
    (s32)D_800A5EFC, (s32)D_800A5AC0, 0x5002E, 0x1280160,
    5,
};
s32 D_800A615C[] = {
    (s32)D_800A5F04, (s32)D_800A5AD8, 0x5002E, 0x1280160,
    5,
};
s32 D_800A6170[] = {
    (s32)D_800A5F0C, (s32)D_800A5AF0, 0x5002E, 0x1280160,
    5,
};
s32 D_800A6184[] = {
    (s32)D_800A5F14, (s32)D_800A5B08, 0x60033, 0x11500D8,
    7,
};
s32 D_800A6198[] = {
    (s32)D_800A5F1C, (s32)D_800A5B20, 0x60033, 0x11500D8,
    7,
};
s32 D_800A61AC[] = {
    (s32)D_800A5F24, (s32)D_800A5B38, 0x60033, 0x11500D8,
    7,
};
s32 D_800A61C0[] = {
    (s32)D_800A5F2C, (s32)D_800A5B50, 0x60033, 0x11500D8,
    7,
};
s32 D_800A61D4[] = {
    (s32)D_800A5F34, (s32)D_800A5B68, 0x60033, 0x11500D8,
    7,
};
s32 D_800A61E8[] = {
    (s32)D_800A5F3C, (s32)D_800A5B80, 0x60033, 0x11500D8,
    7,
};
s32 D_800A61FC[] = {
    (s32)D_800A5F44, (s32)D_800A5B98, 0x60033, 0x11500D8,
    7,
};
s32 D_800A6210[] = {
    (s32)D_800A5F4C, (s32)D_800A5BB0, 0x60033, 0x11500D8,
    7,
};
s32 D_800A6224[] = {
    (s32)D_800A5F54, (s32)D_800A5BC8, 0x60033, 0x11500D8,
    7,
};
s32 D_800A6238[] = {
    (s32)D_800A5F5C, (s32)D_800A5BE0, 0x60033, 0x11500D8,
    7,
};
s32 D_800A624C[] = {
    (s32)D_800A5F64, (s32)D_800A5BF8, 0x70037, 0x12D0108,
    3,
};
s32 D_800A6260[] = {
    (s32)D_800A5F6C, (s32)D_800A5C10, 0x70037, 0x12D0108,
    3,
};
s32 D_800A6274[] = {
    (s32)D_800A5F74, (s32)D_800A5C28, 0x70037, 0x12D0108,
    3,
};
s32 D_800A6288[] = {
    (s32)D_800A5F7C, (s32)D_800A5C40, 0x70037, 0x12D0108,
    3,
};
s32 D_800A629C[] = {
    (s32)D_800A5F84, (s32)D_800A5C58, 0x70037, 0x12D0108,
    3,
};
s32 D_800A62B0[] = {
    (s32)D_800A5F8C, (s32)D_800A5C70, 0x70037, 0x12D0108,
    3,
};
s32 D_800A62C4[] = {
    (s32)D_800A5F94, (s32)D_800A5C88, 0x70037, 0x12D0108,
    3,
};
s32 D_800A62D8[] = {
    (s32)D_800A5F9C, (s32)D_800A5CA0, 0x70037, 0x12D0108,
    3,
};
s32 D_800A62EC[] = {
    (s32)D_800A5FA4, (s32)D_800A5CB8, 0x70037, 0x12D0108,
    3,
};
s32 D_800A6300[] = {
    (s32)D_800A5FAC, (s32)D_800A5CD0, 0x70037, 0x12D0108,
    3,
};
s32 D_800A6314[] = {
    (s32)D_800A5FB4, (s32)D_800A5CE8, 0x8009D, 0xF501D7,
    5,
};
s32 D_800A6328[] = {
    (s32)D_800A5FBC, (s32)D_800A5D00, 0x9009F, 0x12D0108,
    3,
};
s32 D_800A633C[] = {
    (s32)D_800A5FC4, (s32)D_800A5D18, 0xA00A0, 0x1280160,
    5,
};
s32 D_800A6350[] = {
    (s32)D_800A5FCC, (s32)D_800A5D30, 0xB00A1, 0x11500D8,
    7,
};
s32 D_800A6364[] = {
    (s32)D_800A5FD4, (s32)D_800A5D48, 0xC010B, 0xA00161,
    7,
};
s32 D_800A6378[] = {
    (s32)D_800A5FDC, (s32)D_800A5D60, 0xC010B, 0xA00161,
    7,
};
s32 D_800A638C[] = {
    0, 0, 0xD010C, 0xAC0168,
    7,
};
s32 D_800A63A0[] = {
    (s32)D_800A5FE4, (s32)D_800A5D9C, 0xE0118, 0xC10131,
    7,
};
s32 D_800A63B4[] = {
    (s32)D_800A5FF0, (s32)D_800A5DCC, 0xE0118, 0xC10131,
    7,
};
s32 D_800A63C8[] = {
    (s32)D_800A5FFC, (s32)D_800A5DFC, 0xE0118, 0xE00170,
    3,
};
s32 D_800A63DC[] = {
    (s32)D_800A6008, (s32)D_800A5E14, 0xE0118, 0xE00170,
    3,
};
s32 D_800A63F0[] = {
    (s32)D_800A6014, (s32)D_800A5E2C, 0xF0119, 0xE00170,
    3,
};
s32 D_800A6404[] = {
    (s32)D_800A601C, (s32)D_800A6030, (s32)D_800A6044, (s32)D_800A6058,
    (s32)D_800A606C, (s32)D_800A6080, (s32)D_800A6094, (s32)D_800A60A8,
    (s32)D_800A60BC, (s32)D_800A60D0, (s32)D_800A60E4, (s32)D_800A60F8,
    (s32)D_800A610C, (s32)D_800A6120, (s32)D_800A6134, (s32)D_800A6148,
    (s32)D_800A615C, (s32)D_800A6170, (s32)D_800A6184, (s32)D_800A6198,
    (s32)D_800A61AC, (s32)D_800A61C0, (s32)D_800A61D4, (s32)D_800A61E8,
    (s32)D_800A61FC, (s32)D_800A6210, (s32)D_800A6224, (s32)D_800A6238,
    (s32)D_800A624C, (s32)D_800A6260, (s32)D_800A6274, (s32)D_800A6288,
    (s32)D_800A629C, (s32)D_800A62B0, (s32)D_800A62C4, (s32)D_800A62D8,
    (s32)D_800A62EC, (s32)D_800A6300, (s32)D_800A6314, (s32)D_800A6328,
    (s32)D_800A633C, (s32)D_800A6350, (s32)D_800A6364, (s32)D_800A6378,
    (s32)D_800A638C, (s32)D_800A63A0, (s32)D_800A63B4, (s32)D_800A63C8,
    (s32)D_800A63DC, (s32)D_800A63F0, 0,
};
u8 D_800A64D0[] = {
    0x01, 0x00, 0x40, 0x02, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5D, 0x00, 0x7D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x0B, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x6D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9E, 0x00,
    0x5D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xEB, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1A, 0x01, 0x2B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7B, 0x01, 0x22, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0x01,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAB, 0x01, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x12, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xCF, 0x01, 0x71, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x13, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE2, 0x01, 0x6D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7, 0x01,
    0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x01, 0x04, 0x00,
    0x54, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x01,
    0x04, 0x00, 0x74, 0x00, 0x72, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x01, 0x04, 0x00, 0x94, 0x00, 0x62, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x32, 0x02, 0x00, 0x01, 0x04, 0x00, 0x10, 0x01,
    0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x01, 0x04, 0x00,
    0x70, 0x01, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x01,
    0x04, 0x00, 0xA1, 0x01, 0x5B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x01, 0x04, 0x00, 0xC5, 0x01, 0x71, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x32, 0x02, 0x00, 0x01, 0x04, 0x00, 0xD9, 0x01,
    0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x01, 0x04, 0x00,
    0xED, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x01,
    0x04, 0x00, 0xF1, 0x01, 0x7C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x33, 0x02,
    0x00, 0x01, 0x04, 0x00, 0x24, 0x01, 0x68, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x01,
    0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x01, 0x04, 0x00,
    0xE0, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x01,
    0x04, 0x00, 0x88, 0x01, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x01, 0x04, 0x00, 0xA0, 0x01, 0x3C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x00,
    0x07, 0x01, 0x20, 0x01, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x01, 0xBF, 0x00, 0xD9, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x01, 0xA9, 0x00, 0xB8, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0xA1, 0x00,
    0xAE, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x01,
    0xA1, 0x00, 0xAE, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x01, 0x99, 0x00, 0xA6, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x60, 0x01, 0x99, 0x00, 0xA6, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x90, 0x00,
    0x9E, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x01,
    0x91, 0x00, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A6758[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x01, 0x02, 0x80, 0x01, 0xD8, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x12, 0x02, 0x92, 0x00, 0xA2, 0x01,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x10, 0x01, 0xB8, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x03, 0x00, 0x00, 0x01, 0xF0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
StageFuncs D_800A67D0 = { func_800A53B8, func_800A54A4, func_800A5538 };
s32 D_800A67DC[] = {
    57, (s32)D_800A55A4,
#if VERSION_US
    0x10B0011,
#elif VERSION_EU
    0x1120011,
#endif
    0, 0, 66, (s32)D_800A5634,
#if VERSION_US
    0x10B0013,
#elif VERSION_EU
    0x1120013,
#endif
    0, 0, 67, (s32)D_800A56AC,
#if VERSION_US
    0x10B0014,
#elif VERSION_EU
    0x1120014,
#endif
    0, 0, 1522, 0,
#if VERSION_US
    0x10B0039,
#elif VERSION_EU
    0x1120039,
#endif
    (s32)func_800A5270, 0, 1523, (s32)D_800A574C,
#if VERSION_US
    0x10B0034,
#elif VERSION_EU
    0x1120034,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
