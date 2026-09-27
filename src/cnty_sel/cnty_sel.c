#include "cnty_sel.h"

void CNTY_SEL_tickScreen(TaskHeader *task, MenuTask **menu) {
    Obj8001FBE0 loader;
    Resource *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        /* Wait for the sound bank requested by CNTY_SEL_start */
        if (D_80051194.unk4274() == 0) {
            D_8004D5B8.funcs.unk0[0]();
            D_8004D5B8.funcs.unk0[1](0xA000);
            D_8004D5B8.funcs.unk24(320, 240, 0, 0);
            func_8001FBE0(&loader);
            loader.methods[2](0x280, 0);
            loader.methods[3](0, 0x1F0);
            loader.methods[4](D_80044B68[0](CNTY_SEL_IMAGES));
            layer = D_8004D5B8.funcs.unk1C(&CNTY_SEL_screenRect, 3, CNTY_SEL_LAYER);
            layer->unk12C(layer, 0x1F, 0x1F, 0x1F);
            *menu = CNTY_SEL_startMenuTask();
            task->nextState(task);
            D_80051194.unk425C(CNTY_SEL_MUSIC);
        }
        break;
    case TASK_RUN:
    case TASK_TRIGGER:
        break;
    case TASK_END:
        D_80051194.unk427C(CNTY_SEL_MUSIC);
        break;
    }
}

TaskHeader *CNTY_SEL_start(void) {
    TaskHeader *task;

    ClearImage2(&CNTY_SEL_vramRect, 0, 0, 0);
    task = func_800144DC(CNTY_SEL_tickScreen, sizeof(TaskHeader), sizeof(MenuTask *));
    D_80051194.unk4268(CNTY_SEL_SOUND_BANK);
    return task;
}

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawBackground);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_getFadeLevel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawFade);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickBackground);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startBackgroundTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_stepAnimation);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawCursor);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_setCursorSelection);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickCursor);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startCursorTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_getTopPanelScale);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawTopPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickTopPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startTopPanelTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_getRightPanelScale);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawRightPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickRightPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startRightPanelTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_getLeftPanelScale);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawLeftPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickLeftPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startLeftPanelTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickMenu);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startMenuTask);
