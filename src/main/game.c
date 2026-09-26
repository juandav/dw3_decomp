#include "common.h"

typedef struct Fade {
    s32 duration;
    s32 step;
    s32 level;
    s32 active;
} Fade;

typedef struct Task {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 state;
    /* 0x10 */ s32 substate;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 counter;
    /* 0x1C */ u8 unk1C[0x34];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} Task;

typedef struct Task80011FBC {
    /* 0x00 */ u8 unk0[0x50];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 unk58[0xC];
    /* 0x64 */ void (*unk64)(void *);
} Task80011FBC;

typedef struct Task8001ACC8 {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x44];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 dirty;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
} Task8001ACC8;

typedef struct Task8001B3A0 {
    /* 0x00 */ u8 unk0[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ void *unk64;
    /* 0x68 */ u8 unk68[0xC];
    /* 0x74 */ void (*unk74)(void *);
    /* 0x78 */ void (*unk78)(void *);
    /* 0x7C */ void (*unk7C)(void *);
    /* 0x80 */ void (*unk80)(void *);
} Task8001B3A0;

typedef struct Unk80015A34 {
    /* 0x00 */ u8 unk0[0x2C];
    /* 0x2C */ void (*unk2C)(struct Unk80015A34 *, s32);
} Unk80015A34;

typedef struct Slot {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ void *unkC;
} Slot;

typedef struct Callback {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ void (*func)(s32, void *, s32);
    /* 0x0C */ s32 unkC;
    /* 0x10 */ struct Callback *next;
} Callback;

typedef struct Sprite {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u8 unk8[0x10];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C[0x4C];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 callbackCount;
    /* 0x7C */ s32 hasCallbacks;
    /* 0x80 */ Callback *callbacks;
} Sprite;

typedef struct Rect16 {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
} Rect16;

typedef struct Unk80019DFC {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x3C];
    /* 0x50 */ u8 *unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 unk5C[6];
    /* 0x62 */ s16 unk62;
    /* 0x64 */ u8 unk64[0x4C];
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ u8 unkB8[6];
    /* 0xBE */ u8 unkBE;
    /* 0xBF */ u8 unkBF;
    /* 0xC0 */ u8 unkC0;
    /* 0xC1 */ u8 unkC1;
    /* 0xC2 */ s8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5[3];
    /* 0xC8 */ s32 unkC8;
    /* 0xCC */ s32 unkCC;
    /* 0xD0 */ s32 unkD0;
    /* 0xD4 */ s32 unkD4;
    /* 0xD8 */ s32 unkD8;
    /* 0xDC */ s32 unkDC;
    /* 0xE0 */ s32 unkE0;
    /* 0xE4 */ s32 unkE4;
} Unk80019DFC;

typedef struct MemBlock {
    /* 0x0 */ struct MemBlock *prev;
    /* 0x4 */ struct MemBlock *next;
    /* 0x8 */ s32 flags;
} MemBlock;

typedef struct Vec2 {
    s32 x;
    s32 y;
} Vec2;

typedef struct PadState {
    /* 0x000 */ s32 flags;
    /* 0x004 */ u8 unk4[0x3D2];
    /* 0x3D6 */ s16 unk3D6;
    /* 0x3D8 */ s32 unk3D8;
    /* 0x3DC */ s16 unk3DC;
} PadState;

typedef struct Unk800484E8 {
    /* 0x0000 */ u8 unk0[4];
    /* 0x0004 */ s8 unk4;
    /* 0x0005 */ u8 unk5[7];
    /* 0x000C */ s32 unkC;
    /* 0x0010 */ u8 unk10[0x20];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u8 unk34[0x2688];
    /* 0x26BC */ s32 unk26BC;
    /* 0x26C0 */ s32 unk26C0;
    /* 0x26C4 */ s32 unk26C4;
    /* 0x26C8 */ s32 unk26C8;
    /* 0x26CC */ s8 unk26CC;
    /* 0x26CD */ s8 unk26CD;
    /* 0x26CE */ s8 unk26CE;
    /* 0x26CF */ s8 unk26CF;
} Unk800484E8;

void PadStartCom(void);
void PadStopCom(void);
s32 VSyncCallback(void (*func)(void));

