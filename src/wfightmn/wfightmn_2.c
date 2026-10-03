#include "wfightmn.h"

/* The 18-byte entries of the executable's table at D_800427D6 */
typedef struct Unk800427D6 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5[2];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
} Unk800427D6;

extern Unk800427D6 D_800427D6[];

/* FIGHTSTG's */
extern u8 D_800A31F0[0xD4];
extern s32 (*D_800A3104)(s32 arg0, s32 arg1);
BattleTask *func_80087ACC(s32 arg0, s32 arg1, s32 damage);
BattleTask *func_8008C090();
BattleTask *func_8008C8B8(s32 arg0);
BattleTask *func_80086780(s32 digimon, s32 arg1, s32 arg2);
BattleTask *func_80090050(s32 arg0, s32 arg1);
void func_8009C054(u8 id);
void func_80092154(s32 arg0);
s32 func_800921B8();
void func_8009B5BC(s32 arg0);
void func_8009B634(s32 arg0);
void func_8009B7A4(s32 arg0, s32 member, s32 arg2);
BattleTask *func_80099400();
void func_8009BFD0(void);
void func_8009C1C0(void);
void func_8009C240(void);
BattleTask *func_80089F74(s32 digimon, s32 arg1);
BattleTask *func_80090264(Battle *battle);
BattleTask *func_800908C0(s32 arg0, s32 arg1);
BattleTask *func_80088380(Battle *battle);
void func_8009B5F8(s32 arg0);
extern s32 (*D_800A30F0)(void);
void func_8009C000(s32 partner);
void func_8009B678(s32 arg0);
BattleTask *func_8008E390(s32 arg0);
BattleCommands *func_80092124(void);
Unk800919EC *func_800919EC(s32 layer);
Task *func_80086128(s32 id, s32 fadeInTime);
BattleModels *func_800877D4(void);
Task *func_8008A838(s32 layer);
extern s16 D_800A32BE;
extern ActionResult D_800A317C;
#if VERSION_EU
Task *func_800A246C(void);
#endif

extern RECT D_800A9B58;
void func_800A59A0(BattleMenu *task, BattleMenuChildren *children);
void func_800A5538(s32 digimon);
void func_800A5878(void);
void func_800A61C8(void);
s32 func_800A9840(u8 id, s32 damage);
BattleTask *func_800A9040(u8 actor, s32 id);
void func_800A99F0(u8 side);
void func_800A9960(u8 side, s32 damage);
extern s32 D_800A9CC4[][2];

void WFIGHTMN_updateMenu();
extern void (*WFIGHTMN_states[])(BattleMenu *task, BattleMenuChildren *children);

void func_800A52C8(void) {
    Layer *layer;

    GFX.funcs.reset();
    GFX.funcs.allocPrimBuffers(0x19000);
    GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
    layer = GFX.funcs.createLayer(&D_800A9B58, 1, 0x1000);
    layer->setOffset(layer, 0xA0, 0x78);
    layer = GFX.funcs.createLayer(&D_800A9B58, 1, 0x1001);
    layer->setOffset(layer, 0xA0, 0x78);
    layer->allocCallbacks(layer, 100);
    layer = GFX.funcs.createLayer(&D_800A9B58, 8, 0x1002);
    layer->setOffset(layer, D_800A9B58.w / 2, D_800A9B58.h / 2);
    layer->allocCallbacks(layer, 40);
    layer = GFX.funcs.createLayer(&D_800A9B58, 1, 0x1003);
    layer->setOffset(layer, 0xA0, 0x78);
    layer->allocCallbacks(layer, 100);
    layer = GFX.funcs.createLayer(&D_800A9B58, 12, 0x1004);
    layer->setOffset(layer, 0xA0, 0x78);
    layer->allocCallbacks(layer, 100);
    layer = GFX.funcs.createLayer(&D_800A9B58, 1, 0x1005);
    layer->setOffset(layer, 0, 0);
    layer = GFX.funcs.createLayer(&D_800A9B58, 1, 0x1006);
    layer->setOffset(layer, 0, 0);
    layer->allocCallbacks(layer, 10);
}

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn_2", func_800A5538);

/* Checks the chance in D_80042728.unk3C, scaled by how far the first
   partner's level and the first enemy's level are under 32 */
s32 func_800A56D4(void) {
    s32 chance;
    s32 gap;
    s32 r;

    if (D_80042728.unk3C == 0) {
        return 0;
    }
    /* gap on its own line: the match depends on it, which loads the level
       before the enemy's */
    gap = 32 - GAME.partners[GAME.funcs.getPartyMember(0)].level;
    chance = D_80042728.unk3C * (gap - D_80042728.enemies[0].level) / 32;
    r = RANDOM.next() % 128;
    if (r == 0) {
        return 1;
    }
    return r < chance;
}

void WFIGHTMN_checkEquip(s32 member) {
    s32 partner = GAME.funcs.getPartyMember(member);
    s16 *equip;
    s32 i;

    if (partner >= 0) {
        equip = &((PartnerStats *)GAME.funcs.getPartnerStats(partner))->equip[4];
        for (i = 0; i < 2; i++) {
            if (equip[i] == WFIGHTMN_ITEM) {
                func_8009B7A4(0, member, 0);
                return;
            }
        }
    }
}

void WFIGHTMN_checkParty(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        WFIGHTMN_checkEquip(i);
    }
}

/* Marks in D_80042790 that the current partner fought, and with which of
   its slots' Digimon if it isn't in its own form */
void func_800A5878(void) {
    s16 slots[4];
    DigimonData *digimon;
    s32 partner;
    BattleUnit *unit;
    s32 i;

    D_80042790.partners[D_800A31E8.current[0]].fought = 1;
    partner = GAME.funcs.getPartyMember(D_800A31E8.current[0]);
    unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
    digimon = &DIGIMON_DATA[partner];
    if (digimon->id != unit->id && GAME.funcs.getPartnerSlots(partner, slots) > 0) {
        for (i = 0; i < 3; i++) {
            if (slots[i] == unit->id) {
                D_80042790.partners[D_800A31E8.current[0]].used[i] = 1;
                return;
            }
        }
    }
}

