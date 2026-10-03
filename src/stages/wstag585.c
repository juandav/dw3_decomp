#include "common.h"
#include "stage.h"
extern s32 D_800A5168[];
extern s32 D_800A52C0[];
extern s32 D_800A523C[];
extern u8 D_800A5184[];
extern u8 D_800A528C[];
extern u8 D_800A5244[];
extern void (*D_800A52BC[])(void);
void func_800A4CA4();
void func_800A4DD4();

/* Creates the event object of flags 0x4033 and 0x1C20 */
void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (FLAGS_00.checkCondition(0x4033, 0) && FLAGS_00.checkCondition(0x1C20, 1)) {
            children[0] = func_80084B80(0x1CC);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4D4C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A52BC[0]();
    return task;
}

void func_800A4DA8(void) {
    FLAGS_00.applyAction(0x4033, 1);
}

#if VERSION_US
void func_800A4DD4(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x4F4;
    D_800990B4.unkC = 0x4F50000;
    D_800990B4.unk10 = D_800A5244;
    D_800990B4.unk14 = D_800A528C;
    D_800990B4.unk1C = 0x4F3;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13200;
    D_800990B4.unk30 = 0x15B00;
    D_800990B4.unk28 = D_800A5184;
    D_800990B4.unk3C = 0x39;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A523C;
    D_800990B4.events = D_800A52C0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5168;
    D_8009A70C.unk40(0, 0x4F50001);
    D_8009A70C.unk40(7, 0x4F50002);
    D_8009A70C.unk40(4, 0x4F50003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag585", func_800A4DD4);
#endif

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
extern s32 D_800A5060[];
extern s32 D_800A506C[];
extern s32 D_800A5078[];
extern s32 D_800A5084[];
extern s32 D_800A5090[];
extern s32 D_800A509C[];
extern s32 D_800A50A8[];
extern s32 D_800A50B4[];
extern s32 D_800A50E4[];
extern s32 D_800A50F0[];
extern s32 D_800A50FC[];
extern s32 D_800A5108[];
extern s32 D_800A5114[];
extern s32 D_800A5120[];
extern s32 D_800A512C[];
extern s32 D_800A5138[];
extern s32 D_800A4FB8[];
extern s32 D_800A503C[];
extern s32 D_800A50C0[];
extern s32 D_800A5144[];
extern s32 D_800A51F4[];
extern s32 D_800A521C[];
extern s32 D_800A5204[];
extern s32 D_800A5228[];
extern s32 D_800A4EE8[];

s32 D_800A4EE8[] = {
    0x10600, 0x1000002, 0xEF0002, 0x1010180,
    0x10002, 0x3000005, 0x102001E, 0x1150002,
    0x5016E, 0x20302, 0x20101, 0x50001,
    0x1E0300, 0x20101, 0x70001, 0x3C0300,
    0x20101, 0x30001, 0x3C0300, 0x20101,
    0x50001, 0x3C0300, 512, 0x20001,
    0x3010002, 1536, 0x3000002, 60,
};
s32 D_800A4F58[] = {
    75, 12, 0x60080000,
};
s32 D_800A4F64[] = {
    75, 12, 0x60080000,
};
s32 D_800A4F70[] = {
    75, 12, 0x60080000,
};
s32 D_800A4F7C[] = {
    75, 12, 0x60080000,
};
s32 D_800A4F88[] = {
    75, 12, 0x60080000,
};
s32 D_800A4F94[] = {
    75, 12, 0x60080000,
};
s32 D_800A4FA0[] = {
    75, 12, 0x60080000,
};
s32 D_800A4FAC[] = {
    75, 12, 0x60080000,
};
s32 D_800A4FB8[] = {
    4, (s32)D_800A4F58, (s32)D_800A4F64, (s32)D_800A4F70,
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
    0, 0, 0x60040000,
};
s32 D_800A506C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5078[] = {
    0, 0, 0x60040000,
};
s32 D_800A5084[] = {
    0, 0, 0x60040000,
};
s32 D_800A5090[] = {
    0, 0, 0x60040000,
};
s32 D_800A509C[] = {
    0, 0, 0x60040000,
};
s32 D_800A50A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A50B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A50C0[] = {
    0, (s32)D_800A5060, (s32)D_800A506C, (s32)D_800A5078,
    (s32)D_800A5084, (s32)D_800A5090, (s32)D_800A509C, (s32)D_800A50A8,
    (s32)D_800A50B4,
};
s32 D_800A50E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A50F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A50FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5108[] = {
    0, 0, 0x60040000,
};
s32 D_800A5114[] = {
    0, 0, 0x60040000,
};
s32 D_800A5120[] = {
    0, 0, 0x60040000,
};
s32 D_800A512C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5138[] = {
    0, 0, 0x60040000,
};
s32 D_800A5144[] = {
    0, (s32)D_800A50E4, (s32)D_800A50F0, (s32)D_800A50FC,
    (s32)D_800A5108, (s32)D_800A5114, (s32)D_800A5120, (s32)D_800A512C,
    (s32)D_800A5138,
};
s32 D_800A5168[] = {
    42, 0, 0, (s32)D_800A4FB8,
    (s32)D_800A503C, (s32)D_800A50C0, (s32)D_800A5144,
};
u8 D_800A5184[] = {
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
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x00, 0x01,
    0xD8, 0x00, 0x00, 0x00, 0x50, 0x01, 0xFF, 0x01,
};
s32 D_800A51F4[] = {
    0x1020D, 0x1822F, 0x17013, 65535,
};
s32 D_800A5204[] = {
    0, (s32)D_800A51F4, 598, 0,
    0, 0,
};
s32 D_800A521C[] = {
    525, 0x11C20, 65535,
};
s32 D_800A5228[] = {
    (s32)D_800A521C, (s32)D_800A5204, 0x40021, 0x13E017B,
    1,
};
s32 D_800A523C[] = {
    (s32)D_800A5228, 0,
};
u8 D_800A5244[] = {
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x05,
    0x06, 0x00, 0x15, 0x01, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x33, 0x02,
    0x00, 0x05, 0x06, 0x00, 0x95, 0x01, 0x3D, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x00, 0x01, 0x00, 0x0B, 0x04, 0x00, 0xD6, 0x00,
    0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A528C[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x4D, 0x02, 0x58, 0x03, 0x7C, 0x03,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A52BC[])(void) = {
    func_800A4DD4,
};
s32 D_800A52C0[] = {
    460, (s32)D_800A4EE8,
#if VERSION_US
    0x1350007,
#elif VERSION_EU
    0x13C0007,
#endif
    0, (s32)func_800A4DA8, -1, 0,
    0, 0, 0,
};
