#include "wfightts.h"

extern RECT WFIGHTTS_screen;
extern s32 WFIGHTTS_stageCursor;
extern s32 WFIGHTTS_stageScroll;
extern char *WFIGHTTS_stageNames[];

void func_800A5A54();
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

INCLUDE_ASM("wfightts/nonmatchings/wfightts", func_800A5A54);

Task *WFIGHTTS_start(void) {
    return createTaskWithId(func_800A5A54, 0, 0, 0);
}

INCLUDE_ASM("wfightts/nonmatchings/wfightts", func_800A6954);

void func_800A6E80(s32 *arg, s32 *done) {
    BattleTestList *task = createTask(func_800A6954, sizeof(BattleTestList), 0x70);

    task->unk50 = arg;
    task->done = done;
    *done = 0;
}

INCLUDE_ASM("wfightts/nonmatchings/wfightts", func_800A6ECC);

void func_800A72EC(s32 *arg, s32 *done) {
    BattleTestList *task = createTask(func_800A6ECC, sizeof(BattleTestList), 0x3C);

    task->unk50 = arg;
    task->done = done;
    *done = 0;
}

/* The fight stage list: 14 of the 55 stages at a time (UP and DOWN, ten at a
   time with R1 held); it sets *result to the stage, 1-55, or to -1 */
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

INCLUDE_ASM("wfightts/nonmatchings/wfightts", func_800A764C);

BattleTestMotions *func_800A7B9C(s32 a, s32 b) {
    BattleTestMotions *task = createTaskWithId(func_800A764C, sizeof(BattleTestMotions), 0x70, 0xFFFF);

    task->unk250 = a;
    task->unk254 = b;
    return task;
}

INCLUDE_ASM("wfightts/nonmatchings/wfightts", func_800A7BE8);

BattleTestEffects *func_800A81D0(s32 a, s32 b) {
    BattleTestEffects *task = createTaskWithId(func_800A7BE8, sizeof(BattleTestEffects), 0x70, 0xFFFF);

    task->unkF8 = a;
    task->unkFC = b;
    return task;
}

INCLUDE_RODATA("wfightts/nonmatchings/wfightts", WFIGHTTS_strings);

/* The strings of the tables below, as rodata: the C can't emit them, since
   the padding between the strings of one table and the next isn't zeros */
extern char WFIGHTTS_strings[];
#define WFIGHTTS_STR(offset) (WFIGHTTS_strings + (offset))

/* The screen, for the layers */
RECT WFIGHTTS_screen = { 0, 0, 0x140, 0xF0 };
u16 D_800A8224[] = {
    0x017A, 0x01B9, 0x016E, 0x0073, 0x0103, 0x00CA, 0x016E, 0x01B4,
    0x0091, 0x00C5, 0x001F, 0x0089, 0x0097, 0x006C,
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
s32 D_800A8568[] = {
    0, 0,
};
s32 D_800A8570[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A8584[] = {
    0, 0,
};
s32 D_800A858C[] = {
    0, 0, 0, 0,
    0,
};