void func_800A59A0(BattleMenu *task, BattleMenuChildren *children) {
    s16 slots[4];
    s32 i;
    s32 member;
    s32 partner;

    i = 0;
    member = -1;
    partner = GAME.funcs.getPartyMember(children->commands->unk60);
    for (; i < 3; i++) {
        if (GAME.funcs.getPartyMember(i) == partner) {
            member = i;
            break;
        }
    }
    D_80042790.partners[member].fought = 1;
    if (GAME.funcs.getPartnerSlots(GAME.funcs.getPartyMember(member), slots) > 0) {
        for (i = 0; i < 3; i++) {
            if (slots[i] == children->commands->unk64) {
                D_80042790.partners[member].used[i] = 1;
                return;
            }
        }
    }
}

/* The battle menu's task: sets up the battle (its music, FIGHTSTG's tasks and
   the fighters' models), then runs the menu (func_800A8B08), playing sound
   0x60040000 once a partner has flag 4 and the battle's music again after */
void WFIGHTMN_updateMenu(BattleMenu *task, BattleMenuChildren *children) {
    s16 slots[4];
    s32 digimon;
    s32 partner;
    s32 chance;
    s32 mode;
    BattleStats *stats;
    BattleUnit *unit;
    BattleUnit *units;
    s32 found;
    s32 i;

    switch (task->state) {
    case 0:
    default:
        switch (task->substate) {
        case 0:
        default:
            func_800A52C8();
            task->nextSubstate(task);
        case 1:
            switch (task->step) {
            case 0:
            default:
                SOUND.loadBank((D_80042728.unk14 >> 18) & 0x7F);
                task->nextStep(task);
            case 1:
                if (SOUND_STATE.isLoading() == 0) {
                    SOUND_STATE.playSound(D_80042728.unk14);
                    task->nextSubstate(task);
                }
                break;
            }
            break;
        case 2:
            switch (task->step) {
            case 0:
            default:
                children->commands = func_80092124();
                children->unk8 = func_800919EC(0x1001);
                children->stage = func_80086128(D_80042728.unkC, 60);
                children->models = func_800877D4();
                children->lights = func_8008A838(0x1001);
                task->nextStep(task);
                break;
            case 1:
                mode = GAME_FUNCS.getPrevMode();
                if (mode == 0x22D && D_80042728.unk10 == 0x143) {
                    D_800A32BE = 1;
                } else if (mode == 0x23A && D_80042728.unk10 == 0xB) {
                    D_800A32BE = 2;
                } else if (mode == 0x272 && D_80042728.unk10 == 0x1E) {
                    D_800A32BE = 3;
                } else if (D_80042728.unk10 == 0x144) {
                    D_800A31E8.unkD6 = 4;
                    D_800A31E8.unkDB = 0;
                    D_800A31E8.unkDA = 0;
                    D_800A31E8.unkD8 = 0;
                } else {
                    D_800A32BE = 0;
                }
                partner = GAME.funcs.getPartyMember(0);
                if (func_800A56D4() != 0) {
                    digimon = DIGIMON_DATA[partner].id;
                    task->counter = 1;
                } else if (GAME.funcs.getPartnerSlots(partner, slots) > 0 && GAME.partners[partner].unk8 != 0) {
                    digimon = GAME.partners[partner].unk8;
                } else {
                    digimon = DIGIMON_DATA[partner].id;
                }
                children->models->add(children->models, 0, digimon, 1);
                children->models->face(children->models, 0);
                children->models->add(children->models, 0x10, D_80042728.enemies[0].fighter, 1);
                children->models->face(children->models, 0x10);
                func_800A5538(digimon);
                unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
                if (unit->maxHp / 4 >= unit->hp) {
                    children->models->setIdleMotion(children->models, 0, 1);
                }
#if VERSION_EU
                GFX.frameTime = 1;
                children->unk18 = func_800A246C();
#else
                children->unk8->unkF8(children->unk8, children->unk8->unk100(children->unk8));
#endif
                task->step++;
                break;
            case 2:
#if VERSION_EU
                GFX.frameTime = 1;
#endif
                children->loader = WFIGHTMN_createLoader();
                task->step++;
                break;
            case 3:
                if (children->loader == NULL) {
                    task->step++;
                }
                break;
            case 4:
                func_800A5878();
                task->step++;
                break;
            case 5:
                if (task->counter != 0) {
                    func_8009B5F8(0);
                    func_8009B5BC(D_800A3104(0, 0) / 2);
                    children->task = func_80099400();
                    task->args[0] = 7;
                    children->task->show(children->task, 1, task->args);
                    task->step++;
                    func_80092154(1);
                } else {
                    stats = D_800A3308.getStats(0, 1, D_800A31E8.current[0]);
                    chance = D_800A3308.getStats(0x10, 0, D_800A31E8.current[1])->unk8[1] * 8 / stats->unk8[1];
                    if (RANDOM.next() % 128 < chance) {
                        func_8009B5F8(0);
                        func_8009B5BC(D_800A3104(0, 0) / 2);
                        func_80092154(1);
                    } else {
                        func_8009B5BC(0);
                        func_8009B5F8(D_800A3104(0, 0) / 2);
                    }
                    task->nextState(task);
                }
                WFIGHTMN_checkParty();
                break;
            case 6:
                if (children->task == NULL) {
                    task->nextState(task);
                }
                break;
            }
            break;
        }
        break;
    case 1:
        func_800A8B08(task);
        units = D_800A31E8.units[0];
        if (task->unk70 == 0) {
            for (i = 0; i < 3; i++) {
                if (units[i].flags & 4) {
                    SOUND.playSound(0x60040000);
                    task->unk70 = 1;
                    break;
                }
            }
        } else {
            found = 0;
            for (i = 0; i < 3; i++) {
                if (units[i].flags & 4) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                SOUND.playSound(D_80042728.unk14);
                task->unk70 = 0;
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/* Undoes the current partner's unk1A and the actions that go with it */
void func_800A61C8(void) {
    s32 index = D_800A25F0.find(0x13, 0, D_800A31E8.current[0]);
    BattleUnit *unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
    s32 member = GAME_FUNCS.getPartyMember(D_800A31E8.current[0]);

    if (unit->unk1A != 0) {
        if (index >= 0) {
            D_800A25F0.entries[index].kind = 0;
        }
        D_80042728.unk58[member] = 0;
        unit->unk1A = 0;
        index = D_800A25F0.find(8, 0, D_800A31E8.current[0]);
        if (index >= 0) {
            D_800A25F0.entries[index].kind = 0;
        }
    }
}

void func_800A62B8(BattleMenu *task, BattleMenuChildren *children) {
    BattleUnit *unit;
    s32 index;

    switch (task->step) {
    case 0:
    default:
        index = D_800A25F0.find(8, 0, D_800A31E8.current[0]);
        if (index >= 0) {
            D_800A25F0.entries[index].kind = 0;
        }
        index = D_800A25F0.find(4, 0, D_800A31E8.current[0]);
        if (index >= 0) {
            children->task = func_80099400();
            task->args[0] = 0x42;
            task->args[1] = 0;
            children->task->show(children->task, 2, task->args);
            D_800A25F0.entries[index].kind = 0;
        }
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
            if ((unit->flags & 2) && D_800A3308.unkDC(0) != 0) {
                children->task = func_80099400();
                task->args[0] = 0x56;
                task->args[1] = 0;
                children->task->show(children->task, 2, task->args);
                func_8009B5BC(D_800A3104(0, 0));
                task->setSubstate(task, 2);
            } else if (unit->flags & 4) {
                task->setSubstate(task, 0x11);
            } else {
                func_80092154(2);
                task->step = 2;
            }
        }
        break;
    case 2:
        if (func_800921B8() == 0) {
            switch (children->commands->choice) {
            case 1:
                D_800A31E8.unkD4++;
                func_8009B678(0);
                children->task = func_80099400();
                task->args[0] = 0x41;
                task->args[1] = 0;
                children->task->show(children->task, 2, task->args);
                task->setSubstate(task, 2);
                func_800A99F0(0);
                break;
            case 0:
                children->task = func_8008C8B8(0);
                task->setSubstate(task, 2);
                break;
            case 4:
                children->task = func_80090050(0, children->commands->unk60);
                task->setSubstate(task, 2);
                break;
            case 2:
                task->setSubstate(task, 4);
                func_800A99F0(0);
                break;
            case 5:
                task->setSubstate(task, 5);
                func_800A99F0(0);
                break;
            case 6:
                task->setSubstate(task, 6);
                break;
            case 3:
                children->task = func_8008E390(children->commands->unk60);
                task->setSubstate(task, 2);
                break;
            default:
                task->substate = -1;
                break;
            }
            func_8009B5BC(D_800A3104(0, 0));
        }
        break;
    }
}

/* The state that changes the current partner's Digimon to the one picked
   (commands->unk64), then says so */
void func_800A6654(BattleMenu *task, BattleMenuChildren *children) {
    BattleUnit *unit;
    DigimonData *digimon;

    switch (task->step) {
    case 0:
    default:
        unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
        unit->id = children->commands->unk64;
        func_800A5878();
        func_800A61C8();
        children->task = func_80089F74(unit->id, 0);
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            /* a pointer sum, not units[0][...]: the match depends on it,
               which adds the base first */
            digimon = ON_PARTNER_ENTRY_ADDED((D_800A31E8.units[0] + D_800A31E8.current[0])->id);
            children->task = func_80099400();
            task->args[0] = 0;
            task->args[1] = digimon->nameId;
            children->task->show(children->task, 0xC, task->args);
            task->setSubstate(task, 2);
        }
        break;
    }
}

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn_2", func_800A6778);

/* The state after the battle's last action: goes on to state 5 while an
   enemy is left, or ends the battle */
void func_800A69D0(BattleMenu *task, BattleMenuChildren *children) {
    s32 i;
    BattleUnit *unit;

    switch (task->step) {
    case 0:
    default:
        children->task = func_80090050(0, children->commands->unk68);
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            for (i = 0, unit = D_800A31E8.units[1]; i < 3; i++, unit++) {
                if (unit->id != 0 && unit->hp != 0) {
                    task->setSubstate(task, 5);
                    task->step = 1;
                    return;
                }
            }
            func_800A59A0(task, children);
            task->setSubstate(task, 0);
        }
        break;
    }
}

/* After a won battle, picks the enemy whose item the player may get; saves the
   partners' HP and MP, fades out and requests the next mode */
void WFIGHTMN_endBattle(BattleMenu *task, BattleMenuChildren *children) {
    Battle *battle;
    BattleUnit *units;
    BattleUnit *unit;
    EnemyInfo *info;
    BattleEnd *end;
    Layer *layer;
    s32 count;
    s32 pick;
    s32 i;
    s32 partner;
    s32 member;
    s32 mode;

    switch (task->step) {
    case 0:
    default:
#if VERSION_EU
        if (children->unk18 != NULL && children->unk18->state != TASK_DONE) {
            break;
        }
#endif
        if (D_800A30E4 != 0) {
            count = 0;
            battle = &D_800A31E8;
            units = battle->units[1];
            D_80042790.battle = D_80042728.unk10;
            D_80042790.member = battle->current[0];
            for (i = 0; i < 3; i++) {
                if (units[i].id != 0 && units[i].unk18 != 0) {
                    count++;
                }
            }
            pick = RANDOM.next() % count;
            count = 0;
            for (i = 0; i < 3; i++) {
                if (units[i].id != 0 && units[i].unk18 != 0) {
                    if (pick == count) {
                        break;
                    }
                    count++;
                }
            }
            /* an address sum with the offset first: the match depends on it, which
               puts the offset first in the addu */
            unit = (BattleUnit *)(count * sizeof(BattleUnit) + (s32)units);
            info = D_800A2584(unit->id);
            if (unit->unk18 > 0 && info->itemChance + 1 > RANDOM.next() % 1024) {
                D_80042790.item = unit->unk18;
            } else {
                D_80042790.item = 0;
            }
            if (D_80042728.unk4C == 1) {
                D_80042790.item = D_80042728.unk50;
            }
        }
        for (member = 0; member < 3; member++) {
            partner = GAME.funcs.getPartyMember(member);
            if (partner >= 0) {
                if ((D_800A31E8.units[0] + member)->hp <= 0) {
                    GAME.partners[partner].hp = 1;
                    D_80042790.partners[member].fought = 0;
                    D_80042790.partners[member].used[0] = 0;
                    D_80042790.partners[member].used[1] = 0;
                    D_80042790.partners[member].used[2] = 0;
                } else {
                    GAME.partners[partner].hp = (D_800A31E8.units[0] + member)->hp;
                }
                GAME.partners[partner].mp = (D_800A31E8.units[0] + member)->mp;
            }
        }
        end = func_8008A22C();
        children->task = (BattleTask *)end;
        end->start(end, 0, 10);
        task->step++;
        break;
    case 1:
        if (children->task->state == TASK_DONE) {
            layer = GFX_FUNCS.getLayer(0x1000);
            layer->setBgColor(layer, 0, 0, 0);
#if VERSION_EU
            if (children->unk18 != NULL) {
                children->unk18->setState(children->unk18, TASK_KILL);
            }
#endif
            task->step++;
        }
        break;
    case 2:
        func_800A61C8();
        switch (D_800A30E4) {
        case 0:
        default:
            GAME.funcs.requestMode(GAME.fieldMode, 0);
            break;
        case 1:
#if VERSION_EU
            mode = 0xE0B;
#else
            mode = 0xE0A;
#endif
            if (D_800A31E8.unkD6 != 6) {
                mode = 0x1400;
            }
            GAME_FUNCS.requestMode(mode, 0);
            break;
        case 2:
            GAME_FUNCS.requestMode(0xE00, 0);
            break;
        }
        break;
    }
}

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn_2", func_800A6E6C);

/* Removes the current action's kind 6 action, unless the partner it is for
   has WFIGHTMN_ITEM equipped */
void func_800A6FA0(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action = &D_800A25F0.entries[D_800A25F0.current];
    s32 index = D_800A25F0.find(6, (u8)action->actor, action->unit);
    BattleAction *found;
    PartnerStats *stats;

    if (index >= 0) {
        found = &D_800A25F0.entries[index];
        children->task = func_80099400();
        task->args[0] = 0x5A;
        task->args[1] = action->actor;
        task->args[2] = action->unit;
        children->task->show(children->task, 7, task->args);
        if (found->actor == 0) {
            stats = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(found->unit));
            if (stats->equip[4] == WFIGHTMN_ITEM || stats->equip[5] == WFIGHTMN_ITEM) {
                found->kind = 6;
                found->unkC = 0;
            } else {
                found->kind = 0;
            }
        } else {
            found->kind = 0;
        }
    }
    task->setSubstate(task, 2);
}

