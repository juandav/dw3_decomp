/* The sixth object of FIGHTSTG.PRO (see fightstg.c): its rodata starts at
   0x8008267C (USA), 4 bytes past a multiple of 8. */

#include "fightstg.h"
#include "gte.h"

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008C8F0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008CFFC);

void func_8008E390(s32 arg0) {
    ((Unk8008CFFC *)createTask(func_8008CFFC, sizeof(Unk8008CFFC), sizeof(Task *)))->unk70 = arg0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8008E3C8);

void func_8008EAA0(s8 arg0, s32 arg1, s32 arg2) {
    Unk8008E3C8 *task = createTask(func_8008E3C8, sizeof(Unk8008E3C8), 4);

    task->unk70 = arg0;
    task->unk74 = arg1;
    task->unk84 = arg2;
}

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

void func_80091618(Unk800911C8 *task, Unk80091618 *arg1) {
    task->unk54 = *arg1;
    task->unkF0 = 0x1000;
    task->setState(task, 2);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091688);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091788);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091950);

void func_800919EC(s32 arg0) {
    Unk800911C8 *task = createTaskWithId(func_800911C8, sizeof(Unk800911C8), 0, 0x12);

    task->unkF8 = func_80091618;
    task->unkFC = func_80091688;
    task->unk100 = func_80091950;
    task->unk50 = arg0;
    task->unk104 = func_80091788;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091A58);

void func_80092124(void) {
    createTaskWithId(func_80091A58, 0x6C, 7 * sizeof(Task *), 0xE);
}

void func_80092154(s32 arg0) {
    Task *task = TASK_FUNCS.find(0xE, -1, -1);

    if (task != NULL && task->state == TASK_RUN) {
        task->setSubstate(task, arg0);
    }
}

s32 func_800921B8(void) {
    return ((Task *)TASK_FUNCS.find(0xE, -1, -1))->substate != 0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800921EC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80092350);

void func_8009245C(Unk80092350 *task, s32 frames) {
    task->unk50 = 0xFF / frames;
    task->setState(task, TASK_DONE);
}

Unk80092350 *func_80092494(s32 frames) {
    Unk80092350 *task = createTask(func_80092350, sizeof(Unk80092350), 0);

    task->unk50 = 0xFF / frames;
    return task;
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

void func_80093324(s32 arg0, s32 *done) {
    Unk800931CC *task = createTask(func_800931CC, sizeof(Unk800931CC), 0x1C);

    task->unk54 = done;
    *done = -1;
    task->unk50 = arg0;
}

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

void func_80094754(s32 arg0, s32 arg1, s32 arg2) {
    Unk80094278 *task = createTask(func_80094278, sizeof(Unk80094278), 0x60);

    task->unk54 = arg0;
    task->unk58 = arg1;
    task->unk5C = arg2;
}

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

void func_80096C8C(s32 *done, s32 arg1, s32 arg2) {
    Unk800967A4 *task = createTask(func_800967A4, sizeof(Unk800967A4), 0x50);

    task->unk50 = done;
    *done = -1;
    task->unk54 = arg1;
    task->unk58 = arg2;
}

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

void func_80097F8C(Unk80097F8C *task, void *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        func_80097C14(task);
        func_80097D74(task, children);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098004);

void FIGHTSTG_findFighters(Unk80097F8C *task, FighterFilter *filter) {
    s32 side = filter->side != 0;
    BattleFighter *fighters;
    s32 i;

    task->foundCount = 0;
    fighters = D_800A31E8.fighters[side];
    switch (filter->type) {
    case 0:
    default:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 != 0 && fighters[i].unk8 < fighters[i].unk6) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 1:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 != 0 && (fighters[i].unk1C & 1)) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 2:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 != 0 && (fighters[i].unk1C & 2)) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 3:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 != 0 && (fighters[i].unk1C & 4)) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 4:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 != 0 && fighters[i].unk1C != 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 5:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 == 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 6:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 7:
    case 8:
    case 9:
        for (i = 0; i < 3; i++) {
            if (fighters[i].unk0 != 0 && fighters[i].unk8 != 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098428);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80098808);

