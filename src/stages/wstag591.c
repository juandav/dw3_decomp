#include "common.h"
#include "stage.h"
extern s32 D_800A5060[];
extern s32 D_800A5130[];
extern u8 D_800A507C[];
extern u8 D_800A5170[];
extern u8 D_800A5138[];
extern void (*D_800A51A0[])(void);
void func_800A4CA4();
void func_800A4D48();

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
    D_800A51A0[0]();
    return task;
}

#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x5D7
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x5E7
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5138;
    D_800990B4.unk14 = D_800A5170;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x12700, 0x15A00};
    D_800990B4.unk28 = D_800A507C;
    D_800990B4.unk3C = 0x39;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A5130;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5060;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

extern s32 D_800A4E50[];
extern s32 D_800A4E5C[];
extern s32 D_800A4E68[];
extern s32 D_800A4E74[];
extern s32 D_800A4E80[];
extern s32 D_800A4E8C[];
extern s32 D_800A4E98[];
extern s32 D_800A4EA4[];
extern s32 D_800A4ED4[];
extern s32 D_800A4EE0[];
extern s32 D_800A4EEC[];
extern s32 D_800A4EF8[];
extern s32 D_800A4F04[];
extern s32 D_800A4F10[];
extern s32 D_800A4F1C[];
extern s32 D_800A4F28[];
extern s32 D_800A4F58[];
extern s32 D_800A4F64[];
extern s32 D_800A4F70[];
extern s32 D_800A4F7C[];
extern s32 D_800A4F88[];
extern s32 D_800A4F94[];
extern s32 D_800A4FA0[];
extern s32 D_800A4FAC[];
extern s32 D_800A4FDC[];
extern s32 D_800A4FE8[];
extern s32 D_800A4FF4[];
extern s32 D_800A5000[];
extern s32 D_800A500C[];
extern s32 D_800A5018[];
extern s32 D_800A5024[];
extern s32 D_800A5030[];
extern s32 D_800A4EB0[];
extern s32 D_800A4F34[];
extern s32 D_800A4FB8[];
extern s32 D_800A503C[];
extern s32 D_800A50EC[];
extern s32 D_800A5114[];
extern s32 D_800A50FC[];
extern s32 D_800A511C[];

s32 D_800A4E50[] = {
    116, 12, 0x60080000,
};
s32 D_800A4E5C[] = {
    116, 12, 0x60080000,
};
s32 D_800A4E68[] = {
    116, 12, 0x60080000,
};
s32 D_800A4E74[] = {
    116, 12, 0x60080000,
};
s32 D_800A4E80[] = {
    116, 12, 0x60080000,
};
s32 D_800A4E8C[] = {
    116, 12, 0x60080000,
};
s32 D_800A4E98[] = {
    116, 12, 0x60080000,
};
s32 D_800A4EA4[] = {
    116, 12, 0x60080000,
};
s32 D_800A4EB0[] = {
    4, (s32)D_800A4E50, (s32)D_800A4E5C, (s32)D_800A4E68,
    (s32)D_800A4E74, (s32)D_800A4E80, (s32)D_800A4E8C, (s32)D_800A4E98,
    (s32)D_800A4EA4,
};
s32 D_800A4ED4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F04[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F10[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F28[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F34[] = {
    0, (s32)D_800A4ED4, (s32)D_800A4EE0, (s32)D_800A4EEC,
    (s32)D_800A4EF8, (s32)D_800A4F04, (s32)D_800A4F10, (s32)D_800A4F1C,
    (s32)D_800A4F28,
};
s32 D_800A4F58[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F64[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F70[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F88[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F94[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FB8[] = {
    0, (s32)D_800A4F58, (s32)D_800A4F64, (s32)D_800A4F70,
    (s32)D_800A4F7C, (s32)D_800A4F88, (s32)D_800A4F94, (s32)D_800A4FA0,
    (s32)D_800A4FAC,
};
s32 D_800A4FDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5000[] = {
    0, 0, 0x60040000,
};
s32 D_800A500C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5018[] = {
    0, 0, 0x60040000,
};
s32 D_800A5024[] = {
    0, 0, 0x60040000,
};
s32 D_800A5030[] = {
    0, 0, 0x60040000,
};
s32 D_800A503C[] = {
    0, (s32)D_800A4FDC, (s32)D_800A4FE8, (s32)D_800A4FF4,
    (s32)D_800A5000, (s32)D_800A500C, (s32)D_800A5018, (s32)D_800A5024,
    (s32)D_800A5030,
};
s32 D_800A5060[] = {
    108, 0, 0, (s32)D_800A4EB0,
    (s32)D_800A4F34, (s32)D_800A4FB8, (s32)D_800A503C,
};
u8 D_800A507C[] = {
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
    0x40, 0x01, 0x00, 0x01, 0x58, 0x01, 0x00, 0x01,
    0x60, 0x00, 0x00, 0x00, 0x50, 0x01, 0xFF, 0x01,
};
s32 D_800A50EC[] = {
    0x1024D, 0x18234, 0x17013, 65535,
};
s32 D_800A50FC[] = {
    0, (s32)D_800A50EC, 389, 0,
    0, 0,
};
s32 D_800A5114[] = {
    589, 65535,
};
s32 D_800A511C[] = {
    (s32)D_800A5114, (s32)D_800A50FC, 0x40021, 0x13E017B,
    1,
};
s32 D_800A5130[] = {
    (s32)D_800A511C, 0,
};
u8 D_800A5138[] = {
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x05,
    0x06, 0x00, 0x15, 0x01, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x33, 0x02,
    0x00, 0x05, 0x06, 0x00, 0x95, 0x01, 0x3D, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5170[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xB7, 0x02, 0xEE, 0x04, 0xD2, 0x02,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A51A0[])(void) = {
    func_800A4D48,
};