void func_800A70E8(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action = &D_800A25F0.entries[D_800A25F0.current];
    s32 side = action->actor >> 4;
    BattleUnit *unit = &D_800A31E8.units[side][action->unit];

    switch (task->step) {
    case 0:
    default:
        action->unk2 = 1000;
        task->counter = D_800A3308.getHeal(action->actor, action->unit, action->unkC);
        if (unit->hp < unit->maxHp) {
            if (action->unit == D_800A31E8.current[side]) {
                children->task = func_800A9040(action->actor, 0xBD);
                func_800A9840(action->actor, -task->counter);
            }
            task->step++;
        } else {
            task->setSubstate(task, 0);
        }
        break;
    case 1:
        if (children->task == NULL) {
            children->task = func_80099400();
            task->args[0] = action->actor;
            task->args[1] = action->unit;
            task->args[2] = task->counter;
            children->task->show(children->task, 0xA, task->args);
            task->step++;
        }
        break;
    case 2:
        if (children->task == NULL) {
            unit->hp += task->counter;
            if (unit->hp > unit->maxHp) {
                unit->hp = unit->maxHp;
            }
            task->setSubstate(task, 0);
        }
        break;
    }
}

void func_800A72E0(BattleMenu *task, BattleMenuChildren *children) {
    children->task = func_80099400();
    task->args[0] = 0x6A;
    children->task->show(children->task, 1, task->args);
    D_800A31E8.unkD0 = 0;
    D_800A31E8.unkD2 = 0;
    task->setSubstate(task, 2);
}

