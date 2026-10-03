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

void FIGHTSTG_applyCamera(FighterCamera *task) {
    Layer *layer;

    RotMatrixYXZ_gte(&task->rot, &task->coord.coord);
    task->coord.flg = 0;
    task->view.super = &task->coord;
    task->coord.coord.t[0] = task->trans.vx;
    task->coord.coord.t[1] = task->trans.vy;
    task->coord.coord.t[2] = task->trans.vz;
    func_80029DB8(&task->view);
    layer = GFX_FUNCS.getLayer(0x1009);
    layer->setKeepView(layer, 1, task->proj);
    task->frames--;
}

void FIGHTSTG_loadCamera(FighterCamera *task) {
    FighterInfo *info = D_800A32E0.funcs.getInfo(task->fighter);
    s32 i = 6;

    if (task->control->idleMotion != 0) {
        i = 7;
    }
    task->view.vpx = info->camPos[i].x;
    task->view.vpy = -info->camPos[i].y;
    task->view.vpz = -info->camPos[i].z;
    task->view.vrx = info->camRef[i].x;
    task->view.vry = -info->camRef[i].y;
    task->view.vrz = -info->camRef[i].z;
    task->proj = info->camProj[i];
    task->rot.vx = 0;
    task->rot.vy = 0;
    task->rot.vz = 0;
    task->trans.vx = 0;
    task->trans.vy = 0;
    task->trans.vz = 0;
}

void FIGHTSTG_updateCamera(FighterCamera *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
    case TASK_RUN:
        switch (task->step) {
        case 0:
        default:
            if (GFX_FUNCS.getLayer(0x1009) != NULL) {
                FIGHTSTG_loadCamera(task);
                task->frames = 2;
                task->nextStep(task);
            }
            break;
        case 1:
            break;
        }
        if (task->frames != 0) {
            FIGHTSTG_applyCamera(task);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void FIGHTSTG_createCamera(s32 fighter, ModelControl *control) {
    FighterCamera *task = createTask(FIGHTSTG_updateCamera, sizeof(FighterCamera), 0);

    task->fighter = fighter;
    task->control = control;
}

void FIGHTSTG_updateBattleCamera(BattleCamera *task) {
    SVECTOR from;
    SVECTOR to;
    SVECTOR out;
    GsCOORDINATE2 coord;
    GsRVIEW2 view;
    Layer *layer;
    s32 t;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->t = 0x1000;
        task->nextState(task);
        break;
    case TASK_DONE:
        task->setState(task, TASK_RUN);
        task->setSubstate(task, 1);
        /* fallthrough */
    case TASK_RUN:
        switch (task->substate) {
        case 1:
        case 2:
            if (task->t != 0x1000) {
                task->t += (task->tStep >> 8) * GFX_FUNCS.getFrameTime();
                t = task->t;
                if (t < 0x1000) {
                    from.vx = task->from.vpx;
                    from.vy = task->from.vpy;
                    from.vz = task->from.vpz;
                    to.vx = task->to.vpx;
                    to.vy = task->to.vpy;
                    to.vz = task->to.vpz;
                    D_800A3420.lerp(&from, &to, t, &out);
                    task->current.vpx = out.vx;
                    task->current.vpy = out.vy;
                    task->current.vpz = out.vz;
                    from.vx = task->from.vrx;
                    from.vy = task->from.vry;
                    from.vz = task->from.vrz;
                    to.vx = task->to.vrx;
                    to.vy = task->to.vry;
                    to.vz = task->to.vrz;
                    D_800A3420.lerp(&from, &to, t, &out);
                    task->current.vrx = out.vx;
                    task->current.vry = out.vy;
                    task->current.vrz = out.vz;
                    from.vx = task->from.tx;
                    from.vy = task->from.ty;
                    from.vz = task->from.tz;
                    to.vx = task->to.tx;
                    to.vy = task->to.ty;
                    to.vz = task->to.tz;
                    D_800A3420.lerp(&from, &to, t, &out);
                    task->current.tx = out.vx;
                    task->current.ty = out.vy;
                    task->current.tz = out.vz;
                    D_800A3420.lerp(&task->from.rot, &task->to.rot, t, &out);
                    task->current.rot.vx = out.vx;
                    task->current.rot.vy = out.vy;
                    task->current.rot.vz = out.vz;
                    from.vx = task->from.rz;
                    from.vy = task->from.proj;
                    from.vz = 0;
                    to.vx = task->to.rz;
                    to.vy = task->to.proj;
                    to.vz = 0;
                    D_800A3420.lerp(&from, &to, t, &out);
                    task->current.rz = out.vx;
                    task->current.proj = out.vy;
                } else {
                    task->t = 0x1000;
                    task->current = task->to;
                }
            }
            RotMatrixYXZ_gte(&task->current.rot, &coord.coord);
            coord.coord.t[0] = task->current.tx;
            coord.coord.t[1] = task->current.ty;
            coord.coord.t[2] = task->current.tz;
            coord.flg = 0;
            coord.param = NULL;
            coord.super = NULL;
            coord.sub = NULL;
            view.vpx = task->current.vpx;
            view.vpy = task->current.vpy;
            view.vpz = task->current.vpz;
            view.vrx = task->current.vrx;
            view.vry = task->current.vry;
            view.vrz = task->current.vrz;
            view.rz = task->current.rz << 12;
            view.super = &coord;
            func_80029DB8(&view);
            layer = GFX_FUNCS.getLayer(task->layerId);
            layer->setKeepView(layer, 1, task->current.proj);
            if (task->t == 0x1000) {
                task->nextSubstate(task);
            }
            break;
        }
        break;
    case TASK_KILL:
        layer = GFX_FUNCS.getLayer(task->layerId);
        layer->setKeepView(layer, 0, 0);
        break;
    }
}

void FIGHTSTG_setBattleCameraView(BattleCamera *task, CameraView *view) {
    task->current = *view;
    task->t = 0x1000;
    task->setState(task, TASK_DONE);
}

void FIGHTSTG_fadeBattleCamera(BattleCamera *task, CameraView *from, CameraView *to, s32 time) {
    if (from != NULL) {
        task->from = *from;
    } else {
        task->from = task->current;
    }
    task->to = *to;
    task->tStep = 0x100000 / time;
    task->t = 0;
    task->setState(task, TASK_DONE);
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091788);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80091950);

void FIGHTSTG_createBattleCamera(s32 layerId) {
    BattleCamera *task = createTaskWithId(FIGHTSTG_updateBattleCamera, sizeof(BattleCamera), 0, 0x12);

    task->set = FIGHTSTG_setBattleCameraView;
    task->fade = FIGHTSTG_fadeBattleCamera;
    task->getEnemyView = func_80091950;
    task->layerId = layerId;
    task->getFighterView = func_80091788;
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

void func_80093374(void) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 0);
    drawer.setTexture(0x200, 0);
    drawer.draw(FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16), 10, 246, 74);
}

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

