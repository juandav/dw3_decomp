/* The sixth object of FIGHTSTG.PRO (see fightstg.c): its rodata starts at
   0x8008267C (USA), 4 bytes past a multiple of 8. */

#include "fightstg.h"
#include "gte.h"

/* WFIGHTMN's */
void func_800A8F60(u8 side, s32 damage);
s32 func_800A9840(u8 id, s32 damage);
void func_800A9960(u8 side, s32 damage);
void func_800A99F0(u8 side);
s32 func_800A9A40(u8 side, s32 damage, s32 hits);

BattleScript *func_8008C090(void);

/* fightstg.c's u16 rows */
extern ItemScript D_800A210C[];

/* An item's script (func_8008CFFC): step 0 sets it up and deals the damage,
   1 plays item 0x55's second part when the enemy is still standing, 2 waits.
   The match depends on item 0x55's damage being 20 percent, on the row
   pointer of item 0x5A, on the stage being written out in each case and on
   the table being walked by index. */
s32 func_8008C8F0(Unk8008CFFC *task, BattleScript **children) {
    BattleFighter *fighter;
    BattleFighter *enemy;
    BattleFighter *row;
    BattleStats *stats;
    Unk800427D6 *tech;
    s32 atk;
    s32 def;
    s32 min;
    s32 i;

    switch (task->step) {
    case 0:
    default:
        children[0] = func_8008C090();
        children[0]->unk50 = 0;
        switch (task->unk70) {
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
            children[0]->index = 0xF;
            children[0]->stage = (task->unk70 - 0x4D) * 3 + 0x22;
            children[0]->unk6C = 2;
            children[0]->sound = 0x39;
            break;
        case 0x54:
            task->unk74 = RANDOM.next() % 7 + 2;
            children[0]->index = 0xF;
            children[0]->stage = (task->unk74 - 2) * 3 + 0x22;
            children[0]->unk6C = 2;
            children[0]->sound = 0x39;
            break;
        case 0x56:
            children[0]->index = 0x11;
            children[0]->stage = -1;
            children[0]->unk6C = 0x15;
            children[0]->sound = 0x1B;
            break;
        case 0x57:
            children[0]->index = 0x11;
            children[0]->stage = -1;
            children[0]->unk6C = 0x27;
            children[0]->sound = 0x31;
            break;
        case 0x59:
            children[0]->index = 0x11;
            children[0]->stage = -1;
            children[0]->unk6C = 0x29;
            children[0]->sound = 0x31;
            break;
        case 0x58:
            fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
            stats = D_800A3308.computeStats(0x10, 0, D_800A31E8.active[1]);
            if (stats->stats[0] > stats->stats[1]) {
                if (D_80042728.unk3E[8] == 0) {
                    task->unk7C = 1;
                    atk = stats->stats[0];
                    def = stats->stats[1];
                    if (fighter->boosts[0] != 0) {
                        stats->stats[0] -= fighter->boosts[0];
                    }
                    min = -(stats->stats[0] / 2);
                    fighter->boosts[0] -= atk - def;
                    if (fighter->boosts[0] < min) {
                        fighter->boosts[0] = min;
                    }
                }
            } else if (stats->stats[0] < stats->stats[1]) {
                if (D_80042728.unk3E[9] == 0) {
                    task->unk7C = 2;
                    atk = stats->stats[0];
                    def = stats->stats[1];
                    if (fighter->boosts[1] != 0) {
                        stats->stats[1] -= fighter->boosts[1];
                    }
                    min = -(stats->stats[1] / 2);
#if VERSION_EU
                    fighter->boosts[1] -= def - atk;
#else
                    fighter->boosts[1] -= atk - def; /* raises it */
#endif
                    if (fighter->boosts[1] < min) {
                        fighter->boosts[1] = min;
                    }
                }
            }
            children[0]->index = 0x11;
            children[0]->stage = -1;
            if (task->unk7C == 1) {
                children[0]->unk6C = 0x25;
                children[0]->sound = 0x31;
            } else if (task->unk7C == 2) {
                children[0]->unk6C = 0x27;
                children[0]->sound = 0x31;
            } else {
                children[0]->unk6C = 0x2E;
                children[0]->sound = 0x1E;
            }
            break;
        case 0x55:
            children[0]->index = 0xE;
            children[0]->stage = -1;
            children[0]->unk6C = 0x1C;
            children[0]->sound = 0x27;
            if (D_80042728.unk3E[5] == 0) {
                enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                task->unk78 = enemy->maxHp * 20 / 100;
                if (enemy->hp - task->unk78 <= 0) {
                    children[0]->hits[3] = 2;
                    task->counter = 1;
                } else {
                    children[0]->hits[3] = 1;
                    func_800A9840(0x10, task->unk78);
                    func_800A9840(0, -task->unk78);
                }
            } else {
                children[0]->hits[3] = 3;
            }
            break;
        case 0x5A:
            children[0]->index = 0xE;
            tech = &D_800427D6[0x89];
            children[0]->stage = tech->unkD;
            children[0]->unk6C = tech->unkE;
            children[0]->sound = tech->unkF;
            task->unk78 = func_800A9A40(0, D_800A3308.unk88(0, 0x89), 0);
            row = D_800A31E8.fighters[1];
            if (task->unk78 > 0) {
                if (row[D_800A31E8.active[1]].hp - task->unk78 <= 0) {
                    children[0]->hits[3] = 2;
                } else {
                    children[0]->hits[3] = 1;
                    func_800A9840(0x10, task->unk78);
                }
            } else {
                children[0]->hits[3] = 3;
            }
            break;
        default:
            children[0]->index = 0xA;
            children[0]->stage = -1;
            for (i = 0; D_800A210C[i].item != -1; i++) {
                if (D_800A210C[i].item == task->unk70) {
                    children[0]->unk6C = D_800A210C[i].unk6C;
                    children[0]->sound = D_800A210C[i].sound;
                    break;
                }
            }
            if (task->unk70 >= 0x2B && task->unk70 < 0x2F) {
                func_800A9840(0, -*(u16 *)&GET_ITEM[0](task->unk70)->data[2]);
            } else if (task->unk70 == 0x47) {
                func_800A9840(0, -((D_800A31E8.fighters[0] + D_800A31E8.active[0])->maxHp >> 1));
            }
            break;
        }
        task->step++;
        if (D_800A31E8.unkD6 == 6) {
            if (task->unk70 == 0x5A) {
                func_800A9960(0, task->unk78);
            } else {
                func_800A99F0(0);
            }
        }
        break;
    case 1:
        if (children[0] == NULL) {
            if (task->unk70 != 0x55 || task->counter != 0 || D_80042728.unk3E[5] != 0) {
                return 1;
            }
            children[0] = func_8008C090();
            children[0]->unk50 = 0;
            children[0]->index = 0xA;
            children[0]->unk6C = 0x21;
            children[0]->sound = 0x1F;
            task->step++;
        }
        break;
    case 2:
        if (children[0] == NULL) {
            return 1;
        }
        break;
    }
    return 0;
}

/* What items 0x42-0x45 cure (fightstg.c's s32 rows) */
typedef struct StatusCure {
    /* 0x0 */ s16 message;
    /* 0x2 */ s16 flag; /* in BattleFighter.flags */
    /* 0x4 */ s32 item; /* D_800A25F0.funcs.useItem's */
} StatusCure;
extern StatusCure D_800A20EC[];
extern StatusCure D_800A20F4[];
extern StatusCure D_800A20FC[];
extern StatusCure D_800A2104[];

void func_800A57A8(s32 fighter);
void func_8009B840(s32 time);
void func_8009BAC0(u8 side, s32 arg1, u8 arg2);
void func_8009C0B0(void);
Unk80097F8C *func_800908C0(s32 arg0, s32 arg1);
Unk80097F8C *func_80099400(void);
void func_8009C054(u8 side);

/* An item used in battle (func_8008E390): its message, func_8008C8F0's
   script, then substate 1 does what the item does and 2 takes it from the
   bag (item 0x55 attacks again in battle kind 6). The match depends on each
   case's variables being its own, on item 0x47's halves being declared in
   its `if`, on its MP test being written `maxMp <= mp + halfMp`, on item
   0x57's cap being read after the boosts change, on the pointer sum of item
   0x4B and on the cases that say the item does nothing ending on their own
   (item 0x2B's, 0x57's and 0x59's). */
