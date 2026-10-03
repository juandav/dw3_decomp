#include "common.h"
#include "stage.h"
extern void (*D_800A4F58[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task) {
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

StageTask *func_800A4CEC(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A4F58[0]();
    return task;
}

extern s32 D_800A4ECC[];
extern s32 D_800A4F28[];
extern s32 D_800A4E28[];
extern s32 D_800A4EC4[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x6FD
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x70D
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A4ECC;
    D_800990B4.unk14 = D_800A4F28;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xB100, 0x12B00};
    D_800990B4.unk28 = D_800A4E28;
    D_800990B4.unk3C = 0xF;
    D_800990B4.unk40 = 0x603C0000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A4EC4;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4E98[];
extern s32 D_800A4EB0[];

s32 D_800A4E28[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000140, 0, 0x1FF0150,
};
s32 D_800A4E98[] = {
    0, 0, 4, 0,
    0, 0,
};
s32 D_800A4EB0[] = {
    0, (s32)D_800A4E98, 0x40084, 0x1010090,
    7,
};
s32 D_800A4EC4[] = {
    (s32)D_800A4EB0, 0,
};
s32 D_800A4ECC[] = {
    0x6400001, 0x37320132, 0xD8000A, 262,
    0x10000, 0x1380640, 0xA3D38, 0xAA0048,
    0, 0x6400001, 0x433E013E, 0x15C000A,
    225, 0x10000, 0x13E0640, 0xA433E,
    0xE50163, 0, 0, 0,
    0, 0, 0,
};
s32 D_800A4F28[] = {
    65535, 65535, 0x2A40001, 0x1A40412,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A4F58[])(void) = {
    func_800A4D48,
};