Unk80094278 *func_80094754(s32 arg0, s32 arg1, s32 arg2) {
    Unk80094278 *task = createTask(func_80094278, sizeof(Unk80094278), 0x60);

    task->unk54 = arg0;
    task->unk58 = arg1;
    task->unk5C = arg2;
    return task;
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

/* Returns fighter index's unk3D (a 1-based DIGIMON_DATA entry) when that
   entry is among member's partner slots, else 0 */
s32 func_800961DC(Unk800967A4 *task, s32 index, s32 member) {
    BattleFighter *fighter;
    s32 partner;
    s32 next;
    s32 count;
    s32 i;

    GAME.funcs.getPartyMember(index);
    partner = GAME.funcs.getPartyMember(member);
    fighter = &D_800A31E8.fighters[0][index];
    next = ON_PARTNER_ENTRY_ADDED(fighter->id)->unk3D;
    count = GAME.funcs.getPartnerSlots(partner, task->slots);
    if (count <= 0 || next == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        if (task->slots[i] == DIGIMON_DATA[next - 1].id) {
            return next;
        }
    }
    return 0;
}

void func_800962F8(Unk800967A4 *task) {
    SpriteDrawer drawer;
    s32 sheet;
    s32 i;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    drawer.setTexture(0x200, 0);
    for (i = 0; i < task->count; i++) {
        if (task->unk74[i] != 0) {
            drawer.draw(sheet, 0x30, 0x5A, 0x45 + i * 0x1F);
        }
    }
}

void func_800963D4(Unk800967A4 *task, Unk800967A4Windows *w) {
    char *text;
    s32 i;

    text = FILE_CACHE.load(TEXT_FILE(0x80));
    for (i = 0; i < task->count; i++) {
        w->unk4[i] = createTextWindow(0x1005, 3, 0x6C, 0x4E + i * 0x20);
        w->unk4[i]->setString(w->unk4[i], text, 14);
        w->unk14[i] = createTextWindow(0x1005, 3, 0x99, 0x4E + i * 0x20);
        w->unk14[i]->setString(w->unk14[i], text, 16);
        w->unk24[i] = createTextWindow(0x1005, 3, 0x6C, 0x5C + i * 0x20);
        w->unk24[i]->setString(w->unk24[i], text, 13);
        w->unk34[i] = createTextWindow(0x1005, 3, 0x99, 0x5C + i * 0x20);
        w->unk34[i]->setString(w->unk34[i], text, 16);
        w->unkC[i] = createTextWindow(0x1005, 3, 0x98, 0x4E + i * 0x20);
        w->unk1C[i] = createTextWindow(0x1005, 3, 0xBB, 0x4E + i * 0x20);
        w->unk2C[i] = createTextWindow(0x1005, 3, 0x98, 0x5C + i * 0x20);
        w->unk3C[i] = createTextWindow(0x1005, 3, 0xBB, 0x5C + i * 0x20);
        w->unk44[i] = createTextWindow(0x1005, 1, 0x24, 0x4C + i * 0x20);
    }
}

void func_800965D4(Unk800967A4 *task, Unk800967A4Windows *w) {
    BattleFighter *fighter;
    s32 i;

    for (i = 0; i < task->count; i++) {
        fighter = &D_800A31E8.fighters[0][task->unk5C[i]];
        w->unkC[i]->setNumber(w->unkC[i], 0, fighter->hp);
        w->unkC[i]->setRightAlign(w->unkC[i], 1);
        w->unk1C[i]->setNumber(w->unk1C[i], 0, fighter->maxHp);
        w->unk1C[i]->setRightAlign(w->unk1C[i], 1);
        w->unk2C[i]->setNumber(w->unk2C[i], 0, fighter->mp);
        w->unk2C[i]->setRightAlign(w->unk2C[i], 1);
        w->unk3C[i]->setNumber(w->unk3C[i], 0, fighter->maxMp);
        w->unk3C[i]->setRightAlign(w->unk3C[i], 1);
        w->unk44[i]->setString(w->unk44[i], GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(task->unk5C[i])), -1);
        if (fighter->hp == 0) {
            w->unk44[i]->setPalette(w->unk44[i], 7);
        } else {
            w->unk44[i]->setPalette(w->unk44[i], 0);
        }
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800967A4);

void func_80096C8C(s32 *done, s32 *arg1, s32 arg2) {
    Unk800967A4 *task = createTask(func_800967A4, sizeof(Unk800967A4), 0x50);

    task->unk50 = done;
    *done = -1;
    task->unk54 = arg1;
    task->unk58 = arg2;
}

void func_80096CEC(Unk800973D4 *task) {
    SpriteDrawer drawer;
    s32 sheet;

    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    drawer.setTexture(0x200, 0);
    drawer.draw(sheet, 0x2B, 0xA7, 0x8F);
    if (task->tech != 0) {
        drawer.draw(sheet, 2, 0xA7, 0xB8);
        drawer.draw(sheet, 0x29, 0xA3, 0x21);
    }
}

void func_80096DB8(Unk800973D4 *task, Unk800973D4Windows *w) {
    s32 i;

    for (i = 0; i < 4; i++) {
        w->names[i] = createTextWindow(0x1005, 1, 0xBB, 0x92 + i * 0x13);
    }
    w->unk20[4] = createTextWindow(0x1005, 1, 0xAB, 0x92);
    w->unk20[0] = createTextWindow(0x1005, 1, 0xBB, 0xA5);
    w->unk20[1] = createTextWindow(0x1005, 1, 0xBB, 0xB8);
    w->unk20[2] = createTextWindow(0x1005, 3, 0x10E, 0xBA);
    w->unk20[3] = createTextWindow(0x1005, 3, 0x133, 0xBA);
    for (i = 0; i < 4; i++) {
        w->mp[i] = createTextWindow(0x1005, 3, D_800A235C[i * 2], 0x39);
    }
}

void func_80096EE0(Unk800973D4 *task, Unk800973D4Windows *w, s32 visible) {
    DigimonData *data;
    s32 i;

    if (visible) {
        for (i = 0; i < task->count; i++) {
            data = ON_PARTNER_ENTRY_ADDED(task->ids[i]);
            if (data != NULL) {
                w->names[i]->setString(w->names[i], FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (w->names[i] != NULL) {
                w->names[i]->setVisible(w->names[i], visible);
            }
        }
    }
}

void func_80097000(Unk800973D4 *task, Unk800973D4Windows *w, s32 visible) {
    char *text;
    BattleFighter *active;
    BattleFighter *other;
    DigimonData *data;
    s32 i;

    text = FILE_CACHE.load(TEXT_FILE(0x80));
    if (visible) {
        active = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        other = &D_800A31E8.fighters[0][task->unk5C];
        data = ON_PARTNER_ENTRY_ADDED(task->ids[task->unk64]);
        w->unk20[4]->setString(w->unk20[4], FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
        w->unk20[0]->setString(w->unk20[0], text, 0x1B);
        if ((active->flags & 0x10) || (other->flags & 0x10)) {
            w->unk20[0]->setPalette(w->unk20[0], 7);
        } else {
            w->unk20[0]->setPalette(w->unk20[0], 0);
        }
        if (task->tech != 0) {
            w->unk20[1]->setString(w->unk20[1], text, 0x1C);
            w->unk20[2]->setString(w->unk20[2], text, 0xD);
            w->unk20[3]->setNumber(w->unk20[3], 0, D_800427E8[task->tech - 1].mp);
            w->unk20[3]->setRightAlign(w->unk20[3], 1);
            if (active->mp < D_800427E8[task->tech - 1].mp || other->mp < D_800427E8[task->tech - 1].mp) {
                w->unk20[1]->setPalette(w->unk20[1], 7);
            } else if ((active->flags & 0x20) || (other->flags & 0x20) || (active->flags & 8)) {
                w->unk20[1]->setPalette(w->unk20[1], 7);
            } else if (active->hp <= 0 || other->hp <= 0) {
                w->unk20[1]->setPalette(w->unk20[1], 7);
            } else {
                w->unk20[1]->setPalette(w->unk20[1], 0);
            }
            w->mp[0]->setString(w->mp[0], text, 0xD);
            w->mp[1]->setNumber(w->mp[1], 0, active->mp);
            w->mp[1]->setRightAlign(w->mp[1], 1);
            w->mp[2]->setString(w->mp[2], text, 0x10);
            w->mp[3]->setNumber(w->mp[3], 0, active->maxMp);
            w->mp[3]->setRightAlign(w->mp[3], 1);
        }
    } else {
        for (i = 0; i < 5; i++) {
            if (w->unk20[i] != NULL) {
                w->unk20[i]->setVisible(w->unk20[i], visible);
            }
        }
        for (i = 0; i < 4; i++) {
            if (w->mp[i] != NULL) {
                w->mp[i]->setVisible(w->mp[i], visible);
            }
        }
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800973D4);

Unk800973D4 *func_80097B74(s32 *arg0) {
    Unk800973D4 *task = createTask(func_800973D4, sizeof(Unk800973D4), 17 * sizeof(Task *));

    task->unk50 = arg0;
    task->unk5C = *arg0;
    task->unk60 = GAME_FUNCS.getPartyMember(*arg0);
    *arg0 = -1;
    return task;
}

void func_80097BEC(s32 *arg0, s32 *arg1) {
    func_80097B74(arg0)->unk80 = arg1;
}

void func_80097C14(Unk80097F8C *task) {
    SpriteDrawer drawer;
    s32 sheet;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    if (task->unk98 != 0) {
        if (GFX.funcs.getTime() - task->unk94 >= 4) {
            task->unk94 = GFX.funcs.getTime();
            task->unk90++;
            if (task->unk90 >= 5) {
                task->unk90 = 0;
            }
        }
        drawer.setTexture(0x140, 0);
        drawer.setClutRow(task->unk90);
        drawer.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 10, 0x123, 0xD0);
        drawer.setClutRow(0);
    }
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    drawer.setTexture(0x200, 0);
    drawer.draw(sheet, 0x31, 0xB, 0xBC);
}

void func_80097D74(Unk80097F8C *task, Unk80097F8CWindows *windows) {
    switch (task->substate) {
    case 0:
    default:
        if (task->unk74 != 0) {
            task->substate++;
        }
        break;
    case 1:
        task->unk84 = GFX_FUNCS.getTime();
        task->unk80 = 3;
        windows->lines[task->unk78]->setVisible(windows->lines[task->unk78], 1);
        task->substate++;
        break;
    case 2:
        if (task->unk80 < GFX_FUNCS.getTime() - task->unk84) {
            if (++task->unk78 >= task->unk7C) {
                task->unk98 = 1;
                task->substate++;
            } else {
                task->substate = 1;
            }
        }
        break;
    case 3:
        if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            if (task->unk50[++task->unk88] == 0) {
                task->state = 3;
            } else {
                task->unkAC(task, task->unk50[task->unk88], 0);
                task->setSubstate(task, 0);
            }
            task->unk98 = 0;
        }
        break;
    case 4:
        if (GFX_FUNCS.getTime() - task->step > 0x14 || (PAD.getPressed(0) & (1 << PAD_CROSS))) {
            task->state = 3;
        }
        break;
    }
}

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

void func_80098004(Unk80097F8C *task, Unk80097F8CWindows *w, s32 side, s32 index) {
    BattleFighter *fighter;
    BattleTableEntry *entry;

    if (side == 0) {
        w->lines[0]->setSubString(w->lines[0], GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(index)), -1, 1);
    } else {
        fighter = &D_800A31E8.fighters[1][index];
        entry = D_800A2584(fighter->id);
        w->lines[0]->setSubString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x4F)), entry->nameId, 1);
    }
}

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
            if (fighters[i].id != 0 && fighters[i].hp != 0 && fighters[i].hp < fighters[i].maxHp) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 1:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && fighters[i].hp != 0 && (fighters[i].flags & 1)) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 2:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && fighters[i].hp != 0 && (fighters[i].flags & 2)) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 3:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && fighters[i].hp != 0 && (fighters[i].flags & 4)) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 4:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && fighters[i].hp != 0 && fighters[i].flags != 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 5:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && fighters[i].hp == 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 6:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    case 7:
    case 8:
    case 9:
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && fighters[i].hp != 0) {
                task->found[task->foundCount++] = i;
            }
        }
        break;
    }
}