void func_800993BC(Unk80097F8C *task) {
    task->substate = 4;
    task->unk98 = 0;
    task->step = GFX_FUNCS.getTime();
}

void func_80099400(void) {
    Unk80097F8C *task = createTask(func_80097F8C, sizeof(Unk80097F8C), 8);

    task->unkAC = func_80098808;
    task->unkB0 = func_800993BC;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099444);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099514);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099674);

void func_8009981C(Task *task, Unk80099894 *windows, s32 arg2) {
    if (arg2 == 0) {
        windows->unk4->setSubString(windows->unk4, GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0])), -1, 1);
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099894);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800999E4);

void func_80099CC0(s32 *done, s32 arg1, s32 arg2) {
    Unk800999E4 *task = createTask(func_800999E4, sizeof(Unk800999E4), 0x1C);

    task->unk58 = done;
    *done = -1;
    task->unk50 = 0;
    task->unk5C = arg1;
    task->unk60 = arg2;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099D24);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099F20);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009A098);

void func_8009A214(Unk8009A214 *arg0) {
    Unk8009A098 *task = createTask(func_8009A098, sizeof(Unk8009A098), 0);

    task->unk58 = *arg0;
}

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
        task->t = D_800A31E8.frames * task->tStep;
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
        task->t += D_800A31E8.frames * task->tStep;
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

s32 FIGHTSTG_findBattleTableIndex(s32 id) {
    BattleTableEntry *table = (BattleTableEntry *)FILE_CACHE.load(FILE_BATTLE_TABLE);
    s32 i;

    for (i = 0; table[i].id != 0; i++) {
        if (table[i].id == id) {
            return i;
        }
    }
    return -1;
}

BattleTableEntry *FIGHTSTG_getBattleTableEntry(s32 id) {
    BattleTableEntry *table = (BattleTableEntry *)FILE_CACHE.load(FILE_BATTLE_TABLE);
    s32 i = FIGHTSTG_findBattleTableIndex(id);

    if (i >= 0) {
        return &table[i];
    }
    return NULL;
}

void FIGHTSTG_pushEvent(BattleEvent *event) {
    s32 i = 0;
    s32 free = -1;

    for (; i < 99; i++) {
        if (D_800A25F0.events[i].type == 0) {
            free = i;
            break;
        }
    }
    if (free != -1) {
        D_800A25F0.events[free].type = event->type;
        D_800A25F0.events[free].time = event->delay;
        for (i = 0; i < 6; i++) {
            D_800A25F0.events[free].args[i] = event->args[i];
        }
    }
}

void FIGHTSTG_pushEventFirst(BattleEvent *event) {
    s32 i;

#if VERSION_US
    if (event->delay <= 0) {
        event->delay = 1;
    }
#elif VERSION_EU
    if (event->delay < 2) {
        event->delay = 2;
    }
#endif
    for (i = 0; i < 99; i++) {
        if (D_800A25F0.events[i].type != 0) {
            D_800A25F0.events[i].time += event->delay;
        }
    }
#if VERSION_US
    event->delay = 0;
#elif VERSION_EU
    event->delay = 1;
#endif
    FIGHTSTG_pushEvent(event);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009AB90);