void *func_800144DC(void (*update)(void *), s32 size, s32 arg2);
void func_800119AC(void *task);
void func_80011DF0(void *task);
void func_80011FBC(void *task);
void func_800126FC(void *task);
s32 func_80013A44(s32);
Slot *func_80013AB4(void);
void func_80013C08(s32);
void func_80013CB4(void);
void func_80016860(void);
void func_8001816C(void);
void func_8001D070(void);
void func_8001794C(s32, s32);
s32 func_80017B20(void);
void func_80017FAC(s32, s32);
void func_8001837C(s32, s32, s32, s32);
void func_8001B2B8(void *task);
void func_8001B314(void *task);
void func_8001B368(void *task);
void func_8001B3A0(void *task);
void func_8001C0C4(void *task);
void func_80020764(void *task);
void func_8008AEB4(s32, s32, s32, s32, s32);

extern s32 D_80044710;
extern Unk800484E8 D_800484E8;
extern s32 D_8004ABA4;
extern s32 D_8004ABA8;
extern s32 D_8004ABAC;
extern s32 D_8004ABB0;
extern void (*D_8004AD94)(void *);
extern void *(*D_8004AD9C)(s32, s32);
extern void (*D_8004ADA8)(void *, s32);
extern void *(*D_8004AF64)(s32, s32, s32);
extern PadState D_8004AF78;
extern s32 D_8004D3AC;
extern s32 (*D_8004D3B4)(void);
extern u8 *D_8004D5A8;
extern s32 D_8004D5C0;
extern s32 D_8004D5C8;
extern s32 D_8004D5D0;
extern s32 D_8004D5D8;
extern s16 D_800553E8;
extern void (*D_800553F0)(s32);

void func_80010F80(Fade *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn) {
        D_800553F0(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        D_800553F0(0x4001A);
        fade->level = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011014);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011080);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011114);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800119AC);

void func_80011DB0(s32 arg0) {
    Task *task = func_800144DC(func_800119AC, 0xA0, 0x20);

    task->unk50 = arg0;
    task->unk54 = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011DF0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011E78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80011FBC);

void func_80012070(s32 arg0) {
    Task80011FBC *task = func_800144DC(func_80011FBC, 0x68, 0);

    task->unk64 = func_80011DF0;
    task->unk50 = arg0;
    task->unk54 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800120B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001214C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800121B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800123E4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80012698);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800126FC);

void func_80013434(s32 arg0, s32 arg1) {
    Task *task = func_800144DC(func_800126FC, 0xA0, 0xAC);

    task->unk50 = arg0;
    task->unk54 = 1;
    task->unk58 = arg1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013484);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800134C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001350C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001355C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013590);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800135C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001366C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800136CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013758);

s32 func_80013880(void) {
    return D_80044710 != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013890);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800138EC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800139D4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013A0C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013A44);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013AB4);

void func_80013BBC(void) {
    Slot *slot = func_80013AB4();

    D_8004AD94(slot->unkC);
    slot->unk4 = 0;
    slot->unkC = NULL;
    slot->unk8 = 0;
    slot->unk2 = 0;
    slot->unk0 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013C08);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013CB4);

void func_80013DF8(s32 arg0) {
    func_80013C08(arg0);
    do {
        func_80013CB4();
    } while (func_80013A44(arg0) != 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013E34);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013ED4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013F38);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013FCC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800140B0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800140E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014100);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014148);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800141BC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800141D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800141F4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014210);

void func_8001424C(Task *task, s32 state) {
    task->state = state;
    task->substate = 0;
    task->step = 0;
    task->counter = 0;
}

void func_80014260(Task *task, s32 substate) {
    task->substate = substate;
    task->step = 0;
    task->counter = 0;
}

void func_80014270(Task *task, s32 step) {
    task->step = step;
    task->counter = 0;
}

void func_8001427C(Task *task, s32 counter) {
    task->counter = counter;
}

void func_80014284(Task *task) {
    task->substate = 0;
    task->step = 0;
    task->counter = 0;
    task->state++;
}

void func_800142A0(Task *task) {
    task->step = 0;
    task->counter = 0;
    task->substate++;
}

void func_800142B8(Task *task) {
    task->counter = 0;
    task->step++;
}

void func_800142CC(Task *task) {
    task->counter++;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800142E0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800143B4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800144DC);

INCLUDE_ASM("asm/main/nonmatchings/game", main);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C4);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014884);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014898);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014A10);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014AAC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014B8C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014C6C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014F2C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800151F0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800153E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015420);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015458);

s32 func_80015490(void) {
    return 2;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015498);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800154CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800154F8);

