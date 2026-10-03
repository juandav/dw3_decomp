/* The sixth object of FIGHTSTG.PRO (see fightstg.c): its rodata starts at
   0x8008267C (USA), 4 bytes past a multiple of 8. */

#include "fightstg.h"

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008C8F0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008CFFC);

void func_8008E390(s32 arg0) {
    ((Unk8008CFFC *)createTask(func_8008CFFC, sizeof(Unk8008CFFC), sizeof(Task *)))->unk70 = arg0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008E3C8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008EAA0);

#if VERSION_EU
INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008F5D4);
#endif

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008EAF8);

void func_80090050(s32 arg0, s32 arg1) {
    Unk8008EAF8 *task = createTask(func_8008EAF8, sizeof(Unk8008EAF8), sizeof(Task *));

    task->unk50 = arg0;
    task->unk54 = arg1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80090098);

void func_80090264(void) {
    createTask(func_80090098, 0x70, sizeof(Task *));
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80090290);

void func_800908C0(s32 arg0, s32 arg1) {
    Unk80090290 *task = createTask(func_80090290, sizeof(Unk80090290), sizeof(Task *));

    task->unk74 = arg0;
    task->unk78 = arg1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80090908);

void func_80090F28(s32 arg0) {
    ((Unk80090908 *)createTask(func_80090908, sizeof(Unk80090908), sizeof(Task *)))->unk50 = arg0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80090F60);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80090FF0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800910C8);

void func_80091180(s32 arg0, s32 arg1) {
    Unk800910C8 *task = createTask(func_800910C8, sizeof(Unk800910C8), 0);

    task->unk50 = arg0;
    task->unk54 = arg1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800911C8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091618);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091688);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091788);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091950);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800919EC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091A58);

void func_80092124(void) {
    createTaskWithId(func_80091A58, 0x6C, 7 * sizeof(Task *), 0xE);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80092154);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800921B8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800921EC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80092350);

void func_8009245C(Unk80092350 *task, s32 frames) {
    task->unk50 = 0xFF / frames;
    task->setState(task, TASK_DONE);
}

void func_80092494(s32 frames) {
    ((Unk80092350 *)createTask(func_80092350, sizeof(Unk80092350), 0))->unk50 = 0xFF / frames;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800924DC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80092660);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80092738);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800928BC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80092E0C);

void func_80093058(void) {
    createTask(func_80092E0C, 0x88, 5 * sizeof(Task *));
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093084);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800931CC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093324);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093374);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800933EC);

void func_800935F4(void) {
    createTask(func_800933EC, 0x58, 2 * sizeof(Task *));
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093620);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800937FC);

Unk800937FC *func_80093BB0(s32 *arg0) {
    Unk800937FC *task = createTask(func_800937FC, sizeof(Unk800937FC), 7 * sizeof(Task *));

    task->unk50 = arg0;
    task->unk54 = *arg0;
    *arg0 = -1;
    return task;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093BFC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093CB0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093D7C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093E4C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80093F94);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800940CC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80094278);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80094754);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800947AC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800949AC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80094B1C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80094D04);

Unk800937FC *func_80095154(s32 *arg0) {
    Unk800937FC *task = createTask(func_80094D04, 0x390, 13 * sizeof(Task *));

    task->unk50 = arg0;
    *arg0 = -1;
    return task;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80095194);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009539C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80095660);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80095AC0);

Unk800937FC *func_8009619C(s32 *arg0) {
    Unk800937FC *task = createTask(func_80095AC0, 0xD8, 16 * sizeof(Task *));

    task->unk50 = arg0;
    *arg0 = -1;
    return task;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800961DC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800962F8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800963D4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800965D4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800967A4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80096C8C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80096CEC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80096DB8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80096EE0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80097000);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800973D4);

Unk800973D4 *func_80097B74(s32 *arg0) {
    Unk800973D4 *task = createTask(func_800973D4, sizeof(Unk800973D4), 17 * sizeof(Task *));

    task->unk50 = arg0;
    task->unk5C = *arg0;
    task->unk60 = GAME_FUNCS.getPartyMember(*arg0);
    *arg0 = -1;
    return task;
}

void func_80097BEC(s32 *arg0, s32 arg1) {
    func_80097B74(arg0)->unk80 = arg1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80097C14);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80097D74);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80097F8C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098004);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800980C8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098184);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800981F0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009825C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800982C8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098330);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098388);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800983D0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098428);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098808);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800993BC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099400);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099444);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099514);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099674);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009981C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099894);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800999E4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099CC0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099D24);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099F20);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A098);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A214);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A288);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A5AC);