/* Carries out the current action's damage (D_800A3308.getDamage) on its unit */
void func_800A7358(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action;
    BattleUnit *unit;
    BattleUnit *hit;
    s32 side;
    s32 damage;

    switch (task->step) {
    case 0:
    default:
        action = &D_800A25F0.entries[D_800A25F0.current];
        side = action->actor >> 4;
        task->args[0] = action->actor;
        task->args[1] = action->unit;
        damage = D_800A3308.getDamage(&action->actor);
        task->args[2] = damage;
        if (action->unit == D_800A31E8.current[side]) {
            unit = &D_800A31E8.units[side][action->unit];
            if (action->actor == 0) {
                children->task = func_80087ACC(unit->hp - damage <= 0 ? 2 : 1, 1, damage);
            } else {
                children->task = func_8008C090();
                children->task->unk50 = 0;
                children->task->unk54 = 0xE;
                children->task->unk6C = 0x13;
                children->task->unk70 = 0x1A;
                children->task->unk68 = -1;
                if (unit->hp - task->args[2] <= 0) {
                    children->task->hits[3] = 2;
                } else {
                    children->task->hits[3] = 1;
                }
            }
            func_800A9840(action->actor, task->args[2]);
            task->step++;
        } else {
            task->setSubstate(task, 0);
        }
        action->unk2 = 1000;
        break;
    case 1:
        if (children->task == NULL) {
            hit = &D_800A31E8.units[task->args[0] >> 4][task->args[1]];
            hit->hp -= task->args[2];
            if (hit->hp <= 0) {
                hit->hp = 0;
                func_8009C054(task->args[0]);
            }
            children->task = func_80099400();
            children->task->show(children->task, 0xF, task->args);
            task->step++;
        }
        break;
    case 2:
        if (children->task == NULL) {
            task->setSubstate(task, 0);
        }
        break;
    }
}