void func_8001553C(u8 *bits, s32 index, s32 set) {
    s32 byte = index >> 3;
    s32 mask = 1 << (index & 7);

    if (set) {
        bits[byte] |= mask;
    } else {
        bits[byte] &= ~mask;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015584);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800155F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015814);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015904);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015940);

s32 func_80015A34(void) {
    Unk80015A34 *obj = D_8004AF64(0x16, -1, -1);

    obj->unk2C(obj, 3);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015A78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015BB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015BEC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015C58);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015CA4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015D90);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015DD8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015E8C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015FC8);

void func_8001602C(s32 arg0, s32 arg1) {
    func_8008AEB4(0x700, arg0 * 2 + arg1 + 1, 0, 0, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016064);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016260);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800165D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001663C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016694);

void func_80016748(void) {
    D_8004ADA8(&D_800484E8, 0x26BC);
    D_800484E8.unk26BC = 0xE01;
    D_800484E8.unk26C0 = 0xE01;
    D_800484E8.unk4 = 1;
    D_800484E8.unk26CC = 1;
    D_800484E8.unk26CD = 8;
    D_800484E8.unk26CF = 60;
    D_800484E8.unk26C8 = 0;
    D_800484E8.unk26CE = 0;
    D_800484E8.unkC = -1;
    func_80016860();
    D_800484E8.unk30 = (D_8004D3B4() & 0x1FF) + 0x200;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800167DC);

s32 func_8001680C(void) {
    return D_8004ABAC;
}

s32 func_8001681C(void) {
    return D_8004ABA4;
}

s32 func_8001682C(void) {
    return D_8004ABB0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001683C);

s32 func_80016850(void) {
    return D_8004ABA8 != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016860);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016A30);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016A5C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016AC8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016B08);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016BA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016BC8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016C74);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016CC4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016D64);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016E10);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017214);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800172E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017348);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001746C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800175C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800176B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017750);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800177E8);

void func_8001780C(void *ptr) {
    MemBlock *block = (MemBlock *)ptr - 1;
    MemBlock *prev;
    MemBlock *next;

    if (ptr != NULL) {
        prev = block->prev;
        next = block->next;
        block->flags = 0;
        if (next->flags == 0) {
            block->next = next->next;
            next->next->prev = block;
        }
        if (prev->flags == 0) {
            prev->next = block->next;
            block->next->prev = prev;
        }
    }
}

void func_80017878(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017880);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800178F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001794C);

void func_800179A4(s8 *dst, s8 value, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        *dst++ = value;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800179C8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017A78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017B20);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017B88);

s32 func_80017BF0(s32 arg0) {
    s32 ret = func_80017B20();

    func_8001794C(ret, arg0);
    return ret;
}

void func_80017C30(void *ptr, s32 arg1) {
    MemBlock *block = (MemBlock *)ptr - 1;

    if (arg1) {
        block->flags = 4;
    } else {
        block->flags = 2;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017C50);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017C78);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017CB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017CE8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DDC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017ECC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017F38);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017F64);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017FAC);

void func_800180D8(void) {
    func_8001816C();
    D_8004AF78.flags = 0;
}

void func_800180FC(void) {
    if (!(D_8004AF78.flags & 0x40000000)) {
        func_80017FAC(0, 0x10);
    }
    if (!(D_8004AF78.flags & 0x20000000)) {
        PadStartCom();
        D_8004AF78.flags |= 0x20000000;
    }
}

void func_8001816C(void) {
    if (D_8004AF78.flags & 0x20000000) {
        PadStopCom();
    }
    D_8004AF78.flags &= ~0x20000000;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800181B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001837C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800184F0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018514);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018538);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001855C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800185C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001861C);

s32 func_80018644(void) {
    return 0;
}

void func_8001864C(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018654);

s32 func_8001868C(s16 arg0, s32 arg1) {
    if (!(D_8004AF78.flags & 0xC00000)) {
        D_8004AF78.flags |= 0x400000;
        if (D_8004AF78.unk3D8 == 0) {
            D_8004AF78.unk3D6 = arg0;
            D_8004AF78.unk3D8 = arg1;
            D_8004AF78.unk3DC = 0;
            func_8001837C((arg0 * 16) & 0xF0, 0, 0, 0);
            return 1;
        }
    }
    return 0;
}

void func_80018700(void) {
    if (D_8004AF78.flags & 0x400000) {
        D_8004AF78.flags &= ~0x400000;
        D_8004AF78.unk3D8 = 0;
        D_8004AF78.unk3D6 = 0;
        D_8004AF78.unk3DC = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001873C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018774);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018868);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018BC0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018CA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018DC4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018EA0);