void func_80098428(Unk80097F8C *task, Unk80097F8CWindows *w, BattleMessage *msg) {
    BattleFighter *fighter;
    BattleTableEntry *entry;
    s32 member;
    u8 side;
    s32 kind;
    s32 i;

    if (task->foundCount != 0) {
        side = msg->side;
        kind = msg->kind;
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), task->foundCount + 0x15);
        if (side == 0) {
            for (i = 0; i < task->foundCount; i++) {
                member = GAME.funcs.getPartyMember(task->found[i]);
                if (member >= 0) {
                    w->lines[0]->setSubString(w->lines[0], GAME.funcs.getPartnerStats(member), -1, i + 1);
                }
            }
        } else {
            for (i = 0; i < task->foundCount; i++) {
                fighter = &D_800A31E8.fighters[1][task->found[i]];
                if (fighter->id != 0) {
                    entry = D_800A2584(fighter->id);
                    w->lines[0]->setSubString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x4F)), entry->nameId, i + 1);
                }
            }
        }
        switch (kind) {
        case 0:
        default:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x22);
            w->lines[1]->setNumber(w->lines[1], 1, msg->value);
            break;
        case 1:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x28);
            break;
        case 2:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x29);
            break;
        case 3:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x2A);
            break;
        case 4:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x2C);
            break;
        case 5:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x2D);
            break;
        case 6:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x2E);
            break;
        case 7:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x30);
            break;
        case 8:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x31);
            break;
        case 9:
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x32);
            break;
        }
        task->unk7C = 2;
    } else {
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x2F);
        task->unk7C = 1;
    }
}