s32 FIGHTSTG_findEventFrom(s32 start) {
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

s32 FIGHTSTG_findFirstEvent(s32 type) {
    D_800A25F0.findType = type;
    return D_800A25F0.found = FIGHTSTG_findEventFrom(0);
}

s32 FIGHTSTG_findNextEvent(void) {
    return D_800A25F0.found = FIGHTSTG_findEventFrom(D_800A25F0.found + 1);
}

s32 FIGHTSTG_findEvent(s32 type, u8 side, s32 fighter) {
    D_800A25F0.findType = type;
    D_800A25F0.found = FIGHTSTG_findEventFrom(0);
    while (D_800A25F0.found >= 0) {
        if (D_800A25F0.events[D_800A25F0.found].args[0] == side && D_800A25F0.events[D_800A25F0.found].args[1] == fighter) {
            break;
        }
        D_800A25F0.found = FIGHTSTG_findEventFrom(D_800A25F0.found + 1);
    }
    return D_800A25F0.found;
}

void FIGHTSTG_removeEvents(EventKey *key) {
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
    FIGHTSTG_pushEvent(&D_800A34E0);
}

void func_8009B5F8(s32 arg0) {
    D_800A34E0.type = 3;
    D_800A34E0.delay = arg0;
    D_800A34E0.args[0] = -1;
    FIGHTSTG_pushEvent(&D_800A34E0);
}

void func_8009B634(s32 arg0) {
    D_800A34E0.type = 1;
    D_800A34E0.delay = 1;
    D_800A34E0.args[0] = -1;
    D_800A25F0.funcs.unk0 = arg0;
    FIGHTSTG_pushEventFirst(&D_800A34E0);
}

void func_8009B678(u8 side) {
    D_800A34E0.type = 4;
    D_800A34E0.delay = func_8009AEA4(side, 1);
    D_800A34E0.args[0] = side;
    D_800A34E0.args[1] = D_800A31E8.active[side != 0];
    FIGHTSTG_pushEvent(&D_800A34E0);
}

void func_8009B6E8(u8 side) {
    s32 other = side != 0;
    s32 i = FIGHTSTG_findEvent(5, side, other);
    s32 time = func_8009AEA4(side, 2);

    if (i >= 0) {
        QueuedEvent *queued = &D_800A25F0.events[i];

        queued->time = time;
    } else {
        D_800A34E0.type = 5;
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = D_800A31E8.active[other];
        D_800A34E0.args[2] = 0xBD;
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
}

void func_8009B7A4(u8 side, s32 fighter, s32 arg2) {
    s32 i = FIGHTSTG_findEvent(6, side, fighter);

    if (i >= 0) {
        QueuedEvent *queued = &D_800A25F0.events[i];

        queued->args[2] = 0xBD;
    } else {
        D_800A34E0.type = 6;
        D_800A34E0.delay = 1000;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = fighter;
        D_800A34E0.args[2] = arg2;
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
}

void func_8009B840(s32 time) {
    s32 i;

    D_800A25F0.findType = 7;
    i = FIGHTSTG_findEventFrom(0);
    if (time > 0x7FFF) {
        time = 0x7FFF;
    }
    if (i >= 0) {
        D_800A25F0.events[i].time = time;
    } else {
        D_800A34E0.type = 7;
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = -1;
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
}

void func_8009B8D4(u8 side, s32 fighter, s32 arg2) {
    s32 i = FIGHTSTG_findEvent(9, side, fighter);
    s32 other;
    BattleFighter *entry;

    if (i >= 0) {
        QueuedEvent *queued = &D_800A25F0.events[i];

        queued->args[2] = arg2;
    } else {
        D_800A34E0.type = 9;
        D_800A34E0.delay = 1000;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = fighter;
        D_800A34E0.args[2] = arg2;
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
    other = side != 0;
    entry = &D_800A31E8.fighters[other][fighter];
    entry->unk1C |= 1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009B9B0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BAC0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BC10);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BD20);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009BE1C);

void func_8009BF84(s32 arg0) {
    D_800A34E0.type = 8;
    D_800A34E0.delay = 0x7FFF;
    D_800A34E0.args[0] = 0;
    D_800A34E0.args[1] = D_800A31E8.active[0];
    D_800A34E0.args[2] = arg0;
    FIGHTSTG_pushEvent(&D_800A34E0);
}

void func_8009BFD0(void) {
    D_800A34E0.type = 0x12;
    D_800A34E0.delay = 0;
    FIGHTSTG_pushEvent(&D_800A34E0);
}

void func_8009C000(s32 arg0) {
    D_800A34E0.type = 0x13;
    D_800A34E0.delay = func_8009AEA4(0, arg0 + 3);
    D_800A34E0.args[0] = 0;
    D_800A34E0.args[1] = D_800A31E8.active[0];
    FIGHTSTG_pushEvent(&D_800A34E0);
}

void func_8009C054(u8 side) {
    D_800A34E0.type = 0x14;
    D_800A34E0.delay = 1;
    D_800A34E0.args[0] = side;
    D_800A34E0.args[1] = D_800A31E8.active[side != 0];
    FIGHTSTG_pushEventFirst(&D_800A34E0);
}

void func_8009C0B0(void) {
#if VERSION_US
    s32 i = FIGHTSTG_findEvent(0x15, 0, D_800A31E8.active[0]);
    s32 time = func_8009AEA4(0, 8);

    if (i >= 0) {
        QueuedEvent *queued = &D_800A25F0.events[i];

        queued->time = time;
    } else {
        D_800A34E0.type = 0x15;
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = 0;
        D_800A34E0.args[1] = D_800A31E8.active[0];
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
#elif VERSION_EU
    D_800A34E0.type = 0x15;
    D_800A34E0.delay = 1;
    D_800A34E0.args[0] = 0;
    D_800A34E0.args[1] = D_800A31E8.active[0];
    FIGHTSTG_pushEventFirst(&D_800A34E0);
#endif
}

void func_8009C148(void) {
    D_800A34E0.type = 0x16;
    D_800A34E0.delay = 1;
    D_800A34E0.args[0] = 0;
    D_800A34E0.args[1] = D_800A31E8.active[0];
    FIGHTSTG_pushEventFirst(&D_800A34E0);
}

void func_8009C18C(void) {
    D_800A34E0.type = 0x17;
    D_800A34E0.delay = 1;
    FIGHTSTG_pushEventFirst(&D_800A34E0);
}

void func_8009C1C0(void) {
    BattleTableEntry *entry;

    D_800A34E0.type = 0x18;
    D_800A34E0.delay = 3000;
    FIGHTSTG_pushEvent(&D_800A34E0);
    entry = D_800A2584(0x1D3);
    D_800A31E8.unkD8[3] = 1;
    D_800A31E8.fighters[1][0].unk12 = -entry->unk10 >> 1;
    D_800A31E8.fighters[1][0].unk16 = -entry->unk12 >> 1;
}

void func_8009C240(void) {
    s32 i = D_800A25F0.funcs.first(0x18);

    if (i >= 0) {
        D_800A25F0.events[i].time = 1;
    }
}

void func_8009C294(void) {
    s32 side = D_800A317C.unk20 != 0;
    BattleFighter *fighter = &D_800A31E8.fighters[side][D_800A31E8.active[side]];
    s32 value = D_800A3308.unkA4(D_800A317C.unk20, D_800A317C.unk24);

    if (value != 0) {
        if (fighter->unk1B) {
            value *= 2;
        }
        D_800A317C.unk38[2] = value;
    }
}

void func_8009C330(void) {
    BattleAction *action = &D_800A317C;
    Battle800A3308 *funcs = &D_800A3308;
    s32 side = action->unk20 != 0;
    BattleFighter *fighter = &D_800A31E8.fighters[side][D_800A31E8.active[side]];
    Unk800427D6 *entry;
    s32 value;

    if (funcs->unkA8(action->unk20, action->unk24)) {
        entry = &D_800427D6[action->unk24];
        if (entry->unkA < 2) {
            value = funcs->stats[0].unk30[0];
        } else {
            value = entry->unkC;
        }
        if (fighter->unk1B) {
            value *= 2;
        }
        D_800A317C.unk38[3] = value;
    }
}

void func_8009C418(void) {
    BattleAction *action = &D_800A317C;
    Battle800A3308 *funcs = &D_800A3308;
    s32 side = action->unk20 != 0;
    BattleFighter *fighter = &D_800A31E8.fighters[side][D_800A31E8.active[side]];
    Unk800427D6 *entry;
    s32 value;

    if (funcs->unkAC(action->unk20, action->unk24)) {
        entry = &D_800427D6[action->unk24];
        if (entry->unkA < 2) {
            value = funcs->stats[0].unk30[2];
        } else {
            value = entry->unkC;
        }
        if (fighter->unk1B) {
            value *= 2;
        }
        D_800A317C.unk38[4] = value;
    }
}

void func_8009C500(void) {
    s32 side = D_800A317C.unk20 != 0;
    BattleFighter *fighter = &D_800A31E8.fighters[side][D_800A31E8.active[side]];
    Unk800427D6 *entry;
    s32 value;

    if (D_800A3308.unkB0(D_800A317C.unk20, D_800A317C.unk24)) {
        entry = &D_800427D6[D_800A317C.unk24];
        value = entry->unkC;
        if (fighter->unk1B) {
            value *= 2;
        }
        D_800A317C.unk38[entry->unkA] = value;
    }
}

void func_8009C5C4(void) {
    BattleAction *action = &D_800A317C;

    if (D_800A3308.unkB4(action->unk20, action->unk24)) {
        action->unk38[6] = 1;
    }
}

void func_8009C60C(void) {
    s32 count = 3;
    BattleAction *action = &D_800A317C;
    Battle *battle = &D_800A31E8;
    Unk800427D6 *entry = &D_800427D6[action->unk24];
    s32 i;
    s32 side;

    side = action->unk20;
    if (entry->unkA >= 2) {
        count = entry->unk11;
    }
#if VERSION_US
    action->unk34 = 0;
    action->unk36 = 0;
#elif VERSION_EU
    action->unk34 = action->unk30[0];
    action->unk36 = 1;
#endif
    if (side == 0 && battle->unkD0[3] == 6 && action->unk30[0] == 0) {
        action->unk36 = count;
    } else {
#if VERSION_US
        for (i = 0; i < count; i++) {
#elif VERSION_EU
        for (i = 1; i < count; i++) {
#endif
            if (D_800A3308.unk9C(D_800A317C.unk20, D_800A317C.unk24) != 0) {
                D_800A317C.unk30[D_800A317C.unk36++] = 1;
                D_800A317C.unk34++;
            } else {
                D_800A317C.unk30[D_800A317C.unk36++] = 0;
            }
        }
    }
    D_800A317C.unk38[9] = 1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C764);

void func_8009C874(void) {
    BattleAction *action = &D_800A317C;
    Unk800427D6 *e = &D_800427D6[action->unk24];

    action->unk38[e->unkA] = e->unkA;
}

void func_8009C8B0(void) {
    BattleAction *action = &D_800A317C;
    Unk800427D6 *entry = &D_800427D6[action->unk24];

    action->unk38[entry->unkA] = entry->unkA;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C8EC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009C998);

void func_8009CA84(void) {
    s32 other = 1 - (D_800A317C.unk20 != 0);
    Unk800427D6 *entry = &D_800427D6[D_800A317C.unk24];

    D_800A3308.unkE0((u8)(0x10 - D_800A317C.unk20), D_800A31E8.active[other], 1, -entry->unkC);
    func_8009BD20((u8)(0x10 - D_800A317C.unk20), D_800A31E8.active[other], 1, D_800A317C.unk24);
    D_800A317C.unk38[entry->unkA] = entry->unkC;
}

void func_8009CB4C(void) {
    BattleFighter *fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
    Unk800427D6 *entry = &D_800427D6[D_800A317C.unk24];

    if (fighter->unkC != 0) {
        D_800A317C.unk2C = fighter->unkA * entry->unkC / 128;
        if (fighter->unkC < D_800A317C.unk2C) {
            D_800A317C.unk2C = fighter->unkC;
        }
        D_800A317C.unk38[entry->unkA] = D_800A317C.unk2C;
    }
}

void func_8009CBEC(void) {
    s32 i = RANDOM.next() % 2;
    Unk800427D6 *entry;
    PartnerVitals *stats;

    if (D_800A3308.unkC4(D_800A317C.unk20, D_800A317C.unk24)) {
        entry = &D_800427D6[D_800A317C.unk24];
        stats = GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0]));
        stats->status[i] += entry->unkC;
        D_800A317C.unk38[entry->unkA] = 1 << i;
    }
}

void func_8009CCD4(void) {
    Unk800427D6 *entry = &D_800427D6[D_800A317C.unk24];
    PartnerVitals *stats = GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0]));
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_800A3308.unkC4(D_800A317C.unk20, D_800A317C.unk24)) {
            stats->status[i] += entry->unkC;
            D_800A317C.unk38[entry->unkA] |= 1 << i;
        }
    }
}