void func_8009A638(MoveTask *task) {
    SVECTOR from;
    SVECTOR to;
    SVECTOR out;
    s32 t;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->t = D_800A31EC * task->tStep;
        task->nextState(task);
        /* fallthrough */
    case TASK_RUN:
        t = task->t;
        from.vx = task->from.x;
        from.vy = task->from.y;
        from.vz = task->from.z;
        to.vx = task->to.x;
        to.vy = task->to.y;
        to.vz = task->to.z;
        D_800A3420.lerp(&from, &to, t, &out);
        task->control->pos.x = out.vx;
        task->control->pos.y = out.vy;
        task->control->pos.z = out.vz;
        task->t += D_800A31EC * task->tStep;
        if (task->t >= 0x1000) {
            task->control->pos.x = task->to.x;
            task->control->pos.y = task->to.y;
            task->control->pos.z = task->to.z;
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_8009A79C(ModelControl *control, ShortVec3 *to, s32 time) {
    MoveTask *task = createTask(func_8009A638, sizeof(MoveTask), 0);

    task->control = control;
    task->to = *to;
    task->from = control->pos;
    task->t = 0;
    task->tStep = 0x1000 / time;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A830);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A8C0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A9B0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AA1C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AA7C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AB1C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AB90);

s32 func_8009ACA8(s32 start) {
    s32 type = D_800A25F0.findType;
    s32 i;

    if ((u32)(type - 1) >= 24) {
        return -1;
    }
    for (i = start; i < 99; i++) {
        if (D_800A25F0.events[i].type == type) {
            return i;
        }
    }
    return -1;
}

s8 func_8009AD14(s32 type) {
    D_800A25F0.findType = type;
    return D_800A25F0.found = func_8009ACA8(0);
}

s8 func_8009AD54(void) {
    return D_800A25F0.found = func_8009ACA8(D_800A25F0.found + 1);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AD94);

void func_8009AE44(EventKey *key) {
    s32 i;
    s32 b = key->unk4;
    s32 a = key->unk0;

    for (i = 0; i < 99; i++) {
        if (D_800A25F0.events[i].type != 0 && D_800A25F0.events[i].args[0] == a && D_800A25F0.events[i].args[1] == b) {
            D_800A25F0.events[i].type = 0;
        }
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AEA4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B430);

void func_8009B5BC(s32 arg0) {
    D_800A34E0.type = 2;
    D_800A34E0.delay = arg0;
    D_800A34E0.args[0] = -1;
    func_8009AA7C(&D_800A34E0);
}

void func_8009B5F8(s32 arg0) {
    D_800A34E0.type = 3;
    D_800A34E0.delay = arg0;
    D_800A34E0.args[0] = -1;
    func_8009AA7C(&D_800A34E0);
}

void func_8009B634(s32 arg0) {
    D_800A34E0.type = 1;
    D_800A34E0.delay = 1;
    D_800A34E0.args[0] = -1;
    D_800A30E4.unk0 = arg0;
    func_8009AB1C(&D_800A34E0);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B678);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B6E8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B7A4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B840);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B8D4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B9B0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BAC0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BC10);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BD20);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BE1C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BF84);

void func_8009BFD0(void) {
    D_800A34E0.type = 0x12;
    D_800A34E0.delay = 0;
    func_8009AA7C(&D_800A34E0);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C000);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C054);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C0B0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C148);

void func_8009C18C(void) {
    D_800A34E0.type = 0x17;
    D_800A34E0.delay = 1;
    func_8009AB1C(&D_800A34E0);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C1C0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C240);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C294);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C330);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C418);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C500);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C5C4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C60C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C764);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C874);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C8B0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C8EC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C998);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CA84);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CB4C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CBEC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CCD4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CDCC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CEA4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CF18);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009CFF4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D0B0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D204);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D560);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D648);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D674);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D8B4);

void func_8009DA88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8009D8B4(arg0, arg1, arg2, arg3, 0);
}

void func_8009DAA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8009D8B4(arg0, arg1, arg2, arg3, 1);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009DACC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009DC14);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009DCCC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009DD18);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009DDCC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009E74C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009E7E4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009EA74);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009EBAC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009EF04);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F028);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F1F0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F280);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F36C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F5D4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F7A4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F9C0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009FB10);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009FC90);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009FDF8);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009FF60);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A00A4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A020C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0400);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0494);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A052C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A05DC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A062C);

#if VERSION_EU
INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A15A8);
#endif

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A067C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0830);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0978);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0A40);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0B10);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0C80);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0DA4);

void func_800A0EEC(void) {
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0EF4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0FDC);