void func_80098808(Unk80097F8C *task, s32 type, s32 *data) {
    Unk80097F8CWindows *w = task->children;
    s32 total;
    s32 side;

    task->unk74 = 1;
    if (w->lines[0] == NULL) {
        w->lines[0] = createTextWindow(0x1005, 1, 0x14, 0xC2);
    }
    if (w->lines[1] == NULL) {
        w->lines[1] = createTextWindow(0x1005, 1, 0x14, 0xD0);
    }
    task->unk78 = 0;
    switch (type) {
    case 1:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), data[0]);
        task->unk7C = 1;
        break;
    case 2:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), data[0]);
        task->unk7C = 2;
        func_80098004(task, w, data[1], D_800A31E8.active[data[1] != 0]);
        break;
    case 3:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 9);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0xA3)), data[1], 1);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 4:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0xB);
        w->lines[1]->setNumber(w->lines[1], 1, data[1]);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 5:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0xA);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0xA3)), data[1], 1);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 6:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x25);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 7:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), data[0]);
        task->unk7C = 2;
        func_80098004(task, w, data[1], data[2]);
        break;
    case 8:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x22);
        w->lines[1]->setNumber(w->lines[1], 1, data[1]);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 9:
        FIGHTSTG_findFighters(task, (FighterFilter *)data);
        func_80098428(task, w, (BattleMessage *)data);
        break;
    case 10:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x27);
        task->unk7C = 2;
        func_80098004(task, w, data[0], data[1]);
        task->unk50[1] = 11;
        task->unk50[2] = data[0];
        task->unk50[3] = data[1];
        task->unk50[4] = data[2];
        break;
    case 11:
        data = &task->unk50[task->unk88 + 1];
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x22);
        w->lines[1]->setNumber(w->lines[1], 1, data[2]);
        task->unk7C = 2;
        func_80098004(task, w, data[0], data[1]);
        task->unk88 += 3;
        break;
    case 12:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x37);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x4F)), data[1], 1);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 13:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x4E);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x4F);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x4F)), data[0], 1);
        task->unk7C = 2;
        break;
    case 14:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 9);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x6B)), data[1], 1);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 15:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x55);
        w->lines[1]->setNumber(w->lines[1], 1, data[2]);
        task->unk7C = 2;
        func_80098004(task, w, data[0], data[1]);
        break;
    case 16:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x23);
        total = data[1] * data[2];
        w->lines[1]->setNumber(w->lines[1], 1, data[1]);
        w->lines[1]->setNumber(w->lines[1], 2, data[2]);
        w->lines[1]->setNumber(w->lines[1], 3, total);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 17:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x26);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 9);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x6B)), data[0], 1);
        task->unk7C = 2;
        break;
    case 18:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        if (data[2] == 0) {
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x22);
        } else {
            w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x8F);
        }
        w->lines[1]->setNumber(w->lines[1], 1, data[1]);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 19:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), data[1] + 0x49);
        task->unk7C = 2;
        func_80098004(task, w, data[0], D_800A31E8.active[data[0] != 0]);
        break;
    case 20:
        func_80098808(task, 4, data);
        task->unk50[1] = 21;
        task->unk50[2] = (data[0] == 0) << 4;
        task->unk50[3] = data[1];
        break;
    case 21:
        side = task->unk50[task->unk88 + 1];
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 0x22);
        w->lines[1]->setNumber(w->lines[1], 1, task->unk50[task->unk88 + 2]);
        task->unk7C = 2;
        func_80098004(task, w, side, D_800A31E8.active[side != 0]);
        task->unk88 += 2;
        break;
    case 22:
        w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x8C);
        w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), 9);
        w->lines[1]->setSubString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0xA3)), data[0], 1);
        task->unk7C = 2;
        break;
    }
    w->lines[0]->setVisible(w->lines[0], 0);
    w->lines[1]->setVisible(w->lines[1], 0);
}

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

void func_80099444(Unk800999E4 *task) {
    Unk800999E4Windows *w = task->children;
    char *text;
    s32 i;

    if (w->lines[0] == NULL) {
        text = FILE_CACHE.load(TEXT_FILE(0x80));
        for (i = 0; i < 6; i++) {
            w->lines[i] = createTextWindow(0x1005, 1, 0x24, i * 0x13 + 0x6D);
            w->lines[i]->setString(w->lines[i], text, D_800A23AC[i] + 0x6B);
        }
    }
}

void func_80099514(Unk800999E4 *task) {
    SpriteDrawer drawer;
    s32 sheet;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    if (task->showArrow != 0) {
        if (GFX.funcs.getTime() - task->arrowTime >= 4) {
            task->arrowTime = GFX.funcs.getTime();
            task->arrowPalette++;
            if (task->arrowPalette >= 5) {
                task->arrowPalette = 0;
            }
        }
        drawer.setTexture(0x140, 0);
        drawer.setClutRow(task->arrowPalette);
        drawer.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 10, 0x123, 0xD0);
        drawer.setClutRow(0);
    }
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    drawer.setTexture(0x200, 0);
    drawer.draw(sheet, 0x31, 0xB, 0xBC);
}

void func_80099674(Unk800999E4 *task, Unk800999E4Windows *w) {
    s32 pressed = PAD.getPressed(0);

    switch (task->substate) {
    case 0:
    default:
        if (task->unk88 != 0) {
            task->substate++;
        }
        break;
    case 1:
        task->time = GFX_FUNCS.getTime();
        task->delay = 3;
        w->lines[task->line]->setVisible(w->lines[task->line], 1);
        task->substate++;
        break;
    case 2:
        if (task->delay < GFX_FUNCS.getTime() - task->time) {
            if (++task->line >= task->lineCount) {
                task->showArrow = 1;
                if (pressed & (1 << PAD_CROSS)) {
                    SOUND.playSound(0x4001C);
                    if (task->unk64[++task->unk9C] == 0) {
                        task->state = 3;
                    } else {
                        task->unkC0(task, task->unk64[task->unk9C], 0);
                        task->setSubstate(task, 0);
                    }
                    task->showArrow = 0;
                }
            } else {
                task->substate = 1;
            }
        }
        break;
    }
}

