#include "game.h"

void func_80010F80(Fade *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn) {
        D_800553DC.playSound(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        D_800553DC.playSound(0x4001A);
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

void func_80011DF0(Task80011FBC *task, s32 fadeOut, s32 duration) {
    task->unk28(task, 1);
    task->unk10 = 1;
    task->fadeOut = fadeOut;
    if (fadeOut == 0) {
        task->level = 0;
        task->step = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->step = -(0xFF00 / duration);
    }
}

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

Unk8003EB68 *func_800134C0(void) {
    s32 index = func_80013484();

    if (index >= 0) {
        return &D_8003EB68[index];
    }
    return NULL;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001350C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001355C);

s32 func_80013590(s32 arg0, s32 arg1) {
    return func_80013534(arg0)->unk8 == arg1;
}

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

    D_8004AD90.free(slot->unkC);
    slot->unk4 = 0;
    slot->unkC = NULL;
    slot->unk8 = 0;
    slot->unk2 = 0;
    slot->unk0 = 0;
}

void func_80013C08(s32 file) {
    Slot *slot = func_800139D4();

    if (slot != NULL) {
        slot->unk8 = D_8004D708.unk38();
        return;
    }
    slot = func_80013A0C();
    slot->unk4 = file;
    slot->unkC = D_8004AD90.malloc(D_80047F04.getFileSectors(file) << 11, 3);
    slot->unk0 = 1;
    slot->unk8 = 0;
    slot->unk2 = 0;
    D_80044744 = 1;
}

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

s32 func_800141BC(s32 file) {
    return D_80044B78[file] != 0;
}

u16 func_800141D8(s32 file) {
    return D_80046DD4[file];
}

s32 func_800141F4(s32 file) {
    return D_80044B78[file];
}

void func_80014210(s32 file, s32 offset, void *pos) {
    CdIntToPos(D_80044B78[file] + offset, pos);
}

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

void *func_800144DC(void (*update)(void *), s32 size, s32 arg2) {
    return func_800143B4(update, size, arg2, 0);
}

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

s32 func_80015584(void) {
    s32 ret = 0;

    if ((D_800484E8.unk83 != 0 || D_800484E8.unk216 != 0) &&
        (D_800484E8.unkD5 != 0 || D_800484E8.unk268 != 0) &&
        (D_800484E8.unk123 != 0 || D_800484E8.unk2B6 != 0)) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800155F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015814);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015904);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015940);

s32 func_80015A34(void) {
    Unk80015A34 *obj = D_8004AF58.unkC(0x16, -1, -1);

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

void func_80015FC8(s32 item, s32 arg1) {
    if (arg1 != 0) {
        D_8004ABD8.unk24(item, 1);
        return;
    }
    D_800484E8.itemCounts[item]--;
    if (D_800484E8.itemCounts[item] < 0) {
        D_800484E8.itemCounts[item] = 0;
    }
}

void func_8001602C(s32 arg0, s32 arg1) {
    func_8008AEB4(0x700, arg0 * 2 + arg1 + 1, 0, 0, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016064);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016260);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800165D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001663C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016694);

void func_80016748(void) {
    D_8004AD90.bzero(&D_800484E8, 0x26BC);
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
    D_800484E8.unk30 = (D_8004D3B0.rand() & 0x1FF) + 0x200;
}

void func_800167DC(void) {
    s32 prev;

    if (D_800484E8.unk26C0 != 0) {
        prev = D_800484E8.unk26BC;
        D_800484E8.unk26BC = D_800484E8.unk26C0;
        D_800484E8.unk26C0 = 0;
        D_800484E8.unk26C4 = prev;
    }
}

s32 func_8001680C(void) {
    return D_8004ABAC;
}

s32 func_8001681C(void) {
    return D_8004ABA4;
}

s32 func_8001682C(void) {
    return D_8004ABB0;
}

void func_8001683C(s32 arg0, s32 arg1) {
    D_800484E8.unk26C0 = arg0;
    D_800484E8.unk26C8 = arg1;
}

s32 func_80016850(void) {
    return D_8004ABA8 != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016860);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016A30);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016A5C);

void func_80016AC8(s32 item, s32 count) {
    D_800484E8.itemFlags[item] = 1;
    D_800484E8.itemCounts[item] += count;
    if (D_800484E8.itemCounts[item] >= 10) {
        D_800484E8.itemCounts[item] = 9;
    }
}

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

Unk80048C50 *func_800177E8(s32 index) {
    return &D_80048C50[index];
}

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

void func_8001794C(void *dst, s32 size) {
    s32 i;

    if (size & 3) {
        u8 *p = dst;

        for (i = 0; i < size; i++) {
            *p++ = 0;
        }
    } else {
        s32 *p = dst;

        size >>= 2;
        for (i = 0; i < size; i++) {
            *p++ = 0;
        }
    }
}

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

void *func_80017BF0(s32 size) {
    void *ret = func_80017B20();

    func_8001794C(ret, size);
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

void func_80017C78(s32 arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = D_8004ADB8; i < 100; i++, p++) {
        if (*p == 0) {
            *p = arg0;
            return;
        }
    }
}

