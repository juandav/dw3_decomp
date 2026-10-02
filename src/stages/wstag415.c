#include "common.h"
#include "stage.h"
void func_800A541C();
void func_800A4E6C();
extern void (*D_800A6694[])(void);
void func_800A5DC0();

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A4CA8);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A4CB8);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A4DAC);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A4E6C);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A50F4);

Task *func_800A5128(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 1;
    return task;
}

Task *func_800A5160(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 2;
    return task;
}

Task *func_800A5198(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 3;
    return task;
}

Task *func_800A51D0(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 4;
    return task;
}

Task *func_800A5208(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 5;
    return task;
}

Task *func_800A5240(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 6;
    return task;
}

Task *func_800A5278(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 7;
    return task;
}

Task *func_800A52B0(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 8;
    return task;
}

Task *func_800A52E8(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 9;
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5320);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A541C);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5850);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A595C);

Task *func_800A5990(s32 id) {
    Task *task = createTaskWithId(func_800A541C, 0x78, 0, id);

    task->key1 = 1;
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A59C8);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5B50);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5D4C);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5D84);

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5DC0);

StageTask *func_800A5E84(void *owner) {
    StageTask *task = createTask(func_800A5DC0, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A6694[0]();
    return task;
}

void func_800A5EE0(void) {
    FLAGS_00.applyAction(0x4018, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5F2C);