void func_8009CDCC(void) {
    BattleAction *action = &D_800A317C;
    Unk800427D6 *entry = &D_800427D6[action->unk24];
    PartnerVitals *stats = GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0]));
    s32 i;

    if (D_800A3308.unkC4(action->unk20, action->unk24)) {
        for (i = 0; i < 3; i++) {
            stats->status[i] += entry->unkC;
        }
        D_800A317C.unk38[entry->unkA] = 7;
    }
}

void func_8009CEA4(void) {
    Unk800427D6 *entry;

    if (D_800A3308.unkC8(D_800A317C.unk20, D_800A317C.unk24)) {
        entry = &D_800427D6[D_800A317C.unk24];
        D_800A317C.unk38[entry->unkA] = 1;
    }
}

void func_8009CF18(void) {
#if VERSION_EU
    s32 files[2] = { 0x1B9, 0x1BA };
#endif
    s32 i;

    D_800A317C.unk34 = 0;
    D_800A317C.unk36 = 2;
    for (i = 0; i < 2; i++) {
        if (D_800A3308.unkA0(D_800A317C.unk20, D_800A317C.unk24)) {
            D_800A317C.unk30[i] = 1;
#if VERSION_EU
            D_800A317C.unk60[i] = D_800A3308.unk88(D_800A317C.unk20, files[i]);
#endif
            D_800A317C.unk34++;
        }
    }
#if VERSION_US
    D_800A317C.unk60[0] = D_800A3308.unk88(D_800A317C.unk20, 0x1B9);
    D_800A317C.unk60[1] = D_800A3308.unk88(D_800A317C.unk20, 0x1BA);
#endif
    D_800A317C.unk38[9] = 1;
}