void func_80017CB0(s32 arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = D_8004ADB8; i < 100; i++, p++) {
        if (*p == arg0) {
            *p = 0;
            return;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017CE8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DA8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DDC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017ECC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017F38);

void func_80017F64(Task *task) {
    if (task != NULL) {
        task->unk28(task, 3);
        D_8004AF58.unk18(task);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017FAC);

void func_800180D8(void) {
    func_8001816C();
    D_8004AF78.pads[0].flags = 0;
}

void func_800180FC(void) {
    if (!(D_8004AF78.pads[0].flags & 0x40000000)) {
        func_80017FAC(0, 0x10);
    }
    if (!(D_8004AF78.pads[0].flags & 0x20000000)) {
        PadStartCom();
        D_8004AF78.pads[0].flags |= 0x20000000;
    }
}

void func_8001816C(void) {
    if (D_8004AF78.pads[0].flags & 0x20000000) {
        PadStopCom();
    }
    D_8004AF78.pads[0].flags &= ~0x20000000;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800181B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001837C);

u16 func_800184F0(s32 pad) {
    return D_8004AF78.pads[pad].unk48;
}

u16 func_80018514(s32 pad) {
    return D_8004AF78.pads[pad].unk4E;
}

u16 func_80018538(s32 pad) {
    return D_8004AF78.pads[pad].unk4A;
}

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
    if (!(D_8004AF78.pads[0].flags & 0xC00000)) {
        D_8004AF78.pads[0].flags |= 0x400000;
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
    if (D_8004AF78.pads[0].flags & 0x400000) {
        D_8004AF78.pads[0].flags &= ~0x400000;
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

u16 func_80018FB8(void) {
    s32 index = (D_8004D3AC + 1) & 0xFFF;

    D_8004D3AC = index;
    return D_8004B3AC[index];
}

void func_80018FEC(Unk80019DFC *obj, TextBuffer *buf, char *text) {
    s16 len;
    s16 cap;
    u16 size;

    if (text != NULL) {
        len = strlen(text);
        buf->len = len;
        if (len == 0) {
            obj->unkC1 = 0;
            return;
        }
        obj->unkC1 = 1;
        buf->dirty = 1;
        if (buf->data != NULL) {
            if (buf->cap <= buf->len) {
                D_8004AD90.free(buf->data);
                buf->data = NULL;
                buf->cap = 0;
            }
            if (buf->data != NULL) {
                goto copy;
            }
        }
        size = buf->len;
        if (size & 3) {
            cap = (size & ~3) + 8;
        } else {
            cap = size + 4;
        }
        buf->cap = cap;
        buf->data = D_8004AD90.malloc(cap, 2);
    copy:
        D_8004AD90.bzero(buf->data, buf->cap);
        memcpy(buf->data, text, buf->len);
    } else {
        func_80018FEC(obj, buf, D_800101D8);
    }
    if (obj->unkAA == 0) {
        func_80019E34(obj, 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019140);

void func_80019164(s32 arg0, void *arg1, s32 arg2) {
    func_80019360(arg0, arg1, arg2, 0);
}

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

s32 func_8001A820(s32 arg0, TextBuffer *buf) {
    if ((u8)buf->data[buf->pos + 2] < 6) {
        func_80019360(arg0, D_8004853C, -1, (u8)buf->data[buf->pos + 2]);
        buf->data[buf->pos + 2] = 6;
    }
    return 0x8003;
}

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
        D_8004AD90.free(task->unk64);
    }
    task->unk64 = NULL;
    task->unk60 = 0;
}

void func_8001B108(Task8001B3A0 *task, s32 *data) {
    task->data = data;
    if (data[0] == 0x4E454C52) {
        task->compressed = 1;
        task->size = data[1];
    } else {
        task->compressed = 0;
        task->size = 0;
    }
    data += 2;
    task->unk54 = data;
    task->unk68 = data;
}

void func_8001B148(Task8001B3A0 *task) {
    if (task->size > task->unk60) {
        if (task->unk64 != NULL) {
            D_8004AD90.free(task->unk64);
        }
        task->unk64 = D_8004AD90.malloc(task->size, 2);
        task->unk60 = task->size;
    }
    task->unk6C = task->unk64;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B1D0);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B2B8);

void func_8001B314(Task8001B3A0 *task, s32 *data, s32 arg2) {
    task->unk70 = arg2;
    func_8001B108(task, data);
    if (task->compressed) {
        func_8001B148(task);
        task->unk2C(task, 1);
    }
}

void *func_8001B368(Task8001B3A0 *task) {
    if (task->unk10 != 0) {
        return NULL;
    }
    if (task->compressed != 0) {
        return task->unk64;
    }
    return task->data;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B3A0);

void func_8001B434(void) {
    Task8001B3A0 *task = func_800144DC(func_8001B3A0, 0x84, 0);

    task->unk74 = func_8001B2B8;
    task->unk80 = func_8001B0C0;
    task->unk7C = func_8001B314;
    task->unk78 = func_8001B368;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B490);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B5AC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B6A8);

Task *func_8001B804(s32 arg0) {
    Task *task = func_800144DC(func_8001B6A8, 0x6C, 0);

    task->unk50 = arg0;
    D_800553DC.playSound(0x40019);
    return task;
}

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
