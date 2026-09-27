#include "game.h"
#include <libgs.h>

/* -G8 unit: small variables defined here are reached through $gp */
static u_char D_8005C490[8];
static RECT D_8005C450;
static void *D_8005C458;

extern void (*D_8004823C[])();
extern void (*D_8004B358[])();
extern void (*D_8004B360[])();
extern void (*D_8004D5B0[])();
extern void (*D_80044B54[])();
extern void (*D_80055404[])();
void *func_80020844();
void func_8002DE28(s32);
void func_80014884(void);
int CdInit(void);
int SetVideoMode(long mode);
int ResetCallback(void);
int VSync(int mode);
void SsInit(void);
void MemCardInit(long val);
void MemCardStart(void);
int CdControl(u_char com, u_char *param, u_char *result);
int CdControlB(u_char com, u_char *param, u_char *result);

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

INCLUDE_ASM("asm/main/nonmatchings/system", func_800121B8);

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

typedef struct Task800126FC {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 state;
    /* 0x10 */ s32 substate;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 i;
    /* 0x1C */ u8 unk1C[0xC];
    /* 0x28 */ void (*unk28)(struct Task800126FC *, s32);
    /* 0x2C */ u8 unk2C[0xC];
    /* 0x38 */ void (*unk38)(struct Task800126FC *);
    /* 0x3C */ u8 unk3C[0x14];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 cursor;
    /* 0x5C */ s32 count;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ Fade fades[3];
} Task800126FC;

extern s32 D_8005C488;
extern s32 D_8005C48C;
extern s32 D_8003EB20[][6];
extern s32 D_8003EB50[];