/* States 13-15: clear the current action's unit's flag 2, 4 or 8 */
void func_800A75F8(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action = &D_800A25F0.entries[D_800A25F0.current];
    BattleUnit *unit;

    switch (task->step) {
    case 0:
    default:
        task->args[0] = task->substate + 0x1C;
        task->args[1] = action->actor;
        task->args[2] = action->unit;
        children->task = func_80099400();
        children->task->show(children->task, 7, task->args);
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            unit = &D_800A31E8.units[action->actor != 0][action->unit];
            switch (task->substate) {
            case 13:
            default:
                unit->flags &= ~2;
                break;
            case 14:
                unit->flags &= ~4;
                break;
            case 15:
                unit->flags &= ~8;
                break;
            }
            task->setSubstate(task, 0);
        }
        break;
    }
}

/* Clears the current action's unit's unk10[unkC] */
void func_800A7754(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action = &D_800A25F0.entries[D_800A25F0.current];
    BattleUnit *unit;

    switch (task->step) {
    case 0:
    default:
        children->task = func_80099400();
        task->args[0] = action->unkC + 0x5B;
        task->args[1] = action->actor;
        task->args[2] = action->unit;
        children->task->show(children->task, 7, task->args);
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            unit = &D_800A31E8.units[action->actor >> 4][action->unit];
            unit->unk10[action->unkC] = 0;
            task->setSubstate(task, 0);
        }
        break;
    }
}

void func_800A7878(BattleMenu *task, BattleMenuChildren *children) {
    switch (task->step) {
    case 0:
    default:
        func_80092154(3);
        task->step++;
        break;
    case 1:
        if (func_800921B8() == 0) {
            if (children->commands->choice == 0) {
                children->task = func_8008C8B8(0);
                task->setSubstate(task, 2);
            } else {
                task->setSubstate(task, 0);
            }
            func_8009B5BC(D_800A3104(0, 0));
        }
        break;
    }
}

/* Clears the current action's unit's flag 0x10 << unkC */
void func_800A7950(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action = &D_800A25F0.entries[D_800A25F0.current];
    BattleUnit *unit;

    switch (task->step) {
    case 0:
    default:
        children->task = func_80099400();
        task->args[0] = action->unkC + 0x57;
        task->args[1] = action->actor;
        task->args[2] = action->unit;
        children->task->show(children->task, 7, task->args);
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            unit = &D_800A31E8.units[action->actor >> 4][action->unit];
            unit->flags &= ~(1 << (action->unkC + 4));
            task->setSubstate(task, 0);
        }
        break;
    }
}

/* Digivolves the current partner for the battle, to the Digimon its level
   reaches (unk50), and heals it when the change ends */
void func_800A7A7C(BattleMenu *task, BattleMenuChildren *children) {
    BattleModels *models;
    BattleUnit *unit;
    DigimonData *digimon;
    s32 partner;
    s32 level;
    s32 tier;
#if VERSION_EU
    s32 index;
#endif

    switch (task->step) {
    case 0:
    default:
        children->task = func_80099400();
        task->args[0] = 0x61;
        task->args[1] = 0;
        children->task->show(children->task, 2, task->args);
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            partner = GAME.funcs.getPartyMember(D_800A31E8.current[0]);
            level = GAME.funcs.getPartnerStats(partner)->level;
            if (level < 4) {
                tier = 0;
            } else if (level < 19) {
                tier = 1;
            } else if (level < 39) {
                tier = 2;
            } else if (level < 70) {
                tier = 3;
            } else {
                tier = 4;
            }
            unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
            digimon = ON_PARTNER_ENTRY_ADDED(DIGIMON_DATA[partner].id);
            unit->prevId = unit->id;
            unit->id = DIGIMON_DATA[digimon->unk50[tier] - 1].id;
            unit->unk1A = 1;
            func_8009C000(partner);
            children->task = func_80089F74(unit->id, 1);
            task->step++;
        }
        break;
    case 2:
        models = TASK_FUNCS.find(0x14, -1, -1);
        if (models->get(models, 0)->motion == 13) {
            BattleUnit *current = &D_800A31E8.units[0][D_800A31E8.current[0]];
            current->hp = current->maxHp;
#if VERSION_EU
            if (current->flags & 4) {
                index = D_800A25F0.find(0xB, 0, D_800A31E8.current[0]);
                if (index >= 0) {
                    D_800A25F0.entries[index].kind = 0;
                    D_800A25F0.entries[index].unk2 = 0;
                }
                current->flags &= ~4;
                task->unk70 = 0;
            }
#endif
            task->setSubstate(task, 2);
        }
        break;
    }
}

/* Turns the current partner back into the Digimon it was (prevId) */
void func_800A7CB8(BattleMenu *task, BattleMenuChildren *children) {
    BattleUnit *unit;

    switch (task->step) {
    case 0:
    default:
        unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
        unit->id = unit->prevId;
        func_800A61C8();
        children->task = func_80086780(unit->id, 0, func_800A9840(0, 0));
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            children->task = func_80099400();
            task->args[0] = 0x62;
            task->args[1] = 0;
            children->task->show(children->task, 2, task->args);
            task->setSubstate(task, 2);
        }
        break;
    }
}

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn_2", func_800A7DB0);

void func_800A83D8(BattleMenu *task, BattleMenuChildren *children) {
    BattleAction *action = &D_800A25F0.entries[D_800A25F0.current];
    BattleUnit *unit;

    unit = &D_800A31E8.units[0][action->unit];
    unit->unk1B = 0;
    children->task = func_80099400();
    task->args[0] = 0x59;
    task->args[1] = action->actor;
    task->args[2] = action->unit;
    children->task->show(children->task, 7, task->args);
    task->setSubstate(task, 2);
}