void func_80018FA8(s32 arg0) {
    D_8004D3AC = arg0 & 0xFFF;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018FB8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018FEC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019140);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019164);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019184);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001922C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019308);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019360);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800101D8);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800101FC);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_80010230);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_80010268);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019420);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019C2C);

void func_80019DFC(Unk80019DFC *arg0, s32 arg1) {
    u8 *entry;

    if (arg1 < 1 || arg1 > 3) {
        arg1 = 1;
    }
    entry = D_8004D5A8 + arg1 * 0x18;
    arg0->unk50 = entry;
    arg0->unkBE = *entry;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019E34);

void func_80019E64(Unk80019DFC *arg0, s16 arg1, s16 arg2) {
    arg0->unkB0 = arg1;
    arg0->unkB2 = arg2;
}

void func_80019E70(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkC0 = arg1;
}

void func_80019E78(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkBE = arg1;
}

void func_80019E80(Unk80019DFC *arg0, s16 arg1, s16 arg2) {
    if (arg1 != 0 || arg2 != 0) {
        arg0->unkC2 = 1;
        arg0->unkB4 = arg1;
        arg0->unkB6 = arg2;
    } else {
        arg0->unkC2 = 0;
        arg0->unkB4 = 0;
        arg0->unkB6 = 0;
    }
}

void func_80019EB8(Unk80019DFC *arg0, u8 arg1) {
    if (arg0->unk62 == 0) {
        arg0->unkC1 = 0;
    } else {
        arg0->unkC1 = arg1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019ED8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019F28);

void func_8001A094(Unk80019DFC *arg0, s32 arg1) {
    arg0->unkC8 = arg1;
}

void func_8001A09C(Unk80019DFC *arg0, s32 arg1, s32 arg2) {
    arg0->unkD8 = 0x1000;
    arg0->unkD0 = arg1;
    arg0->unkD4 = arg2;
    arg0->unkCC = 1;
}

void func_8001A0B8(Unk80019DFC *arg0, s32 arg1, s32 arg2) {
    arg0->unkE0 = arg1;
    arg0->unkE4 = arg2;
}

void func_8001A0C4(Unk80019DFC *arg0, s32 arg1) {
    arg0->unk58 = arg1;
}

void func_8001A0CC(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkBF = arg1;
}

void func_8001A0D4(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkC4 = arg1;
}

u8 func_8001A0DC(Unk80019DFC *arg0) {
    return arg0->unkC3;
}

u8 func_8001A0E8(Unk80019DFC *arg0) {
    return arg0->unkC1;
}

s32 func_8001A0F4(Unk80019DFC *arg0) {
    return arg0->unk10 == 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A108);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A364);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A3B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A4A8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A530);

s32 func_8001A684(void) {
    return 0x8003;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A68C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A7AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A820);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A890);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AAB4);

void func_8001ACC8(Task8001ACC8 *task, s32 arg1) {
    task->unk64 = arg1;
    if (arg1 == 0) {
        task->unk10 = 0;
        task->unk70 = 0;
    }
    task->dirty = 1;
}

void func_8001ACE4(Task8001ACC8 *task, s32 arg1, s32 arg2) {
    task->unk58 = arg1;
    task->unk5C = arg2;
    task->dirty = 1;
}

void func_8001ACF8(Task8001ACC8 *task, s32 arg1) {
    task->unk60 = arg1;
    task->dirty = 1;
}

void func_8001AD08(Task8001ACC8 *task, s32 arg1) {
    task->unk74 = arg1;
}

void func_8001AD10(Task8001ACC8 *task, s32 arg1) {
    task->unk78 = arg1;
}

void func_8001AD18(Task8001ACC8 *task, s32 arg1) {
    task->unk7C = arg1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AD20);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001AFE0);

void func_8001B0C0(Task8001B3A0 *task) {
    if (task->unk64 != NULL) {
        D_8004AD94(task->unk64);
    }
    task->unk64 = NULL;
    task->unk60 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B108);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B148);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B1D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B2B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B314);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B368);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B3A0);

void func_8001B434(void) {
    Task8001B3A0 *task = func_800144DC(func_8001B3A0, 0x84, 0);

    task->unk74 = func_8001B2B8;
    task->unk80 = (void (*)(void *))func_8001B0C0;
    task->unk7C = func_8001B314;
    task->unk78 = func_8001B368;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B490);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B5AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B6A8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B804);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B864);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BA7C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BB68);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BCCC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C0C4);

