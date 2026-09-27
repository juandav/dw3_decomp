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

s32 func_80011014(Fade *fade) {
    if (!fade->active) {
        return 1;
    }
    fade->level += fade->step;
    if (fade->step > 0) {
        if (fade->level > 0x1000) {
            fade->level = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->level < 0) {
        fade->level = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

void func_80011080(void) {
    Unk2744 *p;
    s32 i;
    s32 j;
    s32 index;

    for (i = 0; i < 3; i++) {
        index = D_800484E8.unk270C(i);
        if (index >= 0) {
            p = D_800484E8.unk2744(index);
            p->unk20 = p->unk22;
            p->unk24 = p->unk26;
            for (j = 2; j >= 0; j--) {
                p->unk42[j] = 0;
            }
        }
    }
}

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

void func_80011FBC(Task80011FBC *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        break;
    case 1:
        if (task->unk10 == 0) {
            break;
        }
        task->level += task->step;
        if (task->fadeOut == 0) {
            if (task->level > 0xFF00) {
                task->level = 0xFF00;
                task->state = 2;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = 2;
        }
        /* fallthrough */
    case 2:
        func_80011E78(task);
        break;
    case 3:
        break;
    }
}

void func_80012070(s32 arg0) {
    Task80011FBC *task = func_800144DC(func_80011FBC, 0x68, 0);

    task->unk64 = func_80011DF0;
    task->unk50 = arg0;
    task->unk54 = 0;
}

void func_800120B8(Fade *fade, s32 fadeIn) {
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

s32 func_8001214C(Fade *fade) {
    if (!fade->active) {
        return 1;
    }
    fade->level += fade->step;
    if (fade->step > 0) {
        if (fade->level > 0x1000) {
            fade->level = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->level < 0) {
        fade->level = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800121B8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800123E4);

s32 func_80012698(void) {
    s32 value = D_800484E8.unk26F8();

    if (value == 0x1000) {
        value = D_800484E8.unk34;
    }
    if (value >= 0x2D7) {
        return -1;
    }
    return value >= 0x270;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800126FC);

void func_80013434(s32 arg0, s32 arg1) {
    Task *task = func_800144DC(func_800126FC, 0xA0, 0xAC);

    task->unk50 = arg0;
    task->unk54 = 1;
    task->unk58 = arg1;
}

s32 func_80013484(s32 id) {
    Unk8003EB68 *entry;
    s32 i;

    for (i = 0, entry = D_8003EB68; i < 52; i++, entry++) {
        if (entry->id == id) {
            return i;
        }
    }
    return -1;
}

Unk8003EB68 *func_800134C0(s32 id) {
    s32 index = func_80013484(id);

    if (index >= 0) {
        return &D_8003EB68[index];
    }
    return NULL;
}

void func_8001350C(void) {
    s32 i;

    for (i = 7; i >= 0; i--) {
        D_80042728.unk58[i] = 0;
    }
}

Unk80041444 *func_80013534(s32 id) {
    if (id <= 0) {
        return NULL;
    }
    return &D_80041444[id];
}

u8 func_8001355C(s32 id) {
    return D_800427B4[func_80013534(id)->unk9];
}

s32 func_80013590(s32 arg0, s32 arg1) {
    return func_80013534(arg0)->unk8 == arg1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800135C0);

s32 func_8001366C(void) {
    s32 pos;

    func_8002E268(D_8005C4C0, 3);
    pos = CdPosToInt(D_8005C4C0);
    if (pos == D_80044710.unk28) {
        D_80044710.unk28 = pos + 1;
        return 0;
    }
    return -1;
}

void func_800136CC(s32 arg0) {
    if (arg0 == 1) {
        if (func_8001366C() != 0) {
            goto error;
        }
        func_8002E268((void *)D_80044710.unk24, 0x200);
        D_80044710.unk24 += 0x800;
        if (--D_80044710.unk20 != 0) {
            return;
        }
    } else {
    error:
        D_80044710.unk20 = -1;
    }
    func_8002DE88(0);
    CdControlF(9, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013758);

s32 func_80013880(void) {
    return D_80044710.state != 0;
}

void func_80013890(void) {
    D_80044710.state = 1;
    D_80044710.unk28 = D_80044710.unk1C;
    D_80044710.unk24 = D_80044710.unk10;
    D_80044710.unk20 = D_80044710.unkC;
    func_8002DE68(func_80013758);
    CdControlF(2, D_80044710.loc);
}

void func_800138EC(s32 file, s32 offset, s32 size, s32 arg3, s32 *done) {
    if (func_80013880() == 0) {
        D_80044710.unk4 = file;
        D_80044710.unk8 = offset;
        D_80044710.unk10 = arg3;
        D_80044710.unk14 = done;
        if (done != NULL) {
            *done = 0;
        }
        if (size == 0) {
            D_80044710.unkC = D_80047F04.getFileSectors(file);
        } else {
            D_80044710.unkC = size;
        }
        D_80047F04.unkC(file, offset, D_80044710.loc);
        D_80044710.unk1C = D_80047F04.unk8(file) + offset;
        func_80013890();
    }
}

Slot *func_800139D4(s32 file) {
    Slot *slot;
    s32 i;

    for (slot = D_80044748, i = 0; i < 64; i++, slot++) {
        if (slot->unk4 == file) {
            return slot;
        }
    }
    return NULL;
}

Slot *func_80013A0C(void) {
    Slot *slot;
    s32 i;

    for (slot = D_80044748, i = 0; i < 64; i++, slot++) {
        if (slot->unk4 == 0) {
            return slot;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013A44);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013AB4);

void func_80013BBC(void) {
    Slot *slot = func_80013AB4();

    D_8004AD84.free(slot->unkC);
    slot->unk4 = 0;
    slot->unkC = NULL;
    slot->unk8 = 0;
    slot->unk2 = 0;
    slot->unk0 = 0;
}

void func_80013C08(s32 file) {
    Slot *slot = func_800139D4(file);

    if (slot != NULL) {
        slot->unk8 = D_8004D708.unk38();
        return;
    }
    slot = func_80013A0C();
    slot->unk4 = file;
    slot->unkC = D_8004AD84.malloc(D_80047F04.getFileSectors(file) << 11, 3);
    slot->unk0 = 1;
    slot->unk8 = 0;
    slot->unk2 = 0;
    D_80044744.unk0 = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80013CB4);

void func_80013DF8(s32 arg0) {
    func_80013C08(arg0);
    do {
        func_80013CB4();
    } while (func_80013A44(arg0) != 0);
}

s32 *func_80013E34(u32 file) {
    Slot *slot = func_800139D4(file);

    if (slot != NULL && slot->unk0 == 3) {
        slot->unk8 = D_8004D708.unk38();
        return slot->unkC;
    }
    while (D_80044710.unk2C() != 0) {
    }
    func_80013DF8(file);
    return func_800139D4(file)->unkC;
}

void func_80013ED4(s32 file) {
    Slot *slot = func_800139D4(file);

    if (slot != NULL && slot->unk0 == 3) {
        D_8004AD84.free(slot->unkC);
        slot->unk4 = 0;
        slot->unkC = NULL;
        slot->unk8 = 0;
        slot->unk2 = 0;
        slot->unk0 = 0;
    }
}

void func_80013F38(void) {
    Slot *slot;
    s32 i;

    for (slot = D_80044748, i = 0; i < 64; i++, slot++) {
        if (slot->unk4 != 0) {
            D_8004AD84.free(slot->unkC);
            slot->unk4 = 0;
            slot->unkC = NULL;
            slot->unk8 = 0;
            slot->unk2 = 0;
            slot->unk0 = 0;
        }
    }
}

void func_80013FCC(u32 addr) {
    Slot *slot = D_80044748;
    s32 i;
    u32 end;

    for (i = 0; i < 64; i++, slot++) {
        if (slot->unk4 != 0) {
            end = (u32)slot->unkC + 0x20;
            end += D_80047F04.getFileSectors(slot->unk4) << 11;
            if (end >= addr) {
                D_8004AD84.free(slot->unkC);
                slot->unk4 = 0;
                slot->unkC = 0;
                slot->unk8 = 0;
                slot->unk2 = 0;
                slot->unk0 = 0;
            }
        }
    }
}

s32 func_800140B0(u32 id) {
    s32 index = id & 0xFFFF;
    s32 *table = func_80013E34(id >> 16);

    return table[index] + (s32)table;
}

s32 func_800140E8(u32 index, s32 *table) {
    return table[index & 0xFFFF] + (s32)table;
}

void func_80014100(void) {
    Slot *slot;
    s32 i;

    for (i = 0, slot = D_80044748; i < 64; i++, slot++) {
        if (slot->unk4 == 0) {
            slot->unk2 = 0;
        } else {
            slot->unk2 = 1;
        }
    }
}

void func_80014148(void) {
    Slot *slot = D_80044748;
    s32 now = D_8004D708.unk38();
    s32 i;

    for (i = 0; i < 64; i++, slot++) {
        if (slot->unk4 != 0 && slot->unk2 != 0) {
            slot->unk8 = now;
            slot->unk2 = 0;
        }
    }
}

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

void func_800142E0(Unk80017ECC *obj) {
    s32 i;
    s32 *items;

    if (obj->count != 0) {
        items = obj->items;
        for (i = 0; i < obj->count; i++) {
            if (items[i] != 0) {
                D_8004ADB8.funcs.unk1C(items[i]);
            }
        }
        D_8004AD84.free(obj->items);
    }
    D_8004AF58.unk8(obj);
    D_8004AD84.free(obj);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800143B4);

void *func_800144DC(void (*update)(void *), s32 size, s32 arg2) {
    return func_800143B4(update, size, arg2, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", main);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C4);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014884);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014898);

s32 func_80014A10(void) {
    long cmds;
    u_long result;
    s32 ret = MemCardSync(1, &cmds, &result);

    if (ret == 1) {
        D_80047F14.cmd = cmds;
        D_80047F14.result = result;
        if (result < 2 || result == 3) {
            D_80047F14.retries = 0;
        } else {
            if (++D_80047F14.retries < D_80047F14.maxRetries) {
                D_80047F14.unkA0 = ret;
                return 0;
            }
            D_80047F14.retries = 0;
            D_80047F14.unkA0 = 0;
        }
    }
    return ret;
}

s32 func_80014AAC(s32 port) {
    switch (D_80047F14.state) {
    case 0:
    default:
        while (MemCardExist(port << 4) == 0) {
            func_80014A10();
        }
        D_80047F14.state = 1;
        break;
    case 1:
        if (func_80014A10() != 0) {
            D_80047F14.state = 0;
            if (D_80047F14.result == 0) {
                return 1;
            }
            return D_80047F14.result + 1;
        }
        if (D_80047F14.unkA0 != 0) {
            D_80047F14.unkA0 = 0;
            while (MemCardExist(port << 4) == 0) {
                func_80014A10();
            }
        }
        break;
    }
    return 0;
}

s32 func_80014B8C(s32 port) {
    switch (D_80047F14.state) {
    case 0:
    default:
        while (MemCardAccept(port << 4) == 0) {
            func_80014A10();
        }
        D_80047F14.state = 2;
        break;
    case 2:
        if (func_80014A10() != 0) {
            D_80047F14.state = 0;
            if (D_80047F14.result == 0) {
                return 1;
            }
            return D_80047F14.result + 1;
        }
        if (D_80047F14.unkA0 != 0) {
            D_80047F14.unkA0 = 0;
            while (MemCardAccept(port << 4) == 0) {
                func_80014A10();
            }
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014C6C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80014F2C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800151F0);

s32 func_800153E8(s32 arg0) {
    s32 ret = func_800151F0(arg0, 0);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015420(s32 arg0) {
    s32 ret = func_800151F0(arg0, 1);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015458(s32 arg0) {
    s32 ret = func_800151F0(arg0, 2);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015490(void) {
    return 2;
}

s32 func_80015498(u8 *data, s32 size, char expected) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < size; i++) {
        sum ^= *data++;
    }
    return ((expected ^ sum) & 0xFF) == 0;
}

u8 func_800154CC(u8 *data, s32 size) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < size; i++) {
        sum ^= *data++;
    }
    return sum;
}

s32 func_800154F8(u8 *bits, s32 index, s32 set) {
    s32 byte = index >> 3;
    s32 mask = 1 << (index & 7);

    if (set != 0) {
        return (bits[byte] & mask) != 0;
    }
    return (bits[byte] & mask) == 0;
}

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

    if ((D_800484E8.unk7C[7] != 0 || D_800484E8.unk20F[7] != 0) &&
        (D_800484E8.unk7C[0x59] != 0 || D_800484E8.unk20F[0x59] != 0) &&
        (D_800484E8.unk7C[0xA7] != 0 || D_800484E8.unk20F[0xA7] != 0)) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_800155F8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015814);

s32 func_80015904(s32 arg0, s32 index) {
    s32 value = D_8004AB24;
    s32 min = D_80048468[index][0];
    s32 max = D_80048468[index][1];
    s32 ret = 0;

    if (value >= min) {
        ret = max >= value;
    }
    return ret;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015940);

s32 func_80015A34(void) {
    Unk80015A34 *obj = D_8004AF58.unkC(0x16, -1, -1);

    obj->unk2C(obj, 3);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015A78);

s32 func_80015BB0(s32 value, s32 mode) {
    if (mode != 0) {
        if (D_8004AB24 == value) {
            return 1;
        }
    } else {
        if (D_8004AB24 != value) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015BEC(s32 index, s32 mode) {
    if (mode != 0) {
        if (D_800484E8.unk7C[index] != 0 || D_800484E8.unk20F[index] != 0) {
            return 1;
        }
    } else {
        if (D_800484E8.unk7C[index] == 0 && D_800484E8.unk20F[index] == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015C58(s32 item, s32 have) {
    if (have != 0) {
        if (D_800484E8.itemCounts[item] != 0) {
            return 1;
        }
    } else {
        if (D_800484E8.itemCounts[item] == 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80015CA4);

s32 func_80015D90(s32 id) {
    if (id < 30) {
        if (D_800484E8.unk44 == id + 1) {
            return 1;
        }
    } else {
        if (D_800484E8.unk46 == id - 29) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015DD8(s32 slot, s32 item) {
    Unk80048C50 *d = &D_80048C50[slot];
    u8 *info = *D_800427A4(item);
    s16 *equip = d->equip;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (equip[i] == item) {
            if (info[2] == 7) {
                d->equip[2] = 0;
                d->equip[3] = 0;
            } else {
                equip[i] = 0;
            }
            return 1;
        }
    }
    return 0;
}

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

s32 func_800165D8(u16 *list) {
    u16 a;

    for (a = *list; a != 0xFFFF; a = *list) {
        list++;
        if (!func_80016064(a, *list++)) {
            return 0;
        }
    }
    return 1;
}

void func_8001663C(u16 *list) {
    u16 a;

    for (a = *list; a != 0xFFFF; a = *list) {
        list++;
        func_80016260(a, *list++);
    }
}

void func_80016694(void) {
    s32 i;
    u8 *p;

    if (D_8004ABB8 != 0) {
        for (i = 2, p = &D_80048280[i]; i >= 0; i--) {
            *p-- = 0;
        }
        func_80016260(0x12, 0);
    }
    if (D_8004ABD8.unk18() == 0x700) {
        func_80016260(0x11, 1);
        func_80016260(0x12, 1);
        if (D_80048284 != 0) {
            func_80016260(0x10, 1);
        } else {
            func_80016260(0x10, 0);
        }
        D_80048284 = 0;
    }
}

void func_80016748(void) {
    D_8004AD84.bzero(&D_800484E8, 0x26BC);
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

s32 func_80016A30(u32 index) {
    if (index >= 3) {
        return -1;
    }
    return D_800484E8.unk70[index];
}

void func_80016A5C(s32 set) {
    s32 i;
    u8 slot;

    for (i = 0; i < 3; i++) {
        slot = D_8004AC38[set][i];
        D_800484E8.unk70[i] = slot;
        D_800484E8.records[slot].unk4 = slot + 3;
    }
    D_8004AB28 = set;
}

void func_80016AC8(s32 item, s32 count) {
    D_800484E8.itemFlags[item] = 1;
    D_800484E8.itemCounts[item] += count;
    if (D_800484E8.itemCounts[item] >= 10) {
        D_800484E8.itemCounts[item] = 9;
    }
}

void func_80016B08(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        func_80016AC8(D_8004AC44[i], 1);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 40; i++) {
            D_800484E8.unk628[j].items[i] = D_8004AC44[i];
        }
    }
}

void func_80016BA8(void) {
    D_800484E8.playTimeMaxed = 0;
    D_800484E8.playSeconds = 0;
    D_800484E8.playMinutes = 0;
    D_800484E8.playHours = 0;
    D_800484E8.playFrames = 0;
}

void func_80016BC8(void) {
    if ((D_800484E8.playFrames >> 8) >= 60) {
        D_800484E8.playFrames &= 0xFF;
        if (++D_800484E8.playSeconds >= 60) {
            D_800484E8.playSeconds = 0;
            if (++D_800484E8.playMinutes >= 60) {
                D_800484E8.playMinutes = 0;
                if (++D_800484E8.playHours >= 1000) {
                    D_800484E8.playHours = 999;
                    D_800484E8.playMinutes = 59;
                    D_800484E8.playSeconds = 59;
                    D_800484E8.playTimeMaxed = 1;
                }
            }
        }
    }
}

s32 func_80016C74(u32 index) {
    if (index >= 3) {
        return -1;
    }
    return D_800484E8.records[D_800484E8.unk70[index]].unk4 - 3;
}

void func_80016CC4(s32 slot, u32 stat, s16 value) {
    Unk80048C50 *d = &D_80048C50[slot];
    s16 *p = d->stats;

    if (stat < 19) {
        p += stat;
        *p = value;
        if (value < 0) {
            *p = 0;
            return;
        }
        if (stat < 2) {
            if (value >= 100) {
                *p = 99;
            }
        } else if (stat - 2 < 4) {
            if (value >= 10000) {
                *p = 9999;
            }
        } else if (value >= 1000) {
            *p = 999;
        }
    }
}

void func_80016D64(s32 slot, u32 stat, s32 delta) {
    Unk80048C50 *d = &D_80048C50[slot];
    s16 *stats = d->stats;
    s16 value;

    if (stat < 19) {
        stats += stat;
        value = *stats + delta;
        *stats = value;
        if (value < 0) {
            *stats = 0;
        } else if (stat < 2) {
            if (value >= 100) {
                *stats = 99;
            }
        } else if (stat - 2 < 4) {
            if (value >= 10000) {
                *stats = 9999;
            }
        } else if (value >= 1000) {
            *stats = 999;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80016E10);

void func_80017214(s16 *p, s32 stat, s32 delta) {
    s32 i;
    s16 value;

    if (stat == 7) {
        for (i = 0; i < 6; i++) {
            value = p[i + 6] + delta;
            p[i + 6] = value;
            if (value >= 1000) {
                p[i + 6] = 999;
            }
        }
    } else if (stat - 1 < 6U) {
        value = p[stat + 5] + delta;
        p[stat + 5] = value;
        if (value >= 1000) {
            p[stat + 5] = 999;
        }
    } else if (stat - 8 < 7U) {
        value = p[stat + 4] + delta;
        p[stat + 4] = value;
        if (value >= 1000) {
            p[stat + 4] = 999;
        }
    }
}

s32 func_800172E8(s32 slot, s32 id) {
    s32 i;

    for (i = 0; i < 44; i++) {
        if (D_800484E8.records[slot].entries[i].unk0 < 3) {
            continue;
        }
        if (D_800484E8.records[slot].entries[i].unk0 == id) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017348);

void func_8001746C(s32 slot, s16 *ids) {
    s32 i;
    s32 index;

    for (i = 0; i < 3; i++) {
        index = func_800172E8(slot, ids[i]);
        if (index >= 0) {
            D_800484E8.records[slot].unk54[i] = D_800484E8.records[slot].entries[index].unk0;
        } else {
            D_800484E8.records[slot].unk54[i] = -1;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017534);

INCLUDE_ASM("asm/main/nonmatchings/game", func_800175C0);

s32 func_800176B8(s32 slot, s32 id, Unk80048C50Entry *out) {
    s32 i = func_800172E8(slot, id);

    if (i != -1) {
        *out = D_800484E8.records[slot].entries[i];
    }
    return i;
}

s32 func_80017750(s32 slot, s32 id, Unk80048C50Entry *in) {
    s32 i = func_800172E8(slot, id);

    if (i != -1) {
        D_800484E8.records[slot].entries[i] = *in;
    }
    return i;
}

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

void func_80017880(s32 tag) {
    MemBlock *block;

    for (block = D_8004AD84.first; block->flags != 1; block = block->next) {
        if (block->flags == tag) {
            func_8001780C(block + 1);
        }
    }
}

void func_800178F8(void) {
    MemBlock *start;
    MemBlock *last;

    D_8004AD84.end = (MemBlock *)0x801FF000;
    last = (MemBlock *)0x801FEFF4;
    start = D_8005C2F8;
    D_8004AD84.first = start;
    D_8004AD84.size = (u8 *)0x801FF000 - (u8 *)start;
    start->prev = start;
    start->next = last;
    start->flags = 0;
    last->prev = start;
    last->flags = 1;
    last->next = D_8004AD84.end;
}

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

void *func_80017B20(s32 size, s32 tag) {
    void *ptr;

    while ((ptr = func_800179C8(size, tag)) == NULL) {
        D_80044744.outOfMemory();
    }
    return ptr;
}

void func_80017B88(s32 arg0, s32 arg1) {
    while (func_80017A78(arg0, arg1) == 0) {
        D_80044744.outOfMemory();
    }
}

void *func_80017BF0(s32 size, s32 tag) {
    void *ret = func_80017B20(size, tag);

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

void func_80017C50(void) {
    s32 i;

    for (i = 99; i >= 0; i--) {
        D_8004ADB8.list[i] = 0;
    }
}

void func_80017C78(s32 arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = D_8004ADB8.list; i < 100; i++, p++) {
        if (*p == 0) {
            *p = arg0;
            return;
        }
    }
}

void func_80017CB0(s32 arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = D_8004ADB8.list; i < 100; i++, p++) {
        if (*p == arg0) {
            *p = 0;
            return;
        }
    }
}

void *func_80017CE8(void) {
    s32 i;
    s32 *e;

    for (i = D_8004ADB8.unk19C; i < 100; i++) {
        e = (s32 *)D_8004ADB8.list[i];
        if (e != NULL && (D_8004ADB8.unk190 == -1 || e[0] == D_8004ADB8.unk190) &&
            (D_8004ADB8.unk194 == -1 || e[1] == D_8004ADB8.unk194) &&
            (D_8004ADB8.unk198 == -1 || e[2] == D_8004ADB8.unk198)) {
            D_8004ADB8.unk19C = i + 1;
            return (void *)D_8004ADB8.list[i];
        }
    }
    return NULL;
}

void func_80017DA8(s32 arg0, s32 arg1, s32 arg2) {
    D_8004ADB8.unk190 = arg0;
    D_8004ADB8.unk194 = arg1;
    D_8004ADB8.unk198 = arg2;
    D_8004ADB8.unk19C = 0;
    func_80017CE8();
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017DDC);

INCLUDE_ASM("asm/main/nonmatchings/game", func_80017ECC);

s32 func_80017F38(s32 arg0) {
    if (arg0 != 0) {
        return func_80017DDC(arg0);
    }
    return 0;
}

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

u8 func_8001861C(s32 pad, s32 index) {
    return D_8004AF78.pads[pad].unkA4[index];
}

s32 func_80018644(void) {
    return 0;
}

void func_8001864C(void) {
}

s32 func_80018654(s32 arg0) {
    if (D_8004AF78.pads[0].flags & 0x800000) {
        if (D_8004AF78.unk3D6 == arg0) {
            return 1;
        }
        return -1;
    }
    return 0;
}

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

s32 func_8001873C(s32 arg0) {
    if (D_8004AF78.pads[0].flags & 0x400000) {
        if (D_8004AF78.unk3D6 == arg0) {
            return 1;
        }
        return -1;
    }
    return 0;
}

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
                D_8004AD84.free(buf->data);
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
        buf->data = D_8004AD84.malloc(cap, 2);
    copy:
        D_8004AD84.bzero(buf->data, buf->cap);
        memcpy(buf->data, text, buf->len);
    } else {
        func_80018FEC(obj, buf, D_800101D8);
    }
    if (obj->unkAA == 0) {
        func_80019E34(obj, 0);
    }
}

void func_80019140(Unk80019DFC *obj, char *text) {
    func_80018FEC(obj, &obj->text[0], text);
}

void func_80019164(Unk80019DFC *obj, char *text, s32 id) {
    func_80019360(obj, text, id, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80019184);

void func_8001922C(Unk80019DFC *obj, u32 index, s32 value) {
    u8 buf[16];
    u8 *p;
    s32 i;

    if (index >= 6) {
        func_80019140(obj, D_800101FC);
        return;
    }
    for (i = 15, p = &buf[i]; i >= 0; i--) {
        *p-- = 0;
    }
    func_80019184(buf, value);
    for (i = 0; buf[i] != 0; i++) {
        buf[i] -= 0x2C;
    }
    func_80018FEC(obj, &obj->text[index], buf);
    obj->text[index].dirty = 0;
}

void func_80019308(Unk80019DFC *obj, char *text, s32 index) {
    if (index < 1 || index > 5) {
        func_80019140(obj, D_80010230);
    } else {
        func_80018FEC(obj, &obj->text[index], text);
    }
}

void func_80019360(Unk80019DFC *obj, char *text, s32 id, s32 index) {
    Obj8001F8F8 cls;
    char *str;

    if (id >= 0) {
        func_8001F8F8(&cls);
        str = cls.unk0(text, id);
        if (str == NULL) {
            return;
        }
        func_80018FEC(obj, &obj->text[index], str);
    } else {
        func_80018FEC(obj, &obj->text[index], text);
    }
    obj->text[index].dirty = 0;
}

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

void func_80019E34(Unk80019DFC *obj, s32 arg1) {
    if (arg1 <= 0) {
        obj->unkA8 = 0;
        obj->unkAA = 0;
        obj->unkA4 = obj->text[0].len;
        return;
    }
    obj->unkA4 = 0;
    obj->unkA8 = 0;
    obj->unkAA = arg1;
    obj->unkA6 = 0;
}

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
    if (arg0->text[0].len == 0) {
        arg0->unkC1 = 0;
    } else {
        arg0->unkC1 = arg1;
    }
}

void func_80019ED8(Unk80019DFC *obj, u8 type) {
    Obj8001F8F8 cls;

    if (type != 0) {
        func_8001F8F8(&cls);
        obj->unkBC = cls.unk4(&obj->text[0], obj->unk50, obj->unkB4);
    } else {
        obj->unkBC = 0;
    }
}

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

s32 func_8001A364(Unk80019DFC *obj, TextBuffer *buf) {
    switch (buf->data[buf->pos + 1]) {
    case 0:
    default:
        func_80019C2C(obj);
        break;
    case 7:
        obj->unkA6 = buf->pos + 2;
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A3B8);

s32 func_8001A4A8(Unk80019DFC *obj, TextBuffer *buf) {
    if (buf->data[buf->pos + 2] < 5) {
        obj->unkC = 2;
        obj->unk10 = 1;
        if (buf->data[buf->pos + 2] < 1 || buf->data[buf->pos + 2] > 4) {
            obj->unk14 = 0;
        } else {
            obj->unk14 = buf->data[buf->pos + 2];
        }
        obj->unk18 = buf->pos + 2;
        return 0;
    }
    return 0x8003;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A530);

s32 func_8001A684(void) {
    return 0x8003;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001A68C);

s32 func_8001A7AC(Unk80019DFC *obj, TextBuffer *buf) {
    if (buf->data[buf->pos + 2] < 0xFF) {
        obj->unkC = 2;
        obj->unk10 = 0;
        obj->unk14 = buf->data[buf->pos + 2];
        buf->data[buf->pos + 2] = 0xFF;
        obj->unkA8 = 0;
        return 0x8000;
    }
    return 0x8003;
}

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
        D_8004AD84.free(task->unk64);
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
            D_8004AD84.free(task->unk64);
        }
        task->unk64 = D_8004AD84.malloc(task->size, 2);
        task->unk60 = task->size;
    }
    task->unk6C = task->unk64;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001B1D0);

void *func_8001B2B8(Task8001B3A0 *task, s32 *data) {
    task->unk70 = 0x10000000;
    func_8001B108(task, data);
    if (task->compressed) {
        func_8001B148(task);
        func_8001B1D0(task);
        return task->unk64;
    }
    return data;
}

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

void func_8001B3A0(Task8001B3A0 *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        break;
    case 1:
        if (task->unk10 != 0 && task->unk10 == task->state) {
            func_8001B1D0(task);
        }
        break;
    case 2:
        break;
    case 3:
        if (task->unk64 != NULL) {
            D_8004AD84.free(task->unk64);
        }
        break;
    }
}

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

void func_8001C0C4(Task *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk28(task, 2);
        break;
    case 1:
        func_8001BB68(task);
        func_8001BCCC(task);
        break;
    case 2:
    case 3:
        break;
    }
}

void func_8001C130(s32 arg0) {
    Task *task = func_800144DC(func_8001C0C4, 0x60, 0);

    task->unk50 = arg0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C168);

void func_8001C454(Task8001C454 *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk68 = 0;
        if (task->unkB8 == 0) {
            task->unk60 = 0;
        } else {
            task->unk60 = 0x1000;
        }
        task->unk90 = 0;
        task->unk88 = task->unk54;
        task->unk8C = task->unk56;
        task->unk38(task);
        break;
    case 1:
        func_8001C168(task);
        break;
    case 2:
    case 3:
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C4D8);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C5C4);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001C72C);

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CAC0);

void func_8001CE60(void) {
    Obj8001FBE0 obj;

    func_8001FBE0(&obj);
    obj.methods[2](0x140, 0);
    obj.methods[4](D_80044744.unk424(0x2780000));
    D_80044744.unk418(0x278);
    D_80044744.unk40C(0x277);
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001CEE0);