void func_800A8494(BattleMenu *task, BattleMenuChildren *children) {
    Battle *battle;
    BattleActions *actions;
    s32 index;
    BattleUnit *unit;
    BattleUnit *units;

    switch (task->step) {
    case 0:
    default:
        battle = &D_800A31E8;
        units = battle->units[0];
        index = GAME_FUNCS.getPartyMember(battle->current[0]);
        unit = units + battle->current[0];
        unit->id = DIGIMON_DATA[index].id;
        unit->unkE = 0;
        func_800A61C8();
        actions = &D_800A25F0;
        index = actions->find(8, 0, battle->current[0]);
        if (index >= 0) {
            actions->entries[index].kind = 0;
        }
        children->task = func_80086780(unit->id, 0, func_800A9840(0, 0));
        task->step++;
        break;
    case 1:
        if (children->task == NULL) {
            children->task = func_80099400();
            task->args[0] = 0x47;
            task->args[1] = 0;
            children->task->show(children->task, 2, task->args);
            task->setSubstate(task, 2);
        }
        break;
    }
}

void func_800A8610(BattleMenu *task, BattleMenuChildren *children) {
    switch (task->step) {
    case 0:
    default:
        if (children->task != NULL) {
            if (GFX_FUNCS.getTime() - task->args[1] > task->args[2]) {
                children->task->close(children->task);
                task->step++;
            }
            break;
        }
        task->setSubstate(task, 0);
        break;
    case 1:
        if (children->task != NULL) {
            children->task->state = TASK_KILL;
        }
        task->setSubstate(task, 0);
        break;
    }
}

INCLUDE_ASM("wfightmn/nonmatchings/wfightmn_2", func_800A86E0);

void func_800A8A64(BattleMenu *task) {
    BattleRequest request;
    s32 index = D_800A25F0.findKind(3);

    if (index >= 0) {
        D_800A25F0.entries[index].kind = 0;
    }
    request.kind = 3;
    request.unk4 = 1;
    request.unk8 = -1;
    D_800A25F0.add(&request);
    D_800A31E8.units[1][0].unk10[3] = 0;
    D_800A31E8.units[1][0].unk10[1] = 0;
    task->setSubstate(task, 2);
}

/* The battle menu's main state: waits for FIGHTSTG's turn (D_800A30F0),
   then runs the state of the command it gets (WFIGHTMN_states) */
void func_800A8B08(BattleMenu *task) {
    BattleMenuChildren *children = task->children;

    switch (task->substate) {
    default:
        if (task->substate >= 3 && task->substate < 27) {
            WFIGHTMN_states[task->substate](task, children);
        } else {
#if VERSION_EU
            task->setSubstate(task, 1);
#endif
            task->step = D_800A25F0.unkB00();
            if (task->step == 0) {
                func_8009B5BC(0);
                func_8009B5F8(D_800A25F0.unkB14(0, 0) / 2);
                task->setSubstate(task, 0);
            }
#if VERSION_US
            else {
                task->setSubstate(task, 1);
            }
#endif
        }
        break;
    case 0:
#if VERSION_EU
        task->setSubstate(task, 1);
        task->step = D_800A30F0();
#else
        task->step = D_800A30F0();
        if (task->step != 0) {
            task->substate = 1;
        }
#endif
        break;
    case 1:
        switch (task->step) {
        default:
            task->setSubstate(task, 3);
            break;
        case 1:
            task->setSubstate(task, 7);
            break;
        case 3:
            if (D_800A31E8.unkD6 == 5) {
                children->task = func_80090264(&D_800A31E8);
                task->setSubstate(task, 2);
            } else if (D_800A31E8.unkD6 == 6) {
                children->task = func_800908C0(0, 0);
                task->setSubstate(task, 2);
            } else {
                (D_800A31E8.units[1] + D_800A31E8.current[1])->unk4++;
                children->task = func_80088380(&D_800A31E8);
                task->setSubstate(task, 2);
            }
            break;
        case 4:
            task->setSubstate(task, 8);
            break;
        case 5:
            task->setSubstate(task, 9);
            break;
        case 6:
            task->setSubstate(task, 0xA);
            break;
        case 7:
            task->setSubstate(task, 0xB);
            break;
        case 9:
            task->setSubstate(task, 0xC);
            break;
        case 10:
            task->setSubstate(task, 0xD);
            break;
        case 11:
            task->setSubstate(task, 0xE);
            break;
        case 12:
            task->setSubstate(task, 0xF);
            break;
        case 13:
        case 14:
        case 15:
            task->setSubstate(task, 0x10);
            break;
        case 16:
        case 17:
            task->setSubstate(task, 0x12);
            break;
        case 18:
            task->setSubstate(task, 0x13);
            break;
        case 19:
            task->setSubstate(task, 0x14);
            break;
        case 20:
            task->setSubstate(task, 0x15);
            break;
        case 21:
            task->setSubstate(task, 0x16);
            break;
        case 22:
            task->setSubstate(task, 0x17);
            break;
        case 23:
            task->setSubstate(task, 0x19);
            break;
        case 24:
            task->setSubstate(task, 0x1A);
            break;
        }
        break;
    case 2:
        if (children->task == NULL) {
            task->setSubstate(task, 0);
        }
        break;
    }
}

Task *WFIGHTMN_start(void) {
    Task *task = createTaskWithId(WFIGHTMN_updateMenu, 0x74, 0x20, 0xC);

    HEAP.zero(D_800A31F0, sizeof(D_800A31F0));
    HEAP.zero(&D_80042790, sizeof(D_80042790));
    return task;
}

void func_800A8EBC(u8 side, s32 id) {
    Unk800427D6 *info = &D_800427D6[id];
    s32 flag;
    u8 kind;

    if (side == 0 && D_800A31E8.unkD6 == 4) {
        flag = 0;
        if (info->unk10 != 5 && info->unk10 != 12) {
            kind = info->unkA;
            if (!(kind <= 1 || (kind >= 9 && kind <= 10) || kind == 12)) {
                flag = 1;
            }
            if (info->unk7 >= 2) {
                flag = 1;
            }
            if (flag) {
                D_800A31E8.unkD8 = id;
            }
        }
    }
}

/* Adds what damage gives to the current partner's gauge
   (D_80042728.unk58), up to 1000 */
