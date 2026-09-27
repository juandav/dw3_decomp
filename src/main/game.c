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

void func_80011E78(Task80011FBC *task) {
    Resource *res = D_8004D5B8.funcs.unk2C(task->unk50);
    u_long *ot = (u_long *)res->unk138(res, task->unk54);
    POLY_F4 *poly = D_8004D5B8.funcs.allocPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->code = 0x2A;
    poly->r0 = poly->g0 = poly->b0 = task->level >> 8;
    poly->x0 = poly->x2 = 0;
    poly->x1 = poly->x3 = 320;
    poly->y0 = poly->y1 = 0;
    poly->y2 = poly->y3 = 256;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = 0xE1000245;
    addPrim(ot, mode);
    D_8004D5B8.funcs.setPrimEnd(mode + 1);
}

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

typedef struct MenuPos {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 y;
    /* 0xA */ s16 unkA;
} MenuPos;

extern MenuPos D_8003EA88[];
extern MenuPos D_8003EA94[5];
extern MenuPos D_8003EAD0[5];
extern s32 D_8003EB0C[];

INCLUDE_ASM("asm/main/nonmatchings/game", func_800121B8);

void func_800123E4(void *arg0, MenuWindows *win, s32 page, s32 show) {
    Unk2728 stats;
    Unk2744 *info;
    s32 id;
    s32 i;

    if (show) {
        id = D_800484E8.unk270C(page);
        if (id >= 0) {
            info = D_800484E8.unk2744(id);
            D_800484E8.unk2728(id, &stats);
            win->pages[page].head->m114(win->pages[page].head, info, -1);
            for (i = 0; i < 5; i++) {
                win->pages[page].left[i]->m114(win->pages[page].left[i], D_80044744.getText(0xB1), D_8003EA94[i].unk0);
                win->pages[page].right[i]->m118(win->pages[page].right[i], 0, ((s16 *)&stats)[D_8003EB0C[i]]);
                win->pages[page].right[i]->m148(win->pages[page].right[i], 1);
            }
        } else {
            win->pages[page].head->m114(win->pages[page].head, D_80044744.getText(0xB1), 0xC);
            for (i = 0; i < 5; i++) {
                win->pages[page].right[i]->m114(win->pages[page].right[i], D_80044744.getText(0xB1), D_8003EA88[6 + i].unk0);
                win->pages[page].right[i]->m148(win->pages[page].right[i], 1);
            }
        }
    } else {
        win->pages[page].head->m144(win->pages[page].head, 0);
        for (i = 0; i < 5; i++) {
            win->pages[page].left[i]->m144(win->pages[page].left[i], 0);
            win->pages[page].right[i]->m144(win->pages[page].right[i], 0);
        }
    }
}

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

s32 func_80013A44(s32 file) {
    Slot *slot = func_800139D4(file);

    if (slot != NULL) {
        slot->unk8 = D_8004D5B8.funcs.unk38();
        if (slot->unk0 == 3) {
            return 0;
        }
    } else {
        func_80013C08(file);
    }
    return 1;
}

Slot *func_80013AB4(void) {
    Slot *best = NULL;
    s32 bestSize = 0;
    s32 i = 0;
    s32 time = D_8004D708.unk38();
    Slot *slot;

    for (slot = D_80044748; i < 64; i++, slot++) {
        if (slot->unk4 != 0 && slot->unk0 == 3 && time >= slot->unk8) {
            if (time != slot->unk8 || D_80047F04.getFileSectors(slot->unk4) >= bestSize) {
                bestSize = D_80047F04.getFileSectors(slot->unk4);
                time = slot->unk8;
                best = slot;
            }
        }
    }
    return best;
}

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

void func_80013CB4(void) {
    Slot *slot;
    s32 i;
    s32 busy;
    s32 reading;

    if (D_80044744.unk0 != 0 && D_80044710.unk2C() != 1) {
        slot = D_80044744.slots;
        reading = 0;
        busy = 0;
        for (i = 0; i < 64; i++, slot++) {
            if (slot->unk4 != 0) {
                switch (slot->unk0) {
                case 2:
                    slot->unk0 = 3;
                    busy = 1;
                    slot->unk8 = D_8004D5B8.funcs.unk38();
                    break;
                case 1:
                    busy = 1;
                    if (!reading) {
                        D_80044710.read(slot->unk4, 0, 0, slot->unkC, NULL);
                        slot->unk0 = 2;
                        reading = busy;
                        slot->unk8 = D_8004D5B8.funcs.unk38();
                    }
                    break;
                }
            }
        }
        if (!busy) {
            D_80044744.unk0 = 0;
        }
    }
}

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

void *func_800143B4(void (*update)(void *), s32 size, s32 nbytes, s32 arg3) {
    Unk80017ECC *task = D_8004AD84.unk20(size, 2);

    if (nbytes != 0) {
        task->items = D_8004AD84.unk20(nbytes, 2);
        task->count = nbytes / 4;
    }
    task->methods[0] = func_8001424C;
    task->methods[1] = func_80014260;
    task->methods[2] = func_80014270;
    task->methods[3] = func_8001427C;
    task->methods[4] = func_80014284;
    task->methods[5] = func_800142A0;
    task->methods[6] = func_800142B8;
    task->methods[7] = func_800142CC;
    task->update = update;
    task->destroy = func_800142E0;
    if (arg3 != 0) {
        task->unk0 = arg3;
        D_8004AF58.unk4(task);
    }
    return task;
}