void func_8009CFF4(void) {
    Unk800427D6 *entry;

    if (D_800A31E8.unkD0[3] == 2) {
        entry = &D_800427D6[D_800A317C.unk24];
        D_800A317C.unk38[entry->unkA] = 1;
    } else {
        D_800A317C.unk30[0] = D_800A3308.unk9C(D_800A317C.unk20, D_800A317C.unk24);
        D_800A317C.unk36++;
        D_800A317C.unk28 = D_800A3308.unk84(D_800A317C.unk20, D_800A317C.unk24);
    }
}

void func_8009D0B0(void) {
    Unk800427D6 *entry = &D_800427D6[D_800A317C.unk24];

    switch (entry->unkA) {
    case 2:
        func_8009C294();
        break;
    case 3:
        func_8009C330();
        break;
    case 4:
        func_8009C418();
        break;
    case 5:
        func_8009C500();
        break;
    case 6:
        func_8009C5C4();
        break;
    case 8:
        func_8009C764();
        break;
    case 12:
        func_8009C8EC();
        break;
    case 26:
        func_8009C998();
        break;
    case 11:
        func_8009C8B0();
        break;
    case 27:
        func_8009CA84();
        break;
    case 29:
        func_8009CB4C();
        break;
    case 32:
        func_8009CBEC();
        break;
    case 33:
        func_8009CCD4();
        break;
    case 34:
        func_8009CDCC();
        break;
    case 13:
        func_8009CEA4();
        break;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D204);

void func_8009D560(void) {
    BattleSpeed *speed = &D_800A31E8.speed;
    s32 time;

    switch (speed->mode) {
    case 0:
    default:
        D_800A31E8.frames = GFX_FUNCS.getFrameTime();
        break;
    case 1:
        D_800A31E8.frames = 0;
        break;
    case 2:
        time = GFX_FUNCS.getFrameTime();
        D_800A31E8.frames = 0;
        speed->rest += time;
        while (speed->rest > 4) {
            D_800A31E8.frames++;
            speed->rest -= 4;
        }
        break;
    case 3:
        D_800A31E8.frames = GFX_FUNCS.getFrameTime() * 2;
        break;
    }
}

void func_8009D648(s32 mode) {
    D_800A31E8.speed.mode = mode;
    D_800A31E8.speed.rest = 0;
    func_8009D560();
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D674);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009D8B4);