void func_8001C130(s32 arg0) {
    Task *task = func_800144DC(func_8001C0C4, 0x60, 0);

    task->unk50 = arg0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C168);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C454);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C4D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C5C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C72C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CAC0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CE60);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CEE0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D070);

void func_8001D114(void) {
    VSyncCallback(func_8001D070);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D138);

s32 func_8001D2EC(void) {
    return D_8004D5C0;
}

s32 func_8001D2FC(void) {
    return D_8004D5C8;
}

s32 func_8001D30C(void) {
    return D_8004D5D0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D31C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D3CC);

s32 func_8001D44C(void) {
    return D_8004D5D8;
}

void func_8001D45C(s32 arg0) {
    D_8004D5D8 = arg0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D468);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D4D4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D5E4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D668);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D6B4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D718);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D768);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D7C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D860);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D8E8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D984);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001D9C0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DA4C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DB8C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DBB0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DBE0);

s32 func_8001DC00(Sprite *sprite) {
    return sprite->unk68;
}

void func_8001DC0C(Sprite *sprite, u8 r, u8 g, u8 b) {
    sprite->unk19 = r;
    sprite->unk1B = b;
    sprite->unk1A = g;
    if (r | g | b) {
        sprite->unk18 = 1;
    } else {
        sprite->unk18 = 0;
    }
}

void func_8001DC3C(Sprite *sprite, s16 x, s16 y) {
    sprite->unk6C = x;
    sprite->unk6E = y;
}

void func_8001DC48(Sprite *sprite, Vec2 *out) {
    out->x = sprite->unk70 >> 8;
    out->y = sprite->unk74 >> 8;
}

void func_8001DC6C(Sprite *sprite, s32 x, s32 y) {
    sprite->unk70 = x;
    sprite->unk74 = y;
}

void func_8001DC78(Sprite *sprite, s32 dx, s32 dy) {
    sprite->unk70 += dx;
    sprite->unk74 += dy;
}

void func_8001DC94(Sprite *sprite, s16 x, s16 y) {
    sprite->x = x;
    sprite->y = y;
}

void func_8001DCA0(Sprite *sprite, s16 w, s16 h) {
    sprite->w = w;
    sprite->h = h;
}

void func_8001DCAC(Sprite *sprite, Rect16 *rect) {
    rect->x = sprite->x - sprite->unk6C + (sprite->unk70 >> 8);
    rect->y = sprite->y - sprite->unk6E + (sprite->unk74 >> 8);
    rect->w = sprite->w;
    rect->h = sprite->h;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DCFC);

void func_8001DD80(Sprite *sprite) {
    sprite->callbacks->unk0 = 0x7FFFFFFF;
    sprite->callbacks->unk4 = 0;
    sprite->callbacks->func = NULL;
    sprite->callbacks->unkC = 0;
    sprite->callbacks->next = NULL;
    sprite->hasCallbacks = 1;
}

void func_8001DDCC(Sprite *sprite, s32 count) {
    sprite->callbacks = D_8004AD9C(count * sizeof(Callback), 2);
    sprite->callbackCount = count;
    func_8001DD80(sprite);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DE24);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DF08);

void func_8001DF70(Sprite *sprite) {
    Callback *cb;

    if (sprite->hasCallbacks) {
        cb = sprite->callbacks;
        do {
            if (cb->func != NULL) {
                cb->func(cb->unkC, sprite, cb->unk4);
            }
            cb = cb->next;
        } while (cb != NULL);
        func_8001DD80(sprite);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001DFE8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E054);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E0D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E140);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E1A0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E3C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E3D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E474);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E51C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E570);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E584);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E598);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E5AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E5B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E5C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E7B0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E7DC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E894);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8A0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8BC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E8DC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E918);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001E950);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F1B4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F1D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F1EC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F200);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F20C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F22C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F31C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F328);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800102BC);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800102CC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F354);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F658);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F8F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F954);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F960);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F974);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001F988);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FA70);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FBD4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FBE0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FC68);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FCA4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FE3C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FF0C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001FFB4);

s32 func_80020064(void) {
    return D_800553E8 != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020074);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8002019C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020218);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020594);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020638);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020764);

void func_80020844(void) {
    func_800144DC(func_80020764, 0x50, 4);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80020870);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8002091C);

INCLUDE_RODATA("asm/main/nonmatchings/game", jtbl_800102EC);