void func_800126FC(Task800126FC *task, MenuWindows *win) {
    Obj8001F22C obj;
    Obj8001F22C obj2;
    s32 prev;
    s32 done;
    s32 i;
    s32 y;
    s32 y2;
    s32 j;

    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        task->fades[0].duration = task->fades[1].duration = task->fades[2].duration = 10;
        func_800120B8(&task->fades[0], 1);
        func_800120B8(&task->fades[1], 1);
        func_800120B8(&task->fades[2], 1);
        if (D_800484E8.unk7C[0x192] != 0) {
            D_8005C48C = 1;
            task->unk60 = 1;
        } else {
            D_8005C48C = 0;
        }
        task->count = task->unk60 + 5;
        if (func_80012698() >= 0) {
            task->unk64 = 1;
        } else {
            task->unk64 = 0;
        }
        func_800121B8(task, win);
        break;
    case 1:
        switch (task->substate) {
        default:
        case 0:
            if (func_8001214C(&task->fades[0])) {
                func_800123E4(task, win, 0, 1);
                win->title->m114(win->title, D_80044B58(0xB1), 0x13);
                D_800553DC.playSound(0x40019);
                task->substate++;
            }
            break;
        case 1:
            if (func_8001214C(&task->fades[1])) {
                func_800123E4(task, win, 1, 1);
                for (task->i = 0; task->i < task->count; task->i++) {
                    win->items[task->i]->m114(win->items[task->i], D_80044744.getText(0xB1),
                                              D_8003EB20[task->unk60][task->i]);
                }
                D_800553DC.playSound(0x40019);
                if (task->unk64 == 0) {
                    win->items[2]->m138(win->items[2], 7);
                }
                task->substate++;
            }
            break;
        case 2:
            if (func_8001214C(&task->fades[2])) {
                func_800123E4(task, win, 2, 1);
                win->unk4->m114(win->unk4, D_80044B58(0xB1), 5);
                win->unk8->m118(win->unk8, 0, D_800484E8.money);
                win->unk8->m148(win->unk8, 1);
                win->cursor->methods[0](win->cursor, 1);
                task->substate++;
            }
            break;
        case 3:
            prev = task->cursor;
            if (((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 4)) & 1) ||
                ((D_8004AF78.getButtonsNew(0) >> D_8004AF78.getButtonBit(0, 4)) & 1)) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            } else if (((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 6)) & 1) ||
                       ((D_8004AF78.getButtonsNew(0) >> D_8004AF78.getButtonBit(0, 6)) & 1)) {
                task->cursor++;
                if (task->cursor > task->count - 1) {
                    task->cursor = task->count - 1;
                }
            }
            if (prev != task->cursor) {
                D_800553DC.playSound(0x8004513E);
                win->cursor->methods[1](win->cursor, 0xB0, task->cursor * 14 + 0x31);
                break;
            }
            done = 0;
            if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
                D_800553DC.playSound(0x8004503C);
                if (task->unk64 == 0 && task->cursor == 2) {
                    break;
                }
                done = 1;
                if (D_8004ABD8.unk8() == 0x1000) {
                    task->unk14 = 1;
                } else {
                    task->unk14 = 0;
                }
                D_8005C488 = task->cursor;
            } else if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 14)) & 1) {
                D_800553DC.playSound(0x800450BD);
                done = 1;
                if (D_8004ABD8.unk8() == 0x1000) {
                    task->unk14 = 0;
                } else {
                    task->unk14 = 1;
                }
            }
            if (done) {
                func_800120B8(&task->fades[0], 0);
                func_800120B8(&task->fades[1], 0);
                func_800120B8(&task->fades[2], 0);
                func_800123E4(task, win, 2, 0);
                win->unk4->m144(win->unk4, 0);
                win->unk8->m144(win->unk8, 0);
                win->cursor->methods[0](win->cursor, 0);
                task->substate++;
            }
            break;
        case 4:
            if (func_8001214C(&task->fades[2])) {
                func_800123E4(task, win, 1, 0);
                for (task->i = 0; task->i < task->count; task->i++) {
                    win->items[task->i]->m144(win->items[task->i], 0);
                }
                D_800553DC.playSound(0x4001A);
                task->substate++;
            }
            break;
        case 5:
            if (func_8001214C(&task->fades[1])) {
                func_800123E4(task, win, 0, 0);
                win->title->m144(win->title, 0);
                D_800553DC.playSound(0x4001A);
                task->substate++;
            }
            break;
        case 6:
            if (func_8001214C(&task->fades[0])) {
                if (task->unk14 == 0) {
                    task->unk28(task, 2);
                    task->unk6C = D_8004D708.unk38();
                } else {
                    task->unk28(task, 3);
                }
            }
            break;
        }
        func_8001F22C(&obj);
        obj.methods[1](0x140, 0);
        obj.methods[3](task->unk50, task->unk54);
        obj.methods[10](0);
        for (i = 0, y = 0x11, y2 = 0x25; i < 3; i++) {
            if (task->fades[i].level != 0) {
                if (task->fades[i].level != 0x1000) {
                    obj.methods[7](task->fades[i].level, 0x1000, 0x1000);
                    obj.methods[9](0, y2);
                } else {
                    obj.methods[7](0x1000, 0x1000, 0x1000);
                }
                obj.methods[5](D_80044744.unk424(0x02770000), 0x15, 0, y);
                obj.methods[5](D_80044744.unk424(0x02770000), 0x17, 0, y);
            }
            y += 0x2E;
            y2 += 0x2E;
        }
        if (task->fades[0].level != 0) {
            if (task->fades[0].level != 0x1000) {
                obj.methods[7](task->fades[0].level, 0x1000, 0x1000);
                obj.methods[9](0x140, 0x19);
            } else {
                obj.methods[7](0x1000, 0x1000, 0x1000);
            }
            obj.methods[5](D_80044B68[0](0x02770000), 0x18, 0x22, 0xD);
        }
        if (task->fades[1].level != 0) {
            if (task->fades[1].level != 0x1000) {
                obj.methods[7](task->fades[1].level, 0x1000, 0x1000);
                obj.methods[9](0x140, 0x52);
            } else {
                obj.methods[7](0x1000, 0x1000, 0x1000);
            }
            obj.methods[5](D_80044B68[0](0x02770000), 0x1C - task->unk60, 0xA8, 0x28);
        }
        if (task->fades[2].level != 0) {
            if (task->fades[2].level != 0x1000) {
                obj.methods[7](task->fades[2].level, 0x1000, 0x1000);
                obj.methods[9](0, 0xA8);
            } else {
                obj.methods[7](0x1000, 0x1000, 0x1000);
            }
            obj.methods[5](D_80044B68[0](0x02770000), 0x1A, 0, 0x9E);
        }
        break;
    case 2:
        switch (task->substate) {
        default:
            task->unk28(task, 2);
        case 0:
        case 1:
        case 2:
            if (D_8004D5B8.funcs.unk38() - task->unk6C >= 2) {
                task->unk6C = D_8004D5B8.funcs.unk38();
                if (++task->unk68 >= 8) {
                    if (++task->substate != 3) {
                        task->unk68 = 0;
                    } else {
                        task->unk68 = 8;
                    }
                }
            }
            break;
        case 3:
        case 4:
        case 5:
            if (D_8004D5B8.funcs.unk38() - task->unk6C >= 2) {
                task->unk6C = D_8004D5B8.funcs.unk38();
                if (++task->unk68 >= 0x10) {
                    if (++task->substate == 6) {
                        task->unk68 = 0xF;
                    } else {
                        task->unk68 = 8;
                    }
                }
            }
            break;
        case 6:
            if (D_800484E8.unk26F8() == 0x1000) {
                D_800484E8.unk2700(D_800484E8.unk34, 0);
            } else {
                D_800484E8.unk2700(0x1000, 0);
                D_8005C488 = task->cursor;
            }
            task->substate++;
            break;
        case 7:
            break;
        }
        func_8001F22C(&obj2);
        obj2.methods[1](0x140, 0);
        obj2.methods[3](task->unk50, task->unk54);
        obj2.methods[10](0);
        for (j = 0; j <= task->substate; j++) {
            if (j == 6) {
                break;
            }
            if (j == task->substate) {
                obj2.methods[6](task->unk68);
            } else if (j < 3) {
                obj2.methods[6](7);
            } else {
                obj2.methods[6](0xF);
            }
            obj2.methods[5](D_80044744.unk424(0x02770000), D_8003EB50[j], 0, 0);
        }
        break;
    case 3:
        break;
    }
}

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

