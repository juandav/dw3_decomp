#include "common.h"
#include "stage.h"
extern void (*D_800A68DC[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task) {
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

StageTask *func_800A4CF0(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A68DC[0]();
    return task;
}

void func_800A4D4C(void) {
    FLAGS_00.applyAction(0x405C, 1);
}

void func_800A4D78(void) {
    FLAGS_00.applyAction(0x406A, 1);
}

extern s32 D_800A61FC[];
extern s32 D_800A666C[];
extern s32 D_800A5660[];
extern s32 D_800A6168[];
extern CVECTOR D_800A4CA4;
extern s32 D_800A5644[];
extern s32 D_800A68E0[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x559
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x569
#endif
void func_800A4DA4(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A61FC;
    D_800990B4.unk14 = D_800A666C;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x49B00, 0x1E300};
    D_800990B4.unk28 = D_800A5660;
    D_800990B4.unk3C = 9;
    D_800990B4.unk40 = 0x60240000;
    D_800990B4.unk4C = D_800A6168;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5644;
    D_800990B4.events = D_800A68E0;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS != 0x26 || FLAGS_00.checkCondition(0x1A0A, 0) != 0) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}
