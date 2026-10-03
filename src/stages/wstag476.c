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

INCLUDE_ASM("stages/nonmatchings/wstag476", func_800A4D48);

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