INCLUDE_ASM("asm/main/nonmatchings/system", func_800135C0);

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

void func_80013758(s32 status) {
    switch (status) {
    case 5:
        if (D_80044710.state == 4) {
            CdControlF(9, 0);
        } else {
            func_80013890();
        }
        break;
    case 2:
        switch (D_80044710.state) {
        case 1:
            D_8005C490[0] = 0xA0;
            CdControlF(0xE, D_8005C490);
            D_80044710.state++;
            break;
        case 2:
            func_8002DE88((s32)func_800136CC);
            CdControlF(6, 0);
            D_80044710.state++;
            break;
        case 3:
            D_80044710.state = 4;
            break;
        case 4:
            func_8002DE68(0);
            if (D_80044710.unk20 == 0) {
                D_80044710.state = 0;
                if (D_80044710.unk14 != NULL) {
                    *D_80044710.unk14 = 1;
                }
            } else {
                func_80013890();
            }
            break;
        }
        break;
    }
}

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

int main(void) {
    RECT rect;
    GsIMAGE tim;
    u_char param[8];

    SetVideoMode(0);
    ResetCallback();
    VSync(0);
    SetDispMask(0);
    ResetGraph(0);
    D_8004D5B8.funcs.unk0[0]();
    D_8004D5B8.funcs.unk10[1]();
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x280;
    rect.h = 0x1FF;
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    GsInitGraph(320, 240, 1, 1, 0);
    GsInit3D();
    SsInit();
    InitGeom();
    D_8004D5B8.funcs.unk10[5](320, 640, 1, 0);
    PutDispEnv(&D_8004D5B8.disp[0]);
    VSync(0);
    GsGetTimInfo((u_long *)D_800100C8 + 1, &tim);
    VSync(0);
    LoadImage(&D_8005C450, tim.pixel);
    DrawSync(0);
    VSync(0);
    SetDispMask(1);
    CdInit();
    func_8002DE28(0);
    SetGraphDebug(0);
    param[0] = 0x80;
    while (CdControl(0xE, param, 0) == 0) {
    }
    VSync(3);
    CdControlB(9, 0, 0);
    D_8004AD84.unkC();
    D_800553DC.unk10();
    D_8004D3B0.srand(0);
    D_8004823C[0]();
    D_8004B358[0](0, 0x12);
    D_8004ABD8.unk0[0]();
    D_8004D5B0[0]();
    for (;;) {
        if (D_8005C458 == NULL) {
            D_8004D5B8.funcs.unk10[0]();
            D_8004D5B8.funcs.unk0[0]();
            D_8004ADB8.funcs.unk0();
            D_8004AD84.unk14(2);
            D_8004ABD8.unk0[1]();
            D_8005C458 = func_80020844();
        }
        D_8005C458 = D_8004ADB8.funcs.unk18(D_8005C458);
        D_8004D5B8.funcs.unk10[2](D_8005C458);
        D_8004B360[0]();
        D_8004D3B0.rand();
        D_80044B54[0]();
        D_80055404[0]();
    }
}

void func_80014818(void) {
    MemCardInit(0);
    MemCardStart();
    D_8004AD84.bzero(&D_80047F14, sizeof(Unk80047F14));
    D_80047F14.maxRetries = 3;
    D_80047F14.iconCount = -1;
    func_80014884();
    D_80047F14.unk310 = 0x100;
    D_80047F14.unk30C = 0x2700;
}

INCLUDE_RODATA("asm/main/nonmatchings/system", D_800100C4);