void func_8009981C(Unk800999E4 *task, Unk800999E4Windows *windows, s32 arg2) {
    if (arg2 == 0) {
        windows->lines[0]->setSubString(windows->lines[0], GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0])), -1, 1);
    }
}

void func_80099894(Unk800999E4 *task, s32 index, s32 arg2) {
    Unk800999E4Windows *w = task->children;

    task->unk88 = 1;
    if (w->lines[0] == NULL) {
        w->lines[0] = createTextWindow(0x1005, 1, 0x14, 0xC2);
    }
    if (w->lines[1] == NULL) {
        w->lines[1] = createTextWindow(0x1005, 1, 0x14, 0xD0);
    }
    task->unk64[0] = D_800A236C[index][0];
    w->lines[0]->setString(w->lines[0], FILE_CACHE.load(TEXT_FILE(0x80)), 0x16);
    w->lines[1]->setString(w->lines[1], FILE_CACHE.load(TEXT_FILE(0x80)), D_800A236C[index][1]);
    task->lineCount = 2;
    func_8009981C(task, w, 0);
    w->lines[0]->setVisible(w->lines[0], 0);
    w->lines[1]->setVisible(w->lines[1], 0);
}

void func_800999E4(Unk800999E4 *task, Unk800999E4Windows *w) {
    s32 i;
    s32 j;
    s16 tmp;

    switch (task->state) {
    case TASK_INIT:
    default:
        w->cursor = func_8009A214(&D_800A23BC);
        w->cursor->sel = task->unk50;
        for (i = 0; i < 8; i++) {
            j = RANDOM.next() % 8;
            tmp = D_800A23AC[i];
            D_800A23AC[i] = D_800A23AC[j];
            D_800A23AC[j] = tmp;
        }
        func_80099444(task);
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
                SOUND.playSound(0x4001C);
                if (D_800A3308.unkD8(0) == 0) {
                    *task->unk58 = 0;
                    task->setState(task, 3);
                } else {
                    task->picked = w->cursor->sel;
                    for (i = 0; i < 6; i++) {
                        w->lines[i]->setState(w->lines[i], 3);
                    }
                    w->cursor->setState(w->cursor, 3);
                    task->unk5C->state = 3;
                    task->unk60->state = 3;
                    task->nextSubstate(task);
                }
                w->cursor->locked = 1;
            }
            break;
        case 1:
            if (w->lines[0] == NULL && w->lines[1] == NULL) {
                func_80099894(task, (D_800A23AC[task->picked] << 1) | (RANDOM.next() & 1), 0);
                task->setState(task, 2);
            }
            break;
        }
        break;
    case TASK_DONE:
        func_80099514(task);
        func_80099674(task, w);
        if (task->state == 3) {
            *task->unk58 = 1;
        }
        break;
    case TASK_KILL:
        break;
    }
}

void func_80099CC0(s32 *done, Task *arg1, Task *arg2) {
    Unk800999E4 *task = createTask(func_800999E4, sizeof(Unk800999E4), 0x1C);

    task->unk58 = done;
    *done = -1;
    task->unk50 = 0;
    task->unk5C = arg1;
    task->unk60 = arg2;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80099D24);

void func_80099F20(Unk8009A098 *task) {
    SpriteDrawer drawer;
    s32 sheet;
    s32 i;
    s32 y;
    s32 row;

    initSpriteDrawer(&drawer);
    i = 0;
    drawer.setLayerId(0x1005, 1);
    drawer.setTexture(0x200, i);
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    y = task->params.spriteY;
    for (; i < task->params.count; i++) {
        if (task->blink[i] != 0 || task->sel == i) {
            task->blink[i] += GFX.funcs.getFrameTime();
            if (task->blink[i] >= 0x14) {
                if (task->sel != i) {
                    task->blink[i] = 0;
                } else {
                    task->blink[i] -= 0x14;
                }
            }
        }
        row = task->blink[i] >> 2;
        if ((u32)row < 5) {
            drawer.setClutRow(row);
        } else {
            drawer.setClutRow(0);
        }
        drawer.draw(sheet, task->params.sprite, task->params.spriteX, y);
        y += task->params.spriteStep;
    }
}

void func_8009A098(Unk8009A098 *task) {
    s32 pressed;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 2:
        default:
            GFX.vsyncFunc = (void (*)(s32))func_80099D24;
            GFX.vsyncArg = (s32)task;
        case 0:
        case 1:
            task->nextSubstate(task);
        case 3:
            if (task->params.sprite != -1) {
                func_80099F20(task);
            }
            if (task->locked == 0) {
                pressed = PAD.getRepeated(0) | PAD.getPressed(0);
                if (pressed & (1 << PAD_UP)) {
                    if (task->sel != 0) {
                        task->sel--;
                        SOUND.playSound(0x4001B);
                    }
                } else if (pressed & (1 << PAD_DOWN)) {
                    if (task->sel != task->params.count - 1) {
                        task->sel++;
                        SOUND.playSound(0x4001B);
                    }
                }
            }
            break;
        }
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        GFX.vsyncFunc = NULL;
        break;
    }
}

Unk8009A098 *func_8009A214(Unk8009A214 *arg0) {
    Unk8009A098 *task = createTask(func_8009A098, sizeof(Unk8009A098), 0);

    task->params = *arg0;
    return task;
}

