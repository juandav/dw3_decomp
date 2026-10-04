/* The fifth object of FIGHTSTG.PRO (see fightstg.c), from the battle
   script: its rodata starts at 0x800825D0 (USA). */

#include "fightstg.h"

BattleScript *func_8008C090(void);
s32 func_8008AF74(BattleScript *script, BattleScriptChildren *children);
void func_8008B784(BattleScript *script, BattleScriptChildren *children);

s32 func_8008ADB0(BattleScript *script, s32 type) {
    switch (type) {
    case 0:
    default:
        return script->unk50 != 0 ? 0x10 : 0;
    case 1:
        return 0;
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 0x10;
    case 5:
        return 0x11;
    case 6:
        return 0x12;
    }
}

void func_8008AE1C(BattleScript *script, BattleScriptChildren *children) {
    s32 hit;

    switch (*script->pc++) {
    case 0:
        if (children->script != NULL) {
            children->script->destroy(children->script);
        }
        children->script = func_8008C090();
        children->script->unk50 = script->unk50 == 0;
        children->script->index = script->hits[3] + 1;
        break;
    /* the match depends on these cases, which do nothing */
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    case 5:
        if (children->script != NULL) {
            children->script->destroy(children->script);
        }
        children->script = func_8008C090();
        children->script->unk50 = script->unk50 == 0;
        switch (script->scripts) {
        case 0:
        default:
            hit = script->hits[0];
            break;
        case 1:
            hit = script->hits[1];
            break;
        case 2:
            hit = script->hits[2];
            break;
        }
        children->script->index = hit + 1;
        script->scripts++;
        break;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AF74);

s32 func_8008B400(BattleScript *script, BattleScriptChildren *children) {
    SVECTOR pos;
    TimLoader loader;
    s32 mode = *script->pc++;
    s32 effect = *script->pc++;
    s32 i;

    if (effect == 9999) {
        effect = script->unk6C;
    }
    switch (mode) {
    case 0:
    default:
        pos.vx = *script->pc++;
        pos.vy = *script->pc++;
        pos.vz = *script->pc++;
        for (i = 0; i < 8; i++) {
            if (children->unk10[i] == NULL) {
                children->unk10[i] = (Task *)FIGHTSTG_startSpriteEffect(effect, &pos);
                break;
            }
        }
        break;
    case 1:
        switch (script->loadStep) {
        case 0:
        default:
            if (!FIGHTSTG_findEffectSheet(effect, &script->effectImages, &script->effectSheet, &script->effectTexPos)) {
                break;
            }
            script->loadStep++;
            /* fallthrough */
        case 1:
            if (script->effectImages == 0 || !FILE_CACHE.isLoading(script->effectImages >> 16)) {
                script->loadStep++;
            }
            script->pc -= 3;
            return 0;
        case 2:
            if (script->effectImages != 0) {
                initTimLoader(&loader);
                loader.setImagePos(script->effectTexPos.x, script->effectTexPos.y);
                loader.loadArchive(FILE_CACHE.getEntry(script->effectImages));
            }
            script->loadStep++;
            /* fallthrough */
        case 3:
            if (script->effectSheet != 0 && FILE_CACHE.isLoading(script->effectSheet >> 16)) {
                script->pc -= 3;
            } else {
                script->loadStep = 0;
            }
            return 0;
        }
    }
    return 1;
}

s32 func_8008B628(BattleScript *script, BattleScriptChildren *children) {
    SVECTOR pos;
    SVECTOR rot;
    s32 mode = *script->pc++;
    s32 id = *script->pc++;
    s32 file;
    s32 i;

    switch (mode) {
    case 0:
    default:
        pos.vx = *script->pc++;
        pos.vy = -*script->pc++;
        pos.vz = -*script->pc++;
        rot.vx = *script->pc++;
        rot.vy = -*script->pc++;
        rot.vz = -*script->pc++;
        for (i = 0; i < 3; i++) {
            if (children->effects[i] == NULL) {
                children->effects[i] = func_80088FC4(id, &pos, &rot);
                break;
            }
        }
        break;
    case 1:
        file = FIGHTSTG_getEffectModelFile(id);
        if (file != 0 && FILE_CACHE.isLoading(file)) {
            script->pc -= 3;
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B784);

s32 func_8008B9A0(BattleScript *script, BattleScriptChildren *children) {
    switch (script->waiting) {
    case 0:
    default:
        script->wait = *script->pc;
        script->waiting = 1;
        script->pc--;
        return 0;
    case 1:
        script->wait -= GFX_FUNCS.getFrameTime();
        script->pc--;
        if (script->wait > 0) {
            return 0;
        }
        script->waiting = 0;
        script->wait = 0;
        script->pc += 2;
        return 1;
    }
}

s32 func_8008BA4C(BattleScript *script, BattleScriptChildren *children) {
    FightStage *stage = TASK_FUNCS.find(0x15, -1, -1);
    s32 mode = *script->pc++;
    s32 id = *script->pc++;
    s32 fadeOut;
    s32 fadeIn;
    s32 motions;
    ModelControl *control;

    if (id == 0x38) {
        id = script->stage;
    }
    if (id == -1) {
        return 1;
    }
    switch (mode) {
    case 0:
    default:
        fadeOut = *script->pc++;
        fadeIn = *script->pc++;
        if (id == 0) {
            id = D_80042728.unkC;
        }
        stage->setStage(stage, id, fadeOut, fadeIn);
        switch (id) {
        case 0x1D:
            control = script->models->get(script->models, 0);
            D_800A3430 = control->idleMotion;
            control->idleMotion = 0;
            break;
        case 0x1E:
            if (D_800A3430 != 0) {
                script->models->get(script->models, 0)->motion = 2;
            }
            break;
        }
        break;
    case 1:
        if (id == 0) {
            return 1;
        }
        motions = func_800860DC(id);
        if (motions != 0 && FILE_CACHE.isLoading(motions)) {
            script->pc -= 3;
            return 0;
        }
        break;
    }
    return 1;
}

void func_8008BBD4(BattleScript *script, BattleScriptChildren *children) {
    s32 sound = *script->pc++;
    s32 time = *script->pc++;

    if (sound == 0x62) {
        sound = script->hits[script->sounds] == 3 ? 0x38 : script->sound;
        script->sounds++;
    } else if (sound == 0x63) {
        sound = script->hits[3] == 3 ? 0x38 : script->sound;
        script->sounds++;
    }
    if (children->sound == NULL) {
        children->sound = FIGHTSTG_playBattleSound(sound, time);
    }
}

void func_8008BC94(BattleScript *script, Unk80092350 **fade) {
    s32 op = *script->pc++;
    s32 frames = *script->pc++;

    switch (op) {
    case 0:
        *fade = func_80092494(frames);
        break;
    case 1:
        if (*fade != NULL) {
            func_8009245C(*fade, frames);
        }
        break;
    }
}

void func_8008BD10(BattleScript *script, BattleScriptChildren *children) {
    s32 more;
    s32 busy;
    s32 i;

    switch (script->state) {
    case 0:
    default:
        switch (script->substate) {
        case 0:
        default:
            script->model = script->unk50 != 0 ? 0x10 : 0;
            script->models = TASK_FUNCS.find(0x14, -1, -1);
            script->fighter = script->models->get(script->models, script->model)->fighter;
            D_800A32E0.funcs.getInfo(script->fighter);
            script->archive = D_800A32E0.unk10->unk8;
            script->pc = (s16 *)FILE_CACHE.getArchiveEntry(script->index, FILE_CACHE.getEntry(script->archive));
            if (script->index != 12) {
                script->nextState(script);
                break;
            }
            script->nextSubstate(script);
            /* fallthrough */
        case 1:
            switch (script->step) {
            case 0:
            default:
                SOUND_STATE.loadBank(0x46);
                script->nextStep(script);
                /* fallthrough */
            case 1:
                if (SOUND_STATE.isLoading()) {
                    return;
                }
            }
            script->nextState(script);
            break;
        }
        break;
    case 1:
        do {
            more = 1;
            switch (*script->pc++) {
            case 1:
                func_8008AE1C(script, children);
                break;
            case 2:
                more = func_8008AF74(script, children);
                break;
            case 3:
                more = func_8008B400(script, children);
                break;
            case 4:
                more = func_8008BA4C(script, children);
                break;
            case 5:
                func_8008B784(script, children);
                break;
            case 6:
                more = func_8008B628(script, children);
                break;
            case 7:
                func_8008BC94(script, &children->fade);
                break;
            /* the match depends on these cases, which do nothing, and on 2 and 3 */
            case 8:
            case 9:
                break;
            case 10:
                func_8008BBD4(script, children);
                break;
            case 11:
                more = func_8008B9A0(script, children);
                break;
            case 0:
            case 0xFF:
                busy = 0;
                if (children->unk4 != NULL) {
                    busy = children->unk4->state < 2;
                }
                if (children->script != NULL) {
                    busy = 1;
                }
                for (i = 0; i < 8; i++) {
                    if (children->unk10[i] != NULL) {
                        busy = 1;
                        break;
                    }
                }
                if (busy) {
                    script->pc--;
                } else {
                    script->setState(script, 3);
                }
                more = 0;
                break;
            }
        } while (more);
        break;
    case 2:
    case 3:
        break;
    }
}

BattleScript *func_8008C090(void) {
    return createTask(func_8008BD10, 0xB4, 16 * sizeof(Task *));
}

#if VERSION_EU
/* the European version has the task of func_800A1048 here */
#include "camera_turn.h"
#endif

/* fightstg_6.c's */
Unk80097F8C *func_80099400(void);
Unk80090908 *func_80090F28(s32 arg0);
void func_8009C054(u8 side);
Unk80097F8C *func_800908C0(s32 arg0, s32 arg1);
Unk8008E3C8 *func_8008EAA0(s32 arg0, s32 arg1, s32 arg2);

/* WFIGHTMN's */
void func_800A8F60(u8 side, s32 damage);

/* A side's first technique (func_8008C8B8): the partner's skills[0] or the
   enemy's battle table unk8[0], its message and WFIGHTMN's func_800A9040,
   then the damage to the other side's active fighter (unk38[6] knocks it
   out, unk38[0x23] takes 70 percent of the partner's HP), a counter when
   that fighter has flag 8 (substate 4) and func_800908C0 when the partner
   misses in battle kind 6. The match depends on the other side's fighter being found
   as its row's offset, other * 0x60, added as an int to its slot in the
   first row, each in a variable of its own in a block of its own (as an
   index, gcc folds the row into (other * 3 + active) * 32); on the blocks
   of their own of substate 0's row and of the event that substate 4 finds;
   on the MP test being written tech->mp > fighter->mp; on unk38[0x23]'s
   damage being stored before lines[0] and on the pointer sum of its HP. */
void func_8008C0BC(Unk8008C0BC *task, Unk80097F8C **children) {
    BattleFighter *fighter;
    BattleFighter *struck;
    BattleFighter *countered;
    Unk800427D6 *tech;
    s32 index;

    switch (task->state) {
    case TASK_INIT:
    default:
        if (task->unk50 == 0) {
            task->tech = ON_PARTNER_ENTRY_ADDED(D_800A31E8.fighters[0][D_800A31E8.active[0]].id)->skills[0];
        } else {
            task->tech = D_800A2584(D_800A31E8.fighters[1][D_800A31E8.active[1]].id)->unk8[0];
        }
        fighter = (D_800A31E8.fighters[1] + D_800A31E8.active[1]);
        tech = &D_800427D6[task->tech];
        if (task->unk50 != 0 && tech->mp > fighter->mp) {
            children[0] = func_80099400();
            task->lines[0] = 0x8D;
            task->lines[1] = task->unk50;
            children[0]->unkAC(children[0], 2, task->lines);
            task->substate = 2;
        } else {
            children[0] = func_80099400();
            task->lines[0] = 8;
            task->lines[1] = task->unk50;
            children[0]->unkAC(children[0], 2, task->lines);
            D_800A317C.unk68(task->unk50, task->tech);
        }
        {
            s32 other = 1 - (task->unk50 >> 4);
            s32 row = other * 0x60;
            BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];

            fighter = (BattleFighter *)(row + (s32)slot);
        }
        if (fighter->flags & 8) {
            task->unk5C = 1;
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            if (children[0] == NULL) {
                children[0] = (Unk80097F8C *)func_800A9040(task->unk50, task->tech);
                {
                    BattleFighter *fighters = D_800A31E8.fighters[0];

                    if (task->unk50 != 0) {
                        fighters = D_800A31E8.fighters[1];
                    }
                    fighters[D_800A31E8.active[task->unk50 != 0]].unkE = 0;
                }
                task->substate++;
            }
            break;
        case 1:
            if (children[0] == NULL) {
                children[0] = func_80099400();
                if (D_800A317C.unk38[9]) {
                    task->lines[0] = 0x10 - task->unk50;
                    task->lines[1] = D_800A317C.damage;
                    task->lines[2] = D_800A317C.unk34;
                    children[0]->unkAC(children[0], 0x10, task->lines);
                    task->damage = D_800A317C.unk34 * D_800A317C.damage;
#if VERSION_EU
                    if (task->damage >= 10000) {
                        task->damage = 9999;
                    }
#endif
                } else if (D_800A317C.unk38[6]) {
                    s32 other = task->unk50 == 0;
                    s32 row = other * 0x60;
                    BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];

                    ((BattleFighter *)(row + (s32)slot))->hp = 0;
                    func_8009C054(other << 4);
                    children[0]->state = 3;
                } else if (D_800A317C.unk38[0x23]) {
                    task->damage = (D_800A31E8.fighters[0] + D_800A31E8.active[0])->hp * 7 / 10;
                    task->lines[0] = 0;
                    task->lines[1] = task->damage;
                    children[0]->unkAC(children[0], 4, task->lines);
                } else if (D_800A317C.hits[0]) {
                    task->lines[0] = (task->unk50 == 0) << 4;
                    task->lines[1] = D_800A317C.damage;
                    children[0]->unkAC(children[0], 4, task->lines);
                    task->damage = D_800A317C.damage;
                } else {
                    task->lines[0] = 0x1D;
                    task->lines[1] = (task->unk50 == 0) << 4;
                    children[0]->unkAC(children[0], 2, task->lines);
                }
                if (task->damage != 0) {
                    s32 other = task->unk50 == 0;
                    s32 row = other * 0x60;
                    BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];

                    struck = (BattleFighter *)(row + (s32)slot);
                    struck->hp -= task->damage;
                    if (struck->hp <= 0) {
                        struck->hp = 0;
                        func_8009C054((task->unk50 == 0) << 4);
                        task->step = 1;
                    }
                }
                task->substate++;
            }
            break;
        case 2:
            if (children[0] == NULL) {
                if (D_800A317C.unk38[0x23]) {
                    children[0] = (Unk80097F8C *)func_80090F28(task->unk50);
                    task->nextSubstate(task);
                } else if (task->step != 0) {
                    task->state = 3;
                } else if (task->damage == 0) {
                    if (task->unk50 != 0 || D_800A31E8.unkD6 != 6) {
                        task->state = 3;
                    } else {
                        task->setSubstate(task, 6);
                    }
                } else {
                    children[0] = (Unk80097F8C *)func_80090F28(task->unk50);
                    task->nextSubstate(task);
                }
            }
            break;
        case 3:
            if (children[0] == NULL) {
                task->nextSubstate(task);
            }
            break;
        case 4:
            index = task->unk50 == 0;
            countered = (D_800A31E8.fighters[index] + D_800A31E8.active[index]);
            if (countered->flags & 8) {
                if (task->unk5C != 0 && D_800A3308.unkD4((u8)(0x10 - task->unk50), task->damage) != 0) {
                    task->lines[0] = 0x2B;
                    task->lines[1] = 0x10 - task->unk50;
                    task->lines[2] = D_800A31E8.active[index];
                    children[0] = func_80099400();
                    children[0]->unkAC(children[0], 7, task->lines);
                    countered->flags &= ~8;
                    {
                        s32 event = D_800A25F0.funcs.find(0xC, 0x10 - task->unk50, D_800A31E8.active[index]);

                        if (event >= 0) {
                            D_800A25F0.events[event].type = 0;
                        }
                    }
                    task->substate = 8;
                } else {
                    task->state = 3;
                }
            } else {
                children[0] = (Unk80097F8C *)func_8008EAA0(index << 4, task->damage, 0);
                task->substate++;
            }
            break;
        case 5:
            if (children[0] != NULL) {
                if (children[0]->state != 2) {
                    break;
                }
                func_800A8F60(task->unk50, task->damage);
            }
            task->state = 3;
            break;
        case 6:
            if (children[0] == NULL) {
                children[0] = (Unk80097F8C *)func_800908C0(1, 0);
                task->nextSubstate(task);
            }
            break;
        case 7:
            if (children[0] == NULL) {
                task->setState(task, 3);
            }
            break;
        case 8:
            if (children[0] == NULL) {
                children[0] = (Unk80097F8C *)func_8008EAA0((task->unk50 == 0) << 4, task->damage, 0);
                task->substate = 5;
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void func_8008C8B8(s32 arg0) {
    ((Unk8008C0BC *)createTask(func_8008C0BC, sizeof(Unk8008C0BC), sizeof(Task *)))->unk50 = arg0;
}