void func_800A8F60(u8 side, s32 damage) {
    BattleUnit *unit = &D_800A31E8.units[0][D_800A31E8.current[0]];
    s32 member = GAME_FUNCS.getPartyMember(D_800A31E8.current[0]);

    if (side != 0 && damage != 0 && unit->hp != 0 && unit->unk1A == 0) {
        D_80042728.unk58[member] += D_800A3308.unkE4(damage);
        if (D_80042728.unk58[member] >= 1000) {
            D_80042728.unk58[member] = 1000;
            func_8009BFD0();
        }
    }
}

/* Starts the effect of actor's move id (FIGHTSTG's func_8008C090): its kind
   and motions from D_800427D6, which hits land from D_800A317C, then sets
   the fighters' idle motions for the damage it does */
BattleTask *func_800A9040(u8 actor, s32 id) {
    Unk800427D6 *info;
    s32 side;
    BattleStats *own;
    BattleStats *other;
    BattleTask *task;
    BattleUnit *units;
    s32 damage;
    s32 i;
    s32 j;

    side = actor != 0;
    info = &D_800427D6[id];
    own = D_800A3308.getStats(actor, 1, D_800A31E8.current[side]);
    other = D_800A3308.getStats((u8)(0x10 - actor), 0, D_800A31E8.current[1 - side]);
    task = func_8008C090();
    task->unk50 = actor;
    if (actor == 0) {
        if (info->unk10 == 5) {
            if (own->unk30[7] != 0) {
                task->unk54 = 8;
                task->unk6C = info->unkE;
                task->unk70 = info->unkF;
            } else {
                for (i = 2; i < 13; i++) {
                    if (D_800A317C.unk38[i] != 0) {
                        task->unk54 = 6;
                        {
                            s32 (*table)[2] = D_800A9CC4; /* match depends on the pointer */

                            j = i - 2;
                            task->unk6C = table[j][0];
                            task->unk70 = table[j][1];
                        }
                        break;
                    }
                }
                if (task->unk54 == 0) {
                    for (i = 0; i < 3; i++) {
                        if (own->unk28[i] >= 2 && own->unk28[i] == other->unk25) {
                            task->unk54 = 6;
                            task->unk6C = info->unkE;
                            task->unk70 = info->unkF;
                            break;
                        }
                    }
                    if (task->unk54 == 0) {
                        task->unk54 = info->unk10;
                        task->unk6C = info->unkE;
                        task->unk70 = info->unkF;
                    }
                }
            }
        } else {
            if (info->unkA < 2 && info->unk4 == 2 && info->unk10 == 6 && own->unk30[7] != 0) {
                task->unk54 = 8;
            } else {
                task->unk54 = info->unk10;
            }
            task->unk6C = info->unkE;
            task->unk70 = info->unkF;
            if (info->unk7 >= 2 || (info->unk9 >= 2 && info->unk9 == other->unk25)) {
                task->unk68 = info->unkD;
            } else {
                task->unk68 = -1;
            }
        }
        if (task->unk68 <= 0) {
            if (own->unk2B >= 2) {
                s32 n;
                s32 m;

                if (info->unk7 >= 2) {
                    n = info->unk7 - 2;
                } else {
                    n = own->unk2B - 2;
                }
                m = n * 3 + 0x21;
                if (own->unk2C >= 0x40) {
                    task->unk68 = m + 1;
                } else {
                    task->unk68 = m;
                }
            } else if (info->unk9 < 2) {
                for (i = 0; i < 3; i++) {
                    if (own->unk28[i] == 2 && other->unk25 == 2) {
                        task->unk68 = 0x35;
                        break;
                    }
                    if (own->unk28[i] == 10 && other->unk25 == 10) {
                        task->unk68 = 0x36;
                        break;
                    }
                }
            }
        }
    } else {
        task->unk54 = info->unk10;
        task->unk6C = info->unkE;
        task->unk70 = info->unkF;
        if (info->unk7 >= 2 || (info->unk9 >= 2 && info->unk9 == other->unk25)) {
            task->unk68 = info->unkD;
        } else {
            task->unk68 = -1;
        }
    }
    units = D_800A31E8.units[1 - side];
    if (id == 0x1B5) {
        damage = 9999;
        task->hits[3] = 1;
    } else if (info->unkA == 0x1F) {
        if (D_800A317C.unk34 != 0) {
            damage = D_800A317C.unk60[0] + D_800A317C.unk60[1];
            if (units[D_800A31E8.current[1 - side]].hp - damage <= 0) {
                if (D_800A317C.unk34 == 1) {
                    task->hits[0] = 3;
                } else {
                    task->hits[0] = 0;
                }
                task->hits[3] = 2;
            } else {
                for (i = 0; i < 2; i++) {
                    if (D_800A317C.hits[i] != 0) {
                        task->hits[i * 3] = 0;
                    } else {
                        task->hits[i * 3] = 3;
                    }
                }
            }
        } else {
            damage = 0;
            task->hits[0] = 3;
            task->hits[3] = 3;
        }
    } else if (D_800A317C.unk38[9] != 0) {
        damage = D_800A317C.unk34 * D_800A317C.damage;
        if (units[D_800A31E8.current[1 - side]].hp - damage <= 0) {
            for (i = 0; i < D_800A317C.unk34 - 1; i++) {
                if (D_800A317C.hits[i] != 0) {
                    task->hits[i] = 0;
                } else {
                    task->hits[i] = 3;
                }
            }
            task->hits[3] = 2;
        } else {
            for (i = 0; i < D_800A317C.unk36 - 1; i++) {
                if (D_800A317C.hits[i] != 0) {
                    task->hits[i] = 0;
                } else {
                    task->hits[i] = 3;
                }
            }
            if (D_800A317C.hits[i] != 0) {
                task->hits[3] = 1;
            } else {
                task->hits[3] = 3;
            }
        }
    } else if (D_800A317C.unk38[6] != 0) {
        task->hits[3] = 2;
        damage = 9999;
    } else if (info->unkA == 0x23 && D_800A317C.unk38[0x23] != 0) {
        task->hits[3] = 1;
        damage = D_800A317C.damage;
    } else if ((u32)(info->unk4 - 2) < 2) {
        if (D_800A317C.hits[0] != 0) {
            if (units[D_800A31E8.current[1 - side]].hp - D_800A317C.damage <= 0) {
                task->hits[3] = 2;
            } else {
                task->hits[3] = 1;
            }
            damage = D_800A317C.damage;
        } else {
            task->hits[3] = 3;
            damage = 0;
        }
    } else {
        switch (id) {
        case 0x64:
        case 0x177:
            damage = -9999;
            break;
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBB:
        case 0xBC:
        case 0x190:
            damage = -D_800A3308.unk90[1](actor, id);
            break;
        default:
            damage = 0;
            break;
        }
    }
    if ((u32)(info->unk4 - 2) < 2) {
        func_800A8EBC(actor, id);
        func_800A9960(actor, damage);
        func_800A9840(0x10 - actor, damage);
        if (D_800A317C.unk38[8] != 0) {
            func_800A9840(actor, -D_800A317C.unk2C);
        }
    } else {
        func_800A99F0(actor);
        func_800A9840(actor, damage);
    }
    return task;
}

