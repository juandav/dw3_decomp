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

typedef struct Shop {
    /* 0x0 */ s32 id;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 price;
} Shop;
extern Shop D_8003E9D8[];

Task8001ACC8 *func_8001AFE0(s16 arg0, s32 arg1, s16 arg2, s16 arg3);

Task80011FBC *func_80012070(s32 arg0);

void func_80011114(Task800119AC *task, Data800119AC *data) {
    s32 prev;

    switch (task->substate) {
    case 0:
    default:
        func_80010F80(&task->fades[0], 1);
        task->substate++;
        break;
    case 1:
        if (func_80011014(&task->fades[0])) {
            data->windows[0]->m114(data->windows[0], D_80044744.getText(0x5D), D_8003E9D8[task->shop].unk4);
            data->windows[1]->m118(data->windows[1], 0, D_800484E8.money);
            data->windows[1]->m148(data->windows[1], 1);
            data->windows[2]->m114(data->windows[2], D_80044744.getText(0x5D), 0x10);
            func_80010F80(&task->fades[1], 1);
            task->substate++;
        }
        break;
    case 2:
        if (func_80011014(&task->fades[1])) {
            data->windows[3]->m114(data->windows[3], D_80044744.getText(0x5D), 0x11);
            data->windows[3]->m118(data->windows[3], 1, D_8003E9D8[task->shop].price);
            data->windows[4]->m114(data->windows[4], D_80044744.getText(0x5D), 0x12);
            data->windows[5]->m114(data->windows[5], D_80044744.getText(0x5D), 0x13);
            data->unk1C->methods[0](data->unk1C, 1);
            task->substate++;
        }
        break;
    case 3:
        prev = task->unk5C;
        if (((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 4)) & 1) ||
            ((D_8004AF78.getButtonsNew(0) >> D_8004AF78.getButtonBit(0, 4)) & 1)) {
            task->unk5C = 0;
        } else if (((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 6)) & 1) ||
                   ((D_8004AF78.getButtonsNew(0) >> D_8004AF78.getButtonBit(0, 6)) & 1)) {
            task->unk5C = 1;
        }
        if (prev != task->unk5C) {
            D_800553DC.playSound(0x8004513E);
            data->unk1C->methods[1](data->unk1C, 0xB8, task->unk5C * 16 + 0x5F);
            break;
        }
        if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
            D_800553DC.playSound(0x8004503C);
            if (task->unk5C != 0) {
                task->substate = 10;
            } else if (D_800484E8.money >= D_8003E9D8[task->shop].price * task->count) {
                task->substate = 20;
            } else {
                task->substate = 10;
                task->unk14 = 1;
            }
        } else if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 14)) & 1) {
            D_800553DC.playSound(0x800450BD);
            task->substate = 10;
        }
        break;
    case 10:
        func_80010F80(&task->fades[1], 0);
        data->windows[3]->m144(data->windows[3], 0);
        data->windows[4]->m144(data->windows[4], 0);
        data->windows[5]->m144(data->windows[5], 0);
        data->unk1C->methods[0](data->unk1C, 0);
        task->substate++;
        break;
    case 11:
        if (func_80011014(&task->fades[1])) {
            if (task->unk14 != 0) {
                func_80010F80(&task->fades[2], 1);
                task->substate = 30;
            } else {
                func_80010F80(&task->fades[0], 0);
                data->windows[0]->m144(data->windows[0], 0);
                data->windows[1]->m144(data->windows[1], 0);
                data->windows[2]->m144(data->windows[2], 0);
                task->substate++;
            }
        }
        break;
    case 12:
        if (func_80011014(&task->fades[0])) {
            task->state = 3;
        }
        break;
    case 20:
        task->unk64 = D_80051194.unk4248;
        task->unk68 = D_8004D708.unk38();
        D_80051194.unk425C(0x4004000D);
        data->unk0 = func_80012070(task->unk50);
        data->unk0->unk64(data->unk0, 0, 0x14);
        task->substate++;
        break;
    case 21:
        if (data->unk0->state == 2) {
            task->fades[0].level = 0;
            task->fades[1].level = 0;
            data->windows[0]->m144(data->windows[0], 0);
            data->windows[1]->m144(data->windows[1], 0);
            data->windows[2]->m144(data->windows[2], 0);
            data->windows[3]->m144(data->windows[3], 0);
            data->windows[4]->m144(data->windows[4], 0);
            data->windows[5]->m144(data->windows[5], 0);
            data->unk1C->methods[0](data->unk1C, 0);
            D_800484E8.money -= D_8003E9D8[task->shop].price * task->count;
            func_80011080();
            task->substate++;
        }
        break;
    case 22:
        if (D_8004D708.unk38() - task->unk68 > 0xF0) {
            data->unk0->unk64(data->unk0, 1, 0x14);
            task->substate++;
        }
        break;
    case 23:
        if (data->unk0->state == 2) {
            D_800553DC.playSound(task->unk64);
            task->state = 3;
        }
        break;
    case 30:
        if (func_80011014(&task->fades[2])) {
            data->windows[3]->m114(data->windows[3], D_80044744.getText(0x5D), 0x14);
            task->unk14 = 0;
            task->substate++;
        }
        break;
    case 31:
        if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
            D_800553DC.playSound(0x4001C);
            data->windows[3]->m144(data->windows[3], 0);
            func_80010F80(&task->fades[2], 0);
            task->substate++;
        }
        break;
    case 32:
        if (func_80011014(&task->fades[2])) {
            func_80010F80(&task->fades[1], 1);
            task->substate = 2;
        }
        break;
    }
}