void *func_800144DC(void (*update)(void *), s32 size, s32 arg2) {
    return func_800143B4(update, size, arg2, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game", main);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C4);

INCLUDE_RODATA("asm/main/nonmatchings/game", D_800100C8);

const char D_800100E4[6][24] = {
    "BASLUS-01436DMW3-USA",
    "BESLPS-99999DMW3-ENG",
    "BESLPS-99999DMW3-FRA",
    "BESLPS-99999DMW3-ITA",
    "BESLPS-99999DMW3-GER",
    "BESLPS-99999DMW3-SPN",
};

void func_80014884(void) {
    D_80047F14.fileName = (char *)D_800100E4[0];
}

void func_80014898(char *title, CardClut *clut, s32 count, s32 *icons) {
    s32 i;

    if (count >= 1 && count <= 3 && (u32)strlen(title) <= 64) {
        D_80047F14.iconCount = count;
        D_8004AD84.bzero(&D_80047F14.header, sizeof(CardHeader));
        D_80047F14.header.magic[0] = 'S';
        D_80047F14.header.magic[1] = 'C';
        D_80047F14.header.blocks = 4;
        D_80047F14.header.type = D_80047F14.iconCount | 0x10;
        strcpy(D_80047F14.header.title, title);
        D_80047F14.header.clut = *clut;
        for (i = 0; i < D_80047F14.iconCount; i++) {
            D_80047F14.icons[i] = icons[i];
        }
    }
}

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

extern s32 D_80048270[];
extern char D_8005C45C[];

s32 func_800151F0(s32 port, s32 cmd) {
    switch (D_80047F14.state) {
    case 0:
    default:
        if (func_80014B8C(port) == 0) {
            return 0;
        }
        switch (D_80047F14.result) {
        case 0:
            D_80047F14.state = 5;
            break;
        case 4:
            if (cmd == 2) {
                D_80047F14.state = 5;
                break;
            }
            D_80047F14.state = 0;
            return 5;
        default:
            D_80047F14.state = 0;
            return D_80047F14.result + 1;
        }
        break;
    case 5:
        if ((D_80047F14.result == 0 && (cmd == 0 || cmd == 1 || cmd == 3)) ||
            (D_80047F14.result == 4 && cmd == 2)) {
            D_8004AD84.bzero(&D_80047F14.fileCount, 0x25C);
            D_80047F14.cmd = D_80048270[cmd];
            switch (cmd) {
            case 0:
            default:
                D_80047F14.result = MemCardGetDirentry(port << 4, D_8005C45C, D_80047F14.files, (long *)&D_80047F14.fileCount, 0, 15);
                break;
            case 1:
                D_80047F14.result = MemCardCreateFile(port << 4, D_80047F14.fileName, 4);
                break;
            case 2:
                D_80047F14.result = MemCardFormat(port << 4);
                break;
            case 3:
                D_80047F14.result = MemCardUnformat(port << 4);
                break;
            }
            if (D_80047F14.result == -1) {
                D_80047F14.result = 8;
            }
        }
        D_80047F14.state = 0;
        if (D_80047F14.result == 0) {
            return 1;
        }
        return D_80047F14.result + 1;
    }
    return 0;
}

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

s32 func_80015584(s32 op, s32 arg) {
    s32 ret = 0;

    if ((D_800484E8.unk7C[7] != 0 || D_800484E8.unk20F[7] != 0) &&
        (D_800484E8.unk7C[0x59] != 0 || D_800484E8.unk20F[0x59] != 0) &&
        (D_800484E8.unk7C[0xA7] != 0 || D_800484E8.unk20F[0xA7] != 0)) {
        ret = 1;
    }
    return ret;
}

s32 func_800155F8(u32 op, s32 arg) {
    s32 result = 0;
    s32 i;
    s32 total;
    s32 id;

    switch (op) {
    case 0:
        if (D_8004AB28 == arg) {
            result = 1;
        }
        break;
    case 1:
        if (D_800484E8.records[arg].unk4 != 0) {
            result = 1;
        }
        break;
    case 2:
        for (i = 0; i < 3; i++) {
            if (D_800484E8.unk270C(i) == arg) {
                result = 1;
                break;
            }
        }
        break;
    case 3:
        D_800484E8.records[arg].unk4 = arg + 3;
        result = 1;
        break;
    case 4:
        if (D_800484E8.records[arg].unk4 != 0 && D_800484E8.records[arg].unk28 >= 0x2D) {
            result = 1;
        }
        break;
    case 5:
        total = 0;
        for (i = 0; i < 3; i++) {
            id = D_800484E8.unk270C(i);
            if (id >= 0) {
                total += D_800484E8.unk2744(id)->unk1C;
            }
        }
        if (total >= arg * 15 + 30) {
            result = 1;
        }
        break;
    case 6:
        if (D_800484E8.records[arg].unk4 == 0) {
            result = 1;
        }
        break;
    }
    return result;
}

s32 func_80015814(s32 op, s32 item) {
    s32 ret = 0;

    switch (op) {
    case 0:
        if (D_800483F8[item] <= D_800484E8.money) {
            ret = 1;
        }
        break;
    case 1:
        D_800484E8.money += D_80048420[item];
        if (D_800484E8.money > 9999999) {
            D_800484E8.money = 9999999;
        }
        break;
    case 2:
        D_800484E8.money -= D_80048440[item];
        if (D_800484E8.money < 0) {
            D_800484E8.money = 0;
        }
        break;
    }
    return ret;
}

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

s32 func_80015940(s32 arg0, s32 mode) {
    s32 ret = 0;
    s32 on = 0;
    s32 off = 0;
    s32 i;

    for (i = 0x27; i < 0x2E; i++) {
        if (func_800154F8(D_8004AB5F, i, 1) != 0) {
            on++;
        } else {
            off++;
        }
    }
    switch (mode) {
    case 0:
        if (on != 0) {
            ret = 1;
        }
        break;
    case 1:
        if (off >= 2) {
            ret = 1;
        }
        break;
    case 2:
        if (off == 1) {
            ret = 1;
        }
        break;
    }
    return ret;
}

s32 func_80015A34(s32 op, s32 arg) {
    Unk80015A34 *obj = D_8004AF58.unkC(0x16, -1, -1);

    obj->unk2C(obj, 3);
    return 1;
}

s32 func_80015A78(s32 id, s32 expected) {
    u8 *p;
    s32 result = 0;
    s32 op;
    s32 arg;

    for (p = D_8004829C; *p != 0xFF; p += 3) {
        if (*p == id) {
            op = p[1] & 0xF;
            arg = p[2];
            switch (p[1] & 0xF0) {
            case 0x00:
                result = func_80015584(op, arg);
                break;
            case 0x10:
                result = func_800155F8(op, arg);
                break;
            case 0x20:
                result = func_80015814(op, arg);
                break;
            case 0x30:
                result = func_80015904(op, arg);
                break;
            case 0x40:
                result = func_80015940(op, arg);
                break;
            case 0x50:
                result = func_80015A34(op, arg);
                break;
            }
            break;
        }
    }
    return expected == result;
}

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

extern s32 D_800484AC[];

s32 func_80015CA4(s32 index, s32 mode) {
    Unk2728 buf;
    s32 total = 0;
    s32 i;
    s32 id;

    for (i = 0; i < 3; i++) {
        id = D_800484E8.unk270C(i);
        if (id >= 0) {
            D_800484E8.unk2728(id, &buf);
            total += buf.unk16;
        }
    }
    if (mode != 0) {
        if (total >= D_800484AC[index]) {
            return 1;
        }
    } else {
        if (total < D_800484AC[index]) {
            return 1;
        }
    }
    return 0;
}

s32 func_80015D90(s32 id, s32 arg1) {
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

void func_80015E8C(s32 item, s32 add) {
    s32 i;

    if (add != 0) {
        if (++D_800484E8.unk7C[item] >= 100) {
            D_800484E8.unk7C[item] = 99;
        }
    } else if (D_800484E8.unk7C[item] != 0) {
        if (--D_800484E8.unk7C[item] < 0) {
            D_800484E8.unk7C[item] = 0;
        }
    } else if (D_800484E8.unk20F[item] != 0) {
        for (i = 0; i < 3; i++) {
            if (func_80015DD8(D_800484E8.unk270C(i), item) != 0) {
                goto found;
            }
        }
        for (i = 0; i < 8; i++) {
            if (D_800484E8.records[i].unk4 >= 3 && func_80015DD8(i, item) != 0) {
                break;
            }
        }
    found:
        D_800484E8.unk20F[item]--;
    }
}

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

s32 func_80016064(u16 code, u16 value) {
    u16 group = (code >> 8) & 0xFE;
    s32 id = code & 0x1FF;
    u16 arg = value;

    if (group == 0x00) {
        return func_800154F8(D_80048280, id, arg);
    } else if (group == 0x02) {
        return func_800154F8(D_8004AB2C, id, arg);
    } else if (group == 0x04) {
        return func_800154F8(D_8004AB39, id, arg);
    } else if (group == 0x06) {
        return func_800154F8(D_8004AB3B, id, arg);
    } else if (group == 0x08) {
        return func_800154F8(D_8004AB3C, id, arg);
    } else if (group == 0x0A) {
        return func_800154F8(D_8004AB3D, id, arg);
    } else if (group == 0x0C) {
        return func_800154F8(D_8004AB3F, id, arg);
    } else if (group == 0x0E) {
        return func_800154F8(D_8004AB47, id, arg);
    } else if (group == 0x10) {
        return func_800154F8(D_8004AB53, id, arg);
    } else if (group == 0x18) {
        return func_800154F8(D_8004AB55, id, arg);
    } else if (group == 0x1A) {
        return func_800154F8(D_8004AB56, id, arg);
    } else if (group == 0x1C) {
        return func_800154F8(D_8004AB5F, id, arg);
    } else if (group == 0x20) {
        return func_800154F8(D_8004AB6A, id, arg);
    } else if (group == 0x40) {
        return func_800154F8(D_8004AB88, id, arg);
    } else if (group == 0x60) {
        return func_80015BB0(id, arg);
    } else if (group == 0x70) {
        return func_80015A78(id, arg);
    } else if (group == 0x72) {
        return func_80015CA4(id, arg);
    } else if (group == 0x7E) {
        return func_80015D90(id, arg);
    } else if (group >= 0x80 && group < 0x8F) {
        return func_80015BEC(id, arg);
    } else if (group == 0x92) {
        return func_80015C58(id, arg);
    }
    return 1;
}

extern void (*D_8009A6EC)(s32 id);
void func_8008B2C4(s32 id);
void func_8008B320(void);

void func_80016260(s32 code, s32 value) {
    u16 group = (code >> 8) & ~1;
    s32 id = code & 0x1FF;

    if (group == 0x00) {
        func_8001553C(D_80048280, id, value);
    }
    if (group == 0x02) {
        func_8001553C(D_8004AB2C, id, value);
    }
    if (group == 0x04) {
        func_8001553C(D_8004AB39, id, value);
    }
    if (group == 0x06) {
        func_8001553C(D_8004AB3B, id, value);
    }
    if (group == 0x08) {
        func_8001553C(D_8004AB3C, id, value);
    }
    if (group == 0x0A) {
        func_8001553C(D_8004AB3D, id, value);
    }
    if (group == 0x0C) {
        func_8001553C(D_8004AB3F, id, value);
    }
    if (group == 0x0E) {
        func_8001553C(D_8004AB47, id, value);
    }
    if (group == 0x10) {
        func_8001553C(D_8004AB53, id, value);
    }
    if (group == 0x18) {
        func_8001553C(D_8004AB55, id, value);
    }
    if (group == 0x1A) {
        func_8001553C(D_8004AB56, id, value);
    }
    if (group == 0x1C) {
        func_8001553C(D_8004AB5F, id, value);
    }
    if (group == 0x20) {
        func_8001553C(D_8004AB6A, id, value);
    }
    if (group == 0x40) {
        func_8001553C(D_8004AB88, id, value);
    }
    if (group == 0x70) {
        func_80015A78(id, 1);
    }
    if (group == 0x74) {
        D_8009A6EC(id);
    }
    if (group == 0x76) {
        func_8001602C(id, 0);
    }
    if (group == 0x78) {
        func_8001602C(id, 1);
    }
    if (group >= 0x80 && group < 0x8F) {
        func_80015E8C(id, value);
    }
    if (group == 0x90) {
        func_8008B2C4(id);
    }
    if (group == 0x92) {
        func_80015FC8(id, value);
    }
    if (group == 0x94) {
        func_8008AEB4(0xA00, id, 0, 0, 0);
    }
    if (group == 0x7A) {
        if ((u16)id < 30) {
            func_8008AEB4(0xF00, (u16)id, 0, 0, 0);
        } else if ((u32)(id - 0x31) < 0x13 || (u32)(id - 0x46) < 5) {
            func_8008AEB4(0x1300, (u16)id, 0, 0, 0);
        } else {
            func_8008B320();
        }
    }
    if (group == 0x7C) {
        if ((u16)id == 0) {
            func_8008AEB4(0xD00, 0, 0, 0, 0);
        } else if ((u16)id == 1) {
            func_8008AEB4(0xB00, 0, 0, 0, 0);
        }
    }
}

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

s32 func_80017348(s32 slot, s16 *out) {
    s32 i;
    s32 n;
    s32 index;

    for (i = 0, n = 0; i < 3; i++) {
        if (D_800484E8.records[slot].unk54[i] >= 3) {
            index = func_800172E8(slot, D_800484E8.records[slot].unk54[i]);
            if (index >= 0 && D_800484E8.records[slot].entries[index].unk0 >= 3) {
                out[n] = D_800484E8.records[slot].entries[index].unk0;
                n++;
            }
        }
    }
    for (i = n; i < 3; i++) {
        out[i] = -1;
    }
    return n;
}

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

s32 func_80017534(s32 slot, u16 *out) {
    s32 i;
    s32 n;
    s32 count;

    for (n = i = 0; i < 44; i++) {
        if (D_800484E8.records[slot].entries[i].unk0 >= 3) {
            out[n] = D_800484E8.records[slot].entries[i].unk0;
            n++;
        }
    }
    count = n;
    for (; n < 44; n++) {
        out[n] = 0;
    }
    return count;
}

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

void *func_800179C8(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *new;
    u32 avail;
    u32 splitSize;

    size = (size + 3) >> 2 << 2;
    splitSize = size + 20;
    for (b = D_8004AD84.first; b->flags != 1; b = b->next) {
        if (b->flags == 0) {
            avail = (u8 *)b->next - (u8 *)b - sizeof(MemBlock);
            if (avail >= size) {
                if (avail > splitSize) {
                    new = (MemBlock *)((u8 *)b + size + sizeof(MemBlock));
                    new->prev = b;
                    new->next = b->next;
                    new->flags = 0;
                    b->next->prev = new;
                    b->next = new;
                }
                b->flags = tag;
                return b + 1;
            }
        }
    }
    return NULL;
}

void *func_80017A78(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *prev;
    MemBlock *new;
    u32 avail;

    size = ((size + 3) >> 2 << 2) + sizeof(MemBlock);
    for (b = D_8004AD84.end - 1; D_8004AD84.first != b; b = b->prev) {
        prev = b->prev;
        if (prev->flags == 0) {
            avail = (u8 *)b - (u8 *)prev;
            if (size == avail) {
                new = prev;
                new->flags = tag;
                return new + 1;
            }
            if (size < avail) {
                new = (MemBlock *)((u8 *)b - size);
                new->prev = prev;
                new->next = b;
                new->flags = tag;
                b->prev->next = new;
                b->prev = new;
                return new + 1;
            }
        }
    }
    return NULL;
}

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

/* Runs the task's update with the stack in the scratchpad. */
#define SetSpadStack(addr) \
    __asm__ volatile("move $8,%0\n\tsw $29,0($8)\n\taddiu $8,$8,-16\n\tmove $29,$8" : : "r"(addr) : "$8", "memory")
#define ResetSpadStack() __asm__ volatile("addiu $29,$29,16\n\tlw $29,0($29)" : : : "memory")

Unk80017ECC *func_80017DDC(Unk80017ECC *task) {
    s32 done = task->state == 3;

    SetSpadStack(0x1F8003FC);
    if (task->state == 1 && task->wait != 0) {
        if (task->wait > 0) {
            task->wait = -1;
        }
    } else {
        task->update(task, task->items);
    }
    ResetSpadStack();
    if (!done) {
        if (task->state != 1 || task->wait == 0) {
            D_8004AF58.unk14(task);
        }
    } else {
        task->destroy(task);
        task = NULL;
    }
    return task;
}

void func_80017ECC(Unk80017ECC *obj) {
    s32 count = obj->count;
    s32 *items = obj->items;
    s32 i;

    for (i = 0; i < count; i++) {
        if (items[i] != 0) {
            items[i] = (s32)func_80017DDC((Unk80017ECC *)items[i]);
        }
    }
}

s32 func_80017F38(s32 arg0) {
    if (arg0 != 0) {
        return (s32)func_80017DDC((Unk80017ECC *)arg0);
    }
    return 0;
}

void func_80017F64(Task *task) {
    if (task != NULL) {
        task->unk28(task, 3);
        D_8004AF58.unk18(task);
    }
}

void func_80017FAC(s32 multitap, s32 arg1) {
    s32 i;
    s32 j;
    s16 count;

    D_8004AD84.bzero(&D_8004AF78, 0x3E0);
    D_8004AD84.memset(D_8004AF78.act, 0xFF, sizeof(D_8004AF78.act));
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            func_8001855C((i * 16 + j) & 0xFF);
        }
    }
    if (multitap != 0) {
        PadInitMtap(D_8004AF78.buf[0], D_8004AF78.buf[1]);
        D_8004AF78.flags |= 0x80000000;
    } else {
        PadInitDirect(D_8004AF78.buf[0], D_8004AF78.buf[1]);
    }
    arg1 &= 0x7F;
    D_8004AF78.unk3D4 = (u8)arg1;
    count = (u8)arg1;
    D_8004AF78.flags |= 0x40000000;
    if (count == 0) {
        D_8004AF78.unk3D4 = 0x10;
    }
    func_800180FC();
}

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

int PadChkVsync(void);
s32 func_80018BC0(u16 port, u8 *data);
void func_8001864C(void);
s32 func_80018654(s32 arg0);

void func_800181B8(void) {
    u8 *record = (u8 *)D_8004AF78.unk3D8 + D_8004AF78.unk3DC * 34;
    s32 ret;
    s32 i;
    s32 j;
    u16 port;

    ret = PadChkVsync();
    if (ret != 1) {
        return;
    }
    if (++D_8004AF78.unk3DC >= 0x707 && func_80018654(D_8004AF78.unk3D6) == ret) {
        func_8001864C();
        return;
    }
    for (i = 0; i < 2; i++) {
        port = i * 16;
        if (D_8004AF78.buf[i][1] == 0x80) {
            for (j = 0; j < 4; j++) {
                if (D_8004AF78.flags & 0x400000) {
                    func_80018868((u8)port, &D_8004AF78.buf[i][2 + j * 8], record + 2 + j * 8);
                } else {
                    func_80018BC0((u8)(port + j), &D_8004AF78.buf[i][2 + j * 8]);
                }
            }
        } else {
            if (D_8004AF78.flags & 0x400000) {
                func_80018868((u8)port, D_8004AF78.buf[i], record);
            } else {
                func_80018BC0((u8)port, D_8004AF78.buf[i]);
            }
        }
    }
}

s32 func_8001837C(u16 port, s32 motor, s16 time, u8 value) {
    u8 id = port;
    s32 mode;
    PadSlot *slot;
    s16 t;
    s32 pad;

    t = time;
    if (!(D_8004AF78.flags & 0x08000000)) {
        return 0;
    }
    if (func_80018774(id) == 0) {
        return 0;
    }
    mode = PadInfoMode(id, 2, 0);
    pad = id >> 4;
    slot = &D_8004AF78.slots[pad][port & 3];
    if (mode == 4 || mode == 7) {
        D_8004AF78.act[pad][motor & 1] = value;
    } else {
        D_8004AF78.act[pad][0] = 0x40;
        D_8004AF78.act[pad][1] = 1;
    }
    if (slot->actTimers[motor] <= 0) {
        slot->actTimers[motor] = t;
    } else if (t == 0) {
        slot->actTimers[motor] = 0;
    }
    PadSetAct(id, D_8004AF78.act[pad], 2);
    return 1;
}

u16 func_800184F0(s32 pad) {
    return D_8004AF78.slots[pad][0].unk0;
}

u16 func_80018514(s32 pad) {
    return D_8004AF78.slots[pad][0].unk6;
}

u16 func_80018538(s32 pad) {
    return D_8004AF78.slots[pad][0].unk2;
}

void func_8001855C(u16 port) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[i] = D_8004B39C[i];
    }
}