void func_8008CFFC(Unk8008CFFC *task, Unk80097F8C **children) {
    s8 unused[0x90]; /* unused, but it is in the original stack frame */

    switch (task->state) {
    case TASK_INIT:
    default:
        switch (task->substate) {
        case 0:
        default:
            children[0] = func_80099400();
            task->lines[0] = 0;
            task->lines[1] = task->unk70;
            children[0]->unkAC(children[0], 0xE, task->lines);
            task->substate++;
            break;
        case 1:
            if (children[0] == NULL && func_8008C8F0(task, (BattleScript **)children)) {
                task->nextState(task);
            }
            break;
        }
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            if (children[0] == NULL) {
                task->substate++;
            }
            break;
        case 1:
            switch (task->unk70) {
            case 0x2B ... 0x41:
            default: {
                BattleFighter *fighter;
                u8 *data;
                s32 heal;

                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                data = GET_ITEM[0](task->unk70)->data;
                if (fighter->maxHp == fighter->hp) {
                    children[0] = func_80099400();
                    task->lines[0] = 0x2F;
                    children[0]->unkAC(children[0], 1, task->lines);
                    task->nextSubstate(task);
                    break;
                }
                if (fighter->hp + *(u16 *)&data[2] <= fighter->maxHp) {
                    heal = *(u16 *)&data[2];
                    fighter->hp += heal;
                } else {
                    heal = fighter->maxHp - fighter->hp;
                    fighter->hp = fighter->maxHp;
                }
                children[0] = func_80099400();
                task->lines[0] = 0;
                task->lines[1] = heal;
                children[0]->unkAC(children[0], 8, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x42 ... 0x45: {
                BattleFighter *fighter;
                StatusCure *cure;

                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                switch (task->unk70) {
                case 0x42:
                default:
                    cure = D_800A20EC;
                    break;
                case 0x43:
                    cure = D_800A20F4;
                    break;
                case 0x44:
                    cure = D_800A20FC;
                    break;
                case 0x45:
                    cure = D_800A2104;
                    break;
                }
                children[0] = func_80099400();
                if (fighter->flags & cure->flag) {
                    fighter->flags &= ~cure->flag;
                    D_800A25F0.funcs.useItem(0, D_800A31E8.active[0], cure->item);
                    task->lines[0] = cure->message;
                    task->lines[1] = 0;
                    children[0]->unkAC(children[0], 2, task->lines);
                } else {
                    task->lines[0] = 0x2F;
                    children[0]->unkAC(children[0], 1, task->lines);
                }
                task->nextSubstate(task);
                break;
            }
            case 0x46: {
                s32 i;

                switch (task->step) {
                case 0:
                    children[0] = func_80099400();
                    task->lines[0] = 0;
                    task->lines[1] = 5;
                    children[0]->unkAC(children[0], 9, task->lines);
                    task->nextStep(task);
                    break;
                case 1:
                    if (children[0] == NULL) {
                        for (i = 0; i < 3; i++) {
                            if (D_800A31E8.fighters[0][i].hp == 0) {
                                D_800A31E8.fighters[0][i].hp = D_800A31E8.fighters[0][i].maxHp;
                                func_800A57A8(i);
                            }
                        }
                        task->nextStep(task);
                    }
                    break;
                case 2:
                    if (children[0] == NULL) {
                        GAME.items[task->unk70]--;
                        task->state = TASK_KILL;
                    }
                    break;
                }
                break;
            }
            case 0x47: {
                BattleFighter *fighter;

                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                children[0] = func_80099400();
                if (fighter->hp != fighter->maxHp || fighter->mp != fighter->maxMp) {
                    s32 half;
                    s32 halfMp;

                    half = fighter->maxHp / 2;
                    halfMp = fighter->maxMp / 2;
                    if (fighter->hp + half >= fighter->maxHp) {
                        fighter->hp = fighter->maxHp;
                    } else {
                        fighter->hp += half;
                    }
                    if (fighter->maxMp <= fighter->mp + halfMp) {
                        fighter->mp = fighter->maxMp;
                    } else {
                        fighter->mp += halfMp;
                    }
                    task->lines[0] = 0x3B;
                    task->lines[1] = 0;
                    children[0]->unkAC(children[0], 2, task->lines);
                } else {
                    task->lines[0] = 0x2F;
                    children[0]->unkAC(children[0], 1, task->lines);
                }
                task->nextSubstate(task);
                break;
            }
            case 0x48: {
                BattleFighter *fighter;
                BattleStats *stats;
                u8 *data;
                s32 max;

                data = GET_ITEM[0](task->unk70)->data;
                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                stats = D_800A3308.computeStats(0, 1, D_800A31E8.active[0]);
                if (fighter->boosts[2] != 0) {
                    stats->stats[4] -= fighter->boosts[2];
                }
                max = stats->stats[4];
                fighter->boosts[2] += max * *(u16 *)&data[2] / 128;
                if (fighter->boosts[2] > max) {
                    fighter->boosts[2] = max;
                }
                func_8009BD20(0, D_800A31E8.active[0], 2, 0);
                children[0] = func_80099400();
                task->lines[0] = 0x32;
                task->lines[1] = 0;
                task->lines[2] = D_800A31E8.active[0];
                children[0]->unkAC(children[0], 7, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x49: {
                BattleFighter *fighter;
                BattleStats *stats;
                u8 *data;
                s32 max;
                s32 min;

                data = GET_ITEM[0](task->unk70)->data;
                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                stats = D_800A3308.computeStats(0, 1, D_800A31E8.active[0]);
                if (fighter->boosts[0] != 0) {
                    stats->stats[0] -= fighter->boosts[0];
                }
                if (fighter->boosts[1] != 0) {
                    stats->stats[1] -= fighter->boosts[1];
                }
                max = stats->stats[0];
                fighter->boosts[0] += max * *(u16 *)&data[2] / 128;
                if (fighter->boosts[0] > max) {
                    fighter->boosts[0] = max;
                }
                min = -(stats->stats[1] / 2);
                fighter->boosts[1] -= stats->stats[1] * *(u16 *)&data[2] / 512;
                if (fighter->boosts[1] < min) {
                    fighter->boosts[1] = min;
                }
                func_8009BD20(0, D_800A31E8.active[0], 0, 0);
                func_8009BD20(0, D_800A31E8.active[0], 1, 0);
                children[0] = func_80099400();
                task->lines[0] = 0x3C;
                task->lines[1] = 0;
                children[0]->unkAC(children[0], 2, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x4A: {
                BattleFighter *fighter;
                BattleStats *stats;
                u8 *data;
                s32 max;
                s32 min;

                data = GET_ITEM[0](task->unk70)->data;
                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                stats = D_800A3308.computeStats(0, 1, D_800A31E8.active[0]);
                if (fighter->boosts[0] != 0) {
                    stats->stats[0] -= fighter->boosts[0];
                }
                if (fighter->boosts[1] != 0) {
                    stats->stats[1] -= fighter->boosts[1];
                }
                max = stats->stats[1];
                fighter->boosts[1] += max * *(u16 *)&data[2] / 128;
                if (fighter->boosts[1] > max) {
                    fighter->boosts[1] = max;
                }
                min = -(stats->stats[0] / 2);
                fighter->boosts[0] -= stats->stats[0] * *(u16 *)&data[2] / 512;
                if (fighter->boosts[0] < min) {
                    fighter->boosts[0] = min;
                }
                func_8009BD20(0, D_800A31E8.active[0], 0, 0);
                func_8009BD20(0, D_800A31E8.active[0], 1, 0);
                children[0] = func_80099400();
                task->lines[0] = 0x3D;
                task->lines[1] = 0;
                children[0]->unkAC(children[0], 2, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x4B: {
                (D_800A31E8.fighters[0] + D_800A31E8.active[0])->unk1B = 1;
    #if VERSION_US
                func_8009C0B0();
    #endif
                children[0] = func_80099400();
                task->lines[0] = 0x3E;
                task->lines[1] = 0;
                children[0]->unkAC(children[0], 2, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x4C: {
                u8 *data;
                s32 i;

                data = GET_ITEM[0](task->unk70)->data;
                i = GAME_FUNCS.getPartyMember(D_800A31E8.active[0]);
                D_80042728.unk58[i] += *(u16 *)&data[2];
                if (D_80042728.unk58[i] >= 999) {
                    D_80042728.unk58[i] = 999;
                }
                children[0] = func_80099400();
                task->lines[0] = 0x3F;
                task->lines[1] = 0;
                children[0]->unkAC(children[0], 2, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x4D ... 0x53: {
                func_8009B840(D_800A25F0.funcs.getDelay(0, 8));
                D_800A31E8.unkD0 = task->unk70 - 0x4B;
                D_800A31E8.unkD2 = 0x40;
                children[0] = func_80099400();
                task->lines[0] = task->unk70 + 0x16;
                children[0]->unkAC(children[0], 1, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x54: {
                func_8009B840(D_800A25F0.funcs.getDelay(0, 8));
                D_800A31E8.unkD0 = task->unk74;
                D_800A31E8.unkD2 = 0x7F;
                children[0] = func_80099400();
                task->lines[0] = task->unk74 + 0x61;
                children[0]->unkAC(children[0], 1, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x55: {
                BattleFighter *fighter;

                if (D_80042728.unk3E[5] == 0) {
                    children[0] = func_80099400();
                    task->lines[0] = 0x10;
                    task->lines[1] = task->unk78;
                    fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                    if (fighter->hp - task->unk78 <= 0) {
                        children[0]->unkAC(children[0], 4, task->lines);
                        fighter->hp = 0;
                        func_8009C054(0x10);
                    } else {
                        children[0]->unkAC(children[0], 0x14, task->lines);
                        fighter->hp -= task->unk78;
                        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                        fighter->hp += task->unk78;
                        if (fighter->hp > fighter->maxHp) {
                            fighter->hp = fighter->maxHp;
                        }
                    }
                } else {
                    children[0] = func_80099400();
                    task->lines[0] = 0x2F;
                    children[0]->unkAC(children[0], 1, task->lines);
                }
                task->nextSubstate(task);
                break;
            }
            case 0x56: {
                BattleFighter *fighter;
                BattleFighter *enemy;
                u8 *data;

                data = GET_ITEM[0](task->unk70)->data;
                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                switch (task->step) {
                case 0:
                default:
                    if ((RANDOM.next() & 1) && D_80042728.unk3E[2] == 0) {
                        func_8009BAC0(0x10, 0, data[2]);
                        children[0] = func_80099400();
                        task->lines[0] = 0x20;
                        task->lines[1] = 0x10;
                        children[0]->unkAC(children[0], 2, task->lines);
                        if ((RANDOM.next() & 3) == 0) {
                            task->nextStep(task);
                        } else {
                            task->nextSubstate(task);
                        }
                        enemy->flags |= 4;
                    } else {
                        children[0] = func_80099400();
                        task->lines[0] = 0x2F;
                        children[0]->unkAC(children[0], 1, task->lines);
                        task->nextSubstate(task);
                    }
                    break;
                case 1:
                    if (children[0] == NULL) {
                        fighter->flags |= 4;
                        func_8009BAC0(0, 0, data[2]);
                        children[0] = func_80099400();
                        task->lines[0] = 0x20;
                        task->lines[1] = 0;
                        children[0]->unkAC(children[0], 2, task->lines);
                        task->nextSubstate(task);
                    }
                    break;
                }
                break;
            }
            case 0x57: {
                BattleFighter *enemy;
                BattleStats *stats;
                s32 max;
                s32 atk;
                s32 def;

                if (D_80042728.unk3E[9] == 0) {
                    enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                    stats = D_800A3308.computeStats(0x10, 0, D_800A31E8.active[1]);
                    atk = stats->stats[0];
                    def = stats->stats[1];
                    if (enemy->boosts[0] != 0) {
                        stats->stats[0] -= enemy->boosts[0];
                    }
                    if (enemy->boosts[1] != 0) {
                        stats->stats[1] -= enemy->boosts[1];
                    }
                    enemy->boosts[0] += atk * 3 / 10;
                    enemy->boosts[1] -= def / 2;
                    max = stats->stats[0];
                    if (enemy->boosts[0] > max) {
                        enemy->boosts[0] = max;
                    }
                    if (enemy->boosts[1] < -stats->stats[1] / 2) {
                        enemy->boosts[1] = -stats->stats[1] / 2;
                    }
                    func_8009BD20(0x10, D_800A31E8.active[1], 0, 0);
                    func_8009BD20(0x10, D_800A31E8.active[1], 1, 0);
                    children[0] = func_80099400();
                    task->lines[0] = 0x40;
                    task->lines[1] = 0x10;
                    children[0]->unkAC(children[0], 2, task->lines);
                    task->nextSubstate(task);
                    break;
                }
                children[0] = func_80099400();
                task->lines[0] = 0x2F;
                children[0]->unkAC(children[0], 1, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x58: {
                switch (task->unk7C) {
                case 1:
                    func_8009BD20(0x10, D_800A31E8.active[1], 0, 0);
                    children[0] = func_80099400();
                    task->lines[0] = 0x33;
                    task->lines[1] = 0x10;
                    task->lines[2] = D_800A31E8.active[1];
                    children[0]->unkAC(children[0], 2, task->lines);
                    break;
                case 2:
                    func_8009BD20(0x10, D_800A31E8.active[1], 1, 0);
                    children[0] = func_80099400();
                    task->lines[0] = 0x34;
                    task->lines[1] = 0x10;
                    task->lines[2] = D_800A31E8.active[1];
                    children[0]->unkAC(children[0], 2, task->lines);
                    break;
                default:
                    children[0] = func_80099400();
                    task->lines[0] = 0x2F;
                    children[0]->unkAC(children[0], 1, task->lines);
                    break;
                }
                task->nextSubstate(task);
                break;
            }
            case 0x59: {
                BattleFighter *enemy;
                BattleStats *stats;
                u8 *data;
                s32 min;

                if (D_80042728.unk3E[10] == 0) {
                    data = GET_ITEM[0](task->unk70)->data;
                    enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                    stats = D_800A3308.computeStats(0x10, 0, D_800A31E8.active[1]);
                    if (enemy->boosts[2] != 0) {
                        stats->stats[4] -= enemy->boosts[2];
                    }
                    min = -(stats->stats[4] / 2);
                    enemy->boosts[2] -= stats->stats[4] * *(u16 *)&data[2] / 128;
                    if (enemy->boosts[2] < min) {
                        enemy->boosts[2] = min;
                    }
                    func_8009BD20(0x10, D_800A31E8.active[1], 2, 0);
                    children[0] = func_80099400();
                    task->lines[0] = 0x35;
                    task->lines[1] = 0x10;
                    task->lines[2] = D_800A31E8.active[1];
                    children[0]->unkAC(children[0], 2, task->lines);
                    task->nextSubstate(task);
                    break;
                }
                children[0] = func_80099400();
                task->lines[0] = 0x2F;
                children[0]->unkAC(children[0], 1, task->lines);
                task->nextSubstate(task);
                break;
            }
            case 0x5A: {
                BattleFighter *enemy;

                if (task->unk78 > 0) {
                    children[0] = func_80099400();
                    task->lines[0] = 0x10;
                    task->lines[1] = task->unk78;
                    children[0]->unkAC(children[0], 4, task->lines);
                    enemy = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                    if (enemy->hp - task->unk78 <= 0) {
                        enemy->hp = 0;
                        func_8009C054(0x10);
                    } else {
                        enemy->hp -= task->unk78;
                    }
                } else {
                    children[0] = func_80099400();
                    task->lines[0] = 0x1D;
                    task->lines[1] = 0x10;
                    children[0]->unkAC(children[0], 2, task->lines);
                }
                task->nextSubstate(task);
                break;
            }
            }
            break;
        case 2:
            if (children[0] == NULL) {
                GAME.items[task->unk70]--;
                if (task->unk70 == 0x55 && D_800A31E8.unkD6 == 6) {
                    children[0] = func_800908C0(1, 0);
                    task->nextSubstate(task);
                } else {
                    task->state = TASK_KILL;
                }
            }
            break;
        case 3:
            if (children[0] == NULL) {
                task->setState(task, TASK_KILL);
            }
            break;
        }
        break;
    case 2:
    case TASK_KILL:
        break;
    }
}


void func_8008E390(s32 arg0) {
    ((Unk8008CFFC *)createTask(func_8008CFFC, sizeof(Unk8008CFFC), sizeof(Task *)))->unk70 = arg0;
}

/* fightstg_3.c's */
s32 func_800883AC(u8 condition, s16 arg);
s32 func_800888C8(u8 kind);

/* A counterattack (func_8008EAA0): the player's from an event of type 8 or
   the partner's first technique, the enemy's from its table entry; substate
   0 plays the technique, 1 shows the damage and takes the HP, 2 hands
   unk74 to func_800A8F60. The match depends on substate 0's technique and
   side being declared in its `if`, on the event index and the stats being
   variables of their own, on the stage being written element * 3 + 0x21 and
   one more, on the enemy's fighter being found as a pointer sum and on one
   row variable for both of substate 0's rows. */
void func_8008E3C8(Unk8008E3C8 *task, BattleScript **children) {
    BattleFighter *fighter;
    BattleFighter *row;
    BattleTableEntry *entry;
    s32 other;
    s32 element;

    switch (task->state) {
    case TASK_INIT:
    default:
        if (task->unk74 == 0) {
            task->state = TASK_DONE;
            break;
        }
        other = task->unk70 != 0;
        fighter = &D_800A31E8.fighters[other][D_800A31E8.active[other]];
        if ((fighter->flags & 2) && D_800A3308.unkDC(task->unk70) != 0) {
            task->state = TASK_DONE;
            break;
        }
        if (task->unk70 == 0) {
            s32 index = D_800A25F0.funcs.find(8, 0, D_800A31E8.active[0]);

            if (index >= 0) {
                task->tech = D_800A25F0.events[index].args[2];
                task->substate = 0;
                D_800A25F0.events[index].type = 0;
#if VERSION_US
            } else if (D_800A3308.computeStats(0, 1, D_800A31E8.active[0])->unk30[9] != 0) {
#elif VERSION_EU
            } else if (D_800A3308.computeStats(0, 1, D_800A31E8.active[0])->unk30[9] != 0
                       && D_800A3308.unkEU(0, task->unk74) != 0) {
#endif
                task->tech = ON_PARTNER_ENTRY_ADDED(fighter->id)->skills[0];
                task->substate = 1;
            } else {
                task->state = TASK_DONE;
                break;
            }
        } else {
            entry = D_800A2584(fighter->id);
            if (entry->counter.condition == 0) {
                task->state = TASK_DONE;
                break;
            }
            if (func_800883AC(entry->counter.condition, entry->counter.conditionArg) == 0) {
                task->state = TASK_DONE;
                break;
            }
            task->tech = func_800888C8(entry->counter.target);
            if (task->tech == 1) {
                task->tech = D_800A2584((D_800A31E8.fighters[1] + D_800A31E8.active[1])->id)->unk8[0];
                task->substate = 1;
            }
        }
        ((Unk80097F8C **)children)[0] = func_80099400();
        task->lines[0] = task->unk70;
        task->lines[1] = task->tech;
        ((Unk80097F8C **)children)[0]->unkAC(children[0], task->substate + 5, task->lines);
        task->hit = D_800A3308.unk9C(task->unk70, task->tech);
        if (task->hit != 0) {
            task->damage = D_800A3308.unk90(task->unk70, task->tech, task->unk74);
            if (D_800A31E8.unkD6 != 0) {
                task->damage = func_800A9A40(task->unk70, task->damage, 0);
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            if (children[0] == NULL) {
                Unk800427D6 *tech = &D_800427D6[task->tech];
                s32 other = task->unk70 != 0;
                children[0] = func_8008C090();
                children[0]->unk50 = task->unk70;
                if (task->unk70 == 0 && tech->unk10 == 5) {
                    children[0]->index = 6;
                } else {
                    children[0]->index = tech->unk10;
                }
                if (tech->unkF != 0) {
                    children[0]->sound = tech->unkF;
                }
                {
                    BattleStats *stats = D_800A3308.computeStats(task->unk70, 1, D_800A31E8.active[other]);

                    if (tech->unk7 >= 2 || stats->unk2B >= 2) {
                        if (tech->unk7 >= 2) {
                            element = tech->unk7 - 2;
                        } else {
                            element = stats->unk2B - 2;
                        }
                        element = element * 3 + 0x21;
                        if (stats->unk2C >= 0x40) {
                            children[0]->stage = element + 1;
                        } else {
                            children[0]->stage = element;
                        }
                    } else {
                        children[0]->stage = -1;
                    }
                }
                if (tech->unkE != 0) {
                    children[0]->unk6C = tech->unkE;
                } else if (tech->unk10 == 5) {
                    children[0]->unk6C = 0x2E;
                    children[0]->sound = 0x1E;
                }
                row = D_800A31E8.fighters[1 - other];
                if (task->hit != 0) {
                    if (row[D_800A31E8.active[1 - other]].hp - task->damage <= 0) {
                        children[0]->hits[3] = 2;
                    } else {
                        children[0]->hits[3] = 1;
                        func_800A9960(task->unk70, task->damage);
                        func_800A9840(0x10 - task->unk70, task->damage);
                    }
                } else {
                    children[0]->hits[3] = 3;
                }
                row = D_800A31E8.fighters[0];
                if (task->unk70 != 0) {
                    row = D_800A31E8.fighters[1];
                }
                row[D_800A31E8.active[task->unk70 != 0]].unkE = 0;
                task->substate++;
            }
            break;
        case 1:
            if (children[0] == NULL) {
                ((Unk80097F8C **)children)[0] = func_80099400();
                if (task->hit != 0) {
                    task->lines[0] = (task->unk70 == 0) << 4;
                    task->lines[1] = task->damage;
                    ((Unk80097F8C **)children)[0]->unkAC(children[0], 4, task->lines);
                } else {
                    task->lines[0] = 0x1D;
                    task->lines[1] = (task->unk70 == 0) << 4;
                    ((Unk80097F8C **)children)[0]->unkAC(children[0], 2, task->lines);
                }
                if (task->damage != 0) {
                    s32 index = task->unk70 == 0;
                    BattleFighter *fighter = &D_800A31E8.fighters[index][D_800A31E8.active[index]];
                    fighter->hp -= task->damage;
                    if (fighter->hp <= 0) {
                        fighter->hp = 0;
                        if (task->unk84 == 0) {
                            func_8009C054(index << 4);
                        }
                    }
                }
                task->substate++;
            }
            break;
        case 2:
            if (children[0] == NULL) {
                func_800A8F60(task->unk70, task->unk74);
                task->state = TASK_KILL;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Unk8008E3C8 *func_8008EAA0(s32 arg0, s32 arg1, s32 arg2) {
    Unk8008E3C8 *task = createTask(func_8008E3C8, sizeof(Unk8008E3C8), 4);

    task->unk70 = arg0;
    task->unk74 = arg1;
    task->unk84 = arg2;
    return task;
}

#if VERSION_EU
/* WFIGHTMN's WFIGHTMN_checkEquip */
void func_800A57A8(s32 fighter);

/* The six event types func_8008F5D4 clears */
extern s32 FIGHTSTG_clearIds[];

/* Revives one of the player's fighters at full HP, clearing its status
   events, and passes tech's unkC to D_800A3308.unkE0 */
void func_8008F5D4(s32 tech, s32 fighter) {
    BattleFighter *fighters = D_800A31E8.fighters[0];
    Unk800427D6 *entry = &D_800427D6[tech];
    s32 index;
    s32 i;

    if (fighters[fighter].id == 0) {
        return;
    }
    for (i = 0; i < 6; i++) {
        index = D_800A25F0.funcs.find(FIGHTSTG_clearIds[i], 0, fighter);
        if (index >= 0) {
            D_800A25F0.events[index].type = 0;
        }
    }
    if (fighters[fighter].hp == 0) {
        func_800A57A8(fighter);
    }
    fighters[fighter].flags = 0;
    fighters[fighter].hp = fighters[fighter].maxHp;
    D_800A3308.unkE0(0, fighter, 1, entry->unkC);
    func_8009BD20(0, fighter, 1, tech);
}
#endif

/* fightstg.c's data */
extern u8 D_800A21D4[];
extern s32 D_800A21D8[];
extern s32 D_800A21E8[];
Unk80090908 *func_80090F28(s32 arg0);
void func_8009BF84(s32 arg0);
void func_8009B6E8(u8 side);
void func_8009B7A4(u8 side, s32 fighter, s32 arg2);
void func_8009BE1C(s32 tech);
void func_8009C148(void);

/* A side's technique or item (func_80090050): state 0 shows its message,
   substate 1 does what it does by its kind (2 and 3 deal damage, 4 is an
   item's cure, revival or healing, 5 a boost, a drain or a heal of the
   enemy, 6 an attack timed by the fighter's third stat), then the counter
   when the other side's fighter has flag 8 (substate 4) and the motion of
   the damage (func_8008EAA0). The match depends on the other side's
   fighter being found as its row's offset added as an int to its slot (as
   in func_8008C0BC), on each case's variables being its own, on substate
   1's cases advancing substate themselves (case 5 once, after its switch)
   and on the heal tests being written hp + unk5C > maxHp. */
void func_8008EAF8(Unk8008EAF8 *task, Unk80097F8C **children) {
    Unk800427D6 *tech;

    switch (task->state) {
    case TASK_INIT:
    default: {
        Unk800427D6 *tech = &D_800427D6[task->unk54];

        if (tech->unk4 == 2 || tech->unk4 == 3) {
            D_800A317C.unk68(task->unk50, task->unk54);
        } else {
            HEAP.zero(&D_800A317C, 0x68);
        }
        children[0] = func_80099400();
        if (tech->unk10 == 0xC) {
            task->lines[0] = 0x3A;
            task->lines[1] = task->unk50;
            children[0]->unkAC(children[0], 2, task->lines);
        } else {
            task->lines[0] = task->unk50;
            task->lines[1] = task->unk54;
            children[0]->unkAC(children[0], 3, task->lines);
        }
        {
            s32 other = 1 - (task->unk50 >> 4);
            s32 row = other * 0x60;
            BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];
            BattleFighter *fighter = (BattleFighter *)(row + (s32)slot);

            if (fighter->flags & 8) {
                task->unk60 = 1;
            }
        }
        task->nextState(task);
        break;
    }
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            if (children[0] == NULL) {
                if (D_800A317C.unk38[10] == 0) {
                    children[0] = (Unk80097F8C *)func_800A9040(task->unk50, task->unk54);
                    {
                        BattleFighter *fighters = D_800A31E8.fighters[0];

                        if (task->unk50 != 0) {
                            fighters = D_800A31E8.fighters[1];
                        }
                        fighters[D_800A31E8.active[task->unk50 != 0]].unkE = 0;
                    }
                } else {
                    func_800A99F0(task->unk50);
                }
                task->substate++;
            }
            break;
        case 1:
            if (children[0] != NULL) {
                break;
            }
            tech = &D_800427D6[task->unk54];
            switch (tech->unk4) {
            default:
                return;
            case 2:
            case 3: {
                s32 other;

                children[0] = func_80099400();
                other = task->unk50 == 0;
                if (D_800A317C.unk38[10]) {
                    func_8009BF84(task->unk54);
                    task->state = 3;
                    return;
                }
                if (D_800A317C.unk38[9]) {
                    if (D_800427E8[task->unk54 - 1].unk5[5] == 0x1F) {
                        task->damage = D_800A317C.unk60[0] + D_800A317C.unk60[1];
                        task->lines[0] = other << 4;
                        task->lines[1] = task->damage;
                        children[0]->unkAC(children[0], 4, task->lines);
                    } else {
#if VERSION_US
                        task->damage = D_800A317C.damage * D_800A317C.unk34;
#endif
                        task->lines[0] = other << 4;
                        task->lines[1] = D_800A317C.damage;
                        task->lines[2] = D_800A317C.unk34;
                        children[0]->unkAC(children[0], 0x10, task->lines);
#if VERSION_EU
                        task->damage = D_800A317C.damage * D_800A317C.unk34;
                        if (task->damage >= 10000) {
                            task->damage = 9999;
                        }
#endif
                    }
                } else if (D_800A317C.unk38[6]) {
                    s32 row = other * 0x60;
                    BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];

                    ((BattleFighter *)(row + (s32)slot))->hp = 0;
                    func_8009C054(other << 4);
                    children[0]->state = 3;
                } else if (D_800A317C.hits[0]) {
                    task->lines[0] = other << 4;
                    task->lines[1] = D_800A317C.damage;
                    children[0]->unkAC(children[0], 4, task->lines);
                    task->damage = D_800A317C.damage;
                } else {
                    task->lines[0] = 0x1D;
                    task->lines[1] = other << 4;
                    children[0]->unkAC(children[0], 2, task->lines);
                }
                if (task->damage != 0) {
                    s32 row = other * 0x60;
                    BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];
                    BattleFighter *fighter = (BattleFighter *)(row + (s32)slot);

                    fighter->hp -= task->damage;
                    if (fighter->hp <= 0) {
                        fighter->hp = 0;
                        func_8009C054(other << 4);
                        task->step = 1;
                    }
                }
                task->substate++;
                return;
            }
            case 4:
                task->lines[0] = task->unk50;
                switch (task->unk54) {
                case 0xBD:
                    func_8009B6E8(task->unk50);
                    func_8009B7A4(task->unk50, D_800A31E8.active[task->unk50 != 0], task->unk54);
                    children[0] = func_80099400();
                    task->lines[0] = 0x27;
                    task->lines[1] = task->unk50;
                    children[0]->unkAC(children[0], 2, task->lines);
                    task->nextSubstate(task);
                    break;
                case 0xBE:
                case 0xBF:
                case 0xC0:
                case 0xC1:
                case 0xC2:
                case 0xC3:
                case 0xC4:
                case 0xC5: {
                    s32 other;
                    s32 kind;
                    BattleFighter *fighters;
                    s32 i;

                    other = task->unk50 != 0;
                    switch (task->unk54) {
                    case 0xBE:
                    case 0xBF:
                    default:
                        kind = 0;
                        break;
                    case 0xC0:
                    case 0xC1:
                        kind = 1;
                        break;
                    case 0xC2:
                    case 0xC3:
                        kind = 2;
                        break;
                    case 0xC4:
                    case 0xC5:
                        kind = 3;
                        break;
                    }
                    fighters = D_800A31E8.fighters[other];
                    switch (task->step) {
                    case 0:
                    default:
                        children[0] = func_80099400();
                        if (task->unk54 & 1) {
                            task->lines[0] = task->unk50;
                            task->lines[1] = D_800A21D8[kind];
                            children[0]->unkAC(children[0], 9, task->lines);
                            task->step = 1;
                            task->counter = 3;
                            return;
                        }
                        if (fighters[D_800A31E8.active[other]].flags & D_800A21D4[kind]) {
                            task->lines[0] = D_800A21E8[kind];
                            task->lines[1] = task->unk50;
                            task->lines[2] = D_800A31E8.active[0];
                            children[0]->unkAC(children[0], 2, task->lines);
                            task->step = 1;
                            task->counter = 1;
                            return;
                        }
                        task->lines[0] = 0x2F;
                        children[0]->unkAC(children[0], 1, task->lines);
                        break;
                    case 1:
                        for (i = 0; i < task->counter; i++) {
                            D_800A25F0.funcs.useItem(task->unk50, i, task->unk54);
                        }
                        break;
                    }
                    task->nextSubstate(task);
                    break;
                }
                case 0x64: {
                    BattleFighter *fighter;
                    s32 i;

                    fighter = D_800A31E8.fighters[0];
                    switch (task->step) {
                    case 0:
                    default:
                        children[0] = func_80099400();
                        task->lines[0] = 0;
                        task->lines[1] = 5;
                        children[0]->unkAC(children[0], 9, task->lines);
                        task->step++;
                        return;
                    case 1:
                        for (i = 0; i < 3; i++) {
                            if (fighter[i].id != 0 && fighter[i].hp == 0) {
                                fighter[i].hp = fighter[i].maxHp;
                                func_800A57A8(i);
                            }
                        }
                        break;
                    }
                    task->nextSubstate(task);
                    break;
                }
                case 0x177: {
#if VERSION_US
                    BattleFighter *fighter;
#endif
                    s32 i;

#if VERSION_US
                    fighter = D_800A31E8.fighters[0];
#endif
                    switch (task->step) {
                    case 0:
                    default:
                        children[0] = func_80099400();
                        task->lines[0] = 0;
                        task->lines[1] = 6;
                        children[0]->unkAC(children[0], 9, task->lines);
                        task->step++;
                        return;
                    case 1:
#if VERSION_US
                        for (i = 0; i < 3; i++) {
                            if (fighter[i].id != 0) {
                                if (fighter[i].hp == 0) {
                                    func_800A57A8(i);
                                }
                                fighter[i].flags = 0;
                                fighter[i].hp = fighter[i].maxHp;
                                func_8009BD20(0, i, 1, task->unk54);
                            }
                        }
#else
                        for (i = 0; i < 3; i++) {
                            func_8008F5D4(0x177, i);
                        }
#endif
                        break;
                    }
                    task->nextSubstate(task);
                    break;
                }
                default: {
                    BattleFighter *fighters;
                    s32 kind;

                    fighters = D_800A31E8.fighters[0];
                    if (task->unk50 != 0) {
                        fighters = D_800A31E8.fighters[1];
                    }
                    switch (task->step) {
                    case 0:
                    default: {
                        s32 i;
                        s32 most;

                        kind = -1;
                        task->unk5C = D_800A3308.unk94(task->unk50, task->unk54);
                        most = 0;
                        if (task->unk54 >= 0xBB) {
                            for (i = 0; i < 3; i++) {
                                if (fighters[i].id != 0 && fighters[i].hp != 0) {
                                    s32 lost = fighters[i].maxHp - fighters[i].hp;

                                    if (most < lost) {
                                        most = lost;
                                    }
                                }
                            }
                            if (most != 0) {
                                kind = 9;
                                if (task->unk5C < most) {
                                    most = task->unk5C;
                                }
                                task->lines[1] = 0;
                                task->lines[2] = most;
                            }
                        } else {
                            s32 lost;

                            i = D_800A31E8.active[task->unk50 != 0];
                            lost = fighters[i].maxHp - fighters[i].hp;
                            if (most < lost) {
                                most = lost;
                            }
                            if (most != 0) {
                                kind = 8;
                                if (task->unk5C < most) {
                                    most = task->unk5C;
                                }
                                task->unk5C = most;
                                task->lines[1] = most;
                            }
                        }
                        children[0] = func_80099400();
                        task->lines[0] = task->unk50;
                        if (kind != -1) {
                            s32 i;

                            children[0]->unkAC(children[0], kind, task->lines);
                            if (task->unk54 >= 0xBB) {
                                for (i = 0; i < 3; i++) {
                                    if (fighters[i].id != 0 && fighters[i].hp != 0) {
                                        if (fighters[i].hp + task->unk5C > fighters[i].maxHp) {
                                            fighters[i].hp = fighters[i].maxHp;
                                        } else {
                                            fighters[i].hp += task->unk5C;
                                        }
                                    }
                                }
                            } else {
                                i = D_800A31E8.active[task->unk50 != 0];
                                if (fighters[i].hp + task->unk5C > fighters[i].maxHp) {
                                    fighters[i].hp = fighters[i].maxHp;
                                } else {
                                    fighters[i].hp += task->unk5C;
                                }
                            }
                            task->nextSubstate(task);
                        } else {
                            task->lines[0] = 0x2F;
                            task->lines[1] = task->unk50;
                            children[0]->unkAC(children[0], 2, task->lines);
                            task->nextSubstate(task);
                        }
                        break;
                    }
                    case 1:
                        return;
                    }
                    break;
                }
                }
                break;
            case 5:
                children[0] = func_80099400();
                switch (task->unk54) {
                case 0xC6:
                case 0xC8:
                case 0xCA:
                case 0xCC:
                case 0xCD:
                case 0xCE:
                case 0xCF:
                case 0xD0: {
                    TechBoost *boost;
                    s32 other;
                    s32 ok;

                    for (boost = D_800A216C; boost->tech != -1; boost++) {
                        if (boost->tech == task->unk54) {
                            break;
                        }
                    }
                    ok = 1;
                    other = task->unk50 >> 4;
                    if (boost->amount <= 0) {
                        other ^= 1;
                        if (task->unk50 == 0 && D_80042728.unk3E[boost->stat + 8]) {
                            task->lines[0] = 0x2F;
                            children[0]->unkAC(children[0], ok, task->lines);
                            ok = 0;
                        }
                    }
                    if (ok == 0) {
                        break;
                    }
                    D_800A3308.unkE0((u8)(other << 4), D_800A31E8.active[other], boost->stat, boost->amount * tech->unkC);
                    func_8009BD20(other << 4, D_800A31E8.active[other], boost->stat, task->unk54);
                    task->lines[0] = boost->line;
                    task->lines[1] = other << 4;
                    task->lines[2] = D_800A31E8.active[other];
                    children[0]->unkAC(children[0], 2, task->lines);
                    break;
                }
                case 0xC7:
                case 0xC9:
                case 0xCB: {
                    TechBoost *boost;
                    s32 i;

                    for (boost = D_800A21B4; boost->tech != -1; boost++) {
                        if (boost->tech == task->unk54) {
                            break;
                        }
                    }
                    for (i = 0; i < 3; i++) {
                        if (D_800A31E8.fighters[task->unk50 >> 4][i].id != 0 && D_800A31E8.fighters[task->unk50 >> 4][i].hp > 0) {
                            D_800A3308.unkE0(task->unk50, i, boost->stat, boost->amount * tech->unkC);
                            func_8009BD20(task->unk50, i, boost->stat, task->unk54);
                        }
                    }
                    task->lines[0] = task->unk50;
                    switch (boost->stat) {
                    case 0:
                        task->lines[1] = 7;
                        break;
                    case 1:
                        task->lines[1] = 8;
                        break;
                    case 2:
                        task->lines[1] = 9;
                        break;
                    }
                    children[0]->unkAC(children[0], 9, task->lines);
                    break;
                }
                case 0xD1:
                case 0xD2: {
                    s32 other = task->unk50 >> 4;
                    s32 row = other * 0x60;
                    BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];

                    ((BattleFighter *)(row + (s32)slot))->unkE = tech->unkC;
                    task->lines[0] = 0x36;
                    task->lines[1] = task->unk50;
                    children[0]->unkAC(children[0], 2, task->lines);
                    break;
                }
                case 0xD3:
                    if (D_800A3308.unkC8(0x10, 0xD3)) {
                        func_8009BE1C(0xD3);
                        task->lines[0] = 0x44;
                        task->lines[1] = 0;
                        children[0]->unkAC(children[0], 2, task->lines);
                    } else {
                        task->lines[0] = 0x2F;
                        children[0]->unkAC(children[0], 1, task->lines);
                    }
                    break;
                case 0xD4:
                    if (D_800A3308.unkCC(0x10, 0xD4)) {
                        func_8009BE1C(0xD4);
                        task->lines[0] = 0x45;
                        task->lines[1] = 0;
                        children[0]->unkAC(children[0], 2, task->lines);
                    } else {
                        task->lines[0] = 0x2F;
                        children[0]->unkAC(children[0], 1, task->lines);
                    }
                    break;
                case 0x187:
                    if (D_800A3308.unkC0(0x10, 0x187)) {
                        func_8009C148();
                        children[0]->state = 3;
                    } else {
                        task->lines[0] = 0x2F;
                        children[0]->unkAC(children[0], 1, task->lines);
                    }
                    break;
                case 0x188: {
                    BattleFighter *to = &D_800A31E8.fighters[1][D_800A31E8.active[1]];
                    BattleFighter *from = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                    s32 amount;

                    if (from->mp != 0) {
                        amount = from->maxMp * tech->unkC / 128;
                        if (from->mp < amount) {
                            amount = from->mp;
                        }
                        to->mp += amount;
                        from->mp -= amount;
                        if (to->mp > to->maxMp) {
                            to->mp = to->maxMp;
                        }
                        if (from->mp < 0) {
                            from->mp = 0;
                        }
                        task->lines[0] = 0x10;
                        task->lines[1] = amount;
                        task->lines[2] = 1;
                        children[0]->unkAC(children[0], 0x12, task->lines);
                    } else {
                        task->lines[0] = 0x2F;
                        task->lines[1] = 0x10;
                        children[0]->unkAC(children[0], 2, task->lines);
                    }
                    break;
                }
                case 0x190: {
                    BattleFighter *fighter = &D_800A31E8.fighters[1][D_800A31E8.active[1]];

                    task->unk5C = D_800A3308.unk94(task->unk50, 0x190);
                    fighter->hp += task->unk5C;
                    if (fighter->hp > fighter->maxHp) {
                        fighter->hp = fighter->maxHp;
                    }
                    fighter->unkE = 0x20;
                    task->lines[0] = 0x46;
                    task->lines[1] = 0x10;
                    children[0]->unkAC(children[0], 2, task->lines);
                    break;
                }
                }
                task->nextSubstate(task);
                break;
            case 6: {
                BattleStats *stats;
                s16 level;
                s32 element;

                children[0] = func_80099400();
                stats = D_800A3308.computeStats(task->unk50, 1, D_800A31E8.active[task->unk50 == 0x10]);
                D_800A31E8.unkD0 = tech->unk4;
                level = stats->stats[2] / 10;
                element = level + tech->unkC;
                if (element >= 0x80) {
                    element = 0x7F;
                }
                D_800A31E8.unkD2 = element;
                func_8009B840(stats->stats[2] * 12 + 1000);
                task->lines[0] = tech->unk7 + 0x61;
                children[0]->unkAC(children[0], 1, task->lines);
                task->nextSubstate(task);
                return;
            }
            }
            break;
        case 2:
            if (children[0] == NULL) {
                Unk800427D6 *tech = &D_800427D6[task->unk54];

                if ((tech->unk4 == 2 || tech->unk4 == 3) && task->step == 0) {
                    if (task->damage == 0) {
                        if (task->unk50 == 0 && D_800A31E8.unkD6 == 6) {
                            task->setSubstate(task, 7);
                            break;
                        }
                    } else {
                        children[0] = (Unk80097F8C *)func_80090F28(task->unk50);
                        task->nextSubstate(task);
                        break;
                    }
                }
                task->state = 3;
            }
            break;
        case 3:
            if (children[0] == NULL) {
                task->substate++;
            }
            break;
        case 4: {
            s32 other = task->unk50 == 0;
            s32 row = other * 0x60;
            BattleFighter *slot = &D_800A31E8.fighters[0][D_800A31E8.active[other]];

            BattleFighter *fighter = (BattleFighter *)(row + (s32)slot);
            Unk800427D6 *tech;

            tech = &D_800427D6[task->unk54];
            if (fighter->flags & 8) {
                if (task->unk60 != 0 && D_800A3308.unkD4(other << 4, task->damage) != 0) {
                    task->lines[0] = 0x2B;
                    task->lines[1] = 0x10 - task->unk50;
                    task->lines[2] = D_800A31E8.active[other];
                    children[0] = func_80099400();
                    children[0]->unkAC(children[0], 7, task->lines);
                    fighter->flags &= ~8;
                    {
                        s32 event = D_800A25F0.funcs.find(0xC, 0x10 - task->unk50, D_800A31E8.active[other]);

                        if (event >= 0) {
                            D_800A25F0.events[event].type = 0;
                        }
                    }
                    task->substate = 9;
                } else {
                    task->state = 3;
                }
            } else if (tech->unk4 == 2) {
                children[0] = (Unk80097F8C *)func_8008EAA0((task->unk50 == 0) << 4, task->damage, tech->unk10 == 0xC);
                task->substate = 6;
            } else {
                task->substate = 5;
            }
            break;
        }
        case 6:
            if (children[0] != NULL) {
                if (children[0]->state != 2) {
                    break;
                }
            case 5:
                func_800A8F60(task->unk50, task->damage);
            }
            task->state = 3;
            break;
        case 7:
            if (children[0] == NULL) {
                Unk800427D6 *tech = &D_800427D6[task->unk54];

                children[0] = func_800908C0(1, tech->unk10 == 0xC);
                task->substate++;
            }
            break;
        case 8:
            if (children[0] == NULL) {
                task->setState(task, 3);
            }
            break;
        case 9:
            if (children[0] == NULL) {
                Unk800427D6 *tech = &D_800427D6[task->unk54];

                if (tech->unk4 == 2) {
                    children[0] = (Unk80097F8C *)func_8008EAA0((task->unk50 == 0) << 4, task->damage, tech->unk10 == 0xC);
                    task->substate = 6;
                } else {
                    task->substate = 5;
                }
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void func_80090050(s32 arg0, s32 arg1) {
    Unk8008EAF8 *task = createTask(func_8008EAF8, sizeof(Unk8008EAF8), sizeof(Task *));

    task->unk50 = arg0;
    task->unk54 = arg1;
}

/* WFIGHTMN declares it as returning its BattleTask */
Unk80097F8C *func_80099400(void);

void func_80090098(Unk80090098 *task, Unk80097F8C **children) {
    BattleTableEntry *entry;
    BattleFighter *fighter;

    switch (task->state) {
    case TASK_INIT:
    default:
        entry = D_800A2584(D_800A31E8.fighters[1][D_800A31E8.active[1]].id);
        children[0] = func_80099400();
        task->lines[0] = 0x10;
        task->lines[1] = entry->unk8[1];
        children[0]->unkAC(children[0], 3, task->lines);
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            if (children[0] == NULL) {
                children[0] = (Unk80097F8C *)func_800A9040(0x10, task->lines[1]);
                task->substate++;
            }
            break;
        case 1:
            if (children[0] == NULL) {
                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                children[0] = func_80099400();
                task->lines[0] = 0;
                task->lines[1] = fighter->hp - 1;
                children[0]->unkAC(children[0], 4, task->lines);
                fighter->hp = 1;
                task->substate++;
            }
            break;
        case 2:
            if (children[0] == NULL) {
                func_8009B5F8(D_800A25F0.funcs.getDelay(0x10, 0));
                func_8009C18C();
                task->state = TASK_KILL;
            }
            break;
        }
        break;
    case 2:
    case TASK_KILL:
        break;
    }
}

void func_80090264(void) {
    createTask(func_80090098, 0x70, sizeof(Task *));
}

Unk80090908 *func_80090F28(s32 arg0);
void func_8009C054(u8 side);
void func_8009C240(void);

/* An attack on the player's active fighter (func_800908C0): state 1 is the
   enemy's technique, 2 another attack, each with its messages, motion and
   damage. The match depends on each case advancing substate itself, on a
   fighter variable of its own in each case and on the pointer sum of the
   flag 8 test. */
void func_80090290(Unk80090290 *task, Unk80097F8C **children) {
    BattleTableEntry *entry = D_800A2584(D_800A31E8.fighters[1][D_800A31E8.active[1]].id);
    BattleFighter *fighter;
    BattleFighter *player;
    BattleFighter *target;
    BattleFighter *struck;
    s32 index;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->setState(task, task->unk74 + 1);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            func_8009B5F8(D_800A25F0.funcs.getDelay(0x10, 0));
            if (D_800A31E8.unkDB != 0) {
                if (D_800A25F0.funcs.first(0x18) >= 0) {
                    task->setState(task, 3);
                } else {
                    children[0] = func_80099400();
                    task->lines[0] = 8;
                    task->lines[1] = 0x10;
                    task->unk70 = entry->unk8[2];
                    children[0]->unkAC(children[0], 2, task->lines);
                    D_800A31E8.unkDB = 0;
                    D_800A31E8.unkDA = 0;
                    task->unk60 = 1;
                }
            } else {
                children[0] = func_80099400();
                task->lines[0] = 0x10;
                task->lines[1] = D_800A31E8.unkD8 != 0 ? D_800A31E8.unkD8 : entry->unk8[0];
                children[0]->unkAC(children[0], 3, task->lines);
                task->unk70 = entry->unk8[0];
            }
            if ((D_800A31E8.fighters[0] + D_800A31E8.active[0])->flags & 8) {
                task->unk7C = 1;
            }
            task->substate++;
            break;
        case 1:
            if (children[0] == NULL) {
                D_800A317C.unk68(0x10, task->unk70);
                children[0] = (Unk80097F8C *)func_800A9040(0x10, task->unk70);
                if (task->unk60 != 0) {
                    func_800A9840(0x10, 0);
                    task->unk60 = 0;
                }
                task->substate++;
            }
            break;
        case 2:
            if (children[0] == NULL) {
                children[0] = func_80099400();
                if (D_800A317C.hits[0]) {
#if VERSION_EU
                    player = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                    /* the European version's instant knockout */
                    if (D_800A317C.unk38[6]) {
                        player->hp = 0;
                        children[0]->state = 3;
                    } else {
                        task->lines[0] = 0;
                        task->lines[1] = D_800A317C.damage;
                        children[0]->unkAC(children[0], 4, task->lines);
                        player->hp -= D_800A317C.damage;
                        if (player->hp <= 0) {
                            player->hp = 0;
                        }
                    }
#else
                    task->lines[0] = 0;
                    task->lines[1] = D_800A317C.damage;
                    children[0]->unkAC(children[0], 4, task->lines);
                    player = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                    player->hp -= D_800A317C.damage;
                    if (player->hp <= 0) {
                        player->hp = 0;
                    }
#endif
                    task->substate++;
                } else {
                    task->lines[0] = 0x1D;
                    task->lines[1] = 0;
                    children[0]->unkAC(children[0], 2, task->lines);
                    task->substate = 5;
                }
            }
            break;
        case 3:
            if (children[0] == NULL) {
                target = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
#if VERSION_EU
                if (D_800A317C.unk38[6]) {
                    target->hp = 0;
                    func_8009C054(0);
                    task->state = 3;
                } else
#endif
                if (target->hp <= 0) {
                    target->hp = 0;
                    func_8009C054(0);
                    task->state = 3;
                } else {
                    children[0] = (Unk80097F8C *)func_80090F28(0x10);
                    task->substate++;
                }
            }
            break;
        case 4:
            if (children[0] == NULL) {
                fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                if (fighter->flags & 8) {
                    if (task->unk7C != 0 && D_800A3308.unkD4(0, D_800A317C.damage) != 0) {
                        task->lines[0] = 0x2B;
                        task->lines[1] = 0;
                        task->lines[2] = D_800A31E8.active[0];
                        children[0] = func_80099400();
                        children[0]->unkAC(children[0], 7, task->lines);
                        fighter->flags &= ~8;
                        index = D_800A25F0.funcs.find(0xC, 0, D_800A31E8.active[0]);
                        if (index >= 0) {
                            D_800A25F0.events[index].type = 0;
                        }
                        task->substate = 5;
                    } else {
                        task->state = 3;
                    }
                } else {
                    task->substate = 5;
                }
            }
            break;
        case 5:
            if (children[0] == NULL) {
                func_800A8F60(0x10, D_800A317C.damage);
                task->state = 3;
            }
            break;
        }
        break;
    case 2:
        if (children[0] == NULL) {
            switch (task->substate) {
            case 0:
            default:
                children[0] = func_80099400();
                task->lines[0] = 0x10;
                children[0]->unkAC(children[0], 6, task->lines);
                task->substate++;
                break;
            case 1:
                D_800A317C.unk68(0x10, entry->unk8[1]);
                children[0] = (Unk80097F8C *)func_800A9040(0x10, entry->unk8[1]);
                task->substate++;
                break;
            case 2:
                children[0] = func_80099400();
                if (D_800A317C.hits[0]) {
                    task->lines[0] = 0;
                    task->lines[1] = D_800A317C.damage;
                    children[0]->unkAC(children[0], 4, task->lines);
                    struck = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                    struck->hp -= D_800A317C.damage;
                    if (struck->hp <= 0) {
                        struck->hp = 0;
                        if (task->unk78 == 0) {
                            func_8009C054(0);
                        }
                    } else {
                        func_800A8F60(0x10, D_800A317C.damage);
                    }
                } else {
                    task->lines[0] = 0x1D;
                    task->lines[1] = 0;
                    children[0]->unkAC(children[0], 2, task->lines);
                }
                task->substate++;
                break;
            case 3:
                func_8009C240();
                task->state = 3;
                break;
            }
        }
        break;
    case 3:
        break;
    }
}

Unk80097F8C *func_800908C0(s32 arg0, s32 arg1) {
    Unk80090290 *task = createTask(func_80090290, sizeof(Unk80090290), sizeof(Task *));

    task->unk74 = arg0;
    task->unk78 = arg1;
    return (Unk80097F8C *)task;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_80090908);

Unk80090908 *func_80090F28(s32 arg0) {
    Unk80090908 *task = createTask(func_80090908, sizeof(Unk80090908), sizeof(Task *));

    task->unk50 = arg0;
    return task;
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

FighterCamera *FIGHTSTG_createCamera(s32 fighter, ModelControl *control) {
    FighterCamera *task = createTask(FIGHTSTG_updateCamera, sizeof(FighterCamera), 0);

    task->fighter = fighter;
    task->control = control;
    return task;
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

/* The view of a fighter's camera (id as Models.getFighter takes it), which ends
   the battle camera's fade */
CameraView *func_80091788(BattleCamera *task, s32 id, s32 camera) {
    Models *models;
    s32 fighter;
    FighterInfo *info;
    FighterInfoEnemy *enemy;

    /* the match depends on the do-while and its breaks, the early exit that
       the stages' event code uses too */
    do {
        models = TASK_FUNCS.find(0x14, -1, -1);
        if (models == NULL) {
            break;
        }
        fighter = models->getFighter(models, id);
        if (fighter == 0) {
            break;
        }
        if (!(id & 0xF0)) {
            info = D_800A32E0.funcs.getInfo(fighter);
            D_800A3438.vpx = info->camPos[camera].x;
            D_800A3438.vpy = -info->camPos[camera].y;
            D_800A3438.vpz = -info->camPos[camera].z;
            D_800A3438.vrx = info->camRef[camera].x;
            D_800A3438.vry = -info->camRef[camera].y;
            D_800A3438.vrz = -info->camRef[camera].z;
            D_800A3438.proj = info->camProj[camera];
        } else {
            enemy = (FighterInfoEnemy *)D_800A32E0.funcs.getInfo(fighter);
            D_800A3438.vpx = enemy->camPos[camera].x;
            D_800A3438.vpy = -enemy->camPos[camera].y;
            D_800A3438.vpz = -enemy->camPos[camera].z;
            D_800A3438.vrx = enemy->camRef[camera].x;
            D_800A3438.vry = -enemy->camRef[camera].y;
            D_800A3438.vrz = -enemy->camRef[camera].z;
            D_800A3438.proj = enemy->camProj[camera];
        }
        D_800A3438.rot.vx = 0;
        D_800A3438.rot.vy = 0;
        D_800A3438.rot.vz = 0;
        D_800A3438.tx = 0;
        D_800A3438.ty = 0;
        D_800A3438.tz = 0;
        D_800A3438.rz = 0;
        task->setState(task, TASK_DONE);
    } while (0);
    return &D_800A3438;
}

/* The view of the enemy's last camera */
CameraView *func_80091950(BattleCamera *task) {
    Models *models;
    s32 fighter;

    /* the match depends on the do-while and its breaks, as func_80091788's */
    do {
        models = TASK_FUNCS.find(0x14, -1, -1);
        if (models == NULL) {
            break;
        }
        fighter = models->getFighter(models, 0x10);
        if (fighter == 0) {
            break;
        }
        D_800A32E0.funcs.getInfo(fighter);
        func_80091788(task, 0, ((FighterInfoEnemy *)D_800A32E0.info)->cameraCount - 1);
    } while (0);
    return &D_800A3438;
}

void FIGHTSTG_createBattleCamera(s32 layerId) {
    BattleCamera *task = createTaskWithId(FIGHTSTG_updateBattleCamera, sizeof(BattleCamera), 0, 0x12);

    task->set = FIGHTSTG_setBattleCameraView;
    task->fade = FIGHTSTG_fadeBattleCamera;
    task->getEnemyView = func_80091950;
    task->layerId = layerId;
    task->getFighterView = func_80091788;
}

HpDisplay *func_80093058(void);
Unk800931CC *func_80093324(s32 arg0, s32 *done);
Unk800933EC *func_800935F4(void);
Unk8008690C *func_80087304(void); /* fightstg_3.c's, which returns its task */
Unk800937FC *func_80093BB0(s32 *arg0);
ItemMenu *func_80095154(s32 *arg0);
Unk80095AC0 *func_8009619C(s32 *arg0);
Unk800967A4 *func_80096C8C(s32 *done, s32 *arg1, s32 arg2);
Unk800973D4 *func_80097BEC(s32 *arg0, s32 *arg1);
Unk800999E4 *func_80099CC0(s32 *done, Task *arg1, Task *arg2);
/* The player's turn: substate 2 opens the battle menu (func_80093324) and then
   the menu of its command, 3 the roulette (func_80099CC0) and 4 func_80096C8C's
   menu; each sets action and goes back to substate 0, which closes the
   children. The match depends on the menus' results being switches with case
   -1 first and on each of the two endings of the command menu's last step
   being written out. */
void func_80091A58(Unk80091A58 *task, Task **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                task->command = 0;
                for (i = 1; i < 7; i++) {
                    if (children[i] != NULL) {
                        children[i]->setState(children[i], 3);
                    }
                }
                task->nextStep(task);
                break;
            case 1:
                break;
            }
            break;
        case 1:
            if (children[0] == NULL) {
                children[0] = (Task *)func_80093058();
            }
            task->setSubstate(task, 0);
            break;
        case 2:
            switch (task->step) {
            case 0:
            default:
                switch (task->counter) {
                case 0:
                default:
                    if (children[0] == NULL) {
                        children[0] = (Task *)func_80093058();
                    }
                    if (children[1] == NULL) {
                        children[1] = (Task *)func_80093324(task->command, &task->result);
                    }
                    if (children[2] == NULL) {
                        children[2] = (Task *)func_800935F4();
                    }
                    if (children[6] == NULL) {
                        children[6] = (Task *)func_80087304();
                    }
                    task->result = -1;
                    task->tickCounter(task);
                case 1:
                    if (task->result != -1) {
                        task->command = task->result;
                        switch (task->result) {
                        case 0:
                            task->action = 0;
                            task->setSubstate(task, 0);
                            break;
                        case 1:
                            task->setStep(task, 3);
                            break;
                        case 2:
                            task->setStep(task, 1);
                            break;
                        case 3:
                            task->setStep(task, 4);
                            task->unk54 = 0;
                            break;
                        case 4:
                            task->setStep(task, 2);
                            break;
                        case 5:
                            task->action = 1;
                            task->setSubstate(task, 0);
                            break;
                        }
                    }
                    break;
                }
                break;
            case 1:
                switch (task->counter) {
                case 0:
                default:
                    task->result = GAME_FUNCS.getPartyMember(D_800A31E8.active[0]);
                    children[3] = (Task *)func_80093BB0(&task->result);
                    task->tickCounter(task);
                case 1:
                    switch (task->result) {
                    case -1:
                        break;
                    case -2:
                        task->setSubstate(task, 2);
                        break;
                    default:
                        task->action = 2;
                        task->unk60 = GAME_FUNCS.getPartyMember(D_800A31E8.active[0]);
                        task->unk64 = task->result;
                        task->setSubstate(task, 0);
                        break;
                    }
                    break;
                }
                break;
            case 2:
                switch (task->counter) {
                case 0:
                default:
                    children[3] = (Task *)func_80095154(&task->result);
                    task->tickCounter(task);
                case 1:
                    switch (task->result) {
                    case -1:
                        break;
                    case -2:
                        task->setSubstate(task, 2);
                        break;
                    default:
                        task->action = 3;
                        task->unk60 = task->result;
                        task->setSubstate(task, 0);
                        break;
                    }
                    break;
                }
                break;
            case 3:
                switch (task->counter) {
                case 0:
                default:
                    children[3] = (Task *)func_8009619C(&task->result);
                    task->tickCounter(task);
                case 1:
                    switch (task->result) {
                    case -1:
                        break;
                    case -2:
                        task->setSubstate(task, 2);
                        break;
                    default:
                        task->action = 4;
                        task->unk60 = task->result;
                        task->setSubstate(task, 0);
                        break;
                    }
                    break;
                }
                break;
            case 4:
                switch (task->counter) {
                case 0:
                default:
                    children[3] = (Task *)func_80096C8C(&task->result, &task->unk54, 1);
                    task->tickCounter(task);
                case 1:
                    switch (task->result) {
                    case -1:
                        break;
                    case -2:
                        task->setSubstate(task, 2);
                        break;
                    default:
                        task->unk60 = task->result;
                        children[4] = (Task *)func_80097BEC(&task->result, &task->unk68);
                        task->tickCounter(task);
                        break;
                    }
                    break;
                case 2:
                    switch (task->result) {
                    case -1:
                        break;
                    case -2:
                        task->setCounter(task, 0);
                        break;
                    default:
                        if ((task->result & 0xF) == 0) {
                            task->action = 5;
                            task->unk64 = task->result >> 4;
                            task->setSubstate(task, 0);
                            task->unk54 = 0;
                        } else {
                            task->action = 6;
                            task->unk64 = task->result >> 4;
                            task->setSubstate(task, 0);
                            task->unk54 = 0;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 3:
            switch (task->counter) {
            case 0:
            default:
                if (children[2] == NULL) {
                    children[2] = (Task *)func_800935F4();
                }
                if (children[6] == NULL) {
                    children[6] = (Task *)func_80087304();
                }
                if (children[1] == NULL) {
                    children[1] = (Task *)func_80099CC0(&task->result, children[2], children[6]);
                }
                task->result = -1;
                task->tickCounter(task);
            case 1:
                switch (task->result) {
                case -1:
                    break;
                case 0:
                    task->action = 0;
                    task->setSubstate(task, 0);
                    break;
                default:
                    task->action = -1;
                    task->setSubstate(task, 0);
                    break;
                }
                break;
            }
            break;
        case 4:
            switch (task->counter) {
            case 0:
            default:
                if (children[6] == NULL) {
                    children[6] = (Task *)func_80087304();
                }
                if (children[3] == NULL) {
                    children[3] = (Task *)func_80096C8C(&task->result, &task->unk54, 0);
                }
                task->tickCounter(task);
            case 1:
                if (task->result != -1) {
                    task->unk60 = task->result;
                    children[4] = (Task *)func_80097B74(&task->result);
                    task->tickCounter(task);
                }
                break;
            case 2:
                switch (task->result) {
                case -1:
                    break;
                case -2:
                    task->setCounter(task, 0);
                    break;
                default:
                    if ((task->result & 0xF) == 0) {
                        task->action = 5;
                        task->unk64 = task->result >> 4;
                        task->setSubstate(task, 0);
                        task->unk54 = 0;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

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

void func_80092350(Unk80092350 *task) {
    switch (task->state) {
    case TASK_INIT: /* the match depends on this case, which default covers */
    default:
        task->nextState(task);
        task->level = 0;
    case TASK_RUN:
        if (task->substate == 0) {
            task->level += task->unk50 * GFX_FUNCS.getFrameTime();
            if (task->level >= 0xFF) {
                task->level = 0xFF;
                task->nextSubstate(task);
            }
        }
        break;
    case TASK_DONE:
        task->level -= task->unk50 * GFX_FUNCS.getFrameTime();
        if (task->level < 0) {
            task->level = 0;
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_KILL:
        break;
    }
    func_800921EC(task);
}

void func_8009245C(Unk80092350 *task, s32 frames) {
    task->unk50 = 0xFF / frames;
    task->setState(task, TASK_DONE);
}

Unk80092350 *func_80092494(s32 frames) {
    Unk80092350 *task = createTask(func_80092350, sizeof(Unk80092350), 0);

    task->unk50 = 0xFF / frames;
    return task;
}

/* Every frame: the hp tween of a side whose active fighter changed jumps to
 * that fighter's hp; every interval, a side's tween starts easing (30 frames)
 * to its fighter's hp, clamped to 0 and the max hp, when that changed. The
 * match depends on a counter for each loop and the side's row of fighters. */
void func_800924DC(HpDisplay *task, TextWindow **windows) {
    s32 hp;
    s32 i;
    s32 j;
    BattleFighter *row;

    task->timer += GFX_FUNCS.getFrameTime();
    for (i = 0; i < 2; i++) {
        row = D_800A31E8.fighters[i];
        if (task->hp[i].fighter != D_800A31E8.active[i]) {
            task->hp[i].from = row[D_800A31E8.active[i]].hp;
            task->hp[i].to = row[D_800A31E8.active[i]].hp;
            task->hp[i].value = row[D_800A31E8.active[i]].hp;
            task->hp[i].active = 0;
            task->hp[i].fighter = D_800A31E8.active[i];
        }
    }
    if (task->timer > task->interval) {
        task->timer -= task->interval;
        for (j = 0; j < 2; j++) {
            row = D_800A31E8.fighters[j];
            hp = row[D_800A31E8.active[j]].hp;
            if (hp <= 0) {
                hp = 0;
            }
            if (hp > row[D_800A31E8.active[j]].maxHp) {
                hp = row[D_800A31E8.active[j]].maxHp;
            }
            if (hp != task->hp[j].to) {
                task->hp[j].from = task->hp[j].value;
                task->hp[j].to = hp;
                task->hp[j].active = 1;
                task->hp[j].time = 0;
                task->hp[j].duration = 30;
            }
        }
    }
}

void func_80092660(HpTween *tween) {
    s32 t;

    if (tween->active != 0) {
        tween->time += GFX_FUNCS.getFrameTime();
        if (tween->time >= tween->duration) {
            tween->active = 0;
            tween->from = tween->value = tween->to;
        } else {
            t = rsin((tween->time << 10) / tween->duration) * tween->duration / 4096;
            tween->value = tween->from + (tween->to - tween->from) * t / tween->duration;
        }
    }
}

void func_80092738(HpDisplay *task, TextWindow **windows) {
    BattleTableEntry *enemy;
    s32 i;

    if (D_800A31E8.active[0] != task->shown[0]) {
        if (windows[0] == NULL) {
            windows[0] = createTextWindow(0x1005, 1, 0xAE, 0x15);
        }
        windows[0]->setString(windows[0], GAME.partners[GAME.funcs.getPartyMember(D_800A31E8.active[0])].name, -1);
    }
    if (D_800A31E8.active[1] != task->shown[1]) {
        enemy = D_800A2584(D_80042728.enemies[D_800A31E8.active[1]].fighter);
        if (windows[1] == NULL) {
            windows[1] = createTextWindow(0x1005, 1, 0x11, 0x15);
        }
        if (enemy != NULL) {
            windows[1]->setString(windows[1], FILE_CACHE.load(TEXT_FILE(0x4F)), enemy->nameId);
        }
    }
    for (i = 0; i < 2; i++) {
        task->shown[i] = D_800A31E8.active[i];
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800928BC);

void func_80092E0C(HpDisplay *task, TextWindow **windows) {
    s32 i;
    BattleFighter (*fighters)[3];

    switch (task->state) {
    case TASK_INIT:
    default:
        task->shown[1] = -1;
        task->shown[0] = -1;
        func_80092738(task, windows);
        windows[2] = createTextWindow(0x1005, 3, 0x10C, 0x1A);
        windows[2]->setString(windows[2], FILE_CACHE.load(TEXT_FILE(0x80)), 0x10);
        fighters = D_800A31E8.fighters;
        windows[4] = createTextWindow(0x1005, 3, 0x10B, 0x1A);
        windows[4]->setNumber(windows[4], 0, fighters[0][D_800A31E8.active[0]].hp);
        windows[4]->setRightAlign(windows[4], 1);
        windows[3] = createTextWindow(0x1005, 3, 0x12E, 0x1A);
        windows[3]->setNumber(windows[3], 0, fighters[0][D_800A31E8.active[0]].maxHp);
        windows[3]->setRightAlign(windows[3], 1);
        for (i = 0; i < 2; i++) {
            task->hp[i].from = fighters[i][D_800A31E8.active[i]].hp;
            task->hp[i].to = fighters[i][D_800A31E8.active[i]].hp;
            task->hp[i].value = fighters[i][D_800A31E8.active[i]].hp;
            task->hp[i].active = 0;
            task->hp[i].fighter = D_800A31E8.active[i];
            task->hp[i].time = 0;
            task->hp[i].duration = 0;
        }
        task->timer = 0;
        task->interval = 8;
        task->nextState(task);
        break;
    case TASK_RUN:
        func_800924DC(task, windows);
        func_80092660(&task->hp[0]);
        func_80092660(&task->hp[1]);
        func_800928BC(task, windows);
        break;
    case TASK_DONE:
        task->nextState(task);
        break;
    case TASK_KILL:
        break;
    }
}

HpDisplay *func_80093058(void) {
    return createTask(func_80092E0C, sizeof(HpDisplay), 5 * sizeof(TextWindow *));
}

/* Creates the six lines once, the first three in palette 7 when the active
   fighter has flag 8 and the third when it has 0x20 (the first window's
   setPalette is called for each) */
void func_80093084(Unk800931CC *task) {
    Unk800931CCWindows *w = task->children;
    BattleFighter *fighter;
    char *text;
    s32 i;

    if (w->lines[0] == NULL) {
        text = FILE_CACHE.load(TEXT_FILE(0x80));
        for (i = 0; i < 6; i++) {
            w->lines[i] = createTextWindow(0x1005, 1, 0x24, 0x6D + i * 0x13);
            w->lines[i]->setString(w->lines[i], text, i + 1);
        }
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        if (fighter->flags & 8) {
            for (i = 0; i < 3; i++) {
                w->lines[0]->setPalette(w->lines[i], 7);
            }
        }
        if (fighter->flags & 0x20) {
            w->lines[0]->setPalette(w->lines[2], 7);
        }
    }
}

/* Six choices: puts a cursor (D_800A2254) on the lines, starting on unk50;
 * cross picks the line into *unk54 and locks the cursor, but not lines 0-2
 * when the active fighter has flag 8, nor line 2 when it has 0x20. The match
 * depends on the early exits being breaks out of a do/while. */
void func_800931CC(Unk800931CC *task, Unk800931CCWindows *w) {
    BattleFighter *fighter;

    switch (task->state) {
    case TASK_INIT:
    default:
        w->cursor = func_8009A214(&D_800A2254);
        w->cursor->sel = task->unk50;
        func_80093084(task);
        task->nextState(task);
        break;
    case TASK_RUN:
        do {
            if (!(PAD.getPressed(0) & (1 << PAD_CROSS))) {
                break;
            }
            SOUND.playSound(0x4001C);
            fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
            if ((fighter->flags & 8) && w->cursor->sel < 3) {
                break;
            }
            if ((fighter->flags & 0x20) && w->cursor->sel == 2) {
                break;
            }
            *task->unk54 = w->cursor->sel;
            task->setState(task, 3);
            w->cursor->locked = 1;
        } while (0);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Unk800931CC *func_80093324(s32 arg0, s32 *done) {
    Unk800931CC *task = createTask(func_800931CC, sizeof(Unk800931CC), 0x1C);

    task->unk54 = done;
    *done = -1;
    task->unk50 = arg0;
    return task;
}

void func_80093374(Unk800933EC *task, FighterCamera **cameras) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 0);
    drawer.setTexture(0x200, 0);
    drawer.draw(FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16), 10, 246, 74);
}

void func_800933EC(Unk800933EC *task, FighterCamera **cameras) {
    Models *models;
    ModelControl *control;
    FighterCamera *other;
    s32 fighter;

    switch (task->state) {
    case TASK_INIT:
    default:
        D_800A3470.x = 0xD0;
        D_800A3470.y = 0x4C;
        D_800A3470.w = 0x64;
        D_800A3470.h = 0x3C;
        task->layer = GFX_FUNCS.createLayer(&D_800A3470, 0xC, 0x1009);
        task->layer->setOffset(task->layer, 0x102, 0x6A);
        task->layer->allocCallbacks(task->layer, 0x32);
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->substate == 0) {
            models = TASK_FUNCS.find(0x14, -1, -1);
            if (models != NULL) {
                control = models->get(models, 0);
                control->unk34[1].enabled = 1;
                control->unk34[1].alt = 0;
                control->unk34[1].arg = 0x1009;
                fighter = control->fighter;
                if (cameras[0] == NULL) {
                    cameras[0] = FIGHTSTG_createCamera(fighter, control);
                    other = cameras[1];
                } else {
                    cameras[1] = FIGHTSTG_createCamera(fighter, control);
                    other = cameras[0];
                }
                if (other != NULL) {
                    other->setState(other, 3);
                }
                task->nextSubstate(task);
            }
        }
        func_80093374(task, cameras);
        break;
    case 2:
        task->nextState(task);
        break;
    case TASK_KILL:
        if (task->layer != NULL) {
            models = TASK_FUNCS.find(0x14, -1, -1);
            models->get(models, 0)->unk34[1].enabled = 0;
            GFX_FUNCS.destroyLayer(0x1009);
        }
        break;
    }
}

Unk800933EC *func_800935F4(void) {
    return createTask(func_800933EC, 0x58, 2 * sizeof(Task *));
}

void func_80093620(Unk800937FC *task) {
    TextWindow **windows = task->children;
    BattleFighter *fighter;
    DigimonData *data;
    s32 index;
    s32 current;
    s32 i;

    /* the match depends on setting index in the loop's init */
    for (i = 0, index = -1; i < 3; i++) {
        if (task->unk54 == GAME.funcs.getPartyMember(i)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return;
    }
    fighter = &D_800A31E8.fighters[0][index];
    if (fighter->unk1A) {
        current = fighter->prevId;
    } else {
        current = fighter->id;
    }
    for (i = 0; i < task->count; i++) {
        if (windows[i + 1] == NULL) {
            windows[i + 1] = createTextWindow(0x1005, 1, 0xBB, 0x92 + i * 0x13);
        }
        data = ON_PARTNER_ENTRY_ADDED(task->ids[i]);
        if (data != NULL) {
            windows[i + 1]->setString(windows[i + 1], FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
            if (current == task->ids[i]) {
                windows[i + 1]->setPalette(windows[i + 1], 7);
            } else {
                windows[i + 1]->setPalette(windows[i + 1], 0);
            }
        }
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800937FC);

Unk800937FC *func_80093BB0(s32 *arg0) {
    Unk800937FC *task = createTask(func_800937FC, sizeof(Unk800937FC), 7 * sizeof(Task *));

    task->unk50 = arg0;
    task->unk54 = *arg0;
    *arg0 = -1;
    return task;
}

void func_80093BFC(Unk80094278 *task) {
    SpriteDrawer drawer;
    s32 sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    drawer.setTexture(0x200, 0);
    if (GFX_FUNCS.getTime() & 0x10) {
        drawer.draw(sheet, 0x1F, 0x18, 0xAB);
        drawer.draw(sheet, 0x20, 0x48, 0xAB);
    }
}

void func_80093CB0(Unk80094278 *task, TextWindow **windows) {
    void *text = FILE_CACHE.load(TEXT_FILE(0x80));

    windows[1] = createTextWindow(0x1005, 3, 0x22, 0xAB);
    windows[1]->setString(windows[1], text, 0x11);
    windows[1]->setPalette(windows[1], 2);
    windows[2] = createTextWindow(0x1005, 3, 0x38, 0xAB);
    windows[2]->setString(windows[2], text, 0x12);
    windows[2]->setPalette(windows[2], 2);
}

void func_80093D7C(Unk80094278 *task) {
    SpriteDrawer drawer;
    s32 sheet;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    sheet = FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16);
    drawer.setTexture(0x140, 0);
    drawer.draw(sheet, 0x23, 0x18, 0x51);
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    drawer.setTexture(0x200, 0);
    drawer.draw(sheet, 0x25, 0x10, 0x4A);
}

/* Creates the thirteen stat numbers of D_800A2294 (up to 999), right
 * aligned, in palette 6 for windows 5, 6 and 9 when stats 19, 20 and 21 are
 * set. The match depends on reading the stat through a pointer sum. */
void func_80093E4C(Unk80094278 *task, TextWindow **windows) {
    s32 i;
    s32 value;

    for (i = 0; i < 13; i++) {
        windows[i + 5] = createTextWindow(0x1005, 1, D_800A2294[i].x, D_800A2294[i].y);
        value = *(task->stats + D_800A2294[i].stat);
        if (value >= 1000) {
            value = 999;
        }
        windows[i + 5]->setNumber(windows[i + 5], 0, value);
        windows[i + 5]->setRightAlign(windows[i + 5], 1);
    }
    if (task->stats[19]) {
        windows[5]->setPalette(windows[5], 6);
    }
    if (task->stats[20]) {
        windows[6]->setPalette(windows[6], 6);
    }
    if (task->stats[21]) {
        windows[9]->setPalette(windows[9], 6);
    }
}

void func_80093F94(Unk80094278 *task) {
    SpriteDrawer drawer;
    s32 sheet;
    s32 i;
    s32 tech;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    sheet = FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16);
    drawer.setTexture(0x140, 0);
    for (i = 0; i < 6; i++) {
        tech = task->techs[i] & 0x1FFF;
        if (tech != 0) {
            drawer.draw(sheet, D_800427E8[tech - 1].icon + 0x37, 0x18, 0x51 + i * 0xE);
        }
    }
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    drawer.setTexture(0x200, 0);
    drawer.draw(sheet, 0x26, 0x10, 0x4A);
}

void func_800940CC(Unk80094278 *task, TextWindow **windows) {
    void *text = FILE_CACHE.load(TEXT_FILE(0x80));
    s32 i;
    s32 tech;

    windows[3] = createTextWindow(0x1005, 1, 0x5A, 0xA9);
    windows[3]->setString(windows[3], text, 0x19);
    windows[4] = createTextWindow(0x1005, 1, 0x93, 0xA9);
    if (task->unk60 >= 0) {
        windows[4]->setNumber(windows[4], 0, task->unk60);
    } else {
        windows[4]->setString(windows[4], text, 0x1A);
    }
    windows[4]->setRightAlign(windows[4], 1);
    for (i = 0; i < 6; i++) {
        windows[i + 18] = createTextWindow(0x1005, 1, 0x26, 0x51 + i * 0xE);
        tech = task->techs[i];
        if (tech != 0) {
            windows[i + 18]->setString(windows[i + 18], FILE_CACHE.load(TEXT_FILE(0xA3)), tech & 0x1FFF);
            if (tech & 0x8000) {
                windows[i + 18]->setPalette(windows[i + 18], 3);
            } else if (tech & 0x4000) {
                windows[i + 18]->setPalette(windows[i + 18], 4);
            }
        }
    }
}

void func_80093E4C(Unk80094278 *task, TextWindow **windows);

void func_80094278(Unk80094278 *task, TextWindow **windows) {
    s32 list[10];
    s32 partner;
    DigimonData *data;
    s32 count;
    s32 tech;
    s32 n;
    s32 k;
    s32 m;
    s32 i;
    s32 j;

    switch (task->state) {
    case 0:
    default:
        partner = task->unk54;
        switch (task->unk58) {
        case 0:
            GAME.funcs.computeStats(partner, (struct PartnerTotals *)task->stats);
            if (task->unk5C != 0) {
                GAME.funcs.getPartnerSlots(partner, task->slots);
                data = ON_PARTNER_ENTRY_ADDED(task->slots[task->unk5C - 1]);
                /* the match depends on indexing from &task->stats[6] and [12] */
                for (j = 0; j < 6; j++) {
                    (&task->stats[6])[j] += data->battleStats[j];
                }
                for (j = 0; j < 7; j++) {
                    (&task->stats[12])[j] += data->resistances[j];
                }
            }
            break;
        case 1:
            if (task->unk5C == 0) {
                data = &DIGIMON_DATA[partner];
                task->techs[0] = data->skills[6] | 0x8000;
                task->unk60 = -1;
            } else {
                GAME.funcs.getPartnerSlots(partner, task->slots);
                GAME.funcs.getPartnerEntry(partner, task->slots[task->unk5C - 1], &task->entries[0]);
                task->unk60 = task->entries[0].unk2;
                for (j = 0, n = 0; j < 6; j++) {
                    if (task->entries[0].techs[j] != 0) {
                        task->techs[n++] = task->entries[0].techs[j];
                    }
                }
            }
            break;
        case 2:
            if (task->unk5C == 0) {
                task->unk60 = -1;
            } else {
                for (k = 0; k < 10; k++) {
                    list[k] = 0;
                }
                k = 0;
                count = GAME.funcs.getPartnerSlots(partner, task->slots);
                for (i = 0; i < count; i++) {
                    if (GAME.funcs.getPartnerEntry(partner, task->slots[i], &task->entries[i]) >= 0 &&
                        i != task->unk5C - 1) {
                        for (j = 0; j < 6; j++) {
                            tech = task->entries[i].techs[j];
                            if (tech != 0 && (tech & 0x4000)) {
                                list[k++] = tech & 0x1FFF;
                            }
                        }
                    }
                }
                n = 0;
                for (m = 0; m < 10; m++) {
                    tech = list[m];
                    for (k = 0; k < 6; k++) {
                        if (task->techs[k] == list[m]) {
                            tech = 0;
                            break;
                        }
                    }
                    if (tech != 0) {
                        task->techs[n++] = tech;
                    }
                }
                task->unk60 = task->entries[task->unk5C - 1].unk2;
            }
            break;
        }
        func_80093CB0(task, windows);
        switch (task->unk58) {
        case 0:
            func_80093E4C(task, windows);
            break;
        case 1:
        case 2:
            func_800940CC(task, windows);
            break;
        }
        task->nextState(task);
        break;
    case 1:
        func_80093BFC(task);
        switch (task->unk58) {
        case 0:
            func_80093D7C(task);
            break;
        case 1:
        case 2:
            func_80093F94(task);
            break;
        }
        break;
    case 2:
        func_80093BFC(task);
        switch (task->unk58) {
        case 0:
            func_80093D7C(task);
            break;
        case 1:
        case 2:
            func_80093F94(task);
            break;
        }
        task->nextState(task);
        break;
    case 3:
        break;
    }
}

Unk80094278 *func_80094754(s32 arg0, s32 arg1, s32 arg2) {
    Unk80094278 *task = createTask(func_80094278, sizeof(Unk80094278), 0x60);

    task->unk54 = arg0;
    task->unk58 = arg1;
    task->unk5C = arg2;
    return task;
}

/* Draws the page's item icons, the page arrows (blinking) and the frame */
void func_800947AC(ItemMenu *task) {
    SpriteDrawer drawer;
    s32 sheet;
    s32 index;
    s32 i;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    drawer.setTexture(0x140, 0);
    sheet = FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16);
    for (i = 0; i < 7; i++) {
        index = task->page * 7 + i;
        if (index > task->count - 1) {
            break;
        }
        drawer.draw(sheet, ITEM_FUNCS->getCategory(task->usable[index]), 0x1D, 0x45 + i * 0xE);
    }
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    drawer.setTexture(0x200, 0);
    if (GFX_FUNCS.getTime() & 0x10) {
        if (task->page > 0) {
            drawer.draw(sheet, 0x1F, 0x10, 0xA9);
        }
        if (task->page < task->pageCount - 1) {
            drawer.draw(sheet, 0x20, 0x90, 0xA9);
        }
    }
    drawer.draw(sheet, 0x27, 8, 0x3E);
    drawer.draw(sheet, 0x28, 0xA6, 0xA0);
    drawer.draw(sheet, 0x31, 0xB, 0xBC);
}

void func_800949AC(ItemMenu *task, ItemMenuWindows *w) {
    char *text;
    s32 i;

    text = FILE_CACHE.load(TEXT_FILE(0x80));
    w->unk4 = createTextWindow(0x1005, 3, 0x1A, 0xA9);
    w->unk4->setString(w->unk4, text, 0x11);
    w->unk4->setPalette(w->unk4, 2);
    w->unk8 = createTextWindow(0x1005, 3, 0x80, 0xA9);
    w->unk8->setString(w->unk8, text, 0x12);
    w->unk8->setPalette(w->unk8, 2);
    w->unkC = createTextWindow(0x1005, 1, 0xAC, 0xA5);
    w->unkC->setString(w->unkC, text, 0xC);
    for (i = 0; i < 7; i++) {
        w->names[i] = createTextWindow(0x1005, 1, 0x2A, 0x45 + i * 0xE);
    }
    w->message = createTextWindow(0x1005, 1, 0x14, 0xC2);
    w->count = createTextWindow(0x1005, 1, 0xC6, 0xA5);
}

/* Shows the page's names and the description and count of the item under
   the cursor, or text 0x15 and 0x1A when there are none */
void func_80094B1C(ItemMenu *task, ItemMenuWindows *w) {
    s32 index;
    s32 item;
    s32 i;

    if (task->count != 0) {
        for (i = 0; i < 7; i++) {
            index = task->page * 7 + i;
            if (index > task->count - 1) {
                w->names[i]->setVisible(w->names[i], 0);
            } else {
                item = task->usable[index];
                if (item != 0) {
                    w->names[i]->setString(w->names[i], FILE_CACHE.load(TEXT_FILE(0x6B)), item);
                }
            }
        }
        item = task->usable[task->page * 7 + w->cursor->sel];
        w->message->setString(w->message, FILE_CACHE.load(TEXT_FILE(0x64)), item);
        w->count->setNumber(w->count, 0, GAME.items[item]);
    } else {
        w->message->setString(w->message, FILE_CACHE.load(TEXT_FILE(0x80)), 0x15);
        w->count->setString(w->count, FILE_CACHE.load(TEXT_FILE(0x80)), 0x1A);
    }
    w->count->setRightAlign(w->count, 1);
}

void func_80094D04(ItemMenu *task, ItemMenuWindows *w) {
    s32 total;
    s32 pressed;
    s32 page;
    s32 rows;
    s32 n;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        total = ITEM_FUNCS->list(1, (u16 *)task->items);
        task->count = 0;
        for (i = 0; i < total; i++) {
            if (task->items[i] == 0) {
                break;
            }
            if (*GET_ITEM[0](task->items[i])->data & 2) {
                task->count++;
            }
        }
        if (task->count != 0) {
            task->usable = HEAP.alloc(task->count * 2, 2);
            n = 0;
            for (i = 0; i < total; i++) {
                if (task->items[i] == 0) {
                    break;
                }
                if (*GET_ITEM[0](task->items[i])->data & 2) {
                    task->usable[n++] = task->items[i];
                }
            }
            if (task->count % 7 != 0) {
                task->pageCount = task->count / 7 + 1;
            } else {
                task->pageCount = task->count / 7;
            }
            if (task->count != 0) {
                if (task->count >= 8) {
                    D_800A22BC.count = 7;
                } else {
                    D_800A22BC.count = task->count;
                }
            }
        }
        w->cursor = func_8009A214(&D_800A22BC);
        func_800949AC(task, w);
        func_80094B1C(task, w);
        task->nextState(task);
        break;
    case TASK_RUN:
        func_800947AC(task);
        pressed = PAD.getPressed(0);
        page = task->page;
        if (task->pageCount != 0) {
            if (pressed & (1 << PAD_L1)) {
                if (--task->page < 0) {
                    task->page = 0;
                }
            } else if (pressed & (1 << PAD_R1)) {
                if (++task->page > task->pageCount - 1) {
                    task->page = task->pageCount - 1;
                }
            }
        }
        if (page != task->page) {
            w->cursor->sel = 0;
            rows = task->count - task->page * 7;
            if (rows >= 8) {
                rows = 7;
            }
            w->cursor->params.count = rows;
            func_80094B1C(task, w);
            SOUND.playSound(0x4001B);
        } else if (task->sel != w->cursor->sel) {
            func_80094B1C(task, w);
        } else if (pressed & (1 << PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            if (task->count != 0) {
                *task->unk50 = task->usable[task->page * 7 + w->cursor->sel];
                task->setState(task, 3);
                w->cursor->locked = 1;
                break;
            }
        } else if (pressed & (1 << PAD_TRIANGLE)) {
            /* the match depends on the goto, which puts the cancel after the
               cursor's line */
            goto cancel;
        }
        task->sel = w->cursor->sel;
        break;
    cancel:
        SOUND.playSound(0x800450BD);
        *task->unk50 = -2;
        task->setState(task, 3);
        break;
    case 2:
        break;
    case 3:
        if (task->usable != NULL) {
            HEAP.free(task->usable);
        }
        break;
    }
}

ItemMenu *func_80095154(s32 *arg0) {
    ItemMenu *task = createTask(func_80094D04, sizeof(ItemMenu), sizeof(ItemMenuWindows));

    task->unk50 = arg0;
    *arg0 = -1;
    return task;
}

void func_80095194(Unk80095AC0 *task) {
    SpriteDrawer drawer;
    s32 sheet;
    s32 index;
    s32 tech;
    s32 i;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1005, 1);
    drawer.setTexture(0x140, 0);
    sheet = FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16);
    for (i = 0; i < 6; i++) {
        index = task->page * 6 + i;
        if (index < task->count) {
            tech = task->techs[index] & 0x1FFF;
            if (tech == 0) {
                break;
            }
            drawer.draw(sheet, D_800427E8[tech - 1].icon + 0x37, 0x1D, 0x45 + i * 0xE);
        }
    }
    drawer.setTexture(0x200, 0);
    sheet = FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16);
    if (GFX_FUNCS.getTime() & 0x10) {
        if (task->page > 0) {
            drawer.draw(sheet, 0x1F, 0x10, 0x9F);
        }
        if (task->page < task->pageCount - 1) {
            drawer.draw(sheet, 0x20, 0x90, 0x9F);
        }
    }
    drawer.draw(sheet, 0x2A, 8, 0x3E);
    drawer.draw(sheet, 0x29, 0xA3, 0x21);
    drawer.draw(sheet, 0x31, 0xB, 0xBC);
}

void func_8009539C(Unk80095AC0 *task, TextWindow **windows) {
    BattleFighter *fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
    void *text = FILE_CACHE.load(TEXT_FILE(0x80));
    s32 i;

    windows[1] = createTextWindow(0x1005, 3, 0x1A, 0x9F);
    windows[1]->setString(windows[1], text, 0x11);
    windows[1]->setPalette(windows[1], 2);
    windows[2] = createTextWindow(0x1005, 3, 0x80, 0x9F);
    windows[2]->setString(windows[2], text, 0x12);
    windows[2]->setPalette(windows[2], 2);
    windows[3] = createTextWindow(0x1005, 3, 0xAC, 0x3A);
    windows[3]->setString(windows[3], text, 0xD);
    windows[6] = createTextWindow(0x1005, 3, 0xD8, 0x3A);
    if (fighter->unk1A) {
        if (fighter->mp < 100) {
            windows[6]->setString(windows[6], text, 0x1A);
        } else if (fighter->mp < 1000) {
            windows[6]->setString(windows[6], text, 0xF);
        } else {
            windows[6]->setString(windows[6], text, 0x24);
        }
    } else {
        windows[6]->setNumber(windows[6], 0, fighter->mp);
    }
    windows[6]->setRightAlign(windows[6], 1);
    windows[5] = createTextWindow(0x1005, 3, 0xD9, 0x3A);
    windows[5]->setString(windows[5], text, 0x10);
    windows[4] = createTextWindow(0x1005, 3, 0xFB, 0x3A);
    windows[4]->setNumber(windows[4], 0, fighter->maxMp);
    windows[4]->setRightAlign(windows[4], 1);
    for (i = 0; i < 6; i++) {
        windows[7 + i] = createTextWindow(0x1005, 1, 0x2A, 0x45 + i * 0xE);
    }
    windows[13] = createTextWindow(0x1005, 1, 0x14, 0xC2);
    windows[14] = createTextWindow(0x1005, 1, 0x100, 0xD0);
    windows[15] = createTextWindow(0x1005, 1, 0x12B, 0xD0);
}

void func_80095660(Unk80095AC0 *task, TextWindow **windows) {
    BattleFighter *fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
    s32 index;
    s32 tech;
    s32 mp;
    s32 i;

    if (task->count != 0) {
        for (i = 0; i < 6; i++) {
            index = task->page * 6 + i;
            if (index > task->count - 1) {
                windows[7 + i]->setVisible(windows[7 + i], 0);
            } else {
                tech = task->techs[index];
                windows[7 + i]->setString(windows[7 + i], FILE_CACHE.load(TEXT_FILE(0xA3)), tech & 0x1FFF);
                mp = D_800A3308.unkE8(0, tech);
                if (fighter->unk1A) {
                    if (tech & 0x8000) {
                        windows[7 + i]->setPalette(windows[7 + i], 3);
                    } else if (tech & 0x4000) {
                        windows[7 + i]->setPalette(windows[7 + i], 4);
                    } else {
                        windows[7 + i]->setPalette(windows[7 + i], 0);
                    }
                } else if (fighter->mp < mp) {
                    windows[7 + i]->setPalette(windows[7 + i], 7);
                } else if (tech & 0x8000) {
                    windows[7 + i]->setPalette(windows[7 + i], 3);
                } else if (tech & 0x4000) {
                    windows[7 + i]->setPalette(windows[7 + i], 4);
                } else {
                    windows[7 + i]->setPalette(windows[7 + i], 0);
                }
            }
        }
        mp = D_800A3308.unkE8(0, task->techs[task->page * 6 + ((Unk8009A098 *)windows[0])->sel]);
        tech = task->techs[task->page * 6 + ((Unk8009A098 *)windows[0])->sel];
        if (fighter->unk1A == 0 && fighter->mp < mp) {
            windows[13]->setString(windows[13], FILE_CACHE.load(TEXT_FILE(0x80)), 0x54);
            windows[14]->setString(windows[14], FILE_CACHE.load(TEXT_FILE(0x80)), 0xD);
            windows[14]->setPalette(windows[14], 7);
            windows[15]->setNumber(windows[15], 0, mp);
            windows[15]->setRightAlign(windows[15], 1);
            windows[15]->setPalette(windows[15], 7);
        } else {
            windows[13]->setString(windows[13], FILE_CACHE.load(TEXT_FILE(0x9C)), tech & 0x1FFF);
            windows[14]->setString(windows[14], FILE_CACHE.load(TEXT_FILE(0x80)), 0xD);
            windows[15]->setNumber(windows[15], 0, mp);
            windows[15]->setRightAlign(windows[15], 1);
            if (tech & 0x4000) {
                windows[14]->setPalette(windows[14], 4);
                windows[15]->setPalette(windows[15], 4);
            } else {
                windows[14]->setPalette(windows[14], 0);
                windows[15]->setPalette(windows[15], 0);
            }
        }
    } else {
        windows[13]->setString(windows[13], FILE_CACHE.load(TEXT_FILE(0x80)), 0x13);
    }
}

/* The battle's technique menu: the active fighter's techniques (a Digimon of
   a partner's slots has its entry's, its signature one and the ones the other
   entries can pass on), six a page */
void func_80095AC0(Unk80095AC0 *task, TextWindow **windows) {
    s32 extra[10];
    BattleFighter *fighter;
    BattleFighter *active;
    DigimonData *data;
    s32 member;
    s32 id;
    s32 slots;
    s32 found;
    s32 count;
    s32 tech;
    s32 pressed;
    s32 page;
    s32 lines;
    s32 mp;
    s32 i;
    s32 j;

    switch (task->state) {
    case TASK_INIT:
    default:
        member = GAME.funcs.getPartyMember(D_800A31E8.active[0]);
        fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
        id = fighter->id;
        if (id == DIGIMON_DATA[member].id) {
            task->techs[0] = DIGIMON_DATA[member].skills[6] | 0x8000;
            task->count = 1;
        } else {
            slots = GAME.funcs.getPartnerSlots(member, task->slots);
            task->count = 0;
            for (i = 0; i < slots; i++) {
                GAME.funcs.getPartnerEntry(member, task->slots[i], &task->entries[i]);
                if (id == task->entries[i].id) {
                    for (j = 0; j < 6; j++) {
                        if (task->entries[i].techs[j] != 0) {
                            task->techs[task->count++] = (s16)(task->entries[i].techs[j] & ~0x4000);
                        }
                    }
                }
            }
            if (fighter->unk1A != 0) {
                data = ON_PARTNER_ENTRY_ADDED(fighter->id);
                found = 0;
                for (j = 0; j < task->count; j++) {
                    if ((task->techs[j] & 0x1FFF) == data->skills[6]) {
                        task->techs[j] = (task->techs[j] & 0x1FFF) | 0x8000;
                        found = -1;
                        break;
                    }
                }
                if (found != -1) {
                    task->techs[task->count++] = data->skills[6] | 0x8000;
                }
            }
            /* the techniques the other entries can pass on */
            for (j = 9; j >= 0; j--) {
                extra[j] = 0;
            }
            count = 0;
            for (i = 0; i < slots; i++) {
                if (id != task->entries[i].id) {
                    for (j = 0; j < 6; j++) {
                        if (task->entries[i].techs[j] & 0x4000) {
                            extra[count++] = task->entries[i].techs[j];
                        }
                    }
                }
            }
            for (j = 0; j < count; j++) {
                tech = extra[j] & 0x1FFF;
                for (i = 0; i < task->count; i++) {
                    if (tech == (task->techs[i] & 0x1FFF)) {
                        tech = 0;
                        break;
                    }
                }
                if (tech != 0) {
                    task->techs[task->count++] = extra[j];
                }
            }
        }
        if (task->count != 0) {
            if (task->count % 6 != 0) {
                task->pageCount = task->count / 6 + 1;
            } else {
                task->pageCount = task->count / 6;
            }
        }
        if (task->count != 0) {
            if (task->count > 6) {
                D_800A22DC.count = 6;
            } else {
                D_800A22DC.count = task->count;
            }
        }
#if VERSION_EU
        else {
            D_800A22DC.count = 1;
        }
#endif
        windows[0] = (TextWindow *)func_8009A214(&D_800A22DC);
        func_8009539C(task, windows);
        func_80095660(task, windows);
        task->nextState(task);
        break;
    case TASK_RUN:
        func_80095194(task);
        /* the match depends on the do-while and its breaks, which skip the
           update of sel, the stages' early exit */
        do {
            pressed = PAD.getPressed(0);
            page = task->page;
            if (task->pageCount != 0) {
                if (pressed & (1 << PAD_L1)) {
                    if (--task->page < 0) {
                        task->page = 0;
                    }
                } else if (pressed & (1 << PAD_R1)) {
                    if (++task->page > task->pageCount - 1) {
                        task->page = task->pageCount - 1;
                    }
                }
            }
            if (page != task->page) {
                ((Unk8009A098 *)windows[0])->sel = 0;
                lines = task->count - task->page * 6;
                if (lines > 6) {
                    lines = 6;
                }
                ((Unk8009A098 *)windows[0])->params.count = lines;
                func_80095660(task, windows);
                SOUND.playSound(0x4001B);
            } else if (task->sel != ((Unk8009A098 *)windows[0])->sel) {
                func_80095660(task, windows);
            } else if (pressed & (1 << PAD_CROSS)) {
                SOUND.playSound(0x4001C);
                if (task->count != 0) {
                    active = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                    /* the match depends on the choice written in both branches */
                    if (active->unk1A != 0) {
                        *task->unk50 = task->techs[task->page * 6 + ((Unk8009A098 *)windows[0])->sel] & 0x1FFF;
                        task->setState(task, 3);
                        ((Unk8009A098 *)windows[0])->locked = 1;
                        break;
                    }
                    mp = D_800A3308.unkE8(0, task->techs[task->page * 6 + ((Unk8009A098 *)windows[0])->sel]);
                    if (active->mp >= mp) {
                        active->mp -= mp;
                        *task->unk50 = task->techs[task->page * 6 + ((Unk8009A098 *)windows[0])->sel] & 0x1FFF;
                        task->setState(task, 3);
                        ((Unk8009A098 *)windows[0])->locked = 1;
                        break;
                    }
                }
            } else if (pressed & (1 << PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                *task->unk50 = -2;
                task->setState(task, 3);
                break;
            }
            task->sel = ((Unk8009A098 *)windows[0])->sel;
        } while (0);
        break;
    case 2:
    case 3:
        break;
    }
}

Unk80095AC0 *func_8009619C(s32 *arg0) {
    Unk80095AC0 *task = createTask(func_80095AC0, sizeof(Unk80095AC0), 16 * sizeof(Task *));

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

/* The battle's partner switch menu: the other two fighters, or a message
   when there is none */
void func_800967A4(Unk800967A4 *task, Unk800967A4Windows *w) {
    SpriteDrawer drawer;
    BattleFighter *fighters;
    BattleFighter *fighter;
    s32 pressed;
    s32 sel;
    s32 active;
    s32 temporary;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        active = D_800A31E8.active[0];
        fighters = D_800A31E8.fighters[0];
        temporary = fighters[active].unk1A;
        for (i = 0; i < 3; i++) {
            if (fighters[i].id != 0 && i != D_800A31E8.active[0]) {
                task->unk5C[task->count] = i;
                if (task->unk58 != 0 && temporary == 0) {
                    task->unk74[task->count] = func_800961DC(task, D_800A31E8.active[0], i);
                }
                task->count++;
            }
        }
        if (task->count > 0) {
            D_800A22FC.count = task->count;
            w->cursor = func_8009A214(&D_800A22FC);
            w->cursor->sel = *task->unk54;
            func_800963D4(task, w);
            func_800965D4(task, w);
            task->nextState(task);
        } else {
            w->message = createTextWindow(0x1005, 1, 0x14, 0xC2);
            w->message->setVisible(w->message, 0);
            task->setState(task, 2);
        }
        break;
    case TASK_RUN:
        func_800962F8(task);
        /* the match depends on the do-while and its break, the stages' early exit */
        do {
            pressed = PAD.getPressed(0);
            if (task->unk58 != 0 && (pressed & (1 << PAD_TRIANGLE))) {
                SOUND.playSound(0x800450BD);
                *task->unk50 = -2;
                task->setState(task, 3);
                break;
            }
            if (pressed & (1 << PAD_CROSS)) {
                SOUND.playSound(0x4001C);
                sel = w->cursor->sel;
                fighter = &D_800A31E8.fighters[0][task->unk5C[sel]];
                if (fighter->hp != 0) {
                    *task->unk54 = sel;
                    *task->unk50 = task->unk5C[w->cursor->sel];
                    task->setState(task, 3);
                    w->cursor->locked = 1;
                }
            }
        } while (0);
        break;
    case 2:
        if (PAD.getPressed(0) & (1 << PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            *task->unk50 = -2;
            task->setState(task, 3);
            w->message->setVisible(w->message, 0);
            break;
        }
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x1005, 1);
        if (task->unk68 != 0) {
            if (GFX.funcs.getTime() - task->unk6C >= 4) {
                task->unk6C = GFX.funcs.getTime();
                task->unk70++;
                if (task->unk70 >= 5) {
                    task->unk70 = 0;
                }
            }
            drawer.setTexture(0x140, 0);
            drawer.setClutRow(task->unk70);
            drawer.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 10, 0x123, 0xD0);
            drawer.setClutRow(0);
        } else {
            task->unk68 = 1;
        }
        drawer.setTexture(0x200, 0);
        drawer.draw(FILE_CACHE.getEntry(FILE_BATTLE_MENU << 16), 0x31, 0xB, 0xBC);
        if (!w->message->isVisible(w->message)) {
            w->message->setString(w->message, FILE_CACHE.load(TEXT_FILE(0x80)), 0x14);
        }
        break;
    case 3:
        break;
    }
}

Unk800967A4 *func_80096C8C(s32 *done, s32 *arg1, s32 arg2) {
    Unk800967A4 *task = createTask(func_800967A4, sizeof(Unk800967A4), 0x50);

    task->unk50 = done;
    *done = -1;
    task->unk54 = arg1;
    task->unk58 = arg2;
    return task;
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

/* The battle's two-step menu: one of a party member's Digimon (its own or a
   slot's), then the attack or the technique the two fighters have together */
void func_800973D4(Unk800973D4 *task, Unk800973D4Windows *w) {
    BattleFighter *active;
    BattleFighter *other;
    DigimonData *data;
    DigimonData *partner;
    s32 member;
    s32 pressed;
    s32 count;
    s32 changed;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        member = task->unk60;
        GAME.funcs.getPartnerSlots(member, task->slots);
        count = 1;
        task->ids[0] = DIGIMON_DATA[member].id;
        for (i = 0; i < 3; i++) {
            if (task->slots[i] >= 3) {
                task->ids[count] = task->slots[i];
                count++;
            }
        }
        task->count = count;
        D_800A231C[0].count = count;
        func_80096DB8(task, w);
        task->unk58 = -1;
        task->nextState(task);
        /* fallthrough */
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                w->cursor = func_8009A214(&D_800A231C[0]);
                w->cursor->sel = task->unk64;
                if (w->techCursor != NULL) {
                    w->techCursor->setState(w->techCursor, 3);
                }
                task->nextStep(task);
                break;
            case 1:
                /* the match depends on the do-while and its breaks, the stages' early
                   exit, here and in the technique menu below */
                do {
                    pressed = PAD.getPressed(0);
                    if (pressed & (1 << PAD_TRIANGLE)) {
                        SOUND.playSound(0x800450BD);
                        *task->unk50 = -2;
                        task->setState(task, 3);
                        break;
                    }
                    if (pressed & (1 << PAD_CROSS)) {
                        SOUND.playSound(0x4001C);
                        task->nextSubstate(task);
                        func_80096EE0(task, w, 0);
                        w->cursor->locked = 1;
                        break;
                    }
                    if (pressed & (1 << PAD_R1)) {
                        if (++task->unk54 == 3) {
                            task->unk54 = 0;
                        }
                        SOUND.playSound(0x4001B);
                        break;
                    }
                    if (pressed & (1 << PAD_L1)) {
                        if (--task->unk54 < 0) {
                            task->unk54 = 2;
                        }
                        SOUND.playSound(0x4001B);
                        break;
                    }
                    func_80096EE0(task, w, 1);
                    func_80097000(task, w, 0);
                } while (0);
                break;
            }
            break;
        case 1:
            switch (task->step) {
            case 0:
            default:
                if (D_800A31E8.fighters[0][D_800A31E8.active[0]].unk1A == 0) {
                    data = ON_PARTNER_ENTRY_ADDED(D_800A31E8.fighters[0][D_800A31E8.active[0]].id);
                    partner = ON_PARTNER_ENTRY_ADDED(task->ids[task->unk64]);
                    if (data->unk3D != 0 && data->unk3D == partner->nameId) {
                        task->tech = data->unk2A;
                    } else {
                        task->tech = 0;
                    }
                }
                /* the match depends on the ?: */
                D_800A231C[1].count = task->tech != 0 ? 2 : 1;
                w->techCursor = func_8009A214(&D_800A231C[1]);
                if (w->cursor != NULL) {
                    w->cursor->setState(w->cursor, 3);
                }
                task->nextStep(task);
                break;
            case 1:
                do {
                    pressed = PAD.getPressed(0);
                    if (pressed & (1 << PAD_CROSS)) {
                        active = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
                        other = &D_800A31E8.fighters[0][task->unk5C];
                        SOUND.playSound(0x4001C);
                        if (w->techCursor->sel == 0) {
                            if (!(active->flags & 0x10) && !(other->flags & 0x10)) {
                                *task->unk50 = 0;
                                *task->unk50 |= task->ids[task->unk64] << 4;
                                task->setSubstate(task, 0);
                                func_80097000(task, w, 0);
                                w->techCursor->locked = 1;
                            }
                        } else if (active->mp >= D_800427E8[task->tech - 1].mp && other->mp >= D_800427E8[task->tech - 1].mp &&
                                   !(active->flags & 0x20) && !(other->flags & 0x20) && !(active->flags & 8) && active->hp > 0 &&
                                   other->hp > 0) {
                            active->mp -= D_800427E8[task->tech - 1].mp;
                            other->mp -= D_800427E8[task->tech - 1].mp;
                            *task->unk50 = w->techCursor->sel;
                            *task->unk50 |= task->ids[task->unk64] << 4;
                            *task->unk80 = task->tech;
                            task->setSubstate(task, 0);
                            func_80097000(task, w, 0);
                            w->techCursor->locked = 1;
                        }
                        break;
                    }
                    if (pressed & (1 << PAD_TRIANGLE)) {
                        SOUND.playSound(0x800450BD);
                        task->setSubstate(task, 0);
                        func_80097000(task, w, 0);
                        break;
                    }
                    if (pressed & (1 << PAD_R1)) {
                        if (++task->unk54 == 3) {
                            task->unk54 = 0;
                        }
                        SOUND.playSound(0x4001B);
                        break;
                    }
                    if (pressed & (1 << PAD_L1)) {
                        if (--task->unk54 < 0) {
                            task->unk54 = 2;
                        }
                        SOUND.playSound(0x4001B);
                        break;
                    }
                    func_80096EE0(task, w, 0);
                    func_80097000(task, w, 1);
                } while (0);
                break;
            }
            func_80096CEC(task);
            break;
        }
        if (task->unk58 != task->unk54) {
            changed = 1;
        } else if (w->cursor == NULL) {
            changed = 0;
        } else if (task->unk64 != w->cursor->sel) {
            task->unk64 = w->cursor->sel;
            changed = 1;
        } else {
            changed = 0;
        }
        if (changed) {
            task->unk58 = task->unk54;
            if (w->unk8 != NULL) {
                w->unk8->setState(w->unk8, 2);
                w->unkC = func_80094754(task->unk60, task->unk54, task->unk64);
            } else {
                if (w->unkC != NULL) {
                    w->unkC->setState(w->unkC, 2);
                }
                w->unk8 = func_80094754(task->unk60, task->unk54, task->unk64);
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Unk800973D4 *func_80097B74(s32 *arg0) {
    Unk800973D4 *task = createTask(func_800973D4, sizeof(Unk800973D4), 17 * sizeof(Task *));

    task->unk50 = arg0;
    task->unk5C = *arg0;
    task->unk60 = GAME_FUNCS.getPartyMember(*arg0);
    *arg0 = -1;
    return task;
}

Unk800973D4 *func_80097BEC(s32 *arg0, s32 *arg1) {
    Unk800973D4 *task = func_80097B74(arg0);

    task->unk80 = arg1;
    return task;
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

Unk80097F8C *func_80099400(void) {
    Unk80097F8C *task = createTask(func_80097F8C, sizeof(Unk80097F8C), 8);

    task->unkAC = func_80098808;
    task->unkB0 = func_800993BC;
    return task;
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

Unk800999E4 *func_80099CC0(s32 *done, Task *arg1, Task *arg2) {
    Unk800999E4 *task = createTask(func_800999E4, sizeof(Unk800999E4), 0x1C);

    task->unk58 = done;
    *done = -1;
    task->unk50 = 0;
    task->unk5C = arg1;
    task->unk60 = arg2;
    return task;
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

MoveTask *func_8009A79C(ModelControl *control, ShortVec3 *to, s32 time) {
    MoveTask *task = createTask(func_8009A638, sizeof(MoveTask), 0);

    task->control = control;
    task->to = *to;
    task->from = control->pos;
    task->t = 0;
    task->tStep = 0x1000 / time;
    return task;
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

/* fightstg.c defines it as a u16 array */
extern EventDelay D_800A310C[];

s32 func_8009AEA4(u8 side, s32 kind) {
    s32 delay;

    /* the match depends on each case having its own row and stats */
    switch (kind) {
    case 2: {
        s32 row = side != 0;
        BattleStats *own = D_800A3308.computeStats(side, 1, D_800A31E8.active[row]);

        delay = RANDOM.next() % D_800A310C[kind].div + own->stats[2] * 10;
        break;
    }
    case 8:
        delay = RANDOM.next() % 8001;
        break;
    case 9: {
        s32 row = side != 0;
        BattleStats *own = D_800A3308.computeStats(side, 1, D_800A31E8.active[row]);
        BattleStats *other = D_800A3308.computeStats((side == 0) << 4, 0, D_800A31E8.active[1 - row]);

        delay = RANDOM.next() % D_800A310C[kind].div + 3000 + (own->stats[2] + D_800A25F0.funcs.unk1) * 8
              - (other->resist[8] + other->resist[4]) * 8;
        break;
    }
    case 10: {
        s32 row = side != 0;
        BattleStats *own = D_800A3308.computeStats(side, 1, D_800A31E8.active[row]);
        BattleStats *other = D_800A3308.computeStats((side == 0) << 4, 0, D_800A31E8.active[1 - row]);

        delay = RANDOM.next() % D_800A310C[kind].div + 3000 + (own->stats[2] + D_800A25F0.funcs.unk1) * 8
              - (other->resist[9] + other->resist[3]) * 8;
        break;
    }
    case 11: {
        s32 row = side != 0;
        BattleStats *own = D_800A3308.computeStats(side, 1, D_800A31E8.active[row]);
        BattleStats *other = D_800A3308.computeStats((side == 0) << 4, 0, D_800A31E8.active[1 - row]);

        delay = RANDOM.next() % D_800A310C[kind].div + 1000 + (own->stats[2] + D_800A25F0.funcs.unk1) * 8
              - (other->resist[10] + other->resist[2]) * 8;
        break;
    }
    case 12: {
        s32 row = side != 0;
        BattleStats *own = D_800A3308.computeStats(side, 1, D_800A31E8.active[row]);

        delay = RANDOM.next() % D_800A310C[kind].div + 2000 + own->stats[2] * 10;
        break;
    }
    default: {
        s32 row = side != 0;
        BattleStats *own = D_800A3308.computeStats(side, 1, D_800A31E8.active[row]);
        BattleStats *other = D_800A3308.computeStats(0x10 - side, 0, D_800A31E8.active[1 - row]);
        s32 square = own->stats[4] * other->stats[4];
        s32 root = 999;
        s32 i;

        /* Newton's square root */
        for (i = 0; i < 10; i++) {
            root = (root + square / root) / 2;
        }
        delay = D_800A310C[kind].div * other->stats[4] / root;
        break;
    }
    }
    if (D_800A310C[kind].min != 0 && delay < D_800A310C[kind].min) {
        delay = D_800A310C[kind].min;
    }
    if (D_800A310C[kind].max != 0 && delay > D_800A310C[kind].max) {
        delay = D_800A310C[kind].max;
    }
    return delay;
}

/* An item's cure (D_800A25F0.funcs.useItem): items 0xBE-0xC5 clear a status of the
   fighter and remove its events, 0xC4 and 0xC5 all of them */
void func_8009B430(u8 side, s32 fighter, s32 item) {
    s32 kind;
    s32 index;
    BattleFighter *fighters;
    s32 i;
    s32 row;

    switch (item) {
    case 0xBE:
    case 0xBF:
    default:
        kind = 0;
        break;
    case 0xC0:
    case 0xC1:
        kind = 1;
        break;
    case 0xC2:
    case 0xC3:
        kind = 2;
        break;
    case 0xC4:
    case 0xC5:
        kind = 3;
        break;
    }
    /* the match depends on the row local, and on kind becoming the event type */
    row = side != 0;
    fighters = D_800A31E8.fighters[row];
    if (fighters[fighter].id == 0) {
        return;
    }
    fighters[fighter].flags &= ~D_800A3164[kind];
    if (kind != 3) {
        kind = D_800A315C[kind];
        index = D_800A25F0.funcs.find(kind, side, fighter);
        if (index >= 0) {
            D_800A25F0.events[index].type = 0;
        }
    } else {
        for (i = 0; i < 6; i++) {
            index = D_800A25F0.funcs.find(D_800A315C[i], side, fighter);
            if (index >= 0) {
                D_800A25F0.events[index].type = 0;
            }
        }
    }
}

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

void func_8009B9B0(u8 side, s32 unused, u8 arg2) {
    s32 other = side != 0;
    s32 i = FIGHTSTG_findEvent(10, side, D_800A31E8.active[other]);
    s32 time;
    BattleFighter *entry;

    D_800A25F0.funcs.unk1 = arg2;
    time = func_8009AEA4(side, 9);
    if (i >= 0) {
        D_800A25F0.events[i].time = time;
    } else {
        D_800A34E0.type = 10;
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = D_800A31E8.active[other];
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
    entry = &D_800A31E8.fighters[other][D_800A31E8.active[other]];
    entry->unk1D = arg2;
    entry->flags |= 2;
}

void func_8009BAC0(u8 side, s32 arg1, u8 arg2) {
    s32 other = side != 0;
    s32 i = FIGHTSTG_findEvent(11, side, D_800A31E8.active[other]);
    s32 time;
    BattleFighter *entry;

    if (arg1 == 0) {
        time = func_8009AEA4(side, 8);
    } else {
        D_800A25F0.funcs.unk1 = arg2;
        time = func_8009AEA4(side, 10);
    }
    if (i >= 0) {
        D_800A25F0.events[i].time = time;
    } else {
        D_800A34E0.type = 11;
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = D_800A31E8.active[other];
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
    entry = &D_800A31E8.fighters[other][D_800A31E8.active[other]];
    entry->unk1F = arg2;
    entry->flags |= 4;
}

void func_8009BC10(u8 side, s32 unused, u8 arg2) {
    s32 other = side != 0;
    s32 i = FIGHTSTG_findEvent(12, side, D_800A31E8.active[other]);
    s32 time;
    BattleFighter *entry;

    D_800A25F0.funcs.unk1 = arg2;
    time = func_8009AEA4(side, 11);
    if (i >= 0) {
        D_800A25F0.events[i].time = time;
    } else {
        D_800A34E0.type = 12;
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = D_800A31E8.active[other];
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
    entry = &D_800A31E8.fighters[other][D_800A31E8.active[other]];
    entry->unk1E = arg2;
    entry->flags |= 8;
}

void func_8009BD20(u8 side, s32 fighter, s32 kind, s32 arg3) {
    s32 i = FIGHTSTG_findEvent(D_800A3168[kind], side, fighter);
    s32 time;

    if (arg3 != 0) {
        time = func_8009AEA4(side, 12);
    } else {
        time = func_8009AEA4(side, 8);
    }
    if (i >= 0) {
        D_800A25F0.events[i].time = time;
    } else {
        D_800A34E0.type = D_800A3168[kind];
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = side;
        D_800A34E0.args[1] = fighter;
        D_800A34E0.args[2] = kind;
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
}

void func_8009BE1C(s32 tech) {
    Unk800427D6 *entry = &D_800427D6[tech];
    s32 kind;
    s32 fighter;
    s32 i;
    s32 time;
    BattleFighter *target;

    kind = 0;
    if (entry->unkA != 13) {
        kind = entry->unkA == 14;
    }
    fighter = D_800A31E8.active[0];
    i = FIGHTSTG_findEvent(D_800A3174[kind], 0, fighter);
    time = (RANDOM.next() % 101 + 100) * entry->unkC;

    if (i >= 0) {
        QueuedEvent *queued = &D_800A25F0.events[i];

        queued->time = time;
    } else {
        D_800A34E0.type = D_800A3174[kind];
        D_800A34E0.delay = time;
        D_800A34E0.args[0] = 0;
        D_800A34E0.args[1] = fighter;
        D_800A34E0.args[2] = kind;
        FIGHTSTG_pushEvent(&D_800A34E0);
    }
    target = &D_800A31E8.fighters[0][fighter];
    if (kind == 0) {
        target->flags |= 0x10;
    } else {
        target->flags |= 0x20;
    }
}

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

/* When unkBC allows it, the action's unk2C becomes its damage times a 128th of
 * the technique's unkC (kind 8) or the player's unk30[6], doubled when the
 * acting fighter's unk1B is set. The match depends on each branch doubling
 * and scaling its own value. */
void func_8009C764(void) {
    BattleAction *action = &D_800A317C;
    Battle800A3308 *funcs = &D_800A3308;
    s32 side = action->unk20 != 0;
    BattleFighter *fighter = &D_800A31E8.fighters[side][D_800A31E8.active[side]];
    Unk800427D6 *entry;
    s32 value;

    if (funcs->unkBC(action->unk20, action->unk24)) {
        entry = &D_800427D6[action->unk24];
        if (entry->unkA == 8) {
            value = entry->unkC;
            if (fighter->unk1B) {
                value *= 2;
            }
            action->unk2C = action->damage * value / 128;
        } else {
            value = funcs->stats[0].unk30[6];
            if (fighter->unk1B) {
                value *= 2;
            }
            action->unk2C = action->damage * value / 128;
        }
        D_800A317C.unk38[8] = 1;
    }
}

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

/* Lowers stat 0 of the other side's active fighter by the technique's unkC
 * percent and starts its event (not when side 0 acts with
 * D_80042728.unk3E[8] set). The match depends on team being a u8. */
void func_8009C998(void) {
    u8 team = D_800A317C.unk20 != 0;
    Unk800427D6 *entry;

    if (team == 0 && D_80042728.unk3E[8] != 0) {
        return;
    }
    entry = &D_800427D6[D_800A317C.unk24];
    D_800A3308.unkE0((u8)(0x10 - D_800A317C.unk20), D_800A31E8.active[1 - team], 0, -entry->unkC);
    func_8009BD20((u8)(0x10 - D_800A317C.unk20), D_800A31E8.active[1 - team], 0, D_800A317C.unk24);
    D_800A317C.unk38[entry->unkA] = entry->unkC;
}

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


void func_8009D204(u8 side, s32 tech) {
    Unk800427D6 *entry;

    HEAP.zero(&D_800A317C, 0x68);
    entry = &D_800427D6[tech];
    D_800A317C.unk20 = side;
    D_800A317C.unk24 = tech;
    if (entry->unkA == 0x1F) {
        func_8009CF18();
    } else if (entry->unkA == 0x23) {
        func_8009CFF4();
    } else {
        /* the match depends on the fighter's pointer sum */
        if (entry->unkA == 10 &&
            (side == 0 || D_800A2584((D_800A31E8.fighters[1] + D_800A31E8.active[1])->id)->unk8[0] != tech)) {
            func_8009C874();
            return;
        }
        switch (entry->unk4) {
        case 2:
            D_800A317C.hits[0] = D_800A3308.unk9C(side, tech);
            D_800A317C.unk36++;
            D_800A317C.damage = D_800A3308.unk84(side, tech);
            /* the match depends on the second test of unkA 9, which the
               compiler merges with the first and with case 3's */
            if (side == 0) {
                if (entry->unkA < 2) {
                    if (entry->unk10 == 11 || entry->unk10 == 12) {
                        break;
                    }
                    if (D_800A3308.stats[0].unk30[7]) {
                        func_8009C60C();
                        break;
                    }
                    if (D_800A317C.hits[0] == 0) {
                        break;
                    }
                    if (D_800A3308.stats[0].unk2D) {
                        func_8009C294();
                    }
                    if (D_800A3308.stats[0].unk2F) {
                        func_8009C330();
                    }
                    if (D_800A3308.stats[0].unk30[1]) {
                        func_8009C418();
                    }
                    if (D_800A3308.stats[0].unk30[3]) {
                        func_8009C5C4();
                    }
                    if (D_800A3308.stats[0].unk30[5]) {
                        func_8009C764();
                    }
                } else if (entry->unkA == 9) {
                    func_8009C60C();
                } else if (D_800A317C.hits[0]) {
                    func_8009D0B0();
                }
            } else if (entry->unkA >= 2) {
                if (entry->unkA == 9) {
                    func_8009C60C();
                } else if (D_800A317C.hits[0]) {
                    func_8009D0B0();
                }
            }
            break;
        case 3:
            D_800A317C.hits[0] = D_800A3308.unkA0(side, tech);
            D_800A317C.unk36++;
            D_800A317C.damage = D_800A3308.unk88(side, tech);
            if (entry->unkA < 2) {
                break;
            }
            if (entry->unkA == 9) {
                func_8009C60C();
            } else if (D_800A317C.hits[0]) {
                func_8009D0B0();
            }
            break;
        }
    }
    if (D_800A31E8.unkD6 != 0) {
        D_800A317C.damage = func_800A9A40(side, D_800A317C.damage, D_800A317C.unk38[9] ? D_800A317C.unk34 : 0);
    }
}

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

/* A Gouraud-shaded quad on a layer, blended when semi is set; the match
   depends on setSemiTrans inside the if and on poly moving on past it */
void func_8009D8B4(s32 layerId, s32 depth, DVECTOR *xy, CVECTOR *colors, s32 semi) {
    Layer *layer = GFX.funcs.getLayer(layerId);
    u_long *ot = (u_long *)layer->getOtEntry(layer, depth);
    POLY_G4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    *(CVECTOR *)&poly->r0 = colors[0];
    *(CVECTOR *)&poly->r1 = colors[1];
    *(CVECTOR *)&poly->r2 = colors[2];
    *(CVECTOR *)&poly->r3 = colors[3];
    setPolyG4(poly);
    if (semi) {
        setSemiTrans(poly, 1);
    }
    poly->x0 = xy[0].vx;
    poly->x1 = xy[1].vx;
    poly->x2 = xy[2].vx;
    poly->x3 = xy[3].vx;
    poly->y0 = xy[0].vy;
    poly->y1 = xy[1].vy;
    poly->y2 = xy[2].vy;
    poly->y3 = xy[3].vy;
    addPrim(ot, poly);
    poly++;
    if (semi) {
        mode = (DR_TPAGE *)poly;
        setlen(mode, 1);
        mode->code[0] = 0xE1000245;
        addPrim(ot, mode);
        poly = (POLY_G4 *)(mode + 1);
    }
    GFX.funcs.setPrim(poly);
}

void func_8009DA88(s32 arg0, s32 arg1, DVECTOR *arg2, CVECTOR *arg3) {
    func_8009D8B4(arg0, arg1, arg2, arg3, 0);
}

void func_8009DAA8(s32 arg0, s32 arg1, DVECTOR *arg2, CVECTOR *arg3) {
    func_8009D8B4(arg0, arg1, arg2, arg3, 1);
}

/* the match depends on reaching the cache through the symbol until a fighter
   is found, and on each branch storing and returning its own info */
FighterInfo *FIGHTSTG_getFighterInfo(s32 id) {
    FightersFile *file;
    FighterEntry *entry;
    u8 *partners;
    u8 *enemies;
    FighterCache *cache;
    FighterInfo *info;
    s32 i;

    if (id == D_800A32E0.id) {
        if (D_800A32E0.unk4) {
            return D_800A32E0.info;
        }
        return D_800A32E0.unk10;
    }
    file = (FightersFile *)FILE_CACHE.load(FILE_FIGHTERS);
    entry = (FighterEntry *)((u8 *)file + file->entries);
    partners = (u8 *)file + file->partners;
    enemies = (u8 *)file + file->enemies;
    while (entry->id != 0) {
        if (entry->id == id) {
            D_800A32E0.id = id;
            cache = &D_800A32E0;
            cache->unk8 = i = entry->index;
            cache->unkC = entry->kind;
            cache->unk4 = entry->kind >= 0x3A;
            if (cache->unk4) {
                info = (FighterInfo *)(enemies + i * 0x48);
                cache->unk10 = info;
                cache->info = info;
                return info;
            } else {
                info = (FighterInfo *)(partners + i * 0xC4);
                cache->unk10 = info;
                cache->info = info;
                return info;
            }
        }
        entry++;
    }
    return NULL;
}

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

s32 func_8009E7E4(u8 side, s32 id, s32 value) {
    Unk800427D6 *tech = &D_800427D6[id];
    BattleStats *user = &D_800A3308.stats[0];
    BattleStats *target = &D_800A3308.stats[1];
    s32 result = value;
    s32 i;

    result += func_8009E74C(result, tech->unk7);
    if (tech->unk9 >= 2) {
        if (tech->unk9 == target->unk25) {
            result += result / 2;
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (user->unk28[i] >= 2 && user->unk28[i] == target->unk25) {
                result += result / 2;
                break;
            }
        }
    }
    if (user->unk26 != 0) {
        result += result * user->unk26 / 64;
    }
    if (tech->unk7 >= 2) {
        result += result * tech->unk8 * 2 / target->resist[tech->unk7 - 2];
    } else if ((tech->unk10 < 11 || tech->unk10 > 12) && user->unk2B != 0) {
        result += result * user->unk2C * 2 / target->resist[user->unk2B - 2];
    }
    if (tech->unkA < 2 && user->unk30[7] != 0 && (tech->unk10 < 11 || tech->unk10 > 12)) {
        result = result * 4 / 10;
    }
    if (func_8009F36C(side, id) != 0) {
        result += result * ((RANDOM.next() & 0x3F) + 0x20) / 64;
    }
    if (target->unk27 != 0) {
        result -= target->unk27;
        if (result <= 0) {
            result = 0;
        }
    }
    if (result > value * 5) {
        result = value * 5;
    }
#if VERSION_EU
    if (result >= 10000) {
        result = 9999;
    }
#endif
    return result;
}

/* A technique's power from the user's stats[0] against the target's stats[1]
 * (an enemy's scaled by its unkA / 16), passed on to func_8009E7E4. The match
 * depends on the division in each branch. */
s32 func_8009EA74(u8 side, s32 id) {
    Unk800427D6 *tech;
    BattleStats *user;
    BattleStats *target;
    s32 value;
    s32 enemy;

    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    user = &D_800A3308.stats[0];
    tech = &D_800427D6[id];
    target = &D_800A3308.stats[1];
    if (side == 0) {
        value = tech->unk2 * user->stats[0] / target->stats[1];
    } else {
        enemy = D_800A31E8.active[1]; /* the match depends on reading it first */
        value = tech->unk2 * D_80042728.enemies[enemy].unkA / 16 * user->stats[0] /
                target->stats[1];
    }
    return func_8009E7E4(side, id, value);
}

s32 func_8009EBAC(u8 side, s32 id) {
    Unk800427D6 *tech;
    BattleStats *user;
    BattleStats *target;
    s32 base;
    s32 enemy;
    s32 power;
    s32 result;
    s16 resist;

    if (side == 0) {
        FIGHTSTG_computeStats(0, 1, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    } else {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
        FIGHTSTG_computeStats(0x10, 1, D_800A31E8.active[1]);
    }
    user = &D_800A3308.stats[0];
    tech = &D_800427D6[id];
    target = &D_800A3308.stats[1];
    if (side == 0) {
        base = tech->unk2;
    } else {
        enemy = D_800A31E8.active[1]; /* the match depends on reading it first */
        base = tech->unk2 * D_80042728.enemies[enemy].unkA / 16;
    }
    power = base * (user->stats[2] * 50 / target->stats[2] + 50) / 100;
    if (power > base * 2) {
        power = base * 2;
    }
    if (power < base / 2) {
        power = base / 2;
    }
    result = power;
    result += func_8009E74C(result, tech->unk7);
    if (tech->unk7 >= 2) {
        resist = target->resist[tech->unk7 - 2];
        if (resist < 100) {
            result = result * (400 - resist * 3) / 100;
        } else if (resist >= 300) {
            result = result * (65 - resist / 20) / 100;
        } else {
            result = result * (125 - resist / 4) / 100;
        }
    }
    if (tech->unk9 >= 2 && tech->unk9 == target->unk25) {
        result += result / 2;
    }
    if (func_8009F5D4(side, id) != 0) {
        result += result * (RANDOM.next() % 65 + 0x20) / 64;
    }
    if (target->unk27 != 0) {
        result -= target->unk27;
        if (result <= 0) {
            result = 0;
        }
    }
    if (result > power * 5) {
        result = power * 5;
    }
#if VERSION_EU
    if (result >= 10000) {
        result = 9999;
    }
#endif
    return result;
}

/* getDamage: the damage of an event (args: the side, the fighter and the
 * base damage) to the fighter if it is its side's active one, less a tenth of
 * its resist[1] and resist[7], as a part of its max HP: at least 1, at most
 * half the max HP. The match depends on the fighter pointer. */
s32 func_8009EF04(s32 *args) {
    u8 side;
    u8 team; /* the match depends on a u8 */
    s32 index;
    s32 damage;
    BattleStats *stats;
    s16 maxHp;
    BattleFighter *fighter;
    s32 result;

    side = args[0];
    index = args[1];
    damage = args[2];
    team = side != 0;
    if (index != D_800A31E8.active[team]) {
        return 0;
    }
    FIGHTSTG_computeStats(side, 0, index);
    stats = &D_800A3308.stats[1];
    fighter = &D_800A31E8.fighters[team][index];
    maxHp = fighter->maxHp;
    result = (damage / 2 - (stats->resist[7] + stats->resist[1]) / 10) * maxHp / 100;
    if (result <= 0) {
        result = 1;
    }
    if (result > maxHp / 2) {
        result = maxHp / 2;
    }
    return result;
}

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
/* D_800A3308.unkEU: a random test, likelier the bigger arg1 is next to the
   player's fighter's max HP */
s32 func_800A15A8(s32 arg0, s32 arg1) {
    BattleFighter *fighter = &D_800A31E8.fighters[0][D_800A31E8.active[0]];
    s32 chance = (arg1 << 6) / fighter->maxHp + 32;

    return (RANDOM.next() & 0x7F) < chance;
}
#endif

INCLUDE_ASM("fightstg/nonmatchings/fightstg_6", func_800A067C);

/* D_800A3308.unkD4: a random test for side, likelier the bigger value is next
   to the enemy's second stat, less likely the higher side's fighter's unk1E
   and the later its event of type 0xC is due. The match depends on the 64
   being set apart from unk1E's half and on the sum being written in one
   statement. */
s32 func_800A0830(u8 side, s32 value) {
    s32 team;
    s32 index;
    s32 chance;
    s16 delay;
    s32 luck;
    BattleStats *def;

    if (side == 0) {
        FIGHTSTG_computeStats(0, 0, D_800A31E8.active[0]);
    } else {
        FIGHTSTG_computeStats(0x10, 0, D_800A31E8.active[1]);
    }
    team = side != 0;
    def = &D_800A3308.stats[1];
    index = D_800A25F0.funcs.find(0xC, side, D_800A31E8.active[team]);
    chance = (value << 7) / def->stats[1];
    delay = D_800A25F0.events[index].time / 100;
    luck = 64;
    luck -= D_800A31E8.fighters[team][D_800A31E8.active[team]].unk1E >> 1;
    chance = chance + luck - delay;
    return (RANDOM.next() & 0x7F) < chance;
}

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

/* Returns value scaled by the sine of t (4096 is 1.0) on the given curve: 0 a
 * quarter of t, 1 the same as a cosine, 2 half of t. The match depends on a
 * return in each case; one shared return after the switch schedules the
 * epilogue differently. */
s32 func_800A0FDC(s32 curve, s32 t, s32 value) {
    switch (curve) {
    case 0:
    default:
        return rsin(t >> 2) * value / 4096;
    case 1:
        return rsin((t >> 2) + 0x400) * value / 4096;
    case 2:
        return rsin(t >> 1) * value / 4096;
    }
}