void func_8009DA88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8009D8B4(arg0, arg1, arg2, arg3, 0);
}

void func_8009DAA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8009D8B4(arg0, arg1, arg2, arg3, 1);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", FIGHTSTG_getFighterInfo);

void FIGHTSTG_cacheFighter(s32 index) {
    FightersFile *file = (FightersFile *)FILE_CACHE.load(FILE_FIGHTERS);
    FighterEntry *entries = (FighterEntry *)((u8 *)file + file->entries);
    u8 *partners = (u8 *)file + file->partners;
    u8 *enemies = (u8 *)file + file->enemies;
    FighterEntry *entry = &entries[index];
    FighterInfo *info;
    s32 i;
    FighterCache *cache = &D_800A32E0;

    cache->id = entry->id;
    cache->unk8 = i = entry->index;
    cache->unkC = entry->kind;
    cache->unk4 = entry->kind >= 0x3A;
    if (cache->unk4 == 0) {
        info = (FighterInfo *)(partners + i * 0xC4);
    } else {
        info = (FighterInfo *)(enemies + i * 0x48);
    }
    cache->unk10 = info;
    cache->info = info;
}

s32 func_8009DCCC(s32 id) {
    s32 *file = (s32 *)FILE_CACHE.load(FILE_FIGHTERS);

    return FIGHTSTG_getFighterInfo(id)->unkC - file[0] + (s32)file;
}

