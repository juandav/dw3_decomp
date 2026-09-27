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