void func_800119AC(Task800119AC *task, Data800119AC *data) {
    Obj8001F22C obj;
    s32 i;
    s32 n;
    s32 id;

    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        id = D_8004ABD8.unk8();
        for (n = 0; D_8003E9D8[n].id != 0; n++) {
            if (id == D_8003E9D8[n].id) {
                break;
            }
        }
        task->shop = n;
        for (i = 0; i < 3; i++) {
            if (D_800484E8.unk270C(i) >= 0) {
                task->count++;
            }
        }
        data->windows[0] = func_8001AAB4(task->unk50, 1, 0x1D, 0x14);
        data->windows[1] = func_8001AAB4(task->unk50, 3, 0x117, 0x17);
        data->windows[2] = func_8001AAB4(task->unk50, 3, 0x11A, 0x17);
        data->windows[3] = func_8001AAB4(task->unk50, 1, 0x79, 0x34);
        data->windows[4] = func_8001AAB4(task->unk50, 1, 0xC5, 0x5F);
        data->windows[5] = func_8001AAB4(task->unk50, 1, 0xC5, 0x6F);
        data->unk1C = func_8001AFE0(task->unk50, 0, 0xB8, 0x5F);
        data->unk1C->methods[0](data->unk1C, 0);
        task->fades[0].duration = 10;
        task->fades[1].duration = 10;
        task->fades[2].duration = 10;
        break;
    case 1:
        func_80011114(task, data);
        func_8001F22C(&obj);
        obj.methods[1](0x140, 0);
        obj.methods[3](task->unk50, task->unk54);
        obj.methods[10](0);
        if (task->fades[0].level != 0) {
            if (task->fades[0].level != 0x1000) {
                obj.methods[7](task->fades[0].level, 0x1000, 0x1000);
                obj.methods[9](0x57, 0x19);
            }
            obj.methods[5](D_80044744.unk424(0x02770000), 0x41, 0x16, 0x12);
            if (task->fades[0].level != 0x1000) {
                obj.methods[9](0x140, 0x18);
            }
            obj.methods[5](D_80044744.unk424(0x02770000), 0x42, 0xD6, 0xF);
        }
        if (task->fades[1].level != 0) {
            if (task->fades[1].level != 0x1000) {
                obj.methods[7](task->fades[1].level, 0x1000, 0x1000);
                obj.methods[9](0x140, 0x41);
            }
            obj.methods[5](D_80044744.unk424(0x02770000), 0x43, 0x4C, 0x2E);
            if (task->fades[1].level != 0x1000) {
                obj.methods[9](0x140, 0x6D);
            }
            obj.methods[5](D_80044744.unk424(0x02770000), 0x44, 0xAF, 0x59);
        }
        if (task->fades[2].level != 0) {
            if (task->fades[2].level != 0x1000) {
                obj.methods[7](task->fades[2].level, 0x1000, 0x1000);
                obj.methods[9](0x140, 0x41);
            }
            obj.methods[5](D_80044744.unk424(0x02770000), 0x43, 0x4C, 0x2E);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

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

Task80011FBC *func_80012070(s32 arg0) {
    Task80011FBC *task = func_800144DC(func_80011FBC, 0x68, 0);

    task->unk64 = func_80011DF0;
    task->unk50 = arg0;
    task->unk54 = 0;
    return task;
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