void FIGHTSTG_updateJump(Jump *task) {
    s32 y;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->dist = 0;
        switch (task->kind) {
        case 4:
            task->dist = task->distance + 0x2800;
            break;
        case 5:
            task->dist = task->control->pos.z - task->control->homePos.z;
            if (task->dist < 0) {
                task->dist = -task->dist;
            }
            break;
        }
        if (task->control->id == 0x10) {
            task->dist = -task->dist;
        }
        task->t = D_800A31E8.frames * task->speed;
        task->nextState(task);
        /* fallthrough */
    case TASK_RUN:
        switch (task->kind) {
        default:
            y = D_800A3420.ease(2, task->t, task->height);
            task->control->pos.y = D_800A3420.ease(1, task->t, task->y) - y;
            break;
        case 4:
        case 5:
            task->control->pos.y = task->control->homePos.y - D_800A3420.ease(2, task->t, task->height);
            break;
        case 6:
            task->control->pos.y = D_800A3420.ease(0, task->t, task->control->homePos.y);
            break;
        }
        if (task->kind == 4) {
            task->control->pos.z = task->control->homePos.z + D_800A3420.ease(0, task->t, task->dist);
        }
        if (task->kind == 5) {
            task->control->pos.z = task->control->homePos.z + task->dist - D_800A3420.ease(0, task->t, task->dist);
        }
        task->t += D_800A31E8.frames * task->speed;
        if (task->t < 0x1000) {
            break;
        }
        task->nextState(task);
        break;
    case TASK_DONE:
        switch (task->kind) {
        default:
            task->control->pos.y = 0;
            break;
        case 4:
        case 5:
        case 6:
            task->control->pos.y = task->control->homePos.y;
            break;
        }
        if (task->kind == 4) {
            task->control->pos.z = task->control->homePos.z + task->dist;
        }
        if (task->kind == 5) {
            task->control->pos.z = task->control->homePos.z;
        }
        task->nextState(task);
        break;
    case TASK_KILL:
        break;
    }
}

Jump *FIGHTSTG_startJump(ModelControl *control, s32 kind, s32 distance) {
    Jump *task = createTask(FIGHTSTG_updateJump, sizeof(Jump), 0);

    task->kind = kind;
    task->control = control;
    task->distance = distance;
    task->y = control->pos.y;
    task->height = D_800A23E4[kind - 1].height;
    task->speed = D_800A23E4[kind - 1].speed;
    return task;
}

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