void FIGHTSTG_getFighterRange(u32 enemy, s32 *min, s32 *max) {
    FightersFile *file = (FightersFile *)FILE_CACHE.load(FILE_FIGHTERS);
    FighterEntry *entry = (FighterEntry *)((u8 *)file + file->entries);
    s32 lo = 0xFF;
    s32 hi = 0;
    s32 i = 0;

    while (entry->id != 0) {
        if ((entry->kind >= 0x3A) == enemy) {
            if (i < lo) {
                lo = i;
            }
            if (hi < i) {
                hi = i;
            }
        }
        entry++;
        i++;
    }
    *min = lo;
    *max = hi;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", FIGHTSTG_computeStats);

s32 func_8009E74C(s32 value, s32 arg1) {
    s16 *effect = D_800A31E8.unkD0;

    if (effect[0] < 2) {
        return 0;
    }
    if (arg1 == effect[0]) {
        return value * effect[1] / 128;
    }
    if (D_800A33F4[arg1] == effect[0]) {
        return -(value * effect[1] / 256);
    }
    return 0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009E7E4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009EA74);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009EBAC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009EF04);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_8009F028);

s32 func_8009F1F0(u8 side, s32 id) {
    BattleStats *stats;
    Unk800427D6 *entry;
    u16 value;
    s32 flag;
    s32 fighter;
#if VERSION_EU
    s32 result;
#endif

    if (side == 0) {
        fighter = D_800A31E8.active[0];
        flag = 0;
    } else {
        flag = 0x10;
        fighter = D_800A31E8.active[1];
    }
    FIGHTSTG_computeStats(flag, 1, fighter);
    stats = &D_800A3308.stats[0];
    entry = &D_800427D6[id];
    value = entry->unk2;
#if VERSION_US
    return (value << 6) + stats->unk8[0] * value / 8;
#elif VERSION_EU
    result = (value << 6) + stats->unk8[0] * value / 8;
    if (result > 9999) {
        result = 9999;
    }
    return result;
#endif
}

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

