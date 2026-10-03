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

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008C0BC);

void func_8008C8B8(s32 arg0) {
    ((Unk8008C0BC *)createTask(func_8008C0BC, sizeof(Unk8008C0BC), sizeof(Task *)))->unk50 = arg0;
}