/* Sets the idle motion of side id >> 4's fighter: 1 (weak) if damage
   leaves it with a quarter of its HP or less; returns whether it did */
s32 func_800A9840(u8 id, s32 damage) {
    u32 side = id >> 4;
    BattleMenuChildren *children = ((Task *)TASK_FUNCS.find(0xC, -1, -1))->children;
    BattleUnit *unit;

    if (id == 0x10 && D_800A31E8.unkD6 == 6) {
        children->models->setIdleMotion(children->models, 0x10, D_800A31E8.unkDB);
        return 1;
    }
    unit = &D_800A31E8.units[side][D_800A31E8.current[side]];
    if (unit->hp - damage <= unit->maxHp / 4) {
        children->models->setIdleMotion(children->models, id, 1);
        return 1;
    }
    children->models->setIdleMotion(children->models, id, 0);
    return 0;
}

void func_800A9960(u8 side, s32 damage) {
    if (D_800A31E8.unkD6 == 6 && side == 0 && D_800A31E8.unkDB == 0 && damage != 0) {
        if (++D_800A31E8.unkDA >= 3) {
            func_8009C1C0();
            func_800A9840(0x10, damage);
        }
    }
}

void func_800A99F0(u8 side) {
    if (D_800A31E8.unkD6 == 6 && side == 0 && D_800A31E8.unkDB != 0) {
        func_8009C240();
    }
}

/* In battles of kind 1 and 2 (Battle.unkD6), cuts the damage that side's
   hits do so that the other side keeps at least an eleventh of its HP; in kind 3
   side 0 does none */
s32 func_800A9A40(u8 side, s32 damage, s32 hits) {
    s32 other = side == 0;
    BattleUnit *unit = &D_800A31E8.units[other][D_800A31E8.current[other]];
    s32 limit;
    s32 total;

    switch (D_800A31E8.unkD6) {
    case 1:
    case 2:
        if (side == 0) {
            /* the s16 cast and total: the match depends on them, which
               narrow the limit and multiply before the branches */
            limit = (s16)(unit->maxHp / 11);
            if (hits != 0) {
                total = damage * hits;
                if (unit->hp > limit) {
                    if (unit->hp - total < limit) {
                        damage = (unit->hp - limit) / hits;
                    }
                } else {
                    damage = 0;
                }
            } else if (unit->hp > limit) {
                if (unit->hp - damage < limit) {
                    damage = unit->hp - limit;
                }
            } else {
                damage = 0;
            }
        }
        break;
    case 3:
        if (side == 0) {
            damage = 0;
        }
        break;
    }
    return damage;
}

void func_800A62B8();
void func_800A6654();
void func_800A6778();
void func_800A69D0();
void WFIGHTMN_endBattle();
void func_800A6E6C();
void func_800A6FA0();
void func_800A70E8();
void func_800A72E0();
void func_800A7358();
void func_800A75F8();
void func_800A7754();
void func_800A7878();
void func_800A7950();
void func_800A7A7C();
void func_800A7CB8();
void func_800A7DB0();
void func_800A83D8();
void func_800A8494();
void func_800A8610();
void func_800A86E0();
void func_800A8A64();

RECT D_800A9B58 = {0, 0, 320, 240};
#if VERSION_US
s32 D_800A9B60[][3] = {
    { 2, 19, 26 },
    { 3, 20, 26 },
    { 4, 21, 27 },
    { 5, 22, 50 },
    { 6, 26, 50 },
    { 8, 28, 39 },
    { -1, 37, 49 },
    { 27, 39, 49 },
    { 28, 41, 49 },
    { -1, 0, 0 },
};
#elif VERSION_EU
s32 D_800A9B60[][3] = {
    { 2, 19, 26 },
    { 3, 20, 26 },
    { 4, 21, 27 },
    { 5, 22, 50 },
    { 6, 26, 50 },
    { 8, 28, 39 },
    { -1, 37, 49 },
};
#endif
s32 D_800A9BD8[][4] = {
    { 2, 5, 64, 34 },
    { 3, 9, 45, 37 },
    { 4, 11, 44, 40 },
    { 5, 14, 29, 43 },
    { 6, 16, 44, 46 },
    { 7, 65, 64, 49 },
    { 8, 7, 64, 52 },
    { -1, 0, 0, 0 },
};
void (*WFIGHTMN_states[])(BattleMenu *task, BattleMenuChildren *children) = {
    NULL, NULL, NULL, func_800A62B8,
    func_800A6654, func_800A6778, func_800A69D0, WFIGHTMN_endBattle,
    func_800A6E6C, func_800A6FA0, func_800A70E8, func_800A72E0,
    func_800A7358, func_800A75F8, func_800A75F8, func_800A75F8,
    func_800A7754, func_800A7878, func_800A7950, func_800A7A7C,
    func_800A7CB8, func_800A7DB0, func_800A83D8, func_800A8494,
    func_800A8610, func_800A86E0, func_800A8A64,
};
/* func_800A9040's unk6C and unk70 by the first of D_800A317C.unk38[2..12]
   that is set */
s32 D_800A9CC4[][2] = {
    {19, 26}, {20, 26}, {21, 27}, {22, 50}, {26, 50}, {0, 0},
    {28, 39}, {0, 0}, {46, 30}, {0, 59}, {31, 58},
};