s32 func_800A0400(u8 side, s32 id) {
    BattleStats *stats;
    Unk800427D6 *entry;
    s32 chance;

    if (side == 0 && D_80042728.unk18[0x2B] != 0) {
        return 0;
    }
#if VERSION_US
    stats = &D_800A3308.stats[0];
#elif VERSION_EU
    stats = FIGHTSTG_computeStats(side, 1, D_800A31E8.active[side >> 4]);
#endif
    entry = &D_800427D6[id];
    if (entry->unkA < 2) {
        chance = stats->unk30[5];
    } else {
        chance = entry->unkB;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A0494(s32 actor, s32 id) {
    s32 i;
    Unk800427D6 *entry;
    s32 chance;

    for (i = 0; i < 8; i++) {
        if (DIGIMON_DATA[i].id == D_800A31E8.fighters[0][D_800A31E8.active[0]].unk0) {
            return 0;
        }
    }
    entry = &D_800427D6[id];
    chance = entry->unkB;
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A052C(s32 actor, s32 id) {
    Unk800427D6 *entry;
    s32 chance;

    FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
    FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    entry = &D_800427D6[id];
    chance = entry->unkB + (D_800A3308.stats[0].unk8[0] - D_800A3308.stats[1].unk8[0]) / 8;
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A05DC(s32 actor, s32 id) {
    Unk800427D6 *entry = &D_800427D6[id];
    s32 chance = entry->unkB;

    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A062C(s32 actor, s32 id) {
    Unk800427D6 *entry = &D_800427D6[id];
    s32 chance = entry->unkB;

    return (RANDOM.next() & 0x7F) < chance;
}

#if VERSION_EU
INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A15A8);
#endif

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A067C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0830);

s32 func_800A0978(u8 side, s32 id) {
    BattleStats *stats;
    s32 other;
    BattleFighter *entry;
    s32 flag;
    s32 fighter;
    s32 chance;

    if (side == 0) {
        fighter = D_800A31E8.active[0];
        flag = 0;
    } else {
        flag = 0x10;
        fighter = D_800A31E8.active[1];
    }
    FIGHTSTG_computeStats(flag, 0, fighter);
    stats = &D_800A3308.stats[1];
    other = side != 0;
    chance = D_800A31E8.fighters[other][D_800A31E8.active[other]].unk1F - (stats->unk8[11] + stats->unk8[5]) / 8;
    return (RANDOM.next() & 0x7F) < chance;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0A40);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0B10);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0C80);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0DA4);

void func_800A0EEC(void) {
}

void FIGHTSTG_lerpVector(SVECTOR *from, SVECTOR *to, s32 t, SVECTOR *out) {
    SVECTOR diff;
    SVECTOR step;

    gte_lddp(t);
    diff.vx = to->vx - from->vx;
    diff.vy = to->vy - from->vy;
    diff.vz = to->vz - from->vz;
    gte_ldsv(&diff);
    gte_gpf12();
    *out = *from;
    gte_stsv(&step);
    out->vx += step.vx;
    out->vy += step.vy;
    out->vz += step.vz;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A0FDC);
