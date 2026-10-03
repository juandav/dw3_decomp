#include "common.h"
#include "stage.h"
extern s32 D_800A762C[];
extern s32 D_800A7404[];
extern u8 D_800A5FE4[];
extern u8 D_800A75F0[];
extern u8 D_800A7498[];
void func_800A52CC();
extern StageFuncs D_800A7620;
void func_800A5894();
void func_800A5998();
void func_800A4D04();

/* The text file of the menus, which the versions number differently */
#if VERSION_US
#define MENU_TEXT 0x11A
#elif VERSION_EU
#define MENU_TEXT 0x120
#endif

/* A two-option menu: creates the event object of the chosen option */
void func_800A4D04(StageMenu *task, StageMenuChildren *children) {
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
            D_800A7620.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7620.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x5)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x5)), 1);
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
            children->event = func_80084B80(task->cursor == 0 ? 0x3B : 0x5EF);
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
            D_800A7620.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7620.update(&task->tween)) {
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

void *func_800A52A0(void) {
    return createTask(func_800A4D04, 0x64, 0x14);
}

/* A two-option menu: creates the event object of the chosen option */
void func_800A52CC(StageMenu *task, StageMenuChildren *children) {
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
            D_800A7620.start(&task->tween, 1);
            task->substate++;
            break;
        case 1:
            if (D_800A7620.update(&task->tween)) {
                for (j = 0; j < 2; j++) {
                    children->options[j]->setString(children->options[j], FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x6)), j + 2);
                }
                children->cursor->setVisible(children->cursor, 1);
                children->title->setString(children->title, FILE_CACHE.getEntry(TEXT_ENTRY(MENU_TEXT, 0x6)), 1);
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
            children->event = func_80084B80(task->cursor == 0 ? 0x41 : 0x5F1);
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
            D_800A7620.start(&task->tween, 0);
            task->substate++;
            break;
        case 11:
            if (D_800A7620.update(&task->tween)) {
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

void *func_800A5868(void) {
    return createTask(func_800A52CC, 0x64, 0x14);
}

void func_800A5894(StageTask *task) {
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

StageTask *func_800A58DC(void *owner) {
    StageTask *task = createTask(func_800A5894, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7620.setup();
    return task;
}

/* Sets flags 0x8192, 0x1A1C and 0x40A1 */
void func_800A5938(void) {
    FLAGS_00.applyAction(0x8192, 1);
    FLAGS_00.applyAction(0x1A1C, 1);
    FLAGS_00.applyAction(0x40A1, 1);
}

#if VERSION_US
void func_800A5998(void) {
    D_800990B4.unk44 = 0xCD;
    D_800990B4.unk8 = 0x1A0;
    D_800990B4.unkC = 0x1A10000;
    D_800990B4.unk10 = D_800A7498;
    D_800990B4.unk14 = D_800A75F0;
    D_800990B4.unk1C = 0x3C2;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1A400;
    D_800990B4.unk30 = 0xC800;
    D_800990B4.unk28 = D_800A5FE4;
    D_800990B4.unk3C = 8;
    D_800990B4.unk40 = 0x60200000;
    D_800990B4.unk4C = D_800A7404;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A762C;
    D_8009A70C.unk40(0, 0x1A10001);
    D_8009A70C.unk40(7, 0x1A10002);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag270", func_800A5998);
#endif

void func_800A5A84(StageTween *tween, s32 up) {
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

s32 func_800A5B18(StageTween *tween) {
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

void func_800A5938();
extern s32 D_800A6144[];
extern s32 D_800A614C[];
extern s32 D_800A6154[];
extern s32 D_800A615C[];
extern s32 D_800A616C[];
extern s32 D_800A6178[];
extern s32 D_800A6188[];
extern s32 D_800A6190[];
extern s32 D_800A61A0[];
extern s32 D_800A61A8[];
extern s32 D_800A61BC[];
extern s32 D_800A61D4[];
extern s32 D_800A61DC[];
extern s32 D_800A61F4[];
extern s32 D_800A61FC[];
extern s32 D_800A6204[];
extern s32 D_800A6210[];
extern s32 D_800A6218[];
extern s32 D_800A6224[];
extern s32 D_800A6230[];
extern s32 D_800A6238[];
extern s32 D_800A6240[];
extern s32 D_800A624C[];
extern s32 D_800A625C[];
extern s32 D_800A6264[];
extern s32 D_800A6274[];
extern s32 D_800A627C[];
extern s32 D_800A6284[];
extern s32 D_800A628C[];
extern s32 D_800A6298[];
extern s32 D_800A62A8[];
extern s32 D_800A62B0[];
extern s32 D_800A62C0[];
extern s32 D_800A62C8[];
extern s32 D_800A62D0[];
extern s32 D_800A62E0[];
extern s32 D_800A62EC[];
extern s32 D_800A62FC[];
extern s32 D_800A6304[];
extern s32 D_800A6314[];
extern s32 D_800A631C[];
extern s32 D_800A6330[];
extern s32 D_800A6348[];
extern s32 D_800A6350[];
extern s32 D_800A6368[];
extern s32 D_800A6370[];
extern s32 D_800A6378[];
extern s32 D_800A6384[];
extern s32 D_800A638C[];
extern s32 D_800A6398[];
extern s32 D_800A63A4[];
extern s32 D_800A63AC[];
extern s32 D_800A63B4[];
extern s32 D_800A63C0[];
extern s32 D_800A63D0[];
extern s32 D_800A63D8[];
extern s32 D_800A63E8[];
extern s32 D_800A63F0[];
extern s32 D_800A63F8[];
extern s32 D_800A6400[];
extern s32 D_800A640C[];
extern s32 D_800A641C[];
extern s32 D_800A6424[];
extern s32 D_800A6434[];
extern s32 D_800A643C[];
extern s32 D_800A6444[];
extern s32 D_800A644C[];
extern s32 D_800A6454[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A6480[];
extern s32 D_800A6488[];
extern s32 D_800A6498[];
extern s32 D_800A64A0[];
extern s32 D_800A64B4[];
extern s32 D_800A64CC[];
extern s32 D_800A64D4[];
extern s32 D_800A64EC[];
extern s32 D_800A64F4[];
extern s32 D_800A64FC[];
extern s32 D_800A6508[];
extern s32 D_800A6510[];
extern s32 D_800A651C[];
extern s32 D_800A6528[];
extern s32 D_800A6530[];
extern s32 D_800A6538[];
extern s32 D_800A6544[];
extern s32 D_800A6554[];
extern s32 D_800A655C[];
extern s32 D_800A656C[];
extern s32 D_800A6574[];
extern s32 D_800A657C[];
extern s32 D_800A6584[];
extern s32 D_800A6590[];
extern s32 D_800A65A0[];
extern s32 D_800A65A8[];
extern s32 D_800A65B8[];
extern s32 D_800A65C0[];
extern s32 D_800A65C8[];
extern s32 D_800A65D8[];
extern s32 D_800A65E4[];
extern s32 D_800A65F4[];
extern s32 D_800A65FC[];
extern s32 D_800A660C[];
extern s32 D_800A6614[];
extern s32 D_800A6628[];
extern s32 D_800A6640[];
extern s32 D_800A6648[];
extern s32 D_800A6660[];
extern s32 D_800A6668[];
extern s32 D_800A6670[];
extern s32 D_800A6678[];
extern s32 D_800A6684[];
extern s32 D_800A6694[];
extern s32 D_800A669C[];
extern s32 D_800A66AC[];
extern s32 D_800A66B4[];
extern s32 D_800A66BC[];
extern s32 D_800A66C4[];
extern s32 D_800A66D0[];
extern s32 D_800A66E0[];
extern s32 D_800A66E8[];
extern s32 D_800A66F8[];
extern s32 D_800A6700[];
extern s32 D_800A6708[];
extern s32 D_800A6714[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A673C[];
extern s32 D_800A6748[];
extern s32 D_800A6758[];
extern s32 D_800A6760[];
extern s32 D_800A6770[];
extern s32 D_800A6778[];
extern s32 D_800A6780[];
extern s32 D_800A678C[];
extern s32 D_800A679C[];
extern s32 D_800A67A4[];
extern s32 D_800A67B4[];
extern s32 D_800A67BC[];
extern s32 D_800A67C4[];
extern s32 D_800A67D0[];
extern s32 D_800A67E0[];
extern s32 D_800A67E8[];
extern s32 D_800A67F8[];
extern s32 D_800A6800[];
extern s32 D_800A6808[];
extern s32 D_800A6814[];
extern s32 D_800A6824[];
extern s32 D_800A682C[];
extern s32 D_800A683C[];
extern s32 D_800A6844[];
extern s32 D_800A6850[];
extern s32 D_800A6858[];
extern s32 D_800A6864[];
extern s32 D_800A686C[];
extern s32 D_800A6874[];
extern s32 D_800A687C[];
extern s32 D_800A6884[];
extern s32 D_800A688C[];
extern s32 D_800A6894[];
extern s32 D_800A689C[];
extern s32 D_800A68A4[];
extern s32 D_800A68AC[];
extern s32 D_800A68B8[];
extern s32 D_800A68C0[];
extern s32 D_800A68C8[];
extern s32 D_800A68D0[];
extern s32 D_800A68D8[];
extern s32 D_800A68E0[];
extern s32 D_800A68E8[];
extern s32 D_800A68F0[];
extern s32 D_800A68F8[];
extern s32 D_800A6904[];
extern s32 D_800A6FCC[];
extern s32 D_800A690C[];
extern s32 D_800A6FD4[];
extern s32 D_800A6924[];
extern s32 D_800A6FDC[];
extern s32 D_800A693C[];
extern s32 D_800A6FE4[];
extern s32 D_800A699C[];
extern s32 D_800A6FF0[];
extern s32 D_800A69CC[];
extern s32 D_800A6FFC[];
extern s32 D_800A6A08[];
extern s32 D_800A7008[];
extern s32 D_800A6A44[];
extern s32 D_800A7014[];
extern s32 D_800A6A5C[];
extern s32 D_800A701C[];
extern s32 D_800A6ABC[];
extern s32 D_800A7028[];
extern s32 D_800A6AEC[];
extern s32 D_800A7034[];
extern s32 D_800A6B28[];
extern s32 D_800A7040[];
extern s32 D_800A6B64[];
extern s32 D_800A704C[];
extern s32 D_800A6B7C[];
extern s32 D_800A7054[];
extern s32 D_800A6B94[];
extern s32 D_800A705C[];
extern s32 D_800A6BAC[];
extern s32 D_800A7064[];
extern s32 D_800A6C0C[];
extern s32 D_800A7070[];
extern s32 D_800A6C3C[];
extern s32 D_800A707C[];
extern s32 D_800A6C78[];
extern s32 D_800A7088[];
extern s32 D_800A6CB4[];
extern s32 D_800A7094[];
extern s32 D_800A6CCC[];
extern s32 D_800A709C[];
extern s32 D_800A6D2C[];
extern s32 D_800A70A8[];
extern s32 D_800A6D68[];
extern s32 D_800A70B4[];
extern s32 D_800A6DA4[];
extern s32 D_800A70C0[];
extern s32 D_800A6DD4[];
extern s32 D_800A70CC[];
extern s32 D_800A6DEC[];
extern s32 D_800A70D4[];
extern s32 D_800A6E04[];
extern s32 D_800A70DC[];
extern s32 D_800A6E40[];
extern s32 D_800A70E4[];
extern s32 D_800A6E7C[];
extern s32 D_800A70EC[];
extern s32 D_800A6EB8[];
extern s32 D_800A70F4[];
extern s32 D_800A6EF4[];
extern s32 D_800A70FC[];
extern s32 D_800A6F0C[];
extern s32 D_800A7108[];
extern s32 D_800A6F90[];
extern s32 D_800A7118[];
extern s32 D_800A6FB4[];
extern s32 D_800A7124[];
extern s32 D_800A712C[];
extern s32 D_800A7134[];
extern s32 D_800A7148[];
extern s32 D_800A715C[];
extern s32 D_800A7170[];
extern s32 D_800A7184[];
extern s32 D_800A7198[];
extern s32 D_800A71AC[];
extern s32 D_800A71C0[];
extern s32 D_800A71D4[];
extern s32 D_800A71E8[];
extern s32 D_800A71FC[];
extern s32 D_800A7210[];
extern s32 D_800A7224[];
extern s32 D_800A7238[];
extern s32 D_800A724C[];
extern s32 D_800A7260[];
extern s32 D_800A7274[];
extern s32 D_800A7288[];
extern s32 D_800A729C[];
extern s32 D_800A72B0[];
extern s32 D_800A72C4[];
extern s32 D_800A72D8[];
extern s32 D_800A72EC[];
extern s32 D_800A7300[];
extern s32 D_800A7314[];
extern s32 D_800A7328[];
extern s32 D_800A733C[];
extern s32 D_800A7350[];
extern s32 D_800A7364[];
extern s32 D_800A7378[];
extern s32 D_800A738C[];
extern s32 D_800A73A0[];
extern s32 D_800A73B4[];
extern s32 D_800A73C8[];
extern s32 D_800A73DC[];
extern s32 D_800A73F0[];
extern s32 D_800A5B84[];
extern s32 D_800A5C2C[];
extern s32 D_800A5CC8[];
extern s32 D_800A5F8C[];
extern s32 D_800A5FA4[];

s32 D_800A5B84[] = {
    0x1E0300, 0x1E0300, 512, 0x330001,
    0x3010002, 0x1E0300, 0x32D0101, 0x20338,
    0x1E0300, 512, 0x20002, 0x3010004,
    0x1E0300, 512, 0x330003, 0x3010004,
    0x1E0300, 512, 0x20004, 0x3010004,
    0x1E0300, 512, 0x20005, 0x3010004,
    0x1E0300, 512, 0x20006, 0x3010004,
    0x1E0300, 512, 0x20007, 0x3010004,
    0x1E0300, 0x32D0101, 0x20339, 0x1E0300,
    0x1E0300, 512, 0x330008, 0x3010002,
    0x1E0300,
#if VERSION_US
    0x46440000,
#elif VERSION_EU
    0x1040000,
#endif
};
s32 D_800A5C2C[] = {
    0x20102, 0xBD0117, 0x1010003, 0x1002D,
    0x1010007, 0x337032D, 0x3000002, 0x300001E,
    0x200001E, 0x10000, 0x2002D, 0x3000301,
    0x101001E, 0x338032D, 0x3000002, 0x200001E,
    0x20000, 0x40002, 0x3000301, 0x200001E,
    0x30000, 0x4002D, 0x3000301, 0x200001E,
    0x40000, 0x40002, 0x3000301, 0x101001E,
    0x339032D, 0x3000002, 0x300001E, 0x200001E,
    0x50000, 0x2002D, 0x1010301, 0x10002,
    0x3000007, 0x300001E, 30,
};
s32 D_800A5CC8[] = {
    0x20102, 0xA3019B, 0x1010003, 0x1002F,
    0x1010007, 0x10032, 0x1010007, 0x10034,
    0x1010003, 0x10037, 0x1010003, 0x100CE,
    0x1010007, 0x337032D, 0x3020002, 0x2000002,
    0x10000, 0x200CE, 0x3000301, 0x200001E,
    0x20000, 0x10002, 0x20101, 0x30007,
    0x1010301, 0x10002, 0x3000003, 0x200001E,
    0x30000, 0x200CE, 0x3000301, 0x200001E,
    0x40000, 0x10002, 0x20101, 0x30007,
    0x1010301, 0x10002, 0x3000003, 0x101001E,
    0x3250323, 0x30000CE, 0x101005A, 0x3260323,
    0x30000CE, 0x200001E, 0x50000, 0x200CE,
    0x3000301, 0x601001E, 0xD00000, 0x30000E1,
    0x3000096, 0x101001E, 0x3250323, 0x3000034,
    0x101005A, 0x3260323, 0x3000034, 0x200001E,
    0x60000, 0x10034, 0x3000301, 0x200001E,
    0x70000, 0x10034, 0x3000301, 0x200001E,
    0x80000, 0x2002F, 0x3000301, 0x200001E,
    0x90000, 0x10034, 0x3000301, 0x200001E,
    0xA0000, 0x2002F, 0x3000301, 0x200001E,
    0xC0001, 0x2002F, 512, 0x34000B,
    0x3010001, 0x3230101, 0x340325, 0x5A0300,
    0x3230101, 0x340326, 0x1E0300, 512,
    0x34000D, 0x3010001, 0x1E0300, 512,
    0x2F000E, 0x3010002, 0x1E0300, 0x3230101,
    0x340327, 0xB40300, 512, 0x32000F,
    0x3010000, 0x3230101, 0x340326, 0x3240101,
    0x370325, 0x5A0300, 0x3240101, 0x370326,
    0x1E0300, 512, 0x370010, 0x3010002,
    0x1E0300, 512, 0x320011, 0x3010000,
    0x1E0300, 512, 0x370012, 0x3010002,
    0x3230101, 0x370327, 0x1E0300, 512,
    0x320013, 0x3010000, 0x3C0300, 0x3230101,
    0x370326, 0x1E0300, 512, 0x370014,
    0x3010002, 0x1E0300, 512, 0x320015,
    0x3010000, 1536, 0x3000002, 0x200005A,
    0x160000, 0x200CE, 0x1010301, 0x34A032D,
    0x3000002, 0x200001E, 0x170000, 0x10002,
    0x20101, 0x30007, 0x1010301, 0x10002,
    0x3000003, 0x200001E, 0x180000, 0x200CE,
    0x3000301, 0x200001E, 0x190000, 0x10002,
    0x20101, 0x30007, 0x1010301, 0x10002,
    0x3000003, 0x200001E, 0x1A0000, 0x200CE,
    0x3000301, 0x101001E, 0x10002, 0x3000007,
    30,
};
s32 D_800A5F8C[] = {
    0x3C0300, 512, 0x330001, 0x3010002,
    0x1E0300, 0,
};
s32 D_800A5FA4[] = {
    0x20102, 0xBD0117, 0x1010003, 0x1002D,
    0x1010007, 0x337032D, 0x3000002, 0x300001E,
    0x200001E, 0x10000, 0x2002D, 0x1010301,
    0x10002, 0x3000007, 0x300001E, 30,
};
u8 D_800A5FE4[] = {
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
    0x80, 0x01, 0x00, 0x01, 0xB8, 0x01, 0x59, 0x01,
    0xE0, 0x01, 0x59, 0x00, 0x60, 0x01, 0xFB, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xB0, 0x01, 0x59, 0x01,
    0xC0, 0x01, 0x59, 0x00, 0x70, 0x01, 0xFB, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA0, 0x01, 0x5D, 0x01,
    0x80, 0x01, 0x5D, 0x00, 0x50, 0x01, 0xFA, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA8, 0x01, 0x5D, 0x01,
    0xA0, 0x01, 0x5D, 0x00, 0x60, 0x01, 0xFA, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x90, 0x01, 0x71, 0x01,
    0x40, 0x01, 0x71, 0x00, 0x70, 0x01, 0xFA, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x98, 0x01, 0x71, 0x01,
    0x60, 0x01, 0x71, 0x00, 0x40, 0x01, 0xF9, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x40, 0x01, 0xD8, 0x01,
    0x00, 0x00, 0xD8, 0x00, 0x50, 0x01, 0xF9, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x80, 0x01, 0x72, 0x01,
    0x00, 0x01, 0x72, 0x00, 0x60, 0x01, 0xF9, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x88, 0x01, 0x72, 0x01,
    0x20, 0x01, 0x72, 0x00, 0x70, 0x01, 0xF9, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xB0, 0x01, 0x81, 0x01,
    0xC0, 0x01, 0x81, 0x00, 0x40, 0x01, 0xF8, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA0, 0x01, 0x85, 0x01,
    0x80, 0x01, 0x85, 0x00, 0x50, 0x01, 0xF8, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA8, 0x01, 0x85, 0x01,
    0xA0, 0x01, 0x85, 0x00, 0x60, 0x01, 0xF8, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xB4, 0x01, 0x00, 0x01,
    0xD0, 0x01, 0x00, 0x00, 0x70, 0x01, 0xF8, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
s32 D_800A6144[] = {
    0x1901C, 65535,
};
s32 D_800A614C[] = {
    0x1901C, 65535,
};
s32 D_800A6154[] = {
    33170, 65535,
};
s32 D_800A615C[] = {
    0x18192, 0x10011, 0x10010, 65535,
};
s32 D_800A616C[] = {
    17, 16, 65535,
};
s32 D_800A6178[] = {
    0x18192, 0x10011, 16, 65535,
};
s32 D_800A6188[] = {
    17, 65535,
};
s32 D_800A6190[] = {
    2, 0x18192, 17, 65535,
};
s32 D_800A61A0[] = {
    0x10002, 65535,
};
s32 D_800A61A8[] = {
    0x10002, 29184, 0x18192, 17,
    65535,
};
s32 D_800A61BC[] = {
    29188, 0x17200, 0x10002, 0x18192,
    17, 65535,
};
s32 D_800A61D4[] = {
    0x17603, 65535,
};
s32 D_800A61DC[] = {
    0x10002, 0x17200, 0x17204, 0x18192,
    17, 65535,
};
s32 D_800A61F4[] = {
    0x17803, 65535,
};
s32 D_800A61FC[] = {
    17, 65535,
};
s32 D_800A6204[] = {
    16, 0x10011, 65535,
};
s32 D_800A6210[] = {
    17, 65535,
};
s32 D_800A6218[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A6224[] = {
    17, 16, 65535,
};
s32 D_800A6230[] = {
    2, 65535,
};
s32 D_800A6238[] = {
    0x10002, 65535,
};
s32 D_800A6240[] = {
    0x10002, 29184, 65535,
};
s32 D_800A624C[] = {
    0x10002, 0x17200, 29188, 65535,
};
s32 D_800A625C[] = {
    0x17603, 65535,
};
s32 D_800A6264[] = {
    0x10002, 0x17200, 0x17204, 65535,
};
s32 D_800A6274[] = {
    0x17803, 65535,
};
s32 D_800A627C[] = {
    2, 65535,
};
s32 D_800A6284[] = {
    0x10002, 65535,
};
s32 D_800A628C[] = {
    0x10002, 29184, 65535,
};
s32 D_800A6298[] = {
    0x10002, 0x17200, 29188, 65535,
};
s32 D_800A62A8[] = {
    0x17603, 65535,
};
s32 D_800A62B0[] = {
    0x10002, 0x17200, 0x17204, 65535,
};
s32 D_800A62C0[] = {
    0x17803, 65535,
};
s32 D_800A62C8[] = {
    33170, 65535,
};
s32 D_800A62D0[] = {
    0x18192, 0x10011, 0x10010, 65535,
};
s32 D_800A62E0[] = {
    17, 16, 65535,
};
s32 D_800A62EC[] = {
    0x18192, 0x10011, 16, 65535,
};
s32 D_800A62FC[] = {
    17, 65535,
};
s32 D_800A6304[] = {
    3, 0x18192, 17, 65535,
};
s32 D_800A6314[] = {
    0x10003, 65535,
};
s32 D_800A631C[] = {
    0x10003, 29184, 0x18192, 17,
    65535,
};
s32 D_800A6330[] = {
    0x10003, 0x17200, 29188, 0x18192,
    17, 65535,
};
s32 D_800A6348[] = {
    0x17604, 65535,
};
s32 D_800A6350[] = {
    0x10003, 0x17200, 0x17204, 0x18192,
    17, 65535,
};
s32 D_800A6368[] = {
    0x17804, 65535,
};
s32 D_800A6370[] = {
    17, 65535,
};
s32 D_800A6378[] = {
    16, 0x10011, 65535,
};
s32 D_800A6384[] = {
    17, 65535,
};
s32 D_800A638C[] = {
    0x10010, 0x10011, 65535,
};
s32 D_800A6398[] = {
    17, 16, 65535,
};
s32 D_800A63A4[] = {
    3, 65535,
};
s32 D_800A63AC[] = {
    0x10003, 65535,
};
s32 D_800A63B4[] = {
    29184, 0x10003, 65535,
};
s32 D_800A63C0[] = {
    0x10003, 0x17200, 29188, 65535,
};
s32 D_800A63D0[] = {
    0x17604, 65535,
};
s32 D_800A63D8[] = {
    0x17204, 0x10003, 0x17200, 65535,
};
s32 D_800A63E8[] = {
    0x17804, 65535,
};
s32 D_800A63F0[] = {
    3, 65535,
};
s32 D_800A63F8[] = {
    0x10003, 65535,
};
s32 D_800A6400[] = {
    0x10003, 29184, 65535,
};
s32 D_800A640C[] = {
    0x10003, 0x17200, 29188, 65535,
};
s32 D_800A641C[] = {
    0x17604, 65535,
};
s32 D_800A6424[] = {
    0x10003, 0x17200, 0x17204, 65535,
};
s32 D_800A6434[] = {
    0x17804, 65535,
};
s32 D_800A643C[] = {
    0x1901B, 65535,
};
s32 D_800A6444[] = {
    0x1901B, 65535,
};
s32 D_800A644C[] = {
    33170, 65535,
};
s32 D_800A6454[] = {
    0x18192, 0x10011, 0x10010, 65535,
};
s32 D_800A6464[] = {
    17, 16, 65535,
};
s32 D_800A6470[] = {
    0x18192, 0x10011, 16, 65535,
};
s32 D_800A6480[] = {
    17, 65535,
};
s32 D_800A6488[] = {
    0, 0x18192, 17, 65535,
};
s32 D_800A6498[] = {
    0x10000, 65535,
};
s32 D_800A64A0[] = {
    0x10000, 29184, 0x18192, 17,
    65535,
};
s32 D_800A64B4[] = {
    0x10000, 29188, 0x17200, 0x18192,
    17, 65535,
};
s32 D_800A64CC[] = {
    0x17601, 65535,
};
s32 D_800A64D4[] = {
    0x17200, 0x10000, 0x17204, 0x18192,
    17, 65535,
};
s32 D_800A64EC[] = {
    0x17801, 65535,
};
s32 D_800A64F4[] = {
    17, 65535,
};
s32 D_800A64FC[] = {
    16, 0x10011, 65535,
};
s32 D_800A6508[] = {
    17, 65535,
};
s32 D_800A6510[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A651C[] = {
    17, 16, 65535,
};
s32 D_800A6528[] = {
    0, 65535,
};
s32 D_800A6530[] = {
    0x10000, 65535,
};
s32 D_800A6538[] = {
    0x10000, 29184, 65535,
};
s32 D_800A6544[] = {
    0x10000, 0x17200, 29188, 65535,
};
s32 D_800A6554[] = {
    0x17601, 65535,
};
s32 D_800A655C[] = {
    0x10000, 0x17200, 0x17204, 65535,
};
s32 D_800A656C[] = {
    0x17801, 65535,
};
s32 D_800A6574[] = {
    0, 65535,
};
s32 D_800A657C[] = {
    0x10000, 65535,
};
s32 D_800A6584[] = {
    0x10000, 29184, 65535,
};
s32 D_800A6590[] = {
    0x10000, 29188, 0x17200, 65535,
};
s32 D_800A65A0[] = {
    0x17601, 65535,
};
s32 D_800A65A8[] = {
    0x10000, 0x17200, 0x17204, 65535,
};
s32 D_800A65B8[] = {
    0x17801, 65535,
};
s32 D_800A65C0[] = {
    33170, 65535,
};
s32 D_800A65C8[] = {
    0x18192, 0x10011, 0x10010, 65535,
};
s32 D_800A65D8[] = {
    17, 16, 65535,
};
s32 D_800A65E4[] = {
    0x18192, 0x10011, 16, 65535,
};
s32 D_800A65F4[] = {
    17, 65535,
};
s32 D_800A65FC[] = {
    1, 0x18192, 17, 65535,
};
s32 D_800A660C[] = {
    0x10001, 65535,
};
s32 D_800A6614[] = {
    0x10001, 29184, 0x18192, 17,
    65535,
};
s32 D_800A6628[] = {
    0x10001, 0x17200, 29188, 0x18192,
    17, 65535,
};
s32 D_800A6640[] = {
    0x17602, 65535,
};
s32 D_800A6648[] = {
    0x10001, 0x17200, 0x17204, 0x18192,
    17, 65535,
};
s32 D_800A6660[] = {
    0x17802, 65535,
};
s32 D_800A6668[] = {
    1, 65535,
};
s32 D_800A6670[] = {
    0x10001, 65535,
};
s32 D_800A6678[] = {
    0x10001, 29184, 65535,
};
s32 D_800A6684[] = {
    0x10001, 0x17200, 29188, 65535,
};
s32 D_800A6694[] = {
    0x17602, 65535,
};
s32 D_800A669C[] = {
    0x10001, 0x17200, 0x17204, 65535,
};
s32 D_800A66AC[] = {
    0x17802, 65535,
};
s32 D_800A66B4[] = {
    1, 65535,
};
s32 D_800A66BC[] = {
    0x10001, 65535,
};
s32 D_800A66C4[] = {
    0x10001, 29184, 65535,
};
s32 D_800A66D0[] = {
    0x10001, 0x17200, 29188, 65535,
};
s32 D_800A66E0[] = {
    0x17602, 65535,
};
s32 D_800A66E8[] = {
    0x10001, 0x17204, 0x17200, 65535,
};
s32 D_800A66F8[] = {
    0x17802, 65535,
};
s32 D_800A6700[] = {
    17, 65535,
};
s32 D_800A6708[] = {
    16, 0x10011, 65535,
};
s32 D_800A6714[] = {
    17, 65535,
};
s32 D_800A671C[] = {
    0x10010, 0x10011, 65535,
};
s32 D_800A6728[] = {
    17, 16, 65535,
};
s32 D_800A6734[] = {
    2, 65535,
};
s32 D_800A673C[] = {
    0x10002, 29184, 65535,
};
s32 D_800A6748[] = {
    0x10002, 0x17200, 29188, 65535,
};
s32 D_800A6758[] = {
    0x17603, 65535,
};
s32 D_800A6760[] = {
    0x10002, 0x17200, 0x17204, 65535,
};
s32 D_800A6770[] = {
    0x17803, 65535,
};
s32 D_800A6778[] = {
    0, 65535,
};
s32 D_800A6780[] = {
    0x10000, 29184, 65535,
};
s32 D_800A678C[] = {
    0x10000, 0x17200, 29188, 65535,
};
s32 D_800A679C[] = {
    0x17601, 65535,
};
s32 D_800A67A4[] = {
    0x10000, 0x17200, 0x17204, 65535,
};
s32 D_800A67B4[] = {
    0x17801, 65535,
};
s32 D_800A67BC[] = {
    3, 65535,
};
s32 D_800A67C4[] = {
    0x10003, 29184, 65535,
};
s32 D_800A67D0[] = {
    0x10003, 0x17200, 29188, 65535,
};
s32 D_800A67E0[] = {
    0x17604, 65535,
};
s32 D_800A67E8[] = {
    0x10003, 0x17200, 0x17204, 65535,
};
s32 D_800A67F8[] = {
    0x17804, 65535,
};
s32 D_800A6800[] = {
    1, 65535,
};
s32 D_800A6808[] = {
    0x10001, 29184, 65535,
};
s32 D_800A6814[] = {
    0x10001, 0x17200, 29188, 65535,
};
s32 D_800A6824[] = {
    0x17602, 65535,
};
s32 D_800A682C[] = {
    0x10001, 0x17200, 0x17204, 65535,
};
s32 D_800A683C[] = {
    0x17802, 65535,
};
s32 D_800A6844[] = {
    0x16004, 6684, 65535,
};
s32 D_800A6850[] = {
    0x11A1C, 65535,
};
s32 D_800A6858[] = {
    0x16004, 0x11A1C, 65535,
};
s32 D_800A6864[] = {
    0x17A31, 65535,
};
s32 D_800A686C[] = {
    0x17015, 65535,
};
s32 D_800A6874[] = {
    0x17A31, 65535,
};
s32 D_800A687C[] = {
    0x1703E, 65535,
};
s32 D_800A6884[] = {
    0x17A32, 65535,
};
s32 D_800A688C[] = {
    0x17018, 65535,
};
s32 D_800A6894[] = {
    0x17A33, 65535,
};
s32 D_800A689C[] = {
    0x17020, 65535,
};
s32 D_800A68A4[] = {
    0x17A34, 65535,
};
s32 D_800A68AC[] = {
    0x17021, 24614, 65535,
};
s32 D_800A68B8[] = {
    0x17A35, 65535,
};
s32 D_800A68C0[] = {
    0x16026, 65535,
};
s32 D_800A68C8[] = {
    0x17A36, 65535,
};
s32 D_800A68D0[] = {
    0x1701A, 65535,
};
s32 D_800A68D8[] = {
    0x17A36, 65535,
};
s32 D_800A68E0[] = {
    0x1602B, 65535,
};
s32 D_800A68E8[] = {
    0x17A36, 65535,
};
s32 D_800A68F0[] = {
    33170, 65535,
};
s32 D_800A68F8[] = {
    0x11C48, 0x1905C, 65535,
};
s32 D_800A6904[] = {
    0x18192, 65535,
};
s32 D_800A690C[] = {
    0, (s32)D_800A6144, 584, 0,
    0, 0,
};
s32 D_800A6924[] = {
    0, (s32)D_800A614C, 49, 0,
    0, 0,
};
s32 D_800A693C[] = {
    (s32)D_800A6154, 0, 1053, (s32)D_800A615C,
    (s32)D_800A616C, 151, (s32)D_800A6178, (s32)D_800A6188,
    150, (s32)D_800A6190, (s32)D_800A61A0, 122,
    (s32)D_800A61A8, 0, 124, (s32)D_800A61BC,
    (s32)D_800A61D4, 125, (s32)D_800A61DC, (s32)D_800A61F4,
    126, 0, 0, 0,
};
s32 D_800A699C[] = {
    (s32)D_800A61FC, 0, 122, (s32)D_800A6204,
    (s32)D_800A6210, 150, (s32)D_800A6218, (s32)D_800A6224,
    151, 0, 0, 0,
};
s32 D_800A69CC[] = {
    (s32)D_800A6230, (s32)D_800A6238, 123, (s32)D_800A6240,
    0, 124, (s32)D_800A624C, (s32)D_800A625C,
    125, (s32)D_800A6264, (s32)D_800A6274, 126,
    0, 0, 0,
};
s32 D_800A6A08[] = {
    (s32)D_800A627C, (s32)D_800A6284, 147, (s32)D_800A628C,
    0, 124, (s32)D_800A6298, (s32)D_800A62A8,
    125, (s32)D_800A62B0, (s32)D_800A62C0, 126,
    0, 0, 0,
};
s32 D_800A6A44[] = {
    0, 0, 1053, 0,
    0, 0,
};
s32 D_800A6A5C[] = {
    (s32)D_800A62C8, 0, 1054, (s32)D_800A62D0,
    (s32)D_800A62E0, 161, (s32)D_800A62EC, (s32)D_800A62FC,
    160, (s32)D_800A6304, (s32)D_800A6314, 152,
    (s32)D_800A631C, 0, 157, (s32)D_800A6330,
    (s32)D_800A6348, 158, (s32)D_800A6350, (s32)D_800A6368,
    159, 0, 0, 0,
};
s32 D_800A6ABC[] = {
    (s32)D_800A6370, 0, 152, (s32)D_800A6378,
    (s32)D_800A6384, 160, (s32)D_800A638C, (s32)D_800A6398,
    161, 0, 0, 0,
};
s32 D_800A6AEC[] = {
    (s32)D_800A63A4, (s32)D_800A63AC, 153, (s32)D_800A63B4,
    0, 157, (s32)D_800A63C0, (s32)D_800A63D0,
    158, (s32)D_800A63D8, (s32)D_800A63E8, 159,
    0, 0, 0,
};
s32 D_800A6B28[] = {
    (s32)D_800A63F0, (s32)D_800A63F8, 154, (s32)D_800A6400,
    0, 157, (s32)D_800A640C, (s32)D_800A641C,
    158, (s32)D_800A6424, (s32)D_800A6434, 159,
    0, 0, 0,
};
s32 D_800A6B64[] = {
    0, 0, 1054, 0,
    0, 0,
};
s32 D_800A6B7C[] = {
    0, (s32)D_800A643C, 48, 0,
    0, 0,
};
s32 D_800A6B94[] = {
    0, (s32)D_800A6444, 48, 0,
    0, 0,
};
s32 D_800A6BAC[] = {
    (s32)D_800A644C, 0, 1051, (s32)D_800A6454,
    (s32)D_800A6464, 136, (s32)D_800A6470, (s32)D_800A6480,
    135, (s32)D_800A6488, (s32)D_800A6498, 112,
    (s32)D_800A64A0, 0, 114, (s32)D_800A64B4,
    (s32)D_800A64CC, 115, (s32)D_800A64D4, (s32)D_800A64EC,
    116, 0, 0, 0,
};
s32 D_800A6C0C[] = {
    (s32)D_800A64F4, 0, 112, (s32)D_800A64FC,
    (s32)D_800A6508, 135, (s32)D_800A6510, (s32)D_800A651C,
    136, 0, 0, 0,
};
s32 D_800A6C3C[] = {
    (s32)D_800A6528, (s32)D_800A6530, 113, (s32)D_800A6538,
    0, 114, (s32)D_800A6544, (s32)D_800A6554,
    115, (s32)D_800A655C, (s32)D_800A656C, 116,
    0, 0, 0,
};
s32 D_800A6C78[] = {
    (s32)D_800A6574, (s32)D_800A657C, 132, (s32)D_800A6584,
    0, 114, (s32)D_800A6590, (s32)D_800A65A0,
    115, (s32)D_800A65A8, (s32)D_800A65B8, 116,
    0, 0, 0,
};
s32 D_800A6CB4[] = {
    0, 0, 1051, 0,
    0, 0,
};
s32 D_800A6CCC[] = {
    (s32)D_800A65C0, 0, 1052, (s32)D_800A65C8,
    (s32)D_800A65D8, 146, (s32)D_800A65E4, (s32)D_800A65F4,
    145, (s32)D_800A65FC, (s32)D_800A660C, 117,
    (s32)D_800A6614, 0, 119, (s32)D_800A6628,
    (s32)D_800A6640, 120, (s32)D_800A6648, (s32)D_800A6660,
    121, 0, 0, 0,
};
s32 D_800A6D2C[] = {
    (s32)D_800A6668, (s32)D_800A6670, 118, (s32)D_800A6678,
    0, 119, (s32)D_800A6684, (s32)D_800A6694,
    120, (s32)D_800A669C, (s32)D_800A66AC, 121,
    0, 0, 0,
};
s32 D_800A6D68[] = {
    (s32)D_800A66B4, (s32)D_800A66BC, 141, (s32)D_800A66C4,
    0, 119, (s32)D_800A66D0, (s32)D_800A66E0,
    120, (s32)D_800A66E8, (s32)D_800A66F8, 121,
    0, 0, 0,
};
s32 D_800A6DA4[] = {
    (s32)D_800A6700, 0, 117, (s32)D_800A6708,
    (s32)D_800A6714, 145, (s32)D_800A671C, (s32)D_800A6728,
    146, 0, 0, 0,
};
s32 D_800A6DD4[] = {
    0, 0, 1052, 0,
    0, 0,
};
s32 D_800A6DEC[] = {
    0, 0, 593, 0,
    0, 0,
};
s32 D_800A6E04[] = {
    (s32)D_800A6734, 0, 148, (s32)D_800A673C,
    0, 124, (s32)D_800A6748, (s32)D_800A6758,
    125, (s32)D_800A6760, (s32)D_800A6770, 126,
    0, 0, 0,
};
s32 D_800A6E40[] = {
    (s32)D_800A6778, 0, 133, (s32)D_800A6780,
    0, 114, (s32)D_800A678C, (s32)D_800A679C,
    115, (s32)D_800A67A4, (s32)D_800A67B4, 116,
    0, 0, 0,
};
s32 D_800A6E7C[] = {
    (s32)D_800A67BC, 0, 155, (s32)D_800A67C4,
    0, 157, (s32)D_800A67D0, (s32)D_800A67E0,
    158, (s32)D_800A67E8, (s32)D_800A67F8, 159,
    0, 0, 0,
};
s32 D_800A6EB8[] = {
    (s32)D_800A6800, 0, 143, (s32)D_800A6808,
    0, 119, (s32)D_800A6814, (s32)D_800A6824,
    120, (s32)D_800A682C, (s32)D_800A683C, 121,
    0, 0, 0,
};
s32 D_800A6EF4[] = {
    0, 0, 583, 0,
    0, 0,
};
s32 D_800A6F0C[] = {
    (s32)D_800A6844, (s32)D_800A6850, 47, (s32)D_800A6858,
    (s32)D_800A6864, 677, (s32)D_800A686C, (s32)D_800A6874,
    677, (s32)D_800A687C, (s32)D_800A6884, 677,
    (s32)D_800A688C, (s32)D_800A6894, 677, (s32)D_800A689C,
    (s32)D_800A68A4, 677, (s32)D_800A68AC, (s32)D_800A68B8,
    677, (s32)D_800A68C0, (s32)D_800A68C8, 677,
    (s32)D_800A68D0, (s32)D_800A68D8, 677, (s32)D_800A68E0,
    (s32)D_800A68E8, 677, 0, 0,
    0,
};
s32 D_800A6F90[] = {
    (s32)D_800A68F0, (s32)D_800A68F8, 99, (s32)D_800A6904,
    0, 100, 0, 0,
    0,
};
s32 D_800A6FB4[] = {
    0, 0, 1186, 0,
    0, 0,
};
s32 D_800A6FCC[] = {
    0x1602B, 65535,
};
s32 D_800A6FD4[] = {
    0x17022, 65535,
};
s32 D_800A6FDC[] = {
    0x17022, 65535,
};
s32 D_800A6FE4[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A6FF0[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A6FFC[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A7008[] = {
    33170, 0x1602B, 65535,
};
s32 D_800A7014[] = {
    0x17022, 65535,
};
s32 D_800A701C[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A7028[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A7034[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A7040[] = {
    33170, 0x1602B, 65535,
};
s32 D_800A704C[] = {
    0x17022, 65535,
};
s32 D_800A7054[] = {
    0x1602B, 65535,
};
s32 D_800A705C[] = {
    0x17022, 65535,
};
s32 D_800A7064[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A7070[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A707C[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A7088[] = {
    33170, 0x1602B, 65535,
};
s32 D_800A7094[] = {
    0x17022, 65535,
};
s32 D_800A709C[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A70A8[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A70B4[] = {
    0x1602B, 0x18192, 65535,
};
s32 D_800A70C0[] = {
    33170, 0x1602B, 65535,
};
s32 D_800A70CC[] = {
    0x1701A, 65535,
};
s32 D_800A70D4[] = {
    0x1701A, 65535,
};
s32 D_800A70DC[] = {
    0x1701A, 65535,
};
s32 D_800A70E4[] = {
    0x1701A, 65535,
};
s32 D_800A70EC[] = {
    0x1701A, 65535,
};
s32 D_800A70F4[] = {
    0x1701A, 65535,
};
s32 D_800A70FC[] = {
    0x18192, 0x17009, 65535,
};
s32 D_800A7108[] = {
    33170, 0x17009, 28698, 65535,
};
s32 D_800A7118[] = {
    33170, 0x1701A, 65535,
};
s32 D_800A7124[] = {
    0x17022, 65535,
};
s32 D_800A712C[] = {
    0x1701A, 65535,
};
s32 D_800A7134[] = {
    (s32)D_800A6FCC, (s32)D_800A690C, 0x4002D, 0xB000FF,
    3,
};
s32 D_800A7148[] = {
    (s32)D_800A6FD4, (s32)D_800A6924, 0x4002D, 0xB000FF,
    3,
};
s32 D_800A715C[] = {
    (s32)D_800A6FDC, (s32)D_800A693C, 0x5002F, 0xDB00C6,
    7,
};
s32 D_800A7170[] = {
    (s32)D_800A6FE4, (s32)D_800A699C, 0x5002F, 0xDB00C6,
    7,
};
s32 D_800A7184[] = {
    (s32)D_800A6FF0, (s32)D_800A69CC, 0x5002F, 0xDB00C6,
    7,
};
s32 D_800A7198[] = {
    (s32)D_800A6FFC, (s32)D_800A6A08, 0x5002F, 0xDB00C6,
    7,
};
s32 D_800A71AC[] = {
    (s32)D_800A7008, (s32)D_800A6A44, 0x5002F, 0xDB00C6,
    7,
};
s32 D_800A71C0[] = {
    (s32)D_800A7014, (s32)D_800A6A5C, 0x60032, 0xE700AD,
    7,
};
s32 D_800A71D4[] = {
    (s32)D_800A701C, (s32)D_800A6ABC, 0x60032, 0xE700AD,
    7,
};
s32 D_800A71E8[] = {
    (s32)D_800A7028, (s32)D_800A6AEC, 0x60032, 0xE700AD,
    7,
};
s32 D_800A71FC[] = {
    (s32)D_800A7034, (s32)D_800A6B28, 0x60032, 0xE700AD,
    7,
};
s32 D_800A7210[] = {
    (s32)D_800A7040, (s32)D_800A6B64, 0x60032, 0xE700AD,
    7,
};
s32 D_800A7224[] = {
    (s32)D_800A704C, (s32)D_800A6B7C, 0x70033, 0x93015C,
    1,
};
s32 D_800A7238[] = {
    (s32)D_800A7054, (s32)D_800A6B94, 0x70033, 0x93015C,
    1,
};
s32 D_800A724C[] = {
    (s32)D_800A705C, (s32)D_800A6BAC, 0x80034, 0xF400FA,
    3,
};
s32 D_800A7260[] = {
    (s32)D_800A7064, (s32)D_800A6C0C, 0x80034, 0xF400FA,
    3,
};
s32 D_800A7274[] = {
    (s32)D_800A7070, (s32)D_800A6C3C, 0x80034, 0xF400FA,
    3,
};
s32 D_800A7288[] = {
    (s32)D_800A707C, (s32)D_800A6C78, 0x80034, 0xF400FA,
    3,
};
s32 D_800A729C[] = {
    (s32)D_800A7088, (s32)D_800A6CB4, 0x80034, 0xF400FA,
    3,
};
s32 D_800A72B0[] = {
    (s32)D_800A7094, (s32)D_800A6CCC, 0x90037, 0x10100E0,
    3,
};
s32 D_800A72C4[] = {
    (s32)D_800A709C, (s32)D_800A6D2C, 0x90037, 0x10100E0,
    3,
};
s32 D_800A72D8[] = {
    (s32)D_800A70A8, (s32)D_800A6D68, 0x90037, 0x10100E0,
    3,
};
s32 D_800A72EC[] = {
    (s32)D_800A70B4, (s32)D_800A6DA4, 0x90037, 0x10100E0,
    3,
};
s32 D_800A7300[] = {
    (s32)D_800A70C0, (s32)D_800A6DD4, 0x90037, 0x10100E0,
    3,
};
s32 D_800A7314[] = {
    (s32)D_800A70CC, (s32)D_800A6DEC, 0xA009D, 0x93015C,
    1,
};
s32 D_800A7328[] = {
    (s32)D_800A70D4, (s32)D_800A6E04, 0xB009E, 0xDB00C6,
    7,
};
s32 D_800A733C[] = {
    (s32)D_800A70DC, (s32)D_800A6E40, 0xC009F, 0xF400FA,
    3,
};
s32 D_800A7350[] = {
    (s32)D_800A70E4, (s32)D_800A6E7C, 0xD00A0, 0xE700AD,
    7,
};
s32 D_800A7364[] = {
    (s32)D_800A70EC, (s32)D_800A6EB8, 0xE00A1, 0x10100E0,
    3,
};
s32 D_800A7378[] = {
    (s32)D_800A70F4, (s32)D_800A6EF4, 0xF00A2, 0xB000FF,
    3,
};
s32 D_800A738C[] = {
    (s32)D_800A70FC, (s32)D_800A6F0C, 0x1000CE, 0x93017B,
    7,
};
s32 D_800A73A0[] = {
    (s32)D_800A7108, (s32)D_800A6F90, 0x1000CE, 0x93017B,
    7,
};
s32 D_800A73B4[] = {
    (s32)D_800A7118, (s32)D_800A6FB4, 0x1000CE, 0x93017B,
    7,
};
s32 D_800A73C8[] = {
    0, 0, 0x1100DC, 0xA3017B,
    7,
};
s32 D_800A73DC[] = {
    (s32)D_800A7124, 0, 0x1200E1, 0x9E015B,
    1,
};
s32 D_800A73F0[] = {
    (s32)D_800A712C, 0, 0x13010E, 0x9E015B,
    1,
};
s32 D_800A7404[] = {
    (s32)D_800A7134, (s32)D_800A7148, (s32)D_800A715C, (s32)D_800A7170,
    (s32)D_800A7184, (s32)D_800A7198, (s32)D_800A71AC, (s32)D_800A71C0,
    (s32)D_800A71D4, (s32)D_800A71E8, (s32)D_800A71FC, (s32)D_800A7210,
    (s32)D_800A7224, (s32)D_800A7238, (s32)D_800A724C, (s32)D_800A7260,
    (s32)D_800A7274, (s32)D_800A7288, (s32)D_800A729C, (s32)D_800A72B0,
    (s32)D_800A72C4, (s32)D_800A72D8, (s32)D_800A72EC, (s32)D_800A7300,
    (s32)D_800A7314, (s32)D_800A7328, (s32)D_800A733C, (s32)D_800A7350,
    (s32)D_800A7364, (s32)D_800A7378, (s32)D_800A738C, (s32)D_800A73A0,
    (s32)D_800A73B4, (s32)D_800A73C8, (s32)D_800A73DC, (s32)D_800A73F0,
    0,
};
u8 D_800A7498[] = {
    0x01, 0x00, 0x40, 0x06, 0x3B, 0x02, 0x00, 0x05,
    0x08, 0x00, 0xAC, 0x01, 0x4B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x3D, 0x02,
    0x00, 0x03, 0x08, 0x00, 0x41, 0x00, 0xB0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x3A, 0x02, 0x00, 0x03, 0x08, 0x00, 0xA9, 0x01,
    0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x01, 0x32, 0x39, 0x08, 0x00,
    0xAC, 0x01, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x3C, 0x02, 0x00, 0x03,
    0x08, 0x00, 0xD6, 0x01, 0x95, 0x00, 0xB0, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x56, 0x00, 0xEF, 0x00,
    0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00,
    0xDC, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0x00, 0xCC, 0x00, 0xE8, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x01, 0xC9, 0x00, 0xE7, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x23, 0x01, 0xB9, 0x00,
    0xD1, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x01,
    0x93, 0x00, 0xA8, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x73, 0x01, 0x8C, 0x00, 0xA0, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x50, 0x01, 0x8B, 0x00, 0xA0, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x81, 0x01, 0x83, 0x00,
    0x99, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01,
    0x83, 0x00, 0x99, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x91, 0x01, 0x7B, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x0B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x01, 0x75, 0x00, 0x90, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x0C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xD0, 0x01, 0x95, 0x00,
    0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A75F0[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x01, 0x02, 0xF0, 0x01, 0xA0, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
StageFuncs D_800A7620 = { func_800A5998, func_800A5A84, func_800A5B18 };
s32 D_800A762C[] = {
    59, (s32)D_800A5B84,
#if VERSION_US
    0x1190000,
#elif VERSION_EU
    0x1200000,
#endif
    0, 0, 65, (s32)D_800A5C2C,
#if VERSION_US
    0x1190001,
#elif VERSION_EU
    0x1200001,
#endif
    0, 0, 1415, (s32)D_800A5CC8,
#if VERSION_US
    0x1190002,
#elif VERSION_EU
    0x1200002,
#endif
    0, (s32)func_800A5938, 1518, 0,
#if VERSION_US
    0x1190005,
#elif VERSION_EU
    0x1200005,
#endif
    (s32)func_800A52A0, 0, 1519, (s32)D_800A5F8C,
#if VERSION_US
    0x1190003,
#elif VERSION_EU
    0x1200003,
#endif
    0, 0, 1520, 0,
#if VERSION_US
    0x1190006,
#elif VERSION_EU
    0x1200006,
#endif
    (s32)func_800A5868, 0, 1521, (s32)D_800A5FA4,
#if VERSION_US
    0x1190004,
#elif VERSION_EU
    0x1200004,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
