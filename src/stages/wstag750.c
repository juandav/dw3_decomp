#include "common.h"
#include "stage.h"
extern s32 D_800A6710[];
extern s32 D_800A658C[];
extern u8 D_800A6194[];
extern u8 D_800A66C4[];
extern u8 D_800A65C8[];
void func_800A4DB4();
extern void (*D_800A670C[])(void);
void func_800A50B4();
void func_800A59CC();
extern AnimFrame D_800A613C[];
extern AnimFrame D_800A6124[];
extern AnimFrame *D_800A6100[];
extern StageEffectSpot D_800A6118[];
StageEffect *func_800A58A0(s32 x, s32 y, s32 frame);
extern s8 D_800A610C[];
extern s8 D_800A6110[];
extern s16 D_800A6114[][2];

s32 func_800A4CA4(Anim4 *obj, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            return 0xFF;
        }
        func_800A4CA4(obj, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A4D7C(StageTileEffect *task) {
    s32 i;

    for (i = 0; i < 3; i++) {
        task->anims[i].anim.index = 0;
        task->anims[i].anim.timer = D_800A6100[i][0].duration;
    }
}

/* Moves its records to (x, y) and animates them when the substate is set to 1 */
void func_800A4DB4(StageTileEffect *task) {
    StageTile *tile;
    StageTile *t;
    s32 i;
    s32 n;
    s32 j;
    s32 frame;
    s32 done;

    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A4D7C(task);
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            switch (task->step) {
            case 0:
                n = 0;
                for (t = D_800990B4.unk10; t->unk2 != 0; t++) {
                    if (t->anim >= 1 && t->anim <= 3) {
                        task->anims[n].tile = t;
                        t->unkA = task->x;
                        t->unkC = task->y + D_800A6110[n];
                        t->unkE = task->y + D_800A610C[n];
                        n++;
                    }
                }
                SOUND.playSound(0x1000000);
                task->nextStep(task);
            case 1:
                done = 0;
                for (i = 0; i < 3; i++) {
                    tile = task->anims[i].tile;
                    frame = func_800A4CA4((Anim4 *)&task->anims[i], D_800A6100[i], 0);
                    switch (frame) {
                    case 0xFF:
                        done++;
                        tile->visible = 0;
                        tile->frame = 0;
                        break;
                    case 0x12C:
                        tile->visible = 0;
                        tile->frame = 0;
                        break;
                    default:
                        tile->visible = 1;
                        tile->frame = frame;
                        break;
                    }
                }
                if (done < 3) {
                    break;
                }
                task->nextStep(task);
            case 2:
                for (j = 0; j < 3; j++) {
                    task->anims[j].tile->visible = 0;
                }
                func_800A4D7C(task);
                task->setSubstate(task, 0);
                break;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Starts the effect at the place of map 0x335 */
void func_800A5034(StageTileEffect *task, s32 id) {
    s32 i;

    if (task != NULL) {
        i = 0;
        switch (id) {
        case 0x335:
            task->x = D_800A6114[i][0];
            task->y = D_800A6114[i][1];
            task->setSubstate(task, 1);
            break;
        }
    }
}

void *func_800A5084(s32 arg) {
    return createTaskWithId(func_800A4DB4, 0x70, 0, arg);
}

/* Creates the stage's effect, the event object of story progress 0x20 that applies, and another object */
void func_800A50B4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (D_800A6118[0].kind == 0) {
            children[0] = func_800A58A0(D_800A6118[0].x, D_800A6118[0].y, D_800A6118[0].frame);
        }
        if (GAME_PROGRESS == 0x20 && FLAGS_00.checkCondition(0x4048, 0) && FLAGS_00.checkCondition(0x4046, 0) &&
            FLAGS_00.checkCondition(0x4066, 0)) {
            children[2] = func_80084B80(0x35C);
        } else if (GAME_PROGRESS == 0x20 && FLAGS_00.checkCondition(0x4046, 1) && FLAGS_00.checkCondition(0x4048, 0) &&
                   FLAGS_00.checkCondition(0x4047, 0) && FLAGS_00.checkCondition(0x4066, 0)) {
            children[2] = func_80084B80(0x373);
        } else if (GAME_PROGRESS == 0x20 && FLAGS_00.checkCondition(0x4048, 1) && FLAGS_00.checkCondition(0x4046, 0) &&
                   FLAGS_00.checkCondition(0x4062, 0) && FLAGS_00.checkCondition(0x4066, 0)) {
            children[2] = func_80084B80(0x374);
        } else if (GAME_PROGRESS == 0x20 && FLAGS_00.checkCondition(0x4066, 1)) {
            children[2] = func_80084B80(0x376);
        }
        children[1] = func_800A5084(0x34E);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A52E8(void *owner) {
    StageTask *task = createTask(func_800A50B4, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A670C[0]();
    return task;
}

s32 func_800A5344(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        anim->timer -= dt;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A5344(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A5464(StageEffect *task, void *arg, s32 idx) {
    SpriteDrawer drawer;
    Layer *layer = arg;
    StageSprite *sprite = &task->sprites[idx];
    s32 y = task->y;
    s32 x = task->x;
    s32 depth;

    if (idx == 1) {
        y -= 0x20;
        depth = 4;
    } else {
        depth = 6;
    }
    initSpriteDrawer(&drawer);
    drawer.setTexture(0x140, 0x100);
    drawer.setLayer(layer, depth);
    drawer.setClutRow(sprite->clutRow);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), sprite->frame, x, y);
}

s32 func_800A554C(s32 x, s32 y, s32 w, s32 h) {
    RECT rect;
    struct Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getViewRect(layer, &rect);
    if (x + w < rect.x) {
        return 0;
    }
    if (rect.x + rect.w < x) {
        return 0;
    }
    if (y + h < rect.y) {
        return 0;
    }
    return rect.y + rect.h >= y;
}

void func_800A5610(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A613C[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A6124[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5344(&task->clutAnim, D_800A6124, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A554C(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5464, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A613C[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A6124[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5344(&task->clutAnim, D_800A6124, 0, 0);
        done = 0;
        frame = func_800A5344(&task->anim, D_800A613C, 1, 0);
        switch (frame) {
        case 0xFF:
            task->sprites[1].frame = 0;
            done = 1;
            break;
        case 0x12C:
            task->sprites[1].frame = 0;
            break;
        default:
            task->sprites[1].frame = task->frame + frame;
            break;
        }
        if (done) {
            task->setState(task, TASK_RUN);
        }
        if (task->sprites[0].frame != 0 && func_800A554C(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5464, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A554C(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A5464, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A58A0(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A5610, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

void func_800A58FC(void) {
    GAME_PROGRESS = 32;
}

void func_800A590C(void) {
    FLAGS_00.applyAction(0x4048, 1);
}

void func_800A5938(void) {
    FLAGS_00.applyAction(0x4047, 1);
}

void func_800A5964(void) {
    FLAGS_00.applyAction(0x4062, 1);
}

void func_800A5990(void) {
    GAME_PROGRESS = 33;
}

void func_800A59A0(void) {
    FLAGS_00.applyAction(0x7C0A, 1);
}

#if VERSION_US
void func_800A59CC(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x6B1;
    D_800990B4.unkC = 0x6B20000;
    D_800990B4.unk10 = D_800A65C8;
    D_800990B4.unk14 = D_800A66C4;
    D_800990B4.unk1C = 0x6B0;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x12A00;
    D_800990B4.unk30 = 0x1D200;
    D_800990B4.unk28 = D_800A6194;
    D_800990B4.unk3C = 0x40;
    D_800990B4.unk4C = D_800A658C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk40 = 0x61000001;
    D_800990B4.events = D_800A6710;
    D_8009A70C.setFile(0, 0x6B20001);
    D_8009A70C.setFile(7, 0x6B20002);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag750", func_800A59CC);
#endif

extern AnimFrame D_800A605C[];
extern AnimFrame D_800A60C0[];
extern AnimFrame D_800A6070[];
extern s32 D_800A6244[];
extern s32 D_800A624C[];
extern s32 D_800A6254[];
extern s32 D_800A6260[];
extern s32 D_800A6270[];
extern s32 D_800A627C[];
extern s32 D_800A628C[];
extern s32 D_800A6294[];
extern s32 D_800A6410[];
extern s32 D_800A629C[];
extern s32 D_800A62D8[];
extern s32 D_800A62F0[];
extern s32 D_800A641C[];
extern s32 D_800A6308[];
extern s32 D_800A6424[];
extern s32 D_800A6320[];
extern s32 D_800A642C[];
extern s32 D_800A6338[];
extern s32 D_800A6434[];
extern s32 D_800A6350[];
extern s32 D_800A643C[];
extern s32 D_800A6368[];
extern s32 D_800A6444[];
extern s32 D_800A6380[];
extern s32 D_800A644C[];
extern s32 D_800A6398[];
extern s32 D_800A6454[];
extern s32 D_800A63B0[];
extern s32 D_800A645C[];
extern s32 D_800A63C8[];
extern s32 D_800A6464[];
extern s32 D_800A63E0[];
extern s32 D_800A646C[];
extern s32 D_800A63F8[];
extern s32 D_800A6474[];
extern s32 D_800A6488[];
extern s32 D_800A649C[];
extern s32 D_800A64B0[];
extern s32 D_800A64C4[];
extern s32 D_800A64D8[];
extern s32 D_800A64EC[];
extern s32 D_800A6500[];
extern s32 D_800A6514[];
extern s32 D_800A6528[];
extern s32 D_800A653C[];
extern s32 D_800A6550[];
extern s32 D_800A6564[];
extern s32 D_800A6578[];
extern s32 D_800A5AC0[];
extern s32 D_800A5CB0[];
extern s32 D_800A5DE4[];
extern s32 D_800A5F14[];
extern s32 D_800A5F80[];
extern s32 D_800A5FE8[];

s32 D_800A5AC0[] = {
    0x20102, 0x12800A0, 0x1010003, 0x1000D,
    0x1010007, 0x337032D, 0x3020002, 0x1010002,
    0x10002, 0x1010003, 0x338032D, 0x3000002,
    0x1010078, 0x339032D, 0x3000002, 0x200001E,
    0x10000, 0x2000D, 0x3000301, 0x200001E,
    0x20000, 0x10002, 0x20101, 0x30007,
    0x1010301, 0x10002, 0x3000003, 0x101001E,
    0x9000D, 0x3030007, 0x101000D, 0x1000D,
    0x3000007, 0x200001E, 0x30000, 0x2000D,
    0x3000301, 0x101001E, 0x1000D, 0x3000003,
    0x102001E, 0x6F000D, 0x30110, 0xD0302,
    0xD0101, 0x30001, 0x1E0300, 0xD0101,
    0x30002, 0x780300, 0xD0101, 0x30001,
    0x5A0300, 0xD0101, 0x70001, 0x1E0300,
    0xD0102, 0x1190081, 0x3020007, 0x101000D,
    0x1000D, 0x3000007, 0x200001E, 0x40000,
    0x2000D, 0x3000301, 0x101001E, 0x3250323,
    0x3000002, 0x101005A, 0x3260323, 0x3000002,
    0x300001E, 0x200001E, 0x50000, 0x10002,
    0x20101, 0x30007, 0x1010301, 0x10002,
    0x3000003, 0x200001E, 0x60000, 0x2000D,
    0x3000301, 0x200001E, 0x70000, 0x10002,
    0x20101, 0x30007, 0x1010301, 0x10002,
    0x3000003, 0x200001E, 0x80000, 0x2000D,
    0x3000301, 0x101001E, 0x10002, 0x3000005,
    0x102001E, 0x1600002, 0x500C8, 0x20302,
    0x10601, 0xC80160, 0x20101, 0x50001,
    0x1E0300, 0x20101, 0x10001, 0x3C0300,
    0x34E0101, 0x20335, 0x780300, 0x20100,
    0, 0x20101, 0x10001, 0x3C0300,
    0x3C0300, 0x2DA0304, 0x37D045F, 1,
};
s32 D_800A5CB0[] = {
    0x10601, 0xE000F0, 0x20100, 0,
    0x20101, 1, 0xD0100, 0x1190081,
    0xD0101, 0x70001, 0x780300, 512,
    0x20001, 0x3010004, 1537, 0xF000D0,
    0x3230101, 0xD0325, 0x3C0300, 0x3230101,
    0xD0326, 0x1E0300, 0xD0102, 0x110006F,
    0x3020003, 0x101000D, 0x2000D, 0x3000003,
    0x601003C, 0xF00000, 0x30000E0, 0x101003C,
    0x335034E, 0x3000002, 0x1000078, 0x15E0002,
    0x10100CA, 0x10002, 0x3000001, 0x601005A,
    0xD00000, 0x20000F0, 0x20000, 0x2000D,
    0x6000301, 0x20000, 0xD0101, 0x70001,
    0x3C0300, 0xD0102, 0x1190081, 0x1010007,
    0x3250323, 0x3000002, 0x101003C, 0x3260323,
    0x3000002, 0x101001E, 0x10002, 0x3000003,
    0x101001E, 0x10002, 0x3000007, 0x101001E,
    0x10002, 0x3000001, 0x200001E, 0x30000,
    0x30002, 0x3000301, 0x200003C, 0x40000,
    0x30002, 0x3040301, 0x102DC, 1,
    0,
};
s32 D_800A5DE4[] = {
    0x10601, 0xE000F0, 0x20100, 0,
    0x20101, 1, 0xD0100, 0x1190081,
    0xD0101, 0x70001, 0x780300, 512,
    0x20003, 0x3010004, 1537, 0xF000D0,
    0x3230101, 0xD0325, 0x3C0300, 0x3230101,
    0xD0326, 0x1E0300, 0xD0102, 0x110006F,
    0x3020003, 0x101000D, 0x2000D, 0x3000003,
    0x601003C, 0xF00000, 0x30000E0, 0x101003C,
    0x335034E, 0x3000002, 0x1000078, 0x15E0002,
    0x10100CA, 0x10002, 0x3000001, 0x601005A,
    0xD00000, 0x20000F0, 0x10000, 0x2000D,
    0x6000301, 0x20000, 0xD0101, 0x70001,
    0x3C0300, 0xD0102, 0x1190081, 0x1010007,
    0x3250323, 0x3000002, 0x101003C, 0x3260323,
    0x3000002, 0x200001E, 0x40000, 0x20002,
    0x1010301, 0x3270323, 0x3000002, 0x101003C,
    0x3260323, 0x3000002, 0x200001E, 0x20000,
    0x20002, 0x20101, 0x70001, 0x3000301,
    0x304001E, 727, 0x10000, 0,
};
s32 D_800A5F14[] = {
    0x20100, 0xCA015E, 0x20101, 0x10001,
    0xD0100, 0x1190081, 0xD0101, 0x70001,
    0x780300, 512, 0x20001, 0x3010002,
    0x3230101, 0x20327, 0x3C0300, 0x20101,
    0x70001, 0x3230101, 0x20326, 0x1E0300,
    512, 0x20002, 0x3010002, 0x1E0300,
    0x2D70304, 0x640064, 0,
};
s32 D_800A5F80[] = {
    0x20100, 0xCA015E, 0x20101, 0x70001,
    0xD0100, 0x1190081, 0xD0101, 0x70001,
    0x780300, 512, 0x20001, 0x3010002,
    0x1E0300, 512, 0x20002, 0x1010002,
    0x10002, 0x3010001, 0x1E0300, 0x20102,
    0x12800A0, 0x3000001, 0x304003C, 0x3C0026A,
    0x70050, 0,
};
s32 D_800A5FE8[] = {
    0x20102, 0x1C80100, 0x1000003, 0xE00015,
    0x10101B9, 0x10015, 0x1010007, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000003,
    0x3000006, 0x200001E, 0x10000, 21,
    0x3000301, 0x101001E, 0x360015, 0x1010007,
    0x375032D, 0x3030002, 0x1010015, 0x370015,
    0x3000007, 0x304005A, 3080, 0,
    0,
};
AnimFrame D_800A605C[] = {
    { 70, 4 }, { 71, 4 }, { 70, 4 }, { 71, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A6070[] = {
    { 0x12C, 56 }, { 85, 6 }, { 86, 6 }, { 87, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 88, 4 },
    { 89, 4 }, { 90, 4 }, { 88, 4 }, { 89, 4 },
    { 90, 4 }, { 88, 4 }, { 89, 4 }, { 90, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A60C0[] = {
    { 0x12C, 16 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 73, 4 }, { 75, 6 }, { 76, 6 }, { 77, 14 },
    { 78, 114 }, { 79, 6 }, { 80, 6 }, { 81, 6 },
    { 82, 6 }, { 83, 6 }, { 84, 8 }, { 255, 0x3E7 },
};
AnimFrame *D_800A6100[] = {
    D_800A605C, D_800A60C0, D_800A6070,
};
s8 D_800A610C[] = {
    30, 30, 30, 0,
};
s8 D_800A6110[] = {
    0, -0x2F, -0x2F, 0,
};
s16 D_800A6114[][2] = {
    { 0x140, 186 },
};
StageEffectSpot D_800A6118[] = {
    { 28, 0, 108, 0x144 },
};
AnimFrame D_800A6124[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A613C[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
u8 D_800A6194[] = {
    0x00, 0x02, 0x00, 0x01, 0x1C, 0x02, 0xA6, 0x01,
    0x70, 0x00, 0xA6, 0x00, 0x30, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x16, 0x02, 0x38, 0x01,
    0x58, 0x00, 0x38, 0x00, 0x00, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x08, 0x02, 0xBC, 0x01,
    0x20, 0x00, 0xBC, 0x00, 0x10, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x10, 0x02, 0xBC, 0x01,
    0x40, 0x00, 0xBC, 0x00, 0x20, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0xBC, 0x01,
    0x00, 0x00, 0xBC, 0x00, 0x30, 0x02, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0xB0, 0x01,
    0xD8, 0x00, 0xB0, 0x00, 0x60, 0x01, 0xF8, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x64, 0x01, 0xC8, 0x01,
    0x90, 0x00, 0xC8, 0x00, 0x70, 0x01, 0xF8, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x4A, 0x01, 0xB0, 0x01,
    0x28, 0x00, 0xB0, 0x00, 0x50, 0x01, 0xF7, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x94, 0x01, 0x40, 0x01,
    0x50, 0x01, 0x40, 0x00, 0x60, 0x01, 0xF7, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x9C, 0x01, 0x48, 0x01,
    0x70, 0x01, 0x48, 0x00, 0x70, 0x01, 0xF7, 0x01,
};
s32 D_800A6244[] = {
    0, 65535,
};
s32 D_800A624C[] = {
    0x10000, 65535,
};
s32 D_800A6254[] = {
    32780, 0x10000, 65535,
};
s32 D_800A6260[] = {
    0x1800C, 7170, 0x10000, 65535,
};
s32 D_800A6270[] = {
    0x19045, 0x11C02, 65535,
};
s32 D_800A627C[] = {
    0x1800C, 0x11C02, 0x10000, 65535,
};
s32 D_800A628C[] = {
    0x17A27, 65535,
};
s32 D_800A6294[] = {
    0x19019, 65535,
};
s32 D_800A629C[] = {
    (s32)D_800A6244, (s32)D_800A624C, 779, (s32)D_800A6254,
    0, 780, (s32)D_800A6260, (s32)D_800A6270,
    781, (s32)D_800A627C, 0, 782,
    0, 0, 0,
};
s32 D_800A62D8[] = {
    0, (s32)D_800A628C, 363, 0,
    0, 0,
};
s32 D_800A62F0[] = {
    0, (s32)D_800A6294, 360, 0,
    0, 0,
};
s32 D_800A6308[] = {
    0, 0, 530, 0,
    0, 0,
};
s32 D_800A6320[] = {
    0, 0, 527, 0,
    0, 0,
};
s32 D_800A6338[] = {
    0, 0, 527, 0,
    0, 0,
};
s32 D_800A6350[] = {
    0, 0, 527, 0,
    0, 0,
};
s32 D_800A6368[] = {
    0, 0, 527, 0,
    0, 0,
};
s32 D_800A6380[] = {
    0, 0, 527, 0,
    0, 0,
};
s32 D_800A6398[] = {
    0, 0, 528, 0,
    0, 0,
};
s32 D_800A63B0[] = {
    0, 0, 529, 0,
    0, 0,
};
s32 D_800A63C8[] = {
    0, 0, 526, 0,
    0, 0,
};
s32 D_800A63E0[] = {
    0, 0, 526, 0,
    0, 0,
};
s32 D_800A63F8[] = {
    0, 0, 786, 0,
    0, 0,
};
s32 D_800A6410[] = {
    0x1700A, 28698, 65535,
};
s32 D_800A641C[] = {
    0x1602B, 65535,
};
s32 D_800A6424[] = {
    0x16021, 65535,
};
s32 D_800A642C[] = {
    0x16022, 65535,
};
s32 D_800A6434[] = {
    0x16023, 65535,
};
s32 D_800A643C[] = {
    0x16024, 65535,
};
s32 D_800A6444[] = {
    0x16025, 65535,
};
s32 D_800A644C[] = {
    0x16026, 65535,
};
s32 D_800A6454[] = {
    0x1701A, 65535,
};
s32 D_800A645C[] = {
    0x1601F, 65535,
};
s32 D_800A6464[] = {
    0x1601E, 65535,
};
s32 D_800A646C[] = {
    0x1701A, 65535,
};
s32 D_800A6474[] = {
    (s32)D_800A6410, (s32)D_800A629C, 0x4000D, 0x1190081,
    7,
};
s32 D_800A6488[] = {
    0, (s32)D_800A62D8, 0x50014, 0x1D900A2,
    7,
};
s32 D_800A649C[] = {
    0, (s32)D_800A62F0, 0x60015, 0x1B900E0,
    7,
};
s32 D_800A64B0[] = {
    (s32)D_800A641C, (s32)D_800A6308, 0x70023, 0x1C80132,
    7,
};
s32 D_800A64C4[] = {
    (s32)D_800A6424, (s32)D_800A6320, 0x70023, 0x1C80132,
    7,
};
s32 D_800A64D8[] = {
    (s32)D_800A642C, (s32)D_800A6338, 0x70023, 0x1C80132,
    7,
};
s32 D_800A64EC[] = {
    (s32)D_800A6434, (s32)D_800A6350, 0x70023, 0x1C80132,
    7,
};
s32 D_800A6500[] = {
    (s32)D_800A643C, (s32)D_800A6368, 0x70023, 0x1C80132,
    7,
};
s32 D_800A6514[] = {
    (s32)D_800A6444, (s32)D_800A6380, 0x70023, 0x1C80132,
    7,
};
s32 D_800A6528[] = {
    (s32)D_800A644C, (s32)D_800A6398, 0x70023, 0x1C80132,
    7,
};
s32 D_800A653C[] = {
    (s32)D_800A6454, (s32)D_800A63B0, 0x70023, 0x1C80132,
    7,
};
s32 D_800A6550[] = {
    (s32)D_800A645C, (s32)D_800A63C8, 0x70023, 0x1C80132,
    7,
};
s32 D_800A6564[] = {
    (s32)D_800A6464, (s32)D_800A63E0, 0x70023, 0x1C80132,
    7,
};
s32 D_800A6578[] = {
    (s32)D_800A646C, (s32)D_800A63F8, 0x8009D, 0x1190081,
    7,
};
s32 D_800A658C[] = {
    (s32)D_800A6474, (s32)D_800A6488, (s32)D_800A649C, (s32)D_800A64B0,
    (s32)D_800A64C4, (s32)D_800A64D8, (s32)D_800A64EC, (s32)D_800A6500,
    (s32)D_800A6514, (s32)D_800A6528, (s32)D_800A653C, (s32)D_800A6550,
    (s32)D_800A6564, (s32)D_800A6578, 0,
};
u8 D_800A65C8[] = {
    0x00, 0x01, 0x50, 0x06, 0x46, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x01, 0xBA, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x60, 0x01,
    0x60, 0x63, 0x06, 0x00, 0x44, 0x01, 0xA9, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x39, 0x02, 0x00, 0x0B, 0x08, 0x00, 0x4E, 0x00,
    0xE9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x39, 0x02, 0x00, 0x0B, 0x08, 0x00,
    0x5D, 0x00, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x39, 0x02, 0x00, 0x0B,
    0x08, 0x00, 0x6D, 0x00, 0xD9, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x3A, 0x02,
    0x00, 0x0B, 0x08, 0x00, 0x4E, 0x00, 0xDD, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x3A, 0x02, 0x00, 0x0B, 0x08, 0x00, 0x5D, 0x00,
    0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x3A, 0x02, 0x00, 0x0B, 0x08, 0x00,
    0x6D, 0x00, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x01, 0x32, 0x34,
    0x0A, 0x00, 0x52, 0x00, 0xEA, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x35, 0x01,
    0x35, 0x37, 0x0A, 0x00, 0x8B, 0x00, 0xE6, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x50, 0x04,
    0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01,
    0x8B, 0x00, 0xCE, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x50, 0x04, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x01, 0x8B, 0x00, 0xD5, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x5C, 0x01, 0x5C, 0x5F,
    0x06, 0x00, 0x44, 0x01, 0xB9, 0x00, 0xD1, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A66C4[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x6C, 0x02, 0xB8, 0x00, 0xB4, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0E, 0x00, 0x6A, 0x02, 0xC0, 0x03, 0x50, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A670C[])(void) = {
    func_800A59CC,
};
s32 D_800A6710[] = {
    820, (s32)D_800A5AC0,
#if VERSION_US
    0x1430019,
#elif VERSION_EU
    0x14A0019,
#endif
    0, (s32)func_800A58FC, 860, (s32)D_800A5CB0,
#if VERSION_US
    0x143001C,
#elif VERSION_EU
    0x14A001C,
#endif
    0, (s32)func_800A590C, 883, (s32)D_800A5DE4,
#if VERSION_US
    0x143001D,
#elif VERSION_EU
    0x14A001D,
#endif
    0, (s32)func_800A5938, 884, (s32)D_800A5F14,
#if VERSION_US
    0x143001E,
#elif VERSION_EU
    0x14A001E,
#endif
    0, (s32)func_800A5964, 886, (s32)D_800A5F80,
#if VERSION_US
    0x143001F,
#elif VERSION_EU
    0x14A001F,
#endif
    0, (s32)func_800A5990, 1245, (s32)D_800A5FE8,
#if VERSION_US
    0x1430008,
#elif VERSION_EU
    0x14A0008,
#endif
    0, (s32)func_800A59A0, -1, 0,
    0, 0, 0,
};