void func_800185C4(u16 port, s32 a, s32 b) {
    u8 tmp = D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[a];

    D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[a] = D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[b];
    D_8004AF78.slots[(u8)port >> 4][port & 3].unk5C[b] = tmp;
}

u8 func_8001861C(s32 pad, s32 index) {
    return D_8004AF78.slots[pad][0].unk5C[index];
}

s32 func_80018644(void) {
    return 0;
}

void func_8001864C(void) {
}

s32 func_80018654(s32 arg0) {
    if (D_8004AF78.flags & 0x800000) {
        if (D_8004AF78.unk3D6 == arg0) {
            return 1;
        }
        return -1;
    }
    return 0;
}

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

s32 func_8001873C(s32 arg0) {
    if (D_8004AF78.flags & 0x400000) {
        if (D_8004AF78.unk3D6 == arg0) {
            return 1;
        }
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_80018774);

void func_80018868(s32 port, u8 *data, u8 *record) {
    u32 id = port & 0xFF;
    s32 mode = PadInfoMode(id, 2, 0);
    u32 pad = (id >> 4) & 1;
    PadSlot *slot = &D_8004AF78.slots[(u8)pad][port & 3];
    s16 buttons;
    s16 i;
    u16 b;
    s16 x, y, z;

    if ((D_8004AF78.flags & 0x400000) && D_8004AF78.unk3D6 == ((port & 3) | pad)) {
        buttons = (~*(u16 *)(data + 2) & 8) | (~*(u16 *)(record + 2) & ~8);
        if (mode == 7) {
            for (i = 0; i < 4; i++) {
                slot->analog[i] = record[4 + i];
            }
        }
    } else {
        b = ~*(u16 *)(data + 2);
        x = (b >> 13) & 1;
        y = (b >> 14) & 1;
        z = (b >> 12) & 1;
        buttons = ~*(u16 *)(data + 2) & ~0x7000;
        if (y) {
            buttons |= 0x2000;
        }
        if (z) {
            buttons |= 0x4000;
        }
        if (x) {
            buttons |= 0x1000;
        }
        if (mode == 7) {
            for (i = 0; i < 4; i++) {
                slot->analog[i] = data[4 + i];
            }
        }
    }
    if (mode == 7) {
        if (slot->analog[2] < 0x41) {
            buttons |= 0x80;
        } else if (slot->analog[2] >= 0xC0) {
            buttons |= 0x20;
        }
        if (slot->analog[3] < 0x41) {
            buttons |= 0x10;
        } else if (slot->analog[3] >= 0xC0) {
            buttons |= 0x40;
        }
    }
    i = 0;
    slot->unk2 = 0;
    for (; i < 16; i++) {
        u8 bit = slot->unk5C[i];
        s32 *time = &slot->repeatTime[bit];
        u8 *count = &slot->repeatCount[bit];

        if ((buttons >> bit) & 1) {
            if (D_8004AF78.unk3D4 > 0) {
                if ((D_8004D5B8.funcs.unk38() - *time + *count) / D_8004AF78.unk3D4 != 0) {
                    *count += 10;
                    if (*count >= 12) {
                        *count = 12;
                    }
                    *time = D_8004D5B8.funcs.unk38();
                    slot->unk2 |= 1 << slot->unk5C[i];
                }
            }
        } else {
            *time = D_8004D5B8.funcs.unk38();
            *count = 0;
        }
    }
    b = slot->unk6;
    slot->unk6 = buttons;
    slot->unk4 = b;
    slot->unk0 = buttons & (b ^ buttons);
}

s32 func_80018BC0(u16 port, u8 *data) {
    u8 id = port;
    s32 mode;

    if (*data != 0 || func_80018774(id & 0xFF) == 0) {
        D_8004AF78.slots[(id >> 4) & 1][port & 3].unk0 = 0;
        D_8004AF78.slots[(id >> 4) & 1][port & 3].unk2 = 0;
        D_8004AF78.slots[(id >> 4) & 1][port & 3].unk6 = 0;
        return 0;
    }
    mode = PadInfoMode(id & 0xFF, 2, 0);
    if (mode == 4 || mode == 7) {
        func_80018EA0(id & 0xFF);
    }
    func_80018868(id & 0xFF, data, 0);
    return 1;
}

s32 func_80018CA8(s32 port, s32 on) {
    u32 id = port & 0xFF;
    s32 mode;
    s32 bit;

    if (func_80018774(id) != 0) {
        mode = PadInfoMode(id, 2, 0);
        if (mode == 4 || mode == 7) {
            bit = ((id >> 4) << 2) | (port & 3);
            if (on != 0) {
                D_8004AF78.flags |= 1 << bit;
                PadSetMainMode(id, PadInfoMode(id, 3, 0), 3);
            } else {
                D_8004AF78.flags &= ~(1 << bit);
                PadSetMainMode(id, PadInfoMode(id, 3, 0), 2);
            }
            D_8004AF78.flags &= 0xF3FFFFFF;
            return 1;
        }
    }
    return 0;
}

void func_80018DC4(u16 port) {
    u32 id = (u8)port;
    s32 count = PadInfoAct(id, -1, 0);
    s32 i;
    s32 act;

    for (i = 0; i < count; i++) {
        act = PadInfoAct(id, i, 2);
        if (act != 0) {
            D_8004AF78.act[id >> 4][i] = act & 1;
        }
    }
    PadSetActAlign(port & 0xFF, D_8004AF78.act[(port & 0xFF) >> 4]);
}

void func_80018EA0(u16 port) {
    u8 id = port;
    s32 i;
    PadSlot *slot = &D_8004AF78.slots[id >> 4][port & 3];

    for (i = 0; i < 2; i++) {
        if (slot->actTimers[i] != 0) {
            if ((slot->actTimers[i] -= D_8004D5B8.funcs.unk3C()) <= 0) {
                slot->actTimers[i] = 0;
                D_8004AF78.act[id >> 4][i] = 0;
            }
            PadSetAct(port & 0xFF, D_8004AF78.act[id >> 4], 2);
        }
    }
}

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

void func_80019184(u8 *buf, s32 value) {
    s32 saved;
    s32 len;
    s32 div;
    s32 d;

    saved = value;
    if (value <= 0) {
        *buf = '0';
        return;
    }
    len = 0;
    div = 10;
    do {
        value -= value % div;
        len++;
        div *= 10;
    } while (value != 0);
    value = saved;
    while (value != 0) {
        d = value % 10;
        value -= d;
        value /= 10;
        buf[--len] = d + '0';
    }
}

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

void func_80019C2C(Unk80019DFC *obj) {
    s32 extra;
    s32 pos;
    s32 lines;
    s32 going;
    u8 *p;
    u8 index;
    s32 c;

    if (obj->unkC == 1) {
        pos = obj->unkA6;
        extra = 0;
        lines = 0;
        going = 1;
        do {
            switch ((s32)((u32)(D_8004D5A8.decode(obj->text[0].data + pos, (u8)obj->text[0].dirty, obj->unk50) << 16) >> 24)) {
            case 0:
            default:
                if (obj->text[0].dirty != 0) {
                    pos += 2;
                } else {
                    pos += 1;
                }
                break;
            case 1:
                pos += 2;
                break;
            case 2:
                p = (u8 *)(pos + (s32)obj->text[0].data);
                c = p[1];
                switch (c) {
                default:
                    pos += D_8004D5A8.codeLengths[c];
                    break;
                case 1:
                    if (++lines < obj->unkBF) {
                        pos += D_8004D5A8.codeLengths[1];
                    } else {
                        going = 0;
                    }
                    break;
                case 2:
                    if (p[2] < 5) {
                        going = 0;
                    }
                    pos += D_8004D5A8.codeLengths[2];
                    break;
                case 5:
                    index = p[2];
                    if (index < 6) {
                        extra += obj->text[index].len;
                        pos += D_8004D5A8.codeLengths[5];
                    } else {
                        going = 0;
                    }
                    break;
                case 3:
                    going = 0;
                    break;
                }
                break;
            case 4:
                going = 0;
                break;
            }
        } while (going != 0);
        obj->unkA4 = pos + extra;
    }
}

void func_80019DFC(Unk80019DFC *arg0, s32 arg1) {
    u8 *entry;

    if (arg1 < 1 || arg1 > 3) {
        arg1 = 1;
    }
    entry = D_8004D5A8.styles + arg1 * 0x18;
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

void func_80019F28(Unk80019DFC *obj) {
    TextBuffer *text = &obj->text[0];
    s32 pos;
    u8 c;
    u8 index;

    if (obj->text[0].data != NULL) {
        for (pos = 0; pos < obj->text[0].len;) {
            switch ((s32)((u32)(D_8004D5A8.decode(text->data + pos, (u8)text->dirty, obj->unk50) << 16) >> 24)) {
            case 0:
            case 3:
            default:
                if (text->dirty != 0) {
                    pos += 2;
                } else {
                    pos += 1;
                }
                break;
            case 1:
                pos += 2;
                break;
            case 2:
                c = text->data[pos + 1];
                if (c == 4) {
                    break;
                }
                if (c == 8) {
                    index = text->data[pos + 2];
                    func_80019308(obj, D_8004853C, index);
                    obj->text[index].dirty = 0;
                    pos += D_8004D5A8.codeLengths[8];
                } else {
                    pos += D_8004D5A8.codeLengths[c];
                }
                break;
            case 4:
                return;
            }
        }
    }
}

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

s32 func_8001A3B8(Unk80019DFC *obj, TextBuffer *buf, TextWait *wait) {
    if (++wait->unk18 == 1) {
        wait->unk10 = buf->pos + 2;
    } else if (wait->unk18 >= obj->unkBF) {
        obj->unkA6 = wait->unk10;
        if (obj->unkBF >= 2) {
            obj->unkBF--;
            func_80019C2C(obj);
            obj->unkBF++;
        }
        return 0x8000;
    }
    obj->unkB8 = 0;
    if (obj->unkC2 != 0) {
        obj->unkBA += obj->unkB6;
    } else {
        obj->unkBA += (s8)obj->unk50[1];
    }
    return 0x8004;
}

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

s32 func_8001A530(Unk80019DFC *obj, TextBuffer *buf) {
    u8 c;

    if (obj->unkAA != 0) {
        obj->unkA4 = buf->pos + 2;
    } else {
        obj->unkA4 = buf->len;
    }
    while (buf->pos < buf->len) {
        switch ((s32)((u32)(D_8004D5A8.decode(buf->data + buf->pos, (u8)buf->dirty, obj->unk50) << 16) >> 24)) {
        case 0:
        case 1:
        default:
            obj->unkA6 = buf->pos;
            buf->pos = buf->len + 1;
            break;
        case 2:
            c = buf->data[buf->pos + 1];
            if (c == 5 || c == 8) {
                obj->unkA6 = buf->pos;
                buf->pos = buf->len + 1;
            } else {
                buf->pos += D_8004D5A8.codeLengths[c];
            }
            break;
        case 4:
            obj->unkA6 = buf->pos - 1;
            return 3;
        }
    }
    return 0;
}

s32 func_8001A684(void) {
    return 0x8003;
}

s32 func_8001A68C(Unk80019DFC *obj, TextBuffer *buf, TextWait *wait) {
    u8 index = buf->data[buf->pos + 2];
    s16 c;
    s32 ret;

    if (obj->text[index].data == NULL) {
        func_80019308(obj, D_80010268, index);
        return 0x8003;
    }
    if (obj->text[index].pos >= obj->text[index].len) {
        return 0x8003;
    }
    c = D_8004D5B4(obj->text[index].data + obj->text[index].pos, (u8)obj->text[index].dirty, obj->unk50, obj->text[index].pos);
    wait->unk14 = c;
    wait->unk16 = (u32)(c << 16) >> 24;
    if (wait->unk16 == 2) {
        return 0x8000;
    }
    if (obj->unkAA != 0) {
        return func_8001A108(obj, &obj->text[index], wait, &obj->text[index].pos);
    }
    ret = func_8001A108(obj, &obj->text[index], wait, &obj->text[index].pos);
    if (ret == 1) {
        return 2;
    }
    return ret;
}

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

void func_8001A890(Unk80019DFC *obj) {
    s32 i;

    switch (obj->unkC) {
    case 0:
    default:
        obj->unk38(obj);
        break;
    case 1:
        if (obj->unkC1 != 0) {
            if (obj->unkAA > 0 && obj->unkC3 == 0) {
                if (++obj->unkA8 > obj->unkAA) {
                    obj->unkA8 = 0;
                    obj->unkA4++;
                    if (obj->unkC8 != 0) {
                        D_800553DC.playSound(obj->unkC8);
                    }
                }
            }
            func_80019420(obj);
        }
        break;
    case 2:
        switch (obj->unk10) {
        case 0:
        default:
            func_80019420(obj);
            if (++obj->unkA8 > obj->unk14) {
                obj->unkA8 = 0;
                obj->unk28(obj, 1);
            }
            break;
        case 1:
            if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, D_8004D474[obj->unk14])) & 1) {
                obj->text[0].data[obj->unk18] = 5;
                obj->unkA8 = obj->unkAA;
                obj->unk28(obj, 1);
            }
            func_80019420(obj);
            break;
        }
        break;
    case 3:
        for (i = 0; i < 6; i++) {
            if (obj->text[i].data != NULL) {
                D_8004AD84.free(obj->text[i].data);
            }
        }
        break;
    }
}

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