void FIGHTSTG_updateBattleSound(BattleSound *task) {
    switch (task->state) {
    case TASK_INIT:
    case TASK_RUN:
    default:
        task->time -= D_800A31E8.frames;
        if (task->time <= 0) {
            SOUND_STATE.keyOff(task->sound, task->voice);
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

BattleSound *FIGHTSTG_playBattleSound(s32 index, s32 time) {
    s32 id;
    BattleSound *task;

    switch (index) {
    default:
        id = D_800A2414[index];
        break;
    case 0x5A:
        id = D_80042728.unk14;
        break;
    case 0x5B:
        SOUND_STATE.stopSound(0x20040006);
        return NULL;
    }
    if (time == 0) {
        SOUND.playSound(id);
        return NULL;
    }
    task = createTask(FIGHTSTG_updateBattleSound, sizeof(BattleSound), 0);
    task->sound = id;
    task->voice = SOUND.playSound(id);
    task->time = time;
    return task;
}

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

/* Pops the next event: the one due soonest (in EU, events of types 2 and 3
   give way to any due no later), moving all the others' times on by its.
   Returns its type, or 0 when there's none or D_800A2588 says to drop it. */
s32 FIGHTSTG_popEvent(void) {
    s32 min = 0x7FFF;
    s32 best = -1;
    s32 i;
    s32 time;
#if VERSION_EU
    QueuedEvent *event;
#endif
    s32 type;

    for (i = 0; i < 99; i++) {
        if (D_800A25F0.events[i].type != 0) {
#if VERSION_EU
            if (best != -1 && D_800A25F0.events[i].time <= D_800A25F0.events[best].time &&
                (D_800A25F0.events[best].type == 2 || D_800A25F0.events[best].type == 3)) {
                best = i;
                min = D_800A25F0.events[i].time;
            }
#endif
            if (D_800A25F0.events[i].time < min) {
                best = i;
                min = D_800A25F0.events[i].time;
            }
        }
    }
    if (best == -1) {
        return 0;
    }
#if VERSION_US
    time = D_800A25F0.events[best].time;
    for (i = 0; i < 99; i++) {
        if (D_800A25F0.events[i].type != 0) {
            D_800A25F0.events[i].time -= time;
        }
    }
    D_800A25F0.curType = D_800A25F0.events[best].type;
    switch (D_800A2588[D_800A25F0.curType]) {
    case 0:
        return 0;
    case -1:
        type = D_800A25F0.events[best].type;
        D_800A25F0.curIndex = best;
        return type;
    default:
        type = D_800A25F0.events[best].type;
        D_800A25F0.curIndex = best;
        D_800A25F0.events[best].type = 0;
        return type;
    }
#elif VERSION_EU
    event = &D_800A25F0.events[best];
    time = event->time;
    for (i = 0; i < 99; i++) {
        if (D_800A25F0.events[i].type != 0) {
            D_800A25F0.events[i].time -= time;
        }
    }
    D_800A25F0.curType = event->type;
    switch (D_800A2588[D_800A25F0.curType]) {
    case 0:
        return 0;
    case -1:
        type = event->type;
        D_800A25F0.curIndex = best;
        return type;
    default:
        type = event->type;
        event->type = 0;
        D_800A25F0.curIndex = best;
        return type;
    }
#endif
}

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
    entry->flags |= 1;
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
    D_800A31E8.unkDB = 1;
    D_800A31E8.fighters[1][0].boosts[1] = -entry->stats[1] >> 1;
    D_800A31E8.fighters[1][0].boosts[3] = -entry->stats[2] >> 1;
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
    action->unk34 = action->hits[0];
    action->unk36 = 1;
#endif
    if (side == 0 && battle->unkD6 == 6 && action->hits[0] == 0) {
        action->unk36 = count;
    } else {
#if VERSION_US
        for (i = 0; i < count; i++) {
#elif VERSION_EU
        for (i = 1; i < count; i++) {
#endif
            if (D_800A3308.unk9C(D_800A317C.unk20, D_800A317C.unk24) != 0) {
                D_800A317C.hits[D_800A317C.unk36++] = 1;
                D_800A317C.unk34++;
            } else {
                D_800A317C.hits[D_800A317C.unk36++] = 0;
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

    if (fighter->mp != 0) {
        D_800A317C.unk2C = fighter->maxMp * entry->unkC / 128;
        if (fighter->mp < D_800A317C.unk2C) {
            D_800A317C.unk2C = fighter->mp;
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
            D_800A317C.hits[i] = 1;
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

    if (D_800A31E8.unkD6 == 2) {
        entry = &D_800427D6[D_800A317C.unk24];
        D_800A317C.unk38[entry->unkA] = 1;
    } else {
        D_800A317C.hits[0] = D_800A3308.unk9C(D_800A317C.unk20, D_800A317C.unk24);
        D_800A317C.unk36++;
        D_800A317C.damage = D_800A3308.unk84(D_800A317C.unk20, D_800A317C.unk24);
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

void FIGHTSTG_projectPoint(Layer *layer, SVECTOR *pos, ShortVec3 *out) {
    s32 shift = 16 - layer->getOtShift(layer);
    DVECTOR screen;
    MATRIX matrix;
    s32 z;

    gte_CompMatrix(&D_80080AF0, &D_8004D3C8, &matrix);
    gte_SetRotMatrix(&matrix);
    gte_SetTransMatrix(&matrix);
    gte_ldv0_unaligned(pos);
    gte_rtps();
    gte_stsxy(&screen);
    gte_stszotz(&z);
    out->x = screen.vx;
    out->y = screen.vy;
    out->z = z >> shift;
}

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

FaceRect *FIGHTSTG_getFighterFace(s32 id) {
    s32 *file = (s32 *)FILE_CACHE.load(FILE_FIGHTERS);

    return (FaceRect *)(FIGHTSTG_getFighterInfo(id)->face - file[0] + (s32)file);
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
    s16 *effect = &D_800A31E8.unkD0;

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

s32 func_8009F028(u8 side, s32 id, s32 value) {
    BattleFighter *fighter;
    s32 own;
    u8 saved;
    s32 result;
    Unk800427D6 *entry;

    if (side == 0) {
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        own = id == ON_PARTNER_ENTRY_ADDED(fighter->id)->skills[0];
    } else {
        fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
        D_800A2584(fighter->id);
        own = 0;
    }
    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    if (own == 1) {
        saved = D_800A3308.stats[0].unk30[7];
        D_800A3308.stats[0].unk30[7] = 0;
        result = func_8009E7E4(side, id, value);
        D_800A3308.stats[0].unk30[7] = saved;
        return result;
    }
    entry = &D_800427D6[id];
    if (fighter->unk1B) {
        result = value * entry->unkC / 32;
    } else {
        result = value * entry->unkC / 64;
    }
    return func_8009E7E4(side, id, result);
}

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
    return (value << 6) + stats->stats[3] * value / 8;
#elif VERSION_EU
    result = (value << 6) + stats->stats[3] * value / 8;
    if (result > 9999) {
        result = 9999;
    }
    return result;
#endif
}

s32 func_8009F280(u8 side, s32 index, s32 big) {
    BattleFighter *fighter;
    s32 value;

    if (side == 0) {
        fighter = &D_800A31E8.fighters[0][index];
    } else {
        fighter = &D_800A31E8.fighters[1][index];
    }
    if (big) {
        value = fighter->maxHp * (RANDOM.next() % 9 + 8) / 128;
    } else {
        value = fighter->maxHp * (RANDOM.next() % 5 + 4) / 128;
    }
#if VERSION_EU
    if (value > 9999) {
        value = 9999;
    }
#endif
    return value;
}

s32 func_8009F36C(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    BattleFighter *fighter;
    s32 chance;
    s32 i;
    s32 j;
    s32 k;

    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    chance = 4;
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (entry->unkA >= 2) {
        if (entry->unkA == 11) {
            chance += entry->unkC;
        }
    } else if (atk->unk30[8] != 0) {
        k = side != 0;
        fighter = &D_800A31E8.fighters[k][D_800A31E8.active[k]];
        if (fighter->unk1B) {
            chance = atk->unk30[8] * 2 + 4;
        } else {
            chance = atk->unk30[8] + 4;
        }
    }
    if (entry->unk9 >= 2) {
        if (entry->unk9 == def->unk25) {
            chance += 0x3C;
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (atk->unk28[i] >= 2 && atk->unk28[i] == def->unk25) {
                chance += 0x10;
                break;
            }
        }
    }
    j = side == 0;
    fighter = &D_800A31E8.fighters[j][D_800A31E8.active[j]];
    if (fighter->flags & 2) {
        chance += fighter->unk1D >> 3;
    }
    if (fighter->flags & 8) {
        chance += fighter->unk1E >> 3;
    }
    if (fighter->flags & 4) {
        chance += fighter->unk1F >> 1;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_8009F5D4(u8 side, s32 id) {
    BattleStats *def;
    Unk800427D6 *entry;
    BattleFighter *fighter;
    s32 value;
    s32 chance;
    s32 j;

#if VERSION_US
    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
#elif VERSION_EU
    if (side == 0) {
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
    }
#endif
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    value = entry->unk8 * 100 / def->resist[entry->unk7 - 2];
    if (value > 0x40) {
        value = 0x40;
    }
    chance = value + 4;
    if (entry->unk9 >= 2 && entry->unk9 == def->unk25) {
        chance = value + 0x40;
    }
    j = side == 0;
    fighter = &D_800A31E8.fighters[j][D_800A31E8.active[j]];
    if (fighter->flags & 2) {
        chance += fighter->unk1D >> 3;
    }
    if (fighter->flags & 8) {
        chance += fighter->unk1E >> 3;
    }
    if (fighter->flags & 4) {
        chance += fighter->unk1F >> 1;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_8009F7A4(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;
    s32 level;
    s32 diff;

    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (side == 0) {
        if (D_800A31E8.unkD6 == 6) {
            return (RANDOM.next() & 0x7F) >= 0x2B;
        }
        diff = atk->stats[4] + atk->unk30[10] - def->stats[4];
        level = atk->level - def->level;
        if (entry->unkA < 2) {
            chance = entry->unk6 + entry->unk6 * (diff / 8 + (level - atk->unk30[8])) / 128;
        } else {
            chance = entry->unk6 + entry->unk6 * (diff / 8 + level) / 128;
        }
    } else {
        level = atk->level - def->level;
        diff = atk->stats[4] - def->stats[4] - def->unk30[11];
        chance = entry->unk6 + entry->unk6 * (diff / 8 + level) / 128;
        if (chance < 0x20) {
            chance = 0x20;
        }
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_8009F9C0(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;
    s32 level;
    s32 diff;

    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (side == 0 && D_800A31E8.unkD6 == 6) {
        return (RANDOM.next() & 0x7F) >= 0x2B;
    }
    diff = atk->stats[3] - def->stats[3];
    level = atk->level - def->level;
    chance = entry->unk6 + entry->unk6 * (diff / 8 + level) / 128;
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_8009FB10(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;
    s32 result;
    s32 base;

    if (side == 0) {
        if (D_80042728.unk3E[0]) {
            return 0;
        }
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (entry->unkA < 2) {
        result = atk->unk2E;
        base = atk->unk2D + atk->stats[3] / 8;
    } else {
        result = entry->unkC;
        base = entry->unkB + atk->stats[3] / 8;
    }
    chance = base - (def->resist[7] + def->resist[1] + def->stats[3] / 2) / 8;
    if (chance <= 0) {
        chance = 1;
    }
    if (chance >= 0x80) {
        chance = 0x7F;
    }
    if ((RANDOM.next() & 0x7F) < chance) {
        return result;
    }
    return 0;
}

s32 func_8009FC90(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;
    s32 base;

    if (side == 0) {
        if (D_80042728.unk3E[1]) {
            return 0;
        }
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (entry->unkA < 2) {
        base = atk->unk2F + atk->stats[3] / 8;
    } else {
        base = entry->unkB + atk->stats[3] / 8;
    }
    chance = base - (def->resist[8] + def->resist[4] + def->stats[3] / 2) / 8;
    if (chance <= 0) {
        chance = 1;
    }
    if (chance >= 0x80) {
        chance = 0x7F;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_8009FDF8(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;
    s32 base;

    if (side == 0) {
        if (D_80042728.unk3E[2]) {
            return 0;
        }
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (entry->unkA < 2) {
        base = atk->unk30[1] + atk->stats[3] / 8;
    } else {
        base = entry->unkB + atk->stats[3] / 8;
    }
    chance = base - (def->resist[9] + def->resist[3] + def->stats[3] / 2) / 8;
    if (chance <= 0) {
        chance = 1;
    }
    if (chance >= 0x80) {
        chance = 0x7F;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_8009FF60(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;

    if (side == 0) {
        if (D_80042728.unk3E[3]) {
            return 0;
        }
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    chance = entry->unkB + atk->stats[3] / 8 - (def->resist[10] + def->resist[2] + def->stats[3] / 2) / 8;
    if (chance <= 0) {
        chance = 1;
    }
    if (chance >= 0x80) {
        chance = 0x7F;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A00A4(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 chance;
    s32 base;

    if (side == 0) {
        if (D_80042728.unk3E[4]) {
            return 0;
        }
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    atk = &D_800A3308.stats[0];
    def = &D_800A3308.stats[1];
    entry = &D_800427D6[id];
    if (entry->unkA < 2) {
        base = atk->unk30[3] + atk->stats[3] / 8;
    } else {
        base = entry->unkB + atk->stats[3] / 8;
    }
    chance = base - (def->resist[11] + def->resist[6] + def->stats[3] / 2) / 8;
    if (chance <= 0) {
        chance = 1;
    }
    if (chance >= 0x80) {
        chance = 0x7F;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A020C(u8 side, s32 id) {
    BattleStats *atk;
    BattleStats *def;
    Unk800427D6 *entry;
    s32 ratio;
    s32 chance;
    s32 power;
    s32 roll;

    if (side == 0) {
        if (D_80042728.unk3E[7]) {
            return 0;
        }
        if (D_800A31E8.fighters[1][D_800A31E8.active[1]].item <= 0) {
            return 0;
        }
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    if (side == 0) {
        atk = &D_800A3308.stats[0];
        def = &D_800A3308.stats[1];
        ratio = atk->stats[4] * 100 / def->stats[4];
        entry = &D_800427D6[id];
        if (ratio > 200) {
            ratio = 200;
        }
        power = (entry->unkB + atk->unk30[14]) * 100 / 64;
        chance = D_800A2584(D_800A31E8.fighters[1][D_800A31E8.active[1]].id)->itemChance * ratio * power / 10000;
        roll = RANDOM.next() % 1024;
        if (roll < chance) {
            return 1;
        }
    }
    return 0;
}

s32 func_800A0400(u8 side, s32 id) {
    BattleStats *stats;
    Unk800427D6 *entry;
    s32 chance;

    if (side == 0 && D_80042728.unk3E[5] != 0) {
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
        if (DIGIMON_DATA[i].id == D_800A31E8.fighters[0][D_800A31E8.active[0]].id) {
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
    chance = entry->unkB + (D_800A3308.stats[0].stats[3] - D_800A3308.stats[1].stats[3]) / 8;
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
    chance = D_800A31E8.fighters[other][D_800A31E8.active[other]].unk1F - (stats->resist[9] + stats->resist[3]) / 8;
    return (RANDOM.next() & 0x7F) < chance;
}

s32 func_800A0A40(u8 side) {
    BattleStats *stats;
    s32 other;
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
    chance = D_800A31E8.fighters[other][D_800A31E8.active[other]].unk1D - (stats->resist[8] + stats->resist[4]) / 8;
    if (chance < 0x20) {
        chance = 0x20;
    }
    return (RANDOM.next() & 0x7F) < chance;
}

void func_800A0B10(u8 side, s32 index, s32 stat, s32 percent) {
    BattleStats *stats;
    BattleFighter *fighter;
    s32 value;
    s32 min;

    if (side == 0) {
        stats = FIGHTSTG_computeStats(0, 0, index);
        fighter = &D_800A31E8.fighters[0][index];
    } else {
        stats = FIGHTSTG_computeStats(0x10, 0, index);
        fighter = &D_800A31E8.fighters[1][index];
    }
    if (fighter->id == 0 || fighter->hp == 0) {
        return;
    }
    if (fighter->boosts[stat] != 0) {
        stats->stats[D_800A3418[stat]] -= fighter->boosts[stat];
    }
    value = stats->stats[D_800A3418[stat]];
    min = -(value / 2);
    fighter->boosts[stat] += value * percent / 128;
    if (fighter->boosts[stat] < min) {
        fighter->boosts[stat] = min;
    }
    if (fighter->boosts[stat] > value) {
        fighter->boosts[stat] = value;
    }
}

s32 func_800A0C80(s32 damage) {
    PartnerStats *partner;
    s32 ratio;
    BattleFighter *fighter;
    s32 value;
    s32 i;
    s16 *acc;

    fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
    ratio = damage * 100 / fighter->maxHp;
    value = ratio * ratio / 20;
    partner = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0]));
    acc = &partner->equip[4];
    for (i = 0; i < 2; i++) {
        if (acc[i] == 0x149) {
            value += value / 5;
        } else if (acc[i] == 0x14A) {
            value += value * 4 / 10;
        }
    }
    if (value > 1000) {
        value = 1000;
    }
    return value;
}

s32 func_800A0DA4(u8 side, s32 id) {
    PartnerStats *partner;
    s32 cost;
    s32 extra;
    s16 item;

    cost = D_800427E8[(id & 0x1FFF) - 1].mp;
    if (side != 0) {
        return cost;
    }
    partner = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_800A31E8.active[0]));
    item = 0;
    if (partner->equip[4] == 0x143 || partner->equip[4] == 0x144) {
        item = partner->equip[4];
    }
    if (partner->equip[5] == 0x143 || partner->equip[5] == 0x144) {
        item = partner->equip[5];
    }
    if (item != 0) {
        cost -= *(s16 *)&GET_ITEM[0](item)->data[6];
        if (cost <= 0) {
            cost = 1;
        }
    }
    if (id & 0x4000) {
        extra = cost / 5;
        if (extra != 0) {
            cost += extra;
        } else {
            cost++;
        }
    }
    return cost;
}

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