void func_8001AD20(Task8001ACC8 *task, Unk80019DFC **win) {
    switch (task->state) {
    case 0:
    default:
        if (*win == NULL) {
            *win = func_8001AAB4(task->unk50, 1, task->unk58, task->unk5C);
        }
        (*win)->m110(*win, D_8004D488[task->unk6C]);
        (*win)->m144(*win, task->unk64);
        (*win)->m15C(*win, task->unk54);
        task->unk70 = D_8004D708.unk38();
        task->unk38(task);
        break;
    case 1:
        if (task->dirty != 0) {
            (*win)->m144(*win, task->unk64);
            (*win)->setPos(*win, task->unk58, task->unk5C);
            (*win)->m138(*win, task->unk60);
            task->dirty = 0;
        }
        if (task->unk64 != 0) {
            if (task->unk7C != 0) {
                if (task->unk6C != 0) {
                    task->unk6C = 0;
                    (*win)->m110(*win, D_8004D488[0]);
                }
            } else if (task->unk10 == 0) {
                if ((D_8004D5B8.funcs.unk38() - task->unk70) / task->unk74 != 0) {
                    task->unk70 = D_8004D5B8.funcs.unk38();
                    task->unk6C = 1;
                    (*win)->m110(*win, D_8004D488[1]);
                    task->unk10 = 1;
                }
            } else if ((D_8004D5B8.funcs.unk38() - task->unk70) / task->unk78 != 0) {
                task->unk70 = D_8004D5B8.funcs.unk38();
                if (++task->unk6C >= 5) {
                    task->unk6C = 0;
                    task->unk10 = 0;
                }
                (*win)->m110(*win, D_8004D488[task->unk6C]);
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task8001ACC8 *func_8001AFE0(s16 arg0, s32 arg1, s16 arg2, s16 arg3) {
    Task8001ACC8 *task = func_800144DC(func_8001AD20, 0x98, 4);

    task->unk50 = arg0;
    task->unk54 = arg1;
    task->unk58 = arg2;
    task->unk5C = arg3;
    task->unk64 = 1;
    task->unk74 = 0x20;
    task->unk78 = 6;
    task->methods[0] = func_8001ACC8;
    task->methods[1] = func_8001ACE4;
    task->methods[3] = func_8001AD08;
    task->methods[4] = func_8001AD10;
    task->methods[2] = func_8001ACF8;
    task->methods[5] = func_8001AD18;
    return task;
}

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

void func_8001B1D0(Task8001B3A0 *task) {
    u8 *src = (u8 *)task->unk68;
    u8 *dst = task->unk6C;
    s32 total = 0;
    s32 done = 0;
    s32 n;
    s32 i;

    while (*src != 0) {
        if (*src & 0x80) {
            n = *src++ & 0x7F;
            for (i = 0; i < n; i++) {
                *dst++ = *src;
            }
            src++;
            total += n;
        } else {
            n = *src++;
            for (i = 0; i < n; i++) {
                *dst++ = *src++;
            }
            total += n;
        }
        if (total >= task->unk70) {
            done = 1;
            task->unk68 = (s32 *)src;
            task->unk6C = dst;
            break;
        }
    }
    if (!done) {
        task->unk2C(task, 0);
    }
}

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

void func_8001B490(Task8001B6A8 *task) {
    Obj8001F22C obj;
    s32 i;
    s32 x;
    Unk80044744 *g;

    i = 0;
    g = &D_80044744;
    x = 0;
    for (; i < 2; i++) {
        func_8001F22C(&obj);
        obj.methods[3](task->unk50, 0);
        obj.methods[1](0x140, 0);
        if (task->unk10 == 0) {
            obj.methods[7](task->unk68, 0x1000, 0x1000);
            obj.methods[9](0x140 - x, 0xC4);
        } else if (task->unk10 == 2) {
            obj.methods[6](task->unk58);
        }
        obj.methods[5](g->unk424(0x02770000), i + 8, 0, 0xA6);
        x += 0x140;
    }
}

void func_8001B5AC(Task8001B6A8 *task) {
    Obj8001F22C obj;

    func_8001F22C(&obj);
    obj.methods[3](task->unk50, 0);
    obj.methods[1](0x140, 0);
    if (D_8004D5B8.funcs.unk38() - task->unk60 >= 4) {
        task->unk60 = D_8004D5B8.funcs.unk38();
        if (++task->unk64 >= 5) {
            task->unk64 = 0;
        }
    }
    obj.methods[6](task->unk64);
    obj.methods[5](D_80044B68(0x02770000), 10, 0x124, 0xCD);
}

void func_8001B6A8(Task8001B6A8 *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        task->unk6A = 0x199;
        break;
    case 1:
        switch (task->unk10) {
        case 0:
        default:
            task->unk68 += task->unk6A;
            if (task->unk68 > 0x1000) {
                task->unk68 = 0x1000;
                task->unk3C(task);
            }
            break;
        case 1:
            if (task->unk5C != 0) {
                func_8001B5AC(task);
            }
            break;
        case 2:
            if (D_8004D5B8.funcs.unk38() - task->unk54 >= 3) {
                task->unk54 = D_8004D5B8.funcs.unk38();
                if (++task->unk58 >= 5) {
                    task->unk28(task, 3);
                    return;
                }
            }
            break;
        }
        func_8001B490(task);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_8001B804(s32 arg0) {
    Task *task = func_800144DC(func_8001B6A8, 0x6C, 0);

    task->unk50 = arg0;
    D_800553DC.playSound(0x40019);
    return task;
}

void func_8001B864(Task8001B6A8 *task, Unk8001BA7C *data) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        break;
    case 1:
        switch (task->unk10) {
        case 0:
        default:
            if (data->window->m16C(data->window) == 0 && data->unk4->unk10 == 1) {
                data->window->m144(data->window, 1);
                task->unk10++;
            }
            break;
        case 1:
            if (data->window->m168(data->window) != 0) {
                data->unk4->unk10 = 2;
                data->window->m144(data->window, 0);
                task->unk10++;
                D_800553DC.playSound(0x4001A);
                break;
            }
            if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
                data->window->m128(data->window);
            }
            if (data->window->m170(data->window) != 0) {
                data->unk4->unk5C = 1;
            } else {
                data->unk4->unk5C = 0;
            }
            break;
        case 2:
            if (data->unk4 == NULL) {
                task->unk28(task, 3);
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_8001BA7C(s32 id, s32 arg1, s32 arg2) {
    Task *task = func_800144DC(func_8001B864, 0x50, 8);
    Unk8001BA7C *data = task->unk24;

    data->window = func_8001AAB4(id, 1, 0x12, 0xB0);
    data->window->m160(data->window, 3);
    data->window->m114(data->window, arg1, arg2);
    data->window->m144(data->window, 0);
    data->window->m130(data->window, 6);
    data->unk4 = func_8001B804(id);
    return task;
}

INCLUDE_ASM("asm/main/nonmatchings/game", func_8001BB68);

void func_8001BCCC(Task8001BB68 *task) {
    Obj8001F22C obj;
    SVECTOR v[4];
    Unk8001BB68 *parent = task->parent;
    u32 type = parent->type;
    s32 pad;
    s32 i;
    s32 x;
    Unk80044744 *g;
    u_long *ot;
    Resource *res;
    POLY_FT4 *p;
    DVECTOR *pos;

    pad = 0;
    if (type < 2) {
        pad = parent->w;
    }
    pos = &D_8004D49C[type].unk4;
    func_8001F22C(&obj);
    obj.methods[3](task->parent->unk54, 0);
    obj.methods[1](0x140, 0);
    g = &D_80044744;
    for (i = 0; i < 4; pos++, i++) {
        switch (i) {
        case 0:
            obj.methods[5](g->unk424(0x02770000), D_8004D49C[type].unk0, task->parent->x + pos->vx,
                           task->parent->y + pos->vy);
            break;
        case 1:
            obj.methods[5](g->unk424(0x02770000), 0, task->parent->x + pos->vx - pad, task->parent->y + pos->vy);
            break;
        case 3:
            if (type < 2) {
                obj.methods[5](g->unk424(0x02770000), 2, task->parent->x + pos->vx, task->parent->y + pos->vy);
            } else {
                x = task->parent->w - 14;
                obj.methods[5](g->unk424(0x02770000), 2, task->parent->x + x, task->parent->y + pos->vy);
            }
            break;
        }
    }
    res = D_8004D5B8.funcs.unk2C(task->parent->unk54);
    ot = (u_long *)res->unk138(res, 0);
    pos = &D_8004D49C[type].unkC;
    v[0].vx = v[2].vx = task->parent->x + pos->vx - pad;
    v[1].vx = v[3].vx = v[0].vx + task->parent->w;
    v[0].vy = v[1].vy = task->parent->y + pos->vy;
    v[2].vy = v[3].vy = v[0].vy + task->parent->h;
    v[0].vz = v[1].vz = v[2].vz = v[3].vz = 0;
    p = D_8004D5B8.funcs.allocPrim();
    setPolyFT4(p);
    setRGB0(p, 0x80, 0x80, 0x80);
    p->tpage = 0x45;
    p->clut = 0x2E57;
    setSemiTrans(p, 1);
    p->x0 = v[0].vx;
    p->y0 = v[0].vy;
    p->x1 = v[1].vx;
    p->y1 = v[1].vy;
    p->x2 = v[2].vx;
    p->y2 = v[2].vy;
    p->x3 = v[3].vx;
    p->y3 = v[3].vy;
    setUV4(p, 0xBC, 0, 0xC7, 0, 0xBC, 0x3E, 0xC7, 0x3E);
    addPrim(ot, p);
    D_8004D5B8.funcs.setPrimEnd(p + 1);
}

void func_8001C0C4(Task *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk28(task, 2);
        break;
    case 1:
        func_8001BB68(task);
        func_8001BCCC((Task8001BB68 *)task);
        break;
    case 2:
    case 3:
        break;
    }
}

Task8001BB68 *func_8001C130(Unk8001BB68 *parent) {
    Task8001BB68 *task = func_800144DC(func_8001C0C4, 0x60, 0);

    task->parent = parent;
    return task;
}

typedef struct Order4 {
    s32 next[4];
} Order4;

extern Order4 D_800102BC;

void func_8001C168(Task8001C454 *task) {
    Resource *res = D_8004D708.unk2C(task->unk64);
    u_long *ot = (u_long *)res->unk138(res, 0);
    SVECTOR out[4];
    SVECTOR in[4];
    LINE_F2 *line;
    Order4 order;
    s32 i;

    if (task->unkB8 == 0) {
        task->unk60 += task->unk5C;
        if (task->unk60 > 0x1000) {
            task->unk60 = 0x1000;
            task->unkBC = 1;
            task->unk28(task, 3);
        }
    } else {
        task->unk60 -= task->unk5C;
        if (task->unk60 < 0) {
            task->unk60 = 0;
            task->unk28(task, 3);
        }
    }
    task->scale.vz = 0;
    task->scale.vx = task->scale.vy = task->unk60;
    RotMatrixYXZ_gte(&task->rot, &task->matrix);
    ScaleMatrix(&task->matrix, &task->scale);
    in[0].vx = in[2].vx = task->unk50 - task->unk54;
    in[1].vx = in[3].vx = in[0].vx + task->unk58;
    in[0].vy = in[1].vy = task->unk52 - task->unk56;
    in[2].vy = in[3].vy = in[0].vy + task->unk5A;
    in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
    for (i = 0; i < 4; i++) {
        ApplyMatrixSV(&task->matrix, &in[i], &out[i]);
        out[i].vx += task->unk54;
        out[i].vy += task->unk56;
    }
    line = D_8004D708.allocPrim();
    for (i = 0; i < 4; i++) {
        order = D_800102BC;
        setLineF2(line);
        setRGB0(line, 0, 0, 0xFF);
        line->x0 = out[i].vx;
        line->y0 = out[i].vy;
        line->x1 = out[order.next[i]].vx;
        line->y1 = out[order.next[i]].vy;
        addPrim(ot, line);
        line++;
    }
    D_8004D708.setPrimEnd(line);
}

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

Task8001C454 *func_8001C4D8(s32 arg0, s16 x, s16 y, s32 w, s32 h, s32 type) {
    s16 pad = w;
    Task8001C454 *task = func_800144DC(func_8001C454, 0xC0, 0);

    task->unk64 = arg0;
    task->unk54 = x;
    task->unk56 = y;
    task->unk58 = w + 0x20;
    task->unk5A = h;
    if (type == 2 || type == 3) {
        pad = 0;
    }
    task->unk6C = D_8004D49C[type].unk8 - pad;
    task->unk6E = D_8004D49C[type].unkA;
    task->unk50 = x + task->unk6C;
    task->unk52 = y + task->unk6E;
    return task;
}

void func_8001C5C4(Unk8001BB68 *task, s32 x, s32 y) {
    Unk8001C5C4 *children = task->children;
    s32 i;
    u32 type;
    s32 wx;
    s32 wy;
    Task8001C454 *item;

    task->x = x;
    task->y = y;
    for (i = 0; i < 3; i++) {
        item = children->items[i];
        if (item != NULL && item->state == 1) {
            item->unk50 = item->unk6C + x;
            item->unk52 = item->unk6E + y;
        }
    }
    type = task->type;
    if (children->windows[0] != NULL) {
        wx = task->x + D_8004D49C[type].unk14;
        wy = task->y + D_8004D49C[type].unk16;
        if (type < 2) {
            wx -= task->w;
        }
        children->windows[0]->setPos(children->windows[0], wx, wy);
    }
    if (children->windows[1] != NULL) {
        wx = task->x + D_8004D49C[type].unk18;
        wy = task->y + D_8004D49C[type].unk1A;
        if (type < 2) {
            wx -= task->w;
        }
        children->windows[1]->setPos(children->windows[1], wx, wy);
    }
}

typedef struct Delays3 {
    s32 frames[3];
} Delays3;

extern Delays3 D_800102CC;

void func_8001C72C(Unk8001BB68 *task, Unk8001C5C4 *children) {
    Delays3 delays;

    switch (task->state) {
    case 0:
    default:
        task->unk28(task, 2);
        break;
    case 1:
        if (children->windows[1]->m168(children->windows[1]) != 0) {
            task->unk28(task, 2);
            task->unk2C(task, 1);
            children->unk14->unk28(children->unk14, 2);
            children->windows[0]->m144(children->windows[0], 0);
            children->windows[1]->m144(children->windows[1], 0);
        } else if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
            children->windows[1]->m128(children->windows[1]);
        }
        if (children->windows[1]->m170(children->windows[1]) != 0) {
            children->unk14->visible = 1;
        } else {
            children->unk14->visible = 0;
        }
        break;
    case 2:
        delays = D_800102CC;
        switch (task->step) {
        case 0:
        default:
            if (task->mode == 0) {
                D_800553DC.playSound(0x40019);
            } else {
                D_800553DC.playSound(0x4001A);
            }
        case 1:
        case 2:
            if (task->counter++ >= delays.frames[task->step]) {
                children->items[task->step] = func_8001C4D8(task->unk54, task->x, task->y, task->w, task->h, task->type);
                children->items[task->step]->unkB8 = task->mode;
                if (task->mode == 0) {
                    children->items[task->step]->unk5C = 0x199;
                } else {
                    children->items[task->step]->unk5C = 0x333;
                }
                task->unk40(task);
                task->counter = 0;
            }
            break;
        case 3:
            if (task->mode == 0) {
                if (children->items[2]->unkBC != 0) {
                    task->unk28(task, 1);
                    children->unk14->unk28(children->unk14, 1);
                    children->windows[0]->m144(children->windows[0], 1);
                    children->windows[1]->m144(children->windows[1], 1);
                }
            } else if (task->mode == 1) {
                if (children->items[2] == NULL) {
                    task->unk28(task, 3);
                }
            }
            break;
        }
        break;
    case 3:
        break;
    }
}

char *strncpy(char *dst, char *src, s32 n);

Unk8001BB68 *func_8001CAC0(s32 id, s16 x, s16 y, s32 file, s32 index, u32 type) {
    Obj8001F8F8 fn;
    char name[0x20];
    Unk8001BB68 *task;
    Unk8001C5C4 *children;
    s32 end;
    u8 *text;
    s32 w;
    s32 i;

    task = func_800144DC((void (*)(void *))func_8001C72C, 0x6C, 0x18);
    task->unk54 = id;
    task->x = x;
    task->y = y;
    children = task->children;
    task->setPos = func_8001C5C4;
    task->type = type;
    func_8001F8F8(&fn);
    i = 0;
    children->windows[0] = func_8001AAB4(task->unk54, 2, task->x + D_8004D49C[type].unk14, task->y + D_8004D49C[type].unk16);
    children->windows[0]->m160(children->windows[0], 3);
    children->windows[1] = func_8001AAB4(task->unk54, 1, task->x + D_8004D49C[type].unk18, task->y + D_8004D49C[type].unk1A);
    children->windows[1]->m160(children->windows[1], 3);
    task->file = file;
    text = (u8 *)fn.unk0(file, index);
    if (text[0] == 2 && text[1] == 7) {
        end = 2;
        while (text[end] != 2 && text[end + 1] != 7) {
            end++;
        }
        D_8004AD84.bzero(name, sizeof(name));
        if (text[i + 2] == 2 && text[i + 3] == 9) {
            strcpy(name, D_8004853C);
        } else {
            strncpy(name, &text[i + 2], -2 - i + end);
        }
        children->windows[0]->m114(children->windows[0], name, -1);
        children->windows[1]->m114(children->windows[1], &text[end + 2], -1);
    } else {
        children->windows[1]->m114(children->windows[1], text, -1);
    }
    children->windows[1]->m130(children->windows[1], 6);
    children->windows[1]->m14C(children->windows[1]);
    w = fn.unk4(children->windows[1]->text, children->windows[1]->unk50, 0);
    if (w < 0x5F) {
        w = 0x5F;
    } else if (w >= 0x8C) {
        w = 0x8B;
    }
    task->w = w;
    task->h = 0x3E;
    if (type < 2) {
        children->windows[0]->setPos(children->windows[0], children->windows[0]->unkB0 - task->w, children->windows[0]->unkB2);
        children->windows[1]->setPos(children->windows[1], children->windows[1]->unkB0 - task->w, children->windows[1]->unkB2);
    }
    for (i = 0; i < 2; i++) {
        children->windows[i]->m138(children->windows[i], 2);
        children->windows[i]->m144(children->windows[i], 0);
    }
    children->unk14 = func_8001C130(task);
    return task;
}

void func_8001CE60(void) {
    Obj8001FBE0 obj;

    func_8001FBE0(&obj);
    obj.methods[2](0x140, 0);
    obj.methods[4](D_80044744.unk424(0x2780000));
    D_80044744.unk418(0x278);
    D_80044744.unk40C(0x277);
}

typedef struct GlyphMap {
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 index;
    /* 0x3 */ u8 pad;
} GlyphMap;

typedef struct FontInfo {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ GlyphMap *unkC;
    /* 0x10 */ GlyphMap *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} FontInfo;

s16 func_8001CEE0(u8 *s, u8 mode, FontInfo *font) {
    u16 code;
    GlyphMap *map;
    s32 i;

    if (s[0] == 0) {
        return 0x400;
    }
    if (mode != 0) {
        if (s[0] < 4) {
            return (s[0] << 8) | s[1];
        }
        if (s[0] == 0xA) {
            return 0x201;
        }
        code = s[0] << 8;
        code |= s[1];
        if ((u16)(code - 0x824F) < 0x146) {
            map = font->unkC;
            for (i = 4; map[i].code != 0xFFFF; i++) {
                if (code == map[i].code) {
                    return map[i].index;
                }
            }
        } else {
            map = font->unk10;
            for (i = 0; map[i].code != 0xFFFF; i++) {
                if (code == map[i].code) {
                    return map[i].index | 0x100;
                }
            }
        }
    } else {
        if (s[0] == 1) {
            if (s[1] > font->unk16) {
                return (((u16)font->unk16 + 1) & 0xFF) | 0x100;
            }
            return (s[0] << 8) | s[1];
        }
        if (s[0] < 4) {
            return (s[0] << 8) | s[1];
        }
        if (s[0] < font->unk14) {
            return s[0];
        }
    }
    return 0x300;
}
